/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_xdxx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_xdxx (电信诈骗下达信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_XDXX_H__
#define __GAB_DXZP_XDXX_H__
typedef struct TDB_GAB_DXZP_XDXX
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*请求单标识 请求单流水号，用于标识查控请求单*/
	char   jybm[6+1];  /*交易编码*/
		/**/
	char   xxlzms[2+1];  /*消息流转模式*/
		/**/
	char   csbwlsh[53+1];  /*传输报文流水号*/
		/**/
	char   gaywsqbh[36+1];  /*公安业务申请编号*/
		/**/
	char   fsjgbm[12+1];  /*发送机构编号*/
		/*发送机构编号*/
	char   sqjgdm[12+1];  /*申请机构代码*/
		/*申请机构代码 公安机关机构编码*/
	char   mbjgdm[12+1];  /*目标机构代码*/
		/*目标机构代码 将协助请求单发送给目标机构的代码*/
	char   cxztlb[2+1];  /*查控主体类别*/
		/*查控主体类别 01代表个人主体 02代表对公（单位）主体*/
	char   ywlx[4+1];  /*业务类型*/
		/*业务类型*/
	char   jjcd[2+1];  /*紧急程度*/
		/*紧急程度 01代表正常；02代表加急*/
	char   ajbh[30+1];  /*案件编号*/
		/*案件编号 案件类型名称*/
	char   ajlx[50+1];  /*案件类型*/
		/*案件类型 案件类型名称*/
	char   ajsy[300+1];  /*案件事由*/
		/*案件事由*/
	char   ajsm[300+1];  /*案件说明*/
		/*案件说明*/
	char   sqrq[8+1];  /*申请日期*/
		/*发送请求给目标机构时的系统日期时间*/
	char   sqsj[6+1];  /*申请时间*/
		/*发送请求给目标机构时的系统日期时间*/
	char   sqjgbm[12+1];  /*申请机构编码*/
		/**/
	char   sqjgmc[150+1];  /*申请机构名称*/
		/*请求人单位名称 查询申请人所属单位名称*/
	char   jbrxm[40+1];  /*经办人姓名*/
		/*请求人姓名*/
	char   jbrzjlx[2+1];  /*经办人证件类型*/
		/*请求人证件类型 此处默认为110031 警官证*/
	char   jbrzjhm[30+1];  /*经办人证件号码*/
		/*请求人证件号码 请求人警号*/
	char   jbrdh[30+1];  /*经办人电话*/
		/*经办人手机号 查询经办人的手机号码*/
	char   xcrxm[40+1];  /*协查人姓名*/
		/*协查人姓名*/
	char   xcrzjlx[2+1];  /*协查人证件类型*/
		/*协查人证件类型 此处默认为110031 警官证*/
	char   xcrzjhm[30+1];  /*协查人证件号码*/
		/*协查人证件号码*/
	char   ywrq[8+1];  /*业务日期*/
		/*业务日期*/
	char   ywlsh[32+1];  /*业务流水号*/
		/*业务流水号*/
	char   jbjg[16+1];  /*银行经办机构*/
		/*经办机构*/
	char   jbgy[16+1];  /*银行经办柜员*/
		/*经办柜员*/
	char   jbxm[100+1];  /*银行经办姓名*/
		/**/
	char   jbdh[30+1];  /*银行经办电话*/
		/**/
	long   rwsl;  /*任务数量*/
		/*任务数量*/
	long   jgfkxdsj;  /*结果反馈限定时间*/
		/*结果反馈限定时间*/
	char   fkxdrq[8+1];  /*反馈限定日期*/
		/*反馈限定日期*/
	char   fkxdsj[6+1];  /*反馈限定时间*/
		/*反馈限定时间*/
	char   fkddrq[8+1];  /*反馈兜底日期*/
		/*反馈兜底日期*/
	char   fkddsj[6+1];  /*反馈兜底时间*/
		/*反馈兜底时间*/
	char   szclbz[1+1];  /*手自处理标志*/
		/*手自处理标志 0-系统 1-手工*/
	char   clrq[8+1];  /*处理日期*/
		/**/
	char   clsj[6+1];  /*处理时间*/
		/**/
	char   zwrq[8+1];  /*gaps日期*/
		/*gaps日期*/
	char   systime[6+1];  /*gaps时间*/
		/*gaps时间*/
	char   zhqzlsh[16+1];  /*gaps流水号*/
		/*gaps流水号*/
	char   qqdzt[2+1];  /*请求单状态*/
		/*请求单状态 第一位：0-初始 1-落地 2-处理(提交) 3-提回 4-反馈  第二位：0-初始 1-不成功；2-成功; 3-超时; 9-处理中*/
	char   ywydm[4+1];  /*业务应答码*/
		/*业务应答码 详见人行业务应答码定义*/
	char   ywydxx[100+1];  /*业务应答信息*/
		/*业务应答信息 详见人行业务应答码定义*/
	char   zxjg[1+1];  /*执行结果*/
		/*执行结果 0-不成功；1-成功*/
	char   respcode[8+1];  /*错误码*/
		/**/
	char   respmsg[100+1];  /*错误原因*/
		/**/
	char   zjrq[8+1];  /*主机日期*/
		/**/
	char   zjlsh[32+1];  /*主机流水号*/
		/**/
	char   dzxh[36+1];  /*冻止序号*/
		/*冻止序号*/
	char   sbpch[36+1];  /*上报批次号*/
		/*上报批次号*/
	char   lxrq[8+1];  /*轮询日期*/
		/*轮询日期*/
	char   lxpch[32+1];  /*轮询批次号*/
		/*轮询批次号*/
	long   pcxh;  /*批次序号*/
		/*批次序号*/
	long   tjhxcs;  /*提交核心次数*/
		/*提交核心次数*/
	long   fkqzcs;  /*反馈前置次数*/
		/*反馈前置次数*/
	char   by11[30+1];  /*备用11*/
		/**/
	char   by12[254+1];  /*备用12*/
		/**/
	char   by13[254+1];  /*备用13*/
		/**/

}GAB_DXZP_XDXX;

#define SD_DATA  GAB_DXZP_XDXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  xxlzms, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  gaywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  fsjgbm, 0),\
	DEFSDMEMBER(T_STRING,  sqjgdm, 0),\
	DEFSDMEMBER(T_STRING,  mbjgdm, 0),\
	DEFSDMEMBER(T_STRING,  cxztlb, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  jjcd, 0),\
	DEFSDMEMBER(T_STRING,  ajbh, 0),\
	DEFSDMEMBER(T_STRING,  ajlx, 0),\
	DEFSDMEMBER(T_STRING,  ajsy, 0),\
	DEFSDMEMBER(T_STRING,  ajsm, 0),\
	DEFSDMEMBER(T_STRING,  sqrq, 0),\
	DEFSDMEMBER(T_STRING,  sqsj, 0),\
	DEFSDMEMBER(T_STRING,  sqjgbm, 0),\
	DEFSDMEMBER(T_STRING,  sqjgmc, 0),\
	DEFSDMEMBER(T_STRING,  jbrxm, 0),\
	DEFSDMEMBER(T_STRING,  jbrzjlx, 0),\
	DEFSDMEMBER(T_STRING,  jbrzjhm, 0),\
	DEFSDMEMBER(T_STRING,  jbrdh, 0),\
	DEFSDMEMBER(T_STRING,  xcrxm, 0),\
	DEFSDMEMBER(T_STRING,  xcrzjlx, 0),\
	DEFSDMEMBER(T_STRING,  xcrzjhm, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  jbjg, 0),\
	DEFSDMEMBER(T_STRING,  jbgy, 0),\
	DEFSDMEMBER(T_STRING,  jbxm, 0),\
	DEFSDMEMBER(T_STRING,  jbdh, 0),\
	DEFSDMEMBER(T_LONG,  rwsl, 0),\
	DEFSDMEMBER(T_LONG,  jgfkxdsj, 0),\
	DEFSDMEMBER(T_STRING,  fkxdrq, 0),\
	DEFSDMEMBER(T_STRING,  fkxdsj, 0),\
	DEFSDMEMBER(T_STRING,  fkddrq, 0),\
	DEFSDMEMBER(T_STRING,  fkddsj, 0),\
	DEFSDMEMBER(T_STRING,  szclbz, 0),\
	DEFSDMEMBER(T_STRING,  clrq, 0),\
	DEFSDMEMBER(T_STRING,  clsj, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  zhqzlsh, 0),\
	DEFSDMEMBER(T_STRING,  qqdzt, 0),\
	DEFSDMEMBER(T_STRING,  ywydm, 0),\
	DEFSDMEMBER(T_STRING,  ywydxx, 0),\
	DEFSDMEMBER(T_STRING,  zxjg, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjlsh, 0),\
	DEFSDMEMBER(T_STRING,  dzxh, 0),\
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_STRING,  lxrq, 0),\
	DEFSDMEMBER(T_STRING,  lxpch, 0),\
	DEFSDMEMBER(T_LONG,  pcxh, 0),\
	DEFSDMEMBER(T_LONG,  tjhxcs, 0),\
	DEFSDMEMBER(T_LONG,  fkqzcs, 0),\
	DEFSDMEMBER(T_STRING,  by11, 0),\
	DEFSDMEMBER(T_STRING,  by12, 0),\
	DEFSDMEMBER(T_STRING,  by13, 0)


	DECLAREFIELDS(SD_GAB_DXZP_XDXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_XDXX_H__*/
