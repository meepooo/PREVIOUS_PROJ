/*PAB_HeadPkgChk  PAB_ICC_InsSerial PAB_ICC_UpdSerial（参考cibybh登记流水）*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "gaps_head.h"
#include "DCI.h"
#include "../incl/PABYBH_ERRMSG.h"
#include "../incl/PABYBH_SERIAL.h"
#include "../incl/pabybh_xmlmacro.h"


static int iCountOpen = 0;

#define _u8 unsigned char
#define _u16 unsigned short
#define _u32 unsigned int



/********************************************************
*   名称:     func_ChkZhCharGBK
*   功能:     检查GBK编码字符串末尾是否有不完整的中文，有则去除
*   参数说明: sTmpStr   字符串
*   返回:     -1:失败
              >=0:成功

GB2312
范围： 0xA1A1 - 0xFEFE
汉字范围： 0xB0A1 - 0xF7FE
GBK
汉字范围： 0x8140 - 0xFEFE

********************************************************/
int
func_ChkZhCharGBK (HXMLTREE lXmlhandle, char* sStr)
{
    int iTmp = 0, iLenStr = 0;
    unsigned char uc;
    char* sTmpStr = sStr;

    iLenStr = strlen(sTmpStr);
    if (0 == iLenStr)
    {
	LOG(LM_STD, Fmtmsg("字符串为空，退出校验！", iTmp), "INFO")
	return 0;
    }

    while (iTmp < iLenStr - 2)
    {
	/*如果是中文字符，则后移两个字节，否则后移一个字节*/
	uc = (unsigned char) sTmpStr[iTmp];
	if (uc >= 0x81 && uc <= 0xFE)
	{
	    iTmp += 2;
	}
	else
	    iTmp++;
    }
    LOG(LM_STD, Fmtmsg("sTmpStr[%X-%X]", (unsigned char )sTmpStr[iTmp], (unsigned char )sTmpStr[iTmp + 1]), "INFO")
    /*对最后两个字节做检查*/
    if (iTmp == iLenStr - 2) /*如果指向倒数第二个字符*/
    {
	uc = (unsigned char) sTmpStr[iTmp];
	if (uc >= 0x81 && uc <= 0xFE)/*最后两个字节是一个汉字，不需要再检查了*/
	    return 0;
	else
	    iTmp++;
    }

    /*现在所有的矛头应该都指向了最后一个字节*/
    if (iTmp == iLenStr - 1) /*如果指向最后一个字符*/
    {
	uc = (unsigned char) sTmpStr[iTmp];
	if (uc >= 0x81 && uc <= 0xFE)/*最后一个字节是半个汉字，干掉它*/
	    sTmpStr[iTmp] = '\0';
	else
	    return 0;
    }
    else/*这是不可能的*/
    {
	LOG(LM_STD, Fmtmsg("扫描字符串错误，这不应该啊！iTmp[%d]", iTmp), "INFO")
	return -1;
    }

    return 0;
}



/************************************************************************
版本:V1.1.1.0
动态组件函数定义
组件函数名称:PAB_ICC_InsSerial
组件名称:PAB_ICC_InsSerial
组件功能:平安银行银银前置插入流水
组件参数:
        如要使字段有值方法有二：
        1.在录入之前对相应的节点赋值。
        2.更新记录之前给相应修改的节点赋值。
        
        程序最好不要修改，这个是平安行E通通用适用，单个业务修改可能引起整体业务失控。                   
项 目 组：
程 序 员:
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT PABYBH_InsSerial( HXMLTREE lXmlhandle )
{
  char sTmp[256+1];
  char sErrMsg[256];
  int  iRet=0;
  PABYBH_SERIAL SDB_Serial;
  
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "" )
#endif

	/*获取流水记录标志 0 记录 1 不记录*/
    memset(sTmp,0,sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_APP_JYXX_LSJLBZ, sTmp);
    if ( ( 0 == sTmp[0] ) || ( sTmp[0] == '1' ))
    {
        LOG(LM_STD, Fmtmsg("本交易不记流水[%s]", sTmp),"")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }


  memset(&SDB_Serial,0x00,sizeof(SDB_Serial));
  
	/*交易日期*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSDATE, sTmp)
	memcpy(SDB_Serial.TRANSDATE, sTmp, sizeof(SDB_Serial.TRANSDATE)-1);
	
	/*平台流水号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSSERIALNO, sTmp)
	memcpy(SDB_Serial.TRANSSERIALNO, sTmp, sizeof(SDB_Serial.TRANSSERIALNO)-1);
	
	/*原平台日期*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORITRANSDATE, sTmp)
	memcpy(SDB_Serial.ORITRANSDATE, sTmp, sizeof(SDB_Serial.ORITRANSDATE)-1);
	
	/*原平台流水号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORITRANSSERIALNO, sTmp)
	memcpy(SDB_Serial.ORITRANSSERIALNO, sTmp, sizeof(SDB_Serial.ORITRANSSERIALNO)-1);
	
	/*交易时间*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSTIME, sTmp)
	memcpy(SDB_Serial.TRANSTIME, sTmp, sizeof(SDB_Serial.TRANSTIME)-1);
	
	/*业务日期*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_WORKDATE, sTmp)
	memcpy(SDB_Serial.WORKDATE, sTmp, sizeof(SDB_Serial.WORKDATE)-1);
	
	/*业务流水号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_WORKSERIALNO, sTmp)
	memcpy(SDB_Serial.WORKSERIALNO, sTmp, sizeof(SDB_Serial.WORKSERIALNO)-1);
	
	/*发起方日期*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_REQDATE, sTmp)
	memcpy(SDB_Serial.REQDATE, sTmp, sizeof(SDB_Serial.REQDATE)-1);
	
	/*发起方流水号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_REQSERIALNO, sTmp)
	memcpy(SDB_Serial.REQSERIALNO, sTmp, sizeof(SDB_Serial.REQSERIALNO)-1);
	
	/*集群节点机器名称*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CLUSTERNODENAME, sTmp)
	memcpy(SDB_Serial.CLUSTERNODENAME, sTmp, sizeof(SDB_Serial.CLUSTERNODENAME)-1);
	
	/*集群节点机器IP*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CLUSTERNODEIP, sTmp)
	memcpy(SDB_Serial.CLUSTERNODEIP, sTmp, sizeof(SDB_Serial.CLUSTERNODEIP)-1);
	
	/*合作行号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_COBANKNO, sTmp)
	memcpy(SDB_Serial.COBANKNO, sTmp, sizeof(SDB_Serial.COBANKNO)-1);
	
	/*交易机构*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSORG, sTmp)
	memcpy(SDB_Serial.TRANSORG, sTmp, sizeof(SDB_Serial.TRANSORG)-1);
	
	/*交易柜员*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSOPER, sTmp)
	memcpy(SDB_Serial.TRANSOPER, sTmp, sizeof(SDB_Serial.TRANSOPER)-1);
	
	/*授权机构*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AUTHORG, sTmp)
	memcpy(SDB_Serial.AUTHORG, sTmp, sizeof(SDB_Serial.AUTHORG)-1);
	
	/*授权柜员*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AUTHOPER, sTmp)
	memcpy(SDB_Serial.AUTHOPER, sTmp, sizeof(SDB_Serial.AUTHOPER)-1);
	
	/*渠道类型*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CNLTYPE, sTmp)
	memcpy(SDB_Serial.CNLTYPE, sTmp, sizeof(SDB_Serial.CNLTYPE)-1);
	
	/*终端设备编号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TERMEQUINO, sTmp)
	memcpy(SDB_Serial.TERMEQUINO, sTmp, sizeof(SDB_Serial.TERMEQUINO)-1);
	
	/*交易代码*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSCODE, sTmp)
	memcpy(SDB_Serial.TRANSCODE, sTmp, sizeof(SDB_Serial.TRANSCODE)-1);
	
	/*附加交易代码0出金1入金2开户手续费3补打工本费*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSCODE1, sTmp)
	memcpy(SDB_Serial.TRANSCODE1, sTmp, sizeof(SDB_Serial.TRANSCODE1)-1);
	
	/*交易名称*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CUACOUNTYPE, sTmp)
	memcpy(SDB_Serial.CUACOUNTYPE, sTmp, sizeof(SDB_Serial.CUACOUNTYPE)-1);
	
	/*来往账标志*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSNAME, sTmp)
	memcpy(SDB_Serial.TRANSNAME, sTmp, sizeof(SDB_Serial.TRANSNAME)-1);
	
	/*资金类型, 0---转出1---转入*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CAPITALTYPE, sTmp)
	memcpy(SDB_Serial.CAPITALTYPE, sTmp, sizeof(SDB_Serial.CAPITALTYPE)-1);
	
	/*服务代码(存管、黄金等)*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_SVRCODE, sTmp)
	memcpy(SDB_Serial.SVRCODE, sTmp, sizeof(SDB_Serial.SVRCODE)-1);
	
	/*客户名称*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CUSTNAME, sTmp)
	memcpy(SDB_Serial.CUSTNAME, sTmp, sizeof(SDB_Serial.CUSTNAME)-1);
	
	/*客户类型00-机构01-个人*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CUSTTYPE, sTmp)
	memcpy(SDB_Serial.CUSTTYPE, sTmp, sizeof(SDB_Serial.CUSTTYPE)-1);
	
	/*银行账号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ACCTNO, sTmp)
	memcpy(SDB_Serial.ACCTNO, sTmp, sizeof(SDB_Serial.ACCTNO)-1);
	
	/*银行帐号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORIACCTNO, sTmp)
	memcpy(SDB_Serial.ORIACCTNO, sTmp, sizeof(SDB_Serial.ORIACCTNO)-1);
	
	/*帐号2变更后的账户*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ACCTNO2, sTmp)
	memcpy(SDB_Serial.ACCTNO2, sTmp, sizeof(SDB_Serial.ACCTNO2)-1);
	
	/*券商代码*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_STOCKCODE, sTmp)
	memcpy(SDB_Serial.STOCKCODE, sTmp, sizeof(SDB_Serial.STOCKCODE)-1);
	
	/*资金帐号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CAPITALACCTNO, sTmp)
	memcpy(SDB_Serial.CAPITALACCTNO, sTmp, sizeof(SDB_Serial.CAPITALACCTNO)-1);
	
	/*交易金额*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSAMT, sTmp)
	SDB_Serial.TRANSAMT=atof(sTmp);
	
	/*交易金额*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORITRANSAMT, sTmp)
	SDB_Serial.ORITRANSAMT=atof(sTmp);
	
	/*金额2*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AMT2, sTmp)
	SDB_Serial.AMT2=atof(sTmp);
	
	/*金额3*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AMT3, sTmp)
	SDB_Serial.AMT3=atof(sTmp);
	
	/*币种*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURR, sTmp)
	memcpy(SDB_Serial.CURR, sTmp, sizeof(SDB_Serial.CURR)-1);
	
	/*钞汇标识*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CASHFLAG, sTmp)
	memcpy(SDB_Serial.CASHFLAG, sTmp, sizeof(SDB_Serial.CASHFLAG)-1);
	
	/*行E通服务代码*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSVRCODE, sTmp)
	memcpy(SDB_Serial.IEPSVRCODE, sTmp, sizeof(SDB_Serial.IEPSVRCODE)-1);
	
	/*行E通交易代码*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPTRANSCODE, sTmp)
	memcpy(SDB_Serial.IEPTRANSCODE, sTmp, sizeof(SDB_Serial.IEPTRANSCODE)-1);
	
	/*行E通业务日期*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPBSIDATE, sTmp)
	memcpy(SDB_Serial.IEPBSIDATE, sTmp, sizeof(SDB_Serial.IEPBSIDATE)-1);
	
	/*行E通交易日期*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPTRADATE, sTmp)
	memcpy(SDB_Serial.IEPTRADATE, sTmp, sizeof(SDB_Serial.IEPTRADATE)-1);
	
	/*行E通流水号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSERIALNO, sTmp)
	memcpy(SDB_Serial.IEPSERIALNO, sTmp, sizeof(SDB_Serial.IEPSERIALNO)-1);
	
	/*原行E通业务日期*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORIIEPBSIDATE, sTmp)
	memcpy(SDB_Serial.ORIIEPBSIDATE, sTmp, sizeof(SDB_Serial.ORIIEPBSIDATE)-1);
	
	/*原行E通流水号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORIIEPSERIALNO, sTmp)
	memcpy(SDB_Serial.ORIIEPSERIALNO, sTmp, sizeof(SDB_Serial.ORIIEPSERIALNO)-1);
	
	/*行E通响应代码*/
	sprintf(SDB_Serial.IEPRESPCODE,"");
	
	/*行E通响应信息*/
	sprintf(SDB_Serial.IEPRESPMSG, "");
	
	/*主机账务日期*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTBSIDATE, sTmp)
	memcpy(SDB_Serial.HOSTBSIDATE, sTmp, sizeof(SDB_Serial.HOSTBSIDATE)-1);
	
	/*主机流水号*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTSERIALNO, sTmp)
	memcpy(SDB_Serial.HOSTSERIALNO, sTmp, sizeof(SDB_Serial.HOSTSERIALNO)-1);
	
	/*主机交易代码*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTTRANSCODE, sTmp)
	memcpy(SDB_Serial.HOSTTRANSCODE, sTmp, sizeof(SDB_Serial.HOSTTRANSCODE)-1);
	
	/*主机响应代码*/
	sprintf(SDB_Serial.HOSTRESPCODE, "");
	
	/*主机响应信息*/
	sprintf(SDB_Serial.HOSTRESPMSG, "");
	
	/*响应码*/
	sprintf(SDB_Serial.RESPCODE, "");
	
	/*响应信息*/
	sprintf(SDB_Serial.RESPMSG, "");
	
	/*中心交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSTAT, sTmp)
	memcpy(SDB_Serial.IEPSTAT, sTmp, sizeof(SDB_Serial.IEPSTAT)-1);
	
	/*核心交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTSTAT, sTmp)
	memcpy(SDB_Serial.HOSTSTAT, sTmp, sizeof(SDB_Serial.HOSTSTAT)-1);
	
	/*交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_STAT, sTmp)
	memcpy(SDB_Serial.STAT, sTmp, sizeof(SDB_Serial.STAT)-1);
	
	/*平台同步中心前原交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORISTAT, sTmp)
	memcpy(SDB_Serial.ORISTAT, sTmp, sizeof(SDB_Serial.ORISTAT)-1);
	
	/*证件类型*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CERTTYPE, sTmp)
	memcpy(SDB_Serial.CERTTYPE, sTmp, sizeof(SDB_Serial.CERTTYPE)-1);
	
	/*证件号码*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CERTNO, sTmp)
	memcpy(SDB_Serial.CERTNO, sTmp, sizeof(SDB_Serial.CERTNO)-1);
	
	/*联系方式*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_PHONE, sTmp)
	memcpy(SDB_Serial.PHONE, sTmp, sizeof(SDB_Serial.PHONE)-1);
	
	/*代理人客户名称*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTNAME, sTmp)
	memcpy(SDB_Serial.AGENTNAME, sTmp, sizeof(SDB_Serial.AGENTNAME)-1);
	
	/*代理人证件类型*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTCERTY, sTmp)
	memcpy(SDB_Serial.AGENTCERTY, sTmp, sizeof(SDB_Serial.AGENTCERTY)-1);
	
	/*代理人证件号码*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTCERNO, sTmp)
	memcpy(SDB_Serial.AGENTCERNO, sTmp, sizeof(SDB_Serial.AGENTCERNO)-1);
	
	/*代理人联系方式*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTPHONE, sTmp)
	memcpy(SDB_Serial.AGENTPHONE, sTmp, sizeof(SDB_Serial.AGENTPHONE)-1);
	
	/*对账标志, 0-未对账1-已对平2-平安多3-核心多4-双方无记账*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CHKFLAG, sTmp)
	memcpy(SDB_Serial.CHKFLAG, sTmp, sizeof(SDB_Serial.CHKFLAG)-1);
	
	/*备注*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_MEMO, sTmp)
	memcpy(SDB_Serial.MEMO, sTmp, sizeof(SDB_Serial.MEMO)-1);
	
	/*备用字段1*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD1, sTmp)
	memcpy(SDB_Serial.EXTFLD1, sTmp, sizeof(SDB_Serial.EXTFLD1)-1);
	
	/*备用字段2*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD2, sTmp)
	memcpy(SDB_Serial.EXTFLD2, sTmp, sizeof(SDB_Serial.EXTFLD2)-1);
	
	/*备用字段3*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD3, sTmp)
	memcpy(SDB_Serial.EXTFLD3, sTmp, sizeof(SDB_Serial.EXTFLD3)-1);
	
	/*备用字段4*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD4, sTmp)
	memcpy(SDB_Serial.EXTFLD4, sTmp, sizeof(SDB_Serial.EXTFLD4)-1);
  
  DCIBegin();
    
  memset(sErrMsg,0x00,sizeof(sErrMsg));
  iRet = DBInsert( "PABYBH_SERIAL", SD_PABYBH_SERIAL, NUMELE( SD_PABYBH_SERIAL ), &SDB_Serial,sErrMsg);
  if( iRet <= 0 )
  {
     LOG( LM_DEBUG, Fmtmsg( "当日流水登记失败! 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
     return COMPRET_FAIL ;
  }
  if( DCICommit() != 0 )
  {
  	 DCIRollback();
     LOG( LM_DEBUG, Fmtmsg( "当日流水提交失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
     fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     return COMPRET_FAIL ;
  }
  
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC; 
}

/************************************************************************
版本:V1.1.1.0
动态组件函数定义
组件函数名称:PAB_ICC_UpdSerial
组件名称:PAB_ICC_UpdSerial
组件功能:平安银行银银前置更新流水
组件参数:
 序号 参数类型  参数名称            资源类别     缺省值  可空  参数说明
  1   1-输入   服务代码          
  2   1-输入   平安银行业务日期                         
项 目 组：
程 序 员:
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT PABYBH_UpdSerial( HXMLTREE lXmlhandle )
{
  char sTmp[256+1];
  char sErrMsg[256];
  char sSql[1024*3];
  char sZwrq[30+1];
  char sZhqzlsh[30+1];
  char sRunSql[2048];
  int  iRet=0;
  int iLen=0;
  PABYBH_SERIAL SDB_Serial;
  
  fpub_InitSoComp( lXmlhandle );
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行开始", fpub_GetCompname( lXmlhandle ) ), "" )
#endif

	/*获取流水记录标志 0 记录 1 不记录*/
    memset(sTmp,0,sizeof(sTmp));
    COMP_SOFTGETXML(XMLNM_APP_JYXX_LSJLBZ, sTmp);
    if ( ( 0 == sTmp[0] ) || ( sTmp[0] == '1' ))
    {
        LOG(LM_STD, Fmtmsg("本交易不记流水[%s]", sTmp),"")
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }
    
  memset(sZwrq, 0x00, sizeof(sZwrq));
  memset(sZhqzlsh, 0x00, sizeof(sZhqzlsh));
  COMP_GETPARSEPARAS(1, sZwrq, "账务日期")
  COMP_GETPARSEPARAS(2, sZhqzlsh, "综合前置流水号")
  trim(sZwrq);
  trim(sZhqzlsh);
 
  memset(&SDB_Serial,0x00,sizeof(SDB_Serial));
  DCIBegin();
  
  /* 初始化条件 --B*/
    memset(sSql, 0, sizeof(sSql));
    iLen = 0; 
	
	/*交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_STAT, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.STAT, sTmp, sizeof(SDB_Serial.STAT));
	if(strlen(SDB_Serial.STAT)>0)
	{
		sprintf(sSql+iLen, "STAT='%s', ORISTAT='%s'", SDB_Serial.STAT, SDB_Serial.STAT);
		iLen=strlen(sSql);
	}
	
	/*原平台日期*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORITRANSDATE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ORITRANSDATE, sTmp, sizeof(SDB_Serial.ORITRANSDATE));
	if(strlen(SDB_Serial.ORITRANSDATE)>0)
	{
		sprintf(sSql+iLen, ", ORITRANSDATE='%s'", SDB_Serial.ORITRANSDATE);
		iLen=strlen(sSql);
	}
	
	/*原平台流水号*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORITRANSSERIALNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ORITRANSSERIALNO, sTmp, sizeof(SDB_Serial.ORITRANSSERIALNO));
	if(strlen(SDB_Serial.ORITRANSSERIALNO)>0)
	{
		sprintf(sSql+iLen, ", ORITRANSSERIALNO='%s'", SDB_Serial.ORITRANSSERIALNO);
		iLen=strlen(sSql);
	}
	
	/*交易机构*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSORG, sTmp)
	trim(sTmp);
	pstrcopy(SDB_Serial.TRANSORG, sTmp, sizeof(SDB_Serial.TRANSORG));
	if(strlen(SDB_Serial.TRANSORG)>0)
	{
		sprintf(sSql+iLen, ", TRANSORG='%s'", SDB_Serial.TRANSORG);
		iLen=strlen(sSql);
	}
	
	/*交易柜员*/
	memset(sTmp, 0x00, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSOPER, sTmp)
	trim(sTmp);
	pstrcopy(SDB_Serial.TRANSOPER, sTmp, sizeof(SDB_Serial.TRANSOPER));
	if(strlen(SDB_Serial.TRANSOPER)>0)
	{
		sprintf(sSql+iLen, ", TRANSOPER='%s'", SDB_Serial.TRANSOPER);
		iLen=strlen(sSql);
	}
	
	/*服务代码*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_SVRCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.SVRCODE, sTmp, sizeof(SDB_Serial.SVRCODE));
	if(strlen(SDB_Serial.SVRCODE)>0)
	{
		sprintf(sSql+iLen, ", SVRCODE='%s'", SDB_Serial.SVRCODE);
		iLen=strlen(sSql);
	}
	
	/*客户名称*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CUSTNAME, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CUSTNAME, sTmp, sizeof(SDB_Serial.CUSTNAME));
	if(strlen(SDB_Serial.CUSTNAME)>0)
	{
		sprintf(sSql+iLen, ", CUSTNAME='%s'", SDB_Serial.CUSTNAME);
		iLen=strlen(sSql);
	}
	
	/*客户类型00-机构01-个人*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CUSTTYPE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CUSTTYPE, sTmp, sizeof(SDB_Serial.CUSTTYPE));
	if(strlen(SDB_Serial.CUSTTYPE)>0)
	{
		sprintf(sSql+iLen, ", CUSTTYPE='%s'", SDB_Serial.CUSTTYPE);
		iLen=strlen(sSql);
	}
	
	/*银行账号*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ACCTNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ACCTNO, sTmp, sizeof(SDB_Serial.ACCTNO));
	if(strlen(SDB_Serial.ACCTNO)>0)
	{
		sprintf(sSql+iLen, ", ACCTNO='%s', ORIACCTNO='%s'", SDB_Serial.ACCTNO, SDB_Serial.ACCTNO);
		iLen=strlen(sSql);
	}
	
	/*帐号2变更后的账户*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ACCTNO2, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ACCTNO2, sTmp, sizeof(SDB_Serial.ACCTNO2));
	if(strlen(SDB_Serial.ACCTNO2)>0)
	{
		sprintf(sSql+iLen, ", ACCTNO2='%s'", SDB_Serial.ACCTNO2);
		iLen=strlen(sSql);
	}
	
	/*券商代码*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_STOCKCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.STOCKCODE, sTmp, sizeof(SDB_Serial.STOCKCODE));
	if(strlen(SDB_Serial.STOCKCODE)>0)
	{
		sprintf(sSql+iLen, ", STOCKCODE='%s'", SDB_Serial.STOCKCODE);
		iLen=strlen(sSql);
	}
	
	/*资金帐号*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CAPITALACCTNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CAPITALACCTNO, sTmp, sizeof(SDB_Serial.CAPITALACCTNO));
	if(strlen(SDB_Serial.CAPITALACCTNO)>0)
	{
		sprintf(sSql+iLen, ", CAPITALACCTNO='%s'", SDB_Serial.CAPITALACCTNO);
		iLen=strlen(sSql);
	}
	
	/*交易金额*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_TRANSAMT, sTmp);
	trim(sTmp);
	if(strlen(sTmp)>0)
	{
		SDB_Serial.TRANSAMT=atof(sTmp);
		sprintf(sSql+iLen, ", TRANSAMT='%.2lf', ORITRANSAMT='%.2lf'", SDB_Serial.TRANSAMT, SDB_Serial.TRANSAMT);
		iLen=strlen(sSql);
	}
	
	/*金额2*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AMT2, sTmp);
	trim(sTmp);
	if(sTmp>0)
	{
		SDB_Serial.AMT2=atof(sTmp);
		sprintf(sSql+iLen, ", AMT2='%f'", SDB_Serial.AMT2);
		iLen=strlen(sSql);
	}
	
	/*金额3*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AMT3, sTmp);
	trim(sTmp);
	if(sTmp>0)
	{
		SDB_Serial.AMT3=atof(sTmp);
		sprintf(sSql+iLen, ", AMT3='%f'", SDB_Serial.AMT3);
		iLen=strlen(sSql);
	}
	
	/*币种*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CURR, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CURR, sTmp, sizeof(SDB_Serial.CURR));
	if(strlen(SDB_Serial.CURR)>0)
	{
		sprintf(sSql+iLen, ", CURR='%s'", SDB_Serial.CURR);
		iLen=strlen(sSql);
	}
	
	/*钞汇标识*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CASHFLAG, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CASHFLAG, sTmp, sizeof(SDB_Serial.CASHFLAG));
	if(strlen(SDB_Serial.CASHFLAG)>0)
	{
		sprintf(sSql+iLen, ", CASHFLAG='%s'", SDB_Serial.CASHFLAG);
		iLen=strlen(sSql);
	}
	
	/*行E通服务代码*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSVRCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPSVRCODE, sTmp, sizeof(SDB_Serial.IEPSVRCODE));
	if(strlen(SDB_Serial.IEPSVRCODE)>0)
	{
		sprintf(sSql+iLen, ", IEPSVRCODE='%s'", SDB_Serial.IEPSVRCODE);
		iLen=strlen(sSql);
	}
	
	/*行E通交易代码*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPTRANSCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPTRANSCODE, sTmp, sizeof(SDB_Serial.IEPTRANSCODE));
	if(strlen(SDB_Serial.IEPTRANSCODE)>0)
	{
		sprintf(sSql+iLen, ", IEPTRANSCODE='%s'", SDB_Serial.IEPTRANSCODE);
		iLen=strlen(sSql);
	}
	
	/*行E通业务日期*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPBSIDATE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPBSIDATE, sTmp, sizeof(SDB_Serial.IEPBSIDATE));
	if(strlen(SDB_Serial.IEPBSIDATE)>0)
	{
		sprintf(sSql+iLen, ", IEPBSIDATE='%s'", SDB_Serial.IEPBSIDATE);
		iLen=strlen(sSql);
	}
	
	/*行E通交易日期*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPTRADATE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPTRADATE, sTmp, sizeof(SDB_Serial.IEPTRADATE));
	if(strlen(SDB_Serial.IEPTRADATE)>0)
	{
		sprintf(sSql+iLen, ", IEPTRADATE='%s'", SDB_Serial.IEPTRADATE);
		iLen=strlen(sSql);
	}
	
	/*行E通流水号*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSERIALNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPSERIALNO, sTmp, sizeof(SDB_Serial.IEPSERIALNO));
	if(strlen(SDB_Serial.IEPSERIALNO)>0)
	{
		sprintf(sSql+iLen, ", IEPSERIALNO='%s'", SDB_Serial.IEPSERIALNO);
		iLen=strlen(sSql);
	}
	
	/*原行E通业务日期*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORIIEPBSIDATE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ORIIEPBSIDATE, sTmp, sizeof(SDB_Serial.ORIIEPBSIDATE));
	if(strlen(SDB_Serial.ORIIEPBSIDATE)>0)
	{
		sprintf(sSql+iLen, ", ORIIEPBSIDATE='%s'", SDB_Serial.ORIIEPBSIDATE);
		iLen=strlen(sSql);
	}
	
	/*原行E通流水号*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_ORIIEPSERIALNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.ORIIEPSERIALNO, sTmp, sizeof(SDB_Serial.ORIIEPSERIALNO));
	if(strlen(SDB_Serial.ORIIEPSERIALNO)>0)
	{
		sprintf(sSql+iLen, ", ORIIEPSERIALNO='%s'", SDB_Serial.ORIIEPSERIALNO);
		iLen=strlen(sSql);
	}
	
	/*行E通响应代码*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPRESPCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPRESPCODE, sTmp, sizeof(SDB_Serial.IEPRESPCODE));
	if(strlen(SDB_Serial.IEPRESPCODE)>0)
	{
		sprintf(sSql+iLen, ", IEPRESPCODE='%s'", SDB_Serial.IEPRESPCODE);
		iLen=strlen(sSql);
	}
	
	/*行E通响应信息*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPRESPMSG, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPRESPMSG, sTmp, sizeof(SDB_Serial.IEPRESPMSG));
	if(strlen(SDB_Serial.IEPRESPMSG)>0)
	{
		sprintf(sSql+iLen, ", IEPRESPMSG='%s'", SDB_Serial.IEPRESPMSG);
		iLen=strlen(sSql);
	}
	
	/*主机账务日期*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTBSIDATE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTBSIDATE, sTmp, sizeof(SDB_Serial.HOSTBSIDATE));
	if(strlen(SDB_Serial.HOSTBSIDATE)>0)
	{
		sprintf(sSql+iLen, ", HOSTBSIDATE='%s'", SDB_Serial.HOSTBSIDATE);
		iLen=strlen(sSql);
	}
	
	/*主机流水号*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTSERIALNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTSERIALNO, sTmp, sizeof(SDB_Serial.HOSTSERIALNO));
	if(strlen(SDB_Serial.HOSTSERIALNO)>0)
	{
		sprintf(sSql+iLen, ", HOSTSERIALNO='%s'", SDB_Serial.HOSTSERIALNO);
		iLen=strlen(sSql);
	}
	
	/*主机交易代码*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTTRANSCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTTRANSCODE, sTmp, sizeof(SDB_Serial.HOSTTRANSCODE));
	if(strlen(SDB_Serial.HOSTTRANSCODE)>0)
	{
		sprintf(sSql+iLen, ", HOSTTRANSCODE='%s'", SDB_Serial.HOSTTRANSCODE);
		iLen=strlen(sSql);
	}
	
	/*主机响应代码*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTRESPCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTRESPCODE, sTmp, sizeof(SDB_Serial.HOSTRESPCODE));
	if(strlen(SDB_Serial.HOSTRESPCODE)>0)
	{
		sprintf(sSql+iLen, ", HOSTRESPCODE='%s'", SDB_Serial.HOSTRESPCODE);
		iLen=strlen(sSql);
	}
	
	/*主机响应信息*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTRESPMSG, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTRESPMSG, sTmp, sizeof(SDB_Serial.HOSTRESPMSG));
	if(strlen(SDB_Serial.HOSTRESPMSG)>0)
	{
		sprintf(sSql+iLen, ", HOSTRESPMSG='%s'", SDB_Serial.HOSTRESPMSG);
		iLen=strlen(sSql);
	}
	
	/*响应码*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_RESPCODE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.RESPCODE, sTmp, sizeof(SDB_Serial.RESPCODE));
	if(strlen(SDB_Serial.RESPCODE)>0)
	{
		sprintf(sSql+iLen, ", RESPCODE='%s'", SDB_Serial.RESPCODE);
		iLen=strlen(sSql);
	}
	
	/*响应信息*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_RESPMSG, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.RESPMSG, sTmp, sizeof(SDB_Serial.RESPMSG));
	if (strlen(SDB_Serial.RESPMSG) == (sizeof(SDB_Serial.RESPMSG) - 1))
    {
			LOG(LM_STD, Fmtmsg("校验字符串"), "INFO")
			func_ChkZhCharGBK(lXmlhandle, SDB_Serial.RESPMSG);
    }
	if(strlen(SDB_Serial.RESPMSG)>0)
	{
		sprintf(sSql+iLen, ", RESPMSG='%s'", SDB_Serial.RESPMSG);
		iLen=strlen(sSql);
	}
	
	/*中心交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_IEPSTAT, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.IEPSTAT, sTmp, sizeof(SDB_Serial.IEPSTAT));
	if(strlen(SDB_Serial.IEPSTAT)>0)
	{
		sprintf(sSql+iLen, ", IEPSTAT='%s'", SDB_Serial.IEPSTAT);
		iLen=strlen(sSql);
	}
	
	/*核心交易状态'0成功1失败6状态未知7被冲正8被撤销9初始'*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_HOSTSTAT, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.HOSTSTAT, sTmp, sizeof(SDB_Serial.HOSTSTAT));
	if(strlen(SDB_Serial.HOSTSTAT)>0)
	{
		sprintf(sSql+iLen, ", HOSTSTAT='%s'", SDB_Serial.HOSTSTAT);
		iLen=strlen(sSql);
	}
	
	
	
	/*证件类型*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CERTTYPE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CERTTYPE, sTmp, sizeof(SDB_Serial.CERTTYPE));
	if(strlen(SDB_Serial.CERTTYPE)>0)
	{
		sprintf(sSql+iLen, ", CERTTYPE='%s'", SDB_Serial.CERTTYPE);
		iLen=strlen(sSql);
	}
	
	/*证件号码*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_CERTNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.CERTNO, sTmp, sizeof(SDB_Serial.CERTNO));
	if(strlen(SDB_Serial.CERTNO)>0)
	{
		sprintf(sSql+iLen, ", CERTNO='%s'", SDB_Serial.CERTNO);
		iLen=strlen(sSql);
	}
	
	/*联系方式*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_PHONE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.PHONE, sTmp, sizeof(SDB_Serial.PHONE));
	if(strlen(SDB_Serial.PHONE)>0)
	{
		sprintf(sSql+iLen, ", PHONE='%s'", SDB_Serial.PHONE);
		iLen=strlen(sSql);
	}
	
	/*代理人名称*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTNAME, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.AGENTNAME, sTmp, sizeof(SDB_Serial.AGENTNAME));
	if(strlen(SDB_Serial.AGENTNAME)>0)
	{
		sprintf(sSql+iLen, ", AGENTNAME='%s'", SDB_Serial.AGENTNAME);
		iLen=strlen(sSql);
	}
	
	/*代理人证件类型*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTCERTY, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.AGENTCERTY, sTmp, sizeof(SDB_Serial.AGENTCERTY));
	if(strlen(SDB_Serial.AGENTCERTY)>0)
	{
		sprintf(sSql+iLen, ", AGENTCERTY='%s'", SDB_Serial.AGENTCERTY);
		iLen=strlen(sSql);
	}
	
	/*代理人证件号码*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTCERNO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.AGENTCERNO, sTmp, sizeof(SDB_Serial.AGENTCERNO));
	if(strlen(SDB_Serial.AGENTCERNO)>0)
	{
		sprintf(sSql+iLen, ", AGENTCERNO='%s'", SDB_Serial.AGENTCERNO);
		iLen=strlen(sSql);
	}
	
	/*代理人联系方式*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_AGENTPHONE, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.AGENTPHONE, sTmp, sizeof(SDB_Serial.AGENTPHONE));
	if(strlen(SDB_Serial.AGENTPHONE)>0)
	{
		sprintf(sSql+iLen, ", AGENTPHONE='%s'", SDB_Serial.AGENTPHONE);
		iLen=strlen(sSql);
	}
	
	/*备注*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_MEMO, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.MEMO, sTmp, sizeof(SDB_Serial.MEMO));
	if(strlen(SDB_Serial.MEMO)>0)
	{
		sprintf(sSql+iLen, ", MEMO='%s'", SDB_Serial.MEMO);
		iLen=strlen(sSql);
	}
	
	/*备用字段1*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD1, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.EXTFLD1, sTmp, sizeof(SDB_Serial.EXTFLD1));
	if(strlen(SDB_Serial.EXTFLD1)>0)
	{
		sprintf(sSql+iLen, ", EXTFLD1='%s'", SDB_Serial.EXTFLD1);
		iLen=strlen(sSql);
	}
	
	/*备用字段2*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD2, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.EXTFLD2, sTmp, sizeof(SDB_Serial.EXTFLD2));
	if(strlen(SDB_Serial.EXTFLD2)>0)
	{
		sprintf(sSql+iLen, ", EXTFLD2='%s'", SDB_Serial.EXTFLD2);
		iLen=strlen(sSql);
	}
	
	/*备用字段3*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD3, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.EXTFLD3, sTmp, sizeof(SDB_Serial.EXTFLD3));
	if(strlen(SDB_Serial.EXTFLD3)>0)
	{
		sprintf(sSql+iLen, ", EXTFLD3='%s'", SDB_Serial.EXTFLD3);
		iLen=strlen(sSql);
	}
	
	/*备用字段4*/
	memset(sTmp, 0, sizeof(sTmp));
	COMP_SOFTGETXML(XMLNM_PABYBH_REQ_EXTFLD4, sTmp);
	trim(sTmp);
	pstrcopy(SDB_Serial.EXTFLD4, sTmp, sizeof(SDB_Serial.EXTFLD4));
	if(strlen(SDB_Serial.EXTFLD4)>0)
	{
		sprintf(sSql+iLen, ", EXTFLD4='%s'", SDB_Serial.EXTFLD4);
		iLen=strlen(sSql);
	}
   
  memset(sErrMsg,0x00,sizeof(sErrMsg));
  memset(sRunSql,0x00,sizeof(sRunSql));
  sprintf(sRunSql,"update PABYBH_SERIAL set %s where transDate ='%s' and transSerialNo ='%s'", sSql, sZwrq, sZhqzlsh);
  LOG(LM_DEBUG,Fmtmsg("sql语句=[%s]",sRunSql),"DEBUG")
  iRet = DCIExecuteDirect(sRunSql);
  if( iRet <= 0 )
  {
  	DCIRollback();
      LOG( LM_DEBUG, Fmtmsg( "更新行E通前置流水失败! 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL ;
  }
 
  if( DCICommit() != 0 )
  {
  	DCIRollback();
      LOG( LM_DEBUG, Fmtmsg( "更新行E通前置流水失败 错误码=[%d]错误信息=[%s]",iRet,DCILastError()), "INFO" );
      fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL ;
  }
  
#ifdef DEBUG
  LOG( LM_DEBUG, Fmtmsg( "组件[%s]执行结束", fpub_GetCompname( lXmlhandle ) ), "INFO" );
#endif
  fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
  return COMPRET_SUCC; 
}

