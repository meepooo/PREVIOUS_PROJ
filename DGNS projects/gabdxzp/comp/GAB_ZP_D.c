/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:��������թƭǰ��ϵͳ
��    ��:V2.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:ORACLE\INFORMIX\DB2
�ļ�����:GAB_ZP_D.c
�ļ�����:��������թƭǰ��ϵͳ ������ģ��ҵ���
�� Ŀ ��:
�� �� Ա:
��������:2016-01-18
��    ��:
�޸�����:
*********************************************************************/
/*  
�޸ļ�¼
�޸�����:
�޸�����:
�޸���:
*/

#include "gabdxzp_head.h"
#include "gabdxzp_alltables.h"



/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_djxj
   ��������:  ��ѯ����թƭ���������
   ��������:  *pst_gab_dxzp_djxj  ����թƭ���������ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_djxj(HXMLTREE lXmlhandle,GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_djxj where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_djxj->ywsqbh,pst_gab_dxzp_djxj->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_DJXJ, NUMELE(SD_GAB_DXZP_DJXJ), pst_gab_dxzp_djxj );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ���������ʧ��,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_djxj->ywsqbh,pst_gab_dxzp_djxj->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�����������ؼ�¼,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_djxj->ywsqbh,pst_gab_dxzp_djxj->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_djxj
   ��������:  �Ǽǵ���թƭ���������
   ��������:  *pst_gab_dxzp_djxj  ����թƭ���������ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_djxj(HXMLTREE lXmlhandle,GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_djxj", SD_GAB_DXZP_DJXJ, NUMELE(SD_GAB_DXZP_DJXJ), pst_gab_dxzp_djxj, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ���������ʧ��,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_djxj->ywsqbh,pst_gab_dxzp_djxj->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}



/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_sajb
   ��������:  ��ѯ����թƭ�永�ٱ���
   ��������:  *pst_gab_dxzp_sajb  ����թƭ�永�ٱ���ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_sajb(HXMLTREE lXmlhandle,GAB_DXZP_SAJB *pst_gab_dxzp_sajb)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_sajb where csbwlsh='%s'", pst_gab_dxzp_sajb->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SAJB, NUMELE(SD_GAB_DXZP_SAJB), pst_gab_dxzp_sajb );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�永�ٱ���ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_sajb->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�永�ٱ�����ؼ�¼,csbwlsh[%s]", 
           pst_gab_dxzp_sajb->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_sajb
   ��������:  �Ǽǵ���թƭ�永�ٱ���
   ��������:  *pst_gab_dxzp_sajb  ����թƭ�永�ٱ���ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_sajb(HXMLTREE lXmlhandle,GAB_DXZP_SAJB *pst_gab_dxzp_sajb)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_sajb", SD_GAB_DXZP_SAJB, NUMELE(SD_GAB_DXZP_SAJB), pst_gab_dxzp_sajb, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�永�ٱ���ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_sajb->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}





/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_sazh
   ��������:  ��ѯ����թƭ�永�˻���
   ��������:  *pst_gab_dxzp_sazh  ����թƭ�永�˻���ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_sazh(HXMLTREE lXmlhandle,GAB_DXZP_SAZH *pst_gab_dxzp_sazh)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_sazh where csbwlsh='%s'", pst_gab_dxzp_sazh->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SAZH, NUMELE(SD_GAB_DXZP_SAZH), pst_gab_dxzp_sazh );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�永�˻���ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_sazh->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�永�˻�����ؼ�¼,csbwlsh[%s]", 
            pst_gab_dxzp_sazh->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_sazh
   ��������:  �Ǽǵ���թƭ�永�˻���
   ��������:  *pst_gab_dxzp_sazh  ����թƭ�永�˻���ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_sazh(HXMLTREE lXmlhandle,GAB_DXZP_SAZH *pst_gab_dxzp_sazh)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_sazh", SD_GAB_DXZP_SAZH, NUMELE(SD_GAB_DXZP_SAZH), pst_gab_dxzp_sazh, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�永�˻���ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_sazh->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_sbxx
   ��������:  ����թƭ�ϱ���Ϣ��
   ��������:  *pst_gab_dxzp_sbxx  ����թƭ�ϱ���Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_sbxx(HXMLTREE lXmlhandle,GAB_DXZP_SBXX *pst_gab_dxzp_sbxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_sbxx where csbwlsh='%s'", pst_gab_dxzp_sbxx->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SBXX, NUMELE(SD_GAB_DXZP_SBXX), pst_gab_dxzp_sbxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�ϱ���Ϣ��ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_sbxx->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�ϱ���Ϣ����ؼ�¼,csbwlsh[%s]", 
            pst_gab_dxzp_sbxx->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_sbxx
   ��������:  ����թƭ�ϱ���Ϣ��
   ��������:  *pst_gab_dxzp_sbxx ����թƭ�ϱ���Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_sbxx(HXMLTREE lXmlhandle,GAB_DXZP_SBXX *pst_gab_dxzp_sbxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_sbxx", SD_GAB_DXZP_SBXX, NUMELE(SD_GAB_DXZP_SBXX), pst_gab_dxzp_sbxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("����թƭ�ϱ���Ϣ��ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_sbxx->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_sfsa
   ��������:  ��ѯ����թƭ����永��
   ��������:  *pst_gab_dxzp_sfsa  ����թƭ����永��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_sfsa(HXMLTREE lXmlhandle,GAB_DXZP_SFSA *pst_gab_dxzp_sfsa)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_sfsa where csbwlsh='%s'", pst_gab_dxzp_sfsa->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SFSA, NUMELE(SD_GAB_DXZP_SFSA), pst_gab_dxzp_sfsa );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ����永��ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_sfsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ����永����ؼ�¼,csbwlsh[%s]", 
            pst_gab_dxzp_sfsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_sfsa
   ��������:  ����թƭ����永��
   ��������:  *pst_gab_dxzp_sfsa  ����թƭ����永��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_sfsa(HXMLTREE lXmlhandle,GAB_DXZP_SFSA *pst_gab_dxzp_sfsa)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_sfsa", SD_GAB_DXZP_SFSA, NUMELE(SD_GAB_DXZP_SFSA), pst_gab_dxzp_sfsa, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ����永��ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_sfsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}



/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_xdxx
   ��������:  ��ѯ����թƭ�´���Ϣ��
   ��������:  *pst_gab_dxzp_xdxx  ����թƭ�´���Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_xdxx(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_xdxx where ywsqbh='%s'", pst_gab_dxzp_xdxx->ywsqbh);
   
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_XDXX, NUMELE(SD_GAB_DXZP_XDXX), pst_gab_dxzp_xdxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�´���Ϣ��ʧ��,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�´���Ϣ����ؼ�¼,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_xdxx
   ��������:  �Ǽǵ���թƭ�´���Ϣ��
   ��������:  *pst_gab_dxzp_xdxx  ����թƭ�´���Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_xdxx(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_xdxx", SD_GAB_DXZP_XDXX, NUMELE(SD_GAB_DXZP_XDXX), pst_gab_dxzp_xdxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�´���Ϣ��ʧ��,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}

/*****************************************************
   ��������:  fdbop_upd_gab_dxzp_xdxx
   ��������:  ���µ���թƭ�´���Ϣ��
   ��������:  *pst_gab_dxzp_xdxx  ����թƭ�´���Ϣ��ṹ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_gab_dxzp_xdxx(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_xdxx set zxjg='%s', respcode='%s', respmsg='%s', qqdzt='%s' where ywsqbh='%s'", 
        pst_gab_dxzp_xdxx->zxjg, pst_gab_dxzp_xdxx->respcode, 
        pst_gab_dxzp_xdxx->respmsg,pst_gab_dxzp_xdxx->qqdzt,
        pst_gab_dxzp_xdxx->ywsqbh);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_xdxx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("���µ���թƭ�´���Ϣ��ʧ��,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�´���Ϣ����ؼ�¼,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   ��������:  fdbop_upd_gab_dxzp_xdxx_aftCallHost
   ��������:  ���µ���թƭ�´���Ϣ��
   ��������:  *pst_gab_dxzp_xdxx  ����թƭ�´���Ϣ��ṹ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_gab_dxzp_xdxx_aftCallHost(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx, char *pOriQqdZt)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    /*alter clrq,clsj by liukq 20160328 20160330 tjhxcs+1 add ywydm,ywydxx 20160408 BEGIN*/
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_xdxx set zxjg='%s', respcode='%s', respmsg='%s', zjrq='%s', zjlsh='%s', sbpch='%s', qqdzt='%s',clrq='%s',clsj='%s',tjhxcs=tjhxcs+1,ywydm='%s',ywydxx='%s'", 
        pst_gab_dxzp_xdxx->zxjg, pst_gab_dxzp_xdxx->respcode, 
        pst_gab_dxzp_xdxx->respmsg,
        pst_gab_dxzp_xdxx->zjrq, pst_gab_dxzp_xdxx->zjlsh,
        pst_gab_dxzp_xdxx->sbpch, pst_gab_dxzp_xdxx->qqdzt,
        pst_gab_dxzp_xdxx->clrq, pst_gab_dxzp_xdxx->clsj,pst_gab_dxzp_xdxx->ywydm,pst_gab_dxzp_xdxx->ywydxx);
  
    if( '\0' != pst_gab_dxzp_xdxx->dzxh[0] || 0 != strlen(pst_gab_dxzp_xdxx->dzxh) )
    	{
    		sprintf(sSql,"%s,dzxh ='%s'",sSql,pst_gab_dxzp_xdxx->dzxh);
    	}
    
    sprintf(sSql,"%s  where ywsqbh='%s' and qqdzt='%s'",sSql, pst_gab_dxzp_xdxx->ywsqbh, pOriQqdZt);
    /*alter by liukq 20160328 END*/
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_xdxx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("���µ���թƭ�´���Ϣ��ʧ��,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�´���Ϣ����ؼ�¼,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   ��������:  fdbop_upd_gab_dxzp_busi
   ��������:  ���µ���թƭ�ֱ���Ϣ
   ��������:  *pst_gab_dxzp_xdxx  ����թƭ�´���Ϣ��ṹ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_gab_dxzp_busi(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx, char *psTableName)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_%s set zxjg='%s', respcode='%s', respmsg='%s' where ywsqbh='%s' and rwxh=1", 
        psTableName,
        pst_gab_dxzp_xdxx->zxjg, pst_gab_dxzp_xdxx->respcode, pst_gab_dxzp_xdxx->respmsg,
        pst_gab_dxzp_xdxx->ywsqbh);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_%s.sql[%s]", psTableName, sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("���µ���թƭ�´���Ϣ��ʧ��,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�´���Ϣ����ؼ�¼,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_upd_gab_dxzp_xdxx_qqdzt
   ��������:  ���µ���թƭ�´���Ϣ������״̬
   ��������:  *pst_gab_dxzp_xdxx  ����թƭ�´���Ϣ��ṹ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_gab_dxzp_xdxx_qqdzt(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx, char *psOriQqdZt)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_xdxx set qqdzt='%s' where ywsqbh='%s' and qqdzt='%s'", 
        pst_gab_dxzp_xdxx->qqdzt,
        pst_gab_dxzp_xdxx->ywsqbh, psOriQqdZt);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_xdxx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("���µ���թƭ�´���Ϣ��ʧ��,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�´���Ϣ����ؼ�¼,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   ��������:  fdbop_upd_gab_dxzp_xdxx_ywlsh
   ��������:  ���µ���թƭ�´���Ϣ������״̬
   ��������:  *pst_gab_dxzp_xdxx  ����թƭ�´���Ϣ��ṹ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_gab_dxzp_xdxx_ywlsh(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx, char *psOriQqdZt)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_xdxx set ywrq='%s', ywlsh='%s', qqdzt='%s' where ywsqbh='%s' and qqdzt='%s'", 
        pst_gab_dxzp_xdxx->ywrq,pst_gab_dxzp_xdxx->ywlsh,
        pst_gab_dxzp_xdxx->qqdzt,
        pst_gab_dxzp_xdxx->ywsqbh, psOriQqdZt);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_xdxx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("���µ���թƭ�´���Ϣ��ʧ��,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�´���Ϣ����ؼ�¼,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_yckk
   ��������:  ��ѯ����թƭ�쳣������
   ��������:  *pst_gab_dxzp_yckk  ����թƭ�쳣������ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_yckk(HXMLTREE lXmlhandle,GAB_DXZP_YCKK *pst_gab_dxzp_yckk)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_yckk where csbwlsh='%s'", pst_gab_dxzp_yckk->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_YCKK, NUMELE(SD_GAB_DXZP_YCKK), pst_gab_dxzp_yckk );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�쳣������ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_yckk->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�쳣��������ؼ�¼,csbwlsh[%s]", 
            pst_gab_dxzp_yckk->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_yckk
   ��������:  �Ǽǵ���թƭ�쳣������
   ��������:  *pst_gab_dxzp_yckk  ����թƭ�쳣������ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_yckk(HXMLTREE lXmlhandle,GAB_DXZP_YCKK *pst_gab_dxzp_yckk)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_yckk", SD_GAB_DXZP_YCKK, NUMELE(SD_GAB_DXZP_YCKK), pst_gab_dxzp_yckk, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�쳣������ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_yckk->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_ycsj
   ��������:  ��ѯ����թƭ�쳣�¼���
   ��������:  *pst_gab_dxzp_ycsj  ����թƭ�쳣�¼���ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_ycsj(HXMLTREE lXmlhandle,GAB_DXZP_YCSJ *pst_gab_dxzp_ycsj)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_ycsj where csbwlsh='%s'", pst_gab_dxzp_ycsj->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_YCSJ, NUMELE(SD_GAB_DXZP_YCSJ), pst_gab_dxzp_ycsj );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�쳣�¼���ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_ycsj->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�쳣�¼�����ؼ�¼,csbwlsh[%s]", 
            pst_gab_dxzp_ycsj->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_ycsj
   ��������:  �Ǽǵ���թƭ�쳣�¼���
   ��������:  *pst_gab_dxzp_ycsj  ����թƭ�쳣�¼���ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_ycsj(HXMLTREE lXmlhandle,GAB_DXZP_YCSJ *pst_gab_dxzp_ycsj)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_ycsj", SD_GAB_DXZP_YCSJ, NUMELE(SD_GAB_DXZP_YCSJ), pst_gab_dxzp_ycsj, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�쳣�¼���ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_ycsj->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_zhsa
   ��������:  ��ѯ����թƭ�˻��永��
   ��������:  *pst_gab_dxzp_zhsa ����թƭ�˻��永��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_zhsa(HXMLTREE lXmlhandle,GAB_DXZP_ZHSA *pst_gab_dxzp_zhsa)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_zhsa where csbwlsh='%s'", pst_gab_dxzp_zhsa->csbwlsh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_ZHSA, NUMELE(SD_GAB_DXZP_ZHSA), pst_gab_dxzp_zhsa );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�˻��永��ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_zhsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�˻��永����ؼ�¼,csbwlsh[%s]", 
            pst_gab_dxzp_zhsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_zhsa
   ��������:  �Ǽǵ���թƭ�˻��永��
   ��������:  *pst_gab_dxzp_zhsa  ����թƭ�˻��永��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_zhsa(HXMLTREE lXmlhandle,GAB_DXZP_ZHSA *pst_gab_dxzp_zhsa)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_zhsa", SD_GAB_DXZP_ZHSA, NUMELE(SD_GAB_DXZP_ZHSA), pst_gab_dxzp_zhsa, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�˻��永��ʧ��,csbwlsh[%s]", 
            pst_gab_dxzp_zhsa->csbwlsh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}




/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_ztcx
   ��������:  ��ѯ����թƭ�����ѯ��
   ��������:  *pst_gab_dxzp_ztcx  ����թƭ�����ѯ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_ztcx(HXMLTREE lXmlhandle,GAB_DXZP_ZTCX *pst_gab_dxzp_ztcx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_ztcx where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_ztcx->ywsqbh,pst_gab_dxzp_ztcx->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_ZTCX, NUMELE(SD_GAB_DXZP_ZTCX), pst_gab_dxzp_ztcx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�����ѯ��ʧ��,ywsqbh[%s],rwxh=[%d]", 
            pst_gab_dxzp_ztcx->ywsqbh,pst_gab_dxzp_ztcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�����ѯ����ؼ�¼,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_ztcx->ywsqbh,pst_gab_dxzp_ztcx->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_ztcx
   ��������:  �Ǽǵ���թƭ�����ѯ��
   ��������:  *pst_gab_dxzp_ztcx  ����թƭ�����ѯ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_ztcx(HXMLTREE lXmlhandle,GAB_DXZP_ZTCX *pst_gab_dxzp_ztcx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_ztcx", SD_GAB_DXZP_ZTCX, NUMELE(SD_GAB_DXZP_ZTCX), pst_gab_dxzp_ztcx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�����ѯ��ʧ��,ywsqbh[%s],rwxh=[%d]", 
            pst_gab_dxzp_ztcx->ywsqbh,pst_gab_dxzp_ztcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_dtcx
   ��������:  ��ѯ����թƭ��̬��ѯ��
   ��������:  *pst_gab_dxzp_dtcx  ����թƭ��̬��ѯ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_dtcx(HXMLTREE lXmlhandle,GAB_DXZP_DTCX *pst_gab_dxzp_dtcx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_dtcx where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_dtcx->ywsqbh,pst_gab_dxzp_dtcx->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_DTCX, NUMELE(SD_GAB_DXZP_DTCX), pst_gab_dxzp_dtcx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ��̬��ѯ��ʧ��,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_dtcx->ywsqbh,pst_gab_dxzp_dtcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ��̬��ѯ����ؼ�¼,ywsqbh[%s],rwxh[%d]", 
           pst_gab_dxzp_dtcx->ywsqbh,pst_gab_dxzp_dtcx->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_dtcx
   ��������:  �Ǽǵ���թƭ��̬��ѯ��
   ��������:  *pst_gab_dxzp_dtcx  ����թƭ��̬��ѯ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_dtcx(HXMLTREE lXmlhandle,GAB_DXZP_DTCX *pst_gab_dxzp_dtcx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_dtcx", SD_GAB_DXZP_DTCX, NUMELE(SD_GAB_DXZP_DTCX), pst_gab_dxzp_dtcx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ��̬��ѯ��ʧ��,ywsqbh[%s],rwxh[%d]", 
           pst_gab_dxzp_dtcx->ywsqbh,pst_gab_dxzp_dtcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}

/*****************************************************
   ��������:  fdbop_upd_gab_dxzp_dtcx_qzsj
   ��������:  ���µ���թƭ��̬��ѯ��̬��ѯ��ֹʱ��
   ��������:  *fdbop_upd_gab_dxzp_dtcx  ����թƭ�´���Ϣ��ṹ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_gab_dxzp_dtcx_qzsj(HXMLTREE lXmlhandle,GAB_DXZP_DTCX *pst_gab_dxzp_dtcx)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_dtcx set dtcxqssj='%s',dtcxjzsj='%s' where ywsqbh='%s' and rwxh=%d", 
        pst_gab_dxzp_dtcx->dtcxqssj,pst_gab_dxzp_dtcx->dtcxjzsj,
        pst_gab_dxzp_dtcx->ywsqbh, pst_gab_dxzp_dtcx->rwxh);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_dtcx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("���µ���թƭ��̬��ѯ��ʧ��,ywsqbh[%s]", 
            pst_gab_dxzp_dtcx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ��̬��ѯ����ؼ�¼,ywsqbh[%s]", 
            pst_gab_dxzp_dtcx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_jjzf
   ��������:  ��ѯ����թƭֹ����ֹ��
   ��������:  *pst_gab_dxzp_jjzf ����թƭֹ����ֹ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_jjzf(HXMLTREE lXmlhandle,GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_jjzf where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_JJZF, NUMELE(SD_GAB_DXZP_JJZF), pst_gab_dxzp_jjzf );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭֹ����ֹ��ʧ��,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭֹ����ֹ����ؼ�¼,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_jjzf
   ��������:  �Ǽǵ���թƭֹ����ֹ��
   ��������:  *pst_gab_dxzp_jjzf  ����թƭֹ����ֹ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_jjzf(HXMLTREE lXmlhandle,GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_jjzf", SD_GAB_DXZP_JJZF, NUMELE(SD_GAB_DXZP_JJZF), pst_gab_dxzp_jjzf, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭֹ����ֹ��ʧ��,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}

/*****************************************************
   ��������:  fdbop_upd_gab_dxzp_jjzf
   ��������:  ���µ���թƭֹ����ֹ��
   ��������:  *pst_gab_dxzp_jjzf  ����թƭֹ����ֹ��ṹ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_gab_dxzp_jjzf(HXMLTREE lXmlhandle,GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_jjzf set zxjg='%s', respcode='%s', respmsg='%s', zxqssj='%s', zxjssj='%s', fksm='%s', fkjgmc='%s' where ywsqbh='%s'", 
        pst_gab_dxzp_jjzf->zxjg, pst_gab_dxzp_jjzf->respcode, 
        pst_gab_dxzp_jjzf->respmsg,
        pst_gab_dxzp_jjzf->zxqssj,
        pst_gab_dxzp_jjzf->zxjssj,
        pst_gab_dxzp_jjzf->ywsqbh, pst_gab_dxzp_jjzf->rwxh);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_jjzf.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭֹ����ֹ��ʧ��,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭֹ����ֹ����ؼ�¼,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jjzf->ywsqbh,pst_gab_dxzp_jjzf->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_jymx
   ��������:  ��ѯ����թƭ������ϸ��
   ��������:  *pst_gab_dxzp_jymx  ����թƭ������ϸ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_jymx(HXMLTREE lXmlhandle,GAB_DXZP_JYMX *pst_gab_dxzp_jymx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_jymx where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_jymx->ywsqbh,pst_gab_dxzp_jymx->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_JYMX, NUMELE(SD_GAB_DXZP_JYMX), pst_gab_dxzp_jymx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ������ϸ��ʧ��,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jymx->ywsqbh,pst_gab_dxzp_jymx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ������ϸ����ؼ�¼,ywsqbh[%s],rwxh[%d]", 
            pst_gab_dxzp_jymx->ywsqbh,pst_gab_dxzp_jymx->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_jymx
   ��������:  �Ǽǵ���թƭ������ϸ��
   ��������:  *pst_gab_dxzp_jymx  ����թƭ������ϸ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_jymx(HXMLTREE lXmlhandle,GAB_DXZP_JYMX *pst_gab_dxzp_jymx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_jymx", SD_GAB_DXZP_JYMX, NUMELE(SD_GAB_DXZP_JYMX), pst_gab_dxzp_jymx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ������ϸ��ʧ��,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_jymx->ywsqbh,pst_gab_dxzp_jymx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}




/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_qhcx
   ��������:  ��ѯ����թƭȫ����ѯ��
   ��������:  *pst_gab_dxzp_qhcx  ����թƭȫ����ѯ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_qhcx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX *pst_gab_dxzp_qhcx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_qhcx where ywsqbh='%s' and rwxh=%d", pst_gab_dxzp_qhcx->ywsqbh,pst_gab_dxzp_qhcx->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_QHCX, NUMELE(SD_GAB_DXZP_QHCX), pst_gab_dxzp_qhcx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭȫ����ѯ��ʧ��,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_qhcx->ywsqbh,pst_gab_dxzp_qhcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭȫ����ѯ����ؼ�¼,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_qhcx->ywsqbh,pst_gab_dxzp_qhcx->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_qhcx
   ��������:  �Ǽǵ���թƭȫ����ѯ��
   ��������:  *pst_gab_dxzp_qhcx ����թƭȫ����ѯ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_qhcx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX *pst_gab_dxzp_qhcx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_qhcx", SD_GAB_DXZP_QHCX, NUMELE(SD_GAB_DXZP_QHCX), pst_gab_dxzp_qhcx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭȫ����ѯ��ʧ��,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_qhcx->ywsqbh,pst_gab_dxzp_qhcx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}




/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_zhxx_zhjyxx
   ��������:  ��ѯ����թƭ �˻���Ϣ_�˺Ž�����Ϣ
   ��������:  *pst_gab_dxzp_zhxx_zhjyxx  ����թƭ�˻���Ϣ_�˺Ž�����Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_zhxx_zhjyxx(HXMLTREE lXmlhandle,GAB_DXZP_ZHXX_ZHJYXX *pst_gab_dxzp_zhxx_zhjyxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_zhxx_zhjyxx where ywsqbh='%s' and rwxh=%d and zhjyxh='%s'", pst_gab_dxzp_zhxx_zhjyxx->ywsqbh,pst_gab_dxzp_zhxx_zhjyxx->rwxh,pst_gab_dxzp_zhxx_zhjyxx->zhjyxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_ZHXX_ZHJYXX, NUMELE(SD_GAB_DXZP_ZHXX_ZHJYXX), pst_gab_dxzp_zhxx_zhjyxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�˻���Ϣ_�˺Ž�����Ϣ��ʧ��,ywsqbh[%s],rwxh[%d],zhjyxh[%s]", 
             pst_gab_dxzp_zhxx_zhjyxx->ywsqbh,pst_gab_dxzp_zhxx_zhjyxx->rwxh,pst_gab_dxzp_zhxx_zhjyxx->zhjyxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�˻���Ϣ_�˺Ž�����Ϣ����ؼ�¼,ywsqbh[%s],rwxh[%d],zhjyxh[%s]", 
             pst_gab_dxzp_zhxx_zhjyxx->ywsqbh,pst_gab_dxzp_zhxx_zhjyxx->rwxh,pst_gab_dxzp_zhxx_zhjyxx->zhjyxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_zhxx_zhjyxx
   ��������:  �Ǽǵ���թƭ�˻���Ϣ_�˺Ž�����Ϣ��
   ��������:  *pst_gab_dxzp_zhxx_zhjyxx ����թƭ�˻���Ϣ_�˺Ž�����Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_zhxx_zhjyxx(HXMLTREE lXmlhandle,GAB_DXZP_ZHXX_ZHJYXX *pst_gab_dxzp_zhxx_zhjyxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_zhxx_zhjyxx", SD_GAB_DXZP_ZHXX_ZHJYXX, NUMELE(SD_GAB_DXZP_ZHXX_ZHJYXX), pst_gab_dxzp_zhxx_zhjyxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�˻���Ϣ_�˺Ž�����Ϣ��ʧ��,ywsqbh[%s],rwxh[%d],zhjyxh[%s]", 
             pst_gab_dxzp_zhxx_zhjyxx->ywsqbh,pst_gab_dxzp_zhxx_zhjyxx->rwxh,pst_gab_dxzp_zhxx_zhjyxx->zhjyxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}














/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_zhjbxx_zhxx
   ��������:  ��ѯ����թƭ �˻�������Ϣ_�˺���Ϣ
   ��������:  *pst_gab_dxzp_zhjbxx_zhxx  ����թƭ�˻�������Ϣ_�˺���Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_zhjbxx_zhxx(HXMLTREE lXmlhandle,GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_zhjbxx_zhxx where ywsqbh='%s' and rwxh=%d and zhxh='%s'", pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,pst_gab_dxzp_zhjbxx_zhxx->rwxh,pst_gab_dxzp_zhjbxx_zhxx->zhxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_ZHJBXX_ZHXX, NUMELE(SD_GAB_DXZP_ZHJBXX_ZHXX), pst_gab_dxzp_zhjbxx_zhxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�˻�������Ϣ_�˺���Ϣ��ʧ��,ywsqbh[%s],rwxh[%d],zhxh[%s]", 
             pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,pst_gab_dxzp_zhjbxx_zhxx->rwxh,pst_gab_dxzp_zhjbxx_zhxx->zhxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�˻�������Ϣ_�˺���Ϣ����ؼ�¼,ywsqbh[%s],rwxh[%d],zhxh[%s]", 
             pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,pst_gab_dxzp_zhjbxx_zhxx->rwxh,pst_gab_dxzp_zhjbxx_zhxx->zhxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_zhjbxx_zhxx
   ��������:  �Ǽǵ���թƭ�˻�������Ϣ_�˺���Ϣ��
   ��������:  *pst_gab_dxzp_zhjbxx_zhxx ����թƭ�˻�������Ϣ_�˺���Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_zhjbxx_zhxx(HXMLTREE lXmlhandle,GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_zhjbxx_zhxx", SD_GAB_DXZP_ZHJBXX_ZHXX, NUMELE(SD_GAB_DXZP_ZHJBXX_ZHXX), pst_gab_dxzp_zhjbxx_zhxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�˻�������Ϣ_�˺���Ϣ��ʧ��,ywsqbh[%s],rwxh[%d],zhxh[%s]", 
             pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,pst_gab_dxzp_zhjbxx_zhxx->rwxh,pst_gab_dxzp_zhjbxx_zhxx->zhxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}













/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_jymx_zhjbxx
   ��������:  ��ѯ����թƭ ������ϸ_�˻�������Ϣ
   ��������:  *pst_gab_dxzp_jymx_zhjbxx  ����թƭ������ϸ_�˻�������Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_jymx_zhjbxx(HXMLTREE lXmlhandle,GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_jymx_zhjbxx where ywsqbh='%s' and rwxh=%d ", pst_gab_dxzp_jymx_zhjbxx->ywsqbh,pst_gab_dxzp_jymx_zhjbxx->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_JYMX_ZHJBXX, NUMELE(SD_GAB_DXZP_JYMX_ZHJBXX), pst_gab_dxzp_jymx_zhjbxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ������ϸ_�˻�������Ϣ��ʧ��,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_jymx_zhjbxx->ywsqbh,pst_gab_dxzp_jymx_zhjbxx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ������ϸ_�˻�������Ϣ����ؼ�¼,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_jymx_zhjbxx->ywsqbh,pst_gab_dxzp_jymx_zhjbxx->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_jymx_zhjbxx
   ��������:  �Ǽǵ���թƭ�˻�������ϸ_�˻�������Ϣ��
   ��������:  *pst_gab_dxzp_jymx_zhjbxx ����թƭ������ϸ_�˻�������Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_jymx_zhjbxx(HXMLTREE lXmlhandle,GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_jymx_zhjbxx", SD_GAB_DXZP_JYMX_ZHJBXX, NUMELE(SD_GAB_DXZP_JYMX_ZHJBXX), pst_gab_dxzp_jymx_zhjbxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ������ϸ_�˻�������Ϣ��ʧ��,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_jymx_zhjbxx->ywsqbh,pst_gab_dxzp_jymx_zhjbxx->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


















/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_qhcx_sfqzxx
   ��������:  ��ѯ����թƭ ȫ����ѯ_˾��ǿ����Ϣ
   ��������:  *pst_gab_dxzp_qhcx_sfqzxx  ����թƭȫ����ѯ_˾��ǿ����Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_qhcx_sfqzxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_SFQZXX *pst_gab_dxzp_qhcx_sfqzxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_qhcx_sfqzxx where ywsqbh='%s' and rwxh=%d and csxh='%s'", pst_gab_dxzp_qhcx_sfqzxx->ywsqbh,pst_gab_dxzp_qhcx_sfqzxx->rwxh,pst_gab_dxzp_qhcx_sfqzxx->csxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_QHCX_SFQZXX, NUMELE(SD_GAB_DXZP_QHCX_SFQZXX), pst_gab_dxzp_qhcx_sfqzxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭȫ����ѯ_˾��ǿ����Ϣ��ʧ��,ywsqbh[%s],rwxh[%d],csxh[%s]", 
             pst_gab_dxzp_qhcx_sfqzxx->ywsqbh,pst_gab_dxzp_qhcx_sfqzxx->rwxh,pst_gab_dxzp_qhcx_sfqzxx->csxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭȫ����ѯ_˾��ǿ����Ϣ����ؼ�¼,ywsqbh[%s],rwxh[%d],csxh[%s]", 
             pst_gab_dxzp_qhcx_sfqzxx->ywsqbh,pst_gab_dxzp_qhcx_sfqzxx->rwxh,pst_gab_dxzp_qhcx_sfqzxx->csxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_qhcx_sfqzxx
   ��������:  �Ǽǵ���թƭȫ����ѯ_˾��ǿ����Ϣ��
   ��������:  *pst_gab_dxzp_qhcx_sfqzxx ����թƭȫ����ѯ_˾��ǿ����Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_qhcx_sfqzxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_SFQZXX *pst_gab_dxzp_qhcx_sfqzxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_qhcx_sfqzxx", SD_GAB_DXZP_QHCX_SFQZXX, NUMELE(SD_GAB_DXZP_QHCX_SFQZXX), pst_gab_dxzp_qhcx_sfqzxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭȫ����ѯ_˾��ǿ����Ϣ��ʧ��,ywsqbh[%s],rwxh[%d],csxh[%s]", 
             pst_gab_dxzp_qhcx_sfqzxx->ywsqbh,pst_gab_dxzp_qhcx_sfqzxx->rwxh,pst_gab_dxzp_qhcx_sfqzxx->csxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}











/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_qhcx_zzhxx
   ��������:  ��ѯ����թƭ ȫ����ѯ_���˺���Ϣ
   ��������:  *pst_gab_dxzp_qhcx_zzhxx  ����թƭȫ����ѯ_���˺���Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_qhcx_zzhxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_ZZHXX *pst_gab_dxzp_qhcx_zzhxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_qhcx_zzhxx where ywsqbh='%s' and rwxh=%d and zzhxh='%s'", pst_gab_dxzp_qhcx_zzhxx->ywsqbh,pst_gab_dxzp_qhcx_zzhxx->rwxh,pst_gab_dxzp_qhcx_zzhxx->zzhxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_QHCX_ZZHXX, NUMELE(SD_GAB_DXZP_QHCX_ZZHXX), pst_gab_dxzp_qhcx_zzhxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭȫ����ѯ_���˺���Ϣ��ʧ��,ywsqbh[%s],rwxh[%d],zzhxh[%s]", 
             pst_gab_dxzp_qhcx_zzhxx->ywsqbh,pst_gab_dxzp_qhcx_zzhxx->rwxh,pst_gab_dxzp_qhcx_zzhxx->zzhxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭȫ����ѯ_���˺���Ϣ����ؼ�¼,ywsqbh[%s],rwxh[%d],zzhxh[%s]", 
             pst_gab_dxzp_qhcx_zzhxx->ywsqbh,pst_gab_dxzp_qhcx_zzhxx->rwxh,pst_gab_dxzp_qhcx_zzhxx->zzhxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_qhcx_zzhxx
   ��������:  �Ǽǵ���թƭȫ����ѯ_˾��ǿ����Ϣ��
   ��������:  *pst_gab_dxzp_qhcx_zzhxx ����թƭȫ����ѯ_˾��ǿ����Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_qhcx_zzhxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_ZZHXX *pst_gab_dxzp_qhcx_zzhxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_qhcx_zzhxx", SD_GAB_DXZP_QHCX_ZZHXX, NUMELE(SD_GAB_DXZP_QHCX_ZZHXX), pst_gab_dxzp_qhcx_zzhxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭȫ����ѯ_���˺���Ϣ��ʧ��,ywsqbh[%s],rwxh[%d],zzhxh[%s]", 
             pst_gab_dxzp_qhcx_zzhxx->ywsqbh,pst_gab_dxzp_qhcx_zzhxx->rwxh,pst_gab_dxzp_qhcx_zzhxx->zzhxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}



















/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_qhcx_qlxx
   ��������:  ��ѯ����թƭ ȫ����ѯ_Ȩ������Ϣ
   ��������:  *pst_gab_dxzp_qhcx_qlxx  ����թƭȫ����ѯ_Ȩ������Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_qhcx_qlxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_QLXX *pst_gab_dxzp_qhcx_qlxx)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_qhcx_qlxx where ywsqbh='%s' and rwxh=%d and xh='%s'", pst_gab_dxzp_qhcx_qlxx->ywsqbh,pst_gab_dxzp_qhcx_qlxx->rwxh,pst_gab_dxzp_qhcx_qlxx->xh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_QHCX_QLXX, NUMELE(SD_GAB_DXZP_QHCX_QLXX), pst_gab_dxzp_qhcx_qlxx );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭȫ����ѯ_Ȩ������Ϣ��ʧ��,ywsqbh[%s],rwxh[%d],xh[%s]", 
             pst_gab_dxzp_qhcx_qlxx->ywsqbh,pst_gab_dxzp_qhcx_qlxx->rwxh,pst_gab_dxzp_qhcx_qlxx->xh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭȫ����ѯ_Ȩ������Ϣ����ؼ�¼,ywsqbh[%s],rwxh[%d],xh[%s]", 
             pst_gab_dxzp_qhcx_qlxx->ywsqbh,pst_gab_dxzp_qhcx_qlxx->rwxh,pst_gab_dxzp_qhcx_qlxx->xh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_qhcx_qlxx
   ��������:  �Ǽǵ���թƭȫ����ѯ_Ȩ������Ϣ��
   ��������:  *pst_gab_dxzp_qhcx_qlxx ����թƭȫ����ѯ_Ȩ������Ϣ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_qhcx_qlxx(HXMLTREE lXmlhandle,GAB_DXZP_QHCX_QLXX *pst_gab_dxzp_qhcx_qlxx)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_qhcx_qlxx", SD_GAB_DXZP_QHCX_QLXX, NUMELE(SD_GAB_DXZP_QHCX_QLXX), pst_gab_dxzp_qhcx_qlxx, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭȫ����ѯ_Ȩ������Ϣ��ʧ��,ywsqbh[%s],rwxh[%d],xh[%s]", 
             pst_gab_dxzp_qhcx_qlxx->ywsqbh,pst_gab_dxzp_qhcx_qlxx->rwxh,pst_gab_dxzp_qhcx_qlxx->xh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}





















/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_dtcx_resp
   ��������:  ��ѯ����թƭ ��̬��ѯ��Ӧ
   ��������:  *pst_gab_dxzp_dtcx_resp  ����թƭ��̬��ѯ��Ӧ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_dtcx_resp(HXMLTREE lXmlhandle,GAB_DXZP_DTCX_RESP *pst_gab_dxzp_dtcx_resp)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_dtcx_resp where ywsqbh='%s' and rwxh=%d ", pst_gab_dxzp_dtcx_resp->ywsqbh,pst_gab_dxzp_dtcx_resp->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_DTCX_RESP, NUMELE(SD_GAB_DXZP_DTCX_RESP), pst_gab_dxzp_dtcx_resp );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ��̬��ѯ��Ӧ��ʧ��,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtcx_resp->ywsqbh,pst_gab_dxzp_dtcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ��̬��ѯ��Ӧ����ؼ�¼,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtcx_resp->ywsqbh,pst_gab_dxzp_dtcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_dtcx_resp
   ��������:  �Ǽǵ���թƭ��̬��ѯ��Ӧ
   ��������:  *pst_gab_dxzp_dtcx_resp ����թƭ��̬��ѯ��Ӧ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_dtcx_resp(HXMLTREE lXmlhandle,GAB_DXZP_DTCX_RESP *pst_gab_dxzp_dtcx_resp)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_dtcx_resp", SD_GAB_DXZP_DTCX_RESP, NUMELE(SD_GAB_DXZP_DTCX_RESP), pst_gab_dxzp_dtcx_resp, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ����թƭ��̬��ѯ��Ӧ��ʧ��,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtcx_resp->ywsqbh,pst_gab_dxzp_dtcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


















/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_dtjc_resp
   ��������:  ��ѯ����թƭ��̬�����Ӧ
   ��������:  *pst_gab_dxzp_dtjc_resp  ����թƭ��̬�����Ӧ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_dtjc_resp(HXMLTREE lXmlhandle,GAB_DXZP_DTJC_RESP *pst_gab_dxzp_dtjc_resp)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_dtjc_resp where ywsqbh='%s' and rwxh=%d ", pst_gab_dxzp_dtjc_resp->ywsqbh,pst_gab_dxzp_dtjc_resp->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_DTJC_RESP, NUMELE(SD_GAB_DXZP_DTJC_RESP), pst_gab_dxzp_dtjc_resp );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ��̬�����Ӧ��ʧ��,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtjc_resp->ywsqbh,pst_gab_dxzp_dtjc_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ��̬�����Ӧ����ؼ�¼,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtjc_resp->ywsqbh,pst_gab_dxzp_dtjc_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_dtjc_resp
   ��������:  �Ǽǵ���թƭ��̬��ѯ��Ӧ
   ��������:  *pst_gab_dxzp_dtjc_resp ����թƭ��̬��ѯ��Ӧ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_dtjc_resp(HXMLTREE lXmlhandle,GAB_DXZP_DTJC_RESP *pst_gab_dxzp_dtjc_resp)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_dtjc_resp", SD_GAB_DXZP_DTJC_RESP, NUMELE(SD_GAB_DXZP_DTJC_RESP), pst_gab_dxzp_dtjc_resp, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ��̬�����Ӧ��ʧ��,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_dtjc_resp->ywsqbh,pst_gab_dxzp_dtjc_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}












/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_smjfj
   ��������:  ��ѯ����թƭɨ���������
   ��������:  *pst_gab_dxzp_smjfj  ����թƭɨ���������ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_smjfj(HXMLTREE lXmlhandle,GAB_DXZP_SMJFJ *pst_gab_dxzp_smjfj)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_smjfj where ywsqbh='%s' and xh=%d ", pst_gab_dxzp_smjfj->ywsqbh,pst_gab_dxzp_smjfj->xh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SMJFJ, NUMELE(SD_GAB_DXZP_SMJFJ), pst_gab_dxzp_smjfj );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭɨ���������ʧ��,ywsqbh[%s],xh[%d]", 
             pst_gab_dxzp_smjfj->ywsqbh,pst_gab_dxzp_smjfj->xh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭɨ�����������ؼ�¼,ywsqbh[%s],xh[%d]", 
             pst_gab_dxzp_smjfj->ywsqbh,pst_gab_dxzp_smjfj->xh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_smjfj
   ��������:  �Ǽǵ���թƭɨ���������
   ��������:  *pst_gab_dxzp_smjfj ����թƭɨ���������ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_smjfj(HXMLTREE lXmlhandle,GAB_DXZP_SMJFJ *pst_gab_dxzp_smjfj)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_smjfj", SD_GAB_DXZP_SMJFJ, NUMELE(SD_GAB_DXZP_SMJFJ), pst_gab_dxzp_smjfj, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭɨ���������ʧ��,ywsqbh[%s],xh[%d]", 
             pst_gab_dxzp_smjfj->ywsqbh,pst_gab_dxzp_smjfj->xh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}















/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_ztcx_resp
   ��������:  ��ѯ����թƭ�ֿ������ѯ��Ӧ
   ��������:  *pst_gab_dxzp_ztcx_resp  ����թƭ�ֿ������ѯ��Ӧ��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_ztcx_resp(HXMLTREE lXmlhandle,GAB_DXZP_ZTCX_RESP *pst_gab_dxzp_ztcx_resp)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_ztcx_resp where ywsqbh='%s' and rwxh=%d ", pst_gab_dxzp_ztcx_resp->ywsqbh,pst_gab_dxzp_ztcx_resp->rwxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_ZTCX_RESP, NUMELE(SD_GAB_DXZP_ZTCX_RESP), pst_gab_dxzp_ztcx_resp );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�ֿ������ѯ��Ӧ��ʧ��,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_ztcx_resp->ywsqbh,pst_gab_dxzp_ztcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�ֿ������ѯ��Ӧ����ؼ�¼,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_ztcx_resp->ywsqbh,pst_gab_dxzp_ztcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_ztcx_resp
   ��������:  �Ǽǵ���թƭ�ֿ������ѯ��Ӧ
   ��������:  *pst_gab_dxzp_ztcx_resp ����թƭ�ֿ������ѯ��Ӧ�ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_ztcx_resp(HXMLTREE lXmlhandle,GAB_DXZP_ZTCX_RESP *pst_gab_dxzp_ztcx_resp)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_ztcx_resp", SD_GAB_DXZP_ZTCX_RESP, NUMELE(SD_GAB_DXZP_ZTCX_RESP), pst_gab_dxzp_ztcx_resp, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�ֿ������ѯ��Ӧ��ʧ��,ywsqbh[%s],rwxh[%d]", 
             pst_gab_dxzp_ztcx_resp->ywsqbh,pst_gab_dxzp_ztcx_resp->rwxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}


/*****************************************************
   ��������:  fdbop_qry_dual
   ��������:  ��ѯҵ����ˮ��
   ��������:  *pst_gab_dual  ����թƭҵ����ˮ�Žṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_dual(HXMLTREE lXmlhandle,GAB_DXZP_DUAL *pst_gab_dxzp_dual, char *psDualName)
{
    int iRet = -1;
    char sDbType[6+1];
    char sSql[256];
    
    memset(sDbType, 0x00, sizeof(sDbType));
    snprintf(sDbType, sizeof(sDbType), "%s", getenv("DB"));
    if (sDbType[0] == '\0')
    {
        GAB_DXZP_PSTRCOPY(sDbType, "ORA")
    }
    memset(sSql, 0x00, sizeof(sSql));
    if (strncmp(sDbType, "ORA", 3) == 0 )
    {
        snprintf(sSql, sizeof(sSql), "select %s.nextval as ID from dual", psDualName);
    }else if (strncmp(sDbType, "DB2", 3) == 0 )
    {
        snprintf(sSql, sizeof(sSql), "select nextval for %s as ID from SYSIBM.SYSDUMMY1", psDualName);
    }else
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, "�ݲ�֧�ֳ�ORACLE/DB2��������ݿ�");
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�ݲ�֧�ֳ�ORACLE/DB2��������ݿ�"),fpub_GetCompname(lXmlhandle));
    }
    LOG(LM_DEBUG, Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_DUAL, NUMELE(SD_GAB_DXZP_DUAL), pst_gab_dxzp_dual );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭҵ����ˮ��ʧ��"),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭҵ����ˮ�ű���ؼ�¼"),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}













/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_sbxx_plzt
   ��������:  ����թƭ�ϱ���Ϣ_����״̬��
   ��������:  *pst_gab_dxzp_sbxx_plzt  ����թƭ�ϱ���Ϣ_����״̬��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_sbxx_plzt(HXMLTREE lXmlhandle,GAB_DXZP_SBXX_PLZT *pst_gab_dxzp_sbxx_plzt)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_sbxx_plzt where sbpch='%s' and sbpcxh=%d ", pst_gab_dxzp_sbxx_plzt->sbpch,pst_gab_dxzp_sbxx_plzt->sbpcxh);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_SBXX_PLZT, NUMELE(SD_GAB_DXZP_SBXX_PLZT), pst_gab_dxzp_sbxx_plzt );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�ϱ���Ϣ_����״̬��ʧ��,sbpch[%s],sbpcxh[%d]", 
             pst_gab_dxzp_sbxx_plzt->sbpch,pst_gab_dxzp_sbxx_plzt->sbpcxh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�ϱ���Ϣ_����״̬����ؼ�¼,sbpch[%s],sbpcxh[%d]", 
             pst_gab_dxzp_sbxx_plzt->sbpch,pst_gab_dxzp_sbxx_plzt->sbpcxh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_sbxx_plzt
   ��������:  �Ǽǵ���թƭ�ϱ���Ϣ_����״̬��
   ��������:  *pst_gab_dxzp_sbxx_plzt ����թƭ�ϱ���Ϣ_����״̬��ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_sbxx_plzt(HXMLTREE lXmlhandle,GAB_DXZP_SBXX_PLZT *pst_gab_dxzp_sbxx_plzt)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_sbxx_plzt", SD_GAB_DXZP_SBXX_PLZT, NUMELE(SD_GAB_DXZP_SBXX_PLZT), pst_gab_dxzp_sbxx_plzt, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�ϱ���Ϣ_����״̬��ʧ��,sbpch[%s],sbpcxh[%d]", 
             pst_gab_dxzp_sbxx_plzt->sbpch,pst_gab_dxzp_sbxx_plzt->sbpcxh),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}





/*****************************************************
   ��������:  fdbop_qry_gab_dxzp_hhmd
   ��������:  ����թƭ�ڻ�������
   ��������:  *pst_gab_dxzp_hhmd  ����թƭ�ڻ�������ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_qry_gab_dxzp_hhmd(HXMLTREE lXmlhandle,GAB_DXZP_HHMD *pst_gab_dxzp_hhmd)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "select * from gab_dxzp_hhmd where mdjz='%s'", pst_gab_dxzp_hhmd->mdjz);
    iRet = ffunc_dbop_selToStruct( sSql, SD_GAB_DXZP_HHMD, NUMELE(SD_GAB_DXZP_HHMD), pst_gab_dxzp_hhmd );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    LOG(LM_STD,Fmtmsg("sSql=[%s]",sSql),"DEBUG");
    return iRet;
}

/*****************************************************
   ��������:  fdbop_ins_gab_dxzp_hhmd
   ��������:  �Ǽǵ���թƭ�ڻ�������
   ��������:  *pst_gab_dxzp_hhmd ����թƭ�ڻ�������ṹ��

   ��������:  0   :�ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_ins_gab_dxzp_hhmd(HXMLTREE lXmlhandle,GAB_DXZP_HHMD *pst_gab_dxzp_hhmd)
{
    int iRet = -1;
    char sErrmsg[256];
    
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = DBInsert("gab_dxzp_hhmd", SD_GAB_DXZP_HHMD, NUMELE(SD_GAB_DXZP_HHMD), pst_gab_dxzp_hhmd, sErrmsg);
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("�Ǽǵ���թƭ�ڻ�������ʧ��,mdjz[%s]", 
            pst_gab_dxzp_hhmd->mdjz),fpub_GetCompname(lXmlhandle));
    }
    
    return 0;
}






/*****************************************************
   ��������:  fdbop_upd_gab_dxzp_hhmd
   ��������:  ���µ���թƭ�ڻ�������
   ��������:  *pst_gab_dxzp_hhmd  ����թƭ�ڻ�������ṹ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_gab_dxzp_hhmd(HXMLTREE lXmlhandle,GAB_DXZP_HHMD *pst_gab_dxzp_hhmd)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_hhmd set mdlx='%s',mdly='%s',\
        ajlx='%s',xm='%s',mdjb='%s',gxrq='%s',gxsj='%s' where mdjz='%s'", 
        pst_gab_dxzp_hhmd->mdlx, pst_gab_dxzp_hhmd->mdly, pst_gab_dxzp_hhmd->ajlx,
        pst_gab_dxzp_hhmd->xm, pst_gab_dxzp_hhmd->mdjb, pst_gab_dxzp_hhmd->gxrq, pst_gab_dxzp_hhmd->gxsj,pst_gab_dxzp_hhmd->mdjz);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_hhmd.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("���µ���թƭ�ڻ�������ʧ��,mdjz[%s]", 
           pst_gab_dxzp_hhmd->mdjz),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�ڻ���������ؼ�¼,mdjz[%s]", 
            pst_gab_dxzp_hhmd->mdjz),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}


/*****************************************************
   ��������:  fdbop_del_gab_dxzp_hhmd
   ��������:  ɾ������թƭ�ڻ�������
   ��������:  *pst_gab_dxzp_hhmd  ����թƭ�ڻ�������ṹ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_del_gab_dxzp_hhmd(HXMLTREE lXmlhandle,GAB_DXZP_HHMD *pst_gab_dxzp_hhmd)
{
    int iRet = -1;
    char sSql[256];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "delete gab_dxzp_hhmd  where mdjz='%s'",pst_gab_dxzp_hhmd->mdjz);
   
    LOG(LM_STD, Fmtmsg("fdbop_del_gab_dxzp_hhmd.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("ɾ������թƭ�ڻ�������ʧ��,mdjz[%s]", 
           pst_gab_dxzp_hhmd->mdjz),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�ڻ���������ؼ�¼,mdjz[%s]", 
            pst_gab_dxzp_hhmd->mdjz),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}



/*****************************************************
   ��������:  fdbop_upd_gab_dxzp_xdxx_qdxx
   ��������:  ���µ���թƭ������Ϣ��
   ��������:  *pst_gab_dxzp_xdxx  ����թƭ�´���Ϣ��ṹ��

   ��������:  0   :���³ɹ�
              1   :δ�ҵ�
              ����:ʧ��

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int fdbop_upd_gab_dxzp_xdxx_qdxx(HXMLTREE lXmlhandle,GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
{
    int iRet = -1;
    char sSql[512];
    
    memset(sSql, 0x00, sizeof(sSql));
    
    snprintf(sSql, sizeof(sSql), "update gab_dxzp_xdxx set jbjg='%s', jbgy='%s' where ywsqbh='%s'", 
        pst_gab_dxzp_xdxx->jbjg, pst_gab_dxzp_xdxx->jbgy, 
        pst_gab_dxzp_xdxx->ywsqbh);
    LOG(LM_STD, Fmtmsg("fdbop_upd_gab_dxzp_xdxx.sql[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet = DCIExecuteDirect( sSql );
    GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, DCILastError());
    if( iRet < 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("���µ���թƭ�´���Ϣ��ʧ��,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }
    if ( iRet == 0 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP_NOTFOUND, MSG_GAB_DXZP_DBOP_NOTFOUND);
        LOGRET( GAB_DXZP_FUNCRET_NOTFOUND, LM_STD, Fmtmsg("δ�ҵ���ѯ����թƭ�´���Ϣ����ؼ�¼,ywsqbh[%s]", 
            pst_gab_dxzp_xdxx->ywsqbh),fpub_GetCompname(lXmlhandle));
    }

    return 0;
}
