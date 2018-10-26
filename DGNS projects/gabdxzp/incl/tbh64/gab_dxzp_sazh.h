/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_sazh.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_sazh (电信诈骗涉案账户表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_SAZH_H__
#define __GAB_DXZP_SAZH_H__
typedef struct TDB_GAB_DXZP_SAZH
{
	char   sbpch[36+1];  /*上报批次号*/
		/**/
	long   sbpcxh;  /*上报批次序号*/
		/**/
	char   jybm[6+1];  /*交易编码*/
		/**/
	char   csbwlsh[53+1];  /*传输报文流水号*/
		/**/
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*请求单标识 请求单流水号，用于标识查控请求单*/
	char   ywlx[4+1];  /*业务类型*/
		/*业务类型*/
	char   sjtzm[4+1];  /*事件特征码*/
		/**/
	char   yywsqbh[36+1];  /*原上报编号*/
		/*原上报编号*/
	char   kh[30+1];  /*卡/折号*/
		/**/
	char   zhm[120+1];  /*账户名*/
		/**/
	char   zjlx[2+1];  /*证件类型*/
		/**/
	char   zjhm[30+1];  /*证件号*/
		/**/
	char   lxdh[30+1];  /*联系电话*/
		/**/
	char   txdz[150+1];  /*通讯地址*/
		/**/
	char   yzbm[10+1];  /*邮政编码*/
		/**/
	char   zhlx[30+1];  /*账户类型*/
		/**/
	char   zhzt[10+1];  /*账户状态*/
		/**/
	char   khrq[8+1];  /*开户日期*/
		/**/
	char   xhrq[8+1];  /*销户日期*/
		/**/
	char   kkdd[20+1];  /*开卡地点*/
		/**/
	char   zwrq[8+1];  /*gaps日期*/
		/*gaps日期*/
	char   systime[6+1];  /*gaps时间*/
		/*gaps时间*/
	char   by1[30+1];  /*备用1*/
		/**/
	char   by2[254+1];  /*备用2*/
		/**/
	char   by3[254+1];  /*备用3*/
		/**/

}GAB_DXZP_SAZH;

#define SD_DATA  GAB_DXZP_SAZH
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  sjtzm, 0),\
	DEFSDMEMBER(T_STRING,  yywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  kh, 0),\
	DEFSDMEMBER(T_STRING,  zhm, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  lxdh, 0),\
	DEFSDMEMBER(T_STRING,  txdz, 0),\
	DEFSDMEMBER(T_STRING,  yzbm, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  zhzt, 0),\
	DEFSDMEMBER(T_STRING,  khrq, 0),\
	DEFSDMEMBER(T_STRING,  xhrq, 0),\
	DEFSDMEMBER(T_STRING,  kkdd, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SAZH)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SAZH_H__*/
