/***********************************************************************
°æÈ¨ËùÓÐ:ºãÉúµç×Ó¹É·ÝÓÐÏÞ¹«Ë¾
ÏîÄ¿Ãû³Æ:×ÛºÏ¼¼ÊõÆ½Ì¨(Turandot)ÏîÄ¿
°æ    ±¾:V1.00
²Ù×÷ÏµÍ³:
Êý ¾Ý ¿â:INFORMIX
ÎÄ ¼þ Ãû:WB_DS_ACCOUNTING_FLOW_DIFF.h
ÎÄ¼þÃèÊö:½á¹¹¶¨ÒåÊý¾Ý¿â¿ª·¢Ç¶CÍ·ÎÄ¼þ
Ïî Ä¿ ×é:
³Ì Ðò Ô±:[wangzh14925]
·¢²¼Ê±¼ä:2009-4-29 19:40:39 [Gen]
ÐÞ    ¶©:
ÐÞ¸ÄÊ±¼ä:
************************************************************************
±í    Ãû:WB_DS_ACCOUNTING_FLOW_DIFF (F_WB30.×Ü·ÖºË¶Ô²î´í±í)
Ëµ    Ã÷:
************************************************************************
ÐÞ¸Ä¼ÇÂ¼:
ÐÞ¸ÄÈÕÆÚ:
ÐÞ¸ÄÄÚÈÝ:
ÐÞ ¸Ä ÈË:
ÐÞ¸ÄÄÚÈÝ:
************************************************************************/
#ifndef __ICPS_DS_ACCOUNTING_FLOW_DIFF_H__
#define __ICPS_DS_ACCOUNTING_FLOW_DIFF_H__
typedef struct TDB_ICPS_DS_ACCOUNTING_FLOW_DIFF
{
	char   busi_date[8+1];  /*ÒµÎñÈÕÆÚ*/
	char   busi_no[16+1];  /*ÒµÎñÖÖÀà*/
	char   subject[40+1];  /*¿ÆÄ¿*/
	char   product_cd[6+1];  /*²úÆ·±àºÅ*/
	char   bank_group_id[5+1];  /*ÒøÍÅ´úÂë*/
	double   db_amt;  /*Ã÷Ï¸»ã×Ü½è·½½ð¶î*/
	int   db_count;  /*½è·½Ã÷Ï¸»ã×Ü±ÊÊý*/
	double   db_pmt;  /*×ÜÕË½è·½·¢Éú¶î*/
	int   db_tcnt;  /*×ÜÕË½è·½±ÊÊý*/
	char   dr_check_flag[1+1]; /*½è·½ºË¶Ô±êÊ¶*/
	double   cr_amt;  /*´û·½·¢Éú¶î»ã×Ü*/
	int   cr_count;  /*´û·½Ã÷Ï¸»ã×Ü±ÊÊý*/
	double   cr_pmt;  /*´û·½·¢Éú¶î*/ 
	int   cr_tcnt;  /*×ÜÕË´û·½±ÊÊý*/
	char   cr_check_flag[1+1]; /*´û·½½ºË¶Ô±êÊ¶*/
	char   extend_param1[100+1];  /*À©Õ¹1*/
	char   extend_param2[250+1];  /*À©Õ¹2*/
	char   extend_param3[40+1];  /*À©Õ¹3*/

}ICPS_DS_ACCOUNTING_FLOW_DIFF;

#define SD_DATA  ICPS_DS_ACCOUNTING_FLOW_DIFF
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  busi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  subject, 0),\
	APP_DEFSDMEMBER(T_STRING,  product_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  bank_group_id, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  db_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,    db_count, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  db_pmt, 2),\
	APP_DEFSDMEMBER(T_LONG,    db_tcnt, 0),\
	APP_DEFSDMEMBER(T_STRING,  dr_check_flag, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  cr_amt, 2),\
	APP_DEFSDMEMBER(T_LONG,    cr_count, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  cr_pmt, 2),\
	APP_DEFSDMEMBER(T_LONG,    cr_tcnt, 0),\
	APP_DEFSDMEMBER(T_STRING,  cr_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)

	APP_DECLAREFIELDS(SD_ICPS_DS_ACCOUNTING_FLOW_DIFF)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_DS_ACCOUNTING_FLOW_DIFF_H__*/
