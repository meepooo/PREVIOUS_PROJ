/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_hhmd.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_hhmd (电信诈骗黑灰名单表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_HHMD_H__
#define __GAB_DXZP_HHMD_H__
typedef struct TDB_GAB_DXZP_HHMD
{
	char   mdlx[1+1];  /*名单类型*/
		/*名单类型 0-账号名单 1-证件名单*/
	char   mdjz[64+1];  /*名单键值*/
		/*名单键值 Hash值  ChinaFinancialCertificationAuthority_原始值,经使用SM3算法进行哈希得到的值,如为证照号码的 01_000000000000000000，目前只支持身份证*/
	char   mdly[1+1];  /*名单来源*/
		/*名单来源 1-公安*/
	char   ajlx[4+1];  /*案件类型*/
		/*案件类型 1-电信诈骗*/
	char   xm[100+1];  /*姓名*/
		/*名单所对应的姓名*/
	char   mdjb[1+1];  /*名单级别*/
		/*名单级别 0-白名单 1-黑名单 2-灰名单 */
	char   gxrq[8+1];  /*更新日期*/
		/*更新日期*/
	char   gxsj[6+1];  /*更新时间*/
		/*更新时间*/
	char   by1[30+1];  /*备用1*/
		/**/
	char   by2[254+1];  /*备用2*/
		/**/
	char   by3[254+1];  /*备用3*/
		/**/

}GAB_DXZP_HHMD;

#define SD_DATA  GAB_DXZP_HHMD
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mdlx, 0),\
	DEFSDMEMBER(T_STRING,  mdjz, 0),\
	DEFSDMEMBER(T_STRING,  mdly, 0),\
	DEFSDMEMBER(T_STRING,  ajlx, 0),\
	DEFSDMEMBER(T_STRING,  xm, 0),\
	DEFSDMEMBER(T_STRING,  mdjb, 0),\
	DEFSDMEMBER(T_STRING,  gxrq, 0),\
	DEFSDMEMBER(T_STRING,  gxsj, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_HHMD)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_HHMD_H__*/
