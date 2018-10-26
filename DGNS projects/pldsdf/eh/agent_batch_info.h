/***********************************************************************
版权所有:批量代收代付
项目名称:批量代收代付
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:DB2
文 件 名:agent_batch_info.h
文件描述:agent_batch_info
项 目 组:批量代收代付
程 序 员:
发布时间:2017-10-24
修    订:
修改时间:
************************************************************************
表    名:agent_batch_info (批量代收付导入信息登记簿)
说    明:批量代收付导入信息登记簿
用于登记批量代收代付文件导入相关信息
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __AGENT_BATCH_INFO_EH__
#define __AGENT_BATCH_INFO_EH__

typedef struct TDB_AGENT_BATCH_INFO
{
	char batch_no[32+1];
	char cpdm[16+1];
	char dwbh[16+1];
	char file_name[256+1];
	char ori_file_name[256+1];
	char up_date[8+1];
	int up_seq_no;
	char up_time[6+1];
	char up_unit[16+1];
	char up_teller[16+1];
	char up_channel[3+1];
	char upload_type[2+1];
	char dc_flag[1+1];
	char plat_date[8+1];
	int seq_no;
	char plat_time[6+1];
	char tx_unit[16+1];
	char teller_no[16+1];
	char channel_no[3+1];
	char exec_date[8+1];
	char withdraw_date[8+1];
	int withdraw_seq;
	char withdraw_time[6+1];
	char withdraw_unit[16+1];
	char withdraw_teller[16+1];
	char withdraw_chann[3+1];
	char brief_code[6+1];
	char md5_code[40+1];
	char stat[1+1];
	char resp_code[7+1];
	char resp_msg[60+1];
	char ret_file_name[256+1];
	int tot_cnt;
	double tot_amt;
	int tot_succ_cnt;
	double tot_succ_amt;
	double tot_busi_amt;
	double tot_amt1;
	double tot_amt2;
	double tot_amt3;
	double tot_amt4;
	double tot_amt5;
	int full_cnt;
	double full_amt;
	int part_cnt;
	double part_amt;
	int fee_cnt;
	double fee;
	int real_fee_cnt;
	double real_fee;
	int open_succ_cnt;
	double open_succ_amt;
	int open_fail_cnt;
	double open_fail_amt;
	char acct_date[8+1];
	char extfld1[40+1];
	char extfld2[40+1];
	char extfld3[40+1];
	char extfld4[40+1];
	char extfld5[40+1];
	char extfld6[80+1];
	char wjlx[1+1];
	char zdrzbz[1+1];
	char zxsj[8+1];
	char fkfz[1+1];
	char lqzjsj[8+1];
	char ret_chkfile_name[256+1];
	char ret_chkmd5_code[60+1];
	char th_stat[2+1];
}SDB_AGENT_BATCH_INFO;

#define SD_DATA SDB_AGENT_BATCH_INFO
#define	SD_MEMBERS\
	DEFSDMEMBER(T_STRING, batch_no, 0),\
	DEFSDMEMBER(T_STRING, cpdm, 0),\
	DEFSDMEMBER(T_STRING, dwbh, 0),\
	DEFSDMEMBER(T_STRING, file_name, 0),\
	DEFSDMEMBER(T_STRING, ori_file_name, 0),\
	DEFSDMEMBER(T_STRING, up_date, 0),\
	DEFSDMEMBER(T_LONG, up_seq_no, 0),\
	DEFSDMEMBER(T_STRING, up_time, 0),\
	DEFSDMEMBER(T_STRING, up_unit, 0),\
	DEFSDMEMBER(T_STRING, up_teller, 0),\
	DEFSDMEMBER(T_STRING, up_channel, 0),\
	DEFSDMEMBER(T_STRING, upload_type, 0),\
	DEFSDMEMBER(T_STRING, dc_flag, 0),\
	DEFSDMEMBER(T_STRING, plat_date, 0),\
	DEFSDMEMBER(T_LONG, seq_no, 0),\
	DEFSDMEMBER(T_STRING, plat_time, 0),\
	DEFSDMEMBER(T_STRING, tx_unit, 0),\
	DEFSDMEMBER(T_STRING, teller_no, 0),\
	DEFSDMEMBER(T_STRING, channel_no, 0),\
	DEFSDMEMBER(T_STRING, exec_date, 0),\
	DEFSDMEMBER(T_STRING, withdraw_date, 0),\
	DEFSDMEMBER(T_LONG, withdraw_seq, 0),\
	DEFSDMEMBER(T_STRING, withdraw_time, 0),\
	DEFSDMEMBER(T_STRING, withdraw_unit, 0),\
	DEFSDMEMBER(T_STRING, withdraw_teller, 0),\
	DEFSDMEMBER(T_STRING, withdraw_chann, 0),\
	DEFSDMEMBER(T_STRING, brief_code, 0),\
	DEFSDMEMBER(T_STRING, md5_code, 0),\
	DEFSDMEMBER(T_STRING, stat, 0),\
	DEFSDMEMBER(T_STRING, resp_code, 0),\
	DEFSDMEMBER(T_STRING, resp_msg, 0),\
	DEFSDMEMBER(T_STRING, ret_file_name, 0),\
	DEFSDMEMBER(T_LONG, tot_cnt, 0),\
	DEFSDMEMBER(T_DOUBLE, tot_amt, 2),\
	DEFSDMEMBER(T_LONG, tot_succ_cnt, 0),\
	DEFSDMEMBER(T_DOUBLE, tot_succ_amt, 2),\
	DEFSDMEMBER(T_DOUBLE, tot_busi_amt, 2),\
	DEFSDMEMBER(T_DOUBLE, tot_amt1, 2),\
	DEFSDMEMBER(T_DOUBLE, tot_amt2, 2),\
	DEFSDMEMBER(T_DOUBLE, tot_amt3, 2),\
	DEFSDMEMBER(T_DOUBLE, tot_amt4, 2),\
	DEFSDMEMBER(T_DOUBLE, tot_amt5, 2),\
	DEFSDMEMBER(T_LONG, full_cnt, 0),\
	DEFSDMEMBER(T_DOUBLE, full_amt, 2),\
	DEFSDMEMBER(T_LONG, part_cnt, 0),\
	DEFSDMEMBER(T_DOUBLE, part_amt, 2),\
	DEFSDMEMBER(T_LONG, fee_cnt, 0),\
	DEFSDMEMBER(T_DOUBLE, fee, 2),\
	DEFSDMEMBER(T_LONG, real_fee_cnt, 0),\
	DEFSDMEMBER(T_DOUBLE, real_fee, 2),\
	DEFSDMEMBER(T_LONG, open_succ_cnt, 0),\
	DEFSDMEMBER(T_DOUBLE, open_succ_amt, 2),\
	DEFSDMEMBER(T_LONG, open_fail_cnt, 0),\
	DEFSDMEMBER(T_DOUBLE, open_fail_amt, 2),\
	DEFSDMEMBER(T_STRING, acct_date, 0),\
	DEFSDMEMBER(T_STRING, extfld1, 0),\
	DEFSDMEMBER(T_STRING, extfld2, 0),\
	DEFSDMEMBER(T_STRING, extfld3, 0),\
	DEFSDMEMBER(T_STRING, extfld4, 0),\
	DEFSDMEMBER(T_STRING, extfld5, 0),\
	DEFSDMEMBER(T_STRING, extfld6, 0),\
	DEFSDMEMBER(T_STRING, wjlx, 0),\
	DEFSDMEMBER(T_STRING, zdrzbz, 0),\
	DEFSDMEMBER(T_STRING, zxsj, 0),\
	DEFSDMEMBER(T_STRING, fkfz, 0),\
	DEFSDMEMBER(T_STRING, lqzjsj, 0),\
	DEFSDMEMBER(T_STRING, ret_chkfile_name, 0),\
	DEFSDMEMBER(T_STRING, ret_chkmd5_code, 0),\
	DEFSDMEMBER(T_STRING, th_stat, 0)

	DECLAREFIELDS(SD_AGENT_BATCH_INFO)

#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __AGENT_BATCH_INFO_EH__*/
