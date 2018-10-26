#include "DCI.h"
#include "stdlib.h"
#include "stdio.h"
#include "gaps_head.h"

#include "../incl/FSJK_DZDJ.h"
#include "../incl/FSJK_DZMX.h"
#include "../incl/FSJK_FCMX.h"
#include "../incl/FSJK_RFMX.h"
#include "../incl/FSJK_ERRMSG.h"
#include "../incl/FSJK_CRC.h"



//查表法CRC校验码生成
unsigned short CRC16(unsigned char* puchMsg, unsigned short usDataLen)
{
	unsigned char uchCRCHi = 0xFF;
	unsigned char uchCRCLo = 0xFF;
	unsigned char uIndex;
	while(usDataLen--)
	{
		uIndex = uchCRCHi ^ *puchMsg++;
		uchCRCHi = uchCRCLo ^ auchCRCHi[uIndex];
		uchCRCLo = auchCRCLo[uIndex];
	}
	return(uchCRCHi << 8|uchCRCLo);
};

void convertStrToUnChar(char* str,unsigned char* UnChar)
{
	int j = 0;
	int i = strlen(str);
	for( j = 0; j < i ;j ++ )
	{
		UnChar[j] = str[j];
	}
	return;
}

/************************************************************************
动态组件函数定义
函数名称: FSJK_ZFPT_CHK_FA
名称: 支付平台对账文件入库
 
组件功能: 支付平台对账文件入库
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT FSJK_ZFPT_CHK_FA(HXMLTREE lXmlhandle)
{
  int iRet=0;
  int iResult=0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sChkDate[30+1];       /*对账日期*/
  char sChkFile[255+1];      /*文件名（带路径）*/
  char sSignDate[8+1];       /*登记日期*/
  char sSignTime[6+1];       /*登记时间*/
  double dPNAMOUNT=0.00;		 /*收费金额*/
  double dPNOVERDUEAMT=0.00; /*滞纳金*/
  double dAMOUNT=0.00;		   /*订单总金额*/
  char sOrgPaySerial[19+1];  /*原支付平台流水号*/
  char sOrgPayTime[14+1];		 /*原交易时间*/
  
  char sPNAMOUNT[20+1];      /*缴款通知书总金额*100（不含滞纳金）,用于计算校验码*/
  char sSRC[100+1];					 /*待计算字符串*/
  unsigned char uSRC[100+1]; /*待计算字符串 unsigned char*/
  unsigned short code;			 /*计算出的校验码*/
  char sCode[5+1];					 /*计算出的校验码 char*/
  int iCodeLen;							 /*校验码的长度*/
	int tmpi;
	int tmplen;

  FSJK_DZMX SDB_fsjk_dzmx;
  FSJK_RFMX SDB_fsjk_rfmx;
  
  
  FILE *fp;
  
  int transcnt=0;               /*交易笔数*/ 
  int refoundcnt=0;             /*退费笔数*/ 
  int detotcnt=0;               /*明细总笔数*/

 
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  
  memset(sChkFile, 0x00, sizeof(sChkFile));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "支付平台对账文件");
  trim(sBuffer);
  pstrcopy(sChkFile,sBuffer,sizeof(sChkFile));
  
  memset(sChkDate, 0x00, sizeof(sChkDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "对账日期");
  trim(sBuffer);
  pstrcopy(sChkDate,sBuffer,sizeof(sChkDate));
  
  memset(sSignDate, 0x00, sizeof(sSignDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(3, sBuffer, "登记日期");
  trim(sBuffer);
  pstrcopy(sSignDate,sBuffer,sizeof(sSignDate));
  
  memset(sSignTime, 0x00, sizeof(sSignTime));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(4, sBuffer, "登记时间");
  trim(sBuffer);
  pstrcopy(sSignTime,sBuffer,sizeof(sSignTime));
  
  LOG(LM_STD, Fmtmsg("支付平台对账文件[%s],对账日期[%s],登记日期[%s],登记时间[%s]", sChkFile, sChkDate, sSignDate, sSignTime), fpub_GetCompname(lXmlhandle)); 

  if(strlen(sChkFile) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "支付平台对账文件名不能为空");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("文件名不能为空！"), fpub_GetCompname(lXmlhandle))
      return COMPRET_FAIL ;
  }
  
  fp = fopen(sChkFile, "r");
  if ( fp == NULL )
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_FILE_FAIL, "支付平台对账文件打开失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("打开文件%s失败",sChkFile), fpub_GetCompname(lXmlhandle))
      return COMPRET_FAIL ;
  }

  while( !feof(fp) )
  {
  	 memset(sBuffer, 0x00, sizeof(sBuffer));     
     fgets(sBuffer, sizeof(sBuffer), fp);
     if( strlen(trim(sBuffer)) <= 0 )
         continue; 
     /*交易笔数*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,1,sTmp,'|','\\');
     trim(sTmp);
     transcnt=atoi(sTmp);
     LOG(LM_STD,Fmtmsg("交易笔数[%d]",transcnt ),"ERROR")
     
     /*退费笔数*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,2,sTmp,'|','\\');
     trim(sTmp);
     refoundcnt = atof(sTmp);
     LOG(LM_STD,Fmtmsg("退费笔数[%d]",refoundcnt ),"ERROR")
     
     break;
  }
  DCIBegin();
  //对账明细入库
  while( !feof(fp) )
  {
		memset(&SDB_fsjk_dzmx, 0x00, sizeof(SDB_fsjk_dzmx));
		memset(sBuffer, 0x00, sizeof(sBuffer));     
		fgets(sBuffer, sizeof(sBuffer), fp);
		if( strlen(trim(sBuffer)) <= 0 )
		   continue;
		
		detotcnt++;
		
		/*支付 和 退费 公共字段*/
		/*1-缴费渠道*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,1,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYCHANNEL,sTmp,sizeof(SDB_fsjk_dzmx.PAYCHANNEL)-1);
		
		/*4-支付平台流水号*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,4,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYSERIAL,sTmp,sizeof(SDB_fsjk_dzmx.PAYSERIAL)-1);
		
		/*5-清算日期*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,5,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYCLEARDATE,sTmp,sizeof(SDB_fsjk_dzmx.PAYCLEARDATE)-1);
		
		/*6-交易时间->支付平台交易时间*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,6,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYDATETIME,sTmp,sizeof(SDB_fsjk_dzmx.PAYDATETIME)-1);
		
		/*7-订单总金额（含滞纳金）*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,7,sTmp,'|','\\');
   	dAMOUNT = atof(sTmp);
   	SDB_fsjk_dzmx.AMOUNT=dAMOUNT;		
		
		/*9-区划代码*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,9,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.DISTRICTNO,sTmp,sizeof(SDB_fsjk_dzmx.DISTRICTNO)-1);
		
		/*10-执收单位编码*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,10,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.UNITNO,sTmp,sizeof(SDB_fsjk_dzmx.UNITNO)-1);
		if(strlen(SDB_fsjk_dzmx.UNITNO) <= 0)
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "支付平台对账文件执收单位编码编码不能为空"), "INFO" );
			fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "支付平台对账文件执收单位编码编码不能为空");
			break;
		}
		 
		/*11-缴款通知书号码*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,11,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYNOTENO,sTmp,sizeof(SDB_fsjk_dzmx.PAYNOTENO)-1); 
		if(strlen(SDB_fsjk_dzmx.PAYNOTENO) <= 0)
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "支付平台对账文件缴款通知书号码不能为空"), "INFO" );
			fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "支付平台对账文件缴款通知书号码不能为空");
			break;
		}
		
		/*12-缴款人*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,12,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.PAYERNAME,sTmp,sizeof(SDB_fsjk_dzmx.PAYERNAME)-1);
		
		/*13-收费金额*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,13,sTmp,'|','\\');
   	dPNAMOUNT = atof(sTmp);
   	SDB_fsjk_dzmx.PNAMOUNT=dPNAMOUNT;
		
		/*14-滞纳金*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,14,sTmp,'|','\\');
   	dPNOVERDUEAMT = atof(sTmp);
   	SDB_fsjk_dzmx.PNOVERDUEAMT=dPNOVERDUEAMT;
					
		/*15-票据类型编码*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,15,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.RECEIPTTYPENO,sTmp,sizeof(SDB_fsjk_dzmx.RECEIPTTYPENO)-1);
		
		/*16-票据号码*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,16,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.RECEIPTNO,sTmp,sizeof(SDB_fsjk_dzmx.RECEIPTNO)-1);
		
		/*17-收费项目数量*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,17,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.ITEMNUMBER,sTmp,sizeof(SDB_fsjk_dzmx.ITEMNUMBER)-1);

		/*31-备注1*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,31,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.REMARK1,sTmp,sizeof(SDB_fsjk_dzmx.REMARK1)-1);
		
		/*32-备注2*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,32,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.REMARK2,sTmp,sizeof(SDB_fsjk_dzmx.REMARK2)-1);
		
		/*33-备注3*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,33,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_dzmx.REMARK3,sTmp,sizeof(SDB_fsjk_dzmx.REMARK3)-1);
		
		/*取出退费标志*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,2,sTmp,'|','\\');
		trim(sTmp);
		/*非退费项，直接入库*/
		if(sTmp[0] == '0'){
					
			/*3-订单号*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,3,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.ORDERNO,sTmp,sizeof(SDB_fsjk_dzmx.ORDERNO)-1); 
			if(strlen(SDB_fsjk_dzmx.ORDERNO) <= 0)
			{
				 iResult = -1;
			   LOG( LM_DEBUG, Fmtmsg( "支付平台对账文件订单号不能为空"), "INFO" );
			   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "支付平台对账文件订单号不能为空");
			   break;
			}
		
			/*8-交易状态、支付平台对账结果（赋两个值）*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,8,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PAYSTATUS,sTmp,sizeof(SDB_fsjk_dzmx.PAYSTATUS)-1);
			memcpy(SDB_fsjk_dzmx.TRANSSTATUS,sTmp,sizeof(SDB_fsjk_dzmx.TRANSSTATUS)-1);			
			
			/*18-财厅交易时间*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,18,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PFTRANSDATETIME,sTmp,sizeof(SDB_fsjk_dzmx.PFTRANSDATETIME)-1);			
			
			/*19-应用名称*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,19,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.APPNAME,sTmp,sizeof(SDB_fsjk_dzmx.APPNAME)-1);
			
			/*20-应用版本*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,20,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.APPVERSION,sTmp,sizeof(SDB_fsjk_dzmx.APPVERSION)-1);
			
			/*21-跳转地址*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,21,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.REDIRECTURL,sTmp,sizeof(SDB_fsjk_dzmx.REDIRECTURL)-1);
			
			/*22-通知地址*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,22,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.NOTIFYURL,sTmp,sizeof(SDB_fsjk_dzmx.NOTIFYURL)-1);
			
			/*23-币种*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,23,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.AMOUNTTYPE,sTmp,sizeof(SDB_fsjk_dzmx.AMOUNTTYPE)-1);
			
			/*24-订单日期*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,24,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.ORDERDATE,sTmp,sizeof(SDB_fsjk_dzmx.ORDERDATE)-1);
			
			/*25-业务代码*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,25,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.BUSCODE,sTmp,sizeof(SDB_fsjk_dzmx.BUSCODE)-1);
			
			/*26-子订单数量*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,26,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.QUANTITY,sTmp,sizeof(SDB_fsjk_dzmx.QUANTITY)-1);
			
			/*27-通用参数*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,27,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.COMM_PARA,sTmp,sizeof(SDB_fsjk_dzmx.COMM_PARA)-1);
			
			/*文件中无，但数据库中需要*/
			/*SIGNDATE-登记日期*/
			memcpy(SDB_fsjk_dzmx.SIGNDATE,sSignDate,sizeof(SDB_fsjk_dzmx.SIGNDATE)-1);
			
			/*SIGNTIME-登记时间*/
			memcpy(SDB_fsjk_dzmx.SIGNTIME,sSignTime,sizeof(SDB_fsjk_dzmx.SIGNTIME)-1);
			
			/*NUMCHKCD-号码校验码*/
		  memset(sSRC, 0x00, sizeof(sSRC));
		  memset(uSRC, 0x00, sizeof(uSRC));
		  memset(sCode, 0x00, sizeof(sCode));
			strcat(sSRC,SDB_fsjk_dzmx.UNITNO);
			strcat(sSRC,SDB_fsjk_dzmx.PAYNOTENO);
		  convertStrToUnChar(sSRC,uSRC);	
			code = CRC16(uSRC,strlen(uSRC));
		  memcpy(sCode,itoa(code),sizeof(sCode)-1);
		  iCodeLen = strlen(sCode);
		  tmpi = 0;
		  tmplen = iCodeLen;
		  for( tmpi = 4; tmpi >= 0 ; tmpi-- )
		  {
		  	if( tmplen > 0 )
		  	{
		  		sCode[tmpi] = sCode[tmplen-1];
		  	}else{
		  		sCode[tmpi] = '0';
		  	}
		  	tmplen--;
		  }
		  memcpy(SDB_fsjk_dzmx.NUMCHKCD,sCode,sizeof(SDB_fsjk_dzmx.NUMCHKCD)-1);
		  
			
			/*TOTCHKCD-全书校验码（暂时使用不包括滞纳金的缴款通知书总金额）*/
		  memset(sSRC, 0x00, sizeof(sSRC));
		  memset(uSRC, 0x00, sizeof(uSRC));
		  memset(sCode, 0x00, sizeof(sCode));
		  memset(sPNAMOUNT, 0x00, sizeof(sPNAMOUNT));
		  memcpy(sPNAMOUNT,itoa( dPNAMOUNT * 100 ),sizeof(sPNAMOUNT)-1);
			strcat(sSRC,SDB_fsjk_dzmx.UNITNO);
			strcat(sSRC,SDB_fsjk_dzmx.PAYNOTENO);
			strcat(sSRC,sPNAMOUNT);
		  convertStrToUnChar(sSRC,uSRC);	
			code = CRC16(uSRC,strlen(uSRC));
		  memcpy(sCode,itoa(code),sizeof(sCode)-1);
		  iCodeLen = strlen(sCode);
		  tmpi = 0;
		  tmplen = iCodeLen;
		  for( tmpi = 4; tmpi >= 0 ; tmpi-- )
		  {
		  	if( tmplen > 0 )
		  	{
		  		sCode[tmpi] = sCode[tmplen-1];
		  	}else{
		  		sCode[tmpi] = '0';
		  	}
		  	tmplen--;
		  }
		  memcpy(SDB_fsjk_dzmx.TOTCHKCD,sCode,sizeof(SDB_fsjk_dzmx.TOTCHKCD)-1);
		  
		  			
			/*SIGNTIME-登记时间*/
			memcpy(SDB_fsjk_dzmx.HOSTDVDSTATUS,"2",sizeof(SDB_fsjk_dzmx.HOSTDVDSTATUS)-1);
			
			/*入表*/
			LOG(LM_STD,Fmtmsg("detotcnt=[%d],Insert,UNITNO=[%s],PAYNOTENO=[%s],ORDERNO=[%s],NUMCHKCD=[%s],TOTCHKCD=[%s]", detotcnt, SDB_fsjk_dzmx.UNITNO, SDB_fsjk_dzmx.PAYNOTENO, SDB_fsjk_dzmx.ORDERNO,SDB_fsjk_dzmx.NUMCHKCD,SDB_fsjk_dzmx.TOTCHKCD),"ERROR")
			memset(sTmp,0x00,sizeof(sTmp));
			iRet = DBInsert( "FSJK_DZMX", SD_FSJK_DZMX, NUMELE( SD_FSJK_DZMX ), &SDB_fsjk_dzmx,sTmp);
			if( iRet < 0 )
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "登记对账明细表失败 缴款通知书号码=[%d]错误码=[%d]错误信息=[%s]",SDB_fsjk_dzmx.PAYNOTENO,iRet,DCILastError()), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "登记对账明细表失败");
				break;   
			}
		
		}else if(sTmp[0] == '1'){/*是退费项*/
			
			/*3-订单号-退费时对应本平台的退费流水号*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,3,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RFSERIAL,sTmp,sizeof(SDB_fsjk_rfmx.RFSERIAL)-1);
			if(strlen(SDB_fsjk_rfmx.RFSERIAL)<=0)
			{
				 iResult = -1;
			   LOG( LM_DEBUG, Fmtmsg( "支付平台对账文件订单号不能为空"), "INFO" );
			   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "支付平台对账文件订单号不能为空");
			   break;
			}
			
			/*8-交易状态-支付平台对账状态*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,8,sTmp,'|','\\');
			trim(sTmp);
			if(sTmp[0] == '0')
			{
				memcpy(SDB_fsjk_dzmx.PAYSTATUS,"2",sizeof(SDB_fsjk_dzmx.PAYSTATUS)-1);
				memcpy(SDB_fsjk_dzmx.TRANSSTATUS,"2",sizeof(SDB_fsjk_dzmx.TRANSSTATUS)-1);
				memcpy(SDB_fsjk_rfmx.RFSTATUS,"1",sizeof(SDB_fsjk_rfmx.RFSTATUS)-1);
			}else if(sTmp[0] == '1')
			{
				memcpy(SDB_fsjk_dzmx.PAYSTATUS,"3",sizeof(SDB_fsjk_dzmx.PAYSTATUS)-1);
				memcpy(SDB_fsjk_dzmx.TRANSSTATUS,"0",sizeof(SDB_fsjk_dzmx.TRANSSTATUS)-1);
				memcpy(SDB_fsjk_rfmx.RFSTATUS,"0",sizeof(SDB_fsjk_rfmx.RFSTATUS)-1);
			}		

			/*29-原支付订单号*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,29,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.ORDERNO,sTmp,sizeof(SDB_fsjk_dzmx.ORDERNO)-1);
			
			/*30-原支付平台流水号*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,30,sTmp,'|','\\');
			trim(sTmp);
			memcpy(sOrgPaySerial,sTmp,sizeof(sOrgPaySerial)-1);
			
			/*31-原交易时间*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,31,sTmp,'|','\\');
			trim(sTmp);
			memcpy(sOrgPayTime,sTmp,sizeof(sOrgPayTime)-1);			
						
			/*更新支付平台对账结果*/ 
		  memset(sSql,0x00,sizeof(sSql));
		  sprintf(sSql,"update FSJK_DZMX set PAYSTATUS='%s',TRANSSTATUS='%s' where UNITNO='%s' and PAYNOTENO='%s' and ORDERNO='%s' and PAYDATETIME='%s'", SDB_fsjk_dzmx.PAYSTATUS, SDB_fsjk_dzmx.TRANSSTATUS, SDB_fsjk_dzmx.UNITNO, SDB_fsjk_dzmx.PAYNOTENO, SDB_fsjk_dzmx.ORDERNO,sOrgPayTime);
		  LOG( LM_DEBUG, Fmtmsg( "detotcnt=[%d],Update,SQL[%s]", detotcnt,sSql), "INFO" ); 
		  iRet = DCIExecuteDirect( sSql );
		  if( iRet <= 0 )
		  {
		  		iResult = -1;
		      LOG(LM_STD,Fmtmsg("更新支付平台对账结果,sqlerr[%s]", DCILastError() ),"ERROR")
		      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "支付平台对账文件入库时更新对账明细表失败");
		      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		      return COMPRET_FAIL;
		  }
			/*更新退费明细表状态*/ 
		  memset(sSql,0x00,sizeof(sSql));
		  sprintf(sSql,"update FSJK_RFMX set RFFLAG='2',RFSTATUS='%s' where RFFLAG='3' and UNITNO='%s' and PAYNOTENO='%s' and RFSERIAL='%s'", SDB_fsjk_rfmx.RFSTATUS, SDB_fsjk_dzmx.UNITNO, SDB_fsjk_dzmx.PAYNOTENO, SDB_fsjk_rfmx.RFSERIAL);
		  LOG( LM_DEBUG, Fmtmsg( "detotcnt=[%d],Update,SQL[%s]", detotcnt,sSql), "INFO" ); 
		  iRet = DCIExecuteDirect( sSql );
		  if( iRet <= 0 )
		  {
		  		iResult = -1;
		      LOG(LM_STD,Fmtmsg("更新支付平台对账结果,sqlerr[%s]", DCILastError() ),"ERROR")
		      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "支付平台对账文件入库时更新退费明细表失败");
		      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		      return COMPRET_FAIL;
		  }
		    	
    }else{

  		iResult = -1;
      LOG(LM_STD,Fmtmsg("不支持的退费标志（非0或1）"),"ERROR")
      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "支付平台对账文件入库失败");
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL;

    }
    
      
	  if( detotcnt == (transcnt+refoundcnt) ){
	   	LOG(LM_STD,Fmtmsg("对账明细入库结束"),"ERROR")
	   	break;
	  }
  }
  
  /*更新对账登记表中的支付平台对账信息*/ 
  memset(sSql,0x00,sizeof(sSql));
  sprintf(sSql,"update FSJK_DZDJ set PAYTRANSNUM='%d',PAYREFOUNDNUM='%d' where CHKDATE='%s' and PAYCHKSTATUS='9'", transcnt, refoundcnt, sChkDate);
  LOG( LM_DEBUG, Fmtmsg( "SQL[%s]", sSql), "INFO" );
  iRet = DCIExecuteDirect( sSql );
  if( iRet <= 0 )
  {
  		iResult = -1;
      LOG(LM_STD,Fmtmsg("支付平台对账文件入库时更新对账登记表失败,sqlerr[%s]", DCILastError() ),"ERROR")
      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "支付平台对账文件入库时更新对账登记表失败");
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL;
  }

  fclose(fp);
  if( iResult < 0 )
  {
      DCIRollback();
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL ;         
  }    
  
  if( DCICommit() != 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( "提交时错误信息=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "事务提交报错");
      return COMPRET_FAIL ;
  }
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
函数名称: FSJK_ZFPT_DVD_FA
名称: 支付平台分成文件入库
 
组件功能: 支付平台分成文件入库
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT FSJK_ZFPT_DVD_FA(HXMLTREE lXmlhandle)
{
  int iRet=0;
  int iResult=0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sChkDate[30+1];       /*对账日期*/
  char sDvdFile[255+1];      /*文件名（带路径）*/
  char sSignDate[8+1];       /*登记日期*/
  char sSignTime[6+1];       /*登记时间*/  
  double dITEMPRICE=0.00;		 /*单价*/
  double dITEMQUANTITY=0.00; /*数量*/
  double dITEMAMOUNT=0.00;	 /*应收金额小计（不含滞纳金）*/
  double dITEMOVERDUEAMT=0.00;/*滞纳金*/

  FSJK_FCMX SDB_fsjk_fcmx;

  FILE *fp;

  int detotcnt=0;               /*明细笔数*/
  int incnt=0;                  /*已入笔数*/
 
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif

  
  memset(sDvdFile, 0x00, sizeof(sDvdFile));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "支付平台分成文件");
  trim(sBuffer);
  pstrcopy(sDvdFile,sBuffer,sizeof(sDvdFile));
  
  memset(sChkDate, 0x00, sizeof(sChkDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "对账日期");
  trim(sBuffer);
  pstrcopy(sChkDate,sBuffer,sizeof(sChkDate));
  
  memset(sSignDate, 0x00, sizeof(sSignDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(3, sBuffer, "登记日期");
  trim(sBuffer);
  pstrcopy(sSignDate,sBuffer,sizeof(sSignDate));
  
  memset(sSignTime, 0x00, sizeof(sSignTime));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(4, sBuffer, "登记时间");
  trim(sBuffer);
  pstrcopy(sSignTime,sBuffer,sizeof(sSignTime));
  
  LOG(LM_STD, Fmtmsg("支付平台分成文件[%s],对账日期[%s],登记日期[%s],登记时间[%s]", sDvdFile, sChkDate, sSignDate, sSignTime), fpub_GetCompname(lXmlhandle)); 


  if(strlen(sDvdFile) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "支付平台分成文件名不能为空");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("文件名不能为空！"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  LOG(LM_STD, Fmtmsg("支付平台分成文件[%s]", sDvdFile), fpub_GetCompname(lXmlhandle));
  
  fp = fopen(sDvdFile, "r");
  if ( fp == NULL )
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_FILE_FAIL, "支付平台分成文件打开失败");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("打开文件%s失败",sDvdFile), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }

  while( !feof(fp) )
  {
  	 memset(sBuffer, 0x00, sizeof(sBuffer));     
     fgets(sBuffer, sizeof(sBuffer), fp);
     if( strlen(trim(sBuffer)) <= 0 )
         continue; 
     /*明细笔数*/
     memset(sTmp,0x00,sizeof(sTmp));
     GetListbyDiv(sBuffer,1,sTmp,'|','\\');
     trim(sTmp);
     detotcnt=atoi(sTmp);
     LOG(LM_STD,Fmtmsg("明细笔数[%d]",detotcnt ),"ERROR")
     
     break;
  }
  DCIBegin();
  //对账明细入库
  while( !feof(fp) )
  {
		memset(&SDB_fsjk_fcmx, 0x00, sizeof(SDB_fsjk_fcmx));
		memset(sBuffer, 0x00, sizeof(sBuffer));     
		fgets(sBuffer, sizeof(sBuffer), fp);
		if( strlen(trim(sBuffer)) <= 0 )
		   continue;
		
		incnt++;
		
		/*1-执收单位编码*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,1,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.UNITNO,sTmp,sizeof(SDB_fsjk_fcmx.UNITNO)-1);
		if(strlen(SDB_fsjk_fcmx.UNITNO) == 0)
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "支付平台分成文件执收单位编码编码不能为空"), "INFO" );
			fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "支付平台分成文件执收单位编码编码不能为空");
			break;
		}
		 
		/*2-缴款通知书号码*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,2,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.PAYNOTENO,sTmp,sizeof(SDB_fsjk_fcmx.PAYNOTENO)-1);
		if(strlen(SDB_fsjk_fcmx.PAYNOTENO) == 0)
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "支付平台分成文件缴款通知书号码不能为空"), "INFO" );
			fpub_SetMsg(lXmlhandle, 98733, "支付平台分成文件缴款通知书号码不能为空");
			break;
		}
	 
		/*3-订单号*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,3,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.ORDERNO,sTmp,sizeof(SDB_fsjk_fcmx.ORDERNO)-1);
		if(strlen(SDB_fsjk_fcmx.ORDERNO) == 0)
		{
			 iResult = -1;
		   LOG( LM_DEBUG, Fmtmsg( "支付平台分成文件订单号不能为空"), "INFO" );
		   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "支付平台分成文件订单号不能为空");
		   break;
		}
		
		/*4-收费项目编码*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,4,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.ITEMNO,sTmp,sizeof(SDB_fsjk_fcmx.ITEMNO)-1);
		if(strlen(SDB_fsjk_fcmx.ORDERNO) == 0)
		{
			 iResult = -1;
		   LOG( LM_DEBUG, Fmtmsg( "支付平台分成文件收费项目编码不能为空"), "INFO" );
		   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "支付平台分成文件收费项目编码不能为空");
		   break;
		}
		
		/*5-收费项目序号*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,5,sTmp,'|','\\');
		trim(sTmp);
		SDB_fsjk_fcmx.ITEMID=atoi(sTmp); 
		
		/*6-收费项目名称*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,6,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.ITEMNAME,sTmp,sizeof(SDB_fsjk_fcmx.ITEMNAME)-1);
		
		/*7-计量单位*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,7,sTmp,'|','\\');
		trim(sTmp);
		memcpy(SDB_fsjk_fcmx.ITEMUNIT,sTmp,sizeof(SDB_fsjk_fcmx.ITEMUNIT)-1);
		
		/*8-单价*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,8,sTmp,'|','\\');
   	dITEMPRICE = atof(sTmp);
   	SDB_fsjk_fcmx.ITEMPRICE=dITEMPRICE;
		
		/*9-数量*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,9,sTmp,'|','\\');
   	dITEMQUANTITY = atof(sTmp);
   	SDB_fsjk_fcmx.ITEMQUANTITY=dITEMQUANTITY;
		
		/*10-应收金额小计*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,10,sTmp,'|','\\');
   	dITEMAMOUNT = atof(sTmp);
   	SDB_fsjk_fcmx.ITEMAMOUNT=dITEMAMOUNT;
		
		/*11-滞纳金*/
		memset(sTmp,0x00,sizeof(sTmp));
		GetListbyDiv(sBuffer,11,sTmp,'|','\\');
   	dITEMOVERDUEAMT = atof(sTmp);
   	SDB_fsjk_fcmx.ITEMOVERDUEAMT=dITEMOVERDUEAMT;
		
		/*文件中无，但数据库中需要*/
		/*SIGNDATE-登记日期*/
		memcpy(SDB_fsjk_fcmx.SIGNDATE,sSignDate,sizeof(SDB_fsjk_fcmx.SIGNDATE)-1);
		
		/*SIGNTIME-登记时间*/
		memcpy(SDB_fsjk_fcmx.SIGNTIME,sSignTime,sizeof(SDB_fsjk_fcmx.SIGNTIME)-1);
		
		/*TRANSDATE-交易日期-对账日期*/
		memcpy(SDB_fsjk_fcmx.TRANSDATE,sChkDate,sizeof(SDB_fsjk_fcmx.TRANSDATE)-1);
		
		/*入表*/
		LOG(LM_STD,Fmtmsg("incnt=[%d],Insert,UNITNO=[%s],PAYNOTENO=[%s],ORDERNO=[%s],ITEMNO=[%s],ITEMID=[%d]", incnt, SDB_fsjk_fcmx.UNITNO, SDB_fsjk_fcmx.PAYNOTENO, SDB_fsjk_fcmx.ORDERNO,SDB_fsjk_fcmx.ITEMNO,SDB_fsjk_fcmx.ITEMID),"ERROR")
		memset(sTmp,0x00,sizeof(sTmp));
		iRet = DBInsert( "FSJK_FCMX", SD_FSJK_FCMX, NUMELE( SD_FSJK_FCMX ), &SDB_fsjk_fcmx,sTmp);
		if( iRet < 0 )
		{
			iResult = -1;
			LOG( LM_DEBUG, Fmtmsg( "登记分成明细表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
			fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "登记分成明细表失败");
			break;   
		}
     
    if( detotcnt == incnt ){
     	LOG(LM_STD,Fmtmsg("分成明细入库结束"),"ERROR")
     	break;
    }
  }

  fclose(fp);
  if( iResult < 0 )
  {
      DCIRollback();
      fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
      return COMPRET_FAIL ;         
  }    
  
  if( DCICommit() != 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( "提交时错误信息=[%s]",DCILastError()), "INFO" );
      DCIRollback();
      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "事务提交报错");
      return COMPRET_FAIL ;
  }
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
函数名称: FSJK_PFCHK_FA
名称: 财厅对账结果文件入库
 
组件功能: 财厅对账结果文件入库
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT FSJK_PFCHK_FA(HXMLTREE lXmlhandle)
{
  int iRet = 0;
  int iResult = 0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sChkDate[30+1];          /*对账日期*/
  char sChkFile[255+1];         /*文件名（带路径，不带批次号）*/
  int iFileNum;                 /*文件个数*/
  int iDZJGLASTSUM;             /*财厅对账结果最后序号*/
  char sFileName[300+1];        /*文件名（带路径，带批次号）*/

  FSJK_DZMX SDB_fsjk_dzmx;
  
  FILE *fp;

  int cnt =0;                   /*明细总笔数（单文件）*/ 
  int succcnt = 0;              /*成功笔数（单文件）*/ 
  int errcnt = 0;               /*失败笔数（单文件）*/ 
  int tbccnt = 0;               /*待确认笔数（单文件）*/
  double succamt = 0.00;        /*成功金额（单文件）*/
  double erramt = 0.00;         /*失败金额（单文件）*/
  double tbcamt = 0.00;         /*待确认金额（单文件）*/
  
  int allcnt = 0;               /*明细总笔数（所有文件）*/ 
  int allsucccnt = 0;           /*成功笔数（所有文件）*/ 
  int allerrcnt = 0;            /*失败笔数（所有文件）*/ 
  int alltbccnt = 0;            /*待确认笔数（所有文件）*/

  double allsuccamt = 0.00;     /*成功金额（所有文件）*/
  double allerramt = 0.00;      /*失败金额（所有文件）*/
  double alltbcamt = 0.00;      /*待确认金额（所有文件）*/

  int nowcnt = 0;               /*当前文件当前笔数*/
  int allnowcnt = 0;            /*所有文件当前笔数*/

  int filecnt = 1;              /*当前文件批次号*/

  fpub_InitSoComp( lXmlhandle );


#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  
  memset(sChkFile, 0x00, sizeof(sChkFile));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "财厅对账结果文件名（不包含批次号）");
  trim(sBuffer);
  pstrcopy(sChkFile,sBuffer,sizeof(sChkFile));

  memset(sChkDate, 0x00, sizeof(sChkDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "对账日期");
  trim(sBuffer);
  pstrcopy(sChkDate,sBuffer,sizeof(sChkDate));

  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(3, sBuffer, "文件个数");
  trim(sBuffer);
  iFileNum=atoi(sBuffer);

  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(4, sBuffer, "财厅对账结果最后序号");
  trim(sBuffer);
  iDZJGLASTSUM=atoi(sBuffer);

  if(strlen(sChkFile) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "财厅对账结果文件名不能为空");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("文件名不能为空！"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
	LOG(LM_STD, Fmtmsg("filecnt=[%d],iFileNum=[%d]",filecnt,iFileNum), fpub_GetCompname(lXmlhandle))
	
	for(filecnt = 1 ; filecnt <= iFileNum ; filecnt++ )
	{
		
		/*组装文件名*/
		memset(sFileName, 0x00, sizeof(sFileName));
		if( filecnt < 10 ){
			strcat(sFileName,sChkFile);
			strcat(sFileName,"0");
			strcat(sFileName,itoa(filecnt+iDZJGLASTSUM));
			strcat(sFileName,".txt");
		} else if( filecnt >= 10 && filecnt < 99 ) {
			strcat(sFileName,sChkFile);
			strcat(sFileName,itoa(filecnt));
		}
		LOG(LM_STD, Fmtmsg("财厅对账结果文件[%s]", sFileName), fpub_GetCompname(lXmlhandle));
		fp = fopen(sFileName, "r");
		if ( fp == NULL )
		{
			fpub_SetMsg(lXmlhandle, FSJK_ERR_FILE_FAIL, "财厅对账结果文件打开失败");
		  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		  LOG(LM_STD, Fmtmsg("打开文件%s失败",sFileName), fpub_GetCompname(lXmlhandle)) 
		  return COMPRET_FAIL ;
		}
		
		nowcnt = 0;
		cnt = 0;
    succcnt = 0; 
    errcnt = 0;  
    tbccnt = 0;	
    succamt = 0.00;	
    erramt = 0.00;
    tbcamt = 0.00;
		
		while( !feof(fp) )
		{
			memset(sBuffer, 0x00, sizeof(sBuffer));     
		  fgets(sBuffer, sizeof(sBuffer), fp);
		  if( strlen(trim(sBuffer)) <= 0 )
		      continue; 
			/*明细总笔数*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,1,sTmp,'|','\\');
			trim(sTmp);
			cnt = atoi(sTmp);
			allcnt += cnt;
			LOG(LM_STD,Fmtmsg("明细总笔数[%d]",cnt ),"ERROR")
			
			/*成功笔数*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,2,sTmp,'|','\\');
			trim(sTmp);
			succcnt = atoi(sTmp);
			allsucccnt += succcnt;
			LOG(LM_STD,Fmtmsg("成功笔数[%d]",succcnt ),"ERROR")
			
			/*成功金额*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,3,sTmp,'|','\\');
			trim(sTmp);
			succamt = atof(sTmp);
			allsuccamt += succamt;
			LOG(LM_STD,Fmtmsg("成功金额[%.2f]",succamt ),"ERROR")
			
			/*失败笔数*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,4,sTmp,'|','\\');
			trim(sTmp);
			errcnt = atoi(sTmp);
			allerrcnt += errcnt;
			LOG(LM_STD,Fmtmsg("失败笔数[%d]",errcnt ),"ERROR")
			
			/*失败金额*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,5,sTmp,'|','\\');
			trim(sTmp);
			erramt = atof(sTmp);
			allerramt += erramt;
			LOG(LM_STD,Fmtmsg("失败金额[%.2f]",erramt ),"ERROR")
			
			/*待确认笔数*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,6,sTmp,'|','\\');
			trim(sTmp);
			tbccnt = atoi(sTmp);
			alltbccnt += tbccnt;
			LOG(LM_STD,Fmtmsg("待确认笔数[%d]",tbccnt ),"ERROR")  
			
			/*待确认金额*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,7,sTmp,'|','\\');
			trim(sTmp);
			tbcamt = atof(sTmp);
			alltbcamt += tbcamt;
			LOG(LM_STD,Fmtmsg("待确认金额[%.2f]",tbcamt ),"ERROR")
			  
			break;
		}
		fgets(sBuffer, sizeof(sBuffer), fp);//读取空白行
		DCIBegin();
		//对账明细入库
		while( !feof(fp) )
		{
			memset(&SDB_fsjk_dzmx, 0x00, sizeof(SDB_fsjk_dzmx));
			memset(sBuffer, 0x00, sizeof(sBuffer));     
			fgets(sBuffer, sizeof(sBuffer), fp);
			if( strlen(trim(sBuffer)) <= 0 )
			   continue;
			
			nowcnt++;
			allnowcnt++;
			
			/*1-区划代码*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,1,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.DISTRICTNO,sTmp,sizeof(SDB_fsjk_dzmx.DISTRICTNO)-1);
			if(strlen(SDB_fsjk_dzmx.DISTRICTNO) == 0)
			{
				 iResult = -1;
			   LOG( LM_DEBUG, Fmtmsg( "财厅对账结果文件区划代码不能为空"), "INFO" );
			   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "财厅对账结果文件区划代码不能为空");
			   break;
			}
			
			/*2-执收单位编码*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,2,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.UNITNO,sTmp,sizeof(SDB_fsjk_dzmx.UNITNO)-1);			 
			if(strlen(SDB_fsjk_dzmx.UNITNO) == 0)
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "财厅对账结果文件执收单位编码编码不能为空"), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "财厅对账结果文件执收单位编码编码不能为空");
				break;
			}
			 
			/*3-缴款通知书号码*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,3,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PAYNOTENO,sTmp,sizeof(SDB_fsjk_dzmx.PAYNOTENO)-1); 
			if(strlen(SDB_fsjk_dzmx.PAYNOTENO) == 0)
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "财厅对账结果文件缴款通知书号码不能为空"), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "财厅对账结果文件缴款通知书号码不能为空");
				break;
			}
		 
			/*4-订单号*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,4,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.ORDERNO,sTmp,sizeof(SDB_fsjk_dzmx.ORDERNO)-1);
			if(strlen(SDB_fsjk_dzmx.ORDERNO) == 0)
			{
				 iResult = -1;
			   LOG( LM_DEBUG, Fmtmsg( "财厅对账结果文件订单号不能为空"), "INFO" );
			   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "财厅对账结果文件订单号不能为空");
			   break;
			}
			
			/*5-对账结果*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,5,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PFCHKSTATUS,sTmp,sizeof(SDB_fsjk_dzmx.PFCHKSTATUS)-1);
			if(strlen(SDB_fsjk_dzmx.PFCHKSTATUS) == 00)
			{
				 iResult = -1;
			   LOG( LM_DEBUG, Fmtmsg( "财厅对账结果文件对账结果不能为空"), "INFO" );
			   fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "财厅对账结果文件对账结果不能为空");
			   break;
			}

			/*6-原因代码*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,6,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PFCHKERRCODE,sTmp,sizeof(SDB_fsjk_dzmx.PFCHKERRCODE)-1);
			
			/*7-原因说明*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,7,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_dzmx.PFCHKERRMSG,sTmp,sizeof(SDB_fsjk_dzmx.PFCHKERRMSG)-1);
						
			LOG(LM_STD,Fmtmsg("allnowcnt=[%d],nowcnt=[%d],DISTRICTNO=[%s],UNITNO=[%s],PAYNOTENO=[%s],ORDERNO=[%s],PFCHKSTATUS=[%s]", allnowcnt, nowcnt, SDB_fsjk_dzmx.DISTRICTNO, SDB_fsjk_dzmx.UNITNO, SDB_fsjk_dzmx.PAYNOTENO, SDB_fsjk_dzmx.ORDERNO,SDB_fsjk_dzmx.PFCHKSTATUS),"ERROR")  
		
			/*更新财厅对账结果*/ 
		  memset(sSql,0x00,sizeof(sSql));
		  sprintf(sSql,"update FSJK_DZMX set PFCHKSTATUS='%s',PFCHKERRCODE='%s',PFCHKERRMSG='%s' where UNITNO='%s' and PAYNOTENO='%s' and ORDERNO='%s'", SDB_fsjk_dzmx.PFCHKSTATUS, SDB_fsjk_dzmx.PFCHKERRCODE, SDB_fsjk_dzmx.PFCHKERRMSG, SDB_fsjk_dzmx.UNITNO, SDB_fsjk_dzmx.PAYNOTENO, SDB_fsjk_dzmx.ORDERNO);
		  LOG( LM_DEBUG, Fmtmsg( "更新财厅对账结果 SQL[%s]", sSql), "INFO" ); 
		  iRet = DCIExecuteDirect( sSql );
		  if( iRet <= 0 )
		  {
		  		iResult = -1;
		      LOG(LM_STD,Fmtmsg("更新财厅对账结果,sqlerr[%s]", DCILastError() ),"ERROR")
		      fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "更新对账明细表报错");
		  }
		   
		  if( nowcnt == cnt ){
		   	LOG(LM_STD,Fmtmsg("财厅对账结果文件[%s]入库结束",sFileName),"ERROR")
		   	break;
		  }
		}
		
		/*更新对账登记表中的财厅对账信息*/ 
		memset(sSql,0x00,sizeof(sSql));
		sprintf(sSql,"update FSJK_DZDJ set PFSUM='%d',PFSUCCSUM='%d',PFERRSUM='%d',PFTBCSUM='%d' where CHKDATE='%s' and PFCHKSTATUS='4'", allcnt, allsucccnt, allerrcnt, alltbccnt,sChkDate);
		LOG( LM_DEBUG, Fmtmsg( "SQL[%s]", sSql), "INFO" );
		iRet = DCIExecuteDirect( sSql );
		if( iRet <= 0 )
		{
				iResult = -1;
				LOG(LM_STD,Fmtmsg("财厅对账文件入库时更新对账登记表失败,sqlerr[%s]", DCILastError() ),"ERROR")
				fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "财厅对账文件入库时更新对账登记表失败");
				fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
				return COMPRET_FAIL;
		}
		
		if( nowcnt != cnt ){
			iResult = -1;
			LOG(LM_STD,Fmtmsg("财厅对账结果文件[%s]实际明细数量[%d]与文件头说明数量[%d]不匹配",sFileName, nowcnt, cnt),"ERROR")
		}
		
		fclose(fp);
		if( iResult < 0 )
		{
			DCIRollback();
			fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
			return COMPRET_FAIL ;
		}
		
		if( DCICommit() != 0 )
		{
			LOG( LM_DEBUG, Fmtmsg( "提交时错误信息=[%s]",DCILastError()), "INFO" );
			DCIRollback();
			fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "事务提交报错");
			return COMPRET_FAIL ;
		}
		
		LOG(LM_STD,Fmtmsg("所有财厅对账结果文件入库结束"),"ERROR")
	}
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}



/************************************************************************
动态组件函数定义
函数名称: FSJK_PFREFOUND_FA
名称: 财厅退费请求文件入库
 
组件功能: 财厅退费请求文件入库
  
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　
************************************************************************/
IRESULT FSJK_PFREFOUND_FA(HXMLTREE lXmlhandle)
{
  int iRet = 0;
  int iResult = 0;
  char sBuffer[1024+1];
  char sTmp[255+1];
  char sSql[1024];
  char sSignDate[30+1];          /*退款日期*/
  char sSignTime[30+1];          /*退款时间*/
  char sRefoundFile[255+1];      /*文件名（带路径，不带批次号）*/
  int iFileNum;				 			 		 /*文件个数*/
  char sFileName[300+1];		     /*文件名（带路径，带批次号）*/

  FSJK_RFMX SDB_fsjk_rfmx;
  
  FILE *fp;

  int cnt = 0;               		/*明细总笔数（单文件）*/
  double amt = 0.00;						/*明细总金额（单文件）*/ 
  int allcnt;               	  /*明细总笔数（所有文件）*/ 
  double allamt = 0.00;					/*明细总金额（所有文件）*/ 
  int nowcnt = 0;								/*当前文件当前笔数*/
  int allnowcnt = 0;						/*所有文件当前笔数*/
  int filecnt = 1;						  /*当前文件批次号*/
  double dAMTOVER = 0.00;				/*退费总金额（单笔，含滞纳金）*/

  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  
  memset(sRefoundFile, 0x00, sizeof(sRefoundFile));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(1, sBuffer, "财厅退费请求文件名（不包含批次号）");
  trim(sBuffer);
  pstrcopy(sRefoundFile,sBuffer,sizeof(sRefoundFile));
  
  memset(sSignDate, 0x00, sizeof(sSignDate));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(2, sBuffer, "登记日期");
  trim(sBuffer);
  pstrcopy(sSignDate,sBuffer,sizeof(sSignDate));
  
  memset(sSignTime, 0x00, sizeof(sSignTime));
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(3, sBuffer, "登记时间");
  trim(sBuffer);
  pstrcopy(sSignTime,sBuffer,sizeof(sSignTime));
  
  memset(sBuffer, 0x00, sizeof(sBuffer));
  COMP_GETPARSEPARAS(4, sBuffer, "文件个数");
  trim(sBuffer);
  iFileNum=atoi(sBuffer);
  
  LOG(LM_STD, Fmtmsg("登记日期[%s],登记时间[%s]", sSignDate, sSignTime), fpub_GetCompname(lXmlhandle)); 

  if(strlen(sRefoundFile) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "财厅退费请求文件名不能为空");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("文件名不能为空！"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  if(strlen(sSignDate) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "登记日期");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("登记日期不能为空！"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }
  
  if(strlen(sSignTime) == 0)
  {
      fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "登记时间");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOG(LM_STD, Fmtmsg("登记时间不能为空！"), fpub_GetCompname(lXmlhandle)) 
      return COMPRET_FAIL ;
  }

	for(filecnt = 1 ; filecnt <= iFileNum ; filecnt++ )
	{
		
		/*组装文件名*/
		memset(sFileName, 0x00, sizeof(sFileName));
		if( filecnt < 10 ){
			strcat(sFileName,sRefoundFile);
			strcat(sFileName,"0");
			strcat(sFileName,itoa(filecnt));
			strcat(sFileName,".txt");
		} else if( filecnt >= 10 && filecnt < 99 ) {
			strcat(sFileName,sRefoundFile);
			strcat(sFileName,itoa(filecnt));
		}
		LOG(LM_STD, Fmtmsg("财厅退费请求文件[%s]", sFileName), fpub_GetCompname(lXmlhandle));
		fp = fopen(sFileName, "r");
		if ( fp == NULL )
		{
			fpub_SetMsg(lXmlhandle, FSJK_ERR_FILE_FAIL, "财厅退费请求文件打开失败");
		  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		  LOG(LM_STD, Fmtmsg("打开文件%s失败",sFileName), fpub_GetCompname(lXmlhandle)) 
		  return COMPRET_FAIL ;
		}
		
		nowcnt = 0;
		cnt = 0;
		amt = 0.00;
		
		while( !feof(fp) )
		{
			memset(sBuffer, 0x00, sizeof(sBuffer));     
		  fgets(sBuffer, sizeof(sBuffer), fp);
		  if( strlen(trim(sBuffer)) <= 0 )
		      continue; 
			/*明细总笔数*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,1,sTmp,'|','\\');
			trim(sTmp);
			cnt = atoi(sTmp);
			allcnt += cnt;
			LOG(LM_STD,Fmtmsg("明细总笔数[%d]",cnt ),"ERROR")
			
			/*明细总金额*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,2,sTmp,'|','\\');
			trim(sTmp);
			amt = atof(sTmp);
			allamt += amt;
			LOG(LM_STD,Fmtmsg("明细总金额[%.2f]",amt ),"ERROR")
			  
			break;
		}
		fgets(sBuffer, sizeof(sBuffer), fp);//读取空白行
		DCIBegin();
		//对账明细入库
		while( !feof(fp) )
		{
			memset(&SDB_fsjk_rfmx, 0x00, sizeof(SDB_fsjk_rfmx));
			memset(sBuffer, 0x00, sizeof(sBuffer));     
			fgets(sBuffer, sizeof(sBuffer), fp);
			if( strlen(trim(sBuffer)) <= 0 )
			   continue;
			
			nowcnt++;
			allnowcnt++;
			
			/*文件名称*/
			memcpy(SDB_fsjk_rfmx.FILENAME,sFileName,sizeof(SDB_fsjk_rfmx.FILENAME)-1);
			/*登记日期*/
			memcpy(SDB_fsjk_rfmx.SIGNDATE,sSignDate,sizeof(SDB_fsjk_rfmx.SIGNDATE)-1);
			/*登记时间*/
			memcpy(SDB_fsjk_rfmx.SIGNTIME,sSignTime,sizeof(SDB_fsjk_rfmx.SIGNTIME)-1);
			/*退费标志-待发起退费*/
			memcpy(SDB_fsjk_rfmx.RFFLAG,"9",sizeof(SDB_fsjk_rfmx.RFFLAG)-1);
			
			/*1-执收单位编码*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,1,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.UNITNO,sTmp,sizeof(SDB_fsjk_rfmx.UNITNO)-1);			 
			if(strlen(SDB_fsjk_rfmx.UNITNO) == 0)
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "财厅退费请求文件执收单位编码不能为空"), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "财厅退费请求文件执收单位编码不能为空");
				break;
			}
			
			/*2-缴款通知书号码*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,2,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.PAYNOTENO,sTmp,sizeof(SDB_fsjk_rfmx.PAYNOTENO)-1); 
			if(strlen(SDB_fsjk_rfmx.PAYNOTENO) == 0)
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "财厅退费请求文件缴款通知书号码不能为空"), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_NODE_NULL, "财厅退费请求文件缴款通知书号码不能为空");
				break;
			}
		 
			/*3-订单号*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,3,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.ORDERNO,sTmp,sizeof(SDB_fsjk_rfmx.ORDERNO)-1);
			
			/*4-缴款人*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,4,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.PAYERNAME,sTmp,sizeof(SDB_fsjk_rfmx.PAYERNAME)-1);

			/*5-需退费总金额*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,5,sTmp,'|','\\');
   		dAMTOVER = atof(sTmp);
   		SDB_fsjk_rfmx.RFAMTOVER=dAMTOVER;
			
			/*6-缴费时间*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,6,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.TRANSTIME,sTmp,sizeof(SDB_fsjk_rfmx.TRANSTIME)-1);
			
			/*7-票据类型编码*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,7,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RECEIPTTYPENO,sTmp,sizeof(SDB_fsjk_rfmx.RECEIPTTYPENO)-1);
			
			/*8-票据号码*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,8,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RECEIPTNO,sTmp,sizeof(SDB_fsjk_rfmx.RECEIPTNO)-1);
			
			/*9-退费原因*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,9,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RFREASON,sTmp,sizeof(SDB_fsjk_rfmx.RFREASON)-1);
			
			/*10-退款人*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,10,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RFNAME,sTmp,sizeof(SDB_fsjk_rfmx.RFNAME)-1);
			
			/*11-退款人联系电话*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,11,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RFTEL,sTmp,sizeof(SDB_fsjk_rfmx.RFTEL)-1);
			
			/*12-退款账号*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,12,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.RFCOUNT,sTmp,sizeof(SDB_fsjk_rfmx.RFCOUNT)-1);
			
			/*13-开户行名称*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,13,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.COUNTBANK,sTmp,sizeof(SDB_fsjk_rfmx.COUNTBANK)-1);
			
			/*14-缴费渠道*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,14,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.PAYCHANNEL,sTmp,sizeof(SDB_fsjk_rfmx.PAYCHANNEL)-1);
			
			/*15-备注*/
			memset(sTmp,0x00,sizeof(sTmp));
			GetListbyDiv(sBuffer,15,sTmp,'|','\\');
			trim(sTmp);
			memcpy(SDB_fsjk_rfmx.REMARK,sTmp,sizeof(SDB_fsjk_rfmx.REMARK)-1);
						
			LOG(LM_STD,Fmtmsg("allnowcnt=[%d],nowcnt=[%d],UNITNO=[%s],PAYNOTENO=[%s],ORDERNO=[%s]", allnowcnt, nowcnt, SDB_fsjk_rfmx.UNITNO, SDB_fsjk_rfmx.PAYNOTENO, SDB_fsjk_rfmx.ORDERNO),"ERROR")  
		
		  /*入表*/
			memset(sTmp,0x00,sizeof(sTmp));
			iRet = DBInsert( "FSJK_RFMX", SD_FSJK_RFMX, NUMELE( SD_FSJK_RFMX ), &SDB_fsjk_rfmx,sTmp);
			if( iRet < 0 )
			{
				iResult = -1;
				LOG( LM_DEBUG, Fmtmsg( "登记退费明细表失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
				fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "登记退费明细表失败");
				break;   
			}
		   
		  if( nowcnt == cnt ){
		   	LOG(LM_STD,Fmtmsg("财厅退费请求文件[%s]入库结束",sFileName),"ERROR")
		   	break;
		  }
		}
		
		if( nowcnt != cnt ){
			iResult = -1;
			LOG(LM_STD,Fmtmsg("财厅退费请求文件[%s]实际明细数量[%d]与文件头说明数量[%d]不匹配",sFileName, nowcnt, cnt),"ERROR")
		}
		
		fclose(fp);
		if( iResult < 0 )
		{
			DCIRollback();
			fpub_SetCompStatus( lXmlhandle, COMPSTATUS_FAIL );
			return COMPRET_FAIL ;         
		}    
		
		if( DCICommit() != 0 )
		{
			LOG( LM_DEBUG, Fmtmsg( "提交时错误信息=[%s]",DCILastError()), "INFO" );
			DCIRollback();
			fpub_SetMsg(lXmlhandle, FSJK_ERR_DB_FAIL, "事务提交报错");
			return COMPRET_FAIL ;
		}
		
		LOG(LM_STD,Fmtmsg("所有财厅退费请求文件入库结束"),"ERROR")
	}
 
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC;
}