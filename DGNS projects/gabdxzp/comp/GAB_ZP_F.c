/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:��������թƭǰ��ϵͳ
��    ��:V2.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:ORACLE\INFORMIX\DB2
�ļ�����:GAB_ZP_F.c
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
#include <iconv.h>
/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_XDXX_Req(HXMLTREE lXmlhandle, GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
 ��������:  ��ȡ����������թƭ�´���Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_XDXX_Req(HXMLTREE lXmlhandle, GAB_DXZP_XDXX *pst_gab_dxzp_xdxx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    char sOldDateTime[14+1];
    char sNewDateTime[14+1];
    char sSql[256];
    int  iDdMins=0;
    GAB_DXZP_DUAL st_gab_dxzp_dual;

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_APPLICATIONID,pst_gab_dxzp_xdxx->ywsqbh,"ҵ��������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYBM,pst_gab_dxzp_xdxx->jybm,"�������ͱ���");
    
    /*��Ϣ��תģʽ*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_XXLZMS,pst_gab_dxzp_xdxx->xxlzms,"��Ϣ��תģʽ");
    pst_gab_dxzp_xdxx->xxlzms[1]=pst_gab_dxzp_xdxx->xxlzms[0];
    pst_gab_dxzp_xdxx->xxlzms[0]='0';
    /*�����������*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_MESSAGEFROM,pst_gab_dxzp_xdxx->fsjgbm,"�����������");
    if (pst_gab_dxzp_xdxx->fsjgbm[0] == '\0')
    {
        strcpy(pst_gab_dxzp_xdxx->fsjgbm, "mps");
    }
    COMP_SOFTSETXML("/gabdxzp/FSJGBM", pst_gab_dxzp_xdxx->fsjgbm)
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CSBWLSH,pst_gab_dxzp_xdxx->csbwlsh,"���䱨����ˮ��");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_GAAPPLICATIONID,pst_gab_dxzp_xdxx->gaywsqbh,"����ҵ��������");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_SQJGDM,pst_gab_dxzp_xdxx->sqjgdm,"�����������");
    /*Ŀ���������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->mbjgdm);
     
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXZTLB,pst_gab_dxzp_xdxx->cxztlb,"����������");
    
    /*ҵ������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWLX,pst_gab_dxzp_xdxx->ywlx,"ҵ������");
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->ywlx); 
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JJCD,pst_gab_dxzp_xdxx->jjcd,"�����̶�");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_AJBH,pst_gab_dxzp_xdxx->ajbh,"�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_AJLX,pst_gab_dxzp_xdxx->ajlx,"��������");

    /*��������*/
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->ajsy);
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_AJSY,pst_gab_dxzp_xdxx->ajsy,"��������");
    if('\0' == pst_gab_dxzp_xdxx->ajsy[0])
    	{
    		GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->ajsy);
    	}
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_AJSM,pst_gab_dxzp_xdxx->ajsm,"����˵��");
 
    /*���������Ŀ�����ʱ��ϵͳ����ʱ��*/
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_SQSJ, sBuf,"����ʱ��");
    pstrcopy(pst_gab_dxzp_xdxx->sqrq,sBuf,sizeof(pst_gab_dxzp_xdxx->sqrq));
    
    /*���������Ŀ�����ʱ��ϵͳ����ʱ��*/
    pstrcopy(pst_gab_dxzp_xdxx->sqsj,sBuf+8,sizeof(pst_gab_dxzp_xdxx->sqsj));
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_SQJGBM,pst_gab_dxzp_xdxx->sqjgbm,"�����������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_SQJGMC,pst_gab_dxzp_xdxx->sqjgmc,"�����������");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBRXM,pst_gab_dxzp_xdxx->jbrxm,"����������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBRZJLX,pst_gab_dxzp_xdxx->jbrzjlx,"������֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBRZJHM,pst_gab_dxzp_xdxx->jbrzjhm,"������֤����"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBRDH,pst_gab_dxzp_xdxx->jbrdh,"�����˵绰"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXRXM,pst_gab_dxzp_xdxx->xcrxm,"Э��������"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_XCRZJLX,pst_gab_dxzp_xdxx->xcrzjlx,"Э����֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_XCRZJHM,pst_gab_dxzp_xdxx->xcrzjhm,"Э����֤����");
   
     
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_xdxx->ywrq,"ҵ������");
    
    /*ҵ����ˮ��*/
    memset(sSql, 0x00, sizeof(sSql));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_DXZP_XL,sSql,"ҵ����ˮ��");
    memset(&st_gab_dxzp_dual, 0x00, sizeof(st_gab_dxzp_dual));
    LOG(LM_STD, Fmtmsg("�Ǽ��´���Ϣ��->sfxt_xl[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet=fdbop_qry_dual(lXmlhandle, &st_gab_dxzp_dual, sSql);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "��ȡҵ����ˮ��");
    snprintf(pst_gab_dxzp_xdxx->ywlsh, sizeof(pst_gab_dxzp_xdxx->ywlsh), 
        "08%ld", st_gab_dxzp_dual.nextval);
    /*�������*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_XNJG,pst_gab_dxzp_xdxx->jbjg,"�������");
    /*�����Ա*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_XNGY,pst_gab_dxzp_xdxx->jbgy,"�����Ա");
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBXM,pst_gab_dxzp_xdxx->jbxm,"���о�������");
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JBDH,pst_gab_dxzp_xdxx->jbdh,"���о���绰");
    
    
    
    /*��������*/
    pst_gab_dxzp_xdxx->rwsl=1;
    
    /*��������޶�ʱ��*/
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"��������޶�ʱ��");
    if (sBuf[0] == '\0')
    {
        strcpy(sBuf,"24");
    }
    pst_gab_dxzp_xdxx->jgfkxdsj=atoi(sBuf);
    /*�����޶�����*/
    memset(sOldDateTime, 0x00, sizeof(sOldDateTime));
    memset(sNewDateTime, 0x00, sizeof(sNewDateTime));
    snprintf(sOldDateTime, sizeof(sOldDateTime), "%s%s", 
        pst_gab_dxzp_xdxx->sqrq, pst_gab_dxzp_xdxx->sqsj);
    iRet = ffunc_gabdxzp_getMoveHours(lXmlhandle, sOldDateTime, pst_gab_dxzp_xdxx->jgfkxdsj, sNewDateTime, sizeof(sNewDateTime));
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->fkxdrq, sNewDateTime)
    /*�����޶�ʱ��*/
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->fkxdsj, sNewDateTime+8)
    /*������������*/
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_DDMIN,sBuf,"������ǰN����");
    if ( sBuf[0] == '\0')
    {
        strcpy(sBuf, "15");
    }
    iDdMins = atoi(sBuf);
    memset(sOldDateTime, 0x00, sizeof(sOldDateTime));
    GAB_DXZP_PSTRCOPY(sOldDateTime, sNewDateTime);
    memset(sNewDateTime, 0x00, sizeof(sNewDateTime));
    iRet = ffunc_gabdxzp_getMoveMins(lXmlhandle, sOldDateTime, iDdMins, sNewDateTime, sizeof(sNewDateTime));
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->fkddrq, sNewDateTime)
    LOG(LM_STD, Fmtmsg("�Ǽ��´���Ϣ��->sOldDateTime[%s] - iDdMins[%d] = sNewDateTime[%s]", 
        sOldDateTime, iDdMins, sNewDateTime), fpub_GetCompname(lXmlhandle));
    /*��������ʱ��*/
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->fkddsj, sNewDateTime+8)
    /*���Դ����־*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->szclbz);
    
    /*��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->clrq);
    /*����ʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->clsj);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_xdxx->zwrq,"��������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSTIME,pst_gab_dxzp_xdxx->systime,"gapsϵͳʱ��");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_ZHQZLSH,pst_gab_dxzp_xdxx->zhqzlsh,"gaps��ˮ��");
    
    /*����״̬ 12��20-��سɹ�*/
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->qqdzt, "20");
    /*ҵ��Ӧ����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->ywydm);
    /*ҵ��Ӧ����Ϣ*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->ywydxx);
    /*ִ�н��*/
    GAB_DXZP_PSTRCOPY(pst_gab_dxzp_xdxx->zxjg, "9");
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->respcode);
    /*����ԭ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->respmsg);
    /*��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->zjrq);
    /*������ˮ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->zjlsh);
    /*��ѯ����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->lxrq);
    /*��ѯ���κ�*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->lxpch);
    /*�������*/
    pst_gab_dxzp_xdxx->pcxh=0;
    
    /*�ύ���Ĵ���*/
    pst_gab_dxzp_xdxx->tjhxcs=0;
    /*����ǰ�ô���*/
    pst_gab_dxzp_xdxx->fkqzcs=0;
    /*����11*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->by11);
    /*����12*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->by12);
    /*����13*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_xdxx->by13);
    
    return 0;
}

/*****************************************************
 ��������:  ffunc_gabdxzp_getXml_945100_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
 ��������:  ��ȡ����������թƭֹ������������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945100_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_jjzf->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_jjzf->rwxh=1;
    /*ԭҵ��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->yywsqbh);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_SFBLC,pst_gab_dxzp_jjzf->sfblc,"�Ƿ�����");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_YJBSQBH,pst_gab_dxzp_jjzf->yjbsqbh,"ԭ�ٱ�������");
    /*����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->kh);
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZCZHYH,pst_gab_dxzp_jjzf->zczhyh,"ת���˻��������л�������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZCZHYHMC,pst_gab_dxzp_jjzf->zczhyhmc,"ת���˻���������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZCZHM,pst_gab_dxzp_jjzf->zczhm,"ת���˻���");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZCZH,pst_gab_dxzp_jjzf->zczh,"ת���˿���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_BZ,pst_gab_dxzp_jjzf->bz,"����");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZCJE, pst_gab_dxzp_jjzf->zcje, "ת�����");
    memset(sBuf,0x00,sizeof(sBuf));
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZCSJ,sBuf,"ת��ʱ��");
    /*ת������*/
    strncpy(pst_gab_dxzp_jjzf->zcrq,sBuf,8);
    /*ת��ʱ��*/
    strncpy(pst_gab_dxzp_jjzf->zcsj,sBuf+8,6);
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_jjzf->khyh,"ֹ���˻��������л�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_jjzf->khyhmc,"ֹ���˻�������������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_jjzf->zhlb,"ֹ���˺����");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_jjzf->zhmc,"ֹ���˻���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_jjzf->zh,"ֹ���˿���");
    /*ֹ��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->dqr);
    //GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DQR,pst_gab_dxzp_jjzf->dqr,"ֹ��������");
    
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"��������޶�ʱ��");
    pst_gab_dxzp_jjzf->jgfksj=atoi(sBuf);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFQSSJ,pst_gab_dxzp_jjzf->zfqssj,"ֹ����ʼʱ��");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJSSJ,pst_gab_dxzp_jjzf->zfjssj,"ֹ������ʱ��");
    /*ִ�н��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjg);
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respcode);
    /*����ԭ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respmsg);
    /*ִ����ʼ����
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqsrq);
    *//*ִ����ʼʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqssj);
    /*ִ����ʼ����
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjsrq);
    *//*ִ����ʼʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjssj);
    /*����˵��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fksm);
    /*������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fkjgmc);
    /*�˻����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zhye);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jjzf->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_jjzf->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by3);
    return 0;
}

/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945101_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
 ��������:  ��ȡ����������թƭֹ���������������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945101_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_jjzf->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_jjzf->rwxh=1;
    /*ԭҵ��������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YYWSQBH,pst_gab_dxzp_jjzf->yywsqbh,"ԭҵ��������");
 
    /*����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->kh);
    
    /*ת���˻��������л�������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhyh);
    /*ת���˻���������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhyhmc);
    /*ת���˻���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhm);
    /*ת���˿���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczh);
    /*����*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->bz);
    /*ת�����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcje);

    /*ת������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcrq);
    /*ת��ʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcsj);
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_jjzf->khyh,"ֹ���˻��������л�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_jjzf->khyhmc,"ֹ���˻�������������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_jjzf->zhlb,"ֹ���˺����");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_jjzf->zhmc,"ֹ���˻���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_jjzf->zh,"ֹ���˿���");
    /*ֹ��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->dqr);
    /*��������޶�ʱ��*/
    pst_gab_dxzp_jjzf->jgfksj=24;
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->jgfksj);
    /*ֹ�����ʱ��(yyyyMMddHHmmss)*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJCSXSJ,pst_gab_dxzp_jjzf->zfqssj,"ֹ�����ʱ��");
 
    /*ִ�н��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjg);
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respcode);
    /*����ԭ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respmsg);
    /*ִ����ʼ����
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqsrq);
    *//*ִ����ʼʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqssj);
    /*ִ����ʼ����
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjsrq);
    *//*ִ����ʼʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjssj);
    /*����˵��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fksm);
    /*������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fkjgmc);
    /*�˻����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zhye);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jjzf->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_jjzf->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by3);
    return 0;
}




/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945102_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
 ��������:  ��ȡ����������թƭֹ�����ڱ���������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945102_Req(HXMLTREE lXmlhandle, GAB_DXZP_JJZF *pst_gab_dxzp_jjzf)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_jjzf->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_jjzf->rwxh=1;
    /*ԭҵ��������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YYWSQBH,pst_gab_dxzp_jjzf->yywsqbh,"ԭҵ��������");
 
    /*����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->kh);
    
    /*ת���˻��������л�������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhyh);
    /*ת���˻���������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhyhmc);
    /*ת���˻���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczhm);
    /*ת���˿���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zczh);
    /*����*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->bz);
    /*ת�����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcje);

    /*ת������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcrq);
    /*ת��ʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zcsj);
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_jjzf->khyh,"ֹ���˻��������л�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_jjzf->khyhmc,"ֹ���˻�������������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_jjzf->zhlb,"ֹ���˺����");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_jjzf->zhmc,"ֹ���˻���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_jjzf->zh,"ֹ���˿���");
    //GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DQR,pst_gab_dxzp_jjzf->dqr,"ֹ��������");
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->dqr);
    /*��������޶�ʱ��*/
    pst_gab_dxzp_jjzf->jgfksj=24;
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->jgfksj);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFYQQSSJ,pst_gab_dxzp_jjzf->zfqssj,"ֹ����ʼʱ��");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJCSXSJ,pst_gab_dxzp_jjzf->zfjssj,"ֹ������ʱ��");
 
    /*ִ�н��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjg);
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respcode);
    /*����ԭ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->respmsg);
    /*ִ����ʼ����
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqsrq);
    *//*ִ����ʼʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxqssj);
    /*ִ����ʼ����
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjsrq);
    *//*ִ����ʼʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zxjssj);
    /*����˵��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fksm);
    /*������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->fkjgmc);
    /*�˻����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->zhye);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jjzf->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_jjzf->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jjzf->by3);
    return 0;
}



/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945103_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
 ��������:  ��ȡ����������թƭ���ᱨ��������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945103_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_djxj->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_djxj->rwxh=1;
    /*ԭҵ��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->yywsqbh);
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_djxj->khyh,"�����˻��������л�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_djxj->khyhmc,"�����˻�������������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_djxj->zhlb,"�����˺����"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_djxj->zhmc,"�����˻���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_djxj->zh,"�����˿���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJLX,pst_gab_dxzp_djxj->zjlx,"�����˻�֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJHM,pst_gab_dxzp_djxj->zjhm,"�����˺�֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DJFS,pst_gab_dxzp_djxj->djfs,"���᷽ʽ"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_BZ,pst_gab_dxzp_djxj->bz,"����"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JE,pst_gab_dxzp_djxj->je,"���"); 
    /*���ᵽ����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->dqr);
    //GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DQR,pst_gab_dxzp_djxj->dqr,"���ᵽ����"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DJQSSJ,pst_gab_dxzp_djxj->djqssj,"������ʼʱ��"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJSSJ,pst_gab_dxzp_djxj->djjssj,"�������ʱ��"); 
    
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"��������޶�ʱ��"); 
    pst_gab_dxzp_djxj->jgfksj=atoi(sBuf);
    /*ִ�н��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjg);
    
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respcode);
    
    /*����ԭ��*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respmsg);
    
    /*����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->kh);
    
    /*ִ����ʼ����
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqsrq);
    *//*ִ����ʼʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqssj);
    /*ִ�н�������
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjsrq);
    *//*ִ�н���ʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjssj);
    /*����˵��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fksm);
    /*������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fkjgmc);
    /*ִ�ж�����*/   
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->djje);
    /*�˻����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhye);
    /*���ȶ�����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjje);
    /*���ȶ��ᵽ����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjrq); 
    /*�˻��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhkyye); 
    /*���ȶ������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjjg);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_djxj->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_djxj->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by3);
    return 0;
}






/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945104_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
 ��������:  ��ȡ����������թƭ����������������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945104_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_djxj->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_djxj->rwxh=1;
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YYWSQBH,pst_gab_dxzp_djxj->yywsqbh,"ԭҵ��������");
 
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_djxj->khyh,"�����˻��������л�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_djxj->khyhmc,"�����˻�������������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_djxj->zhlb,"�����˺����"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_djxj->zhmc,"�����˻���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_djxj->zh,"�����˿���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJLX,pst_gab_dxzp_djxj->zjlx,"�����˻�֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJHM,pst_gab_dxzp_djxj->zjhm,"�����˺�֤������");
    /*���᷽ʽ*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->djfs); 
    /*����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->bz); 
    /*���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->je); 
    /*���ᵽ����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->dqr);
    /*��������޶�ʱ��*/
    pst_gab_dxzp_djxj->jgfksj=24;
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->jgfksj);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJCSXSJ,pst_gab_dxzp_djxj->djqssj,"������ʱ��(yyyyMMddHHmmss)");
   
    /*ִ�н��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjg);
    
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respcode);
    
    /*����ԭ��*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respmsg);
    
    /*����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->kh);
    
    /*ִ����ʼ����
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqsrq);
    *//*ִ����ʼʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqssj);
    /*ִ�н�������
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjsrq);
    *//*ִ�н���ʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjssj);
    /*����˵��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fksm);
    /*������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fkjgmc);
    /*ִ�ж�����*/   
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->djje);
    /*�˻����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhye);
    /*���ȶ�����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjje);
    /*���ȶ��ᵽ����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjrq); 
    /*�˻��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhkyye); 
    /*���ȶ������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjjg);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_djxj->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_djxj->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by3);
    return 0;
}



/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945105_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
 ��������:  ��ȡ����������թƭ�������ڱ���������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945105_Req(HXMLTREE lXmlhandle, GAB_DXZP_DJXJ *pst_gab_dxzp_djxj)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_djxj->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_djxj->rwxh=1;
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YYWSQBH,pst_gab_dxzp_djxj->yywsqbh,"ԭҵ��������");
 
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_djxj->khyh,"�����˻��������л�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_djxj->khyhmc,"�����˻�������������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_djxj->zhlb,"�����˺����"); 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_djxj->zhmc,"�����˻���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZH,pst_gab_dxzp_djxj->zh,"�����˿���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJLX,pst_gab_dxzp_djxj->zjlx,"�����˻�֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZJHM,pst_gab_dxzp_djxj->zjhm,"�����˺�֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DJFS,pst_gab_dxzp_djxj->djfs,"���᷽ʽ");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_BZ,pst_gab_dxzp_djxj->bz,"����");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JE,pst_gab_dxzp_djxj->je,"���");
    //GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DQR,pst_gab_dxzp_djxj->dqr,"���ᵽ����");
    /*���ᵽ����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->dqr);
    /*��������޶�ʱ��*/
    pst_gab_dxzp_djxj->jgfksj=24;
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->jgfksj);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFYQQSSJ,pst_gab_dxzp_djxj->djqssj,"������ʼʱ��");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZFJCSXSJ,pst_gab_dxzp_djxj->djjssj,"�������ʱ��");
    
   
    /*ִ�н��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjg);
    
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respcode);
    
    /*����ԭ��*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->respmsg);
    
    /*����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->kh);
    
    /*ִ����ʼ����
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqsrq);
    *//*ִ����ʼʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxqssj);
    /*ִ�н�������
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjsrq);
    *//*ִ�н���ʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxjssj);
    /*����˵��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fksm);
    /*������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->fkjgmc);
    /*ִ�ж�����*/   
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->djje);
    /*�˻����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhye);
    /*���ȶ�����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjje);
    /*���ȶ��ᵽ����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjrq); 
    /*�˻��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zhkyye); 
    /*���ȶ������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->zxdjjg);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_djxj->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_djxj->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_djxj->by3);
    return 0;
}


/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945106_Req(HXMLTREE lXmlhandle, GAB_DXZP_JYMX *pst_gab_dxzp_jymx)
 ��������:  ��ȡ����������թƭ�˻�������ϸ��ѯ����������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945106_Req(HXMLTREE lXmlhandle, GAB_DXZP_JYMX *pst_gab_dxzp_jymx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_jymx->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_jymx->rwxh=1;
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_jymx->khyh,"��ѯ�˻��������л�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_jymx->khyhmc,"��ѯ�˻�������������"); 
    /*��ѯ�˺����*/
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_jymx->zhlb,"��ѯ�˺����"); 
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_jymx->zhmc,"��ѯ�˻���");  
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CARDN,pst_gab_dxzp_jymx->zh,"��ѯ�˿���");  
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXNR,pst_gab_dxzp_jymx->cxnr,"��ѯ����");      
      
   
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXQSSJ,sBuf,"��ѯ��ʼʱ��");
    trim(sBuf);
    strncpy( pst_gab_dxzp_jymx->cxqsrq,sBuf,8); 
    strncpy( pst_gab_dxzp_jymx->cxqssj,sBuf+8,6);
    
   
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXJZSJ,sBuf,"��ѯ��ֹʱ��");
    trim(sBuf);
    strncpy(pst_gab_dxzp_jymx->cxjzrq,sBuf,8); 
    strncpy(pst_gab_dxzp_jymx->cxjzsj,sBuf+8,6);
   
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"��������޶�ʱ��"); 
    pst_gab_dxzp_jymx->jgfksj=atoi(sBuf);
        
    /*ִ�н��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->zxjg);    
        
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->respcode);
    
    /*����ԭ��*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->respmsg);
    /*����˵��*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->fksm);
    /*������������*/ 
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->fkjgmc);
     
     
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jymx->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_jymx->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx->by3);
    return 0;
}




/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945107_Req(HXMLTREE lXmlhandle, GAB_DXZP_SRL_ZTCX *pst_gab_dxzp_ztcx)
 ��������:  ��¼����թƭ�����ѯ�����Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945107_Req(HXMLTREE lXmlhandle, GAB_DXZP_ZTCX *pst_gab_dxzp_ztcx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_ztcx->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_ztcx->rwxh=1;
 
       
 
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_ztcx->khyh,"��ѯ�˻��������л�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_ztcx->khyhmc,"��ѯ�˻�������������");
    
    /*��ѯ�˺����*/
  
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_ztcx->zhlb,"��ѯ�˺����"); 
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_ztcx->zhmc,"��ѯ�˻���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CARDN,pst_gab_dxzp_ztcx->zh,"��ѯ�˿���");
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"��������޶�ʱ��");
    pst_gab_dxzp_ztcx->jgfksj=atoi(sBuf);
    /*ִ�н��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->zxjg);
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->respcode);
    /*����ԭ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->respmsg);

    /*����˵��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->fksm);
    /*������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->fkjgmc);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_ztcx->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_ztcx->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx->by3);
    
    return 0;
}
/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945108_Req(HXMLTREE lXmlhandle,  GAB_DXZP_DTCX  *pst_gab_dxzp_dtcx)
 ��������:  ��¼����թƭ��̬��ѯ�����Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945108_Req(HXMLTREE lXmlhandle, GAB_DXZP_DTCX *pst_gab_dxzp_dtcx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_dtcx->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_dtcx->rwxh=1;
    
    /*ԭҵ��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->yywsqbh);
    /*����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->kh);
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_BZ,pst_gab_dxzp_dtcx->bz,"����");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_dtcx->khyh,"��ѯ�˻��������л�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_dtcx->khyhmc,"��ѯ�˻�������������");
    /*��ѯ�˺����*/

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_dtcx->zhlb,"��ѯ�˺����"); 
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_dtcx->zhmc,"��ѯ�˻���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CARDN,pst_gab_dxzp_dtcx->zh,"��ѯ�˿���");

   /*��̬����*/
 	  //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->dtml);
    strcpy(pst_gab_dxzp_dtcx->dtml,"1");
    /*ִ����ʼ����*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZXQSSJ,pst_gab_dxzp_dtcx->zxqsrq,"ִ����ʼ����");
    /*ִ�н�ֹ����*/
  
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZXJZSJ,pst_gab_dxzp_dtcx->zxjzrq,"ִ�н�ֹ����");
    
    /*��̬��ѯ��ʼʱ��*/

    sprintf(pst_gab_dxzp_dtcx->dtcxqssj,"%s%s",GetSysDate(),GetSysTime()); 
    
    /*��̬��ѯ��ֹʱ��*/
    strcpy(pst_gab_dxzp_dtcx->dtcxjzsj,pst_gab_dxzp_dtcx->dtcxqssj);
       
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"��������޶�����");
    pst_gab_dxzp_dtcx->jgfksj = atof(sBuf);
	  
	  /*ִ�н��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->zxjg);
    
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->respcode);
    /*����ԭ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->respmsg);

    /*����˵��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->fksm);
    /*������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->fkjgmc);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_dtcx->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_dtcx->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by3);
    
    return 0;
    
}
/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945109_Req(HXMLTREE lXmlhandle,  GAB_DXZP_DTCX  *pst_gab_dxzp_dtcx)
 ��������:  ����թƭ�˻���̬��ѯ������Ķ�̬��Ϣ 
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945109_Req(HXMLTREE lXmlhandle, GAB_DXZP_DTCX *pst_gab_dxzp_dtcx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_dtcx->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_dtcx->rwxh=1;
    
    /*�����跴��*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_YYWSQBH,pst_gab_dxzp_dtcx->yywsqbh,"ԭҵ��������");
    
    /*����*/
 	  GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->kh);
 	  /*����*/
 	  GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->bz);
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_KHYH,pst_gab_dxzp_dtcx->khyh,"��ѯ�˻��������л�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_KHYHMC,pst_gab_dxzp_dtcx->khyhmc,"��ѯ�˻�������������");
    /*��ѯ�˺����*/

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_dtcx->zhlb,"��ѯ�˺����"); 
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHMC,pst_gab_dxzp_dtcx->zhmc,"��ѯ�˻���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CARDN,pst_gab_dxzp_dtcx->zh,"��ѯ�˿���");
    
    
    /*��̬����*/
 	  //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->dtml);
 	  strcpy(pst_gab_dxzp_dtcx->dtml,"0");
 	  
 	  /*��̬��ѯ�����Чʱ��*/
 	  GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZXJZSJ,pst_gab_dxzp_dtcx->zxqsrq,"��̬��ѯ�����Чʱ��");
   
   	GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->zxjzrq);
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"��������޶�����");
    pst_gab_dxzp_dtcx->jgfksj = atof(sBuf);
    /*ִ�н��*/
  	GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->zxjg);
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->respcode);
    /*����ԭ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->respmsg);

    /*����˵��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->fksm);
    /*������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->fkjgmc);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_dtcx->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_dtcx->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx->by3);
   
   
    return 0;
}
/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945110_Req(HXMLTREE lXmlhandle,  GAB_DXZP_QHCX *pst_gab_dxzp_qhcx
)
 ��������:  ��¼����թƭȫ����ѯ�����Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945110_Req(HXMLTREE lXmlhandle, GAB_DXZP_QHCX *pst_gab_dxzp_qhcx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH,pst_gab_dxzp_qhcx->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_qhcx->rwxh=1;
   
    /*��ѯ�˺����*/

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHLB,pst_gab_dxzp_qhcx->zhlb,"��ѯ�˺����"); 
       
 	
 	  GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXZJLX,pst_gab_dxzp_qhcx->cxzjlx,"��ѯ֤�����ʹ���");
 	  GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXZJHM,pst_gab_dxzp_qhcx->cxzjhm,"��ѯ֤�պ���");
 	  GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_QHCX_DXZP_ZHMC,pst_gab_dxzp_qhcx->zhmc,"��ѯ��������");
 	  GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CXNR,pst_gab_dxzp_qhcx->cxnr,"��ѯ����");
   
    memset(sBuf, 0x00, sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JGFKSJ,sBuf,"��������޶�����");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_BANKNAME,pst_gab_dxzp_qhcx->bankname,"��ѯ��������");
 	  
    pst_gab_dxzp_qhcx->jgfksj = atof(sBuf);
    
    /*ִ�н��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->zxjg);
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->respcode);
    /*����ԭ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->respmsg);

    /*����˵��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->fksm);
    /*������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->fkjgmc);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_qhcx->zwrq,"gaps����");

    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_qhcx->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx->by3);
    

    return 0;
}
/*****************************************************
   ��������:  int ffunc_xml_getNodeValue(HXMLTREE lXmlhandle, const char* szPath, const char* nodeAttr, char* szValue, unsigned int size, int iFlag)
   ��������:  ��ȡXML�ڵ�ֵ,���ַ����ڵ�Ϊ����'-';����������ͽڵ�Ϊ����0
   ��������:  lXmlhandle  XML���������
              Path  �ڵ�·��
              nodeAttr �ڵ����� 0-�ַ���, 1-�����ֵ�
              szValue �ڵ�ֵ����ַ���
              size  ���ֵ�Ŀռ��С
              iFlag �ڵ��Ƿ������� GAB_DXZP_XML_NULL GAB_DXZP_XML_NOTNULL
             
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
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!�ڵ�[%s]��Ŀ�����ΪNULL!", MSG_GAB_DXZP_XMLOP, psPath),"")
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
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!�ڵ�[%s]������[%d]!", MSG_GAB_DXZP_XMLOP, psPath, iRet),"") 
        return -2;
    }
    
    if( (psValue[0] == '\0') && (XML_NODE_NOTNULL == iFlag) )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!�ڵ�[%s]ֵΪ��!", MSG_GAB_DXZP_XMLOP, psPath),"")
        return -2;
    }    
    trim(psValue);       
    return strlen(psValue);
}




/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_SBXX_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SBXX *pst_gab_dxzp_sbxx)

 ��������:  ��¼����թƭ�ϱ���Ϣ�������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_SBXX_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SBXX *pst_gab_dxzp_sbxx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    char sSql[256];

    GAB_DXZP_DUAL st_gab_dxzp_dual;
   
    /*���䱨����ˮ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->csbwlsh);
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_sbxx->jybm,"���ױ���");
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_SBPCH,sBuf,"���󵥱�ʶ");
    if('\0'==sBuf[0] || 0 == strcmp(sBuf," "))
    	{
        GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sbxx->sbpch,"���󵥱�ʶ");
      }
     else
     	{
     		trim(sBuf);
     		strcpy(pst_gab_dxzp_sbxx->sbpch,sBuf);
     	}
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sbxx->ywsqbh,"�ϱ����κ�");
    /*�����������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_DXZP_YHJGID,pst_gab_dxzp_sbxx->sqjgdm,"�����������");
    
   
    /*Ŀ���������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_DXZP_QSJGID,pst_gab_dxzp_sbxx->mbjgdm,"Ŀ���������");

    /*ҵ������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_sbxx->ywlx,"ҵ������");
  
    /*�¼�����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->sjms);
    /*�ϱ���������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_DXZP_YHJGID,pst_gab_dxzp_sbxx->sbjgdm,"�ϱ���������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_SBJGMC,pst_gab_dxzp_sbxx->sbjgmc,"�ϱ���������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_JBRXM,pst_gab_dxzp_sbxx->jbrxm,"����������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_JBRDH,pst_gab_dxzp_sbxx->jbrdh,"�����˵绰");
    if('\0'== pst_gab_dxzp_sbxx->jbrxm[0] || 0 == strcmp(pst_gab_dxzp_sbxx->jbrxm," ") )
    	{
    		GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JBXM,pst_gab_dxzp_sbxx->jbrxm,"����������");
      }
    if('\0'== pst_gab_dxzp_sbxx->jbrdh[0] || 0 == strcmp(pst_gab_dxzp_sbxx->jbrdh," ") )
    	{
    		GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JBDH,pst_gab_dxzp_sbxx->jbrdh,"�����˵绰");
      }
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sbxx->ywrq,"ҵ������");
    
    /*ҵ����ˮ��*/
    memset(sSql, 0x00, sizeof(sSql));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_DXZP_XL,sSql,"ҵ����ˮ��");
    memset(&st_gab_dxzp_dual, 0x00, sizeof(st_gab_dxzp_dual));
    LOG(LM_STD, Fmtmsg("�Ǽ��´���Ϣ��->sfxt_xl[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet=fdbop_qry_dual(lXmlhandle, &st_gab_dxzp_dual, sSql);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "��ȡҵ����ˮ��");
    snprintf(pst_gab_dxzp_sbxx->ywlsh, sizeof(pst_gab_dxzp_sbxx->ywlsh), 
        "08%ld", st_gab_dxzp_dual.nextval);
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_JYJG,pst_gab_dxzp_sbxx->jbjg,"�������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_JYGY,pst_gab_dxzp_sbxx->jbgy,"�����Ա");
    /*��������*/
    strncpy(pst_gab_dxzp_sbxx->clrq,pst_gab_dxzp_sbxx->ywrq,8);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSTIME,pst_gab_dxzp_sbxx->clsj,"����ʱ��");
    /*�ϱ���¼��*/
    memset(sBuf,0x00,sizeof(sBuf));
    pst_gab_dxzp_sbxx->sbjls=1;
    /*�ϱ����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->sbjg);
    /*��Ӧ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->respcode);
    /*��Ӧ��Ϣ*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->respmsg);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sbxx->zwrq,"gaps����");
    

    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_sbxx->systime,GetSysTime());
    
    GAB_DXZP_GETXMLSTR_NOTNULL("/pub/zhqzlsh",pst_gab_dxzp_sbxx->zhqzlsh,"gaps��ˮ��");
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx->by3);
    

    return 0;
}



/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945111_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SAJB *pst_gab_dxzp_sajb)

 ��������:  ��¼����թƭ�����ٱ������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945111_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SAJB *pst_gab_dxzp_sajb)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sajb->sbpch,"�ϱ����κ�");
    pst_gab_dxzp_sajb->sbpcxh=1;
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_sajb->jybm,"���ױ���");
    /*���䱨����ˮ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->csbwlsh);
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sajb->ywsqbh,"���󵥱�ʶ");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_JSJGID,pst_gab_dxzp_sajb->jsjgid,"���ջ���ID");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_TGJGBM,pst_gab_dxzp_sajb->tgjgbm,"���ջ���ID");
    /*ҵ������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_sajb->ywlx,"ҵ������");
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SHRXM,pst_gab_dxzp_sajb->shrxm,"�ܺ�������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SHRLXDH,pst_gab_dxzp_sajb->shrlxdh,"�ܺ�����ϵ�绰");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJLX,pst_gab_dxzp_sajb->zjlx,"֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJHM,pst_gab_dxzp_sajb->zjhm,"֤����");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SJMS,pst_gab_dxzp_sajb->sjms,"�¼�����");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_AJJBLX,pst_gab_dxzp_sajb->ajjblx,"�����ٱ�����");
    
    /*��������*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_ZJRQ,pst_gab_dxzp_sajb->zjrq,"��������");
    /*������ˮ��*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_ZJLSH,pst_gab_dxzp_sajb->zjlsh,"������ˮ��");
    /*��ֹ���*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_DZXH,pst_gab_dxzp_sajb->dzxh,"��ֹ���");
    /*Ӱ���־*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_YXBZ,pst_gab_dxzp_sajb->yxbz,"Ӱ���־");
    /*����״̬*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->qqdzt);
    /*ִ�н��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->zxjg);
    /*������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->respcode);
    /*����ԭ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->respmsg);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sajb->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_sajb->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sajb->by3);
    

    return 0;
}


/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945112_Req(HXMLTREE lXmlhandle,  GAB_DXZP_YCKK *pst_gab_dxzp_yckk)

 ��������:  ��¼����թƭ�쳣������¼�����Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945112_Req(HXMLTREE lXmlhandle,  GAB_DXZP_YCKK *pst_gab_dxzp_yckk)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_yckk->sbpch,"�ϱ����κ�");
    pst_gab_dxzp_yckk->sbpcxh=1;
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_yckk->jybm,"���ױ���");
    
   /*���䱨����ˮ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->csbwlsh);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_yckk->ywsqbh,"���󵥱�ʶ");
    /*ҵ������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_yckk->ywlx,"ҵ������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SJTZM,pst_gab_dxzp_yckk->sjtzm,"�¼�������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_YYWSQBH,pst_gab_dxzp_yckk->yywsqbh,"ԭ�ϱ����");
   
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJLX,pst_gab_dxzp_yckk->zjlx,"֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJHM,pst_gab_dxzp_yckk->zjhm,"֤����");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_XM,pst_gab_dxzp_yckk->xm,"����");
    
    /*�˿���*/
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->zh);
    /*����ʱ��*/
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->kksj);
    /*�����ص�*/
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->kkdd);
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_yckk->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_yckk->systime,GetSysTime());
    

    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_yckk->by3);
    

    return 0;
}


/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945113_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SAZH *pst_gab_dxzp_sazh)

 ��������:  ��¼����թƭ�永�˻���¼�����Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945113_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SAZH *pst_gab_dxzp_sazh)
{
    int  iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sazh->sbpch,"�ϱ����κ�");
    pst_gab_dxzp_sazh->sbpcxh=1;
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_sazh->jybm,"���ױ���");
    /*���䱨����ˮ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->csbwlsh);
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sazh->ywsqbh,"���󵥱�ʶ");
    /*ҵ������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_sazh->ywlx,"ҵ������");
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->ywlx);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SJTZM,pst_gab_dxzp_sazh->sjtzm,"�¼�������");
   
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_YYWSQBH,pst_gab_dxzp_sazh->yywsqbh,"ԭ�ϱ����");
    
    //GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZH,pst_gab_dxzp_sazh->zh,"֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZHM,pst_gab_dxzp_sazh->zhm,"�˻���");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJLX,pst_gab_dxzp_sazh->zjlx,"֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJHM,pst_gab_dxzp_sazh->zjhm,"֤����");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_LXDH,pst_gab_dxzp_sazh->lxdh,"��ϵ�绰");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_TXDZ,pst_gab_dxzp_sazh->txdz,"ͨѶ��ַ");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YZBM,pst_gab_dxzp_sazh->yzbm,"��������");
   
    /*�˻�����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->zhlx);
    /*�˻�״̬*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->zhzt);
    /*��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->khrq);
    /*��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->xhrq);
    /*�����ص�*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->kkdd);
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sazh->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_sazh->systime,GetSysTime());
    
    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sazh->by3);
    

    return 0;
}

/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945114_Req(HXMLTREE lXmlhandle,  GAB_DXZP_YCSJ *pst_gab_dxzp_ycsj)

 ��������:  ��¼����թƭ�쳣�¼���¼�����Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945114_Req(HXMLTREE lXmlhandle,  GAB_DXZP_YCSJ *pst_gab_dxzp_ycsj)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_ycsj->sbpch,"�ϱ����κ�");
    pst_gab_dxzp_ycsj->sbpcxh=1;
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_ycsj->jybm,"���ױ���");
    /*���䱨����ˮ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->csbwlsh);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_ycsj->ywsqbh,"���󵥱�ʶ");
    /*ҵ������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_ycsj->ywlx,"ҵ������");
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ywlx);
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_SJTZM,pst_gab_dxzp_ycsj->sjtzm,"�¼�������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_CHANLE_YYWSQBH,pst_gab_dxzp_ycsj->yywsqbh,"ԭ�ϱ����");
    
    
    /*������ˮ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->jylsh);
    /*����ʱ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->jysj);
    /*��������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->jylx);
    /*����*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->bz);
    /*���׽��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->je);
    /*ת���˻��������л�������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->zcyhjg);
    /*ת���˻�������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->zcyhmc);
    /*ת���˻���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->zczhhm);
    /*ת���˿���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->zczh);
    /*���׶Զ��˻��������л�������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ddyhjg);
    /*���׶Զ��˻�������������*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ddyhmc);
    /*���׶Զ��˻���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ddzhm);
    /*���׶Զ��˿���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ddzh);
    /*ip��ַ*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->ipdz);
    /*mac��ַ*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->mac);
    /*�豸ID*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->sbid);
    /*���׵ص�*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->jydd);
    /*��ע*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->beiz);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_ycsj->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_ycsj->systime,GetSysTime());
    

    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ycsj->by3);
    

    return 0;
}

/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945115_Req(HXMLTREE lXmlhandle,  GAB_DXZP_ZHSA *pst_gab_dxzp_zhsa)

 ��������:  ��¼����թƭ�˻��永��¼�����Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945115_Req(HXMLTREE lXmlhandle,  GAB_DXZP_ZHSA *pst_gab_dxzp_zhsa)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_zhsa->jybm,"���ױ���");
    
    /*���䱨����ˮ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->csbwlsh);
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_zhsa->ywsqbh,"���󵥱�ʶ");
    /*ҵ������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_zhsa->ywlx,"ҵ������");
    iRet = xml_ElementExist(lXmlhandle, "/gabdxzp/yhkh2");
    if(1 == iRet)
    {
    	strncpy(pst_gab_dxzp_zhsa->ywlx,"0503",4);
    }
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->ywlx);
    /*���п���*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YHKH,pst_gab_dxzp_zhsa->zh,"���п���");
    //GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->zh);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZHM,pst_gab_dxzp_zhsa->zhm,"�˻���");
    /*���п���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->zt);

    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_zhsa->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_zhsa->systime,GetSysTime());
    

    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhsa->by3);
    

    return 0;
}


/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_945116_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SFSA *pst_gab_dxzp_sfsa)

 ��������:  ��¼����թƭ����永��¼�����Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_945116_Req(HXMLTREE lXmlhandle,  GAB_DXZP_SFSA *pst_gab_dxzp_sfsa)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_JYBM,pst_gab_dxzp_sfsa->jybm,"���ױ���");
    
    /*���䱨����ˮ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sfsa->csbwlsh);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,pst_gab_dxzp_sfsa->ywsqbh,"���󵥱�ʶ");
    /*ҵ������*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWLX,pst_gab_dxzp_sfsa->ywlx,"ҵ������");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJLX,pst_gab_dxzp_sfsa->zjlx,"֤������");
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJHM,pst_gab_dxzp_sfsa->zjhm,"֤����");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_ZJSYRXM,pst_gab_dxzp_sfsa->zhhm,"֤������������");
    
    /*״̬*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sfsa->zt);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sfsa->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_sfsa->systime,GetSysTime());
    

    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sfsa->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sfsa->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sfsa->by3);
    

    return 0;
}













/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_ZHXX_ZHJYXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHXX_ZHJYXX *pst_gab_dxzp_zhxx_zhjyxx,int i,int j)

 ��������:  ��¼����թƭ�˻���Ϣ_�˺Ž�����Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_ZHXX_ZHJYXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHXX_ZHJYXX *pst_gab_dxzp_zhxx_zhjyxx,int i,int j)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_YWSQBH,pst_gab_dxzp_zhxx_zhjyxx->ywsqbh,"���󵥱��");
    
    /*�������*/
    pst_gab_dxzp_zhxx_zhjyxx->rwxh=1;
    /*�˻����*/
    strcpy(pst_gab_dxzp_zhxx_zhjyxx->zhxh,"1");
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_ZHJYXH,pst_gab_dxzp_zhxx_zhjyxx->zhjyxh,"�˺Ž������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYLX,pst_gab_dxzp_zhxx_zhjyxx->jylx,"��������");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYYE,pst_gab_dxzp_zhxx_zhjyxx->jyye,"�������");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYSJ,pst_gab_dxzp_zhxx_zhjyxx->jysj,"����ʱ��");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYLSH,pst_gab_dxzp_zhxx_zhjyxx->jylsh,"������ˮ��");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYDFMC,pst_gab_dxzp_zhxx_zhjyxx->jydfmc,"���׶Է�����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYDFZH,pst_gab_dxzp_zhxx_zhjyxx->jydfzh,"���׶Է��˺�");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYDFZJHM,pst_gab_dxzp_zhxx_zhjyxx->jydfzjhm,"���׶Է�֤������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYDFZHKHH,pst_gab_dxzp_zhxx_zhjyxx->jydfzhkhh,"���׶Է��˺ſ�����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYZY,pst_gab_dxzp_zhxx_zhjyxx->jyzy,"����ժҪ");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYWDMC,pst_gab_dxzp_zhxx_zhjyxx->jywdmc,"������������");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYWDDM,pst_gab_dxzp_zhxx_zhjyxx->jywddm,"�����������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_RZH,pst_gab_dxzp_zhxx_zhjyxx->rzh,"��־��");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_CPH,pst_gab_dxzp_zhxx_zhjyxx->cph,"��Ʊ��");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_PZZL,pst_gab_dxzp_zhxx_zhjyxx->pzzl,"ƾ֤����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_PZH,pst_gab_dxzp_zhxx_zhjyxx->pzh,"ƾ֤��");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_XJBZ,pst_gab_dxzp_zhxx_zhjyxx->xjbz,"�ֽ��־");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_ZDH,pst_gab_dxzp_zhxx_zhjyxx->zdh,"�ն˺�");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYSFCG,pst_gab_dxzp_zhxx_zhjyxx->jysfcg,"�����Ƿ�ɹ�");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYFSD,pst_gab_dxzp_zhxx_zhjyxx->jyfsd,"���׷�����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_SHMC,pst_gab_dxzp_zhxx_zhjyxx->shmc,"�̻�����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_SHH,pst_gab_dxzp_zhxx_zhjyxx->shh,"�̻���");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_IP,pst_gab_dxzp_zhxx_zhjyxx->ip,"ip��ַ");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_MAC,pst_gab_dxzp_zhxx_zhjyxx->mac,"mac��ַ");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYGYH,pst_gab_dxzp_zhxx_zhjyxx->jygyh,"���׹�Ա��");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_BEIZ,pst_gab_dxzp_zhxx_zhjyxx->beiz,"��ע");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JDBZ,pst_gab_dxzp_zhxx_zhjyxx->jdbz,"�����־");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_BZ,pst_gab_dxzp_zhxx_zhjyxx->bz,"����");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_ZHXX_ZHJYXX_JYJE,pst_gab_dxzp_zhxx_zhjyxx->jyje,"���׽��");
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_zhxx_zhjyxx->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_zhxx_zhjyxx->systime,GetSysTime());
    

    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhxx_zhjyxx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhxx_zhjyxx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhxx_zhjyxx->by3);
    

    return 0;
}













/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_ZHJBXX_ZHXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx,int i)

 ��������:  ��¼����թƭ�˻��˻�������Ϣ_�˺���Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_ZHJBXX_ZHXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_YWSQBH,pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,"���󵥱��");
    
    /*�������*/
    pst_gab_dxzp_zhjbxx_zhxx->rwxh=1;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZHXH,pst_gab_dxzp_zhjbxx_zhxx->zhxh,"�˻����");
    //trim(sBuf);
    //pst_gab_dxzp_zhjbxx_zhxx->zhxh=atoi(sBuf);
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZH,pst_gab_dxzp_zhjbxx_zhxx->zh,"�˺�");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZHLX,pst_gab_dxzp_zhjbxx_zhxx->zhlx,"�˻�����");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZHZT,pst_gab_dxzp_zhjbxx_zhxx->zhzt,"�˻�״̬");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_BZ,pst_gab_dxzp_zhjbxx_zhxx->bz,"����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_CHBZ,pst_gab_dxzp_zhjbxx_zhxx->chbz,"�����־");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZHYE,pst_gab_dxzp_zhjbxx_zhxx->zhye,"�˻����");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_KYYE,pst_gab_dxzp_zhjbxx_zhxx->kyye,"�������");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_ZHJBXX_ZHXX_ZHJYSJ,pst_gab_dxzp_zhjbxx_zhxx->zhjysj,"�����ʱ��");
 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_zhjbxx_zhxx->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_zhjbxx_zhxx->systime,GetSysTime());
    

    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by3);
    

    return 0;
}











/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_QHCX_ZHXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx,int i)

 ��������:  ��¼����թƭ�˻��˻�������Ϣ_�˺���Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_QHCX_ZHXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_ZHJBXX_ZHXX *pst_gab_dxzp_zhjbxx_zhxx,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QHCX_ZHXX_YWSQBH,pst_gab_dxzp_zhjbxx_zhxx->ywsqbh,"���󵥱��");
    
    /*�������*/
    pst_gab_dxzp_zhjbxx_zhxx->rwxh=1;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_ZHXH,pst_gab_dxzp_zhjbxx_zhxx->zhxh,"�˻����");

    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_ZH,pst_gab_dxzp_zhjbxx_zhxx->zh,"�˺�");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_ZHLX,pst_gab_dxzp_zhjbxx_zhxx->zhlx,"�˻�����");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_ZHZT,pst_gab_dxzp_zhjbxx_zhxx->zhzt,"�˻�״̬");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_BZ,pst_gab_dxzp_zhjbxx_zhxx->bz,"����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_CHBZ,pst_gab_dxzp_zhjbxx_zhxx->chbz,"�����־");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_ZHYE,pst_gab_dxzp_zhjbxx_zhxx->zhye,"�˻����");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHXX_KYYE,pst_gab_dxzp_zhjbxx_zhxx->kyye,"�������");
    
 
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_zhjbxx_zhxx->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_zhjbxx_zhxx->systime,GetSysTime());
    

    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_zhjbxx_zhxx->by3);
    

    return 0;
}
















/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_JYMX_ZHJBXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx)

 ��������:  ��¼����թƭ�˻��˻�������Ϣ_�˺���Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_JYMX_ZHJBXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_YWSQBH,pst_gab_dxzp_jymx_zhjbxx->ywsqbh,"���󵥱��");
    
    /*�������*/
    pst_gab_dxzp_jymx_zhjbxx->rwxh=1;
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_ZHM,pst_gab_dxzp_jymx_zhjbxx->zhm,"�˻���");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_KZH,pst_gab_dxzp_jymx_zhjbxx->kzh,"��/�ۺ�");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_KHWD,pst_gab_dxzp_jymx_zhjbxx->khwd,"��������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_KHWDDM,pst_gab_dxzp_jymx_zhjbxx->khwddm,"�����������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_KHRQ,pst_gab_dxzp_jymx_zhjbxx->khrq,"��������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_XHRQ,pst_gab_dxzp_jymx_zhjbxx->xhrq,"��������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_XHWD,pst_gab_dxzp_jymx_zhjbxx->xhwd,"��������");
    /*GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_ZHJYSJ,pst_gab_dxzp_jymx_zhjbxx->zhjysj,"�����ʱ��");*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_JYMX_ZHJBXX_BEIZ,pst_gab_dxzp_jymx_zhjbxx->beiz,"��ע");
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jymx_zhjbxx->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_jymx_zhjbxx->systime,GetSysTime());
    

    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by3);
    

    return 0;
}













/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_QHCX_SFQZXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_QHCX_SFQZXX *pst_gab_dxzp_qhcx_sfqzxx,int i)

 ��������:  ��¼����թƭȫ����ѯ_˾��ǿ����Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_QHCX_SFQZXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_QHCX_SFQZXX *pst_gab_dxzp_qhcx_sfqzxx,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QHCX_SFQZXX_YWSQBH,pst_gab_dxzp_qhcx_sfqzxx->ywsqbh,"���󵥱��");
    /*�������*/
    pst_gab_dxzp_qhcx_sfqzxx->rwxh=1;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_CSXH,pst_gab_dxzp_qhcx_sfqzxx->csxh,"��ʩ���");
    
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_ZH,pst_gab_dxzp_qhcx_sfqzxx->zh,"�˺�");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_KH,pst_gab_dxzp_qhcx_sfqzxx->kh,"��/�ۺ�");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_DJKSR,pst_gab_dxzp_qhcx_sfqzxx->djksr,"���Ὺʼ��");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_DJJZR,pst_gab_dxzp_qhcx_sfqzxx->djjzr,"�����ֹ��");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_DJJGMC,pst_gab_dxzp_qhcx_sfqzxx->djjgmc,"�����������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_BZ,pst_gab_dxzp_qhcx_sfqzxx->bz,"����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_DJJE,pst_gab_dxzp_qhcx_sfqzxx->djje,"������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_BEIZ,pst_gab_dxzp_qhcx_sfqzxx->beiz,"��ע");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_SFQZXX_DJCSLX,pst_gab_dxzp_qhcx_sfqzxx->djcslx,"�����ʩ����");
    
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_qhcx_sfqzxx->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_qhcx_sfqzxx->systime,GetSysTime());
    

    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_sfqzxx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_sfqzxx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_sfqzxx->by3);
    

    return 0;
}
















/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_QHCX_ZZHXX_Resp(HXMLTREE lXmlhandle, GAB_DXZP_QHCH_ZZHXX *pst_gab_dxzp_qhcx_zzhxx,int i)
 ��������:  ��ȡ����թƭȫ����ѯ-���˺���Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_QHCX_ZZHXX_Resp(HXMLTREE lXmlhandle, GAB_DXZP_QHCX_ZZHXX *pst_gab_dxzp_qhcx_zzhxx,int i,int j)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QHCX_ZZHXX_YWSQBH,pst_gab_dxzp_qhcx_zzhxx->ywsqbh,"ҵ��������");
    /*�������*/
    pst_gab_dxzp_qhcx_zzhxx->rwxh=i;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZZHXH,pst_gab_dxzp_qhcx_zzhxx->zzhxh,"���˻����");
   
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZH,pst_gab_dxzp_qhcx_zzhxx->zh,"�ˣ�������");
    
    /*ҵ������*/
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZZHLB,pst_gab_dxzp_qhcx_zzhxx->zzhlb,"���˻����");
    
    //GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZZHZH,pst_gab_dxzp_qhcx_zzhxx->zzhzh,"���˻��˺�");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_BZ,pst_gab_dxzp_qhcx_zzhxx->bz,"����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_CHBZ,pst_gab_dxzp_qhcx_zzhxx->chbz,"�����־");
        /*�˻����*/
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZHYE,pst_gab_dxzp_qhcx_zzhxx->zhye,"�˻����");
      /*�˻�״̬*/
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZHZT,pst_gab_dxzp_qhcx_zzhxx->zhzt,"�˻�״̬");
    /*�������*/
    GAB_DXZP_GETXMLSTR_NULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_KYYE,pst_gab_dxzp_qhcx_zzhxx->kyye,"�������");
    /*�����ʱ��*/
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2(XMLNM_GAB_DXZP_QHCX_ZZHXX_ZHJYSJ,pst_gab_dxzp_qhcx_zzhxx->zhjysj,"�����ʱ��");

    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_qhcx_zzhxx->zwrq,"gaps����");
    
    /*gapsʱ��*/
   
    strcpy(pst_gab_dxzp_qhcx_zzhxx->systime,GetSysTime());
    
     /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_zzhxx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_zzhxx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_zzhxx->by3);
    
    return 0;
}
/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_QHCX_QLXX_Resp(HXMLTREE lXmlhandle, GAB_DXZP_QHCX_QLXX *pst_gab_dxzp_qhcx_qlxx,int i)
 ��������:  ��ȡ����թƭȫ����ѯ-���˺���Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_QHCX_QLXX_Resp(HXMLTREE lXmlhandle, GAB_DXZP_QHCX_QLXX *pst_gab_dxzp_qhcx_qlxx,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

     
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QHCX_QLXX_YWSQBH,pst_gab_dxzp_qhcx_qlxx->ywsqbh,"ҵ��������");
    /*�������*/
    pst_gab_dxzp_qhcx_qlxx->rwxh=1;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_XH,pst_gab_dxzp_qhcx_qlxx->xh,"���");
    
 
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_ZH,pst_gab_dxzp_qhcx_qlxx->zh,"�˺�");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_KH,pst_gab_dxzp_qhcx_qlxx->kh,"�ʿ���");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_ZJLX,pst_gab_dxzp_qhcx_qlxx->zjlx,"֤�����ʹ���");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_ZJHM,pst_gab_dxzp_qhcx_qlxx->zjhm,"֤������");
    
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_QLLX,pst_gab_dxzp_qhcx_qlxx->qllx,"Ȩ������");
    
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_QLRXM,pst_gab_dxzp_qhcx_qlxx->qlrxm,"Ȩ��������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_QLJE,pst_gab_dxzp_qhcx_qlxx->qlje,"Ȩ�����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_QLRTXDZ,pst_gab_dxzp_qhcx_qlxx->qlrtxdz,"Ȩ����ͨѶ��ַ");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_QLXX_QLRLXFS,pst_gab_dxzp_qhcx_qlxx->qlrlxfs,"Ȩ������ϵ��ʽ");
  
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_qhcx_qlxx->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_qhcx_qlxx->systime,GetSysTime());
   
    
     /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_qlxx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_qlxx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_qhcx_qlxx->by3);
    
    return 0;
}
/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_DTCX_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_DTCX_RESP *pst_gab_dxzp_dtcx_resp,int i)
 ��������:  ��ȡ����թƭ��̬��ѯ��Ӧ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_DTCX_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_DTCX_RESP *pst_gab_dxzp_dtcx_resp,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

     
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DTCX_RESP_SBPCH,pst_gab_dxzp_dtcx_resp->sbpch,"�ϱ����κ�");
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_SBPCXH,sBuf,"�ϱ��������");
    trim(sBuf);
    pst_gab_dxzp_dtcx_resp->sbpcxh=atoi(sBuf);
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DTCX_RESP_YWSQBH,pst_gab_dxzp_dtcx_resp->ywsqbh,"ҵ��������");
    /*�������*/
    //pst_gab_dxzp_dtcx_resp->rwxh=1;
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/dccs",sBuf,"�������");
    trim(sBuf);
    if('\0'==sBuf[0])
    	{
    	   pst_gab_dxzp_dtcx_resp->rwxh=1;
    	}
    else
    	{
    		 pst_gab_dxzp_dtcx_resp->rwxh=atoi(sBuf)+1;
    	}
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTCX_RESP_ZHM,pst_gab_dxzp_dtcx_resp->zhm,"�˻���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DTCX_RESP_CXZH,pst_gab_dxzp_dtcx_resp->zh,"�˺�");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYLX,pst_gab_dxzp_dtcx_resp->jylx,"��������");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JDBZ,pst_gab_dxzp_dtcx_resp->jdbz,"�����־");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_BZ,pst_gab_dxzp_dtcx_resp->bz,"����");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYJE,pst_gab_dxzp_dtcx_resp->jyje,"���׽��");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYYE,pst_gab_dxzp_dtcx_resp->jyye,"�������");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYSJ,pst_gab_dxzp_dtcx_resp->jysj,"����ʱ��");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYLSH,pst_gab_dxzp_dtcx_resp->jylsh,"������ˮ��");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYDFMC,pst_gab_dxzp_dtcx_resp->jydfmc,"���׶Է�����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYDFZH,pst_gab_dxzp_dtcx_resp->jydfzh,"���׶Է��˺�");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYDFZJHM,pst_gab_dxzp_dtcx_resp->jydfzjhm,"���׶Է�֤������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYDFZHKHH,pst_gab_dxzp_dtcx_resp->jydfzhkhh,"���׶Է��˻�������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYZY,pst_gab_dxzp_dtcx_resp->jyzy,"����ժҪ");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYWDMC,pst_gab_dxzp_dtcx_resp->jywdmc,"������������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYWDDM,pst_gab_dxzp_dtcx_resp->jywddm,"�����������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_RZH,pst_gab_dxzp_dtcx_resp->rzh,"��־��");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_CPH,pst_gab_dxzp_dtcx_resp->cph,"��Ʊ��");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_PZZL,pst_gab_dxzp_dtcx_resp->pzzl,"ƾ֤����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_PZH,pst_gab_dxzp_dtcx_resp->pzh,"ƾ֤��");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_XJBZ,pst_gab_dxzp_dtcx_resp->xjbz,"�ֽ��־");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_ZDH,pst_gab_dxzp_dtcx_resp->zdh,"�ն˺�");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYSFCG,pst_gab_dxzp_dtcx_resp->jysfcg,"�����Ƿ�ɹ�");
    
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYFSD,pst_gab_dxzp_dtcx_resp->jyfsd,"���׷�����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_MAC,pst_gab_dxzp_dtcx_resp->mac,"mac��ַ");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_JYGYH,pst_gab_dxzp_dtcx_resp->jygyh,"���׹�Ա��");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_BEIZ,pst_gab_dxzp_dtcx_resp->beiz,"��ע");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_SHMC,pst_gab_dxzp_dtcx_resp->shmc,"�̻�����");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_SHH,pst_gab_dxzp_dtcx_resp->shh,"�̻���");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_IP,pst_gab_dxzp_dtcx_resp->ip,"ip��ַ");

    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTCX_RESP_FKJGMC,pst_gab_dxzp_dtcx_resp->fkjgmc,"������������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTCX_RESP_FKSM,pst_gab_dxzp_dtcx_resp->fksm,"��ѯ����˵��");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_dtcx_resp->zwrq,"gaps����");
    
    /*gapsʱ��*/
   strcpy(pst_gab_dxzp_dtcx_resp->systime,GetSysTime());
   
   
     /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx_resp->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx_resp->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtcx_resp->by3);
    
    return 0;
}
/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_DTJC_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_DTJC_RESP *pst_gab_dxzp_dtjc_resp)
 ��������:  ��ȡ����թƭ��̬�����Ӧ��Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_DTJC_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_DTJC_RESP *pst_gab_dxzp_dtjc_resp)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DTJC_RESP_YWSQBH,pst_gab_dxzp_dtjc_resp->ywsqbh,"ҵ��������");
    /*�������*/
    pst_gab_dxzp_dtjc_resp->rwxh=1;
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTJC_RESP_JCDTCXSM,pst_gab_dxzp_dtjc_resp->jcdtcxsm,"�����̬��ѯ˵��");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTJC_RESP_FKSM,pst_gab_dxzp_dtjc_resp->fksm,"����˵��");


    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_dtjc_resp->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_dtjc_resp->systime,GetSysTime());
   
    
     /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtjc_resp->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtjc_resp->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_dtjc_resp->by3);
    
    return 0;
}
/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_ZTCX_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_ZTCX_RESP *pst_gab_dxzp_ztcx_resp)
 ��������:  ��ȡ����թƭ�����ѯ��Ӧ��Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_ZTCX_RESP_Resp(HXMLTREE lXmlhandle, GAB_DXZP_ZTCX_RESP *pst_gab_dxzp_ztcx_resp)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZTCX_RESP_YWSQBH,pst_gab_dxzp_ztcx_resp->ywsqbh,"ҵ��������");
    /*�������*/
    pst_gab_dxzp_ztcx_resp->rwxh=1;
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_FKJGMC,pst_gab_dxzp_ztcx_resp->fkjgmc,"������������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_FKSM,pst_gab_dxzp_ztcx_resp->fksm,"��ѯ����˵��");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZTCX_RESP_ZJLX,pst_gab_dxzp_ztcx_resp->zjlx,"��ѯ֤�����ʹ���");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZTCX_RESP_ZJHM,pst_gab_dxzp_ztcx_resp->zjhm,"��ѯ֤������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZTCX_RESP_ZTMC,pst_gab_dxzp_ztcx_resp->ztmc,"��ѯ��������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_ZTCX_RESP_LXSJ,pst_gab_dxzp_ztcx_resp->lxsj,"��ϵ�ֻ�");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DBRXM,pst_gab_dxzp_ztcx_resp->dbrxm,"��/������������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DBRZJLX,pst_gab_dxzp_ztcx_resp->dbrzjlx,"��/��������֤������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DBRZJHM,pst_gab_dxzp_ztcx_resp->dbrzjhm,"��/��������֤������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_ZZDZ,pst_gab_dxzp_ztcx_resp->zzdz,"סլ��ַ");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_ZZDH,pst_gab_dxzp_ztcx_resp->zzdh,"סլ�绰");
    
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_GZDW,pst_gab_dxzp_ztcx_resp->gzdw,"������λ");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DWDZ,pst_gab_dxzp_ztcx_resp->dwdz,"��λ��ַ");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DWDH,pst_gab_dxzp_ztcx_resp->dwdh,"��λ�绰");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_YXDZ,pst_gab_dxzp_ztcx_resp->yxdz,"�����ַ");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_FRDB,pst_gab_dxzp_ztcx_resp->frdb,"���˴���");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_FRDBZJLX,pst_gab_dxzp_ztcx_resp->frdbzjlx,"���˴���֤������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_FRDBZJHM,pst_gab_dxzp_ztcx_resp->frdbzjhm,"���˴���֤������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_KHGSZZHM,pst_gab_dxzp_ztcx_resp->khgszzhm,"�ͻ�����ִ�պ���");

    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_GSNSH,pst_gab_dxzp_ztcx_resp->gsnsh,"��˰��˰��");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_ZTCX_RESP_DSNSH,pst_gab_dxzp_ztcx_resp->dsnsh,"��˰��˰��");

  
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_ztcx_resp->zwrq,"gaps����");
    
    /*gapsʱ��*/
   strcpy(pst_gab_dxzp_ztcx_resp->systime,GetSysTime());
   
    
     /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx_resp->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx_resp->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_ztcx_resp->by3);
    
    return 0;
}









/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_SMJFJ_Req(HXMLTREE lXmlhandle, GAB_DXZP_SMJFJ *pst_gab_dxzp_smjfj)
 ��������:  ��ȡ����թƭɨ���������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_SMJFJ_Req(HXMLTREE lXmlhandle, GAB_DXZP_SMJFJ *pst_gab_dxzp_smjfj)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_APPLICATIONID,pst_gab_dxzp_smjfj->ywsqbh,"ҵ��������");
    
    /*���*/
    pst_gab_dxzp_smjfj->xh=1;
    /*�ļ���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_smjfj->wjm);
    /*�ļ���С*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_smjfj->wjdx);
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_smjfj->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_smjfj->systime,GetSysTime());
   
   
     /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_smjfj->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_smjfj->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_smjfj->by3);
    
    return 0;
}










/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_SBXX_PLZT_Req(HXMLTREE lXmlhandle, GAB_DXZP_SBXX_PLZT *pst_gab_dxzp_sbxx_plzt,int i)
 ��������:  ��ȡ����թƭɨ���������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_SBXX_PLZT_Req(HXMLTREE lXmlhandle, GAB_DXZP_SBXX_PLZT *pst_gab_dxzp_sbxx_plzt,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];

    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_DTCX_RESP_SBPCH,pst_gab_dxzp_sbxx_plzt->sbpch,"�ϱ����κ�");
    memset(sBuf,0x00,sizeof(sBuf));
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_DTCX_RESP_SBPCXH,sBuf,"�ϱ��������");
    trim(sBuf);
    pst_gab_dxzp_sbxx_plzt->sbpcxh=atoi(sBuf);
   
   
    /*�ϱ����״���*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->sbjydm);
    /*�ϱ�״̬*/
    strcpy(pst_gab_dxzp_sbxx_plzt->sbzt,"0");
    /*��Ӧ��*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->respcode);

    /*��Ӧ��Ϣ*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->respmsg);

    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_sbxx_plzt->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_sbxx_plzt->systime,GetSysTime());
   
   
     /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_sbxx_plzt->by3);
    
    return 0;
}





/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_QHCX_ZHJBXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx,int i)

 ��������:  ��¼����թƭ�˻��˻�������Ϣ_�˺���Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_QHCX_ZHJBXX_Resp(HXMLTREE lXmlhandle,  GAB_DXZP_JYMX_ZHJBXX *pst_gab_dxzp_jymx_zhjbxx,int i)
{
    int iRet = -1;
    char sBuf[256];
    char sOriTransTime[10 + 1];
   
   
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QHCX_ZHJBXX_YWSQBH,pst_gab_dxzp_jymx_zhjbxx->ywsqbh,"ҵ��������");
    
    /*�������*/
    pst_gab_dxzp_jymx_zhjbxx->rwxh=i;
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_ZHM,pst_gab_dxzp_jymx_zhjbxx->zhm,"�˻���");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_KZH,pst_gab_dxzp_jymx_zhjbxx->kzh,"��/�ۺ�");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_KHWD,pst_gab_dxzp_jymx_zhjbxx->khwd,"��������");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_KHWDDM,pst_gab_dxzp_jymx_zhjbxx->khwddm,"�����������");
    GAB_DXZP_GETXMLSTR_NOTNULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_KHRQ,pst_gab_dxzp_jymx_zhjbxx->khrq,"��������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_XHRQ,pst_gab_dxzp_jymx_zhjbxx->xhrq,"��������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_XHWD,pst_gab_dxzp_jymx_zhjbxx->xhwd,"��������");
    GAB_DXZP_GETXMLSTR_NULL_MULTI(XMLNM_GAB_DXZP_QHCX_ZHJBXX_BEIZ,pst_gab_dxzp_jymx_zhjbxx->beiz,"��ע");
    
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,pst_gab_dxzp_jymx_zhjbxx->zwrq,"gaps����");
    
    /*gapsʱ��*/
    strcpy(pst_gab_dxzp_jymx_zhjbxx->systime,GetSysTime());
    

    /*����1*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_jymx_zhjbxx->by3);
    

    return 0;
}

















enum {
  LF = 0xA,
  CR = 0xD,
  NL = '\n',
  default_maxlen = 76,
  eq_sign = 100,
  pad_idx = 64
};

const char g_EncTable[] =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/=";

const int g_DecTable[] = {
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,-1,-1,-1,-1,-1,-1,-1,
        -1,-1,-1,62,-1,-1,-1,63,52,53,
        54,55,56,57,58,59,60,61,-1,-1,
        -1, eq_sign, -1,-1,-1, 0, 1, 2, 3, 4,
         5, 6, 7, 8, 9,10,11,12,13,14,
        15,16,17,18,19,20,21,22,23,24,
        25,-1,-1,-1,-1,-1,-1,26,27,28,
        29,30,31,32,33,34,35,36,37,38,
        39,40,41,42,43,44,45,46,47,48,
        49,50,51,-1
};

const int g_DecTableSz = sizeof(g_DecTable) / sizeof(char);

static int fpub_b64_encode(int _idx, unsigned char *ch, char **_out, int *pos, int maxlen)
{
  int pad_count = 3 - _idx;
  int i, len = 0;
  int idx[4];
  char *out = *_out;

  idx[0] = ch[0] >> 2;
  switch(pad_count)
  {
  case 0:
    idx[1] = (((ch[0] & 3) << 4) |  (ch[1] >> 4));
    idx[2] = ((ch[1] & 0xf) << 2) | (ch[2] >> 6);
    idx[3] = ch[2] & 0x3f;
    break;
  case 1:
    idx[1] = (((ch[0] & 3) << 4) |  (ch[1] >> 4));
    idx[2] = (ch[1] & 0xf) << 2 ;
    idx[3] = pad_idx;
    break;
  case 2:
    idx[1] = (ch[0] & 3) << 4;
    idx[2] = idx[3] = pad_idx;
    break;
  }
  for(i = 0; i < 4; ++i)
  {
    *out++ = g_EncTable[ idx[i] ];
    len++;
    ++(*pos);
    if (maxlen > 0 && *pos > maxlen) {
      *out++ = NL;
      len++;
      *pos = 1;
    }
  }
  *_out = out;
  return len;
}

char * fpub_base64_encode(char *src, int *size, int maxlen)
{
  unsigned char ch[3];
  char *_ret = NULL;
  char *r;
  int idx = 0;
  int len, i;
  int outsize = 0;
  int pos = 1;

  len = (*size) / 3 * 4 + 4;
  if (maxlen > 0)
    len += ((len / maxlen) + 1);
  _ret = (char *)malloc(len+1);
  if (_ret == NULL)
    return NULL;
  r = _ret;
  memset(r, 0, len+1);

  for(i = 0; i < *size; i++)
  {
    ch[idx++] = (unsigned char)src[i];
    if(idx < 3)
      continue;
    outsize += fpub_b64_encode(idx, ch, &r, &pos, maxlen);
    idx = 0;
  }
  if(idx > 0)
  {
    outsize += fpub_b64_encode(idx, ch, &r, &pos, maxlen);
  }
  *size = outsize;
  return _ret;
}

static int fpub_b64_decode(int idx, unsigned char *ch, char **_out)
{
  char *out = *_out;
  int len = 0;

  if(idx < 4)
  {
    switch(idx)
    {
    case 0:
    case 1:
      return len;
    case 2:
      ch[2] = ch[3] = eq_sign;
      break;
    case 3:
      ch[3] = eq_sign;
      break;
    }
  }
  *out++ = (ch[0] << 2 | ((ch[1] >> 4) & 0x3) );
  len++;
  if(ch[2] == eq_sign)
    return len;
  *out++ = (ch[1] << 4 | ((ch[2] >> 2) & 0xF) );
  len++;
  if(ch[3] == eq_sign)
    return len;
  *out++ = (ch[2] << 6 | ch[3]);
  len++;

  *_out = out;
  return len;
}

/*****************************************************
   ��������:  char * fpub_base64_decode(char *src, int *size)
   ��������:  base64ת��
   ��������:
       char *src    Դ��
       int  *size   Ŀ�괮����


   ��������:   NULL ʧ��
              !NULL �ɹ�


   ����˵��:


   �޸�˵��:
*****************************************************/
char * fpub_base64_decode(char *src, int *size)
{
     unsigned char c;
     char *_ret = NULL;
     char *r;
     unsigned char ch[4];
     int idx = 0;
     int len, i;
     int outsize = 0;

     len = (*size) / 4 * 3+1;
     _ret = (char *)malloc(len+1);
     if (_ret == NULL)
       return NULL;
     r = _ret;
     memset(r, 0, len+1);

     for(i = 0; i < *size; i++)
     {
       c = (unsigned char)src[i];
       if(c > g_DecTableSz || g_DecTable[c] == -1)
         continue;
       ch[idx++] = g_DecTable[c];
       if(idx < 4)
         continue;
       outsize += fpub_b64_decode(idx, ch, &r);
       idx = 0;
     }
     if(idx > 0)
       outsize += fpub_b64_decode(idx, ch, &r);
     *size = outsize;
     return _ret;
}
int convert(char *src, char *dest, char *input, size_t ilen, char *output, size_t *olen)
{
    char **pin = &input;
    char **pout = &output;
    iconv_t cd = iconv_open(dest, src);
    if (cd == (iconv_t)-1)
    {
        return -1;
    }
    if (iconv(cd, pin, &ilen, pout, olen))
    {
        iconv_close(cd);
        return -2;
    }
    iconv_close(cd);
    return 0;
}
/*****************************************************
 ��������:  int ffunc_gabdxzp_getMoveHours(HXMLTREE lXmlhandle, char *psOldDateTime, int iMoveHours, char *psNewDateTime, int iNewDateTime)

 ��������:  ����ƫ�ƺ�����ʱ��
 ��������:  lXmlhandle           XML���
            psOldDateTime        ԭ����ʱ��
            iMoveHours           ƫ��Сʱ��
            psNewDateTime        ������ʱ��

 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ReturnDate(char *currdate,int steps)
{
	time_t  now,time1;
	int retdate,ndays=0,n;
	struct tm *ptm,tm1;
	char yy[5],mm[3],dd[3];

	memset(yy,0,sizeof(yy));
	memset(mm,0,sizeof(mm));
	memset(dd,0,sizeof(dd));
	memcpy(yy,currdate,4);yy[4]=0;
	memcpy(mm,currdate+4,2);mm[2]=0;
	memcpy(dd,currdate+6,2);dd[2]=0;
	ndays=steps;

	time(&now);
	tm1 = *localtime(&now);
	tm1.tm_year = atoi(yy)-1900;
  	tm1.tm_mon = atoi(mm)-1;
  	tm1.tm_mday = atoi(dd);
	time1 = mktime(&tm1);

	n=(int)(difftime(time1,now)/(60*60*24));
	ndays+=n;
  	now += ndays * 3600 * 24;
  	if(ndays >0)
  		now -=3600;

  	ptm = localtime(&now);
  	retdate = (ptm->tm_year+1900) * 10000 + (ptm->tm_mon + 1) * 100 + ptm->tm_mday;
	return retdate;
}

int ffunc_gabdxzp_getMoveHours(HXMLTREE lXmlhandle, char *psOldDateTime, int iMoveHours, char *psNewDateTime, int iNewDateTime)
{
    int iHours=0;
    int iDays=0,iHour=0;
    char sOldDate[8+1];/*��׼����*/
    char sOldTime[6+1];/*��׼Сʱ*/
    char sHours[2+1];
    char sBuf[256];
    char sDesDate[8+1];
    char sDayTime[14+1];
    
    /*��ȡԭ��׼���ںͻ�׼ʱ��*/
    memset(sOldDate, 0x00, sizeof(sOldDate));
    pstrcopy(sOldDate, psOldDateTime, sizeof(sOldDate));
    memset(sOldTime, 0x00, sizeof(sOldTime));
    pstrcopy(sOldTime, psOldDateTime+8, sizeof(sOldTime));
    
    /*��ȡ��׼Сʱ*/
    memset(sHours, 0x00, sizeof(sHours));
    strncpy(sHours, sOldTime, 2);
    /*����ƫ��Сʱ=��׼Сʱ + ƫ��Сʱ��*/
    iHours = atoi(sHours) + iMoveHours;
    iDays = iHours / 24;
    /*�������Сʱ=ƫ��Сʱ - N����*/
    iHour = iMoveHours - ( iDays*24 );
    iHours = iHours - ( iDays*24 );
    /*����ƫ������*/
	memset(sDesDate,0,sizeof(sDesDate));
	snprintf(sDesDate, sizeof(sDesDate), "%d",ReturnDate(sOldDate,iDays));
    /*����ƫ������ʱ��*/
    memset(psNewDateTime, 0x00, iNewDateTime);
    snprintf(psNewDateTime, iNewDateTime, "%s%02d%4s", sDesDate, iHours, sOldTime+2);
    
    return 0;
}
/*****************************************************
 ��������:  int ffunc_gabdxzp_getMoveMins(HXMLTREE lXmlhandle, char *psOldDateTime, int iMoveHours, char *psNewDateTime, int iNewDateTime)

 ��������:  ������ǰ���ڷ���
 ��������:  lXmlhandle           XML���
            psOldDateTime        ԭ����ʱ��
            iMoveMins            ��ǰ������
            psNewDateTime        ������ʱ��

 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getMoveMins(HXMLTREE lXmlhandle, char *psOldDateTime, int iMoveMins, char *psNewDateTime, int iNewDateTime)
{
    char sCurDate[8+1];
    char sCurTime[6+1];
    char sBuf[256];
    char sNewDate[8+1];
    char sCurMM[2+1];
    int iTimes=0;
    int iDays=0;
    int iHours=0;
    int iCurHours=0;
    int iAddHours=0;
    int iMins=0;
    int iCurMins=0;
    int iAddMins=0;

    memset(sCurDate, 0x00, sizeof(sCurDate));
    strncpy(sCurDate, psOldDateTime, sizeof(sCurDate)-1);
    memset(sCurTime, 0x00, sizeof(sCurTime));
    strncpy(sCurTime, psOldDateTime+8, sizeof(sCurTime)-1);
    iTimes = iMoveMins;
    /*��ȡ��ǰСʱ�ͷ���*/
    memset(sBuf, 0x00, sizeof(sBuf));
    strncpy(sBuf, sCurTime, 2);
    iCurHours=atoi(sBuf);
    memset(sBuf, 0x00, sizeof(sBuf));
    strncpy(sBuf, sCurTime+2, 2);
    iCurMins=atoi(sBuf);
    /*������ǰ����*/
    iDays = iTimes / 1440;
    if ( iDays > 0 )
    {/*��ǰN��*/
        memset(sNewDate, 0x00, sizeof(sNewDate));
        iDays *= -1;
        snprintf(sNewDate, sizeof(sNewDate), "%d", ReturnDate(sCurDate,iDays));
        strncpy(sCurDate, sNewDate, sizeof(sCurDate)-1);
        iTimes += iDays * 1440;
        /*printf("Ӧ��ǰ[%d]���,iTime[%d]\n", iDays, iTimes);*/
    }
    /*������ǰСʱ��*/
    iHours = iTimes / 60;
    /*printf("iHours[%d] = iTimes[%d]/60;\n", iHours, iTimes);*/
    if ( iHours > 0 )
    {/*��ǰNСʱ*/
        iAddHours = iCurHours - iHours ;
        if ( iAddHours < 0 )
        {/*��Ҫ��һ��*/
            memset(sNewDate, 0x00, sizeof(sNewDate));
            snprintf(sNewDate, sizeof(sNewDate), "%d", ReturnDate(sCurDate,-1));
            strncpy(sCurDate, sNewDate, sizeof(sCurDate)-1);
            iCurHours += iAddHours;
        }else
        {
            iCurHours = iAddHours;
        }
        /*printf("Now=[%s%02d%02d]\n", sCurDate, iCurHours, iCurMins);*/
        iTimes -= iHours * 60;
    }
    /*������ǰN����*/
    iAddMins = iCurMins - iTimes;
    if ( iAddMins < 0 )
    {/*��Ҫ��һСʱ*/
        iCurMins = iAddMins + 60;
        iCurHours -= 1;
        iAddHours = iCurHours;
        if ( iAddHours < 0 )
        {/*��Ҫ��һ��*/
            memset(sNewDate, 0x00, sizeof(sNewDate));
            snprintf(sNewDate, sizeof(sNewDate), "%d", ReturnDate(sCurDate,-1));
            strncpy(sCurDate, sNewDate, sizeof(sCurDate)-1);
            /*alter iAddHours-->24 by liukq 20160428 BEGIN*/
            iCurHours += 24;
            /*alter by liukq 20160428 END*/
        }else
        {
            iCurHours = iAddHours;
        }
        /*printf("Now=[%s%02d%02d]\n", sCurDate, iCurHours, iCurMins);*/
    }else
    {
        iCurMins = iAddMins;
    }
    snprintf(psNewDateTime, iNewDateTime, "%s%02d%02d%s", sCurDate, iCurHours, iCurMins, sCurTime+4);
    return 0;
}

/* dci �����װ���� */
/* ��ѯһ����¼���ṹ���� */
/*
����: ��ѯ���������ṹ��
����ֵ:
    <0 ʧ��
    =0 ���޼�¼
    >0 ��ѯ�ɹ�
*/
int ffunc_dbop_selToStruct( const char* sSql, FLD_DESC desc_arr[], int desc_num, void* pdes)
{
    CURSOR cur;
    char szErrMsg[512];

    if( sSql == NULL || pdes == NULL || desc_arr == NULL || desc_num <= 0)
    {
        LOG(LM_STD, Fmtmsg("���������"), "WARNING");
        return -1;
    }
    cur = DCIDeclareCursor( sSql, DCI_DEFAULT);
    if (cur == INVALID_CURSOR)
    {
        LOG(LM_STD, Fmtmsg("�α궨��ʧ��[%s]-[%s]",  DCILastError(), sSql), "ERROR");
        return -2;
    }
    if(DCIExecute(cur) == -1)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��[%s]", DCILastError() ), "ERROR");
        DCIFreeCursor(cur);
        return -3;
    }

    int rs = 0;
    if( 0 > ( rs = DBFetch( cur, desc_arr, desc_num, pdes, szErrMsg ) ) )
    {
        LOG(LM_STD, Fmtmsg("�α��ȡ��¼����[%s]",  szErrMsg ), "ERROR");
        DCIFreeCursor(cur);
        return -4;
    }
    DCIFreeCursor(cur);  /*����©��*/
    return rs;
}

/* dci �����װ���� */
/* ������ִ���α� */
/*
����: ������ִ���α�
����ֵ:
    <0 ʧ��
    =0 �ɹ�
*/
int ffunc_dbop_dcrExecCursor(HXMLTREE lXmlhandle, const char* psSql, char *psCurSorName, CURSOR *cur)
{
    if ((*cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("��%s�α�ʧ��", psCurSorName),fpub_GetCompname(lXmlhandle));
    }
    if (DCIExecute(*cur) == -1)
    {
        DCIFreeCursor(*cur);
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("ִ��%s�α�ʧ��", psCurSorName),fpub_GetCompname(lXmlhandle));
    }
    return 0;
}

/* �ͷ��α� */
/*
����: �ͷ��α�
����ֵ:
    <0 ʧ��
    =0 �ɹ�
*/
int ffunc_dbop_freeCursor(HXMLTREE lXmlhandle, char *psCurSorName, CURSOR *cur)
{
    if (DCIFreeCursor(*cur) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("�ͷ�%s�α�ʧ��", psCurSorName),fpub_GetCompname(lXmlhandle));
    }
    return 0;
}

/*****************************************************
   ��������:  int ffunc_file_crtLocalPath(HXMLTREE lXmlhandle, char* psFilePath)
   ��������:  ���������ļ�Ŀ¼
   ��������:  
              psFilePath   �ļ�·��(����·��)                 
              
   ��������:  ����: 0
              ����:

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int ffunc_file_crtLocalPath(HXMLTREE lXmlhandle, char* psFilePath)
{
	FILE *fp;
	char sFileName[256];
	int iRet = -1;
    
    if ( !psFilePath || psFilePath[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("�ļ�·�������������Ϊ��" ));
        return -1;
    }
    
    memset(sFileName, 0x00, sizeof(sFileName));
    snprintf(sFileName, sizeof(sFileName), "%s/%s", psFilePath, "a.txt");
    iRet = access(sFileName, F_OK);
    if ( iRet != 0  )
    {
        /*�����ļ�·��*/
        iRet = mkdir(psFilePath, S_IRWXU+S_IRGRP+S_IWGRP+S_IROTH);
        if ( iRet != 0 )
        {
            fpub_SetMsg(lXmlhandle, 99002, Fmtmsg("�ļ�����ʧ��[%s]", strerror(errno)));
            LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�ļ�����ʧ��[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle)); 
        }
        /*����a.txt�ļ�*/
        fp = fopen(sFileName,"w");
        if ( fp == NULL )
        {	
            fpub_SetMsg(lXmlhandle, 99002, Fmtmsg("�ļ�����ʧ��[%s]", strerror(errno)));
            LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�ļ�����ʧ��[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle)); 
        }
        fclose(fp);
    }        
	return 0;		
}

/*****************************************************
   ��������:  int ffunc_file_wrtFile(HXMLTREE lXmlhandle, char* psFilePath)
   ��������:  ���������ļ�Ŀ¼
   ��������:  
              psFilePath   �ļ�·��(����·��)                 
              
   ��������:  ����: 0
              ����:

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int ffunc_file_wrtFile(HXMLTREE lXmlhandle, char* psFileName, char *psFileConent, int iFileLen)
{
	FILE *fp;
	int iRet = -1;
    
    if ( !psFileName || psFileName[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("�ļ�·�������������Ϊ��" ));
        return -1;
    }
    /*�����ļ�*/
    fp = fopen(psFileName,"w");
    if ( fp == NULL )
    {	
        fpub_SetMsg(lXmlhandle, 99002, Fmtmsg("�ļ�����ʧ��[%s]", strerror(errno)));
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("�ļ�����ʧ��[%s]", strerror(errno)), fpub_GetCompname(lXmlhandle)); 
    }
    fwrite(psFileConent, iFileLen, 1, fp);
    fclose(fp);
    return 0;
}

/*****************************************************
   ��������:  int ffunc_file_getFileName(HXMLTREE lXmlhandle, char* psAbsFileName, char* psFileName)
   ��������:  �Ӿ���·���ļ��л�ȡ�ļ�����
   ��������:  
              psAbsFileName   �ļ�����(����·��)  
              psFileName      �ļ�����               
              
   ��������:  ����: 0
              ����:

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int ffunc_file_getFileName(HXMLTREE lXmlhandle, char* psAbsFileName, char* psFileName)
{
	char sFileName[256];
	int iRet = -1;
	int iAbsLen = 0;
	int iFound = 0;
	int i;
    
    if ( !psAbsFileName || psAbsFileName[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("�����ļ����Ʋ���Ϊ��" ));
        return -1;
    }
    
    iAbsLen = strlen(psAbsFileName);
    for ( i=iAbsLen; i>=0; i--)
    {
        if ( psAbsFileName[i] == '/')
        {
            iFound = 1;
            break;
        }
        continue;
    }
    if ( iFound == 1 && psFileName )
    {
        pstrcopy(psFileName, psAbsFileName + i + 1, iAbsLen - i);
    }
        
	return 0;		
}

/*****************************************************
   ��������:  int ffunc_file_getFileSize(HXMLTREE lXmlhandle, char* psFileName, int* iFileSize)
   ��������:  ��ȡ�ļ���С
   ��������:  
              psFileName   �ļ���(����·��)
              iFileSize    �ļ���С
              
   ��������:  ����: 0
              ����:

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int ffunc_file_getFileSize(HXMLTREE lXmlhandle, char* psFileName, int* iFileSize)
{
	FILE *fp;
    struct stat struStat;
    
    if ( !psFileName || psFileName[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("�ļ�������Ϊ��" ));
        return -1;
    }
    
    fp = fopen(psFileName,"r");
    if ( fp == NULL )
    {	
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_FILEOP, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)));
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)), fpub_GetCompname(lXmlhandle)); 
    }
    fstat(fileno(fp), &struStat);
    
    *iFileSize = struStat.st_size;
    fclose(fp);
    
	return 0;		
}
/*****************************************************
   ��������:  char* ffunc_file_getFileContents(HXMLTREE lXmlhandle)
   ��������:  ��ȡ�ļ�����
   ��������:  
              psFileName   �ļ���(����·��)
              iFileSize    �ļ���С                  
              
   ��������:  ����: �ļ�����ָ��,�����ⲿfree
              ����:

   ����˵��:  

   �޸�˵��:  
*****************************************************/
char*  ffunc_file_getFileContents(HXMLTREE lXmlhandle, char* psFileName, int *iFileSize)
{
    char *psFileContents = NULL;
    FILE *fp;
    caddr_t pUpfileHead;
    struct stat struStat;
    int iRet = -1;
    
    if ( !psFileName || psFileName[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("�ļ�������Ϊ��" ));
        return NULL;
    }
    
    iRet = ffunc_file_getFileSize(lXmlhandle, psFileName, iFileSize);
    if ( iRet < 0 )
    {
        LOG(LM_STD, Fmtmsg("��ȡ�ļ���Сʧ��[%d]", iRet), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }
    psFileContents = (char *)malloc(*iFileSize+1);
    if (psFileContents == NULL)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_MALLOC, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }
    memset(psFileContents, 0x00, *iFileSize+1);
    
    fp = fopen(psFileName,"rb");
    if ( fp == NULL )
    {	
        free(psFileContents);psFileContents=NULL;
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_FILEOP, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }
    if ((pUpfileHead = mmap(NULL, (size_t)*iFileSize, PROT_READ, MAP_SHARED, fileno(fp), (off_t)0)) == (caddr_t) - 1)
    {
        free(psFileContents);psFileContents=NULL;
        munmap(pUpfileHead, (size_t)*iFileSize);
        fclose(fp);	
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_MALLOC, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_MALLOC, *iFileSize), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }

    pstrcopy(psFileContents, pUpfileHead, *iFileSize+1);
    munmap(pUpfileHead, (size_t)*iFileSize);
    fclose(fp);
    
    return psFileContents;
}
/*****************************************************
   ��������:  char* ffunc_file_getJPEGContents(HXMLTREE lXmlhandle)
   ��������:  ��ȡӰ������
   ��������:  
              psFileName   �ļ���(����·��)
              iFileSize    �ļ���С                  
              
   ��������:  ����: �ļ�����ָ��,�����ⲿfree
              ����:

   ����˵��:  

   �޸�˵��:  
*****************************************************/
char*  ffunc_file_getJPEGContents(HXMLTREE lXmlhandle, char* psFileName, int *iFileSize)
{
    char *psFileContents = NULL;
    FILE *fp;
    struct stat struStat;
    char sFileCont[10240];
    int iRet = -1;
    
    if ( !psFileName || psFileName[0] == '\0')
    {
        fpub_SetMsg( lXmlhandle, 99001, Fmtmsg("�ļ�������Ϊ��" ));
        return NULL;
    }
    
    iRet = ffunc_file_getFileSize(lXmlhandle, psFileName, iFileSize);
    if ( iRet < 0 )
    {
        LOG(LM_STD, Fmtmsg("��ȡ�ļ���Сʧ��[%d]", iRet), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }
    psFileContents = (char *)malloc(*iFileSize+1);
    if (psFileContents == NULL)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_MALLOC, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }
    memset(psFileContents, 0x00, *iFileSize+1);

    fp = fopen(psFileName,"rb");
    if ( fp == NULL )
    {	
        free(psFileContents);psFileContents=NULL;
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_FILEOP, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    } 
    iRet=fread(psFileContents,(size_t)*iFileSize,1 ,fp);
    LOG(LM_STD, Fmtmsg("1------[%d]-[%d]---", iRet, *iFileSize), fpub_GetCompname(lXmlhandle)); 
    /*if ( strlen(psFileContents) > 0)
    {
        free(psFileContents);psFileContents=NULL;
        LOG(LM_STD, Fmtmsg("1----[%s]------",strerror(errno)), fpub_GetCompname(lXmlhandle));
        fclose(fp);	
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_MALLOC, Fmtmsg(MSG_GAB_DXZP_MALLOC, iFileSize));
        LOG(LM_STD, Fmtmsg(MSG_GAB_DXZP_MALLOC, *iFileSize), fpub_GetCompname(lXmlhandle)); 
        return NULL;
    }*/
LOG(LM_STD, Fmtmsg("2----------"), fpub_GetCompname(lXmlhandle));
    fclose(fp);
    
    return psFileContents;
}
/*****************************************************
   ��������:  int ffunc_dxzp_945118_DTCX_hxqs(HXMLTREE lXmlhandle, char *sSql)
   ��������:  ��̬��ѯ����ȡ��
   ��������:  
              sSql   ��̬��ѯ���              
              
   ��������:  ����: 0
              ����:

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int ffunc_dxzp_945118_DTCX_hxqs(HXMLTREE lXmlhandle, char *psSql, char *psCurDateTime)
{
    int  iParas;
    char sBuf[256];
    char errmsg[256];
    char sOriQqdZt[2+1];
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    CURSOR cur;
    GAB_DXZP_AUTOPROC gab_dxzp_autoproc;
    GAB_DXZP_XDXX gab_dxzp_xdxx;
    GAB_DXZP_DTCX gab_dxzp_dtcx;
    
    /* ��ѯ��Ҫ��������� */
    if ((cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    for ( i=1; ; i++)
    {
        memset(&gab_dxzp_autoproc, 0x00, sizeof(gab_dxzp_autoproc));
        iRet = DBFetch(cur, SD_GAB_DXZP_AUTOPROC, NUMELE(SD_GAB_DXZP_AUTOPROC), &gab_dxzp_autoproc, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        
        if (gab_dxzp_autoproc.qqdzt[1] == '9' && gab_dxzp_autoproc.qqdzt[0] != '9')
        {/*���ڴ�����,ȡһ����¼*/
            continue;
        }
        /*alter 22-->30 by liukq 20160426 BEGIN*/
        if (strcmp(gab_dxzp_autoproc.qqdzt, "30") == 0 ||
            strcmp(gab_dxzp_autoproc.qqdzt, "40") == 0 )
        {/*���ڴ�����,ȡһ����¼*/
            continue;
        }
        /*alter by liukq 20160426 END*/
        memset(&gab_dxzp_dtcx, 0x00, sizeof(gab_dxzp_dtcx));
         /*add by liukq 20160324 BEGIN*/
        GAB_DXZP_PSTRCOPY(gab_dxzp_dtcx.ywsqbh, gab_dxzp_autoproc.ywsqbh)
        gab_dxzp_dtcx.rwxh=1;
        iRet = fdbop_qry_gab_dxzp_dtcx(lXmlhandle,&gab_dxzp_dtcx);
        if ( iRet < 0 )
        {
            continue;
        }
        /*add by liukq 20160324 END*/
        if (strcmp(gab_dxzp_autoproc.qqdzt, "99") == 0 )
        {/*42--���ϱ�ǰ�����ݺ�,�����ò�ѯ��ʼʱ��Ϊ�ϴβ�ѯ��ֹʱ��*/
            GAB_DXZP_PSTRCOPY(gab_dxzp_dtcx.dtcxqssj, gab_dxzp_dtcx.dtcxjzsj)
        }
        memset(&gab_dxzp_xdxx, 0x00, sizeof(gab_dxzp_xdxx));
        GAB_DXZP_PSTRCOPY(gab_dxzp_xdxx.ywsqbh, gab_dxzp_autoproc.ywsqbh)
        memset(sOriQqdZt, 0x00, sizeof(sOriQqdZt));
        GAB_DXZP_PSTRCOPY(sOriQqdZt, gab_dxzp_autoproc.qqdzt)
        GAB_DXZP_PSTRCOPY(gab_dxzp_xdxx.qqdzt, "20")
        iRet = fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &gab_dxzp_xdxx, sOriQqdZt);
        if ( iRet < 0 )
        {
            continue;
        }
        /*alter by liukq 20160324 BEGIN
        memset(&gab_dxzp_dtcx, 0x00, sizeof(gab_dxzp_dtcx));
        
        GAB_DXZP_PSTRCOPY(gab_dxzp_dtcx.ywsqbh, gab_dxzp_autoproc.ywsqbh)
        gab_dxzp_dtcx.rwxh=1;
        alter by liukq 20160324 END*/
        GAB_DXZP_PSTRCOPY(gab_dxzp_dtcx.dtcxjzsj, psCurDateTime)
        iRet = fdbop_upd_gab_dxzp_dtcx_qzsj(lXmlhandle, &gab_dxzp_dtcx);
        DCICommit();
        if ( iRet < 0 )
        {
            continue;
        }
        /* ����������Ϣ��ֵ */
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_YWSQBH, gab_dxzp_autoproc.ywsqbh);/*ҵ��������*/
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_CLLX, "2");/*��������*/
        LOG(LM_STD,Fmtmsg("�������ô�����ҵ������flow_gabdxzp_945117����,ywsqbh[%s],jjcd[%s],qqdzt[%s]",
            gab_dxzp_autoproc.ywsqbh, gab_dxzp_autoproc.jjcd, gab_dxzp_autoproc.qqdzt),"INFO");
        /* ���ô�����ҵ����� */
        if(fpub_CallFlow(lXmlhandle,"subflow_gabdxzp_945117")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("���ô�����ҵ������flow_gabdxzp_945117[%s]ʧ��",
                gab_dxzp_autoproc.ywsqbh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("ִ�д�����ҵ������ʧ��"));
            return COMPRET_FAIL ;
        }
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    LOG(LM_STD,Fmtmsg("����թƭ��̬��ѯ����ȡ��,������[%d]��ҵ��", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"����թƭ��̬��ѯ����ȡ��ִ�н���");
    return COMPRET_SUCC;
}


/*****************************************************
   ��������:  int ffunc_dxzp_945118_DTCX_fkqz(HXMLTREE lXmlhandle, char *sSql)
   ��������:  ��̬��ѯ����ǰ��
   ��������:  
              sSql   ��̬��ѯ���              
              
   ��������:  ����: 0
              ����:

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int ffunc_dxzp_945118_DTCX_fkqz(HXMLTREE lXmlhandle, char *psSql, char *psCurDateTime)
{
    int  iParas;
    char sBuf[256];
    char errmsg[256];
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    char sOriQqdZt[2+1];
    CURSOR cur;
    GAB_DXZP_AUTOPROC gab_dxzp_autoproc;
    GAB_DXZP_XDXX gab_dxzp_xdxx;
    
    /* ��ѯ��Ҫ��������� */
    if ((cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    for ( i=1; ; i++)
    {
        memset(&gab_dxzp_autoproc, 0x00, sizeof(gab_dxzp_autoproc));
        iRet = DBFetch(cur, SD_GAB_DXZP_AUTOPROC, NUMELE(SD_GAB_DXZP_AUTOPROC), &gab_dxzp_autoproc, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
         
        if (gab_dxzp_autoproc.qqdzt[1] == '9'  )
        {/*���ڴ�����,ȡһ����¼*/
            continue;
        }
        
        memset(&gab_dxzp_xdxx, 0x00, sizeof(gab_dxzp_xdxx));
        GAB_DXZP_PSTRCOPY(gab_dxzp_xdxx.ywsqbh, gab_dxzp_autoproc.ywsqbh)
        iRet = fdbop_qry_gab_dxzp_xdxx(lXmlhandle, &gab_dxzp_xdxx);
        if ( iRet < 0 )
        {
            continue;
        }
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_YWSQBH, gab_dxzp_autoproc.ywsqbh);
        /* ����������Ϣ��ֵ */
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_SBPCH, gab_dxzp_xdxx.sbpch);/*�ϱ����κ�*/
        LOG(LM_STD,Fmtmsg("�������ô�����ҵ������flow_gabdxzp_945122����,sbpch[%s]",
            gab_dxzp_xdxx.sbpch),"INFO");
        /* ���ô�����ҵ����� */
        if(fpub_CallFlow(lXmlhandle,"flow_gabdxzp_945122")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("����������Ϣ�ϱ�ҵ������flow_gabdxzp_945122[%s]ʧ��",
                gab_dxzp_autoproc.ywsqbh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("����������Ϣ�ϱ�ҵ������ʧ��"));
            return COMPRET_FAIL ;
        }
        memset(sOriQqdZt, 0x00, sizeof(sOriQqdZt));
        GAB_DXZP_PSTRCOPY(sOriQqdZt, gab_dxzp_xdxx.qqdzt)
        GAB_DXZP_PSTRCOPY(gab_dxzp_xdxx.qqdzt, "99")
        iRet = fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &gab_dxzp_xdxx, sOriQqdZt);
        DCICommit();
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("����թƭ��̬��ѯ����ǰ��,������[%d]��ҵ��", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"����թƭ��̬��ѯ����ǰ��ִ�н���");
    return COMPRET_SUCC;
}

/*****************************************************
   ��������:  int ffunc_dxzp_DTCX_sstsfk(HXMLTREE lXmlhandle, char *sSql)
   ��������:  ��̬��ѯ����ǰ��
   ��������:  
              sSql   ��̬��ѯ���              
              
   ��������:  ����: 0
              ����:

   ����˵��:  

   �޸�˵��:  
*****************************************************/
int ffunc_dxzp_DTCX_sstsfk(HXMLTREE lXmlhandle, char *psSql, char *psCurDateTime)
{
    int  iParas;
    char sBuf[256];
    char errmsg[256];
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    char sOriQqdZt[2+1];
    CURSOR cur;
    GAB_DXZP_AUTOPROC gab_dxzp_autoproc;
    GAB_DXZP_XDXX gab_dxzp_xdxx;
    
    /* ��ѯ��Ҫ��������� */
    if ((cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    for ( i=1; ; i++)
    {
        memset(&gab_dxzp_autoproc, 0x00, sizeof(gab_dxzp_autoproc));
        iRet = DBFetch(cur, SD_GAB_DXZP_AUTOPROC, NUMELE(SD_GAB_DXZP_AUTOPROC), &gab_dxzp_autoproc, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        
        memset(&gab_dxzp_xdxx, 0x00, sizeof(gab_dxzp_xdxx));
        GAB_DXZP_PSTRCOPY(gab_dxzp_xdxx.ywsqbh, gab_dxzp_autoproc.ywsqbh)
        iRet = fdbop_qry_gab_dxzp_xdxx(lXmlhandle, &gab_dxzp_xdxx);
        if ( iRet < 0 )
        {
            continue;
        }
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_YWSQBH, gab_dxzp_autoproc.ywsqbh);
        /* ����������Ϣ��ֵ */
        LOG(LM_STD,Fmtmsg("�������ö�̬��ѯʵʱ��������flow_gabdxzp_945108_2����,sbpch[%s]",
            gab_dxzp_xdxx.sbpch),"INFO");
        /* ���ô�����ҵ����� */
        if(fpub_CallFlow(lXmlhandle,"flow_gabdxzp_945108_2")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("����������Ϣ�ϱ�ҵ������flow_gabdxzp_945108_2[%s]ʧ��",
                gab_dxzp_autoproc.ywsqbh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("����������Ϣ�ϱ�ҵ������ʧ��"));
            return COMPRET_FAIL ;
        }
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("����թƭ��̬��ѯ����ǰ��,������[%d]��ҵ��", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"����թƭ��̬��ѯ����ǰ��ִ�н���");
    return COMPRET_SUCC;
}



/*****************************************************
   ��������:  int GetItemValueT(char *src, char *split, char *out, int index)
   ��������:  ��̬��ѯ����ǰ��
   ��������:  
                       
              
   ��������:  

   ����˵��:  

   �޸�˵��:  
*****************************************************/


char *GetItemValueT(char *src, char *split, char *out, int index)
{
  char *p=NULL;
  int n = 0;
  int nFlag = 0; /* 0Ϊ��ʼֵ��1Ϊ������� */
  char srctmp[1+1];
  unsigned char uc;
  char *pStr=NULL;
  pStr = src;
  int indexflag = 0;
  
  /* ���ҵ���index���ָ�����λ�� */
    while(indexflag < index)
    {
        while(*pStr != NULL)
          {
              uc = (unsigned char)*pStr;
            if (nFlag == 1)
            {
                /* ǰһ��Ϊ������֣���ô��ο϶�Ҫ����ʣ�µİ������ */
                nFlag = 0;
            }
            else
            {
                /* ǰһ�β�Ϊ���ֵ���� */
                /* �ж���ε��ַ��Ƿ�Ϊ������ֵ���� */
                if(uc >= 0x81 && uc <= 0xFE && nFlag == 0) /* ���ֵ���� */
                {
                    nFlag = 1;
                }
                else
                {
                    /* ���Ҳ��Ϊ������ֵ���� */
                    if ((strncmp(pStr, split, strlen(split)) == 0))//��һ��$����
                	   {
                	   	pStr ++;
                	   	if ((strncmp(pStr, split, strlen(split)) == 0))//�жϵڶ����Ƿ�Ϊ$��
                	   		{                                            //
                	   			 break;                                    
                	   		}                                            //
                	   	else                                           //���ڶ�������$��
                	   		{                                            //
                	   			pStr --;                                   //ָ��ָ��ǰһ��
                	   		}                                            //
                	   }
                }
            }
            
            *pStr ++;
          }
        indexflag++;
        *pStr ++;
    }
  
  /*LOG(LM_DEBUG,Fmtmsg("---pStr[%s]---", pStr),"INFO")*/
  while(*pStr != NULL){
        /* ���ܰ������ֵ���� */
        /* ��������Ӵ�������֡��|���|�����ְ�����ֵ���� */
        /*if ((strncmp(pStr, split, strlen(split)) == 0) && (index != 2))
            break;*/
        
        memset(srctmp, 0, sizeof(srctmp));
        strncpy(srctmp, pStr, 1);
        /*LOG(LM_DEBUG,Fmtmsg("srctmp[%s]  pStr[%s] [%d]", srctmp, pStr,nFlag),"INFO")*/
        
        uc = (unsigned char)*pStr;
        if (nFlag == 1)
        {
            /* ǰһ��Ϊ������֣���ô��ο϶�Ҫ����ʣ�µİ������ */
            nFlag = 0;
        }
        else
        {
            /* ǰһ�β�Ϊ���ֵ���� */
            /* �ж���ε��ַ��Ƿ�Ϊ������ֵ���� */
            if(uc >= 0x81 && uc <= 0xFE && nFlag == 0) /* ���ֵ���� */
            {
                nFlag = 1;
              
            }
            else
            {
                /* ���Ҳ��Ϊ������ֵ���� */
                if ((strncmp(pStr, split, strlen(split)) == 0))//��һ��$����
                	{
                		pStr ++;//
                		if ((strncmp(pStr, split, strlen(split)) == 0))//�жϵڶ����Ƿ�Ϊ$��
                			{                                            //
                				 break;                       
                			}                                            //
                		else                                           //���ڶ�������$��
                			{                                            //
                				pStr --;                                   //ָ��ָ��ǰһ��
                			}                                            //
                	}
                   
            }
        }

    
    
    out[n++] = *pStr ++;
  }
  
  /*LOG(LM_DEBUG,Fmtmsg("out��%s��", out),"INFO")*/
  out[n] = 0;
  return out;
}
















/*****************************************************
 ��������:  int ffunc_gabdxzp_getXml_HHMD(HXMLTREE lXmlhandle, GAB_DXZP_HHMD *pst_gab_dxzp_hhmd)
 ��������:  ��ȡ����թƭɨ���������Ϣ
 ��������:  lXmlhandle           XML���


 ��������:  0   :�ɹ�
 -1  :ʧ��

 ����˵��:

 �޸�˵��:
 *****************************************************/
int ffunc_gabdxzp_getXml_HHMD(HXMLTREE lXmlhandle, GAB_DXZP_HHMD *pst_gab_dxzp_hhmd,char *sbuf)
{
    int iRet = -1;
    /*��������*/
		GetItemValueT(sbuf, "$" ,pst_gab_dxzp_hhmd->mdlx, 0); 
		trim(pst_gab_dxzp_hhmd->mdlx);
		/*������ֵ*/
		GetItemValueT(sbuf, "$" ,pst_gab_dxzp_hhmd->mdjz, 1); 
		trim(pst_gab_dxzp_hhmd->mdjz); 
		
		/*������Դ*/
		GetItemValueT(sbuf, "$" ,pst_gab_dxzp_hhmd->mdly, 3); 
		trim(pst_gab_dxzp_hhmd->mdly); 
		/*��������*/
		GetItemValueT(sbuf, "$" ,pst_gab_dxzp_hhmd->ajlx, 4); 
		trim(pst_gab_dxzp_hhmd->ajlx); 
		/*����*/
		GetItemValueT(sbuf, "$" ,pst_gab_dxzp_hhmd->xm, 5); 
		trim(pst_gab_dxzp_hhmd->xm); 
		/*��������*/
		GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_hhmd->mdjb);
		/*��������*/
		strcpy(pst_gab_dxzp_hhmd->gxrq,GetSysDate());
		/*����ʱ��*/
		strcpy(pst_gab_dxzp_hhmd->gxsj,GetSysTime());
		/*����1*/
		GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_hhmd->by1);
    /*����2*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_hhmd->by2);
    /*����3*/
    GAB_DXZP_FIELD_SETNULLTOBLANK(pst_gab_dxzp_hhmd->by3);
        
    return 0;
}




/*****************************************************
   ��������:  int ffunc_date_getNow()
   ��������:  ��ȡ��ǰϵͳʱ���
   ��������:     
       
              
              
   ��������:  ����: 0    �ɹ�
              ����: < 0  ����

   ����˵��:  
              ��ȡ��ǰϵͳʱ���
              
              snprintf(sBuf, sizeof(sBuf), "%s", ffunc_date_getNow());
   �޸�˵��:  
*****************************************************/
char* ffunc_date_getNow()
{
    struct timeb tp;
    struct tm *tm;
    static char sTimeStamp[64];
    
    ftime(&tp);
    tm = localtime(&tp.time);
    memset(sTimeStamp, 0x00, sizeof(sTimeStamp));
    snprintf(sTimeStamp, sizeof(sTimeStamp), "%4d-%02d-%02d %02d:%02d:%02d.%.3d",
            1900+ tm->tm_year,
            1 + tm->tm_mon,
            tm->tm_mday,
            tm->tm_hour,
            tm->tm_min,
            tm->tm_sec,
            tp.millitm
            );
    return sTimeStamp;
}
