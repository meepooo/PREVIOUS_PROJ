/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V3.0.00
����ϵͳ:AIX5.3
�ļ�����:SYW_TIPS_BATCH.ec
�ļ�����:TIPS��������
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
/* mod dci 20141103 
EXEC SQL INCLUDE  "gaps_head.eh";
EXEC SQL INCLUDE  "../eh/tips_pljydj.eh";�������׵ǼǱ�
EXEC SQL INCLUDE  "../eh/tips_ssplpcdj.eh";˰���������εǼǱ�
EXEC SQL INCLUDE  "../eh/tips_ssplksfmx.eh";˰��������˰����ϸ��
EXEC SQL INCLUDE  "../eh/tips_ssplzfksf.eh";˰������ֹ����˰�ѱ�
EXEC SQL INCLUDE  "../eh/tips_pzsj.eh";ƾ֤���ݱ�
*/

/* add dci 20141103 */
#include "../eh/tips_pljydj.h"/*�������׵ǼǱ� */
#include "../eh/tips_ssplpcdj.h"/*˰���������εǼǱ� */
#include "../eh/tips_ssplksfmx.h"/*˰��������˰����ϸ�� */
#include "../eh/tips_ssplzfksf.h"/*˰������ֹ����˰�ѱ� */
#include "../eh/tips_pzsj.h"/*ƾ֤���ݱ� */
#include "../eh/DRC/tips_taxtypemx_drc.h"/* ˰����ϸ�� */
/* end add dci 20141103 */

#define SQLNOTFOUND_TIPS ( \
                (sqlca.sqlcode == 100) \
             || (sqlca.sqlcode == 1403) \
             || (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0) \
             )

#define FILE_BEGIN "BEGIN"
#define FILE_END "END"

#ifndef __TIPS_GENFILE_
#define __TIPS_GENFILE_
typedef struct TDB_GENFILE
{
    HXMLTREE lXmlhandle ;        /* ȫ��XML����� */
    char zwrq[8+1] ;            /* �������� */
    char pljylsh[8+1] ;          /* ����������ˮ�� */
    char plpch[5+1] ;         /* �������κ� */
    char resicxp[30+1];        /* ICXP�������� */
    FILE *fp;                    /* �ļ�ָ�� */
}SDB_GENFILE;
#endif

/* �Ǽ�ƾ֤��Ϣ */
/* 2014��12��20��DCI���� */
int prv_tips_InitPZSJ_pl(HXMLTREE lXmlhandle, SDB_TIPS_SSPLKSFMX stPlksfmx)
{
		/* add dci 20141103 
    EXEC SQL BEGIN DECLARE SECTION;
         SDB_TIPS_PZSJ stPzsj;
    EXEC SQL END DECLARE SECTION;
    */
    
    /* add DCI 20141103 */
    char sBuf[256];/* ��ʱ���� */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		SDB_TIPS_PZSJ stPzsj;
		SDB_TIPS_PLJYDJ stPljydj;
		int iRet=0;
/* end add dci 20141103 */
        
    /* ��ѯ�������׵ǼǱ���Ϣ */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_pljydj\
    	 where zwrq='%s' and pljylsh='%s'",stPlksfmx.zwrq, stPlksfmx.pljylsh);     
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))       
    iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj);
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24279, "initPlksfmx��ѯ�������׵ǼǱ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    /* end add dci 20141103 */
    
    
    memset(&stPzsj, 0x00, sizeof(stPzsj));
    
    pstrcopy(stPzsj.zwrq, stPlksfmx.zwrq, sizeof(stPzsj.zwrq));
    stPzsj.zhqzlsh = stPlksfmx.plmxxh;
    pstrcopy(stPzsj.jyrq, stPlksfmx.workdate, sizeof(stPzsj.jyrq));
    pstrcopy(stPzsj.dqdh, stPlksfmx.dqdh, sizeof(stPzsj.dqdh));
    pstrcopy(stPzsj.jgdh, stPlksfmx.jgdh, sizeof(stPzsj.jgdh));
    pstrcopy(stPzsj.jygy, stPlksfmx.jygy, sizeof(stPzsj.jygy));
    pstrcopy(stPzsj.zddh, stPlksfmx.zddh, sizeof(stPzsj.zddh));
    pstrcopy(stPzsj.msgno, "3102", sizeof(stPzsj.msgno));/* ���ı�� */
    pstrcopy(stPzsj.entrustdate, stPlksfmx.entrustdate, sizeof(stPzsj.entrustdate));
    pstrcopy(stPzsj.taxorgcode, stPlksfmx.taxorgcode, sizeof(stPzsj.taxorgcode));
    pstrcopy(stPzsj.packno, stPlksfmx.packno, sizeof(stPzsj.packno));
    pstrcopy(stPzsj.trano, stPlksfmx.trano, sizeof(stPzsj.trano));
    pstrcopy(stPzsj.payeebankno, stPlksfmx.payeebankno, sizeof(stPzsj.payeebankno));
    pstrcopy(stPzsj.payeename, stPljydj.payeename, sizeof(stPzsj.payeename));
    
    pstrcopy(stPzsj.paybkcode, stPlksfmx.paybkcode, sizeof(stPzsj.paybkcode));
    pstrcopy(stPzsj.payopbkcode, stPlksfmx.payopbkcode, sizeof(stPzsj.payopbkcode));
    pstrcopy(stPzsj.payacct, stPlksfmx.payacct, sizeof(stPzsj.payacct));
    pstrcopy(stPzsj.handorgname, stPlksfmx.handorgname, sizeof(stPzsj.handorgname));
    stPzsj.jyje=stPlksfmx.jyje;
    pstrcopy(stPzsj.corpcode, "", sizeof(stPzsj.corpcode));
    pstrcopy(stPzsj.taxvouno, stPlksfmx.taxvouno, sizeof(stPzsj.taxvouno));
    pstrcopy(stPzsj.taxpaycode, stPlksfmx.taxpaycode, sizeof(stPzsj.taxpaycode));
    stPzsj.pzlx[0]='1';
    stPzsj.dycs=0;
    stPzsj.dzbz[0]='0';
    pstrcopy(stPzsj.pzsjwjm, stPlksfmx.spxx, sizeof(stPzsj.pzsjwjm));
    /* add by lijn 20140825 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyqd", sBuf)
    pstrcopy(stPzsj.jyqd, sBuf, sizeof(stPzsj.jyqd));
    pstrcopy(stPzsj.zjrq      , stPlksfmx.zjrq      , sizeof(stPzsj.zjrq      ));
    pstrcopy(stPzsj.zjsj      , stPlksfmx.zjsj      , sizeof(stPzsj.zjsj      ));
    pstrcopy(stPzsj.zjlsh     , stPlksfmx.zjlsh     , sizeof(stPzsj.zjlsh     ));
    if(strcmp(stPlksfmx.czbd,"7")==0)
    	pstrcopy(stPzsj.jyzt      , "0"      , sizeof(stPzsj.jyzt      ));
    else
    	pstrcopy(stPzsj.jyzt      , "1"      , sizeof(stPzsj.jyzt      ));
    stPzsj.hxdzbz[0]='0';
    pstrcopy(stPzsj.qsbz      , stPlksfmx.qsbz      , sizeof(stPzsj.qsbz      ));
    pstrcopy(stPzsj.taxpayname, stPlksfmx.taxpayname, sizeof(stPzsj.taxpayname));
    pstrcopy(stPzsj.qspch			, ""			, sizeof(stPzsj.qspch			));
    pstrcopy(stPzsj.chkdate   , stPlksfmx.chkdate   , sizeof(stPzsj.chkdate   ));
    pstrcopy(stPzsj.chkacctord, stPlksfmx.chkacctord, sizeof(stPzsj.chkacctord));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/req/khjg",sBuf)       
    pstrcopy(stPzsj.opbankno   , sBuf   , sizeof(stPzsj.opbankno   ));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/req/khjgmc",sBuf) 
    pstrcopy(stPzsj.opbankname,  sBuf   , sizeof(stPzsj.opbankname));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/req/khh",sBuf) 
    pstrcopy(stPzsj.khh,  sBuf   , sizeof(stPzsj.khh));
    
    prv_get_dxje(stPzsj.jyje,sBuf);
    pstrcopy(stPzsj.chjyje,  sBuf   , sizeof(stPzsj.chjyje));
    /* add by lijn 20140825 */
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_pzsj", SD_TIPS_PZSJ, NUMELE(SD_TIPS_PZSJ), &stPzsj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	/* DCIRollback();   */
    	
    	LOG(LM_STD,Fmtmsg("����ƾ֤��Ϣʧ��,szwrq[%s], zhqzlsh=[%d]",stPzsj.zwrq, stPzsj.zhqzlsh),"ERROR")        
        return -1;
    }
    /* end dci 20141103 */
    /* mod dci 20141103 
    EXEC SQL INSERT INTO tips_pzsj VALUES(:stPzsj);
    if ( SQLERR )
    {
        LOG(LM_STD,Fmtmsg("����ƾ֤��Ϣʧ��,szwrq[%s], zhqzlsh=[%d]",stPzsj.zwrq, stPzsj.zhqzlsh),"ERROR")        
        return -1;
    }
    */
    LOG(LM_STD,Fmtmsg("����ƾ֤��Ϣ�ɹ�,szwrq[%s], zhqzlsh=[%d]",stPzsj.zwrq, stPzsj.zhqzlsh),"INFO")      
    return 0;    
    
}

/*
 *   ί�й�ϵУ�� mod by tuql 20090909 У��ͨ���󷵻ص������ż��������� 
 */
int prv_tips_ChkWtgx(char *prono, char *payacct, char *taxpaycode, char *dqdh, char *jgdh, char *payopbkcode/* add by sunpj 20090909 */,char *payacct2/* add by liurj 20180713 */)
{
	/* add dci 20141103 
EXEC SQL BEGIN DECLARE SECTION;*/
	   char sProtocolNo[60+1];
	   char sPayAcct[32+1];
	   char sWtgxzt[1+1];
	   char sYzbz[1+1];
	   char sTaxPayCode[20+1];
	   char sDqdh[10+1];/* add by tuql 20090909 */
	   char sJgdh[10+1];/* add by tuql 20090909 */	   
	   char sPayOpBkCode[12+1];/* add by sunpj 20090909 */	
	   char sPayAcct2[32+1]; /* add by liurj 20180713 */
	/* add dci 20141103 
EXEC SQL END DECLARE SECTION;*/
	
		/* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */
	
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    pstrcopy(sProtocolNo, prono, sizeof(sProtocolNo));/* Э����� */
    pstrcopy(sPayAcct, payacct, sizeof(sPayAcct));/* �������˺� */
    trim(sProtocolNo);trim(sPayAcct);
    
    memset(sWtgxzt, 0x00, sizeof(sWtgxzt));
    memset(sYzbz, 0x00, sizeof(sYzbz));
    memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
    memset(sDqdh, 0x00, sizeof(sDqdh));
    memset(sJgdh, 0x00, sizeof(sJgdh));
	memset(sPayOpBkCode, 0x00, sizeof(sPayOpBkCode));
	memset(sPayAcct2, 0x00, sizeof(sPayAcct2));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
	snprintf( sSql1, sizeof(sSql1), "select wtgxzt, yzbz, taxpaycode, djdqdh, djjgdh, payopbkcode, payacct2 FROM tips_wtgxdj\
	WHERE protocolno ='%s' AND payacct ='%s'",sProtocolNo,sPayAcct);
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")        
		iRet = DBSelectToMultiVar(sErrmsg, sSql1, &sWtgxzt, &sYzbz, &sTaxPayCode, &sDqdh, &sJgdh, &sPayOpBkCode, &sPayAcct2);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        LOG(LM_STD,Fmtmsg("��ѯί�й�ϵʧ��protocolno[%s], payacct[%s]", sProtocolNo, sPayAcct),"INFO")
     		return -1;	
        
    }
    if ( iRet == 0 )
    {
        /*��ϵδ�ҵ�,�����ش�  */
     	return 1;
    }


    /* end dci 20141103 */
    /* mod dci 20141103 
    EXEC SQL SELECT wtgxzt, yzbz, taxpaycode, djdqdh, djjgdh 
         INTO :sWtgxzt, :sYzbz, :sTaxPayCode, :sDqdh, :sJgdh
         FROM tips_wtgxdj
         WHERE  protocolno = :sProtocolNo
           AND  payacct = :sPayAcct;        
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");     
    if ( SQLERR )
    {        
    	LOG(LM_STD,Fmtmsg("��ѯί�й�ϵʧ��protocolno[%s], payacct[%s]", sProtocolNo, sPayAcct),"INFO")
     	return -1;
    }
    if ( SQLNOTFOUND_TIPS )
    {     
        /*��ϵδ�ҵ�,�����ش�  
     	return 1;
    }
    */
  
    if(sWtgxzt[0]!='0')	  		
    {
        /*ί�й�ϵ�쳣*/  
        return 2;
    }

    if(sYzbz[0]!='1')	  		
    {
        /*��ϵδ��֤*/  
        return 3;
    }
    trim(sTaxPayCode);
    /* Linuxϵͳ����Ϊsizeof(taxpaycode), ���ܴ��� */
    pstrcopy(taxpaycode, sTaxPayCode, sizeof(sTaxPayCode));
    trim(sDqdh);
    trim(sJgdh);
    pstrcopy(dqdh, sDqdh, sizeof(sDqdh));
    pstrcopy(jgdh, sJgdh, sizeof(sJgdh));
	pstrcopy(payopbkcode, sPayOpBkCode, sizeof(sPayOpBkCode));
	pstrcopy(payacct2,sPayAcct2,sizeof(sPayAcct2));
    return 0;	
}	

/* �ѻ�ȡ�������ļ���Ϣ�ŵ�XML���� */
int prv_tips_PutKsfmxToXml(HXMLTREE lXmlhandle, SDB_TIPS_SSPLKSFMX stPlksfmx, char *sKeyCode)
{
   /* ��MXL���г�ʼ��һЩֵ���Ա����������������ļ� */ 
   char sBuf[256];
   /* ��ʼ�� */
   COMP_SOFTSETXML("/hxxt/qqzjwj/qzlsh","")/* ǰ����ˮ�� */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zczh","")/* ת���ʺ� */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zrzh","")/* ת���ʺ� */
   COMP_SOFTSETXML("/hxxt/qqzjwj/jyje","")/* ���׽�� */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zydm","")/* ժҪ���� */
   /* ��ֵ */
   memset(sBuf, 0x00, sizeof(sBuf));
   snprintf(sBuf, sizeof(sBuf), "%d", stPlksfmx.plmxxh);
   COMP_SOFTSETXML("/hxxt/qqzjwj/qzlsh",sBuf)/* ǰ����ˮ�� */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zczh",stPlksfmx.payacct)/* ת���ʺ� */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zrzh",stPlksfmx.dfzh)/* ת���ʺ� */
   memset(sBuf, 0x00, sizeof(sBuf));
   snprintf(sBuf, sizeof(sBuf), "%.2f", stPlksfmx.jyje);
   COMP_SOFTSETXML("/hxxt/qqzjwj/jyje",sBuf)/* ���׽�� */
   COMP_SOFTSETXML("/hxxt/qqzjwj/zydm", sKeyCode)/* ժҪ���� */
      
   return 0 ; 
}
/* 
 * �����������������ļ�
 */
int prv_tips_GenZjFile(SDB_GENFILE stGenZjFile)
{
    /* add dci  20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_SSPLKSFMX   stPlksfmx;
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sPlpch[5+1];
    EXEC SQL END DECLARE SECTION;
    */
    int i;
    int iflag;
    int iret=-1;
    char sLine[1024];
    /* SDB_ZjIniCfg stZjIniCfg ; */    
    
		/* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		CURSOR cur;
		SDB_TIPS_SSPLKSFMX   stPlksfmx;
		char sZwrq[8+1];
    char sPljylsh[8+1];
    char sPlpch[5+1];
	char sSql[1024+1];
	char sKeyCode[3+1];
		int iRet=0;
/* end add dci 20141103 */
      
    /* ��ȡ���������ļ�ʱ�Ļ���������Ϣ 
    memset(&stZjIniCfg, 0x00, sizeof(stZjIniCfg));
    iret=prv_plhk_GetZjIniCfg( &stZjIniCfg);
    */
    memset(sZwrq, 0x00, sizeof(sZwrq));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    memset(sPlpch, 0x00, sizeof(sPlpch));
    pstrcopy(sZwrq, stGenZjFile.zwrq, sizeof(sZwrq));
    pstrcopy(sPljylsh, stGenZjFile.pljylsh, sizeof(sPljylsh));
    pstrcopy(sPlpch, stGenZjFile.plpch, sizeof(sPlpch));
           
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT * FROM  tips_ssplksfmx\
    	WHERE zwrq = '%s' and pljylsh = '%s' and plpch = '%s' ORDER BY plmxxh",sZwrq,sPljylsh,sPlpch); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")          
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        
        fpub_SetMsg(stGenZjFile.lXmlhandle,36001, "���α�ʧ��");
        LOG(LM_STD,Fmtmsg("prv_tips_GenZjFile��cur_ksfmx_rzfileʧ��"),"ERROR");
        return -1;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        
        iflag=-1;
        LOG(LM_STD,Fmtmsg("prv_tips_GenZjFile��cur_ksfmx_rzfile��ȡ����ʧ��"),"ERROR");
        
    }
		
    for (i=1,iflag=0;;i++)
    {
    		memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
    		memset(sLine, 0x00, sizeof(sLine));
				iRet = DBFetch(cur, SD_TIPS_SSPLKSFMX,NUMELE(SD_TIPS_SSPLKSFMX),&stPlksfmx, sErrmsg );
				
				if ( iRet < 0 )
        {  
        	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        	
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("prv_tips_GenZjFile��cur_ksfmx_rzfile��ȡ����ʧ��"),"ERROR");
        	break;
        }
        if ( iRet == 0 )
          break;

		/**ժҪ������ add by sunpj 20170712**/
		memset(sSql, 0x00, sizeof(sSql));
		memset(sKeyCode, 0x00, sizeof(sKeyCode));
		sprintf(sSql, "select decode(taxorgtype,'1','111','2','112','3','999','4','234','5','109','999') from tips_taxcodeinfo where taxorgcode='%s'"
		            , stPlksfmx.taxorgcode);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO")
		iRet = DBSelectToVarChar(sErrmsg, sKeyCode, sSql);
		if (0 > iRet || 0 == iRet)
		{
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]", DCILastError() ,iRet),"ERROR")
			strcpy(sKeyCode, "054");
		}

      	
      	iret=prv_tips_PutKsfmxToXml(stGenZjFile.lXmlhandle, stPlksfmx, sKeyCode);                      
        iret=SBATCH_FuncICXPPKG(stGenZjFile.lXmlhandle, stGenZjFile.resicxp, sLine);
        if (iret < 0)
        {  
            iflag=-2; 
            break;  
        }	
        fprintf(stGenZjFile.fp,"%s\n",sLine);                     
      	                
    }
    
    DCIFreeCursor(cur);
    
    /* end dci 20141103 */
    /* dci mod 20141103    
    EXEC SQL DECLARE cur_ksfmx_rzfile CURSOR for 
        SELECT * FROM  tips_ssplksfmx 
        WHERE zwrq = :sZwrq 
         AND  pljylsh = :sPljylsh
         AND  plpch = :sPlpch
         ORDER BY plmxxh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_ksfmx_rzfile;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_ksfmx_rzfile",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(stGenZjFile.lXmlhandle,36001, "���α�ʧ��");
        LOG(LM_STD,Fmtmsg("prv_tips_GenZjFile��cur_ksfmx_rzfileʧ��"),"ERROR");
        return -1;
    }
    /*��ʼѭ��
    for (i=1,iflag=0;;i++)
    {
        memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
        memset(sLine, 0x00, sizeof(sLine));
        EXEC SQL FETCH cur_ksfmx_rzfile INTO :stPlksfmx;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_ksfmx_rzfile", sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("prv_tips_GenZjFile��cur_ksfmx_rzfile��ȡ����ʧ��"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;
        /*����¼���ݷŵ�XML��   
        iret=prv_tips_PutKsfmxToXml(stGenZjFile.lXmlhandle, stPlksfmx);                      
        iret=SBATCH_FuncICXPPKG(stGenZjFile.lXmlhandle, stGenZjFile.resicxp, sLine);
        if (iret < 0)
        {  
            iflag=-2; 
            break;  
        }	
        fprintf(stGenZjFile.fp,"%s\n",sLine);
    }	
    EXEC SQL CLOSE cur_ksfmx_rzfile; 
    */   
    /* EXEC SQL FREE  cur_ksfmx_rzfile; */
     
    if (iflag < 0)
    {
        fpub_SetMsg(stGenZjFile.lXmlhandle,36002,"�������������ļ�ʧ��");
        LOG(LM_STD,Fmtmsg("�������������ļ�ʧ��iflag=[%d]",iflag),"ERROR");
        return -2;
    }
    return 0;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitPLJYDJ
�������: ��ʼ���������׵ǼǱ�
�������: 
  �����������׵ǼǱ�
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
�������׵ǼǱ�	tips_pljydj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��09��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitPLJYDJ(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[256];
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
        int iCount=0;
        char sPljydm[60+1];
    EXEC SQL END   DECLARE SECTION;
    */
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		CURSOR cur;
  	SDB_TIPS_PLJYDJ stPljydj;
    int iCount=0;
    char sPljydm[60+1];
		int iRet=0;
/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif    

    memset(&stPljydj, 0x00, sizeof(stPljydj));
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy( stPljydj.zwrq, sBuf, sizeof(stPljydj.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "����������ˮ��")
    pstrcopy( stPljydj.pljylsh, sBuf, sizeof(stPljydj.pljylsh));
    
    LOG(LM_STD,Fmtmsg("��ʼ���������׵ǼǱ� ��������[%s],����������ˮ��[%s]", 
        stPljydj.zwrq, stPljydj.pljylsh), fpub_GetCompname(lXmlhandle));
		
		/* add dci 20141103 */
		iCount=0;
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_pljydj\
    	 where zwrq='%s' and pljylsh=%d",stPljydj.zwrq,stPljydj.pljylsh);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	  
    }
		/* end dci 20141103 */
		/* dci mod 20141103 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_pljydj
         WHERE zwrq = :stPljydj.zwrq
           AND pljylsh = :stPljydj.pljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    /* �жϱ��������Ƿ��ظ� */
    if ( iCount > 0 )	
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24272, Fmtmsg("���������ѵǼ�"));
        LOG(LM_STD,Fmtmsg("InitPLJYDJ���������ѵǼ�"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_FAIL; 
    }   
    
    /* 2.�������״���
    EXEC SQL SELECT b.num_desc INTO :sPljydm
         FROM tips_taxcodeinfo a, tips_codelist b
         WHERE a.taxorgcode = :stPljydj.orgcode
           AND b.code_name = 'tipspljydm'
           AND a.taxorgtype = b.num;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR || SQLNOTFOUND_TIPS || sPljydm[0]=='\0')
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24274, Fmtmsg("�������״��벻��Ϊ��"));
        LOG(LM_STD,Fmtmsg("��ȡ�������״���ʧ�ܻ��������״���Ϊ��"), fpub_GetCompname(lXmlhandle));
        return COMPRET_FAIL;
    }*/
    memset(sPljydm, 0x00, sizeof(sPljydm));    
    pstrcopy(stPljydj.pljydm, "SWPKS", sizeof(stPljydj.pljydm));
    COMP_SOFTSETXML("/tips/pljydm", stPljydj.pljydm)

    /* 4.�����ܱ��� */
    stPljydj.pczbs = 0 ;

    /* 5.ί������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate", sBuf)
    pstrcopy( stPljydj.entrustdate, sBuf, sizeof(stPljydj.entrustdate));
    if ( stPljydj.entrustdate[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24273, Fmtmsg("��Χ��������Ϊ��"));
        LOG(LM_STD,Fmtmsg("ί�����ڲ���Ϊ��, entrustdate=[%s]", stPljydj.entrustdate),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    } 
    
    /* 6.���ջ��ش��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode", sBuf)
    pstrcopy( stPljydj.orgcode, sBuf, sizeof(stPljydj.orgcode));    
    if ( stPljydj.orgcode[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24275, Fmtmsg("���ջ��ش��벻��Ϊ��"));
        LOG(LM_STD,Fmtmsg("���ջ��ش��벻��Ϊ��, orgcode=[%s]", stPljydj.orgcode),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

    /* 7.����ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PackNo", sBuf)
    pstrcopy( stPljydj.packno, sBuf, sizeof(stPljydj.packno));       
    if ( stPljydj.packno[0] == '\0')
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24286, Fmtmsg("����ˮ�Ų���Ϊ��"));
        LOG(LM_STD,Fmtmsg("����ˮ�Ų���Ϊ��, packno=[%s]", stPljydj.packno),fpub_GetCompname(lXmlhandle)) 
        return COMPRET_FAIL;
    }

		/* add dci 20141103 */
		iCount=0;
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_pljydj\
    	 where entrustdate='%s' and orgcode='%s' and packno='%s'",stPljydj.entrustdate,stPljydj.orgcode,stPljydj.packno);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	  
    }
    /* end add dci 20141103 */
    
		/* mod dci 20141103 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_pljydj
         WHERE entrustdate = :stPljydj.entrustdate
           AND orgcode = :stPljydj.orgcode
           AND packno = :stPljydj.packno;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24271, Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    /* �жϱ��������Ƿ��ظ� */
    if ( iCount > 0 )	
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24272, Fmtmsg("���������ѵǼ�"));
        LOG(LM_STD,Fmtmsg("InitPLJYDJ���������ѵǼ�"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_FAIL; 
    }

    /* 8.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stPljydj.workdate, sBuf, sizeof(stPljydj.workdate));
    
    /* 9.�ܱ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllNum", sBuf)
    stPljydj.allnum = atoi(sBuf);

    /* 10.�ܽ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AllAmt", sBuf)
    stPljydj.allamt = atof(sBuf);
    
    /* 11�������(1)|�տ����к�(12)|�տλ����(12)|�տ����˺�(12)|�տ�������(60)|�������к�(12)|
     */
    /* 11.1������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/HandleType", sBuf)
    stPljydj.handletype[0] = sBuf[0];
    
    /* 11.2�տ����к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
    pstrcopy(stPljydj.payeebankno, sBuf, sizeof(stPljydj.payeebankno)); 
    trim(stPljydj.payeebankno);
    
    /* 11.3�տλ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeOrgCode", sBuf)
    pstrcopy(stPljydj.payeeorgcode, sBuf, sizeof(stPljydj.payeeorgcode)); 
    trim(stPljydj.payeeorgcode);
    
    /* 11.4�տ����˺� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeAcct", sBuf)
    pstrcopy(stPljydj.payeeacct, sBuf, sizeof(stPljydj.payeeacct)); 
    trim(stPljydj.payeeacct);
        
    /* 11.5�տ������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeName", sBuf)
    pstrcopy(stPljydj.payeename, sBuf, sizeof(stPljydj.payeename)); 
    trim(stPljydj.payeename);

    /* 11.6�������к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
    pstrcopy(stPljydj.paybkcode, sBuf, sizeof(stPljydj.paybkcode)); 
    trim(stPljydj.paybkcode);               
		
		/* �������� add 20150730 */
		memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stPljydj.chkdate, sBuf, sizeof(stPljydj.chkdate));
    
    /* 12.�����ܱ��� */
    stPljydj.rzzbs = 0 ;
    /* 13.�����ܽ�� */
    stPljydj.rzzje = 0.0 ;
    /* 14.ֹ���ܱ��� */
    stPljydj.zfzbs = 0 ;    
    /* 15.ֹ���ܽ�� */
    stPljydj.zfzje = 0.0 ;    
    /* 16.��Ӧ�� */
    stPljydj.xym[0] = '0' ;    
    /* 17.��Ӧ��Ϣ */
    pstrcopy(stPljydj.xyxx, "�������׳�ʼ��", sizeof(stPljydj.xyxx));    
    /* 18.�������� */
    stPljydj.czbd[0] = '1' ;    
    /* 19.��ɱ�־ */
    stPljydj.wcbz[0] = '9' ;
    /* 20.������ʼ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stPljydj.clqsrq, sBuf, sizeof(stPljydj.clqsrq));    
    /* 21.������ʼʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stPljydj.clqssj, sBuf, sizeof(stPljydj.clqssj));
    /* 22.����������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stPljydj.cljsrq, sBuf, sizeof(stPljydj.cljsrq));
    /* 23.�������ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stPljydj.cljssj, sBuf,sizeof(stPljydj.cljssj));
    /* 24.��չ��־ */
    pstrcopy(stPljydj.kzbz, "00000000",sizeof(stPljydj.kzbz));
    /* 25.�����ֶ� */
		
		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_pljydj", SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	/* DCIRollback();   */
    	
    	fpub_SetMsg(lXmlhandle, 24276, "InitPLJYDJ��ʼ���������׵ǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitPLJYDJ��ʼ���������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;      
    }

		/* end dci 20141103 */
		/* mod dci 20141103 
    EXEC SQL INSERT INTO tips_pljydj  VALUES (:stPljydj);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24276, "InitPLJYDJ��ʼ���������׵ǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitPLJYDJ��ʼ���������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	   
    */ 

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;        
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitPLKSFMX
�������: ��ʼ��˰��������˰����ϸ��
�������: 
  ��ʼ��˰��������˰����ϸ��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
�������׵ǼǱ�	tips_ssplksfmx

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��10��
�޸�����: 2014��12��20��DCI����
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitPLKSFMX(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
      SDB_TIPS_PLJYDJ stPljydj;
      SDB_TIPS_SSPLKSFMX stPlksfmx;
      char sZwrq[8+1];
      char sPljylsh[8+1];
      char sPayBkCode[12+1];
      char sDfzh[20+1];
      char sDqdh[10+1];
      char sJgdh[10+1];
      char sTaxPayCode[20+1];
      int iCount;
    EXEC SQL END   DECLARE SECTION;    
    */
    int i,j;
    int iflag;
    int iret;
    char sBuf[256];
    char sXmlNodePath[40+1+20];
    char sTaxInfoPath[256];
    char sPayment3102[10240];
    FILE *fp;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_PLJYDJ stPljydj;
      SDB_TIPS_SSPLKSFMX stPlksfmx;
      SDB_TIPS_TAXTYPEMX stTaxtypemx;
      char sZwrq[8+1];
      char sPljylsh[8+1];
      char sPayBkCode[12+1];
      char sDfzh[20+1];
      char sDqdh[10+1];
      char sJgdh[10+1];
      char sTaxPayCode[20+1];
      char sPayAcct2[32+1]; /*add by liurj 20180713*/
      int iCount;
      int iTaxTypeNum=0;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));  
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(2, sBuf, "����������ˮ��")
    pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));  

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxInfoPath, 0x00, sizeof(sTaxInfoPath));
    COMP_GETPARSEPARAS(3, sBuf, "����˰Ʊ·��")
    pstrcopy(sTaxInfoPath, sBuf, sizeof(sTaxInfoPath));
        
    LOG(LM_STD,Fmtmsg("��ʼ��˰��������˰����ϸ��ʼ..."),"INFO")
    LOG(LM_STD,Fmtmsg("��������[%s], ������ˮ��[%s],˰Ʊ·��[%s]", 
        sZwrq, sPljylsh, sTaxInfoPath),"INFO")  

    /*�ж�������˰����ϸ�����Ƿ����м�¼*/
    /* add dci 20141103 */
    iCount=0;
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_ssplksfmx\
    	 where zwrq='%s' and pljylsh='%s'",sZwrq,sPljylsh);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24277, "initPlksfmx��ѯ������˰����ϸ��¼����");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx��ѯ������˰����ϸ��¼����"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    /* end dci 20141103 */
    /* mod dci 20141103
    iCount =0;
    EXEC SQL SELECT count(*) INTO :iCount
    	 FROM  tips_ssplksfmx
         WHERE zwrq = :sZwrq 
           AND pljylsh = :sPljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )	
    {
         fpub_SetMsg(lXmlhandle, 24277, "initPlksfmx��ѯ������˰����ϸ��¼����");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx��ѯ������˰����ϸ��¼����"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    */
    if (iCount > 0)
    {
         fpub_SetMsg(lXmlhandle, 24278, "initPlksfmxУ���,������˰����ϸ����������");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmxУ���,������˰����ϸ����������"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;	    	 
    }
    
    /* ��ѯ�������׵ǼǱ���Ϣ */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_pljydj\
    	 where zwrq='%s' and pljylsh='%s'",sZwrq,sPljylsh);     
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))       
    iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj);
    /*   	      	
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPljydj.zwrq, &stPljydj.pljydm, &stPljydj.pljylsh, &stPljydj.pczbs, \
    	&stPljydj.entrustdate, &stPljydj.orgcode, &stPljydj.packno, &stPljydj.workdate, &stPljydj.allnum, \
    	&stPljydj.allamt, &stPljydj.handletype, &stPljydj.payeebankno, &stPljydj.payeeorgcode, \
    	&stPljydj.payeeacct, &stPljydj.payeename, &stPljydj.paybkcode, &stPljydj.chkdate, &stPljydj.chkacctord, \
    	&stPljydj.rzzbs, &stPljydj.rzzje, &stPljydj.zfzbs, &stPljydj.zfzje, &stPljydj.xym, &stPljydj.xyxx, \
    	&stPljydj.czbd, &stPljydj.wcbz, &stPljydj.clqsrq, &stPljydj.clqssj, &stPljydj.cljsrq, &stPljydj.cljssj, \
    	&stPljydj.kzbz, &stPljydj.byzd);
		*/
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24279, "initPlksfmx��ѯ�������׵ǼǱ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    /* end add dci 20141103 */
    /* mod dci 20141103 
    memset(&stPljydj, 0x00, sizeof(stPljydj));
    EXEC SQL SELECT * INTO :stPljydj
             FROM   tips_pljydj
             WHERE  zwrq = :sZwrq
               AND  pljylsh = :sPljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS ))
    {
         fpub_SetMsg(lXmlhandle, 24279, "initPlksfmx��ѯ�������׵ǼǱ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    */
		LOG(LM_STD,Fmtmsg("sZwrq[%s]sPljylsh[%s]...",sZwrq,sPljylsh),fpub_GetCompname(lXmlhandle))
    /*���ݸ������кŴ���ҵ���������еǼǱ��ѯ�����ʺ�*/
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    pstrcopy(sPayBkCode, stPljydj.paybkcode, sizeof(sPayBkCode));
    memset(sDfzh, 0x00, sizeof(sDfzh));
    memset(sDqdh, 0x00, sizeof(sDqdh));
    memset(sJgdh, 0x00, sizeof(sJgdh));
    
    /* add dci 20141103 */
    /* ��ȡ�����˺� */
	/*
    memset( sSql1, 0x00, sizeof( sSql1 ) );       
    snprintf( sSql1, sizeof(sSql1), "select dfzh from tips_qshdj\
    	 where paybkcode='%s'",sPayBkCode);   
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")          	    	
    iRet =DBSelectToMultiVar(sErrmsg, sSql1, sDfzh);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24280, "initPlksfmx��ѯ�����˺�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx��ѯ�����˺�ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ; 
    }
    if ( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24280, "initPlksfmx��������Ϣδ��ʼ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx��������Ϣδ��ʼ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ; 
    }* del by sunpj 20170706/
    /* add dci 20141103 */
        
    /* mod dci 20141103
    EXEC SQL SELECT dfzh, dqdh, jgdh 
         INTO :sDfzh, :sDqdh, :sJgdh 
         FROM tips_qshdj 
         WHERE paybkcode = :sPayBkCode;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24280, "initPlksfmx��ѯ�����˺�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx��ѯ�����˺�ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ; 
    }
    if ( SQLNOTFOUND_TIPS )
    {
         fpub_SetMsg(lXmlhandle, 24280, "initPlksfmx��������Ϣδ��ʼ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("initPlksfmx��������Ϣδ��ʼ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ; 
    }
    */
    
    trim(sDfzh);
    trim(sDqdh);
    trim(sJgdh);
    /* ��ʼ���� 
    EXEC SQL BEGIN WORK ; */
       
    memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
    pstrcopy(stPlksfmx.zwrq, stPljydj.zwrq, sizeof(stPlksfmx.zwrq)); /* �������� */
    pstrcopy(stPlksfmx.pljydm, stPljydj.pljydm, sizeof(stPlksfmx.pljydm));/* �������״��� */
    pstrcopy(stPlksfmx.pljylsh, stPljydj.pljylsh, sizeof(stPlksfmx.pljylsh));/* ����������ˮ�� */
    pstrcopy(stPlksfmx.plpch, "00000", sizeof(stPlksfmx.plpch));/* �������κ� */
    stPlksfmx.clcs = 0 ;/* ������� */
    pstrcopy(stPlksfmx.workdate, stPljydj.workdate, sizeof(stPlksfmx.workdate));/* �������� */
    pstrcopy(stPlksfmx.chkdate, stPljydj.chkdate, sizeof(stPlksfmx.chkdate));/* �������� */ 
    pstrcopy(stPlksfmx.entrustdate, stPljydj.entrustdate, sizeof(stPlksfmx.entrustdate));/* ί������ */
    pstrcopy(stPlksfmx.taxorgcode, stPljydj.orgcode, sizeof(stPlksfmx.taxorgcode));/* ���ջ��ش��� */
    pstrcopy(stPlksfmx.packno, stPljydj.packno, sizeof(stPlksfmx.packno));/* ����ˮ�� */
    pstrcopy(stPlksfmx.paybkcode, stPljydj.paybkcode, sizeof(stPlksfmx.paybkcode));/* �������к� */
    /*pstrcopy(stPlksfmx.dqdh, sDqdh, sizeof(stPlksfmx.dqdh));*/ /* �������� mod 20150720 */
    /*pstrcopy(stPlksfmx.jgdh, sJgdh, sizeof(stPlksfmx.jgdh));*/ /* �������� mod 20150720 */
    /* ��ִ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ReturnTerm",sBuf)
    stPlksfmx.returnterm=atoi(sBuf);
    pstrcopy(stPlksfmx.payeebankno, stPljydj.payeebankno, sizeof(stPlksfmx.payeebankno));
    stPlksfmx.czbd[0]='0';/* �������� */
    stPlksfmx.qsbz[0]='0';/* �����־ 0-δ���� */
    pstrcopy(stPlksfmx.kzbz, "00000000", sizeof(stPlksfmx.kzbz));
    LOG(LM_STD,Fmtmsg("��������[%s], �������״���[%s], ����������ˮ��[%s]", 
        stPlksfmx.zwrq, stPlksfmx.pljydm, stPlksfmx.pljylsh),"INFO")
    LOG(LM_STD,Fmtmsg("ί������[%s], ���ջ��ش���[%s], ����ˮ��[%s]", 
        stPlksfmx.entrustdate, stPlksfmx.taxorgcode, stPlksfmx.packno),"INFO") 
    
    for ( i=1; i<= stPljydj.allnum; i++ )
    {
        iflag=0;
        stPlksfmx.plmxxh=0;
        memset(stPlksfmx.trano, 0x00, sizeof(stPlksfmx.trano));
        memset(stPlksfmx.protocolno, 0x00, sizeof(stPlksfmx.protocolno));
        memset(stPlksfmx.dfzh, 0x00, sizeof(stPlksfmx.dfzh));
        memset(stPlksfmx.payopbkcode, 0x00, sizeof(stPlksfmx.payopbkcode));
        memset(stPlksfmx.payacct, 0x00, sizeof(stPlksfmx.payacct));
        memset(stPlksfmx.handorgname, 0x00, sizeof(stPlksfmx.handorgname));
        memset(stPlksfmx.taxvouno, 0x00, sizeof(stPlksfmx.taxvouno));
        stPlksfmx.jyje=0.00;
        memset(stPlksfmx.xym, 0x00, sizeof(stPlksfmx.xym));
        memset(stPlksfmx.xyxx, 0x00, sizeof(stPlksfmx.xyxx));
        memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
        stPlksfmx.czbd[0]='0';
        memset(stPlksfmx.taxpaycode, 0x00, sizeof(stPlksfmx.taxpaycode));
        memset(stPlksfmx.spxx, 0x00, sizeof(stPlksfmx.spxx));
        
        /* add by tuql 20090909 */
        memset(stPlksfmx.dqdh, 0x00, sizeof(stPlksfmx.dqdh));
        memset(stPlksfmx.jgdh, 0x00, sizeof(stPlksfmx.jgdh));
        
        /* ������ϸ���, Ӧ�û�ȡ�ۺ�ǰ����ˮ�� */
        memset(sBuf, 0x00, sizeof(sBuf));
        iret=prv_GenSerino(lXmlhandle, sBuf, sizeof(sBuf));
        if ( iret <= 0 )
        {        
            LOG(LM_STD,Fmtmsg("��ȡ�µ��ۺ�ǰ����ˮ��ʧ��[%d]", iret),"ERROR")   
            iflag = -1;
            break;	
        }
        stPlksfmx.plmxxh=iret;
        LOG(LM_STD,Fmtmsg("������ϸ���[%d]",stPlksfmx.plmxxh),"INFO")
        /* ������ˮ�� */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TraNo", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.trano, sBuf, sizeof(stPlksfmx.trano));
        /* Э����� */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/ProtocolNo", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.protocolno, sBuf, sizeof(stPlksfmx.protocolno));  
                      
        /* ��������к� 
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/PayOpBkCode", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.payopbkcode, sBuf, sizeof(stPlksfmx.payopbkcode)); del by sunpj 20170706*/
        /* �����˺� */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/PayAcct", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.payacct, sBuf, sizeof(stPlksfmx.payacct));
        /* �ɿλ���� */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/HandOrgName", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.handorgname, sBuf, sizeof(stPlksfmx.handorgname));
        /* ��˰������ */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxPayName", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.taxpayname, sBuf, sizeof(stPlksfmx.taxpayname));
        /* ˰Ʊ���� */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxVouNo", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        pstrcopy(stPlksfmx.taxvouno, sBuf, sizeof(stPlksfmx.taxvouno));
        /* ���׽�� */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TraAmt", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        stPlksfmx.jyje=atof(sBuf);
        /* ��Ӧ�� */
        stPlksfmx.xym[0]='0';
        /* ��Ӧ��Ϣ */
        strcpy(stPlksfmx.xyxx, "������سɹ�");
        trim(stPlksfmx.xyxx);
        
        /* ���ί�й�ϵ�������˰�˱��롢ʵ���˺� mod by tuql 20090909 ���ӷ��ص������ż���������*/
        LOG(LM_STD,Fmtmsg("����ί�й�ϵ��麯����ʼ......"),"INFO")
        memset(sPayAcct2, 0x00, sizeof(sPayAcct2));
        
        iret = prv_tips_ChkWtgx( stPlksfmx.protocolno, 
                                 stPlksfmx.payacct, 
                                 sTaxPayCode,
                                 stPlksfmx.dqdh,
                                 stPlksfmx.jgdh,
                                 stPlksfmx.payopbkcode,
                                 sPayAcct2
                                );
        LOG(LM_STD,Fmtmsg("�������к�[%s], �����к�[%s], ��������[%s]", 
        stPlksfmx.paybkcode, sPayBkCode, stPlksfmx.jgdh),"INFO")     
        if ( iret < 0 )
        {   
            iflag = -2;
            LOG(LM_STD,Fmtmsg("��ί�й�ϵ��麯��ʧ��[%d]", iret),"ERROR")
            break;                
        }
        if ( iret == 1 )
        {
            pstrcopy(stPlksfmx.xym, "24009", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"����Э�鲻����",sizeof(stPlksfmx.xyxx));
            stPlksfmx.czbd[0]='8';/* �������� 8-ί�й�ϵ������ */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -3;
                break;	
    				}
            /* end dci 20141103 */
            
            /* mod dci 20141103 
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -3;
                break;	
            }
            */
            continue ;            
        }                                
        if ( iret == 2 )
        {
            pstrcopy(stPlksfmx.xym, "24009", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"����Э��״̬�쳣",sizeof(stPlksfmx.xyxx));
            stPlksfmx.czbd[0]='8';/* �������� 8-ί�й�ϵ�쳣 */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -4;
                break;	
    				}
    				/* end add dci 20141103 */
            /* mod dci 20141103
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -4;
                break;	
            }
            */
            continue ;            
        }
        if ( iret == 3 )
        {
            pstrcopy(stPlksfmx.xym, "24009", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"����Э��δ��֤",sizeof(stPlksfmx.xyxx));
            stPlksfmx.czbd[0]='8';/* �������� 8-����Э��δ��֤ */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    					    	
    					LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -5;
                break;	
    				}
    				/* end add dci 20141103 */
    				
            /* mod dci 20141103
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -5;
                break;	
            }
            */
            continue ;            
        } 
        trim(sTaxPayCode);

        /* ��ί�й�ϵ�ǼǱ��еĸ������˺�2д����Ӧ���,��������ϸ���и������˺�Ϊ�������˺�2 add by liurj 20180713*/
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/PayAcct2", i);
        COMP_SOFTSETXML(sXmlNodePath, sPayAcct2)
        memset(stPlksfmx.payacct, 0x00, sizeof(stPlksfmx.payacct));
        pstrcopy(stPlksfmx.payacct, sPayAcct2, sizeof(stPlksfmx.payacct));
            
		/* ��ȡ���������кš������˺� */
		trim(stPlksfmx.payopbkcode);
		memset( sSql1, 0x00, sizeof( sSql1 ) );       
		snprintf( sSql1, sizeof(sSql1), "select dfzh from tips_qshdj\
		                 where paybkcode='%s'",stPlksfmx.payopbkcode);   
		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")          	    	
		iRet =DBSelectToMultiVar(sErrmsg, sSql1, &sDfzh);
		if ( iRet < 0 )
		{
		    LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
		    
		    fpub_SetMsg(lXmlhandle, 24280, "initPlksfmx��ѯ�����˺�ʧ��");
		    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		    LOG(LM_STD, Fmtmsg("initPlksfmx��ѯ�����˺�ʧ��"), fpub_GetCompname(lXmlhandle))	
		    return COMPRET_FAIL ; 
		}
		if ( iRet == 0 )
		{
		    LOG(LM_STD, Fmtmsg("initPlksfmx��������Ϣδ��ʼ��"), fpub_GetCompname(lXmlhandle))	
		}
		
        /* ��ί�й�ϵ�ǼǱ��е���˰�˱��д����Ӧ��� */
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        sprintf(sBuf,"/tips/MSG/Payment3102|%d/TaxPayCode", i);
        COMP_SOFTSETXML(sXmlNodePath, sTaxPayCode)
        pstrcopy(stPlksfmx.taxpaycode, sTaxPayCode, sizeof(stPlksfmx.taxpaycode));
        
        
        
        /* ˰Ʊ��Ϣ */
        memset(sPayment3102, 0x00, sizeof(sPayment3102));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        sprintf(sXmlNodePath,"/tips/MSG/Payment3102|%d",i);
        if ( (iret=xml_ExportXMLString(lXmlhandle,sPayment3102,sizeof(sPayment3102),sXmlNodePath,1 )) == -1 )
        {
            pstrcopy(stPlksfmx.xym, "24282", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"��ȡ˰Ʊ��Ϣʧ��",sizeof(stPlksfmx.xyxx));
            stPlksfmx.czbd[0]='2';/* �������� 2-������ */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    					    	
    					LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -6;
                break;	
    				}
    				/* end add dci 20141103 */
    				
            /* mod dci 20141103 
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -6;
                break;	
            }
            */
            continue ;                            
        }
        
        /* ��˰Ʊ��Ϣ��ŵ��ļ���ȥ */
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));/* ��ŵ��ļ��� */
        snprintf(sXmlNodePath, sizeof(sXmlNodePath), "spxx_%s_%d",stPlksfmx.zwrq, stPlksfmx.plmxxh);
        trim(sXmlNodePath);
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf), "%s%s", sTaxInfoPath, sXmlNodePath);
        fp = fopen(sBuf, "w+");
        if ( fp==NULL )
        {
            LOG(LM_STD,Fmtmsg("����˰Ʊ��Ϣʧ�� �ļ�ȫ·��[%s]", sBuf),"ERROR")   
            LOG(LM_STD,Fmtmsg("������Ϣ[%s]", strerror(errno)),"ERROR")   
            pstrcopy(stPlksfmx.xym, "24283", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"��˰Ʊ��Ϣ�ļ�ʧ��",sizeof(stPlksfmx.xyxx));
            stPlksfmx.czbd[0]='2';/* �������� 2-������ */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -7;
                break;	
    				}
    				/* end add dci 20141103 */
    				
            /* mod dci 20141103
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -7;
                break;	
            }
            */
            continue ;              
        }
        fprintf(fp, "%s\n", sPayment3102); 
        fclose(fp);
        pstrcopy(stPlksfmx.spxx, sXmlNodePath, sizeof(stPlksfmx.spxx));                
        /* �����˺� */
        pstrcopy(stPlksfmx.dfzh, sDfzh, sizeof(stPlksfmx.dfzh));/* �����ʺ� */
        if( strlen(stPlksfmx.dfzh)==0)
        {
            pstrcopy(stPlksfmx.xym, "24281", sizeof(stPlksfmx.xym));
            pstrcopy(stPlksfmx.xyxx,"֧���д����˺�Ϊ��",sizeof(stPlksfmx.xyxx));    
            stPlksfmx.czbd[0]='2';/* �������� 2-������ */
            
            /* add dci 20141103 */
            memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -8;
                break;	
    				}
    				/* end add dci 20141103 */
    				
            /* mod dci 20141103
            EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
            if ( SQLERR )
            {        
                LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
                iflag = -8;
                break;	
            }
            */
            continue ;
        }
        
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
    		iRet = DBInsert("tips_ssplksfmx", SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx, sErrmsg);
    		if( iRet < 0 )
    		{
    				LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    				/* DCIRollback();   */
    	
    				LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
            iflag = -9;
            break;	
    		}
    				/* end add dci 20141103 */
        /* mod dci 20141103
        EXEC SQL INSERT INTO tips_ssplksfmx VALUES(:stPlksfmx);
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {        
            LOG(LM_STD,Fmtmsg("����������˰�ѱ���� ������ˮ��[%s]", stPlksfmx.trano),"ERROR")   
            iflag = -9;
            break;	
        }
        */
        
        /*������ÿ��������ϸ����֮�󣬲��������ϸ���ݵ�˰����ϸ����ݸ���Ի�20171028*/
        /*������ϸ��˰������*/
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeNum", i);
        COMP_SOFTGETXML(sXmlNodePath,sBuf)
        iTaxTypeNum=atoi(sBuf);
        
        for(j=1; j<=iTaxTypeNum; j++)
        {        
        		memset(&stTaxtypemx, 0x00, sizeof(stTaxtypemx));
        		pstrcopy(stTaxtypemx.jyrq, stPlksfmx.zwrq, sizeof(stTaxtypemx.jyrq));
        		//pstrcopy(stTaxtypemx.jylsh, itoa(stPlksfmx.plmxxh), sizeof(stTaxtypemx.jylsh));
        		sprintf(stTaxtypemx.jylsh, "%s", itoa(stPlksfmx.plmxxh));
        		pstrcopy(stTaxtypemx.spxx, stPlksfmx.spxx, sizeof(stTaxtypemx.spxx));
        		
        		memset(sBuf, 0x00, sizeof(sBuf));
        		memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        		snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeList3102|%d/ProjectId", i, j);
        		COMP_SOFTGETXML(sXmlNodePath,sBuf)
        		trim(sBuf);
            pstrcopy(stTaxtypemx.projectid, sBuf, sizeof(stTaxtypemx.projectid));
        		
        		memset(sBuf, 0x00, sizeof(sBuf));
        		memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        		snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeList3102|%d/TaxTypeName", i, j);
        		COMP_SOFTGETXML(sXmlNodePath,sBuf)
        		trim(sBuf);
            pstrcopy(stTaxtypemx.taxtypename, sBuf, sizeof(stTaxtypemx.taxtypename));
        		
        		memset(sBuf, 0x00, sizeof(sBuf));
        		memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        		snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeList3102|%d/TaxStartDate", i, j);
        		COMP_SOFTGETXML(sXmlNodePath,sBuf)
        		trim(sBuf);
            pstrcopy(stTaxtypemx.taxstartdate, sBuf, sizeof(stTaxtypemx.taxstartdate));
            
        		memset(sBuf, 0x00, sizeof(sBuf));
        		memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        		snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeList3102|%d/TaxEndDate", i, j);
        		COMP_SOFTGETXML(sXmlNodePath,sBuf)
        		trim(sBuf);
            pstrcopy(stTaxtypemx.taxenddate, sBuf, sizeof(stTaxtypemx.taxenddate));            

        		memset(sBuf, 0x00, sizeof(sBuf));
        		memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
        		snprintf(sXmlNodePath, sizeof(sXmlNodePath),"/tips/MSG/Payment3102|%d/TaxTypeList3102|%d/TaxTypeAmt", i, j);
        		COMP_SOFTGETXML(sXmlNodePath,sBuf)
        		trim(sBuf);
            stTaxtypemx.taxtypeamt = atof(sBuf);
            
            memset( sErrmsg, 0x00, sizeof(sErrmsg));
            iRet = DBInsert("tips_taxtypemx", SD_TIPS_TAXTYPEMX, NUMELE(SD_TIPS_TAXTYPEMX), &stTaxtypemx, sErrmsg);
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                
                fpub_SetMsg(lXmlhandle, 24327, "����˰����ϸ��ʧ��");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                iflag = -9;
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����˰����ϸ��ʧ��"),fpub_GetCompname(lXmlhandle))
                break;
            }                		
        }
        /*����������ϸ��˰����ϸ�������*/
        
    }    
    if ( iflag < 0 )
    {
        /* EXEC SQL ROLLBACK WORK;*/
        LOG(LM_STD,Fmtmsg("  -->������˰���������ʧ��,ret[%d]..",iflag),"ERROR"); 
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("������˰���������ʧ��"));
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
   
    /*ȫ���ύ */
    /*iRet =DCICommit();
    if ( iRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	      
       	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("���ݿ����ʧ��"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    }
    */

    /* mod dci 20141103
    /* EXEC SQL COMMIT WORK;    
    if ( SQLERR )  
    {
       LOG(LM_STD,Fmtmsg("�ύ���ݿ�ʧ��sqlcode[%d]",sqlca.sqlcode),"ERROR");
       /* EXEC SQL ROLLBACK WORK; 
       fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("���ݿ����ʧ��"));
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       return COMPRET_FAIL;    	
    }*/
            
    LOG(LM_STD,Fmtmsg("������˰��������سɹ�"),"INFO"); 
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC; 
}    
/************************************************************************
��̬�����������
�����������: SYW_TIPS_UpdPLJYDJ
�������: �����������׵ǼǱ�״̬
�������: 
  �����������׵ǼǱ�״̬
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
�������׵ǼǱ�	tips_pljydj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��10��
�޸�����: 2014��12��20��DCI����
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_UpdPLJYDJ(HXMLTREE lXmlhandle)
{
	
    int iParas;
    char sBuf[200+1];
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
    EXEC SQL END   DECLARE SECTION;
    */
  	
  	/* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		SDB_TIPS_PLJYDJ stPljydj;		
		int iRet=0;
/* end add dci 20141103 */
  	
  	iRet = DCIBegin();
		if( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}

    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    memset(&stPljydj, 0x00, sizeof(stPljydj));
    COMP_PARACOUNTCHK(6);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy( stPljydj.zwrq, sBuf, sizeof(stPljydj.zwrq));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "����������ˮ��")
    pstrcopy( stPljydj.pljylsh, sBuf, sizeof(stPljydj.pljylsh));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "��������")
    pstrcopy( stPljydj.czbd, sBuf, sizeof(stPljydj.czbd));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(4, sBuf, "��ɱ�־")
    pstrcopy( stPljydj.wcbz, sBuf, sizeof(stPljydj.wcbz));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(5, sBuf, "��Ӧ��")
    pstrcopy( stPljydj.xym, sBuf, sizeof(stPljydj.xym));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(6, sBuf, "��Ӧ��Ϣ")
    pstrcopy( stPljydj.xyxx, sBuf, sizeof(stPljydj.xyxx));       
    
    /*22.�����������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate",sBuf)
    pstrcopy(stPljydj.cljsrq,sBuf,sizeof(stPljydj.cljsrq));
    /*23.�������ʱ��*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime",sBuf)
    pstrcopy(stPljydj.cljssj,sBuf,sizeof(stPljydj.cljssj));
    
    /* add dci 20141103 */
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_pljydj \
    		set	czbd   ='%s',\
    				wcbz   ='%s',\
    				xym    ='%s',\
    				xyxx   ='%s',\
    				cljsrq ='%s',\
    				cljssj ='%s' \
    			where zwrq='%s' and pljylsh='%s'" \
    			,stPljydj.czbd  \
    			,stPljydj.wcbz  \
    			,stPljydj.xym   \
    			,stPljydj.xyxx  \
          ,stPljydj.cljsrq\
          ,stPljydj.cljssj,stPljydj.zwrq,stPljydj.pljylsh);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")                 	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        
        fpub_SetMsg(lXmlhandle, 24285, "���������ǼǱ�ʧ��"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,
             Fmtmsg("updPLJYDJ���������ǼǱ�ʧ��zwrq[%s],pljylsh[%s]", stPljydj.zwrq,stPljydj.pljylsh),
             fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    if( iRet == 0)
    {
    		 LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
         fpub_SetMsg(lXmlhandle, 24285, "����ʧ��-->�����ǼǱ��¼δ�ҵ�");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,
             Fmtmsg("updPLJYDJ���������ǼǱ�ʧ��zwrq[%s],pljylsh[%s]", stPljydj.zwrq,stPljydj.pljylsh),
             fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    iRet =DCICommit();
    /* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
    if ( iRet < 0 )
    {
      	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      	DCIRollback();
      	
      	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
       	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	return COMPRET_FAIL;     
    }
    */
    /* end add dci 20141103 */
    /* mod dci 20141103
    EXEC SQL UPDATE tips_pljydj
    	   SET czbd = :stPljydj.czbd,
    	       wcbz = :stPljydj.wcbz,
    	       xym = :stPljydj.xym,
    	       xyxx = :stPljydj.xyxx,
    	       cljsrq = :stPljydj.cljsrq,
    	       cljssj = :stPljydj.cljssj
         WHERE zwrq = :stPljydj.zwrq 
           AND pljylsh = :stPljydj.pljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (SQLERR )	
    {
         fpub_SetMsg(lXmlhandle, 24285, "���������ǼǱ�ʧ��"); 
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,
             Fmtmsg("updPLJYDJ���������ǼǱ�ʧ��zwrq[%s],pljylsh[%s],sqlcode[%d]", stPljydj.zwrq,stPljydj.pljylsh,sqlca.sqlcode),
             fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }	
    if (SQLNOTFOUND_TIPS )	
    {
         fpub_SetMsg(lXmlhandle, 24285, "����ʧ��-->�����ǼǱ��¼δ�ҵ�");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD,
             Fmtmsg("updPLJYDJ���������ǼǱ�ʧ��zwrq[%s],pljylsh[%s],sqlcode[%d]", stPljydj.zwrq,stPljydj.pljylsh,sqlca.sqlcode),
             fpub_GetCompname(lXmlhandle))
         return COMPRET_FAIL ;	
    }
    */	   
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
} 

/************************************************************************
��̬�����������
�����������: SYW_TIPS_ChkPLJYDJ
�������: ����������ײ�������״̬
�������: 
  ����������ײ�������״̬
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  1                  ��¼�ظ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
�������׵ǼǱ�	tips_pljydj


�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��10��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_ChkPLJYDJ(HXMLTREE lXmlhandle)
{	
    int iParas;
    char sBuf[200+1];
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
        char sCzbd[30],sWcbz[30];
    EXEC SQL END   DECLARE SECTION;
  	*/
  	/* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		SDB_TIPS_PLJYDJ stPljydj;
        char sCzbd[30],sWcbz[30];
		int iRet=0;
/* end add dci 20141103 */
  	
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    memset(&stPljydj, 0x00, sizeof(stPljydj));
    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy( stPljydj.zwrq, sBuf, sizeof(stPljydj.zwrq));
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "����������ˮ��")
    pstrcopy( stPljydj.pljylsh, sBuf, sizeof(stPljydj.pljylsh));
    memset(sBuf, 0, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "���鲽��")
    pstrcopy( stPljydj.czbd, sBuf, sizeof(stPljydj.czbd));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT czbd,wcbz FROM tips_pljydj\
    	where zwrq='%s' and pljylsh='%s'",stPljydj.zwrq, stPljydj.pljylsh);     
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&sCzbd, &sWcbz);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24271, "��ѯ�������ױ����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("chkPLJYDJ��ѯ�������ױ����zwrq[%s],pljylsh[%s]", stPljydj.zwrq,stPljydj.pljylsh),
            fpub_GetCompname(lXmlhandle))	
        
    }
    if ( iRet == 0 )
    {
        /*���û���ҵ���������δ��ʼ���׶Σ�0.mod by tuql 20090614 ��0����Ϊ1*/
    		pstrcopy(sCzbd,"1",sizeof(sCzbd));
    }

    /* end dci 20141103 */
    
    /* mod dci 20141103
    memset(sCzbd,0,sizeof(sCzbd));
    EXEC SQL SELECT czbd,wcbz INTO :sCzbd,:sWcbz
    	   FROM  tips_pljydj
         WHERE zwrq = :stPljydj.zwrq 
           AND pljylsh = :stPljydj.pljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )	
    {
        fpub_SetMsg(lXmlhandle, 24271, "��ѯ�������ױ����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("chkPLJYDJ��ѯ�������ױ����zwrq[%s],pljylsh[%s]", stPljydj.zwrq,stPljydj.pljylsh),
            fpub_GetCompname(lXmlhandle))	
    }	   
    if ( SQLNOTFOUND_TIPS )
    {
    	/*���û���ҵ���������δ��ʼ���׶Σ�0.mod by tuql 20090614 ��0����Ϊ1
    	pstrcopy(sCzbd,"1",sizeof(sCzbd));
    }
    */
    
    trim(sCzbd);
    trim(sWcbz);
    if (strncmp(sCzbd,stPljydj.czbd,1) != 0)
    {
        fpub_SetMsg(lXmlhandle, 24287,Fmtmsg("�������㲻��"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("У��������㲻һ��zwrq[%s],pljylsh[%s],chkCzbd[%s],dbCzbd[%s]", 
            stPljydj.zwrq,stPljydj.pljylsh,stPljydj.czbd,sCzbd),
        fpub_GetCompname(lXmlhandle))	
    }
    
    if (sWcbz[0]=='9')
    {
        fpub_SetMsg(lXmlhandle, 24288, "�������������ڴ�����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("�������������ڴ�����zwrq[%s],pljylsh[%s],sWcbz[%s]", 
            stPljydj.zwrq,stPljydj.pljylsh,sWcbz),
        fpub_GetCompname(lXmlhandle))	
    }
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
} 

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitPLPCDJ
�������: ��ʼ���������εǼǱ�
  
�������: 
��� ��������   ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��


������״̬: 
  ���״̬��         ���˵��
  0                  ����
  -1���������������� ʧ�ܡ���
��־��Ϣ: 
  ��־����           ��־��

��Ҫ�������:
  ����                     ����
 gapsywk:tips_pljydj       ����
 gapsywk:tips_ssplksfmx    ����
 gapsywk:tips_ssplpcdj     ����

ʹ������:
   �����ֻ��Ե�һ�������ύ�������ļ�����
   һ������ֻ��һ���ļ�(��һ�������ļ�������Ϊ�����ļ�)�������	

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��11��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitPLPCDJ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLPCDJ stPlpcdj;
        char sZwrq[8+1];
        char sPlpch[5+1];
        char sPljylsh[8+1];
        int iZbs=0;
        int iCount=0;
        double dZje=0.0;
    EXEC SQL END   DECLARE SECTION;	
    */
    SDB_GENFILE stGenZjFile;
    char sBuf[256];
    char sTmpBuf[256];
    char sFile_short[60+1];
    char sFile_ret[60+1];
    char sNode_zbs[100];
    int  i;
    int  iret;
    int  iflag;
    int  j;
  
  	/* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLPCDJ stPlpcdj;
        char sZwrq[8+1];
        char sPlpch[5+1];
        char sPljylsh[8+1];
        int iZbs=0;
        int iCount=0;
        double dZje=0.0;
        char cZbs[16+1];
        char cZje[32+1];
		int iRet=0;
/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif
  
    COMP_PARACOUNTCHK(6);
  
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq)); 
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(2,sBuf,"����������ˮ��")
    pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));
    trim(sPljylsh);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPlpch, 0x00, sizeof(sPlpch));
    COMP_GETPARSEPARAS(3,sBuf,"�������κ�")
    pstrcopy(sPlpch, sBuf, sizeof(sPlpch));
    trim(sPlpch);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFile_short, 0x00, sizeof(sFile_short));
    COMP_GETPARSEPARAS(4,sBuf,"���������ļ���")
    pstrcopy(sFile_short, sBuf, sizeof(sFile_short));
    trim(sFile_short);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFile_ret, 0x00, sizeof(sFile_ret));
    COMP_GETPARSEPARAS(5,sBuf,"���������ļ���")
    pstrcopy(sFile_ret, sBuf, sizeof(sFile_ret));
    trim(sFile_ret);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sNode_zbs, 0x00, sizeof(sNode_zbs));
    COMP_GETPARSEPARAS(6,sBuf,"���������ܱ���")
    pstrcopy(sNode_zbs, sBuf, sizeof(sNode_zbs));
    trim(sNode_zbs);
    
    LOG(LM_STD,Fmtmsg("��������[%s],����������ˮ��[%s],�������κ�[%s]",sZwrq,sPljylsh,sPlpch),"INFO");
    LOG(LM_STD,Fmtmsg("���������ļ���[%s],���������ļ���[%s]",sFile_short, sFile_ret),"INFO");

		/* add dci 20141103 */
		memset(&stPljydj, 0x00, sizeof(stPljydj));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT * FROM tips_pljydj\
    	where zwrq='%s' and pljylsh='%s'",sZwrq, sPljylsh);  
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj);
    /*   
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPljydj.zwrq, &stPljydj.pljydm, &stPljydj.pljylsh, &stPljydj.pczbs, \
    	&stPljydj.entrustdate, &stPljydj.orgcode, &stPljydj.packno, &stPljydj.workdate, &stPljydj.allnum, \
    	&stPljydj.allamt, &stPljydj.handletype, &stPljydj.payeebankno, &stPljydj.payeeorgcode, \
    	&stPljydj.payeeacct, &stPljydj.payeename, &stPljydj.paybkcode, &stPljydj.chkdate, &stPljydj.chkacctord, \
    	&stPljydj.rzzbs, &stPljydj.rzzje, &stPljydj.zfzbs, &stPljydj.zfzje, &stPljydj.xym, &stPljydj.xyxx, \
    	&stPljydj.czbd, &stPljydj.wcbz, &stPljydj.clqsrq, &stPljydj.clqssj, &stPljydj.cljsrq, &stPljydj.cljssj, \
    	&stPljydj.kzbz, &stPljydj.byzd);*/
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24271, "��ѯ�����ǼǼ�¼����");
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ��ѯ�����ǼǼ�¼����"),
               fpub_GetCompname(lXmlhandle))	
        
    }
    /* end dci 20141103 */
    
		/* mod dci 20141103 
    memset(&stPljydj, 0x00, sizeof(stPljydj));  
    EXEC SQL SELECT * INTO :stPljydj 
         FROM  tips_pljydj 
         WHERE zwrq = :sZwrq 
           AND pljylsh = :sPljylsh ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS ) ) 
    {
           fpub_SetMsg(lXmlhandle, 24271, "��ѯ�����ǼǼ�¼����");
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ��ѯ�����ǼǼ�¼����"),
               fpub_GetCompname(lXmlhandle))	
    }	 
    */
  
  /*״̬��� ��Ϊ�ǵ�һ�����Σ����Ա�������*/
  /*1 pljydj���е�pczbs����Ϊ0 */
  if (stPljydj.pczbs > 0)
  {
  	 fpub_SetMsg(lXmlhandle, 24293, "����У���쳣���������μ�¼");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ״̬У���쳣���������μ�¼"),
         fpub_GetCompname(lXmlhandle))	
  }
   /*2 plpcdj����û�ж�Ӧ�����μ�¼ */
  iCount = 0;
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
  snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_ssplpcdj \
  where zwrq='%s' and pljylsh='%s'",sZwrq , sPljylsh);   	
  iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
  if ( iRet < 0 )
  {
  	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
		
		fpub_SetMsg(lXmlhandle, 24294, "��ѯ�������εǼǱ�ʧ��");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ��ѯ�������εǼǱ�ʧ��"),
         fpub_GetCompname(lXmlhandle))	
        
	}
   
  /* end add dci 20141103 */
  /* mod dci 20141103
  EXEC SQL SELECT count(*) INTO :iCount 
       FROM  tips_ssplpcdj
       WHERE zwrq = :sZwrq 
         AND pljylsh = :sPljylsh ;
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
  if ( SQLERR ) 
  {
     fpub_SetMsg(lXmlhandle, 24294, "��ѯ�������εǼǱ�ʧ��");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ��ѯ�������εǼǱ�ʧ��"),
         fpub_GetCompname(lXmlhandle))	
  }	 
  */
    
  if ( iCount > 0 )
  {
     fpub_SetMsg(lXmlhandle, 24293, "����У���쳣���������μ�¼");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,
         Fmtmsg("initPLPCDJ���α������м�¼���쳣icount[%d]",iCount),
         fpub_GetCompname(lXmlhandle))	  	
  }
  /*3 plksfmx����û��״̬��6-�����������ȴ�������صļ�¼*/
  iCount = 0;  
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
  snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_ssplksfmx \
  where zwrq='%s' and pljylsh='%s' and czbd = '6'",sZwrq , sPljylsh);   	
  iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
  if ( iRet < 0 )
  {
  	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
		
		fpub_SetMsg(lXmlhandle, 24277, "��ѯ������˰����ϸ��ʧ��");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ��ѯ������˰����ϸ��ʧ��"),
         fpub_GetCompname(lXmlhandle))	
        
	}
  /* end dci 20141103 */
  
  /* mod dci 20141103  
  EXEC SQL SELECT count(*) INTO :iCount 
       FROM  tips_ssplksfmx
       WHERE zwrq = :sZwrq 
         AND pljydm = :sPljylsh 
         AND czbd = '6';
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
  if ( SQLERR ) 
  {
     fpub_SetMsg(lXmlhandle, 24277, "��ѯ������˰����ϸ��ʧ��");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ��ѯ������˰����ϸ��ʧ��"),
         fpub_GetCompname(lXmlhandle))	
  }	   
  */
  
  if ( iCount > 0 )
  {
     fpub_SetMsg(lXmlhandle, 16999, "��˰����ϸ�������м�¼�����������쳣");
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     LOGRET(COMPRET_FAIL,LM_STD,
        Fmtmsg("initPLPCDJ��˰����ϸ�������м�¼�����������쳣icount[%d]",iCount),
        fpub_GetCompname(lXmlhandle))	  	
  }  

  /* ��ʼ���� 
  EXEC SQL BEGIN WORK ;   */      
  
  /*�����������εǼ���Ϣ*/
  memset(&stPlpcdj,0x00,sizeof(stPlpcdj));
  pstrcopy(stPlpcdj.zwrq, stPljydj.zwrq, sizeof(stPlpcdj.zwrq)); 
  pstrcopy(stPlpcdj.pljydm, stPljydj.pljydm, sizeof(stPlpcdj.pljydm)); 
  pstrcopy(stPlpcdj.pljylsh, stPljydj.pljylsh, sizeof(stPlpcdj.pljylsh));
  pstrcopy(stPlpcdj.plpch, sPlpch, sizeof(stPlpcdj.plpch));     
  stPlpcdj.pclsh = stPljydj.pczbs + 1;     /* ������ˮ�� =1 */ 
  stPlpcdj.ykbs=0;
  stPlpcdj.ykje=0.00;
  stPlpcdj.skbs=0;
  stPlpcdj.skje=0.00;
  stPlpcdj.zjsbbs=0;
  pstrcopy(stPlpcdj.xym, "00", sizeof(stPlpcdj.xym));
  pstrcopy(stPlpcdj.xyxx, "����׼�����,�����ο�ʼ����", sizeof(stPlpcdj.xyxx));  
  stPlpcdj.czbd[0] = '1';                    /* �������׳�ʼ�� */
    
  memset(sBuf, 0x00, sizeof(sBuf));
  COMP_SOFTGETXML("/sys/sysdate",sBuf);
  pstrcopy(stPlpcdj.clqsrq, sBuf, sizeof(stPlpcdj.clqsrq)); /*������ʼ����*/
  pstrcopy(stPlpcdj.cljsrq, sBuf, sizeof(stPlpcdj.cljsrq)); /*�����������*/
  
  memset(sBuf, 0x00, sizeof(sBuf));
  COMP_SOFTGETXML("/sys/systime",sBuf);
  pstrcopy(stPlpcdj.clqssj, sBuf, sizeof(stPlpcdj.clqssj));/*������ʼʱ��*/
  pstrcopy(stPlpcdj.cljssj, sBuf, sizeof(stPlpcdj.cljssj));/*�������ʱ��*/
  pstrcopy(stPlpcdj.qqzjwjm, sFile_short, sizeof(stPlpcdj.qqzjwjm));/* ���������ļ��� */
  pstrcopy(stPlpcdj.zjjgwjm, sFile_ret, sizeof(stPlpcdj.zjjgwjm));/* ��������ļ��� */

	/* add dci 20141103 */
	memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_ssplpcdj", SD_TIPS_SSPLPCDJ, NUMELE(SD_TIPS_SSPLPCDJ), &stPlpcdj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	/* DCIRollback(); */
    	
        fpub_SetMsg(lXmlhandle, 24296, "�����������α�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ�����������α�ʧ��"),
            fpub_GetCompname(lXmlhandle))		
    }

	/* end dci 20141103 */
	/* mod dci 20141103 
  EXEC SQL INSERT INTO tips_ssplpcdj VALUES ( :stPlpcdj );
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
  if ( SQLERR )
  {
  	    /* EXEC SQL ROLLBACK WORK; 
        fpub_SetMsg(lXmlhandle, 24296, "�����������α�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ�����������α�ʧ��"),
            fpub_GetCompname(lXmlhandle))		
  }	     
  */
  
  /* ����������˰����ϸ����׼�����˵ļ�¼ */
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_ssplksfmx set plpch = '%s',clcs  = clcs + 1 \
    where zwrq='%s' and pljylsh='%s' and czbd = '0'",sPlpch, sZwrq , sPljylsh);   	
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24297, "����������˰����ϸ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ����������˰����ϸ��ʧ��"),
            fpub_GetCompname(lXmlhandle))		     
    }
  /* end add dci 20141103 */
  
  /* mod dci 20141103
  EXEC SQL UPDATE tips_ssplksfmx
       SET plpch = :sPlpch,
           clcs  = clcs + 1
       WHERE zwrq = :sZwrq 
         AND pljylsh = :sPljylsh
         AND czbd ='0';              /*�������� 0 ����׼��
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
  if ( SQLERR ) 
  {
  	   /*  EXEC SQL ROLLBACK WORK; 
        fpub_SetMsg(lXmlhandle, 24297, "����������˰����ϸ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ����������˰����ϸ��ʧ��"),
            fpub_GetCompname(lXmlhandle))		
  }
  */
  /*ͳ�Ʊ�������Ҫ������ܱ������ܽ��*/
  iZbs = 0;
  dZje = 0.0;  
  
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
	snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx \
    	where zwrq='%s' and pljylsh='%s' and plpch = '%s'",sZwrq , sPljylsh, sPlpch);  
  LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
    iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cZbs, &cZje);
    iZbs=atoi(cZbs);
    dZje=atof(cZje);

    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
             
          fpub_SetMsg(lXmlhandle, 24298, "ͳ������Ӧ�۱�����Ӧ�۽��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("initPLPCDJͳ������Ӧ�۱�����Ӧ�۽��ʧ��"),
            fpub_GetCompname(lXmlhandle))		     
    }

  /* end add dci 20141103 */
  /* mod dci 20141103
   
  EXEC SQL SELECT COUNT(*), nvl(SUM(jyje), 0.00) INTO :iZbs,:dZje 
       FROM tips_ssplksfmx
       WHERE zwrq = :sZwrq 
        AND  pljylsh = :sPljylsh 
        AND  plpch = :sPlpch;     
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");       
  if ( SQLERR )
  {
  	 /*   EXEC SQL ROLLBACK WORK;
        fpub_SetMsg(lXmlhandle, 24298, "ͳ������Ӧ�۱�����Ӧ�۽��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("initPLPCDJͳ������Ӧ�۱�����Ӧ�۽��ʧ��"),
            fpub_GetCompname(lXmlhandle))		
  }	
  */    
  LOG(LM_STD,Fmtmsg("��ǰ�����账�����Ӧ�۱���[%d],��Ӧ�۽��[%.2f]",iZbs,dZje),"INFO");

  /*�޸����εǼ���Ϣ*/
  stPlpcdj.ykbs = iZbs;
  stPlpcdj.ykje = dZje;
  
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_ssplpcdj set ykbs = %d,ykje=%f \
    where zwrq='%s' and pljylsh='%s' and plpch = '%s'", stPlpcdj.ykbs, stPlpcdj.ykje, sZwrq , sPljylsh,sPlpch);   	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 || iRet ==0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24299, "�����������α�ʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ�����������α�ʧ��"),
          fpub_GetCompname(lXmlhandle))	  
    }
  /* end add dci 20141103 */
  /* mod dci 20141103 
  EXEC SQL UPDATE tips_ssplpcdj 
       SET ykbs  = :stPlpcdj.ykbs,
           ykje  = :stPlpcdj.ykje           
      WHERE zwrq  = :sZwrq 
        AND pljylsh = :sPljylsh
        AND plpch = :sPlpch ;
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");   
  if (( SQLERR ) || ( SQLNOTFOUND_TIPS))
  {
  	 /*  EXEC SQL ROLLBACK WORK;
      fpub_SetMsg(lXmlhandle, 24299, "�����������α�ʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ�����������α�ʧ��"),
          fpub_GetCompname(lXmlhandle))		
  }	
  */     
  
  /*�޸��������׵Ǽ���Ϣ*/
  /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_pljydj set pczbs = pczbs + 1 \
    where zwrq='%s' and pljylsh='%s' ", sZwrq , sPljylsh);   	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 || iRet ==0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24285, "���������Ǽ���Ϣʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ���������Ǽ���Ϣʧ��"),
          fpub_GetCompname(lXmlhandle))		
    }
  /* end dci 20141103 */
  /* mod dci 20141103 
  EXEC SQL UPDATE tips_pljydj 
       SET pczbs = pczbs + 1         /*�����ܱ��� �����εǼǱ��е�pclshͬ��
       WHERE zwrq = :sZwrq 
         AND pljylsh =:sPljylsh;
  SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");   
  if (( SQLERR ) || ( SQLNOTFOUND_TIPS))
  {
  	/*  EXEC SQL ROLLBACK WORK;
      fpub_SetMsg(lXmlhandle, 24285, "���������Ǽ���Ϣʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("initPLPCDJ���������Ǽ���Ϣʧ��"),
          fpub_GetCompname(lXmlhandle))		
   }
   */
   
   /*��ȫ�������ڲ��ύ
   EXEC SQL COMMIT WORK;
   if ( SQLERR )  
   {
      LOG(LM_STD,Fmtmsg("�ύ���ݿ�ʧ��sqlcode=[%d]",sqlca.sqlcode),"ERROR");
      EXEC SQL ROLLBACK WORK;
      fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("���ݿ����ʧ��"));
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPRET_FAIL;    	
   } */ 
   
   /*д���ܱ���*/
   memset(sBuf, 0x00, sizeof(sBuf));
   sprintf(sBuf,"%ld",iZbs);
   COMP_HARDSETXML(sNode_zbs, sBuf);

   /*д���ܽ�� mod by tuql 20090908 */
   memset(sBuf, 0x00, sizeof(sBuf));
   sprintf(sBuf,"%15.2f",dZje);
   COMP_HARDSETXML("/tips/pczje", sBuf);
   
   LOG(LM_STD,Fmtmsg("��ʼ���������ν���..."),"INFO");
   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   return COMPRET_FAIL;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_UpdPLPCDJ
�������: �����������εǼǱ�״̬
�������: 
  �����������εǼǱ�״̬
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  1                  ��¼�ظ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
�������׵ǼǱ�	tips_ssplpcdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��11��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_UpdPLPCDJ(HXMLTREE lXmlhandle)
{
	
    int iParas;
    char sBuf[200+1];
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_SSPLPCDJ stPlpcdj;
    EXEC SQL END   DECLARE SECTION;
  	*/
  	/* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		SDB_TIPS_SSPLPCDJ stPlpcdj;
		int iRet=0;
/* end add dci 20141103 */
  	
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    memset(&stPlpcdj, 0x00, sizeof(stPlpcdj));
    COMP_PARACOUNTCHK(6);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy( stPlpcdj.zwrq, sBuf, sizeof(stPlpcdj.zwrq));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "����������ˮ��")
    pstrcopy( stPlpcdj.pljylsh, sBuf, sizeof(stPlpcdj.pljylsh));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "�������κ�")
    pstrcopy( stPlpcdj.plpch, sBuf, sizeof(stPlpcdj.plpch));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(4, sBuf, "��������")
    pstrcopy( stPlpcdj.czbd, sBuf, sizeof(stPlpcdj.czbd));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(5, sBuf, "��Ӧ��")
    pstrcopy( stPlpcdj.xym, sBuf, sizeof(stPlpcdj.xym));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(6, sBuf, "��Ӧ��Ϣ")
    pstrcopy( stPlpcdj.xyxx, sBuf, sizeof(stPlpcdj.xyxx));
       
    
    /*20.�����������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate",sBuf)
    pstrcopy(stPlpcdj.cljsrq,sBuf,sizeof(stPlpcdj.cljsrq));
    /*21.�������ʱ��*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime",sBuf)
    pstrcopy(stPlpcdj.cljssj,sBuf,sizeof(stPlpcdj.cljssj));
     
    /* add dci 20141103 */
  memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_ssplpcdj \
    set czbd = '%s' \
       ,xym   ='%s' \
       ,xyxx  ='%s' \
       ,cljsrq='%s' \
       ,cljssj='%s' \
    		where zwrq='%s' and pljylsh='%s' and plpch='%s'", \
    		stPlpcdj.czbd,            \
        stPlpcdj.xym,             \
        stPlpcdj.xyxx,            \
        stPlpcdj.cljsrq,          \
        stPlpcdj.cljssj,\
   			stPlpcdj.zwrq , stPlpcdj.pljylsh, stPlpcdj.plpch);   	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 || iRet ==0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24299, "�����������α�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("updPLPCDJ�����������α�ʧ��"),
            fpub_GetCompname(lXmlhandle))	
    }
  /* end dci 20141103 */
  	/* mod dci 20141103
    EXEC SQL UPDATE tips_ssplpcdj
         SET czbd = :stPlpcdj.czbd,
             xym = :stPlpcdj.xym,
             xyxx = :stPlpcdj.xyxx,
             cljsrq = :stPlpcdj.cljsrq,
             cljssj = :stPlpcdj.cljssj
        WHERE zwrq = :stPlpcdj.zwrq 
          AND pljylsh = :stPlpcdj.pljylsh
          AND plpch = :stPlpcdj.plpch;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if ((SQLERR) || (SQLNOTFOUND_TIPS) )	
    {
        fpub_SetMsg(lXmlhandle, 24299, "�����������α�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("updPLPCDJ�����������α�ʧ��"),
            fpub_GetCompname(lXmlhandle))	
    }	   
    */

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
} 

/************************************************************************
��̬�����������
�����������: SYW_TIPS_GenQQZJWJ
�������:�������������ļ�

  
�������: 
��� ��������   ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��


������״̬: 
  ���״̬��         ���˵��
  0                  ����
  -1���������������� ʧ�ܡ���
��־��Ϣ: 
  ��־����           ��־��

��Ҫ�������:
  ����                     ����
 gapsywk:tips_pljydj       ����
 gapsywk:tips_ssplksfmx    ����
 gapsywk:tips_ssplpcdj     ����

ʹ������:
   ���������ļ�����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��12��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_GenQQZJWJ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;*/
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sPlpch[5+1];
    /* add dci 20141103
    EXEC SQL END   DECLARE SECTION;	*/
    FILE *fp1;
    SDB_GENFILE stGenZjFile;
    char sBuf[254];
    char sFile[100];
    char sTmpBuf[254];
    char sResIcxp[30];
    char sResIcxpH[30];
    int  i;
    int  iret;
    int  iflag;
    int  j;
    ICXPCFG SBwpz;
  
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif
  
    COMP_PARACOUNTCHK(5);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq)); 
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(2,sBuf,"����������ˮ��")
    pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPlpch, 0x00, sizeof(sPlpch));
    COMP_GETPARSEPARAS(3,sBuf,"�������κ�")
    pstrcopy(sPlpch, sBuf, sizeof(sPlpch));
      
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFile, 0x00, sizeof(sFile));
    COMP_GETPARSEPARAS(4,sBuf,"���������ļ���")
    pstrcopy(sFile, sBuf, sizeof(sFile));
    trim(sFile);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sResIcxp, 0x00, sizeof(sResIcxp));
    COMP_GETPARSEPARAS(5,sBuf,"ICXP��������")
    pstrcopy(sResIcxp, sBuf, sizeof(sResIcxp));
    
    LOG(LM_STD,Fmtmsg("��������[%s],����������ˮ��[%s],�������κ�[%s],�����ļ�[%s]....",
        sZwrq,sPljylsh,sPlpch,sFile),"INFO");

    /*У��ICXP����������Դ�Ƿ����*/
    if( fpub_GetIcxpCfg(lXmlhandle ,(ICXPCFG *)&SBwpz,sResIcxp)!= MID_SYS_SUCC ) 
    {
        fpub_SetMsg(lXmlhandle, 36003, "������Դ������");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("ICXP����������Դ������[%s]", sResIcxp),"ERROR");
        return COMPRET_FAIL;
    }
    
    /*�Ƚ��ļ�,У��*/
    fp1 = fopen(sFile,"w+");
    if ( fp1 == NULL )
    {
        fpub_SetMsg(lXmlhandle,36004,"���ļ�ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("���ļ�ʧ��errinfo=[%s]",strerror(errno)),"ERROR");
        return COMPRET_FAIL;
    }
  
    memset(&stGenZjFile, 0x00, sizeof(stGenZjFile));
    stGenZjFile.lXmlhandle = lXmlhandle;
    pstrcopy(stGenZjFile.zwrq, sZwrq, sizeof(stGenZjFile.zwrq));
    pstrcopy(stGenZjFile.pljylsh, sPljylsh, sizeof(stGenZjFile.pljylsh));
    pstrcopy(stGenZjFile.plpch, sPlpch, sizeof(stGenZjFile.plpch));
    pstrcopy(stGenZjFile.resicxp, sResIcxp, sizeof(stGenZjFile.resicxp));
    stGenZjFile.fp = fp1;
    
    /* ���������ļ� */
    /* fprintf(fp1, "%s\n", FILE_BEGIN); */
    iret=prv_tips_GenZjFile( stGenZjFile );
    if( iret < 0 )
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        fclose(fp1);
        return COMPRET_FAIL;         
    }
    /* fprintf(fp1, "%s\n", FILE_END);  */
    fclose(fp1);
     
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_ClZJJGWJ
�������: ������������ļ�
�������: ������������ļ�

  
�������: 
��� ��������   ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  ����
  -1���������������� ʧ�ܡ���

��Ҫ�������:
  ����                     ����
 gapsywk:tips_pljydj       ����
 gapsywk:tips_ssplksfmx    ����
 gapsywk:tips_ssplpcdj     ����

ʹ������:
   ������������ļ�����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��12��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_ClZJJGWJ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLKSFMX stPlksfmx;
        SDB_TIPS_SSPLPCDJ stPlpcdj;
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sPlpch[5+1];
        char sSysdate[8+1];
        char sSystime[6+1];
        char sResHxxtResp[30+1];/*������Ӧ������   
        int iClsbbs=0;/* ƽ̨����ʧ�ܱ��� 
        int iZjsbbs = 0;/* ���������쳣ʧ�ܱ���
        int iZbsSucc = 0;
        double dZjeSucc = 0.00;
        char sFileErr[256];
        char sBuf[256];
        char sZjxym[18+1];/* add by tuql 20090908 
    EXEC SQL END   DECLARE SECTION;	
    */
    FILE *fp1, *fperr;
    char sFile[256];
    char sLine[1024];
    char sResIcxp[30+1];
    int  i;
    int  iret;
    int  iflag;
    ICXPCFG SBwpz;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/                  
    char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
    SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLKSFMX stPlksfmx;
        SDB_TIPS_SSPLPCDJ stPlpcdj;
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sPlpch[5+1];
        char sSysdate[8+1];
        char sSystime[6+1];
        char sResHxxtResp[30+1];/*������Ӧ������ */  
        int iClsbbs=0;/* ƽ̨����ʧ�ܱ��� */
        int iZjsbbs = 0;/* ���������쳣ʧ�ܱ��� */
        int iZbsSucc = 0;
        double dZjeSucc = 0.00;
        char cClsbbs[16+1];/* ƽ̨����ʧ�ܱ��� */
        char cZjsbbs[16+1];/* ���������쳣ʧ�ܱ��� */
        char cZbsSucc[16+1];
        char cZjeSucc[32+1];
        char sFileErr[256];
        char sBuf[256];
        char sZjxym[18+1];/* add by tuql 20090908 */
		int iRet=0;
/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif
  
    COMP_PARACOUNTCHK(7);
      
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));  
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(2,sBuf,"����������ˮ��")
    pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPlpch, 0x00, sizeof(sPlpch));
    COMP_GETPARSEPARAS(3,sBuf,"�������κ�")
    pstrcopy(sPlpch, sBuf, sizeof(sPlpch));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFile, 0x00, sizeof(sFile));
    COMP_GETPARSEPARAS(4,sBuf,"���ʽ���ļ���")
    pstrcopy(sFile, sBuf, sizeof(sFile));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFileErr, 0x00, sizeof(sFileErr));
    COMP_GETPARSEPARAS(5,sBuf,"������Ϣ�ļ�")
    pstrcopy(sFileErr, sBuf, sizeof(sFileErr));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sResIcxp, 0x00, sizeof(sResIcxp));
    COMP_GETPARSEPARAS(6,sBuf,"�����ļ���ʽ����")
    pstrcopy(sResIcxp, sBuf, sizeof(sResIcxp));
  
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sResHxxtResp, 0x00, sizeof(sResHxxtResp));  
    COMP_GETPARSEPARAS(7,sBuf,"������Ӧ��Դ����")
    pstrcopy(sResHxxtResp, sBuf, sizeof(sResHxxtResp));
    
    LOG(LM_STD,Fmtmsg("������������ļ���ʼ��������Ӧ��Դ����[%s]���ʽ���ļ���[%s]....",sResHxxtResp, sFile),"INFO");
    LOG(LM_STD,Fmtmsg("��������[%s],�������״���[%s],�������κ�[%s]",sZwrq,sPljylsh,sPlpch),"INFO");
    
    memset(sSysdate, 0x00, sizeof(sSysdate));
    memset(sSystime, 0x00, sizeof(sSystime));
    COMP_SOFTGETXML("/sys/sysdate", sSysdate);
    COMP_SOFTGETXML("/sys/systime", sSystime);
    	     
    /*��ѯ�������׵Ǽ���Ϣ*/
    memset(&stPljydj, 0x00, sizeof(stPljydj));
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_pljydj \
    where zwrq='%s' and pljylsh='%s'",sZwrq, sPljylsh);  
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = prv_SelMulToStruct( sSql1, SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj);
    /*
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPljydj.zwrq, &stPljydj.pljydm, &stPljydj.pljylsh, &stPljydj.pczbs, \
    	&stPljydj.entrustdate, &stPljydj.orgcode, &stPljydj.packno, &stPljydj.workdate, &stPljydj.allnum, \
    	&stPljydj.allamt, &stPljydj.handletype, &stPljydj.payeebankno, &stPljydj.payeeorgcode, \
    	&stPljydj.payeeacct, &stPljydj.payeename, &stPljydj.paybkcode, &stPljydj.chkdate, &stPljydj.chkacctord, \
    	&stPljydj.rzzbs, &stPljydj.rzzje, &stPljydj.zfzbs, &stPljydj.zfzje, &stPljydj.xym, &stPljydj.xyxx, \
    	&stPljydj.czbd, &stPljydj.wcbz, &stPljydj.clqsrq, &stPljydj.clqssj, &stPljydj.cljsrq, &stPljydj.cljssj, \
    	&stPljydj.kzbz, &stPljydj.byzd);*/
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24271, "��ѯ�������׵ǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ��ѯ����������Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))	     
    }

    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT * INTO :stPljydj
             FROM   tips_pljydj
             WHERE  zwrq = :sZwrq
               AND  pljylsh = :sPljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS ))
    {
        fpub_SetMsg(lXmlhandle, 24271, "��ѯ�������׵ǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ��ѯ����������Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))	
    }
    */
    
    /*��ѯ���εǼ���Ϣ*/
    memset(&stPlpcdj, 0x00, sizeof(stPlpcdj));
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_ssplpcdj \
    	where zwrq='%s' and pljylsh='%s' and plpch='%s'",sZwrq, sPljylsh,sPlpch);   
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = prv_SelMulToStruct( sSql1, SD_TIPS_SSPLPCDJ, NUMELE(SD_TIPS_SSPLPCDJ), &stPlpcdj);
    /*  	
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPlpcdj.zwrq,&stPlpcdj.pljydm,&stPlpcdj.pljylsh,\
    	&stPlpcdj.plpch,&stPlpcdj.pclsh,&stPlpcdj.ykbs,&stPlpcdj.ykje,&stPlpcdj.skbs,&stPlpcdj.skje,\
    	&stPlpcdj.zjsbbs,&stPlpcdj.qqzjwjm,&stPlpcdj.zjjgwjm,&stPlpcdj.xym,&stPlpcdj.xyxx,&stPlpcdj.czbd,\
    	&stPlpcdj.clqsrq,&stPlpcdj.clqssj,&stPlpcdj.cljsrq,&stPlpcdj.cljssj,&stPlpcdj.byzd );*/
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24294, "��ѯ�������εǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ClZJJGWJ��ѯ�������εǼǱ�ʧ��"),
            fpub_GetCompname(lXmlhandle))	   
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT * INTO :stPlpcdj
             FROM   tips_ssplpcdj
             WHERE  zwrq = :sZwrq
               AND  pljylsh = :sPljylsh
               AND  plpch = :sPlpch;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS ))
    {
        fpub_SetMsg(lXmlhandle, 24294, "��ѯ�������εǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ClZJJGWJ��ѯ�������εǼǱ�ʧ��"),
            fpub_GetCompname(lXmlhandle))	
    }
    */   
           
    fp1=fopen(sFile,"r");
    if (fp1==NULL)
    {
        fpub_SetMsg(lXmlhandle, 36004, "���ļ�����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ����������ļ�����errinfo=[%s]",strerror(errno)),
            fpub_GetCompname(lXmlhandle))	
    }
  
    /** �ļ�ͷβ��� **/
    /* mod by leejn 20141231 
    fseek(fp1,-4L,2);
    memset(sLine, 0x00, sizeof(sLine));
    if (fgets(sLine,sizeof(sLine),fp1) != NULL)
    {
        if (strncmp(sLine,"END",3) != 0)    �����ļ������һ��Ϊ��END
        {
            fclose(fp1);
            fpub_SetMsg(lXmlhandle, 36007, "У���ļ�β��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,
                Fmtmsg("ClZJJGWJУ����������ļ�β��sline[%s]",sLine),
                fpub_GetCompname(lXmlhandle))	
        }
    }else
    {
        fclose(fp1);
        fpub_SetMsg(lXmlhandle, 36008, "�ļ�Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ��������ļ�Ϊ��,���ļ�β"),
            fpub_GetCompname(lXmlhandle))	
    }

    fseek(fp1,0L,0);   ָ�������ļ�ͷ 
    memset(sLine, 0, sizeof(sLine));
    if (fgets(sLine,sizeof(sLine),fp1)!=NULL)
    {
        if (strncmp(sLine,"BEGIN",5) != 0)  �����ļ���һ������ӦΪ��BEGIN
        {
            fclose(fp1);
            fpub_SetMsg(lXmlhandle, 36009, "У���ļ�ͷ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJУ���ļ�ͷ��"),
                fpub_GetCompname(lXmlhandle))	
        }
    }
    else
    {
        fclose(fp1);
        fpub_SetMsg(lXmlhandle, 36008, "�ļ�Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ��������ļ�Ϊ��,���ļ�ͷ"),
            fpub_GetCompname(lXmlhandle))	
    }
    */

    /*�򿪴�����Ϣ�ļ�*/
    fperr=fopen(sFileErr, "a+");
    if (fperr==NULL)
    {
       fclose(fp1);
       fpub_SetMsg(lXmlhandle, 36004, "���ļ�����");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ���������ʧ���ļ�����errinfo[%s]",strerror(errno)),
           fpub_GetCompname(lXmlhandle))	
    }
    fprintf(fperr, "��������ļ�����ʧ����Ϣ:��������[%s]����������ˮ��[%s]���κ�[%s]�ļ���[%s]\n", sZwrq,sPljylsh,sPlpch,sFile);
      	
      	
    /* ��ʼ����  
    EXEC SQL BEGIN WORK ;*/ 
      
    /*�ļ��崦��*/
    for (iflag=0,i=1; ;i++)
    {
        memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
        memset(sLine, 0x00, sizeof(sLine));
        if (fgets(sLine,sizeof(sLine),fp1)	== NULL)
           break;
        if (strncmp(sLine, "END", 3) == 0)
        {   
           break;      
        }   
        sLine[strlen(sLine)-1]=0;   /*ȥ�����һ�����з�*/
        iret = 0 ;
        iret=SBATCH_FuncICXPUPKG(lXmlhandle,sResIcxp,sLine,strlen(sLine));
        if (iret < 0)
        { 
           iflag = -1; 
           break; 
        }	

        /*�ڴ˽��б������ݱ�ĸ���*/             
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/hxxt/zjjgwj/qzlsh", sBuf);
        stPlksfmx.plmxxh = atoi(sBuf); /* ������ϸ��� */        
				
				/* add dci 20141103 */
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select * from tips_ssplksfmx \
    			where zwrq='%s' and pljylsh='%s' and plpch='%s' and plmxxh=%d",\
    			sZwrq, sPljylsh,sPlpch, stPlksfmx.plmxxh);     	
    		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    		iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx);
    		/*
    		iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPlksfmx.zwrq,&stPlksfmx.pljydm,&stPlksfmx.pljylsh,\
    		 &stPlksfmx.plpch,&stPlksfmx.plmxxh,&stPlksfmx.clcs,&stPlksfmx.workdate,&stPlksfmx.entrustdate,\
    		 &stPlksfmx.taxorgcode,&stPlksfmx.packno,&stPlksfmx.returnterm,&stPlksfmx.chkdate,&stPlksfmx.chkacctord,\
    		 &stPlksfmx.trano,&stPlksfmx.protocolno,&stPlksfmx.dfzh,&stPlksfmx.paybkcode,&stPlksfmx.payopbkcode,\
    		 &stPlksfmx.payacct,&stPlksfmx.payeebankno,&stPlksfmx.handorgname,&stPlksfmx.taxvouno,&stPlksfmx.jyje,\
    		 &stPlksfmx.sxf,&stPlksfmx.zhye,&stPlksfmx.je2,&stPlksfmx.zjrq,&stPlksfmx.zjsj,&stPlksfmx.zjlsh,\
    		 &stPlksfmx.dqdh,&stPlksfmx.jgdh,&stPlksfmx.jygy,&stPlksfmx.zddh,&stPlksfmx.czbd,&stPlksfmx.qsbz,\
    		 &stPlksfmx.xym,&stPlksfmx.xyxx,&stPlksfmx.kzbz,&stPlksfmx.taxpaycode,&stPlksfmx.taxpayname,&stPlksfmx.spxx,\
    		 &stPlksfmx.byzd );  */  		
    		if ( iRet < 0 || iRet == 0)
    		{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        		LOG(LM_STD,Fmtmsg("ZjjgwjCl��ѯʧ��plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -3;  
            break; 
    		}
    		/* end add dci 20141103 */
    
				/* mod dci 20141103 
        EXEC SQL SELECT * INTO :stPlksfmx
             FROM tips_ssplksfmx
             WHERE zwrq  = :sZwrq
              AND pljylsh = :sPljylsh
              AND plpch = :sPlpch 
              AND plmxxh = :stPlksfmx.plmxxh;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        { 
            LOG(LM_STD,Fmtmsg("ZjjgwjCl��ѯʧ��plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -3;  
            break; 
        }
        */
        
        memset(sBuf, 0x00, sizeof(sBuf));     
        COMP_SOFTGETXML("/hxxt/zjjgwj/zczh", sBuf);
        pstrcopy(stPlksfmx.payacct, sBuf, sizeof(stPlksfmx.payacct)); /* �ۿ��ʺ� */
        
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/hxxt/zjjgwj/jyje", sBuf);
        stPlksfmx.jyje = atof(sBuf);   /* Ӧ�۽�� */
        
        /* add by tuql 20090908 ������Ӧ����ܳ���5λ */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sZjxym, 0x00, sizeof(sZjxym));
        COMP_SOFTGETXML("/hxxt/zjjgwj/zjxym", sBuf);
        /*pstrcopy(stPlksfmx.xym, sBuf, sizeof(stPlksfmx.xym)); ��Ӧ��*/
        pstrcopy(sZjxym, sBuf, sizeof(sZjxym)); /*��Ӧ��*/
        trim(sZjxym);

        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/hxxt/zjjgwj/zhye", sBuf);
        stPlksfmx.zhye=atof(sBuf); /*�˻����*/

        memset(sBuf, 0x00, sizeof(sBuf));     
        COMP_SOFTGETXML("/hxxt/zjjgwj/zjrq", sBuf);
        pstrcopy(stPlksfmx.zjrq, sBuf, sizeof(stPlksfmx.zjrq)); /* �������� */
        
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/hxxt/zjjgwj/zjsj", sBuf);
        pstrcopy(stPlksfmx.zjsj, sBuf, sizeof(stPlksfmx.zjsj));  /* ����ʱ�� */
        
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML("/hxxt/zjjgwj/zjlsh", sBuf);
        pstrcopy(stPlksfmx.zjlsh, sBuf, sizeof(stPlksfmx.zjlsh)); /*������ˮ��*/
        trim(stPlksfmx.zjlsh);       

        /* ��ȡ��Ӧ��Ϣ */
        memset(stPlksfmx.xyxx, 0x00, sizeof(stPlksfmx.xyxx));
        memset(sBuf, 0x00, sizeof(sBuf));

        /* add dci 20141103 */
        /* ��Ʒ���޴˱�ʹ���пɸ��ݺ�����Ӧ�롢��Ӧ��Ϣ����
        memset( sSql1, 0x00, sizeof( sSql1 ) );
				snprintf( sSql1, sizeof(sSql1), "SELECT orespcode, respmsg FROM trc_respcodecfg\
    			WHERE resname='%s' AND irespcode ='%s'",sResHxxtResp,sZjxym);     
    		iRet = DBSelectToMultiVar(sErrmsg, sSql1,&sResHxxtResp, &sZjxym);
    		if ( iRet < 0 )
    		{
        	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        	LOG(LM_STD,Fmtmsg("ZjjgwjCl����ʧ��plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -5;  
            break;
        
    		}
    		if ( iRet == 0)
    		{
        	 �Ѹ��³���ļ�¼д����������ʧ���ļ��� 
            pstrcopy(stPlksfmx.xyxx, "δ֪����", sizeof(stPlksfmx.xyxx));
            pstrcopy(stPlksfmx.xym, "99004", sizeof(stPlksfmx.xym));      	
        }else
        {
            trim(stPlksfmx.xyxx);
            memset(stPlksfmx.xym, 0x00, sizeof(stPlksfmx.xym));
            trim(sBuf);
            pstrcopy(stPlksfmx.xym, sBuf, sizeof(stPlksfmx.xym));            
        } 	
        */
        /* end add dci 20141103 */
        
        /* mod dci 20141103
        EXEC SQL SELECT orespcode, respmsg INTO :sBuf, :stPlksfmx.xyxx
             FROM trc_respcodecfg
             WHERE resname = :sResHxxtResp
               AND irespcode=:sZjxym;/* mod by tuql 20090908 AND irespcode=:stPlksfmx.xym; 
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        { 
            LOG(LM_STD,Fmtmsg("ZjjgwjCl����ʧ��plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -5;  
            break; 
        } 
        
        if ( SQLNOTFOUND_TIPS )
        {
        	 �Ѹ��³���ļ�¼д����������ʧ���ļ��� 
            pstrcopy(stPlksfmx.xyxx, "δ֪����", sizeof(stPlksfmx.xyxx));
            pstrcopy(stPlksfmx.xym, "99004", sizeof(stPlksfmx.xym));      	
        }else
        {
            trim(stPlksfmx.xyxx);
            memset(stPlksfmx.xym, 0x00, sizeof(stPlksfmx.xym));
            trim(sBuf);
            pstrcopy(stPlksfmx.xym, sBuf, sizeof(stPlksfmx.xym));            
        } 
        */                  

        /* ��Ӧ��Ϊ�㣬���ۿ�ɹ�,��֮Ϊʧ�� mod by tuql 20090908*/
		/*��������Ӧ��ת��Ϊƽ̨�ڲ�������ϸ����״̬��־*/
		memset(sBuf, 0x00, sizeof(sBuf));
		LOG(LM_DEBUG, Fmtmsg("begin fpub_GetRespInValue src[%s]", sZjxym), "INFO");
		fpub_GetRespOutValue(lXmlhandle, "xym_tips_hxxt2tips", sZjxym, 1, sBuf, sizeof(sBuf)-1);
		LOG(LM_DEBUG,  Fmtmsg("end fpub_GetRespInValue dst[%s]", sBuf), "INFO");
		trim(sBuf);
		pstrcopy(stPlksfmx.xym, sBuf, sizeof(stPlksfmx.xym));
		COMP_SOFTGETXML(XMLNM_RESPMSG, stPlksfmx.xyxx);
		if (atoi(stPlksfmx.xym) == 90000)
        {
            stPlksfmx.czbd[0]='7';
        }else
        {
            stPlksfmx.czbd[0]='8';
        } 
		
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "update tips_ssplksfmx \
    		set	xym   ='%s',\
    				xyxx  ='%s',\
    				jyje  =%0.2f,\
    				czbd  ='%s',\
    				zjrq  ='%s',\
    				zjsj  ='%s',\
    				zjlsh ='%s' \
    			WHERE zwrq   ='%s'\
    			  AND pljylsh='%s'\
    			  AND plpch  ='%s'\
    			  AND plmxxh =%d\
    			  AND payacct='%s'",\
    			  stPlksfmx.xym ,stPlksfmx.xyxx,stPlksfmx.jyje,stPlksfmx.czbd,stPlksfmx.zjrq\
          ,stPlksfmx.zjsj,stPlksfmx.zjlsh,sZwrq,sPljylsh,sPlpch,stPlksfmx.plmxxh,stPlksfmx.payacct);
        LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")       	
    		iRet = DCIExecuteDirect(sSql1);	 
    		if ( iRet < 0 )
    		{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		LOG(LM_STD,Fmtmsg("ZjjgwjCl����ʧ��plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -2;  
            break; 
    		}
    		if( iRet == 0)
    		{
    		 		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        		/* �Ѹ��³���ļ�¼д����������ʧ���ļ��� */
            iClsbbs++;
            LOG(LM_STD,Fmtmsg("����ʧ��,��������δ�ҵ���Ӧ��¼[%ld],[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            fprintf(fperr, "%s|����ʧ��,��������δ�ҵ���Ӧ��¼\n", sLine); 
            continue;      	
    		}	
        /* end add dci 20141103 */
        /* mod dci 20141103        
        EXEC SQL UPDATE tips_ssplksfmx 
            SET  xym      = :stPlksfmx.xym,
                 xyxx     = :stPlksfmx.xyxx,
                 jyje     = :stPlksfmx.jyje,   
                 czbd     = :stPlksfmx.czbd,
                 zjrq     = :stPlksfmx.zjrq,
                 zjsj     = :stPlksfmx.zjsj,   
                 zjlsh    = :stPlksfmx.zjlsh  
            WHERE zwrq  = :sZwrq
              AND pljylsh = :sPljylsh
              AND plpch = :sPlpch 
              AND plmxxh = :stPlksfmx.plmxxh 
              AND payacct  = :stPlksfmx.payacct;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        { 
            LOG(LM_STD,Fmtmsg("ZjjgwjCl����ʧ��plmxxh[%ld],jfzh[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            iflag = -2;  
            break; 
        }
        
        if ( SQLNOTFOUND_TIPS )
        {
        	/* �Ѹ��³���ļ�¼д����������ʧ���ļ��� 
            iClsbbs++;
            LOG(LM_STD,Fmtmsg("����ʧ��,��������δ�ҵ���Ӧ��¼[%ld],[%s]", stPlksfmx.plmxxh, stPlksfmx.payacct),"ERROR");
            fprintf(fperr, "%s|����ʧ��,��������δ�ҵ���Ӧ��¼\n", sLine); 
            continue;      	
        } 
        */
        /* �������ۿ�ɹ�,���˰Ʊ��Ϣ�Ǽǵ�tips_pzsj����ȥ */
        if(atoi(stPlksfmx.xym)==90000)
        {
            iret = prv_tips_InitPZSJ_pl(lXmlhandle, stPlksfmx); 
            if ( iret != 0 )
            {
                LOG(LM_STD,Fmtmsg("ZjjgwjCl����ƾ֤��Ϣʧ��plmxxh[%ld][%s],ret=[%d]", stPlksfmx.plmxxh, stPlksfmx.payacct, iret),"ERROR");
                iflag = -4;  
                continue;            
            }
        }    
        
        
    }
    fclose(fp1);
    fclose(fperr);
	
    if (iflag < 0)
    {
        /* EXEC SQL ROLLBACK WORK; */
        fpub_SetMsg(lXmlhandle, 36009, "�������������Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,
            Fmtmsg("ClZJJGWJ�������������Ϣʧ��iflag[%d]",iflag),
            fpub_GetCompname(lXmlhandle))	
    }  
    
    /*һ�θ��±�����������Ӧ��Ϣ
    EXEC SQL UPDATE tips_ssplksfmx SET tips_ssplksfmx.xyxx = 
         (
            SELECT respmsg FROM trc_respcodecfg b
            WHERE tips_ssplksfmx.xym = b.orespcode
              AND b.resname = :sResHxxtResp
         )
         WHERE zwrq = :sZwrq
           AND pljylsh = :sPljylsh
           AND plpch = :sPlpch ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        EXEC SQL ROLLBACK WORK;
       fpub_SetMsg(lXmlhandle, 36008, "����������Ӧ�����");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ����������Ӧ�����"),
           fpub_GetCompname(lXmlhandle))		
    }*/
    
    /* mod by tuql 20090909 ��36012��Ӧ��ĳ�99004 */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "update tips_ssplksfmx \
    		SET  xym      = '99004',             \
    			xyxx     = '����û�������۽��',\
    			czbd     = '8'    				       \
    			WHERE zwrq   ='%s'\
    			  AND pljylsh='%s'\
    			  AND plpch  ='%s'\
    			  AND czbd = '6'",\
    			  sZwrq ,sPljylsh ,sPlpch);               	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        
       	fpub_SetMsg(lXmlhandle, 36009, "�������������Ϣʧ��");
       	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       	LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ�������������Ϣʧ��"),
           fpub_GetCompname(lXmlhandle))		
    }    
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL UPDATE tips_ssplksfmx 
        SET  xym      = '99004',
             xyxx     = '����û�������۽��',
             czbd     = '8'
        WHERE zwrq  = :sZwrq
          AND pljylsh = :sPljylsh
          AND plpch = :sPlpch 
          AND czbd = '6';     
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")    
    if ( SQLERR )
    {
       /* EXEC SQL ROLLBACK WORK;
       fpub_SetMsg(lXmlhandle, 36009, "�������������Ϣʧ��");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ�������������Ϣʧ��"),
           fpub_GetCompname(lXmlhandle))		
    }
    */    	       
    /*ͳ�� ʵ�۱�����ʵ�۽��*/
    iZbsSucc = 0;
    dZjeSucc = 0.00;
    /* add dci 20141103 */
  	memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx \
    	where zwrq='%s' and pljylsh='%s' and plpch = '%s' AND czbd = '7'",sZwrq , sPljylsh, sPlpch);  
	LOG(LM_DEBUG, Fmtmsg("sql [%s]", sSql1), "INFO");
	iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,cZbsSucc, cZjeSucc);
    iZbsSucc=atoi(cZbsSucc);
    dZjeSucc=atof(cZjeSucc);

    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24277, "��ѯ������˰����ϸ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJͳ��ʵ�۱��������ʧ��"),
            fpub_GetCompname(lXmlhandle))			     
    }

  	/* end add dci 20141103 */
    /* mod dci 20141103
    EXEC SQL SELECT COUNT(*),NVL(SUM(jyje),0.00) INTO :iZbsSucc,:dZjeSucc
    	 FROM tips_ssplksfmx
        WHERE zwrq  = :sZwrq 
          AND pljylsh = :sPljylsh
          AND plpch = :sPlpch
          AND czbd = '7';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        /* EXEC SQL ROLLBACK WORK;
        fpub_SetMsg(lXmlhandle, 24277, "��ѯ������˰����ϸ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJͳ��ʵ�۱��������ʧ��"),
            fpub_GetCompname(lXmlhandle))				
    }	   
  	*/
  	
    /*ͳ�� ���������쳣ʧ�ܱ���......*/
    iZjsbbs = 0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM tips_ssplksfmx \
    	where zwrq='%s' and pljylsh='%s' and plpch = '%s' AND xym in ('-9999','-9998','1644')",\
    	sZwrq , sPljylsh, sPlpch);  
    iRet = DBSelectToVar(sErrmsg,&iZjsbbs, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24277, "��ѯ������˰����ϸ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJͳ�����������쳣ʧ�ܱ���ʧ��"),
            fpub_GetCompname(lXmlhandle))				     
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103  
    EXEC SQL SELECT COUNT(*) INTO :iZjsbbs
    	 FROM tips_ssplksfmx
        WHERE zwrq  = :sZwrq 
          AND pljylsh = :sPljylsh
          AND plpch = :sPlpch
          AND xym in ('-9999','-9998','1644') ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        /* EXEC SQL ROLLBACK WORK;
        fpub_SetMsg(lXmlhandle, 24277, "��ѯ������˰����ϸ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJͳ�����������쳣ʧ�ܱ���ʧ��"),
            fpub_GetCompname(lXmlhandle))				
    }	       
    */
    
  	/*�������εǼǱ���Ϣ*/
  	/* add dci 20141103 */
  	memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "update tips_ssplpcdj \
    		SET skbs  = skbs + %d,\
           	skje  = skje + %f,\
           	cljsrq = '%s',    \
           	cljssj = '%s',    \
           	zjsbbs = %d    \
    			WHERE zwrq   ='%s'\
    			  AND pljylsh='%s'\
    			  AND plpch  ='%s'",\
    				iZbsSucc \
    			,dZjeSucc\
    			,sSysdate  \
          ,sSystime \
          ,iZjsbbs  \
    			,sZwrq    \
    			,sPljylsh \
    			,sPlpch   );               	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24299, "�����������α�ʧ��");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ�����������α�ʧ��"),
           fpub_GetCompname(lXmlhandle))				
    }    
  /* end dci 20141103 */
  /* mod dci 20141103
  EXEC SQL UPDATE tips_ssplpcdj 
       SET skbs  = skbs + :iZbsSucc,     /* ʵ�۱��� 
           skje  = skje + :dZjeSucc,     /* ʵ�۽�� 
           cljsrq = :sSysdate,          /* ����������� 
           cljssj = :sSystime,          /* �������ʱ�� 
           zjsbbs = :iZjsbbs           /* ��������ʧ�ܱ��� 
      WHERE zwrq  = :sZwrq 
        AND pljylsh = :sPljylsh
        AND plpch = :sPlpch ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS))
    {
      /*  EXEC SQL ROLLBACK WORK;
       fpub_SetMsg(lXmlhandle, 24299, "�����������α�ʧ��");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ�����������α�ʧ��"),
           fpub_GetCompname(lXmlhandle))		
    }	
    */     
    
    /*���������ǼǱ���Ϣ*/
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_pljydj \
    		SET rzzbs  = rzzbs + %d, \
           rzzje  = rzzje + %f,  \
           cljsrq = '%s',   \
           cljssj = '%s'    \
    			WHERE zwrq   ='%s'\
    			  AND pljylsh='%s'",\
    				iZbsSucc \
    			,dZjeSucc\
    			,sSysdate  \
          ,sSystime \
          ,sZwrq    \
    			,sPljylsh );               	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24299, "�����������α�ʧ��");
       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
       LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ�����������α�ʧ��"),
           fpub_GetCompname(lXmlhandle))				
    } 
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL UPDATE tips_pljydj 
         SET rzzbs  = rzzbs + :iZbsSucc,     /* �����ܱ���        
             rzzje  = rzzje + :dZjeSucc,     /* �����ܽ��                 
             cljsrq = :sSysdate,            /* �����������    
             cljssj = :sSystime            /* �������ʱ�� 
        WHERE zwrq  = :sZwrq  
          AND pljylsh = :sPljylsh ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS))
    {
       /*  EXEC SQL ROLLBACK WORK;
        fpub_SetMsg(lXmlhandle, 24285, "���������ǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClZJJGWJ���������ǼǱ�ʧ��"),
            fpub_GetCompname(lXmlhandle))	
    }
    */
 	     
    /*��ȫ�������ڲ��ύ
    EXEC SQL COMMIT WORK;
    if ( SQLERR )  
    {
       LOG(LM_STD,Fmtmsg("���ݿ��ύʧ��sqlcode=[%d]",sqlca.sqlcode),"ERROR");
       EXEC SQL ROLLBACK WORK;
       fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("���ݿ����ʧ��"));
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       return COMPRET_FAIL;    	
    }*/
    
    LOG(LM_STD,Fmtmsg("������������ļ�����...."),"INFO");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_GenPLKSFHZ
�������: ����������˰�ѻ�ִ
�������: ����������˰�ѻ�ִ

  
�������: 
��� ��������   ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  ����
  -1���������������� ʧ�ܡ���

��Ҫ�������:
    ����              ����
    tips_ssplksfmx    ��ѯ


ʹ������:
   ������������ļ�����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��12��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_GenPLKSFHZ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLKSFMX stPlksfmx;
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sTraNo[8+1];/* ������ˮ�� 
        double dSkje;
        char sTaxVouNo[18+1];/* ˰Ʊ���� 
        char sXym[5+1];/* ��Ӧ�� 
        char sXyxx[60+1];/* ��Ӧ��Ϣ 
    EXEC SQL END   DECLARE SECTION;
    */
  	
    char sBuf[256];
    char sTmpBuf[256];
  	int i;
  	int iflag;
  	
  	/* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		CURSOR cur;
		SDB_TIPS_PLJYDJ stPljydj;
        SDB_TIPS_SSPLKSFMX stPlksfmx;
        char sZwrq[8+1];
        char sPljylsh[8+1];
        char sTraNo[8+1];/* ������ˮ�� */
        double dSkje;
        char sTaxVouNo[18+1];/* ˰Ʊ���� */
        char sXym[5+1];/* ��Ӧ�� */
        char sXyxx[60+1];/* ��Ӧ��Ϣ */
		int iRet=0;
/* end add dci 20141103 */
  	
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    memset(&stPljydj, 0x00, sizeof(stPljydj));
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));  
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(2, sBuf, "����������ˮ��")
    pstrcopy( sPljylsh, sBuf, sizeof(sPljylsh));
    
    LOG(LM_STD,Fmtmsg("����������˰�ѻ�ִ��ʼ����...��������[%s]����������ˮ��[%s]",
        sZwrq, sPljylsh),"INFO");
        
    /*��ѯ�������׵Ǽ���Ϣ*/
    memset(&stPljydj, 0x00, sizeof(stPljydj));
    /* add dci 20141103 */
    
    /* end dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_pljydj \
    	where zwrq='%s' and pljylsh='%s'",sZwrq , sPljylsh); 	
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")   
    iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_PLJYDJ, NUMELE(SD_TIPS_PLJYDJ), &stPljydj);
    /*   
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPljydj.zwrq, &stPljydj.pljydm, &stPljydj.pljylsh, &stPljydj.pczbs, \
    	&stPljydj.entrustdate, &stPljydj.orgcode, &stPljydj.packno, &stPljydj.workdate, &stPljydj.allnum, \
    	&stPljydj.allamt, &stPljydj.handletype, &stPljydj.payeebankno, &stPljydj.payeeorgcode, \
    	&stPljydj.payeeacct, &stPljydj.payeename, &stPljydj.paybkcode, &stPljydj.chkdate, &stPljydj.chkacctord, \
    	&stPljydj.rzzbs, &stPljydj.rzzje, &stPljydj.zfzbs, &stPljydj.zfzje, &stPljydj.xym, &stPljydj.xyxx, \
    	&stPljydj.czbd, &stPljydj.wcbz, &stPljydj.clqsrq, &stPljydj.clqssj, &stPljydj.cljsrq, &stPljydj.cljssj, \
    	&stPljydj.kzbz, &stPljydj.byzd);*/
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24271, "��ѯ�������׵ǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ��ѯ����������Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))	    
    }

    /* mod dci 20141103 
    EXEC SQL SELECT * INTO :stPljydj
             FROM   tips_pljydj
             WHERE  zwrq = :sZwrq
               AND  pljylsh = :sPljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if (( SQLERR ) || ( SQLNOTFOUND_TIPS ))
    {
        fpub_SetMsg(lXmlhandle, 24271, "��ѯ�������׵ǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ��ѯ����������Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))	
    }    
    */
    
    /* ��������ͷ������ */
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/PayBkCode",stPljydj.paybkcode);/* �������к� */
    COMP_HARDSETXML("/tips/PayBkCode",stPljydj.paybkcode);
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/EntrustDate",sZwrq);/* tipsר��ǰ���������� */
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/PackNo",sPljylsh); /*���صİ���ˮ��*/
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/OriTaxOrgCode",stPljydj.orgcode);/* ԭ���ջ��ش��� */
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/OriEntrustDate",stPljydj.entrustdate);/* ԭί������ */
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/OriPackNo",stPljydj.packno);/* ԭ����ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    sprintf(sBuf,"%d",stPljydj.allnum);
    COMP_SOFTSETXML("/CFX/MSG/BatchHead2102/AllNum",sBuf);/* �ܱ��� */
    
    memset(sBuf, 0x00, sizeof(sBuf));
    sprintf(sBuf,"%.2f",stPljydj.allamt);
    COMP_SOFTSETXML("/CFX/MSG/BatchHead2102/AllAmt",sBuf);/* �ܽ�� */
    
    memset(sBuf, 0x00, sizeof(sBuf));
    sprintf(sBuf,"%d",stPljydj.rzzbs);
    COMP_SOFTSETXML("/CFX/MSG/BatchHead2102/SuccNum",sBuf);/* �ɹ����� */
    
    memset(sBuf, 0x00, sizeof(sBuf));
    sprintf(sBuf,"%.2f",stPljydj.rzzje);
    COMP_SOFTSETXML("/CFX/MSG/BatchHead2102/SuccAmt",sBuf);/* �ɹ���� */ 
    
    memset(sBuf, 0x00, sizeof(sBuf));
    if (   stPljydj.wcbz[0]=='0'
         ||stPljydj.wcbz[0]=='1'
         ||stPljydj.wcbz[0]=='2'
         ||stPljydj.wcbz[0]=='9'
        )
       strcpy(sBuf,"90000");
    else
       strcpy(sBuf,"24020");
  
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/Result",sBuf);
    COMP_HARDSETXML("/CFX/MSG/BatchHead2102/AddWord",trim(stPljydj.xyxx));
    
    /* ����ҵ����ϸ�� */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT trano, jyje, taxvouno, xym, xyxx FROM  tips_ssplksfmx\
    	WHERE zwrq = '%s' and pljylsh = '%s' ORDER BY plmxxh",sZwrq,sPljylsh); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("OPEN CUR sSql1[%s]...",sSql1),"INFO")   
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        
        fpub_SetMsg(lXmlhandle,36001, "���α�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ��cur_ksfmx_plhz�α�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }        
    /* end dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL DECLARE cur_ksfmx_plhz CURSOR for 
        SELECT trano, jyje, taxvouno, xym, xyxx
        FROM  tips_ssplksfmx 
        WHERE zwrq = :sZwrq 
         AND  pljylsh = :sPljylsh
         ORDER BY plmxxh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_ksfmx_plhz;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_ksfmx_plhz",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,36001, "���α�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GenPLKFSHZ��cur_ksfmx_plhz�α�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*��ʼѭ��*/ 
    /* add dci 20141103 */
    
		for (i=1,iflag=0;;i++)
    {
    		    	
        memset(sTraNo, 0x00, sizeof(sTraNo));
        memset(sTaxVouNo, 0x00, sizeof(sTaxVouNo));
        memset(sXym, 0x00, sizeof(sXym));
        memset(sXyxx, 0x00, sizeof(sXyxx));
        dSkje = 0.00 ;
                
        iRet = DCIFetch(cur);
        if ( iRet < 0 )
    		{
        	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        	
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("GenPLKFSHZ��cur�α��ȡ����ʧ��"),"ERROR");
        	break;
    		}  
    		if ( iRet == 0 )
          break;       
        
        strncpy( sTraNo, DCIFieldAsString(cur, 0 ), sizeof( sTraNo ) );
        dSkje = atof( DCIFieldAsString(cur, 1 ) );
        strncpy( sTaxVouNo, DCIFieldAsString(cur, 2 ), sizeof( sTaxVouNo ) );
        strncpy( sXym, DCIFieldAsString(cur, 3 ), sizeof( sXym ) );
        strncpy( sXyxx, DCIFieldAsString(cur, 4 ), sizeof( sXyxx ) );           
        
        trim(sTraNo);
        trim(sTaxVouNo);
        trim(sXym);
        trim(sXyxx);
            
        /*����¼���ݷŵ�XML�� */
        /* ������ˮ�� */
        memset(sBuf, 0x00, sizeof(sBuf));     
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/OriTraNo",i);
     	  COMP_SOFTSETXML(sBuf,sTraNo);
     	  /* ���׽�� */
     	  memset(sBuf, 0x00, sizeof(sBuf));
     	  memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TraAmt",i);
     	  sprintf(sTmpBuf,"%.2f",dSkje);
     	  COMP_SOFTSETXML(sBuf,sTmpBuf);
     	  /* ˰Ʊ���� */
     	  memset(sBuf, 0x00, sizeof(sBuf));
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TaxVouNo",i);
     	  COMP_SOFTSETXML(sBuf,sTaxVouNo);
     	  /* ��˰������ */
     	  memset(sBuf, 0x00, sizeof(sBuf));
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TaxDate",i);
     	  COMP_SOFTSETXML(sBuf,sZwrq);   /*��˰����ӦΪ��̨����������*/
     	  /* ������--��Ӧ�� */ 
     	  memset(sBuf, 0x00, sizeof(sBuf));
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/Result",i);
     	  COMP_SOFTSETXML(sBuf, sXym);
     	  /* ����--��Ӧ��Ϣ */
     	  memset(sBuf, 0x00, sizeof(sBuf));
     	  sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/AddWord",i);
     	  COMP_SOFTSETXML(sBuf,sXyxx);                        
       
    }
    

		DCIFreeCursor(cur);
   	/* end add dci 20141103 */
   	
    /* mod dci 20141103 
    for (i=1,iflag=0;;i++)
    {
        memset(sTraNo, 0x00, sizeof(sTraNo));
        memset(sTaxVouNo, 0x00, sizeof(sTaxVouNo));
        memset(sXym, 0x00, sizeof(sXym));
        memset(sXyxx, 0x00, sizeof(sXyxx));
        dSkje = 0.00 ;
        
        EXEC SQL FETCH cur_ksfmx_plhz INTO :sTraNo, :dSkje, :sTaxVouNo, :sXym, :sXyxx;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_ksfmx_plhz", sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("GenPLKFSHZ��cur_ksfmx_plhz�α��ȡ����ʧ��"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;
        /*����¼���ݷŵ�XML��
        /* ������ˮ�� 
        memset(sBuf, 0x00, sizeof(sBuf));     
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/OriTraNo",i);
     	COMP_SOFTSETXML(sBuf,sTraNo);
     	/* ���׽�� 
     	memset(sBuf, 0x00, sizeof(sBuf));
     	memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TraAmt",i);
     	sprintf(sTmpBuf,"%.2f",dSkje);
     	COMP_SOFTSETXML(sBuf,sTmpBuf);
     	/* ˰Ʊ���� 
     	memset(sBuf, 0x00, sizeof(sBuf));
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TaxVouNo",i);
     	COMP_SOFTSETXML(sBuf,sTaxVouNo);
     	/* ��˰������ 
     	memset(sBuf, 0x00, sizeof(sBuf));
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/TaxDate",i);
     	COMP_SOFTSETXML(sBuf,sZwrq);   /*��˰����ӦΪ��̨����������*/
     	/* ������--��Ӧ�� 
     	memset(sBuf, 0x00, sizeof(sBuf));
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/Result",i);
     	COMP_SOFTSETXML(sBuf, sXym);
     	/* ����--��Ӧ��Ϣ 
     	memset(sBuf, 0x00, sizeof(sBuf));
     	sprintf(sBuf,"/CFX/MSG/BatchReturn2102|%d/AddWord",i);
     	COMP_SOFTSETXML(sBuf,sXyxx);        	
        
    }	
    EXEC SQL CLOSE cur_ksfmx_plhz;    
    /* EXEC SQL FREE  cur_ksfmx_plhz; 
    */
     
    if (iflag < 0)
    {
        fpub_SetMsg(lXmlhandle,36010,"����������˰�ѻ�ִ");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����������˰�ѻ�ִiflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }            
    LOG(LM_STD,Fmtmsg("����������˰�ѻ�ִ����"),"INFO");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;

}

/************************************************************************
��̬�����������
��������: SYW_TIPS_ZfChkPLJYDJ
����: У��ֹ��ԭ������ԭ�����Ƿ����
����ӿڣ�
����ӿڣ� 
  0 -- У��ɹ�
  1 -- ԭ��������
  2 -- ԭ���ײ�����
 -1 -- ϵͳ����
 
�������: 
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
�������׵ǼǱ�	tips_pljydj
������˰����ϸ�� tips_ssplksfmx

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��16��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_ZfChkPLJYDJ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;*/
        char sTaxOrgCode[12+1];
        char sOriEntrustDate[8+1];
        char sOriPackNo[8+1];
        char sOriTraNo[8+1];
        char sStopType[1+1];
        int  iCount=0;
    /* add dci 20141103
    EXEC SQL END DECLARE SECTION;*/
    int i,iret=0;
    int iflag=0;
    char sBuf[256];
	
		char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
	fpub_InitSoComp(lXmlhandle);
	
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")  
    #endif
   
    /*��ȡ�������  --S*/
    COMP_PARACOUNTCHK(5)
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(1,sBuf,"���ջ��ش���");
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sOriEntrustDate, 0x00, sizeof(sOriEntrustDate));
    COMP_GETPARSEPARAS(2,sBuf,"ԭί������");
    pstrcopy(sOriEntrustDate, sBuf, sizeof(sOriEntrustDate));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sOriPackNo, 0x00, sizeof(sOriPackNo));
    COMP_GETPARSEPARAS(3,sBuf,"ԭ����ˮ��");
    pstrcopy(sOriPackNo, sBuf, sizeof(sOriPackNo));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sOriTraNo, 0x00, sizeof(sOriTraNo));
    COMP_GETPARSEPARAS(4,sBuf,"ԭ������ˮ��");
    pstrcopy(sOriTraNo, sBuf, sizeof(sOriTraNo));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sStopType, 0x00, sizeof(sStopType));
    COMP_GETPARSEPARAS(5,sBuf,"ֹ������");
    pstrcopy(sStopType, sBuf, sizeof(sStopType));
    
    LOG(LM_STD,Fmtmsg("У��ֹ���������ʼ����..."), fpub_GetCompname(lXmlhandle)) 
    LOG(LM_STD,Fmtmsg("���ջ��ش���[%s],ԭί������[%s],ԭ����ˮ��[%s],ԭ������ˮ��[%s],ֹ������[%s]...",
        sTaxOrgCode, sOriEntrustDate, sOriPackNo, sOriTraNo, sStopType), fpub_GetCompname(lXmlhandle))    
    
    iCount = -1 ;
    if ( sStopType[0] == '1')/* ����ֹ�� */
    {
    		/* add dci 20141103 */
    		
				memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_pljydj\
    	 		where orgcode='%s' and entrustdate='%s' and packno='%s'",sTaxOrgCode,sOriEntrustDate,sOriPackNo);     	
    		iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    		if ( iRet < 0 )
    		{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        		fpub_SetMsg(lXmlhandle, 24301, "��ѯֹ��ԭ�����׳���");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ZfChkPLJYDJ��ѯֹ��ԭ�����׳���"),fpub_GetCompname(lXmlhandle));	
    		}
    		/* end add dci 20141103 */
    		/* mod dci 20141103 
        EXEC SQL SELECT COUNT(*) INTO :iCount
             FROM tips_pljydj
             WHERE orgcode=:sTaxOrgCode
               AND entrustdate=:sOriEntrustDate
               AND packno=:sOriPackNo;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {
            fpub_SetMsg(lXmlhandle, 24301, "��ѯֹ��ԭ�����׳���");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ZfChkPLJYDJ��ѯֹ��ԭ�����׳���"),fpub_GetCompname(lXmlhandle));	
        }
        */
        
        if ( iCount < 1 )
        {
            fpub_SetMsg(lXmlhandle, 94055, "ԭֹ����������");
            fpub_SetCompStatus(lXmlhandle, 1);
            LOGRET(COMPRET_FAIL,LM_STD,"ZfChkPLJYDJԭֹ����������",fpub_GetCompname(lXmlhandle));
        }
    }else/* ����ֹ�� */
    {
    		/* add dci 20141103 */
    		
				memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_ssplksfmx\
    	 		where taxorgcode='%s' and entrustdate='%s' and packno='%s' and trano='%s'",sTaxOrgCode,sOriEntrustDate,sOriPackNo,sOriTraNo);     	
    		iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    		if ( iRet < 0 )
    		{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        		fpub_SetMsg(lXmlhandle, 24301, "��ѯֹ��ԭ�����׳���");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ZfChkPLJYDJ��ѯֹ��ԭ�����׳���"),fpub_GetCompname(lXmlhandle));	
    		}
    		/* end add dci 20141103 */
    		
    		/* mod dci 20141103 
        EXEC SQL SELECT COUNT(*) INTO :iCount
             FROM tips_ssplksfmx
             WHERE taxorgcode=:sTaxOrgCode
               AND entrustdate=:sOriEntrustDate
               AND packno=:sOriPackNo
               AND trano=:sOriTraNo;        
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {
            fpub_SetMsg(lXmlhandle, 24301, "��ѯֹ��ԭ�����׳���");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ZfChkPLJYDJ��ѯֹ��ԭ�����׳���"),fpub_GetCompname(lXmlhandle));	
        }
        */
        if ( iCount < 1 )
        {
            fpub_SetMsg(lXmlhandle, 94054, "ԭֹ�����ײ�����");
            fpub_SetCompStatus(lXmlhandle, 1);
            LOGRET(COMPRET_FAIL,LM_STD,"ZfChkPLJYDJԭֹ�����ײ�����",fpub_GetCompname(lXmlhandle));
        }
    }
    LOG(LM_STD,Fmtmsg("У��ֹ��������ɹ�..."),"INFO");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;    
                
}

/************************************************************************
��̬�����������
��������: SYW_TIPS_InitPLZFKSF
����: ��ʼ������ֹ����˰��
 
�������: ��ʼ������ֹ����˰��
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
˰������ֹ����˰��	tips_ssplzfksf

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��16��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitPLZFKSF(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;
        int iCount;
        SDB_TIPS_SSPLZFKSF stPlzfksf ;
    EXEC SQL END DECLARE SECTION;
    */
    int i;
    int iRet=0;
    int iFlag=0;
    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		
		int iCount;
        SDB_TIPS_SSPLZFKSF stPlzfksf ;
		/* end add dci 20141103 */
    
	fpub_InitSoComp(lXmlhandle);
	
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")  
    #endif
   
    memset(&stPlzfksf, 0x00, sizeof(stPlzfksf));
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy( stPlzfksf.zwrq, sBuf, sizeof(stPlzfksf.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "����ֹ����ˮ��")
    pstrcopy( stPlzfksf.plzflsh, sBuf, sizeof(stPlzfksf.plzflsh));
    
    LOG(LM_STD,Fmtmsg("��ʼ������ֹ����˰�ѱ� ��������[%s],����ֹ����ˮ��[%s]", 
        stPlzfksf.zwrq, stPlzfksf.plzflsh), fpub_GetCompname(lXmlhandle));

    iCount = 0 ;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_ssplzfksf\
    	 		where zwrq='%s' and plzflsh='%s'",stPlzfksf.zwrq,stPlzfksf.plzflsh);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("��ѯ����ֹ����˰�ѱ�ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_ssplzfksf
         WHERE zwrq = :stPlzfksf.zwrq
           AND plzflsh = :stPlzfksf.plzflsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("��ѯ����ֹ����˰�ѱ�ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    /* �жϱ��������Ƿ��ظ� */
    if ( iCount > 0 )	
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24303, Fmtmsg("��ֹ�����ѵǼ�-ǰ���ڲ�����ֹ����ˮ���ظ�"));
        LOG(LM_STD,Fmtmsg("InitPLZFKSF��ֹ�����ѵǼ�-ǰ���ڲ�����ֹ����ˮ���ظ�"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_FAIL; 
    }
    
    /* 3.���ջ��ش���  */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode", sBuf)
    pstrcopy(stPlzfksf.taxorgcode, sBuf, sizeof(stPlzfksf.taxorgcode));
    /* 4.ί������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate", sBuf)
    pstrcopy(stPlzfksf.entrustdate, sBuf, sizeof(stPlzfksf.entrustdate));
    /* 5.ֹ���������  */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/StopNo", sBuf)
    pstrcopy(stPlzfksf.stopno, sBuf, sizeof(stPlzfksf.stopno));
    
    iCount = 0 ;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_ssplzfksf\
    	 		where taxorgcode='%s' and plzflsh='%s' and stopno='%s'",\
    	 		stPlzfksf.taxorgcode,stPlzfksf.entrustdate,stPlzfksf.stopno);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("��ѯ����ֹ����˰�ѱ�ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_ssplzfksf
         WHERE taxorgcode=:stPlzfksf.taxorgcode
           AND entrustdate=:stPlzfksf.entrustdate
           AND stopno=:stPlzfksf.stopno;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("��ѯ����ֹ����˰�ѱ�ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    /* �жϱ��������Ƿ��ظ� */
    if ( iCount > 0 )	
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24303, Fmtmsg("��ֹ�����ѵǼ�-ֹ����������ظ�"));
        LOG(LM_STD,Fmtmsg("InitPLZFKSF��ֹ�����ѵǼ�-ֹ����������ظ�"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_FAIL; 
    }
            
    /* 6.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stPlzfksf.workdate, sBuf, sizeof(stPlzfksf.workdate));
    /* 7.ԭί������  */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/OriEntrustDate", sBuf)
    pstrcopy(stPlzfksf.orientrustdate, sBuf, sizeof(stPlzfksf.orientrustdate));
    /* 8.ԭ����ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/OriPackNo", sBuf)
    pstrcopy(stPlzfksf.oripackno, sBuf, sizeof(stPlzfksf.oripackno));
    iCount = 0 ;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select count(*) from tips_ssplzfksf\
    	 		where taxorgcode='%s' and orientrustdate='%s' and oripackno='%s'",\
    	 		stPlzfksf.taxorgcode,stPlzfksf.orientrustdate,stPlzfksf.oripackno);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("��ѯ����ֹ����˰�ѱ�ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_ssplzfksf
         WHERE taxorgcode=:stPlzfksf.taxorgcode
           AND orientrustdate=:stPlzfksf.orientrustdate
           AND oripackno=:stPlzfksf.oripackno;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24302, Fmtmsg("��ѯ����ֹ����˰�ѱ�ʧ��"));
        LOG(LM_STD,Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    /* �жϱ��������Ƿ��ظ� */
    if ( iCount > 0 )	
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24303, Fmtmsg("��ֹ�����ѵǼ�-�������ͬһ�ۿ���ظ�ֹ��"));
        LOG(LM_STD,Fmtmsg("InitPLZFKSF��ֹ�����ѵǼ�-�������ͬһ�ۿ���ظ�ֹ��"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_FAIL; 
    }
    /* 9.ԭ������ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/OriTraNo", sBuf)
    pstrcopy(stPlzfksf.oritrano, sBuf, sizeof(stPlzfksf.oritrano));
    /* 10.ֹ������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/StopType", sBuf)
    pstrcopy(stPlzfksf.stoptype, sBuf, sizeof(stPlzfksf.stoptype));
    /* 11.�ܱ��� 12.�ܽ��  */
    if (stPlzfksf.stoptype[0]=='1')/* ����ֹ�� */
    {
    		/* add dci 20141103 */
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select allnum, allamt, zwrq, pljylsh from tips_pljydj\
    	 		where orgcode='%s' and entrustdate='%s' and packno='%s'",\
    	 		stPlzfksf.taxorgcode,stPlzfksf.orientrustdate,stPlzfksf.oripackno);     	
    		/* iRet = DBSelectToMultiVar(sErrmsg,sSql1, &stPlzfksf.allnum,stPlzfksf.allamt,stPlzfksf.yzwrq,stPlzfksf.ypljylsh); */
    		iRet = DBSelectToMultiVar(sErrmsg,sSql1, &stPlzfksf.allnum,&stPlzfksf.allamt,stPlzfksf.yzwrq,stPlzfksf.ypljylsh);
    		if ( iRet < 0 )
    		{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        		fpub_SetMsg(lXmlhandle, 24301, "��ѯֹ��ԭ�����׳���");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("InitPLZFKSF��ѯֹ��ԭ�����׳���"),
                fpub_GetCompname(lXmlhandle))	
    		}
    		/* end add dci 20141103 */
    		
    		/* mod dci 20141103
        EXEC SQL SELECT allnum, allamt, zwrq, pljylsh 
             INTO :stPlzfksf.allnum, :stPlzfksf.allamt, :stPlzfksf.yzwrq, :stPlzfksf.ypljylsh
             FROM tips_pljydj
             WHERE orgcode=:stPlzfksf.taxorgcode
               AND entrustdate=:stPlzfksf.orientrustdate
               AND packno=:stPlzfksf.oripackno;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {
            fpub_SetMsg(lXmlhandle, 24301, "��ѯֹ��ԭ�����׳���");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("InitPLZFKSF��ѯֹ��ԭ�����׳���"),
                fpub_GetCompname(lXmlhandle))	
        } 
        */        
    }else
    {
    		/* add dci 20141103 */
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select jyje, zwrq, pljylsh, plmxxh from tips_ssplksfmx\
    	 		where taxorgcode='%s' and entrustdate='%s' and packno='%s' and trano='%s'",\
    	 		stPlzfksf.taxorgcode,stPlzfksf.orientrustdate,stPlzfksf.oripackno,stPlzfksf.oritrano);     	
    	/*	iRet = DBSelectToMultiVar(sErrmsg,sSql1, &stPlzfksf.allamt, &stPlzfksf.yzwrq, &stPlzfksf.ypljylsh, &stPlzfksf.yplmxxh);*/
    		iRet = DBSelectToMultiVar(sErrmsg,sSql1, &stPlzfksf.allamt, stPlzfksf.yzwrq, stPlzfksf.ypljylsh, &stPlzfksf.yplmxxh);
    		if ( iRet < 0 )
    		{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        		fpub_SetMsg(lXmlhandle, 24301, "��ѯֹ��ԭ�����׳���");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("InitPLZFKSF��ѯֹ��ԭ�����׳���"),
                fpub_GetCompname(lXmlhandle))	
    		}
    		/* end add dci 20141103 */
    		
    		/* mod dci 20141103 
        EXEC SQL SELECT jyje, zwrq, pljylsh, plmxxh
             INTO :stPlzfksf.allamt, :stPlzfksf.yzwrq, :stPlzfksf.ypljylsh, :stPlzfksf.yplmxxh
             FROM tips_ssplksfmx
             WHERE taxorgcode=:stPlzfksf.taxorgcode
               AND entrustdate=:stPlzfksf.orientrustdate
               AND packno=:stPlzfksf.oripackno
               AND trano=:stPlzfksf.oritrano;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR )
        {
            fpub_SetMsg(lXmlhandle, 24301, "��ѯֹ��ԭ�����׳���");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("InitPLZFKSF��ѯֹ��ԭ�����׳���"),
                fpub_GetCompname(lXmlhandle))	
        }
        */
        stPlzfksf.allnum = 1 ;        
    }        

    /* 17.��ǰ״̬ */
    stPlzfksf.dqzt[0]='0';
    /* 18.��Ӧ�� */
    pstrcopy(stPlzfksf.xym, "00000", sizeof(stPlzfksf.xym));
    /* 19.��Ӧ��Ϣ */
    pstrcopy(stPlzfksf.xyxx, "ֹ�����Ǽǳɹ�", sizeof(stPlzfksf.xyxx));
    /* 20.��չ��־ */
    pstrcopy(stPlzfksf.kzbz, "00000000", sizeof(stPlzfksf.kzbz));
    /* 21.ֹ��ԭ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/StopReason", sBuf)
    pstrcopy(stPlzfksf.stopreason, sBuf, sizeof(stPlzfksf.stopreason));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_ssplzfksf", SD_TIPS_SSPLZFKSF, NUMELE(SD_TIPS_SSPLZFKSF), &stPlzfksf, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	DCIRollback();   
    	
    	fpub_SetMsg(lXmlhandle, 24306, "�Ǽ�����ֹ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitPLZFKSF�Ǽ�����ֹ��ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	  
    
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL INSERT INTO tips_ssplzfksf  VALUES (:stPlzfksf);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24306, "�Ǽ�����ֹ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitPLZFKSF�Ǽ�����ֹ��ʧ��"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	  
    */  

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;        
}

/************************************************************************
��̬�����������
��������: SYW_TIPS_ClPLZFKSF
����: ��������ֹ����˰��
 
�������: ��������ֹ����˰��
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
˰������ֹ����˰��	tips_ssplzfksf

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��16��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_ClPLZFKSF(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;*/
         char sYzwrq[8+1];/* ԭ�������� */
         char sYpljylsh[8+1];/* ԭ����������ˮ�� */
         char sCzbd[1+1];/* �������� */
         char sWcbz[1+1];/* ��ɱ�־ */
         int iYplmxxh;
         char sSysDate[8+1];/* ϵͳ���� */
         char sSysTime[6+1];/* ϵͳʱ�� */
         int iZfbs;/* ֹ����� */
         double dZfje;/* ֹ������ */ 
         char sJyCzbd[1+1];/* ���ײ������� */
         char sJyXym[5+1];/* ������Ӧ�� */ 
         int iSuccNum=0; 
         double dSuccAmt=0.00; 
         char sXym[5+1];
         char sXyxx[60+1]; 
         char sDqzt[1+1];/* ��ǰ״̬ */  
    /* add dci 20141103
    EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    char sStopType[1+1];/* ֹ������ */
    char sStopAnswerPath[60];/* ֹ��Ӧ���� */
    char sAddWordPath[60];/* ���Խ�� */
    int iStopResult;
    
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
    int iRet=0;
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("��������ֹ����˰�ѿ�ʼ..."), fpub_GetCompname(lXmlhandle))
    
    COMP_PARACOUNTCHK(6);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sYzwrq, 0x00, sizeof(sYzwrq));
    COMP_GETPARSEPARAS(1, sBuf, "ԭ��������")
    pstrcopy( sYzwrq, sBuf, sizeof(sYzwrq));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sYpljylsh, 0x00, sizeof(sYpljylsh));
    COMP_GETPARSEPARAS(2, sBuf, "ԭ����������ˮ��")
    pstrcopy( sYpljylsh, sBuf, sizeof(sYpljylsh)); 
    trim(sYpljylsh);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iYplmxxh=0;
    COMP_GETPARSEPARAS(3, sBuf, "ԭ������ϸ���")
    iYplmxxh=atoi(sBuf);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sStopType, 0x00, sizeof(sStopType));
    COMP_GETPARSEPARAS(4, sBuf, "ֹ������")
    pstrcopy( sStopType, sBuf, sizeof(sStopType)); 
    trim(sStopType);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sStopAnswerPath, 0x00, sizeof(sStopAnswerPath));
    COMP_GETPARAS(5, sBuf, "ֹ��Ӧ��")
    pstrcopy( sStopAnswerPath, sBuf, sizeof(sStopAnswerPath)); 
    trim(sStopAnswerPath);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sAddWordPath, 0x00, sizeof(sAddWordPath));
    COMP_GETPARAS(6, sBuf, "����")
    pstrcopy( sAddWordPath, sBuf, sizeof(sAddWordPath)); 
    trim(sAddWordPath);
            
    LOG(LM_STD,Fmtmsg("ԭ��������[%s],ԭ����������ˮ��[%s],ԭ������ϸ���[%d],ֹ������[%s]...", 
        sYzwrq, sYpljylsh, iYplmxxh, sStopType), fpub_GetCompname(lXmlhandle))

    memset(sCzbd, 0x00, sizeof(sCzbd));
    memset(sWcbz, 0x00, sizeof(sWcbz));
    iZfbs=0;
    dZfje=0.00;
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select czbd, wcbz, allnum, allamt from tips_pljydj\
    	 		where zwrq='%s' and pljylsh='%s'",sYzwrq,sYpljylsh);     	
    iRet = DBSelectToMultiVar(sErrmsg,sSql1, &sCzbd, &sWcbz, &iZfbs, &dZfje);
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 99003, "��ѯԭ�����㼰��ɱ�־ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF��ѯԭ�����㼰��ɱ�־ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT czbd, wcbz, allnum, allamt
         INTO :sCzbd, :sWcbz, :iZfbs, :dZfje
         FROM tips_pljydj
         WHERE zwrq=:sYzwrq
           AND pljylsh=:sYpljylsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR || SQLNOTFOUND_TIPS )
    {
        fpub_SetMsg(lXmlhandle, 99003, "��ѯԭ�����㼰��ɱ�־ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF��ѯԭ�����㼰��ɱ�־ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    if ( sWcbz[0]=='9' )/* ��ɱ�־ 9-�������ڴ����� */
    {
        fpub_SetMsg(lXmlhandle, 99090, "ԭ��/�������ڴ�����,����ֹ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSFԭ��/�������ڴ�����,����ֹ��"),
            fpub_GetCompname(lXmlhandle))       
    }

    memset(sSysDate, 0x00, sizeof(sSysDate));
    memset(sSysTime, 0x00, sizeof(sSysTime));
    COMP_SOFTGETXML("/sys/sysdate", sSysDate)
    COMP_SOFTGETXML("/sys/systime", sSysTime)

    /* ��ʼ���� 
    EXEC SQL BEGIN WORK ;   */ 

    /* ����ԭ����Ϊ���ڴ����� */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_pljydj \
    				SET wcbz='9' \
    			where zwrq='%s' and pljylsh='%s'" \
    			,sYzwrq  ,sYpljylsh);
               	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")                
        
        fpub_SetMsg(lXmlhandle, 99003, "�����������׵ǼǱ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF�����������׵ǼǱ�ʧ��"),
            fpub_GetCompname(lXmlhandle)) 	
    }
    /* end dci 20141103 */    
    
    /* mod dci 20141103 
    EXEC SQL UPDATE tips_pljydj SET wcbz='9'
         WHERE zwrq=:sYzwrq
           AND pljylsh=:sYpljylsh;        
    if ( SQLERR )	
    {
         /* EXEC SQL ROLLBACK WORK;
         fpub_SetMsg(lXmlhandle, 99003, "�����������׵ǼǱ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF�����������׵ǼǱ�ʧ��"),
            fpub_GetCompname(lXmlhandle)) 	
    }
    */
    
    iSuccNum=0;
    dSuccAmt=0.00;
    iStopResult=0;
    memset(sDqzt, 0x00, sizeof(sDqzt));
    memset(sXym, 0x00, sizeof(sXym));
    memset(sXyxx, 0x00, sizeof(sXyxx));        
    if ( sStopType[0]=='1' )/* ����ֹ�� */
    {
        if ( sCzbd[0]=='2' )
        {
            iSuccNum=iZfbs;
            dSuccAmt=dZfje;
            sWcbz[0]='3';
            sDqzt[0]='1';
            iStopResult=1;/* ֹ���ɹ� */
            pstrcopy(sXym, "24020", sizeof(sXym));
            pstrcopy(sXyxx, "������ֹ���ɹ�", sizeof(sXyxx));
            /* ����ԭ��������˰����ϸ�����ؼ�¼ */
            /* add dci 20141103 */
    				memset( sSql1, 0x00, sizeof( sSql1 ) );
    				snprintf( sSql1, sizeof(sSql1), "update tips_ssplksfmx \
    								SET czbd='1',\
                     xym='%s',\
                     xyxx='%s'\
    								where zwrq='%s' and pljylsh='%s'" \
    								,sXym, sXyxx, sYzwrq ,sYpljylsh);
               	
    				iRet = DCIExecuteDirect(sSql1);	 
    				if ( iRet < 0 )
    				{
        			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")                
        
        			fpub_SetMsg(lXmlhandle, 99003, "����������˰����ϸ��ʧ��");
                 fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                 LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF����������˰����ϸ��ʧ��"),
                     fpub_GetCompname(lXmlhandle))	
    				}
    				/* end add dci 20141103 */
    
            /* mod dci 20141103
            EXEC SQL UPDATE tips_ssplksfmx
                 SET czbd='1',
                     xym=:sXym,
                     xyxx=:sXyxx
                WHERE zwrq=:sYzwrq
                  AND pljylsh=:sYpljylsh;                     
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
            if (SQLERR)	
            {
                /* EXEC SQL ROLLBACK WORK;
                 fpub_SetMsg(lXmlhandle, 99003, "����������˰����ϸ��ʧ��");
                 fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                 LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF����������˰����ϸ��ʧ��"),
                     fpub_GetCompname(lXmlhandle))	
            }
            */
        }else
        {
            iSuccNum=0;
            dSuccAmt=0.00;
            sDqzt[0]='2';/* 2-����ʧ�� */
            pstrcopy(sXym, "99090", sizeof(sXym));
            pstrcopy(sXyxx, "ֹ��ʧ��,�ѿۿ�", sizeof(sXyxx)); 
            iStopResult=2;/* ֹ��ʧ��-�ѿۿ� */            
        }      
    }else
    {
        /* ��ѯԭ���׵Ĳ������㼰���׽�� */
        dZfje=0.00;
        memset(sJyCzbd, 0x00, sizeof(sJyCzbd));
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
				snprintf( sSql1, sizeof(sSql1), "SELECT jyje, czbd FROM tips_ssplksfmx \
    				where zwrq='%s' and pljylsh='%s' and plmxxh = '%d'",sYzwrq , sYpljylsh, iYplmxxh);  
    		iRet = DBSelectToMultiVar(sErrmsg, sSql1,&dZfje, &sJyCzbd);
    		if ( iRet < 0 || iRet == 0)
    		{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        		fpub_SetMsg(lXmlhandle, 99003, "��ѯԭ�����㼰��ɱ�־ʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF��ѯԭ�����㼰��ɱ�־ʧ��"),
                fpub_GetCompname(lXmlhandle))		     
    		}
        /* end add dci 20141103 */
        
        /* mod dci 20141103 
        EXEC SQL SELECT jyje, czbd INTO :dZfje, :sJyCzbd
             FROM tips_ssplksfmx
            WHERE zwrq=:sYzwrq
              AND pljylsh=:sYpljylsh
              AND plmxxh=:iYplmxxh;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
        if ( SQLERR || SQLNOTFOUND_TIPS )
        {
           /* EXEC SQL ROLLBACK WORK; 
            fpub_SetMsg(lXmlhandle, 99003, "��ѯԭ�����㼰��ɱ�־ʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF��ѯԭ�����㼰��ɱ�־ʧ��"),
                fpub_GetCompname(lXmlhandle))
        }
        */
        
        if( sCzbd[0]=='2' )/* �˴�Ϊ�������׵ǼǱ�Ĳ����������жϣ���δ�ۿ� */
        {
            iStopResult=1;/* ֹ���ɹ� */
            sJyCzbd[0]='1';/* ���ײ������� 1-��ֹ�� */
            sDqzt[0]='1';/* 1-ֹ���ɹ� */
            iSuccNum=1;
            dSuccAmt=dZfje;
            pstrcopy(sXym, "24020", sizeof(sXym));
            pstrcopy(sXyxx, "�˿�˰�ѽ��ױ�ֹ��", sizeof(sXyxx));
            /* add dci 20141103 */
    				memset( sSql1, 0x00, sizeof( sSql1 ) );
    				snprintf( sSql1, sizeof(sSql1), "update tips_ssplksfmx \
    								SET czbd='1',\
                     xym='%s',\
                     xyxx='%s'\
    								where zwrq='%s' and pljylsh='%s' and plmxxh=%d" \
    								,sXym, sXyxx, sYzwrq  ,sYpljylsh, iYplmxxh);
               	
    				iRet = DCIExecuteDirect(sSql1);	 
    				if ( iRet < 0 )
    				{
        			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")                
        
        			fpub_SetMsg(lXmlhandle, 99003, "����������˰����ϸ��ʧ��");
                 fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                 LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF����������˰����ϸ��ʧ��"),
                     fpub_GetCompname(lXmlhandle))		
    				}
    				/* end add dci 20141103 */
    				
            /* mod dci 20141103 
            EXEC SQL UPDATE tips_ssplksfmx
                 SET czbd=:sJyCzbd,
                     xym=:sXym,
                     xyxx=:sXyxx
                WHERE zwrq=:sYzwrq
                  AND pljylsh=:sYpljylsh
                  AND plmxxh=:iYplmxxh;                     
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
            if (SQLERR)	
            {
                /* EXEC SQL ROLLBACK WORK; 
                 fpub_SetMsg(lXmlhandle, 99003, "����������˰����ϸ��ʧ��");
                 fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                 LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF����������˰����ϸ��ʧ��"),
                     fpub_GetCompname(lXmlhandle))	
             
            }
            */
            
        }else
        {
            iStopResult=2;/* ֹ��ʧ�� */
            iSuccNum=0;
            dSuccAmt=0.00;
            sDqzt[0]='2';/* 2-����ʧ�� */
            pstrcopy(sXym, "99090", sizeof(sXym));
            pstrcopy(sXyxx, "ֹ��ʧ��,�ѿۿ�", sizeof(sXyxx));   
        }                
    }
    /* �����������׵ǼǱ� */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_pljydj \
    								SET zfzbs=%d,\
                        zfzje=%f,\
                        wcbz='%s',\
                        cljsrq='%s',\
                        cljssj='%s',\
                        xym='%s',\
                        xyxx='%s'\
                        where zwrq='%s' and pljylsh='%s'", \
    								iSuccNum,dSuccAmt,sWcbz,sSysDate,sSysTime,sXym,sXyxx,sYzwrq ,sYpljylsh);
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")                
        
        fpub_SetMsg(lXmlhandle, 99003, "���������ǼǱ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF�����������׵ǼǱ�ʧ��"),
             fpub_GetCompname(lXmlhandle))	
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL UPDATE tips_pljydj 
         SET zfzbs=:iSuccNum,
             zfzje=:dSuccAmt,
             wcbz=:sWcbz,/* ��ɱ�־ 
             cljsrq=:sSysDate,
             cljssj=:sSysTime,
             xym=:sXym,
             xyxx=:sXyxx
         WHERE zwrq=:sYzwrq
           AND pljylsh=:sYpljylsh;            
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (SQLERR)	
    {
        /* EXEC SQL ROLLBACK WORK; 
         fpub_SetMsg(lXmlhandle, 99003, "���������ǼǱ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF�����������׵ǼǱ�ʧ��"),
             fpub_GetCompname(lXmlhandle))	
    } 
    */
               
    /* ����������˰��ֹ���� */
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_ssplzfksf \
    								SET num_succ=%d,\
                        amt_succ=%f,\
                        clrq='%s',\
                        clsj='%s',\
             						dqzt='%s',\
             						xym='%s',\
                        xyxx='%s'\
    								where yzwrq='%s' and ypljylsh='%s'", \
    								iSuccNum,dSuccAmt,sSysDate,sSysTime,sDqzt,sXym,sXyxx,sYzwrq , sYpljylsh);
    									
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")                
        
        fpub_SetMsg(lXmlhandle, 99003, "��������ֹ����˰�ѱ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF��������ֹ����˰�ѱ�ʧ��"),
             fpub_GetCompname(lXmlhandle))
    }
    /* end add dci 20141103 */
    /* mod dci 20141103 
    EXEC SQL UPDATE tips_ssplzfksf
         SET num_succ=:iSuccNum,
             amt_succ=:dSuccAmt,
             clrq=:sSysDate,
             clsj=:sSysTime,
             dqzt=:sDqzt,
             xym=:sXym,
             xyxx=:sXyxx   
        WHERE yzwrq=:sYzwrq
          AND ypljylsh=:sYpljylsh;            
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
    if (SQLERR || SQLNOTFOUND_TIPS)	
    {
       /*  EXEC SQL ROLLBACK WORK;
         fpub_SetMsg(lXmlhandle, 99003, "��������ֹ����˰�ѱ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ClPLZFKSF��������ֹ����˰�ѱ�ʧ��"),
             fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*ȫ���ύ
    EXEC SQL COMMIT WORK;
    if ( SQLERR )  
    {
       LOG(LM_STD,Fmtmsg("���ݿ��ύʧ��sqlcode=[%d]",sqlca.sqlcode),"ERROR");
       /* EXEC SQL ROLLBACK WORK;
       fpub_SetMsg(lXmlhandle, 99003,Fmtmsg("���ݿ����ʧ��"));
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       return COMPRET_FAIL;    	
    }    
    */
    memset(sBuf, 0x00, sizeof(sBuf));
    sprintf(sBuf, "%d", iStopResult);
    COMP_SOFTSETXML(sStopAnswerPath, sBuf) 
    COMP_SOFTSETXML(sAddWordPath, sXyxx)
    LOG(LM_STD,Fmtmsg("��������ֹ����˰�ѽ���,ֹ��Ӧ��[%d](1-�ɹ�,2-ʧ��),����[%s]...", 
        iStopResult, sXyxx),"INFO"); 
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;

}


/************************************************************************
��̬�����������
��������: SYW_TIPS_PLKSF
����: ����������˰�ѽ���
 
�������: ����������˰�ѽ���
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
�������׵ǼǱ�	tips_pljydj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��03��11��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_PLKSF(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;*/
         int iCount ;
         char sZwrq[8+1];/* �������� */
         char sPljylsh[8+1];/* ����������ˮ�� */
         char sCzbd[1+1];/* �������� */
         char sWcbz[1+1];/* ��ɱ�־ */ 
         char sWorkDate[8+1];/* �������� */
    /* add dci 20141103
    EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    char sSubFlow[100];
    int iflag=0 ;
    int iAll = 0;
    int iSucc;
    int iFail;
	int iPEruptCnt = 10;
	int iPCount = 0;
    
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		CURSOR cur;
		int iRet=0;
    
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(1);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSubFlow, 0x00, sizeof(sSubFlow));
    COMP_GETPARSEPARAS(1, sBuf, "�ڲ�������")
    pstrcopy(sSubFlow, sBuf, sizeof(sSubFlow));
    trim(sSubFlow);

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tipsx/receipt/plks/peruptcnt", sBuf);
	trim(sBuf);
	if ( strlen(sBuf) > 0 ) {
		iPEruptCnt = atoi(sBuf);
		if ( 0 == iPEruptCnt ) {
			iPEruptCnt = 10;
		}
	}
    LOG(LM_STD,Fmtmsg("��������������˰�ѿ�ʼ,������˰��������[%s]...", sSubFlow), fpub_GetCompname(lXmlhandle))
    
    memset(sWorkDate, 0x00, sizeof(sWorkDate));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select workdate from tips_nbcsb	where 1=1"); 
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")          	
    iRet = DBSelectToVar(sErrmsg, &sWorkDate, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24310, "��ѯ�ڲ�������ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ�ڲ�������ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;              
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT workdate INTO :sWorkDate
         FROM tips_nbcsb
         WHERE 1=1;
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24310, "��ѯ�ڲ�������ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ�ڲ�������ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    */
        
    iCount = 0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select COUNT(*) from tips_pljydj\
    	where workdate='%s' and wcbz in ('0', '3') 	AND czbd in ('2', '3', '4', '5', '6')",sWorkDate);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);    	
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24310, "��ѯ�������׵ǼǱ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_pljydj
         WHERE workdate=:sWorkDate
           AND wcbz in ('0', '3')
           AND czbd in ('2', '3', '4', '5', '6');
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24310, "��ѯ�������׵ǼǱ�ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ�������׵ǼǱ�ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    */
    
    if ( iCount < 1 )
    {
         fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "��ǰû��Ҫ�����������˰�ѽ���");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
         LOG(LM_STD, Fmtmsg("��ǰû��Ҫ�����������˰�ѽ���"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_SUCC ;        
    }
    
    LOG(LM_STD, Fmtmsg("��ǰ��Ҫ�����������˰�ѽ��׹�[%d]��", iCount), fpub_GetCompname(lXmlhandle))	
    
    /* ��ʼ�����账���������˰�ѽ���*/
    /* ����ҵ����ϸ�� */    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT zwrq, pljylsh FROM  tips_pljydj\
    	where workdate='%s' and wcbz in ('0', '3') \
           AND czbd in ('2', '3', '4', '5', '6') ORDER BY zwrq, pljylsh desc",sWorkDate);
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

    /* end dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL DECLARE cur_pljydj_plksf CURSOR for 
        SELECT zwrq, pljylsh
        FROM  tips_pljydj 
         WHERE workdate=:sWorkDate
           AND wcbz in ('0', '3')
           AND czbd in ('2', '3', '4', '5', '6');
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_pljydj_plksf;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_pljydj_plksf",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,36001, "���α�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("PLKSF��cur_pljydj_plksf�α�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*��ʼѭ��*/
    iSucc = 0;
    iFail = 0;
	iAll = 0;
    /* add dci 20141103 */        
	iRet = DCIFetch(cur);
	/**begin ������β������� add by zhangl 20161026 */
	iPCount = 1;
	/**end ������β�������*/
    while( iRet > 0 )
    {
    		memset(sZwrq, 0x00, sizeof(sZwrq));
    		memset(sPljylsh, 0x00, sizeof(sPljylsh));
    		
        strncpy( sZwrq, DCIFieldAsString(cur, 0 ), sizeof( sZwrq ) );
        strncpy( sPljylsh, DCIFieldAsString(cur, 1 ), sizeof( sPljylsh ) );
                   
        trim(sZwrq);
        trim(sPljylsh);
        
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        COMP_SOFTSETXML("/tips/pljylsh", sPljylsh)
        iAll++;
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("PLKSF��������˰��������ϵͳ����"),"ERROR");
        	break;
        }
        
		
        /*�ж��������Ƿ���ɹ� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*����2ʧ��,������Ϊ�ɹ� */
        {
        	iFail ++;
        	/* iflag=-3; */
        	LOG(LM_STD,Fmtmsg("PLKSF��������˰��������ʧ��"),"ERROR");
        	continue;
        }
        iSucc++;

		/**begin ������β������� add by zhangl 20161026 */
		if ( ++iPCount > iPEruptCnt ) { /*�ô��Զ����񲢷�������ϣ��˳�*/
			break;
		}
		/**end ������β�������*/
        
		iRet = DCIFetch(cur);               
    }
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }   

		DCIFreeCursor(cur);
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    for (iAll=0,iflag=0;;iAll++)
    {
        memset(sZwrq, 0x00, sizeof(sZwrq));
        memset(sPljylsh, 0x00, sizeof(sPljylsh));
        
        EXEC SQL FETCH cur_pljydj_plksf INTO :sZwrq, :sPljylsh;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_pljydj_plksf", sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("PLKSF��cur_pljydj_plksf�α��ȡ����ʧ��"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;

        trim(sZwrq);
        trim(sPljylsh);
        
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        COMP_SOFTSETXML("/tips/pljylsh", sPljylsh)
        
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("PLKSF��������˰��������ϵͳ����"),"ERROR");
        	break;
        }
        
        /*�ж��������Ƿ���ɹ�
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*����2ʧ��,������Ϊ�ɹ�
        {
        	iFail ++;
        	/* iflag=-3; 
        	LOG(LM_STD,Fmtmsg("PLKSF��������˰��������ʧ��"),"ERROR");
        	continue;
        }
        iSucc++;
    }                      
    EXEC SQL CLOSE cur_pljydj_plksf;
    */
        
    /* EXEC SQL FREE  cur_pljydj_plksf;*/
    if (iflag < 0)
    {
        fpub_SetMsg(lXmlhandle,24313,"��������������˰��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������������˰��ʧ��iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("��������������˰�ѽ���,��[%d]��,�ɹ�[%d]��,ʧ��[%d]��",
        iAll, iSucc, iFail), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}


/************************************************************************
��̬�����������
��������: SYW_TIPS_PLKSF_P2D
����: ����������˰�ѽ���(����)
 
�������: ����������˰�ѽ���(����)
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
�������׵ǼǱ�	tips_pljydj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��03��11��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_PLKSF_P2D(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103
    EXEC SQL BEGIN DECLARE SECTION;*/
         int iCount ;
         char sZwrq[8+1];/* �������� */
         char sPljylsh[8+1];/* ����������ˮ�� */
         char sCzbd[1+1];/* �������� */
         char sWcbz[1+1];/* ��ɱ�־ */ 
         char sWorkDate[8+1];/* �������� */
         int iZbs;
         char cZbs[16+1];
         double dZje;
         char cZje[32+1];
         int iPlmxxh;/* ������ϸ��� */
    /* add dci 20141103
    EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    char sSubFlow[100];
    int iflag=0 ;
    int iAll=0;
    int iSucc=0;
    int iFail=0;
	int iEruptCnt = 10;
	int iEruptStep = 0;
	int iEruptSnd = 2;
	
    
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		CURSOR cur;
		int iRet=0;
		
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSubFlow, 0x00, sizeof(sSubFlow));
    COMP_GETPARSEPARAS(1, sBuf, "�ڲ�������")
    pstrcopy(sSubFlow, sBuf, sizeof(sSubFlow));
    trim(sSubFlow);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq)); 
    COMP_GETPARSEPARAS(2,sBuf,"��������")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPljylsh, 0x00, sizeof(sPljylsh));
    COMP_GETPARSEPARAS(3,sBuf,"����������ˮ��")
    pstrcopy(sPljylsh, sBuf, sizeof(sPljylsh));
    trim(sPljylsh);

	/*��ȡ��������������Ĭ��Ϊ10*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tipsx/receipt/plks/eruptcnt", sBuf);
	trim(sBuf);
	if (strlen(sBuf) > 0) {
		iEruptCnt = atoi(sBuf);
		if ( 0 == iEruptCnt) {
			iEruptCnt = 10;
		}
	}
	/*��ȡ�����ж�ʱ�䳤�ȣ� Ĭ��Ϊ2s*/
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tipsx/receipt/plks/eruptsnd", sBuf);
	trim(sBuf);
	if (strlen(sBuf) > 0) {
		iEruptSnd = atoi(sBuf);
		if ( 0 == iEruptSnd ) {
			iEruptSnd = 2;
		} 
	}
	
    LOG(LM_STD,Fmtmsg("������˰��(����)��ʼ,��������[%s],����������ˮ��[%s]����[%s],...", 
        sZwrq, sPljylsh, sSubFlow), fpub_GetCompname(lXmlhandle))
        
    iCount = 0;
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select COUNT(*) from tips_ssplksfmx \
     where zwrq='%s' and pljylsh=%s and czbd='0'",sZwrq,sPljylsh);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24310, "��ѯ������˰����ϸ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ������˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }

    /* end add dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT COUNT(*) INTO :iCount
         FROM tips_ssplksfmx
         WHERE zwrq=:sZwrq
           AND pljylsh=:sPljylsh
           AND czbd='0';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24310, "��ѯ������˰����ϸ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ������˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    */
        
    if ( iCount < 1 )
    {
        iZbs = 0;
        dZje = 0.0;  
        iCount = 0;
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
				snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM tips_ssplksfmx \
    			where zwrq='%s' and pljylsh='%s' and czbd='6'",sZwrq , sPljylsh); 
    		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")       
    		/*iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&iZbs, &dZje);*/
    		iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cZbs);
    		iZbs=atoi(cZbs);
    		
    		if ( iRet < 0 )
    		{
        	   fpub_SetMsg(lXmlhandle, 24310, "��ѯ������˰����ϸ��ʧ��");
		         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		         LOG(LM_STD, Fmtmsg("��ѯ������˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))	
		         return COMPRET_FAIL ;            
    		}
    		if ( iCount > 0 )
        {
					    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
					    LOG(LM_STD,Fmtmsg("����δ������ļ�¼"), fpub_GetCompname(lXmlhandle))
					    return COMPRET_SUCC;
        }
        
        /* end add dci 20141103 */
        
        /* mod dci 20141103  
		    EXEC SQL SELECT COUNT(*) INTO :iCount
		         FROM tips_ssplksfmx
		         WHERE zwrq=:sZwrq
		           AND pljylsh=:sPljylsh
		           AND czbd='6';
		    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
		    if ( SQLERR )
		    {
		         fpub_SetMsg(lXmlhandle, 24310, "��ѯ������˰����ϸ��ʧ��");
		         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		         LOG(LM_STD, Fmtmsg("��ѯ������˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))	
		         return COMPRET_FAIL ;        
		    }
				if ( iCount > 0 )
        {
					    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
					    LOG(LM_STD,Fmtmsg("����δ������ļ�¼"), fpub_GetCompname(lXmlhandle))
					    return COMPRET_SUCC;
        }
        */
        
        /* add dci 20141103 */
        memset( sSql1, 0x00, sizeof( sSql1 ) );
				snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*), SUM(jyje) FROM tips_ssplksfmx \
    			where zwrq='%s' and pljylsh='%s' and czbd='7'",sZwrq , sPljylsh); 
    		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")       
    		/*iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&iZbs, &dZje);*/
    		iRet = DBSelectToMultiVarChar(sErrmsg, sSql1,&cZbs, &cZje);
    		iZbs=atoi(cZbs);
    		dZje=atof(cZje);
    		
    		if ( iRet < 0 )
    		{
        	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
             
          fpub_SetMsg(lXmlhandle, 24311, "��ѯ������˰����ϸ��ʧ��");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("��ѯ������˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))	
             return COMPRET_FAIL ;          
    		}
        /* end add dci 20141103 */
        
        /* mod dci 20141103  
        EXEC SQL SELECT COUNT(*), nvl(SUM(jyje), 0.00) INTO :iZbs,:dZje 
             FROM tips_ssplksfmx
             WHERE zwrq=:sZwrq
               AND pljylsh=:sPljylsh
               AND czbd='7';
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
        if ( SQLERR )
        {
             fpub_SetMsg(lXmlhandle, 24311, "��ѯ������˰����ϸ��ʧ��");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("��ѯ������˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))	
             return COMPRET_FAIL ;        
        }
        */
        
        /*�޸��������׵Ǽ���Ϣ*/
        /* add dci 20141103 */
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "update tips_pljydj \
    			SET rzzbs  = rzzbs + %d,  \
           		rzzje  = rzzje + %.2f  \
           	WHERE zwrq   ='%s'\
    			  AND pljylsh='%s'",\
    			iZbs \
    			,dZje\
          ,sZwrq    \
    			,sPljylsh );
    		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")                     	
    		iRet = DCIExecuteDirect(sSql1);	 
    		if ( iRet < 0 || iRet == 0)
    		{
        	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        	fpub_SetMsg(lXmlhandle, 24285, "���������Ǽ���Ϣʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���������Ǽ���Ϣʧ��"),
                fpub_GetCompname(lXmlhandle))			
    		} 
    		/* end add dci 20141103 */
    		
        /* mod dci 20141103 
        EXEC SQL UPDATE tips_pljydj 
             SET rzzbs = :iZbs,         /*�����ܱ���
                 rzzje = :dZje
             WHERE zwrq = :sZwrq 
               AND pljylsh =:sPljylsh;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");   
        if (( SQLERR ) || ( SQLNOTFOUND_TIPS))
        {
            fpub_SetMsg(lXmlhandle, 24285, "���������Ǽ���Ϣʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���������Ǽ���Ϣʧ��"),
                fpub_GetCompname(lXmlhandle))		
         }       
        */
        iRet =DCICommit();
        /* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  */
        if ( iRet < 0 )
        {
      	  LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      	  DCIRollback();
      	
      	  fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
       	  fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       	  return COMPRET_FAIL;     
        }
        
                  
        fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "��ǰ������û��Ҫ���ͺ��Ŀۿ�ļ�¼");
        fpub_SetCompStatus(lXmlhandle, 1);
        LOG(LM_STD, Fmtmsg("��ǰ������û��Ҫ���ͺ��Ŀۿ�ļ�¼"), fpub_GetCompname(lXmlhandle))	
        return COMPRET_SUCC ;        
    }
    
    LOG(LM_STD, Fmtmsg("��ǰ��������Ҫ�����ͺ��Ŀۿ�ļ�¼��[%d]��", iCount), fpub_GetCompname(lXmlhandle))	
    
    /* ��ʼ�����账���������˰�ѽ���*/
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT plmxxh FROM  tips_ssplksfmx\
    	where zwrq='%s' and pljylsh='%s' and czbd='0'",sZwrq , sPljylsh);  
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
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

    /* end dci 20141103 */
    /* mod dci 20141103 
    EXEC SQL DECLARE cur_plksfmx_p2d CURSOR for 
        SELECT plmxxh
        FROM tips_ssplksfmx
         WHERE zwrq=:sZwrq
           AND pljylsh=:sPljylsh
           AND czbd='0';
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DECLARE,sqlca.sqlcode),"ERROR");
    
    EXEC SQL OPEN cur_plksfmx_p2d;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_plksfmx_p2d",sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle,36001, "���α�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("PLKSF��cur_plksfmx_p2d�α�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    
    /*��ʼѭ��*/
    iSucc = 0;
    iFail = 0;
    /* add dci 20141103 */
	LOG(LM_DEBUG, Fmtmsg("��������[%d], ͣ��ʱ��[%d]s", iEruptCnt, iEruptSnd), "INFO");
    for (iAll=0,iflag=0;;iAll++)
    {
    	/*�첽call������������ begin 20161019  add by zhangl*/

		if (++iEruptStep > iEruptCnt) {
			iEruptStep = 0;
			sleep(iEruptSnd);
		}

		/*�첽call������������ end 20161019  add by zhangl*/
		
        iPlmxxh=0;
        
        iRet = DCIFetch(cur);
        if ( iRet < 0 )
    		{
         	iflag=-1;
        	LOG(LM_STD,Fmtmsg("PLKSF��cur_plksfmx_p2d�α��ȡ����ʧ��"),"ERROR");
        	break;
        }
        if ( iRet == 0 )
          break;
        
        iPlmxxh= atoi( DCIFieldAsString(cur, 0 ) );	
        
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        COMP_SOFTSETXML("/tips/pljylsh", sPljylsh)
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf), "%d", iPlmxxh);
        COMP_SOFTSETXML("/tips/plmxxh", sBuf)
        
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("PLKSF��������˰��(����)ϵͳ����"),"ERROR");
        	break;
        }
        
        /*�ж��������Ƿ���ɹ� */
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*����2ʧ��,������Ϊ�ɹ� */
        {
        	iFail ++;
        	iflag=-3;
        	LOG(LM_STD,Fmtmsg("PLKSF��������˰��(����)ʧ��"),"ERROR");
        	continue;
        }
        iSucc++;
    }                      
    DCIFreeCursor(cur);

    /* end add dci 20141103 */
    
    /* mod dci 20141103
    for (iAll=0,iflag=0;;iAll++)
    {
        iPlmxxh=0;
        
        EXEC SQL FETCH cur_plksfmx_p2d INTO :iPlmxxh;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_plksfmx_p2d", sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("PLKSF��cur_plksfmx_p2d�α��ȡ����ʧ��"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND_TIPS )
          break;
        
        COMP_SOFTSETXML("/tips/zwrq", sZwrq)
        COMP_SOFTSETXML("/tips/pljylsh", sPljylsh)
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf), "%d", iPlmxxh);
        COMP_SOFTSETXML("/tips/plmxxh", sBuf)
        
        if ( fpub_CallFlow(lXmlhandle,sSubFlow) != MID_SYS_SUCC)
        {
        	iFail ++;
        	iflag=-2;
        	LOG(LM_STD,Fmtmsg("PLKSF��������˰��(����)ϵͳ����"),"ERROR");
        	break;
        }
        
        /*�ж��������Ƿ���ɹ�
        memset(sBuf, 0x00, sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_PFLOWSTATUS,sBuf)
        if ( sBuf[0] == '2' )  /*����2ʧ��,������Ϊ�ɹ�
        {
        	iFail ++;
        	iflag=-3;
        	LOG(LM_STD,Fmtmsg("PLKSF��������˰��(����)ʧ��"),"ERROR");
        	continue;
        }
        iSucc++;
    }                      
    EXEC SQL CLOSE cur_plksfmx_p2d;    
    */
    
    if (iflag < 0)
    {
        fpub_SetMsg(lXmlhandle,24313,"��������������˰��(����)ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������������˰��(����)ʧ��iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("��������������˰��(����)����,��[%d]��,�ɹ�[%d]��,ʧ��[%d]��",
        iAll, iSucc, iFail), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
��������: SYW_TIPS_InitPZSJ_P2D
����: ��ʼ��ƾ֤����(����)
 
�������: ��ʼ��ƾ֤����(����)
  
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����
������˰����ϸ��	tips_ssplksfmx

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��03��11��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitPZSJ_P2D(HXMLTREE lXmlhandle)
{
    int iParas;
    /* add dci 20141103 
EXEC SQL BEGIN DECLARE SECTION;*/
         SDB_TIPS_SSPLKSFMX stPlksfmx;
         char sZwrq[8+1];
         int iPlmxxh;/* ������ϸ��� */
    /* add dci 20141103 
EXEC SQL END DECLARE SECTION;*/
    char sBuf[256];
    int iRet=0;
    
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
    
    COMP_PARACOUNTCHK(2);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq)); 
    COMP_GETPARSEPARAS(1,sBuf,"��������")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iPlmxxh=0;
    COMP_GETPARSEPARAS(2,sBuf,"������ϸ���")
    iPlmxxh=atoi(sBuf);

    LOG(LM_STD,Fmtmsg("��ʼ��ƾ֤����(����)��ʼ,��������[%s],������ϸ���[%d]...", 
        sZwrq, iPlmxxh), fpub_GetCompname(lXmlhandle))
        
    memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select * from tips_ssplksfmx where zwrq='%s' and plmxxh=%d",sZwrq,iPlmxxh);     	
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")      
    iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx);
    /*
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&stPlksfmx.zwrq,&stPlksfmx.pljydm,&stPlksfmx.pljylsh,\
    		 &stPlksfmx.plpch,&stPlksfmx.plmxxh,&stPlksfmx.clcs,&stPlksfmx.workdate,&stPlksfmx.entrustdate,\
    		 &stPlksfmx.taxorgcode,&stPlksfmx.packno,&stPlksfmx.returnterm,&stPlksfmx.chkdate,&stPlksfmx.chkacctord,\
    		 &stPlksfmx.trano,&stPlksfmx.protocolno,&stPlksfmx.dfzh,&stPlksfmx.paybkcode,&stPlksfmx.payopbkcode,\
    		 &stPlksfmx.payacct,&stPlksfmx.payeebankno,&stPlksfmx.handorgname,&stPlksfmx.taxvouno,&stPlksfmx.jyje,\
    		 &stPlksfmx.sxf,&stPlksfmx.zhye,&stPlksfmx.je2,&stPlksfmx.zjrq,&stPlksfmx.zjsj,&stPlksfmx.zjlsh,\
    		 &stPlksfmx.dqdh,&stPlksfmx.jgdh,&stPlksfmx.jygy,&stPlksfmx.zddh,&stPlksfmx.czbd,&stPlksfmx.qsbz,\
    		 &stPlksfmx.xym,&stPlksfmx.xyxx,&stPlksfmx.kzbz,&stPlksfmx.taxpaycode,&stPlksfmx.taxpayname,&stPlksfmx.spxx,\
    		 &stPlksfmx.byzd );*/    
    LOG(LM_STD,Fmtmsg("stPlksfmx[%s][%s][%s][%s][%d][%d][%s][%s][%s][%s][%d][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s]\n \
    [%f][%f][%f][%f][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s][%s]\n",\
    			stPlksfmx.zwrq,stPlksfmx.pljydm,stPlksfmx.pljylsh,\
    		 stPlksfmx.plpch,stPlksfmx.plmxxh,stPlksfmx.clcs,stPlksfmx.workdate,stPlksfmx.entrustdate,\
    		 stPlksfmx.taxorgcode,stPlksfmx.packno,stPlksfmx.returnterm,stPlksfmx.chkdate,stPlksfmx.chkacctord,\
    		 stPlksfmx.trano,stPlksfmx.protocolno,stPlksfmx.dfzh,stPlksfmx.paybkcode,stPlksfmx.payopbkcode,\
    		 stPlksfmx.payacct,stPlksfmx.payeebankno,stPlksfmx.handorgname,stPlksfmx.taxvouno,stPlksfmx.jyje,\
    		 stPlksfmx.sxf,stPlksfmx.zhye,stPlksfmx.je2,stPlksfmx.zjrq,stPlksfmx.zjsj,stPlksfmx.zjlsh,\
    		 stPlksfmx.dqdh,stPlksfmx.jgdh,stPlksfmx.jygy,stPlksfmx.zddh,stPlksfmx.czbd,stPlksfmx.qsbz,\
    		 stPlksfmx.xym,stPlksfmx.xyxx,stPlksfmx.kzbz,stPlksfmx.taxpaycode,stPlksfmx.taxpayname,stPlksfmx.spxx,\
    		 stPlksfmx.byzd),"INFO")
  
    if ( iRet < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        fpub_SetMsg(lXmlhandle, 24310, "��ѯ������˰����ϸ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ������˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;          
    }

    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL SELECT * INTO :stPlksfmx
         FROM tips_ssplksfmx
         WHERE zwrq=:sZwrq
           AND plmxxh=:iPlmxxh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24310, "��ѯ������˰����ϸ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ������˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }    
    */
		
		iRet = 0;
		
    iRet = prv_tips_InitPZSJ_pl(lXmlhandle, stPlksfmx);
    if ( iRet != 0 )
    {
         fpub_SetMsg(lXmlhandle, 24310, "����ƾ֤��Ϣʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("����ƾ֤��Ϣʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;            
    }
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("��ʼ��ƾ֤����(����)����"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}

