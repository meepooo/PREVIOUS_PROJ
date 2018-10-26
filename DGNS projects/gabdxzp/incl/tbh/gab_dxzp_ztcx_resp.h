/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:gab_dxzp_ztcx_resp.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:gab_dxzp_ztcx_resp (电信诈骗主体查询响应)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __GAB_DXZP_ZTCX_RESP_H__
#define __GAB_DXZP_ZTCX_RESP_H__
typedef struct TDB_GAB_DXZP_ZTCX_RESP
{
	char   ywsqbh[36+1];  /*业务申请编号*/
		/*主键，请求单流水号，用于标识查控请求单*/
	int   rwxh;  /*任务序号*/
		/*任务序号*/
	char   fkjgmc[150+1];  /*反馈机构名称*/
		/*反馈机构名称*/
	char   fksm[300+1];  /*查询反馈说明*/
		/*查询反馈说明*/
	char   zjlx[2+1];  /*查询证照类型代码*/
		/*查询证照类型代码*/
	char   zjhm[30+1];  /*查询证照号码*/
		/*查询证照号码*/
	char   ztmc[100+1];  /*查询主体名称*/
		/*查询主体名称*/
	char   lxsj[20+1];  /*联系手机*/
		/*联系手机*/
	char   dbrxm[60+1];  /*账/卡代办人姓名*/
		/*账/卡代办人姓名*/
	char   dbrzjlx[2+1];  /*账/卡代办人证件类型*/
		/*账/卡代办人证件类型*/
	char   dbrzjhm[30+1];  /*账/卡代办人证件号码*/
		/*账/卡代办人证件号码*/
	char   zzdz[150+1];  /*住宅地址*/
		/*住宅地址*/
	char   zzdh[20+1];  /*住宅电话*/
		/*住宅电话*/
	char   gzdw[100+1];  /*工作单位*/
		/*工作单位*/
	char   dwdz[150+1];  /*单位地址*/
		/*单位地址*/
	char   dwdh[20+1];  /*单位电话*/
		/*单位电话*/
	char   yxdz[60+1];  /*邮箱地址*/
		/*邮箱地址*/
	char   frdb[60+1];  /*法人代表*/
		/*法人代表*/
	char   frdbzjlx[15+1];  /*法人代表证件类型*/
		/*法人代表证件类型*/
	char   frdbzjhm[30+1];  /*法人代表证件号码*/
		/*法人代表证件号码*/
	char   khgszzhm[18+1];  /*客户工商执照号码*/
		/*客户工商执照号码*/
	char   gsnsh[20+1];  /*国税纳税号*/
		/*国税纳税号*/
	char   dsnsh[20+1];  /*地税纳税号*/
		/*地税纳税号*/
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

}GAB_DXZP_ZTCX_RESP;

#define SD_DATA  GAB_DXZP_ZTCX_RESP
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywsqbh, 0),\
	DEFSDMEMBER(T_LONG,  rwxh, 0),\
	DEFSDMEMBER(T_STRING,  fkjgmc, 0),\
	DEFSDMEMBER(T_STRING,  fksm, 0),\
	DEFSDMEMBER(T_STRING,  zjlx, 0),\
	DEFSDMEMBER(T_STRING,  zjhm, 0),\
	DEFSDMEMBER(T_STRING,  ztmc, 0),\
	DEFSDMEMBER(T_STRING,  lxsj, 0),\
	DEFSDMEMBER(T_STRING,  dbrxm, 0),\
	DEFSDMEMBER(T_STRING,  dbrzjlx, 0),\
	DEFSDMEMBER(T_STRING,  dbrzjhm, 0),\
	DEFSDMEMBER(T_STRING,  zzdz, 0),\
	DEFSDMEMBER(T_STRING,  zzdh, 0),\
	DEFSDMEMBER(T_STRING,  gzdw, 0),\
	DEFSDMEMBER(T_STRING,  dwdz, 0),\
	DEFSDMEMBER(T_STRING,  dwdh, 0),\
	DEFSDMEMBER(T_STRING,  yxdz, 0),\
	DEFSDMEMBER(T_STRING,  frdb, 0),\
	DEFSDMEMBER(T_STRING,  frdbzjlx, 0),\
	DEFSDMEMBER(T_STRING,  frdbzjhm, 0),\
	DEFSDMEMBER(T_STRING,  khgszzhm, 0),\
	DEFSDMEMBER(T_STRING,  gsnsh, 0),\
	DEFSDMEMBER(T_STRING,  dsnsh, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  by1, 0),\
	DEFSDMEMBER(T_STRING,  by2, 0),\
	DEFSDMEMBER(T_STRING,  by3, 0)


	DECLAREFIELDS(SD_GAB_DXZP_ZTCX_RESP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __GAB_DXZP_ZTCX_RESP_H__*/
