/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_KHXX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_KHXX (客户信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_KHXX_H__
#define __APP_KHXX_H__
typedef struct TDB_APP_KHXX
{
  char   khbh[16+1];              /*客户编号*/
              /*客户编号 由序列 K_KHBH 生成*/
  char   khxm[80+1];              /*客户姓名*/
              /*客户姓名*/
  char   ywxm[40+1];              /*英文姓名*/
              /*英文姓名*/
  char   bm[20+1];              /*别名*/
              /*别名*/
  char   khlx[1+1];              /*客户类型*/
              /*客户类型 见数据字典KEY=K_KHLX*/
  char   zjkhbh[32+1];              /*主机客户编号*/
              /*主机客户编号*/
  char   zjlx[3+1];              /*证件类型*/
              /*证件类型 见数据字典KEY=K_ZJLX*/
  char   zjhm[32+1];              /*证件号码*/
              /*证件号码*/
  char   csny[8+1];              /*出生年月*/
              /*出生年月*/
  char   sex[1+1];              /*性别*/
              /*性别 见数据字典KEY=K_SEX*/
  char   gj[3+1];              /*国籍*/
              /*国籍*/
  char   hk[60+1];              /*户口*/
              /*户口*/
  char   hyzk[1+1];              /*婚姻状况*/
              /*婚姻状况 0未婚 1已婚 2离婚 9未知*/
  char   jycd[1+1];              /*教育程度*/
              /*教育程度 见数据字典KEY=K_JYCD*/
  char   zy[3+1];              /*职业*/
              /*职业  根据国家标准*/
  char   zw[20+1];              /*职务*/
              /*职务*/
  double  srqk;              /*收入情况年*/
              /*收入情况年*/
  char   gsdz[60+1];              /*公司地址*/
              /*公司地址*/
  char   gsyb[6+1];              /*公司邮编*/
              /*公司邮编*/
  char   gsdh[16+1];              /*公司电话*/
              /*公司电话*/
  char   zzdz[60+1];              /*住宅地址*/
              /*住宅地址*/
  char   zzyb[6+1];              /*住宅邮编*/
              /*住宅邮编*/
  char   zzdh[16+1];              /*住宅电话*/
              /*住宅电话*/
  char   sjhm[16+1];              /*手机号码*/
              /*手机号码*/
  char   memail[32+1];              /*电子邮箱*/
              /*电子邮箱*/
  char   yjdzlx[1+1];              /*邮寄地址类型*/
              /*邮寄地址类型 1公司地址2住宅地址*/
  char   bz[1+1];              /*标志*/
              /*标志 0正常 1无效 X删除*/
}APP_KHXX;

#define SD_DATA  APP_KHXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  khbh, 0),\
	DEFSDMEMBER(T_STRING,  khxm, 0),\
	DEFSDMEMBER(T_STRING,  ywxm, 0),\
	DEFSDMEMBER(T_STRING,  bm, 0),\
	DEFSDMEMBER(T_STRING,  khlx, 0),\
	DEFSDMEMBER(T_STRING,  zjkhbh, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  csny, 0),\
	DEFSDMEMBER(T_STRING,  sex, 0),\
	DEFSDMEMBER(T_STRING,  gj, 0),\
	DEFSDMEMBER(T_STRING,  hk, 0),\
	DEFSDMEMBER(T_STRING,  hyzk, 0),\
	DEFSDMEMBER(T_STRING,  jycd, 0),\
	DEFSDMEMBER(T_STRING,  zy, 0),\
	DEFSDMEMBER(T_STRING,  zw, 0),\
	DEFSDMEMBER(T_DOUBLE,  srqk, 2),\
	DEFSDMEMBER(T_STRING,  gsdz, 0),\
	DEFSDMEMBER(T_STRING,  gsyb, 0),\
	DEFSDMEMBER(T_STRING,  gsdh, 0),\
	DEFSDMEMBER(T_STRING,  zzdz, 0),\
	DEFSDMEMBER(T_STRING,  zzyb, 0),\
	DEFSDMEMBER(T_STRING,  zzdh, 0),\
	DEFSDMEMBER(T_STRING,  sjhm, 0),\
	DEFSDMEMBER(T_STRING,  memail, 0),\
	DEFSDMEMBER(T_STRING,  yjdzlx, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0)


	DECLAREFIELDS(SD_APP_KHXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_KHXX_H__*/

