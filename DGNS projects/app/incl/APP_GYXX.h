/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_GYXX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_GYXX (柜员信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_GYXX_H__
#define __APP_GYXX_H__
typedef struct TDB_APP_GYXX
{
  char   gyh[16+1];              /*柜员号*/
              /*柜员号*/
  char   jgbh[16+1];              /*机构编号*/
              /*机构编号*/
  char   mm[32+1];              /*柜员密码*/
              /*柜员密码*/
  char   gyjb[2+1];              /*柜员级别*/
              /*柜员级别*/
  char   gygw[32+1];              /*柜员岗位*/
              /*柜员岗位*/
  char   gymc[16+1];              /*柜员名称*/
              /*柜员名称*/
  char   email[32+1];              /*email*/
              /*email地质*/
  char   fax[16+1];              /*传真*/
              /*传真*/
  char   tel[16+1];              /*电话*/
              /*电话*/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
  char   extfld1[40+1];              /*扩展参数1*/
              /*扩展参数1*/
  char   extfld2[40+1];              /*扩展参数2*/
              /*扩展参数2*/
  char   zt[1+1];              /*状态*/
              /*状态*/
}APP_GYXX;

#define SD_DATA  APP_GYXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  gyh, 0),\
	DEFSDMEMBER(T_STRING,  jgbh, 0),\
	DEFSDMEMBER(T_STRING,  mm, 0),\
	DEFSDMEMBER(T_STRING,  gyjb, 0),\
	DEFSDMEMBER(T_STRING,  gygw, 0),\
	DEFSDMEMBER(T_STRING,  gymc, 0),\
	DEFSDMEMBER(T_STRING,  email, 0),\
	DEFSDMEMBER(T_STRING,  fax, 0),\
	DEFSDMEMBER(T_STRING,  tel, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  zt, 0)


	DECLAREFIELDS(SD_APP_GYXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_GYXX_H__*/
