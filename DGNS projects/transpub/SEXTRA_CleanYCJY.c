/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用前置（GAPS）项目
版    本:V4.1
操作系统:AIX
文件名称:SEXTRA_CleanYCJY.c
文件描述:异常处理更新ycjy状态组件集合
项 目 组:GAPS研发组
程 序 员:Shining
发布日期:
修    订:
修改日期:2011-8-3 10:15:33
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
      <sonote>sqlite数据库修改异常交易映像状态组件</sonote>\
      <version>\
        <rec ver=\"4.0.0\" modify=\"2011-8-3 10:59\" programer=\"Shining\" filesize=\"7558\">ASPKV4环境新增根据条件sqlte操作函数SEXTRA_CleanYCJY修改ywty_ycjyyx状态</rec>\
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
组件函数名称: SEXTRA_CleanYCJY
组件名称: 清理异常交易缓冲池
组件功能:
    用于清理异常交易缓冲池
组件参数:
序号 参数名称   资源类别     缺省值   是否可空  参数说明
1    账务日期   XML解析字符串             非空      实际账务日期
2    产品代码   XML解析字符串             非空      产品代码

项 目 组: 中间业务产品研发组
程 序 员: 时宁
发布日期: 2011年08月03日
修改日期:
参数使用示例:
修改：

************************************************************************/
IRESULT SEXTRA_CleanYCJY(HXMLTREE lXmlhandle)
{
  int  iParas;
  int  rc,i=0;
  char sState[1+1];
  CURSOR cur;
  char sSql[1024];
  char sZwrq[8+1];
  char sCpdm[20];       /*产品代码*/

  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "")
#endif
  /*获取参数个数*/

  COMP_PARACOUNTCHKMIN(2)
  COMP_GETPARSEPARAS(1, sZwrq, "账务日期");
	COMP_GETPARSEPARAS(2, sCpdm, "产品代码");
	
/* 更新异常交易流水表状态 */
  if (prv_update(lXmlhandle, sZwrq , sCpdm) != 0)
  {
      fpub_SetMsg(lXmlhandle,MID_SQL_ERR, MSG_SQL_ERR);
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return -1;
  }

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  return COMPRET_SUCC;
}

/*
   shining 2011-7-30 16:48:02
   新增更新异常数据中异常业务状态，使用sqlite3操作
   本操作将打开数据库open->update->close的过程
   异常处理标志：0 未处理_NO 1 处理成功_SUCC 2 处理失败_FAIL 3 处理重复次数超限_RPTOVER
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

/*从SPA中获以信号量*/
	  if ( xml_GetElement(lXmlhandle,XMLNM_GSAHEAD,sbuf,sizeof(sbuf))<0 )
	  {   
	    fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,
	           Fmtmsg("异常系统错误：获取SPA[%s]",GETXMLERR));
	    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);

      LOG(LM_STD, Fmtmsg("SYS_COMP:%d, 异常系统错误：获取SPA首地址失败", MID_SYS_COMP_2081), __func__);
      return COMPSTATUS_FAIL;
	  }   
	  pGSAhead = (char*)atol(sbuf);
	  pGSA_SPA=(GSA_SPA *)pGSAhead;
/*打开数据库操作*/
    sqlite3_open(sfile_db, &sqlite_db);
    if (sqlite_db == NULL)  
    {
       LOG(LM_STD, Fmtmsg("SYS_COMP:%d, 打开系统数据库失败,msg[%s]", MID_SYS_COMP_2078,sqlite3_errmsg(sqlite_db)), __func__);
    	 sqlite3_close(sqlite_db);
    	 return COMPSTATUS_FAIL;
    }		
  
/*组装sqlite3 update操作,其中异常处理标志：0 未处理_NO 1 处理成功_SUCC 2 处理失败_FAIL 3 处理重复次数超限_RPTOVER*/
/*待修改*/
   snprintf(sSql, sizeof(sSql), "update ywty_ycjyyx set ycclbz = '%c' where zwrq = '%s' and yykz = '%s' and ycclbz = '%c' ", '2', sZwrq, sYykz, '0');

/*加锁*/
  if ( SemP(pGSA_SPA->semSQLITE) ==FAIL )
  {
       LOG(LM_STD, Fmtmsg("SYS_COMP:%d, 操作系统数据库失败,SemP Err,[%d][%s]", 
           MID_SYS_COMP_2079, errno,strerror(errno)), __func__);
    	 sqlite3_close(sqlite_db);
    	 return COMPSTATUS_FAIL;
  }
  
  if (sqlite3_exec(sqlite_db, sSql, NULL, NULL, &errmsg) != MID_SYS_SUCC)
  {
    LOG(LM_STD, Fmtmsg("SYS_COMP:%d, 执行SQL语句失败,errmsg=[%s]", MID_SYS_COMP_1520,errmsg), __func__);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERR, MSG_SQL_ERR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    sqlite3_close(sqlite_db);
    SemV(pGSA_SPA->semSQLITE);
    return COMPSTATUS_FAIL;
  }
  LOG(LM_STD, Fmtmsg("执行sql[%s]影响记录条数:[%d]", sSql, sqlite3_changes(sqlite_db)), __func__)

	sqlite3_close(sqlite_db);
/*解锁*/
  if ( SemV(pGSA_SPA->semSQLITE) ==FAIL )
  {
       LOG(LM_STD, Fmtmsg("SYS_COMP:%d, 操作系统数据库失败,SemV Err,[%d][%s]", 
           MID_SYS_COMP_2080, errno,strerror(errno)), __func__);
    	 return COMPSTATUS_FAIL;
  }	  
	return 0;
}

int main()
{
	return 0;
}
