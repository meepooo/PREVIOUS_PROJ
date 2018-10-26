/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V4.1.00
����ϵͳ:AIX/Linux/HP-UX
�� �� ��:SCOMP_DEMO.c
�ļ�����:���������������ר�������
�� Ŀ ��:GAPS�з���
�� �� Ա:Tianhc
��������:2011-07-15 8:43:28
��    ��:
�޸�����:
****************************************************************************/

#include "gaps_head.h"
#include "xml.h"
static char Level_STRAC_DEMO_c[] = "{$Id: STRAC_DEMO.c 2548 2014-07-09 09:26:16Z tianhc $}";

/************************************************************************
��̬�����������
�����������: STRAC_HELLOWORLD
�������: TRAC_HELLOWORLD
�������:
     ��򵥵�Hello World���,������ϰ&��ѧ
�������:
  ��� ��������   ��Դ���     ȱʡֵ   �Ƿ�ɿ�  ����˵��
  1   ��1������    416-�����ַ���            Y    0-�������Ϊʧ��,��������������гɹ�

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: GAPSV4.1
�� �� Ա:
��������: 2011-07-15 8:44:15
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT STRAC_HELLOWORLD(HXMLTREE lXmlhandle)
{
  char spara1[30];
  char sbuf[255];
  int  iParas;
  fpub_InitSoComp(lXmlhandle);
  COMP_GETPARSEPARAS(1, spara1, "��1������")
  LOG(LM_DEBUG, Fmtmsg("  -->��1������[%s]", spara1), "INFO")
  LOG(LM_STD, Fmtmsg("Hello World!"), __func__)
  if ( strcmp(spara1, "0") == 0 )
  {
    LOG(LM_STD, Fmtmsg("  -->���׾ܾ�:xxxx"), "ERROR");
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "")
#endif
  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}


static char* prv_malloc_2(int isize)
{
	  char *ptmp;
	  LOG(LM_STD, Fmtmsg("  Ƕ�׺����е��ڴ����2..."), __func__)
	  ptmp = (char *)malloc(isize);
	  return ptmp;
}	


static char* prv_malloc(int isize)
{
	  LOG(LM_STD, Fmtmsg("  Ƕ�׺����е��ڴ����1..."), __func__)
	  return prv_malloc_2(isize);
}	

/************************************************************************
��̬�����������
�����������: STRAC_MEMLEAK
�������: TRAC_MEMLEAK
�������:
     �ڴ�й©����ģ�����,������֤���԰��������Ƿ�����
�������:
  ��� ��������   ��Դ���     ȱʡֵ   �Ƿ�ɿ�  ����˵��


������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: GAPSV4.1
�� �� Ա:
��������: 2011-07-15 8:44:15
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT STRAC_MEMLEAK(HXMLTREE lXmlhandle)
{
  char sflag_malloc[30], sflag_openfile[30], sflag_cursor[30];
  char sbuf[255], *p, *pfunc, *poverstack;
  char sbuf6[6];
  int  iParas, iret;
  FILE *fp;
  CURSOR cur;
  
  fpub_InitSoComp(lXmlhandle);
  COMP_GETPARSEPARAS(1, sflag_malloc, "�ڴ���俪��")
  COMP_GETPARSEPARAS(2, sflag_openfile, "���ļ�����")
  COMP_GETPARSEPARAS(3, sflag_cursor, "���α꿪��")


  LOG(LM_DEBUG, Fmtmsg("  -->�ڴ���俪��[%s],���ļ�����[%s],���α꿪��[%s]", sflag_malloc, sflag_openfile, sflag_cursor), "INFO")
  LOG(LM_STD, Fmtmsg(" [WARN]�����ֻ���ڲ���!��֤���̵��Թ����е��ڴ�й©���ļ������DCI SQL�����Ƿ�����!!"), __func__)

  
  if ((p = (char *)malloc(1234)) == NULL)
  {
    LOG(LM_STD, Fmtmsg("  -->����쳣:�ڴ����ʧ��!, err[%s]", strerror(errno)), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }		

  if (sbuf[0] == '1')                   /*ʹ��δ��ʼ���ı���!*/
  {	
  	LOG(LM_STD, Fmtmsg("δ��ʼ���ı���"), __func__);
  }	

  p[1235] = '1';                        /*�ѿռ�:����ָ��Խ��--���Ծ�̬���*/
  xml_GetElement(lXmlhandle, "/sys/sysdate", sbuf, sizeof(sbuf));
  poverstack = (char *)malloc(6) ;
  strcpy(poverstack, sbuf);             /*�ѿռ�:����ָ��Խ��(д)-�޷���̬���*/
  free(poverstack);
  
  strcpy(sbuf6, sbuf);                  /*ջ�ռ�:����ָ��Խ��(д)-�޷���̬���*/
  
  sbuf6[0] = p[1235];                   /*�ѿռ�:����ָ��Խ��(��)-���Ծ�̬���*/
  p[0]     = sbuf6[7];                  /*ջ�ռ�:����ָ��Խ��(��)-���Ծ�̬���*/

  
  pfunc=prv_malloc(4321);
  if (sflag_malloc[0] != '1')
  {	
  	free(p);
  	free(pfunc);
  }
  else
  {
    LOG(LM_STD, Fmtmsg("  -->ע��:���������1234�ֽ��ڴ�,δ�ͷ�,ģ���ڴ�й©����, ��ACIDE�����в��԰���-->���ڴ�й©�����ʱ,Ӧ���ܷ��ֱ�����쳣!"), __func__);
    LOG(LM_STD, Fmtmsg("  -->ע��:���������4321�ֽ��ڴ�(Ƕ�׺���),δ�ͷ�,ģ���ڴ�й©����, ��ACIDE�����в��԰���-->���ڴ�й©�����ʱ,Ӧ���ܷ��ֱ�����쳣!"), __func__);
  }		  

  snprintf(sbuf, sizeof(sbuf), "%s/etc/gaps.ini", getenv("HOME"));
  if ((fp = fopen(sbuf, "r")) == NULL)
  {
    LOG(LM_STD, Fmtmsg("  -->����쳣:���ļ�ʧ��, file[%s], err[%s]!", sbuf, strerror(errno)), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }		
  if (sflag_openfile[0] != '1')
  	fclose(fp);
  else
  {
    LOG(LM_STD, Fmtmsg("  -->ע��:�������һ���ļ�,δ�ر�,ģ����δ�صĳ���, ��ACIDE�����в��԰���,Ӧ���ܷ��ֱ�����쳣!"), __func__);
  }		  
  
  snprintf(sbuf, sizeof(sbuf), "select count(*) from ywty_drls");
  if ((cur = DCIDeclareCursor(sbuf, DCI_STMT_LOCATOR)) == -1)  
  {
    LOG(LM_STD, Fmtmsg("  -->����쳣:ִ��SQLʧ��, sql[%s],DCIDeclareCursor err[%s]!", sbuf, DCILastError()), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }		
  if (DCIExecute(cur) == -1)
  {
    LOG(LM_STD, Fmtmsg("  -->����쳣:ִ��SQLʧ��, sql[%s],DCIExecute err[%s]!", sbuf, DCILastError()), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }		
  iret = DCIFetch(cur);
  if (iret < 0)
  {
    LOG(LM_STD, Fmtmsg("  -->����쳣:ִ��SQLʧ��, sql[%s],DCIFetch err[%s]!", sbuf, DCILastError()), __func__);
    DCIFreeCursor(cur);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }		
  LOG(LM_STD, Fmtmsg(" Fetch, sql[%s], fld[0]=%s", sbuf, DCIFieldAsString(cur, 0)), __func__);

  if (sflag_cursor[0] != '1')
  	DCIFreeCursor(cur);
  else
  {
    LOG(LM_STD, Fmtmsg("  -->ע��:�������һ���α�,δ�ر�,ģ���α�δ�صĳ���, ��ACIDE�����в��԰���,Ӧ���ܷ��ֱ�����쳣!"), __func__);
  }		  
  /*SHA���ٲ����ʣ�
    1�����״����ռ�, һ��Ҳ���ͷ�; 2������ϵͳ���õ�; 
    3��6�����ٲ�����7������,7������ٹ����ϵͳ���ù���;
  */
  if (item_set("test_key", strlen("test_key"), __func__, strlen(__func__)) == '\0')
  {
    LOG(LM_STD, Fmtmsg("  -->����쳣:SHA����ʧ��, item_set err[%s]!", item_get_err_msg(item_getErrorId())), __func__);
  }		

  LOG(LM_STD, Fmtmsg(" �ڴ�й©����������, ��鿴HTTP��־����ϸ��Ϣ�����ڷ�ACIDE�����ģ�����,��Щй©����Ҳ������ʾ!"), __func__);  
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "")
#endif
  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}

/*
  ��������ص�����DEMO��
  HXMLTREE   hxml        ��ǰ������xml���
  char       *compname   ��ǰ�����
  int        icompstat   ���ִ��״̬
  int        computime   ���ִ�к�ʱ,��λms
*/
int func_exlog(HXMLTREE hxml, char *compname, int icompstat, int computime)
{
	char sline[255];
	if (icompstat >= 0)
	  return 0;
	snprintf(sline, sizeof(sline), "\nsystime=%s, zhqzlsh=%s, trace=%s ...\n", 
	   xml_GetElementP(hxml, "/sys/systime"),
	   xml_GetElementP(hxml, "/pub/zhqzlsh"),
	   xml_GetElementP(hxml, "/pub/traceid"));
	LOG(LM_STD, sline, __func__);
	return 0;  
}	

/************************************************************************
��̬�����������
�����������: SGAPS_COMPEXFUNC_REG
�������: GAPS_COMPEXFUNC_REG
�������:
     GAPSƽ̨����չ�����ע�����ִ����Һ���
     �����ڳ�ʼ�������е���!
�������:

������״̬:
  ���״̬��         ���˵��
  ȱʡ

��־��Ϣ:
  ��־����           ��־��

��Ӧ��Ϣ:
  �ڲ���Ӧ��         �ڲ���Ӧ��Ϣ

��Ҫ����Ԫ��:
  Ԫ��·��          ����

��Ҫ�������:
  ����              ����

ʹ������:

�� Ŀ ��: GAPSV4.1
�� �� Ա:
��������: 2014/7/7 11:10:40
�޸�����:
����ʹ��ʾ��:
************************************************************************/   
IRESULT SGAPS_COMPEXFUNC_REG(HXMLTREE lXmlhandle)
{
  fpub_InitSoComp(lXmlhandle);
	
	LOG(LM_STD, Fmtmsg(" ע��GAPS����������Һ���: %s", "func_exlog"), __func__);
	fpub_gapssfs_compexfunc_reg( (void *)func_exlog);
	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0; 
}	



