/********************************************************************
 ��Ȩ����:�������ӹɷ����޹�˾�����ݣ�
 ��Ŀ����:��������������թƭǰ����Ŀ(GABDXZP4.1)
 ��    ��:V2.1.0.1
 ����ϵͳ:
 �ļ�����:GAB_ZP_C.c
 �ļ�����:����թƭ�����
 �� �� Ա:tuql
 ��������:2015-9-29
 �� �� Ա:
 �޸�����:
 �޸�˵��: 
 *********************************************************************/
#include "gaps_head.h"
#include "gabdxzp_head.h"
#include "gabdxzp_alltables.h"
#include <string.h>

char * fpub_base64_decode(char *src, int *size);
char * fpub_base64_encode(char *src, int *size, int maxlen);
#define SOCOMPVERSION "V2.0.0.1"
#define SOCOMPBUILDNO "V2.0.0.1"
#define  MAXSIZE 1024*1024  /*1M*/
/************************************************************************
 ��̬�����������
 �����������:ShowSocompVersion
 �������:����汾��ں���
 ************************************************************************/
IRESULT ShowSocompVersion(char *sinfo, int isize)
{
    char sversion[] =
        "<?xml version=\"1.0\" encoding=\"GB2312\"?>\
   <root>\
      <soname>GAB_ZP_C.so</soname>\
      <sosrcname>GAB_ZP_C.*c </sosrcname>\
      <sonote>����������թƭ����ģ��</sonote>\
      <version>\
         <rec ver=\"2.0.0.1\" modify=\"2016-01-21 09:08\" programer=\"����������թƭǰ�ò�Ʒ��\" filesize=\"1000\">��Ԫ�������</rec>\
      </version>\
   </root>";
    printf("\n================��̬���������Ϣ================\n");
    printf("SOCOMPBUILDNO:%s.\n", SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n", SOCOMPVERSION);
    printf("%s-%s\n", __PROJECTSNAME, __VERSION);
    if (strlen(sversion) >= isize)
    {
        printf(" -->ȡ��ϸ��Ϣʧ��...\n");
        return -2;
    }
    strcpy(sinfo, sversion);
    printf(" -->��鿴��ϸ��Ϣ...\n");
    return 0;
}

/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_XDXX_INS
 �������:�Ǽ��´���Ϣ��
 �������:�Ǽ��´���Ϣ��
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_XDXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    GAB_DXZP_XDXX st_gab_dxzp_xdxx;/*�´���Ϣ��*/

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("�Ǽ��´���Ϣ��->��ʼ����"), fpub_GetCompname(lXmlhandle));
    /*1.װ���´���Ϣ��*/
    memset(&st_gab_dxzp_xdxx, 0x00, sizeof(st_gab_dxzp_xdxx));
    iRet = ffunc_gabdxzp_getXml_XDXX_Req(lXmlhandle, &st_gab_dxzp_xdxx);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ���´���Ϣ��");
    LOG(LM_STD, Fmtmsg("�Ǽ��´���Ϣ��->���װ���´���Ϣ��"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*3.�Ǽ��´���Ϣ��*/
    iRet = fdbop_ins_gab_dxzp_xdxx(lXmlhandle, &st_gab_dxzp_xdxx);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽ��´���Ϣ��");
    LOG(LM_STD, Fmtmsg("�Ǽ��´���Ϣ��->��ɵǼ��´���Ϣ��"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, st_gab_dxzp_xdxx.qqdzt)
    COMP_SOFTSETXML(XMLNM_SFXT_HOST_REQ_CLLX, "2")
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ��´���Ϣ��->����ɹ�[%s]", st_gab_dxzp_xdxx.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_JJZF_INS
 �������:�Ǽǽ���ֹ����
 �������:�Ǽǽ���ֹ����
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_JJZF_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char JJZF_JYDM[10];
    GAB_DXZP_JJZF st_gab_dxzp_jjzf;/*ֹ����ֹ��*/

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("�Ǽǽ���ֹ����->��ʼ����"), fpub_GetCompname(lXmlhandle));
    /*2.װ��ֹ����ֹ��*/
    memset(&st_gab_dxzp_jjzf, 0x00, sizeof(st_gab_dxzp_jjzf));
    GAB_DXZP_GETXMLSTR_NOTNULL("/pub/jydm",JJZF_JYDM,"���״���");
    if(0==strcmp(JJZF_JYDM,"945100"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945100_Req(lXmlhandle, &st_gab_dxzp_jjzf);
    	}
    if (0==strcmp(JJZF_JYDM,"945101"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945101_Req(lXmlhandle, &st_gab_dxzp_jjzf);
    	}
    if(0==strcmp(JJZF_JYDM,"945102"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945102_Req(lXmlhandle, &st_gab_dxzp_jjzf);
    	} 
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ��ֹ����ֹ��");
    LOG(LM_STD, Fmtmsg("�Ǽǽ���ֹ����->���װ��ֹ����ֹ��"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.�Ǽ�ֹ����ֹ��*/
    iRet = fdbop_ins_gab_dxzp_jjzf(lXmlhandle, &st_gab_dxzp_jjzf);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽ�ֹ����ֹ��");
    LOG(LM_STD, Fmtmsg("�Ǽǽ���ֹ����->��ɵǼ�ֹ����ֹ��"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽǽ���ֹ����->����ɹ�[%s]",st_gab_dxzp_jjzf.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}





/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_DJXJ_INS
 �������:�ǼǶ��������
 �������:�ǼǶ��������
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_DJXJ_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char DJXJ_JYDM[10];
    GAB_DXZP_DJXJ st_gab_dxzp_djxj;/*ֹ����ֹ��*/

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("�ǼǶ��������->��ʼ����"), fpub_GetCompname(lXmlhandle));
    /*2.װ�ض��������*/
    memset(&st_gab_dxzp_djxj, 0x00, sizeof(st_gab_dxzp_djxj));
    GAB_DXZP_GETXMLSTR_NOTNULL("/pub/jydm",DJXJ_JYDM,"���״���");
    if(0==strcmp(DJXJ_JYDM,"945103"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945103_Req(lXmlhandle, &st_gab_dxzp_djxj);
    	}
    if (0==strcmp(DJXJ_JYDM,"945104"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945104_Req(lXmlhandle, &st_gab_dxzp_djxj);
    	}
    if(0==strcmp(DJXJ_JYDM,"945105"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945105_Req(lXmlhandle, &st_gab_dxzp_djxj);
    	} 
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ض��������");
    LOG(LM_STD, Fmtmsg("�ǼǶ��������->���װ�ض��������"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.�ǼǶ��������*/
    iRet = fdbop_ins_gab_dxzp_djxj(lXmlhandle, &st_gab_dxzp_djxj);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�ǼǶ��������");
    LOG(LM_STD, Fmtmsg("�ǼǶ��������->��ɵǼǶ��������"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�ǼǶ��������->����ɹ�[%s]",st_gab_dxzp_djxj.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}



/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_SBXX_INS
 �������:��¼����թƭ�ϱ���Ϣ��¼
 �������:��¼����թƭ�ϱ���Ϣ��¼
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_SBXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
    char sXhNodepath[200];
    int n=-1;
   
    GAB_DXZP_SBXX st_gab_dxzp_sbxx;/*�ϱ���Ϣ��*/

    fpub_InitSoComp(lXmlhandle);
    memset(sPath,0x00,sizeof(sPath));
    memset(sXhNodepath,0x00,sizeof(sXhNodepath));
    COMP_PARACOUNTCHKMIN(2)
    COMP_GETPARSEPARAS(1,sPath,"���䱨����ˮ�Ŵ��·��")
    COMP_GETPARSEPARAS(2,sXhNodepath,"ѭ���ڵ���·��")
    
    trim(sPath);
    trim(sXhNodepath);
    LOG(LM_STD, Fmtmsg("�Ǽ��ϱ���Ϣ��->��ʼ����"), fpub_GetCompname(lXmlhandle));
    /*2.װ���ϱ���Ϣ��*/
    memset(&st_gab_dxzp_sbxx, 0x00, sizeof(st_gab_dxzp_sbxx));
    
    iRet = ffunc_gabdxzp_getXml_SBXX_Req(lXmlhandle, &st_gab_dxzp_sbxx);
    
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ���ϱ���Ϣ��");
    memset(st_gab_dxzp_sbxx.csbwlsh,0x00,sizeof(st_gab_dxzp_sbxx.csbwlsh));
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"���䱨����ˮ��");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_sbxx.csbwlsh,"%s",sCsBwlsh);
    if(0<strlen(sXhNodepath))
    	{
   			 n=xml_ElementCount(lXmlhandle,sXhNodepath);
   			 if(n<0)
   			   {
   			  		LOG(LM_STD,Fmtmsg("%s�ڵ㲻����",sXhNodepath), fpub_GetCompname(lXmlhandle));
   			      return n;
   			   }
   			 if(0==n)
   			 	{
   			 		st_gab_dxzp_sbxx.sbjls=1;
   			 	 }
   			 else
   			 	{
   			    st_gab_dxzp_sbxx.sbjls=n;
   			   }
      }
    LOG(LM_STD, Fmtmsg("�Ǽ��ϱ���Ϣ��->���װ���ϱ���Ϣ��"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.�Ǽ��ϱ���Ϣ��*/
    iRet = fdbop_ins_gab_dxzp_sbxx(lXmlhandle, &st_gab_dxzp_sbxx);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽ��ϱ���Ϣ��");
    LOG(LM_STD, Fmtmsg("�Ǽ��ϱ���Ϣ��->��ɵǼ��ϱ���Ϣ��"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ��ϱ���Ϣ��->����ɹ�[%s]",st_gab_dxzp_sbxx.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}


/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_SAJB_INS
 �������:��¼����թƭ�永�ٱ���¼
 �������:��¼����թƭ�永�ٱ���¼
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_SAJB_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
    
    
    GAB_DXZP_SAJB st_gab_dxzp_sajb;/*�永�ٱ���*/

    fpub_InitSoComp(lXmlhandle);
    
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"���䱨����ˮ�Ŵ��·��")
    trim(sPath);
    
    LOG(LM_STD, Fmtmsg("�Ǽ��永�ٱ���->��ʼ����"), fpub_GetCompname(lXmlhandle));
    /*2.װ���永�ٱ���*/
    memset(&st_gab_dxzp_sajb, 0x00, sizeof(st_gab_dxzp_sajb));
    
    iRet = ffunc_gabdxzp_getXml_945111_Req(lXmlhandle, &st_gab_dxzp_sajb);
    
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ���永�ٱ���");
    
    memset(st_gab_dxzp_sajb.csbwlsh,0x00,sizeof(st_gab_dxzp_sajb.csbwlsh));
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"���䱨����ˮ��");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_sajb.csbwlsh,"%s",sCsBwlsh);
    
    LOG(LM_STD, Fmtmsg("�Ǽ��永�ٱ���->���װ���永�ٱ���"), fpub_GetCompname(lXmlhandle));
    /*�˴�ֻ���ڵ����ϱ�ȡֹ���������Ϣ*/
    COMP_SOFTSETXML("/gabdxzp/sbpch",st_gab_dxzp_sajb.sbpch);
    /*�˴�ֻ���ڵ����ϱ�ȡֹ���������Ϣ*/
    DCIBegin();
    /*4.�Ǽ��永�ٱ���*/
    iRet = fdbop_ins_gab_dxzp_sajb(lXmlhandle, &st_gab_dxzp_sajb);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽ��永�ٱ���");
    LOG(LM_STD, Fmtmsg("�Ǽ��永�ٱ���->��ɵǼ��永�ٱ���"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ��永�ٱ���->����ɹ�[%s]",st_gab_dxzp_sajb.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_YCKK_INS
 �������:��¼����թƭ�쳣������¼
 �������:��¼����թƭ�쳣������¼
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_YCKK_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
    GAB_DXZP_YCKK st_gab_dxzp_yckk;/*�쳣������*/

    fpub_InitSoComp(lXmlhandle);
    
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"���䱨����ˮ�Ŵ��·��")
    trim(sPath);
    LOG(LM_STD, Fmtmsg("�쳣������->��ʼ����"), fpub_GetCompname(lXmlhandle));
    /*2.װ���永�ٱ���*/

  	memset(&st_gab_dxzp_yckk, 0x00, sizeof(st_gab_dxzp_yckk));
  	iRet = ffunc_gabdxzp_getXml_945112_Req(lXmlhandle, &st_gab_dxzp_yckk);
  	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ���쳣������");
  	
  	memset(st_gab_dxzp_yckk.csbwlsh,0x00,sizeof(st_gab_dxzp_yckk.csbwlsh));
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"���䱨����ˮ��");
    trim(sCsBwlsh);
  	sprintf(st_gab_dxzp_yckk.csbwlsh,"%s",sCsBwlsh);
  	LOG(LM_STD, Fmtmsg("�Ǽ��쳣������->���װ���쳣������"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.�Ǽ��쳣������*/
    iRet = fdbop_ins_gab_dxzp_yckk(lXmlhandle, &st_gab_dxzp_yckk);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽ��쳣������");

    LOG(LM_STD, Fmtmsg("�Ǽ��쳣������->��ɵǼ��쳣������"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ��쳣������->����ɹ�[%s]",st_gab_dxzp_yckk.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}



/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_SAZH_INS
 �������:��¼����թƭ�永�˻���¼
 �������:��¼����թƭ�永�˻���¼
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_SAZH_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
   
    GAB_DXZP_SAZH st_gab_dxzp_sazh;/*�永�˻���*/

    fpub_InitSoComp(lXmlhandle);
    
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"���䱨����ˮ�Ŵ��·��")
    trim(sPath);
    LOG(LM_STD, Fmtmsg("�永�˻���->��ʼ����"), fpub_GetCompname(lXmlhandle));
    /*2.װ���永�˻���*/
   
   
    memset(&st_gab_dxzp_sazh, 0x00, sizeof(st_gab_dxzp_sazh));
    iRet = ffunc_gabdxzp_getXml_945113_Req(lXmlhandle, &st_gab_dxzp_sazh);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ���永�˻���");
    memset(st_gab_dxzp_sazh.csbwlsh,0x00,sizeof(st_gab_dxzp_sazh.csbwlsh));
    
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"���䱨����ˮ��");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_sazh.csbwlsh,"%s",sCsBwlsh);
   
    LOG(LM_STD, Fmtmsg("�Ǽ�->���װ���永�˻���"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.�Ǽ��永�˻���*/
   
    iRet = fdbop_ins_gab_dxzp_sazh(lXmlhandle, &st_gab_dxzp_sazh);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽ��永�˻���");
     
  
    LOG(LM_STD, Fmtmsg("�Ǽ��永�˻���->��ɵǼ��永�˻���"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ��永�˻���->����ɹ�[%s]",st_gab_dxzp_sazh.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}


/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_YCSJ_INS
 �������:��¼����թƭ�쳣�¼���¼
 �������:��¼����թƭ�쳣�¼���¼
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_YCSJ_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
   
    GAB_DXZP_YCSJ st_gab_dxzp_ycsj;/*�쳣�¼���*/

    fpub_InitSoComp(lXmlhandle);
    
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"���䱨����ˮ�Ŵ��·��")
    trim(sPath);
    LOG(LM_STD, Fmtmsg("�쳣�¼���->��ʼ����"), fpub_GetCompname(lXmlhandle));
    /*2.װ���쳣�¼���*/
   
   
    memset(&st_gab_dxzp_ycsj, 0x00, sizeof(st_gab_dxzp_ycsj));
    iRet = ffunc_gabdxzp_getXml_945114_Req(lXmlhandle, &st_gab_dxzp_ycsj);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ���쳣�¼���");
    memset(st_gab_dxzp_ycsj.csbwlsh,0x00,sizeof(st_gab_dxzp_ycsj.csbwlsh));
    
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"���䱨����ˮ��");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_ycsj.csbwlsh,"%s",sCsBwlsh);
    LOG(LM_STD, Fmtmsg("�Ǽ�->���װ���쳣�¼���"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.�Ǽ��쳣�¼���*/
   
    iRet = fdbop_ins_gab_dxzp_ycsj(lXmlhandle, &st_gab_dxzp_ycsj);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽ��쳣�¼���");
   
  
    LOG(LM_STD, Fmtmsg("�Ǽ��쳣�¼���->��ɵǼ��쳣�¼���"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ��쳣�¼���->����ɹ�[%s]",st_gab_dxzp_ycsj.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_ZHSA_INS
 �������:��¼����թƭ�˻��永��¼
 �������:��¼����թƭ�˻��永��¼
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_ZHSA_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
    
    GAB_DXZP_ZHSA st_gab_dxzp_zhsa;/*�˻��永��*/

    fpub_InitSoComp(lXmlhandle);
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"���䱨����ˮ�Ŵ��·��")
    trim(sPath);
    LOG(LM_STD, Fmtmsg("�Ǽ��˻��永��->��ʼ����"), fpub_GetCompname(lXmlhandle));
    /*2.װ���˻��永��*/
    memset(&st_gab_dxzp_zhsa, 0x00, sizeof(st_gab_dxzp_zhsa));
   
    iRet = ffunc_gabdxzp_getXml_945115_Req(lXmlhandle, &st_gab_dxzp_zhsa);

    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ���˻��永��");
    
    memset(st_gab_dxzp_zhsa.csbwlsh,0x00,sizeof(st_gab_dxzp_zhsa.csbwlsh));
        
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"���䱨����ˮ��");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_zhsa.csbwlsh,"%s",sCsBwlsh);
    LOG(LM_STD, Fmtmsg("�Ǽ��˻��永��->���װ���˻��永��"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.�Ǽ��˻��永��*/
    iRet = fdbop_ins_gab_dxzp_zhsa(lXmlhandle, &st_gab_dxzp_zhsa);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽ��˻��永��");
    LOG(LM_STD, Fmtmsg("�Ǽ��˻��永��->��ɵǼ��˻��永��"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ��˻��永��->����ɹ�[%s]",st_gab_dxzp_zhsa.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}




/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_SFSA_INS
 �������:��¼����թƭ����永��¼
 �������:��¼����թƭ����永��¼
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_SFSA_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
    
    GAB_DXZP_SFSA st_gab_dxzp_sfsa;/*����永��*/

    fpub_InitSoComp(lXmlhandle);
    
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"���䱨����ˮ�Ŵ��·��")
    trim(sPath);
    LOG(LM_STD, Fmtmsg("�Ǽ�����永��->��ʼ����"), fpub_GetCompname(lXmlhandle));
    /*2.װ������永��*/
    memset(&st_gab_dxzp_sfsa, 0x00, sizeof(st_gab_dxzp_sfsa));
   
    iRet = ffunc_gabdxzp_getXml_945116_Req(lXmlhandle, &st_gab_dxzp_sfsa);

    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ������永��");
    
    memset(st_gab_dxzp_sfsa.csbwlsh,0x00,sizeof(st_gab_dxzp_sfsa.csbwlsh));
        
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"���䱨����ˮ��");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_sfsa.csbwlsh,"%s",sCsBwlsh);
    
    LOG(LM_STD, Fmtmsg("�Ǽ�����永��->���װ������永��"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.�Ǽ��˻��永��*/
    iRet = fdbop_ins_gab_dxzp_sfsa(lXmlhandle, &st_gab_dxzp_sfsa);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽ�����永��");
    LOG(LM_STD, Fmtmsg("�Ǽ�����永��->��ɵǼ�����永��"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ�����永��->����ɹ�[%s]",st_gab_dxzp_sfsa.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}





/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_DATA_DEAL
 �������:���ݴ���
 �������:���ݴ���
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_DATA_DEAL(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sStartTime[40];
    char sStopTime[40];
    char sStrq[9];
    char sSprq[9];
    char sStsj[7];
    char sSpsj[7];
    fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

    memset(sStartTime,0x00,sizeof(sStartTime));
    memset(sStopTime,0x00,sizeof(sStopTime));
    memset(sStrq,0x00,sizeof(sStrq));
    memset(sSprq,0x00,sizeof(sSprq));
    memset(sStsj,0x00,sizeof(sStsj));
    memset(sSpsj,0x00,sizeof(sSpsj));
    COMP_PARACOUNTCHKMIN(2)
    COMP_GETPARSEPARAS(1,sStartTime,"��ʼʱ��")
    COMP_GETPARSEPARAS(2,sStopTime,"����ʱ��")
    LOG(LM_STD,Fmtmsg("��ʼʱ��=[%s],����ʱ��=[%s]",sStartTime,sStopTime),fpub_GetCompname(lXmlhandle));
    
    
    if('\0' != sStartTime[0] || '\0' != sStopTime[0])
    	{
    		strncpy( sStrq,sStartTime,8); 
      	strncpy( sStsj,sStartTime+8,6); 
      	strncpy( sSprq,sStopTime,8); 
      	strncpy( sSpsj,sStopTime+8,6); 
      	iRet = xml_SetElement(lXmlhandle,"/sfck/host/resp/zxqsrq",sStrq);
      	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "�ڵ���ֵ");
      	iRet = xml_SetElement(lXmlhandle,"/sfck/host/resp/zxqssj",sStsj);
      	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "�ڵ���ֵ");
      	iRet = xml_SetElement(lXmlhandle,"/sfck/host/resp/zxjsrq",sSprq);
      	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "�ڵ���ֵ");
      	iRet = xml_SetElement(lXmlhandle,"/sfck/host/resp/zxjssj",sSpsj);
      	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "�ڵ���ֵ");
    	}
    	
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif    
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   
    return COMPSTATUS_SUCC;
}



/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_CSBWLSH_SC
 �������:���䱨����ˮ������
 �������:���䱨����ˮ������
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
 

IRESULT GAB_DXZP_CSBWLSH_SC(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sMbJgBm[40];
    char sCsBwlsh[53+1];
    char sZwrq[8+1];
    char sPath[200];
    char sSql[256];
    char sYwlsh[40];
    char sTGJGBM[100];
    GAB_DXZP_DUAL st_gab_dxzp_dual;
    
    fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
    LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif
    memset(sMbJgBm,0x00,sizeof(sMbJgBm));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
    memset(sZwrq,0x00,sizeof(sZwrq));
    memset(sPath,0x00,sizeof(sPath));
    
    COMP_PARACOUNTCHKMIN(2)
    COMP_GETPARSEPARAS(1,sMbJgBm,"Ŀ���������")
    COMP_GETPARSEPARAS(2,sPath,"���䱨����ˮ�Ŵ��·��")
    trim(sMbJgBm);
    trim(sPath);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,sZwrq,"gaps����");
    trim(sZwrq);
    memset(sSql, 0x00, sizeof(sSql));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_DXZP_XL,sSql,"ҵ����ˮ��");
    memset(&st_gab_dxzp_dual, 0x00, sizeof(st_gab_dxzp_dual));
    LOG(LM_STD, Fmtmsg("sfxt_xl[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet=fdbop_qry_dual(lXmlhandle, &st_gab_dxzp_dual, sSql);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "��ȡҵ����ˮ��");
    GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/tgjgbm",sTGJGBM,"�йܻ�������");
    if( '\0' == sTGJGBM[0] || 0 == strcmp(sTGJGBM," ") )
    	{
    		strcpy(sTGJGBM,"000000000000");
    	}
    sprintf(sCsBwlsh,"%12.12s_%12.12s%s%s%014ld",sMbJgBm,sTGJGBM,sZwrq,GetSysTime(),st_gab_dxzp_dual.nextval);
    trim(sCsBwlsh);
    LOG(LM_STD,Fmtmsg("���䱨����ˮ��[%s]",sCsBwlsh),fpub_GetCompname(lXmlhandle));
    
    iRet = xml_SetElement(lXmlhandle,sPath,sCsBwlsh);
    
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "�ڵ���ֵ");
    
    	
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif    
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   
    return COMPSTATUS_SUCC;
}


/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_APPLICATIONID_SC
 �������:ҵ������������
 �������:ҵ������������
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
 

IRESULT GAB_DXZP_APPLICATIONID_SC(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sPath[200];
    char sApplicationID[36+1];
    char sZwrq[8+1];
    char sJyDm[20];
    char sValue[4+1];
    char sSql[256];
    char sYwlsh[40];
    char sYwlx[4+1];
    GAB_DXZP_DUAL st_gab_dxzp_dual;
    fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
    LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif
   
    memset(sPath,0x00,sizeof(sPath));
    memset(sApplicationID,0x00,sizeof(sApplicationID));
    memset(sZwrq,0x00,sizeof(sZwrq));
    COMP_PARACOUNTCHKMIN(2)
    COMP_GETPARSEPARAS(1,sJyDm,"���״���") 
    COMP_GETPARSEPARAS(2,sPath,"ҵ�������Ŵ��·��")
    trim(sJyDm);
    trim(sPath);
    LOG(LM_STD,Fmtmsg("���״���[%s]",sJyDm),fpub_GetCompname(lXmlhandle));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,sZwrq,"gaps����");
    GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/ywlx",sYwlx,"ҵ������");
    
    trim(sZwrq);
    memset(sValue,0x00,sizeof(sValue));
    if(0 == strcmp(sJyDm,"945111"))
    	{
    		strcpy(sValue,"0401");
    	}
     else if(0 == strcmp(sJyDm,"945112"))
     	{
     	  strcpy(sValue,"0403");	
     	}
     else if(0 == strcmp(sJyDm,"945113"))
     	{
     		strcpy(sValue,"0404");
      }
     else if(0 == strcmp(sJyDm,"945114"))
     	{
     		strcpy(sValue,"0405");
      }
     else if(0 == strcmp(sJyDm,"945115"))
     	{
     		strcpy(sValue,"0501");
      }
     else if(0 == strcmp(sJyDm,"945116"))
     	{
     		strcpy(sValue,"0502");
      }
      else if(0 == strcmp(sJyDm,"945123"))
     	{
     		strcpy(sValue,"0305");
      }
      else if(sYwlx[0] != '\0')
      	{
      		strncpy(sValue,sYwlx,4);
      	}
      else 
      {
        LOG(LM_STD,Fmtmsg("�˽��״��벻���ڣ�"),fpub_GetCompname(lXmlhandle));
        return -1;
      }
    
    memset(sSql, 0x00, sizeof(sSql));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_DXZP_XL,sSql,"ҵ����ˮ��");
    memset(&st_gab_dxzp_dual, 0x00, sizeof(st_gab_dxzp_dual));
    LOG(LM_STD, Fmtmsg("sfxt_xl[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet=fdbop_qry_dual(lXmlhandle, &st_gab_dxzp_dual, sSql);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "��ȡҵ����ˮ��");
    sprintf(sApplicationID,"%s%s%s%018ld",sValue,sZwrq,GetSysTime(),st_gab_dxzp_dual.nextval);
    iRet = xml_SetElement(lXmlhandle,sPath,sApplicationID);
    LOG(LM_STD,Fmtmsg("ҵ��������[%s]",sApplicationID),fpub_GetCompname(lXmlhandle));
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "�ڵ���ֵ");
    
    	
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif    
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   
    return COMPSTATUS_SUCC;
}






/************************************************************************
��̬�����������
�����������:GAB_DXZP_ATTACHMENT_LOAD
�������:GAB_DXZP_ATTACHMENT_LOAD
�������:
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
	1         ����      para1               XML����             [/Response/Body/Attachments]  0         
	2         ����      para2               XML����                                           0         
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-27 10:29:10(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_ATTACHMENT_LOAD(HXMLTREE lXmlhandle)
{
  int iRet = -1;
  char sbuf[1024];
  char xmlnode[1024];
  char attachments[255];
  char path[255];
  char filename[256];
  int  iParas;
  int childcount = 0;
  int i = 0;
  int elementlen = 0;
  char * pcontentbase64 = NULL;
  int alloclen = 0;
  char * pcontent = NULL;
  FILE * fp = NULL;
  GAB_DXZP_SMJFJ st_gab_dxzp_smjfj;/*����թƭɨ���������*/
  
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

	COMP_PARACOUNTCHKMIN(2);
	
	memset(sbuf, 0x00, sizeof(sbuf));
	COMP_GETPARSEPARAS(1, sbuf, "���������Žڵ�");
	memset(attachments, 0x00, sizeof(attachments));
	pstrcopy(attachments, sbuf, sizeof(attachments));
	
	memset(sbuf, 0x00, sizeof(sbuf));
	COMP_GETPARSEPARAS(2, sbuf, "����������·��");
	memset(path, 0x00, sizeof(path));
	pstrcopy(path, sbuf, sizeof(path));
	
	LOG(LM_STD, Fmtmsg("  -->[%s],[%s]",attachments,path), __func__);

	if (strlen(attachments) == 0 || strlen(path) == 0) {
		LOG(LM_STD, Fmtmsg("����Ĳ���1����%s��������2:��%s�� ��Ч������Ϊ��", attachments, path), __func__);
		fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}

	if ('/' == attachments[strlen(attachments)-1]) {
		attachments[strlen(attachments)-1] = '\0';
	}

	if ('/' == path[strlen(path)-1]) {
		path[strlen(path)-1] = '\0';
	}
	
	if (-1 == (childcount = xml_ChildElementCount(lXmlhandle, attachments))) {
		LOG(LM_STD, Fmtmsg(" xml_ChildElementCount-->����ʧ��:attachments=%s", attachments), __func__);
		fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}

	for (i = 0 ; i < childcount; ++i) {
		memset(sbuf, 0x00, sizeof(sbuf));
		memset(xmlnode, 0x00, sizeof(xmlnode));
		snprintf(xmlnode, sizeof(xmlnode)-1, "%s/Attachment|%d/Filename", attachments, i+1);
		if (-1 == xml_GetElement(lXmlhandle, xmlnode, sbuf, sizeof(sbuf)-1)) {
			LOG(LM_STD, Fmtmsg(" xml_GetElement-->����ʧ��:xmlnode=%s, bufsize=%d", xmlnode, sizeof(sbuf)-1), __func__);
			fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;
		}
		
		memset(filename, 0x00, sizeof(filename));
		snprintf(filename, sizeof(filename)-1, "%s/%s", path, sbuf);
		
		
		memset(xmlnode, 0x00, sizeof(xmlnode));
		snprintf(xmlnode, sizeof(xmlnode)-1, "%s/Attachment|%d/Content", attachments, i+1);
		if (-1 == (elementlen = xml_GetElementLen(lXmlhandle, xmlnode))) {
			LOG(LM_STD, Fmtmsg(" xml_GetElementLen-->����ʧ��:xmlnode=%s", xmlnode), __func__);
			fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;		
		}
		
		if (elementlen+1 > alloclen) {
			if ( NULL == (pcontentbase64 = (char *)realloc(pcontentbase64, elementlen+1))) {
				if (pcontentbase64) {
					free(pcontentbase64);
				}
				LOG(LM_STD, Fmtmsg(" realloc-->����ʧ��:����%d�ֽ��ڴ�ʧ��", elementlen+1), __func__);
				fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				return COMPRET_FAIL;			
			}
			alloclen = elementlen+1;
		}
		memset(pcontentbase64, 0x00, alloclen);
		
		if (-1 == xml_GetElement(lXmlhandle, xmlnode, pcontentbase64, elementlen+1)) {
			LOG(LM_STD, Fmtmsg(" xml_GetElement-->����ʧ��:xmlnode=%s, bufsize=%d", xmlnode, elementlen), __func__);
			free(pcontentbase64);
			fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;
		}
		
		if (NULL == (pcontent = fpub_base64_decode(pcontentbase64, &elementlen))) {
			LOG(LM_STD, Fmtmsg(" fpub_base64_decode-->����ʧ��:pcontentbase64=[%s] elementlen=%d", pcontentbase64, elementlen), __func__);
			free(pcontentbase64);
			fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;		
		}
		memset(&st_gab_dxzp_smjfj,0x00,sizeof(st_gab_dxzp_smjfj));
		iRet = ffunc_gabdxzp_getXml_SMJFJ_Req(lXmlhandle, &st_gab_dxzp_smjfj);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ص���թƭɨ���������");
    LOG(LM_STD, Fmtmsg("�Ǽǵ���թƭɨ���������->���װ�ص���թƭɨ���������"), fpub_GetCompname(lXmlhandle));
    st_gab_dxzp_smjfj.xh=i;
    sprintf(st_gab_dxzp_smjfj.wjm,"%s",filename);
    sprintf(st_gab_dxzp_smjfj.wjdx,"%d",elementlen);
    DCIBegin();

    iRet = fdbop_ins_gab_dxzp_smjfj(lXmlhandle, &st_gab_dxzp_smjfj);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽǵ���թƭɨ���������");
    LOG(LM_STD, Fmtmsg("�Ǽǵ���թƭɨ���������->��ɵ���թƭɨ���������"), fpub_GetCompname(lXmlhandle));
    DCICommit();
		
		
		
		if (NULL == (fp = fopen(filename, "w+"))) {
			LOG(LM_STD, Fmtmsg(" fopen-->����ʧ��:filename=%s", filename), __func__);
			free(pcontentbase64);
			free(pcontent);
			fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;		
		}
		LOG(LM_STD,Fmtmsg("elementlen[%d],pcontent[%s]",elementlen,pcontent), __func__);
		fwrite(pcontent, 1, elementlen, fp);
		fclose(fp);
		free(pcontent);
	}
	if (pcontentbase64) {
		free(pcontentbase64);
	}
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}





/************************************************************************
��̬�����������
�����������:GAB_DXZP_CKZTCX_INS
�������:GAB_DXZP_CKZTCX_INS
�������:
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:33:46(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_CKZTCX_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  
  GAB_DXZP_ZTCX st_gab_dxzp_ztcx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  
  /* װ�سֿ������ѯ�� */
  memset(&st_gab_dxzp_ztcx, 0x00, sizeof(st_gab_dxzp_ztcx));

  iRet = ffunc_gabdxzp_getXml_945107_Req(lXmlhandle, &st_gab_dxzp_ztcx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ص���թƭ�����ѯ��");
  LOG(LM_STD, Fmtmsg("�Ǽǵ���թƭ�����ѯ��->���װ�ص���թƭ�����ѯ��"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_ztcx(lXmlhandle, &st_gab_dxzp_ztcx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽǵ���թƭ�����ѯ��");
  LOG(LM_STD, Fmtmsg("�Ǽǵ���թƭ�����ѯ��->��ɵǼǵ���թƭ�����ѯ��"), fpub_GetCompname(lXmlhandle));
  DCICommit();
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}








/************************************************************************
��̬�����������
�����������:GAB_DXZP_DTCX_INS
�������:GAB_DXZP_DTCX_INS
�������:
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-26 17:00:02(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_DTCX_INS(HXMLTREE lXmlhandle)
{
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  
  GAB_DXZP_DTCX st_gab_dxzp_dtcx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  
  /* װ�ض�̬��ѯ�� */
  memset(&st_gab_dxzp_dtcx, 0x00, sizeof(st_gab_dxzp_dtcx));

  iRet = ffunc_gabdxzp_getXml_945108_Req(lXmlhandle, &st_gab_dxzp_dtcx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ض�̬��ѯ��");
  LOG(LM_STD, Fmtmsg("�ǼǶ�̬��ѯ��->���װ�ض�̬��ѯ��"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_dtcx(lXmlhandle, &st_gab_dxzp_dtcx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�ǼǶ�̬��ѯ��");
  LOG(LM_STD, Fmtmsg("�ǼǶ�̬��ѯ��->��ɶ�̬��ѯ��"), fpub_GetCompname(lXmlhandle));
  DCICommit();
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}








/************************************************************************
��̬�����������
�����������:GAB_DXZP_DTCXJC_INS
�������:GAB_DXZP_DTCXJC_INS
�������:
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-27 10:10:10(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_DTCXJC_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  
  GAB_DXZP_DTCX st_gab_dxzp_dtcx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* װ�ض�̬��ѯ�� */
  memset(&st_gab_dxzp_dtcx, 0x00, sizeof(st_gab_dxzp_dtcx));

  iRet = ffunc_gabdxzp_getXml_945109_Req(lXmlhandle, &st_gab_dxzp_dtcx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ض�̬��ѯ��");
  LOG(LM_STD, Fmtmsg("�ǼǶ�̬��ѯ��->���װ�ض�̬��ѯ��"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_dtcx(lXmlhandle, &st_gab_dxzp_dtcx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�ǼǶ�̬��ѯ��");
  LOG(LM_STD, Fmtmsg("�ǼǶ�̬��ѯ��->��ɶ�̬��ѯ��"), fpub_GetCompname(lXmlhandle));
  DCICommit();
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}








/************************************************************************
��̬�����������
�����������:GAB_DXZP_JYMXCX_INS
�������:GAB_DXZP_JYMXCX_INS
�������:
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:25:19(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_JYMXCX_INS(HXMLTREE lXmlhandle)
{

  char sbuf[255];
  int  iParas;
  int iRet = -1;

  GAB_DXZP_JYMX st_gab_dxzp_jymx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  /*װ�ؽ�����ϸ��ѯ��*/
  memset(&st_gab_dxzp_jymx, 0x00, sizeof(st_gab_dxzp_jymx));
  iRet = ffunc_gabdxzp_getXml_945106_Req(lXmlhandle, &st_gab_dxzp_jymx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ؽ�����ϸ��ѯ��");
  LOG(LM_STD, Fmtmsg("�Ǽǽ�����ϸ��ѯ��->���װ�ؽ�����ϸ��ѯ��"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_jymx(lXmlhandle, &st_gab_dxzp_jymx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽǽ�����ϸ��ѯ��");
  LOG(LM_STD, Fmtmsg("�Ǽǽ�����ϸ��ѯ��->��ɵǼǽ�����ϸ��ѯ��"), fpub_GetCompname(lXmlhandle));
  DCICommit();
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return COMPSTATUS_SUCC;
}








/************************************************************************
��̬�����������
�����������:GAB_DXZP_KEQZHCX_INS
�������:GAB_DXZP_KEQZHCX_INS
�������:
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_KEQZHCX_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  GAB_DXZP_QHCX st_gab_dxzp_qhcx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* װ�ؿͻ�ȫ�˻���ѯ�� */
  memset(&st_gab_dxzp_qhcx, 0x00, sizeof(st_gab_dxzp_qhcx));

  iRet = ffunc_gabdxzp_getXml_945110_Req(lXmlhandle, &st_gab_dxzp_qhcx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ؿͻ�ȫ�˻���ѯ�� ");
  LOG(LM_STD, Fmtmsg("�Ǽǿͻ�ȫ�˻���ѯ��->���װ�ؿͻ�ȫ�˻���ѯ��"), fpub_GetCompname(lXmlhandle));
  LOG(LM_STD,Fmtmsg("cxzjlx[%s]",st_gab_dxzp_qhcx.cxzjlx), fpub_GetCompname(lXmlhandle));
  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_qhcx(lXmlhandle, &st_gab_dxzp_qhcx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽǿͻ�ȫ�˻���ѯ��");
  LOG(LM_STD, Fmtmsg("�Ǽǿͻ�ȫ�˻���ѯ��->��ɵǼǿͻ�ȫ�˻���ѯ��"), fpub_GetCompname(lXmlhandle));
  DCICommit();
  
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}















/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_ZHJBXX_ZHXX_INS
 �������:�Ǽǵ���թƭ�˻�������Ϣ_�˺���Ϣ
 �������:�Ǽǵ���թƭ�˻�������Ϣ_�˺���Ϣ
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_ZHJBXX_ZHXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    int i=1,j=1,t=1,n=1,iCnts1=0,iCnts2=0;/*��������*/
    char sPath[200];
    GAB_DXZP_ZHJBXX_ZHXX st_gab_dxzp_zhjbxx_zhxx;/*�˻�������Ϣ_�˺���Ϣ��*/
    GAB_DXZP_ZHXX_ZHJYXX st_gab_dxzp_zhxx_zhjyxx;/*�˻���Ϣ_�˺Ž�����Ϣ*/
    fpub_InitSoComp(lXmlhandle);

    /*��ȡ��������*/
    iCnts1=xml_ElementCount(lXmlhandle,"/sfck/host/resp/zhjbxx/zhxx");
    if(iCnts1<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/sfck/host/resp/zhjbxx/zhxx�ڵ㲻����"),fpub_GetCompname(lXmlhandle));
   			 if(0==iCnts1)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return iCnts1;
   		}
    LOG(LM_STD, Fmtmsg("�Ǽ��˻�������Ϣ_�˺���Ϣ��->��ʼ����[%d]", iCnts1), fpub_GetCompname(lXmlhandle));
    
    /*2.װ�ؼ��Ǽ��˻�������Ϣ_�˺���Ϣ��*/
    DCIBegin();
    for ( i=1,j=1; i<=iCnts1; i++,j++)
    {
        memset(&st_gab_dxzp_zhjbxx_zhxx, 0x00, sizeof(st_gab_dxzp_zhjbxx_zhxx));
        iRet = ffunc_gabdxzp_getXml_ZHJBXX_ZHXX_Resp(lXmlhandle, &st_gab_dxzp_zhjbxx_zhxx, i);
        GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ���˻�������Ϣ_�˺���Ϣ��");
  
        LOG(LM_STD, Fmtmsg("�Ǽ��˻�������Ϣ_�˺���Ϣ��->����˻�������Ϣ_�˺���Ϣ��[%d]", i), fpub_GetCompname(lXmlhandle));
        
        /*�Ǽ��˻�������Ϣ_�˺���Ϣ��->���װ���˻�������Ϣ_�˺���Ϣ��*/
        iRet = fdbop_ins_gab_dxzp_zhjbxx_zhxx(lXmlhandle, &st_gab_dxzp_zhjbxx_zhxx);
        GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "�Ǽ��˻�������Ϣ_�˺���Ϣ��->���װ���˻�������Ϣ_�˺���Ϣ��");
        LOG(LM_STD, Fmtmsg("�Ǽ��˻�������Ϣ_�˺���Ϣ��->���װ���˻�������Ϣ_�˺���Ϣ��[%d]", i), fpub_GetCompname(lXmlhandle));
        
        /*��ȡ��������*/
        iCnts2=0;
        memset(sPath,0x00,sizeof(sPath));
        sprintf(sPath,"/sfck/host/resp/zhjbxx/zhxx|%d/zhjyxx",i);
        trim(sPath);
        iCnts2=xml_ElementCount(lXmlhandle,sPath);
        if(iCnts2<=0)
   	    	{
   			     LOG(LM_STD,Fmtmsg("/sfck/host/resp/zhjbxx/zhxx|%d/zhjyxx�ڵ㲻����",i),fpub_GetCompname(lXmlhandle));
   			     if(0==iCnts2)
   			       {
   			         continue;
   			       }
   			     return iCnts2;
   		    }
   		  LOG(LM_STD,Fmtmsg("/sfck/host/resp/zhjbxx/zhxx|%d/zhjyxx",i),fpub_GetCompname(lXmlhandle));
        LOG(LM_STD, Fmtmsg("�Ǽǵ���թƭ�˻���Ϣ_�˺Ž�����Ϣ->��ʼ����[%d]", iCnts2), fpub_GetCompname(lXmlhandle));
        
        
        for(t=1,n=1;t<=iCnts2;t++,n++)
        {
        		 memset(&st_gab_dxzp_zhxx_zhjyxx,0x00,sizeof(st_gab_dxzp_zhxx_zhjyxx));
        		 iRet = ffunc_gabdxzp_getXml_ZHXX_ZHJYXX_Resp(lXmlhandle, &st_gab_dxzp_zhxx_zhjyxx, i,t);
        	   GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ���˻���Ϣ_�˺Ž�����Ϣ��");
             strcpy(st_gab_dxzp_zhxx_zhjyxx.zhxh,st_gab_dxzp_zhjbxx_zhxx.zhxh);
             LOG(LM_STD, Fmtmsg("�Ǽ��˻���Ϣ_�˺Ž�����Ϣ��->����˻���Ϣ_�˺Ž�����Ϣ��[%d]", t), fpub_GetCompname(lXmlhandle));
             /*�Ǽ��˻���Ϣ_�˺Ž�����Ϣ��->���װ���˻���Ϣ_�˺Ž�����Ϣ��*/
             iRet = fdbop_ins_gab_dxzp_zhxx_zhjyxx(lXmlhandle, &st_gab_dxzp_zhxx_zhjyxx);
             GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "�Ǽ��˻���Ϣ_�˺Ž�����Ϣ��->���װ���˻�������Ϣ_�˺���Ϣ��");
             LOG(LM_STD, Fmtmsg("�Ǽ��˻���Ϣ_�˺Ž�����Ϣ��->���װ���˻���Ϣ_�˺Ž�����Ϣ��[%d]", t), fpub_GetCompname(lXmlhandle));
             
        	   if ( n > GAB_DXZP_COMMIT_CNT )
             {/*�ﵽ�ύ��¼�����ύ����*/
                DCICommit();
                DCIBegin();
                n = 1;
             }
        	
        }
        
        if ( j > GAB_DXZP_COMMIT_CNT )
        {/*�ﵽ�ύ��¼�����ύ����*/
            DCICommit();
            DCIBegin();
            j = 1;
        }
    }
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ��˻�������Ϣ_�˺���Ϣ��->����ɹ�[%d][%d]", i,t), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}













/************************************************************************
��̬�����������
�����������:GAB_DXZP_JYMX_ZHJBXX_INS
�������:GAB_DXZP_JYMX_ZHJBXX_INS
�������:��¼����թƭ������ϸ�˻�������Ϣ
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_JYMX_ZHJBXX_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  GAB_DXZP_JYMX_ZHJBXX st_gab_dxzp_jymx_zhjbxx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* װ�ؽ�����ϸ_�˻�������Ϣ�� */
  memset(&st_gab_dxzp_jymx_zhjbxx, 0x00, sizeof(st_gab_dxzp_jymx_zhjbxx));

  iRet = ffunc_gabdxzp_getXml_JYMX_ZHJBXX_Resp(lXmlhandle, &st_gab_dxzp_jymx_zhjbxx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ؽ�����ϸ_�˻�������Ϣ�� ");
  LOG(LM_STD, Fmtmsg("�Ǽǽ�����ϸ_�˻�������Ϣ��->���װ�ؽ�����ϸ_�˻�������Ϣ��"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_jymx_zhjbxx(lXmlhandle, &st_gab_dxzp_jymx_zhjbxx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽǽ�����ϸ_�˻�������Ϣ��");
  LOG(LM_STD, Fmtmsg("�Ǽǽ�����ϸ_�˻�������Ϣ��->��ɵǼǽ�����ϸ_�˻�������Ϣ��"), fpub_GetCompname(lXmlhandle));
  DCICommit();
  
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}










/************************************************************************
��̬�����������
�����������:GAB_DXZP_QHCX_SFQZXX_INS
�������:GAB_DXZP_QHCX_SFQZXX_INS
�������:��¼����թƭȫ����ѯ_˾��ǿ����Ϣ
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/

IRESULT GAB_DXZP_QHCX_SFQZXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    int i=1,j=1, iCnts=0;/*��������*/
    GAB_DXZP_QHCX_SFQZXX st_gab_dxzp_qhcx_sfqzxx;/*ȫ����ѯ_˾��ǿ����Ϣ��*/

    fpub_InitSoComp(lXmlhandle);

    /*��ȡ��������*/
    iCnts=xml_ElementCount(lXmlhandle,"/sfck/host/resp/sfqzxx");
    if(iCnts<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/sfck/host/resp/sfqzxx�ڵ㲻����"),fpub_GetCompname(lXmlhandle));
   			  if(0==iCnts)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return iCnts;
   		}
    LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_˾��ǿ����Ϣ��->��ʼ����[%d]", iCnts), fpub_GetCompname(lXmlhandle));
    
    /*2.װ�ؼ��Ǽ�ȫ����ѯ_˾��ǿ����Ϣ��*/
    DCIBegin();
    for ( i=1,j=1; i<=iCnts; i++,j++)
    {
        memset(&st_gab_dxzp_qhcx_sfqzxx, 0x00, sizeof(st_gab_dxzp_qhcx_sfqzxx));
        iRet = ffunc_gabdxzp_getXml_QHCX_SFQZXX_Resp(lXmlhandle, &st_gab_dxzp_qhcx_sfqzxx, i);
        GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ��ȫ����ѯ_˾��ǿ����Ϣ��");
  
        LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_˾��ǿ����Ϣ��->���ȫ����ѯ_˾��ǿ����Ϣ��[%d]", i), fpub_GetCompname(lXmlhandle));
        
        /*�Ǽ�ȫ����ѯ_˾��ǿ����Ϣ��->���װ��ȫ����ѯ_˾��ǿ����Ϣ��*/
        iRet = fdbop_ins_gab_dxzp_qhcx_sfqzxx(lXmlhandle, &st_gab_dxzp_qhcx_sfqzxx);
        GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "�Ǽ�ȫ����ѯ_˾��ǿ����Ϣ��->���װ��ȫ����ѯ_˾��ǿ����Ϣ��");
        LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_˾��ǿ����Ϣ��->���װ��ȫ����ѯ_˾��ǿ����Ϣ��[%d]", i), fpub_GetCompname(lXmlhandle));
        if ( j > GAB_DXZP_COMMIT_CNT )
        {/*�ﵽ�ύ��¼�����ύ����*/
            DCICommit();
            DCIBegin();
            j = 1;
        }
    }
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_˾��ǿ����Ϣ��->����ɹ�[%d]", i), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}














/************************************************************************
��̬�����������
�����������:GAB_DXZP_QHCX_ZHJBXX_ZZHXX_INS
�������:GAB_DXZP_QHCX_ZHJBXX_ZZHXX_INS
�������:��¼����թƭȫ����ѯ�˻�������Ϣ_���˺���Ϣ
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/

IRESULT GAB_DXZP_QHCX_ZHJBXX_ZZHXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    int i=1,j=1,t=1,n=1, iCnts=0,iCnts2=0;/*��������*/
    
    GAB_DXZP_JYMX_ZHJBXX st_gab_dxzp_jymx_zhjbxx;/*ȫ����ѯ_�˻�������Ϣ��*/
    GAB_DXZP_QHCX_ZZHXX st_gab_dxzp_qhcx_zzhxx;/*ȫ����ѯ_���˺���Ϣ��*/
    
    fpub_InitSoComp(lXmlhandle);
    
    /*��ȡ��������*/
    iCnts=xml_ElementCount(lXmlhandle,"/sfck/host/resp/zhjbxx");
    if(iCnts<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/sfck/host/resp/zhjbxx�ڵ㲻����"),fpub_GetCompname(lXmlhandle));
   			  if(0==iCnts)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return iCnts;
   		}
    LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_�˻�������Ϣ��->��ʼ����[%d]", iCnts), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    for(t=1,n=1;t<=iCnts;t++,n++)
    {
    	memset(&st_gab_dxzp_jymx_zhjbxx,0x00,sizeof(st_gab_dxzp_jymx_zhjbxx));
    	iRet =ffunc_gabdxzp_getXml_QHCX_ZHJBXX_Resp(lXmlhandle,&st_gab_dxzp_jymx_zhjbxx,t);
    	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ��ȫ����ѯ_�˻�������Ϣ��");
  
      LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_�˻�������Ϣ��->���ȫ����ѯ_�˻�������Ϣ��[%d]", t), fpub_GetCompname(lXmlhandle));
        
      /*�Ǽ�ȫ����ѯ_�˻�������Ϣ��->���ȫ����ѯ_�˻�������Ϣ��*/
      iRet = fdbop_ins_gab_dxzp_jymx_zhjbxx(lXmlhandle, &st_gab_dxzp_jymx_zhjbxx);
      GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "�Ǽ�ȫ����ѯ_�˻�������Ϣ��->���ȫ����ѯ_�˻�������Ϣ��");
      LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_���˺���Ϣ��->���װ��ȫ����ѯ_�˻�������Ϣ��[%d]", t), fpub_GetCompname(lXmlhandle));
      if ( n > GAB_DXZP_COMMIT_CNT )
         {/*�ﵽ�ύ��¼�����ύ����*/
             DCICommit();
             DCIBegin();
             n = 1;
         }
       memset(sPath,0x00,sizeof(sPath));
       sprintf(sPath,"/sfck/host/resp/zhjbxx|%d/zzhxx",t);
      /*��ȡ��������*/
      iCnts2=xml_ElementCount(lXmlhandle,sPath);
      if(iCnts2<=0)
   		 {
   			  LOG(LM_STD,Fmtmsg("%s�ڵ㲻����",sPath),fpub_GetCompname(lXmlhandle));
   			   if(0==iCnts2)
   			    {
   			      continue;
   			    }
   			  return iCnts2;
   		 }
      LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_���˺���Ϣ��->��ʼ����[%d]", iCnts2), fpub_GetCompname(lXmlhandle));
    
      /*2.װ�ؼ��Ǽ�ȫ����ѯ_���˺���Ϣ��*/
    
      for ( i=1,j=1; i<=iCnts2; i++,j++)
       {
         memset(&st_gab_dxzp_qhcx_zzhxx, 0x00, sizeof(st_gab_dxzp_qhcx_zzhxx));
         iRet = ffunc_gabdxzp_getXml_QHCX_ZZHXX_Resp(lXmlhandle, &st_gab_dxzp_qhcx_zzhxx, t,i);
         GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ��ȫ����ѯ_���˺���Ϣ��");
  
         LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_���˺���Ϣ��->���ȫ����ѯ_���˺���Ϣ��[%d]", i), fpub_GetCompname(lXmlhandle));
        
         /*�Ǽ�ȫ����ѯ_���˺���Ϣ��->���װ��ȫ����ѯ_���˺���Ϣ��*/
         iRet = fdbop_ins_gab_dxzp_qhcx_zzhxx(lXmlhandle, &st_gab_dxzp_qhcx_zzhxx);
         GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "�Ǽ�ȫ����ѯ_���˺���Ϣ��->���װ��ȫ����ѯ_���˺���Ϣ��");
         LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_���˺���Ϣ��->���װ��ȫ����ѯ_���˺���Ϣ��[%d]", i), fpub_GetCompname(lXmlhandle));
         if ( j > GAB_DXZP_COMMIT_CNT )
          {/*�ﵽ�ύ��¼�����ύ����*/
             DCICommit();
             DCIBegin();
             j = 1;
          }
       }
     }
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_���˺���Ϣ��->����ɹ�[%d]", i), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}















/************************************************************************
��̬�����������
�����������:GAB_DXZP_QHCX_QLXX_INS
�������:GAB_DXZP_QHCX_QLXX_INS
�������:��¼����թƭȫ����ѯ_Ȩ������Ϣ
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/

IRESULT GAB_DXZP_QHCX_QLXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    int i=1,j=1, iCnts=0;/*��������*/
    GAB_DXZP_QHCX_QLXX st_gab_dxzp_qhcx_qlxx;/*ȫ����ѯ_Ȩ������Ϣ*/

    fpub_InitSoComp(lXmlhandle);

    /*��ȡ��������*/
    iCnts=xml_ElementCount(lXmlhandle,"/sfck/host/resp/qzxx");
    if(iCnts<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/sfck/host/resp/qzxx�ڵ㲻����"),fpub_GetCompname(lXmlhandle));
   			  if(0==iCnts)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return iCnts;
   		}
    LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_Ȩ������Ϣ��->��ʼ����[%d]", iCnts), fpub_GetCompname(lXmlhandle));
    
    /*2.װ�ؼ��Ǽ�ȫ����ѯ_Ȩ������Ϣ��*/
    DCIBegin();
    for ( i=1,j=1; i<=iCnts; i++,j++)
    {
        memset(&st_gab_dxzp_qhcx_qlxx, 0x00, sizeof(st_gab_dxzp_qhcx_qlxx));
        iRet = ffunc_gabdxzp_getXml_QHCX_QLXX_Resp(lXmlhandle, &st_gab_dxzp_qhcx_qlxx, i);
        GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ��ȫ����ѯ_Ȩ������Ϣ��");
  
        LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_Ȩ������Ϣ��->���ȫ����ѯ_Ȩ������Ϣ��[%d]", i), fpub_GetCompname(lXmlhandle));
        
        /*�Ǽ�ȫ����ѯ_Ȩ������Ϣ��->���װ��ȫ����ѯ_Ȩ������Ϣ��*/
        iRet = fdbop_ins_gab_dxzp_qhcx_qlxx(lXmlhandle, &st_gab_dxzp_qhcx_qlxx);
        GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "�Ǽ�ȫ����ѯ_Ȩ������Ϣ��->���װ��ȫ����ѯ_Ȩ������Ϣ��");
        LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_Ȩ������Ϣ��->���װ��ȫ����ѯ_Ȩ������Ϣ��[%d]", i), fpub_GetCompname(lXmlhandle));
        if ( j > GAB_DXZP_COMMIT_CNT )
        {/*�ﵽ�ύ��¼�����ύ����*/
            DCICommit();
            DCIBegin();
            j = 1;
        }
    }
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽ�ȫ����ѯ_Ȩ������Ϣ��->����ɹ�[%d]", i), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}



























/************************************************************************
��̬�����������
�����������:GAB_DXZP_DTCX_RESP_INS
�������:GAB_DXZP_DTCX_RESP_INS
�������:��¼����թƭ��̬��ѯ��Ӧ
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_DTCX_RESP_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  int iCnts=0;
  int i=1,j=1;
  GAB_DXZP_DTCX_RESP st_gab_dxzp_dtcx_resp;
  GAB_DXZP_SBXX_PLZT st_gab_dxzp_sbxx_plzt;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* װ�ض�̬��ѯ��Ӧ�� */
  memset(&st_gab_dxzp_dtcx_resp, 0x00, sizeof(st_gab_dxzp_dtcx_resp));
  iCnts=xml_ElementCount(lXmlhandle,"/sfck/host/resp/zhjyxx");
  if(iCnts<=0)
  	{
        LOG(LM_STD,Fmtmsg("/sfck/host/resp/zhjyxx�ڵ㲻����"),fpub_GetCompname(lXmlhandle));
         if(0==iCnts)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
  			return iCnts;
  	}
  LOG(LM_STD, Fmtmsg("�ǼǶ�̬��ѯ��Ӧ��->��ʼ����[%d]", iCnts), fpub_GetCompname(lXmlhandle));
  DCIBegin();  
  for(i=1,j=1;i<=iCnts;i++,j++)
    {
       iRet = ffunc_gabdxzp_getXml_DTCX_RESP_Resp(lXmlhandle, &st_gab_dxzp_dtcx_resp,i);
       GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ض�̬��ѯ��Ӧ�� ");
       LOG(LM_STD, Fmtmsg("�ǼǶ�̬��ѯ��Ӧ��->���װ�ض�̬��ѯ��Ӧ��"), fpub_GetCompname(lXmlhandle));
       
       iRet = ffunc_gabdxzp_getXml_SBXX_PLZT_Req(lXmlhandle,&st_gab_dxzp_sbxx_plzt,i); 
       GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ض�̬��ѯ��Ӧ�� ");
       strcpy(st_gab_dxzp_sbxx_plzt.sbjydm,"945123");
       LOG(LM_STD, Fmtmsg("�Ǽ��ϱ���Ϣ_����״̬��->���װ���ϱ���Ϣ_����״̬��"), fpub_GetCompname(lXmlhandle));
              
       iRet = fdbop_ins_gab_dxzp_dtcx_resp(lXmlhandle, &st_gab_dxzp_dtcx_resp);
       GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "�ǼǶ�̬��ѯ��Ӧ��->���װ�صǼǶ�̬��ѯ��Ӧ��");
       iRet = fdbop_ins_gab_dxzp_sbxx_plzt(lXmlhandle, &st_gab_dxzp_sbxx_plzt);
       GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "�Ǽ��ϱ���Ϣ_����״̬��->���װ�صǼ��ϱ���Ϣ_����״̬��");
       
       LOG(LM_STD, Fmtmsg("�ǼǶ�̬��ѯ��Ӧ��->��ɵǼǶ�̬��ѯ��Ӧ��[%d]",i), fpub_GetCompname(lXmlhandle));
       LOG(LM_STD, Fmtmsg("�Ǽ��ϱ���Ϣ_����״̬��->��ɵǼ��ϱ���Ϣ_����״̬��[%d]",i), fpub_GetCompname(lXmlhandle));
       if ( j > GAB_DXZP_COMMIT_CNT )
           {/*�ﵽ�ύ��¼�����ύ����*/
                 DCICommit();
                 DCIBegin();
                 j = 1;
           }
       
   }
  DCICommit();
  
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}















/************************************************************************
��̬�����������
�����������:GAB_DXZP_DTJC_RESP_INS
�������:GAB_DXZP_DTJC_RESP_INS
�������:��¼����թƭ��̬�����Ӧ
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_DTJC_RESP_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  GAB_DXZP_DTJC_RESP st_gab_dxzp_dtjc_resp;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* װ�ض�̬�����Ӧ�� */
  memset(&st_gab_dxzp_dtjc_resp, 0x00, sizeof(st_gab_dxzp_dtjc_resp));

  iRet = ffunc_gabdxzp_getXml_DTJC_RESP_Resp(lXmlhandle, &st_gab_dxzp_dtjc_resp);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ض�̬�����Ӧ�� ");
  LOG(LM_STD, Fmtmsg("�ǼǶ�̬�����Ӧ��->���װ�ض�̬�����Ӧ��"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_dtjc_resp(lXmlhandle, &st_gab_dxzp_dtjc_resp);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�ǼǶ�̬�����Ӧ��");
  LOG(LM_STD, Fmtmsg("�ǼǶ�̬�����Ӧ��->��ɵǼǶ�̬�����Ӧ��"), fpub_GetCompname(lXmlhandle));
  DCICommit();
  
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}














/************************************************************************
��̬�����������
�����������:GAB_DXZP_ZTCX_RESP_INS
�������:GAB_DXZP_ZTCX_RESP_INS
�������:��¼����թƭ�ֿ������ѯ��Ӧ
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_ZTCX_RESP_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  GAB_DXZP_ZTCX_RESP st_gab_dxzp_ztcx_resp;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* װ�سֿ������ѯ��Ӧ�� */
  memset(&st_gab_dxzp_ztcx_resp, 0x00, sizeof(st_gab_dxzp_ztcx_resp));

  iRet = ffunc_gabdxzp_getXml_ZTCX_RESP_Resp(lXmlhandle, &st_gab_dxzp_ztcx_resp);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�سֿ������ѯ��Ӧ�� ");
  LOG(LM_STD, Fmtmsg("�Ǽǳֿ������ѯ��Ӧ��->���װ�سֿ������ѯ��Ӧ��"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_ztcx_resp(lXmlhandle, &st_gab_dxzp_ztcx_resp);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "�Ǽǳֿ������ѯ��Ӧ��");
  LOG(LM_STD, Fmtmsg("�Ǽǳֿ������ѯ��Ӧ��->��ɵǼǳֿ������ѯ��Ӧ��"), fpub_GetCompname(lXmlhandle));
  DCICommit();
  
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}

















/************************************************************************
��̬�����������
�����������:GAB_DXZP_QUERY_JYMX
�������:GAB_DXZP_QUERY_JYMX
�������:ȡ������ϸ��ѯ��Ϣ
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_QUERY_JYMX(HXMLTREE lXmlhandle)
{
    int  iParas;
    int iRet=-1;
    char sErrmsg[1000];
    char sSql[512];
    char sYwsqbh[100];
    char sBuf[200];
    char sSql_jyxx[512];
    int i=0;
    
    CURSOR query_jymx_cur;
    CURSOR zhxx_jyxx_cur;
    
   
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHKMIN(1);
    memset(sYwsqbh,0x00,sizeof(sYwsqbh));
    COMP_GETPARSEPARAS(1, sYwsqbh, "ҵ��������");
     
    GAB_DXZP_ZHJBXX_ZHXX st_gab_dxzp_zhjbxx_zhxx;
    GAB_DXZP_ZHXX_ZHJYXX st_gab_dxzp_zhxx_zhjyxx;
      
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"SELECT * \
     FROM gab_dxzp_zhjbxx_zhxx  WHERE  ywsqbh='%s' ORDER BY zhxh asc",sYwsqbh);
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((query_jymx_cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(query_jymx_cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(query_jymx_cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    while(1)
    {
        memset(&st_gab_dxzp_zhjbxx_zhxx, 0x00, sizeof(st_gab_dxzp_zhjbxx_zhxx));
        iRet = DBFetch(query_jymx_cur, SD_GAB_DXZP_ZHJBXX_ZHXX, NUMELE(SD_GAB_DXZP_ZHJBXX_ZHXX), &st_gab_dxzp_zhjbxx_zhxx, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zh);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhxh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zhxh);
       
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhlx",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zhlx);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhzt",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zhzt);

        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/bz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.bz);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/chbz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.chbz);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhye",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zhye);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/kyye",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.kyye);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjysj",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zhjysj);
        
        LOG(LM_STD,Fmtmsg("zhxh=[%s]",st_gab_dxzp_zhjbxx_zhxx.zhxh),fpub_GetCompname(lXmlhandle));
          
        memset(sSql_jyxx, 0x00, sizeof(sSql_jyxx));
        snprintf(sSql_jyxx,sizeof(sSql_jyxx),"SELECT *\
        FROM gab_dxzp_zhxx_zhjyxx  WHERE  ywsqbh='%s' and rwxh=1 and zhxh='%s' ORDER BY zhjyxh asc",sYwsqbh,st_gab_dxzp_zhjbxx_zhxx.zhxh);
        LOG(LM_STD,Fmtmsg("sSql_jyxx[%s]", sSql_jyxx),fpub_GetCompname(lXmlhandle));
        
        if ((zhxx_jyxx_cur = DCIDeclareCursor(sSql_jyxx, DCI_STMT_LOCATOR)) == -1)
         {
           LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
        if (DCIExecute(zhxx_jyxx_cur) == -1)
         {
           LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
           DCIFreeCursor(zhxx_jyxx_cur);
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
         i=0;
         while(1)
         {
         	   i++;
         	   memset(&st_gab_dxzp_zhxx_zhjyxx, 0x00, sizeof(st_gab_dxzp_zhxx_zhjyxx));
             iRet = DBFetch(zhxx_jyxx_cur, SD_GAB_DXZP_ZHXX_ZHJYXX, NUMELE(SD_GAB_DXZP_ZHXX_ZHJYXX), &st_gab_dxzp_zhxx_zhjyxx, sErrmsg );
             if ( iRet <= 0 )
             {
                 if(1 == i)  
                 	{
                 		 memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jylx",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jdbz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/bz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jyje",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jyye",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jysj",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jylsh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jydfmc",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jydfzh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jydfzjhm",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jydfzhkhh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jyzy",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jywdmc",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jywddm",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/rzh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/cph",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/pzzl",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/pzh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/xjbz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/zdh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jysfcg",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jyfsd",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/shmc",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/shh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/ip",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/mac",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jygyh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/beiz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                 		
                 	}       	
                 break;
             }
         	   memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jylx",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jylx);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jdbz",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jdbz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/bz",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.bz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jyje",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jyje);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jyye",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jyye);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jysj",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jysj);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jylsh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jylsh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jydfmc",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jydfmc);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jydfzh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jydfzh);
             
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jydfzjhm",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jydfzjhm);
             
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jydfzhkhh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jydfzhkhh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jyzy",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jyzy);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jywdmc",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jywdmc);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jywddm",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jywddm);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/rzh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.rzh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/cph",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.cph);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/pzzl",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.pzzl);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/pzh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.pzh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/xjbz",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.xjbz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/zdh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.zdh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jysfcg",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jysfcg);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jyfsd",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jyfsd);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/shmc",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.shmc);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/shh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.shh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/ip",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.ip);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/mac",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.mac);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jygyh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jygyh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/beiz",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.beiz);
             
         }
         DCIFreeCursor(zhxx_jyxx_cur);
         if( iRet < 0 )
         {
             LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
             fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return COMPRET_FAIL;
         }
       
    }
    DCIFreeCursor(query_jymx_cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"����������թƭ������ϸ��ѯ����");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_PROC_COMMBUF
 �������:����ͨѶ����
 �������:����ͨѶ����
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_PROC_COMMBUF(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPkgHead[30+1];
    char sYwLxBm[6+1];/*ҵ�����ͱ���*/
    char sXxLzMs[2+1];/*��Ϣ��תģʽ*/
    char sJgID[14+1];/*����ID*/
    char sAddPkg[64];/*���ⱨ��*/
    char *pCommbuf = NULL;
    char *pUTF8 = NULL;
    int  iCommbufLen=0;
    int  iUTF8Len=0;
    int  iRealCommLen=0;
    int  iAddPkg=0;

    fpub_InitSoComp(lXmlhandle);
    
    memset(sYwLxBm, 0x00, sizeof(sYwLxBm));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_QZJ_YWLXBM, sYwLxBm,"ҵ�����ͱ���");
    if (sYwLxBm[0] == '\0')
    {
        GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_PUB_JYBM, sYwLxBm,"ҵ�����ͱ���");
    }
    memset(sXxLzMs, 0x00, sizeof(sXxLzMs));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_QZJ_MODE, sXxLzMs,"��Ϣ��תģʽ");
    trim(sXxLzMs);
    if(sXxLzMs[0] == '\0')
    {
        pstrcopy(sXxLzMs, "01", sizeof(sXxLzMs));
    }
    memset(sJgID, 0x00, sizeof(sJgID));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_QZJ_JGID, sJgID,"����ID");
    trim(sJgID);
    if (sJgID[0] == '\0')
    {
        GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_QSJGID, sJgID,"����ID");
    }
    if ( atoi(sYwLxBm)>100101 && atoi(sYwLxBm) <= 100310)
    {/*��Ϊ��������,��ֱ�Ӵ�/gabdxzp/xdxx/fsjgbm�ڵ��л�ȡ*/
        memset(sJgID, 0x00, sizeof(sJgID));
        GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/xdxx/fsjgbm", sJgID,"����ID");
        if (sJgID[0] == '\0')
        {
            GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/FSJGBM", sJgID,"����ID");
        }
    }
    memset(sAddPkg, 0x00, sizeof(sAddPkg));
    snprintf(sAddPkg, sizeof(sAddPkg),"<Mode>%s</Mode><To>%s</To>",sXxLzMs, sJgID);
    iAddPkg=strlen(sAddPkg);
    iCommbufLen = xml_GetBinElementLen(lXmlhandle, "/commbuf");
    if (iCommbufLen <= 0 )
    {
        LOG(LM_STD,Fmtmsg("/commbuf����Ϊ[%s],��ȷ��", iCommbufLen ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD, Fmtmsg("����ͨѶ����->��ʼ����,ywlxbm[%s][%d]", sYwLxBm, iCommbufLen), fpub_GetCompname(lXmlhandle));
    /* ���ݻ�ȡ���ĳ��������ڴ� */
    pCommbuf = (char *)malloc( iCommbufLen+30+1 );
    if ( pCommbuf == NULL )
    {
        LOG(LM_STD,Fmtmsg("��̬����commbuf�ڴ�ʧ��" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
	/*��ȡͨѶ������*/
	memset(pCommbuf, 0x00, iCommbufLen+30+1);
	if(0 > (iRet = xml_RelGetBinElement(lXmlhandle, "/commbuf", pCommbuf, iCommbufLen+30+1)))
	{
		free(pCommbuf);pCommbuf=NULL;
		LOG(LM_STD, Fmtmsg("ȡͨѶ������iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "��ǰ�û�ͨѶʧ��,��ȡͨѶ������");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	LOG(LM_STD, Fmtmsg("get pCommbuf[%d][%s]", iRet, pCommbuf), fpub_GetCompname(lXmlhandle));
    iRealCommLen=strlen(pCommbuf);
    if (strcmp(sYwLxBm,"100501")==0 || 
        strcmp(sYwLxBm,"100502")==0 || 
        strcmp(sYwLxBm,"100503")==0)
    {/*������֤,ʲô������*/
        
    }else if (strcmp(sYwLxBm,"000000")==0 || strcmp(sYwLxBm,"000001")==0 )
    {/*��ȡ��Ϣ*/
        /*ȥXMLͷ*/
        iRealCommLen -=40;
        memmove(pCommbuf, pCommbuf+40, iRealCommLen);
        /*alter by liukq 20160420 BEGIN*/
        /*��ҵ���������*/
        /*
        memset(sPkgHead, 0x00, sizeof(sPkgHead));
        snprintf(sPkgHead, sizeof(sPkgHead), "%6.6s", sYwLxBm);
        memmove(pCommbuf+6, pCommbuf, iRealCommLen);
        memcpy(pCommbuf, sPkgHead, 6);
        iRealCommLen += 6;*/
        /*alter by liukq 20160420 END*/
    }else
    {/*����ҵ����*/
        /*ȥXMLͷ*/
        iRealCommLen -=40;
        memmove(pCommbuf, pCommbuf+40, iRealCommLen);
         /*alter by liukq 20160420 BEGIN*/
        /*��ҵ���������*/
        /*memset(sPkgHead, 0x00, sizeof(sPkgHead));
        snprintf(sPkgHead, sizeof(sPkgHead), "%6.6s", sYwLxBm);
        memmove(pCommbuf+6, pCommbuf, iRealCommLen);
        memcpy(pCommbuf, sPkgHead, 6);
        iRealCommLen += 6;*/
        /*alter by liukq 20160420 END*/
        /*�Ӷ�����Ϣ
        memmove(pCommbuf+15+iAddPkg, pCommbuf+15, iRealCommLen-15);
        memcpy(pCommbuf+15, sAddPkg, iAddPkg);
        iRealCommLen += iAddPkg;
        */
        pCommbuf[iRealCommLen]='\0';
    }
    iUTF8Len=iRealCommLen * 1.5;
    pUTF8 = (char *)malloc( iUTF8Len );
    if ( pUTF8 == NULL )
    {
		free(pCommbuf);pCommbuf=NULL;
		LOG(LM_STD, Fmtmsg("����UTF-8�ڴ�ʧ��[%d]", iUTF8Len), fpub_GetCompname(lXmlhandle));
		/*alter by liukq 20160503 BEGIN
		fpub_SetMsg(lXmlhandle, 99999, "��ǰ�û�ͨѶ��ʱ,�����ڴ����");
		END*/
		/*alter by liukq 20160503 BEGIN*/
		fpub_SetMsg(lXmlhandle, 98601, "��ǰ�û�ͨѶʧ��,�����ڴ����");
		/*alter by liukq 20160503 END*/
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
    }   
    memset(pUTF8, 0x00, iUTF8Len);
    iRet = convert("GB18030", "UTF-8", pCommbuf, iRealCommLen, pUTF8, &iUTF8Len);
    if ( iRet < 0 )
    {
		free(pCommbuf);pCommbuf=NULL;
		free(pUTF8);pUTF8=NULL;
		LOG(LM_STD, Fmtmsg("ת��GB18030 -> UTF-8�ڴ�ʧ��[%d]", iRealCommLen), fpub_GetCompname(lXmlhandle));
		/*alter by liukq 20160503 BEGIN
		fpub_SetMsg(lXmlhandle, 99999, "��ǰ�û�ͨѶ��ʱ,ת�����ĸ�ʽ����");
		END*/
		/*alter by liukq 20160503 BEGIN*/
		fpub_SetMsg(lXmlhandle, 98601, "��ǰ�û�ͨѶʧ��,ת�����ĸ�ʽ����");
		/*alter by liukq 20160503 END*/
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
    }
    free(pCommbuf);pCommbuf=NULL;
    iUTF8Len=strlen(pUTF8);
    LOG(LM_STD, Fmtmsg("proc pCommbuf[%d][%s]", iUTF8Len, pUTF8), fpub_GetCompname(lXmlhandle));
    /*дͨѶ��*/
    if(0 > (iRet = xml_RelSetBinElement(lXmlhandle, "/commbuf", pUTF8, iUTF8Len)))
	{
		free(pUTF8);pUTF8=NULL;
		LOG(LM_STD, Fmtmsg("дͨѶ������iRet=[%d]", iRet), fpub_GetCompname(lXmlhandle));
		/*alter by liukq 20160503 BEGIN
		fpub_SetMsg(lXmlhandle, 99999, "��ǰ�û�ͨѶ��ʱ,дͨѶ������");
		END*/
		/*alter by liukq 20160503 BEGIN*/
		fpub_SetMsg(lXmlhandle, 98601, "��ǰ�û�ͨѶʧ��,дͨѶ������");
		/*alter by liukq 20160503 END*/
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	free(pUTF8);pUTF8=NULL;
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("����ͨѶ����->����ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}


/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_945120_LAST
 �������:��ʱ��ȡ��Ϣ����
 �������:��ʱ��ȡ��Ϣ����
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_945120_LAST(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sXmlNode[64+1];
    char sPkgFileName[256];
    char sPkgFilePath[256];
    char sFsjgbm[12+1];
    int iXmlCnts=0;
    char *pCommbuf = NULL;
    char *pUTF8 = NULL;
    char *pAscII = NULL;
    int  iCommbufLen=0;
    int  iUTF8Len=0;
    int  iAscIILen=0;
    int  iRealCommLen=0;
    int  iNodePkgLen=0;
    int  i=0;
    char sNodePkg[1024000];
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("��ʱ��ȡ��Ϣ����->��ʼ����"), fpub_GetCompname(lXmlhandle));
    /*��ȡ�����ļ���*/
    memset(sPkgFilePath, 0x00, sizeof(sPkgFilePath));
    snprintf(sPkgFilePath, sizeof(sPkgFilePath), "%s/file/dxzpqzdata/%s", getenv("HOME"), GetSysDate());
    ffunc_file_crtLocalPath(lXmlhandle, sPkgFilePath);
    memset(sPkgFileName, 0x00, sizeof(sPkgFileName));
    snprintf(sPkgFileName, sizeof(sPkgFileName), "%s/pkg%s", sPkgFilePath, GetSysTime());
    /*��ȡ��ʱ��Ϣ*/
    iCommbufLen = xml_GetBinElementLen(lXmlhandle, "/commbuf");
    if (iCommbufLen <= 0 )
    {
        LOG(LM_STD,Fmtmsg("/commbuf����Ϊ[%s],��ȷ��", iCommbufLen ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* ���ݻ�ȡ���ĳ��������ڴ� */
    pCommbuf = (char *)malloc( iCommbufLen+1 );
    if ( pCommbuf == NULL )
    {
        LOG(LM_STD,Fmtmsg("��̬����commbuf�ڴ�ʧ��" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
	/*��ȡͨѶ������*/
	memset(pCommbuf, 0x00, iCommbufLen+1);
	if(0 > (iRet = xml_RelGetBinElement(lXmlhandle, "/commbuf", pCommbuf, iCommbufLen+1)))
	{
		free(pCommbuf);pCommbuf=NULL;
		LOG(LM_STD, Fmtmsg("ȡͨѶ������iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "��ǰ�û�ͨѶʧ��,��ȡͨѶ������");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	LOG(LM_STD, Fmtmsg("get pCommbuf[%d][%s]", iRet, pCommbuf), fpub_GetCompname(lXmlhandle));
    /*д��ȡ��Ϣ�ļ�*/
    iRet = ffunc_file_wrtFile(lXmlhandle, sPkgFileName, pCommbuf, iCommbufLen);
	free(pCommbuf);pCommbuf=NULL;
	if ( iRet < 0 )
	{
		LOG(LM_STD, Fmtmsg("д��ȡ��Ϣ�ļ�����iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99997, "д��ȡ��Ϣ�ļ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
    /*��ȡ�����¼��*/
    iXmlCnts=xml_ChildElementCount(lXmlhandle, "/Response/Body/MessageList");
    if ( iXmlCnts < 0 )
    {
		LOG(LM_STD, Fmtmsg("��ȡ�����¼������iRet=[%d]", iXmlCnts), "ERROR");
		fpub_SetMsg(lXmlhandle, 99996, "��ȡ�����¼��ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
    }
    LOG(LM_STD, Fmtmsg("��ȡ�����¼��[%d]", iXmlCnts), fpub_GetCompname(lXmlhandle));
    for(i=0;i<iXmlCnts;i++)
    {
        memset(sXmlNode, 0x00, sizeof(sXmlNode));
        snprintf(sXmlNode, sizeof(sXmlNode),"/Response/Body/MessageList/Message|%d", i);
        memset(sNodePkg, 0x00, sizeof(sNodePkg));
        COMP_SOFTGETXML(sXmlNode, sNodePkg)
        LOG(LM_STD, Fmtmsg("sXmlNode[%s][%s]", sXmlNode, sNodePkg), fpub_GetCompname(lXmlhandle));
        iNodePkgLen=strlen(sNodePkg);
        pUTF8 = fpub_base64_decode(sNodePkg, &iNodePkgLen);
        iUTF8Len = strlen(pUTF8);
        iAscIILen=iUTF8Len * 1.5;
        pAscII = (char *)malloc( iAscIILen );
        if ( pAscII == NULL )
        {
            free(pUTF8);pUTF8=NULL;
	    	LOG(LM_STD, Fmtmsg("����GB18030�ڴ�ʧ��[%d]", iAscIILen), fpub_GetCompname(lXmlhandle));
	    	continue;
        } 
        memset(pAscII, 0x00, iAscIILen);
        iRet = convert( "UTF-8", "GB18030", pUTF8, iUTF8Len, pAscII, &iAscIILen);
        if ( iRet < 0 )
        {
            free(pUTF8);pUTF8=NULL;
            free(pAscII);pAscII=NULL;
	    	LOG(LM_STD, Fmtmsg("ת��UTF-8 -> GB18030��������ʧ��[%d]", iUTF8Len), fpub_GetCompname(lXmlhandle));
	    	continue;
        }
        free(pUTF8);pUTF8=NULL;
        iAscIILen=strlen(pAscII);
        LOG(LM_STD, Fmtmsg("base64->ascii=[%d][%s]", iAscIILen,pAscII), fpub_GetCompname(lXmlhandle));
        if(0 > (iRet = xml_RelSetBinElement(lXmlhandle, "/commbuf", pAscII, iAscIILen)))
	    {
	    	free(pAscII);pAscII=NULL;
	    	LOG(LM_STD, Fmtmsg("[%d]дͨѶ������iRet=[%s]", i+1, sNodePkg), fpub_GetCompname(lXmlhandle));
	    	continue;
	    }
	    free(pAscII);pAscII=NULL;
	    if( fpub_CallFlow(lXmlhandle,"subflow_gabdxzp_945120") != MID_SYS_SUCC)
	    {
	    	LOG(LM_STD, Fmtmsg("[%d]���÷ַ�������ʧ��", i+1), fpub_GetCompname(lXmlhandle));
	    	continue;
	    }
    }
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("��ʱ��ȡ��Ϣ����->����ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_CHKSTS
 �������:������ҵ��״̬���
 �������:������ҵ��״̬���
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_CHKSTS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sSql[256];
    char sYwsqbh[36+1];/*ҵ��������*/
    char sCllx[1+1];/*��������*/
    char sOriQqdZt[2+1];/*ԭ����״̬*/
    char sNewQqdZt[2+1];/*������״̬*/
    char sHostfcflat[20];
    GAB_DXZP_XDXX st_gab_dxzp_xdxx;/*�´���Ϣ��*/
    GAB_DXZP_DUAL st_gab_dxzp_dual;
    
    memset(sYwsqbh, 0x00, sizeof(sYwsqbh));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH, sYwsqbh,"ҵ��������");
    memset(sCllx, 0x00, sizeof(sCllx));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CLLX, sCllx,"��������");
    
    LOG(LM_STD, Fmtmsg("������ҵ��״̬���->����ʼ,ywsqbh[%s],cllx[%s]",
        sYwsqbh, sCllx), fpub_GetCompname(lXmlhandle));
    /*��ѯ��Ϣ�´��*/
    memset(&st_gab_dxzp_xdxx, 0x00, sizeof(st_gab_dxzp_xdxx));
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.ywsqbh, sYwsqbh);
    iRet=fdbop_qry_gab_dxzp_xdxx(lXmlhandle, &st_gab_dxzp_xdxx);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "��ѯ��Ϣ�´��");
    LOG(LM_STD, Fmtmsg("��ɲ�ѯ��Ϣ�´��,qqdzt[%s]", 
        st_gab_dxzp_xdxx.qqdzt), fpub_GetCompname(lXmlhandle));
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, st_gab_dxzp_xdxx.qqdzt)
    memset(sOriQqdZt, 0x00, sizeof(sOriQqdZt));
    GAB_DXZP_PSTRCOPY(sOriQqdZt, st_gab_dxzp_xdxx.qqdzt)
    
    memset(sHostfcflat,0x00,sizeof(sHostfcflat));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_HXFCBZ,sHostfcflat,"���ĳ�ʱ�Ƿ���ر�־");

    /*������ڴ���״̬*/
    if ( strcmp(sOriQqdZt, "99" ) == 0 )
    {
	    LOG(LM_STD, Fmtmsg("��ָ���ѷ���,�������ٴη���"), "ERROR");
	    fpub_SetMsg(lXmlhandle, 99903, "��ָ���ѷ���,����Ҫ�ٴη���");
	    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	    return COMPRET_FAIL;
    }

    /*������ڴ���״̬*/
    if ( sOriQqdZt[1] == '9')
    {
	    LOG(LM_STD, Fmtmsg("ҵ�����ڴ�����,�������ٴδ���,״̬����[%s]", sOriQqdZt), "ERROR");
	    fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DEALING, MSG_GAB_DXZP_DEALING);
	    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	    return COMPRET_FAIL;
    }
    /*���ݴ���������״̬���,Ϊ���������*/
    if(sCllx[0]=='2')
    {/*Ҫ���ύ����,����״̬���12-��سɹ���21-�ύʧ��*/
        /*alter by liukq 20160324 BEGIN*/
        if (strcmp(sOriQqdZt, "20") != 0 && strcmp(sOriQqdZt, "21") != 0 && strcmp(sOriQqdZt, "23") != 0 && strcmp(sOriQqdZt, "33") != 0 )
        {
	        LOG(LM_STD, Fmtmsg("Ҫ���ύ����,״̬����[%s]", sOriQqdZt), "ERROR");
	        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_CHKSTS, MSG_GAB_DXZP_CHKSTS);
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	        return COMPRET_FAIL;
        }
        if(0==strcmp(sHostfcflat,"1"))
        {/*���ķ���*/
            if(0== strcmp(sOriQqdZt, "21") || 0 == strcmp(sOriQqdZt, "23") || 0 == strcmp(sOriQqdZt, "33") )
            {
                strcpy(st_gab_dxzp_xdxx.qqdzt,"20");
            	iRet=fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
                GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "������Ϣ�´��");
                DCICommit();
                COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, "20")
                COMP_SOFTSETXML("/gabdxzp/xxxd/qqdzt","20")
                strcpy(sOriQqdZt,"20");
            }
         }else 
         {/*���Ĳ�����*/
            if (0 == strcmp(sOriQqdZt, "21"))
            {/*��������ҵ����ˮ��*/
                /*ҵ����ˮ��*/
                memset(sSql, 0x00, sizeof(sSql));
                GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_DXZP_XL,sSql,"ҵ����ˮ��");
                memset(&st_gab_dxzp_dual, 0x00, sizeof(st_gab_dxzp_dual));
                LOG(LM_STD, Fmtmsg("�Ǽ��´���Ϣ��->sfxt_xl[%s]", sSql), fpub_GetCompname(lXmlhandle));
                iRet=fdbop_qry_dual(lXmlhandle, &st_gab_dxzp_dual, sSql);
                GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "��ȡҵ����ˮ��");
                snprintf(st_gab_dxzp_xdxx.ywlsh, sizeof(st_gab_dxzp_xdxx.ywlsh), 
                    "08%ld", st_gab_dxzp_dual.nextval);
                
                GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,st_gab_dxzp_xdxx.ywrq,"ҵ������");
                strcpy(st_gab_dxzp_xdxx.qqdzt,"20");
            	iRet=fdbop_upd_gab_dxzp_xdxx_ywlsh(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
                GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "������Ϣ�´��");
                DCICommit();
                COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, "20")
                COMP_SOFTSETXML("/gabdxzp/xxxd/qqdzt","20")
                strcpy(sOriQqdZt,"20");
            }else if( 0 == strcmp(sOriQqdZt, "23") || 0 == strcmp(sOriQqdZt, "33") )
            {
                LOG(LM_STD, Fmtmsg("ԭ�����ύ���ĳ�ʱ,���Ĳ�����,���֤���ٴ���!"), "ERROR");
	            fpub_SetMsg(lXmlhandle, 99999, "ԭ�����ύ���ĳ�ʱ,���Ĳ�����,���֤���ٴ���");
	            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	            return COMPRET_FAIL;
            }
        }
        /*alter by liukq 20160324 END*/
        
    }else if(sCllx[0]=='3')
    {/*Ҫ��������,����״̬���22-�ύ�ɹ� �� 31-���ʧ��*/
    	   /*alter by liukq 20160324 BEGIN*/
        if (strcmp(sOriQqdZt, "30") != 0 && strcmp(sOriQqdZt, "23") != 0 && strcmp(sOriQqdZt, "31") != 0 && strcmp(sOriQqdZt, "33") != 0)
        {
	        LOG(LM_STD, Fmtmsg("Ҫ����غ���,״̬����[%s]", sOriQqdZt), "ERROR");
	        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_CHKSTS, MSG_GAB_DXZP_CHKSTS);
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	        return COMPRET_FAIL;
        }
        if(0==strcmp(sHostfcflat,"1"))
        	{
           if(0== strcmp(sOriQqdZt, "31") ||  0 == strcmp(sOriQqdZt, "23") || 0== strcmp(sOriQqdZt, "33") )
           	{
           		/*alter 22-->30 by liukq 20160426  BEGIB*/
           		strcpy(st_gab_dxzp_xdxx.qqdzt,"30");
           		iRet=fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
              GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "������Ϣ�´��");
              DCICommit();
              COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, "30")
              COMP_SOFTSETXML("/gabdxzp/xxxd/qqdzt","30")
              strcpy(sOriQqdZt,"30");
              /*alter by liukq 20160426  END*/
           	}
         }
         else 
         	{
         		if( 0 == strcmp(sOriQqdZt, "23") || 0 == strcmp(sOriQqdZt, "33") )
         			{
         				 LOG(LM_STD, Fmtmsg("���Ĳ������ύʧ��!"), "ERROR");
	               fpub_SetMsg(lXmlhandle, 99999, "���Ĳ������ύʧ��");
	               fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	               return COMPRET_FAIL;
           	}
         }
        /*alter by liukq 20160324 END*/
    }else if(sCllx[0]=='4')
    {/*Ҫ����ǰ��,����״̬���32-��سɹ� ��41-����ʧ��*/
    	  /*add by liukq 20160323 sOriQqdZt=43,add 20160406 sOriQqdZt=31*/
        if (strcmp(sOriQqdZt, "31") != 0 &&strcmp(sOriQqdZt, "40") != 0 && strcmp(sOriQqdZt, "41") != 0 && strcmp(sOriQqdZt, "43") != 0)
        {
	        LOG(LM_STD, Fmtmsg("Ҫ����ǰ��,״̬����[%s]", sOriQqdZt), "ERROR");
	        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_CHKSTS, MSG_GAB_DXZP_CHKSTS);
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	        return COMPRET_FAIL;
        }
    }else
    {/*�������,����������*/
        
    }
    /*��ȡ�µ�����״̬*/
    memset(sNewQqdZt, 0x00, sizeof(sNewQqdZt));
    sNewQqdZt[0]=sCllx[0];
    sNewQqdZt[1]='9';
    /*��������״̬*/
    DCIBegin();
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.qqdzt, sNewQqdZt);
    iRet=fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "��ѯ��Ϣ�´��");
    DCICommit();
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, st_gab_dxzp_xdxx.qqdzt)
    COMP_SOFTSETXML(XMLNM_SFXT_HOST_REQ_CLLX, sCllx)
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("������ҵ��״̬���->����ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_CALLHOST_COMMPROC
 �������:�����ĺ󹫹�����
 �������:�����ĺ󹫹�����
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_CALLHOST_COMMPROC(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sYwsqBh[36+1];/*ҵ��������*/
    char sOriQqdZt[2+1];/*����״̬*/
    char sHxSynMode[1+1];/*����ͬ�첽ģʽ*/
    char sYwlxBm[6+1];/*ҵ�����ͱ���*/
    char sTableName[4+1];
    char sSbPch[36+1];/*�ϱ����κ�*/
    char sMAXTJHXCS[20];/*�ύ����������*/
    GAB_DXZP_XDXX st_gab_dxzp_xdxx;/*�´���Ϣ��*/
    /*add by liukq 20160331 BEGIN*/
    GAB_DXZP_XDXX st_gab_dxzp_xdxx_tjhxcs;/*�´���Ϣ��ר����tjhxcs*/
    /*add by liukq 20160331 END*/
    memset(sYwsqBh, 0x00, sizeof(sYwsqBh));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH, sYwsqBh,"ҵ��������");
    memset(sOriQqdZt, 0x00, sizeof(sOriQqdZt));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QQDZT, sOriQqdZt,"����״̬");
    memset(sHxSynMode, 0x00, sizeof(sHxSynMode));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_HXSYNFLG, sHxSynMode,"����ͬ�첽ģʽ");
    memset(sSbPch, 0x00, sizeof(sSbPch));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTCX_RESP_SBPCH, sSbPch,"�ϱ����κ�");
    LOG(LM_STD, Fmtmsg("�����ĺ󹫹�����->ywsqbh[%s],sOriQqdZt[%s],sHxSynMode[%s],sSbPch[%s]", 
        sYwsqBh, sOriQqdZt, sHxSynMode, sSbPch), fpub_GetCompname(lXmlhandle));
    /*��ȡ������Ӧ���*/
    memset(&st_gab_dxzp_xdxx, 0x00, sizeof(st_gab_dxzp_xdxx));
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.ywsqbh, sYwsqBh)
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.qqdzt, sOriQqdZt);
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.sbpch, sSbPch);
    /*add by liukq 20160408 BEGIN*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_YwyDm, st_gab_dxzp_xdxx.ywydm,"ҵ��Ӧ����");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_sYwyDxx, st_gab_dxzp_xdxx.ywydxx,"ҵ��Ӧ����Ϣ");
    trim(st_gab_dxzp_xdxx.ywydm);
    trim( st_gab_dxzp_xdxx.ywydxx);
    /*add by liukq 20160408 END*/
    /*add by liukq 20160331 BEGIN*/
    memset(&st_gab_dxzp_xdxx_tjhxcs, 0x00, sizeof(st_gab_dxzp_xdxx_tjhxcs));
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx_tjhxcs.ywsqbh, sYwsqBh)
    /*add by liukq 20160331 END*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_RESPCODE, st_gab_dxzp_xdxx.respcode,"��Ӧ��");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_RESPMSG, st_gab_dxzp_xdxx.respmsg,"��Ӧ��Ϣ");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_HOST_RESP_ZJRQ, st_gab_dxzp_xdxx.zjrq,"��������");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_HOST_RESP_ZJLSH, st_gab_dxzp_xdxx.zjlsh,"������ˮ��");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_DZXH, st_gab_dxzp_xdxx.dzxh,"��ֹ���");
    
    /*add by liukq 20160328*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,st_gab_dxzp_xdxx.clrq,"��������");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSTIME,st_gab_dxzp_xdxx.clsj,"����ʱ��");
    /*add by liukq 20160328*/
    st_gab_dxzp_xdxx.zxjg[0]='0';/*ִ�н�� 0-���ɹ�*/
    if(strcmp(st_gab_dxzp_xdxx.respcode, "00000") == 0)
    {/*�ɹ�*/
        st_gab_dxzp_xdxx.qqdzt[0]='4';
        st_gab_dxzp_xdxx.qqdzt[1]='0';
        st_gab_dxzp_xdxx.zxjg[0]='1';/*ִ�н�� 1-�ɹ�*/
        if (sHxSynMode[0] == '1')
        {/*����ͬ�첽ģʽ 0-ͬ�� ,������״̬ǿ��Ϊ3-���*/
          st_gab_dxzp_xdxx.qqdzt[0]='3';
         }
    }else if (strcmp(st_gab_dxzp_xdxx.respcode, "99999") == 0 || strcmp(st_gab_dxzp_xdxx.respcode, "98501") == 0)
    {/*��ʱ*/
    	  /*st_gab_dxzp_xdxx.qqdzt[1]='3';*/
    	  /*add by liukq 20160331 BEGIN*/
    	  if (sHxSynMode[0] == '0')
        {/*����ͬ�첽ģʽ 0-ͬ�� ,������״̬ǿ��Ϊ3-���*/
          st_gab_dxzp_xdxx.qqdzt[0]='3';
         }
    	  iRet=fdbop_qry_gab_dxzp_xdxx(lXmlhandle, &st_gab_dxzp_xdxx_tjhxcs);
        GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "��ѯ��Ϣ�´��");
        memset(sMAXTJHXCS,0x00,sizeof(sMAXTJHXCS));
        GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/maxtjhxcs", sMAXTJHXCS,"�ύ����������");
        LOG(LM_STD,Fmtmsg("tjhxcs[%d],sMAXTJHXCS[%s]",st_gab_dxzp_xdxx_tjhxcs.tjhxcs,sMAXTJHXCS),"DEBUG");
        if(st_gab_dxzp_xdxx_tjhxcs.tjhxcs<atoi(sMAXTJHXCS) || 0==strcmp(st_gab_dxzp_xdxx_tjhxcs.jybm,"100305"))
        {
          st_gab_dxzp_xdxx.qqdzt[1]='3';
        }
        else
        {
        	st_gab_dxzp_xdxx.qqdzt[1]='1';
        }
        /*add by liukq 20160331 END*/
    }else
    {/*ʧ��*/
    	  if (sHxSynMode[0] == '0')
        {/*����ͬ�첽ģʽ 0-ͬ�� ,������״̬ǿ��Ϊ3-���*/
          st_gab_dxzp_xdxx.qqdzt[0]='3';
         }
        st_gab_dxzp_xdxx.qqdzt[1]='1';
    }
    COMP_SOFTSETXML("/host/resp/zjjg", st_gab_dxzp_xdxx.zxjg);
    
    /*��ȡ�ֱ���*/
    memset(sYwlxBm, 0x00, sizeof(sYwlxBm));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWLXBM, sYwlxBm,"ҵ�����ͱ���");
    switch(atoi(sYwlxBm))
    {
        case 100101:/*ֹ��*/
        case 100103:/*ֹ�����*/
        case 100105:/*ֹ������*/
            GAB_DXZP_PSTRCOPY(sTableName, "jjzf");
            break;
        case 100201:/*����*/
        case 100203:/*������*/
        case 100205:/*��������*/
            GAB_DXZP_PSTRCOPY(sTableName, "djxj");
            break;
        case 100301:/*������ϸ��ѯ*/
            GAB_DXZP_PSTRCOPY(sTableName, "jymx");
            break;
        case 100303:/*�����ѯ*/
            GAB_DXZP_PSTRCOPY(sTableName, "ztcx");
            break;
        case 100305:/*��̬��ѯ*/
        case 100307:/*��̬�����ѯ*/
            GAB_DXZP_PSTRCOPY(sTableName, "dtcx");
            break;
        case 100309:/*�ͻ�ȫ�˺Ų�ѯ*/
            GAB_DXZP_PSTRCOPY(sTableName, "qhcx");
            break;
        default:
            break;
    }
    LOG(LM_STD, Fmtmsg("�����ĺ󹫹�����->sNewQqdZt[%s],sTableName[%s]", 
        st_gab_dxzp_xdxx.qqdzt, sTableName), fpub_GetCompname(lXmlhandle));
    
    
    
    DCIBegin();
    iRet=fdbop_upd_gab_dxzp_xdxx_aftCallHost(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "������Ϣ�´��");
    iRet=fdbop_upd_gab_dxzp_busi(lXmlhandle, &st_gab_dxzp_xdxx, sTableName);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "����ҵ���");
    DCICommit();
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, st_gab_dxzp_xdxx.qqdzt)
    COMP_SOFTSETXML(XMLNM_SFXT_HOST_RESP_ZXJG, st_gab_dxzp_xdxx.zxjg)
    //if (sHxSynMode[0] == '1' && strcmp(st_gab_dxzp_xdxx.qqdzt, "21") == 0)
    if (sHxSynMode[0] == '1' && strcmp(st_gab_dxzp_xdxx.qqdzt, "30") == 0)
    {/*�첽���ύ���ĳɹ�,����Ϊ�˳�*/
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOG(LM_STD, Fmtmsg("�����ĺ󹫹�����->�첽���ύ���ĳɹ�,��Ϊͣ����"), fpub_GetCompname(lXmlhandle));
        //fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_BATCH_BREAK, MSG_GAB_DXZP_BATCH_BREAK);
        return COMPSTATUS_SUCC;
    }
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�����ĺ󹫹�����->����ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_UPDSTS
 �������:��������״̬
 �������:��������״̬
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_UPDSTS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sYwsqBh[36+1];/*ҵ��������*/
    char sOriQqdZt[2+1];/*����״̬*/
    char sNewQqdZt[2+1];/*����״̬*/
    char sCllx[1+1];/*��������*/
    char sYwlxBm[6+1];/*ҵ�����ͱ���*/
    char sSuccFail[16+1];
    GAB_DXZP_XDXX st_gab_dxzp_xdxx;/*�´���Ϣ��*/
    
    memset(sSuccFail, 0, sizeof(sSuccFail));
    COMP_GETPARSEPARAS(1,sSuccFail,"��ʧ��־")
    
    memset(sNewQqdZt, 0, sizeof(sNewQqdZt));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"����״̬")
    
    GAB_DXZP_PSTRCOPY(sNewQqdZt, sBuf);
    memset(sYwsqBh, 0x00, sizeof(sYwsqBh));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH, sYwsqBh,"ҵ��������");
   
    memset(sOriQqdZt, 0x00, sizeof(sOriQqdZt));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QQDZT, sOriQqdZt,"����״̬");
   
    /*��������Ϊ1-���ʱ��Ĭ��Ϊ���ʵʱ�ύ����*/
    memset(sCllx, 0x00, sizeof(sCllx));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_HOST_REQ_CLLX, sCllx, "��������");

    LOG(LM_STD, Fmtmsg("��������״̬->ywsqbh[%s],sOriQqdZt[%s],sSuccFail[%s],sNewQqdZt[%s]", 
        sYwsqBh, sOriQqdZt, sSuccFail, sNewQqdZt), fpub_GetCompname(lXmlhandle));
    if (sSuccFail[0] != '\0')
    {/*������ʧ��־*/
        GAB_DXZP_PSTRCOPY(sNewQqdZt, sOriQqdZt);
        sNewQqdZt[1] = sSuccFail[0];
    }else
    {/*���򴫽�������״̬*/
       if (sCllx[0] == '3')
        {/*��Ϊ3-�������,����״̬ҲӦ����һ��*/
            sNewQqdZt[0] = sCllx[0];
        }
    }
    
    /*��������״̬*/
    memset(&st_gab_dxzp_xdxx, 0x00, sizeof(st_gab_dxzp_xdxx));
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.ywsqbh, sYwsqBh);
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.qqdzt, sNewQqdZt);
    DCIBegin();
    iRet=fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "��ѯ��Ϣ�´��");
    DCICommit();
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, st_gab_dxzp_xdxx.qqdzt)
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("��������״̬->����ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
��̬�����������
�����������:GAB_DXZP_AUTOPROC
�������: GAB_DXZP_AUTOPROC
�������: ����������թƭ�Զ�����
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    
�����  
0   �ɹ�
-1  ʧ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_945118(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sSysDate[8+1];
    char sSysTime[6+1];
    char errmsg[256];
    char sProcKind[2+1];/*1-����+ʧ��,2-ͳһ����,3-��̬��ѯ*/
    char sProcDate[8+1];
    char sBusiTable[64+1];
    int  iAutoProcs=10;/*�Զ����������*/
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    char sHxSynMode[1+1];
    CURSOR cur;
    GAB_DXZP_AUTOPROC gab_dxzp_autoproc;
    
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHKMIN(1);
    memset(sProcKind, 0x00, sizeof(sProcKind));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "��������"); 
    pstrcopy(sProcKind, sBuf, sizeof(sProcKind));

    memset(sSysDate, 0x00, sizeof(sSysDate));
    COMP_SOFTGETXML(XMLNM_SYSDATE, sSysDate)
    memset(sSysTime, 0x00, sizeof(sSysTime));
    COMP_SOFTGETXML(XMLNM_SYSTIME, sSysTime)
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_DXZP_AUTOPROCS, sBuf)
    if ( sBuf[0] != '\0')
    {
        iAutoProcs = atoi(sBuf);
    }
    /*add by liukq 20160331 BEGIN*/
    memset(sHxSynMode, 0x00, sizeof(sHxSynMode));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_HXSYNFLG, sHxSynMode,"����ͬ�첽ģʽ");
    /*add by liukq 20160331 END*/
    
    LOG(LM_STD,Fmtmsg("����������թƭ�Զ�����ִ�п�ʼ[%d]",iAutoProcs),fpub_GetCompname(lXmlhandle));
    
    /* ��ѯ��Ҫ��������� */
    memset(sSql, 0x00, sizeof(sSql));
    /*add jybm !='100305' by liukq 20160316  add qqdzt in 23,33 20160331 add qqdzt in 31 20160406 begin */
    /*alter by liukq 20160504 ������ҵ��ͳ�ʱҵ��ֿ� BEGIN*/
    if (sProcKind[0] == '2')
    {
        snprintf(sSql,sizeof(sSql),"SELECT ywsqbh,jjcd,qqdzt,'' FROM gab_dxzp_xdxx \
            WHERE qqdzt in ('20', '30', '31','40') and jybm !='100305' ORDER BY jjcd desc, ywsqbh asc ");
    }else if (sProcKind[0] == '3')
    {
        snprintf(sSql,sizeof(sSql),"SELECT ywsqbh,jjcd,qqdzt,'' FROM gab_dxzp_xdxx \
            WHERE qqdzt in ('23','33') and jybm !='100305' ORDER BY jjcd desc, ywsqbh asc ");
    }else if (sProcKind[0] == '4')
    {
        snprintf(sSql,sizeof(sSql),"SELECT ywsqbh,jjcd,qqdzt,'' FROM gab_dxzp_xdxx \
            WHERE qqdzt in ('43') and jybm !='100305' ORDER BY jjcd desc, ywsqbh asc ");
    }
    else
    {
        snprintf(sSql,sizeof(sSql),"SELECT ywsqbh,jjcd,qqdzt,'' FROM gab_dxzp_xdxx \
            WHERE ( fkddrq <'%s' or ( fkddrq ='%s' and fkddsj < '%s') ) and qqdzt in ('20', '30','31','40')  and jybm !='100305' ORDER BY jjcd desc, ywsqbh asc ", 
            sSysDate, sSysDate, sSysTime );
    }
    /*alter by liukq 20160504 ������ҵ��ͳ�ʱҵ��ֿ� END*/
    /*add jybm !='100305' by liukq 20160316 end */
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
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
    
    for ( i=1; i<=iAutoProcs; i++)
    {
        memset(&gab_dxzp_autoproc, 0x00, sizeof(gab_dxzp_autoproc));
        iRet = DBFetch(cur, SD_GAB_DXZP_AUTOPROC, NUMELE(SD_GAB_DXZP_AUTOPROC), &gab_dxzp_autoproc, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        
        /* ����������Ϣ��ֵ */
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_YWSQBH, gab_dxzp_autoproc.ywsqbh);/*ҵ��������*/
        /*alter by liukq 20160316 begin*/
        memset(sProcKind,0x00,sizeof(sProcKind));
        if(0 == strcmp(gab_dxzp_autoproc.qqdzt,"20") || 0 == strcmp(gab_dxzp_autoproc.qqdzt,"23") ||  0 == strcmp(gab_dxzp_autoproc.qqdzt,"33"))
        	{
        		if( 0 == strcmp(gab_dxzp_autoproc.qqdzt,"33") || 0 == strcmp(gab_dxzp_autoproc.qqdzt,"23"))
        			{
        		   if (sHxSynMode[0] == '0')
                 {/*����ͬ�첽ģʽ 0-ͬ�� */
        		       strcpy(sProcKind,"2");
        	       }
        	      else
        	      	{
        	      		strcpy(sProcKind,"3");
        	      	}
        	    }
        	   else
        	    {
        	    	strcpy(sProcKind,"2");
        	    }
        	}
        if(0 == strcmp(gab_dxzp_autoproc.qqdzt,"30"))
        	{
        		strcpy(sProcKind,"3");
        	}
        if(0 == strcmp(gab_dxzp_autoproc.qqdzt,"31") || 0 == strcmp(gab_dxzp_autoproc.qqdzt,"40") || 0 == strcmp(gab_dxzp_autoproc.qqdzt,"43"))
        	{
        		strcpy(sProcKind,"4");
        	}
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_CLLX,sProcKind);/*��������*/
        /*alter by liukq 20160316 begin*/
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
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_STD,Fmtmsg("����������թƭ�Զ�����ִ�н���,������[%d]��ҵ��", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"����������թƭ�Զ�����ִ�н���");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:GAB_DXZP_945118_DTCX
�������: GAB_DXZP_945118_DTCX
�������: ����������թƭ��̬��ѯ
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    
�����  
0   �ɹ�
-1  ʧ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_945118_DTCX(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sSysDate[8+1];
    char sSysTime[6+1];
    char sCurDateTime[14+1];
    char errmsg[256];
    char sProcKind[2+1];/*1-����+ʧ��,2-ͳһ����,32-��̬��ѯ����ȡ��,34-��̬��ѯ����ǰ��*/
    int i=1;
    int iRet=-1;
    
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHKMIN(1);
    memset(sProcKind, 0x00, sizeof(sProcKind));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "��������"); 
    pstrcopy(sProcKind, sBuf, sizeof(sProcKind));

    memset(sSysDate, 0x00, sizeof(sSysDate));
    COMP_SOFTGETXML(XMLNM_SYSDATE, sSysDate)
    memset(sSysTime, 0x00, sizeof(sSysTime));
    COMP_SOFTGETXML(XMLNM_SYSTIME, sSysTime)
    memset(sCurDateTime, 0x00, sizeof(sCurDateTime));
    snprintf(sCurDateTime, sizeof(sCurDateTime),"%s%s", sSysDate, sSysTime);
    
    LOG(LM_STD,Fmtmsg("����������թƭ�Զ�����ִ�п�ʼ"),fpub_GetCompname(lXmlhandle));
    
    /* ��ѯ��Ҫ��������� */
    memset(sSql, 0x00, sizeof(sSql));
    if (strcmp(sProcKind, "32") == 0 )
    {/*����ȡ��*/
        snprintf(sSql,sizeof(sSql),"SELECT a.ywsqbh,a.jjcd,a.qqdzt,b.zh FROM gab_dxzp_dtcx b, gab_dxzp_xdxx a \
            WHERE a.ywsqbh = b.ywsqbh and b.zxjzrq > '%s' and b.dtml='1' and a.qqdzt != '40' ORDER BY ywsqbh asc ", sCurDateTime );
        LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
        iRet = ffunc_dxzp_945118_DTCX_hxqs(lXmlhandle, sSql, sCurDateTime);
    }else
    {/*����ǰ��*/
        COMP_SOFTSETXML("/gabdxzp/dtcxplfk", "1")/*��̬��ѯ��������*/
        snprintf(sSql,sizeof(sSql),"SELECT a.ywsqbh,a.jjcd,a.qqdzt,b.zh FROM gab_dxzp_dtcx b, gab_dxzp_xdxx a \
            WHERE a.ywsqbh = b.ywsqbh and b.zxjzrq > '%s' and b.dtml='1' and a.qqdzt = '40' ORDER BY ywsqbh asc ", sCurDateTime );
        LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
        iRet = ffunc_dxzp_945118_DTCX_fkqz(lXmlhandle, sSql, sCurDateTime);
    }
    
    LOG(LM_STD,Fmtmsg("����������թƭ�Զ�����ִ�н���"), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"����������թƭ�Զ�����ִ�н���");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}


/************************************************************************
��̬�����������
�����������:GAB_DXZP_945124
�������: GAB_DXZP_945124
�������: ����թƭ��̬��ѯ��������
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    
�����  
0   �ɹ�
-1  ʧ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_945124(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sSysDate[8+1];
    char sSysTime[6+1];
    char sCurDateTime[14+1];
    char sZh[32+1];
    char errmsg[256];
    int i=1;
    int iRet=-1;
    
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHKMIN(1);
    memset(sZh, 0x00, sizeof(sZh));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "�˺�"); 
    pstrcopy(sZh, sBuf, sizeof(sZh));

    memset(sSysDate, 0x00, sizeof(sSysDate));
    COMP_SOFTGETXML(XMLNM_SYSDATE, sSysDate)
    memset(sSysTime, 0x00, sizeof(sSysTime));
    COMP_SOFTGETXML(XMLNM_SYSTIME, sSysTime)
    memset(sCurDateTime, 0x00, sizeof(sCurDateTime));
    snprintf(sCurDateTime, sizeof(sCurDateTime),"%s%s", sSysDate, sSysTime);
    
    LOG(LM_STD,Fmtmsg("����������թƭ��̬��ѯʵʱ���ͷ���ִ�п�ʼ"),fpub_GetCompname(lXmlhandle));
    
    /* ��ѯ��Ҫ��������� */
    memset(sSql, 0x00, sizeof(sSql));
    /*����ǰ��*/
    COMP_SOFTSETXML("/gabdxzp/dtcxplfk", "1")/*��̬��ѯ��������*/
    snprintf(sSql,sizeof(sSql),"SELECT a.ywsqbh,a.jjcd,a.qqdzt,b.zh FROM gab_dxzp_dtcx b, gab_dxzp_xdxx a \
        WHERE a.ywsqbh = b.ywsqbh and b.zxjzrq > '%s' and b.dtml='1' and b.zh = '%s' ORDER BY ywsqbh asc ", sCurDateTime, sZh );
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    iRet = ffunc_dxzp_DTCX_sstsfk(lXmlhandle, sSql, sCurDateTime);

    LOG(LM_STD,Fmtmsg("����������թƭ��̬��ѯʵʱ���ͷ���ִ�н���"), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"����������թƭ��̬��ѯʵʱ���ͷ���ִ�н���");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
/************************************************************************
��̬�����������
�����������:GAB_DXZP_COMMQZJ
�������:��ǰ�û�ͨѶ
�������:��ǰ�û�ͨѶ
�������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��Ҫ�������:
  ����                       ����

��������:

�� Ŀ ��: 
�� �� Ա:������ 
��������:2016-03-10
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_COMMQZJ(HXMLTREE lXmlhandle)
{
    int iParas;
    int iSock;                          /*�׽���*/
    uint32_t lCommbufLen=0;         /*ͨѶ������*/
    uint32_t lCommbufLen2=0;                /*ͨѶ������*/
    char sBuf[256];             /*��������*/
    char sIp[16+1];                 /*IP*/
    int iPort;                          /*�˿�*/
    int iOuttime;                   /*��ʱʱ��*/
    char sCommBufLen[8+1];  /*ͨѶ������*/
    char *pCommBuf=NULL;    /*ͨѶ��*/
    int iRet=-1;
    
    /*1-�����ʼ*/
    fpub_InitSoComp(lXmlhandle);

    /*2-��ȡ����*/
    COMP_PARACOUNTCHK(3)
    memset(sBuf, 0x00, sizeof ( sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "������IP");
    pstrcopy(sIp, sBuf, sizeof(sIp));

    memset(sBuf, 0x00, sizeof ( sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "�������˿�");
    iPort = atoi(sBuf);

    memset(sBuf, 0x00, sizeof ( sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "��ʱʱ��");
    iOuttime = atoi(sBuf);

    LOG(LM_STD, Fmtmsg("��ǰ�û�ͨѶִ�п�ʼ[%s][%d][%d]",
        sIp, iPort, iOuttime), fpub_GetCompname(lXmlhandle));

    lCommbufLen = xml_GetBinElementLen(lXmlhandle, "/commbuf");
    if (lCommbufLen <= 0 )
    {
        LOG(LM_STD,Fmtmsg("/commbuf����Ϊ[%s],��ȷ��", lCommbufLen ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* ���ݻ�ȡ���ĳ��������ڴ� */
    pCommBuf = (char *)malloc( lCommbufLen+1 );
    if ( pCommBuf == NULL )
    {
        LOG(LM_STD,Fmtmsg("��̬����commbuf�ڴ�ʧ��" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*2-��ͨѶ������*/
    memset(pCommBuf, 0x00, lCommbufLen+1);
    if(0 > (iRet = xml_RelGetBinElement(lXmlhandle, "/commbuf", pCommBuf, lCommbufLen+1)))
    {
        LOG(LM_STD, Fmtmsg("ȡǰ�û�ͨѶ������iRet=[%d]", iRet), "DEBUG");
        /*alter by liukq 20160427 BEGIN
        fpub_SetMsg(lXmlhandle, 99999, "��ǰ�û�ͨѶʧ��,��ȡͨѶ������");
        */
        /*alter by liukq 20160427 BEGIN*/
        fpub_SetMsg(lXmlhandle, 98601, "��ǰ�û�ͨѶʧ��,��ȡͨѶ������");
        /*alter by liukq 20160427 END*/
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*ȥ��ҵ�����ͱ���*/
    /*alter by liukq 20160427 BEGIN
    lCommbufLen -= 6;
    memmove(pCommBuf, pCommBuf+6, lCommbufLen);
    pCommBuf[lCommbufLen] = '\0'; END*/
    LOG(LM_STD, Fmtmsg("lCommbufLen=[%d][%s]", lCommbufLen, pCommBuf), fpub_GetCompname(lXmlhandle));
    /*3-�����˽�������*/
    itcp_sethead(1);
    itcp_setenv(iPort, &iSock);
    if(0 > (iRet = itcp_calln(sIp,3)))
    {
        free(pCommBuf);pCommBuf=NULL;
        LOG(LM_STD, Fmtmsg("��ǰ�û��������Ӵ���iRet=[%d]", iRet), "DEBUG");
        /*alter by liukq 20160427 BEGIN
        fpub_SetMsg(lXmlhandle, 99999, "��ǰ�û�ͨѶʧ��,�������Ӵ���");
        */
        /*alter by liukq 20160427 BEGIN*/
        fpub_SetMsg(lXmlhandle, 98601, "��ǰ�û�ͨѶʧ��,�������Ӵ���"); 
        /*alter by liukq 20160427 END*/
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*3-����ͨѶ������*/
    LOG(LM_STD, Fmtmsg("����ǰ�û�ͨѶ������=[%d]", lCommbufLen+4), fpub_GetCompname(lXmlhandle));
    lCommbufLen2 = htonl(lCommbufLen);
    if(0 > (iRet = itcp_send((char *)&lCommbufLen2, 4, iOuttime)))
    {
        itcp_clear();
        free(pCommBuf);pCommBuf=NULL;
        LOG(LM_STD, Fmtmsg("����ǰ�û�ͨѶ�����ȴ���iRet=[%d]", iRet), fpub_GetCompname(lXmlhandle));
        fpub_SetMsg(lXmlhandle, 99999, "��ǰ�û�ͨѶʧ��,����ͨѶ�����ȴ���");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*5-����ͨѶ��*/
    if(0 > (iRet = itcp_send(pCommBuf, lCommbufLen, iOuttime)))
    {
        itcp_clear();
        free(pCommBuf);pCommBuf=NULL;
        LOG(LM_STD, Fmtmsg("����ǰ�û�ͨѶ������iRet=[%d]", iRet), "DEBUG");
        fpub_SetMsg(lXmlhandle, 99999, "��ǰ�û�ͨѶʧ��,����ͨѶ������");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    free(pCommBuf);pCommBuf=NULL;
    /*6-����ͨѶ������*/
    lCommbufLen2 = 0;
    if(0 > (iRet = itcp_recv((char *)&lCommbufLen2, 4, iOuttime)))
    {
        LOG(LM_STD, Fmtmsg("����ǰ�û�ͨѶ�����ȴ���iRet=[%d]", iRet), "DEBUG");
        itcp_clear();
        fpub_SetMsg(lXmlhandle, 99999, "��ǰ�û�ͨѶ��ʱ,����ͨѶ�����ȴ���");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    lCommbufLen = ntohl(lCommbufLen2);
    LOG(LM_STD, Fmtmsg("����ǰ�û���Ӧ���ĳ���=[%ld]", lCommbufLen), fpub_GetCompname(lXmlhandle));
    /* ���ݻ�ȡ���ĳ��������ڴ� */
    pCommBuf = (char *)malloc( lCommbufLen+1 );
    if ( pCommBuf == NULL )
    {
        LOG(LM_STD,Fmtmsg("��̬����commbuf�ڴ�ʧ��" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    memset(pCommBuf, 0x00, lCommbufLen+1);
    /*7-����ͨѶ��*/
    if(0 > (iRet = itcp_recv(pCommBuf, lCommbufLen, iOuttime)))
    {
        itcp_clear();
        free(pCommBuf);pCommBuf=NULL;
        LOG(LM_STD, Fmtmsg("����ͨѶ������iRet=[%d]", iRet), "DEBUG");
        fpub_SetMsg(lXmlhandle, 99999, "��ǰ�û�ͨѶ��ʱ,����ͨѶ������");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD, Fmtmsg("����ǰ�û���Ӧ����=[%d][%s]", lCommbufLen, pCommBuf), fpub_GetCompname(lXmlhandle));
    itcp_clear();
    
    /*9-д��commbuf*/
    if(0 > (iRet = xml_RelSetBinElement(lXmlhandle, "/commbuf", pCommBuf, lCommbufLen)))
    {
        free(pCommBuf);pCommBuf=NULL;
        LOG(LM_STD, Fmtmsg("дǰ�û�ͨѶ������iRet=[%d]", iRet), "DEBUG");
        /*alter by liukq 20160427 BEGIN
        fpub_SetMsg(lXmlhandle, 99999, "��ǰ�û�ͨѶ��ʱ,дͨѶ������");
        */
        /*alter by liukq 20160427 BEGIN*/
        fpub_SetMsg(lXmlhandle, 98601, "��ǰ�û�ͨѶʧ��,дͨѶ������");
        /*alter by liukq 20160427 END*/
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    free(pCommBuf);pCommBuf=NULL;
    /*14-�������*/
    LOG(LM_STD,Fmtmsg("��ǰ�û�ͨѶִ�н���"),fpub_GetCompname(lXmlhandle));
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:GAB_DXZP_945122
�������: GAB_DXZP_945122
�������: ����������թƭ������Ϣ�ϱ�
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    
�����  
0   �ɹ�
-1  ʧ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_945122(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sSbPch[36+1];
    char sSbJydm[6+1];
    char sJybm[6+1];
    char errmsg[256];
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    CURSOR cur;
    GAB_DXZP_SBXX_PLZT gab_dxzp_sbxx_plzt;
    
    fpub_InitSoComp(lXmlhandle);
    
    memset(sSbPch, 0x00, sizeof(sSbPch));
    GAB_DXZP_GETXMLSTR_NOTNULL("/gabdxzp/sbpch",sSbPch,"�ϱ����κ�");
    
    LOG(LM_STD,Fmtmsg("������Ϣ�ϱ�ִ�п�ʼ[%s],sbjydm[%s],jybm[%s]",
        sSbPch, sSbJydm, sJybm),fpub_GetCompname(lXmlhandle));
    COMP_SOFTSETXML("/gabdxzp/YorNbatch", "1");
    /* ��ѯ��Ҫ��������� */
    memset(sSql, 0x00, sizeof(sSql));
    /*add sbzt=3��ʱ�ϱ� by liukq 20160324 BEGIN*/
    snprintf(sSql,sizeof(sSql),"SELECT * FROM gab_dxzp_sbxx_plzt WHERE sbpch='%s' and sbzt in ('0', '2','3')", sSbPch);
    /*add by liukq 20160324 END*/
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
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
        memset(&gab_dxzp_sbxx_plzt, 0x00, sizeof(gab_dxzp_sbxx_plzt));
        iRet = DBFetch(cur, SD_GAB_DXZP_SBXX_PLZT, NUMELE(SD_GAB_DXZP_SBXX_PLZT), &gab_dxzp_sbxx_plzt, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        #if 0
        memset(sJybm, 0x00, sizeof(sJybm));
        if (strcmp(gab_dxzp_sbxx_plzt.sbjydm, "945111") == 0 )
        {/*�����ٱ�*/
            strcpy(sJybm, "100401");
        }else if (strcmp(gab_dxzp_sbxx_plzt.sbjydm, "945112") == 0 )
        {/*�쳣����*/
            strcpy(sJybm, "100402");
        }else if (strcmp(gab_dxzp_sbxx_plzt.sbjydm, "945113") == 0 )
        {/*�永�˻�*/
            strcpy(sJybm, "100403");
        }else if (strcmp(gab_dxzp_sbxx_plzt.sbjydm, "945114") == 0 )
        {/*�쳣�¼�*/
            strcpy(sJybm, "100404");
        }
        #endif
        /* ����������Ϣ��ֵ */
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_SBPCXH, itoa(gab_dxzp_sbxx_plzt.sbpcxh));/*�ϱ��������*/
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_SBZT, gab_dxzp_sbxx_plzt.sbzt);/*�ϱ�״̬*/
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_SBJYDM, gab_dxzp_sbxx_plzt.sbjydm);/*�ϱ����״���*/
        LOG(LM_STD,Fmtmsg("�������������ϱ�������subflow_gabdxzp_945122����,sbpch[%s],sbpcxh[%d],sbzt[%s],sbjydm[%s]",
            gab_dxzp_sbxx_plzt.sbpch, gab_dxzp_sbxx_plzt.sbpcxh, gab_dxzp_sbxx_plzt.sbzt,
            gab_dxzp_sbxx_plzt.sbjydm),"INFO");
        /* ���ô�����ҵ����� */
        if(fpub_CallFlow(lXmlhandle,"subflow_gabdxzp_945122")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("���������ϱ�������subflow_gabdxzp_945122[%s-%d]ʧ��",
                gab_dxzp_sbxx_plzt.sbpch, gab_dxzp_sbxx_plzt.sbpcxh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("ִ�������ϱ�������ʧ��"));
            return COMPRET_FAIL ;
        }
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("����թƭ������Ϣ�ϱ�ִ�н���,������[%d]��ҵ��", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"����թƭ������Ϣ�ϱ�ִ�н���");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}


/************************************************************************
��̬�����������
�����������:GAB_DXZP_945125
�������: GAB_DXZP_945125
�������: ˾����س�ʱ��֤
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    
�����  
0   �ɹ�
-1  ʧ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_945125(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sHxFcBz[1+1];/*���ķ��ر�־0-������,1-����*/
    char sSbJydm[6+1];
    char sJybm[6+1];
    char errmsg[256];
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    CURSOR cur;
    SFCK_TIMEOUT sfck_timeout;
    
    fpub_InitSoComp(lXmlhandle);
    
    memset(sHxFcBz, 0x00, sizeof(sHxFcBz));
    COMP_SOFTGETXML(XMLNM_SFXT_HXFCBZ, sHxFcBz)
    
    LOG(LM_STD,Fmtmsg("˾����س�ʱ��ִ֤�п�ʼ[%s]",sHxFcBz),fpub_GetCompname(lXmlhandle));
    if (sHxFcBz[0] != '0')
    {/*0-����,���Զ��Ϻ��Ĳ�֤״̬*/
        LOG(LM_STD,Fmtmsg("˾�����,���ķ���,���ط����״���,����"),"INFO");
        fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"˾�����,���ķ���,���ط����״���,����");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }
    
    /* ��ѯ��Ҫ��������� */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"SELECT * FROM sfck_timeout WHERE 1=1");
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
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
        memset(&sfck_timeout, 0x00, sizeof(sfck_timeout));
        iRet = DBFetch(cur, SD_SFCK_TIMEOUT, NUMELE(SD_SFCK_TIMEOUT), &sfck_timeout, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }

        /* ����������Ϣ��ֵ */
        COMP_SOFTSETXML("/sfck/tmout/xtbh", sfck_timeout.xtbh);/*ϵͳ���*/
        COMP_SOFTSETXML("/sfck/tmout/ywbm", sfck_timeout.ywbm);/*ҵ�����*/
        COMP_SOFTSETXML("/sfck/tmout/ywsqbh", sfck_timeout.ywsqbh);/*ҵ��������*/
        COMP_SOFTSETXML("/sfck/tmout/ywrq", sfck_timeout.ywrq);/*ҵ������*/
        COMP_SOFTSETXML("/sfck/tmout/ywlsh", sfck_timeout.ywlsh);/*ҵ����ˮ��*/
        COMP_SOFTSETXML("/sfck/tmout/qqdzt", sfck_timeout.qqdzt);/*����״̬*/
        LOG(LM_STD,Fmtmsg("�������ó�ʱ��֤������subflow_gabdxzp_945125����,xtbh[%s],ywsqbh[%s],ywrq[%s],ywlsh[%s]",
            sfck_timeout.xtbh, sfck_timeout.ywsqbh, sfck_timeout.ywrq, sfck_timeout.ywlsh),"INFO");
        /* ���ô�����ҵ����� */
        if(fpub_CallFlow(lXmlhandle,"subflow_gabdxzp_945125")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("���������ϱ�������subflow_gabdxzp_945125[%s]ʧ��",
                sfck_timeout.ywsqbh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("ִ�г�ʱ��֤������ʧ��"));
            return COMPRET_FAIL ;
        }
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("˾����س�ʱ��ִ֤�н���,������[%d]��ҵ��", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"˾����س�ʱ��ִ֤�н���");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}


/************************************************************************
��̬�����������
�����������:GAB_DXZP_HHMD_INS
�������: GAB_DXZP_HHMD_INS
�������: �Ǽǹ���������թƭ�������
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    
�����  
0   �ɹ�
-1  ʧ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/

IRESULT GAB_DXZP_HHMD_INS(HXMLTREE lXmlhandle)
{
  
    char sbuf[1024+1];
    int  iParas;
    int  iRet = -1;
    int  iRet1= -1;
    char szFilePath[255];
    char sFlag[20];
    char sHhLevel[40];
    FILE *fp=NULL;
    GAB_DXZP_HHMD st_gab_dxzp_hhmd;
    
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHK(2)
    memset(szFilePath, 0x00, sizeof(szFilePath));
    COMP_GETPARSEPARAS(1, szFilePath, "�Һ������ļ�·��");
    COMP_GETPARSEPARAS(2, sHhLevel, "��������");
    trim(szFilePath);
    trim(sHhLevel);
	  LOG(LM_STD,Fmtmsg("  -->�Һ������ļ�·��[%s]",szFilePath),"INFO")
	  fp = fopen( szFilePath, "r" );
	  if ( fp == NULL )
	     {
	      	LOG(LM_STD,Fmtmsg("���ļ�ʧ��,file=[%s]",szFilePath),fpub_GetCompname(lXmlhandle));
	      	fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("���ļ�ʧ��"));
	      	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	      	return COMPRET_FAIL;
	     }
	     
	  DCIBegin();
    memset(sbuf, 0x00, sizeof(sbuf));
	  while (fgets(sbuf, 1024, fp) != NULL)
	   {
		     trim(sbuf);
		     if (0 == strlen(sbuf))
			   continue;
			   
			   memset(&st_gab_dxzp_hhmd,0x00,sizeof(st_gab_dxzp_hhmd));
			   
			   /*������ֵ*/
			   GetItemValueT(sbuf, "$" ,st_gab_dxzp_hhmd.mdjz, 1); 
		     trim(st_gab_dxzp_hhmd.mdjz); 
			   /*������ʶ*/
		     memset(sFlag,0x00,sizeof(sFlag));
		     GetItemValueT(sbuf, "$" ,sFlag, 2); 
		     trim(sFlag); 
		     
         if(0 == strcmp(sFlag,"+"))
		     	{
		     		 LOG(LM_STD,Fmtmsg("��ʼ��ѯ-->�Һ�������,mdjz[%s]",st_gab_dxzp_hhmd.mdjz),fpub_GetCompname(lXmlhandle));   
		         iRet = fdbop_qry_gab_dxzp_hhmd(lXmlhandle,&st_gab_dxzp_hhmd);

		         if( iRet < 0 )
               {
               	   fclose(fp);
                   fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
                   LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("��ѯ����թƭ�ڻ�������ʧ��,mdjz[%s]", 
                   st_gab_dxzp_hhmd.mdjz),fpub_GetCompname(lXmlhandle));
               }
             else if ( iRet == 0 )
               {
               	  memset(&st_gab_dxzp_hhmd,0x00,sizeof(st_gab_dxzp_hhmd));
		              ffunc_gabdxzp_getXml_HHMD(lXmlhandle,&st_gab_dxzp_hhmd,sbuf);
		              LOG(LM_STD,Fmtmsg("���װ�غڻ�������Ϣ"),fpub_GetCompname(lXmlhandle));
		              strncpy(st_gab_dxzp_hhmd.mdjb,sHhLevel,1);
		              
                  iRet1 = fdbop_ins_gab_dxzp_hhmd(lXmlhandle,&st_gab_dxzp_hhmd);
                  if( iRet1 <0 && iRet1 != GAB_DXZP_FUNCRET_KEYERR ) 
                    { 
                        DCICommit();
                        fclose(fp);
                        LOGRET(iRet1, LM_STD, Fmtmsg(MSG_GAB_DXZP_CALLFUNC_FAIL, "�������թƭ�ڻ�������ʧ��"), fpub_GetCompname(lXmlhandle)); 
                     }
                  LOG(LM_STD, Fmtmsg("�ǼǺڻ�������->��ɵǼǺڻ�������"), fpub_GetCompname(lXmlhandle));
                  
               }
             else
		          {
		          	  memset(&st_gab_dxzp_hhmd,0x00,sizeof(st_gab_dxzp_hhmd));
		              ffunc_gabdxzp_getXml_HHMD(lXmlhandle,&st_gab_dxzp_hhmd,sbuf);
		              LOG(LM_STD,Fmtmsg("���װ�غڻ�������Ϣ"),fpub_GetCompname(lXmlhandle));
		              strncpy(st_gab_dxzp_hhmd.mdjb,sHhLevel,1);
		              
		         	    iRet1 =fdbop_upd_gab_dxzp_hhmd(lXmlhandle,&st_gab_dxzp_hhmd);
		         	    if(iRet1<0)
		         	    	{
		         	    	  DCICommit();
		         	    		fclose(fp);
                      LOGRET(iRet1, LM_STD, Fmtmsg(MSG_GAB_DXZP_CALLFUNC_FAIL, "���µ���թƭ�ڻ�������ʧ��"), fpub_GetCompname(lXmlhandle)); 
		         	    	}
		         	}
		    }
		   if(0 == strcmp(sFlag,"-"))
		    	{
		    		iRet1 =fdbop_del_gab_dxzp_hhmd(lXmlhandle,&st_gab_dxzp_hhmd);
		    		if(iRet1<0)
		         	{       
		         		DCICommit();
		         		fclose(fp);
                LOGRET(iRet1, LM_STD, Fmtmsg(MSG_GAB_DXZP_CALLFUNC_FAIL, "ɾ������թƭ�ڻ�������ʧ��"), fpub_GetCompname(lXmlhandle)); 
		         	}
		    	}
     }
   DCICommit();
   fclose(fp);
   
   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   return 0;
}
/************************************************************************
��̬�����������
�����������:GAB_DXZP_XDXX_UPDATE
�������: GAB_DXZP_XDXX_UPDATE
�������: ���¹���������թƭ�´���Ϣ
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    
�����  
0   �ɹ�
-1  ʧ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/

IRESULT GAB_DXZP_XDXX_UPDATE(HXMLTREE lXmlhandle)
{
  
    char sbuf[1024+1];
    int  iParas;
    int iRet=-1;
    GAB_DXZP_XDXX st_gab_dxzp_xdxx;
    memset(&st_gab_dxzp_xdxx,0x00,sizeof(st_gab_dxzp_xdxx));
    
    fpub_InitSoComp(lXmlhandle);
    
		GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/jbjg",st_gab_dxzp_xdxx.jbjg,"�������");
    GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/jbgy",st_gab_dxzp_xdxx.jbgy,"�����Ա");
    GAB_DXZP_GETXMLSTR_NOTNULL("/gabdxzp/ywsqbh",st_gab_dxzp_xdxx.ywsqbh,"ҵ��������");
    trim(st_gab_dxzp_xdxx.jbjg);
    trim(st_gab_dxzp_xdxx.jbgy);
    trim(st_gab_dxzp_xdxx.ywsqbh);

    if( 0 == strcmp(st_gab_dxzp_xdxx.jbjg," ") || '\0' == st_gab_dxzp_xdxx.jbjg[0])
    	{
    		GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_XNJG,st_gab_dxzp_xdxx.jbjg,"�������");
    	}
    if( 0 == strcmp(st_gab_dxzp_xdxx.jbgy," ") || '\0' == st_gab_dxzp_xdxx.jbgy[0])
    	{
    		GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_XNGY,st_gab_dxzp_xdxx.jbgy,"�����Ա");
    	}
		 iRet =fdbop_upd_gab_dxzp_xdxx_qdxx(lXmlhandle,&st_gab_dxzp_xdxx);
		 GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "������Ϣ�´��");
		 DCICommit();      
   xml_SetElement(lXmlhandle,"/gabdxzp/jbjg" ,st_gab_dxzp_xdxx.jbjg);
   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   return 0;
}



/************************************************************************
��̬�����������
�����������:GAB_DXZP_SET_ATTACHMENT_INFO
�������: GAB_DXZP_SET_ATTACHMENT_INFO
�������: ����������թƭ����������Ϣ
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    
�����  
0   �ɹ�
-1  ʧ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/

IRESULT GAB_DXZP_SET_ATTACHMENT_INFO(HXMLTREE lXmlhandle)
{
    char sbuf[256];
    int  iParas;
    int  iRet=-1;
    int  ilen=0;
    char YorNbase[2];
    char *psFileContents=NULL;
    char sSql[512];
    char sSbPch[36+1];
    char sbase64en[MAXSIZE];
    char *psBase64=NULL;
    int  iBase64Malloc=0;
    char sCommBuf[32768];/*32k*/
    int  iCommBuf=0;
    char *psBodyEnd=NULL;
    int  iBodyLen=0;
    char sYxxx[3145728];/*3M*/
    char sYwSqBh[36+1];
    char sReplFilename[200+1];
    int i=1;
    char psFileName[200];
    char sErrmsg[1000];
    CURSOR cur;
    GAB_DXZP_SMJFJ st_gab_dxzp_smjfj;/*����թƭɨ���������*/
    
    
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHK(1)
    memset(YorNbase, 0x00, sizeof(YorNbase));
    COMP_GETPARSEPARAS(1, YorNbase, "�Ƿ����base64����");
    trim(YorNbase);
    
    memset(sSbPch, 0x00, sizeof(sSbPch));
    GAB_DXZP_GETXMLSTR_NOTNULL("/gabdxzp/sbpch",sSbPch,"�ϱ����κ�");
    /*alter by liukq 20160504 BEGIN*/
    memset(sYwSqBh,0x00,sizeof(sYwSqBh));
    GAB_DXZP_GETXMLSTR_NOTNULL("/gabdxzp_ywbm/ApplicationID",sYwSqBh,"ҵ��������");
    /*alter by liukq 20160504 END*/
    memset(sCommBuf, 0x00, sizeof(sCommBuf));
	if(0 > (iRet = xml_RelGetBinElement(lXmlhandle, "/commbuf", sCommBuf, sizeof(sCommBuf)-1)))
	{
		LOG(LM_STD, Fmtmsg("ȡͨѶ������iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "��ǰ�û�ͨѶʧ��,��ȡͨѶ������");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	iCommBuf=strlen(sCommBuf);
	/*��λ�������ʶ��*/
	psBodyEnd=strstr(sCommBuf,"</Body>");
	if (psBodyEnd==NULL)
	{
		LOG(LM_STD, Fmtmsg("��λ�����������ʧ��"), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "δ�ҵ�������,�鱨�쳣");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
    memset(sSql, 0x00, sizeof(sSql));
   
    snprintf(sSql,sizeof(sSql),"SELECT * FROM gab_dxzp_smjfj WHERE ywsqbh='%s'", sSbPch);

    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
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
    memset(sYxxx, 0x00, sizeof(sYxxx));
	  iBodyLen = iCommBuf - strlen(psBodyEnd);
    memcpy(sYxxx, sCommBuf, iBodyLen);
    psBodyEnd=NULL;
    
     for ( i=1; ; i++)
    {
        memset(&st_gab_dxzp_smjfj, 0x00, sizeof(st_gab_dxzp_smjfj));
        memset(sbase64en,0x00,sizeof(sbase64en));
        memset(psFileName,0x00,sizeof(psFileName));
        /*alter  by liukq 20160504 BEGIN*/
        memset(sReplFilename,0x00,sizeof(sReplFilename));
        /*alter  by liukq 20160504 END*/
        iRet = DBFetch(cur, SD_GAB_DXZP_SMJFJ, NUMELE(SD_GAB_DXZP_SMJFJ), &st_gab_dxzp_smjfj, sErrmsg );
        if ( iRet <= 0 )
        {
        	  if(i!=1)
        	  {
        	  	strcat(sYxxx, "</Attachments>");
        	  }
            break;
        }
        if(1==i)
        	{
        	 strcat(sYxxx, "<Attachments>");
        	}
        ffunc_file_getFileName(lXmlhandle,st_gab_dxzp_smjfj.wjm,psFileName);
        if('\0' == psFileName[0])
        {
        	LOG(LM_STD,Fmtmsg("---->��ȡ�ļ���ʧ��"),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_GAB_DXZP_FILEOP,"��ȡ�ļ���");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
		    strcat(sYxxx, "<Attachment><Filename>");
		    memset(sbuf,0x00,sizeof(sbuf));
		    sprintf(sbuf,"/Attachments/Attachment|%d/Filename",i);
		    LOG(LM_STD,Fmtmsg("i=[%d],Filename=[%s],ilen=[%d]",i,psFileName,ilen),"DEBUG");
		    /*alter by liukq 20160504 BEGIN
		    strcat(sYxxx, psFileName);
		    END*/
		    /*alter by liukq 20160504 BEGIN*/
		    strcpy(sReplFilename,psFileName);
		    memcpy(sReplFilename+3,sYwSqBh,36);
		    strcat(sYxxx, sReplFilename);
		    /*alter by liukq 20160504 END*/
		    strcat(sYxxx, "</Filename><Content>");
		    COMP_SOFTSETXML(sbuf,psFileName);
        ilen=0;
        psFileContents=ffunc_file_getJPEGContents(lXmlhandle,st_gab_dxzp_smjfj.wjm, &ilen);
        if(NULL==psFileContents)
        {
        	free(psFileContents);
        	psFileContents=NULL;
        	LOG(LM_STD,Fmtmsg("---->��ȡ�ļ�����ʧ��"),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_GAB_DXZP_FILEOP,"��ȡ�ļ�����ʧ��");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
		   LOG(LM_STD,Fmtmsg("i=[%d],psFileContents=[%s],ilen=[%d]",i,psFileName,ilen),"DEBUG");
        if( 0 == strcmp(YorNbase,"0"))
        {
        	strncpy(sbase64en,psFileContents,MAXSIZE);
        	psBase64=psFileContents;
        	iBase64Malloc=0;
        }else
         {
            psBase64=fpub_base64_encode(psFileContents,&ilen,MAXSIZE);
            if(NULL == psBase64)
     	    {
     	       free(psFileContents);
        		 psFileContents=NULL;
			       LOG(LM_STD, Fmtmsg(" fpub_base64_encode-->���ܴ���ʧ�� "), __func__);
			       fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			       return COMPRET_FAIL;		
		     }
		     iBase64Malloc=1;  
		  }
		    

		    memset(sbuf,0x00,sizeof(sbuf));
		    sprintf(sbuf,"/Attachments/Attachment|%d/Content",i);
		    COMP_SOFTSETXML(sbuf,sbase64en);
		    LOG(LM_STD,Fmtmsg("i=[%d],psBase64=[%s],ilen=[%d]",i,psBase64,ilen),"DEBUG");
		    strcat(sYxxx, psBase64);
		    strcat(sYxxx, "</Content></Attachment>");
		    if (iBase64Malloc==1) free(psBase64);psBase64=NULL;
		    free(psFileContents);psFileContents=NULL;
        
    }
    DCIFreeCursor(cur);
    strcat(sYxxx, "</Body></Request>");
    iCommBuf=strlen(sYxxx);
    if(0 > (iRet = xml_RelSetBinElement(lXmlhandle, "/commbuf", sYxxx, iCommBuf)))
	{
		LOG(LM_STD, Fmtmsg("дͨѶ������iRet=[%d]", iRet), "DEBUG");
		/*alter by liukq 20160503 BEGIN
		fpub_SetMsg(lXmlhandle, 99999, "��������ʧ��,дͨѶ������");
		END*/
		/*alter by liukq 20160503 BEGIN*/
		fpub_SetMsg(lXmlhandle, 98601, "��������ʧ��,дͨѶ������");
		/*alter by liukq 20160503 END*/
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return 0;
}
/************************************************************************
��̬�����������
�����������:GAB_DXZP_SMJFJ_INS
�������:GAB_DXZP_SMJFJ_INS
�������:��¼����թƭɨ���������(���齨Ϊ�����ٱ�ר��)
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/

IRESULT GAB_DXZP_SMJFJ_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    int i=1,j=1, iCnts=0;/*��������*/
    char sSbpch[36+1];
    GAB_DXZP_SMJFJ st_gab_dxzp_smjfj;/*����թƭɨ���������*/

    fpub_InitSoComp(lXmlhandle);
    memset(sSbpch,0x00,sizeof(sSbpch));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,sSbpch,"�ϱ����κ�");
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_APPLICATIONID,sSbpch);

    /*��ȡ��������*/
    iCnts=xml_ElementCount(lXmlhandle,"/gabdxzp/yxxx");
    if(iCnts<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/gabdxzp/yxxx�ڵ㲻����"),fpub_GetCompname(lXmlhandle));
   			 if(0==iCnts)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return iCnts;
   		}
    LOG(LM_STD, Fmtmsg("�Ǽǵ���թƭɨ���������->��ʼ����[%d]", iCnts), fpub_GetCompname(lXmlhandle));
    
    /*2.װ�ؼ��Ǽǵ���թƭɨ���������*/
    DCIBegin();
    for ( i=1,j=1; i<=iCnts; i++,j++)
    {
        memset(&st_gab_dxzp_smjfj, 0x00, sizeof(st_gab_dxzp_smjfj));
        iRet = ffunc_gabdxzp_getXml_SMJFJ_Req(lXmlhandle, &st_gab_dxzp_smjfj);
        GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "װ�ص���թƭɨ���������");
        st_gab_dxzp_smjfj.xh=i;
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/yxxx|%d/wjm",i);
        GAB_DXZP_GETXMLSTR_NOTNULL(sBuf,st_gab_dxzp_smjfj.wjm,"�ļ���");
        LOG(LM_STD, Fmtmsg("�Ǽǵ���թƭɨ���������->��ɵ���թƭɨ���������[%d]", i), fpub_GetCompname(lXmlhandle));
        
        /*�Ǽǵ���թƭɨ���������->���װ�ص���թƭɨ���������*/
        iRet = fdbop_ins_gab_dxzp_smjfj(lXmlhandle, &st_gab_dxzp_smjfj);
        GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "�Ǽǵ���թƭɨ���������->���װ�ص���թƭɨ���������");
        LOG(LM_STD, Fmtmsg("�Ǽǵ���թƭɨ���������->���װ�ص���թƭɨ���������[%d]", i), fpub_GetCompname(lXmlhandle));
        if ( j > GAB_DXZP_COMMIT_CNT )
        {/*�ﵽ�ύ��¼�����ύ����*/
            DCICommit();
            DCIBegin();
            j = 1;
        }
    }
    DCICommit();
    
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("�Ǽǵ���թƭɨ���������->����ɹ�[%d]", i), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}







/************************************************************************
��̬�����������
�����������:GAB_DXZP_QUERY_QHCX_ZHJBXX_ZZHXX
�������:GAB_DXZP_QUERY_QHCX_ZHJBXX_ZZHXX
�������:ȡȫ����ѯ�˻�������Ϣ���˻���Ϣ
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_QUERY_QHCX_ZHJBXX_ZZHXX(HXMLTREE lXmlhandle)
{
    int  iParas;
    int iRet=-1;
    char sErrmsg[1000];
    char sSql[512];
    char sYwsqbh[100];
    char sBuf[200];
    char sSql_zzhxx[512];
    int i=0;
    
    CURSOR query_qhcx_zhjbxxcur;
    CURSOR query_qhcx_zhxx_cur;
    
    GAB_DXZP_JYMX_ZHJBXX st_gab_dxzp_jymx_zhjbxx;/*ȫ����ѯ_�˻�������Ϣ��*/
    GAB_DXZP_QHCX_ZZHXX st_gab_dxzp_qhcx_zzhxx;/*ȫ����ѯ_���˺���Ϣ��*/
   
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHKMIN(1);
    memset(sYwsqbh,0x00,sizeof(sYwsqbh));
    COMP_GETPARSEPARAS(1, sYwsqbh, "ҵ��������");
     
    
    
      
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"SELECT * \
     FROM gab_dxzp_jymx_zhjbxx  WHERE  ywsqbh='%s' ORDER BY rwxh asc",sYwsqbh);
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((query_qhcx_zhjbxxcur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(query_qhcx_zhjbxxcur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(query_qhcx_zhjbxxcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    while(1)
    {
        memset(&st_gab_dxzp_jymx_zhjbxx, 0x00, sizeof(st_gab_dxzp_jymx_zhjbxx));
        iRet = DBFetch(query_qhcx_zhjbxxcur, SD_GAB_DXZP_JYMX_ZHJBXX, NUMELE(SD_GAB_DXZP_JYMX_ZHJBXX), &st_gab_dxzp_jymx_zhjbxx, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zhm",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.zhm);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/kzh",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.kzh);
       
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/khwd",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.khwd);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/khwddm",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.khwddm);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/khrq",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.khrq);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/xhrq",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.xhrq);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/xhwd",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.xhwd);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/beiz",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.beiz);
        
        LOG(LM_STD,Fmtmsg("rwxh=[%d]",st_gab_dxzp_jymx_zhjbxx.rwxh),fpub_GetCompname(lXmlhandle));
          
        memset(sSql_zzhxx, 0x00, sizeof(sSql_zzhxx));
        snprintf(sSql_zzhxx,sizeof(sSql_zzhxx),"SELECT *\
        FROM gab_dxzp_qhcx_zzhxx  WHERE  ywsqbh='%s' and rwxh=%d  ORDER BY zzhxh asc",sYwsqbh,st_gab_dxzp_jymx_zhjbxx.rwxh);
        LOG(LM_STD,Fmtmsg("sSql_zzhxx[%s]", sSql_zzhxx),fpub_GetCompname(lXmlhandle));
        
        if ((query_qhcx_zhxx_cur = DCIDeclareCursor(sSql_zzhxx, DCI_STMT_LOCATOR)) == -1)
         {
           LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
        if (DCIExecute(query_qhcx_zhxx_cur) == -1)
         {
           LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
           DCIFreeCursor(query_qhcx_zhxx_cur);
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
         i=0;
         while(1)
         {
         	   i++;
         	   memset(&st_gab_dxzp_qhcx_zzhxx, 0x00, sizeof(st_gab_dxzp_qhcx_zzhxx));
             iRet = DBFetch(query_qhcx_zhxx_cur, SD_GAB_DXZP_QHCX_ZZHXX, NUMELE(SD_GAB_DXZP_QHCX_ZZHXX), &st_gab_dxzp_qhcx_zzhxx, sErrmsg );
             if ( iRet <= 0 )
             {
                 if(1 == i)  
                 	{
                 		 memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zzhxh",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                 		 memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zh",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zzhlb",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zhzt",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/bz",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/chbz",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zhye",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/kyye",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zhjysj",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                 		
                 	}       	
                 break;
             }
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zzhxh",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             
         	   memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zh",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zzhlb",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zzhlb);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zhzt",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zhzt);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/bz",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.bz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/chbz",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.chbz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zhye",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zhye);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/kyye",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.kyye);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zhjysj",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zhjysj);
            
         }
         DCIFreeCursor(query_qhcx_zhxx_cur);
         if( iRet < 0 )
         {
             LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
             fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return COMPRET_FAIL;
         }
       
    }
    DCIFreeCursor(query_qhcx_zhjbxxcur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"����������թƭ������ϸ��ѯ����");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
��̬�����������
�����������:GAB_DXZP_HQTGJGXX
�������: GAB_DXZP_HQTGJGXX
�������: ��ȡ�йܻ�����Ϣ
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��    
�����  
0   �ɹ�
-1  ʧ��
ʹ������:
�� �� Ա: 
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_HQTGJGXX(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sErrmsg[256];
    int  iAutoProcs=10;/*�Զ����������*/
    int i=1;
    int iRet=-1;
    CURSOR cur;
    GAB_DXZP_HMHH gab_dxzp_hmhh;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("��ȡ�йܻ�����Ϣ�Զ�����ִ�п�ʼ"),fpub_GetCompname(lXmlhandle));
    
    /* ��ѯ��Ҫ��������� */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"select * from gab_dxzp_hmhh where hb='t' ");
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
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
        memset(&gab_dxzp_hmhh, 0x00, sizeof(gab_dxzp_hmhh));
        iRet = DBFetch(cur, SD_GAB_DXZP_HMHH, NUMELE(SD_GAB_DXZP_HMHH), &gab_dxzp_hmhh, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        
        /* ����������Ϣ��ֵ */
        COMP_SOFTSETXML("/gabdxzp/jgid", gab_dxzp_hmhh.hh);/*�й��к�*/
        LOG(LM_STD,Fmtmsg("�������û�ȡ�йܻ�������subflow_gabdxzp_945128����,hh[%s]",gab_dxzp_hmhh.hh),"INFO");
        /* ���ô�����ҵ����� */
        if(fpub_CallFlow(lXmlhandle,"subflow_gabdxzp_945128")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("���ô�����ҵ������subflow_gabdxzp_945128[%s]ʧ��",
                gab_dxzp_hmhh.hh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("ִ�л�ȡ�йܻ�����Ϣ����ʧ��"));
            return COMPRET_FAIL ;
        }
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_STD,Fmtmsg("��ȡ�йܻ�����Ϣ�Զ�����ִ�н���,������[%d]��ҵ��", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"��ȡ�йܻ�����Ϣ�Զ�����ִ�н���");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}









/************************************************************************
��̬�����������
�����������:GAB_DXZP_QUERY_SAZH_GLZHXX_JYMX
�������:GAB_DXZP_QUERY_SAZH_GLZHXX_JYMX
�������:ȡ�˻��永�����˻�-������Ϣ
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2016-1-25 16:46:21(gen)
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_QUERY_SAZH_GLZHXX_JYMX(HXMLTREE lXmlhandle)
{
    int  iParas;
    int iRet=-1;
    char sErrmsg[1000];
    char sSql[512];
    char sSbpch[40];
    char sSbpcxh[20];
    int pcxh=0;
    char sBuf[200];
    char sSql_glzhxx_jymx[512];
    int i=0,iZHXH=0;
    char sZHXH[20];
    
    CURSOR query_glzhxxcur;
    CURSOR query_glzhxx_jymxcur;
    
    GAB_DXZP_SBXX_GLZHXX st_gab_dxzp_sbxx_glzhxx;/*�ϱ���Ϣ_�����˻���Ϣ��*/
    GAB_DXZP_SBXX_JYMX st_gab_dxzp_sbxx_jymx;/*�ϱ���Ϣ_������ϸ��*/
   
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHKMIN(2);
    memset(sSbpch,0x00,sizeof(sSbpch));
    COMP_GETPARSEPARAS(1, sSbpch, "�ϱ����κ�");
    memset(sSbpcxh,0x00,sizeof(sSbpcxh));
    COMP_GETPARSEPARAS(2, sSbpcxh, "�ϱ��������"); 
    trim(sSbpch);
    trim(sSbpcxh);
    pcxh=atoi(sSbpcxh);  
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"SELECT * \
     FROM gab_dxzp_sbxx_glzhxx  WHERE  sbpch='%s' and sbpcxh=%d ORDER BY zhxh asc",sSbpch,pcxh);
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((query_glzhxxcur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(query_glzhxxcur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(query_glzhxxcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    while(1)
    {
        memset(&st_gab_dxzp_sbxx_glzhxx, 0x00, sizeof(st_gab_dxzp_sbxx_glzhxx));
        iRet = DBFetch(query_glzhxxcur, SD_GAB_DXZP_SBXX_GLZHXX, NUMELE(SD_GAB_DXZP_SBXX_GLZHXX), &st_gab_dxzp_sbxx_glzhxx, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        iZHXH++;
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/zh",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_glzhxx.zh);
        
        memset(sZHXH,0x00,sizeof(sZHXH));
        memset(sBuf,0x00,sizeof(sBuf));
        strcpy(sZHXH,itoa(iZHXH));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/zzhxh",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,sZHXH);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/zhlx",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_glzhxx.zhlx);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/zhzt",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_glzhxx.zhzt);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/bz",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_glzhxx.bz);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/chbz",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_glzhxx.chbz);
        
        LOG(LM_STD,Fmtmsg("rwxh=[%d]",iZHXH),fpub_GetCompname(lXmlhandle));
          
        memset(sSql_glzhxx_jymx, 0x00, sizeof(sSql_glzhxx_jymx));
        snprintf(sSql_glzhxx_jymx,sizeof(sSql_glzhxx_jymx),"SELECT *\
        FROM gab_dxzp_sbxx_jymx  WHERE  sbpch='%s' and sbpcxh=%d and zhxh='%s'  ORDER BY jyxh asc",sSbpch,pcxh,st_gab_dxzp_sbxx_glzhxx.zhxh);
        LOG(LM_STD,Fmtmsg("sSql_glzhxx_jymx[%s]", sSql_glzhxx_jymx),fpub_GetCompname(lXmlhandle));
        
        if ((query_glzhxx_jymxcur = DCIDeclareCursor(sSql_glzhxx_jymx, DCI_STMT_LOCATOR)) == -1)
         {
           LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
        if (DCIExecute(query_glzhxx_jymxcur) == -1)
         {
           LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR");
           DCIFreeCursor(query_glzhxx_jymxcur);
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
         i=0;
         while(1)
         {
         	   i++;
         	   memset(&st_gab_dxzp_sbxx_jymx, 0x00, sizeof(st_gab_dxzp_sbxx_jymx));
             iRet = DBFetch(query_glzhxx_jymxcur, SD_GAB_DXZP_SBXX_JYMX, NUMELE(SD_GAB_DXZP_SBXX_JYMX), &st_gab_dxzp_sbxx_jymx, sErrmsg );
             if ( iRet <= 0 )
             {
                 if(1 == i)  
                 	{
                 		 memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/jylsh",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/jysj",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/jylx",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/bz",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/jyje",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/fkkhhhh",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/fkkhhmc",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/fkfxm",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/fkfzh",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/skkhhhh",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/skkhhmc",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/skfxm",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/skfzh",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/ip",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/mac",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/sbid",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/jydd",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/beiz",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                 	}       	
                 break;
             }
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/jylsh",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.jylsh);
             
         	   memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/jysj",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.jysj);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/jylx",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.jylx);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/bz",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.bz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/jyje",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.jyje);
            
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/fkkhhhh",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.zczhyhjg);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/fkkhhmc",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.zczhyhmc);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/fkfxm",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.zczhm);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/fkfzh",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.zczh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/skkhhhh",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.ddzhyhjg);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/skkhhmc",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.ddzhyhmc);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/skfxm",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.ddzhm);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/skfzh",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.ddzh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/ip",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.ip);
            
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/mac",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.mac);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/sbid",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.sbid);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/jydd",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.jydd);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/beiz",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.beiz);
             
         }
         DCIFreeCursor(query_glzhxx_jymxcur);
         if( iRet < 0 )
         {
             LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
             fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return COMPRET_FAIL;
         }
       
    }
    DCIFreeCursor(query_glzhxxcur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"����������թƭ������ϸ��ѯ����");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}




/************************************************************************
��̬�����������
�����������:GAB_DXZP_2LOOP_CHECK_SAZH
�������: GAB_DXZP_2LOOP_CHECK_SAZH
�������: ����������թƭ2��ѭ�����ļ������˻�������Ϣ
�������:
��� ��������  ��������             ��Դ���           ȱʡֵ     �ɿ�  ����˵��

�����
0   �ɹ�
-1  ʧ��
ʹ������:
�� �� Ա:
��������:
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT GAB_DXZP_2LOOP_CHECK_SAZH(HXMLTREE lXmlhandle)
{
    int  iParas;
    int  count=-1;/*ѭ������*/
    char s1Looppath[200];/*һ��ѭ��·��*/
    char s2Looppath[200];/*����ѭ��·��*/
    char sBuf[254];
    char sCatXml[254];
    int  iRet=-1;
    int i=1;

    fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
    LOG(LM_STD, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif

    memset(s1Looppath,0x00,sizeof(s1Looppath));
    memset(s2Looppath,0x00,sizeof(s2Looppath));
    memset(sBuf,0x00,sizeof(sBuf));

    COMP_PARACOUNTCHKMIN(2)
    COMP_GETPARSEPARAS(1,s1Looppath,"һ��ѭ��·��")
    COMP_GETPARSEPARAS(2,s2Looppath,"����ѭ��·��")
    trim(s1Looppath);
    trim(s2Looppath);
    
    count=xml_ElementCount(lXmlhandle,"/gabdxzp/glzhxx");
    if(count<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/gabdxzp/glzhxx�ڵ㲻����"),fpub_GetCompname(lXmlhandle));
   			  if(0==count)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return count;
   		}
   		
    LOG(LM_STD,Fmtmsg("s1Looppath[%s],s2Looppath[%s]",s1Looppath,s2Looppath),fpub_GetCompname(lXmlhandle));

    for(i=1;i<=count;i++)
      {
         memset(sBuf,0x00,sizeof(sBuf));
         sprintf(sBuf,"%s|%d/%s",s1Looppath,i,s2Looppath);
     	   iRet = xml_ElementExist(lXmlhandle,sBuf);
     	   if(0 == iRet)
     	   	{
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/jylsh",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/jysj",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/jylx",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/bz",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/jyje",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/fkkhhhh",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/fkkhhmc",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/fkfxm",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/fkfzh",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/skkhhhh",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/skkhhmc",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/skfxm",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/skfzh",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");
     	   		

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/ip",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/mac",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/sbid",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/jydd",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/beiz",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");
     	   		
     	   	}
     	   if(0 > iRet)
     	   	{
     	   		GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, " xml_ElementExist �жϽڵ����ʧ��");
     	   	}
      }


#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

    return COMPSTATUS_SUCC;
}

/************************************************************************
 ��̬�����������
 �����������:GAB_DXZP_UTF8TOGBK
 �������:ת��UTF-8
 �������:ת��UTF-8
 �������:
 ��� ��������  ��������      ��Դ���         ȱʡֵ            �ɿ�   ����˵��

 ������״̬:
 ���״̬��         ���˵��
 ȱʡ

 ��Ҫ�������:
 ����                       ����

 ��������:

 �� Ŀ ��:
 �� �� Ա:
 ��������:
 �޸�����:
 ����ʹ��ʾ��:
 ************************************************************************/
IRESULT GAB_DXZP_UTF8TOGBK(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    int iUTF8Len=0;
    int iGBKLen=0;
    char *pUTF8 = NULL;
    char *pGBK = NULL;

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("ת��UTF-8->��ʼ����"), fpub_GetCompname(lXmlhandle));

    /*��ȡ��ʱ��Ϣ*/
    iUTF8Len = xml_GetBinElementLen(lXmlhandle, "/commbuf");
    if (iUTF8Len <= 0 )
    {
        LOG(LM_STD,Fmtmsg("/commbuf����Ϊ[%s],��ȷ��", iUTF8Len ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* ���ݻ�ȡ���ĳ��������ڴ� */
    pUTF8 = (char *)malloc( iUTF8Len+1 );
    if ( pUTF8 == NULL )
    {
        LOG(LM_STD,Fmtmsg("��̬����commbuf�ڴ�ʧ��" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
	/*��ȡͨѶ������*/
	memset(pUTF8, 0x00, iUTF8Len+1);
	if(0 > (iRet = xml_RelGetBinElement(lXmlhandle, "/commbuf", pUTF8, iUTF8Len+1)))
	{
		free(pUTF8);pUTF8=NULL;
		LOG(LM_STD, Fmtmsg("ȡͨѶ������iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "ת��UTF-8,��ȡͨѶ������");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	LOG(LM_STD, Fmtmsg("get pUTF8[%d][%s]", iRet, pUTF8), fpub_GetCompname(lXmlhandle));
    
    iGBKLen = iUTF8Len * 1.5 ;
    pGBK = (char *)malloc( iGBKLen+1 );
    if ( pGBK == NULL )
    {
        free(pUTF8);pUTF8=NULL;
        LOG(LM_STD,Fmtmsg("��̬����commbuf�ڴ�ʧ��" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    memset(pGBK, 0x00, iGBKLen+1);
    iRet = convert( "UTF-8", "GB18030", pUTF8, iUTF8Len, pGBK, &iGBKLen);
    if ( iRet < 0 )
    {
		free(pUTF8);pUTF8=NULL;
		free(pGBK);pGBK=NULL;
		LOG(LM_STD, Fmtmsg("ת��UTF-8,ת��GB18030��������ʧ��iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "ת��UTF-8,ת��GB18030��������ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
    }
    free(pUTF8);pUTF8=NULL;
    iGBKLen=strlen(pGBK);
    LOG(LM_STD, Fmtmsg("utf-8->gbk=[%d][%s]", iGBKLen,pGBK), fpub_GetCompname(lXmlhandle));
    if(0 > (iRet = xml_RelSetBinElement(lXmlhandle, "/commbuf", pGBK, iGBKLen)))
    {
    	free(pGBK);pGBK=NULL;
		LOG(LM_STD, Fmtmsg("��д/commbuf��������ʧ��iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "ת��UTF-8,��д/commbuf��������ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
    }
    free(pGBK);pGBK=NULL;
    /* ���׽��� */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("ת��UTF-8->����ɹ�"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}
