/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_sajb.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[屠秋龙]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_sajb (电信诈骗涉案举报表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_SAJB_H__
#define __GAB_DXZP_SAJB_H__
typedef struct TDB_GAB_DXZP_SAJB
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
		/*业务申请编号*/
	char   jsjgid[12+1];  /*接收机构id*/
		/*接收机构id*/
	char   tgjgbm[12+1];  /*托管机构编码*/
		/*托管机构编码*/
	char   ywlx[4+1];  /*业务类型*/
		/*业务类型*/
	char   shrxm[60+1];  /*受害人姓名*/
		/**/
	char   shrlxdh[30+1];  /*受害人联系电话*/
		/**/
	char   zjlx[2+1];  /*证件类型*/
		/**/
	char   zjhm[30+1];  /*证件号*/
		/**/
	char   sjms[300+1];  /*事件描述*/
		/**/
	char   ajjblx[2+1];  /*案件举报类型*/
		/*案件举报类型  01-报案,02-止付后补流程*/
	char   zjrq[8+1];  /*主机日期*/
		/**/
	char   zjlsh[32+1];  /*主机流水号*/
		/**/
	char   dzxh[36+1];  /*冻止序号*/
		/*冻止序号*/
	char   yxbz[1+1];  /*影像标志*/
		/*影像标志 0-有影像 1-无影像*/
	char   qqdzt[2+1];  /*请求单状态*/
		/*请求单状态 第一位：0-初始 1-落地 2-处理(提交) 3-提回 4-反馈  第二位：0-初始 1-不成功；2-成功; 3-超时; 9-处理中*/
	char   zxjg[1+1];  /*执行结果*/
		/*执行结果 0-不成功；1-成功*/
	char   respcode[8+1];  /*错误码*/
		/**/
	char   respmsg[100+1];  /*错误原因*/
		/**/
	char   fkdjjzsj[14+1];  /*反馈冻结截止时间*/
		/**/
	char   cxjg[4+1];  /*查询结果*/
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

}GAB_DXZP_SAJB;

#define SD_DATA  GAB_DXZP_SAJB
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sbpch, 0),\
	DEFSDMEMBER(T_LONG,  sbpcxh, 0),\
	DEFSDMEMBER(T_STRING,  jybm, 0),\
	DEFSDMEMBER(T_STRING,  csbwlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_STRING,  jsjgid, 0),\
	DEFSDMEMBER(T_STRING,  tgjgbm, 0),\
	DEFSDMEMBER(T_STRING,  ywlx, 0),\
	DEFSDMEMBER(T_STRING,  shrxm, 0),\
	DEFSDMEMBER(T_STRING,  shrlxdh, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  sjms, 0),\
	DEFSDMEMBER(T_STRING,  ajjblx, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjlsh, 0),\
	DEFSDMEMBER(T_STRING,  dzxh, 0),\
	DEFSDMEMBER(T_STRING,  yxbz, 0),\
	DEFSDMEMBER(T_STRING,  qqdzt, 0),\
	DEFSDMEMBER(T_STRING,  zxjg, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  fkdjjzsj, 0),\
	DEFSDMEMBER(T_STRING,  cxjg, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_SAJB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_SAJB_H__*/
