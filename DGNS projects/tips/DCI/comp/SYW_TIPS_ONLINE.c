/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V3.0.00
����ϵͳ:AIX5.3
�ļ�����:SYW_TIPS_ONLINE.ec
�ļ�����:TIPS����ʵʱ����
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:Tuql
��������:
��    ��:
�޸�����:20141103 leejn mod DCI
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
EXEC SQL INCLUDE  "../eh/tips_drls.eh";/* ������ˮ 
EXEC SQL INCLUDE  "../eh/tips_yhsbcx.eh";/* �����걨��ѯ 
EXEC SQL INCLUDE  "../eh/tips_wtgxdj.eh";/* ί�й�ϵ�Ǽ� 
EXEC SQL INCLUDE  "../eh/tips_pzsj.eh";/* ƾ֤���ݱ� 
EXEC SQL INCLUDE  "../eh/tips_zygsbw.eh";/* ���ɸ�ʽ���� 
EXEC SQL INCLUDE  "../eh/tips_taxtypemx.eh";*/

/* add dci 20141103 */
#include "../eh/tips_drls.h"/* ������ˮ */
#include "../eh/tips_yhsbcx.h"/* �����걨��ѯ */
#include "../eh/tips_wtgxdj.h"/* ί�й�ϵ�Ǽ� */
#include "../eh/tips_wtgxdjlsls.h"/* ί�й�ϵ�Ǽ���ʷ��ˮ */
#include "../eh/tips_pzsj.h"/* ƾ֤���ݱ� */
#include "../eh/tips_zygsbw.h"/* ���ɸ�ʽ���� */
#include "../eh/tips_taxtypemx.h" 
/* end add dci 20141103 */

#define SQLNOTFOUND_TIPS ( \
                (sqlca.sqlcode == 100) \
             || (sqlca.sqlcode == 1403) \
             || (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0) \
             )

int sQj2Bj(char s[200] , char *st);


/* �Ǽ�ƾ֤��Ϣ--ʵʱ���� */
int prv_tips_InitPZSJ_db(HXMLTREE lXmlhandle, SDB_TIPS_DRLS stDrls)
{
    /* add dci 20141103 
    EXEC SQL BEGIN DECLARE SECTION;
         SDB_TIPS_PZSJ stPzsj;
    EXEC SQL END DECLARE SECTION;
    */
    
    char sBuf[256];/* ��ʱ���� */
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;		
    SDB_TIPS_PZSJ stPzsj;
		/* end add dci 20141103 */    
    
    memset(&stPzsj, 0x00, sizeof(stPzsj));
    
    pstrcopy(stPzsj.zwrq, stDrls.zwrq, sizeof(stPzsj.zwrq));
    stPzsj.zhqzlsh = stDrls.zhqzlsh;
    pstrcopy(stPzsj.jyrq, stDrls.workdate, sizeof(stPzsj.jyrq));
    pstrcopy(stPzsj.dqdh, stDrls.dqdh, sizeof(stPzsj.dqdh));
    pstrcopy(stPzsj.jgdh, stDrls.jgdh, sizeof(stPzsj.jgdh));
    pstrcopy(stPzsj.jygy, stDrls.jygy, sizeof(stPzsj.jygy));
    pstrcopy(stPzsj.zddh, stDrls.zddh, sizeof(stPzsj.zddh));
    pstrcopy(stPzsj.msgno, stDrls.msgno, sizeof(stPzsj.msgno));/* ���ı�� */
    pstrcopy(stPzsj.entrustdate, stDrls.entrustdate, sizeof(stPzsj.entrustdate));
    pstrcopy(stPzsj.taxorgcode, stDrls.taxorgcode, sizeof(stPzsj.taxorgcode));
    pstrcopy(stPzsj.packno, stDrls.trano, sizeof(stPzsj.packno));
    pstrcopy(stPzsj.trano, stDrls.trano, sizeof(stPzsj.trano));
    pstrcopy(stPzsj.payeebankno, stDrls.payeebankno, sizeof(stPzsj.payeebankno));
    pstrcopy(stPzsj.payeename, stDrls.payeename, sizeof(stPzsj.payeename));
    pstrcopy(stPzsj.paybkcode, stDrls.paybkcode, sizeof(stPzsj.paybkcode));
    pstrcopy(stPzsj.payopbkcode, stDrls.payopbkcode, sizeof(stPzsj.payopbkcode));
    pstrcopy(stPzsj.payacct, stDrls.payacct, sizeof(stPzsj.payacct));
    pstrcopy(stPzsj.handorgname, stDrls.handorgname, sizeof(stPzsj.handorgname));
    stPzsj.jyje=stDrls.jyje;
    pstrcopy(stPzsj.corpcode, "", sizeof(stPzsj.corpcode));
    pstrcopy(stPzsj.taxvouno, stDrls.taxvouno, sizeof(stPzsj.taxvouno));
    pstrcopy(stPzsj.taxpaycode, stDrls.taxpaycode, sizeof(stPzsj.taxpaycode));
    stPzsj.pzlx[0]='1';
    stPzsj.dycs=0;
    stPzsj.dzbz[0]='0';
    pstrcopy(stPzsj.pzsjwjm, stDrls.spxx, sizeof(stPzsj.pzsjwjm));
    /* add by lijn 20140825 */
    pstrcopy(stPzsj.jyqd, stDrls.jyqd, sizeof(stPzsj.jyqd));
    pstrcopy(stPzsj.zjrq      , stDrls.zjrq      , sizeof(stPzsj.zjrq      ));
    pstrcopy(stPzsj.zjsj      , stDrls.zjsj      , sizeof(stPzsj.zjsj      ));
    pstrcopy(stPzsj.zjlsh     , stDrls.zjlsh     , sizeof(stPzsj.zjlsh     ));
    pstrcopy(stPzsj.jyzt      , stDrls.jyzt      , sizeof(stPzsj.jyzt      ));
    stPzsj.hxdzbz[0]='0';
    pstrcopy(stPzsj.qsbz      , stDrls.qsbz      , sizeof(stPzsj.qsbz      ));
  	pstrcopy(stPzsj.taxpayname, stDrls.taxpayname, sizeof(stPzsj.taxpayname));
    pstrcopy(stPzsj.qspch			, ""			, sizeof(stPzsj.qspch			));
    pstrcopy(stPzsj.chkdate   , stDrls.chkdate   , sizeof(stPzsj.chkdate   ));
    pstrcopy(stPzsj.chkacctord, stDrls.chkacctord, sizeof(stPzsj.chkacctord));
    
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
		LOG(LM_STD,Fmtmsg("taxpayname[%s], taxpayname=[%s]",stPzsj.taxpayname, stDrls.taxpayname),"ERROR")
    /* end add 20140825 */
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_pzsj", SD_TIPS_PZSJ, NUMELE(SD_TIPS_PZSJ), &stPzsj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	LOG(LM_STD,Fmtmsg("����ƾ֤��Ϣʧ��,szwrq[%s], zhqzlsh=[%d]",stPzsj.zwrq, stPzsj.zhqzlsh),"ERROR")
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����ƾ֤��Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))
    }   
    /* end add dci 20141103 */
     
    /* DCI MOD 20141103 
    EXEC SQL INSERT INTO tips_pzsj VALUES(:stPzsj);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))    
    if ( SQLERR )
    {
        LOG(LM_STD,Fmtmsg("����ƾ֤��Ϣʧ��,szwrq[%s], zhqzlsh=[%d]",stPzsj.zwrq, stPzsj.zhqzlsh),"ERROR")        
        return -1;
    }
    */
    
    return 0;    
}


/*
  ����Э�����ţ�ʹ��xh2�ֶ�
  4λ���+8λ���
*/
int prv_tips_genxh2(int ioffset, char *szwrq, char *sxh_ret)
{
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
      char sxh[40],sxh_upd[40];
    /* EXEC SQL END DECLARE SECTION; add dci 20141103 */
    char sxh_new[40];
    int inum=0;
    
    int iRet;
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
    char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/  
    
    if (strlen(szwrq)!=8)  
    {
        LOG(LM_STD,Fmtmsg("������������ڸ�ʽ����ȷ,szwrq[%s]",szwrq),"ERROR")
        return -9;
    }	
    /*   EXEC SQL BEGIN WORK;*/
  	/* mod 20141103 
    EXEC SQL lock table tips_sfxyxh in exclusive mode;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if(SQLERR)
    {
        LOG(LM_STD,Fmtmsg("������ű�ʧ��[tips_sfxyxh],sqlcode[%d]",sqlca.sqlcode),"ERROR")
        EXEC SQL rollback WORK;
        return -1;
    }
    EXEC SQL select xh2 into :sxh from tips_sfxyxh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
    if((SQLERR) || ( SQLNOTFOUND_TIPS ))
    {
        LOG(LM_STD,Fmtmsg("ȡ��ǰ��ź�ʧ��[tips_sfxyxh],sqlcode[%d]",sqlca.sqlcode),"ERROR") 
        EXEC SQL rollback WORK;
        return -1;
    }
    trim(sxh);
    if (strlen(sxh)!=12)   			          /*û������
       sprintf(sxh_new,"%-4.4s%08ld",szwrq,1);
    else  if ( memcmp(sxh,szwrq,4)!=0 )	  /*�ǵ���
       sprintf(sxh_new,"%-4.4s%08ld",szwrq,1);
    else
    {
       sprintf(sxh_new,"%012.0f",atof(sxh)+1);
    }	   
    sprintf(sxh_upd,"%012.0f",atof(sxh_new)+ioffset-1);	 
    EXEC SQL update tips_sfxyxh set xh2 = :sxh_upd;
    if ( SQLUPDATEERR )
    {
        LOG(LM_DEBUG,Fmtmsg("�������2ʧ��[tips_sfxyxh],xh[%s],xh_new[%s],sqlcode[%d]",
                  sxh,sxh_new,sqlca.sqlcode),"ERROR") 
        EXEC SQL rollback WORK;
        return -1;
    }
    EXEC SQL COMMIT WORK;
    if ( SQLERR )
    {
      LOG(LM_STD,Fmtmsg("�������2COMMITʧ��,sqlcode[%d]",sqlca.sqlcode),"ERROR");
      EXEC SQL rollback WORK; 
      return -1;	
    }
    /* end 	mod 20141103 */
    
    /* DCI add 20141103 */
    iRet = DCIBegin();
		if( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
			
			LOG(LM_STD,Fmtmsg("DCIBegin"),"ERROR");
			return COMPRET_FAIL;
		}

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "lock table tips_sfxyxh in exclusive mode");     	
    iRet = DCIExecuteDirect(sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        LOG(LM_STD,Fmtmsg("������ű�ʧ��[tips_sfxyxh]"),"ERROR")
        DCIRollback();
        return -1;
        
    }
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select xh2 from tips_sfxyxh");     	
    iRet = DBSelectToVar(sErrmsg, &sxh, sSql1);
    if ( iRet < 0 || iRet == 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        LOG(LM_STD,Fmtmsg("ȡ��ǰ��ź�ʧ��[tips_sfxyxh]"),"ERROR") 
        DCIRollback();
        return -1;
    }
        
    trim(sxh);
    if (strlen(sxh)!=12)   			          /*û������ */
       sprintf(sxh_new,"%-4.4s%08ld",szwrq,1);
    else  if ( memcmp(sxh,szwrq,4)!=0 )	  /*�ǵ��� */
       sprintf(sxh_new,"%-4.4s%08ld",szwrq,1);
    else
    {
       sprintf(sxh_new,"%012.0f",atof(sxh)+1);
    }	   
    sprintf(sxh_upd,"%012.0f",atof(sxh_new)+ioffset-1);
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_sfxyxh set xh2 ='%s'",sxh_upd);     	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        DCIRollback();
        
        LOG(LM_DEBUG,Fmtmsg("�������2ʧ��[tips_sfxyxh],xh[%s],xh_new[%s]",
                  sxh,sxh_new),"ERROR") 
        return -1;
    }
    iRet =DCICommit();
    /* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      LOG(LM_STD,Fmtmsg("�������2COMMITʧ��"),"ERROR");
      DCIRollback(); 
      return -1;	
    }
    */
    strcpy(sxh_ret,sxh_new);
    LOG(LM_STD,Fmtmsg("�������2�ɹ�,���[%s]-[%s]",sxh_new,sxh_upd),"INFO");
    return 0;
}


/************************************************************************
��̬�����������
�����������: SYW_TIPS_YzcxSFXY
�������: ��֤�볷������Э��
�������: 
  ��֤�볷������Э��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�	tips_wtgxdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��20��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_YzcxSFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sTaxOrgCode[12+1];/* ���ջ��ش��� */
	    char sTaxOrgCode_t[12+1];/* ���ջ��ش��� */
        char sPayBkCode[12+1];/* �������к� */
		char sPayBkCode_t[12+1];/* �������к� */
        char sPayAcct[32+1];/* �����˺� */
		char sPayAcct_t[32+1];/* �����˺� */
    	char sProtocolNo[60+1];/* Э����� */
        char sProtocolNo_t[60+1];/* Э����� */

		char sHandOrgName[200+1];/* �ɿλ���� */
        char sHandOrgName_t[200+1];/* �ɿλ���� */

		char sTaxPayCode[20+1];/* ��˰�˱��� */
        char sTaxPayCode_t[20+1];/* ��˰�˱��� */
        char sWtgxzt[1+1];/* ί�й�ϵ״̬ */
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    char sVCSign[1+1];/* ��֤��־ */
    char sYzxgrq[8+1];
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(7);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(1, sBuf, "���ջ��ش���")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(2, sBuf, "�������к�")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "�����˺�")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(4, sBuf, "Э�����")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sHandOrgName, 0x00, sizeof(sHandOrgName));
    COMP_GETPARSEPARAS(5, sBuf, "�ɿλ����")
    pstrcopy(sHandOrgName, sBuf, sizeof(sHandOrgName));
    trim(sHandOrgName);
    memset(sBuf, 0x00, sizeof(sBuf));
    sQj2Bj(sHandOrgName,sBuf);
    memset(sHandOrgName, 0x00, sizeof(sHandOrgName));
    strcpy(sHandOrgName,sBuf);
    LOG(LM_STD,Fmtmsg("�ɿλ����_t[%s]", sHandOrgName), fpub_GetCompname(lXmlhandle))    
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
    COMP_GETPARSEPARAS(6, sBuf, "��˰�˱���")
    pstrcopy(sTaxPayCode, sBuf, sizeof(sTaxPayCode));
    trim(sTaxPayCode);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sVCSign, 0x00, sizeof(sVCSign));
    COMP_GETPARSEPARAS(7, sBuf, "��֤��־")
    pstrcopy(sVCSign, sBuf, sizeof(sVCSign));
    trim(sVCSign); 

	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sYzxgrq, 0x00, sizeof(sYzxgrq));
	COMP_SOFTGETXML("/tips/zwrq", sBuf);
	trim(sBuf);
	pstrcopy(sYzxgrq, sBuf, sizeof(sYzxgrq));
	
    LOG(LM_STD,Fmtmsg("��֤��������Э�鿪ʼ����... ���ջ��ش���[%s],�������к�[%s],�����˺�[%s]", 
        sTaxOrgCode, sPayBkCode, sPayAcct), fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("Э�����[%s],�ɿλ����[%s],��˰�˱���[%s],��֤��־[%s]", 
        sProtocolNo, sHandOrgName, sTaxPayCode, sVCSign), fpub_GetCompname(lXmlhandle))        

    /* ��ѯ�ͻ�ί�й�ϵ */
    memset(sWtgxzt, 0x00, sizeof(sWtgxzt));
    memset(sProtocolNo_t, 0x00, sizeof(sProtocolNo_t));
    memset(sHandOrgName_t, 0x00, sizeof(sHandOrgName_t));
    memset(sTaxPayCode_t, 0x00, sizeof(sTaxPayCode_t));
    
    /* add DCI 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT taxorgcode,paybkcode,payacct,wtgxzt, protocolno,handorgname, taxpaycode FROM tips_wtgxdj\
    	WHERE protocolno ='%s'", sProtocolNo);     	
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,sTaxOrgCode_t,sPayBkCode_t,sPayAcct_t,sWtgxzt, sProtocolNo_t,sHandOrgName_t,sTaxPayCode_t);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24346, Fmtmsg("��ѯί�й�ϵ�ǼǱ�ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�ǼǱ�ʧ��"), 
            fpub_GetCompname(lXmlhandle));	
        
    }
    if ( iRet == 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24347, Fmtmsg("����Э��δǩԼ"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э��δǩԼ"), 
            fpub_GetCompname(lXmlhandle));     
    }
    /* end add DCI 20141103 */  
    
    /* DCI MOD 20141103 
    EXEC SQL SELECT wtgxzt, protocolno, to_single_byte(handorgname), taxpaycode
         INTO :sWtgxzt, :sProtocolNo_t, :sHandOrgName_t, :sTaxPayCode_t
         FROM tips_wtgxdj
         WHERE taxorgcode = :sTaxOrgCode
           AND paybkcode = :sPayBkCode
           AND payacct = :sPayAcct
           AND protocolno = :sProtocolNo;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24346, Fmtmsg("��ѯί�й�ϵ�ǼǱ�ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�ǼǱ�ʧ��"), 
            fpub_GetCompname(lXmlhandle));	
    }
    if ( SQLNOTFOUND_TIPS )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24347, Fmtmsg("����Э��δǩԼ�����ջ��ش��š������˺Ų���."));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э��δǩԼ�����ջ��ش��š������˺Ų���."), 
            fpub_GetCompname(lXmlhandle));        
    }
    */

	trim(sTaxOrgCode_t);
	trim(sPayBkCode_t);
	trim(sPayAcct_t);
    trim(sWtgxzt);
	trim(sProtocolNo_t);
    trim(sHandOrgName_t);
    trim(sTaxPayCode_t);
    LOG(LM_STD,Fmtmsg("���ջ��ش���_t[%s],�������к�_t[%s],�����˻�_t[%s],Э�����_t[%s],�ɿλ����_t[%s],��˰�˱���_t[%s]", 
        sTaxOrgCode_t,sPayBkCode_t,sPayAcct_t,sProtocolNo_t, sHandOrgName_t, sTaxPayCode_t), fpub_GetCompname(lXmlhandle))    

    /* �ж�ί�й�ϵ״̬ */
    if ( sWtgxzt[0]=='1' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24348, Fmtmsg("����Э�鱻����"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э�鱻����"), 
            fpub_GetCompname(lXmlhandle));         
    }        
    if ( sWtgxzt[0]=='2' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24349, Fmtmsg("����Э�鱻����"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э�鱻����"), 
            fpub_GetCompname(lXmlhandle));         
    }
    if ( sWtgxzt[0]!='0' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24350, Fmtmsg("����Э��״̬�쳣"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э��״̬�쳣"), 
            fpub_GetCompname(lXmlhandle));         
    }

	if (strcmp(sTaxOrgCode_t, sTaxOrgCode) != 0) {
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24351, Fmtmsg("���ջ��ز�һ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ջ��ز�һ��"), 
            fpub_GetCompname(lXmlhandle)); 
	}
	if (strcmp(sPayBkCode_t, sPayBkCode) != 0) {
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24351, Fmtmsg("�������кŲ�һ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�������кŲ�һ��"), 
            fpub_GetCompname(lXmlhandle)); 
	}
	if (strcmp(sPayAcct_t, sPayAcct) != 0) {
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24351, Fmtmsg("�����˻���һ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����˻���һ��"), 
            fpub_GetCompname(lXmlhandle)); 
	}
	
    /* �ж�Э������Ƿ�һ�� */
    if ( strcmp(sProtocolNo, sProtocolNo_t) != 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24351, Fmtmsg("Э����Ų�һ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("Э����Ų�һ��"), 
            fpub_GetCompname(lXmlhandle));         
    }    
    /* �жϽɿλ�����Ƿ�һ�� */
    if ( strcmp(sHandOrgName, sHandOrgName_t) != 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24352, Fmtmsg("�ɿλ���Ʋ�һ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�ɿλ���Ʋ�һ��"), 
            fpub_GetCompname(lXmlhandle));
    }
    /* �ж���˰�˱����Ƿ�һ�� 
    if ( strcmp(sTaxPayCode, sTaxPayCode_t) != 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24353, Fmtmsg("��˰�˱��벻һ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��˰�˱��벻һ��"), 
            fpub_GetCompname(lXmlhandle));
    }*/
    
    /* DCI 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    
		if (sVCSign[0]=='0')/* ��֤ */
    {
        snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj set yzbz='1',yzxgrq='%s' WHERE taxorgcode='%s' AND paybkcode ='%s' AND payacct ='%s' AND protocolno ='%s'",\
        	sYzxgrq,sTaxOrgCode, sPayBkCode, sPayAcct, sProtocolNo);    	
    		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
    		iRet = DCIExecuteDirect(sSql1);	 
    		if ( iRet < 0 || iRet == 0)/* add 20141215 iRet=0Ҳ��Ϊ���²��ɹ� */
    		{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        		        
        			fpub_SetMsg(lXmlhandle, 24354, "����ί�й�ϵ�ǼǱ�ʧ��");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����ί�й�ϵ�ǼǱ�ʧ��"),
                 fpub_GetCompname(lXmlhandle))
    		}
        LOG(LM_STD,Fmtmsg("����Э����֤ͨ��"), fpub_GetCompname(lXmlhandle))
    }else
    {
        snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj set yzbz='2',yzxgrq='%s' WHERE taxorgcode='%s' AND paybkcode ='%s' AND payacct ='%s' AND protocolno ='%s'",\
        	sYzxgrq,sTaxOrgCode, sPayBkCode, sPayAcct, sProtocolNo);     	
        LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")
    		iRet = DCIExecuteDirect(sSql1);	        	 
    		if ( iRet < 0 || iRet == 0)/* add 20141215 iRet=0Ҳ��Ϊ���²��ɹ� */
    		{
        		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        		        
        			fpub_SetMsg(lXmlhandle, 24354, "����ί�й�ϵ�ǼǱ�ʧ��");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����ί�й�ϵ�ǼǱ�ʧ��"),
                 fpub_GetCompname(lXmlhandle))
    		}
        LOG(LM_STD,Fmtmsg("����Э�鳷��ͨ��"), fpub_GetCompname(lXmlhandle))        
    } 
    /* END DCI 20141103 */
    
    /* ������֤������־���´��� 
    if (sVCSign[0]=='0')/* ��֤ 
    {
        EXEC SQL UPDATE tips_wtgxdj
             SET  yzbz='1'
            WHERE taxorgcode = :sTaxOrgCode
              AND paybkcode = :sPayBkCode
              AND payacct = :sPayAcct
           		AND protocolno = :sProtocolNo;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
        if ( SQLERR )	
        {
             fpub_SetMsg(lXmlhandle, 24354, "����ί�й�ϵ�ǼǱ�ʧ��");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����ί�й�ϵ�ǼǱ�ʧ��"),
                 fpub_GetCompname(lXmlhandle))
        }
        LOG(LM_STD,Fmtmsg("����Э����֤ͨ��"), fpub_GetCompname(lXmlhandle))
    }else
    {
        EXEC SQL UPDATE tips_wtgxdj
             SET  yzbz='2'
            WHERE taxorgcode = :sTaxOrgCode
              AND paybkcode = :sPayBkCode
              AND payacct = :sPayAcct           
           		AND protocolno = :sProtocolNo;
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR")
        if ( SQLERR )	
        {
             fpub_SetMsg(lXmlhandle, 24354, "����ί�й�ϵ�ǼǱ�ʧ��");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����ί�й�ϵ�ǼǱ�ʧ��"),
                 fpub_GetCompname(lXmlhandle))
        }
        LOG(LM_STD,Fmtmsg("����Э�鳷��ͨ��"), fpub_GetCompname(lXmlhandle))        
    }  
    */
          
    fpub_SetMsg(lXmlhandle, 0, "����Э����֤�볷������ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("����Э����֤�볷������ɹ�"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_JySFXY
�������: У������Э��
�������: 
  У������Э��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�	tips_wtgxdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��20��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_JySFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sTaxOrgCode[12+1];/* ���ջ��ش��� */
        char sPayBkCode[12+1];/* �������к� */
        char sPayAcct[32+1];/* �����˺� */
        char sWtgxzt[1+1];/* ί�й�ϵ״̬ */
        char sYzbz[1+1];/* ��֤��־ */
        char sTaxPayCode[20+1];/* ��˰�˱��� */
        char sProtocolNo[60+1];/* Э����� */
        char sDqdh[10+1];/* �������� add by tuql 20090909*/
        char sJgdh[10+1];/* �������� add by tuql 20090909*/
        char sPayAcct2[32+1];/* �����˺�2 add by liurj 20180713 */
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    char sMsgNo[4+1];/* ���ı�� */
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(5);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(1, sBuf, "���ջ��ش���")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(2, sBuf, "�������к�")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "�����˺�")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(4, sBuf, "Э�����")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sMsgNo, 0x00, sizeof(sMsgNo));
    COMP_GETPARSEPARAS(5, sBuf, "���ı��")
    pstrcopy(sMsgNo, sBuf, sizeof(sMsgNo));
    trim(sMsgNo);

    LOG(LM_STD,Fmtmsg("У������Э�鿪ʼ����... ���ջ��ش���[%s],�������к�[%s],�����˺�[%s]", 
        sTaxOrgCode, sPayBkCode, sPayAcct), fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("Э�����[%s],���ı��[%s]", sProtocolNo, sMsgNo), fpub_GetCompname(lXmlhandle)) 

    memset(sWtgxzt, 0x00, sizeof(sWtgxzt));
    memset(sYzbz, 0x00, sizeof(sYzbz));
    memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
    memset(sDqdh, 0x00, sizeof(sDqdh));
    memset(sJgdh, 0x00, sizeof(sJgdh));
    memset(sPayAcct2, 0x00, sizeof(sPayAcct2)); /*add by liurj 20180713*/
    
    /* DCI 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    if ( sProtocolNo[0]=='\0' )
    {
    	/* modefied by liurj 20180713 ���Ӳ�ѯ�ֶ�payacct2 */
    	snprintf( sSql1, sizeof(sSql1), "SELECT wtgxzt, yzbz, taxpaycode,djdqdh, djjgdh, payacct2 FROM tips_wtgxdj \
    		WHERE payacct='%s' and paybkcode='%s'",sPayAcct,sPayBkCode);     
        
    }else
    {
    	/* 20150730 �޸�ΪͬʱУ��Э��š������˺� */
    	/* modefied by liurj 20180713 ���Ӳ�ѯ�ֶ�payacct2 */
      snprintf( sSql1, sizeof(sSql1), "SELECT wtgxzt, yzbz, taxpaycode,djdqdh, djjgdh, payacct2 FROM tips_wtgxdj \
    		WHERE protocolno='%s' and payacct='%s' and paybkcode='%s'",sProtocolNo,sPayAcct,sPayBkCode); 
         
    }  
         
   
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")  
    /* modefied by liurj 20180713 ���Ӳ�ѯ�ֶ�payacct2 */
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&sWtgxzt, &sYzbz, &sTaxPayCode, &sDqdh, &sJgdh, &sPayAcct2);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24346, Fmtmsg("��ѯί�й�ϵ�ǼǱ�ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�ǼǱ�ʧ��"), 
            fpub_GetCompname(lXmlhandle));	
        
    }
    if ( iRet == 0 )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24347, Fmtmsg("����Э��δǩԼ"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э��δǩԼ"), 
            fpub_GetCompname(lXmlhandle));     
    }
    /* end add DCI 20141103 */
    
    /* MOD DCI 20141103
    if ( sProtocolNo[0]=='\0' )
    {
        EXEC SQL SELECT wtgxzt, yzbz, taxpaycode,djdqdh, djjgdh
             INTO :sWtgxzt, :sYzbz, :sTaxPayCode, :sDqdh, :sJgdh
             FROM tips_wtgxdj
             WHERE  payacct=:sPayAcct;
    }else
    {
        EXEC SQL SELECT wtgxzt, yzbz, taxpaycode,djdqdh, djjgdh
             INTO :sWtgxzt, :sYzbz, :sTaxPayCode, :sDqdh, :sJgdh
             FROM tips_wtgxdj
             WHERE  payacct=:sPayAcct
               AND  protocolno=:sProtocolNo;
    }        
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 99003, Fmtmsg("��ѯί�й�ϵ�ǼǱ�ʧ��"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�ǼǱ�ʧ��"), 
            fpub_GetCompname(lXmlhandle));
    }
    if ( SQLNOTFOUND_TIPS )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 24009, Fmtmsg("����Э��δǩԼ"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э��δǩԼ"), 
            fpub_GetCompname(lXmlhandle));        
    }
    */
    
    trim(sWtgxzt);trim(sYzbz);trim(sTaxPayCode);
    LOG(LM_STD,Fmtmsg("ί�й�ϵ״̬[%s],��֤״̬[%s],��˰�˱���_t[%s]", 
        sWtgxzt, sYzbz, sTaxPayCode), fpub_GetCompname(lXmlhandle)) 

    /* �ж�ί�й�ϵ״̬ */
    if ( sWtgxzt[0]=='2' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24009, Fmtmsg("����Э�鱻����"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э�鱻����"), 
            fpub_GetCompname(lXmlhandle));         
    }        
    if ( sWtgxzt[0]=='3' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24009, Fmtmsg("����Э�鱻����"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э�鱻����"), 
            fpub_GetCompname(lXmlhandle));         
    }
    if ( sWtgxzt[0]!='0' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24009, Fmtmsg("����Э��״̬�쳣"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э��״̬�쳣"), 
            fpub_GetCompname(lXmlhandle));         
    }
    /* �ж�ί�й�ϵ��֤��־ */
    if ( sYzbz[0]!='1' )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24009, Fmtmsg("����Э��δ��֤���ѳ���"));
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э��δ��֤���ѳ���"), 
            fpub_GetCompname(lXmlhandle));         
    }
    
    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "/tips/MSG/Payment%s/TaxPayCode", sMsgNo);
    trim(sBuf);
    COMP_SOFTSETXML(sBuf, sTaxPayCode) 
    COMP_SOFTSETXML("/tips/TaxPayCode", sTaxPayCode)
    
    /* add by tuql 20090910 ��ǩԼʱ�ĵ������Ÿ��µ�����ȥ */
    COMP_SOFTSETXML("/tips/djdqdh", sDqdh)
    COMP_SOFTSETXML("/tips/djjgdh", sJgdh)
    
    /* add by liurj 20180713 ������Э����е�payacct2���浽�ڵ� */
    COMP_SOFTSETXML("/tips/PayAcct2", sPayAcct2)
    
    fpub_SetMsg(lXmlhandle, 0, "У������Э��ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("У������Э��ɹ�"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}
/************************************************************************
��̬�����������
�����������: SYW_TIPS_InsDRLS
�������: �Ǽǵ�����ˮ
�������: 
  �Ǽǵ�����ˮ
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�	tips_drls

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��23��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InsDRLS(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
         SDB_TIPS_DRLS stDrls;
         char sKhh[12+1];
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */ 

    char sBuf[256];
    char sInsDrls[1+1];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
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

    memset(&stDrls, 0x00, sizeof(stDrls));
    /* 1.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zwrq", sBuf)
    pstrcopy(stDrls.zwrq, sBuf, sizeof(stDrls.zwrq));
    if (stDrls.zwrq[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24119, "�������ڲ���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�������ڲ���Ϊ��"), 
            fpub_GetCompname(lXmlhandle))         
    }        
    /* 2.�ۺ�ǰ����ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh", sBuf)
    if (sBuf[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24120, "�ۺ�ǰ����ˮ�Ų���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�ۺ�ǰ����ˮ�Ų���Ϊ��"), 
            fpub_GetCompname(lXmlhandle))         
    }    
    stDrls.zhqzlsh=atoi(sBuf);
    
    LOG(LM_STD,Fmtmsg("�Ǽǵ�����ˮ��ʼ����...��������[%s]�ۺ�ǰ����ˮ��[%d]",
        stDrls.zwrq, stDrls.zhqzlsh),"INFO");

    /* 3.�������� mod by tuql 20090505 �޸�Ϊ��/pub/subsysname��ȡֵ*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/subsysname", sBuf)
    pstrcopy(stDrls.jyqd, sBuf, sizeof(stDrls.jyqd));
    /* 4.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stDrls.workdate, sBuf, sizeof(stDrls.workdate));
    /* 5.ί������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate", sBuf)
    pstrcopy(stDrls.entrustdate, sBuf, sizeof(stDrls.entrustdate));
    if (stDrls.entrustdate[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24121, "ί�����ڲ���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("ί�����ڲ���Ϊ��"), 
            fpub_GetCompname(lXmlhandle))         
    }
    /* 6.���ջ��ش��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode", sBuf)
    pstrcopy(stDrls.taxorgcode, sBuf, sizeof(stDrls.taxorgcode));
    if (stDrls.taxorgcode[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24122, "���ջ��ش��벻��Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���ջ��ش��벻��Ϊ��"), 
            fpub_GetCompname(lXmlhandle))         
    }
    /* 7.������ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraNo", sBuf)
    pstrcopy(stDrls.trano, sBuf, sizeof(stDrls.trano));
    if (stDrls.trano[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24123, "������ˮ�Ų���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("������ˮ�Ų���Ϊ��"), 
            fpub_GetCompname(lXmlhandle))         
    }
    /* 8.���ı�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MsgNo", sBuf)
    pstrcopy(stDrls.msgno, sBuf, sizeof(stDrls.msgno));
    if (stDrls.msgno[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24124, "���ı�Ų���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���ı�Ų���Ϊ��"), 
            fpub_GetCompname(lXmlhandle))         
    }
    /* 9.ί������2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate2", sBuf)
    pstrcopy(stDrls.entrustdate2, sBuf, sizeof(stDrls.entrustdate2));
    /* 10.������ˮ��2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraNo2", sBuf)
    pstrcopy(stDrls.trano2, sBuf, sizeof(stDrls.trano2));
    /* 11.�ۺ�ǰ����ˮ��2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh2", sBuf)
    stDrls.zhqzlsh2=atoi(sBuf);
    /* 12.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stDrls.chkdate, sBuf, sizeof(stDrls.chkdate));
    /* 13.�������κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctOrd", sBuf)
    pstrcopy(stDrls.chkacctord, sBuf, sizeof(stDrls.chkacctord));
    /* 14.������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/HandleType", sBuf)
    pstrcopy(stDrls.handletype, sBuf, sizeof(stDrls.handletype));
    /* 15.������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TreCode", sBuf)
    pstrcopy(stDrls.trecode, sBuf, sizeof(stDrls.trecode));
    /* 16.�տ����к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
    pstrcopy(stDrls.payeebankno, sBuf, sizeof(stDrls.payeebankno));
    /* 17.�տλ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeOrgCode", sBuf)
    pstrcopy(stDrls.payeeorgcode, sBuf, sizeof(stDrls.payeeorgcode));
    
    /* 18.�տ����ʺ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeAcct", sBuf)
    pstrcopy(stDrls.payeeacct, sBuf, sizeof(stDrls.payeeacct));
    /* 19.�տ������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeName", sBuf)
    pstrcopy(stDrls.payeename, sBuf, sizeof(stDrls.payeename));
    trim(stDrls.payeename);
    /* 20.�����к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
    pstrcopy(stDrls.paybkcode, sBuf, sizeof(stDrls.paybkcode));
    /* 21.��������к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayOpBkCode", sBuf)
    pstrcopy(stDrls.payopbkcode, sBuf, sizeof(stDrls.payopbkcode));
    /* 22.Э����� add by tuql 20091112*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ProtocolNo", sBuf)
    pstrcopy(stDrls.protocolno, sBuf, sizeof(stDrls.protocolno));
    
    /* 23.�������ʺ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct", sBuf)
    pstrcopy(stDrls.payacct, sBuf, sizeof(stDrls.payacct));
    /* 24.�ɿλ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/HandOrgName", sBuf)
    pstrcopy(stDrls.handorgname, sBuf, sizeof(stDrls.handorgname));
    trim(stDrls.handorgname);
    /* 25.�����˺� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dfzh", sBuf)
    pstrcopy(stDrls.dfzh, sBuf, sizeof(stDrls.dfzh));
    trim(stDrls.dfzh);
    /* 26.���׽�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraAmt", sBuf)
    stDrls.jyje=atof(sBuf);
    /* 27.˰Ʊ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxVouNo", sBuf)
    pstrcopy(stDrls.taxvouno, sBuf, sizeof(stDrls.taxvouno));
    
    /* 28.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/djdqdh", sBuf)
    pstrcopy(stDrls.dqdh, sBuf, sizeof(stDrls.dqdh));
    trim(stDrls.dqdh);
    /* 29.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/djjgdh", sBuf)
    pstrcopy(stDrls.jgdh, sBuf, sizeof(stDrls.jgdh));
    trim(stDrls.jgdh);
   
    /*memset(sKhh, 0x00, sizeof(sKhh));
    ������������к�
    EXEC SQL SELECT jgdh INTO :sKhh 
	     FROM  tips_jgdhdj  
	     WHERE khqshh=:stDrls.payopbkcode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "��ѯ�������ŵǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ�������ŵǼǱ�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }*/   
     
    /* 30.���׹�Ա */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy", sBuf)
    pstrcopy(stDrls.jygy, sBuf, sizeof(stDrls.jygy));
    trim(stDrls.jygy);
    /* 31.�ն˴��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh", sBuf)
    pstrcopy(stDrls.zddh, sBuf, sizeof(stDrls.zddh));
    trim(stDrls.zddh);
    /* 32.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stDrls.jyrq, sBuf, sizeof(stDrls.jyrq));
    /* 33.����ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stDrls.jysj, sBuf, sizeof(stDrls.jysj));
    /* 34.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjrq", sBuf)
    pstrcopy(stDrls.zjrq, sBuf, sizeof(stDrls.zjrq));
    /* 35.����ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjsj", sBuf)
    pstrcopy(stDrls.zjsj, sBuf, sizeof(stDrls.zjsj));
    /* 36.������ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjlsh", sBuf)
    pstrcopy(stDrls.zjlsh, sBuf, sizeof(stDrls.zjlsh));
    trim(stDrls.zjlsh);
    /* 37.������Ӧ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjxym", sBuf)
    pstrcopy(stDrls.zjxym, sBuf, sizeof(stDrls.zjxym));
    /* 38.������Ӧ��Ϣ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjxyxx", sBuf)
    pstrcopy(stDrls.zjxyxx, sBuf, sizeof(stDrls.zjxyxx));
    trim(stDrls.zjxyxx);
    /* 39.������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/sxf", sBuf)
    stDrls.sxf=atof(sBuf);
    /* 40.�ʻ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhye", sBuf)
    stDrls.zhye=atof(sBuf);
    /* 41.��Ӧ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/respcode", sBuf)
    pstrcopy(stDrls.xym, sBuf, sizeof(stDrls.xym));
    /* 42.��Ӧ��Ϣ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/respmsg", sBuf)
    pstrcopy(stDrls.xyxx, sBuf, sizeof(stDrls.xyxx));
    trim(stDrls.xyxx);
    /* 43.����״̬ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyzt", sBuf)
    pstrcopy(stDrls.jyzt, sBuf, sizeof(stDrls.jyzt));
    if (stDrls.jyzt[0]=='\0')
    {
        fpub_SetMsg(lXmlhandle, 24125, "����״̬����Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("����״̬����Ϊ��"), 
            fpub_GetCompname(lXmlhandle))         
    }
    /* 44.���ʱ�־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dzbz", sBuf)
    pstrcopy(stDrls.dzbz, sBuf, sizeof(stDrls.dzbz));
    if (stDrls.dzbz[0]=='\0')
    {
        strcpy(stDrls.dzbz, "00");
    }    
    /* 45.�����־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsbz", sBuf)
    pstrcopy(stDrls.qsbz, sBuf, sizeof(stDrls.qsbz));
    if (stDrls.qsbz[0]=='\0')
    {
        stDrls.qsbz[0]='0';
    }
    /* 46.��չ��־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/kzbz", sBuf)
    pstrcopy(stDrls.kzbz, sBuf, sizeof(stDrls.kzbz));
    /* 47.��˰�˱��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayCode", sBuf)
    pstrcopy(stDrls.taxpaycode, sBuf, sizeof(stDrls.taxpaycode));
    /* 48.��˰������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName", sBuf)
    trim(sBuf);
    pstrcopy(stDrls.taxpayname, sBuf, sizeof(stDrls.taxpayname));
    /* 49.˰Ʊ��Ϣ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/spxx", sBuf)
    pstrcopy(stDrls.spxx, sBuf, sizeof(stDrls.spxx));
    /* 50.�����ֶ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/czyhbz", sBuf)
    pstrcopy(stDrls.byzd, sBuf, sizeof(stDrls.byzd));
    
    /* ADD DCI 20141103 */
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_drls", SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	    	
    	memset(sInsDrls, 0x00, sizeof(sInsDrls));
      sInsDrls[0]='0';
      COMP_SOFTSETXML("/tips/insdrls", sInsDrls)
      fpub_SetMsg(lXmlhandle, 24112, "�Ǽǵ�����ˮ��ʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("InsDRLS�Ǽǵ�����ˮ��ʧ��"), 
            fpub_GetCompname(lXmlhandle))        
    }
    
    
    iRet =DCICommit();
    /* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      LOG(LM_STD,Fmtmsg("�Ǽǵ�����ˮ��ʧ��"),"ERROR");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("InsDRLS�Ǽǵ�����ˮ��ʧ��"), 
            fpub_GetCompname(lXmlhandle))    
    }
    */

		/* end add DCI 20141103 */
		
    /* DCI MOD 20141103 
    EXEC SQL INSERT INTO tips_drls  VALUES (:stDrls);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        memset(sInsDrls, 0x00, sizeof(sInsDrls));
        sInsDrls[0]='0';
        COMP_SOFTSETXML("/tips/insdrls", sInsDrls)
        fpub_SetMsg(lXmlhandle, 24112, "�Ǽǵ�����ˮ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("InsDRLS�Ǽǵ�����ˮ��ʧ��"), 
            fpub_GetCompname(lXmlhandle))        
    }    
    EXEC SQL COMMIT; /*�����ύ
    */ 
    
    memset(sInsDrls, 0x00, sizeof(sInsDrls));
    sInsDrls[0]='1';
    COMP_SOFTSETXML("/tips/insdrls", sInsDrls)
    fpub_SetMsg(lXmlhandle, 0, "�Ǽǵ�����ˮ��ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�Ǽǵ�����ˮ��ɹ�"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}
/************************************************************************
��̬�����������
�����������: SYW_TIPS_UpdDRLS
�������: ���µ�����ˮ
�������: 
  ���µ�����ˮ
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�	tips_drls

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��23��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_UpdDRLS(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
         SDB_TIPS_DRLS stDrls;
         char sKhh[12+1];
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */ 

    char sBuf[256];
    char sInsDrls[1+1];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
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

    memset(&stDrls, 0x00, sizeof(stDrls));
    /* 1.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zwrq", sBuf)
    pstrcopy(stDrls.zwrq, sBuf, sizeof(stDrls.zwrq));    
    /* 2.�ۺ�ǰ����ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh", sBuf)
    stDrls.zhqzlsh=atoi(sBuf);
    
    LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʼ����...��������[%s]�ۺ�ǰ����ˮ��[%d]",
        stDrls.zwrq, stDrls.zhqzlsh),"INFO");
		
	  memset(sBuf, 0x00, sizeof(sBuf));
	  memset(sInsDrls, 0x00, sizeof(sInsDrls));
	  COMP_SOFTGETXML("/tips/insdrls", sBuf)
	  sInsDrls[0]=sBuf[0];
	  /* �����Ϊ0��Ϊ��,�򲻸���ԭ��ˮ */
	  if (sInsDrls[0]=='0'||sInsDrls[0]=='\0')
	  {
          fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
          LOG(LM_STD,Fmtmsg("����������ˮʧ�ܲ��ظ�����ˮ,����"), fpub_GetCompname(lXmlhandle))
          return COMPRET_SUCC;						
	  }	
    /* 3.�������� mod by tuql 20090505 �޸�Ϊ��/pub/subsysname��ȡֵ*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/subsysname", sBuf)
    pstrcopy(stDrls.jyqd, sBuf, sizeof(stDrls.jyqd));
    /* 4.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stDrls.workdate, sBuf, sizeof(stDrls.workdate));
    /* 5.ί������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate", sBuf)
    pstrcopy(stDrls.entrustdate, sBuf, sizeof(stDrls.entrustdate));
    /* 6.���ջ��ش��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode", sBuf)
    pstrcopy(stDrls.taxorgcode, sBuf, sizeof(stDrls.taxorgcode));
    /* 7.������ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraNo", sBuf)
    pstrcopy(stDrls.trano, sBuf, sizeof(stDrls.trano));
    /* 8.���ı�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MsgNo", sBuf)
    pstrcopy(stDrls.msgno, sBuf, sizeof(stDrls.msgno));
    /* 9.ί������2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/EntrustDate2", sBuf)
    pstrcopy(stDrls.entrustdate2, sBuf, sizeof(stDrls.entrustdate2));
    /* 10.������ˮ��2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraNo2", sBuf)
    pstrcopy(stDrls.trano2, sBuf, sizeof(stDrls.trano2));
    /* 11.�ۺ�ǰ����ˮ��2 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh2", sBuf)
    stDrls.zhqzlsh2=atoi(sBuf);
    /* 12.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stDrls.chkdate, sBuf, sizeof(stDrls.chkdate));
    /* 13.�������κ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ChkAcctOrd", sBuf)
    pstrcopy(stDrls.chkacctord, sBuf, sizeof(stDrls.chkacctord));
    /* 12.������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/HandleType", sBuf)
    pstrcopy(stDrls.handletype, sBuf, sizeof(stDrls.handletype));
    /* 13.������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TreCode", sBuf)
    pstrcopy(stDrls.trecode, sBuf, sizeof(stDrls.trecode));
    /* 14.�տ����к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeBankNo", sBuf)
    pstrcopy(stDrls.payeebankno, sBuf, sizeof(stDrls.payeebankno));
    /* 15.�տλ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeOrgCode", sBuf)
    pstrcopy(stDrls.payeeorgcode, sBuf, sizeof(stDrls.payeeorgcode));
    /* 16.Э����� add by tuql 20091112*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ProtocolNo", sBuf)
    pstrcopy(stDrls.protocolno, sBuf, sizeof(stDrls.protocolno));
    /* 16.�տ����ʺ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeAcct", sBuf)
    pstrcopy(stDrls.payeeacct, sBuf, sizeof(stDrls.payeeacct));
    /* 17.�տ������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayeeName", sBuf)
    pstrcopy(stDrls.payeename, sBuf, sizeof(stDrls.payeename));
    trim(stDrls.payeename);
    /* 18.�����к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode", sBuf)
    pstrcopy(stDrls.paybkcode, sBuf, sizeof(stDrls.paybkcode));
    /* 19.��������к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayOpBkCode", sBuf)
    pstrcopy(stDrls.payopbkcode, sBuf, sizeof(stDrls.payopbkcode));
    /* 20.�������ʺ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct", sBuf)
    pstrcopy(stDrls.payacct, sBuf, sizeof(stDrls.payacct));
    /* 21.�ɿλ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/HandOrgName", sBuf)
    pstrcopy(stDrls.handorgname, sBuf, sizeof(stDrls.handorgname));
    trim(stDrls.handorgname);
    /* 22.�����˺� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dfzh", sBuf)
    pstrcopy(stDrls.dfzh, sBuf, sizeof(stDrls.dfzh));
    trim(stDrls.dfzh);
    /* 22.���׽�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TraAmt", sBuf)
    stDrls.jyje=atof(sBuf);
    /* 23.˰Ʊ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxVouNo", sBuf)
    pstrcopy(stDrls.taxvouno, sBuf, sizeof(stDrls.taxvouno));
    /* 24.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/djdqdh", sBuf)/* mod by tuql 20090909 ��dqdh-->djdqdh */
    pstrcopy(stDrls.dqdh, sBuf , sizeof(stDrls.dqdh));
    trim(stDrls.dqdh);
    /* 25.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/djjgdh", sBuf)
    pstrcopy(stDrls.jgdh, sBuf, sizeof(stDrls.jgdh));
    trim(stDrls.jgdh);
    /*������������к�
    EXEC SQL SELECT jgdh INTO :sKhh 
	     FROM  tips_jgdhdj  
	     WHERE khqshh=:stDrls.payopbkcode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "��ѯ�������ŵǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ�������ŵǼǱ�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }*/    
    /* 26.���׹�Ա */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy", sBuf)
    pstrcopy(stDrls.jygy, sBuf, sizeof(stDrls.jygy));
    trim(stDrls.jygy);
    /* 27.�ն˴��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh", sBuf)
    pstrcopy(stDrls.zddh, sBuf, sizeof(stDrls.zddh));
    trim(stDrls.zddh);
    /* 28.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stDrls.jyrq, sBuf, sizeof(stDrls.jyrq));
    /* 29.����ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stDrls.jysj, sBuf, sizeof(stDrls.jysj));
    /* 30.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjrq", sBuf)
    pstrcopy(stDrls.zjrq, sBuf, sizeof(stDrls.zjrq));
    /* 31.����ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjsj", sBuf)
    pstrcopy(stDrls.zjsj, sBuf, sizeof(stDrls.zjsj));
    /* 32.������ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjlsh", sBuf)
    pstrcopy(stDrls.zjlsh, sBuf, sizeof(stDrls.zjlsh));
    trim(stDrls.zjlsh);
    /* 33.������Ӧ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjxym", sBuf)
    pstrcopy(stDrls.zjxym, sBuf, sizeof(stDrls.zjxym));
    /* 34.������Ӧ��Ϣ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zjxyxx", sBuf)
    pstrcopy(stDrls.zjxyxx, sBuf, sizeof(stDrls.zjxyxx));
    trim(stDrls.zjxyxx);
    /* 35.������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/sxf", sBuf)
    stDrls.sxf=atof(sBuf);
    /* 36.�ʻ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhye", sBuf)
    stDrls.zhye=atof(sBuf);
    /* 37.��Ӧ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/respcode", sBuf)
    pstrcopy(stDrls.xym, sBuf, sizeof(stDrls.xym));
    /* 38.��Ӧ��Ϣ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/respmsg", sBuf)
    pstrcopy(stDrls.xyxx, sBuf, sizeof(stDrls.xyxx));
    trim(stDrls.xyxx);
    /* 39.����״̬ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyzt", sBuf)
    pstrcopy(stDrls.jyzt, sBuf, sizeof(stDrls.jyzt));
    /* 40.���ʱ�־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dzbz", sBuf)
    pstrcopy(stDrls.dzbz, sBuf, sizeof(stDrls.dzbz));
    /* 41.�����־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/qsbz", sBuf)
    pstrcopy(stDrls.qsbz, sBuf, sizeof(stDrls.qsbz));
    /* 42.��չ��־ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/kzbz", sBuf)
    pstrcopy(stDrls.kzbz, sBuf, sizeof(stDrls.kzbz));
    /* 43.��˰�˱��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayCode", sBuf)
    pstrcopy(stDrls.taxpaycode, sBuf, sizeof(stDrls.taxpaycode));
    /* 43.��˰������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName", sBuf)
    pstrcopy(stDrls.taxpayname, sBuf, sizeof(stDrls.taxpayname));
    /* 44.˰Ʊ��Ϣ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/spxx", sBuf)
    pstrcopy(stDrls.spxx, sBuf, sizeof(stDrls.spxx));
    /* 45.�����ֶ� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/byzd", sBuf)
    pstrcopy(stDrls.byzd, sBuf, sizeof(stDrls.byzd));

		/* add dci 20141103 */
		
		memset( sSql1, 0x00, sizeof( sSql1 ) );
		    snprintf( sSql1, sizeof(sSql1), "zwrq ='%s' AND zhqzlsh =%d", stDrls.zwrq, stDrls.zhqzlsh); 
		LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))    
    iRet = DBUpdate("tips_drls", SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls, sSql1, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	fpub_SetMsg(lXmlhandle, 24113, "���µ�����ˮ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("UpdDRLS���µ�����ˮ��ʧ��"), 
            fpub_GetCompname(lXmlhandle))        
    }
    
    iRet =DCICommit();
    /* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),"ERROR");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"), 
            fpub_GetCompname(lXmlhandle))    
    }
    */
		/* end dci 20141103 */

		/* DCI MOD 20141103 
    EXEC SQL UPDATE tips_drls
         SET jyqd = :stDrls.jyqd,
             workdate = :stDrls.workdate,
             entrustdate = :stDrls.entrustdate,
             taxorgcode = :stDrls.taxorgcode,
             trano = :stDrls.trano,
             msgno = :stDrls.msgno,
             entrustdate2 = :stDrls.entrustdate2,
             trano2 = :stDrls.trano2,
             zhqzlsh2 = :stDrls.zhqzlsh2,
             chkdate = :stDrls.chkdate,
             chkacctord = :stDrls.chkacctord,                
             handletype = :stDrls.handletype,
             trecode = :stDrls.trecode,
             payeebankno = :stDrls.payeebankno,
             payeeorgcode = :stDrls.payeeorgcode,
             payeeacct = :stDrls.payeeacct,
             payeename = :stDrls.payeename,
             paybkcode = :stDrls.paybkcode,
             payopbkcode = :stDrls.payopbkcode,
             protocolno = :stDrls.protocolno,/* add by tuql 20091112 
             payacct = :stDrls.payacct,
             handorgname = :stDrls.handorgname,
             dfzh = :stDrls.dfzh,
             jyje = :stDrls.jyje,
             taxvouno = :stDrls.taxvouno,
             dqdh = :stDrls.dqdh,
             jgdh = :stDrls.jgdh,
             jygy = :stDrls.jygy,
             zddh = :stDrls.zddh,
             jyrq = :stDrls.jyrq,
             jysj = :stDrls.jysj,
             zjrq = :stDrls.zjrq,
             zjsj = :stDrls.zjsj,
             zjlsh = :stDrls.zjlsh,
             zjxym = :stDrls.zjxym,
             zjxyxx = :stDrls.zjxyxx,
             sxf = :stDrls.sxf,
             zhye = :stDrls.zhye,
             xym = :stDrls.xym,
             xyxx = :stDrls.xyxx,
             jyzt = :stDrls.jyzt,
             dzbz = :stDrls.dzbz,
             qsbz = :stDrls.qsbz,
             kzbz = :stDrls.kzbz,
             taxpaycode = :stDrls.taxpaycode,
             taxpayname = :stDrls.taxpayname,
             spxx = :stDrls.spxx
             /*byzd = :stDrls.byzd
         WHERE zwrq = :stDrls.zwrq
           AND zhqzlsh = :stDrls.zhqzlsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24113, "���µ�����ˮ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("UpdDRLS���µ�����ˮ��ʧ��"), 
            fpub_GetCompname(lXmlhandle))        
    }

    EXEC SQL COMMIT;  /*�����ύ*/
    /* fpub_SetMsg(lXmlhandle, 0, "���µ�����ˮ��ɹ�"); */
    /* END DCI MOD 20141103 */
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("���µ�����ˮ��ɹ�"), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitYHSBCX
�������: ��ʼ�������걨��ѯ������
�������: 
  ��ʼ�������걨��ѯ������
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
�����걨��ѯ��	tips_yhsbcx

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��24��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitYHSBCX(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 
         SDB_TIPS_YHSBCX stYhsbcx;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		SDB_TIPS_YHSBCX stYhsbcx;
		/* end add dci 20141103 */
            
    fpub_InitSoComp(lXmlhandle); 
    
    memset(&stYhsbcx, 0x00, sizeof(stYhsbcx));
    /* 1.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zwrq", sBuf)
    pstrcopy(stYhsbcx.zwrq, sBuf, sizeof(stYhsbcx.zwrq));
    /* 2.�ۺ�ǰ����ˮ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/zhqzlsh", sBuf)
    stYhsbcx.zhqzlsh=atoi(sBuf);
    
    LOG(LM_STD,Fmtmsg("��ʼ�������걨��ѯ������ ��������[%s],�ۺ�ǰ����ˮ��[%d]", 
        stYhsbcx.zwrq, stYhsbcx.zhqzlsh), fpub_GetCompname(lXmlhandle));
    
    /* 3.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jyqd", sBuf)
    pstrcopy(stYhsbcx.jyqd, sBuf, sizeof(stYhsbcx.jyqd));
    /* 4.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh", sBuf)
    pstrcopy(stYhsbcx.dqdh, sBuf, sizeof(stYhsbcx.dqdh));
    /* 5.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jgdh", sBuf)
    pstrcopy(stYhsbcx.jgdh, sBuf, sizeof(stYhsbcx.jgdh));
    /* 6.���׹�Ա */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy", sBuf)
    pstrcopy(stYhsbcx.jygy, sBuf, sizeof(stYhsbcx.jygy));
    /* 7.�ն˴��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh", sBuf)
    pstrcopy(stYhsbcx.zddh, sBuf, sizeof(stYhsbcx.zddh));
    /* 8.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/HEAD/WorkDate", sBuf)
    pstrcopy(stYhsbcx.workdate, sBuf, sizeof(stYhsbcx.workdate));
    /* 9.�������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stYhsbcx.jyrq, sBuf, sizeof(stYhsbcx.jyrq));
    /* 10.����ʱ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stYhsbcx.jysj, sBuf, sizeof(stYhsbcx.jysj));
    /* 11.��ҵ�����к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/BankNo", sBuf)
    pstrcopy(stYhsbcx.bankno, sBuf, sizeof(stYhsbcx.bankno));
    /* 12.ί������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/EntrustDate", sBuf)
    pstrcopy(stYhsbcx.entrustdate, sBuf, sizeof(stYhsbcx.entrustdate));
    /* 13.��ѯ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/QueryNo", sBuf)
    pstrcopy(stYhsbcx.queryno, sBuf, sizeof(stYhsbcx.queryno));
    /* 14.��������к� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/PayOpBkCode", sBuf)
    pstrcopy(stYhsbcx.payopbkcode, sBuf, sizeof(stYhsbcx.payopbkcode));
    /* 15.���������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/BankName", sBuf)
    pstrcopy(stYhsbcx.bankname, sBuf, sizeof(stYhsbcx.bankname));
    /* 16.���ջ��ش��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/TaxOrgCode", sBuf)
    pstrcopy(stYhsbcx.taxorgcode, sBuf, sizeof(stYhsbcx.taxorgcode));
    /* 17.��ҵ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/CorpCode", sBuf)
    pstrcopy(stYhsbcx.corpcode, sBuf, sizeof(stYhsbcx.corpcode));
    /* 18.��˰�˱��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/TaxPayCode", sBuf)
    pstrcopy(stYhsbcx.taxpaycode, sBuf, sizeof(stYhsbcx.taxpaycode));
    /* 19.�ⲿ�걨������� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/CFX/MSG/DeclareQuery2091/OuterLevyNo", sBuf)
    pstrcopy(stYhsbcx.outerlevyno, sBuf, sizeof(stYhsbcx.outerlevyno));
    /* 20.���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AddWord", sBuf)
    pstrcopy(stYhsbcx.addword, sBuf, sizeof(stYhsbcx.addword));
    /* 21.���׽�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jyje", sBuf)
    stYhsbcx.jyje=atof(sBuf);
    /* 23.������ϸ�� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/DetailNum", sBuf)
    stYhsbcx.detailnum = atoi(sBuf);
    /* 24.������ */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/Result", sBuf)
    pstrcopy(stYhsbcx.result, sBuf, sizeof(stYhsbcx.result));
    /* 25.˰Ʊ��Ϣ�ļ��� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/spxxwjm", sBuf)
    pstrcopy(stYhsbcx.spxxwjm, sBuf, sizeof(stYhsbcx.spxxwjm));
		      
		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_yhsbcx", SD_TIPS_YHSBCX, NUMELE(SD_TIPS_YHSBCX), &stYhsbcx, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	fpub_SetMsg(lXmlhandle, 24233, "��ʼ�������걨��ѯ������ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("��ʼ�������걨��ѯ������ʧ��"), fpub_GetCompname(lXmlhandle))      
    }
		/* end add dci 20141103 */
		
		/* dci mod 20141103 
    EXEC SQL INSERT INTO tips_yhsbcx  VALUES (:stYhsbcx);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24233, "��ʼ�������걨��ѯ������ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("��ʼ�������걨��ѯ������ʧ��"), fpub_GetCompname(lXmlhandle))      
    }	 
    */   

    fpub_SetMsg(lXmlhandle, 0, "��ʼ�������걨��ѯ�����ݳɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("��ʼ�������걨��ѯ�����ݳɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_GenSBCXHZ
�������: �����걨��ѯ��ִ
�������: 
  �����걨��ѯ��ִ
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����


�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��24��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_GenSBCXHZ(HXMLTREE lXmlhandle)
{
    int iParas;
    int iflag=0;
    int iCount=0;
    int smcount=0;
    char sBuf[256];/* ��ʱ���� */
    char sBuf2[256];
    char sBuf3[256];
    char szBuf[256];
    char sRoot[256];
    char sFileName[256];
    double dTaxAmt=0.00;
    double dTaxAmt2=0.00;
    FILE *fp;    
    int i;
    int iret=0;
    int j;

    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")  
    #endif
    
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 

    memset(sRoot,0,sizeof(sRoot));
    memset(sBuf,0,sizeof(sBuf));
    memset(sBuf2,0,sizeof(sBuf2));
    memset(sBuf3,0,sizeof(sBuf3));
    memset(szBuf,0,sizeof(szBuf));
    
    COMP_PARACOUNTCHK(1)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"�ļ���");
    pstrcopy(sFileName, sBuf, sizeof(sFileName));
    trim(sFileName);

    /*�½��ļ�*/
    fp=fopen(sFileName,"w");
    if ( fp == NULL )
    {
        fclose(fp);
        fpub_SetMsg(lXmlhandle, 24234, "�����걨��ѯ��ִ�ļ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�����걨��ѯ��ִ�ļ�ʧ��[%s]", strerror(errno)), 
            fpub_GetCompname(lXmlhandle))      
    }
    
    /*�����ļ�ͷ*/
    fprintf(fp,"                     ���ж��걨��ѯ��ִ\n\n");    
    /********************��ȡ�걨��ִ��������******************************/
    /*��ҵ�����к�*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/RealHead1009/BankNo",sBuf)
    trim(sBuf);
    /*ԭί������*/
    memset(sBuf2, 0x00, sizeof(sBuf2));
    COMP_SOFTGETXML("/tips/MSG/RealHead1009/OriEntrustDate",sBuf2)
    trim(sBuf2);
    /*ԭ��ѯ���*/
    memset(szBuf, 0x00, sizeof(szBuf));
    COMP_SOFTGETXML("/tips/MSG/RealHead1009/OriQueryNo",szBuf)
    trim(szBuf);
    fprintf(fp," ��ҵ�����к�: %-12.12s   ԭί������: %-8.8s  ԭ��ѯ���: %-8.8s \n",sBuf,sBuf2,szBuf);

    /*������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/RealHead1009/Result",sBuf)
    trim(sBuf);
    /*����*/
    memset(sBuf2, 0x00, sizeof(sBuf2));
    COMP_SOFTGETXML("/tips/MSG/RealHead1009/AddWord",sBuf2)
    trim(sBuf2);
    fprintf(fp,"     ������: %-5.5s          ����: %s \n",sBuf,sBuf2);

    /*���ջ��ش���*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/TaxOrgCode",sBuf)
    trim(sBuf);
    /*��ҵ����*/
    memset(sBuf2, 0x00, sizeof(sBuf2));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/CorpCode",sBuf2)
    trim(sBuf2);
    /*��˰�˱���*/
    memset(szBuf, 0x00, sizeof(szBuf));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/TaxPayCode",szBuf)
    trim(szBuf);
    fprintf(fp," ���ջ��ش���: %-12.12s   ��ҵ����: %-20.20s\n",sBuf,sBuf2);
    fprintf(fp,"   ��˰�˱���: %-20.20s \n\n",szBuf);

    /*�ⲿ�걨�������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/OuterLevyNo",sBuf)
    trim(sBuf);
    /*���׽��*/
    memset(sBuf2, 0x00, sizeof(sBuf2));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/TraAmt",sBuf2)
    dTaxAmt=atof(sBuf2);
    /*��ϸ����*/
    memset(szBuf, 0x00, sizeof(szBuf));
    COMP_SOFTGETXML("/tips/MSG/Payment1009/DetailNum",szBuf)
    iCount=atoi(szBuf);
    fprintf(fp," �ⲿ�걨�������: %-20.20s  ���׽��: %.2f  ��ϸ����: %s \n\n",sBuf,dTaxAmt,szBuf);
   
    /*ѭ��ȡ˰����ϸ��Ϣ*/
    for(i=1; i<=iCount; i++)
    {
        /*˰�ִ���*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxTypeCode",i);
        COMP_SOFTGETXML(sRoot,sBuf)
        trim(sBuf);
        /*˰������*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(sBuf2, 0x00, sizeof(sBuf2));
        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxTypeName",i);
        COMP_SOFTGETXML(sRoot,sBuf2)
        trim(sBuf2);
        /*˰����������*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(szBuf, 0x00, sizeof(szBuf));   	  
        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxType",i);
        COMP_SOFTGETXML(sRoot,szBuf)
        trim(szBuf);
        memset(sBuf3, 0x00, sizeof(sBuf3));
        if ( strcmp(szBuf,"1") == 0 )
          strcpy(sBuf3,"��������");
        else if ( strcmp(szBuf,"2") == 0 )
          strcpy(sBuf3,"����Ƿ˰");
        else if ( strcmp(szBuf,"3") == 0 )
          strcpy(sBuf3,"�������(ί�д��������ۡ�����)");
        else if ( strcmp(szBuf,"4") == 0 )
          strcpy(sBuf3,"��鲹˰");
        trim(sBuf3);  
        fprintf(fp," ˰�ִ���: %-10.10s  ˰������: %s  ˰����������: %s \n",sBuf,sBuf2,sBuf3);
        /*˰����ʼ����*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxStartDate",i);
        COMP_SOFTGETXML(sRoot,sBuf)
        trim(sBuf);
        /*˰����ֹ����*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(sBuf2, 0x00, sizeof(sBuf2));
        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxEndDate",i);
        COMP_SOFTGETXML(sRoot,sBuf2)
        trim(sBuf2);
        /*��ϸ����*/
        memset(sRoot, 0x00, sizeof(sRoot));
        memset(szBuf, 0x00, sizeof(szBuf));
        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/DetailNum",i);
        COMP_SOFTGETXML(sRoot,szBuf)
        smcount=atoi(szBuf);
        fprintf(fp," ˰����ʼ����: %-8.8s  ˰����ֹ����: %-8.8s ��ϸ����: %s\n",sBuf,sBuf2,szBuf);
   	  
        /*��ѭ��ȡ˰Ŀ��ϸ��Ϣ*/
        for(j=1; j<=smcount; j++)
        {
            /*˰Ŀ����*/
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxSubjectCode",i,j);
            COMP_SOFTGETXML(sRoot,sBuf)
            trim(sBuf);
            /*��˰����*/
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf2, 0x00, sizeof(sBuf2));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxNumber",i,j);
            COMP_SOFTGETXML(sRoot,sBuf2)
            trim(sBuf2);
            /*��˰���*/
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(sBuf3, 0x00, sizeof(sBuf3));
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxAmt",i,j);
            COMP_SOFTGETXML(sRoot,sBuf3)
            dTaxAmt=atof(sBuf3);
            /*ʵ��˰��*/
            memset(sRoot, 0x00, sizeof(sRoot));
            memset(szBuf, 0x00, sizeof(szBuf));            
            snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1009/TaxTypeList1009|%d/TaxSubjectList1009|%d/FactTaxAmt",i,j);
            COMP_SOFTGETXML(sRoot,szBuf)
            dTaxAmt2=atof(szBuf);
            fprintf(fp,"     ˰Ŀ����: %s    ��˰����: %s    ��˰���: %.2f  ʵ��˰��: %.2f \n\n",sBuf,sBuf2,dTaxAmt,dTaxAmt2);
        }
    }
    /*�ر��ļ�ָ��*/
    fclose(fp);

    fpub_SetMsg(lXmlhandle, 0, "�����걨��ѯ��ִ�ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�����걨��ѯ��ִ�ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_Cov1009TO2090
�������: ��ԭ˰Ʊ��Ϣ1009�ڵ�ת����2090�ڵ���
�������: 
  ��ԭ˰Ʊ��Ϣ1009�ڵ�ת����2090�ڵ���
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����


�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��02��24��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_Cov1009TO2090(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[256];
    char sTmpNode[255];
    char sNodeTmpRoot[56];
    char sNodeMXRoot[56];
    int i;
    int k;
    int ilen;
    int iflag1;
    int iflag2;
    double dSumFactTaxAmt=0.00;
    int iProjectNum=0;
    int iDetailNum=0;
    
    fpub_InitSoComp(lXmlhandle);

    /*��ȡ�������  --S*/
    COMP_PARACOUNTCHK(2)
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sNodeTmpRoot, 0x00, sizeof(sNodeTmpRoot));
    COMP_GETPARSEPARAS(1,sBuf,"1009��ϸ��Žڵ�"); 
    pstrcopy(sNodeTmpRoot, sBuf, sizeof(sNodeTmpRoot));
    trim(sNodeTmpRoot);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sNodeMXRoot, 0x00, sizeof(sNodeMXRoot));
    COMP_GETPARSEPARAS(2,sBuf,"2090��ϸ��Žڵ�");
    pstrcopy(sNodeMXRoot, sBuf, sizeof(sNodeMXRoot)); 
    trim(sNodeMXRoot);
    
    LOG(LM_STD,Fmtmsg("  -->��ԭ˰Ʊ��Ϣ1009�ڵ�ת����2090�ڵ���,1009��Žڵ�[%s],2090��Žڵ�[%d]",
        sNodeTmpRoot,sNodeMXRoot),fpub_GetCompname(lXmlhandle));   

    /*�����ϸ�ڵ����*/
    iProjectNum=0;
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTmpNode,0x00,sizeof(sTmpNode));
    snprintf(sTmpNode,sizeof(sTmpNode),"%s/DetailNum",sNodeTmpRoot);
    COMP_SOFTGETXML(sTmpNode,sBuf);
    iProjectNum = atoi(sBuf);
    
    LOG(LM_STD,Fmtmsg("  -->ȡ�ӽڵ�[%s]����[%d]",sTmpNode,iProjectNum),fpub_GetCompname(lXmlhandle));
    
    /*ѭ�����˰����ϸ*/
    for (i=1,iflag1=0;i<=iProjectNum;i++)
    {
        /*����ProjectId ��Ŀ���*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/ProjectId",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/ProjectId",sNodeMXRoot,i);     
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*����TaxTypeCode ˰�ִ���*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxTypeCode",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxTypeCode",sNodeMXRoot,i);     
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*����TaxStartDate ˰������������*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxStartDate",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxStartDate",sNodeMXRoot,i);     
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*����TaxEndDate ˰����������ֹ*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxEndDate",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxEndDate",sNodeMXRoot,i);     
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*����TaxType ˰������*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxType",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxType",sNodeMXRoot,i);     
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*��ȡDetailNum ��ϸ����*/
        iDetailNum=0;
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/DetailNum",sNodeTmpRoot,i);
        COMP_SOFTGETXML(sTmpNode,sBuf);
        iDetailNum = atoi(sBuf);
        /*ѭ������˰Ŀ��ϸ*/
        dSumFactTaxAmt = 0.00;
        for (k=1,iflag2=0;k<=iDetailNum;k++)
        {
            /*��ȡFactTaxAmt ʵ��˰��*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/FactTaxAmt",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            dSumFactTaxAmt = dSumFactTaxAmt + atof(sBuf);
        }
        /*����TaxTypeAmt ˰�ֽ��*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxTypeAmt",sNodeMXRoot,i);
        snprintf(sBuf, sizeof(sBuf), "%.2f", dSumFactTaxAmt);
        COMP_HARDSETXML(sTmpNode,sBuf); 
        
        /*����DetailNum ��ϸ����*/
        memset(sTmpNode,0x00,sizeof(sTmpNode));
        snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/DetailNum",sNodeMXRoot,i);     
        memset(sBuf, 0x00, sizeof(sBuf));
        snprintf(sBuf, sizeof(sBuf), "%d", iDetailNum);
        COMP_HARDSETXML(sTmpNode,sBuf); 
        /*ѭ������˰Ŀ��ϸ*/
        for (k=1,iflag2=0;k<=iDetailNum;k++)
        {
            /*����DetailNo ��ϸ���*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/DetailNo",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/DetailNo",sNodeMXRoot,i,k);     
            COMP_HARDSETXML(sTmpNode,sBuf);       
            /*����TaxSubjectCode ˰Ŀ����*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxSubjectCode",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxSubjectCode",sNodeMXRoot,i,k);     
            COMP_HARDSETXML(sTmpNode,sBuf);
            /*����TaxNumber ��˰����*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxNumber",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxNumber",sNodeMXRoot,i,k);     
            COMP_HARDSETXML(sTmpNode,sBuf);
            /*����TaxAmt ��˰���*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/TaxAmt",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxAmt",sNodeMXRoot,i,k);     
            COMP_HARDSETXML(sTmpNode,sBuf);
            /*����FactTaxAmt ʵ��˰��*/
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            memset(sBuf, 0x00, sizeof(sBuf));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList1009|%d/TaxSubjectList1009|%d/FactTaxAmt",sNodeTmpRoot,i,k);
            COMP_SOFTGETXML(sTmpNode,sBuf);
            memset(sTmpNode,0x00,sizeof(sTmpNode));
            snprintf(sTmpNode,sizeof(sTmpNode),"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/FactTaxAmt",sNodeMXRoot,i,k);     
            COMP_HARDSETXML(sTmpNode,sBuf);
        }               
    }    
    fpub_SetMsg(lXmlhandle, 0, "�����걨��ѯ��ִ�ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�����걨��ѯ��ִ�ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}
/************************************************************************
��̬�����������
�����������: SYW_TIPS_QrySFXY
�������: ��ѯ����Э��
�������: 
  ��ѯ����Э��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�	tips_wtgxdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��3��3��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_QrySFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sSql[512];
        char sProtocolNo[60+1];/* Э����� */
        char sTaxOrgCode[12+1];/* ���ջ��ش��� */
        char sTaxPayCode[20+1];/* ��˰�˱��� */
        char sPayAcct[32+1];/* �����˺� */
        char sPayBkCode[12+1];/* �������к� */
        char sHandOrgName[200+1];/* �ɿλ���� */
        char sGxdjrq[8+1];/* ��ϵ�Ǽ����� */
        char sYzbz[1+1];/* ��֤��־ */
        SDB_TIPS_WTGXDJ stWtgxdj;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    int iCount;
    int i, iflag;
    FILE *fp;
    char sFileName[256];
    char sSysDate[8+1];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		CURSOR cur;
		/* end add dci 20141103 */		
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(5);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "Э�����")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "���ջ��ش���")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
    COMP_GETPARSEPARAS(3, sBuf, "��˰�˱���")
    pstrcopy(sTaxPayCode, sBuf, sizeof(sTaxPayCode));
    trim(sTaxPayCode);    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(4, sBuf, "�����˺�")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct); 
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sFileName, 0x00, sizeof(sFileName));
    COMP_GETPARSEPARAS(5, sBuf, "�ļ�����")
    pstrcopy(sFileName, sBuf, sizeof(sFileName));
    trim(sFileName);

    LOG(LM_STD,Fmtmsg("��ѯ����Э�鿪ʼ����..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("Э�����[%s],���ջ��ش���[%s],��˰�˱���[%s],�����˺�[%s]", 
        sProtocolNo, sTaxOrgCode, sTaxPayCode, sPayAcct),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("�ļ�����[%s]", sFileName),fpub_GetCompname(lXmlhandle))

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sSysDate, 0x00, sizeof(sSysDate));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(sSysDate, sBuf, sizeof(sSysDate));

    fp = fopen(sFileName,"w");
    if ( fp == NULL )
    {
        fpub_SetMsg(lXmlhandle,24311,"���ļ�ʧ��");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ļ�ʧ��errinfo=[%s]",strerror(errno)),"ERROR");
    }   

    /*��ӡ�ļ�ͷ*/
    fprintf(fp,"                               TIPS����Э���ѯ\n");
    fprintf(fp,"                                                                                                ��ѯʱ�䣺%8.8s\n",sSysDate);
    
    fprintf(fp,"|����Э�����|���ջ��ش���| �������к� |     ��˰�˱���     |    �˻�����      |         �ͻ�����         |����ʱ��| ��֤��־ |\n");

 	iCount = 0;
 	memset(sSql, 0x00, sizeof(sSql));
 	snprintf(sSql, sizeof(sSql),"select protocolno,taxorgcode,paybkcode,taxpaycode,payacct,handorgname,gxdjrq,yzbz from tips_wtgxdj where 1=1");
 	if ( strlen(sProtocolNo) != 0 )
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," and protocolno='%s'",sProtocolNo);
 	if ( strlen(sTaxOrgCode) != 0 )
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," and taxorgcode='%s'",sTaxOrgCode);
 	if ( strlen(sTaxPayCode) != 0 )
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," and taxpaycode='%s'",sTaxPayCode);
 	if ( strlen(sPayAcct) != 0 )
 	    snprintf(sSql+strlen(sSql),sizeof(sSql)," and payacct='%s'",sPayAcct);
 	snprintf(sSql+strlen(sSql),sizeof(sSql)," order by protocolno ");
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
    memset(&stWtgxdj, 0x00, sizeof(stWtgxdj));
		iRet = DBFetch(cur, SD_TIPS_WTGXDJ,NUMELE(SD_TIPS_WTGXDJ),&stWtgxdj, sErrmsg );
    while( iRet > 0 )
    {
        iCount ++;
        memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
        memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
        memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
        memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
        memset(sPayAcct, 0x00, sizeof(sPayAcct));
        memset(sHandOrgName, 0x00, sizeof(sHandOrgName));
        memset(sGxdjrq, 0x00, sizeof(sGxdjrq));
        memset(sYzbz, 0x00, sizeof(sYzbz));
        
        pstrcopy(sProtocolNo,stWtgxdj.protocolno,sizeof(sProtocolNo));
        trim(sProtocolNo);
        pstrcopy(sTaxOrgCode,stWtgxdj.taxorgcode,sizeof(sTaxOrgCode));
        trim(sTaxOrgCode);
        pstrcopy(sPayBkCode,stWtgxdj.paybkcode,sizeof(sPayBkCode));
        trim(sPayBkCode);
        pstrcopy(sTaxPayCode,stWtgxdj.taxpaycode,sizeof(sTaxPayCode));
        trim(sTaxPayCode);
        pstrcopy(sPayAcct,stWtgxdj.payacct,sizeof(sPayAcct));
        trim(sPayAcct);
        pstrcopy(sHandOrgName,stWtgxdj.handorgname,sizeof(sHandOrgName));
        trim(sHandOrgName);
        pstrcopy(sGxdjrq,stWtgxdj.gxdjrq,sizeof(sGxdjrq));
        trim(sGxdjrq);
        pstrcopy(sYzbz,stWtgxdj.yzbz,sizeof(sYzbz));
        trim(sYzbz);
        
        memset(sBuf, 0x00, sizeof(sBuf));        
        if ( sYzbz[0]=='0' )
            strcpy(sBuf,"δ��֤"); 
        else if ( sYzbz[0]=='1' )
            strcpy(sBuf,"����֤ͨ��");
        else
            strcpy(sBuf,"������");
        
        fprintf(fp,"|%-12.12s|%-12.12s|%-12.12s|%-20.20s|%-18.18s|%-26.26s|%-8.8s|%-10.10s|\n",
            sProtocolNo,sTaxOrgCode,sPayBkCode,sTaxPayCode,sPayAcct,sHandOrgName,sGxdjrq,sBuf);  
            
        memset(&stWtgxdj, 0x00, sizeof(stWtgxdj));
				iRet = DBFetch(cur, SD_TIPS_WTGXDJ,NUMELE(SD_TIPS_WTGXDJ),&stWtgxdj, sErrmsg );                
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
            
	/* dci mod 20141103 
 	/*prepare*
    EXEC SQL PREPARE sql_qrysfxy FROM :sSql;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"sql_qrysfxy",sqlca.sqlcode),"ERROR");    
    /*declare*
    EXEC SQL DECLARE cur_wtgxdj_qry CURSOR for sql_qrysfxy;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_wtgxdj_qry",sqlca.sqlcode),"ERROR");

    EXEC SQL OPEN cur_wtgxdj_qry;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CUROPEN,"cur_wtgxdj_qry", sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
        fclose(fp);
        fpub_SetMsg(lXmlhandle,24312, "���α�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);        
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("QrySFXY��cur_wtgxdj_qry�α�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }

    /*��ʼѭ��*
    for (i=0,iflag=0;;i++)
    {
        memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
        memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
        memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
        memset(sTaxPayCode, 0x00, sizeof(sTaxPayCode));
        memset(sPayAcct, 0x00, sizeof(sPayAcct));
        memset(sHandOrgName, 0x00, sizeof(sHandOrgName));
        memset(sGxdjrq, 0x00, sizeof(sGxdjrq));
        memset(sYzbz, 0x00, sizeof(sYzbz));
        
        EXEC SQL FETCH cur_wtgxdj_qry INTO :sProtocolNo, :sTaxOrgCode, :sPayBkCode, :sTaxPayCode, :sPayAcct, :sHandOrgName, :sGxdjrq, :sYzbz;     
        SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_CURFETCH,"cur_wtgxdj_qry",sqlca.sqlcode),"ERROR");
        if ( SQLERR )
        {  
        	iflag=-1;
        	LOG(LM_STD,Fmtmsg("QrySFXY��cur_wtgxdj_qry�α��ȡ����ʧ��"),"ERROR");
        	break;
        }
        if ( SQLNOTFOUND )
          break;
          
        trim(sProtocolNo);
        trim(sTaxOrgCode);
        trim(sPayBkCode);
        trim(sTaxPayCode);
        trim(sPayAcct);
        trim(sHandOrgName);
        trim(sGxdjrq);
        trim(sYzbz);
        memset(sBuf, 0x00, sizeof(sBuf));        
        if ( sYzbz[0]=='0' )
            strcpy(sBuf,"δ��֤"); 
        else if ( sYzbz[0]=='1' )
            strcpy(sBuf,"����֤ͨ��");
        else
            strcpy(sBuf,"������");
        
        fprintf(fp,"|%-12.12s|%-12.12s|%-12.12s|%-20.20s|%-18.18s|%-26.26s|%-8.8s|%-10.10s|\n",
            sProtocolNo,sTaxOrgCode,sPayBkCode,sTaxPayCode,sPayAcct,sHandOrgName,sGxdjrq,sBuf);                  
     }     
    EXEC SQL CLOSE cur_wtgxdj_qry;    
    /* EXEC SQL FREE  cur_wtgxdj_qry; */
    fclose(fp); 
    
    if (iflag < 0)
    {
        fpub_SetMsg(lXmlhandle,24313,"���ɲ�ѯ����Э���ִ�ļ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ɲ�ѯ����Э���ִ�ļ�ʧ��iflag=[%d]",iflag),
            fpub_GetCompname(lXmlhandle))
    }
    
    if ( i == 0 )
    {
        fpub_SetMsg(lXmlhandle,24314,"�޷��鵽��ص�����Э����Ϣ");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL); 
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�޷��鵽��ص�����Э����Ϣ"),
            fpub_GetCompname(lXmlhandle))        
    }
    
    fpub_SetMsg(lXmlhandle, 0, "��ѯ����Э���ϵ�ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("��ѯ����Э���ϵ�ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_DelSFXY
�������: ��������Э��
�������: 
  ��������Э��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

�������裺
   ǰ��������������ɾ��ǰ����ɶ��˺�����������У��
        
        ɾ��
          ����Э����š���ѯ����Э������
             У������Э���ֶΣ����ջ��ش��š���˰���˺š�֧�����к��Ƿ��ǰ̨���͵�һ��
             ����Э�����ί�й�ϵ״̬-->1,���سɹ���

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�	tips_wtgxdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��3��3��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_DelSFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sProtocolNo[60+1];/* Э����� */
        char sTaxOrgCode[12+1];/* ���ջ��ش��� */
        char sPayAcct[32+1];/* �����˺� */
        SDB_TIPS_WTGXDJ stWtgxdj;
        SDB_TIPS_WTGXDJ stWtgxdj1;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "Э�����")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "���ջ��ش���")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "�����˺�")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);

    LOG(LM_STD,Fmtmsg("��������Э�鿪ʼ����..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("Э�����[%s],���ջ��ش���[%s],�����˺�[%s]", 
        sProtocolNo, sTaxOrgCode, sPayAcct),fpub_GetCompname(lXmlhandle))

		/*
    memset(&stWtgxdj, 0x00, sizeof(stWtgxdj));
    EXEC SQL SELECT * INTO :stWtgxdj
         FROM tips_wtgxdj
		     WHERE protocolno=:sProtocolNo
           AND taxorgcode=:sTaxOrgCode
           AND payacct=:sPayAcct;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "��ѯί�й�ϵ�Ǽ���Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�Ǽ���Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))
    }

    if ( SQLNOTFOUND_TIPS )
    {
        fpub_SetMsg(lXmlhandle, 24317, "ί�й�ϵδ����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ί�й�ϵδ����"),
            fpub_GetCompname(lXmlhandle))
    } 
    */
    /* add DCI 20141103 */
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    memset( sSql1, 0x00, sizeof( sSql1 ) );
    memset( &stWtgxdj, 0x00, sizeof( &stWtgxdj ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT PROTOCOLNO, TAXORGCODE, PAYBKCODE, PAYACCT, BANKPROTOCOLNO, TAXPAYCODE, \
    		PAYOPBKCODE, TAXPAYNAME, HANDORGNAME, KHH, WTGXZT, GXDJRQ, DJLSH, DJDQDH, DJJGDH, DJJYGY, DJZDDH, XGRQ, \
    		XGLSH, XGDQDH, XGJGDH, XGJYGY, XGZDDH, KZBZ, YZBZ, YZXGRQ, BYZD, OPBANKNO \
    		FROM  tips_wtgxdj WHERE \
    		protocolno='%s' AND taxorgcode='%s' AND payacct='%s'",sProtocolNo,sTaxOrgCode,sPayAcct);
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))  
    /*iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_WTGXDJ, NUMELE(SD_TIPS_WTGXDJ), &stWtgxdj);*/
         
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,stWtgxdj.protocolno,stWtgxdj.taxorgcode,\
    stWtgxdj.paybkcode,stWtgxdj.payacct,stWtgxdj.bankprotocolno,stWtgxdj.taxpaycode,stWtgxdj.payopbkcode,\
    stWtgxdj.taxpayname,stWtgxdj.handorgname,stWtgxdj.khh,stWtgxdj.wtgxzt,stWtgxdj.gxdjrq,stWtgxdj.djlsh,\
    stWtgxdj.djdqdh,stWtgxdj.djjgdh,stWtgxdj.djjygy,stWtgxdj.djzddh,stWtgxdj.xgrq,stWtgxdj.xglsh,\
    stWtgxdj.xgdqdh,stWtgxdj.xgjgdh,stWtgxdj.xgjygy,stWtgxdj.xgzddh,stWtgxdj.kzbz,stWtgxdj.yzbz,stWtgxdj.yzxgrq,\
    stWtgxdj.byzd,stWtgxdj.opbankno);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        
        fpub_SetMsg(lXmlhandle, 24316, "��ѯί�й�ϵ�Ǽ���Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�Ǽ���Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))
        
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24317, "ί�й�ϵδ����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ί�й�ϵδ����"),
            fpub_GetCompname(lXmlhandle))    
    }
    /* end add DCI 20141103 */   
    
    /*����֤��Э�鲻��ɾ��--BEGIN 20120804 wangw*/
    if ( strncmp(stWtgxdj.yzbz,"0",1) )   
    {
        fpub_SetMsg(lXmlhandle, 24320, "����֤��Э�鲻��ɾ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����֤��Э�鲻��ɾ��"),
            fpub_GetCompname(lXmlhandle))
    }
    /*����֤��Э�鲻��ɾ��--END 20120804 wangw*/
		
    /*�޸���ˮ�� */
    COMP_SOFTGETXML("/pub/zhqzlsh",stWtgxdj.xglsh);
    /*�޸����� */
    COMP_SOFTGETXML("/sys/sysdate",stWtgxdj.xgrq);
    /*�޸Ļ������� */
    COMP_SOFTGETXML("/pub/jgdh",stWtgxdj.xgjgdh);
    /*�޸ĵ������� */
    COMP_SOFTGETXML("/pub/dqdh",stWtgxdj.xgdqdh);
    /*�޸Ľ��׹�Ա */
    COMP_SOFTGETXML("/pub/jygy",stWtgxdj.xgjygy);
    
    /*�����¼����ʷί�й�ϵ�� */	
    /*	
    EXEC SQL INSERT INTO tips_wtgxdjlsls VALUES(:stWtgxdj); 
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24318, "������ʷί�м�¼ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("������ʷί�м�¼ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }*/
    /* add DCI 20141103 */
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_wtgxdjlsls", SD_TIPS_WTGXDJLSLS, NUMELE(SD_TIPS_WTGXDJLSLS), &stWtgxdj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	fpub_SetMsg(lXmlhandle, 24318, "������ʷί�м�¼ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("������ʷί�м�¼ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    /* end add DCI 20141103*/
    
    /* ɾ������Э�� */
    /* DCI MOD 20141103
    EXEC SQL delete FROM tips_wtgxdj 
         WHERE protocolno=:sProtocolNo
           AND taxorgcode=:sTaxOrgCode
           AND payacct=:sPayAcct;        
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24319, "ɾ������Э��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ������Э��ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }*/
    
    /* ADD DCI 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "delete FROM  tips_wtgxdj WHERE \
    		protocolno='%s' AND taxorgcode='%s' AND payacct='%s'",sProtocolNo,sTaxOrgCode,sPayAcct);
    iRet = DCIExecuteDirect(sSql1);
    if( iRet < 0 )
    {
    		fpub_SetMsg(lXmlhandle, 24319, "ɾ������Э��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ������Э��ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    
    fpub_SetMsg(lXmlhandle, 0, "ɾ������Э��ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("ɾ������Э��ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_AddSFXY
�������: ǩԼ����Э��
�������: 
  ǩԼ����Э��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

�������裺
   ǰ��������������ɾ��ǰ����ɶ��˺�����������У��
        1 ����
          ���ջ���У��
          ��ѯ���ջ��ء���˰���˺š�֧�����кż�¼�Ƿ���ڡ�
            ����->�ж�Э������Ƿ��ǰ̨���͵�һ�£�
                     һ�£��޸�ί�й�ϵ״̬->0�����سɹ�
                     ��һ��,����ʧ�ܣ����ջ��ء���˰���˺š�֧�����кŶ�Ӧ��ϵ�Ѵ��ڡ�                                                      
            �����ڣ�����
          ��ѯЭ����������ݿ����Ƿ��Ѵ��ڡ�
            ����->����ʧ��,Э�����Ӧ�����ջ��ء���˰���˺š�֧�����кż�¼������ 
            ������->��������Э�顣

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�	tips_wtgxdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��3��3��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_AddSFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sProtocolNo[60+1];/* Э����� */
        char sTaxOrgCode[12+1];/* ���ջ��ش��� */
        char sPayAcct[32+1];/* �����˺� */
        char sPayBkCode[12+1];/* �������к� */
        char sPayOpBkCode[12+1];/* ������к� */
        char sYzbz_tmp[1+1];
        SDB_TIPS_WTGXDJ stWtgxdj;
        SDB_TIPS_WTGXDJ stWtgxdj1;
        int iCount;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    char sZwrq[8+1];
    char sBankProNo[30];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */  
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(4);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "Э�����")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "���ջ��ش���")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "�����˺�")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(4, sBuf, "�������к�")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    LOG(LM_STD,Fmtmsg("ǩԼ����Э�鿪ʼ����..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("Э�����[%s],���ջ��ش���[%s],�����˺�[%s],�������к�[%s]", 
        sProtocolNo, sTaxOrgCode, sPayAcct, sPayBkCode),fpub_GetCompname(lXmlhandle))
				
    /* ��ѯ���ջ����Ƿ���� */
    /* mod DCI ע��20141103
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_taxcodeinfo  
	     WHERE taxorgcode=:sTaxOrgCode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24321, "��ѯ���ջ��ش���ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ���ջ��ش���ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24322, "���ջ��ش��벻����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ջ��ش��벻����"),
            fpub_GetCompname(lXmlhandle))        
    }*/
    /* add DCI 20141103 */
    
    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_taxcodeinfo WHERE taxorgcode='%s'",sTaxOrgCode);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24321, "��ѯ���ջ��ش���ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ���ջ��ش���ʧ��"),
            fpub_GetCompname(lXmlhandle))
        
    }
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24322, "���ջ��ش��벻����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ջ��ش��벻����"),
            fpub_GetCompname(lXmlhandle))        
    }
    /* end add DCI 20141103 */    

    /* ��ѯ�������к��Ƿ���� 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_qshdj  
	     WHERE paybkcode=:sPayBkCode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24323, "��ѯ��ҵ���������еǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ��ҵ���������еǼǱ�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24324, "�������к�δ��ʼ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�������к�δ��ʼ��"),
            fpub_GetCompname(lXmlhandle))        
    }*/
    /* add DCI 20141103 */
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT COUNT(*) FROM  tips_qshdj WHERE paybkcode='%s'",sPayBkCode);     	
    iRet = DBSelectToVar(sErrmsg, &iCount, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24323, "��ѯ��ҵ���������еǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ��ҵ���������еǼǱ�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24324, "�������к�δ��ʼ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�������к�δ��ʼ��"),
            fpub_GetCompname(lXmlhandle)) 
    }
    /* end add DCI 20141103 */ 

    /* ��ѯ�Ƿ���ǩԼ 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_wtgxdj  
	     WHERE taxorgcode=:sTaxOrgCode
	       AND paybkcode=:sPayBkCode
	       AND payacct=:sPayAcct;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "��ѯί�й�ϵ�Ǽ���Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�Ǽ���Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount != 0 )
    {
        fpub_SetMsg(lXmlhandle, 24325, "����Э���Ѵ���,ǩԼʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("3����Э���Ѵ���,ǩԼʧ��"),
            fpub_GetCompname(lXmlhandle))        
    }*/    

    /* ��ѯ�Ƿ���ǩԼ */
    /*iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_wtgxdj  
	     WHERE protocolno=:sProtocolNo;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "��ѯί�й�ϵ�Ǽ���Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�Ǽ���Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount > 0 )
    {
			  EXEC SQL SELECT yzbz INTO :sYzbz_tmp 
				     FROM  tips_wtgxdj  
				     WHERE protocolno=:sProtocolNo;
				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
				trim(sYzbz_tmp); 
		    if( strcmp(sYzbz_tmp,"2")==0 )
		    {
				    EXEC SQL delete FROM tips_wtgxdj 
				         WHERE protocolno=:sProtocolNo;        
				    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_DELETE,sqlca.sqlcode),"ERROR"); 
				    if ( SQLERR )
				    {
				        fpub_SetMsg(lXmlhandle, 24319, "ɾ������Э��ʧ��");
				        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ������Э��ʧ��"),
				            fpub_GetCompname(lXmlhandle))
				    }
		    }   
				else
				{
		        fpub_SetMsg(lXmlhandle, 24325, "����Э���Ѵ���,ǩԼʧ��");
		        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("1����Э���Ѵ���,ǩԼʧ��"),
		            fpub_GetCompname(lXmlhandle))        
				}
    }*/
    /* add DCI 20141103 */
    iCount = 0 ;
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT count(*) FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);     	
    iRet = DBSelectToVar( sErrmsg, &iCount, sSql1) ; 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24316, "��ѯί�й�ϵ�Ǽ���Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�Ǽ���Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    if ( iCount > 0 )
    {
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "SELECT yzbz FROM  tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);     	
    		iRet = DBSelectToVar( sErrmsg, &sYzbz_tmp, sSql1) ;    		 
        trim(sYzbz_tmp); 
		    if( strcmp(sYzbz_tmp,"2")==0 )
        {
        	memset( sSql1, 0x00, sizeof( sSql1 ) );
        	snprintf( sSql1, sizeof(sSql1), "delete FROM tips_wtgxdj WHERE protocolno='%s'",sProtocolNo);
        	iRet = DCIExecuteDirect(sSql1);
	     		if ( iRet < 0 )
	     		{
	     			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        		
	     			fpub_SetMsg(lXmlhandle, 24319, "ɾ������Э��ʧ��");
				    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				    LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("ɾ������Э��ʧ��"),
				            fpub_GetCompname(lXmlhandle))
	     		}
	     	}
	     	else
				{
		        fpub_SetMsg(lXmlhandle, 24325, "����Э���Ѵ���,ǩԼʧ��");
		        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э���Ѵ���,ǩԼʧ��"),
		            fpub_GetCompname(lXmlhandle))        
				}     	
    }
    /* end add DCI 20141103 */ 

    /*Э�����δ��ʹ��,��ʼ��������Э��*/     
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));     
    COMP_SOFTGETXML("/tips/zwrq",sBuf);
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    /* ��������Э������� */
    iRet = 0;
    memset(sBankProNo,0x00,sizeof(sBankProNo));
    iRet = prv_tips_genxh2(1,sBuf,sBankProNo);
    if (iRet < 0)
    {
        fpub_SetMsg(lXmlhandle, 24326, "���������ڲ�Э���ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���������ڲ�Э���ʧ��"),
            fpub_GetCompname(lXmlhandle)) 
    }
    trim(sBankProNo);
		COMP_SOFTSETXML("/tips/BANKProtocolNo",sBankProNo)
		
    memset(&stWtgxdj,0,sizeof(stWtgxdj));
      
    /*����Э�����*/
    pstrcopy(stWtgxdj.bankprotocolno,sBankProNo,sizeof(stWtgxdj.bankprotocolno));
    /*ί�й�ϵ״̬*/ 
    stWtgxdj.wtgxzt[0]='0';
    /*Э�����*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/ProtocolNo",sBuf)
    pstrcopy(stWtgxdj.protocolno, sBuf, sizeof(stWtgxdj.protocolno));
    if(strlen(stWtgxdj.protocolno)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "Э�����Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("Э�����Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*���ջ��ش���*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxOrgCode",sBuf)
    pstrcopy(stWtgxdj.taxorgcode, sBuf, sizeof(stWtgxdj.taxorgcode));
    if(strlen(stWtgxdj.taxorgcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "���ջ��ش���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ջ��ش���Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*��˰�˱���*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/TaxPayCode",sBuf)
    pstrcopy(stWtgxdj.taxpaycode, sBuf, sizeof(stWtgxdj.taxpaycode));
    if(strlen(stWtgxdj.taxpaycode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "��˰�˱���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��˰�˱���Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*��˰������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName",sBuf)
    pstrcopy(stWtgxdj.taxpayname, sBuf, sizeof(stWtgxdj.taxpayname));
     if(strlen(stWtgxdj.taxpayname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "��˰������Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��˰������Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
   /*�ɿλ����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jkdwmc",sBuf)
    pstrcopy(stWtgxdj.handorgname, sBuf, sizeof(stWtgxdj.handorgname));
     if(strlen(stWtgxdj.handorgname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�ɿλ����Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�ɿλ����Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
   /* �������к�*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayBkCode",sBuf)
    pstrcopy(stWtgxdj.paybkcode, sBuf, sizeof(stWtgxdj.paybkcode));
     if(strlen(stWtgxdj.paybkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�������к�Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�������к�Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
   /* �����ʻ�*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/PayAcct",sBuf)
    pstrcopy(stWtgxdj.payacct, sBuf, sizeof(stWtgxdj.payacct));
    if(strlen(stWtgxdj.payacct)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�����ʻ�Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����ʻ�Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*�ͻ�����*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/khh",sBuf)
    pstrcopy(stWtgxdj.khh, sBuf, sizeof(stWtgxdj.khh));
    /*��ϵ�Ǽ�����*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/gxdjrq",sBuf)		/* 20150803 /tips/zwrq �޸�Ϊ/tips/gxdjrq */
    pstrcopy(stWtgxdj.gxdjrq, sBuf, sizeof(stWtgxdj.gxdjrq));
    
    /*�Ǽ���ˮ��*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/zhqzlsh",sBuf)
    pstrcopy(stWtgxdj.djlsh, sBuf, sizeof(stWtgxdj.djlsh));
    /*��������*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/jgdh",sBuf)
    pstrcopy(stWtgxdj.djjgdh, sBuf, sizeof(stWtgxdj.djjgdh));
    /*��������*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh",sBuf)
    pstrcopy(stWtgxdj.djdqdh, sBuf, sizeof(stWtgxdj.djdqdh));
    /*���׹�Ա*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy",sBuf)
    pstrcopy(stWtgxdj.djjygy, sBuf, sizeof(stWtgxdj.djjygy));
    /*�ն˴���*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh",sBuf)
    pstrcopy(stWtgxdj.djzddh, sBuf, sizeof(stWtgxdj.djzddh));
    /*��չ��־*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/resp/zhlx", sBuf)/* �ʻ����� */  
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[0]=sBuf[0];
    }else
        stWtgxdj.kzbz[0]='0'; 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/chbz", sBuf)/* �����־ */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[1]=sBuf[0];
    }else
        stWtgxdj.kzbz[1]='0';
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/kzbz", sBuf)/* ���۱�־ P���˻� C���� Ĭ�����˻�P add 20140901 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[2]=sBuf[0];
    }else
        stWtgxdj.kzbz[2]='P'; 
    strcat(stWtgxdj.kzbz, "00000");
    LOG(LM_STD,Fmtmsg("Э�����[%s],���ջ��ش���[%s],�����˺�[%s],kzbz[%s]", 
        sProtocolNo, sTaxOrgCode, sPayAcct, stWtgxdj.kzbz),fpub_GetCompname(lXmlhandle))    

    /*��֤��־*/
    stWtgxdj.yzbz[0]='0';
    /*�ͻ���*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/khh",sBuf);
    pstrcopy(stWtgxdj.khh,sBuf,sizeof(stWtgxdj.khh)); 
    /*������л�����--20120829 wangw*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.opbankno,sBuf,sizeof(stWtgxdj.opbankno)); 
    /*��ע--�����л����� ����̨��ѯЭ���� add 20150710 */
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));
    /*��ע--����������
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips_host/resp/khhmc",sBuf)
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));*/
    
    /*��������к�*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhhh",sBuf);
    pstrcopy(stWtgxdj.payopbkcode,sBuf,sizeof(stWtgxdj.payopbkcode));
    
    /*������ʶ
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/czbz", sBuf)/* ������ʶ 
    pstrcopy(stWtgxdj.czbz,sBuf,sizeof(stWtgxdj.czbz));
    
    EXEC SQL INSERT INTO tips_wtgxdjlsls VALUES(:stWtgxdj); 
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24318, "������ʷί�м�¼ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("������ʷί�м�¼ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }*/ 
        
    /*��������Э��*/
    /* mod dci 20141103 
    EXEC SQL INSERT INTO tips_wtgxdj VALUES(:stWtgxdj);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");     
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24327, "��������Э��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������Э��ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_wtgxdj", SD_TIPS_WTGXDJ, NUMELE(SD_TIPS_WTGXDJ), &stWtgxdj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
    	fpub_SetMsg(lXmlhandle, 24327, "��������Э��ʧ��");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������Э��ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    
    fpub_SetMsg(lXmlhandle, 0, "ǩԼ����Э��ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("ǩԼ����Э��ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}
/************************************************************************
��̬�����������
�����������: SYW_TIPS_InitPZSJ_DB
�������: �Ǽ�ƾ֤������Ϣ(����)
�������: 
  �Ǽ�ƾ֤������Ϣ(����)
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

�������裺


������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�	tips_drls

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: TUQL
��������: 2009��3��10��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_InitPZSJ_DB(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        SDB_TIPS_DRLS stDrls;
        SDB_TIPS_TAXTYPEMX stTaxtypemx;
        char sZwrq[8+1];/* �������� */
        int iZhqzlsh;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    char sRoot[256];
    int  iCount=0,i;
    char sXmlNodePath[200];
    char sTaxInfoPath[200];
    char sPayment3102[10240];
    int iret;
    FILE *fp;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		
		char sProtocolno[61];
		char sSpxx[41];
		
		/* end add dci 20141103 */
            
    fpub_InitSoComp(lXmlhandle);   

    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "��������")
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    iZhqzlsh=0;
    COMP_GETPARSEPARAS(2, sBuf, "�ۺ�ǰ����ˮ��")
    iZhqzlsh = atoi(sBuf);

    LOG(LM_STD,Fmtmsg("�Ǽ�ƾ֤������Ϣ(����)��ʼ����..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("��������[%s],�ۺ�ǰ����ˮ��[%d]", 
        sZwrq, iZhqzlsh),fpub_GetCompname(lXmlhandle))

		/* add dci 20141103 */
		iRet = DCIBegin();
		if( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
		
		memset( sSql1, 0x00, sizeof( sSql1 ) );
		memset( &stDrls, 0x00, sizeof( &stDrls ) );
		snprintf( sSql1, sizeof(sSql1), "select * from tips_drls where zwrq='%s' and zhqzlsh=%d",sZwrq,iZhqzlsh); 
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))    
    /*iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls);*/
       
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,
&stDrls.zwrq         ,
&stDrls.zhqzlsh      ,
&stDrls.jyqd         ,
&stDrls.workdate     ,
&stDrls.entrustdate  ,
&stDrls.taxorgcode   ,
&stDrls.trano        ,
&stDrls.msgno        ,
&stDrls.entrustdate2 ,
&stDrls.trano2       ,
&stDrls.zhqzlsh2     ,
&stDrls.chkdate      ,
&stDrls.chkacctord   ,
&stDrls.handletype   ,
&stDrls.trecode      ,
&stDrls.payeebankno  ,
&stDrls.payeeorgcode ,
&stDrls.payeeacct    ,
&stDrls.payeename    ,
&stDrls.paybkcode    ,
&stDrls.payopbkcode  ,
&stDrls.protocolno   ,
&stDrls.payacct      ,
&stDrls.handorgname  ,
&stDrls.dfzh         ,
&stDrls.jyje         ,
&stDrls.taxvouno     ,
&stDrls.dqdh         ,
&stDrls.jgdh         ,
&stDrls.jygy         ,
&stDrls.zddh         ,
&stDrls.jyrq         ,
&stDrls.jysj         ,
&stDrls.zjrq         ,
&stDrls.zjsj         ,
&stDrls.zjlsh        ,
&stDrls.zjxym        ,
&stDrls.zjxyxx       ,
&stDrls.sxf          ,
&stDrls.zhye         ,
&stDrls.xym          ,
&stDrls.xyxx         ,
&stDrls.jyzt         ,
&stDrls.dzbz         ,
&stDrls.qsbz         ,
&stDrls.kzbz         ,
&stDrls.taxpaycode   ,
&stDrls.taxpayname   ,
&stDrls.spxx         ,
&stDrls.byzd          );
        
    LOG(LM_STD,Fmtmsg("ZWRQ         [%s]",stDrls.zwrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHQZLSH      [%d]",stDrls.zhqzlsh     ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYQD         [%s]",stDrls.jyqd        ),"INFO") 
    LOG(LM_STD,Fmtmsg("WORKDATE     [%s]",stDrls.workdate    ),"INFO") 
    LOG(LM_STD,Fmtmsg("ENTRUSTDATE  [%s]",stDrls.entrustdate ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXORGCODE   [%s]",stDrls.taxorgcode  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TRANO        [%s]",stDrls.trano       ),"INFO") 
    LOG(LM_STD,Fmtmsg("MSGNO        [%s]",stDrls.msgno       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ENTRUSTDATE2 [%s]",stDrls.entrustdate2),"INFO") 
    LOG(LM_STD,Fmtmsg("TRANO2       [%s]",stDrls.trano2      ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHQZLSH2     [%d]",stDrls.zhqzlsh2    ),"INFO") 
    LOG(LM_STD,Fmtmsg("CHKDATE      [%s]",stDrls.chkdate     ),"INFO") 
    LOG(LM_STD,Fmtmsg("CHKACCTORD   [%s]",stDrls.chkacctord  ),"INFO") 
    LOG(LM_STD,Fmtmsg("HANDLETYPE   [%s]",stDrls.handletype  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TRECODE      [%s]",stDrls.trecode     ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEBANKNO  [%s]",stDrls.payeebankno ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEORGCODE [%s]",stDrls.payeeorgcode),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEEACCT    [%s]",stDrls.payeeacct   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYEENAME    [%s]",stDrls.payeename   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYBKCODE    [%s]",stDrls.paybkcode   ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYOPBKCODE  [%s]",stDrls.payopbkcode ),"INFO") 
    LOG(LM_STD,Fmtmsg("PROTOCOLNO   [%s]",stDrls.protocolno  ),"INFO") 
    LOG(LM_STD,Fmtmsg("PAYACCT      [%s]",stDrls.payacct     ),"INFO") 
    LOG(LM_STD,Fmtmsg("HANDORGNAME  [%s]",stDrls.handorgname ),"INFO") 
    LOG(LM_STD,Fmtmsg("DFZH         [%s]",stDrls.dfzh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYJE         [%f]",stDrls.jyje        ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXVOUNO     [%s]",stDrls.taxvouno    ),"INFO") 
    LOG(LM_STD,Fmtmsg("DQDH         [%s]",stDrls.dqdh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JGDH         [%s]",stDrls.jgdh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYGY         [%s]",stDrls.jygy        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZDDH         [%s]",stDrls.zddh        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYRQ         [%s]",stDrls.jyrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYSJ         [%s]",stDrls.jysj        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJRQ         [%s]",stDrls.zjrq        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJSJ         [%s]",stDrls.zjsj        ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJLSH        [%s]",stDrls.zjlsh       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJXYM        [%s]",stDrls.zjxym       ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZJXYXX       [%s]",stDrls.zjxyxx      ),"INFO") 
    LOG(LM_STD,Fmtmsg("SXF          [%f]",stDrls.sxf         ),"INFO") 
    LOG(LM_STD,Fmtmsg("ZHYE         [%f]",stDrls.zhye        ),"INFO") 
    LOG(LM_STD,Fmtmsg("XYM          [%s]",stDrls.xym         ),"INFO") 
    LOG(LM_STD,Fmtmsg("XYXX         [%s]",stDrls.xyxx        ),"INFO") 
    LOG(LM_STD,Fmtmsg("JYZT         [%s]",stDrls.jyzt        ),"INFO") 
    LOG(LM_STD,Fmtmsg("DZBZ         [%s]",stDrls.dzbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("QSBZ         [%s]",stDrls.qsbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("KZBZ         [%s]",stDrls.kzbz        ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXPAYCODE   [%s]",stDrls.taxpaycode  ),"INFO") 
    LOG(LM_STD,Fmtmsg("TAXPAYNAME   [%s]",stDrls.taxpayname  ),"INFO") 
    LOG(LM_STD,Fmtmsg("SPXX         [%s]",stDrls.spxx        ),"INFO") 
    LOG(LM_STD,Fmtmsg("BYZD         [%s]",stDrls.byzd        ),"INFO") 
    
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24201, "��ѯ������ˮ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ������ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
		/* end add dci */
		
		/* dci mod 20141103 
    memset(&stDrls, 0x00, sizeof(stDrls));    
    EXEC SQL SELECT * INTO :stDrls
        FROM tips_drls
        WHERE  zwrq = :sZwrq
          AND  zhqzlsh = :iZhqzlsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24201, "��ѯ������ˮ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��ѯ������ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    */
    
    /* ˰Ʊ��Ϣ */
    memset(sPayment3102, 0x00, sizeof(sPayment3102));
    memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));
    /* mod by tuql 20090505 ��֧�ֵ�һ��3001�޸�Ϊ֧��3001��1008 */
    if (strcmp(stDrls.msgno, "3001") == 0)
    {
        strcpy(sXmlNodePath,"/tips/MSG/Payment3001");   
    
        if ( (iret=xml_ExportXMLString(lXmlhandle,sPayment3102,sizeof(sPayment3102),sXmlNodePath,1 )) == -1 )
        {
             fpub_SetMsg(lXmlhandle, 24211, "��ȡ˰Ʊ��Ϣʧ��");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("��ȡ˰Ʊ��Ϣʧ��[%s]", sXmlNodePath), fpub_GetCompname(lXmlhandle))	
             return COMPRET_FAIL ;        
        }
        /* ��˰Ʊ��Ϣ��ŵ��ļ���ȥ */
        memset(sXmlNodePath, 0x00, sizeof(sXmlNodePath));/* ��ŵ��ļ��� */
        snprintf(sXmlNodePath, sizeof(sXmlNodePath), "spxx_%s_%d",sZwrq, iZhqzlsh);
        trim(sXmlNodePath);
        snprintf(sTaxInfoPath, sizeof(sTaxInfoPath), "%s/file/tips/spxx/%s", getenv("HOME"), sXmlNodePath);
        fp = fopen(sTaxInfoPath, "w+");
        if ( fp==NULL )
        {
             fpub_SetMsg(lXmlhandle, 24212, "��˰Ʊ��Ϣ�ļ�ʧ��");
             fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
             LOG(LM_STD, Fmtmsg("��˰Ʊ��Ϣ�ļ�ʧ��"), fpub_GetCompname(lXmlhandle))	
             return COMPRET_FAIL ;        
        }
        fprintf(fp, "%s\n", sPayment3102); 
        fclose(fp);
        
        pstrcopy(stDrls.spxx, sXmlNodePath, sizeof(stDrls.spxx));        
        COMP_SOFTSETXML("/tips/spxx", sXmlNodePath)

		    /*��ϸ����*/
		    memset(sBuf, 0x00, sizeof(sBuf));
		    COMP_SOFTGETXML("/tips/MSG/Payment3001/TaxTypeNum",sBuf)
		    iCount=atoi(sBuf);
		   
		    /*ѭ��ȡ˰����ϸ��Ϣ*/
		    for(i=1; i<=iCount; i++)
		    {
		    	  
		        memset(&stTaxtypemx, 0x00, sizeof(stTaxtypemx));
    				pstrcopy(stTaxtypemx.jyrq, stDrls.zwrq, sizeof(stTaxtypemx.jyrq));
    				pstrcopy(stTaxtypemx.jylsh, stDrls.trano, sizeof(stTaxtypemx.jylsh));
    				pstrcopy(stTaxtypemx.spxx, stDrls.spxx, sizeof(stTaxtypemx.spxx));
    				LOG(LM_STD,Fmtmsg("jyrq[%s]",stTaxtypemx.jyrq),fpub_GetCompname(lXmlhandle))
    				LOG(LM_STD,Fmtmsg("jylsh[%s]",stTaxtypemx.jylsh),fpub_GetCompname(lXmlhandle))

		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment3001/TaxTypeList3001|%d/ProjectId",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.projectid, sBuf, sizeof(stTaxtypemx.projectid));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxTypeName",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxtypename, sBuf, sizeof(stTaxtypemx.taxtypename));

		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));   	  
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxStartDate",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxstartdate, sBuf, sizeof(stTaxtypemx.taxstartdate));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxEndDate",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxenddate, sBuf, sizeof(stTaxtypemx.taxenddate));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment3001/TaxTypeList3001|%d/TaxTypeAmt",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxtypeamt, sBuf, sizeof(stTaxtypemx.taxtypeamt));
						
						LOG(LM_STD,Fmtmsg("i[%d],jyrq[%s],jylsh[%s],projectid[%s]",i,stTaxtypemx.jyrq,stTaxtypemx.jylsh,stTaxtypemx.projectid),"INFO") 
						/* add dci 20141103 */
						memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_taxtypemx", SD_TIPS_TAXTYPEMX, NUMELE(SD_TIPS_TAXTYPEMX), &stTaxtypemx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					fpub_SetMsg(lXmlhandle, 24327, "����˰����ϸ��ʧ��");
      				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����˰����ϸ��ʧ��"),
            		fpub_GetCompname(lXmlhandle))
    				}
						/* end dci 20141103*/
						
						/* mod dci 20141103
						EXEC SQL INSERT INTO TIPS_TAXTYPEMX	VALUES(:stTaxtypemx);
				    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR"); 
				    if ( SQLERR )
				    {
				         fpub_SetMsg(lXmlhandle, 24201, "����˰����ϸ��ʧ��");
				         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				         LOG(LM_STD, Fmtmsg("����˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))	
				         return COMPRET_FAIL ;        
				    }
				    */
				                
		    }
		    
		    /* add dci 20141103 ֻ��3001������Ҫ����tips_drls��spxx 20141204�޸� 
		    1008�ı����걨ʱ���Ѿ�����˰Ʊ��д��tips_drls��spxx
		    */      
    		memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "update tips_drls set spxx ='%s' where zwrq='%s' and zhqzlsh=%d",stDrls.spxx,sZwrq,iZhqzlsh);     	
    		LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))       
    		iRet = DCIExecuteDirect(sSql1);	 
    		if ( iRet < 0 )
    		{
        	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        	fpub_SetMsg(lXmlhandle, 24201, "���µ�����ˮ��ʧ��");
         	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         	LOG(LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         	return COMPRET_FAIL ;        
    		}
    		/* end add dci 20141103 */
		    
    }else if (strcmp(stDrls.msgno, "1008") == 0)
    {
        strcpy(sXmlNodePath,"/tips/MSG/Payment1008");  
        
		    /*��ϸ����*/
		    memset(sBuf, 0x00, sizeof(sBuf));
		    COMP_SOFTGETXML("/tips/MSG/Payment1008/TaxTypeNum",sBuf)
		    iCount=atoi(sBuf);
		   
		    /*ѭ��ȡ˰����ϸ��Ϣ*/
		    for(i=1; i<=iCount; i++)
		    {
						LOG(LM_STD,Fmtmsg("����˰����ϸ��ʼ..."),fpub_GetCompname(lXmlhandle))
		        memset(&stTaxtypemx, 0x00, sizeof(stTaxtypemx));
    				pstrcopy(stTaxtypemx.jyrq, stDrls.zwrq, sizeof(stTaxtypemx.jyrq));
    				pstrcopy(stTaxtypemx.jylsh, stDrls.trano, sizeof(stTaxtypemx.jylsh));
    				pstrcopy(stTaxtypemx.spxx, stDrls.spxx, sizeof(stTaxtypemx.spxx));

		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot, sizeof(sRoot), "/tips/MSG/Payment1008/TaxTypeList1008|%d/ProjectId",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.projectid, sBuf, sizeof(stTaxtypemx.projectid));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxTypeName",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxtypename, sBuf, sizeof(stTaxtypemx.taxtypename));

		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));   	  
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxStartDate",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxstartdate, sBuf, sizeof(stTaxtypemx.taxstartdate));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxEndDate",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxenddate, sBuf, sizeof(stTaxtypemx.taxenddate));
		        
		        memset(sRoot, 0x00, sizeof(sRoot));
		        memset(sBuf, 0x00, sizeof(sBuf));
		        snprintf(sRoot,sizeof(sRoot),"/tips/MSG/Payment1008/TaxTypeList1008|%d/TaxTypeAmt",i);
		        COMP_SOFTGETXML(sRoot,sBuf)
		        trim(sBuf);
    				pstrcopy(stTaxtypemx.taxtypeamt, sBuf, sizeof(stTaxtypemx.taxtypeamt));

						LOG(LM_STD,Fmtmsg("����˰����ϸ��ʼ..."),fpub_GetCompname(lXmlhandle))
						
						/* add dci 20141103 */
						memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_taxtypemx", SD_TIPS_TAXTYPEMX, NUMELE(SD_TIPS_TAXTYPEMX), &stTaxtypemx, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    					
    					fpub_SetMsg(lXmlhandle, 24327, "����˰����ϸ��ʧ��");
      				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      				LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����˰����ϸ��ʧ��"),
            		fpub_GetCompname(lXmlhandle))
    				}
						/* end dci 20141103*/
						
						/* dci mod 20141103
				    EXEC SQL INSERT INTO TIPS_TAXTYPEMX	VALUES(:stTaxtypemx);
				    LOG(LM_STD,Fmtmsg("����˰����ϸ��ʼ...111"),fpub_GetCompname(lXmlhandle))
				    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR"); 
				    if ( SQLERR )
				    {
				         fpub_SetMsg(lXmlhandle, 24201, "����˰����ϸ��ʧ��");
				         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				         LOG(LM_STD, Fmtmsg("����˰����ϸ��ʧ��"), fpub_GetCompname(lXmlhandle))	
				         return COMPRET_FAIL ;        
				    }   
				    */         
		    }

    }else
    {
         fpub_SetMsg(lXmlhandle, 24211, Fmtmsg("��֧�ִ˱��ı��[%s]��ʵʱƾ֤", stDrls.msgno));
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("��֧�ִ˱��ı��[%s]��ʵʱƾ֤", stDrls.msgno), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }            
    
    /* ���뵥��ƾ֤���� */
    LOG(LM_STD,Fmtmsg("����ƾ֤���ݿ�ʼ"),fpub_GetCompname(lXmlhandle))       
    iret = prv_tips_InitPZSJ_db(lXmlhandle, stDrls);
    if ( iret < 0 )
    {
         fpub_SetMsg(lXmlhandle, 24213, "����ƾ֤��Ϣʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("����ƾ֤��Ϣʧ��[%d]", iret), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    LOG(LM_STD,Fmtmsg("����ƾ֤���ݽ���"),fpub_GetCompname(lXmlhandle))  
            
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_drls \
    		set spxx ='%s' where zwrq='%s' and zhqzlsh=%d",stDrls.spxx,sZwrq,iZhqzlsh);
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")            	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24201, "���µ�����ˮ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }
    
    iRet =DCICommit();
    /* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      LOG(LM_STD,Fmtmsg("���µ�����ˮ��ʧ��"),"ERROR");
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"), 
            fpub_GetCompname(lXmlhandle))    
    }
    */
    
    /* end dci */
    
    /* dci mod 20141103
    EXEC SQL UPDATE tips_drls
        SET spxx=:stDrls.spxx
        WHERE  zwrq = :sZwrq
          AND  zhqzlsh = :iZhqzlsh;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24201, "���µ�����ˮ��ʧ��");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOG(LM_STD, Fmtmsg("���µ�����ˮ��ʧ��"), fpub_GetCompname(lXmlhandle))	
         return COMPRET_FAIL ;        
    }         
    */
       
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�Ǽ�ƾ֤������Ϣ(����)�������"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;       
}


/************************************************************************
��̬�����������
�����������: SYW_TIPS_Init2090FromSblr
�������: �����걨¼����������2090׼������
�������: 
   
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��־��Ϣ: 
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ
  
��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: ���ڡ���Ʒ����
�� �� Ա: xiahl
��������: 2005-10-24 20:13
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_Init2090FromSblr(HXMLTREE lXmlhandle)
{
   char sbuf[255],snode_dataroot[255],snode_mxroot[50],sbuf2[255];
   char stmpnode[255];
   int ilen,iParas,iProjectNum=0,iDetailNum=0;
   int i,k,iflag1,iflag2;
   double dSumFactTaxAmt=0.00,tmpAmt=0.00;
   
   fpub_InitSoComp(lXmlhandle);
   
#ifdef DEBUG
   LOG(LM_STD,Fmtmsg("  �����걨¼����������2090׼�����ݿ�ʼ-->"),"INFO");
#endif

   /*��ȡ�������  --S*/
   COMP_PARACOUNTCHK(3)
   
   /*XMLԴֵ*/
   COMP_GETPARSEPARAS(1,snode_dataroot,"��ϸ¼���Ÿ��ڵ�");
   COMP_GETPARSEPARAS(2,snode_mxroot,"2090��ϸ��Žڵ�");	
   /*�����ϸ�ڵ����*/
   iProjectNum=0;
   COMP_SOFTGETXML("/tips/DetailNum",sbuf);
   iProjectNum = atoi(sbuf);
   
   LOG(LM_STD,Fmtmsg("  -->ȡ�ӽڵ�/tips/jls����[%d]",iProjectNum),"INFO");
   
   if (iProjectNum == 0)
   {
   		 LOG(LM_STD,Fmtmsg("  -->�걨��ϸ��¼����Ϊ0!"),"ERROR");
		   fpub_SetCompStatus(lXmlhandle,1);
		   fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("�걨��ϸ��¼����Ϊ0!"));
		   return 1;
   }
   
   /*ѭ�����˰����ϸ*/
   for (i=1,iflag1=0;i<=iProjectNum;i++)
   {
   	  /*����ProjectId ��Ŀ���*/
   	  memset(sbuf,0,sizeof(sbuf));
   	  sprintf(sbuf,"%d",i);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/ProjectId",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 
      /*����TaxTypeCode ˰�ִ���*/
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/TAX_TYPE_CODE",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxTypeCode",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 

      
      /*����TaxStartDate ˰������������*/
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/BUSS_START_DATE",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxStartDate",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 
      /*����TaxEndDate ˰����������ֹ*/
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/BUSS_END_DATE",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxEndDate",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 
      /*����TaxType ˰������*/
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/TAX_TYPE",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxType",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 
      /*����TaxTypeAmt ˰�ֽ��*/
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/TAX_TYPE_AMT",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
      tmpAmt = atof(sbuf);
      memset(sbuf,0,sizeof(sbuf));
      sprintf(sbuf,"%.2f",tmpAmt);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxTypeAmt",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf);
      dSumFactTaxAmt = dSumFactTaxAmt + atof(sbuf); 
      /*����DetailNum ��ϸ���� */
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s|%d/TAX_GL_NUM",snode_dataroot,i);
      COMP_SOFTGETXML(stmpnode,sbuf);
      iDetailNum = atoi(sbuf);
   	  memset(stmpnode,0,sizeof(stmpnode));
      sprintf(stmpnode,"%s/TaxTypeList2090|%d/DetailNum",snode_mxroot,i);     
      COMP_HARDSETXML(stmpnode,sbuf); 
      /*ѭ������˰Ŀ��ϸ*/
      for (k=1,iflag2=0;k<=iDetailNum;k++)
      {
          /*����DetailNo ��ϸ���*/
          memset(sbuf,0,sizeof(sbuf));
          sprintf(sbuf,"%d",k);
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/DetailNo",snode_mxroot,i,k);     
          COMP_HARDSETXML(stmpnode,sbuf);       
          /*����TaxSubjectCode ˰Ŀ����*/
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s|%d/TAX_GL_INFO_ARRAY/array/struct|%d/TAX_GL_CODE",snode_dataroot,i,k);
          COMP_SOFTGETXML(stmpnode,sbuf);
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxSubjectCode",snode_mxroot,i,k);     
          COMP_HARDSETXML(stmpnode,sbuf);
          /*����TaxNumber ��˰����*/
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s|%d/TAX_GL_INFO_ARRAY/array/struct|%d/NUM",snode_dataroot,i,k);
          COMP_SOFTGETXML(stmpnode,sbuf);
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxNumber",snode_mxroot,i,k);     
          COMP_HARDSETXML(stmpnode,sbuf);
          /*����TaxAmt ��˰���*/
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s|%d/TAX_GL_INFO_ARRAY/array/struct|%d/DUE_FEE",snode_dataroot,i,k);
          COMP_SOFTGETXML(stmpnode,sbuf);
          tmpAmt = atof(sbuf);
          memset(sbuf,0,sizeof(sbuf));
          sprintf(sbuf,"%.2f",tmpAmt);
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/TaxAmt",snode_mxroot,i,k);     
          COMP_HARDSETXML(stmpnode,sbuf);
          /*����FactTaxAmt ʵ��˰��*/
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s|%d/TAX_GL_INFO_ARRAY/array/struct|%d/ACT_ACCEPT_AMT",snode_dataroot,i,k);
          COMP_SOFTGETXML(stmpnode,sbuf);
          tmpAmt = atof(sbuf);
          memset(sbuf,0,sizeof(sbuf));
          sprintf(sbuf,"%.2f",tmpAmt);
   	      memset(stmpnode,0,sizeof(stmpnode));
          sprintf(stmpnode,"%s/TaxTypeList2090|%d/TaxSubjectList2090|%d/FactTaxAmt",snode_mxroot,i,k);
          COMP_HARDSETXML(stmpnode,sbuf);
      }
   }
   
   /*�������׽��*/
   COMP_GETPARSEPARAS(3,sbuf,"�������׽��ڵ�");
   memset(sbuf2,0,sizeof(sbuf2));
   sprintf(sbuf2,"%.2f",dSumFactTaxAmt);
   COMP_HARDSETXML(sbuf,sbuf2);
   
   fpub_SetCompStatus(lXmlhandle,0);
   LOG(LM_STD,Fmtmsg("  �����걨¼����������2090׼�����ݳɹ�-->"),"INFO");
   return 0;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_UpdSFXY
�������: �޸�����Э��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

�������裺
   ǰ��������������ɾ��ǰ����ɶ��˺�����������У��        1 ����

          ��ѯЭ����������ݿ����Ƿ��Ѵ��ڡ�
            ����->��֤Э�����Ӧ�����ջ��ء���˰���˺š�֧�����кż�¼�Ƿ�����������Ľ���ʧ�ܣ����ϵĸ��¡� 
            ������->����ʧ��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����              ����
ί�й�ϵ�Ǽ�	tips_wtgxdj

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: wangw
��������: 2012��8��3��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_UpdSFXY(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sProtocolNo[60+1];/* Э����� */
        char sProtocolno_tmp[60+1];/* Э����� */
        char sTaxOrgCode[12+1];/* ���ջ��ش��� */
        char sPayAcct[32+1];/* �����˺� */
        char sPayBkCode[12+1];/* �������к� */
        char sPayOpBkCode[12+1];/* �������к� */
        SDB_TIPS_WTGXDJ stWtgxdj;
        SDB_TIPS_WTGXDJ stWtgxdj1;
        int iCount;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */

    char sBuf[256];
    char sZwrq[8+1];
    char sBankProNo[30];
    int iret;
    
    /* add DCI 20141103 */
    char sSql1[1024];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
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

    COMP_PARACOUNTCHK(4);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sProtocolNo, 0x00, sizeof(sProtocolNo));
    COMP_GETPARSEPARAS(1, sBuf, "Э�����")
    pstrcopy(sProtocolNo, sBuf, sizeof(sProtocolNo));
    trim(sProtocolNo);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTaxOrgCode, 0x00, sizeof(sTaxOrgCode));
    COMP_GETPARSEPARAS(2, sBuf, "���ջ��ش���")
    pstrcopy(sTaxOrgCode, sBuf, sizeof(sTaxOrgCode));
    trim(sTaxOrgCode);       
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayAcct, 0x00, sizeof(sPayAcct));
    COMP_GETPARSEPARAS(3, sBuf, "�����˺�")
    pstrcopy(sPayAcct, sBuf, sizeof(sPayAcct));
    trim(sPayAcct);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sPayBkCode, 0x00, sizeof(sPayBkCode));
    COMP_GETPARSEPARAS(4, sBuf, "�������к�")
    pstrcopy(sPayBkCode, sBuf, sizeof(sPayBkCode));
    trim(sPayBkCode);
    
    LOG(LM_STD,Fmtmsg("ǩԼ����Э�鿪ʼ����..."),fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("Э�����[%s],���ջ��ش���[%s],�����˺�[%s],�������к�[%s]", 
        sProtocolNo, sTaxOrgCode, sPayAcct, sPayBkCode),fpub_GetCompname(lXmlhandle))

    /* ��ѯ�Ƿ���ǩԼ */
    /* add dci 20141103 */
    
    memset(&stWtgxdj1, 0x00, sizeof(stWtgxdj1));
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "select yzbz from tips_wtgxdj where protocolno='%s' ",sProtocolNo);     	
    iRet = DBSelectToVar(sErrmsg, &stWtgxdj1.yzbz, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
                
        fpub_SetMsg(lXmlhandle, 24316, "��ѯί�й�ϵ�Ǽ���Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�Ǽ���Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))   
    }
    if( iRet == 0)
    {
        fpub_SetMsg(lXmlhandle, 24325, "����Э�鲻����,����ǩԼ����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э�鲻����,����ǩԼ����"),
            fpub_GetCompname(lXmlhandle))        
    }
    /* end add dci 20141103 */
    /* mod dci 20141103 
    memset(&stWtgxdj1, 0x00, sizeof(stWtgxdj1));
    EXEC SQL SELECT * INTO :stWtgxdj1 
	     FROM  tips_wtgxdj  
	     WHERE protocolno=:sProtocolNo;
		SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "��ѯί�й�ϵ�Ǽ���Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�Ǽ���Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( SQLNOTFOUND )
    {
        fpub_SetMsg(lXmlhandle, 24325, "����Э�鲻����,����ǩԼ����");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("����Э�鲻����,����ǩԼ����"),
            fpub_GetCompname(lXmlhandle))        
    }
    */

    LOG(LM_STD,Fmtmsg("��֤��־[%s]...",stWtgxdj1.yzbz),fpub_GetCompname(lXmlhandle))
    if( strcmp(stWtgxdj1.yzbz,"0") )
    {
        fpub_SetMsg(lXmlhandle, 24327, "������Э������֤�����������޸�");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("������Э������֤�����������޸�"),
            fpub_GetCompname(lXmlhandle))
    }    

    /* ��ѯ�Ƿ���ǩԼ 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_wtgxdj  
	     WHERE taxorgcode=:sTaxOrgCode
	       AND paybkcode=:sPayBkCode
	       AND payacct=:sPayAcct;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24316, "��ѯί�й�ϵ�Ǽ���Ϣʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯί�й�ϵ�Ǽ���Ϣʧ��"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount != 0 )
    {
			    EXEC SQL SELECT protocolno INTO :sProtocolno_tmp 
				     FROM  tips_wtgxdj  
				     WHERE taxorgcode=:sTaxOrgCode
				       AND paybkcode=:sPayBkCode
				       AND payacct=:sPayAcct;
				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR");
				trim(sProtocolno_tmp); 
		    if( strcmp(sProtocolno_tmp,sProtocolNo) )
		    {
		        fpub_SetMsg(lXmlhandle, 24325, "���˻��Ѿ��ʹ����ջ����ж�Ӧ��ϵ,�����ظ�ǩԼ");
		        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���˻��Ѿ��ʹ����ջ����ж�Ӧ��ϵ,�����ظ�ǩԼ"),
		            fpub_GetCompname(lXmlhandle))        
		    }   
    }*/    
    
    /* ��ѯ���ջ����Ƿ���� */
    /* mod dci 20141103 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_taxcodeinfo  
	     WHERE taxorgcode=:sTaxOrgCode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24321, "��ѯ���ջ��ش���ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ���ջ��ش���ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24322, "���ջ��ش��벻����");
        LOG(LM_STD,Fmtmsg("iCount[%d],taxorgcode[%s]...",iCount,sTaxOrgCode),fpub_GetCompname(lXmlhandle))
        EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_taxcodeinfo  
	     WHERE taxorgcode=:sTaxOrgCode;
	     	LOG(LM_STD,Fmtmsg("iCount[%d],taxorgcode[%s]...",iCount,sTaxOrgCode),fpub_GetCompname(lXmlhandle))
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ջ��ش��벻����"),
            fpub_GetCompname(lXmlhandle))        
    }    
		*/
    /* ��ѯ�������к��Ƿ���� */
    /* mod dci 20141103 
    iCount = 0 ;
    EXEC SQL SELECT COUNT(*) INTO :iCount 
	     FROM  tips_qshdj  
	     WHERE paybkcode=:sPayBkCode;
	SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR"); 
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24323, "��ѯ��ҵ���������еǼǱ�ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ��ҵ���������еǼǱ�ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }    
    if ( iCount == 0 )
    {
        fpub_SetMsg(lXmlhandle, 24324, "�������к�δ��ʼ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�������к�δ��ʼ��"),
            fpub_GetCompname(lXmlhandle))        
    }
		*/
		   
    /*��ʼ�޸�����Э��*/     
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));     
    COMP_SOFTGETXML("/tips/zwrq",sBuf);
    pstrcopy(sZwrq, sBuf, sizeof(sZwrq));
    
    iret = 0;

    memset(&stWtgxdj,0,sizeof(stWtgxdj));
      

    /*ί�й�ϵ״̬*/ 
    stWtgxdj.wtgxzt[0]='0';
    /*Э�����*/
    pstrcopy(stWtgxdj.protocolno, sProtocolNo, sizeof(stWtgxdj.protocolno));
    if(strlen(stWtgxdj.protocolno)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "Э�����Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("Э�����Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*���ջ��ش���*/
    pstrcopy(stWtgxdj.taxorgcode, sTaxOrgCode, sizeof(stWtgxdj.taxorgcode));
    if(strlen(stWtgxdj.taxorgcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "���ջ��ش���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���ջ��ش���Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
   /*��˰�˱���*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/TaxPayCode",sBuf)
    pstrcopy(stWtgxdj.taxpaycode, sBuf, sizeof(stWtgxdj.taxpaycode));
    if(strlen(stWtgxdj.taxpaycode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "��˰�˱���Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��˰�˱���Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*��˰������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/TaxPayName",sBuf)
    pstrcopy(stWtgxdj.taxpayname, sBuf, sizeof(stWtgxdj.taxpayname));
    if(strlen(stWtgxdj.taxpayname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "��˰������Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��˰������Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*�ɿλ����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/jkdwmc",sBuf)
    pstrcopy(stWtgxdj.handorgname, sBuf, sizeof(stWtgxdj.handorgname));
    if(strlen(stWtgxdj.handorgname)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�ɿλ����Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�ɿλ����Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
    /* �������к�*/
    pstrcopy(stWtgxdj.paybkcode, sPayBkCode, sizeof(stWtgxdj.paybkcode));
    if(strlen(stWtgxdj.paybkcode)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�������к�Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�������к�Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
    /* �����ʻ�*/ 
    pstrcopy(stWtgxdj.payacct, sPayAcct, sizeof(stWtgxdj.payacct));
    if(strlen(stWtgxdj.payacct)==0)
    {
        fpub_SetMsg(lXmlhandle, 24324, "�����ʻ�Ϊ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�����ʻ�Ϊ��"),
            fpub_GetCompname(lXmlhandle))        
    }
    /*�ͻ�����*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/khh",sBuf)
    pstrcopy(stWtgxdj.khh, sBuf, sizeof(stWtgxdj.khh));
    /*��ϵ�޸�����*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/xgrq",sBuf)		/* 20150803 /tips/zwrq �޸�Ϊ/tips/xgrq */
    pstrcopy(stWtgxdj.xgrq, sBuf, sizeof(stWtgxdj.xgrq));
    
    /*�޸���ˮ��*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/zhqzlsh",sBuf)
    pstrcopy(stWtgxdj.xglsh, sBuf, sizeof(stWtgxdj.xglsh));
    /*�޸Ļ�������*/
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/pub/jgdh",sBuf)
    pstrcopy(stWtgxdj.xgjgdh, sBuf, sizeof(stWtgxdj.xgjgdh));
    /*�޸ĵ�������*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh",sBuf)
    pstrcopy(stWtgxdj.xgdqdh, sBuf, sizeof(stWtgxdj.xgdqdh));
    /*�޸Ľ��׹�Ա*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy",sBuf)
    pstrcopy(stWtgxdj.xgjygy, sBuf, sizeof(stWtgxdj.xgjygy));
    /*�޸��ն˴���*/ 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh",sBuf)
    pstrcopy(stWtgxdj.xgzddh, sBuf, sizeof(stWtgxdj.xgzddh));
    /*��չ��־*/
    
    /*��չ��־ edit 20140901 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/resp/zhlx", sBuf)/* �ʻ����� */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[0]=sBuf[0];
    }else
        stWtgxdj.kzbz[0]='0'; 
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/chbz", sBuf)/* �����־ */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[1]=sBuf[0];
    }else
        stWtgxdj.kzbz[1]='0';
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips_host/req/kzbz", sBuf)/* ���۱�־ add 20140901 */
    if ( sBuf[0] != '\0')
    {
        stWtgxdj.kzbz[2]=sBuf[0];
    }else
        stWtgxdj.kzbz[2]='C'; 
    strcat(stWtgxdj.kzbz, "00000");   
    /*�ͻ��� �ظ�20140808ɾ��*/
    /*memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/khh",sBuf);
    pstrcopy(stWtgxdj.khh, sBuf, sizeof(stWtgxdj.khh));*/
    /*��������к�*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhhh",sBuf);
    pstrcopy(stWtgxdj.payopbkcode, sBuf, sizeof(stWtgxdj.payopbkcode));
    /*������л�����*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.opbankno,sBuf,sizeof(stWtgxdj.opbankno)); 
    /*��ע--�����л����� ����̨��ѯЭ���� add 20150710 */
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips/fkkhhjgh",sBuf);
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));
    /*��ע--����������
    memset(sBuf, 0x00, sizeof(sBuf)); 
    COMP_SOFTGETXML("/tips_host/resp/khhmc",sBuf)
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));*/
    /*��֤��־*/
    stWtgxdj.yzbz[0]='0';
        
    /*�������
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/tamc/req/fkkhhhh",sBuf);
    pstrcopy(stWtgxdj.payopbkcode, sBuf, sizeof(stWtgxdj.payopbkcode));*/

    /*������л�����
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/tamc/req/bz",sBuf);
    pstrcopy(stWtgxdj.byzd, sBuf, sizeof(stWtgxdj.byzd));
    LOG(LM_STD,Fmtmsg("sPayOpBkCode[%s]byzd[%s]...",stWtgxdj.payopbkcode,stWtgxdj.byzd),fpub_GetCompname(lXmlhandle))
		pstrcopy(stWtgxdj.payopbkcode,sPayOpBkCode,sizeof(stWtgxdj.payopbkcode)); */
		
    /*��������Э��*/
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "update tips_wtgxdj  \
    		set	taxorgcode='%s'  \
						,paybkcode='%s'  \
						,payacct='%s'    \
						,taxpaycode='%s' \
						,payopbkcode='%s'\
						,taxpayname='%s' \
						,handorgname='%s'\
						,byzd='%s'       \
						,khh='%s'        \
						,xgrq='%s'       \
						,xglsh='%s'      \
						,xgdqdh='%s'     \
						,xgjgdh='%s'     \
						,xgjygy='%s'     \
						,xgzddh='%s'     \
						,opbankno='%s'   \
    			where protocolno='%s'" \
    			,stWtgxdj.taxorgcode   \
    			,stWtgxdj.paybkcode    \
    			,stWtgxdj.payacct      \
    			,stWtgxdj.taxpaycode   \
          ,stWtgxdj.payopbkcode  \
          ,stWtgxdj.taxpayname   \
          ,stWtgxdj.handorgname  \
          ,stWtgxdj.byzd         \
          ,stWtgxdj.khh          \
          ,stWtgxdj.xgrq         \
          ,stWtgxdj.xglsh        \
          ,stWtgxdj.xgdqdh       \
          ,stWtgxdj.xgjgdh       \
          ,stWtgxdj.xgjygy       \
          ,stWtgxdj.xgzddh       \
          ,stWtgxdj.opbankno     \
          ,sProtocolNo);
    LOG(LM_STD,Fmtmsg("sSql1[%s]...",sSql1),fpub_GetCompname(lXmlhandle))               	
    iRet = DCIExecuteDirect(sSql1);	 
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        fpub_SetMsg(lXmlhandle, 24327, "�޸�����Э��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�޸�����Э��ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
		iRet =DCICommit();
		/* INFORMIX ����Ҫ�����ύ���� DB2 ORA��Ҫ�ſ�ע��  
    if ( iRet < 0 )
    {
      LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      DCIRollback();
      
      fpub_SetMsg(lXmlhandle, 24327, "�޸�����Э��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�޸�����Э��ʧ��"),
            fpub_GetCompname(lXmlhandle))  
    }
    */

    /* end dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL UPDATE tips_wtgxdj 
    		set taxorgcode= :stWtgxdj.taxorgcode,
    				paybkcode= :stWtgxdj.paybkcode,
    				payacct= :stWtgxdj.payacct,
    				taxpaycode= :stWtgxdj.taxpaycode,
    				payopbkcode= :stWtgxdj.payopbkcode,
    				taxpayname= :stWtgxdj.taxpayname,
    				handorgname= :stWtgxdj.handorgname,
    				byzd= :stWtgxdj.byzd,
    				khh= :stWtgxdj.khh,
    				xgrq= :stWtgxdj.xgrq,
    				xglsh= :stWtgxdj.xglsh,
    				xgdqdh= :stWtgxdj.xgdqdh,
    				xgjgdh= :stWtgxdj.xgjgdh,
    				xgjygy= :stWtgxdj.xgjygy,
    				xgzddh= :stWtgxdj.xgzddh,
    				opbankno= :stWtgxdj.opbankno
    			where protocolno=:sProtocolNo;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");     
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24327, "�޸�����Э��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("�޸�����Э��ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
    
    EXEC SQL COMMIT;  /*�����ύ
    */
    fpub_SetMsg(lXmlhandle, 0, "�޸�����Э��ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�޸�����Э��ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������: SYW_TIPS_XIBTZPD
�������: �����ж�
�������: 
  �����ж�
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: wangw
��������: 2012��08��1��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_XIBTZPD(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sTzlx[1+1];/* �������� */
        char sYzwrq[8+1];/* �������� */
        char sDzjg[10+1];/* ���˽�� */
        long	dYqzlsh=0;
        int iCount;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */
    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */

    fpub_InitSoComp(lXmlhandle);
    LOG(LM_STD,Fmtmsg("�����жϿ�ʼ"), fpub_GetCompname(lXmlhandle));

    COMP_PARACOUNTCHK(3)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��������");
    trim(sBuf);
    strcpy(sTzlx,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"ԭ��������");
    trim(sBuf);
    strcpy(sYzwrq,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"ԭǰ����ˮ��");
    dYqzlsh = atol(sBuf);
    
    /*��ѯ���˲�ƽ�ǼǱ�--�޸�Ϊ��ѯԭʵʱ��������ˮ--20120830 wangw*/
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "SELECT dzbz from tips_drls where zwrq='%s' and zhqzlsh=%d",sYzwrq,dYqzlsh);     	
    LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
    iRet = DBSelectToVar(sErrmsg, &sDzjg, sSql1);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")         
        
        fpub_SetMsg(lXmlhandle, 24327, "��ѯ������ˮ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }
		
		/*δ�鵽������ˮʱ�ٲ鵱��������˰��ϸ */
    if ( iRet == 0)
    {
    	memset( sSql1, 0x00, sizeof( sSql1 ) );
    	snprintf( sSql1, sizeof(sSql1), "SELECT kzbz from tips_ssplksfmx where zwrq='%s' and plmxxh=%d",sYzwrq,dYqzlsh);  
    	LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")  	
    	iRet = DBSelectToVar(sErrmsg, &sDzjg, sSql1);    	
	    if ( iRet < 0 )
	    {
	    		LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
	    		
	        fpub_SetMsg(lXmlhandle, 24327, "��ѯ������˰��ϸ��ʧ��");
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ������˰��ϸ��ʧ��"),
	            fpub_GetCompname(lXmlhandle))
	    }   
	    if ( iRet == 0 )
	    {
        fpub_SetMsg(lXmlhandle, 24327, "δ�鵽��Ӧ��ƽ��ϸ");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("δ�鵽��Ӧ��ƽ��ϸ"),
            fpub_GetCompname(lXmlhandle))
      }
    }
    /* end dci 20141103 */
    
		/* EXEC SQL SELECT dzjg into :sDzjg from  tips_dzbpdj
    	WHERE zwrq = :sYzwrq and zhqzlsh = :dYqzlsh ; */
    /* mod dci 20141103
    EXEC SQL SELECT dzbz into :sDzjg from  tips_drls
    	WHERE zwrq = :sYzwrq and zhqzlsh = :dYqzlsh ;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");     
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24327, "��ѯ������ˮ��ʧ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ������ˮ��ʧ��"),
            fpub_GetCompname(lXmlhandle))
    }   

    /*δ�鵽������ˮʱ�ٲ鵱��������˰��ϸ
    if ( SQLNOTFOUND )
    {
    	EXEC SQL SELECT kzbz into :sDzjg from  tips_ssplksfmx
    		WHERE zwrq = :sYzwrq and plmxxh = :dYqzlsh ;
	    if ( SQLERR )
	    {
	        fpub_SetMsg(lXmlhandle, 24327, "��ѯ������˰��ϸ��ʧ��");
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��ѯ������˰��ϸ��ʧ��"),
	            fpub_GetCompname(lXmlhandle))
	    }   
	    if ( SQLNOTFOUND )
	    {
        fpub_SetMsg(lXmlhandle, 24327, "δ�鵽��Ӧ��ƽ��ϸ");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("δ�鵽��Ӧ��ƽ��ϸ"),
            fpub_GetCompname(lXmlhandle))
      }
    }
    */   

    /*���˽��ΪTIPS��ģ����������*/
    if (( sDzjg[1] == '3'||sDzjg[0] == '2') && sTzlx[0] == '1' )
    {
        fpub_SetMsg(lXmlhandle, 24327, "���˽��ΪTIPS�������ٵģ����ܳ���");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���˽��ΪTIPS�������ٵģ����ܳ���"),
            fpub_GetCompname(lXmlhandle))
    }   
    
    /*���˽��Ϊ���Ķ�ģ���������*/
    if (( sDzjg[0] == '3'||sDzjg[1] == '2') && sTzlx[0] == '0' )
    {
        fpub_SetMsg(lXmlhandle, 24327, "���˽��Ϊ���Ķ��TIPS�ٵģ����ܲ���");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("���˽��Ϊ���Ķ��TIPS�ٵģ����ܲ���"),
            fpub_GetCompname(lXmlhandle))
    }   

    fpub_SetMsg(lXmlhandle, 0, "�����жϳɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("�����жϳɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;  
}    



/************************************************************************
��̬�����������
�����������: SYW_TIPS_XIBLSH
�������: ���ɷ�������ˮ��
�������: 
  ���ɷ�������ˮ��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: wangw
��������: 2012��08��1��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_XIBLSH(HXMLTREE lXmlhandle)
{
    int iParas;
    char sZhqzlsh[8+1];/* ǰ����ˮ�� */
    char sZwrq[8+1];/* �������� */
    char sHxlsh[15+1];/* ���˽�� */
    long	dQzlsh=0;
    char sBuf[256];
    char sNode[256];

    fpub_InitSoComp(lXmlhandle);
    LOG(LM_STD,Fmtmsg("���ɷ�������ˮ�ſ�ʼ"), fpub_GetCompname(lXmlhandle));

    COMP_PARACOUNTCHK(3)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��������");
    trim(sBuf);
    strcpy(sZwrq,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"ǰ����ˮ��");
    trim(sBuf);
    strcpy(sZhqzlsh,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"����ڵ�");
    trim(sBuf);
    strcpy(sNode,sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memcpy(sBuf,"TASK",4);
    memcpy(sBuf+4,sZwrq+2,6);

    if(strlen(sZhqzlsh)<5)
    {
	    dQzlsh = atol(sZhqzlsh);    
	    sprintf(sHxlsh,"%s%05.5d%",sBuf,dQzlsh);
  	}
  	else
  		sprintf(sHxlsh,"%s%5.5s%",sBuf,sZhqzlsh);
  		
LOG(LM_STD,Fmtmsg("----------serial_no[%s]-------------",sHxlsh), fpub_GetCompname(lXmlhandle));
		
    COMP_SOFTSETXML(sNode, sHxlsh)

    fpub_SetMsg(lXmlhandle, 0, "���ɷ�������ˮ��");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("���ɷ�������ˮ��"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;  
}    

/************************************************************************
��̬�����������
�����������: SYW_TIPS_XIBYWLSH
�������: ����ҵ����ˮ��
�������: 
  ���ɷ�������ˮ��
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: wangw
��������: 2012��08��1��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_XIBYWLSH(HXMLTREE lXmlhandle)
{
    int iParas;
    char sZhqzlsh[8+1];/* ǰ����ˮ�� */
    char sZwrq[8+1];/* �������� */
    char sHxlsh[15+1];/* ���˽�� */
    long	dQzlsh=0;
    char sBuf[256];
    char sNode[256];

    fpub_InitSoComp(lXmlhandle);
    LOG(LM_STD,Fmtmsg("����ҵ����ˮ�ſ�ʼ"), fpub_GetCompname(lXmlhandle));

    COMP_PARACOUNTCHK(3)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"��������");
    trim(sBuf);
    strcpy(sZwrq,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"ǰ����ˮ��");
    trim(sBuf);
    strcpy(sZhqzlsh,sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"����ڵ�");
    trim(sBuf);
    strcpy(sNode,sBuf);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memcpy(sBuf,"TIPS",4);
    memcpy(sBuf+4,sZwrq+2,6);

    if(strlen(sZhqzlsh)<5)
    {
	    dQzlsh = atol(sZhqzlsh);    
	    sprintf(sHxlsh,"%s%05.5d%",sBuf,dQzlsh);
  	}
  	else
  		sprintf(sHxlsh,"%s%5.5s%",sBuf,sZhqzlsh);
  		
LOG(LM_STD,Fmtmsg("----------serial_no[%s]-------------",sHxlsh), fpub_GetCompname(lXmlhandle));
		
    COMP_SOFTSETXML(sNode, sHxlsh)

    fpub_SetMsg(lXmlhandle, 0, "���ɷ�������ˮ��");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("���ɷ�������ˮ��"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;  
}    


/************************************************************************
��̬�����������
�����������: SYW_TIPS_XIBFLOOR
�������: ����ȡ��
�������: 
  ����ȡ���������ó�����ȡ��-1
�������: 
��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ����ʧ�ܡ���

��Ҫ�������:
  ����         ����

�� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
�� �� Ա: wangw
��������: 2012��08��1��
�޸�����: 
����ʹ��ʾ��: 
************************************************************************/
IRESULT SYW_TIPS_XIBFLOOR(HXMLTREE lXmlhandle)
{
    int iParas;
    int iBcs=0;      /* ������ */
    int iCs;          /* ���� */
    int iShang;
    char sBuf[256];
    char sNode[256];

    fpub_InitSoComp(lXmlhandle);
    LOG(LM_STD,Fmtmsg("��������ȡ������ʼ"), fpub_GetCompname(lXmlhandle));

    COMP_PARACOUNTCHK(3)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"������");
    trim(sBuf);
    iBcs=atoi(sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"����");
    trim(sBuf);
    iCs=atoi(sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3,sBuf,"����ڵ�");
    trim(sBuf);
    strcpy(sNode,sBuf);
    
    if(iCs==0)
    {
	    fpub_SetMsg(lXmlhandle, 0, "��������ȡ����ʧ��");
	    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	    LOG(LM_STD,Fmtmsg("��������ȡ����ʧ��"), fpub_GetCompname(lXmlhandle));
    }
LOG(LM_STD,Fmtmsg("----------iShang[%d]-------------",iShang), fpub_GetCompname(lXmlhandle));

		/*modify bu wangw 20120913 ������ó�����ȡ��-1������ѭ��������*/
		if(iBcs%iCs == 0 )    	
    	iShang = floor(iBcs/iCs)-1;
    else
    	iShang = floor(iBcs/iCs);
LOG(LM_STD,Fmtmsg("----------iShang[%d]-------------",iShang), fpub_GetCompname(lXmlhandle));
		sprintf(sBuf,"%d",iShang);
    
    COMP_SOFTSETXML(sNode, sBuf)

    fpub_SetMsg(lXmlhandle, 0, "��������ȡ�����ɹ�");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("��������ȡ�����ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;  
}    

/*Add by wangw 20120906 ת��ȫ���ַ�Ϊ��ǣ��Ա��ں���ȫ���ַ�*/
int sQj2Bj(char s[200],char *st)
{
    /* EXEC SQL BEGIN DECLARE SECTION; add dci 20141103 */
        char sQj[200+1];
        char sBj[200+1];
        int iCount;
    /* EXEC SQL END   DECLARE SECTION; add dci 20141103 */
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI ִ��sql��� add 20141103*/
		char sErrmsg[256]; /*DCI ִ��sql��䷵�ش�����Ϣ add 20141103*/ 
		int iRet=0;
		/* end add dci 20141103 */

    memset(sQj,0,sizeof(sQj));
    memset(sBj,0,sizeof(sBj));
    strcpy(sQj,s);
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "drop table qj2bj" );
               	
    iRet = DCIExecuteDirect(sSql1);	 
    
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof(sSql1), "create table qj2bj (  	string	char(200)  )" );
               	
    iRet = DCIExecuteDirect(sSql1);	
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        LOG(LM_STD,Fmtmsg("����ʱ��qj2bjʧ��"),"ERROR")
       return -1;
    }
		
		memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "insert into qj2bj values ('%s')",sQj);
    iRet = DCIExecuteDirect(sSql1);	
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      LOG(LM_STD,Fmtmsg("������ʱ��qj2bjʧ��"),"ERROR")
       return -1;
    }
		
		memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), " select to_single_byte(string) from qj2bj where string='%s'",sQj);     	
    iRet = DBSelectToVar(sErrmsg, &sBj, sSql1);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      LOG(LM_STD,Fmtmsg("��ѯ��ʱ��qj2bjʧ��"),"ERROR")
       return -1;
    }
    /* end dci 20141103 */
    
    /* mod dci 20141103 
    EXEC SQL drop table qj2bj;
    EXEC SQL create table qj2bj
    (
    	string	char(200)
    );
    if ( SQLERR )
    {
	     LOG(LM_STD,Fmtmsg("����ʱ��qj2bjʧ��,sqlcode[%d]",sqlca.sqlcode),"ERROR")
       return -1;
    }
    
    EXEC SQL insert into qj2bj values (:sQj);
    if ( SQLERR )
    {
	     LOG(LM_STD,Fmtmsg("������ʱ��qj2bjʧ��,sqlcode[%d]",sqlca.sqlcode),"ERROR")
       return -1;
    }
    
    EXEC SQL select to_single_byte(string) into :sBj from qj2bj where string=:sQj;
    if ( SQLERR )
    {
	     LOG(LM_STD,Fmtmsg("��ѯ��ʱ��qj2bjʧ��,sqlcode[%d]",sqlca.sqlcode),"ERROR")
       return -1;
    }
    */
    trim(sBj);
    strcpy(st,sBj);	
    
    return 0 ;
}



