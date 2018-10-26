/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_sbxx_jymx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_sbxx_jymx (电信诈骗上报信息_交易明细表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_SBXX_JYMX_H__
#define __GAB_DXZP_SBXX_JYMX_H__
typedef struct TDB_GAB_DXZP_SBXX_JYMX
{
	char   sbpch[36+1];  /*上报批次号*/
		/*上报批次号*/
	long   sbpcxh;  /*上报批次序号*/
		/*上报批次序号*/
	char   zhxh[8+1];  /*账户序号*/
		/*账户序号*/
	long   jyxh;  /*交易序号*/
		/*交易序号*/
	char   jybm[6+1];  /*交易编码*/
		/*交易编码*/
	char   csbwlsh[53+1];  /*传输报文流水号*/
		/*传输报文流水号*/
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*业务申请编号*/
	char   sjtzm[4+1];  /*事件特征码*/
		/*事件特征码*/
	char   zh[50+1];  /*账卡号*/
		/*账卡号*/
	char   zhm[120+1];  /*账户名*/
		/*账户名*/
	char   zjlx[6+1];  /*证件类型*/
		/*证件类型*/
	char   zjhm[30+1];  /*证件号*/
		/*证件号*/
	char   jylsh[64+1];  /*交易流水号*/
		/*交易流水号*/
	char   jysj[14+1];  /*交易时间*/
		/*交易时间*/
	char   jylx[20+1];  /*交易类型*/
		/*交易类型*/
	char   bz[3+1];  /*币种*/
		/*币种*/
	char   jyje[20+1];  /*交易金额*/
		/*交易金额*/
	char   zczhyhjg[12+1];  /*转出账户银行机构*/
		/*转出账户银行机构*/
	char   zczhyhmc[136+1];  /*转出账户银行名称*/
		/*转出账户银行名称*/
	char   zczhm[60+1];  /*转出账户名*/
		/*转出账户银行名称*/
	char   zczh[30+1];  /*转出账号*/
		/*转出账号*/
	char   ddzhyhjg[12+1];  /*对端账户银行机构*/
		/*对端账户银行机构*/
	char   ddzhyhmc[136+1];  /*对端账户银行名称*/
		/*对端账户银行名称*/
	char   ddzhm[60+1];  /*对端账户名*/
		/*对端账户名*/
	char   ddzh[30+1];  /*对端账号*/
		/*对端账号*/
	char   ip[30+1];  /*ip地址*/
		/*ip地址*/
	char   mac[20+1];  /*mac地址*/
		/*mac地址*/
	char   sbid[20+1];  /*设备id*/
		/*设备id*/
	char   jydd[150+1];  /*交易地点*/
		/*交易地点*/
	char   beiz[150+1];  /*备注*/
		/**/
	char   zfbz[1+1];  /*止付标志*/
		/*止付标志 0-已止付；1-未止付；*/
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

}GAB_DXZP_SBXX_JYMX;

#define SD_DATA  GAB_DXZP_SBXX_JYMX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  zhxh, 0),\
	DEFSDMEMBER(T_LONG,  jyxh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  sjtzm, 0),\
	DEFSDMEMBER(T_STRING,  zh, 0),\
	DEFSDMEMBER(T_STRING,  zhm, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  jylsh, 0),\
	DEFSDMEMBER(T_STRING,  jysj, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  jyje, 0),\
	DEFSDMEMBER(T_STRING,  zczhyhjg, 0),\
	DEFSDMEMBER(T_STRING,  zczhyhmc, 0),\
	DEFSDMEMBER(T_STRING,  zczhm, 0),\
	DEFSDMEMBER(T_STRING,  zczh, 0),\
	DEFSDMEMBER(T_STRING,  ddzhyhjg, 0),\
	DEFSDMEMBER(T_STRING,  ddzhyhmc, 0),\
	DEFSDMEMBER(T_STRING,  ddzhm, 0),\
	DEFSDMEMBER(T_STRING,  ddzh, 0),\
	DEFSDMEMBER(T_STRING,  ip, 0),\
	DEFSDMEMBER(T_STRING,  mac, 0),\
	DEFSDMEMBER(T_STRING,  sbid, 0),\
	DEFSDMEMBER(T_STRING,  jydd, 0),\
	DEFSDMEMBER(T_STRING,  beiz, 0),\
	DEFSDMEMBER(T_STRING,  zfbz, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SBXX_JYMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SBXX_JYMX_H__*/
