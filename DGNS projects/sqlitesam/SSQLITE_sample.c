/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V4.1.00
操作系统:AIX/Linux/HP-UX
文件名称:SSQLITE_sample.c
文件描述:sqlite数据库组件-查询样例
项 目 组:GAPS研发组
程 序 员:时宁
发布日期:
修    订:
修改日期:2009-4-15 17:01
*********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "sqlite3.h"
#include "gaps_sys.h"
#include "sha.h"
#include "gaps_head.h"

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "4.0.2"

#define MSG_ITEM_ERROR              "ITEM：item操作失败[%s]"
#define MID_ITEM_ERR              "item_getErrorId()"
#define MSG_ITEM_ERR              "ITEM：item_get_err_msg(item_getErrorId())"

int sc_db_callback(HXMLTREE  lXmlhandle, int n_cols, char **data, char **names);
IRESULT SDB_SqliteSelect(HXMLTREE lXmlhandle);

int ShowSocompVersion(char *sinfo, int isize)
{
  char sversion[] = "<?xml version=\"1.0\" encoding=\"GB2312\"?>\
     <root>\
      <soname>SSQLITE_sample.so</soname>\
      <sosrcname>SSQLITE_sample.c</sosrcname>\
      <sonote>sqlite数据库查询样例组件</sonote>\
      <version>\
        <rec ver=\"4.0.00\" modify=\"2009-6-11 11:43\" programer=\"Shining\" filesize=\"20003\">ASPKV4环境新增sqlte操作样例</rec>\
      </version>\
     </root>";
  printf("\n================动态组件基本信息================\n");
  printf("SOCOMPBUILDNO:%s\n", SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s\n", SOCOMPVERSION);
  printf("%s-%s\n", __PROJECTSNAME, __VERSION);
  if (strlen(sversion) >= isize)
  {
    printf(" -->取详细信息失败...\n");
    return -2;
  }
  strcpy(sinfo, sversion);
  printf(" -->请查看详细信息...\n");
  return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称: SDB_SqliteSelect
组件名称: 执行select语句
组件功能:
    用于执行select查询语句
组件参数:
序号 参数名称   资源类别     缺省值   是否可空  参数说明
1 sql语句 XML解析字符串     用于执行的select语句

项 目 组: 中间业务产品研发组
程 序 员: 时宁
发布日期: 2009年04月14日
修改日期:
参数使用示例:
修改：

************************************************************************/
IRESULT SDB_SqliteSelect(HXMLTREE lXmlhandle)
{
  int  iParas;
  char sSql[1024];
  sqlite3 *sqlite_db = NULL;
  item *it;
  char *errmsg;
  char sRecordpath[256];    /* 记录存放路径 */
  long lDbaddr;
  char sItemkey[8];


  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "")
#endif
  /*获取参数个数*/
  memset(sSql, 0, sizeof(sSql));

  COMP_PARACOUNTCHKMIN(2)
  COMP_GETPARSEPARAS(1, sSql, "待执行的select语句")
  COMP_GETDFTPARAS(2, sRecordpath, "查询结果记录存放路径", "/record");

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
    LOG(LM_STD, Fmtmsg("删除结点[/recordpath]失败"), __func__)
    return COMPSTATUS_FAIL;
  }

  if (xml_AddElement( lXmlhandle, "/recordpath", sRecordpath ) == -1)
  {
    LOG(LM_STD, Fmtmsg("增加结点[/recordpath]失败"), __func__)
    return COMPSTATUS_FAIL;
  }

  xml_DelElement( lXmlhandle, sRecordpath );    /* 清空即将存放结果的结点 */
  if (sqlite3_exec(sqlite_db, sSql, sc_db_callback, lXmlhandle, &errmsg) != MID_SYS_SUCC)
  {
    LOG(LM_STD, Fmtmsg(MSG_SQL_ERROR, errmsg), __func__)
    fpub_SetMsg(lXmlhandle, MID_SQL_ERR, MSG_SQL_ERR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPSTATUS_FAIL;
  }

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
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
    LOG(LM_STD, Fmtmsg("取结点[/recordpath]失败"), __func__)
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
      LOG(LM_STD, Fmtmsg("设置结点[%s]失败", strname), __func__)
      return -1;
    }
  }
  return 0;
}

int main()
{
  return 0;
}
