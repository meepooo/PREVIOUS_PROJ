/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_ycsj.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_ycsj (电信诈骗异常事件表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_YCSJ_H__
#define __GAB_DXZP_YCSJ_H__
typedef struct TDB_GAB_DXZP_YCSJ
{
	char   sbpch[36+1];  /*上报批次号*/
		/**/
	int   sbpcxh;  /*上报批次序号*/
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
	char   jylsh[64+1];  /*交易流水号*/
		/**/
	char   jysj[14+1];  /*交易时间*/
		/**/
	char   jylx[20+1];  /*交易类型*/
		/**/
	char   bz[3+1];  /*币种*/
		/**/
	char   je[20+1];  /*交易金额*/
		/**/
	char   zcyhjg[12+1];  /*转出账户所属银行机构编码*/
		/**/
	char   zcyhmc[136+1];  /*转出账户所属银行名称*/
		/**/
	char   zczhhm[60+1];  /*转出账户名*/
		/**/
	char   zczh[30+1];  /*转出账卡号*/
		/**/
	char   ddyhjg[12+1];  /*交易对端账户所属银行机构编码*/
		/**/
	char   ddyhmc[136+1];  /*交易对端账户所属银行名称*/
		/**/
	char   ddzhm[60+1];  /*交易对端账户名*/
		/**/
	char   ddzh[30+1];  /*交易对端账卡号*/
		/**/
	char   ipdz[30+1];  /*ip地址*/
		/**/
	char   mac[20+1];  /*mac地址*/
		/**/
	char   sbid[20+1];  /*设备id*/
		/**/
	char   jydd[150+1];  /*交易地点*/
		/**/
	char   beiz[150+1];  /*备注*/
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

}GAB_DXZP_YCSJ;

#define SD_DATA  GAB_DXZP_YCSJ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  sjtzm, 0),\
	DEFSDMEMBER(T_STRING,  yywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  jylsh, 0),\
	DEFSDMEMBER(T_STRING,  jysj, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  je, 0),\
	DEFSDMEMBER(T_STRING,  zcyhjg, 0),\
	DEFSDMEMBER(T_STRING,  zcyhmc, 0),\
	DEFSDMEMBER(T_STRING,  zczhhm, 0),\
	DEFSDMEMBER(T_STRING,  zczh, 0),\
	DEFSDMEMBER(T_STRING,  ddyhjg, 0),\
	DEFSDMEMBER(T_STRING,  ddyhmc, 0),\
	DEFSDMEMBER(T_STRING,  ddzhm, 0),\
	DEFSDMEMBER(T_STRING,  ddzh, 0),\
	DEFSDMEMBER(T_STRING,  ipdz, 0),\
	DEFSDMEMBER(T_STRING,  mac, 0),\
	DEFSDMEMBER(T_STRING,  sbid, 0),\
	DEFSDMEMBER(T_STRING,  jydd, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_YCSJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_YCSJ_H__*/
