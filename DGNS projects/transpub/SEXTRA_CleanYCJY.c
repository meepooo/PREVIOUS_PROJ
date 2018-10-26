/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ǰ�ã�GAPS����Ŀ
��    ��:V4.1
����ϵͳ:AIX
�ļ�����:SEXTRA_CleanYCJY.c
�ļ�����:�쳣�������ycjy״̬�������
�� Ŀ ��:GAPS�з���
�� �� Ա:Shining
��������:
��    ��:
�޸�����:2011-8-3 10:15:33
*********************************************************************/

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "4.0.0"

#include "gaps_head.h"
#include "ywty_ycjyyx.h"
#include "sqlite3.h"
#include "DCI.h"
#include "gaps_mid_syscomp.h"

static int prv_update(HXMLTREE lXmlhandle, char *sZwrq, char *sCpdm );

int ShowSocompVersion(char *sinfo, int isize)
{
  char sversion[] = "<?xml version=\"1.0\" encoding=\"GB2312\"?>\
     <root>\
      <soname>SEXTRA_CleanYCJY.so</soname>\
      <sosrcname>SEXTRA_CleanYCJY.c</sosrcname>\
      <sonote>sqlite���ݿ��޸��쳣����ӳ��״̬���</sonote>\
      <version>\
        <rec ver=\"4.0.0\" modify=\"2011-8-3 10:59\" programer=\"Shining\" filesize=\"7558\">ASPKV4����������������sqlte��������SEXTRA_CleanYCJY�޸�ywty_ycjyyx״̬</rec>\
      </version>\
     </root>";
  printf("\n================��̬���������Ϣ================\n");
  printf("SOCOMPBUILDNO:%s\n", SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s\n", SOCOMPVERSION);
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
�����������: SEXTRA_CleanYCJY
�������: �����쳣���׻����
�������:
    ���������쳣���׻����
�������:
��� ��������   ��Դ���     ȱʡֵ   �Ƿ�ɿ�  ����˵��
1    ��������   XML�����ַ���             �ǿ�      ʵ����������
2    ��Ʒ����   XML�����ַ���             �ǿ�      ��Ʒ����

�� Ŀ ��: �м�ҵ���Ʒ�з���
�� �� Ա: ʱ��
��������: 2011��08��03��
�޸�����:
����ʹ��ʾ��:
�޸ģ�

************************************************************************/
IRESULT SEXTRA_CleanYCJY(HXMLTREE lXmlhandle)
{
  int  iParas;
  int  rc,i=0;
  char sState[1+1];
  CURSOR cur;
  char sSql[1024];
  char sZwrq[8+1];
  char sCpdm[20];       /*��Ʒ����*/

  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "")
#endif
  /*��ȡ��������*/

  COMP_PARACOUNTCHKMIN(2)
  COMP_GETPARSEPARAS(1, sZwrq, "��������");
	COMP_GETPARSEPARAS(2, sCpdm, "��Ʒ����");
	
/* �����쳣������ˮ��״̬ */
  if (prv_update(lXmlhandle, sZwrq , sCpdm) != 0)
  {
      fpub_SetMsg(lXmlhandle,MID_SQL_ERR, MSG_SQL_ERR);
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return -1;
  }

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  return COMPRET_SUCC;
}

/*
   shining 2011-7-30 16:48:02
   ���������쳣�������쳣ҵ��״̬��ʹ��sqlite3����
   �������������ݿ�open->update->close�Ĺ���
   �쳣�����־��0 δ����_NO 1 ����ɹ�_SUCC 2 ����ʧ��_FAIL 3 �����ظ���������_RPTOVER
*/
static int prv_update(HXMLTREE lXmlhandle, char *sZwrq, char *sYykz )
{
    GSA_SPA *pGSA_SPA;
    char *pGSAhead;
    char sbuf[255], sfile_db[100], sSql[1024];
    int iret;
    char *errmsg;
    sqlite3_stmt *pStmt;
    sqlite3 *sqlite_db = NULL;

    if (getenv("GAPSCFGDIR") == NULL)
       snprintf(sfile_db, sizeof(sfile_db), "%s/cfg/%s", getenv("HOME"), FILE_SYSDB);
    else
       snprintf(sfile_db, sizeof(sfile_db), "%s/%s", getenv("GAPSCFGDIR"), FILE_SYSDB);

/*��SPA�л����ź���*/
	  if ( xml_GetElement(lXmlhandle,XMLNM_GSAHEAD,sbuf,sizeof(sbuf))<0 )
	  {   
	    fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,
	           Fmtmsg("�쳣ϵͳ���󣺻�ȡSPA[%s]",GETXMLERR));
	    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);

      LOG(LM_STD, Fmtmsg("SYS_COMP:%d, �쳣ϵͳ���󣺻�ȡSPA�׵�ַʧ��", MID_SYS_COMP_2081), __func__);
      return COMPSTATUS_FAIL;
	  }   
	  pGSAhead = (char*)atol(sbuf);
	  pGSA_SPA=(GSA_SPA *)pGSAhead;
/*�����ݿ����*/
    sqlite3_open(sfile_db, &sqlite_db);
    if (sqlite_db == NULL)  
    {
       LOG(LM_STD, Fmtmsg("SYS_COMP:%d, ��ϵͳ���ݿ�ʧ��,msg[%s]", MID_SYS_COMP_2078,sqlite3_errmsg(sqlite_db)), __func__);
    	 sqlite3_close(sqlite_db);
    	 return COMPSTATUS_FAIL;
    }		
  
/*��װsqlite3 update����,�����쳣�����־��0 δ����_NO 1 ����ɹ�_SUCC 2 ����ʧ��_FAIL 3 �����ظ���������_RPTOVER*/
/*���޸�*/
   snprintf(sSql, sizeof(sSql), "update ywty_ycjyyx set ycclbz = '%c' where zwrq = '%s' and yykz = '%s' and ycclbz = '%c' ", '2', sZwrq, sYykz, '0');

/*����*/
  if ( SemP(pGSA_SPA->semSQLITE) ==FAIL )
  {
       LOG(LM_STD, Fmtmsg("SYS_COMP:%d, ����ϵͳ���ݿ�ʧ��,SemP Err,[%d][%s]", 
           MID_SYS_COMP_2079, errno,strerror(errno)), __func__);
    	 sqlite3_close(sqlite_db);
    	 return COMPSTATUS_FAIL;
  }
  
  if (sqlite3_exec(sqlite_db, sSql, NULL, NULL, &errmsg) != MID_SYS_SUCC)
  {
    LOG(LM_STD, Fmtmsg("SYS_COMP:%d, ִ��SQL���ʧ��,errmsg=[%s]", MID_SYS_COMP_1520,errmsg), __func__);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERR, MSG_SQL_ERR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    sqlite3_close(sqlite_db);
    SemV(pGSA_SPA->semSQLITE);
    return COMPSTATUS_FAIL;
  }
  LOG(LM_STD, Fmtmsg("ִ��sql[%s]Ӱ���¼����:[%d]", sSql, sqlite3_changes(sqlite_db)), __func__)

	sqlite3_close(sqlite_db);
/*����*/
  if ( SemV(pGSA_SPA->semSQLITE) ==FAIL )
  {
       LOG(LM_STD, Fmtmsg("SYS_COMP:%d, ����ϵͳ���ݿ�ʧ��,SemV Err,[%d][%s]", 
           MID_SYS_COMP_2080, errno,strerror(errno)), __func__);
    	 return COMPSTATUS_FAIL;
  }	  
	return 0;
}

int main()
{
	return 0;
}
