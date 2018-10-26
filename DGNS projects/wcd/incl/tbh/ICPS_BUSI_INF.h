/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_BUSI_INF.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_BUSI_INF (6.业务信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_BUSI_INF_H__
#define __ICPS_BUSI_INF_H__
typedef struct TDB_ICPS_BUSI_INF
{
	char   busi_no[16+1];  /*业务编号*/
		/*业务编号 jiebei-借呗 jintiao-金条 wbank-微粒贷*/
	char   busi_nm[64+1];  /*业务名称*/
		/*业务名称*/
	char   local_id[16+1];  /*本机构代码*/
		/*本机构代码*/
	char   time_zone[32+1];  /*本机构时区*/
		/*本机构时区*/
	char   sign_type[16+1];  /*签名算法类型*/
		/*签名算法类型 RSA*/
	char   message_charset[16+1];  /*报文字符编码*/
		/*报文字符编码*/
	char   version[8+1];  /*版本号*/
		/*版本号*/
	char   clear_acct_id[64+1];  /*内部清算账号*/
		/*内部清算账号*/
	char   clear_acct_nm[128+1];  /*内部清算账号名称*/
		/*内部清算账号名称*/
	char   position_acct_id[64+1];  /*内部头寸账号*/
		/*内部头寸账号*/
	char   position_acct_nm[128+1];  /*内部头寸账号名称*/
		/*内部头寸账号名称*/
	char   fee_out_acct_id[64+1];  /*手续费支出账号*/
		/*手续费支出账号*/
	char   fee_out_acct_nm[128+1];  /*手续费支出账号名称*/
		/*手续费支出账号名称*/
	char   fee_in_acct_id[64+1];  /*手续费收入账号*/
		/*手续费收入账号*/
	char   fee_in_acct_nm[128+1];  /*手续费收入账号名称*/
		/*手续费收入账号名称*/
	char   provisions_acct_id[64+1];  /*第三方备付金账号*/
		/*第三方备付金账号*/
	char   provisions_acct_nm[128+1];  /*第三方备付金账号名称*/
		/*第三方备付金账号名称*/
	char   open_flag[1+1];  /*开通标识*/
		/*开通标识 0-未开通 1-开通*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_BUSI_INF;

#define SD_DATA  ICPS_BUSI_INF
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  local_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  time_zone, 0),\
	APP_DEFSDMEMBER(T_STRING,  sign_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  message_charset, 0),\
	APP_DEFSDMEMBER(T_STRING,  version, 0),\
	APP_DEFSDMEMBER(T_STRING,  clear_acct_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  clear_acct_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  position_acct_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  position_acct_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  fee_out_acct_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  fee_out_acct_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  fee_in_acct_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  fee_in_acct_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  provisions_acct_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  provisions_acct_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  open_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_BUSI_INF)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_BUSI_INF_H__*/
