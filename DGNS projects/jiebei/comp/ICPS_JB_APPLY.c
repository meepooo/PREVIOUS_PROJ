/********************************************************************
 ��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
 ��Ŀ����:
 ��    ��:V2.1.0.1
 ����ϵͳ:
 �ļ�����:ICPS_JB_APPLY.c
 �ļ�����:��ݸũ�̽�������ģ�����
 �� �� Ա:
 ��������:2015-9-29
 �� �� Ա:
 �޸�����:
 �޸�˵��:
 *********************************************************************/
#include "../incl/ICPS_JB_HEAD.h"


/*****************************************************
   ��������:  int ffunc_xml_getNodeValue(HXMLTREE lXmlhandle, const char* szPath, const char* nodeAttr, char* szValue, unsigned int size, int iFlag)
   ��������:  ��ȡXML�ڵ�ֵ,���ַ����ڵ�Ϊ����'-';����������ͽڵ�Ϊ����0
   ��������:  lXmlhandle  XML���������
              Path  �ڵ�·��
              nodeAttr �ڵ����� 0-�ַ���, 1-�����ֵ�
              szValue �ڵ�ֵ����ַ���
              size  ���ֵ�Ŀռ��С
              iFlag �ڵ��Ƿ������� ICPS_JB_XML_NULL ICPS_JB_XML_NOTNULL
             
   ��������:  >0: �ڵ�ֵ��ʵ�ʳ���
              -1:�������Ϊ�ջ��������ΪNULL
              -2:��Ϊ�յ�XML�ڵ㲻����
              -3:����ԭ��ʧ��

   ����˵��:  
            
   �޸�˵��:  
*****************************************************/
int ffunc_xml_getNodeValue(HXMLTREE lXmlhandle, char* psPath, char* psNodeAttr, char* psValue, unsigned int size, int iFlag)
{
    int  iRet = 0;
    char sBuf[1024];
    int  iNodeValueLen = 0;
    char* psNodeValue = NULL;
    
    if ( psValue == NULL )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_XMLOP, Fmtmsg(MSG_ICPS_JB_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!�ڵ�[%s]��Ŀ�����ΪNULL!", MSG_ICPS_JB_XMLOP, psPath),"")
        return -1;
    }
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iNodeValueLen = sizeof(sBuf);
    if ( iNodeValueLen > size )
    {
        psNodeValue = sBuf;
        iRet = xml_GetElement(lXmlhandle, psPath, psNodeValue, iNodeValueLen);
        pstrcopy(psValue, psNodeValue, size);
    }else
    {
        iNodeValueLen = size;
        psNodeValue = psValue ;
        iRet = xml_GetElement(lXmlhandle, psPath, psNodeValue, iNodeValueLen);
    }
    psNodeValue = NULL;
    if( iRet == FAIL && XML_NODE_NOTNULL == iFlag )
    {        
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_XMLOP, Fmtmsg(MSG_ICPS_JB_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!�ڵ�[%s]������[%d]!", MSG_ICPS_JB_XMLOP, psPath, iRet),"") 
        return -2;
    }
    
    if( (psValue[0] == '\0') && (XML_NODE_NOTNULL == iFlag) )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_XMLOP, Fmtmsg(MSG_ICPS_JB_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!�ڵ�[%s]ֵΪ��!", MSG_ICPS_JB_XMLOP, psPath),"")
        return -2;
    }    
    trim(psValue);       
    return strlen(psValue);
}

/*****************************************************
   ��������:  fdbop_ins_icps_jb_applyinfo
   ��������:  �Ǽ����������
   ��������:  *pst_icps_jb_applyinfo   ����������Ϣ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_icps_jb_applyinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_APPLYINFO *pst_icps_jb_applyinfo)
{
    int iRet = -1;
    char sErrmsg[1000];
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("icps_jb_applyinfo", SD_ICPS_JB_APPLYINFO, NUMELE(SD_ICPS_JB_APPLYINFO), pst_icps_jb_applyinfo, sErrmsg);
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_DBOP, MSG_ICPS_JB_DBOP);
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽ��������뵥��ʧ��ʧ��,reqmsgid[%s]", 
            pst_icps_jb_applyinfo->reqmsgid),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}
/*****************************************************
   ��������:  fdbop_ins_icps_jb_zminfo
   ��������:  �Ǽ�������֥����Ϣ
   ��������:  *pst_icps_jb_zminfo   ������֥����Ϣ

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_icps_jb_zminfo(HXMLTREE lXmlhandle,ST_ICPS_JB_ZMINFO *pst_icps_jb_zminfo,char *sMap)
{
    int iRet = -1;
    char sErrmsg[1000];
    memset(sErrmsg, 0x00, sizeof(sErrmsg));

    iRet = DBInsertBLOB("icps_jb_zminfo",SD_ICPS_JB_ZMINFO, NUMELE(SD_ICPS_JB_ZMINFO), pst_icps_jb_zminfo, sErrmsg,sMap, strlen(sMap));

    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_DBOP, MSG_ICPS_JB_DBOP);
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽ�������֥����Ϣʧ��,reqmsgid[%s]", 
            pst_icps_jb_zminfo->reqmsgid),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}
/*****************************************************
   ��������:  fdbop_ins_icps_jb_resultinfo
   ��������:  �Ǽ�����ȷ��������Ϣ
   ��������:  *pst_icps_jb_resultinfo   ����ȷ��������Ϣ

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_icps_jb_resultinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_RESULTINFO *pst_icps_jb_resultinfo)
{
    int iRet = -1;
    char sErrmsg[1000];
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("icps_jb_resultinfo", SD_ICPS_JB_RESULTINFO, NUMELE(SD_ICPS_JB_RESULTINFO), pst_icps_jb_resultinfo, sErrmsg);
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_DBOP, MSG_ICPS_JB_DBOP);
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽ�����ȷ��������Ϣʧ��,reqmsgid[%s]", 
            pst_icps_jb_resultinfo->reqmsgid),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}
/*****************************************************
   ��������:  fdbop_ins_icps_jb_extinfo
   ��������:  �Ǽ�������������Ϣ
   ��������:  *pst_icps_jb_extinfo   ������������Ϣ

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_icps_jb_extinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_EXTINFO *pst_icps_jb_extinfo)
{
    int iRet = -1;
    char sErrmsg[1000];
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("icps_jb_extinfo", SD_ICPS_JB_EXTINFO, NUMELE(SD_ICPS_JB_EXTINFO), pst_icps_jb_extinfo, sErrmsg);
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_DBOP, MSG_ICPS_JB_DBOP);
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽ�������������Ϣʧ��,reqmsgid[%s]", 
            pst_icps_jb_extinfo->reqmsgid),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}
/*****************************************************
   ��������:  fdbop_ins_icps_jb_bankinfo
   ��������:  �Ǽ���������������
   ��������:  *pst_icps_jb_bankinfo  ��������������

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_icps_jb_bankinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_BANKINFO *pst_icps_jb_bankinfo)
{
    int iRet = -1;
    char sErrmsg[1000];
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("icps_jb_bankinfo", SD_ICPS_JB_BANKINFO, NUMELE(SD_ICPS_JB_BANKINFO), pst_icps_jb_bankinfo, sErrmsg);
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_ICPS_JB_DBOP, MSG_ICPS_JB_DBOP);
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽ���������������ʧ��,reqmsgid[%s]", 
            pst_icps_jb_bankinfo->reqmsgid),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}
/*****************************************************
   ��������:  fdbop_upd_icps_jb_applyinfo_702513
   ��������:  �������Ͻ���-����������Ϣ��---���ڳ���
   ��������:  *pst_icps_jb_applyinfo  ���Ͻ���-����������Ϣ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_icps_jb_applyinfo_702513(HXMLTREE lXmlhandle,ST_ICPS_JB_APPLYINFO *pst_icps_jb_applyinfo)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update icps_jb_applyinfo set applystat='%s',reqdate='%s',reqtime1='%s',isadmit='%s', \
            creditamt='%s',creditrate='%s',refusecode='%s',refusemsg='%s'  \
            where reqmsgid='%s' and applyno='%s' ", 
        pst_icps_jb_applyinfo->applystat,pst_icps_jb_applyinfo->reqdate,pst_icps_jb_applyinfo->reqtime1,
        pst_icps_jb_applyinfo->isadmit, pst_icps_jb_applyinfo->creditamt,
        pst_icps_jb_applyinfo->creditrate,pst_icps_jb_applyinfo->refusecode,pst_icps_jb_applyinfo->refusemsg,
        pst_icps_jb_applyinfo->reqmsgid,pst_icps_jb_applyinfo->applyno);
    
    LOG(LM_STD, Fmtmsg("fdbop_icps_jb_applyinfo.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 9001, "�����ز���ʧ��");
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("��������������Ϣ��--���ڳ���ʧ��,reqmsgid[%s],applyno[%s]", 
        pst_icps_jb_applyinfo->reqmsgid,pst_icps_jb_applyinfo->applyno),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 9002, "δ�ҵ���ؼ�¼");
        LOGRET( ICPS_JB_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ�����������Ϣ����ؼ�¼,reqmsgid[%s],applyno[%s]", 
        pst_icps_jb_applyinfo->reqmsgid,pst_icps_jb_applyinfo->applyno),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   ��������:  fdbop_upd_icps_jb_applyinfo_702514
   ��������:  �������Ͻ���-����������Ϣ��---���ϳ��󷵻�
   ��������:  *pst_icps_jb_applyinfo  ���Ͻ���-����������Ϣ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_icps_jb_applyinfo_702514(HXMLTREE lXmlhandle,ST_ICPS_JB_APPLYINFO *pst_icps_jb_applyinfo)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update icps_jb_applyinfo set respcode='%s',respmsg='%s',resultstat='%s', \
            retry='%s',respdate='%s',resptime='%s' where reqmsgid='%s' and applyno='%s' ", 
        pst_icps_jb_applyinfo->respcode,pst_icps_jb_applyinfo->respmsg,pst_icps_jb_applyinfo->resultstat,pst_icps_jb_applyinfo->retry,
        pst_icps_jb_applyinfo->respdate,pst_icps_jb_applyinfo->resptime,pst_icps_jb_applyinfo->reqmsgid,
        pst_icps_jb_applyinfo->applyno);
    
    LOG(LM_STD, Fmtmsg("fdbop_icps_jb_applyinfo.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 9001, "�����ز���ʧ��");
        LOGRET( ICPS_JB_FUNCRET_SQLERR, LM_STD, Fmtmsg("��������������Ϣ��ʧ��,reqmsgid[%s],applyno[%s]", 
        pst_icps_jb_applyinfo->reqmsgid,pst_icps_jb_applyinfo->applyno),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 9002, "δ�ҵ���ؼ�¼");
        LOGRET( ICPS_JB_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ�����������Ϣ����ؼ�¼,reqmsgid[%s],applyno[%s]", 
        pst_icps_jb_applyinfo->reqmsgid,pst_icps_jb_applyinfo->applyno),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   ��������:  fdbop_upd_icps_jb_resultinfo
   ��������:  �������Ͻ���-����ȷ��������Ϣ��
   ��������:  *pst_icps_jb_resultinfo  ���Ͻ���-����ȷ��������Ϣ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_icps_jb_resultinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_RESULTINFO *pst_icps_jb_resultinfo)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update icps_jb_resultinfo set resultcode='%s',resultmsg='%s',isadmit='%s',admitmsg='%s' where applyno='%s' ", 
        pst_icps_jb_resultinfo->resultcode,pst_icps_jb_resultinfo->resultmsg,pst_icps_jb_resultinfo->isadmit,
        pst_icps_jb_resultinfo->admitmsg,pst_icps_jb_resultinfo->applyno);
    
    LOG(LM_STD, Fmtmsg("fdbop_icps_jb_resultinfo.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 9001, "�����ز���ʧ��");
        LOGRET( -12, LM_STD, Fmtmsg("��������ȷ��������Ϣ��ʧ��,reqmsgid[%s],applyno[%s]", 
            pst_icps_jb_resultinfo->reqmsgid,pst_icps_jb_resultinfo->applyno),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 9002, "δ�ҵ���ؼ�¼");
        LOGRET( 1403, LM_STD, Fmtmsg("δ�ҵ�������ȷ��������Ϣ����ؼ�¼,reqmsgid[%s],applyno[%s]", 
            pst_icps_jb_resultinfo->reqmsgid,pst_icps_jb_resultinfo->applyno),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_upd_icps_jb_bankinfo
   ��������:  �������Ͻ���-���г�������
   ��������:  *pst_icps_jb_bankinfo  ���Ͻ���-���г�������

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_icps_jb_bankinfo(HXMLTREE lXmlhandle,ST_ICPS_JB_RESULTINFO *pst_icps_jb_resultinfo, char *Condition)
{
    int iRet = -1;
    char sSql[512];
    char sErrmsg[512];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    
    snprintf(sSql, sizeof(sSql), "update icps_jb_resultinfo set resultcode='%s',resultmsg='%s',isadmit='%s',admitmsg='%s' where reqmsgid='%s' and applyno='%s' ", 
        pst_icps_jb_resultinfo->resultcode,pst_icps_jb_resultinfo->resultmsg,pst_icps_jb_resultinfo->isadmit,
        pst_icps_jb_resultinfo->admitmsg,pst_icps_jb_resultinfo->reqmsgid,pst_icps_jb_resultinfo->applyno);
    
    LOG(LM_STD, Fmtmsg("fdbop_icps_jb_resultinfo.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 9001, "�����ز���ʧ��");
        LOGRET( -12, LM_STD, Fmtmsg("��������ȷ��������Ϣ��ʧ��,reqmsgid[%s],applyno[%s]", 
            pst_icps_jb_resultinfo->reqmsgid,pst_icps_jb_resultinfo->applyno),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 9002, "δ�ҵ���ؼ�¼");
        LOGRET( 1403, LM_STD, Fmtmsg("δ�ҵ�������ȷ��������Ϣ����ؼ�¼,reqmsgid[%s],applyno[%s]", 
            pst_icps_jb_resultinfo->reqmsgid,pst_icps_jb_resultinfo->applyno),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_sel_icps_jb_idcode2addr
   ��������:  ��ѯ���Ͻ���-���֤������ת������
   ��������:  *pst_icps_jb_idcode2addr ���֤������ת���ṹ

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_sel_icps_jb_idcode2addr(HXMLTREE lXmlhandle,ST_ICPS_JB_IDCODE2ADDR *pst_icps_jb_idcode2addr)
{
    int iRet = -1;
    char sSql[512];
    char sErrmsg[512];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    
    snprintf(sSql, sizeof(sSql), "select shrtnm,fullnm,upcode,lvl from icps_jb_idcode2addr where id6code='%s' ", pst_icps_jb_idcode2addr->id6code);
    
    LOG(LM_STD, Fmtmsg("fdbop_icps_jb_idcode2addr.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DBSelectToMultiVar(sErrmsg, sSql, pst_icps_jb_idcode2addr->shrtnm,pst_icps_jb_idcode2addr->fullnm,pst_icps_jb_idcode2addr->upcode,
            pst_icps_jb_idcode2addr->lvl);
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, 9001, "�����ز���ʧ��");
        LOGRET( -12, LM_STD, Fmtmsg("��ѯ���Ͻ������֤������ת������ʧ��,id6code[%s]", pst_icps_jb_idcode2addr->id6code),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, 9002, "δ�ҵ���ؼ�¼");
        LOGRET( 1403, LM_STD, Fmtmsg("δ�ҵ����֤������ת������ؼ�¼,id6code[%s]", pst_icps_jb_idcode2addr->id6code),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/****************************************************************************** 
�������ơ�DBInsertBLOB 
�������ܡø���������һ���ṹ���ݸ��±� 
���������tb -- ���� 
desc_arr -- �ṹ������Ϣ 
desc_num -- �ṹ�������� 
pstru -- ����ָ�� 
sblob -- BLOB�ֶ����� 
int ilen -- BLOB���� 

���������errmsg -- ������Ϣ 
�� �� ֵ��>= 0 -- �ɹ� Ӱ������� 
���� -- ʧ�� 

˵��BLOB�ֶα�ṹ���Զ����int�� 
******************************************************************************/ 
int DBInsertBLOB(const char* tb, FLD_DESC desc_arr[], int desc_num, void *pstru, char *errmsg, char *sblob, int ilen) 
{ 
    int i, n; 
    int rowcount; 
    char *stmt, *p=NULL; 
    CURSOR cur; 
    FLD_DESC *pdesc; 
    
    if (desc_num <= 0 || pstru == NULL) 
        return 0; 
    
    stmt = (char *)calloc(1, (MAX_SYM_LEN + 3) * desc_num * 2 + strlen(tb) + 100); 
    if (stmt == NULL) 
    { 
        if (errmsg) 
        sprintf(errmsg, "�ڴ�������"); 
        return -1; 
    }
    memset( &pdesc, 0x00, sizeof(pdesc));
    pdesc = desc_arr; 
    
    n = sprintf(stmt, "insert into %s ( %s ", tb, pdesc->name); 
    pdesc++; 

    for (i = 1, p = stmt + n; i < desc_num-1; i++, pdesc++) 
    { 
        n = sprintf(p, ", %s", pdesc->name); 
        p += n; 
    }

    if (ilen <= 0 )
    { 
        strcat(p, ") values ("); 
        p = p+10;
    }
    else
    {
        n = sprintf(p, ", %s", pdesc->name);
        p += n;
        strcat(p, ") values (");
        p = p+10;
    }
    memset( &pdesc, 0x00, sizeof(pdesc));
    pdesc = desc_arr;
    n = sprintf(p, ":%s ", pdesc->name);
    pdesc++; 

    for (i = 1, p += n; i < desc_num-1; i++, pdesc++) 
    { 
        n = sprintf(p, ", :%s", pdesc->name); 
        p += n; 
    }

    if (ilen <= 0 )
    { 
        strcat(p, ")"); 
    }
    else
    {
        n = sprintf(p, ", :%s", pdesc->name);
        strcat(p, ")");
    }

    
    cur = DCIDeclareCursor(stmt, DCI_STMT_LOCATOR); 
    if (cur == INVALID_CURSOR) 
    { 
        if (errmsg) 
        strcpy(errmsg, DCILastError()); 
        free(stmt); 
        return -2; 
    } 
    free(stmt); 
    
    for (i = 0, pdesc = desc_arr; i < desc_num-1; i++, pdesc++) 
    { 
        int datatype; 
        int datalen; 
        double dv; 
        char dvbuf[64]; 
    
        char *pval = (char *)pstru + pdesc->offset; 
        switch (pdesc->type) 
        { 
            case TT_CHAR: 
            case TT_STRING: 
            datatype = DCIT_CHAR; 
            #ifdef DB_MYSQL 
                datalen = MAX(strlen(pval), pdesc->extlen); 
            #else 
                datalen = MAX(strlen(pval)+1, pdesc->extlen); 
            #endif 
            break; 
        
            case TT_SHORT: 
            datatype = DCIT_INTEGER; 
            datalen = sizeof(short); 
            break; 
            
            case TT_LONG: 
            if ( sizeof(long) == sizeof(int )) 
            { 
                datatype = DCIT_INTEGER; 
                datalen = sizeof(int); 
                /* ����32λ�´����Ĳ��� */ 
            if(pdesc->maxlen == 8) 
            { 
                datatype = DCIT_LONG; 
                datalen = sizeof(long long); 
            } 
            } 
            else 
            { 
                datatype = DCIT_LONG; 
                datalen = sizeof(long); 
                /* ��64λ��int�����ݴ��� */ 
                if(pdesc->maxlen == 4) 
                { 
                    datatype = DCIT_INTEGER; 
                    datalen = sizeof(int); 
                } 
            } 
            break; 
            
            case TT_DOUBLE: 
                datatype = DCIT_DOUBLE; 
                datalen = sizeof(double); 
                if (pdesc->extlen > 0) 
                { 
                snprintf(dvbuf, sizeof(dvbuf), "%.*lf", pdesc->extlen, *(double *)pval); 
                dv = atof(dvbuf); 
                memcpy(pval, &dv, sizeof(double)); 
                } 
                break; 
            
            default: 
                if (errmsg) 
                strcpy(errmsg, "δ֪���ֶ�����"); 
                DCIFreeCursor(cur); 
                return -3; 
        } 
    
        if (DCIBindPara(cur, i, pval, datalen, datatype) == -1) 
        { 
            if (errmsg) 
            strcpy(errmsg, DCILastError()); 
            PRINTF("pos = %d\n", i); 
            DCIFreeCursor(cur); 
            return -4; 
        } 
    } 
    /*��BLOB�ֶ�*/ 
    if (ilen > 0)
    {
        if (DCIBindPara(cur, i, sblob, ilen, DCIT_BLOB) != 0) 
        { 
            if (errmsg) 
            strcpy(errmsg, DCILastError()); 
            PRINTF("pos = %d\n", i); 
            DCIFreeCursor(cur); 
            return -5; 
        }
    } 

    rowcount = DCIExecute(cur); 
    if (rowcount == -1) 
    { 
        if (errmsg) 
        strcpy(errmsg, DCILastError()); 
        DCIFreeCursor(cur); 
        return -6; 
    } 
    
    DCIFreeCursor(cur); 
    return rowcount; 
} 
/************************************************************************
��̬�����������
�����������:ICPS_JB_INSERT_REQ
�������:ICPS_JB_INSERT_REQ
�������: ���Ͻ��½����¼�Ǽ�
��������б�
    ���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
    ���״̬��          ���˵��
    -9999               ȱʡ
    0                   �ɹ�
************************************************************************/
IRESULT ICPS_JB_INSERT_REQ(HXMLTREE lXmlhandle)
{
    int    iParas;    
    int    iRet=0;    
    int    iRet1 = 0;
    int    iLen = 0;
    int    iNum=0;
    int    iNum1=0;
    int    i=0;
    char   trace_code[10]={0};
    char   stmp[512]={0};
    char   stmp1[2+1]={0} ;
    char   ptrq[8+1]={0};
    char   ptlsh[10+1]={0};
    char   sSql[512]={0};
    char   sMapbuf[10240+1]={0};
    CURSOR cur;
    
    
    ST_ICPS_JB_APPLYINFO applyinfo; /*����������Ϣ */
    ST_ICPS_JB_ZMINFO zminfo; /*����������Ϣ--֥����Ϣ */
    ST_ICPS_JB_EXTINFO extinfo; /*��������Ϣ */
    ST_ICPS_JB_RESULTINFO resultinfo;  /*����������Ϣ */
    ST_ICPS_JB_BANKINFO bankinfo;  /*���з������� */
    ST_ICPS_JB_IDCODE2ADDR code2addr; /*���֤������ת�� add 20171128 yj */
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("���Ͻ��µǼ���⴦�����[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "")

    /*��ʼ��*/                               
    memset(&applyinfo, 0x00, sizeof(applyinfo));
    memset(&zminfo, 0x00, sizeof(zminfo));
    memset(&extinfo, 0x00, sizeof(extinfo));
    memset(&resultinfo, 0x00, sizeof(resultinfo));
    memset(&code2addr, 0x00, sizeof(code2addr)); /* add 20171128 yj */
    
    /*��ȡ������Ϣ */
    memset(stmp,0x00,sizeof(stmp));
    memset(trace_code,0x00,sizeof(trace_code));
    COMP_SOFTGETXML("/pub/jydm", trace_code); /*���״��� */
     /*ƽ̨����+ƽ̨��ˮ��*/
    memset(ptrq,0x00,sizeof(ptrq));
    memset(ptlsh,0x00,sizeof(ptlsh));
    COMP_SOFTGETXML(XMLNM_ICPS_JB_PTRQ,ptrq);
    COMP_SOFTGETXML(XMLNM_ICPS_JB_PTLSH,ptlsh); 
    DCIBegin();   /**��ʼ����**/
    if (0 == strcmp(trace_code,"702511"))  /*���·��ͳ�����������Ǽ�*/
    {
        ICPS_JB_PSTRCOPY(applyinfo.ptrq,ptrq);
        ICPS_JB_PSTRCOPY(applyinfo.ptlsh,ptlsh);
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_VERSION,applyinfo.version,"�汾��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_APPID,applyinfo.appid,"ϵͳ��ʶ");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_FUNCTION,applyinfo.function,"���ױ���");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_REQTIMEZONE,applyinfo.reqtimezone,"���ͷ�����ʱ��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_REQTIME,applyinfo.reqtime,"���ķ���ʱ��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_REQMSGID,applyinfo.reqmsgid,"������Ψһ��ʾ");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_SIGNTYPE,applyinfo.signtype,"ǩ���㷨����");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_INPUTCHARSET,applyinfo.inputcharset,"�����ַ�����");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_RESERVE,applyinfo.reserve,"Ԥ����");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_APPLYNO,applyinfo.applyno,"���뵥��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_CERTTYPE,applyinfo.certtype,"֤������");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_CERTNO,applyinfo.certno,"֤������");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_CERTVALIDENDDATE,applyinfo.certvalidenddate,"֤����Ч��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_NAME,applyinfo.name,"����");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_CUSTOMERNO,applyinfo.customerno,"�ͻ����");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_CUSTOMERNO,applyinfo.creditno,"���ű��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_MOBILENO,applyinfo.mobileno,"�ֻ���");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_OCCUPATION,applyinfo.occupation,"ְҵ");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_ADDRESS,applyinfo.address,"��ϸ��ַ"); /* sos mod 20171130 */
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_CITY,applyinfo.city,"����");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_PROV,applyinfo.prov,"ʡ��");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_AREA,applyinfo.area,"����");
		ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_REQTRACENO,applyinfo.reqtraceno,"��С΢ƽ̨������ˮ��");
        /**** add bgn 20171128 yj ****/
		LOG(LM_STD, Fmtmsg("zhandd", fpub_GetCompname(lXmlhandle)), "")
        if(strlen(applyinfo.address) == 0)
        {
            strncpy(code2addr.id6code,applyinfo.certno,6);
            iRet1 = fdbop_sel_icps_jb_idcode2addr(lXmlhandle,&code2addr);
            strcpy(applyinfo.address, code2addr.fullnm);
        }
        /**** add end 20171128 yj ****/
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_ZMAUTHFLAG,applyinfo.zmauthflag,"֥����Ȩ�ɹ���ʾ");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_HASJBADMIT,applyinfo.hasjbadmit,"�Ƿ�֮ǰ���н��¶��");
        ICPS_JB_PSTRCOPY(applyinfo.applystat,"9");
        ICPS_JB_PSTRCOPY(applyinfo.resultstat,"9");
        ICPS_JB_PSTRCOPY(applyinfo.retry,"Y");
        ICPS_JB_PSTRCOPY(applyinfo.reqcode,"00000");
        ICPS_JB_PSTRCOPY(applyinfo.reqmsg,"���ճɹ�");
        
        
        /****************�Ǽǿ�� icps_jb_applyinfo  ********************/ 
        memset(sSql, 0x00, sizeof(sSql));
        snprintf(sSql, sizeof(sSql), "select count(*) from icps_jb_applyinfo where  applyno='%s'",applyinfo.applyno);
        LOG(LM_STD,Fmtmsg("��ѯ�Ƿ���Ҫ�ݵȷ���->sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));

        if ((iRet1 =sql_CountSql(sSql)) < 1)
        {    
    
            LOG(LM_STD, Fmtmsg("��ʼ�Ǽ����Ͻ���-�������󵥱�icps_jb_applyinfo����[%s]", fpub_GetCompname(lXmlhandle)), "");
            iRet1 = fdbop_ins_icps_jb_applyinfo(lXmlhandle,&applyinfo);
            if(iRet1<0)
            {
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return -1;
            }
            LOG(LM_STD, Fmtmsg("�Ǽ����Ͻ���-�������󵥱�icps_jb_applyinfo���ɹ���[%s]", fpub_GetCompname(lXmlhandle)), "");
                
            /*�ж��Ƿ���֥����Ϣ*/
            if ( (iRet = xml_ChildElementCount(lXmlhandle,XMLNM_ICPS_JB_ZM_INFO)) > 0)
            {
                ICPS_JB_PSTRCOPY(zminfo.ptrq,ptrq);
                ICPS_JB_PSTRCOPY(zminfo.ptlsh,ptlsh);
                ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_REQMSGID,zminfo.reqmsgid,"������Ψһ��ʾ");
                ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLYNO,zminfo.applyno,"���뵥��");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_COMPANY_NAME,zminfo.company_name,"���ڹ�˾");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_OCCUPATION,zminfo.occupation,"ְҵ����");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_HAVE_CAR_FLAG,zminfo.have_car_flag,"�Ƿ��г�");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_HAVE_FANG_FLAG,zminfo.have_fang_flag,"�Ƿ��з�");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_AUTH_FIN_LAST_1M_CNT,zminfo.auth_fin_last_1mcnt,"���һ����������ѯ���ڻ�����");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_AUTH_FIN_LAST_3M_CNT,zminfo.auth_fin_last_3mcnt,"���������������ѯ���ڻ�����");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_AUTH_FIN_LAST_6M_CNT,zminfo.auth_fin_last_6mcnt,"���������������ѯ���ڻ�����");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_OVD_ORDER_CNT_6M,zminfo.ovd_order_cnt_6m,"��������������ܱ���");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_OVD_ORDER_AMT_6M,zminfo.ovd_order_amt_6m,"��������������ܽ��");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_MOBILE_FIXED_DAYS,zminfo.mobile_fixed_days,"�ֻ����ȶ�����");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_ADR_STABILITY_DAYS,zminfo.adr_stability_days,"��ַ�ȶ�����");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_LAST_6M_AVG_ASSET_TOTAL,zminfo.last6mavgassettotal,"��������������ʲ��վ�ֵ");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_TOT_PAY_AMT_6M,zminfo.tot_pay_amt_6m,"���������֧���ܽ��");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_XFDC_INDEX,zminfo.xfdc_index,"���ѵ���");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_POSITIVE_BIZ_CNT_1Y,zminfo.positive_biz_cnt_1y,"���һ����Լ������");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_CREDITSCORE_SUCCESS,zminfo.creditscore_success,"֥����������-�ɹ���־");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_CREDITSCORE_BIZ_NO,zminfo.creditscore_biz_no,"֥����������-bizno");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_CREDITSCORE_ZM_SCORE,zminfo.creditscore_zmscore,"֥����������-֥���");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_WATCHLISTII_SUCCESS,zminfo.watchlistii_success,"֥����ҵ��ע����-�ɹ���־");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_WATCHLISTII_BIZ_NO,zminfo.watchlistii_biz_no,"֥����ҵ��ע����-bizno");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_WATCHLISTII_IS_MATCHED,zminfo.watchlistii_matched,"֥����ҵ��ע����-�Ƿ��ע");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_IVS_SUCCESS,zminfo.ivs_success,"֥����թ��ע�嵥-�ɹ���־");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_IVS_HIT,zminfo.ivs_hit,"֥����թ��ע�嵥-�Ƿ����");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_ZM_IVS_BIZ_NO,zminfo.ivs_biz_no,"֥����թ��ע�嵥-bizno");
                
                if ( (iRet = xml_ChildElementCount(lXmlhandle,XMLNM_ICPS_JB_PBOC_INFO)) > 0)
                {
                    memset(sMapbuf,0x00,sizeof(sMapbuf));
                    if((iLen=xml_ExportXMLString(lXmlhandle,sMapbuf,sizeof(sMapbuf),XMLNM_ICPS_JB_PBOC_INFO,1))==FAIL)
                    {
                        fpub_SetMsg(lXmlhandle,MID_ICPS_JB_XMLOP,Fmtmsg(MSG_ICPS_JB_XMLOP,iLen,GETXMLERR));
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        DCIFreeCursor(cur);
                        return COMPRET_FAIL;
                    }
                    LOG(LM_DEBUG,Fmtmsg("export len[%d]", iLen ),"INFO")
                }
                        
                LOG(LM_STD, Fmtmsg("��ʼ�Ǽ����Ͻ���-������֥����Ϣ��icps_jb_zminfo����[%s]", fpub_GetCompname(lXmlhandle)), "");
                /****************�Ǽǿ�� icps_jb_zminfo  ********************/ 
                iRet1 = fdbop_ins_icps_jb_zminfo(lXmlhandle,&zminfo,sMapbuf);
                if(iRet1<0)
                {
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    DCIRollback;
                    return -1;
                }
                LOG(LM_STD, Fmtmsg("�Ǽ����Ͻ���-������֥����Ϣ��icps_jb_zminfo���ɹ���[%s]", fpub_GetCompname(lXmlhandle)), "");

            }
            /*�ж��Ƿ�����չ��Ϣ---�����ĵ���չ��Ϣ�Ѿ����뵽icps_jb_applyinfo��
            if ( (iRet = xml_ChildElementCount(lXmlhandle,XMLNM_ICPS_JB_EXT_INFO)) > 0)
            {
            }
            *******************/
        }
        else
        {
            LOG(LM_STD, Fmtmsg("��icps_jb_applyinfo�������Ѵ��ڣ������ظ���⣡[%s]", fpub_GetCompname(lXmlhandle)), "");
			/*����С΢ƽ̨����������ˮ��*/
        }
    }
    else if (0 == strcmp(trace_code,"702515"))  /*���·�������ȷ��*/
    {
        ICPS_JB_PSTRCOPY(resultinfo.ptrq,ptrq);
        ICPS_JB_PSTRCOPY(resultinfo.ptlsh,ptlsh);
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_VERSION,resultinfo.version,"�汾��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_APPID,resultinfo.appid,"ϵͳ��ʶ");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_FUNCTION,resultinfo.function,"���ױ���");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_REQTIMEZONE,resultinfo.reqtimezone,"���ͷ�����ʱ��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_REQTIME,resultinfo.reqtime,"���ķ���ʱ��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_REQMSGID,resultinfo.reqmsgid,"������Ψһ��ʾ");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_SIGNTYPE,resultinfo.signtype,"ǩ���㷨����");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_INPUTCHARSET,resultinfo.inputcharset,"�����ַ�����");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_RESERVE,resultinfo.reserve,"Ԥ����");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_APPLYNO,resultinfo.applyno,"���뵥��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_CERTTYPE,resultinfo.certtype,"֤������");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_CERTNO,resultinfo.certno,"֤������");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_NAME,resultinfo.name,"����");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESULT_PLATFORMACCESS,resultinfo.platformaccess,"��������������Ƿ�ͨ��");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_PLATFORMREFUSEREASON,resultinfo.platformrefusereaso,"��������������Ƿ�ͨ��");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_PLATFORMADMIT,resultinfo.platformadmit,"���ͨ����������������");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_PLATFORMRATE,resultinfo.platformrate,"���ͨ���������������������");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_RISKRATING,resultinfo.riskrating,"��������");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_SOLVENCYRATINGS,resultinfo.solvencyratings,"��ծ��������");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_CHANGERESULTREASON,resultinfo.changeresultreason,"��ȡ����۱��ԭ��");
        /****************�Ǽǿ�� icps_jb_resultinfo  ********************/ 
        memset(sSql, 0x00, sizeof(sSql));
        snprintf(sSql, sizeof(sSql), "select * from icps_jb_resultinfo where applyno='%s'",resultinfo.applyno);
        LOG(LM_STD,Fmtmsg("��ѯ�Ƿ���Ҫ�ݵȷ���->sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));

        if ((iRet1 =sql_CountSql(sSql)) < 1)
        {    
            LOG(LM_STD, Fmtmsg("��ʼ�Ǽ����Ͻ���-����ȷ�����󵥱�icps_jb_resultinfo����[%s]", fpub_GetCompname(lXmlhandle)), "");
            iRet1 = fdbop_ins_icps_jb_resultinfo(lXmlhandle,&resultinfo);
            if(iRet1<0)
            {
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                return -1;
            }
            LOG(LM_STD, Fmtmsg("�Ǽ����Ͻ���-����ȷ�����󵥱�icps_jb_resultinfo���ɹ���[%s]", fpub_GetCompname(lXmlhandle)), "");
            /*�ж��Ƿ������������չ��Ϣ*/
            if ( (iRet = xml_ChildElementCount(lXmlhandle,XMLNM_ICPS_JB_EXT_INFO)) > 0)
            {
                ICPS_JB_PSTRCOPY(extinfo.ptrq,ptrq);
                ICPS_JB_PSTRCOPY(extinfo.ptlsh,ptlsh);
                ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_REQMSGID,extinfo.reqmsgid,"������Ψһ��ʾ");
                ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLYNO,extinfo.applyno,"���뵥��");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_ISPLATADM,extinfo.isplatadm,"ƽ̨���Ƿ�׼��");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_PLATUNADMREASON,extinfo.platunadmreason,"ƽ̨����׼��ԭ��");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_PLATCREDITAMT,extinfo.platcreditamt,"ƽ̨�����Ŷ��");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_ISJBPRECREDITCUST,extinfo.isjbprecreditcust,"�Ƿ����Ԥ���ſͻ�");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_LOANRATE,extinfo.loanrate,"��������");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_PERIOD,extinfo.period,"��Ʒ����");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_REPAYTYPE,extinfo.repaytype,"���ʽ");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_RISKLEVEL,extinfo.risklevel,"��������");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_REPAYABILITYLVL,extinfo.repayabilitylvl,"��ծ��������");
                ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_EXT_CHANGEREASON,extinfo.changereason,"����ԭ����");
                /****************�Ǽǿ�� icps_jb_extinfo  ********************/ 
                LOG(LM_STD, Fmtmsg("��ʼ�Ǽ����Ͻ���-�������н����Ϣ��icps_jb_extinfo����[%s]", fpub_GetCompname(lXmlhandle)), "");
                iRet1 = fdbop_ins_icps_jb_extinfo(lXmlhandle,&extinfo);
                if(iRet1<0)
                {
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    DCIRollback;
                    return -1;
                }
                LOG(LM_STD, Fmtmsg("�Ǽ����Ͻ���-�������н����Ϣ��icps_jb_extinfo���ɹ���[%s]", fpub_GetCompname(lXmlhandle)), "");
            }
        }
        else
        {
            LOG(LM_STD, Fmtmsg("��icps_jb_resultinfo�������Ѵ��ڣ������ظ���⣡[%s]", fpub_GetCompname(lXmlhandle)), "");
        }

    }

    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

    return 0;

}
/************************************************************************
��̬�����������
�����������:ICPS_JB_UPDATE_REQ
�������:ICPS_JB_UPDATE_REQ
�������: ���Ͻ��½����¼����
��������б�
    ���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
    ���״̬��          ���˵��
    -9999               ȱʡ
    0                   �ɹ�

************************************************************************/
IRESULT ICPS_JB_UPDATE_REQ(HXMLTREE lXmlhandle)
{
    int    iParas;    
    int    iRet=0;    
    int    iRet1 = 0;
    int    iNum=0;
    int    iNum1=0;
    char   stmp[512];
    char   ptrq[8+1];
    char   ptlsh[10+1];
    char   systime[6+1];
    char   jydm[12+1];
    
    
    ST_ICPS_JB_APPLYINFO applyinfo; /*����������Ϣ */
    ST_ICPS_JB_RESULTINFO resultinfo;  /*����������Ϣ */
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("���Ͻ��¸��´������[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "")
    
    DCIBegin();   /**��ʼ����**/
    memset(jydm,0x00,sizeof(jydm));
    COMP_SOFTGETXML("/pub/jydm", jydm); /*���״��� */
    /*ƽ̨����+ƽ̨��ˮ��*/
    memset(ptrq,0x00,sizeof(ptrq));
    memset(ptlsh,0x00,sizeof(ptlsh));
    COMP_SOFTGETXML(XMLNM_ICPS_JB_PTRQ,ptrq);
    COMP_SOFTGETXML(XMLNM_ICPS_JB_PTLSH,ptlsh);
    /*ʱ��*/
    memset(systime,0x00,sizeof(systime));
    memset(stmp,0x00,sizeof(stmp));
    COMP_SOFTGETXML(XMLNM_ICPS_JB_SYSTIME,stmp);      
    memcpy(systime,stmp,sizeof(systime)-1);
    
    if (0 == strcmp(jydm,"702513")) /*�����ڲ������������*/
    {
        memset(&applyinfo,0x00,sizeof(applyinfo));
        ICPS_JB_PSTRCOPY(applyinfo.reqdate,ptrq);
        ICPS_JB_PSTRCOPY(applyinfo.reqtime1,systime);
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_REQMSGID,applyinfo.reqmsgid,"������Ψһ��ʾ");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLYNO,applyinfo.applyno,"���뵥��");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_ISADMIT,applyinfo.isadmit,"�Ƿ��Ƽ�׼��");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_CREDITNO,applyinfo.creditno,"���ű��");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_CREDITAMT,applyinfo.creditamt,"�Ƽ�׼��ʱ���Ƽ��Ķ��");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_CREDITRATE,applyinfo.creditrate,"�Ƽ�׼��ʱ���Ƽ�������");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_REFUSECODE,applyinfo.refusecode,"�Ƽ��ܾ�ʱ���ܾ���");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_REFUSEMSG,applyinfo.refusemsg,"�Ƽ��ܾ�ʱ���ܾ�ԭ��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_APPLYSTAT,applyinfo.applystat,"��������״̬");
        LOG(LM_STD, Fmtmsg("��ʼ�������Ͻ���-����������Ϣ��icps_jb_applyinfo����[%s]", fpub_GetCompname(lXmlhandle)), "");
        iRet =fdbop_upd_icps_jb_applyinfo_702513(lXmlhandle,&applyinfo);
        if(iRet<0)
        {
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return -1;
        }
        LOG(LM_STD, Fmtmsg("�������Ͻ���-����������Ϣ��-���ڳ���icps_jb_applyinfo���ɹ���[%s]", fpub_GetCompname(lXmlhandle)), "");
    }
    else if (0 == strcmp(jydm,"702514")) /*���з������Ž��*/
    {
        memset(&applyinfo,0x00,sizeof(applyinfo));
        ICPS_JB_PSTRCOPY(applyinfo.respdate,ptrq);
        ICPS_JB_PSTRCOPY(applyinfo.resptime,systime);
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_REQMSGID,applyinfo.reqmsgid,"������Ψһ��ʾ");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLYNO,applyinfo.applyno,"���뵥��");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESPCODE,applyinfo.respcode,"������Ӧ��");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESPMSG,applyinfo.respmsg,"������Ӧ��Ϣ");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_APPLY_RETRY,applyinfo.retry,"�Ƿ���Ҫ����");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLY_RESULTSTAT,applyinfo.resultstat,"���󷵻�״̬��");
        LOG(LM_STD, Fmtmsg("��ʼ�������Ͻ���-����������Ϣ��-���ϳ��󷵻ء�icps_jb_applyinfo����[%s]", fpub_GetCompname(lXmlhandle)), "");
        iRet =fdbop_upd_icps_jb_applyinfo_702514(lXmlhandle,&applyinfo);
        if(iRet<0)
        {
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return -1;
        }
        LOG(LM_STD, Fmtmsg("�������Ͻ���-����������Ϣ��icps_jb_applyinfo���ɹ���[%s]", fpub_GetCompname(lXmlhandle)), "");
    }
    else if (0 == strcmp(jydm,"702515")) /*���·�������ȷ��*/
    {
        memset(&resultinfo,0x00,sizeof(resultinfo));
        ICPS_JB_PSTRCOPY(resultinfo.ptrq,ptrq);
        ICPS_JB_PSTRCOPY(resultinfo.ptlsh,ptlsh);
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_REQMSGID,resultinfo.reqmsgid,"������Ψһ��ʾ");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_APPLYNO,resultinfo.applyno,"���뵥��");
        ICPS_JB_GETXMLSTR_NOTNULL(XMLNM_ICPS_JB_RESPCODE,resultinfo.resultcode,"��Ӧ��");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESPMSG,resultinfo.resultmsg,"��Ӧ����");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_ISADMIT,resultinfo.isadmit,"�Ƿ��Ƽ�׼��");
        ICPS_JB_GETXMLSTR_NULL(XMLNM_ICPS_JB_RESULT_ADMITMSG,resultinfo.admitmsg,"׼��ԭ��");
        iRet =fdbop_upd_icps_jb_resultinfo(lXmlhandle,&resultinfo);
        LOG(LM_STD, Fmtmsg("��ʼ�������Ͻ���-����������Ϣ��icps_jb_applyinfo����[%s]", fpub_GetCompname(lXmlhandle)), "");
        iRet =fdbop_upd_icps_jb_resultinfo(lXmlhandle,&resultinfo);
        if(iRet<0)
        {
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            return -1;
        }
        LOG(LM_STD, Fmtmsg("�������Ͻ���-����������Ϣ��icps_jb_applyinfo���ɹ���[%s]", fpub_GetCompname(lXmlhandle)), "");
    }
    
    DCICommit();
    
    LOG(LM_STD, Fmtmsg("���Ͻ��¸��´������[%s]ִ�гɹ�", fpub_GetCompname(lXmlhandle)), "")
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

    return 0;

}
