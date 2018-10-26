/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_smjfj.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_smjfj (电信诈骗扫描件附件表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_SMJFJ_H__
#define __GAB_DXZP_SMJFJ_H__
typedef struct TDB_GAB_DXZP_SMJFJ
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*业务申请编号*/
	long   xh;  /*序号*/
		/*序号*/
	char   wjm[254+1];  /*文件名*/
		/**/
	char   wjdx[12+1];  /*文件大小*/
		/**/
	char   yxjz[36+1];  /*影像健值*/
		/*影像健值*/
	char   zwrq[8+1];  /*gaps日期*/
		/*gaps日期*/
	char   systime[6+1];  /*gaps时间*/
		/*gaps时间*/
	char   by1[30+1];  /*备用1*/
		/*备用1*/
	char   by2[254+1];  /*备用2*/
		/*备用2*/
	char   by3[254+1];  /*备用3*/
		/*备用3*/

}GAB_DXZP_SMJFJ;

#define SD_DATA  GAB_DXZP_SMJFJ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  xh, 0),\
	DEFSDMEMBER(T_STRING,  wjm, 0),\
	DEFSDMEMBER(T_STRING,  wjdx, 0),\
	DEFSDMEMBER(T_STRING,  yxjz, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SMJFJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SMJFJ_H__*/
