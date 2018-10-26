/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V4.1.00
操作系统:AIX/Linux/HP-UX
文 件 名:SSERIAL.c
文件描述:插流水/更新流水/流水报表相关组件集
项 目 组:GAPS研发组
程 序 员:[Tianhc]
发布日期:2009-6-16 15:19:57
修    订:
修改日期:
****************************************************************************/
/*
   说明信息：
      在ASPKV4环境下，推荐使用系统提供的DCI模式访问数据库；
      即：不使用数据库自带的EXEC SQL嵌C的开发模式，而是通过已封装的DCI函数操作数据库
      本代码即为使用DCI的一个样例，包括：
       insert(结构模式)/update(结构模式)/select(游标模式)
*/
/****************************************************************************
修改记录
修改日期:2009-8-1 9:06:43
修 改 人:Tianhc
修改内容:
   对代码进行发布前整理
Tianhc 2009-9-24 14:04:28
  V4.0.01
    原版本在出错时未置响应码/响应信息
****************************************************************************/



#include "gaps_head.h"
#include "ywty_drls.h"
#include "DCI.h"

static char SSERIAL_c[] = "{$Id: SSERIAL.c 2219 2013-01-25 07:20:11Z tianhc $}";

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "4.0.02"

int ShowSocompVersion(char *sinfo, int isize)
{
  char sversion[] = "<?xml version=\"1.0\" encoding=\"GB2312\"?>\
     <root>\
      <soname>SSERIAL.so</soname>\
      <sosrcname>SSERIAL.c</sosrcname>\
      <sonote>流水表相关组件集合</sonote>\
      <version>\
        <rec ver=\"4.0.00\" modify=\"2009-8-1 9:14:20\" programer=\"Tianhc Chendh\" filesize=\"81519\">ASPKV4发布前整理</rec>\
        <rec ver=\"4.0.02\" modify=\"2012/10/17 10:34:30\" programer=\"Tianhc\" filesize=\"22539\">修改Update时条件错误</rec>\
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
组件函数名称: SERIAL_InsertCurrent
组件名称: SERIAL_InsertCurrent
组件功能:
     调用DCI接口，向ywty_drls表插入一条记录
组件参数:
  序号 参数名称   资源类别     缺省值   是否可空  参数说明


组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: Turandot@ASPKV4
程 序 员:
发布日期: 2009-8-1 9:15:25
修改日期:
参数使用示例:
************************************************************************/
IRESULT SERIAL_InsertCurrent(HXMLTREE lXmlhandle)
{

  int iParas;
  int ret;
  YWTY_DRLS Sywty_drls;
  char sBuf[300];
  char errmsg[512];

  fpub_InitSoComp(lXmlhandle);

  LOG(LM_STD, Fmtmsg("插入当日流水...."), "INFO")
  memset(&Sywty_drls, 0, sizeof(Sywty_drls));
  /*帐务日期*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_HARDGETXML("/pub/zwrq", sBuf)
  trim(sBuf);
  pstrcopy(Sywty_drls.zwrq, sBuf, sizeof(Sywty_drls.zwrq));
  /*综合前置流水号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_HARDGETXML("/pub/zhqzlsh", sBuf)
  Sywty_drls.zhqzlsh = atoi(sBuf);
  /*中心流水号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/zxlsh", sBuf)
  pstrcopy(Sywty_drls.zxlsh, sBuf, sizeof(Sywty_drls.zxlsh));
  /*第三方帐务日期*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/dsfzwrq", sBuf)
  pstrcopy(Sywty_drls.dsfzwrq, sBuf, sizeof(Sywty_drls.dsfzwrq));
  /*第三方流水号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/dsflsh", sBuf)
  pstrcopy(Sywty_drls.dsflsh, sBuf, sizeof(Sywty_drls.dsflsh));
  /*交易跟踪号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jygzh", sBuf)
  pstrcopy(Sywty_drls.jygzh, sBuf, sizeof(Sywty_drls.jygzh));
  /*综合前置流水号2*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/zhqzlsh2", sBuf)
  Sywty_drls.zhqzlsh2 = atoi(sBuf);
  /*授权码*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/sqm", sBuf)
  pstrcopy(Sywty_drls.sqm, sBuf, sizeof(Sywty_drls.sqm));
  /*授权操作员*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/sqczy", sBuf)
  pstrcopy(Sywty_drls.sqczy, sBuf, sizeof(Sywty_drls.sqczy));
  /*上级机构*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/sjjgbh", sBuf)
  pstrcopy(Sywty_drls.sjjgbh, sBuf, sizeof(Sywty_drls.sjjgbh));
  /*机构编号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jgbh", sBuf)
  pstrcopy(Sywty_drls.jgbh, sBuf, sizeof(Sywty_drls.jgbh));
  /*内部机构标识*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/nbjgbs", sBuf)
  pstrcopy(Sywty_drls.nbjgbs, sBuf, sizeof(Sywty_drls.nbjgbs));
  /*委托机构编号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/wtjgbh", sBuf)
  pstrcopy(Sywty_drls.wtjgbh, sBuf, sizeof(Sywty_drls.wtjgbh));
  /*委托内部机构标识*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/wtnbjgbs", sBuf)
  pstrcopy(Sywty_drls.wtnbjgbs, sBuf, sizeof(Sywty_drls.wtnbjgbs));
  /*操作员号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/czyh", sBuf)
  pstrcopy(Sywty_drls.czyh, sBuf, sizeof(Sywty_drls.czyh));
  /*节点编号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jdbh", sBuf)
  pstrcopy(Sywty_drls.jdbh, sBuf, sizeof(Sywty_drls.jdbh));
  /*交易渠道*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/sys/apps|1/appcode", sBuf); /*Tian 2003-9-10 19:30*/
  pstrcopy(Sywty_drls.jyqd, sBuf, sizeof(Sywty_drls.jyqd));
  /*交易日期*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/sys/sysdate", sBuf)
  pstrcopy(Sywty_drls.jyrq, sBuf, sizeof(Sywty_drls.jyrq));
  /*交易时间*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/sys/systime", sBuf)
  pstrcopy(Sywty_drls.jysj, sBuf, sizeof(Sywty_drls.jysj));
  /*交易代码*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jydm", sBuf)
  pstrcopy(Sywty_drls.jydm, sBuf, sizeof(Sywty_drls.jydm));
  /*交易名称*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jymc", sBuf)
  pstrcopy(Sywty_drls.jymc, sBuf, sizeof(Sywty_drls.jymc));
  /*业务代码*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/ywdm", sBuf)
  pstrcopy(Sywty_drls.ywdm, sBuf, sizeof(Sywty_drls.ywdm));
  /*项目代码*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/xmdh", sBuf)
  pstrcopy(Sywty_drls.xmdh, sBuf, sizeof(Sywty_drls.xmdh));
  /*客户名称*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/khmc", sBuf)
  pstrcopy(Sywty_drls.khmc, sBuf, sizeof(Sywty_drls.khmc));
  /*交易账号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jyzh", sBuf)
  pstrcopy(Sywty_drls.jyzh, sBuf, sizeof(Sywty_drls.jyzh));
  /*帐户种类*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/zhzl", sBuf)
  pstrcopy(Sywty_drls.zhzl, sBuf, sizeof(Sywty_drls.zhzl));
  /*交易账号2*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jyzh2", sBuf)
  pstrcopy(Sywty_drls.jyzh2, sBuf, sizeof(Sywty_drls.jyzh2));
  /*帐户种类2*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/zhzl2", sBuf)
  pstrcopy(Sywty_drls.zhzl2, sBuf, sizeof(Sywty_drls.zhzl2));
  /*帐户机构2*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/zhjg2", sBuf)
  pstrcopy(Sywty_drls.zhjg2, sBuf, sizeof(Sywty_drls.zhjg2));
  /*客户号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/khh", sBuf)
  pstrcopy(Sywty_drls.khh, sBuf, sizeof(Sywty_drls.khh));
  /*用户号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/yhh", sBuf)
  pstrcopy(Sywty_drls.yhh, sBuf, sizeof(Sywty_drls.yhh));
  /*币种号*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/bzh", sBuf)
  pstrcopy(Sywty_drls.bzh, sBuf, sizeof(Sywty_drls.bzh));
  /*交易金额*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jyje", sBuf)
  Sywty_drls.jyje = atof(sBuf);
  /*手续费*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/sxf", sBuf)
  Sywty_drls.sxf = atof(sBuf);
  /*工本费*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/gbf", sBuf)
  Sywty_drls.gbf = atof(sBuf);
  /*滞纳金*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/znj", sBuf)
  Sywty_drls.znj = atof(sBuf);
  /*交易状态*/
  Sywty_drls.jyzt[0] = '9' ;/*处理*/
  /*响应码*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML(XMLNM_RESPCODE, sBuf)
  pstrcopy(Sywty_drls.xym, sBuf, sizeof(Sywty_drls.xym));
  /*响应信息*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML(XMLNM_RESPMSG, sBuf)
  pstrcopy(Sywty_drls.xyxx, sBuf, sizeof(Sywty_drls.xyxx));
  /*交易方式*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jyfs", sBuf)
  pstrcopy(Sywty_drls.jyfs, sBuf, sizeof(Sywty_drls.jyfs));
  /*借贷标志*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jdbz", sBuf)
  pstrcopy(Sywty_drls.jdbz, sBuf, sizeof(Sywty_drls.jdbz));
  /*记帐标志*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/jzbz", sBuf)
  pstrcopy(Sywty_drls.jzbz, sBuf, sizeof(Sywty_drls.jzbz));
  /*清算标志*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/qsbz", sBuf)
  pstrcopy(Sywty_drls.qsbz, sBuf, sizeof(Sywty_drls.qsbz));
  /*归档标志*/
  COMP_SOFTGETXML("/pub/gdbz", sBuf)
  pstrcopy(Sywty_drls.gdbz, sBuf, sizeof(Sywty_drls.gdbz));
  /*交易种类*/
  COMP_SOFTGETXML("/pub/jyzl", sBuf)
  pstrcopy(Sywty_drls.jyzl, sBuf, sizeof(Sywty_drls.jyzl));
  /*扩展标志*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/kzbz", sBuf)
  pstrcopy(Sywty_drls.kzbz, sBuf, sizeof(Sywty_drls.kzbz));
  /*外部帐务标识*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/wbzwbs", sBuf)
  pstrcopy(Sywty_drls.wbzwbs, sBuf, sizeof(Sywty_drls.wbzwbs));
  /*备用*/
  memset(sBuf, 0, sizeof(sBuf));
  COMP_SOFTGETXML("/pub/byzd", sBuf)
  pstrcopy(Sywty_drls.byzd, sBuf, sizeof(Sywty_drls.byzd));

  ret = DBInsert("ywty_drls", SD_YWTY_DRLS, NUMELE(SD_YWTY_DRLS), &Sywty_drls, errmsg);
  if (ret < 0)
  {/*插入当日流水失败*/
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("数据异常：插入数据库语句失败[%s]", errmsg),
           fpub_GetCompname(lXmlhandle))
  }

  if (DCICommit() == -1)
  {
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("数据异常：提交事务失败[%s]", DCILastError()),
           fpub_GetCompname(lXmlhandle))
  }

  LOG(LM_STD, Fmtmsg("插入成功"), "INFO")

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SERIAL_UpdateCurrent
组件名称: SERIAL_UpdateCurrent
组件功能:
   根据当前XML树内容，调用DCI接口，更新当前的流水表中当前记录
组件参数:
  序号 参数名称   资源类别     缺省值   是否可空  参数说明
  1    交易状态   解析字符串   0         N        根据ywty_drls表结构中的定义

组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: Turandot@ASPKV4
程 序 员:
发布日期: 2009-8-1 9:15:25
修改日期:
参数使用示例:
************************************************************************/
IRESULT SERIAL_UpdateCurrent(HXMLTREE lXmlhandle)
{
  int  iParas;
  int  ret;
  char sJyzt[50];
  char sBuf[254];
  char sCondition[128];
  char errmsg[512];
  YWTY_DRLS Sywty_drls;

  fpub_InitSoComp(lXmlhandle);
  COMP_PARACOUNTCHK(1)
  COMP_GETPARSEPARAS(1, sJyzt, "交易状态")

  LOG(LM_STD, Fmtmsg("  -->更新当日流水,状态[%s]...", sJyzt), "INFO")


  /*获取组件参数  --S*/

  /*获取组件参数  --E*/
  /*完成功能  --S*/
  memset(&Sywty_drls, 0, sizeof(Sywty_drls));

  /*帐务日期*/
  COMP_HARDGETXML("/pub/zwrq", sBuf)
  pstrcopy(Sywty_drls.zwrq, sBuf, sizeof(Sywty_drls.zwrq));
  /*综合前置流水号*/
  COMP_HARDGETXML("/pub/zhqzlsh", sBuf)
  Sywty_drls.zhqzlsh = atoi(sBuf);
  /*中心流水号*/
  COMP_SOFTGETXML("/pub/zxlsh", sBuf)
  pstrcopy(Sywty_drls.zxlsh, sBuf, sizeof(Sywty_drls.zxlsh));
  /*第三方帐务日期*/
  COMP_SOFTGETXML("/pub/dsfzwrq", sBuf)
  pstrcopy(Sywty_drls.dsfzwrq, sBuf, sizeof(Sywty_drls.dsfzwrq));
  /*第三方流水号*/
  COMP_SOFTGETXML("/pub/dsflsh", sBuf)
  pstrcopy(Sywty_drls.dsflsh, sBuf, sizeof(Sywty_drls.dsflsh));
  /*交易跟踪号*/
  COMP_SOFTGETXML("/pub/jygzh", sBuf)
  pstrcopy(Sywty_drls.jygzh, sBuf, sizeof(Sywty_drls.jygzh));
  /*综合前置流水号2*/
  COMP_SOFTGETXML("/pub/zhqzlsh2", sBuf)
  Sywty_drls.zhqzlsh2 = atoi(sBuf);
  /*授权码*/
  COMP_SOFTGETXML("/pub/sqm", sBuf)
  pstrcopy(Sywty_drls.sqm, sBuf, sizeof(Sywty_drls.sqm));
  /*授权操作员*/
  COMP_SOFTGETXML("/pub/sqczy", sBuf)
  pstrcopy(Sywty_drls.sqczy, sBuf, sizeof(Sywty_drls.sqczy));
  /*上级机构*/
  COMP_SOFTGETXML("/pub/sjjgbh", sBuf)
  pstrcopy(Sywty_drls.sjjgbh, sBuf, sizeof(Sywty_drls.sjjgbh));
  /*机构编号*/
  COMP_SOFTGETXML("/pub/jgbh", sBuf)
  pstrcopy(Sywty_drls.jgbh, sBuf, sizeof(Sywty_drls.jgbh));
  /*内部机构标识*/
  COMP_SOFTGETXML("/pub/nbjgbs", sBuf)
  pstrcopy(Sywty_drls.nbjgbs, sBuf, sizeof(Sywty_drls.nbjgbs));
  /*委托机构编号*/
  COMP_SOFTGETXML("/pub/wtjgbh", sBuf)
  pstrcopy(Sywty_drls.wtjgbh, sBuf, sizeof(Sywty_drls.wtjgbh));
  /*委托内部机构标识*/
  COMP_SOFTGETXML("/pub/wtnbjgbs", sBuf)
  pstrcopy(Sywty_drls.wtnbjgbs, sBuf, sizeof(Sywty_drls.wtnbjgbs));
  /*操作员号*/
  COMP_SOFTGETXML("/pub/czyh", sBuf)
  pstrcopy(Sywty_drls.czyh, sBuf, sizeof(Sywty_drls.czyh));
  /*节点编号*/
  COMP_SOFTGETXML("/pub/jdbh", sBuf)
  pstrcopy(Sywty_drls.jdbh, sBuf, sizeof(Sywty_drls.jdbh));
  /*交易渠道*/
  COMP_SOFTGETXML("/sys/apps|1/appcode", sBuf); /*Tian 2003-9-10 19:30*/
  pstrcopy(Sywty_drls.jyqd, strtolower(sBuf), sizeof(Sywty_drls.jyqd));
  /*交易日期*/
  COMP_SOFTGETXML("/sys/sysdate", sBuf)
  pstrcopy(Sywty_drls.jyrq, sBuf, sizeof(Sywty_drls.jyrq));
  /*交易时间*/
  COMP_SOFTGETXML("/sys/systime", sBuf)
  pstrcopy(Sywty_drls.jysj, sBuf, sizeof(Sywty_drls.jysj));
  /*交易代码*/
  COMP_SOFTGETXML("/pub/jydm", sBuf)
  pstrcopy(Sywty_drls.jydm, sBuf, sizeof(Sywty_drls.jydm));
  /*交易名称*/
  COMP_SOFTGETXML("/pub/jymc", sBuf)
  pstrcopy(Sywty_drls.jymc, sBuf, sizeof(Sywty_drls.jymc));
  /*业务代码*/
  COMP_SOFTGETXML("/pub/ywdm", sBuf)
  pstrcopy(Sywty_drls.ywdm, sBuf, sizeof(Sywty_drls.ywdm));
  /*项目代码*/
  COMP_SOFTGETXML("/pub/xmdh", sBuf)
  pstrcopy(Sywty_drls.xmdh, sBuf, sizeof(Sywty_drls.xmdh));
  /*客户名称*/
  COMP_SOFTGETXML("/pub/khmc", sBuf)
  pstrcopy(Sywty_drls.khmc, sBuf, sizeof(Sywty_drls.khmc));
  /*交易账号*/
  COMP_SOFTGETXML("/pub/jyzh", sBuf)
  pstrcopy(Sywty_drls.jyzh, sBuf, sizeof(Sywty_drls.jyzh));
  /*帐户种类*/
  COMP_SOFTGETXML("/pub/zhzl", sBuf)
  pstrcopy(Sywty_drls.zhzl, sBuf, sizeof(Sywty_drls.zhzl));
  /*交易账号2*/
  COMP_SOFTGETXML("/pub/jyzh2", sBuf)
  pstrcopy(Sywty_drls.jyzh2, sBuf, sizeof(Sywty_drls.jyzh2));
  /*帐户种类2*/
  COMP_SOFTGETXML("/pub/zhzl2", sBuf)
  pstrcopy(Sywty_drls.zhzl2, sBuf, sizeof(Sywty_drls.zhzl2));
  /*帐户机构2*/
  COMP_SOFTGETXML("/pub/zhjg2", sBuf)
  pstrcopy(Sywty_drls.zhjg2, sBuf, sizeof(Sywty_drls.zhjg2));
  /*客户号*/
  COMP_SOFTGETXML("/pub/khh", sBuf)
  pstrcopy(Sywty_drls.khh, sBuf, sizeof(Sywty_drls.khh));
  /*用户号*/
  COMP_SOFTGETXML("/pub/yhh", sBuf)
  pstrcopy(Sywty_drls.yhh, sBuf, sizeof(Sywty_drls.yhh));
  /*币种号*/
  COMP_SOFTGETXML("/pub/bzh", sBuf)
  pstrcopy(Sywty_drls.bzh, sBuf, sizeof(Sywty_drls.bzh));
  /*交易金额*/
  COMP_SOFTGETXML("/pub/jyje", sBuf)
  Sywty_drls.jyje = atof(sBuf);
  /*手续费*/
  COMP_SOFTGETXML("/pub/sxf", sBuf)
  Sywty_drls.sxf = atof(sBuf);
  /*工本费*/
  COMP_SOFTGETXML("/pub/gbf", sBuf)
  Sywty_drls.gbf = atof(sBuf);
  /*滞纳金*/
  COMP_SOFTGETXML("/pub/znj", sBuf)
  Sywty_drls.znj = atof(sBuf);

  /*交易状态*/
  pstrcopy(Sywty_drls.jyzt, sJyzt, sizeof(Sywty_drls.jyzt));

  /*响应码*/
  COMP_SOFTGETXML(XMLNM_RESPCODE, sBuf)
  pstrcopy(Sywty_drls.xym, sBuf, sizeof(Sywty_drls.xym));
  /*响应信息*/
  COMP_SOFTGETXML(XMLNM_RESPMSG, sBuf)
  pstrcopy(Sywty_drls.xyxx, sBuf, sizeof(Sywty_drls.xyxx));
  /*交易方式*/
  COMP_SOFTGETXML("/pub/jyfs", sBuf)
  pstrcopy(Sywty_drls.jyfs, sBuf, sizeof(Sywty_drls.jyfs));
  /*借贷标志*/
  COMP_SOFTGETXML("/pub/jdbz", sBuf)
  pstrcopy(Sywty_drls.jdbz, sBuf, sizeof(Sywty_drls.jdbz));
  /*归档标志*/
  COMP_SOFTGETXML("/pub/gdbz", sBuf)
  pstrcopy(Sywty_drls.gdbz, sBuf, sizeof(Sywty_drls.gdbz));
  /*交易种类*/
  COMP_SOFTGETXML("/pub/jyzl", sBuf)
  pstrcopy(Sywty_drls.jyzl, sBuf, sizeof(Sywty_drls.jyzl));
  /*记帐标志*/
  COMP_SOFTGETXML("/pub/jzbz", sBuf)
  pstrcopy(Sywty_drls.jzbz, sBuf, sizeof(Sywty_drls.jzbz));
  /*清算标志*/
  COMP_SOFTGETXML("/pub/qsbz", sBuf)
  pstrcopy(Sywty_drls.qsbz, sBuf, sizeof(Sywty_drls.qsbz));
  /*扩展标志*/
  COMP_SOFTGETXML("/pub/kzbz", sBuf)
  pstrcopy(Sywty_drls.kzbz, sBuf, sizeof(Sywty_drls.kzbz));
  /*外部帐务标识*/
  COMP_SOFTGETXML("/pub/wbzwbs", sBuf)
  pstrcopy(Sywty_drls.wbzwbs, sBuf, sizeof(Sywty_drls.wbzwbs));
  /*备用*/
  COMP_SOFTGETXML("/pub/byzd", sBuf)
  pstrcopy(Sywty_drls.byzd, sBuf, sizeof(Sywty_drls.byzd));

  /*DEMO错误，zhqzlsh是int型而非string型!*/
  sprintf(sCondition, "zwrq = '%s' and zhqzlsh = %d", Sywty_drls.zwrq, Sywty_drls.zhqzlsh);

  ret =  DBUpdate("ywty_drls", SD_YWTY_DRLS, NUMELE(SD_YWTY_DRLS), &Sywty_drls, sCondition, errmsg);
  if (ret < 0)
  {/*插入当日流水失败*/
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("数据异常：插入数据库语句失败[%s]", errmsg),
           fpub_GetCompname(lXmlhandle))
  }

  if (DCICommit() == -1)
  {
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("数据异常：提交事务失败[%s]", DCILastError()),
           fpub_GetCompname(lXmlhandle))
  }

  LOG(LM_STD, Fmtmsg("更新成功"), "INFO")
  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

  return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SERIAL_ReportToFile
组件名称: SERIAL_ReportToFile
组件功能:
   生成一个简单报表的样例
   指定条件下的记录，全部记录到文件中，类似unload功能

组件参数:
  序号 参数名称   资源类别     缺省值   是否可空  参数说明


组件结果状态:
  结果状态码         结果说明
  缺省

日志信息:
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:

项 目 组: Turandot@ASPKV4
程 序 员:
发布日期: 2009-8-1 9:15:25
修改日期:
参数使用示例:
************************************************************************/
IRESULT SERIAL_ReportToFile(HXMLTREE lXmlhandle)
{
  int  iParas;
  int  rowcount = 0;
  int rc;
  char sDeli[256];
  char sFile[256];
  char sCondition[512];
  char sSql[1024];
  char errmsg[512];
  FILE* fp;
  CURSOR cur;
  YWTY_DRLS Sywty_drls;

  fpub_InitSoComp(lXmlhandle);
  COMP_PARACOUNTCHK(3)
  COMP_GETPARSEPARAS(1, sFile,      "文件名")
  COMP_GETPARSEPARAS(2, sCondition, "条件")
  COMP_GETPARSEPARAS(3, sDeli,      "分隔符")

  LOG(LM_STD, Fmtmsg("  -->导出到文件[%s],条件[%s]分隔符[%s]...", sFile, sCondition, sDeli), "INFO")


  /*获取组件参数  --S*/

  /*获取组件参数  --E*/
  /*完成功能  --S*/
  memset(&Sywty_drls, 0, sizeof(Sywty_drls));

  trim(sCondition);
  if (strlen(sCondition) > 0)
    sprintf(sSql, "select * from ywty_drls where %s", sCondition);
  else
    strcpy(sSql, "select * from ywty_drls");

  if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
  {
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("数据异常：准备数据库语句失败[%s]", DCILastError()),
           fpub_GetCompname(lXmlhandle))
  }


  if (DCIExecute(cur) == -1)
  {
    DCIFreeCursor(cur);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("数据异常：执行数据库语句失败[%s]", DCILastError()),
           fpub_GetCompname(lXmlhandle))
  }

  fp = fopen(sFile, "w");
  if (fp == NULL)
  {
    DCIFreeCursor(cur);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("打开文件失败[%s]", sFile),
           fpub_GetCompname(lXmlhandle))
  }

  while ((rc = DBFetch(cur, SD_YWTY_DRLS, NUMELE(SD_YWTY_DRLS), &Sywty_drls, errmsg)) > 0)
  {
    int i;
    FLD_DESC *pdesc;
    int desc_num = NUMELE(SD_YWTY_DRLS);

    rowcount++;
    for (i = 0, pdesc = SD_YWTY_DRLS; i < desc_num; i++, pdesc++)
    {
      char *pval = (char *) & Sywty_drls + pdesc->offset;
      switch (pdesc->type)
      {
      case TT_CHAR:
      case TT_STRING:
        fprintf(fp, "%s%s", pval, sDeli);
        break;

      case TT_SHORT:
        fprintf(fp, "%d%s", *(int *) pval, sDeli);
        break;
      case TT_LONG:
        fprintf(fp, "%ld%s", *(long *) pval, sDeli);
        break;

      case TT_DOUBLE:
        fprintf(fp, "%lf%s", *(double *) pval, sDeli);
        break;
      default:
        LOG(LM_STD, Fmtmsg("  -->未知的字段类型[%d]...", pdesc->type), "INFO")
        break;
      }
    }
    fprintf(fp, "\n");
  }

  LOG(LM_STD, Fmtmsg(" 导出记录数=%d", rowcount), __func__)
  
  if (rc < 0)
  {
    fclose(fp);
    DCIFreeCursor(cur);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
    LOGRET(-1, LM_STD,
           Fmtmsg("数据异常：获取数据库内容失败[%s]", errmsg),
           fpub_GetCompname(lXmlhandle))
  }
  fclose(fp);
  DCIFreeCursor(cur);
  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

  return COMPRET_SUCC;
}

int main()
{
  return 0;
}
