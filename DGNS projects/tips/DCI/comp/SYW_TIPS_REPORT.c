/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V3.0.00
操作系统:AIX5.3
文件名称:SYW_TIPS_REPORT.ec
文件描述:TIPS报表清单交易
项 目 组:TIPS专用前置产品组
程 序 员:Tuql
发布日期:
修    订:
修改日期:  
*********************************************************************/
/*
总体说明:

函数说明
组件函数名称                 组件名称                      发布日期  程序员 修改日期 修改人

*/

#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include "gaps_head.h"
/* add dci 20141103
EXEC SQL INCLUDE  "gaps_head.eh";
EXEC SQL INCLUDE  "../eh/tips_struct_report.eh";*/

#include  "../eh/tips_struct_report.h" 
#include  "../eh/tips_drls.h"   
#include  "../eh/tips_ssplksfmx.h"

int  (*prv_tips_reportXX)(HXMLTREE lXmlhandle, 
                          FILE *fp,
                          int *i, 
                          char dqdh[], 
                          char jgdh[],
                          char jgmc[], 
                          int *all, 
                          double *zje
                          );

int (*prv_tips_report_wqdbodyXX) (HXMLTREE lXmlhandle, 
                                  FILE *fp,
                                  int tablekind,
                                  int i,
                                  SDB_TIPS_STRUCT_REPORT stReport
                                  );

int prv_tips_qrycnjyzt(HXMLTREE lXmlhandle,
                       int tablekind, 
                       char jyzt[], 
                       char *cnjyzt,
                       int cnjyztlen
                       )
{
    /* EXEC SQL BEGIN DECLARE SECTION;*/
        char sCnJyzt[60];
        char sJyzt[1+1];
        char sCodeName[32];
    /* EXEC SQL END DECLARE SECTION;*/
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */
		
    memset(sJyzt, 0x00, sizeof(sJyzt));
    pstrcopy(sJyzt, jyzt, sizeof(sJyzt));
    
    memset(sCodeName, 0x00, sizeof(sCodeName));
    if ( tablekind == 1 )
    {
        strcpy(sCodeName, "drls_jyzt");
    }else
    {
        strcpy(sCodeName, "tipsplksfmxczbdsw");
    }    
    memset(sCnJyzt, 0x00, sizeof(sCnJyzt));
    /* add dci 20141103 */
    snprintf( sSql1, sizeof(sSql1), "select num_desc from tips_codelist \
    	where code_name='%s' and num='%s'",sCodeName,sJyzt);     	
    iRet = DBSelectToVar(sErrmsg, &sCnJyzt, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24502, "查询数据字典失败");
         return -1;        
    }

    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT num_desc INTO :sCnJyzt
         FROM tips_codelist
         WHERE code_name=:sCodeName
           AND num=:sJyzt;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24502, "查询数据字典失败");
         return -1;
    }
    */
    
    trim(sCnJyzt);
    if(sCnJyzt[0]=='\0')
        pstrcopy(cnjyzt, sJyzt, 1);
    else    
        pstrcopy(cnjyzt, sCnJyzt, cnjyztlen);
    return 0;        
}

/* 查询流水表总笔数 */
int prv_tips_report_count(HXMLTREE lXmlhandle,  
                            char dqdh[], 
                            char jgdh[],
                            char tablename[],
                            char wherecon[],
                            int *zbs,
                            double *zje
                            )
{
    /*EXEC SQL BEGIN DECLARE SECTION;*/
        char sSql[1024];
        int iCount;
        double dZje;/* 总金额 */
        short indZje;/* 指示变量 */
    /*EXEC SQL END DECLARE SECTION;*/
    char sQsrq[8+1];/* 起始日期 */
    char sJzrq[8+1];/* 截止日期 */
    char sTaxOrgCode[12+1];/* 征收机关代码 */
    char sTaxVouNo[18+1];/* 税票号码 */
    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		CURSOR cur;
		/* end add dci 20141103 */	
		
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsrq, 0x00, sizeof(sQsrq));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(sQsrq, sBuf, sizeof(sQsrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJzrq, 0x00, sizeof(sJzrq));
    COMP_SOFTGETXML("/tips/jzrq", sBuf)
    pstrcopy(sJzrq, sBuf, sizeof(sJzrq));

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_SOFTGETXML("/tips/TaxOrgCode", sBuf)
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxVouNo, 0x00, sizeof(sTaxVouNo));
    COMP_SOFTGETXML("/tips/TaxVouNo", sBuf)
    pstrcopy(sTaxVouNo, sBuf, sizeof(sTaxVouNo));         

    /* 先查询本机构是否有记录存在，若无，则返回 */    
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "select count(*), sum(jyje) from %s where 1=1 and zwrq >= '%s' and zwrq <= '%s' and dqdh='%s' and jgdh='%s' %s ", tablename, sQsrq, sJzrq, dqdh, jgdh, wherecon);
    if (strlen(sTaxOrgCode) !=0 )
    {
        snprintf(sSql+strlen(sSql), sizeof(sSql), "and taxorgcode='%s' ", sTaxOrgCode); 
    }        
    if (strlen(sTaxVouNo)!=0 )
    {
        snprintf(sSql+strlen(sSql), sizeof(sSql), "and taxvouno='%s' ", sTaxVouNo); 
    }
 		trim(sSql);
 		
 		/* add dci 20141103 */
 		if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
  	{
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
  	}
  	if (DCIExecute(cur) == -1)
  	{
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        
        fpub_SetMsg(lXmlhandle,24311, "前置系统错误:打开cur_report_count游标失败");       
        LOGRET(-1,LM_STD,Fmtmsg("打开cur_report_count游标失败"),
            fpub_GetCompname(lXmlhandle))
  	}
  	
 		/* end add dci 20141103 */
 		
 		/* mod dci 20141103
 		/*prepare
    EXEC SQL PREPARE sql_report_count FROM :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_report_count",sqlca.sqlcode),"ERROR");    
    /*declare
    EXEC SQL DECLARE cur_report_count CURSOR for sql_report_count;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_report_count",sqlca.sqlcode),"ERROR");

    EXEC SQL OPEN cur_report_count;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_report_count", sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24311, "前置系统错误:打开cur_report_count游标失败");       
        LOGRET(-1,LM_STD,Fmtmsg("打开cur_report_count游标失败"),
            fpub_GetCompname(lXmlhandle))
    }
    */
        
    iCount=0;
    dZje=0.00;
    indZje=0.00;
    
    /* add dci 20141103 */    
  	iRet = DCIFetch(cur);
  	if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        
        DCIFreeCursor(cur);   
        fpub_SetMsg(lXmlhandle,24312, "前置系统错误:从游标cur_report_count获取数据失败");       
        LOGRET(-2,LM_STD,Fmtmsg("从游标cur_report_count获取数据失败"),
            fpub_GetCompname(lXmlhandle))
    } 
    iCount= atoi( DCIFieldAsString(cur, 0 ) );	
    dZje=atof( DCIFieldAsString(cur, 1 ) );	
    DCIFreeCursor(cur);
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL FETCH cur_report_count INTO :iCount, :dZje;     
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_report_count",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {  
        EXEC SQL CLOSE cur_report_count;    
        fpub_SetMsg(lXmlhandle,24312, "前置系统错误:从游标cur_report_count获取数据失败");       
        LOGRET(-2,LM_STD,Fmtmsg("从游标cur_report_count获取数据失败"),
            fpub_GetCompname(lXmlhandle))
    }
    EXEC SQL CLOSE cur_report_count;  
    */  

    (*zbs)=iCount;    
    if ( iCount > 0 )
    {
        LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),fpub_GetCompname(lXmlhandle));   
        (*zje)=dZje;
    }else
    {
        (*zje)=0.00;        
    }
    return iCount;
}

/* 往账写清单体 */
int prv_tips_report_wqdbody01(HXMLTREE lXmlhandle, 
                              FILE *fp,
                              int tablekind,
                              int i,
                              SDB_TIPS_STRUCT_REPORT stReport
                              )
{
    char sCnJyzt[8+1];
    char sJyzt[1+1];
    int iRet=0;
    
    memset(sJyzt, 0x00, sizeof(sJyzt));
    pstrcopy(sJyzt, stReport.jyzt, sizeof(sJyzt));
    memset(sCnJyzt, 0x00, sizeof(sCnJyzt));
    iRet=prv_tips_qrycnjyzt(lXmlhandle,tablekind,sJyzt,sCnJyzt,sizeof(sCnJyzt));
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("查询交易状态失败[%d]",iRet),fpub_GetCompname(lXmlhandle));
        return iRet;   
    }    
    fprintf(fp,"%05d %8.8s %8d %24.24s %20.20s %15.2f  %12.12s  %18.18s %8.8s %8.8s %4.4s         %10.10s \n",
            i,stReport.zwrq,stReport.zhqzlsh,stReport.payacct,stReport.handorgname,stReport.jyje,stReport.taxorgcode,stReport.taxvouno,sCnJyzt,stReport.chkdate, stReport.chkacctord, stReport.jygy);        
    return 0;
}

/* 异常往账写清单体 */
int prv_tips_report_wqdbody02(HXMLTREE lXmlhandle, 
                              FILE *fp,
                              int tablekind,
                              int i,
                              SDB_TIPS_STRUCT_REPORT stReport
                              )
{
    char sCnJyzt[8+1];
    char sJyzt[1+1];
    int iRet=0;
    
    memset(sJyzt, 0x00, sizeof(sJyzt));
    pstrcopy(sJyzt, stReport.jyzt, sizeof(sJyzt));
    memset(sCnJyzt, 0x00, sizeof(sCnJyzt));
    iRet=prv_tips_qrycnjyzt(lXmlhandle,tablekind,sJyzt,sCnJyzt,sizeof(sCnJyzt));
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("查询交易状态失败[%d]",iRet),fpub_GetCompname(lXmlhandle));
        return iRet;   
    }
    fprintf(fp,"%05d %8.8s %8d %24.24s %20.20s %15.2f  %12.12s  %18.18s %8.8s %8.8s %4.4s         %10.10s  %30.30s\n",
            i,stReport.zwrq,stReport.zhqzlsh,stReport.payacct,stReport.handorgname,stReport.jyje,stReport.taxorgcode,stReport.taxvouno,sCnJyzt,stReport.chkdate, stReport.chkacctord, stReport.jygy, stReport.xyxx);        
    return 0;
}

/* 来账写清单体 */
int prv_tips_report_wqdbody03(HXMLTREE lXmlhandle, 
                              FILE *fp,
                              int tablekind,
                              int i,
                              SDB_TIPS_STRUCT_REPORT stReport
                              )
{
    char sCnJyzt[8+1];
    char sJyzt[1+1];
    int iRet=0;
    
    memset(sJyzt, 0x00, sizeof(sJyzt));
    pstrcopy(sJyzt, stReport.jyzt, sizeof(sJyzt));
    memset(sCnJyzt, 0x00, sizeof(sCnJyzt));
    iRet=prv_tips_qrycnjyzt(lXmlhandle,tablekind,sJyzt,sCnJyzt,sizeof(sCnJyzt));
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("查询交易状态失败[%d]",iRet),fpub_GetCompname(lXmlhandle));
        return iRet;   
    }
    fprintf(fp,"%05d %8.8s %8d   %24.24s %20.20s %15.2f  %12.12s  %20.20s %18.18s %8.8s %8.8s %4.4s          \n",
            i,stReport.zwrq,stReport.zhqzlsh,stReport.payacct,stReport.handorgname,stReport.jyje,stReport.taxorgcode,stReport.protocolno,stReport.taxvouno,sCnJyzt,stReport.chkdate, stReport.chkacctord);        
    return 0;
}

/* 异常来账写清单体 */
int prv_tips_report_wqdbody04(HXMLTREE lXmlhandle, 
                              FILE *fp,
                              int tablekind,
                              int i,
                              SDB_TIPS_STRUCT_REPORT stReport
                              )
{
    char sCnJyzt[8+1];
    char sJyzt[1+1];
    int iRet=0;
    
    memset(sJyzt, 0x00, sizeof(sJyzt));
    pstrcopy(sJyzt, stReport.jyzt, sizeof(sJyzt));
    memset(sCnJyzt, 0x00, sizeof(sCnJyzt));
    iRet=prv_tips_qrycnjyzt(lXmlhandle,tablekind,sJyzt,sCnJyzt,sizeof(sCnJyzt));
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("查询交易状态失败[%d]",iRet),fpub_GetCompname(lXmlhandle));
        return iRet;   
    }
    fprintf(fp,"%05d %8.8s %8d   %24.24s %20.20s %15.2f  %12.12s  %20.20s %18.18s %8.8s %8.8s %4.4s       %30.30s\n",
            i,stReport.zwrq,stReport.zhqzlsh,stReport.payacct,stReport.handorgname,stReport.jyje,stReport.taxorgcode,stReport.protocolno,stReport.taxvouno,sCnJyzt,stReport.chkdate, stReport.chkacctord, stReport.xyxx);        
    return 0;
}

/* 写清单(部分通用) */
int prv_tips_report_wqd(HXMLTREE lXmlhandle, 
                        FILE *fp, 
                        char dqdh[], 
                        char jgdh[], 
                        int *all, 
                        double *zje,
                        int tablekind,
                        char tablename[],
                        char wherecon[]
                        )
{
    /*EXEC SQL BEGIN DECLARE SECTION;*/
        char sSql[1024];
        int iCount;
        SDB_TIPS_STRUCT_REPORT stReport;
    /*EXEC SQL END DECLARE SECTION;*/
    char sQsrq[8+1];/* 起始日期 */
    char sJzrq[8+1];/* 截止日期 */
    char sTaxOrgCode[12+1];/* 征收机关代码 */
    char sTaxVouNo[18+1];/* 税票号码 */
    char sQdlb[2+1];/* 清单类别 */
    char sBuf[256];
    int iflag,i,j;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		CURSOR cur;
		/* end add dci 20141103 */	
		     
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsrq, 0x00, sizeof(sQsrq));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(sQsrq, sBuf, sizeof(sQsrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJzrq, 0x00, sizeof(sJzrq));
    COMP_SOFTGETXML("/tips/jzrq", sBuf)
    pstrcopy(sJzrq, sBuf, sizeof(sJzrq));

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_SOFTGETXML("/tips/TaxOrgCode", sBuf)
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxVouNo, 0x00, sizeof(sTaxVouNo));
    COMP_SOFTGETXML("/tips/TaxVouNo", sBuf)
    pstrcopy(sTaxVouNo, sBuf, sizeof(sTaxVouNo));         

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQdlb, 0x00, sizeof(sQdlb));
    COMP_SOFTGETXML("/tips/qdlb", sBuf)
    pstrcopy(sQdlb, sBuf, sizeof(sQdlb));

    if(strncmp(sQdlb,"01",2)==0)   
        prv_tips_report_wqdbodyXX=prv_tips_report_wqdbody01;
    else if(strncmp(sQdlb,"02",2)==0)
        prv_tips_report_wqdbodyXX=prv_tips_report_wqdbody02;   
    else if(strncmp(sQdlb,"03",2)==0)
        prv_tips_report_wqdbodyXX=prv_tips_report_wqdbody03;
    else if(strncmp(sQdlb,"04",2)==0)
        prv_tips_report_wqdbodyXX=prv_tips_report_wqdbody04;
    else
    {
        fpub_SetMsg(lXmlhandle, 24401, "清单类别有误");
        LOG(LM_STD,Fmtmsg("清单类别有误"),fpub_GetCompname(lXmlhandle))
        return -401;        
    }
    
    memset(sSql, 0x00, sizeof(sSql));
    if (tablekind==1)/* 查询当日流水 */
    {
        snprintf(sSql, sizeof(sSql), "select zwrq,zhqzlsh,payacct,handorgname,jyje,taxorgcode,taxvouno,jyzt,chkdate,chkacctord,jygy,xyxx,protocolno from %s where 1=1 and zwrq >= '%s' and zwrq <= '%s' and dqdh='%s' and jgdh='%s' %s ", 
            tablename, sQsrq, sJzrq, dqdh, jgdh, wherecon);        
    }else/* 批量明细 */
    {
        snprintf(sSql, sizeof(sSql), "select zwrq,plmxxh,payacct,handorgname,jyje,taxorgcode,taxvouno,czbd,chkdate,chkacctord,jygy,xyxx,protocolno from %s where 1=1 and zwrq >= '%s' and zwrq <= '%s' and dqdh='%s' and jgdh='%s' %s ", 
            tablename, sQsrq, sJzrq, dqdh, jgdh, wherecon);        
    }        

    if (strlen(sTaxOrgCode) !=0 )
    {
        snprintf(sSql+strlen(sSql), sizeof(sSql), "and taxorgcode='%s' ", sTaxOrgCode); 
    }        
    if (strlen(sTaxVouNo)!=0 )
    {
        snprintf(sSql+strlen(sSql), sizeof(sSql), "and taxvouno='%s' ", sTaxVouNo); 
    }
 	if (tablekind==1)/* 查询当日流水 */
    {
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," order by zwrq, zhqzlsh ");
 	}else/* 批量明细 */
 	{
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," order by zwrq, plmxxh "); 	    
 	}    
 	trim(sSql);
 	LOG(LM_STD,Fmtmsg("sSql[%s]",sSql),fpub_GetCompname(lXmlhandle));
 		
 		/* add dci 20141103 */
 		if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
  	{
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
  	}
  	if (DCIExecute(cur) == -1)
  	{
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        
        fpub_SetMsg(lXmlhandle,24311, "前置系统错误:打开cur_report_count游标失败");       
        LOGRET(-1,LM_STD,Fmtmsg("打开cur_report_count游标失败"),
            fpub_GetCompname(lXmlhandle))
  	}
  	
 		/* end add dci 20141103 */
 		/* mod dci 20141103
    EXEC SQL PREPARE sql_report_wqd FROM :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_report_wqd",sqlca.sqlcode),"ERROR");    
    /*declare
    EXEC SQL DECLARE cur_report_wqd CURSOR for sql_report_wqd;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_report_wqd",sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_report_wqd;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_report_wqd", sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24314, "前置系统错误,打开游标cur_report_wqd失败");       
        LOGRET(-4,LM_STD,Fmtmsg("打开cur_report_wqd游标失败"),
            fpub_GetCompname(lXmlhandle))
    }
		*/
    /*开始循环*/
    for (i=1,j=(*all),iflag=0;;i++)
    {
        memset(&stReport, 0x00, sizeof(stReport));
        /* add dci 20141103 */
        if (strcmp(tablename,"tips_drls") == 0)
        	iRet = DBFetch(cur, SD_TIPS_DRLS,NUMELE(SD_TIPS_DRLS),&stReport, sErrmsg );
        else 
					iRet = DBFetch(cur, SD_TIPS_SSPLKSFMX,NUMELE(SD_TIPS_SSPLKSFMX),&stReport, sErrmsg );
				if ( iRet < 0 )
        {  
        	iflag=-1;
        	fpub_SetMsg(lXmlhandle,24315, "前置系统错误:从cur_report_wqd游标获取数据失败");
        	LOG(LM_STD,Fmtmsg("从cur_report_wqd游标获取数据失败"),"ERROR");
        	break;
        }
        if ( iRet == 0 )
          break;
        /* end add dci 20141103 */
        
        /* mod dci 20141103 
        EXEC SQL FETCH cur_report_wqd INTO :stReport;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_report_wqd",sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	fpub_SetMsg(lXmlhandle,24315, "前置系统错误:从cur_report_wqd游标获取数据失败");
        	LOG(LM_STD,Fmtmsg("从cur_report_wqd游标获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;
        */
        
        iflag=prv_tips_report_wqdbodyXX(lXmlhandle,fp,tablekind,j+i,stReport);
        if (iflag<0)
        {
        	LOG(LM_STD,Fmtmsg("写清单文件体失败[%d]", iflag),"ERROR");
        	break;            
        }    
        (*all)++;
        (*zje) += stReport.jyje;    
    }   
    /* add dci 20141103 */
    DCIFreeCursor(cur);
    /* end add dci 20141103 */
    
    /* mod dci 20141103    
    EXEC SQL CLOSE cur_report_wqd;    */

    if (iflag < 0)
    { 
        LOGRET(-5,LM_STD,Fmtmsg("生成清单失败iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    return COMPRET_SUCC; 	
}

/* 生成往账清单 往账异常清单*/
int prv_tips_report0102(HXMLTREE lXmlhandle, 
                        FILE *fp,
                        int *i, 
                        char dqdh[], 
                        char jgdh[],
                        char jgmc[], 
                        int *all, 
                        double *zje
                        )
{   
    char sBuf[256];
    int iRet;
    int iAllCount;
    int iDrls;
    int iLsls;
    char sTableName[32];
    char sWhereCon[128];
    char sQdlb[2+1];/* 清单类别 */
    int iAllJg=0;/* 机构总笔数 */
    double dSumJg=0.00;/* 机构总金额 */
    int iTmpBs=0;/* 临时笔数 */
    double dTmpJe=0.00;/* 临时金额 */
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQdlb, 0x00, sizeof(sQdlb));
    COMP_SOFTGETXML("/tips/qdlb", sBuf)
    pstrcopy(sQdlb, sBuf, sizeof(sQdlb));    
    
    iAllCount=0;
    memset(sWhereCon, 0x00, sizeof(sWhereCon));
    if (strncmp(sQdlb, "01", 2) == 0)
    {
        strcpy(sWhereCon, " and msgno='1008' and jyzt='0' ");   
    }else
    {
        strcpy(sWhereCon, " and msgno='1008' and jyzt!='0' ");   
    }        
    
    /* 先查一下当日流水表是否有记录存在 */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_drls");
    iDrls=0;
    iDrls=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iDrls < 0 )                                    
    {
        LOGRET(iDrls,LM_STD,Fmtmsg("查询当日流水表是否有记录失败[%d]", iDrls),
            fpub_GetCompname(lXmlhandle))        
    }
    iAllCount += iDrls;
    /* 先查一下历史流水表是否有记录存在 */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_lsls");
    iLsls=0;
    iLsls=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iLsls < 0 )                                    
    {
        LOGRET(iLsls,LM_STD,Fmtmsg("查询历史流水表是否有记录失败[%d]", iLsls),
            fpub_GetCompname(lXmlhandle))        
    }    
    iAllCount += iLsls;
    /* 本机构没有可查询的记录,则直接返回成功 */
    if ( iAllCount < 1 )
    {
        /* LOG(LM_DEBUG,Fmtmsg("本机构[%s][%s]查询日期内无记录", dqdh, jgdh), fpub_GetCompname(lXmlhandle)); */
        return 0;
    }
    if (strncmp(sQdlb, "01", 2) == 0)
    {        
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(fp,"序 号 扣款日期 交易流水号      付款人账号            付款人名称              交易金额  征收机关代码       税票号码      交易状态 对账日期 对账批次 记账柜员\n");
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }else
    {
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(fp,"序 号 扣款日期 交易流水号      付款人账号            付款人名称              交易金额  征收机关代码       税票号码      交易状态 对账日期 对账批次 记账柜员  异常信息  \n");
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");        
    }    
    if ( iDrls > 0 )/* 若当日流水表有数据,则写清单 */
    {    
        memset(sTableName, 0x00, sizeof(sTableName));
        strcpy(sTableName, "tips_drls");
        iRet=prv_tips_report_wqd(lXmlhandle, 
                                 fp, 
                                 dqdh, 
                                 jgdh, 
                                 &iAllJg, 
                                 &dSumJg,
                                 1,
                                 sTableName,
                                 sWhereCon
                                 );   
        if (iRet < 0)
        { 
            LOGRET(-5,LM_STD,Fmtmsg("生成清单失败iRet=[%d]",iRet),
                fpub_GetCompname(lXmlhandle))
        }
    }

    if ( iLsls > 0 )/* 若当日流水表有数据,则写清单 */
    {    
        memset(sTableName, 0x00, sizeof(sTableName));
        strcpy(sTableName, "tips_lsls");
        iRet=prv_tips_report_wqd(lXmlhandle, 
                                 fp, 
                                 dqdh, 
                                 jgdh, 
                                 &iAllJg, 
                                 &dSumJg,
                                 1,
                                 sTableName,
                                 sWhereCon
                                 );   
        if (iRet < 0)
        { 
            LOGRET(-5,LM_STD,Fmtmsg("生成清单失败iRet=[%d]",iRet),
                fpub_GetCompname(lXmlhandle))
        }
    }
    fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(fp,"机构号：%s       合计笔数：%d       合计金额:%.2f\n\n", jgdh, iAllJg, dSumJg); 
    (*all)+= iAllJg;
    (*zje) += dSumJg;
    
    return COMPRET_SUCC;              
}

/* 生成来账清单 来账异常清单*/
int prv_tips_report0304(HXMLTREE lXmlhandle, 
                        FILE *fp,
                        int *i, 
                        char dqdh[], 
                        char jgdh[],
                        char jgmc[], 
                        int *all, 
                        double *zje
                        )
{   
    char sBuf[256];
    int iRet;
    int iAllCount;
    int iDrls;
    int iLsls;
    int iPlmx;
    int iPlls;
    char sTableName[32];
    char sWhereCon[128];
    char sQdlb[2+1];/* 清单类别 */
    int iAllJg=0;/* 机构总笔数 */
    double dSumJg=0.00;/* 机构总金额 */
    int iTmpBs=0;/* 临时笔数 */
    double dTmpJe=0.00;/* 临时金额 */
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQdlb, 0x00, sizeof(sQdlb));
    COMP_SOFTGETXML("/tips/qdlb", sBuf)
    pstrcopy(sQdlb, sBuf, sizeof(sQdlb));    
    
    iAllCount=0;
    memset(sWhereCon, 0x00, sizeof(sWhereCon));
    if (strncmp(sQdlb, "03", 2) == 0)
    {
        strcpy(sWhereCon, " and msgno='3001' and jyzt='0' ");   
    }else
    {
        strcpy(sWhereCon, " and msgno='3001' and jyzt!='0' ");   
    }        
    
    /* 查当日流水表是否有记录存在 */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_drls");
    iDrls=0;
    iDrls=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iDrls < 0 )                                    
    {
        LOGRET(iDrls,LM_STD,Fmtmsg("查询当日流水表是否有记录失败[%d]", iDrls),
            fpub_GetCompname(lXmlhandle))        
    }
    iAllCount += iDrls;
    /* 查历史流水表是否有记录存在 */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_lsls");
    iLsls=0;
    iLsls=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iLsls < 0 )                                    
    {
        LOGRET(iLsls,LM_STD,Fmtmsg("查询历史流水表是否有记录失败[%d]", iLsls),
            fpub_GetCompname(lXmlhandle))        
    }    
    iAllCount += iLsls;
    
    memset(sWhereCon, 0x00, sizeof(sWhereCon));
    if (strncmp(sQdlb, "03", 2) == 0)
    {
        strcpy(sWhereCon, " and czbd='7' ");   
    }else
    {
        strcpy(sWhereCon, " and czbd!='7' ");   
    }
    /* 查批量扣税费明细表是否有记录存在 */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_ssplksfmx");
    iPlmx=0;
    iPlmx=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iPlmx < 0 )                                    
    {
        LOGRET(iPlmx,LM_STD,Fmtmsg("查询批量扣税费明细表是否有记录失败[%d]", iPlmx),
            fpub_GetCompname(lXmlhandle))        
    }
    iAllCount += iPlmx;
    /* 查批量历史流水表是否有记录存在 */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_ssplksfmx_ls");
    iPlls=0;
    iPlls=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iLsls < 0 )                                    
    {
        LOGRET(iPlls,LM_STD,Fmtmsg("查询历史流水表是否有记录失败[%d]", iPlls),
            fpub_GetCompname(lXmlhandle))        
    }    
    iAllCount += iPlls;    
    /* 本机构没有可查询的记录,则直接返回成功 */
    if ( iAllCount < 1 )
    {
        /* LOG(LM_DEBUG,Fmtmsg("本机构[%s][%s]查询日期内无记录", dqdh, jgdh), fpub_GetCompname(lXmlhandle)); */
        return 0;
    }
    if (strncmp(sQdlb, "03", 2) == 0)
    {        
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(fp,"序 号 扣款日期 交易流水号      付款人账号            付款人名称                交易金额  征收机关代码    协议书号              税票号码      交易状态 对账日期 对账批次 \n");
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }else
    {
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(fp,"序 号 扣款日期 交易流水号      付款人账号            付款人名称                交易金额  征收机关代码    协议书号              税票号码      交易状态 对账日期 对账批次 异常信息  \n");
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");        
    }    
    
    memset(sWhereCon, 0x00, sizeof(sWhereCon));
    if (strncmp(sQdlb, "03", 2) == 0)
    {
        strcpy(sWhereCon, " and msgno='3001' and jyzt='0' ");   
    }else
    {
        strcpy(sWhereCon, " and msgno='3001' and jyzt!='0' ");   
    }
    if ( iDrls > 0 )/* 若当日流水表有数据,则写清单 */
    {    
        memset(sTableName, 0x00, sizeof(sTableName));
        strcpy(sTableName, "tips_drls");
        iRet=prv_tips_report_wqd(lXmlhandle, 
                                 fp, 
                                 dqdh, 
                                 jgdh, 
                                 &iAllJg, 
                                 &dSumJg,
                                 1,
                                 sTableName,
                                 sWhereCon
                                 );   
        if (iRet < 0)
        { 
            LOGRET(-5,LM_STD,Fmtmsg("生成清单失败iRet=[%d]",iRet),
                fpub_GetCompname(lXmlhandle))
        }
    }

    if ( iLsls > 0 )/* 若当日流水表有数据,则写清单 */
    {    
        memset(sTableName, 0x00, sizeof(sTableName));
        strcpy(sTableName, "tips_lsls");
        iRet=prv_tips_report_wqd(lXmlhandle, 
                                 fp, 
                                 dqdh, 
                                 jgdh, 
                                 &iAllJg, 
                                 &dSumJg,
                                 1,
                                 sTableName,
                                 sWhereCon
                                 );   
        if (iRet < 0)
        { 
            LOGRET(-5,LM_STD,Fmtmsg("生成清单失败iRet=[%d]",iRet),
                fpub_GetCompname(lXmlhandle))
        }
    }

    memset(sWhereCon, 0x00, sizeof(sWhereCon));
    if (strncmp(sQdlb, "03", 2) == 0)
    {
        strcpy(sWhereCon, " and czbd='7' ");   
    }else
    {
        strcpy(sWhereCon, " and czbd!='7' ");   
    }
    if ( iPlmx > 0 )/* 若批量明细表有数据,则写清单 */
    {    
        memset(sTableName, 0x00, sizeof(sTableName));
        strcpy(sTableName, "tips_ssplksfmx");
        iRet=prv_tips_report_wqd(lXmlhandle, 
                                 fp, 
                                 dqdh, 
                                 jgdh, 
                                 &iAllJg, 
                                 &dSumJg,
                                 2,
                                 sTableName,
                                 sWhereCon
                                 );   
        if (iRet < 0)
        { 
            LOGRET(-5,LM_STD,Fmtmsg("生成清单失败iRet=[%d]",iRet),
                fpub_GetCompname(lXmlhandle))
        }
    }

    if ( iPlls > 0 )/* 若批量明细历史表有数据,则写清单 */
    {    
        memset(sTableName, 0x00, sizeof(sTableName));
        strcpy(sTableName, "tips_ssplksfmx_ls");
        iRet=prv_tips_report_wqd(lXmlhandle, 
                                 fp, 
                                 dqdh, 
                                 jgdh, 
                                 &iAllJg, 
                                 &dSumJg,
                                 2,
                                 sTableName,
                                 sWhereCon
                                 );   
        if (iRet < 0)
        { 
            LOGRET(-5,LM_STD,Fmtmsg("生成清单失败iRet=[%d]",iRet),
                fpub_GetCompname(lXmlhandle))
        }
    }

    fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(fp,"机构号：%s       合计笔数：%d       合计金额:%.2f\n\n", jgdh, iAllJg, dSumJg); 
    (*all)+= iAllJg;
    (*zje) += dSumJg;
    
    return COMPRET_SUCC;              
}

/* 生成业务量统计清单*/
int prv_tips_report05(HXMLTREE lXmlhandle, 
                        FILE *fp,
                        int *i, 
                        char dqdh[], 
                        char jgdh[],
                        char jgmc[],                         
                        int *all, 
                        double *zje
                        )
{   
    char sBuf[256];
    char sTableName[32];
    char sWhereCon[128];
    int iRet;
    int iDrskbs=0;/* 当日实扣笔数 */
    double dDrskje=0.00;/* 当日实扣金额 */
    int iLsskbs=0;/* 历史实扣笔数 */
    double dLsskje=0.00;/* 历史实扣金额 */
    int iSkbs=0;/* 实扣笔数 */
    double dSkje=0.00;/* 实扣金额 */
    int iDrpkbs=0;/* 当日批扣笔数 */
    double dDrpkje=0.00;/* 当日批扣金额 */
    int iLspkbs=0;/* 历史批扣笔数 */
    double dLspkje=0.00;/* 历史批扣金额 */
    int iPkbs=0;/* 批扣笔数 */
    double dPkje=0.00;/* 批扣金额 */
    int iDryjsbbs=0;/* 当日银缴申报笔数 */
    double dDryjsbje=0.00;/* 当日银缴申报金额 */
    int iLsyjsbbs=0;/* 历史银缴申报笔数 */
    double dLsyjsbje=0.00;/* 历史银缴申报笔数 */
    int iYjsbbs=0;/* 银缴申报笔数 */
    double dYjsbje=0.00;/* 银缴申报金额 */
    int iDryjjkbs=0;/* 当日银缴缴款笔数 */
    double dDryjjkje=0.00;/* 当日银缴缴款金额 */
    int iLsyjjkbs=0;/* 历史银缴缴款笔数 */
    double dLsyjjkje=0.00;/* 历史银缴缴款金额 */
    int iYjjkbs=0;/* 银缴缴款笔数 */
    double dYjjkje=0.00;/* 银缴缴款金额 */
    int iAllJg=0;/* 机构总笔数 */
    double dSumJg=0.00;/* 机构总金额 */
    int iTmpbs=0;/* 临时笔数 */
    double dTmpje=0.00;/* 临时金额 */
    
    fpub_InitSoComp(lXmlhandle); 

    iAllJg=0;
    dSumJg=0.00;
    
    iSkbs=0;
    dSkje=0.00;           
    memset(sWhereCon, 0x00, sizeof(sWhereCon));
    strcpy(sWhereCon, " and msgno='3001' "); 
    /* 1.查询当日流水表的实扣笔数及金额 */  
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_drls");
    iDrskbs=0;
    dDrskje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iDrskbs,&dDrskje);
    if ( iRet < 0 )                   
    {
        LOGRET(iRet,LM_STD,Fmtmsg("查询当日流水表的实扣笔数及金额失败[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }
    iSkbs += iDrskbs;
    dSkje += dDrskje;
    /* 2.查询历史流水表的实扣笔数及金额 */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_lsls");
    iLsskbs=0;
    dLsskje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iLsskbs,&dLsskje);
    if ( iRet < 0 )                                    
    {
        LOGRET(iRet,LM_STD,Fmtmsg("查询历史流水表的实扣笔数及金额失败[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }    
    iSkbs += iLsskbs;
    dSkje += dLsskje;
    iAllJg += iSkbs;
    dSumJg += dSkje;

    iPkbs=0;
    dPkje=0.00;
    memset(sWhereCon, 0x00, sizeof(sWhereCon));
    /* 3.查询当日批扣笔数及金额 */  
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_ssplksfmx");
    iDrpkbs=0;
    dDrpkje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iDrpkbs,&dDrpkje);
    if ( iRet < 0 )                   
    {
        LOGRET(iRet,LM_STD,Fmtmsg("查询当日批扣笔数及金额失败[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }
    iPkbs += iDrpkbs;
    dPkje += dDrpkje;
    /* 4.查询历史批扣笔数及金额 */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_ssplksfmx_ls");
    iLspkbs=0;
    dLspkje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iLspkbs,&dLspkje);
    if ( iRet < 0 )                                    
    {
        LOGRET(iRet,LM_STD,Fmtmsg("查询历史批扣笔数及金额失败[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }    
    iPkbs += iLspkbs;
    dPkje += dLspkje;
    iAllJg += iPkbs;
    dSumJg += dPkje;

    iYjsbbs=0;
    dYjsbje=0.00;
    memset(sWhereCon, 0x00, sizeof(sWhereCon));
    strcpy(sWhereCon, " and msgno='1008' "); 
    /* 5.查询当日流水表的银缴申报笔数及金额 */  
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_drls");
    iDryjsbbs=0;
    dDryjsbje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iDryjsbbs,&dDryjsbje);
    if ( iRet < 0 )                   
    {
        LOGRET(iRet,LM_STD,Fmtmsg("查询当日流水表的银缴申报笔数及金额失败[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }
    iYjsbbs += iDryjsbbs;
    dYjsbje += dDryjsbje;
    /* 6.查询历史流水表的银缴申报笔数及金额 */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_lsls");
    iLsyjsbbs=0;
    dLsyjsbje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iLsyjsbbs,&dLsyjsbje);
    if ( iRet < 0 )                                    
    {
        LOGRET(iRet,LM_STD,Fmtmsg("查询历史流水表的银缴申报笔数及金额失败[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }    
    iYjsbbs += iLsyjsbbs;
    dYjsbje += dLsyjsbje;    
    iAllJg += iYjsbbs;
    dSumJg += dYjsbje;
    
    iYjjkbs=0;
    dYjjkje=0.00;
    memset(sWhereCon, 0x00, sizeof(sWhereCon));
    strcpy(sWhereCon, " and msgno='1008' and jyzt='0' "); 
    /* 7.查询当日流水表的银缴缴款笔数及金额 */  
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_drls");
    iDryjjkbs=0;
    dDryjjkje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iDryjjkbs,&dDryjjkje);
    if ( iRet < 0 )                   
    {
        LOGRET(iRet,LM_STD,Fmtmsg("查询当日流水表的银缴缴款笔数及金额失败[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }
    iYjjkbs += iDryjjkbs;
    dYjjkje += dDryjjkje;
    /* 6.查询历史流水表的银缴缴款笔数及金额 */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_lsls");
    iLsyjjkbs=0;
    dLsyjjkje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iLsyjjkbs,&dLsyjjkje);
    if ( iRet < 0 )                                    
    {
        LOGRET(iRet,LM_STD,Fmtmsg("查询历史流水表的银缴缴款笔数及金额失败[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }    
    iYjjkbs += iLsyjjkbs;
    dYjjkje += dLsyjjkje; 
    iAllJg += iYjjkbs;
    dSumJg += dYjjkje;
    
    /* 本机构没有可查询的记录,则直接返回成功 */
    if ( iAllJg < 1 )
    {
        /* LOG(LM_DEBUG,Fmtmsg("本机构[%s][%s]查询日期内无记录", dqdh, jgdh), fpub_GetCompname(lXmlhandle)); */
        return 0;
    }   
    fprintf(fp,"%5d %-10.10s  %-16.16s  %5d %15.2f %5d %15.2f %5d %15.2f %5d %15.2f %5d %15.2f\n",
            (*i)+1, jgdh, jgmc, iSkbs, dSkje, iPkbs, dPkje, iYjsbbs, dYjsbje, iYjjkbs, dYjjkje, iAllJg, dSumJg );               
    (*i)++;
    /* 输出统计笔数及金额 */
    /* 1.实扣笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/skbs", sBuf)
    iTmpbs= atoi(sBuf) + iSkbs;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%d", iTmpbs);
    COMP_SOFTSETXML("/tips/skbs", sBuf)
    /* 2.实扣金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/skje", sBuf)
    dTmpje = atof(sBuf) + dSkje;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%.2f", dTmpje);
    COMP_SOFTSETXML("/tips/skje", sBuf)
    /* 3.批扣笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/pkbs", sBuf)
    iTmpbs = atoi(sBuf) + iPkbs;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%d", iTmpbs);
    COMP_SOFTSETXML("/tips/pkbs", sBuf)
    /* 4.批扣金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/pkje", sBuf)
    dTmpje = atof(sBuf) + dPkje;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%.2f", dTmpje);
    COMP_SOFTSETXML("/tips/pkje", sBuf)
    /* 5.银缴申报笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjsbbs", sBuf)
    iTmpbs = atoi(sBuf) + iYjsbbs;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%d", iTmpbs);
    COMP_SOFTSETXML("/tips/yjsbbs", sBuf)
    /* 6.银缴申报金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjsbje", sBuf)
    dTmpje = atof(sBuf) + dYjsbje;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%.2f", dTmpje);
    COMP_SOFTSETXML("/tips/yjsbje", sBuf)
    /* 7.银缴缴款笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjjkbs", sBuf)
    iTmpbs = atoi(sBuf) + iYjjkbs;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%d", iTmpbs);
    COMP_SOFTSETXML("/tips/yjjkbs", sBuf)
    /* 8.银缴缴款金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjjkje", sBuf)
    dTmpje = atof(sBuf) + dYjjkje;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%.2f", dTmpje);
    COMP_SOFTSETXML("/tips/yjjkje", sBuf)            
    (*all)+= iAllJg;
    (*zje) += dSumJg;
    
    return COMPRET_SUCC;              
}

/* 生成各类清单(提取符合条件的机构) */
int prv_tips_report(HXMLTREE lXmlhandle, FILE *fp, int *all, double *zje, char qdlb[])
{
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sDqdh[10+1];
         char sJgdh[10+1];
         char sFJgdh[10+1];
         char sCodeName[40+1];
         char sInnerOrgID[27+1];
         char sJgmc[20+1];
    /*EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    char sJgdh1[10+1];
    char sDqdh1[10+1];
    char sPrvName[64];
    char sJgmc1[20+1];
    int i, iflag;
    int j=0;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		CURSOR cur;
		/* end add dci 20141103 */	
		        
    if(   strncmp(qdlb,"01",2)==0 
       || strncmp(qdlb,"02",2)==0 
      )   
        prv_tips_reportXX=prv_tips_report0102;
    else  if(   strncmp(qdlb,"03",2)==0 
               || strncmp(qdlb,"04",2)==0 
               )
         prv_tips_reportXX=prv_tips_report0304;
    else if(strncmp(qdlb,"05",2)==0)
    {    
         prv_tips_reportXX=prv_tips_report05;
    }else
    {
        fpub_SetMsg(lXmlhandle, 24401, "清单类别有误");
        LOG(LM_STD,Fmtmsg("清单类别有误"),fpub_GetCompname(lXmlhandle))
        return -401;        
    }        
            
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDqdh, 0x00, sizeof(sDqdh));
    COMP_SOFTGETXML("/tips/dqdh", sBuf)
    pstrcopy(sDqdh, sBuf, sizeof(sDqdh));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJgdh1, 0x00, sizeof(sJgdh1));
    COMP_SOFTGETXML("/tips/jgdh", sBuf)
    pstrcopy(sJgdh1, sBuf, sizeof(sJgdh1));
        
    memset(sCodeName, 0x00, sizeof(sCodeName));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select code_name from tips_codemean where code_name='tipszhdqbsm'");     	
    iRet = DBSelectToVar(sErrmsg, &sCodeName, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24402, "查询TIPS数据字典失败");
        LOG(LM_STD,Fmtmsg("查询TIPS数据字典失败"),fpub_GetCompname(lXmlhandle))
        return -402;      
    }

    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT code_name INTO :sCodeName
         FROM tips_codemean
         WHERE code_name='tipszhdqbsm';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24402, "查询TIPS数据字典失败");
        LOG(LM_STD,Fmtmsg("查询TIPS数据字典失败"),fpub_GetCompname(lXmlhandle))
        return -402;
    }
    */
    
    /* 若是总分行按地区来划分,则地区代号与机构代号放在一起 */
    memset(sJgdh, 0x00, sizeof(sJgdh));
    /* add dci 20141103 */
    if ( iRet == 0 )
    {
        snprintf(sJgdh, sizeof(sJgdh), "%s", sJgdh1);
    }else
    {
        snprintf(sJgdh, sizeof(sJgdh), "%s%s", sDqdh, sJgdh1);
    }  
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    if ( SQLNOTFOUND )
    {
        snprintf(sJgdh, sizeof(sJgdh), "%s", sJgdh1);
    }else
    {
        snprintf(sJgdh, sizeof(sJgdh), "%s%s", sDqdh, sJgdh1);
    }  
    */               
    memset(sJgdh1, 0x00, sizeof(sJgdh1));
    pstrcopy(sJgdh1, sJgdh, sizeof(sJgdh1));

    memset(sInnerOrgID, 0x00, sizeof(sInnerOrgID));
    if(strlen(sJgdh)!=0)
    {
    		/* add dci 20141103 */
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select inner_org_id from t_org where org_id='%s'",sJgdh);     	
    		iRet = DBSelectToVar(sErrmsg, &sInnerOrgID, sSql1);
    		/* end add dci 20141103 */
    		
    		/* mod dci 20141103 
        EXEC SQL SELECT inner_org_id INTO :sInnerOrgID
             FROM t_org
             WHERE org_id=:sJgdh;
        */        
    }else
    {
    		/* add dci 20141103 */
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select inner_org_id,org_id from t_org where above_org_id='%s'",sJgdh);     	
    		iRet = DBSelectToMultiVar(sErrmsg, sInnerOrgID,sJgdh, sSql1);
    		/* end add dci 20141103 */
    		
        /* mod dci 20141103
        EXEC SQL SELECT inner_org_id,org_id INTO :sInnerOrgID, :sJgdh
             FROM t_org
             WHERE above_org_id='/'; 
        */       
    }
    /* add dci 20141103 */
    if ( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle,24403, "查询机构表失败");
        LOG(LM_STD,Fmtmsg("查询机构表失败"),"ERROR");
        return -403;
    }    
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24404, "本机构未初始化");
        LOG(LM_STD,Fmtmsg("本机构[%s]未初始化", sJgdh),fpub_GetCompname(lXmlhandle))
        return -404;
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24403, "查询机构表失败");
        LOG(LM_STD,Fmtmsg("查询机构表失败"),"ERROR");
        return -403;
    }    
    if ( SQLNOTFOUND )
    {
        fpub_SetMsg(lXmlhandle, 24404, "本机构未初始化");
        LOG(LM_STD,Fmtmsg("本机构[%s]未初始化", sJgdh),fpub_GetCompname(lXmlhandle))
        return -404;
    }
    */
    
    trim(sInnerOrgID);
    if(strlen(sInnerOrgID) < 27)
    {
       sInnerOrgID[strlen(sInnerOrgID)]='%'; 
    }
    trim(sInnerOrgID);    
		
		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT org_id, org_name FROM  t_org "
    	"WHERE inner_org_id like '%s' ORDER BY org_id",sInnerOrgID); 
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,36001, "打开游标失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ打开cur_ksfmx_plhz游标失败"),
            fpub_GetCompname(lXmlhandle))
    }

		/* end add dci 20141103 */
		
		/* mod dci 20141103 
    EXEC SQL DECLARE cur_report CURSOR for 
        SELECT org_id, org_name FROM  t_org 
        WHERE  inner_org_id like :sInnerOrgID
         ORDER BY org_id;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_report;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_report",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24405, "打开游标cur_report失败");
        LOG(LM_STD,Fmtmsg("打开cur_report游标失败"),"ERROR");
        return -405;
    }    
		*/
		
    /*开始循环*/
    for (i=1,iflag=0;;i++)
    {
        memset(sFJgdh, 0x00, sizeof(sFJgdh));
        memset(sJgmc, 0x00, sizeof(sJgmc));
        
        /* add dci 20141103 */
        iRet = DCIFetch(cur);
				if ( iRet < 0 )
        {  
        	iflag=-406;
        	fpub_SetMsg(lXmlhandle,24406, "从cur_report获取数据失败");
        	LOG(LM_STD,Fmtmsg("从cur_report获取数据失败"),"ERROR");
        	break;
        }
        if ( iRet == 0 )
          break;
        
        strncpy( sFJgdh, DCIFieldAsString(cur, 0 ), sizeof( sFJgdh ) );
        strncpy( sJgmc, DCIFieldAsString(cur, 1 ), sizeof( sJgmc ) );

        /* end add dci 20141103 */
        
        /* mod dci 20141103 
        EXEC SQL FETCH cur_report INTO :sFJgdh, :sJgmc;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_report", sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-406;
        	fpub_SetMsg(lXmlhandle,24406, "从cur_report获取数据失败");
        	LOG(LM_STD,Fmtmsg("从cur_report获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;
        */
          
        trim(sFJgdh);
        trim(sJgmc);
        memset(sDqdh1, 0x00, sizeof(sDqdh1));
        pstrcopy(sDqdh1, sFJgdh, sizeof(sDqdh1));
        memset(sJgmc1, 0x00, sizeof(sJgmc1));
        pstrcopy(sJgmc1, sJgmc, sizeof(sJgmc1));
        iflag=-1;
        iflag=prv_tips_reportXX(lXmlhandle, fp, &j, sDqdh1, sFJgdh, sJgmc1, all, zje); 
        if( iflag < 0 )
        {
            LOG(LM_STD,Fmtmsg("生成清单失败iflag=[%d]",iflag),"ERROR");
            break;
        }	
    }	
    /* add dci 20141103 */
    DCIFreeCursor(cur);
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL CLOSE cur_report; */
     
    if (iflag < 0)
    {
        LOG(LM_STD,Fmtmsg("生成清单失败iflag=[%d]",iflag),"ERROR");
        return iflag;
    }    
    return 0;            
}

/* 生成业务量统计清单 */
int prv_tips_reportywl(HXMLTREE lXmlhandle, FILE *fp, int *all, double *zje, char qdlb[])
{
    char sBuf[256];
    int iRet;
    int iSkbs=0;/* 实扣笔数 */
    double dSkje=0.00;/* 实扣金额 */
    int iPkbs=0;/* 批扣笔数 */
    double dPkje=0.00;/* 批扣金额 */
    int iYjsbbs=0;/* 银缴缴款笔数 */
    double dYjsbje=0.00;/* 银缴缴款金额 */
    int iYjjkbs=0;/* 银缴缴款笔数 */
    double dYjjkje=0.00;/* 银缴缴款金额 */

    fprintf(fp,"                                         实时扣税               批量扣税                         银行端缴税                       合计\n"); 
    fprintf(fp," 序号 机构号      机构名称            笔数         金额      笔数          金额 申报笔数     申报金额 银缴笔数    银缴金额     笔数       金额\n"); 
    COMP_SOFTSETXML("/tips/skbs","0")
    COMP_SOFTSETXML("/tips/skje","0.00")
    COMP_SOFTSETXML("/tips/pkbs","0")
    COMP_SOFTSETXML("/tips/pkje","0.00")
    COMP_SOFTSETXML("/tips/yjsbbs","0")
    COMP_SOFTSETXML("/tips/yjsbje","0.00")
    COMP_SOFTSETXML("/tips/yjjkbs","0")
    COMP_SOFTSETXML("/tips/yjjkje","0.00")
    iRet = prv_tips_report(lXmlhandle, fp, all, zje, qdlb);          
    if ( iRet < 0 )
    {
         LOGRET(iRet,LM_STD,Fmtmsg("生成清单失败[%d]", iRet), fpub_GetCompname(lXmlhandle))        
    }
    /* 1.实扣笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/skbs", sBuf)
    iSkbs=atoi(sBuf);
    /* 2.实扣金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/skje", sBuf)
    dSkje=atof(sBuf);
    /* 3.批扣笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/pkbs", sBuf)
    iPkbs=atoi(sBuf);
    /* 4.批扣金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/pkje", sBuf)
    dPkje=atof(sBuf);
    /* 5.银缴申报笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjsbbs", sBuf)
    iYjsbbs=atoi(sBuf);
    /* 6.银缴申报金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjsbje", sBuf)
    dYjsbje=atof(sBuf);
    /* 7.银缴缴款笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjjkbs", sBuf)
    iYjjkbs=atoi(sBuf);
    /* 8.银缴缴款金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjjkje", sBuf)
    dYjjkje=atof(sBuf);
    fprintf(fp,"-------------------------------------------------------------------------------------------------------------------------------------------------\n");    
    fprintf(fp,"合计：                              %5d %15.2f %5d %15.2f %5d %15.2f %5d %15.2f %5d %15.2f\n",
            iSkbs, dSkje, iPkbs, dPkje, iYjsbbs, dYjsbje, iYjjkbs, dYjjkje, (*all), (*zje));               
    return 0;    
}

/* 生成对账表 */
int prv_tips_reportdzb(HXMLTREE lXmlhandle, FILE *fp, int *all, double *zje, char qdlb[])
{
    /*EXEC SQL BEGIN DECLARE SECTION;*/
        char sSql[1024];
        char sPayeeBankNo[12+1];/* 收款行行号 */
        char sChkDate[8+1];/* 对账日期 */
        char sChkAcctOrd[4+1];/* 对账批次 */
        char sChkAcctType[1+1];/* 对账类型 */
        int iZbs;/* 总笔数 */
        double dZje;/* 总金额 */
        char sQsbz[1+1];/* 清算标志 */
        char sZjlsh[32+1];/* 主机流水号 */
        char sZjrq[8+1];/* 主机日期 */
        char sCnChkAcctType[60+1];/* 对账类型中文 */
        char sCnQsbz[60+1];/* 清算类型中文 */
    /*EXEC SQL END DECLARE SECTION;*/
    char sQsrq[8+1];/* 起始日期 */
    char sJzrq[8+1];/* 截止日期 */
    char sBuf[256];
    int iflag,i,j;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		CURSOR cur;
		/* end add dci 20141103 */	

    fprintf(fp," 序号  收款行行号   对账日期 对账批次 对账类型   总笔数          总金额 清算标志  支付交易序号  支付委托日期\n"); 
     
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsrq, 0x00, sizeof(sQsrq));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(sQsrq, sBuf, sizeof(sQsrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJzrq, 0x00, sizeof(sJzrq));
    COMP_SOFTGETXML("/tips/jzrq", sBuf)
    pstrcopy(sJzrq, sBuf, sizeof(sJzrq));

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
    COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
    pstrcopy(sPayeeBankNo, sBuf, sizeof(sPayeeBankNo));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
    COMP_SOFTGETXML("/tips/ChkAcctOrd", sBuf)
    pstrcopy(sChkAcctOrd, sBuf, sizeof(sChkAcctOrd));

    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "select payeebankno,chkdate,chkacctord,chkaccttype,jybs,jyje,qsbz,zjlsh,zjrq from tips_sszjhhls where 1=1 and chkdate >= '%s' and chkdate <= '%s'  ", sQsrq, sJzrq);       

    if (strlen(sPayeeBankNo) !=0 )
    {
        snprintf(sSql+strlen(sSql), sizeof(sSql), " and payeebankno='%s' ", sPayeeBankNo); 
    }        
    if (strlen(sChkAcctOrd)!=0 )
    {
        snprintf(sSql+strlen(sSql), sizeof(sSql), " and chkacctord='%s' ", sChkAcctOrd); 
    }
    snprintf(sSql+strlen(sSql),sizeof(sSql)," order by payeebankno, chkdate, chkacctord ");

 	trim(sSql);
 	LOG(LM_STD,Fmtmsg("sSql[%s]",sSql),fpub_GetCompname(lXmlhandle));
 	
 		/* add dci 20141103 */
 		if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
  	{
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
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
 		/* end add dci 20141103 */
 		
 		/* mod dci 20141103
    EXEC SQL PREPARE sql_report_dzb FROM :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_report_dzb",sqlca.sqlcode),"ERROR");    
    /*declare
    EXEC SQL DECLARE cur_report_dzb CURSOR for sql_report_dzb;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_report_dzb",sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_report_dzb;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_report_dzb", sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24314, "前置系统错误,打开游标cur_report_dzb失败");       
        LOGRET(-4,LM_STD,Fmtmsg("打开cur_report_dzb游标失败"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*开始循环*/
    for (i=1,iflag=0;;i++)
    {
        memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
        memset(sChkDate, 0x00, sizeof(sChkDate));
        memset(sChkAcctOrd, 0x00, sizeof(sChkAcctOrd));
        memset(sChkAcctType, 0x00, sizeof(sChkAcctType));
        iZbs=0;
        dZje=0.00;
        memset(sQsbz, 0x00, sizeof(sQsbz));
        memset(sZjlsh, 0x00, sizeof(sZjlsh));
        memset(sZjrq, 0x00, sizeof(sZjrq));
        
        /* add dci 20141103 */
        iRet = DCIFetch(cur);
				if ( iRet < 0 )
        {  
        	iflag=-1;
        	fpub_SetMsg(lXmlhandle,24315, "前置系统错误:从cur_report_dzb游标获取数据失败");
        	LOG(LM_STD,Fmtmsg("从cur_report_dzb游标获取数据失败"),"ERROR");
        	break;
        }
        if ( iRet ==0 )
          break;
        
        strncpy( sPayeeBankNo, DCIFieldAsString(cur, 0 ), sizeof( sPayeeBankNo ) );
				strncpy( sChkDate, DCIFieldAsString(cur, 1 ), sizeof( sChkDate ) );
				strncpy( sChkAcctOrd, DCIFieldAsString(cur, 2 ), sizeof( sChkAcctOrd ) );
				strncpy( sChkAcctType, DCIFieldAsString(cur, 3 ), sizeof( sChkAcctType ) );

        /* end add dci 20141103 */
        
        /* mod dci 20141103
        EXEC SQL FETCH cur_report_dzb INTO :sPayeeBankNo, :sChkDate, :sChkAcctOrd, :sChkAcctType, :iZbs, :dZje, :sQsbz, :sZjlsh, :sZjrq;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_report_dzb",sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	fpub_SetMsg(lXmlhandle,24315, "前置系统错误:从cur_report_dzb游标获取数据失败");
        	LOG(LM_STD,Fmtmsg("从cur_report_dzb游标获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;
          
        */
        
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select num_desc from tips_codelist \
    			where code_name='tipstbdzlx' and num='%s'",sChkAcctType);     	
    		iRet = DBSelectToVar(sErrmsg, &sCnChkAcctType, sSql1);
				if ( iRet < 0 )
        {
        	iflag=-2;
        	fpub_SetMsg(lXmlhandle,24316, "查询数据字典数据对账类型失败");
        	LOG(LM_STD,Fmtmsg("查询数据字典数据对账类型失败"),"ERROR");
            break;
        }
        /* end add dci 20141103 */
                
        /* mod dci 20141103
        memset(sCnChkAcctType, 0x00, sizeof(sCnChkAcctType));
        EXEC SQL SELECT num_desc INTO :sCnChkAcctType
             FROM tips_codelist
             WHERE code_name='tipstbdzlx'
               AND num=:sChkAcctType;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {
        	iflag=-2;
        	fpub_SetMsg(lXmlhandle,24316, "查询数据字典数据对账类型失败");
        	LOG(LM_STD,Fmtmsg("查询数据字典数据对账类型失败"),"ERROR");
            break;
        }
        */
        
        trim(sCnChkAcctType);
        memset(sCnQsbz, 0x00, sizeof(sCnQsbz));
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select num_desc from tips_codelist \
    			where code_name='tipsqsbz' and num='%s'",sQsbz);     	
    		iRet = DBSelectToVar(sErrmsg, &sCnChkAcctType, sSql1);
				if ( iRet < 0 )
        {
        	iflag=-3;
        	fpub_SetMsg(lXmlhandle,24317, "查询数据字典数据清算标志失败");
        	LOG(LM_STD,Fmtmsg("查询数据字典数据清算标志失败"),"ERROR");
            break;
        }
        /* end add dci 20141103 */
        
        /* mod dci 20141103 
        EXEC SQL SELECT num_desc INTO :sCnQsbz
             FROM tips_codelist
             WHERE code_name='tipsqsbz'
               AND num=:sQsbz;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {
        	iflag=-3;
        	fpub_SetMsg(lXmlhandle,24317, "查询数据字典数据清算标志失败");
        	LOG(LM_STD,Fmtmsg("查询数据字典数据清算标志失败"),"ERROR");
            break;
        }
        */
        
        trim(sCnQsbz);            
        fprintf(fp,"%05d  %12.12s %8.8s %4.4s     %4.4s     %8d %15.2f %6.6s         %8.8s %8.8s\n",
            i, sPayeeBankNo, sChkDate, sChkAcctOrd, sCnChkAcctType, iZbs, dZje, sCnQsbz, sZjlsh, sZjrq);    
        (*all) += iZbs;
        (*zje) += dZje;    
     }
     /* add dci 20141103 */
     DCIFreeCursor(cur);
     /* end add dci 20141103 */
     
     /* mod dci 20141103     
    EXEC SQL CLOSE cur_report_dzb;    */

    if (iflag < 0)
    { 
        LOGRET(-5,LM_STD,Fmtmsg("生成清单失败iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    
    fprintf(fp,"------------------------------------------------------------------------------------------------------------\n");           
    return COMPRET_SUCC;    
}

/* 生成资金清算汇总 */
int prv_tips_reportzjqshz(HXMLTREE lXmlhandle, FILE *fp, int *all, double *zje, char qdlb[])
{
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         int iZpc0=0;/* 日间总批次 */
         int iZbs0=0;/* 日间总笔数 */
         double dZje0=0.00;/* 日间总金额 */
         int iQsbs0=0;/* 日间清算笔数 */
         double dQsje0=0.00;/* 日间清算金额 */
         int iFQsbs0=0;/* 日间未清算笔数 */
         double dFQsje0=0.00;/* 日间未清算金额 */
         int iZpc1=0;/* 日切总批次 */
         int iZbs1=0;/* 日切总笔数 */
         double dZje1=0.00;/* 日切总金额 */
         int iQsbs1=0;/* 日切清算笔数 */
         double dQsje1=0.00;/* 日切清算金额 */
         int iFQsbs1=0;/* 日切未清算笔数 */
         double dFQsje1=0.00;/* 日切未清算金额 */
         char sChkDate[8+1];/* 对账日期 */
         char sChkDate2[8+1];/* 对账日期 */
    /*EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    int iRet;
    
    char cZbs0[8+1];/* 日间总笔数 */
    char cZje0[32+1];/* 日间总金额 */
    char cQsbs0[8+1];/* 日间清算笔数 */
    char cQsje0[32+1];/* 日间清算金额 */
    char cFQsbs0[8+1];/*日间未清算笔数 */
    char cFQsje0[32+1];/* 日间未清算金额 */
    
    char cZbs1[8+1];/*日切总笔数 */
    char cZje1[32+1];/* 日切总金额 */
    char cQsbs1[8+1];/*日切清算笔数 */
    char cQsje1[32+1];/* 日切清算金额 */
    char cFQsbs1[8+1];/*日切未清算笔数 */
    char cFQsje1[32+1];/* 日切未清算金额 */  
    
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		CURSOR cur;

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sChkDate, 0x00, sizeof(sChkDate));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(sChkDate, sBuf, sizeof(sChkDate));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sChkDate2, 0x00, sizeof(sChkDate2));
    COMP_SOFTGETXML("/tips/jzrq", sBuf)
    pstrcopy(sChkDate2, sBuf, sizeof(sChkDate2));

    LOG(LM_STD,Fmtmsg("生成资金清算汇总开始处理 查询日期[%s]--[%s]", 
        sChkDate, sChkDate2),fpub_GetCompname(lXmlhandle)) 
    
    fprintf(fp,"对账类型 总批次   总笔数          总金额 清算笔数        清算金额 未清算笔数      未清算金额\n"); 

    /* 查询日间总批次 */
    iZpc0=0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_sszjhhls \
    	 where chkdate <= '%s' AND chkdate >= '%s' AND chkaccttype = '0'",sChkDate2,sChkDate);     	
    iRet = DBSelectToVar(sErrmsg, &iZpc0, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("查询日间总批次出错"));
        LOG(LM_STD,Fmtmsg("查询日间总批次出错"),fpub_GetCompname(lXmlhandle)) 
        return -71;     
    }

    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT NVL(COUNT(*),0) INTO :iZpc0
         FROM tips_sszjhhls 
         WHERE chkdate <= :sChkDate2
           AND chkdate >= :sChkDate
           AND chkaccttype = '0';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("查询日间总批次出错"));
        LOG(LM_STD,Fmtmsg("查询日间总批次出错"),fpub_GetCompname(lXmlhandle)) 
        return -71;
    }
    */
    /* 查询日间总笔数,总金额 */
    iZbs0=0;
    dZje0=0.00;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select SUM(jybs),SUM(jyje) from tips_sszjhhls \
    	 where chkdate <= '%s' AND chkdate >= '%s' AND chkaccttype = '0'",sChkDate2,sChkDate);     	
    /*iRet =  DBSelectToMultiVar(sErrmsg, sSql1,&iZbs0, &dZje0);*/
    iRet =  DBSelectToMultiVarChar(sErrmsg, sSql1,&cZbs0, &cZje0);
    		
		iZbs0=atoi(cZbs0);
		dZje0=atof(cZje0);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24272, Fmtmsg("查询日间总笔数总金额出错"));
        LOG(LM_STD,Fmtmsg("查询日间总笔数总金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -72;
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT NVL(SUM(jybs),0), NVL(SUM(jyje), 0.00) INTO :iZbs0, :dZje0
         FROM tips_sszjhhls 
         WHERE chkdate <= :sChkDate2
           AND chkdate >= :sChkDate
           AND chkaccttype = '0';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24272, Fmtmsg("查询日间总笔数总金额出错"));
        LOG(LM_STD,Fmtmsg("查询日间总笔数总金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -72;
    }
    */
    /* 查询日间清算笔数,清算金额 */
    iQsbs0=0;
    dQsje0=0.00;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select SUM(jybs),SUM(jyje) from tips_sszjhhls \
    	 where chkdate <= '%s' AND chkdate >= '%s' AND chkaccttype = '0' AND dzbz = '1' AND qsbz = '1'",sChkDate2,sChkDate);     	
    /*iRet =  DBSelectToMultiVar(sErrmsg, sSql1,&iQsbs0, &dQsje0);*/
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cQsbs0, &cQsje0);
    		
		iQsbs0=atoi(cQsbs0);
		dQsje0=atof(cQsje0);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24273, Fmtmsg("查询日间清算笔数、清算金额出错"));
        LOG(LM_STD,Fmtmsg("查询日间清算笔数、清算金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -73;
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT NVL(SUM(jybs),0), NVL(SUM(jyje), 0.00) INTO :iQsbs0, :dQsje0
         FROM tips_sszjhhls 
         WHERE chkdate <= :sChkDate2
           AND chkdate >= :sChkDate
           AND chkaccttype = '0'
           AND dzbz = '1'
           AND qsbz = '1';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24273, Fmtmsg("查询日间清算笔数、清算金额出错"));
        LOG(LM_STD,Fmtmsg("查询日间清算笔数、清算金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -73;
    }
    */                   

    /* 查询日间未清算笔数,未清算金额 */
    iFQsbs0=0;
    dFQsje0=0.00;
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select SUM(jybs),SUM(jyje) from tips_sszjhhls \
    	 where chkdate <= '%s' AND chkdate >= '%s' AND chkaccttype = '0' AND dzbz <> '1' AND qsbz <> '1'",sChkDate2,sChkDate);     	
    /*iRet =  DBSelectToMultiVar(sErrmsg, sSql1,&iFQsbs0, &dFQsje0);*/
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cFQsbs0, &cFQsje0);
    		
		iFQsbs0=atoi(cFQsbs0);
		dFQsje0=atof(cFQsje0);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24274, Fmtmsg("查询日间未清算笔数、未清算金额出错"));
        LOG(LM_STD,Fmtmsg("查询日间未清算笔数、未清算金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -74;
    }
    /* end add dci 20141103 */ 
    /* mod dci 20141103
    EXEC SQL SELECT NVL(SUM(jybs),0), NVL(SUM(jyje), 0.00) INTO :iFQsbs0, :dFQsje0
         FROM tips_sszjhhls 
         WHERE chkdate <= :sChkDate2
           AND chkdate >= :sChkDate
           AND chkaccttype = '0'
           AND dzbz <> '1'
           AND qsbz <> '1';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24274, Fmtmsg("查询日间未清算笔数、未清算金额出错"));
        LOG(LM_STD,Fmtmsg("查询日间未清算笔数、未清算金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -74;
    }
    */

    fprintf(fp,"日间 %8d   %8d %15.2f %8d %15.2f   %8d %15.2f\n",
            iZpc0, iZbs0, dZje0, iQsbs0, dQsje0, iFQsbs0, dFQsje0);

    /* 查询日切总批次 */
    iZpc1=0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_sszjhhls \
    	 where chkdate <= '%s' AND chkdate >= '%s' AND chkaccttype = '0'",sChkDate2,sChkDate);     	
    iRet = DBSelectToVar(sErrmsg, &iZpc1, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("查询日切总批次出错"));
        LOG(LM_STD,Fmtmsg("查询日切总批次出错"),fpub_GetCompname(lXmlhandle)) 
        return -75;   
    }

    /* end add dci 20141103 */
    /* mod dci 20141103 
    EXEC SQL SELECT NVL(COUNT(*),0) INTO :iZpc1
         FROM tips_sszjhhls 
         WHERE chkdate <= :sChkDate2
           AND chkdate >= :sChkDate
           AND chkaccttype = '1';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("查询日切总批次出错"));
        LOG(LM_STD,Fmtmsg("查询日切总批次出错"),fpub_GetCompname(lXmlhandle)) 
        return -75;
    }
    */
    /* 查询日切总笔数,总金额 */
    iZbs1=0;
    dZje1=0.00;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select SUM(jybs),SUM(jyje) from tips_sszjhhls \
    	 where chkdate <= '%s' AND chkdate >= '%s' AND chkaccttype = '1'",sChkDate2,sChkDate);     	
    /*iRet =  DBSelectToMultiVar(sErrmsg, sSql1,&iZbs1, &dZje1);*/
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cZbs1, &cZje1);
    		
		iZbs1=atoi(cZbs1);
		dZje1=atof(cZje1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24276, Fmtmsg("查询日切总笔数总金额出错"));
        LOG(LM_STD,Fmtmsg("查询日切总笔数总金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -76;
    }
    /* end add dci 20141103 */ 
    
    /* mod dci 20141103
    EXEC SQL SELECT NVL(SUM(jybs),0), NVL(SUM(jyje), 0.00) INTO :iZbs1, :dZje1
         FROM tips_sszjhhls 
         WHERE chkdate <= :sChkDate2
           AND chkdate >= :sChkDate
           AND chkaccttype = '1';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24276, Fmtmsg("查询日切总笔数总金额出错"));
        LOG(LM_STD,Fmtmsg("查询日切总笔数总金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -76;
    }
    */
    
    /* 查询日切清算笔数,清算金额 */
    
    iQsbs1=0;
    dQsje1=0.00;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select SUM(jybs),SUM(jyje) from tips_sszjhhls \
    	 where chkdate <= '%s' AND chkdate >= '%s' AND chkaccttype = '1'  AND dzbz = '1' AND qsbz = '1'",sChkDate2,sChkDate);     	
    /*iRet =  DBSelectToMultiVar(sErrmsg, sSql1,&iQsbs1, &dQsje1);*/
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cQsbs1, &cQsje1);
    		
		iQsbs1=atoi(cQsbs1);
		dQsje1=atof(cQsje1);
    
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24277, Fmtmsg("查询日间清算笔数、清算金额出错"));
        LOG(LM_STD,Fmtmsg("查询日间清算笔数、清算金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -77;
    }
    /* end add dci 20141103 */ 
    
    /* mod dci 20141103
    EXEC SQL SELECT NVL(SUM(jybs),0), NVL(SUM(jyje), 0.00) INTO :iQsbs1, :dQsje1
         FROM tips_sszjhhls 
         WHERE chkdate <= :sChkDate2
           AND chkdate >= :sChkDate
           AND chkaccttype = '1'
           AND dzbz = '1'
           AND qsbz = '1';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24277, Fmtmsg("查询日间清算笔数、清算金额出错"));
        LOG(LM_STD,Fmtmsg("查询日间清算笔数、清算金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -77;
    }   
    */                

    /* 查询日切未清算笔数,未清算金额 */
    iFQsbs1=0;
    dFQsje1=0.00;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select SUM(jybs),SUM(jyje) from tips_sszjhhls \
    	 where chkdate <= '%s' AND chkdate >= '%s' AND chkaccttype = '1'  AND dzbz <> '1' AND qsbz <> '1'",sChkDate2,sChkDate);     	
    /*iRet =  DBSelectToMultiVar(sErrmsg, sSql1,&iFQsbs1, &dFQsje1);*/
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cFQsbs1, &cFQsje1);
    		
		iFQsbs1=atoi(cFQsbs1);
		dFQsje1=atof(cFQsje1);
    
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24278, Fmtmsg("查询日切未清算笔数、未清算金额出错"));
        LOG(LM_STD,Fmtmsg("查询日切未清算笔数、未清算金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -78;
    }
    /* end add dci 20141103 */ 
    
    /* mod dci 20141103
    EXEC SQL SELECT NVL(SUM(jybs),0), NVL(SUM(jyje), 0.00) INTO :iFQsbs1, :dFQsje1
         FROM tips_sszjhhls 
         WHERE chkdate <= :sChkDate2
           AND chkdate >= :sChkDate
           AND chkaccttype = '1'
           AND dzbz <> '1'
           AND qsbz <> '1';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24278, Fmtmsg("查询日切未清算笔数、未清算金额出错"));
        LOG(LM_STD,Fmtmsg("查询日切未清算笔数、未清算金额出错"),fpub_GetCompname(lXmlhandle)) 
        return -78;
    }
    */

    fprintf(fp,"日切 %8d   %8d %15.2f %8d %15.2f   %8d %15.2f\n",
            iZpc1, iZbs1, dZje1, iQsbs1, dQsje1, iFQsbs1, dFQsje1);

    fprintf(fp,"--------------------------------------------------------------------------------------------\n");    
    fprintf(fp,"合计 %8d   %8d %15.2f %8d %15.2f   %8d %15.2f\n",
            iZpc0+iZpc1, iZbs0+iZbs1, dZje0+dZje1, 
            iQsbs0+iQsbs1, dQsje0+dQsje1, iFQsbs0+iFQsbs1, dFQsje0+dFQsje1);
    (*all) = iZbs0 + iZbs1;
    (*zje) = dZje0 + dZje1;            
    return 0;    
}

/* 生成征收机关扣税异常业务汇总表*/
int prv_tips_reportswychz(HXMLTREE lXmlhandle, FILE *fp, int *all, double *zje, char qdlb[])
{   
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sSql[1024]; 
         char sTableName[32+1];
         char sQsrq[8+1];/* 起始日期 */
         char sJzrq[8+1];/* 截至日期 */
         char sPayeeBankNo[12+1];/* 收款行行号 */
         char sDqdh[10+1];/* 地区代号 */
         char sJgdh[10+1];/* 机构代号 */
         int iZbs;/* 总笔数 */
         double dZje;/* 总金额 */  
    /*EXEC SQL END DECLARE SECTION;*/    
    char sBuf[256];
    char zwrq[8+1];
    int  qzlsh;
    int i,iFlag;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		CURSOR cur_ycywhz;
		/* end add dci 20141103 */	

    fpub_InitSoComp(lXmlhandle);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(zwrq, 0x00, sizeof(zwrq));
    COMP_SOFTGETXML("/tips/zwrq", sBuf)
    pstrcopy(zwrq, sBuf, sizeof(zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    qzlsh=0;
    COMP_SOFTGETXML("/pub/zhqzlsh", sBuf)
    qzlsh=atoi(sBuf);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsrq, 0x00, sizeof(sQsrq));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(sQsrq, sBuf, sizeof(sQsrq));

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJzrq, 0x00, sizeof(sJzrq));
    COMP_SOFTGETXML("/tips/jzrq", sBuf)
    pstrcopy(sJzrq, sBuf, sizeof(sJzrq));
        
    /* 拼接表名 */
    memset(sTableName, 0x00, sizeof(sTableName));
    snprintf(sTableName, sizeof(sTableName), "tmp_%s%08d", zwrq, qzlsh);
    
    /* 删除临时表 */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "drop table %s ", sTableName); 
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        LOG(LM_STD,Fmtmsg("删除临时表失败"),sSql);
        return -1;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    */

    /* 创建临时表 */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "create table %s (payeebankno char(12), dqdh char(10), jgdh char(10), zbs integer, zje decimal(15,2))", sTableName); 
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle,24801,"创建临时异常业务汇总表失败");
    	LOG(LM_STD,Fmtmsg("创建临时异常业务汇总表失败SQL"),sSql);
    	return -81;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if(SQLERR)
    {
        fpub_SetMsg(lXmlhandle,24801,"创建临时异常业务汇总表失败");
    	LOG(LM_STD,Fmtmsg("创建临时异常业务汇总表失败SQL"),sSql);
    	return -81;
    }
    */
    
    LOG(LM_STD,Fmtmsg("创建临时清算登记表成功[%s]",sTableName),"INFO");       
    
    /* 检索当日流水表数据并导入刚创建的临时表 */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "insert into %s select payeebankno, dqdh, jgdh, count(*) as zbs, sum(jyje) as zje from tips_drls where zwrq <= '%s' and zwrq >= '%s' and msgno = '3001' and jyzt <> '0' group by payeebankno, dqdh, jgdh ", sTableName, sJzrq, sQsrq);
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24802, "将当日流水表数据导入临时表失败");
    	LOG(LM_STD,Fmtmsg("将当日流水表数据导入临时表失败"),sSql);
    	return -82;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if(SQLERR)
    {
        fpub_SetMsg(lXmlhandle, 24802, "将当日流水表数据导入临时表失败");
    	LOG(LM_STD,Fmtmsg("将当日流水表数据导入临时表失败"),sSql);
    	return -82;
    }
    */
    
    /* 检索历史流水表数据并导入刚创建的临时表 */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "insert into %s select payeebankno, dqdh, jgdh, count(*) as zbs, sum(jyje) as zje from tips_lsls \
    	where zwrq <= '%s' and zwrq >= '%s' and msgno = '3001' and jyzt <> '0' group by payeebankno, dqdh, jgdh ", sTableName, sJzrq, sQsrq);
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle,24803, "将历史流水表数据导入临时表失败");
    	LOG(LM_STD,Fmtmsg("将历史流水表数据导入临时表失败"),sSql);
    	return -83;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if(SQLERR)
    {
        fpub_SetMsg(lXmlhandle,24803, "将历史流水表数据导入临时表失败");
    	LOG(LM_STD,Fmtmsg("将历史流水表数据导入临时表失败"),sSql);
    	return -83;
    }

    /* 检索批量扣税费明细表数据并导入刚创建的临时表 */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "insert into %s select payeebankno, dqdh, jgdh, count(*) as zbs, sum(jyje) as zje from tips_ssplksfmx \
    	where zwrq <= '%s' and zwrq >= '%s' and czbd <> '7' group by payeebankno, dqdh, jgdh ", sTableName, sJzrq, sQsrq);
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle,24804,"将批量扣税费明细表数据导入临时表失败");
    	LOG(LM_STD,Fmtmsg("将批量扣税费明细表数据导入临时表失败"),sSql);
    	return -84;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if(SQLERR)
    {
        fpub_SetMsg(lXmlhandle,24804,"将批量扣税费明细表数据导入临时表失败");
    	LOG(LM_STD,Fmtmsg("将批量扣税费明细表数据导入临时表失败"),sSql);
    	return -84;
    }

    /* 检索批量扣税费明细历史表数据并导入刚创建的临时表 */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "insert into %s select payeebankno, dqdh, jgdh, count(*) as zbs,sum(jyje) as zje from tips_ssplksfmx_ls \
    	where zwrq <= '%s' and zwrq >= '%s' and czbd <> '7' group by payeebankno, dqdh, jgdh ", sTableName, sJzrq, sQsrq);
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle,24805,"将批量扣税费明细表数据导入临时表失败");
    	LOG(LM_STD,Fmtmsg("将批量扣税费明细表数据导入临时表失败"),sSql);
    	return -85;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;    
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if(SQLERR)
    {
        fpub_SetMsg(lXmlhandle,24805,"将批量扣税费明细表数据导入临时表失败");
    	LOG(LM_STD,Fmtmsg("将批量扣税费明细表数据导入临时表失败"),sSql);
    	return -85;
    }*/

    /* 声明游标，开始从临时表中取数据 */
    /* add dci 20141103 */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "select payeebankno, dqdh, jgdh, sum(zbs) as zbs, sum(zje)\
    	from %s group by payeebankno, dqdh, jgdh order by payeebankno, dqdh, jgdh ", sTableName);
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
     if ((cur_ycywhz = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur_ycywhz) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur_ycywhz);
        fpub_SetMsg(lXmlhandle,24806,"打开游标cur_ycywhz失败");
    		LOG(LM_STD,Fmtmsg("打开游标cur_ycywhz失败"),sSql);
    		return -86;
    }
 	 
    fprintf(fp, "序号    国库号         机构号     笔数            金额    \n");  
    
    for (i=1,iFlag=0;;i++)
    {
        memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
        memset(sDqdh, 0x00, sizeof(sDqdh));
        memset(sJgdh, 0x00, sizeof(sJgdh));
        iZbs=0;
        dZje=0.00;
        
        iRet = DCIFetch2(cur_ycywhz, DCI_FETCH_NEXT, 0);  
    		if(iRet < 0)
				{
					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")

					iFlag=-87;
        	LOG(LM_STD,Fmtmsg("从cur_ycywhz游标获取数据失败"),"ERROR");
        	break;
				}
				if ( iRet == 0 )
            break;
            
        sprintf( sPayeeBankNo      , "%s", DCIFieldAsString( cur_ycywhz, 0 ) );  
        sprintf( sDqdh       , "%s", DCIFieldAsString( cur_ycywhz, 1 ) );       
        iZbs = atoi(DCIFieldAsString( cur_ycywhz, 2 ) );
        dZje = atof(DCIFieldAsString( cur_ycywhz, 3 ) );        
        
        trim(sPayeeBankNo);
        trim(sDqdh);
        trim(sJgdh);
        
        fprintf(fp, "%05d %12.12s %10.10s %8d %15.2f \n", 
            i, sPayeeBankNo, sJgdh, iZbs, dZje);
        (*all) += iZbs;
        (*zje) += dZje;      
     }                   
    DCIFreeCursor(cur_ycywhz);
    
    fprintf(fp, "----------------------------------------------------------------\n");
    /* 删除临时表 */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "drop table %s ", sTableName); 
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle,24807,"生成征收机关扣税异常业务汇总表");
    		LOG(LM_STD,Fmtmsg("生成征收机关扣税异常业务汇总表[%d]", iFlag),"ERROR");
    		return iFlag;
        
    }
    /* end add dci */
    
    /* mod dci 20141103
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "select payeebankno, dqdh, jgdh, nvl(sum(zbs),0) as zbs, nvl(sum(zje), 0.00) from %s group by payeebankno, dqdh, jgdh order by payeebankno, dqdh, jgdh ", sTableName);
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
 	/*prepare
    EXEC SQL PREPARE sql_ycywhz FROM :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_ycywhz",sqlca.sqlcode),"ERROR");    
    /*declare
    EXEC SQL DECLARE cur_ycywhz CURSOR for sql_ycywhz;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_ycywhz",sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_ycywhz;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_ycywhz", sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24806,"打开游标cur_ycywhz失败");
    	LOG(LM_STD,Fmtmsg("打开游标cur_ycywhz失败"),sSql);
    	return -86;
    }
    fprintf(fp, "序号    国库号         机构号     笔数            金额    \n");    
    for (i=1,iFlag=0;;i++)
    {
        memset(sPayeeBankNo, 0x00, sizeof(sPayeeBankNo));
        memset(sDqdh, 0x00, sizeof(sDqdh));
        memset(sJgdh, 0x00, sizeof(sJgdh));
        iZbs=0;
        dZje=0.00;
        EXEC SQL FETCH cur_ycywhz INTO :sPayeeBankNo, :sDqdh, :sJgdh, :iZbs, :dZje;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_ycywhz",sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iFlag=-87;
        	LOG(LM_STD,Fmtmsg("从cur_ycywhz游标获取数据失败"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
            break;
        trim(sPayeeBankNo);
        trim(sDqdh);
        trim(sJgdh);
        
        fprintf(fp, "%05d %12.12s %10.10s %8d %15.2f \n", 
            i, sPayeeBankNo, sJgdh, iZbs, dZje);
        (*all) += iZbs;
        (*zje) += dZje;      
     }                   
    EXEC SQL CLOSE cur_ycywhz;
    fprintf(fp, "----------------------------------------------------------------\n");
    /* 删除临时表 
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "drop table %s ", sTableName); 
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if (iFlag < 0)
    {
        fpub_SetMsg(lXmlhandle,24807,"生成征收机关扣税异常业务汇总表");
    	LOG(LM_STD,Fmtmsg("生成征收机关扣税异常业务汇总表[%d]", iFlag),"ERROR");
    	return iFlag;
    }*/
    
    return COMPRET_SUCC;              
}
  
/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_REPORT
组件名称: 生成各类清单
组件功能: 
  生成各类清单
  清单类别:
  01-往账清单
  02-往账异常清单
  03-来账清单
  04-来账异常清单
  05-业务量统计表
  06-对账清单
  07-资金清算汇总清单
  08-税务扣税异常汇总表
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
当日流水	tips_drls
历史流水    tips_lsls
批量扣税费明细 tips_ssplksfmx
批量扣税费历史明细 tips_ssplksfmx_ls

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年12月10日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_REPORT(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sBankName[60+1];/* 行名 */
         char sReportName[60+1];/* 报表名称 */
         int iQdlb;   
    /*EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    char sQdlb[2+1];/* 清单类别 */
    char sQdFile[256];/* 清单文件名 */
    char sSysDate[8+1];
    char sQsrq[8+1];
    char sJzrq[8+1];
    int iAll=0;
    double dZje=0.00;
    
    FILE *fp;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		CURSOR cur;
		/* end add dci 20141103 */	
            
    fpub_InitSoComp(lXmlhandle); 
    
    COMP_PARACOUNTCHK(2);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQdlb, 0x00, sizeof(sQdlb));
    COMP_GETPARSEPARAS(1, sBuf, "清单类别")
    pstrcopy(sQdlb, sBuf, sizeof(sQdlb));
    trim(sQdlb);

    memset(sQdFile, 0x00, sizeof(sQdFile));
    COMP_GETPARSEPARAS(2, sBuf, "清单文件名")
    pstrcopy(sQdFile, sBuf, sizeof(sQdFile));
    trim(sQdFile);
    
    LOG(LM_STD,Fmtmsg("生成各类清单...清单类别[%s],清单文件名[%s]", sQdlb, sQdFile), fpub_GetCompname(lXmlhandle))        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSysDate, 0x00, sizeof(sSysDate));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(sSysDate, sBuf, sizeof(sSysDate));

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsrq, 0x00, sizeof(sQsrq));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(sQsrq, sBuf, sizeof(sQsrq));
    if ( sQsrq[0] == '\0')/* add by tuql 20091224 增加对起始日期及截止日期非空判断*/
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("起始日期不能为空"));
        LOG(LM_STD,Fmtmsg("起始日期不能为空, qsrq=[%s]", sQsrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJzrq, 0x00, sizeof(sJzrq));
    COMP_SOFTGETXML("/tips/jzrq", sBuf)
    pstrcopy(sJzrq, sBuf, sizeof(sJzrq));
    if ( sJzrq[0] == '\0')/* add by tuql 20091224 增加对起始日期及截止日期非空判断*/
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24276, Fmtmsg("截止日期不能为空"));
        LOG(LM_STD,Fmtmsg("截止日期不能为空, jzrq=[%s]", sJzrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }
    
    /* add dci 20141103 */
    memset(sBankName, 0x00, sizeof(sBankName));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select bankname from tips_nbcsb WHERE 1=1");     	
    iRet = DBSelectToVar(sErrmsg, &sBankName, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24501, "查询内部参数表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询内部参数表失败"), fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;        
    }
    trim(sBankName);

    iQdlb=atoi(sQdlb);
    memset(sReportName, 0x00, sizeof(sReportName));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select num_desc from tips_codelist WHERE code_name='report_name'\
    	AND num='%d'",iQdlb);     	
    iRet = DBSelectToVar(sErrmsg, &sReportName, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24501, "查询内部参数表失败");
        fpub_SetMsg(lXmlhandle, 24502, "查询数据字典失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询数据字典失败"), fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;        
    }    
    if ( iRet == 0)
    {
         fpub_SetMsg(lXmlhandle, 24503, "清单名称未初始化");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("清单名称未初始化"), fpub_GetCompname(lXmlhandle))        
    } 
                
    trim(sReportName);
    
    /* end add dci */
    /* mod dci 20141103
    memset(sBankName, 0x00, sizeof(sBankName));
    EXEC SQL SELECT bankname INTO :sBankName
         FROM tips_nbcsb 
         WHERE 1=1;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24501, "查询内部参数表失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询内部参数表失败"), fpub_GetCompname(lXmlhandle))
    }         
    trim(sBankName);

    iQdlb=atoi(sQdlb);
    memset(sReportName, 0x00, sizeof(sReportName));
    EXEC SQL SELECT num_desc INTO :sReportName
         FROM tips_codelist 
         WHERE code_name='report_name'
           AND num=:iQdlb;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24502, "查询数据字典失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("查询数据字典失败"), fpub_GetCompname(lXmlhandle))
    }
    if (SQLNOTFOUND)
    {
         fpub_SetMsg(lXmlhandle, 24503, "清单名称未初始化");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("清单名称未初始化"), fpub_GetCompname(lXmlhandle))        
    } 
                
    trim(sReportName);
    
    */
    
    fp = fopen(sQdFile,"w");
    if ( fp == NULL )
    {
         fpub_SetMsg(lXmlhandle, 24504, "打开清单文件失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开清单文件失败[%s]", 
             strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
    fprintf(fp,"         %s横向联网系统%s\n", sBankName, sReportName);
    fprintf(fp,"         查询日期:%s-%s      打印日期:%s\n", sQsrq, sJzrq, sSysDate);
    
    iRet=-1;
    iAll=0;/* add by tuql 20100108 */
    dZje=0.00;/* add by tuql 20100108 */
    switch(iQdlb)
    {
        case 1:/* 01-往账清单 */
        case 2:/* 02-往账异常清单 */
        case 3:/* 03-来账清单 */
        case 4:/* 04-来账异常清单 */    
            iRet = prv_tips_report(lXmlhandle, fp, &iAll, &dZje, sQdlb);
            fprintf(fp,"总计笔数:%d     金额:%.2f\n", iAll, dZje);
            if ( iAll < 1 )
            {    
                fpub_SetMsg(lXmlhandle, 24505, "该机构及其下属机构无数据");
                LOG(LM_STD,Fmtmsg("该机构及其下属机构无数据"), fpub_GetCompname(lXmlhandle));             
                iRet=-505;
            }    
            break;
        case 5:                       
            iRet = prv_tips_reportywl(lXmlhandle, fp, &iAll, &dZje, sQdlb); 
            if ( iAll < 1 )
            {    
                fpub_SetMsg(lXmlhandle, 24506, "该机构及其下属机构无数据");
                LOG(LM_STD,Fmtmsg("该机构及其下属机构无数据"), fpub_GetCompname(lXmlhandle));             
                iRet=-506;
            }            
            break;
        case 6:                       
            iRet = prv_tips_reportdzb(lXmlhandle, fp, &iAll, &dZje, sQdlb); 
            fprintf(fp,"总计笔数:%d     金额:%.2f\n", iAll, dZje);
            if ( iAll < 1 )
            {    
                fpub_SetMsg(lXmlhandle, 24507, "查询区间内无数据");
                LOG(LM_STD,Fmtmsg("查询区间内无数据"), fpub_GetCompname(lXmlhandle));             
                iRet=-507;
            }            
            break;
        case 7:                       
            iRet = prv_tips_reportzjqshz(lXmlhandle, fp, &iAll, &dZje, sQdlb); 
            if ( iAll < 1 )
            {    
                fpub_SetMsg(lXmlhandle, 24508, "查询区间内无数据");
                LOG(LM_STD,Fmtmsg("查询区间内无数据"), fpub_GetCompname(lXmlhandle));             
                iRet=-508;
            }            
            break;
        case 8:                       
            iRet = prv_tips_reportswychz(lXmlhandle, fp, &iAll, &dZje, sQdlb); 
            fprintf(fp,"总计笔数:%d     金额:%.2f\n", iAll, dZje);
            if ( iAll < 1 )
            {    
                fpub_SetMsg(lXmlhandle, 24509, "查询区间内无数据");
                LOG(LM_STD,Fmtmsg("查询区间内无数据"), fpub_GetCompname(lXmlhandle));             
                iRet=-509;
            }            
            break;
        default:
            fpub_SetMsg(lXmlhandle, 24510, "清单类别有误");
            LOG(LM_STD,Fmtmsg("清单类别有误[%s]", sQdlb), fpub_GetCompname(lXmlhandle)) 
            iRet=-510;       
            break; 
    }
    fclose(fp);
    if ( iRet < 0 )
    {
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("生成清单失败[%d]", iRet), fpub_GetCompname(lXmlhandle))        
    }
        
    fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "生成清单成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("生成清单成功"), fpub_GetCompname(lXmlhandle));             
    return COMPRET_SUCC;                    
}
