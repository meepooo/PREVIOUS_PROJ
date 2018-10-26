/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_sbxx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_sbxx (电信诈骗上报信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_SBXX_H__
#define __GAB_DXZP_SBXX_H__
typedef struct TDB_GAB_DXZP_SBXX
{
	char   csbwlsh[53+1];  /*传输报文流水号*/
		/**/
	char   jybm[6+1];  /*交易编码*/
		/**/
	char   sbpch[36+1];  /*上报批次号*/
		/**/
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*请求单标识 请求单流水号，用于标识查控请求单*/
	char   sqjgdm[12+1];  /*申请机构代码*/
		/*申请机构代码 公安机关机构编码*/
	char   mbjgdm[12+1];  /*目标机构代码*/
		/*目标机构代码 将协助请求单发送给目标机构的代码*/
	char   ywlx[4+1];  /*业务类型*/
		/*业务类型*/
	char   sjms[500+1];  /*事件描述*/
		/**/
	char   sbjgdm[16+1];  /*上报机构代码*/
		/**/
	char   sbjgmc[200+1];  /*上报机构名称*/
		/**/
	char   jbrxm[100+1];  /*经办人姓名*/
		/**/
	char   jbrdh[30+1];  /*经办人电话*/
		/**/
	char   ywrq[8+1];  /*业务日期*/
		/*业务日期*/
	char   ywlsh[32+1];  /*业务流水号*/
		/*业务流水号*/
	char   jbjg[16+1];  /*经办机构*/
		/*经办机构*/
	char   jbgy[16+1];  /*经办柜员*/
		/*经办柜员*/
	char   clrq[8+1];  /*处理日期*/
		/**/
	char   clsj[6+1];  /*处理时间*/
		/**/
	long   sbjls;  /*上报记录数*/
		/**/
	char   sbjg[2+1];  /*上报结果*/
		/**/
	char   respcode[8+1];  /*响应码*/
		/**/
	char   respmsg[200+1];  /*响应信息*/
		/**/
	char   zwrq[8+1];  /*gaps日期*/
		/*gaps日期*/
	char   systime[6+1];  /*gaps时间*/
		/*gaps时间*/
	char   zhqzlsh[16+1];  /*gaps流水号*/
		/*gaps流水号*/
	char   sbpcwjm[254+1];  /*上报批次文件名*/
		/**/
	char   by1[30+1];  /*备用1*/
		/**/
	char   by2[254+1];  /*备用2*/
		/**/
	char   by3[254+1];  /*备用3*/
		/**/

}GAB_DXZP_SBXX;

#define SD_DATA  GAB_DXZP_SBXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  sqjgdm, 0),\
	DEFSDMEMBER(T_STRING,  mbjgdm, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  sjms, 0),\
	DEFSDMEMBER(T_STRING,  sbjgdm, 0),\
	DEFSDMEMBER(T_STRING,  sbjgmc, 0),\
	DEFSDMEMBER(T_STRING,  jbrxm, 0),\
	DEFSDMEMBER(T_STRING,  jbrdh, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  jbjg, 0),\
	DEFSDMEMBER(T_STRING,  jbgy, 0),\
	DEFSDMEMBER(T_STRING,  clrq, 0),\
	DEFSDMEMBER(T_STRING,  clsj, 0),\
	DEFSDMEMBER(T_LONG,  sbjls, 0),\
	DEFSDMEMBER(T_STRING,  sbjg, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  zhqzlsh, 0),\
	DEFSDMEMBER(T_STRING,  sbpcwjm, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SBXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SBXX_H__*/
