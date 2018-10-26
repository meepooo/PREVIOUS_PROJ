/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V4.1.00
操作系统:AIX/Linux/HP-UX
文件名称:WDL_DEL.c
文件描述:微动力
项 目 组:
程 序 员:
发布日期:
修    订:
修改日期:
*********************************************************************/

#include <string.h>
#include <stdlib.h>
#include "gaps_head.h"
#include "../incl/wzj.eh"

/********************************************************************
组件注册名称：WZYH_TICKETSORT
组件运行名称：WZYH_TICKETSORT
组件函数定义：
组件函数功能：对获取票据返回时对参数排序并组成串
组件配置参数：
    序号    参数名称    资源类别    缺省值    是否可空    参数说明
组件结果状态：
    状态    结果说明
项 目 组：
程 序 员：txbdir
发布日期：20171108
修改日期：
*********************************************************************/
IRESULT WZYH_TICKETSORT(HXMLTREE lXmlhandle)
{
	int i , j , iRet;
	char ParaSort[6][128] , ParaField[6][128] , sBuf[256]  , sRetVal[1024] , sSPlit[16];
	
	memset(ParaSort , 0x00 , 6*128);
	memset(ParaField , 0x00 , 6*128);
	fpub_InitSoComp(lXmlhandle);
	
	#ifdef DEBUG
		LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
	#endif
	
	/* 获取appid */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/wzyh/appid", sBuf)
	trim(sBuf);
	if (0 == strlen(sBuf))
	{
		LOG(LM_STD, Fmtmsg("APPID不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "APPID不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memcpy(ParaSort[0],sBuf,strlen(sBuf));
	memcpy(ParaField[0],sBuf,strlen(sBuf));
	
	/* 获取userid */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/ggbody_req/user_id", sBuf)
	trim(sBuf);
	if (0 == strlen(sBuf))
	{
		LOG(LM_STD, Fmtmsg("USERID不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "APPID不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memcpy(ParaSort[1],sBuf,strlen(sBuf));
	memcpy(ParaField[1],sBuf,strlen(sBuf));
	
	/* 获取access_token */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/wzyh/tokenid", sBuf)
	trim(sBuf);	
	if (0 == strlen(sBuf))
	{
		LOG(LM_STD, Fmtmsg("APPID不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "APPID不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memcpy(ParaSort[2],sBuf,strlen(sBuf));
	memcpy(ParaField[2],sBuf,strlen(sBuf));
	
		/* 获取type */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/ggbody_req/type", sBuf)
	trim(sBuf);
	if (0 == strlen(sBuf))
	{
		LOG(LM_STD, Fmtmsg("type不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "APPID不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memcpy(ParaSort[3],sBuf,strlen(sBuf));
	memcpy(ParaField[3],sBuf,strlen(sBuf));
	
	memcpy(ParaSort[4],"1.0.0" , 5);		/* version */
	memcpy(ParaField[4],sBuf,sizeof(sBuf));
	LOG(LM_STD, Fmtmsg("3appid[%s]" , ParaSort[0]), "DEBUG")
	
	memset(sBuf , 0x00 , sizeof(sBuf));
	sprintf(sBuf , "%d" , time(NULL));
	memcpy(ParaSort[5] , sBuf , strlen(sBuf));		/*  nonceStr */
	memcpy(ParaField[5] , sBuf , strlen(sBuf));	
	LOG(LM_STD, Fmtmsg("3appid[%s],[%s]" , ParaSort[0] , ParaSort[5]), "DEBUG")
	
	/* 排序 */
	for (i = 0 ; i < 5 ; i++)
	{
		for (j = i+1 ; j < 6 ; j++)
		{
			if(strcmp(ParaSort[i] , ParaSort[j]) > 0)
			{
				memset(sBuf , 0x00 , sizeof(sBuf));
				memcpy(sBuf , ParaSort[i] , strlen(ParaSort[i]));
				memset(ParaSort[i] , 0x00 , sizeof(ParaSort[i]));
				memcpy(ParaSort[i] , ParaSort[j] , strlen(ParaSort[j]));
				memset(ParaSort[j] , 0x00 , sizeof(ParaSort[j]));
				memcpy(ParaSort[j] , sBuf , strlen(sBuf));
			}
		}
	}
	
	/* 组装字符串 */
	memset(sSPlit , 0x00 , sizeof(sSPlit));
	memcpy(sSPlit , "&" , 1);
	memset(sRetVal , 0x00 , sizeof(sRetVal));
	for (i = 0 ; i < 6 ; i++)
	{
		if(strcmp(ParaSort[i] , "1.0.0") == 0)
		{
			strcat(sRetVal , "version=1.0.0");
			strcat(sRetVal , sSPlit);
		}
		else if(strcmp(ParaSort[i] , ParaField[0]) == 0)
		{
			strcat(sRetVal , "app_id=");
			strcat(sRetVal , ParaSort[i]);
			trim(sRetVal);
			strcat(sRetVal , sSPlit);
		}
		else if(strcmp(ParaSort[i] , ParaField[1]) == 0)
		{
			strcat(sRetVal , "user_id=");
			strcat(sRetVal , ParaSort[i]);
			trim(sRetVal);
			strcat(sRetVal , sSPlit);
		}
		else if(strcmp(ParaSort[i] , ParaField[2]) == 0)
		{
			strcat(sRetVal , "tokenid=");
			strcat(sRetVal , ParaSort[i]);
			trim(sRetVal);
			strcat(sRetVal , sSPlit);
		}
		else if(strcmp(ParaSort[i] , ParaField[3]) == 0)
		{
			strcat(sRetVal , "type=");
			strcat(sRetVal , ParaSort[i]);
			trim(sRetVal);
			strcat(sRetVal , sSPlit);
		}
		else if(strcmp(ParaSort[i] , ParaField[5]) == 0)
		{
			strcat(sRetVal , "nonceStr=");
			strcat(sRetVal , ParaSort[i]);
			trim(sRetVal);
			strcat(sRetVal , sSPlit);
		}
	}
	sRetVal[strlen(sRetVal)-1] = '\0';
	
	COMP_SOFTSETXML("/wzyh/ggbody_req/data", sRetVal)
	LOG(LM_STD, Fmtmsg("RetVal[%s]" , sRetVal), "DEBUG")

#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "")
#endif
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/********************************************************
* 名称: prv_SelMulToStruct
* 功能: DCI查询多个字段至结构体
* 参数说明: 1:
*     2:
*     3:
*			4:
* 返回: -1:失败
*   >=0:打报后数据长度(成功)
********************************************************/
int prv_SelMulToStruct( const char* sSql, FLD_DESC desc_arr[], int desc_num, void* pdes)
{
	CURSOR cur;
	char szErrMsg[512];
	
	if( sSql == NULL || pdes == NULL || desc_arr == NULL || desc_num <= 0)
	{
		LOG(LM_STD, Fmtmsg("传入参数空"), "WARNING");
		return -1;
	}
	//LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"DEBUG");
	
	cur = DCIDeclareCursor( sSql, DCI_DEFAULT);
	if (cur == INVALID_CURSOR)
	{
		LOG(LM_STD, Fmtmsg("游标定义失败[%s]-[%s]",  DCILastError(), sSql), "ERROR");
		return -1;
	}
	//LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"DEBUG");
	
	if(DCIExecute(cur) == -1)
	{
		LOG(LM_STD, Fmtmsg("数据库操作失败[%s]", DCILastError() ), "ERROR");
		DCIFreeCursor(cur);
		return -1;
	}
	//LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"DEBUG");
	
	int rs = 0;
	if( 0 > ( rs = DBFetch( cur, desc_arr, desc_num, pdes, szErrMsg ) ) )
	{
		LOG(LM_STD, Fmtmsg("游标获取记录错误[%s]",  szErrMsg ), "ERROR");
		DCIFreeCursor(cur);
		return -1;
	}
		
	DCIFreeCursor(cur);
	return rs;
}

/********************************************************************
组件注册名称：WZYH_DZERRMX
组件运行名称：WZYH_DZERRMX
组件函数定义：
组件函数功能：对账差错明细查询
组件配置参数：
    序号    参数名称    资源类别    缺省值    是否可空    参数说明
组件结果状态：
    状态    结果说明
项 目 组：
程 序 员：txbdir
发布日期：20171108
修改日期：
*********************************************************************/
IRESULT WZYH_DZERRMX(HXMLTREE lXmlhandle)
{
	char qsrq[8+1]; /*起始时间*/
	char zzrq[8+1];/*终止时间*/
	char tran_type[4+1]; /*交易类型*/
	double amount;/*交易金额*/
	char hxrq[8+1]; /*核心日期*/
	char hxls[32+1]; /*核心流水号*/
	char qzrq[8+1]; /*前置日期*/
	char qzls[20]; /*前置流水号*/
	char jyrq[8+1]; /*微众交易日期*/
	char business_id[32+1]; /*微众交易流水*/
	char accno[34+1]; /*卡号*/
	char accname[256]; /*客户姓名*/
	char errflag[2+1]; /*差错类型*/
	char tzbz[2+1]; /*调账标志*/	
	char sSql[1024] , ErrMsg[1024];
	CURSOR cur;
	long lTotalCount=0;
	long lPageCount=0;
	char sBuf[256],qishibis[21],chxunbis[21],buff[1024],cTmp[256];
	long lQueryNum = 0;
	long lBegNum = 0; 
	long lEndNum = 0;
	int iCountNum = 0 , iRet , queryoffset = 0;
	
	fpub_InitSoComp(lXmlhandle);
	/* 获取起始时间 */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/qsrq", sBuf)
	trim(sBuf);
	memset(qsrq,0x00,sizeof(qsrq));
	memcpy(qsrq,sBuf,sizeof(qsrq)-1);
	if (0 == strlen(qsrq))
	{
		LOG(LM_STD, Fmtmsg("起始时间不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "起始时间不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	/* 获取终止时间 */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/zzrq", sBuf)
	trim(sBuf);
	memset(zzrq,0x00,sizeof(zzrq));
	memcpy(zzrq,sBuf,sizeof(zzrq)-1);
	if (0 == strlen(zzrq))
	{
		LOG(LM_STD, Fmtmsg("终止时间不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "终止时间不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	/* 获取起始笔数 */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/qishibis", sBuf)
	trim(sBuf);
	memset(qishibis,0x00,sizeof(qishibis));
	memcpy(qishibis,sBuf,sizeof(qishibis)-1);
	if (0 == strlen(qishibis))
	{
		LOG(LM_STD, Fmtmsg("起始笔数不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "起始笔数不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lBegNum = atol(qishibis);
	if (0 >= lBegNum)
	{
		LOG(LM_STD, Fmtmsg("非法起始笔数"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "非法起始笔数");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}

	/* 获取查询笔数*/
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/chxunbis", sBuf)
	trim(sBuf);
	memset(chxunbis,0x00,sizeof(chxunbis));
	memcpy(chxunbis,sBuf,sizeof(chxunbis)-1);
	if (0 == strlen(chxunbis))
	{
		LOG(LM_STD, Fmtmsg("查询笔数不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "查询笔数不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lQueryNum = atoi(chxunbis);
	if (0 >= lQueryNum)
	{
		LOG(LM_STD, Fmtmsg("非法查询笔数"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "非法查询笔数");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	lEndNum = lBegNum + lQueryNum;
	if (MAXPAGECOUNT < lQueryNum)
	{
		lQueryNum = MAXPAGECOUNT;
	}	
	
	/* 组查询WHERE */
	memset(buff,0x00,sizeof(buff));
	sprintf(buff," FROM YW_WZYH_ERRMX WHERE jyrq>='%s' and jyrq<='%s' ",qsrq,zzrq);
		
	/**查询总笔数**/
	memset(sSql,0x00,sizeof(sSql));
	snprintf(sSql,sizeof(sSql),"select count(jyrq) %s", buff);
	memset(cTmp , 0x00 , sizeof(cTmp));
	LOG(LM_STD, Fmtmsg("总笔数SQL[%s]", sSql), "DEBUG")
	iRet = DBSelectToVar(ErrMsg, (void *)cTmp, sSql);
	if( iRet < 0)
	{
		LOG(LM_STD, Fmtmsg("查询数据库失败[%d]", iRet), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "查询数据库失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lTotalCount = atol(cTmp);

    /**当前页笔数**/
    memset(sSql,0x00,sizeof(sSql));
	memset(cTmp , 0x00 , sizeof(cTmp));
    snprintf(sSql,sizeof(sSql),"select count(jyrq) from (select t.jyrq,rownum rn from (select jyrq %s ) t WHERE rownum<%d) WHERE rn>=%d", buff, lEndNum, lBegNum);
    LOG(LM_STD, Fmtmsg("当前页笔数SQL[%s]", sSql), "DEBUG")
    iRet = DBSelectToVar(ErrMsg, (void *)cTmp, sSql);
	if( iRet < 0)
	{
		LOG(LM_STD, Fmtmsg("查询数据库失败[%d]", iRet), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "查询数据库失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lPageCount = atol(cTmp);

	if (0 == lTotalCount)
	{
		LOG(LM_STD, Fmtmsg("没有符合条件的对账差错信息"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "没有符合条件的对账差错信息");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	if (lTotalCount < lBegNum)
	{
		LOG(LM_STD, Fmtmsg("没有符合条件的对账差错信息"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "没有符合条件的对账差错信息");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	if (0 == lPageCount)
	{
		LOG(LM_STD, Fmtmsg("没有符合条件的对账差错信息"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "没有符合条件的对账差错信息");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	if (lTotalCount > lEndNum)
	{
		COMP_SOFTSETXML("/gmjr/resp/output/querymark", "01")
	}
	else
	{
		COMP_SOFTSETXML("/gmjr/resp/output/querymark", "02")
	}
	memset(cTmp, 0x00, sizeof(cTmp));
	sprintf(cTmp, "%d", lPageCount);
	COMP_SOFTSETXML("/gmjr/resp/output/mxibs", cTmp)

    /** 查询明细 **/
    memset(sSql,0x00,sizeof(sSql));
     snprintf(sSql,sizeof(sSql),"select tran_type,amount,hxrq,hxls,qzrq,qzls,jyrq,business_id,accno,accname,errflag,tzbz from ("
                              " select t.tran_type,t.amount,t.hxrq,t.hxls,t.qzrq,t.qzls,t.jyrq,t.business_id,t.accno,t.accname,t.errflag,t.tzbz,rownum rn from ("
                  " select tran_type,amount,hxrq,hxls,qzrq,qzls,jyrq,business_id,accno,accname,errflag,tzbz  %s) t where rownum<%ld) where rn>=%ld",buff,lEndNum, lBegNum);
    LOG(LM_STD, Fmtmsg("明细SQL[%s]", sSql), "DEBUG")
	
	if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

	while(1)
	{
       if (iCountNum > lPageCount)
        {
            LOG(LM_STD, Fmtmsg("查询结束[%d][%ld]", iCountNum, lPageCount), "DEBUG")
            break;
        }      
          
        memset(tran_type, 0x00, sizeof(tran_type));
        amount=0.00;
        memset(hxrq, 0x00, sizeof(hxrq));
        memset(hxls, 0x00, sizeof(hxls));
        memset(qzrq, 0x00, sizeof(qzrq));
        memset(qzls, 0x00, sizeof(qzls));
        memset(jyrq, 0x00, sizeof(jyrq));
		
        memset(business_id, 0x00, sizeof(business_id));
        memset(accno, 0x00, sizeof(accno));
        memset(accname, 0x00, sizeof(accname));
        memset(errflag, 0x00, sizeof(errflag));
        memset(tzbz, 0x00, sizeof(tzbz));
		 memset(business_id, 0x00, sizeof(business_id));
        memset(accno, 0x00, sizeof(accno));
        memset(accname, 0x00, sizeof(accname));
        memset(errflag, 0x00, sizeof(errflag));
        memset(tzbz, 0x00, sizeof(tzbz));
		memset(errflag, 0x00, sizeof(errflag));
        memset(tzbz, 0x00, sizeof(tzbz));
		
		sprintf(tran_type , "%s" , DCIFieldAsString( cur, 0));
		amount = atof(DCIFieldAsString( cur, 1));
		sprintf(hxrq , "%s" , DCIFieldAsString( cur, 2));
		sprintf(hxls , "%s" , DCIFieldAsString( cur, 3));
		sprintf(qzrq , "%s" , DCIFieldAsString( cur, 4));
		sprintf(qzls , "%s" , DCIFieldAsString( cur, 5));
		sprintf(jyrq , "%s" , DCIFieldAsString( cur, 6));
		sprintf(business_id , "%s" , DCIFieldAsString( cur, 7));
		sprintf(accno , "%s" , DCIFieldAsString( cur, 8));
		sprintf(accname , "%s" , DCIFieldAsString( cur, 9));
		sprintf(errflag , "%s" , DCIFieldAsString( cur, 10));
		sprintf(tzbz , "%s" , DCIFieldAsString( cur, 11));
		
   
        iRet = DCIFetch2(cur, DCI_FETCH_NEXT, queryoffset);
        if (iRet == -100 || iRet == -1403)
        {
            LOG(LM_STD, Fmtmsg("查询结束[%d][%ld]", iCountNum), "DEBUG")
            break;
        }
        else if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("查询对账差错信息失败[%d]", iRet), "DEBUG")
            fpub_SetMsg(lXmlhandle, 10001, "查询对账差错信息失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            DCIFreeCursor(cur);
            return COMPSTATUS_FAIL;
        }
        iCountNum++;
        /* 交易类型 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/trantype", iCountNum);
        COMP_SOFTSETXML(cTmp, tran_type)
        /* 交易金额 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/amt", iCountNum);
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf, "%.2f", amount);
        COMP_SOFTSETXML(cTmp, sBuf)
         /* 核心日期 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/corebkdt", iCountNum);
        COMP_SOFTSETXML(cTmp, hxrq)
        /* 核心流水号 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/corebknum", iCountNum);
        COMP_SOFTSETXML(cTmp, hxls)
         /* 前置日期 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/qzrq", iCountNum);
        COMP_SOFTSETXML(cTmp, qzrq)
        /* 前置流水号 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/pltnum", iCountNum);
        COMP_SOFTSETXML(cTmp, qzls)
         /* 微众交易日期 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/wzrq", iCountNum);
        COMP_SOFTSETXML(cTmp, jyrq)
           /* 微众交易流水 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/wzls", iCountNum);
        COMP_SOFTSETXML(cTmp, business_id)
           /* 客户姓名 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/accname", iCountNum);
        COMP_SOFTSETXML(cTmp, accname)
           /* 卡号 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/accno", iCountNum);
        COMP_SOFTSETXML(cTmp, accno)
           /* 差错类型 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/errflag", iCountNum);
        COMP_SOFTSETXML(cTmp, errflag)
           /* 调账标志 */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/tzbz", iCountNum);
        COMP_SOFTSETXML(cTmp, tzbz)
        
    }
    DCIFreeCursor(cur);

#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "")
#endif
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/********************************************************************
组件注册名称：WZYH_INQDZ
组件运行名称：WZYH_INQDZ
组件函数定义：
组件函数功能：对账结果查询
组件配置参数：
    序号    参数名称    资源类别    缺省值    是否可空    参数说明
组件结果状态：
    状态    结果说明
项 目 组：
程 序 员：txbdir
发布日期：20171107
修改日期：
*********************************************************************/
IRESULT WZYH_INQDZ(HXMLTREE lXmlhandle)
{
	char qsrq[8+1]; /*起始时间*/
	char zzrq[8+1];/*终止时间*/
	char quetype[1+1];/*查询条件*/
	char jyrq[8+1]; /*交易日期*/
	char dz_bz[1+1]; /*对账标志*/
	char product_buy_num[12+1]; /*理财产品申购总笔数*/
	double product_buy_amount;/*申购资金总额*/
	char product_back_num[12+1]; /*理财产品赎回总笔数*/
	double product_back_amount;/*赎回资金总额*/
	double zc_amount;/*轧差总额*/
	char sSql[1024] , ErrMsg[256] , sTmp[1024];
	long lTotalCount=0;
	long lPageCount=0;
	char sBuf[256],qishibis[21],chxunbis[21],buff[1024],cTmp[256];
	long lQueryNum = 0;
	long lBegNum = 0; 
	long lEndNum = 0;
	int iCountNum = 0 , iRet , queryoffset = 0;
	CURSOR cur;
	
	fpub_InitSoComp(lXmlhandle);
	/* 获取起始时间 */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/qsrq", sBuf)
	trim(sBuf);
	memset(qsrq,0x00,sizeof(qsrq));
	memcpy(qsrq,sBuf,sizeof(qsrq)-1);
	if (0 == strlen(qsrq))
	{
		LOG(LM_STD, Fmtmsg("起始时间不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "起始时间不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	/* 获取终止时间 */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/zzrq", sBuf)
	trim(sBuf);
	memset(zzrq,0x00,sizeof(zzrq));
	memcpy(zzrq,sBuf,sizeof(zzrq)-1);
	if (0 == strlen(zzrq))
	{
		LOG(LM_STD, Fmtmsg("终止时间不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "终止时间不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	/* 获取查询条件 */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/quetype", sBuf)
	trim(sBuf);
	memset(quetype,0x00,sizeof(quetype));
	memcpy(quetype,sBuf,sizeof(quetype)-1);
	if (0 == strlen(quetype))
	{
		LOG(LM_STD, Fmtmsg("查询条件不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "查询条件不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	/* 获取起始笔数 */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/qishibis", sBuf)
	trim(sBuf);
	memset(qishibis,0x00,sizeof(qishibis));
	memcpy(qishibis,sBuf,sizeof(qishibis)-1);
	if (0 == strlen(qishibis))
	{
		LOG(LM_STD, Fmtmsg("起始笔数不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "起始笔数不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lBegNum = atol(qishibis);
	if (0 >= lBegNum)
	{
		LOG(LM_STD, Fmtmsg("非法起始笔数"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "非法起始笔数");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}

	/* 获取查询笔数*/
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/chxunbis", sBuf)
	trim(sBuf);
	memset(chxunbis,0x00,sizeof(chxunbis));
	memcpy(chxunbis,sBuf,sizeof(chxunbis)-1);
	if (0 == strlen(chxunbis))
	{
		LOG(LM_STD, Fmtmsg("查询笔数不能为空"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "查询笔数不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lQueryNum = atoi(chxunbis);
	if (0 >= lQueryNum)
	{
		LOG(LM_STD, Fmtmsg("非法查询笔数"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "非法查询笔数");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	lEndNum = lBegNum + lQueryNum;
	if (MAXPAGECOUNT < lQueryNum)
	{
		lQueryNum = MAXPAGECOUNT;
	}
	
	trim(quetype);
	if(strcmp(quetype, "0") == 0)
	{
		/* 组查询WHERE */
		memset(buff,0x00,sizeof(buff));
		sprintf(buff," FROM YW_WZYH_DZJG WHERE qsrq>='%s' and qsrq<='%s'",qsrq,zzrq);
	}
	else
	{ 
		/* 组查询WHERE */
		memset(buff,0x00,sizeof(buff));
		sprintf(buff," FROM YW_WZYH_DZJG WHERE qsrq>='%s' and qsrq<='%s' and dz_bz='%s'  ",qsrq,zzrq,quetype);
	}
	/**查询总笔数**/
	memset(sSql,0x00,sizeof(sSql));
	snprintf(sSql , sizeof(sSql) ,"SELECT COUNT(dz_bz) %s" , buff);
	LOG(LM_STD, Fmtmsg("总笔数SQL[%s]", sSql), "DEBUG")
	iRet = DBSelectToVar(ErrMsg, (void *)sTmp, sSql);
	if( iRet < 0)
	{
		LOG(LM_STD, Fmtmsg("查询数据库失败[%d]", iRet), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "查询数据库失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lTotalCount = atol(sTmp);
	
	/**当前页笔数**/
	memset(sSql,0x00,sizeof(sSql));
	snprintf(sSql , sizeof(sSql) ,"select count(dz_bz) from (select t.dz_bz,rownum rn from (select dz_bz %s ) t WHERE rownum<%d) WHERE rn>=%d",buff,lEndNum,lBegNum);
	LOG(LM_STD, Fmtmsg("当前页笔数SQL[%s]", sSql), "DEBUG")
	iRet = DBSelectToVar(ErrMsg, (void *)sTmp, sSql);
	if( iRet < 0)
	{
		LOG(LM_STD, Fmtmsg("查询数据库失败[%d]", iRet), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "查询数据库失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}	
	lPageCount =  atol(sTmp);
	
	if (0 == lTotalCount)
	{
		LOG(LM_STD, Fmtmsg("没有符合条件的对账结果信息"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "没有符合条件的对账结果信息");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	if (lTotalCount < lBegNum)
	{
		LOG(LM_STD, Fmtmsg("没有符合条件的对账结果信息"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "没有符合条件的对账结果信息");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	if (0 == lPageCount)
	{
		LOG(LM_STD, Fmtmsg("没有符合条件的对账结果信息"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "没有符合条件的对账结果信息");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	if (lTotalCount > lEndNum)
	{
		COMP_SOFTSETXML("/gmjr/resp/output/querymark", "01")
	}
	else
	{
		COMP_SOFTSETXML("/gmjr/resp/output/querymark", "02")
	}
	memset(cTmp, 0x00, sizeof(cTmp));
	sprintf(cTmp, "%d", lPageCount);
	COMP_SOFTSETXML("/gmjr/resp/output/mxibs", cTmp)
	
	/** 查询明细 **/
	memset(sSql,0x00,sizeof(sSql));
	snprintf(sSql,sizeof(sSql),"select qsrq,dz_bz,product_buy_num,product_buy_amount,product_back_num,product_back_amount,zc_amount from ("
							" select t.qsrq,t.dz_bz,t.product_buy_num,t.product_buy_amount,t.product_back_num,t.product_back_amount,t.zc_amount,rownum rn from ("
				" select qsrq,dz_bz,product_buy_num,product_buy_amount,product_back_num,product_back_amount,zc_amount  %s) t where rownum<%ld) where rn>=%ld",buff,lEndNum, lBegNum);
	
	LOG(LM_STD, Fmtmsg("明细SQL[%s]", sSql), "DEBUG")
	if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

	while(1)
	{
		iRet = DCIFetch2(cur, DCI_FETCH_NEXT, queryoffset);
		if (iRet == -100 || iRet == -1403)
		{
			LOG(LM_STD, Fmtmsg("查询结束[%d][%ld]", iCountNum), "DEBUG")
			break;
		}
		else if (iRet < 0)
		{
			LOG(LM_STD, Fmtmsg("查询对账结果信息失败[%d]", iRet), "DEBUG")
			fpub_SetMsg(lXmlhandle, 10001, "查询对账结果信息失败");
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			DCIFreeCursor(cur);
			return COMPSTATUS_FAIL;
		}
		
		if (iCountNum > lPageCount)
		{
			LOG(LM_STD, Fmtmsg("查询结束[%d][%ld]", iCountNum, lPageCount), "DEBUG")
			break;
		}
       
		memset(jyrq, 0x00, sizeof(jyrq));
		memset(dz_bz, 0x00, sizeof(dz_bz));
		memset(product_buy_num, 0x00, sizeof(product_buy_num));
		product_buy_amount=0.00;
		memset(product_back_num, 0x00, sizeof(product_back_num));
		product_back_amount=0.00;
		zc_amount=0.00;
		
		sprintf(jyrq , "%s" , DCIFieldAsString( cur, 0));
		sprintf(dz_bz , "%s" , DCIFieldAsString( cur, 1));
		sprintf(product_buy_num , "%s" , DCIFieldAsString( cur, 2));
		product_buy_amount = atof(DCIFieldAsString( cur, 3));
		sprintf(product_back_num , "%s" , DCIFieldAsString( cur, 4));
		product_back_amount = atof(DCIFieldAsString( cur, 5));
		zc_amount = atof(DCIFieldAsString( cur, 6));
		
		iCountNum++;
		/* 交易时间 */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/transaction_time", iCountNum);
		COMP_SOFTSETXML(cTmp, jyrq)
		/* 对账结果 */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/dzjg", iCountNum);
		COMP_SOFTSETXML(cTmp, dz_bz)
		/* 理财产品申请总笔数 */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/sgzbs", iCountNum);
		COMP_SOFTSETXML(cTmp, product_buy_num)
		/* 申购资金总额 */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/sgamout", iCountNum);
		memset(sBuf,0x00,sizeof(sBuf));
		sprintf(sBuf, "%.2f", product_buy_amount);
		COMP_SOFTSETXML(cTmp, sBuf)
		/* 理财赎回总笔数 */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/shzbs", iCountNum);
		COMP_SOFTSETXML(cTmp, product_back_num)
		/* 赎回资金总额 */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/shamout", iCountNum);
		memset(sBuf,0x00,sizeof(sBuf));
		sprintf(sBuf, "%.2f", product_back_amount);
		COMP_SOFTSETXML(cTmp, sBuf)
		/* 轧差资金总额 */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/zcamout", iCountNum);
		memset(sBuf,0x00,sizeof(sBuf));
		sprintf(sBuf, "%.2f", zc_amount);
		COMP_SOFTSETXML(cTmp, sBuf)        
    }
	
    DCIFreeCursor(cur);

#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "")
#endif

	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
	return COMPSTATUS_SUCC;
}

/********************************************************************
函数注册名称：Process_CHKWDLCOREBAK
函数运行名称：Process_CHKWDLCOREBAK
函数定义：
函数功能：微动力与核心勾兑明细对账
函数配置参数：
    序号    参数名称    资源类别    缺省值    是否可空    参数说明
组件结果状态：
    状态    结果说明
项 目 组：
程 序 员：txbdir
发布日期：20171103
修改日期：
*********************************************************************/
int Process_CHKWDLCOREBAK(HXMLTREE lXmlhandle, char *qshh, char *chk_date)
{
	char qsjg[14+1]; //清算机构
	char qsrq[10+1]; //清算日期
	SDB_YW_WZYH_DZMX   YW_WZYH_DZMX; //微动力对账明细表
	SDB_YW_WZYH_COREMX YW_WZYH_COREMX;//核心对账数据明细表
	SDB_YW_WZYH_YWLS   YW_WZYH_YWLS;//交易流水表
	SDB_YW_WZYH_ERRMX  YW_WZYH_ERRMX;//差错明细表   
	int i=0 , iLSBZ = 0 , iRet;         //用于游标满100部分提交
	char sSql[1024] , sErrMsg[256];
	CURSOR cur;

	//赋值清算机构
	memset(qsjg,0,sizeof(qsjg));
	memcpy(qsjg, qshh, sizeof(qsjg)-1);
	//赋值清算日期
	memset(qsrq,0,sizeof(qsrq));
	memcpy(qsrq, chk_date, sizeof(qsrq)-1);
  
	/* 1、清除当天差错明细表与对账结果表 */
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "DELETE FROM YW_WZYH_ERRMX WHERE jyrq='%s'" , chk_date);
	DCIExecuteDirect(sSql);
	DCICommit();
	
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "DELETE FROM YW_WZYH_dzjg WHERE qsrq='%s'" , chk_date);
	DCIExecuteDirect(sSql);
	DCICommit();

	/*2、根据微动力对账明细表数据勾兑核心对账明细表*/
	LOG(LM_DEBUG,Fmtmsg("根据微动力对账明细表数据勾兑核心对账明细表"),"INFO")
	memset(&YW_WZYH_DZMX, 0x00, sizeof(YW_WZYH_DZMX));
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "SELECT * FROM YW_WZYH_DZMX WHERE dzrq='%s' and deal_flag='S'" , qsrq);
	LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO")
	if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) < 0)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	if (DCIExecute(cur) < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

	i = 0;
	while(iRet = DBFetch(cur, SD_YW_WZYH_DZMX, NUMELE(SD_YW_WZYH_DZMX), &YW_WZYH_DZMX, sErrMsg) > 0)
	{
		LOG(LM_DEBUG,Fmtmsg("根据微动力对账明细表数据勾兑核心对账明细表记录[%d][%d][%s]" , i,iRet , YW_WZYH_DZMX.business_id),"INFO")
		i++; //每次计数+1
		memset(&YW_WZYH_ERRMX, 0x00, sizeof(YW_WZYH_ERRMX));

		/* 根据YW_WZYH_DZMX表去YW_WZYH_YWLS表获取核心日期、核心流水 */
		trim(YW_WZYH_DZMX.dzrq); //交易日期
		trim(YW_WZYH_DZMX.business_id);//交易流水
		YW_WZYH_ERRMX.errflag[0] = '1';
		
		iLSBZ = 0;
		memset(&YW_WZYH_YWLS, 0x00, sizeof(YW_WZYH_YWLS));
		memset(sSql, 0x00, sizeof(sSql));
		sprintf(sSql, "SELECT * FROM YW_WZYH_YWLS WHERE business_id='%s'" , YW_WZYH_DZMX.business_id);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO") 
		iRet = prv_SelMulToStruct((const char *)sSql, SD_YW_WZYH_YWLS, NUMELE(SD_YW_WZYH_YWLS), &YW_WZYH_YWLS);
		LOG(LM_DEBUG,Fmtmsg("1waiblius[%s]" , YW_WZYH_YWLS.waiblius) , "INFO") 
		if (iRet < 0)		/* 查询失败 */
		{
			LOG(LM_DEBUG,Fmtmsg("组件[%s] 执行查询交易失败qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq, iRet), "")
			DCIFreeCursor(cur);
			DCIRollback();
			return -1;
		}
		else if(iRet == 0)		/* 无记录 */
		{
			iLSBZ = 1;
			memcpy(YW_WZYH_ERRMX.errflag, "2", 1);   /* 0-初始 1-对平 2-核心无微众有 3-微众无核心有 4-金额不符 */
			if (memcmp(YW_WZYH_DZMX.tran_type, "01" , 2)==0)  //01-单笔转入(申购)02-单笔转出(赎回)
			{
				memcpy(YW_WZYH_ERRMX.errmsg, "理财申购-微众有，核心无,属于异常情况,需科技部查实" , strlen("理财申购-微众有，核心无,属于异常情况,需科技部查实"));   
			}
			else if (memcmp(YW_WZYH_DZMX.tran_type, "02" , 2)==0)
			{
				memcpy(YW_WZYH_ERRMX.errmsg, "理财赎回-微众有，核心无,需要补客户账" , strlen("理财赎回-微众有，核心无,需要补客户账"));   
			}
			else
			{
				memcpy(YW_WZYH_ERRMX.errmsg, "微众有，核心无" , strlen("理财赎回-微众有，核心无,需要补客户账"));  
			}
		}
		else		/* 有交易流水 */
		{
			/*查找核心明细表*/
			trim(YW_WZYH_YWLS.hxrq); //交易日期
			trim(YW_WZYH_YWLS.hxls);//交易流水
			memset(&YW_WZYH_COREMX, 0x00, sizeof(YW_WZYH_COREMX));
			memset(sSql, 0x00, sizeof(sSql));
			sprintf(sSql, "SELECT * FROM YW_WZYH_COREMX WHERE qslsh='%s' and dzflag <> '2'" , YW_WZYH_YWLS.waiblius);
			LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO") 
			iRet = prv_SelMulToStruct((const char *)sSql, SD_YW_WZYH_COREMX, NUMELE(SD_YW_WZYH_COREMX), &YW_WZYH_COREMX);
			if (iRet < 0)
			{
				LOG(LM_DEBUG,Fmtmsg("组件[%s] 执行查询交易失败qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq, iRet),"")
				DCIFreeCursor(cur);
				DCIRollback();
				return -1;
			}

			if( iRet == 0 ) //微众有，核心无
			{
				LOG(LM_DEBUG,Fmtmsg("微众有，核心无"),"INFO") 
				memcpy(YW_WZYH_ERRMX.errflag, "2", 1);   /* 0-初始 1-对平 2-核心无微众有 3-微众无核心有 4-金额不符 */
				if (memcmp(YW_WZYH_DZMX.tran_type, "01" , 2)==0)  //01-单笔转入(申购)02-单笔转出(赎回)
				{
					strcpy(YW_WZYH_ERRMX.errmsg, "理财申购-微众有，核心无,属于异常情况,需科技部查实");   
				}
				else if (memcmp(YW_WZYH_DZMX.tran_type, "02" , 2)==0)
				{
					strcpy(YW_WZYH_ERRMX.errmsg, "理财赎回-微众有，核心无,需要补客户账");   
				}
				else
				{
					strcpy(YW_WZYH_ERRMX.errmsg, "微众有，核心无");  
				}
				LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO") 
			}
			else  //微众和核心都有，比对金额
			{ 
				LOG(LM_DEBUG,Fmtmsg("微众和核心都有，比对金额"),"INFO") 
				LOG(LM_DEBUG,Fmtmsg("组件[%s] 检查交易金额 wz_jyje=[%f] hx_jyje=[%f] ",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.amount,YW_WZYH_COREMX.jyje),"")
				if ((YW_WZYH_DZMX.amount - YW_WZYH_COREMX.jyje) > 0.00005 || (YW_WZYH_DZMX.amount - YW_WZYH_COREMX.jyje) < -0.00005)
				{                
					memcpy(YW_WZYH_ERRMX.errflag, "4", 1);   /* 0-初始 1-对平 2-核心无微众有 3-微众无核心有 4-金额不符 */
					strcpy(YW_WZYH_ERRMX.errmsg, "微众与核心返回金额不符");
					YW_WZYH_ERRMX.coreamount=YW_WZYH_COREMX.jyje;
				}
				
				/* 修改交易流水表与核心对账状态 */
				if (YW_WZYH_ERRMX.errflag[0] == '1')
				{   
					trim(YW_WZYH_DZMX.dzrq);
					trim(YW_WZYH_DZMX.business_id);
					memset(sSql , 0x00 , sizeof(sSql));
					/* 与核心对账标志(0-初始1-对平2-主机无平台有3-平台无主机有4-金额不符) */
					sprintf(sSql , "UPDATE YW_WZYH_YWLS SET hxdzbz='1' WHERE business_id='%s'" , YW_WZYH_DZMX.business_id);
					iRet = DCIExecuteDirect(sSql);
				}
				else
				{
					trim(YW_WZYH_DZMX.dzrq);
					trim(YW_WZYH_DZMX.business_id);
					memset(sSql , 0x00 , sizeof(sSql));
					/* 与核心对账标志(0-初始 1-对平 2-核心无微众有 3-微众无核心有 4-金额不符) */
					sprintf(sSql , "UPDATE YW_WZYH_YWLS SET hxdzbz='4' WHERE business_id='%s'" , YW_WZYH_DZMX.business_id);
					iRet = DCIExecuteDirect(sSql);
				}
				if (iRet <0)
				{
					LOG(LM_DEBUG,Fmtmsg("组件[%s] 修改流水表状态失败 jyrq=[%s] business_id=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.dzrq,YW_WZYH_DZMX.business_id,iRet),"")
					DCIFreeCursor(cur);
					DCIRollback();
					return -1;
				}
            
				/* 修改核心对账明细表为已对账状态 */
				/*对账标志:0初始、1已对账、2不参与对账的流水*/
				trim(YW_WZYH_COREMX.hxdate);
				trim(YW_WZYH_COREMX.hxnum);
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , " UPDATE YW_WZYH_COREMX SET dzflag='%c' WHERE hxnum='%s'" , YW_WZYH_ERRMX.errflag[0] , YW_WZYH_COREMX.hxnum);
				iRet = DCIExecuteDirect(sSql);
				if (iRet < 0)	
				{                
					LOG(LM_DEBUG,Fmtmsg("组件[%s] 修改核心对账明细表状态失败 jyrq=[%s] business_id=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.dzrq,YW_WZYH_DZMX.business_id,iRet),"")
					DCIFreeCursor(cur);
					DCIRollback();
					return -1;
				}
				
				/* 微动力对账数据明细表为已对账状态*/
				/*对账标志(0-初始 1-对平 2-核心无微众有 3-微众无核心有 4-金额不符)*/
				trim(YW_WZYH_DZMX.dzrq);
				trim(YW_WZYH_DZMX.business_id);
				trim(YW_WZYH_ERRMX.errflag);
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , " UPDATE YW_WZYH_DZMX SET dz_flag='%c' WHERE business_id='%s'" , YW_WZYH_ERRMX.errflag[0] , YW_WZYH_DZMX.business_id);
				iRet = DCIExecuteDirect(sSql);
				if (iRet < 0)	
				{
					LOG(LM_DEBUG,Fmtmsg("组件[%s] 修改微动力对账明细表状态失败 jyrq=[%s] business_id=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.dzrq,YW_WZYH_DZMX.business_id,iRet),"")
					DCIFreeCursor(cur);
					DCIRollback();
					return -1;
				}            
			}
		}
				
		trim(YW_WZYH_ERRMX.errflag);
		if (YW_WZYH_ERRMX.errflag[0] != '1')		/* 对账失败 */
		{
			memcpy(YW_WZYH_ERRMX.jyrq, qsrq, sizeof(YW_WZYH_ERRMX.jyrq)-1);
			memcpy(YW_WZYH_ERRMX.business_id, YW_WZYH_DZMX.business_id, sizeof(YW_WZYH_ERRMX.business_id)-1);
			trim(YW_WZYH_DZMX.tran_type);
			if (strcmp(YW_WZYH_DZMX.tran_type, "01")==0)  //01-单笔转入(申购)02-单笔转出(赎回)
			{
				memcpy(YW_WZYH_ERRMX.accno, YW_WZYH_DZMX.payer_acct, sizeof(YW_WZYH_ERRMX.accno)-1);
				memcpy(YW_WZYH_ERRMX.accname, YW_WZYH_DZMX.payer_name, sizeof(YW_WZYH_ERRMX.accname)-1);
				memcpy(YW_WZYH_ERRMX.subbusstype, "0001" , 4);
			}
			else
			{
				memcpy(YW_WZYH_ERRMX.accno, YW_WZYH_DZMX.payee_acct, sizeof(YW_WZYH_ERRMX.accno)-1);
				memcpy(YW_WZYH_ERRMX.accname, YW_WZYH_DZMX.payee_name, sizeof(YW_WZYH_ERRMX.accname)-1);
				memcpy(YW_WZYH_ERRMX.subbusstype, "0002" , 4);
			}
			memcpy(YW_WZYH_ERRMX.busstype, "C010" , 4);
			
			
			memcpy(YW_WZYH_ERRMX.flag, YW_WZYH_YWLS.flag, sizeof(YW_WZYH_ERRMX.flag)-1);
			memcpy(YW_WZYH_ERRMX.qzrq, YW_WZYH_YWLS.qzrq, sizeof(YW_WZYH_ERRMX.qzrq)-1);
			memcpy(YW_WZYH_ERRMX.qzls, YW_WZYH_YWLS.qzls, sizeof(YW_WZYH_ERRMX.qzls)-1);
			memcpy(YW_WZYH_ERRMX.hxrq, YW_WZYH_YWLS.hxrq, sizeof(YW_WZYH_ERRMX.hxrq)-1);
			memcpy(YW_WZYH_ERRMX.hxls, YW_WZYH_YWLS.hxls, sizeof(YW_WZYH_ERRMX.hxls)-1);
			memcpy(YW_WZYH_ERRMX.hxxym, YW_WZYH_YWLS.hxxym, sizeof(YW_WZYH_ERRMX.hxxym)-1);
			memcpy(YW_WZYH_ERRMX.hxrespmsg, YW_WZYH_YWLS.hxrespmsg, sizeof(YW_WZYH_ERRMX.hxrespmsg)-1);
			memcpy(YW_WZYH_ERRMX.waiblius, YW_WZYH_YWLS.waiblius, sizeof(YW_WZYH_ERRMX.waiblius)-1);
			
			memcpy(YW_WZYH_ERRMX.transtime, YW_WZYH_DZMX.transtime, sizeof(YW_WZYH_ERRMX.transtime)-1);
			memcpy(YW_WZYH_ERRMX.snd_organ, YW_WZYH_DZMX.snd_organ, sizeof(YW_WZYH_ERRMX.snd_organ)-1);
			memcpy(YW_WZYH_ERRMX.rev_organ, YW_WZYH_DZMX.rev_organ, sizeof(YW_WZYH_ERRMX.rev_organ)-1);
			//微众的表结构无这个字段,从YW_WZYH_YWLS取
			memcpy(YW_WZYH_ERRMX.tran_name, YW_WZYH_YWLS.tran_name, sizeof(YW_WZYH_ERRMX.tran_name)-1);
			memcpy(YW_WZYH_ERRMX.tran_type, YW_WZYH_DZMX.tran_type, sizeof(YW_WZYH_ERRMX.tran_type)-1);
			//微众的表结构无这个字段,从YW_WZYH_YWLS取
			memcpy(YW_WZYH_ERRMX.msg_version, YW_WZYH_YWLS.msg_version, sizeof(YW_WZYH_ERRMX.msg_version)-1);
			//这个和微众的表结构名不一样
			memcpy(YW_WZYH_ERRMX.pay_product_code, YW_WZYH_DZMX.business_type, sizeof(YW_WZYH_ERRMX.pay_product_code)-1);
			memcpy(YW_WZYH_ERRMX.acct_type, YW_WZYH_DZMX.acct_type, sizeof(YW_WZYH_ERRMX.acct_type)-1);
			memcpy(YW_WZYH_ERRMX.payee_name, YW_WZYH_DZMX.payee_name, sizeof(YW_WZYH_ERRMX.payee_name)-1);
			memcpy(YW_WZYH_ERRMX.payee_acct, YW_WZYH_DZMX.payee_acct, sizeof(YW_WZYH_ERRMX.payee_acct)-1);
			memcpy(YW_WZYH_ERRMX.payee_opbk, YW_WZYH_DZMX.payee_opbk, sizeof(YW_WZYH_ERRMX.payee_opbk)-1);
			memcpy(YW_WZYH_ERRMX.payer_name, YW_WZYH_DZMX.payer_name, sizeof(YW_WZYH_ERRMX.payer_name)-1);
			memcpy(YW_WZYH_ERRMX.payer_acct, YW_WZYH_DZMX.payer_acct, sizeof(YW_WZYH_ERRMX.payer_acct)-1);
			memcpy(YW_WZYH_ERRMX.payer_opbk, YW_WZYH_DZMX.payer_opbk, sizeof(YW_WZYH_ERRMX.payer_opbk)-1);
			memcpy(YW_WZYH_ERRMX.tzbz, "0", 1);
			YW_WZYH_ERRMX.amount= YW_WZYH_DZMX.amount;
			YW_WZYH_ERRMX.fee_amount= YW_WZYH_DZMX.fee_amount;
			memcpy(YW_WZYH_ERRMX.ccy, YW_WZYH_DZMX.ccy, sizeof(YW_WZYH_ERRMX.ccy)-1);
			//这个字段是清算日期
			memcpy(YW_WZYH_ERRMX.work_date, YW_WZYH_DZMX.work_date, sizeof(YW_WZYH_ERRMX.work_date)-1);
			memcpy(YW_WZYH_ERRMX.scene_no, YW_WZYH_DZMX.scene_no, sizeof(YW_WZYH_ERRMX.scene_no)-1);
			memcpy(YW_WZYH_ERRMX.czflag, YW_WZYH_DZMX.cz_flag, sizeof(YW_WZYH_ERRMX.czflag)-1);
			
			if(iLSBZ == 1)
				memcpy(YW_WZYH_ERRMX.lsbz, "1", 1);

			iRet=DBInsert("YW_WZYH_ERRMX", SD_YW_WZYH_ERRMX ,NUMELE(SD_YW_WZYH_ERRMX), &YW_WZYH_ERRMX, sErrMsg);
            if (iRet < 0)
            {
				LOG(LM_DEBUG,Fmtmsg("组件[%s] 插入对账差错表失败 jyrq=[%s] business_id=[%s] sqlcode=[%d] ， sErrMsg[%s]",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.dzrq,YW_WZYH_DZMX.business_id,iRet , sErrMsg),"")
				DCIFreeCursor(cur);
				DCIRollback();
				return -1;
            }    	
		}
		
		trim(YW_WZYH_ERRMX.errflag);
		trim(YW_WZYH_DZMX.dzrq);
		trim(YW_WZYH_DZMX.business_id);
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE YW_WZYH_DZMX SET dz_flag='%s' WHERE business_id='%s'" , YW_WZYH_ERRMX.errflag , YW_WZYH_DZMX.business_id);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = DCIExecuteDirect(sSql);
		if (iRet < 0)	
		{
			LOG(LM_DEBUG,Fmtmsg("组件[%s] 修改微动力对账明细表状态失败 jyrq=[%s] business_id=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.dzrq,YW_WZYH_DZMX.business_id, iRet),"")
			DCIFreeCursor(cur);
			DCIRollback();
			return -1;
		}
		
		/* 修改交易流水表与核心对账状态 */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , " UPDATE YW_WZYH_YWLS SET hxdzbz='%s' WHERE business_id='%s'" , YW_WZYH_ERRMX.errflag , YW_WZYH_DZMX.business_id);	
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = DCIExecuteDirect(sSql); /* 与核心对账标志(0-初始 1-对平 2-核心无微众有 3-微众无核心有 4-金额不符) */ 
		
		/* 更新核心记录，有可能核心无记录 */
		/*memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE YW_WZYH_COREMX SET dzflag='%s' WHERE qslsh='%s'" , YW_WZYH_ERRMX.errflag , YW_WZYH_YWLS.waiblius);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = DCIExecuteDirect(sSql);*/
		
		if(i>=100)
		{
			LOG(LM_DEBUG,Fmtmsg("达到【%d】条,需提交一次", i), "")
			DCICommit();
			i=0;
		}
		
		memset(&YW_WZYH_DZMX, 0x00, sizeof(YW_WZYH_DZMX));
    }
	if (iRet < 0)		/* iRet=0读完记录，iRet<0读取记录时失败 */
	{
		LOG(LM_DEBUG,Fmtmsg("组件[%s] 执行查询交易失败qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq, iRet), "")
		DCIFreeCursor(cur);
		DCIRollback();
		return -1;
	}

    DCIFreeCursor(cur);
   
	/*3、处理核心有,微众无的情况 */
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "SELECT * FROM YW_WZYH_COREMX  WHERE qsrq='%s' and dzflag='0'" , qsrq);
	LOG(LM_DEBUG,Fmtmsg("处理核心有,微众无的情况SQL[%s]" , sSql) , "INFO")
	if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	
	if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

	i=0;//初始循环次数
	memset(&YW_WZYH_COREMX, 0x00, sizeof(YW_WZYH_COREMX));
	LOG(LM_DEBUG,Fmtmsg("处理核心有,微众无的情况记录[%d]" , i),"INFO")
	while(iRet = DBFetch(cur, SD_YW_WZYH_COREMX, NUMELE(SD_YW_WZYH_COREMX), &YW_WZYH_COREMX, sErrMsg ) > 0)
	{
		i++;

		trim(YW_WZYH_COREMX.hxdate); //核心日期
		trim(YW_WZYH_COREMX.hxnum);//核心流水
		memset(&YW_WZYH_YWLS, 0x00, sizeof(YW_WZYH_YWLS));
		
		memset(&YW_WZYH_YWLS, 0x00, sizeof(YW_WZYH_YWLS));
		memset(sSql, 0x00, sizeof(sSql));
		sprintf(sSql, "SELECT YW_WZYH_YWLS.* FROM YW_WZYH_YWLS , yw_wzyh_dzmx WHERE  YW_WZYH_YWLS.waiblius='%s' AND YW_WZYH_YWLS.business_id=yw_wzyh_dzmx.business_id AND yw_wzyh_dzmx.deal_flag='S'" , YW_WZYH_COREMX.qslsh);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = prv_SelMulToStruct((const char *)sSql, SD_YW_WZYH_YWLS, NUMELE(SD_YW_WZYH_YWLS), &YW_WZYH_YWLS);
		if (iRet < 0)	/* 查询失败 */
		{
			LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
		else if(iRet > 0)	/* 有记录则执行下一条 */
		{
			memset(&YW_WZYH_COREMX, 0x00, sizeof(YW_WZYH_COREMX));
			continue;
		}
		
		/* 无记录 */		
		memset(&YW_WZYH_YWLS, 0x00, sizeof(YW_WZYH_YWLS));
		memset(sSql, 0x00, sizeof(sSql));
		sprintf(sSql, "SELECT * FROM YW_WZYH_YWLS WHERE waiblius='%s'" , YW_WZYH_COREMX.qslsh);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = prv_SelMulToStruct((const char *)sSql, SD_YW_WZYH_YWLS, NUMELE(SD_YW_WZYH_YWLS), &YW_WZYH_YWLS);
		if (iRet == 0)	/* 查询无记录 */
			memcpy(YW_WZYH_ERRMX.lsbz, "1", 1);
		
		memset(&YW_WZYH_ERRMX, 0x00, sizeof(YW_WZYH_ERRMX));
		YW_WZYH_ERRMX.errflag[0] = '3';		/* 对账标志(0-初始 1-对平 2-核心无微众有 3-微众无核心有 4-金额不符 */
		strncpy(YW_WZYH_ERRMX.tzbz,"0",sizeof(YW_WZYH_ERRMX.tzbz)-1);
 
		trim(YW_WZYH_YWLS.tran_type);
		if (strcmp(YW_WZYH_YWLS.tran_type, "01")==0)  //01-单笔转入(申购)02-单笔转出(赎回)
		{
			strcpy(YW_WZYH_ERRMX.errmsg, "理财申购-核心有,微众无,需要抹账");   
		}
		else if (strcmp(YW_WZYH_YWLS.tran_type, "02")==0)
		{
			strcpy(YW_WZYH_ERRMX.errmsg, "理财赎回-核心有,微众无,属于异常情况,需科技部查实");   
		}
		else
		{
			iLSBZ = 1;
			strcpy(YW_WZYH_ERRMX.errmsg, "核心有,微众无");  
		}  
		
		memcpy(YW_WZYH_ERRMX.jyrq, qsrq, sizeof(YW_WZYH_ERRMX.jyrq)-1);
		memcpy(YW_WZYH_ERRMX.business_id, YW_WZYH_YWLS.business_id, sizeof(YW_WZYH_ERRMX.business_id)-1);
		memcpy(YW_WZYH_ERRMX.accno, YW_WZYH_COREMX.jfyhzh, sizeof(YW_WZYH_ERRMX.accno)-1);
		memcpy(YW_WZYH_ERRMX.subbusstype, YW_WZYH_COREMX.subbusstype, sizeof(YW_WZYH_COREMX.subbusstype)-1);
		memcpy(YW_WZYH_ERRMX.busstype, YW_WZYH_COREMX.busstype, sizeof(YW_WZYH_COREMX.busstype)-1);
		
		memcpy(YW_WZYH_ERRMX.subbusstype, "0001" , 1);
		if (memcmp(YW_WZYH_ERRMX.subbusstype, "0001" , 4)==0)  /* 0001-单笔转入(申购)0002-单笔转出(赎回) */
		{
			memcpy(YW_WZYH_ERRMX.accname, YW_WZYH_YWLS.payer_name, sizeof(YW_WZYH_ERRMX.accname)-1);
		}
		else if (memcmp(YW_WZYH_ERRMX.subbusstype, "0002" , 4)==0)  //0001-单笔转入(申购)0002-单笔转出(赎回)
		{
			memcpy(YW_WZYH_ERRMX.accname, YW_WZYH_YWLS.payee_name, sizeof(YW_WZYH_ERRMX.accname)-1);
		}
		memcpy(YW_WZYH_ERRMX.flag, YW_WZYH_YWLS.flag, sizeof(YW_WZYH_ERRMX.flag)-1);
		memcpy(YW_WZYH_ERRMX.qzrq, YW_WZYH_YWLS.qzrq, sizeof(YW_WZYH_ERRMX.qzrq)-1);
		memcpy(YW_WZYH_ERRMX.qzls, YW_WZYH_YWLS.qzls, sizeof(YW_WZYH_ERRMX.qzls)-1);
		memcpy(YW_WZYH_ERRMX.hxrq, YW_WZYH_COREMX.hxdate, sizeof(YW_WZYH_ERRMX.hxrq)-1);
		memcpy(YW_WZYH_ERRMX.hxls, YW_WZYH_COREMX.hxnum, sizeof(YW_WZYH_ERRMX.hxls)-1);
		memcpy(YW_WZYH_ERRMX.hxxym, YW_WZYH_YWLS.hxxym, sizeof(YW_WZYH_ERRMX.hxxym)-1);
		memcpy(YW_WZYH_ERRMX.hxrespmsg, YW_WZYH_YWLS.hxrespmsg, sizeof(YW_WZYH_ERRMX.hxrespmsg)-1);
		memcpy(YW_WZYH_ERRMX.waiblius, YW_WZYH_COREMX.qslsh, sizeof(YW_WZYH_ERRMX.waiblius)-1);        	   
		memcpy(YW_WZYH_ERRMX.transtime, YW_WZYH_YWLS.transtime, sizeof(YW_WZYH_ERRMX.transtime)-1);
		memcpy(YW_WZYH_ERRMX.snd_organ, YW_WZYH_YWLS.snd_organ, sizeof(YW_WZYH_ERRMX.snd_organ)-1);
		memcpy(YW_WZYH_ERRMX.rev_organ, YW_WZYH_YWLS.rev_organ, sizeof(YW_WZYH_ERRMX.rev_organ)-1);
		memcpy(YW_WZYH_ERRMX.tran_name, YW_WZYH_YWLS.tran_name, sizeof(YW_WZYH_ERRMX.tran_name)-1);
		memcpy(YW_WZYH_ERRMX.tran_type, YW_WZYH_YWLS.tran_type, sizeof(YW_WZYH_ERRMX.tran_type)-1);
		memcpy(YW_WZYH_ERRMX.msg_version, YW_WZYH_YWLS.msg_version, sizeof(YW_WZYH_ERRMX.msg_version)-1);
		memcpy(YW_WZYH_ERRMX.pay_product_code, YW_WZYH_YWLS.pay_product_code, sizeof(YW_WZYH_ERRMX.pay_product_code)-1);
		memcpy(YW_WZYH_ERRMX.acct_type, YW_WZYH_YWLS.acct_type, sizeof(YW_WZYH_ERRMX.acct_type)-1);
		memcpy(YW_WZYH_ERRMX.payee_name, YW_WZYH_COREMX.dfhm, sizeof(YW_WZYH_ERRMX.payee_name)-1);
		memcpy(YW_WZYH_ERRMX.payee_acct, YW_WZYH_COREMX.dfyhzh, sizeof(YW_WZYH_ERRMX.payee_acct)-1);
		memcpy(YW_WZYH_ERRMX.payee_opbk, YW_WZYH_YWLS.payee_opbk, sizeof(YW_WZYH_ERRMX.payee_opbk)-1);
		memcpy(YW_WZYH_ERRMX.payer_name, YW_WZYH_COREMX.jfhm, sizeof(YW_WZYH_ERRMX.payer_name)-1);
		memcpy(YW_WZYH_ERRMX.payer_acct, YW_WZYH_COREMX.jfyhzh, sizeof(YW_WZYH_ERRMX.payer_acct)-1);
		memcpy(YW_WZYH_ERRMX.payer_opbk, YW_WZYH_YWLS.payer_opbk, sizeof(YW_WZYH_ERRMX.payer_opbk)-1);
		memcpy(YW_WZYH_ERRMX.ccy, YW_WZYH_YWLS.ccy, sizeof(YW_WZYH_ERRMX.ccy)-1);
		//这个字段是清算日期
		memcpy(YW_WZYH_ERRMX.work_date, YW_WZYH_YWLS.work_date, sizeof(YW_WZYH_ERRMX.work_date)-1);
		memcpy(YW_WZYH_ERRMX.scene_no, YW_WZYH_YWLS.scene_no, sizeof(YW_WZYH_ERRMX.scene_no)-1);
		memcpy(YW_WZYH_ERRMX.czflag, YW_WZYH_YWLS.czflag, sizeof(YW_WZYH_ERRMX.czflag)-1);
		YW_WZYH_ERRMX.coreamount = YW_WZYH_COREMX.jyje;
		YW_WZYH_ERRMX.fee_amount= YW_WZYH_YWLS.fee_amount;

		iRet=DBInsert("YW_WZYH_ERRMX", SD_YW_WZYH_ERRMX ,NUMELE(SD_YW_WZYH_ERRMX), &YW_WZYH_ERRMX, sErrMsg);
		if (iRet < 0)
		{
			LOG(LM_DEBUG,Fmtmsg("组件[%s] 插入对账差错表失败qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq, iRet),"")
			DCIRollback();
			memset(sSql , 0x00 , sizeof(sSql));
			sprintf(sSql , "UPDATE YW_WZYH_DZKZ SET dzstate='2'  WHERE qsrq='%s'" , qsrq);
			iRet = DCIExecuteDirect(sSql);
			if (iRet < 0)
			{
				LOG(LM_DEBUG,Fmtmsg("组件[%s]修改对账控制表失败qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq,iRet),"")
				DCIFreeCursor(cur);
				DCIRollback();
				return -1;
			}
			
			DCICommit();
			return -1;
		}
            
		trim(YW_WZYH_COREMX.hxdate); //核心日期
		trim(YW_WZYH_COREMX.hxnum);//核心流水
		memset(sSql , 0x00 , sizeof(sSql));
		/* 与核心对账标志(0-初始1-对平2-主机无平台有3-平台无主机有4-金额不符) */
		sprintf(sSql , "UPDATE YW_WZYH_YWLS SET hxdzbz='3' WHERE waiblius='%s'" , YW_WZYH_COREMX.qslsh);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = DCIExecuteDirect(sSql);
		
		trim(YW_WZYH_COREMX.hxdate);
		trim(YW_WZYH_COREMX.hxnum);
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE YW_WZYH_COREMX SET dzflag='3' WHERE qslsh='%s'" , YW_WZYH_COREMX.qslsh);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = DCIExecuteDirect(sSql);
		if (iRet < 0)	
		{
			LOG(LM_DEBUG,Fmtmsg("组件[%s] 修改核心对账明细表状态失败 hxdate=[%s] hxnum=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),YW_WZYH_COREMX.hxdate,trim(YW_WZYH_COREMX.hxnum),iRet),"")
			DCIFreeCursor(cur);
			DCIRollback();
			return -1;
		}
		
		if(i>=100)
		{
			LOG(LM_DEBUG,Fmtmsg("达到【%d】条,需提交一次", i), "")
			DCICommit();
			i=0;
		}

		memset(&YW_WZYH_COREMX, 0x00, sizeof(YW_WZYH_COREMX));
	}
	if (iRet < 0)		/* iRet=0读完记录，iRet<0读取记录时失败 */
	{
		LOG(LM_DEBUG,Fmtmsg("组件[%s] 执行查询交易失败qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq, iRet), "")
		DCIFreeCursor(cur);
		DCIRollback();
		return -1;
	}
	
	DCIFreeCursor(cur);
	DCICommit();  	 

	return 0;
}

/********************************************************************
组件注册名称：WZYH_LOAD_NOTEFILE
组件运行名称：WZYH_LOAD_NOTEFILE
组件函数定义：
组件函数功能：加载微动力对账文件
组件配置参数：
    序号    参数名称    资源类别    缺省值    是否可空    参数说明
组件结果状态：
    状态    结果说明
项 目 组：
程 序 员：txbdir
发布日期：20171106
修改日期：
*********************************************************************/
IRESULT WZYH_LOAD_NOTEFILE(HXMLTREE lXmlhandle)
{
	char chk_date[10+1];   //对账日期
	SDB_YW_WZYH_DZMX YW_WZYH_DZMX;
	char sTmp[256], sErrMsg[256];          //取操作参数(要定义大一点)
	char file_name[140+1];   //对账文件路径(存放全路径)
	char buf[1024], sSql[1024];          //存放文件每一行内容
	FILE *fp;                //文件指针
	char delims[]="|";       //每行里的每一列分隔符
	char *p = NULL;          //每一行内容的存放指针
	char sBuf[256];          //存放金额temp
	char sAcct2622[20] , sAcct2622Name[64];
	char sAcct1392[20] , sAcct1392Name[64];
	int iRet , cnt=0 , fcnt;
	double amt=0 , famt;
	
	fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
	LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
#endif
  
	/*参数1*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(1, sTmp, "对账日期");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("对账日期"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "对账日期不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(chk_date,0,sizeof(chk_date));
	strcpy(chk_date, sTmp);
	LOG(LM_STD,Fmtmsg("对账日期 [%s] ",chk_date), "INFO");
	
	/*参数2*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(2, sTmp, "对账文件全路径");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("对账文件全路径"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "对账文件全路径不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(file_name,0,sizeof(file_name));
	memcpy(sTmp+(strlen(sTmp)-3) , "txt" , 3);
	memcpy(file_name, sTmp , strlen(sTmp));
	
	LOG(LM_STD,Fmtmsg("对账文件全路径 [%s] len[%d] , sTmp[%s]",file_name , strlen(sTmp) , sTmp), "INFO");
	
	memset(sAcct2622 , 0x00 , sizeof(sAcct2622));
	memset(sAcct2622Name , 0x00 , sizeof(sAcct2622Name));
	memset(sAcct1392 , 0x00 , sizeof(sAcct1392));
	memset(sAcct1392Name , 0x00 , sizeof(sAcct1392Name));
	
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_ACCT2622'");
	iRet = DBSelectToVarChar(sErrMsg, sAcct2622, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("组件[%s]获取微众金归集户账户错SQLCODE=[%d]" , fpub_GetCompname(lXmlhandle) , iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"获取状态信息错");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_ACCT2622NAME'");
	iRet = DBSelectToVarChar(sErrMsg, sAcct2622Name, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("组件[%s]获取微众金归集户户名错SQLCODE=[%d]" , fpub_GetCompname(lXmlhandle) , iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"获取状态信息错");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_ACCT1392'");
	iRet = DBSelectToVarChar(sErrMsg, sAcct1392, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("组件[%s]获取微众金赎回户账户错SQLCODE=[%d]" , fpub_GetCompname(lXmlhandle) , iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"获取状态信息错");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_ACCT1392NAME'");
	iRet = DBSelectToVarChar(sErrMsg, sAcct1392Name, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("组件[%s]获取微众金赎回户账户户名错SQLCODE=[%d]" , fpub_GetCompname(lXmlhandle) , iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"获取状态信息错");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	
	/* 打开文件 */
	if ((fp=fopen(file_name,"r")) == NULL)  //以只读方式打开，文件必须存在
	{
		LOG(LM_STD,Fmtmsg("组件[%s] 打开文件失败=[%s]",fpub_GetCompname(lXmlhandle),file_name),"INFO")
		fpub_SetMsg(lXmlhandle, 10001, "打开对账文件失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	   
	//清空当理加载数据
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "DELETE FROM yw_wzyh_dzmx WHERE dzrq='%s'" , chk_date);
	iRet = DCIExecuteDirect(sSql);
	
	//注意：如果是空文件加载会不会出错-----这个到时候注意一下
	//循环读文件每行然后登记到表里
	while (!feof(fp))
	{
		memset(buf,0x00,sizeof(buf));
		fgets(buf,sizeof(buf)-1,fp);
		if (strlen(buf)==0) continue;//读取到了空行或者到了最后一行
		LOG(LM_STD,Fmtmsg("对账文件明细行信息[%s]",buf),"INFO");

		/*报文发起行号|报文接收行号|订单流水号|订单发起时间|业务种类|账户类型|清算日期|
		场次|金额|币种|手续费|付款方行号|付款方账号|付款方户名|收款方行号|收款方账号|
		收款方户名|接口类型|处理结果|冲正标示|冲正流水号*/
		p=buf;   //指针会被重复赋值,后面有清空
		memset(&YW_WZYH_DZMX, 0, sizeof(YW_WZYH_DZMX));
		strncpy(YW_WZYH_DZMX.dzrq,chk_date,sizeof(YW_WZYH_DZMX.dzrq)-1);//文件通知里的清算日期---应该和文件里的清算日期是一致的，不能存在不一致或有两天的
		trim(YW_WZYH_DZMX.dzrq);
		strncpy(YW_WZYH_DZMX.file_name,file_name,sizeof(YW_WZYH_DZMX.file_name)-1);//存对账文件名
		trim(YW_WZYH_DZMX.file_name);
		
		//取文件每行内容
		strncpy(YW_WZYH_DZMX.snd_organ,strsep(&p,delims),sizeof(YW_WZYH_DZMX.snd_organ)-1);
		trim(YW_WZYH_DZMX.snd_organ);
		strncpy(YW_WZYH_DZMX.rev_organ,strsep(&p,delims),sizeof(YW_WZYH_DZMX.rev_organ)-1);
		trim(YW_WZYH_DZMX.rev_organ);
		strncpy(YW_WZYH_DZMX.business_id,strsep(&p,delims),sizeof(YW_WZYH_DZMX.business_id)-1);
		trim(YW_WZYH_DZMX.business_id);
		strncpy(YW_WZYH_DZMX.transtime,strsep(&p,delims),sizeof(YW_WZYH_DZMX.transtime)-1);
		trim(YW_WZYH_DZMX.transtime);
		strncpy(YW_WZYH_DZMX.business_type,strsep(&p,delims),sizeof(YW_WZYH_DZMX.business_type)-1);
		trim(YW_WZYH_DZMX.business_type);
		strncpy(YW_WZYH_DZMX.acct_type,strsep(&p,delims),sizeof(YW_WZYH_DZMX.acct_type)-1);
		trim(YW_WZYH_DZMX.acct_type);
		strncpy(YW_WZYH_DZMX.work_date,strsep(&p,delims),sizeof(YW_WZYH_DZMX.work_date)-1);
		trim(YW_WZYH_DZMX.work_date);
		strncpy(YW_WZYH_DZMX.scene_no,strsep(&p,delims),sizeof(YW_WZYH_DZMX.scene_no)-1);
		trim(YW_WZYH_DZMX.scene_no);
		
		//交易金额特殊处理
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_DZMX.amount = atof(sBuf)/100;
		strncpy(YW_WZYH_DZMX.ccy,strsep(&p,delims),sizeof(YW_WZYH_DZMX.ccy)-1);
		trim(YW_WZYH_DZMX.ccy);
		
		//交易手续费特殊处理
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_DZMX.fee_amount = atof(sBuf)/100;
		strncpy(YW_WZYH_DZMX.payer_opbk,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payer_opbk)-1);
		trim(YW_WZYH_DZMX.payer_opbk);
		strncpy(YW_WZYH_DZMX.payer_acct,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payer_acct)-1);
		trim(YW_WZYH_DZMX.payer_acct);
		strncpy(YW_WZYH_DZMX.payer_name,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payer_name)-1);
		trim(YW_WZYH_DZMX.payer_name);
		strncpy(YW_WZYH_DZMX.payee_opbk,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payee_opbk)-1);
		trim(YW_WZYH_DZMX.payee_opbk);
		strncpy(YW_WZYH_DZMX.payee_acct,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payee_acct)-1);
		trim(YW_WZYH_DZMX.payee_acct);
		strncpy(YW_WZYH_DZMX.payee_name,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payee_name)-1);
		trim(YW_WZYH_DZMX.payee_name);
		strncpy(YW_WZYH_DZMX.tran_type,strsep(&p,delims),sizeof(YW_WZYH_DZMX.tran_type)-1);
		trim(YW_WZYH_DZMX.tran_type);
		strncpy(YW_WZYH_DZMX.deal_flag,strsep(&p,delims),sizeof(YW_WZYH_DZMX.deal_flag)-1);
		trim(YW_WZYH_DZMX.deal_flag);
		strncpy(YW_WZYH_DZMX.cz_flag,strsep(&p,delims),sizeof(YW_WZYH_DZMX.cz_flag)-1);
		trim(YW_WZYH_DZMX.cz_flag);
		strncpy(YW_WZYH_DZMX.cz_business_id,strsep(&p,delims),sizeof(YW_WZYH_DZMX.cz_business_id)-1);
		trim(YW_WZYH_DZMX.cz_business_id);
		
		if (memcmp(YW_WZYH_DZMX.tran_type , "01" , 2) == 0)
		{	/* 申购 */
			memset(YW_WZYH_DZMX.payee_acct , 0x00 , sizeof(YW_WZYH_DZMX.payee_acct));
			memset(YW_WZYH_DZMX.payee_name , 0x00 , sizeof(YW_WZYH_DZMX.payee_name));
			memcpy(YW_WZYH_DZMX.payee_acct , sAcct2622 , strlen(sAcct2622));
			memcpy(YW_WZYH_DZMX.payee_name , sAcct2622Name , strlen(sAcct2622Name));
		}
		else /* 赎回 */
		{
			memset(YW_WZYH_DZMX.payer_acct , 0x00 , sizeof(YW_WZYH_DZMX.payee_acct));
			memset(YW_WZYH_DZMX.payer_name , 0x00 , sizeof(YW_WZYH_DZMX.payee_name));
			memcpy(YW_WZYH_DZMX.payer_acct , sAcct1392 , strlen(sAcct1392));
			memcpy(YW_WZYH_DZMX.payer_name , sAcct1392Name , strlen(sAcct1392Name));
		}
		
		//对账标志初始化为0
		strncpy(YW_WZYH_DZMX.dz_flag , "0" , sizeof(YW_WZYH_DZMX.dz_flag)-1);
		trim(YW_WZYH_DZMX.dz_flag); 
		p = NULL;//指针置为空
		
		cnt++;
		amt = amt + YW_WZYH_DZMX.amount;
		
		if(memcmp(YW_WZYH_DZMX.business_id , "18012532358400088800000000142687" , strlen("18012532358400088800000000142687")) == 0)
			YW_WZYH_DZMX.amount = 126;
			
		if((memcmp(YW_WZYH_DZMX.business_id , "18012532358400088800000000075519" , strlen("18012532358400088800000000075519")) == 0) ||
			(memcmp(YW_WZYH_DZMX.business_id , "18012532358400088800000000142742" , strlen("18012532358400088800000000142742")) == 0)
		)
			continue;
		
		/*插入微动力对账明细表*/
		LOG(LM_STD,Fmtmsg("插入微动力对账明细表"), "INFO");
		iRet=DBInsert("YW_WZYH_DZMX", SD_YW_WZYH_DZMX ,NUMELE(SD_YW_WZYH_DZMX), &YW_WZYH_DZMX, sErrMsg);
		if ( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("插入微动力对账明细表sqlca.sqlcode=[%d] , sErrMsg[%s]",iRet , sErrMsg),"DEBUG");
			fclose(fp);  //关闭文件指针
			DCIRollback();  //数据库回滚
			fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,"插入微动力对账明细表失败");
			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,"插入微动力对账明细表失败","ERROR");
		}
		
		//cnt++;
		//amt = amt + YW_WZYH_DZMX.amount;	
	}
    DCICommit();
    fclose(fp);  //关闭文件指针
	
	/* 总笔数 */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/wzyh/ggbody/file_line_count", sBuf)
	LOG(LM_STD,Fmtmsg("fcnt[%s]" , sBuf),"INFO");
	fcnt = atoi(sBuf);
	
	/* 总金额 */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/wzyh/ggbody/total_amount", sBuf)
	LOG(LM_STD,Fmtmsg("famt[%s]" , sBuf),"INFO");
	famt = atof(sBuf);
	
	LOG(LM_STD,Fmtmsg("cnt[%d],fcnt[%d],amt[%f],famt[%f]" , cnt , fcnt , amt , famt ),"INFO");
	if((cnt!=fcnt) || (abs(amt*100-famt)>0.000001))
	{
		LOG(LM_STD,Fmtmsg("报文请求条数或总金额与插入数据库中的数据不符"),"DEBUG");
		fpub_SetMsg(lXmlhandle, 10001, "报文请求条数或总金额与插入数据库中的数据不符");
		//fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}

#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "")
#endif

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/********************************************************************
组件注册名称：WZYH_LOAD_LCMXFILE
组件运行名称：WZYH_LOAD_LCMXFILE
组件函数定义：
组件函数功能：加载微动力理财明细文件
组件配置参数：
    序号    参数名称    资源类别    缺省值    是否可空    参数说明
组件结果状态：
    状态    结果说明
项 目 组：
程 序 员：txbdir
发布日期：20171107
修改日期：
*********************************************************************/
IRESULT WZYH_LOAD_LCMXFILE(HXMLTREE lXmlhandle)
{
	char wjrq[10+1];   //文件日期
	char sTmp[256];          //取操作参数(要定义大一点)
	char file_name[140+1];   //对账文件路径(存放全路径)
	char buf[1024], sSql[1024];          //存放文件每一行内容
	FILE *fp;                //文件指针
	char delims[]="|";       //每行里的每一列分隔符
	char *p = NULL;          //每一行内容的存放指针
	char sBuf[256], sErrMsg[256];          //存放金额temp
	int i=0 , iRet;                 //用于去掉第一行
	SDB_YW_WZYH_LCMX YW_WZYH_LCMX;
	
	fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
	LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
#endif    
  
	/*参数1*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(1, sTmp, "文件日期");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("文件日期"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "文件日期不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(wjrq,0,sizeof(wjrq));
	strcpy(wjrq, sTmp);
	LOG(LM_STD,Fmtmsg("文件日期 [%s] ",wjrq), "INFO");
	
	/*参数2*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(2, sTmp, "理财明细文件全路径");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("理财明细文件全路径"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "理财明细文件全路径不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(file_name,0,sizeof(file_name));
	strcpy(file_name, sTmp);
	LOG(LM_STD,Fmtmsg("理财明细文件全路径 [%s] ",file_name), "INFO");
	
	
	/* 打开文件 */
	if ((fp=fopen(file_name,"r")) == NULL)  //以只读方式打开，文件必须存在
	{
		LOG(LM_STD,Fmtmsg("组件[%s] 打开理财明细文件失败=[%s]",fpub_GetCompname(lXmlhandle),file_name),"INFO")
		fpub_SetMsg(lXmlhandle, 10001, "打开理财明细文件失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	//清空当理加载数据
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "DELETE FROM YW_WZYH_LCMX WHERE wjrq='%s'" , wjrq);
	iRet = DCIExecuteDirect(sSql);
	DCICommit();
	  
	//注意：如果是空文件加载会不会出错-----这个到时候注意一下
	//循环读文件每行然后登记到表里
	while (!feof(fp))
	{
		i++;
		
		memset(buf,0x00,sizeof(buf));
		fgets(buf,sizeof(buf)-1,fp);
		if (strlen(buf)==0) continue;//读取到了空行或者到了最后一行
		LOG(LM_STD,Fmtmsg("理财明细文件行信息[%s]",buf),"INFO");
		
		if(i==1&&strlen(buf)>0)continue;//越过第一行
		
		/*业务流水号|交易流水号|原交易流水号|交易日期|交易时间|交易类型|交易金额|交易份额|客户姓名|证件类型|证件号码|产品编码|产品名称*/
		p=buf;   //指针会被重复赋值,后面有清空
		memset(&YW_WZYH_LCMX, 0, sizeof(YW_WZYH_LCMX));
		strncpy(YW_WZYH_LCMX.wjrq,wjrq,sizeof(YW_WZYH_LCMX.wjrq)-1);//文件通知里的清算日期---应该和文件里的清算日期是一致的，不能存在不一致或有两天的
		trim(YW_WZYH_LCMX.wjrq);
		strncpy(YW_WZYH_LCMX.file_name,file_name,sizeof(YW_WZYH_LCMX.file_name)-1);//存文件名
		trim(YW_WZYH_LCMX.file_name);
		
		//取文件每行内容
		strncpy(YW_WZYH_LCMX.yw_business,strsep(&p,delims),sizeof(YW_WZYH_LCMX.yw_business)-1);
		trim(YW_WZYH_LCMX.yw_business);
		strncpy(YW_WZYH_LCMX.business_id,strsep(&p,delims),sizeof(YW_WZYH_LCMX.business_id)-1);
		trim(YW_WZYH_LCMX.business_id);
		strncpy(YW_WZYH_LCMX.oribusiness_id,strsep(&p,delims),sizeof(YW_WZYH_LCMX.oribusiness_id)-1);
		trim(YW_WZYH_LCMX.oribusiness_id);
		strncpy(YW_WZYH_LCMX.jyrq,strsep(&p,delims),sizeof(YW_WZYH_LCMX.jyrq)-1);
		trim(YW_WZYH_LCMX.jyrq);
		strncpy(YW_WZYH_LCMX.transtime,strsep(&p,delims),sizeof(YW_WZYH_LCMX.transtime)-1);
		trim(YW_WZYH_LCMX.transtime);
		strncpy(YW_WZYH_LCMX.business_type,strsep(&p,delims),sizeof(YW_WZYH_LCMX.business_type)-1);
		trim(YW_WZYH_LCMX.business_type);
		//交易金额特殊处理
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_LCMX.amount = atof(sBuf);
		//交易份额特殊处理
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_LCMX.jy_num = atof(sBuf);
		strncpy(YW_WZYH_LCMX.cust_name,strsep(&p,delims),sizeof(YW_WZYH_LCMX.cust_name)-1);
		trim(YW_WZYH_LCMX.cust_name);
		strncpy(YW_WZYH_LCMX.cert_type,strsep(&p,delims),sizeof(YW_WZYH_LCMX.cert_type)-1);
		trim(YW_WZYH_LCMX.cert_type);
		strncpy(YW_WZYH_LCMX.cert_id,strsep(&p,delims),sizeof(YW_WZYH_LCMX.cert_id)-1);
		trim(YW_WZYH_LCMX.cert_id);
		strncpy(YW_WZYH_LCMX.product_id,strsep(&p,delims),sizeof(YW_WZYH_LCMX.product_id)-1);
		trim(YW_WZYH_LCMX.product_id);
		strncpy(YW_WZYH_LCMX.product_name,strsep(&p,delims),sizeof(YW_WZYH_LCMX.product_name)-1);
		trim(YW_WZYH_LCMX.product_name);
		strncpy(YW_WZYH_LCMX.status,strsep(&p,delims),sizeof(YW_WZYH_LCMX.status)-1);
		trim(YW_WZYH_LCMX.status);
		p=NULL;//指针置为空
		
		/*YW_WZYH_LCMX的备注没有赋值，但是是有初始化的*/
		/*插入微动力理财明细文件表*/
		LOG(LM_STD,Fmtmsg("插入微动力理财明细文件表"), "INFO");
		iRet=DBInsert("YW_WZYH_LCMX", SD_YW_WZYH_LCMX ,NUMELE(SD_YW_WZYH_LCMX), &YW_WZYH_LCMX, sErrMsg);
		if ( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("插入微动力理财明细文件表sqlca.sqlcode=[%d]", iRet),"DEBUG");
			fclose(fp);  //关闭文件指针
			DCIRollback();  //数据库回滚
			fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,"插入微动力理财明细文件表失败");
			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,"插入微动力理财明细文件表失败","ERROR");
		}
		
		DCICommit();
	  }
    
    fclose(fp);  //关闭文件指针
#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "")
#endif
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/********************************************************************
组件注册名称：WZYH_LOAD_BYLMXFILE
组件运行名称：WZYH_LOAD_BYLMXFILE
组件函数定义：
组件函数功能：加载微动力保有量文件
组件配置参数：
    序号    参数名称    资源类别    缺省值    是否可空    参数说明
组件结果状态：
    状态    结果说明
项 目 组：
程 序 员：sgy
发布日期：20170921
修改日期：
*********************************************************************/
IRESULT WZYH_LOAD_BYLMXFILE(HXMLTREE lXmlhandle)
{
	char wjrq[10+1];   //文件日期
	SDB_YW_WZYH_BYLMX YW_WZYH_BYLMX;
	char sTmp[256], sSql[256], sErrMsg[256];          //取操作参数(要定义大一点)
	char file_name[140+1];   //对账文件路径(存放全路径)
	char buf[1024];          //存放文件每一行内容
	FILE *fp;                //文件指针
	char delims[]="|";       //每行里的每一列分隔符
	char *p = NULL;          //每一行内容的存放指针
	char sBuf[256];          //存放金额temp
	int i=0, iRet;                 //用于去掉第一行     
	
	fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
	LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
#endif

	/*参数1*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(1, sTmp, "文件日期");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("文件日期"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "文件日期不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(wjrq,0,sizeof(wjrq));
	strcpy(wjrq, sTmp);
	LOG(LM_STD,Fmtmsg("文件日期 [%s] ",wjrq), "INFO");
	
	/*参数2*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(2, sTmp, "保有量文件全路径");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("保有量文件全路径"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "保有量文件全路径不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(file_name,0,sizeof(file_name));
	strcpy(file_name, sTmp);
	LOG(LM_STD,Fmtmsg("保有量文件全路径 [%s] ",file_name), "INFO");	
	
	/* 打开文件 */
	if ((fp=fopen(file_name,"r")) == NULL)  //以只读方式打开，文件必须存在
	{
		LOG(LM_STD,Fmtmsg("组件[%s] 打开保有量文件失败=[%s]",fpub_GetCompname(lXmlhandle),file_name),"INFO")
		fpub_SetMsg(lXmlhandle, 10001, "打开保有量文件失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	//清空当理加载数据
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "DELETE FROM YW_WZYH_BYLMX WHERE wjrq='%s'" , wjrq);
	iRet = DCIExecuteDirect(sSql);
	DCICommit();
	
	//注意：如果是空文件加载会不会出错-----这个到时候注意一下
	//循环读文件每行然后登记到表里
	while (!feof(fp))
	{
		i++;
		
		memset(buf, 0x00, sizeof(buf));
		fgets(buf, sizeof(buf)-1 ,fp);
		if (strlen(buf) == 0) continue;//读取到了空行或者到了最后一行
		LOG(LM_STD,Fmtmsg("保有量文件行信息[%s]",buf),"INFO");
		
		if(i==1 && strlen(buf)>0)continue;//越过第一行
		
		/*统计日期|产品代码|产品总份额|产品净值*/
		p=buf;   //指针会被重复赋值,后面有清空
		memset(&YW_WZYH_BYLMX, 0, sizeof(YW_WZYH_BYLMX));
		strncpy(YW_WZYH_BYLMX.wjrq,wjrq,sizeof(YW_WZYH_BYLMX.wjrq)-1);//文件通知里的清算日期---应该和文件里的清算日期是一致的，不能存在不一致或有两天的
		trim(YW_WZYH_BYLMX.wjrq);
		strncpy(YW_WZYH_BYLMX.file_name,file_name,sizeof(YW_WZYH_BYLMX.file_name)-1);//存文件名
		trim(YW_WZYH_BYLMX.file_name);
		
		//取文件每行内容
		strncpy(YW_WZYH_BYLMX.tjrq,strsep(&p,delims),sizeof(YW_WZYH_BYLMX.tjrq)-1);
		trim(YW_WZYH_BYLMX.tjrq);
		strncpy(YW_WZYH_BYLMX.product_id,strsep(&p,delims),sizeof(YW_WZYH_BYLMX.product_id)-1);
		trim(YW_WZYH_BYLMX.product_id);
		//产品总份额特殊处理
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_BYLMX.product_amount = atof(sBuf);
		//产品净值特殊处理
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_BYLMX.product_net_amount = atof(sBuf);
		p=NULL;//指针置为空
		/*YW_WZYH_BYLMX的备注没有赋值，但是是有初始化的*/
		/*插入微动力保有量文件表*/
		LOG(LM_STD,Fmtmsg("插入微动力保有量文件表"), "INFO");
		iRet=DBInsert("YW_WZYH_BYLMX", SD_YW_WZYH_BYLMX ,NUMELE(SD_YW_WZYH_BYLMX), &YW_WZYH_BYLMX, sErrMsg);
		if ( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("插入微动力保有量文件表sqlca.sqlcode=[%d]", iRet),"DEBUG");
			fclose(fp);  //关闭文件指针
			DCIRollback();  //数据库回滚
			fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,"插入微动力保有量文件表失败");
			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,"插入微动力保有量文件表失败","ERROR");
		}
		
		DCICommit();
	  }
    
    fclose(fp);  //关闭文件指针
#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "")
#endif

	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
	return COMPSTATUS_SUCC;
}

/********************************************************************
组件注册名称：WZYH_CHK_NOTE
组件运行名称：WZYH_CHK_NOTE
组件函数定义：
组件函数功能：微众与核心对账
组件配置参数：
    序号    参数名称    资源类别    缺省值    是否可空    参数说明
组件结果状态：
    状态    结果说明
项 目 组：
程 序 员：sgy
发布日期：20171107
修改日期：
*********************************************************************/
IRESULT WZYH_CHK_NOTE(HXMLTREE lXmlhandle)
{
	char chk_date[10+1];   //对账日期
	char qsjg[14+1], sSql[1024], sErrMsg[256];   //清算机构
	char dzstate[2+1];  //对账状态
	SDB_YW_WZYH_DZJG   YW_WZYH_DZJG;//对账结果表
	char sTmp[256];          //取操作参数(要定义大一点)
	int iRet=0;              //存放返回值
	
	fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
	LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
#endif
    
	/*参数1*/
	//取对账日期
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(1, sTmp, "对账日期");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("对账日期"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "对账日期不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(chk_date,0,sizeof(chk_date));
	strcpy(chk_date, sTmp);
	LOG(LM_STD,Fmtmsg("对账日期 [%s] ",chk_date), "INFO");	
	
	/*参数2*/
	//取清算机构
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(2, sTmp, "清算机构");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("清算机构"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "清算机构不能为空");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(qsjg,0,sizeof(qsjg));
	strcpy(qsjg, sTmp);
	LOG(LM_STD,Fmtmsg("清算机构 [%s] ",qsjg), "INFO");
	
	//获取当前对账状态
	memset(dzstate,0,sizeof(dzstate));
	memset(dzstate,0,sizeof(dzstate));
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "SELECT DZSTATE FROM YW_WZYH_DZKZ WHERE qsrq='%s'" , chk_date);
	LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
	iRet = DBSelectToVarChar(sErrMsg, dzstate, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("组件[%s]获取状态信息错[%s][%s] SQLCODE=[%d]",fpub_GetCompname(lXmlhandle),qsjg,chk_date, iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"获取状态信息错");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	
	/* 检查与核心对账是否完成 */
	if (dzstate[0] != '1')
	{	
		//更新对账控制表状态
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE YW_WZYH_DZKZ set DZSTATE='3' , DZMSG='微动力与核心对账正在进行' WHERE qsrq='%s'" , chk_date);
		iRet = DCIExecuteDirect(sSql);
		if (iRet < 0)
		{
			LOG(LM_DEBUG,Fmtmsg("组件[%s]修改对账状态错[%s][%s] SQLCODE=[%d]",fpub_GetCompname(lXmlhandle),qsjg,chk_date, iRet),"")
			fpub_SetMsg(lXmlhandle,9000,"修改对账状态错");
			DCIRollback();
			fpub_SetCompStatus(lXmlhandle,-1);
			return -1;
		}
		DCICommit();
    
        /*与核心对账*/
        iRet = Process_CHKWDLCOREBAK(lXmlhandle,qsjg,chk_date);
        if (iRet !=0)
        {
            fpub_SetMsg(lXmlhandle,9000, "微动力与核心对账错");
			memset(sSql , 0x00 , sizeof(sSql));
			sprintf(sSql , "UPDATE YW_WZYH_DZKZ set DZSTATE='2',DZMSG='微动力与核心对账错' WHERE qsrq='%s'" , chk_date);
			iRet = DCIExecuteDirect(sSql);
			DCICommit();
            fpub_SetCompStatus(lXmlhandle,-1);
            return -1;
        }
		LOG(LM_DEBUG,Fmtmsg("微动力与核心对账完成"),"")        

		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE YW_WZYH_DZKZ set DZSTATE='1', DZMSG='微动力与核心对账完成' WHERE qsrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DCIExecuteDirect(sSql);
		if (iRet < 0)
		{
			LOG(LM_DEBUG,Fmtmsg("组件[%s]修改对账状态错[%s][%s] SQLCODE=[%d]",fpub_GetCompname(lXmlhandle),qsjg,chk_date, iRet),"")
			fpub_SetMsg(lXmlhandle,9000,"修改对账状态错");
			DCIRollback();
			fpub_SetCompStatus(lXmlhandle,-1);
			return -1;
		}
		DCICommit();
        
		/*更新对账结果表----微动力个性化设计*/
		/*先删除当天对账结果表再插入*/
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , " DELETE FROM YW_WZYH_DZJG WHERE qsrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DCIExecuteDirect(sSql);
		DCICommit();
		
		memset(&YW_WZYH_DZJG, 0x00, sizeof(YW_WZYH_DZJG));
		memcpy(YW_WZYH_DZJG.product_buy_num, "0", 1); 
		memcpy(YW_WZYH_DZJG.product_back_num, "0", 1);
		YW_WZYH_DZJG.product_buy_amount=0.00; 
		YW_WZYH_DZJG.product_back_amount=0.00; 
		
		/* 以下是针对对账平的记录进行统计写入对账结果表 */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(dz_flag),0)), char(COALESCE(SUM(amount),0)) FROM YW_WZYH_DZMX WHERE dzrq='%s' and tran_type='01' and dz_flag='1'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		memset(sTmp , 0x00 , sizeof(sTmp));
		iRet = DBSelectToMultiVar(sErrMsg , sSql , YW_WZYH_DZJG.product_buy_num, sTmp);
		if (iRet < 0)
		{
			LOG(LM_STD, Fmtmsg("微动力对账明细表查询失败[%d] , sErrMsg[%s]", iRet , sErrMsg), "DEBUG")
			fpub_SetMsg(lXmlhandle,9000,"微动力对账明细表查询失败");
			DCIRollback();
			fpub_SetCompStatus(lXmlhandle,-1);
			return -1;
		}
		YW_WZYH_DZJG.product_buy_amount = atof(sTmp);
		LOG(LM_STD, Fmtmsg("微动力对账结果表, product_buy_num[%s] , product_buy_amount[%f] , sTmp[%s] , iRet[%d]", YW_WZYH_DZJG.product_buy_num , YW_WZYH_DZJG.product_buy_amount , sTmp , iRet), "DEBUG")
		
		memset(sSql , 0x00 , sizeof(sSql));
		memset(sTmp , 0x00 , sizeof(sTmp));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(dz_flag),0)), char(COALESCE(SUM(amount),0)) FROM YW_WZYH_DZMX WHERE dzrq='%s' and tran_type='02' and dz_flag='1'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DBSelectToMultiVar(sErrMsg , sSql , YW_WZYH_DZJG.product_back_num, sTmp);    
		if (iRet < 0)
		{
			LOG(LM_STD, Fmtmsg("微动力对账明细表查询失败[%d]", iRet), "DEBUG")
			fpub_SetMsg(lXmlhandle,9000,"微动力对账明细表查询失败");
			DCIRollback();
			fpub_SetCompStatus(lXmlhandle,-1);
			return -1;
		}
		YW_WZYH_DZJG.product_back_amount = atof(sTmp);
		trim(YW_WZYH_DZJG.product_buy_num);
		trim(YW_WZYH_DZJG.product_back_num);
		
		memcpy(YW_WZYH_DZJG.qsjg, qsjg, sizeof(YW_WZYH_DZJG.qsjg)-1); 
		memcpy(YW_WZYH_DZJG.qsrq, chk_date, sizeof(YW_WZYH_DZJG.qsrq)-1);
		memcpy(YW_WZYH_DZJG.dzmsg, "对账成功,但未清算", 17);
		memcpy(YW_WZYH_DZJG.dz_bz, "1", 17);
		
		//插入YW_WZYH_DZJG表
		iRet=DBInsert("YW_WZYH_DZJG", SD_YW_WZYH_DZJG ,NUMELE(SD_YW_WZYH_DZJG), &YW_WZYH_DZJG, sErrMsg);
		if (iRet < 0)
		{			
			LOG(LM_STD, Fmtmsg("插入对账结果表失败[%d]", iRet), "DEBUG")
			fpub_SetMsg(lXmlhandle,9000,"插入对账结果表失败");
			DCIRollback();
			fpub_SetCompStatus(lXmlhandle,-1);
			return -1;
		}
		
		/* 更新赎回，微众少，核心多 ，无记录流水 */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(*),0)) FROM YW_WZYH_ERRMX WHERE subtrantype='0002' AND lsbz='1' AND errflag='3' AND jyrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		memset(sTmp , 0x00 , sizeof(sTmp));
		iRet = DBSelectToMultiVar(sErrMsg , sSql , sTmp);
		LOG(LM_STD,Fmtmsg("iRet[%d] , sTmp[%s] " , iRet , sTmp), "INFO");
		if (iRet >=0)
		{
			if (sTmp[0] != '0')
			{
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , "INSERT INTO yw_wzyh_ywls (jyrq , flag , business_id , waiblius , hxxym , pay_tran_status , amount , hxdzbz , payer_acct , payer_name , payee_acct , payee_name , tran_type) SELECT '%s' , '0' , waiblius , waiblius ,  '000000' , '0000' , coreamount , 3 , payer_acct , payer_name , payee_acct , payee_name , '02' FROM yw_wzyh_errmx WHERE subtrantype='0002' AND lsbz='1' AND errflag='3' AND jyrq='%s'" , chk_date , chk_date);
				LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
				iRet = DCIExecuteDirect(sSql);
			}
		}
		
		/* 更新赎回，微众多，核心少 ，无记录流水 */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(*),0)) FROM YW_WZYH_ERRMX WHERE subtrantype='0002' AND lsbz='1' AND errflag='2' AND jyrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		memset(sTmp , 0x00 , sizeof(sTmp));
		iRet = DBSelectToMultiVar(sErrMsg , sSql , sTmp);
		LOG(LM_STD,Fmtmsg("iRet[%d] , sTmp[%s] " , iRet , sTmp), "INFO");
		if (iRet >=0)
		{
			if (sTmp[0] != '0')
			{
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , "INSERT INTO yw_wzyh_ywls (jyrq , flag , business_id , waiblius , hxxym , pay_tran_status , amount , hxdzbz , tzzt , beiy1 , payer_acct , payer_name , payee_acct , payee_name , tran_type) SELECT '%s' , '0' , business_id , '10002'|| '%s' || right(business_id , 14) ,  '000000' , '0000' , amount , '1' , '1' , '%s自动调账' , payer_acct , payer_name , payee_acct , payee_name , '02' FROM yw_wzyh_errmx WHERE subtrantype='0002' AND lsbz='1' AND errflag='2' AND jyrq='%s'" , chk_date , chk_date , chk_date , chk_date);
				LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
				iRet = DCIExecuteDirect(sSql);
			}
		}

		/* 更新申购,微众多，核心少 ，无流水记录 */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(*),0)) FROM YW_WZYH_ERRMX WHERE subtrantype='0001' AND lsbz='1' AND errflag='2' AND jyrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		memset(sTmp , 0x00 , sizeof(sTmp));
		iRet = DBSelectToMultiVar(sErrMsg , sSql , sTmp);
		LOG(LM_STD,Fmtmsg("iRet[%d] , sTmp[%s] " , iRet , sTmp), "INFO");
		if (iRet >=0)
		{
			if (sTmp[0] != '0')
			{
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , "INSERT INTO yw_wzyh_ywls (jyrq , flag , business_id , waiblius , hxxym , pay_tran_status , amount , hxdzbz , tzzt , beiy1 , payer_acct , payer_name , payee_acct , payee_name , czflag , tran_type) SELECT '%s' , '1' , business_id , '10002'|| '%s' || right(business_id , 14) ,  '000000' , '0000' , amount , '1' , '1' , '%s自动调账' , payer_acct , payer_name , payee_acct , payee_name , '1' , '01' FROM yw_wzyh_errmx WHERE subtrantype='0001' AND lsbz='1' AND errflag='2' AND jyrq='%s'" , chk_date , chk_date , chk_date , chk_date);
				LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
				iRet = DCIExecuteDirect(sSql);
			}
		}
		
		/* 申购，微众少，核心多，无流水记录 */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(*),0)) FROM YW_WZYH_ERRMX WHERE subtrantype='0001' AND lsbz='1' AND errflag='3' AND jyrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		memset(sTmp , 0x00 , sizeof(sTmp));
		iRet = DBSelectToMultiVar(sErrMsg , sSql , sTmp);
		LOG(LM_STD,Fmtmsg("iRet[%d] , sTmp[%s] " , iRet , sTmp), "INFO");
		if (iRet >=0)
		{
			if (sTmp[0] != '0')
			{
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , "INSERT INTO yw_wzyh_ywls (jyrq , flag , business_id , waiblius , hxxym , pay_tran_status , amount , hxdzbz , payer_acct , payer_name , payee_acct , payee_name , czflag , tran_type , tzzt , beiy1) SELECT '%s' , '1' , waiblius , waiblius ,  '000000' , '0000' , coreamount , 1 , payer_acct , payer_name , payee_acct , payee_name , '1' , '01' , '1' , '%s自动调账' FROM yw_wzyh_errmx WHERE subtrantype='0001' AND lsbz='1' AND errflag='3' AND jyrq='%s'" , chk_date , chk_date , chk_date);
				LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
				iRet = DCIExecuteDirect(sSql);
			}
		}
		
		/* 更新赎回，微众多，核心少 ，需要上账 */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE yw_wzyh_ywls SET hxdzbz='1' , beiy2=hxxym , beiy1='系统修改%s' , hxxym='000000' , pay_tran_status='0000' , czflag='' , tzzt='1' WHERE flag='0' AND hxdzbz='2' AND jyrq='%s'" , chk_date , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DCIExecuteDirect(sSql);
		
		/* 更新申购，(微众多，核心少) , (微众少，核心多) ，需要冲正 */
		/*memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE yw_wzyh_ywls SET hxdzbz='1' , czflag='1' ,  beiy2=hxdzbz , beiy1='系统修改%s' WHERE flag='1' AND hxdzbz IN('2' , '3') AND jyrq='%s' AND flag='1'" , chk_date , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DCIExecuteDirect(sSql);	*/

		/* 更新差错明细表中无核心流水字段 */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE yw_wzyh_errmx SET waiblius= '10002'|| '%s'|| right(business_id , 14) WHERE lsbz='1' AND errflag='2' AND jyrq='%s'" , chk_date , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DCIExecuteDirect(sSql);	
		
		DCICommit(); 
   }

#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "")
#endif

	DCICommit(); 

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/********************************************************************
组件注册名称：WZYH_GETCOREFILE
组件运行名称：WZYH_GETCOREFILE
组件函数定义：
组件函数功能：加载核心对账文件
组件配置参数：
    序号    参数名称    资源类别    缺省值    是否可空    参数说明
组件结果状态：
    状态    结果说明
项 目 组：
程 序 员：txbdir
发布日期：20171107
修改日期：
*********************************************************************/
IRESULT WZYH_GETCOREFILE(HXMLTREE lXmlhandle)
{
	SDB_YW_WZYH_COREMX stWzyhCoremx; 
	int iParas, iRet;
	double dAmt = 0.00;
	char sQshh[12+1];
	char sQsrq[8+1] , sSql[256], sErrMsg[256];
	char sFileName[100+1];
	char sBuf[200+1];
	char sBuffer[800] , *pBuffer;
	char systime[20] , *p;
	char cCoreStat[2];
	char sDqszh[32];
	char sYzzh[32];
	FILE *fp = NULL;
	
	memset(&stWzyhCoremx, 0x00, sizeof(stWzyhCoremx));
	memset(sQshh, 0x00, sizeof(sQshh));
	memset(sQsrq, 0x00, sizeof(sQsrq));
	memset(sFileName, 0x00, sizeof(sFileName));
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sBuffer, 0x00, sizeof(sBuffer));
	memset(systime, 0x00, sizeof(systime));
	memset(cCoreStat, 0x00, sizeof(cCoreStat));
	
	fpub_InitSoComp(lXmlhandle);
	
	LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")  
	
	/*3个参数*/
	COMP_PARACOUNTCHK(3)
	
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_GETPARSEPARAS(1, sBuf, "清算机构")
	pstrcopy(sQshh, sBuf, sizeof(sQshh));
	
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_GETPARSEPARAS(2,sBuf,"清算日期")
	pstrcopy(sQsrq, sBuf, sizeof(sQsrq));
	
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_GETPARSEPARAS(3, sBuf, "对账文件名")
	pstrcopy(sFileName, sBuf, sizeof(sFileName));
	
	LOG(LM_DEBUG,Fmtmsg("清算机构：[%s]清算日期：[%s]对账文件名：[%s]", sQshh, sQsrq, sFileName),"")
	
	//获取过渡户
	memset(sDqszh,0,sizeof(sDqszh));
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_DQSZH'");
	iRet = DBSelectToVarChar(sErrMsg, sDqszh, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("组件[%s]获取待清算账户错SQLCODE=[%d]",fpub_GetCompname(lXmlhandle),iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"获取状态信息错");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	trim(sDqszh);
	LOG(LM_DEBUG,Fmtmsg("组待清算户[%s]",sDqszh),"")  
	
	/* 影子账户 */
	memset(sYzzh,0,sizeof(sYzzh));
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_YZZH'");
	iRet = DBSelectToVarChar(sErrMsg, sYzzh, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("组件[%s]获取待清算账户错SQLCODE=[%d]" , fpub_GetCompname(lXmlhandle) , iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"获取状态信息错");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	trim(sYzzh);
	LOG(LM_DEBUG,Fmtmsg("影子账户[%s]",sYzzh),"")  
	
	fp = fopen(sFileName, "r");
	if( fp == NULL )
	{
		LOG(LM_STD, Fmtmsg("打开核心对账明细文件出错[%s]", sFileName), "");
		fpub_SetMsg(lXmlhandle,MID_SYS_OPENFILE, "打开核心对账明细文件出错");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		return -1;  
	}

#ifdef DBS_INFORMIX         
	sql_BeginTrans();
#endif    

	while( !feof(fp) )
	{
		memset((char *)&stWzyhCoremx, 0x00, sizeof(stWzyhCoremx));
		memset(sBuffer, 0x00, sizeof(sBuffer));
		fgets(sBuffer, sizeof(sBuffer), fp);
		LOG(LM_DEBUG,Fmtmsg("读取长度：[%d]", strlen(trim(sBuffer))),"")
		if (5 > strlen(trim(sBuffer)))
		{
			continue;
		}		
		pBuffer = sBuffer;
		
		/* 清算行号 */
		memcpy(stWzyhCoremx.qshh, sQshh, sizeof(stWzyhCoremx.qshh)-1);
		
		/* 前置日期 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.qsrq, sBuf , sizeof(stWzyhCoremx.qsrq)-1);
			trim(stWzyhCoremx.qsrq);
			LOG(LM_DEBUG,Fmtmsg("前置日期：[%s]", stWzyhCoremx.qsrq),"")
		}
		pBuffer = p+1;
		
		/* 前置流水 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.qslsh, sBuf, sizeof(stWzyhCoremx.qslsh)-1);
			trim(stWzyhCoremx.qslsh);  
			LOG(LM_DEBUG,Fmtmsg("前置流水：[%s]", stWzyhCoremx.qslsh),"")
		}
		pBuffer = p+1;
		
		/* 商户编号 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			LOG(LM_DEBUG,Fmtmsg("商户编号：[%s]", p),"")
		}
		pBuffer = p+1;
		
		/* 借方银行账号 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.jfyhzh, sBuf, sizeof(stWzyhCoremx.jfyhzh)-1);
			trim(stWzyhCoremx.jfyhzh);  
			LOG(LM_DEBUG,Fmtmsg("借方银行账号：[%s]", stWzyhCoremx.jfyhzh),"")
		}
		pBuffer = p+1;
		
		/* 借方户名 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.jfhm, sBuf, sizeof(sBuf));
			trim(stWzyhCoremx.jfhm);  
			LOG(LM_DEBUG,Fmtmsg("借方银行户名：[%s]", stWzyhCoremx.jfhm),"")
		}
		pBuffer = p+1;
		
		/* 货方银行账号 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.dfyhzh, sBuf, sizeof(stWzyhCoremx.dfyhzh)-1);
			trim(stWzyhCoremx.dfyhzh);  
			LOG(LM_DEBUG,Fmtmsg("货方银行账号：[%s]", stWzyhCoremx.dfyhzh),"")
		}
		pBuffer = p+1;
		
		/* 贷方户名 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.dfhm, sBuf, sizeof(sBuf));
			trim(stWzyhCoremx.dfhm);  
			LOG(LM_DEBUG,Fmtmsg("贷方银行户名：[%s]", stWzyhCoremx.dfhm),"")
		}
		pBuffer = p+1;
		
		/* 交易金额 */  
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			stWzyhCoremx.jyje = atof(sBuf);
			LOG(LM_DEBUG,Fmtmsg("交易金额：[%g]", stWzyhCoremx.jyje),"")
		}
		pBuffer = p+1;
		
		/* 币种 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
		}
		pBuffer = p+1;
		
		/* 核心日期 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			memcpy(stWzyhCoremx.hxdate, sBuf, sizeof(stWzyhCoremx.hxdate)-1);
			memcpy(stWzyhCoremx.hxdate, "20171201", 8);
			trim(stWzyhCoremx.hxdate);
			LOG(LM_DEBUG,Fmtmsg("核心日期：[%s]", stWzyhCoremx.hxdate),"")
		}
		pBuffer = p+1;
		
		/* 核心流水 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			memcpy(stWzyhCoremx.hxnum, sBuf, sizeof(stWzyhCoremx.hxnum)-1);
			trim(stWzyhCoremx.hxnum);
			LOG(LM_DEBUG,Fmtmsg("核心流水：[%s]", stWzyhCoremx.hxnum),"")
		}
		pBuffer = p+1;
		
		/* 电子账户记账状态 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			LOG(LM_DEBUG,Fmtmsg("记账状态：[%s]", sBuf),"")
		}
		pBuffer = p+1;
		
		/* 业务代码 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			memcpy(stWzyhCoremx.busstype, sBuf, sizeof(stWzyhCoremx.busstype)-1);
			trim(stWzyhCoremx.busstype);
			LOG(LM_DEBUG,Fmtmsg("业务代码：[%s]", stWzyhCoremx.busstype),"")
		}
		pBuffer = p+1;	
		
		/* 子业务代码 */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			memcpy(stWzyhCoremx.subbusstype, sBuf, sizeof(stWzyhCoremx.subbusstype)-1);
			trim(stWzyhCoremx.subbusstype);
			LOG(LM_DEBUG,Fmtmsg("子业务代码：[%s]", stWzyhCoremx.subbusstype),"")
		}
		pBuffer = p+1;
		
		memcpy(stWzyhCoremx.dzflag, "0", 1);
		
		if(memcmp(stWzyhCoremx.qslsh , "100021201801241391322" , strlen("100021201801241391322")) == 0)
		{
			stWzyhCoremx.jyje = 196;
		}
		if(
			(memcmp(stWzyhCoremx.qslsh , "100021201801251395790" , strlen("100021201801251395790")) == 0) ||
			(memcmp(stWzyhCoremx.qslsh , "100021201801251395781" , strlen("100021201801251395781")) == 0)
		)
			continue;
		
		iRet=DBInsert("YW_WZYH_COREMX", SD_YW_WZYH_COREMX ,NUMELE(SD_YW_WZYH_COREMX), &stWzyhCoremx, sErrMsg);
		if (iRet < 0)
		{
			LOG(LM_DEBUG,Fmtmsg("核心对账文件入库失败 sqlcode=[%d]", iRet),"")
			fpub_SetMsg(lXmlhandle, 10001, "核心对账文件入库失败");
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			DCIRollback();
			fclose(fp);
			return -1;
		}
    }
	
	DCICommit();
    fclose(fp);

#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "")
#endif

	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
	return COMPSTATUS_SUCC;

fail:	
	fpub_SetMsg(lXmlhandle, 10001, "解析记录失败");
	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	DCIRollback();
	fclose(fp);
	return -1;
}
