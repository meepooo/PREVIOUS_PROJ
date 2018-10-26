/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_CLI_USER.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_CLI_USER (批量客户端_用户信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_CLI_USER_H__
#define __BATCH_CLI_USER_H__
typedef struct TDB_BATCH_CLI_USER
{
  char   contract_no[32+1];              /*协议编号*/
              /**/
  char   user_id[32+1];              /*用户ID*/
              /**/
  char   user_name[80+1];              /*用户名*/
              /**/
  char   contact[32+1];              /*联系人*/
              /**/
  char   phone[16+1];              /*电话号码*/
              /**/
  char   mobile[12+1];              /*手机号*/
              /**/
  char   email[50+1];              /*EMAIL*/
              /**/
  char   ptrq[8+1];              /*登记日期*/
              /**/
  char   tran_time[6+1];              /*登记时间*/
              /**/
  char   ptls[16+1];              /*登记流水*/
              /**/
  char   branch[16+1];              /*登记机构*/
              /**/
  char   oper[16+1];              /*登记柜员*/
              /**/
  char   acct_manager[32+1];              /*客户经理*/
              /**/
  char   acct_name[80+1];              /*签约户名*/
              /**/
  char   acct_no[32+1];              /*签约账号*/
              /**/
  char   status[1+1];              /*签约状态*/
              /*0 未发送
                n 发送n次
                */
  long    send_flag;              /*发送标志*/
              /*0 未发送
                n 发送n次
                */
  char   key[32+1];              /*KEY*/
              /**/
  char   extfld1[16+1];              /*扩展字段一*/
              /**/
  char   extfld2[32+1];              /*扩展字段二*/
              /**/
  char   extfld3[50+1];              /*扩展字段三*/
              /**/
  char   extfld4[64+1];              /*扩展字段四*/
              /**/
}BATCH_CLI_USER;

#define SD_DATA  BATCH_CLI_USER
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  contract_no, 0),\
	DEFSDMEMBER(T_STRING,  user_id, 0),\
	DEFSDMEMBER(T_STRING,  user_name, 0),\
	DEFSDMEMBER(T_STRING,  contact, 0),\
	DEFSDMEMBER(T_STRING,  phone, 0),\
	DEFSDMEMBER(T_STRING,  mobile, 0),\
	DEFSDMEMBER(T_STRING,  email, 0),\
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  tran_time, 0),\
	DEFSDMEMBER(T_STRING,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  branch, 0),\
	DEFSDMEMBER(T_STRING,  oper, 0),\
	DEFSDMEMBER(T_STRING,  acct_manager, 0),\
	DEFSDMEMBER(T_STRING,  acct_name, 0),\
	DEFSDMEMBER(T_STRING,  acct_no, 0),\
	DEFSDMEMBER(T_STRING,  status, 0),\
	DEFSDMEMBER(T_LONG,  send_flag, 0),\
	DEFSDMEMBER(T_STRING,  key, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0),\
	DEFSDMEMBER(T_STRING,  extfld4, 0)


	DECLAREFIELDS(SD_BATCH_CLI_USER)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_CLI_USER_H__*/
