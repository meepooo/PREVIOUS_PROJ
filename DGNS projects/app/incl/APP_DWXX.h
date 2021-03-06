/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_DWXX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_DWXX (单位信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_DWXX_H__
#define __APP_DWXX_H__
typedef struct TDB_APP_DWXX
{
  char   dwbh[16+1];              /*单位编号*/
              /**/
  char   dwmc[80+1];              /*单位名称*/
              /*单位名称*/
  char   dwzjlx[2+1];              /*单位证件类型*/
              /*单位证件类型 见数据字典 KEY=K_DWZJLX*/
  char   dwzjhm[32+1];              /*单位证件号码*/
              /*单位证件号码*/
  char   dwlxr[16+1];              /*单位联系人名称*/
              /*单位联系人名称*/
  char   dwlxrdh[16+1];              /*单位联系人电话*/
              /*单位联系人电话*/
  char   dwdz[60+1];              /*单位联系地址*/
              /*单位联系地址*/
  char   dwemail[32+1];              /*单位联系email*/
              /*单位联系email*/
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
              /*状态 0 正� X删除*/
}APP_DWXX;

#define SD_DATA  APP_DWXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  dwmc, 0),\
	DEFSDMEMBER(T_STRING,  dwzjlx, 0),\
	DEFSDMEMBER(T_STRING,  dwzjhm, 0),\
	DEFSDMEMBER(T_STRING,  dwlxr, 0),\
	DEFSDMEMBER(T_STRING,  dwlxrdh, 0),\
	DEFSDMEMBER(T_STRING,  dwdz, 0),\
	DEFSDMEMBER(T_STRING,  dwemail, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  zt, 0)


	DECLAREFIELDS(SD_APP_DWXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_DWXX_H__*/
