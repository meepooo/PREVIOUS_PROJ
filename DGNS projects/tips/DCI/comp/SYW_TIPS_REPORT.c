/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V3.0.00
����ϵͳ:AIX5.3
�ļ�����:SYW_TIPS_REPORT.ec
�ļ�����:TIPS�����嵥����
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:Tuql
��������:
��    ��:
�޸�����:  
*********************************************************************/
/*
����˵��:

����˵��
�����������                 �������                      ��������  ����Ա �޸����� �޸���

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
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24502, "��ѯ�����ֵ�ʧ��");
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
         fpub_SetMsg(lXmlhandle, 24502, "��ѯ�����ֵ�ʧ��");
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

/* ��ѯ��ˮ���ܱ��� */
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
        double dZje;/* �ܽ�� */
        short indZje;/* ָʾ���� */
    /*EXEC SQL END DECLARE SECTION;*/
    char sQsrq[8+1];/* ��ʼ���� */
    char sJzrq[8+1];/* ��ֹ���� */
    char sTaxOrgCode[12+1];/* ���ջ��ش��� */
    char sTaxVouNo[18+1];/* ˰Ʊ���� */
    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
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

    /* �Ȳ�ѯ�������Ƿ��м�¼���ڣ����ޣ��򷵻� */    
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
  	}
  	if (DCIExecute(cur) == -1)
  	{
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        
        fpub_SetMsg(lXmlhandle,24311, "ǰ��ϵͳ����:��cur_report_count�α�ʧ��");       
        LOGRET(-1,LM_STD,Fmtmsg("��cur_report_count�α�ʧ��"),
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
        fpub_SetMsg(lXmlhandle,24311, "ǰ��ϵͳ����:��cur_report_count�α�ʧ��");       
        LOGRET(-1,LM_STD,Fmtmsg("��cur_report_count�α�ʧ��"),
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        
        DCIFreeCursor(cur);   
        fpub_SetMsg(lXmlhandle,24312, "ǰ��ϵͳ����:���α�cur_report_count��ȡ����ʧ��");       
        LOGRET(-2,LM_STD,Fmtmsg("���α�cur_report_count��ȡ����ʧ��"),
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
        fpub_SetMsg(lXmlhandle,24312, "ǰ��ϵͳ����:���α�cur_report_count��ȡ����ʧ��");       
        LOGRET(-2,LM_STD,Fmtmsg("���α�cur_report_count��ȡ����ʧ��"),
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

/* ����д�嵥�� */
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
        LOG(LM_STD,Fmtmsg("��ѯ����״̬ʧ��[%d]",iRet),fpub_GetCompname(lXmlhandle));
        return iRet;   
    }    
    fprintf(fp,"%05d %8.8s %8d %24.24s %20.20s %15.2f  %12.12s  %18.18s %8.8s %8.8s %4.4s         %10.10s \n",
            i,stReport.zwrq,stReport.zhqzlsh,stReport.payacct,stReport.handorgname,stReport.jyje,stReport.taxorgcode,stReport.taxvouno,sCnJyzt,stReport.chkdate, stReport.chkacctord, stReport.jygy);        
    return 0;
}

/* �쳣����д�嵥�� */
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
        LOG(LM_STD,Fmtmsg("��ѯ����״̬ʧ��[%d]",iRet),fpub_GetCompname(lXmlhandle));
        return iRet;   
    }
    fprintf(fp,"%05d %8.8s %8d %24.24s %20.20s %15.2f  %12.12s  %18.18s %8.8s %8.8s %4.4s         %10.10s  %30.30s\n",
            i,stReport.zwrq,stReport.zhqzlsh,stReport.payacct,stReport.handorgname,stReport.jyje,stReport.taxorgcode,stReport.taxvouno,sCnJyzt,stReport.chkdate, stReport.chkacctord, stReport.jygy, stReport.xyxx);        
    return 0;
}

/* ����д�嵥�� */
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
        LOG(LM_STD,Fmtmsg("��ѯ����״̬ʧ��[%d]",iRet),fpub_GetCompname(lXmlhandle));
        return iRet;   
    }
    fprintf(fp,"%05d %8.8s %8d   %24.24s %20.20s %15.2f  %12.12s  %20.20s %18.18s %8.8s %8.8s %4.4s          \n",
            i,stReport.zwrq,stReport.zhqzlsh,stReport.payacct,stReport.handorgname,stReport.jyje,stReport.taxorgcode,stReport.protocolno,stReport.taxvouno,sCnJyzt,stReport.chkdate, stReport.chkacctord);        
    return 0;
}

/* �쳣����д�嵥�� */
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
        LOG(LM_STD,Fmtmsg("��ѯ����״̬ʧ��[%d]",iRet),fpub_GetCompname(lXmlhandle));
        return iRet;   
    }
    fprintf(fp,"%05d %8.8s %8d   %24.24s %20.20s %15.2f  %12.12s  %20.20s %18.18s %8.8s %8.8s %4.4s       %30.30s\n",
            i,stReport.zwrq,stReport.zhqzlsh,stReport.payacct,stReport.handorgname,stReport.jyje,stReport.taxorgcode,stReport.protocolno,stReport.taxvouno,sCnJyzt,stReport.chkdate, stReport.chkacctord, stReport.xyxx);        
    return 0;
}

/* д�嵥(����ͨ��) */
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
    char sQsrq[8+1];/* ��ʼ���� */
    char sJzrq[8+1];/* ��ֹ���� */
    char sTaxOrgCode[12+1];/* ���ջ��ش��� */
    char sTaxVouNo[18+1];/* ˰Ʊ���� */
    char sQdlb[2+1];/* �嵥��� */
    char sBuf[256];
    int iflag,i,j;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
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
        fpub_SetMsg(lXmlhandle, 24401, "�嵥�������");
        LOG(LM_STD,Fmtmsg("�嵥�������"),fpub_GetCompname(lXmlhandle))
        return -401;        
    }
    
    memset(sSql, 0x00, sizeof(sSql));
    if (tablekind==1)/* ��ѯ������ˮ */
    {
        snprintf(sSql, sizeof(sSql), "select zwrq,zhqzlsh,payacct,handorgname,jyje,taxorgcode,taxvouno,jyzt,chkdate,chkacctord,jygy,xyxx,protocolno from %s where 1=1 and zwrq >= '%s' and zwrq <= '%s' and dqdh='%s' and jgdh='%s' %s ", 
            tablename, sQsrq, sJzrq, dqdh, jgdh, wherecon);        
    }else/* ������ϸ */
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
 	if (tablekind==1)/* ��ѯ������ˮ */
    {
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," order by zwrq, zhqzlsh ");
 	}else/* ������ϸ */
 	{
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," order by zwrq, plmxxh "); 	    
 	}    
 	trim(sSql);
 	LOG(LM_STD,Fmtmsg("sSql[%s]",sSql),fpub_GetCompname(lXmlhandle));
 		
 		/* add dci 20141103 */
 		if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
  	{
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
  	}
  	if (DCIExecute(cur) == -1)
  	{
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        
        fpub_SetMsg(lXmlhandle,24311, "ǰ��ϵͳ����:��cur_report_count�α�ʧ��");       
        LOGRET(-1,LM_STD,Fmtmsg("��cur_report_count�α�ʧ��"),
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
        fpub_SetMsg(lXmlhandle,24314, "ǰ��ϵͳ����,���α�cur_report_wqdʧ��");       
        LOGRET(-4,LM_STD,Fmtmsg("��cur_report_wqd�α�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
		*/
    /*��ʼѭ��*/
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
        	fpub_SetMsg(lXmlhandle,24315, "ǰ��ϵͳ����:��cur_report_wqd�α��ȡ����ʧ��");
        	LOG(LM_STD,Fmtmsg("��cur_report_wqd�α��ȡ����ʧ��"),"ERROR");
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
        	fpub_SetMsg(lXmlhandle,24315, "ǰ��ϵͳ����:��cur_report_wqd�α��ȡ����ʧ��");
        	LOG(LM_STD,Fmtmsg("��cur_report_wqd�α��ȡ����ʧ��"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;
        */
        
        iflag=prv_tips_report_wqdbodyXX(lXmlhandle,fp,tablekind,j+i,stReport);
        if (iflag<0)
        {
        	LOG(LM_STD,Fmtmsg("д�嵥�ļ���ʧ��[%d]", iflag),"ERROR");
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
        LOGRET(-5,LM_STD,Fmtmsg("�����嵥ʧ��iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    return COMPRET_SUCC; 	
}

/* ���������嵥 �����쳣�嵥*/
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
    char sQdlb[2+1];/* �嵥��� */
    int iAllJg=0;/* �����ܱ��� */
    double dSumJg=0.00;/* �����ܽ�� */
    int iTmpBs=0;/* ��ʱ���� */
    double dTmpJe=0.00;/* ��ʱ��� */
    
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
    
    /* �Ȳ�һ�µ�����ˮ���Ƿ��м�¼���� */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_drls");
    iDrls=0;
    iDrls=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iDrls < 0 )                                    
    {
        LOGRET(iDrls,LM_STD,Fmtmsg("��ѯ������ˮ���Ƿ��м�¼ʧ��[%d]", iDrls),
            fpub_GetCompname(lXmlhandle))        
    }
    iAllCount += iDrls;
    /* �Ȳ�һ����ʷ��ˮ���Ƿ��м�¼���� */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_lsls");
    iLsls=0;
    iLsls=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iLsls < 0 )                                    
    {
        LOGRET(iLsls,LM_STD,Fmtmsg("��ѯ��ʷ��ˮ���Ƿ��м�¼ʧ��[%d]", iLsls),
            fpub_GetCompname(lXmlhandle))        
    }    
    iAllCount += iLsls;
    /* ������û�пɲ�ѯ�ļ�¼,��ֱ�ӷ��سɹ� */
    if ( iAllCount < 1 )
    {
        /* LOG(LM_DEBUG,Fmtmsg("������[%s][%s]��ѯ�������޼�¼", dqdh, jgdh), fpub_GetCompname(lXmlhandle)); */
        return 0;
    }
    if (strncmp(sQdlb, "01", 2) == 0)
    {        
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(fp,"�� �� �ۿ����� ������ˮ��      �������˺�            ����������              ���׽��  ���ջ��ش���       ˰Ʊ����      ����״̬ �������� �������� ���˹�Ա\n");
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }else
    {
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(fp,"�� �� �ۿ����� ������ˮ��      �������˺�            ����������              ���׽��  ���ջ��ش���       ˰Ʊ����      ����״̬ �������� �������� ���˹�Ա  �쳣��Ϣ  \n");
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");        
    }    
    if ( iDrls > 0 )/* ��������ˮ��������,��д�嵥 */
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
            LOGRET(-5,LM_STD,Fmtmsg("�����嵥ʧ��iRet=[%d]",iRet),
                fpub_GetCompname(lXmlhandle))
        }
    }

    if ( iLsls > 0 )/* ��������ˮ��������,��д�嵥 */
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
            LOGRET(-5,LM_STD,Fmtmsg("�����嵥ʧ��iRet=[%d]",iRet),
                fpub_GetCompname(lXmlhandle))
        }
    }
    fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(fp,"�����ţ�%s       �ϼƱ�����%d       �ϼƽ��:%.2f\n\n", jgdh, iAllJg, dSumJg); 
    (*all)+= iAllJg;
    (*zje) += dSumJg;
    
    return COMPRET_SUCC;              
}

/* ���������嵥 �����쳣�嵥*/
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
    char sQdlb[2+1];/* �嵥��� */
    int iAllJg=0;/* �����ܱ��� */
    double dSumJg=0.00;/* �����ܽ�� */
    int iTmpBs=0;/* ��ʱ���� */
    double dTmpJe=0.00;/* ��ʱ��� */
        
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
    
    /* �鵱����ˮ���Ƿ��м�¼���� */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_drls");
    iDrls=0;
    iDrls=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iDrls < 0 )                                    
    {
        LOGRET(iDrls,LM_STD,Fmtmsg("��ѯ������ˮ���Ƿ��м�¼ʧ��[%d]", iDrls),
            fpub_GetCompname(lXmlhandle))        
    }
    iAllCount += iDrls;
    /* ����ʷ��ˮ���Ƿ��м�¼���� */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_lsls");
    iLsls=0;
    iLsls=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iLsls < 0 )                                    
    {
        LOGRET(iLsls,LM_STD,Fmtmsg("��ѯ��ʷ��ˮ���Ƿ��м�¼ʧ��[%d]", iLsls),
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
    /* ��������˰����ϸ���Ƿ��м�¼���� */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_ssplksfmx");
    iPlmx=0;
    iPlmx=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iPlmx < 0 )                                    
    {
        LOGRET(iPlmx,LM_STD,Fmtmsg("��ѯ������˰����ϸ���Ƿ��м�¼ʧ��[%d]", iPlmx),
            fpub_GetCompname(lXmlhandle))        
    }
    iAllCount += iPlmx;
    /* ��������ʷ��ˮ���Ƿ��м�¼���� */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_ssplksfmx_ls");
    iPlls=0;
    iPlls=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iTmpBs,&dTmpJe);
    if ( iLsls < 0 )                                    
    {
        LOGRET(iPlls,LM_STD,Fmtmsg("��ѯ��ʷ��ˮ���Ƿ��м�¼ʧ��[%d]", iPlls),
            fpub_GetCompname(lXmlhandle))        
    }    
    iAllCount += iPlls;    
    /* ������û�пɲ�ѯ�ļ�¼,��ֱ�ӷ��سɹ� */
    if ( iAllCount < 1 )
    {
        /* LOG(LM_DEBUG,Fmtmsg("������[%s][%s]��ѯ�������޼�¼", dqdh, jgdh), fpub_GetCompname(lXmlhandle)); */
        return 0;
    }
    if (strncmp(sQdlb, "03", 2) == 0)
    {        
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(fp,"�� �� �ۿ����� ������ˮ��      �������˺�            ����������                ���׽��  ���ջ��ش���    Э�����              ˰Ʊ����      ����״̬ �������� �������� \n");
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    }else
    {
        fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
        fprintf(fp,"�� �� �ۿ����� ������ˮ��      �������˺�            ����������                ���׽��  ���ջ��ش���    Э�����              ˰Ʊ����      ����״̬ �������� �������� �쳣��Ϣ  \n");
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
    if ( iDrls > 0 )/* ��������ˮ��������,��д�嵥 */
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
            LOGRET(-5,LM_STD,Fmtmsg("�����嵥ʧ��iRet=[%d]",iRet),
                fpub_GetCompname(lXmlhandle))
        }
    }

    if ( iLsls > 0 )/* ��������ˮ��������,��д�嵥 */
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
            LOGRET(-5,LM_STD,Fmtmsg("�����嵥ʧ��iRet=[%d]",iRet),
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
    if ( iPlmx > 0 )/* ��������ϸ��������,��д�嵥 */
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
            LOGRET(-5,LM_STD,Fmtmsg("�����嵥ʧ��iRet=[%d]",iRet),
                fpub_GetCompname(lXmlhandle))
        }
    }

    if ( iPlls > 0 )/* ��������ϸ��ʷ��������,��д�嵥 */
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
            LOGRET(-5,LM_STD,Fmtmsg("�����嵥ʧ��iRet=[%d]",iRet),
                fpub_GetCompname(lXmlhandle))
        }
    }

    fprintf(fp,"-----------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
    fprintf(fp,"�����ţ�%s       �ϼƱ�����%d       �ϼƽ��:%.2f\n\n", jgdh, iAllJg, dSumJg); 
    (*all)+= iAllJg;
    (*zje) += dSumJg;
    
    return COMPRET_SUCC;              
}

/* ����ҵ����ͳ���嵥*/
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
    int iDrskbs=0;/* ����ʵ�۱��� */
    double dDrskje=0.00;/* ����ʵ�۽�� */
    int iLsskbs=0;/* ��ʷʵ�۱��� */
    double dLsskje=0.00;/* ��ʷʵ�۽�� */
    int iSkbs=0;/* ʵ�۱��� */
    double dSkje=0.00;/* ʵ�۽�� */
    int iDrpkbs=0;/* �������۱��� */
    double dDrpkje=0.00;/* �������۽�� */
    int iLspkbs=0;/* ��ʷ���۱��� */
    double dLspkje=0.00;/* ��ʷ���۽�� */
    int iPkbs=0;/* ���۱��� */
    double dPkje=0.00;/* ���۽�� */
    int iDryjsbbs=0;/* ���������걨���� */
    double dDryjsbje=0.00;/* ���������걨��� */
    int iLsyjsbbs=0;/* ��ʷ�����걨���� */
    double dLsyjsbje=0.00;/* ��ʷ�����걨���� */
    int iYjsbbs=0;/* �����걨���� */
    double dYjsbje=0.00;/* �����걨��� */
    int iDryjjkbs=0;/* �������ɽɿ���� */
    double dDryjjkje=0.00;/* �������ɽɿ��� */
    int iLsyjjkbs=0;/* ��ʷ���ɽɿ���� */
    double dLsyjjkje=0.00;/* ��ʷ���ɽɿ��� */
    int iYjjkbs=0;/* ���ɽɿ���� */
    double dYjjkje=0.00;/* ���ɽɿ��� */
    int iAllJg=0;/* �����ܱ��� */
    double dSumJg=0.00;/* �����ܽ�� */
    int iTmpbs=0;/* ��ʱ���� */
    double dTmpje=0.00;/* ��ʱ��� */
    
    fpub_InitSoComp(lXmlhandle); 

    iAllJg=0;
    dSumJg=0.00;
    
    iSkbs=0;
    dSkje=0.00;           
    memset(sWhereCon, 0x00, sizeof(sWhereCon));
    strcpy(sWhereCon, " and msgno='3001' "); 
    /* 1.��ѯ������ˮ���ʵ�۱�������� */  
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_drls");
    iDrskbs=0;
    dDrskje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iDrskbs,&dDrskje);
    if ( iRet < 0 )                   
    {
        LOGRET(iRet,LM_STD,Fmtmsg("��ѯ������ˮ���ʵ�۱��������ʧ��[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }
    iSkbs += iDrskbs;
    dSkje += dDrskje;
    /* 2.��ѯ��ʷ��ˮ���ʵ�۱�������� */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_lsls");
    iLsskbs=0;
    dLsskje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iLsskbs,&dLsskje);
    if ( iRet < 0 )                                    
    {
        LOGRET(iRet,LM_STD,Fmtmsg("��ѯ��ʷ��ˮ���ʵ�۱��������ʧ��[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }    
    iSkbs += iLsskbs;
    dSkje += dLsskje;
    iAllJg += iSkbs;
    dSumJg += dSkje;

    iPkbs=0;
    dPkje=0.00;
    memset(sWhereCon, 0x00, sizeof(sWhereCon));
    /* 3.��ѯ�������۱�������� */  
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_ssplksfmx");
    iDrpkbs=0;
    dDrpkje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iDrpkbs,&dDrpkje);
    if ( iRet < 0 )                   
    {
        LOGRET(iRet,LM_STD,Fmtmsg("��ѯ�������۱��������ʧ��[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }
    iPkbs += iDrpkbs;
    dPkje += dDrpkje;
    /* 4.��ѯ��ʷ���۱�������� */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_ssplksfmx_ls");
    iLspkbs=0;
    dLspkje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iLspkbs,&dLspkje);
    if ( iRet < 0 )                                    
    {
        LOGRET(iRet,LM_STD,Fmtmsg("��ѯ��ʷ���۱��������ʧ��[%d]", iRet),
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
    /* 5.��ѯ������ˮ��������걨��������� */  
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_drls");
    iDryjsbbs=0;
    dDryjsbje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iDryjsbbs,&dDryjsbje);
    if ( iRet < 0 )                   
    {
        LOGRET(iRet,LM_STD,Fmtmsg("��ѯ������ˮ��������걨���������ʧ��[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }
    iYjsbbs += iDryjsbbs;
    dYjsbje += dDryjsbje;
    /* 6.��ѯ��ʷ��ˮ��������걨��������� */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_lsls");
    iLsyjsbbs=0;
    dLsyjsbje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iLsyjsbbs,&dLsyjsbje);
    if ( iRet < 0 )                                    
    {
        LOGRET(iRet,LM_STD,Fmtmsg("��ѯ��ʷ��ˮ��������걨���������ʧ��[%d]", iRet),
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
    /* 7.��ѯ������ˮ������ɽɿ��������� */  
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_drls");
    iDryjjkbs=0;
    dDryjjkje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iDryjjkbs,&dDryjjkje);
    if ( iRet < 0 )                   
    {
        LOGRET(iRet,LM_STD,Fmtmsg("��ѯ������ˮ������ɽɿ���������ʧ��[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }
    iYjjkbs += iDryjjkbs;
    dYjjkje += dDryjjkje;
    /* 6.��ѯ��ʷ��ˮ������ɽɿ��������� */
    memset(sTableName, 0x00, sizeof(sTableName));
    strcpy(sTableName, "tips_lsls");
    iLsyjjkbs=0;
    dLsyjjkje=0.00;
    iRet=prv_tips_report_count(lXmlhandle,dqdh,jgdh,sTableName,sWhereCon,&iLsyjjkbs,&dLsyjjkje);
    if ( iRet < 0 )                                    
    {
        LOGRET(iRet,LM_STD,Fmtmsg("��ѯ��ʷ��ˮ������ɽɿ���������ʧ��[%d]", iRet),
            fpub_GetCompname(lXmlhandle))        
    }    
    iYjjkbs += iLsyjjkbs;
    dYjjkje += dLsyjjkje; 
    iAllJg += iYjjkbs;
    dSumJg += dYjjkje;
    
    /* ������û�пɲ�ѯ�ļ�¼,��ֱ�ӷ��سɹ� */
    if ( iAllJg < 1 )
    {
        /* LOG(LM_DEBUG,Fmtmsg("������[%s][%s]��ѯ�������޼�¼", dqdh, jgdh), fpub_GetCompname(lXmlhandle)); */
        return 0;
    }   
    fprintf(fp,"%5d %-10.10s  %-16.16s  %5d %15.2f %5d %15.2f %5d %15.2f %5d %15.2f %5d %15.2f\n",
            (*i)+1, jgdh, jgmc, iSkbs, dSkje, iPkbs, dPkje, iYjsbbs, dYjsbje, iYjjkbs, dYjjkje, iAllJg, dSumJg );               
    (*i)++;
    /* ���ͳ�Ʊ�������� */
    /* 1.ʵ�۱��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/skbs", sBuf)
    iTmpbs= atoi(sBuf) + iSkbs;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%d", iTmpbs);
    COMP_SOFTSETXML("/tips/skbs", sBuf)
    /* 2.ʵ�۽�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/skje", sBuf)
    dTmpje = atof(sBuf) + dSkje;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%.2f", dTmpje);
    COMP_SOFTSETXML("/tips/skje", sBuf)
    /* 3.���۱��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/pkbs", sBuf)
    iTmpbs = atoi(sBuf) + iPkbs;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%d", iTmpbs);
    COMP_SOFTSETXML("/tips/pkbs", sBuf)
    /* 4.���۽�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/pkje", sBuf)
    dTmpje = atof(sBuf) + dPkje;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%.2f", dTmpje);
    COMP_SOFTSETXML("/tips/pkje", sBuf)
    /* 5.�����걨���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjsbbs", sBuf)
    iTmpbs = atoi(sBuf) + iYjsbbs;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%d", iTmpbs);
    COMP_SOFTSETXML("/tips/yjsbbs", sBuf)
    /* 6.�����걨��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjsbje", sBuf)
    dTmpje = atof(sBuf) + dYjsbje;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%.2f", dTmpje);
    COMP_SOFTSETXML("/tips/yjsbje", sBuf)
    /* 7.���ɽɿ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjjkbs", sBuf)
    iTmpbs = atoi(sBuf) + iYjjkbs;
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf),"%d", iTmpbs);
    COMP_SOFTSETXML("/tips/yjjkbs", sBuf)
    /* 8.���ɽɿ��� */
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

/* ���ɸ����嵥(��ȡ���������Ļ���) */
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
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
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
        fpub_SetMsg(lXmlhandle, 24401, "�嵥�������");
        LOG(LM_STD,Fmtmsg("�嵥�������"),fpub_GetCompname(lXmlhandle))
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24402, "��ѯTIPS�����ֵ�ʧ��");
        LOG(LM_STD,Fmtmsg("��ѯTIPS�����ֵ�ʧ��"),fpub_GetCompname(lXmlhandle))
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
        fpub_SetMsg(lXmlhandle, 24402, "��ѯTIPS�����ֵ�ʧ��");
        LOG(LM_STD,Fmtmsg("��ѯTIPS�����ֵ�ʧ��"),fpub_GetCompname(lXmlhandle))
        return -402;
    }
    */
    
    /* �����ܷ��а�����������,�����������������ŷ���һ�� */
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
        fpub_SetMsg(lXmlhandle,24403, "��ѯ������ʧ��");
        LOG(LM_STD,Fmtmsg("��ѯ������ʧ��"),"ERROR");
        return -403;
    }    
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24404, "������δ��ʼ��");
        LOG(LM_STD,Fmtmsg("������[%s]δ��ʼ��", sJgdh),fpub_GetCompname(lXmlhandle))
        return -404;
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,24403, "��ѯ������ʧ��");
        LOG(LM_STD,Fmtmsg("��ѯ������ʧ��"),"ERROR");
        return -403;
    }    
    if ( SQLNOTFOUND )
    {
        fpub_SetMsg(lXmlhandle, 24404, "������δ��ʼ��");
        LOG(LM_STD,Fmtmsg("������[%s]δ��ʼ��", sJgdh),fpub_GetCompname(lXmlhandle))
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetMsg(lXmlhandle,36001, "���α�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ��cur_ksfmx_plhz�α�ʧ��"),
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
        fpub_SetMsg(lXmlhandle,24405, "���α�cur_reportʧ��");
        LOG(LM_STD,Fmtmsg("��cur_report�α�ʧ��"),"ERROR");
        return -405;
    }    
		*/
		
    /*��ʼѭ��*/
    for (i=1,iflag=0;;i++)
    {
        memset(sFJgdh, 0x00, sizeof(sFJgdh));
        memset(sJgmc, 0x00, sizeof(sJgmc));
        
        /* add dci 20141103 */
        iRet = DCIFetch(cur);
				if ( iRet < 0 )
        {  
        	iflag=-406;
        	fpub_SetMsg(lXmlhandle,24406, "��cur_report��ȡ����ʧ��");
        	LOG(LM_STD,Fmtmsg("��cur_report��ȡ����ʧ��"),"ERROR");
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
        	fpub_SetMsg(lXmlhandle,24406, "��cur_report��ȡ����ʧ��");
        	LOG(LM_STD,Fmtmsg("��cur_report��ȡ����ʧ��"),"ERROR");
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
            LOG(LM_STD,Fmtmsg("�����嵥ʧ��iflag=[%d]",iflag),"ERROR");
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
        LOG(LM_STD,Fmtmsg("�����嵥ʧ��iflag=[%d]",iflag),"ERROR");
        return iflag;
    }    
    return 0;            
}

/* ����ҵ����ͳ���嵥 */
int prv_tips_reportywl(HXMLTREE lXmlhandle, FILE *fp, int *all, double *zje, char qdlb[])
{
    char sBuf[256];
    int iRet;
    int iSkbs=0;/* ʵ�۱��� */
    double dSkje=0.00;/* ʵ�۽�� */
    int iPkbs=0;/* ���۱��� */
    double dPkje=0.00;/* ���۽�� */
    int iYjsbbs=0;/* ���ɽɿ���� */
    double dYjsbje=0.00;/* ���ɽɿ��� */
    int iYjjkbs=0;/* ���ɽɿ���� */
    double dYjjkje=0.00;/* ���ɽɿ��� */

    fprintf(fp,"                                         ʵʱ��˰               ������˰                         ���ж˽�˰                       �ϼ�\n"); 
    fprintf(fp," ��� ������      ��������            ����         ���      ����          ��� �걨����     �걨��� ���ɱ���    ���ɽ��     ����       ���\n"); 
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
         LOGRET(iRet,LM_STD,Fmtmsg("�����嵥ʧ��[%d]", iRet), fpub_GetCompname(lXmlhandle))        
    }
    /* 1.ʵ�۱��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/skbs", sBuf)
    iSkbs=atoi(sBuf);
    /* 2.ʵ�۽�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/skje", sBuf)
    dSkje=atof(sBuf);
    /* 3.���۱��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/pkbs", sBuf)
    iPkbs=atoi(sBuf);
    /* 4.���۽�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/pkje", sBuf)
    dPkje=atof(sBuf);
    /* 5.�����걨���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjsbbs", sBuf)
    iYjsbbs=atoi(sBuf);
    /* 6.�����걨��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjsbje", sBuf)
    dYjsbje=atof(sBuf);
    /* 7.���ɽɿ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjjkbs", sBuf)
    iYjjkbs=atoi(sBuf);
    /* 8.���ɽɿ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/yjjkje", sBuf)
    dYjjkje=atof(sBuf);
    fprintf(fp,"-------------------------------------------------------------------------------------------------------------------------------------------------\n");    
    fprintf(fp,"�ϼƣ�                              %5d %15.2f %5d %15.2f %5d %15.2f %5d %15.2f %5d %15.2f\n",
            iSkbs, dSkje, iPkbs, dPkje, iYjsbbs, dYjsbje, iYjjkbs, dYjjkje, (*all), (*zje));               
    return 0;    
}

/* ���ɶ��˱� */
int prv_tips_reportdzb(HXMLTREE lXmlhandle, FILE *fp, int *all, double *zje, char qdlb[])
{
    /*EXEC SQL BEGIN DECLARE SECTION;*/
        char sSql[1024];
        char sPayeeBankNo[12+1];/* �տ����к� */
        char sChkDate[8+1];/* �������� */
        char sChkAcctOrd[4+1];/* �������� */
        char sChkAcctType[1+1];/* �������� */
        int iZbs;/* �ܱ��� */
        double dZje;/* �ܽ�� */
        char sQsbz[1+1];/* �����־ */
        char sZjlsh[32+1];/* ������ˮ�� */
        char sZjrq[8+1];/* �������� */
        char sCnChkAcctType[60+1];/* ������������ */
        char sCnQsbz[60+1];/* ������������ */
    /*EXEC SQL END DECLARE SECTION;*/
    char sQsrq[8+1];/* ��ʼ���� */
    char sJzrq[8+1];/* ��ֹ���� */
    char sBuf[256];
    int iflag,i,j;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		CURSOR cur;
		/* end add dci 20141103 */	

    fprintf(fp," ���  �տ����к�   �������� �������� ��������   �ܱ���          �ܽ�� �����־  ֧���������  ֧��ί������\n"); 
     
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
  	}
  	if (DCIExecute(cur) == -1)
  	{
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
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
        fpub_SetMsg(lXmlhandle,24314, "ǰ��ϵͳ����,���α�cur_report_dzbʧ��");       
        LOGRET(-4,LM_STD,Fmtmsg("��cur_report_dzb�α�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*��ʼѭ��*/
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
        	fpub_SetMsg(lXmlhandle,24315, "ǰ��ϵͳ����:��cur_report_dzb�α��ȡ����ʧ��");
        	LOG(LM_STD,Fmtmsg("��cur_report_dzb�α��ȡ����ʧ��"),"ERROR");
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
        	fpub_SetMsg(lXmlhandle,24315, "ǰ��ϵͳ����:��cur_report_dzb�α��ȡ����ʧ��");
        	LOG(LM_STD,Fmtmsg("��cur_report_dzb�α��ȡ����ʧ��"),"ERROR");
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
        	fpub_SetMsg(lXmlhandle,24316, "��ѯ�����ֵ����ݶ�������ʧ��");
        	LOG(LM_STD,Fmtmsg("��ѯ�����ֵ����ݶ�������ʧ��"),"ERROR");
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
        	fpub_SetMsg(lXmlhandle,24316, "��ѯ�����ֵ����ݶ�������ʧ��");
        	LOG(LM_STD,Fmtmsg("��ѯ�����ֵ����ݶ�������ʧ��"),"ERROR");
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
        	fpub_SetMsg(lXmlhandle,24317, "��ѯ�����ֵ����������־ʧ��");
        	LOG(LM_STD,Fmtmsg("��ѯ�����ֵ����������־ʧ��"),"ERROR");
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
        	fpub_SetMsg(lXmlhandle,24317, "��ѯ�����ֵ����������־ʧ��");
        	LOG(LM_STD,Fmtmsg("��ѯ�����ֵ����������־ʧ��"),"ERROR");
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
        LOGRET(-5,LM_STD,Fmtmsg("�����嵥ʧ��iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    
    fprintf(fp,"------------------------------------------------------------------------------------------------------------\n");           
    return COMPRET_SUCC;    
}

/* �����ʽ�������� */
int prv_tips_reportzjqshz(HXMLTREE lXmlhandle, FILE *fp, int *all, double *zje, char qdlb[])
{
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         int iZpc0=0;/* �ռ������� */
         int iZbs0=0;/* �ռ��ܱ��� */
         double dZje0=0.00;/* �ռ��ܽ�� */
         int iQsbs0=0;/* �ռ�������� */
         double dQsje0=0.00;/* �ռ������� */
         int iFQsbs0=0;/* �ռ�δ������� */
         double dFQsje0=0.00;/* �ռ�δ������ */
         int iZpc1=0;/* ���������� */
         int iZbs1=0;/* �����ܱ��� */
         double dZje1=0.00;/* �����ܽ�� */
         int iQsbs1=0;/* ����������� */
         double dQsje1=0.00;/* ���������� */
         int iFQsbs1=0;/* ����δ������� */
         double dFQsje1=0.00;/* ����δ������ */
         char sChkDate[8+1];/* �������� */
         char sChkDate2[8+1];/* �������� */
    /*EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    int iRet;
    
    char cZbs0[8+1];/* �ռ��ܱ��� */
    char cZje0[32+1];/* �ռ��ܽ�� */
    char cQsbs0[8+1];/* �ռ�������� */
    char cQsje0[32+1];/* �ռ������� */
    char cFQsbs0[8+1];/*�ռ�δ������� */
    char cFQsje0[32+1];/* �ռ�δ������ */
    
    char cZbs1[8+1];/*�����ܱ��� */
    char cZje1[32+1];/* �����ܽ�� */
    char cQsbs1[8+1];/*����������� */
    char cQsje1[32+1];/* ���������� */
    char cFQsbs1[8+1];/*����δ������� */
    char cFQsje1[32+1];/* ����δ������ */  
    
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		CURSOR cur;

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sChkDate, 0x00, sizeof(sChkDate));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(sChkDate, sBuf, sizeof(sChkDate));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sChkDate2, 0x00, sizeof(sChkDate2));
    COMP_SOFTGETXML("/tips/jzrq", sBuf)
    pstrcopy(sChkDate2, sBuf, sizeof(sChkDate2));

    LOG(LM_STD,Fmtmsg("�����ʽ�������ܿ�ʼ���� ��ѯ����[%s]--[%s]", 
        sChkDate, sChkDate2),fpub_GetCompname(lXmlhandle)) 
    
    fprintf(fp,"�������� ������   �ܱ���          �ܽ�� �������        ������ δ�������      δ������\n"); 

    /* ��ѯ�ռ������� */
    iZpc0=0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_sszjhhls \
    	 where chkdate <= '%s' AND chkdate >= '%s' AND chkaccttype = '0'",sChkDate2,sChkDate);     	
    iRet = DBSelectToVar(sErrmsg, &iZpc0, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("��ѯ�ռ������γ���"));
        LOG(LM_STD,Fmtmsg("��ѯ�ռ������γ���"),fpub_GetCompname(lXmlhandle)) 
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
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("��ѯ�ռ������γ���"));
        LOG(LM_STD,Fmtmsg("��ѯ�ռ������γ���"),fpub_GetCompname(lXmlhandle)) 
        return -71;
    }
    */
    /* ��ѯ�ռ��ܱ���,�ܽ�� */
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24272, Fmtmsg("��ѯ�ռ��ܱ����ܽ�����"));
        LOG(LM_STD,Fmtmsg("��ѯ�ռ��ܱ����ܽ�����"),fpub_GetCompname(lXmlhandle)) 
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
        fpub_SetMsg(lXmlhandle, 24272, Fmtmsg("��ѯ�ռ��ܱ����ܽ�����"));
        LOG(LM_STD,Fmtmsg("��ѯ�ռ��ܱ����ܽ�����"),fpub_GetCompname(lXmlhandle)) 
        return -72;
    }
    */
    /* ��ѯ�ռ��������,������ */
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24273, Fmtmsg("��ѯ�ռ�������������������"));
        LOG(LM_STD,Fmtmsg("��ѯ�ռ�������������������"),fpub_GetCompname(lXmlhandle)) 
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
        fpub_SetMsg(lXmlhandle, 24273, Fmtmsg("��ѯ�ռ�������������������"));
        LOG(LM_STD,Fmtmsg("��ѯ�ռ�������������������"),fpub_GetCompname(lXmlhandle)) 
        return -73;
    }
    */                   

    /* ��ѯ�ռ�δ�������,δ������ */
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24274, Fmtmsg("��ѯ�ռ�δ���������δ���������"));
        LOG(LM_STD,Fmtmsg("��ѯ�ռ�δ���������δ���������"),fpub_GetCompname(lXmlhandle)) 
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
        fpub_SetMsg(lXmlhandle, 24274, Fmtmsg("��ѯ�ռ�δ���������δ���������"));
        LOG(LM_STD,Fmtmsg("��ѯ�ռ�δ���������δ���������"),fpub_GetCompname(lXmlhandle)) 
        return -74;
    }
    */

    fprintf(fp,"�ռ� %8d   %8d %15.2f %8d %15.2f   %8d %15.2f\n",
            iZpc0, iZbs0, dZje0, iQsbs0, dQsje0, iFQsbs0, dFQsje0);

    /* ��ѯ���������� */
    iZpc1=0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_sszjhhls \
    	 where chkdate <= '%s' AND chkdate >= '%s' AND chkaccttype = '0'",sChkDate2,sChkDate);     	
    iRet = DBSelectToVar(sErrmsg, &iZpc1, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("��ѯ���������γ���"));
        LOG(LM_STD,Fmtmsg("��ѯ���������γ���"),fpub_GetCompname(lXmlhandle)) 
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
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("��ѯ���������γ���"));
        LOG(LM_STD,Fmtmsg("��ѯ���������γ���"),fpub_GetCompname(lXmlhandle)) 
        return -75;
    }
    */
    /* ��ѯ�����ܱ���,�ܽ�� */
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24276, Fmtmsg("��ѯ�����ܱ����ܽ�����"));
        LOG(LM_STD,Fmtmsg("��ѯ�����ܱ����ܽ�����"),fpub_GetCompname(lXmlhandle)) 
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
        fpub_SetMsg(lXmlhandle, 24276, Fmtmsg("��ѯ�����ܱ����ܽ�����"));
        LOG(LM_STD,Fmtmsg("��ѯ�����ܱ����ܽ�����"),fpub_GetCompname(lXmlhandle)) 
        return -76;
    }
    */
    
    /* ��ѯ�����������,������ */
    
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24277, Fmtmsg("��ѯ�ռ�������������������"));
        LOG(LM_STD,Fmtmsg("��ѯ�ռ�������������������"),fpub_GetCompname(lXmlhandle)) 
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
        fpub_SetMsg(lXmlhandle, 24277, Fmtmsg("��ѯ�ռ�������������������"));
        LOG(LM_STD,Fmtmsg("��ѯ�ռ�������������������"),fpub_GetCompname(lXmlhandle)) 
        return -77;
    }   
    */                

    /* ��ѯ����δ�������,δ������ */
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24278, Fmtmsg("��ѯ����δ���������δ���������"));
        LOG(LM_STD,Fmtmsg("��ѯ����δ���������δ���������"),fpub_GetCompname(lXmlhandle)) 
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
        fpub_SetMsg(lXmlhandle, 24278, Fmtmsg("��ѯ����δ���������δ���������"));
        LOG(LM_STD,Fmtmsg("��ѯ����δ���������δ���������"),fpub_GetCompname(lXmlhandle)) 
        return -78;
    }
    */

    fprintf(fp,"���� %8d   %8d %15.2f %8d %15.2f   %8d %15.2f\n",
            iZpc1, iZbs1, dZje1, iQsbs1, dQsje1, iFQsbs1, dFQsje1);

    fprintf(fp,"--------------------------------------------------------------------------------------------\n");    
    fprintf(fp,"�ϼ� %8d   %8d %15.2f %8d %15.2f   %8d %15.2f\n",
            iZpc0+iZpc1, iZbs0+iZbs1, dZje0+dZje1, 
            iQsbs0+iQsbs1, dQsje0+dQsje1, iFQsbs0+iFQsbs1, dFQsje0+dFQsje1);
    (*all) = iZbs0 + iZbs1;
    (*zje) = dZje0 + dZje1;            
    return 0;    
}

/* �������ջ��ؿ�˰�쳣ҵ����ܱ�*/
int prv_tips_reportswychz(HXMLTREE lXmlhandle, FILE *fp, int *all, double *zje, char qdlb[])
{   
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sSql[1024]; 
         char sTableName[32+1];
         char sQsrq[8+1];/* ��ʼ���� */
         char sJzrq[8+1];/* �������� */
         char sPayeeBankNo[12+1];/* �տ����к� */
         char sDqdh[10+1];/* �������� */
         char sJgdh[10+1];/* �������� */
         int iZbs;/* �ܱ��� */
         double dZje;/* �ܽ�� */  
    /*EXEC SQL END DECLARE SECTION;*/    
    char sBuf[256];
    char zwrq[8+1];
    int  qzlsh;
    int i,iFlag;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
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
        
    /* ƴ�ӱ��� */
    memset(sTableName, 0x00, sizeof(sTableName));
    snprintf(sTableName, sizeof(sTableName), "tmp_%s%08d", zwrq, qzlsh);
    
    /* ɾ����ʱ�� */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "drop table %s ", sTableName); 
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        LOG(LM_STD,Fmtmsg("ɾ����ʱ��ʧ��"),sSql);
        return -1;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    */

    /* ������ʱ�� */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "create table %s (payeebankno char(12), dqdh char(10), jgdh char(10), zbs integer, zje decimal(15,2))", sTableName); 
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle,24801,"������ʱ�쳣ҵ����ܱ�ʧ��");
    	LOG(LM_STD,Fmtmsg("������ʱ�쳣ҵ����ܱ�ʧ��SQL"),sSql);
    	return -81;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if(SQLERR)
    {
        fpub_SetMsg(lXmlhandle,24801,"������ʱ�쳣ҵ����ܱ�ʧ��");
    	LOG(LM_STD,Fmtmsg("������ʱ�쳣ҵ����ܱ�ʧ��SQL"),sSql);
    	return -81;
    }
    */
    
    LOG(LM_STD,Fmtmsg("������ʱ����ǼǱ�ɹ�[%s]",sTableName),"INFO");       
    
    /* ����������ˮ�����ݲ�����մ�������ʱ�� */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "insert into %s select payeebankno, dqdh, jgdh, count(*) as zbs, sum(jyje) as zje from tips_drls where zwrq <= '%s' and zwrq >= '%s' and msgno = '3001' and jyzt <> '0' group by payeebankno, dqdh, jgdh ", sTableName, sJzrq, sQsrq);
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24802, "��������ˮ�����ݵ�����ʱ��ʧ��");
    	LOG(LM_STD,Fmtmsg("��������ˮ�����ݵ�����ʱ��ʧ��"),sSql);
    	return -82;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if(SQLERR)
    {
        fpub_SetMsg(lXmlhandle, 24802, "��������ˮ�����ݵ�����ʱ��ʧ��");
    	LOG(LM_STD,Fmtmsg("��������ˮ�����ݵ�����ʱ��ʧ��"),sSql);
    	return -82;
    }
    */
    
    /* ������ʷ��ˮ�����ݲ�����մ�������ʱ�� */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "insert into %s select payeebankno, dqdh, jgdh, count(*) as zbs, sum(jyje) as zje from tips_lsls \
    	where zwrq <= '%s' and zwrq >= '%s' and msgno = '3001' and jyzt <> '0' group by payeebankno, dqdh, jgdh ", sTableName, sJzrq, sQsrq);
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle,24803, "����ʷ��ˮ�����ݵ�����ʱ��ʧ��");
    	LOG(LM_STD,Fmtmsg("����ʷ��ˮ�����ݵ�����ʱ��ʧ��"),sSql);
    	return -83;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if(SQLERR)
    {
        fpub_SetMsg(lXmlhandle,24803, "����ʷ��ˮ�����ݵ�����ʱ��ʧ��");
    	LOG(LM_STD,Fmtmsg("����ʷ��ˮ�����ݵ�����ʱ��ʧ��"),sSql);
    	return -83;
    }

    /* ����������˰����ϸ�����ݲ�����մ�������ʱ�� */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "insert into %s select payeebankno, dqdh, jgdh, count(*) as zbs, sum(jyje) as zje from tips_ssplksfmx \
    	where zwrq <= '%s' and zwrq >= '%s' and czbd <> '7' group by payeebankno, dqdh, jgdh ", sTableName, sJzrq, sQsrq);
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle,24804,"��������˰����ϸ�����ݵ�����ʱ��ʧ��");
    	LOG(LM_STD,Fmtmsg("��������˰����ϸ�����ݵ�����ʱ��ʧ��"),sSql);
    	return -84;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if(SQLERR)
    {
        fpub_SetMsg(lXmlhandle,24804,"��������˰����ϸ�����ݵ�����ʱ��ʧ��");
    	LOG(LM_STD,Fmtmsg("��������˰����ϸ�����ݵ�����ʱ��ʧ��"),sSql);
    	return -84;
    }

    /* ����������˰����ϸ��ʷ�����ݲ�����մ�������ʱ�� */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "insert into %s select payeebankno, dqdh, jgdh, count(*) as zbs,sum(jyje) as zje from tips_ssplksfmx_ls \
    	where zwrq <= '%s' and zwrq >= '%s' and czbd <> '7' group by payeebankno, dqdh, jgdh ", sTableName, sJzrq, sQsrq);
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    
    /* add dci 20141103 */    
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle,24805,"��������˰����ϸ�����ݵ�����ʱ��ʧ��");
    	LOG(LM_STD,Fmtmsg("��������˰����ϸ�����ݵ�����ʱ��ʧ��"),sSql);
    	return -85;
        
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL execute immediate :sSql;    
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if(SQLERR)
    {
        fpub_SetMsg(lXmlhandle,24805,"��������˰����ϸ�����ݵ�����ʱ��ʧ��");
    	LOG(LM_STD,Fmtmsg("��������˰����ϸ�����ݵ�����ʱ��ʧ��"),sSql);
    	return -85;
    }*/

    /* �����α꣬��ʼ����ʱ����ȡ���� */
    /* add dci 20141103 */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "select payeebankno, dqdh, jgdh, sum(zbs) as zbs, sum(zje)\
    	from %s group by payeebankno, dqdh, jgdh order by payeebankno, dqdh, jgdh ", sTableName);
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
     if ((cur_ycywhz = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur_ycywhz) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur_ycywhz);
        fpub_SetMsg(lXmlhandle,24806,"���α�cur_ycywhzʧ��");
    		LOG(LM_STD,Fmtmsg("���α�cur_ycywhzʧ��"),sSql);
    		return -86;
    }
 	 
    fprintf(fp, "���    �����         ������     ����            ���    \n");  
    
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
					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")

					iFlag=-87;
        	LOG(LM_STD,Fmtmsg("��cur_ycywhz�α��ȡ����ʧ��"),"ERROR");
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
    /* ɾ����ʱ�� */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "drop table %s ", sTableName); 
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    iRet = DCIExecuteDirect(sSql);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle,24807,"�������ջ��ؿ�˰�쳣ҵ����ܱ�");
    		LOG(LM_STD,Fmtmsg("�������ջ��ؿ�˰�쳣ҵ����ܱ�[%d]", iFlag),"ERROR");
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
        fpub_SetMsg(lXmlhandle,24806,"���α�cur_ycywhzʧ��");
    	LOG(LM_STD,Fmtmsg("���α�cur_ycywhzʧ��"),sSql);
    	return -86;
    }
    fprintf(fp, "���    �����         ������     ����            ���    \n");    
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
        	LOG(LM_STD,Fmtmsg("��cur_ycywhz�α��ȡ����ʧ��"),"ERROR");
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
    /* ɾ����ʱ�� 
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql, sizeof(sSql), "drop table %s ", sTableName); 
    LOG(LM_DEBUG,Fmtmsg("%s", sSql),"DEBUG");
    EXEC SQL execute immediate :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_ERROR,sqlca.sqlcode),sSql);
    if (iFlag < 0)
    {
        fpub_SetMsg(lXmlhandle,24807,"�������ջ��ؿ�˰�쳣ҵ����ܱ�");
    	LOG(LM_STD,Fmtmsg("�������ջ��ؿ�˰�쳣ҵ����ܱ�[%d]", iFlag),"ERROR");
    	return iFlag;
    }*/
    
    return COMPRET_SUCC;              
}
  
/************************************************************************
��̬�����������
�����������: SYW_TIPS_REPORT
�������: ���ɸ����嵥
�������: 
  ���ɸ����嵥
  �嵥���:
  01-�����嵥
  02-�����쳣�嵥
  03-�����嵥
  04-�����쳣�嵥
  05-ҵ����ͳ�Ʊ�
  06-�����嵥
  07-�ʽ���������嵥
  08-˰���˰�쳣���ܱ�
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
������ˮ	tips_drls
��ʷ��ˮ    tips_lsls
������˰����ϸ tips_ssplksfmx
������˰����ʷ��ϸ tips_ssplksfmx_ls

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��12��10��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_REPORT(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sBankName[60+1];/* ���� */
         char sReportName[60+1];/* �������� */
         int iQdlb;   
    /*EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    char sQdlb[2+1];/* �嵥��� */
    char sQdFile[256];/* �嵥�ļ��� */
    char sSysDate[8+1];
    char sQsrq[8+1];
    char sJzrq[8+1];
    int iAll=0;
    double dZje=0.00;
    
    FILE *fp;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		CURSOR cur;
		/* end add dci 20141103 */	
            
    fpub_InitSoComp(lXmlhandle); 
    
    COMP_PARACOUNTCHK(2);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQdlb, 0x00, sizeof(sQdlb));
    COMP_GETPARSEPARAS(1, sBuf, "�嵥���")
    pstrcopy(sQdlb, sBuf, sizeof(sQdlb));
    trim(sQdlb);

    memset(sQdFile, 0x00, sizeof(sQdFile));
    COMP_GETPARSEPARAS(2, sBuf, "�嵥�ļ���")
    pstrcopy(sQdFile, sBuf, sizeof(sQdFile));
    trim(sQdFile);
    
    LOG(LM_STD,Fmtmsg("���ɸ����嵥...�嵥���[%s],�嵥�ļ���[%s]", sQdlb, sQdFile), fpub_GetCompname(lXmlhandle))        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSysDate, 0x00, sizeof(sSysDate));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(sSysDate, sBuf, sizeof(sSysDate));

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQsrq, 0x00, sizeof(sQsrq));
    COMP_SOFTGETXML("/tips/qsrq", sBuf)
    pstrcopy(sQsrq, sBuf, sizeof(sQsrq));
    if ( sQsrq[0] == '\0')/* add by tuql 20091224 ���Ӷ���ʼ���ڼ���ֹ���ڷǿ��ж�*/
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("��ʼ���ڲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("��ʼ���ڲ���Ϊ��, qsrq=[%s]", sQsrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sJzrq, 0x00, sizeof(sJzrq));
    COMP_SOFTGETXML("/tips/jzrq", sBuf)
    pstrcopy(sJzrq, sBuf, sizeof(sJzrq));
    if ( sJzrq[0] == '\0')/* add by tuql 20091224 ���Ӷ���ʼ���ڼ���ֹ���ڷǿ��ж�*/
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24276, Fmtmsg("��ֹ���ڲ���Ϊ��"));
        LOG(LM_STD,Fmtmsg("��ֹ���ڲ���Ϊ��, jzrq=[%s]", sJzrq),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }
    
    /* add dci 20141103 */
    memset(sBankName, 0x00, sizeof(sBankName));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select bankname from tips_nbcsb WHERE 1=1");     	
    iRet = DBSelectToVar(sErrmsg, &sBankName, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24501, "��ѯ�ڲ�������ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ�ڲ�������ʧ��"), fpub_GetCompname(lXmlhandle))
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
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24501, "��ѯ�ڲ�������ʧ��");
        fpub_SetMsg(lXmlhandle, 24502, "��ѯ�����ֵ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ�����ֵ�ʧ��"), fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;        
    }    
    if ( iRet == 0)
    {
         fpub_SetMsg(lXmlhandle, 24503, "�嵥����δ��ʼ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�嵥����δ��ʼ��"), fpub_GetCompname(lXmlhandle))        
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
         fpub_SetMsg(lXmlhandle, 24501, "��ѯ�ڲ�������ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ�ڲ�������ʧ��"), fpub_GetCompname(lXmlhandle))
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
         fpub_SetMsg(lXmlhandle, 24502, "��ѯ�����ֵ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ�����ֵ�ʧ��"), fpub_GetCompname(lXmlhandle))
    }
    if (SQLNOTFOUND)
    {
         fpub_SetMsg(lXmlhandle, 24503, "�嵥����δ��ʼ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�嵥����δ��ʼ��"), fpub_GetCompname(lXmlhandle))        
    } 
                
    trim(sReportName);
    
    */
    
    fp = fopen(sQdFile,"w");
    if ( fp == NULL )
    {
         fpub_SetMsg(lXmlhandle, 24504, "���嵥�ļ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���嵥�ļ�ʧ��[%s]", 
             strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
    fprintf(fp,"         %s��������ϵͳ%s\n", sBankName, sReportName);
    fprintf(fp,"         ��ѯ����:%s-%s      ��ӡ����:%s\n", sQsrq, sJzrq, sSysDate);
    
    iRet=-1;
    iAll=0;/* add by tuql 20100108 */
    dZje=0.00;/* add by tuql 20100108 */
    switch(iQdlb)
    {
        case 1:/* 01-�����嵥 */
        case 2:/* 02-�����쳣�嵥 */
        case 3:/* 03-�����嵥 */
        case 4:/* 04-�����쳣�嵥 */    
            iRet = prv_tips_report(lXmlhandle, fp, &iAll, &dZje, sQdlb);
            fprintf(fp,"�ܼƱ���:%d     ���:%.2f\n", iAll, dZje);
            if ( iAll < 1 )
            {    
                fpub_SetMsg(lXmlhandle, 24505, "�û���������������������");
                LOG(LM_STD,Fmtmsg("�û���������������������"), fpub_GetCompname(lXmlhandle));             
                iRet=-505;
            }    
            break;
        case 5:                       
            iRet = prv_tips_reportywl(lXmlhandle, fp, &iAll, &dZje, sQdlb); 
            if ( iAll < 1 )
            {    
                fpub_SetMsg(lXmlhandle, 24506, "�û���������������������");
                LOG(LM_STD,Fmtmsg("�û���������������������"), fpub_GetCompname(lXmlhandle));             
                iRet=-506;
            }            
            break;
        case 6:                       
            iRet = prv_tips_reportdzb(lXmlhandle, fp, &iAll, &dZje, sQdlb); 
            fprintf(fp,"�ܼƱ���:%d     ���:%.2f\n", iAll, dZje);
            if ( iAll < 1 )
            {    
                fpub_SetMsg(lXmlhandle, 24507, "��ѯ������������");
                LOG(LM_STD,Fmtmsg("��ѯ������������"), fpub_GetCompname(lXmlhandle));             
                iRet=-507;
            }            
            break;
        case 7:                       
            iRet = prv_tips_reportzjqshz(lXmlhandle, fp, &iAll, &dZje, sQdlb); 
            if ( iAll < 1 )
            {    
                fpub_SetMsg(lXmlhandle, 24508, "��ѯ������������");
                LOG(LM_STD,Fmtmsg("��ѯ������������"), fpub_GetCompname(lXmlhandle));             
                iRet=-508;
            }            
            break;
        case 8:                       
            iRet = prv_tips_reportswychz(lXmlhandle, fp, &iAll, &dZje, sQdlb); 
            fprintf(fp,"�ܼƱ���:%d     ���:%.2f\n", iAll, dZje);
            if ( iAll < 1 )
            {    
                fpub_SetMsg(lXmlhandle, 24509, "��ѯ������������");
                LOG(LM_STD,Fmtmsg("��ѯ������������"), fpub_GetCompname(lXmlhandle));             
                iRet=-509;
            }            
            break;
        default:
            fpub_SetMsg(lXmlhandle, 24510, "�嵥�������");
            LOG(LM_STD,Fmtmsg("�嵥�������[%s]", sQdlb), fpub_GetCompname(lXmlhandle)) 
            iRet=-510;       
            break; 
    }
    fclose(fp);
    if ( iRet < 0 )
    {
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����嵥ʧ��[%d]", iRet), fpub_GetCompname(lXmlhandle))        
    }
        
    fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "�����嵥�ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�����嵥�ɹ�"), fpub_GetCompname(lXmlhandle));             
    return COMPRET_SUCC;                    
}
