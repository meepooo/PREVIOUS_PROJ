/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V4.1.00
����ϵͳ:AIX/Linux/HP-UX
�ļ�����:SSQLITE_sample.c
�ļ�����:sqlite���ݿ����-��ѯ����
�� Ŀ ��:GAPS�з���
�� �� Ա:ʱ��
��������:
��    ��:
�޸�����:2009-4-15 17:01
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "gaps_sys.h"
#include "sha.h"
#include "gaps_head.h"

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "4.0.2"

#define MSG_ITEM_ERROR              "ITEM��item����ʧ��[%s]"
#define MID_ITEM_ERR              "item_getErrorId()"
#define MSG_ITEM_ERR              "ITEM��item_get_err_msg(item_getErrorId())"

int sc_db_callback(HXMLTREE  lXmlhandle, int n_cols, char **data, char **names);
IRESULT SDB_SqliteSelect(HXMLTREE lXmlhandle);

int ShowSocompVersion(char *sinfo, int isize)
{
  char sversion[] = "<?xml version=\"1.0\" encoding=\"GB2312\"?>\
     <root>\
      <soname>SSQLITE_sample.so</soname>\
      <sosrcname>SSQLITE_sample.c</sosrcname>\
      <sonote>sqlite���ݿ��ѯ�������</sonote>\
      <version>\
        <rec ver=\"4.0.00\" modify=\"2009-6-11 11:43\" programer=\"Shining\" filesize=\"20003\">ASPKV4��������sqlte��������</rec>\
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
�����������: SDB_SqliteSelect
�������: ִ��select���
�������:
    ����ִ��select��ѯ���
�������:
��� ��������   ��Դ���     ȱʡֵ   �Ƿ�ɿ�  ����˵��
1 sql��� XML�����ַ���     ����ִ�е�select���

�� Ŀ ��: �м�ҵ���Ʒ�з���
�� �� Ա: ʱ��
��������: 2009��04��14��
�޸�����:
����ʹ��ʾ��:
�޸ģ�

************************************************************************/
IRESULT SDB_SqliteSelect(HXMLTREE lXmlhandle)
{
  int  iParas;
  char sSql[1024];
  sqlite3 *sqlite_db = NULL;
  item *it;
  char *errmsg;
  char sRecordpath[256];    /* ��¼���·�� */
  long lDbaddr;
  char sItemkey[8];


  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "")
#endif
  /*��ȡ��������*/
  memset(sSql, 0, sizeof(sSql));

  COMP_PARACOUNTCHKMIN(2)
  COMP_GETPARSEPARAS(1, sSql, "��ִ�е�select���")
  COMP_GETDFTPARAS(2, sRecordpath, "��ѯ�����¼���·��", "/record");

  strcpy(sItemkey, "db_addr");
  if ((it = item_get(sItemkey, strlen(sItemkey))) == NULL)
  {
    LOG(LM_STD, Fmtmsg(MSG_ITEM_ERROR, item_get_err_msg(item_getErrorId())), __func__)
    fpub_SetMsg(lXmlhandle, MID_ITEM_ERR, MSG_ITEM_ERR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPSTATUS_FAIL;
  }

  memcpy(&lDbaddr, ITEM_data(it), sizeof(lDbaddr));
  sqlite_db = (struct sqlite3*)lDbaddr;

  if ( xml_DelElement( lXmlhandle, "/recordpath" ) == -1 )
  {
    LOG(LM_STD, Fmtmsg("ɾ�����[/recordpath]ʧ��"), __func__)
    return COMPSTATUS_FAIL;
  }

  if (xml_AddElement( lXmlhandle, "/recordpath", sRecordpath ) == -1)
  {
    LOG(LM_STD, Fmtmsg("���ӽ��[/recordpath]ʧ��"), __func__)
    return COMPSTATUS_FAIL;
  }

  xml_DelElement( lXmlhandle, sRecordpath );    /* ��ռ�����Ž���Ľ�� */
  if (sqlite3_exec(sqlite_db, sSql, sc_db_callback, lXmlhandle, &errmsg) != MID_SYS_SUCC)
  {
    LOG(LM_STD, Fmtmsg(MSG_SQL_ERROR, errmsg), __func__)
    fpub_SetMsg(lXmlhandle, MID_SQL_ERR, MSG_SQL_ERR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPSTATUS_FAIL;
  }

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  return COMPRET_SUCC;
}

int sc_db_callback(HXMLTREE  lXmlhandle, int n_cols, char **data, char **names)
{
  int i;
  char stmp[4096];
  char strname[1024];
  char recordpath[256];

  memset(recordpath, 0, sizeof(recordpath));
  if (xml_GetElement( lXmlhandle, "/recordpath", recordpath, sizeof(recordpath) ) == -1)
  {
    LOG(LM_STD, Fmtmsg("ȡ���[/recordpath]ʧ��"), __func__)
    return -1;
  }
  for (i = 0;i < n_cols;i++)
  {
    memset(stmp, 0, sizeof(stmp));
    memset(strname, 0, sizeof(strname));
    memcpy(stmp, data[i], strlen(data[i]) < 4096 ? strlen(data[i]) : 4096);
    memcpy(strname, names[i], strlen(names[i]) < 1024 ? strlen(names[i]) : 1024);

    sprintf(strname, "/%s|0/%s", recordpath, trim(strname));
    if (xml_AddElement( lXmlhandle, strname, stmp ) == -1)
    {
      LOG(LM_STD, Fmtmsg("���ý��[%s]ʧ��", strname), __func__)
      return -1;
    }
  }
  return 0;
}

int main()
{
  return 0;
}
