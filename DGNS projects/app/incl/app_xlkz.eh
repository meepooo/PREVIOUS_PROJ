/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合服务平台(GAPS)项目
版    本:V2.1
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:DB2
文 件 名:APP_XLKZ.eh
文件描述:APP_XLKZ;结构定义数据库开发嵌C头文件
项 目 组:金融.产品三部
程 序 员:SC
发布时间:2011-5-27 11:00:48 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:APP_XLKZ (序列控制表)
说    明:序列控制表
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __APP_XLKZ_EH__
#define __APP_XLKZ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif

EXEC SQL BEGIN DECLARE SECTION;
struct TDB_APP_XLKZ
{
  char   pkey[20+1];              /*KEY值*/
              /**/
  sqlint32    curr_value;              /*当前值*/
              /**/
  sqlint32    pinc;              /*步进值*/
              /**/
  sqlint32    min_value;              /*最小值*/
              /**/
  sqlint32    max_value;              /*最大值*/
              /**/
  char   remark[40+1];              /*说明*/
              /**/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
}sdb_app_xlkz;
EXEC SQL END DECLARE SECTION;
#endif  /*end of __APP_XLKZ_EH__*/
