/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:����˾�����ǰ��ϵͳ
��    ��:V2.0
����ϵͳ:AIX
�� �� ��:ORA
�ļ�����:SF_C_LST.c
�ļ�����:�б��ѯģ��
�� Ŀ ��:
�� �� Ա:������
��������:2016-02-26

��    ��:
�޸�����:
*********************************************************************/

#include "gaps_head.h"
#include "gabdxzp_head.h"
#include "sfxt_lstqry.h"

#define SOCOMPVERSION "V2.0.0.1"
#define SOCOMPBUILDNO "V2.0.0.1"
/************************************************************************
��̬�����������
�����������:ShowSocompVersion
�������:����汾��ں���
************************************************************************/
IRESULT ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
   <root>\
      <soname>SFXT_LST.so</soname>\
      <sosrcname>SF_*_LST.*c </sosrcname>\
      <sonote>˾������б��ѯģ��</sonote>\
      <version>\
         <rec ver=\"2.0.0.1\" modify=\"2016-02-26 09:08\" programer=\"˾����ز�Ʒ��\" filesize=\"1000\">��Ԫ�������</rec>\
      </version>\
   </root>";
  printf("\n================��̬���������Ϣ================\n");
  printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
  printf("%s-%s\n",__PROJECTSNAME,__VERSION);
  if ( strlen(sversion) >= isize )
  {
    printf(" -->ȡ��ϸ��Ϣʧ��...\n");
    return -2;
  }
  strcpy(sinfo,sversion);
  printf(" -->��鿴��ϸ��Ϣ...\n");
  return 0;
}

/************************************************************************
��̬�����������
�����������: SFXT_COMMLST
�������: ˾�����ͨ�ò�ѯ 
�������:
  
 �������
 ��� ��������  ��������         ��Դ���     ȱʡֵ      �ɿ�  ����˵��


������״̬:
  ���״̬��         ���˵��
    COMPSTATUS_SUCC
��������˵����
    

�� Ŀ ��: 
�� �� Ա: ������
��������: 2016��2��26��
�޸�����: 
����ʹ��ʾ��:
************************************************************************/
IRESULT SFXT_COMMLST(HXMLTREE lXmlhandle)
{
    char sSql[4096];
    int  iRet = -1;
    int  iRealNum = 0;
    int iStartNum = 0;
    int iQueryNum = 20;
    int iEndNum = 0;
    int iCntNum = 0;
    int iTmp = 0;
    char sRspType[1+1];
    char sBuf[256];
    
    fpub_InitSoComp(lXmlhandle);
        
    memset(sSql, 0x00, sizeof(sSql));
    COMP_GETPARSEPARAS(1, sSql, "ͨ�ò�ѯ���")

    /* ��ȡ��ʼ��������ѯ���� */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "��ʼ����")
    if( sBuf[0] == '\0' )
    {
        sBuf[0] == '1' ;
    }
    iStartNum = atoi(sBuf);

    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "��ѯ����")
    if( sBuf[0] == '\0' )
    {
        sBuf[0] == '1' ;
    }
    iQueryNum = atoi(sBuf);
    
    iEndNum = iStartNum + iQueryNum ;
    /* �б��ѯ���ط�ʽ */
    memset(sRspType, 0x00, sizeof(sRspType));
    GAB_DXZP_GETXMLSTR_NULL( XMLNM_RSPTYPE, sRspType, "���ط�ʽ" )
    /* ��ȡ�ܱ��� */
    iRet = ffunc_sfxt_listQry_getCntNum(lXmlhandle, sSql, strlen(sSql), &iCntNum);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "��ȡ�ܱ���");
    LOG(LM_STD,Fmtmsg("˾�����ͨ�ò�ѯ->��ɻ�ȡ�ܱ���[%d]", iCntNum), fpub_GetCompname(lXmlhandle)); 
    LOG( LM_DEBUG, Fmtmsg("˾�����ͨ�ò�ѯ->�б��ѯsql:[%s]", sSql), fpub_GetCompname(lXmlhandle));
    if ( sRspType[0] == '0' )/* д�ļ�*/
    {
        iRet= ffunc_sfxt_listQry_wrtRndFile(lXmlhandle, sSql, iStartNum, iEndNum, &iRealNum);
    }else
    {
        iRet= ffunc_sfxt_listQry_wrtRndXml(lXmlhandle, sSql, iStartNum, iEndNum, &iRealNum);
    }
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "��ȡ���ݼ�д�ļ�");
    LOG(LM_STD,Fmtmsg("˾�����ͨ�ò�ѯ->��ɻ�ȡ����д��¼"), fpub_GetCompname(lXmlhandle));  
    /* �践��ֵ */
    COMP_SOFTSETXML(XMLNM_RESP_TOTALNUM, itoa(iCntNum))
    COMP_SOFTSETXML(XMLNM_RESP_REALNUM, itoa(iRealNum))
    iTmp = iCntNum-iEndNum ;
    if ( iTmp < 0 )
    {
        iTmp = 0;
    }
    COMP_SOFTSETXML(XMLNM_RESP_SURPNUM, itoa(iTmp))
    COMP_SOFTSETXML(XMLNM_RESP_STARTNUM, itoa(iStartNum))
    COMP_SOFTSETXML(XMLNM_RESP_QUERYNUM, itoa(iQueryNum))
    
    fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "˾�����ͨ�ò�ѯ�ɹ�");
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}
