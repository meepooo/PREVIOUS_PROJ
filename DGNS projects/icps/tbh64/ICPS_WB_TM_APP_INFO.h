/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_APP_INFO.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_APP_INFO (F_WB7.主卡申请人信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_APP_INFO_H__
#define __ICPS_WB_TM_APP_INFO_H__
typedef struct TDB_ICPS_WB_TM_APP_INFO
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   id[20+1];  /*标识*/
		/*标识*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   app_no[20+1];  /*申请件编号*/
		/*申请件编号*/
	char   user_field53[1+1];  /*备用字段53*/
		/*备用字段53*/
	char   user_field54[19+1];  /*备用字段54*/
		/*备用字段54*/
	char   name[80+1];  /*姓名*/
		/*姓名*/
	char   emb_logo[30+1];  /*凸印名称*/
		/*凸印名称*/
	char   gender[2+1];  /*性别*/
		/*性别*/
	char   nationality[3+1];  /*国籍*/
		/*国籍*/
	char   residency_country_cd[3+1];  /*永久居住地国家代码*/
		/*永久居住地国家代码*/
	char   id_type[1+1];  /*证件类型*/
		/*证件类型*/
	char   id_no[30+1];  /*证件号码*/
		/*证件号码*/
	char   user_field55[14+1];  /*备用字段55*/
		/*备用字段55*/
	char   user_field56[200+1];  /*备用字段56*/
		/*备用字段56*/
	char   birthday[14+1];  /*生日*/
		/*生日*/
	char   user_field57[1+1];  /*备用字段57*/
		/*备用字段57*/
	double   user_field58;  /*备用字段58*/
		/*备用字段58*/
	char   user_field59[1+1];  /*备用字段59*/
		/*备用字段59*/
	char   user_field60[1+1];  /*备用字段60*/
		/*备用字段60*/
	char   user_field61[3+1];  /*备用字段61*/
		/*备用字段61*/
	char   user_field62[40+1];  /*备用字段62*/
		/*备用字段62*/
	char   user_field63[40+1];  /*备用字段63*/
		/*备用字段63*/
	char   user_field64[40+1];  /*备用字段64*/
		/*备用字段64*/
	char   user_field65[1+1];  /*备用字段65*/
		/*备用字段65*/
	char   user_field66[200+1];  /*备用字段66*/
		/*备用字段66*/
	char   user_field67[10+1];  /*备用字段67*/
		/*备用字段67*/
	char   user_field68[20+1];  /*备用字段68*/
		/*备用字段68*/
	char   user_field69[14+1];  /*备用字段69*/
		/*备用字段69*/
	char   cellphone[20+1];  /*移动电话*/
		/*移动电话*/
	char   user_field70[80+1];  /*备用字段70*/
		/*备用字段70*/
	char   user_field71[40+1];  /*备用字段71*/
		/*备用字段71*/
	char   user_field72[40+1];  /*备用字段72*/
		/*备用字段72*/
	char   user_field73[1+1];  /*备用字段73*/
		/*备用字段73*/
	char   user_field74[2+1];  /*备用字段74*/
		/*备用字段74*/
	double   user_field75;  /*备用字段75*/
		/*备用字段75*/
	char   user_field76[1+1];  /*备用字段76*/
		/*备用字段76*/
	char   user_field77[20+1];  /*备用字段77*/
		/*备用字段77*/
	char   user_field78[200+1];  /*备用字段78*/
		/*备用字段78*/
	char   user_field79[3+1];  /*备用字段79*/
		/*备用字段79*/
	char   user_field80[40+1];  /*备用字段80*/
		/*备用字段80*/
	char   user_field81[40+1];  /*备用字段81*/
		/*备用字段81*/
	char   user_field82[40+1];  /*备用字段82*/
		/*备用字段82*/
	char   user_field83[200+1];  /*备用字段83*/
		/*备用字段83*/
	char   user_field84[10+1];  /*备用字段84*/
		/*备用字段84*/
	char   user_field85[20+1];  /*备用字段85*/
		/*备用字段85*/
	char   user_field86[80+1];  /*备用字段86*/
		/*备用字段86*/
	char   user_field87[1+1];  /*备用字段87*/
		/*备用字段87*/
	char   user_field88[1+1];  /*备用字段88*/
		/*备用字段88*/
	char   user_field89[1+1];  /*备用字段89*/
		/*备用字段89*/
	double   user_field90;  /*备用字段90*/
		/*备用字段90*/
	char   user_field91[20+1];  /*备用字段91*/
		/*备用字段91*/
	char   user_field92[1+1];  /*备用字段92*/
		/*备用字段92*/
	char   user_field93[1+1];  /*备用字段93*/
		/*备用字段93*/
	char   user_field94[14+1];  /*备用字段94*/
		/*备用字段94*/
	char   user_field95[1+1];  /*备用字段95*/
		/*备用字段95*/
	char   user_field96[1+1];  /*备用字段96*/
		/*备用字段96*/
	char   user_field97[10+1];  /*备用字段97*/
		/*备用字段97*/
	char   user_field98[1+1];  /*备用字段98*/
		/*备用字段98*/
	char   user_field99[1+1];  /*备用字段99*/
		/*备用字段99*/
	char   pr_of_country[1+1];  /*是否永久居住*/
		/*是否永久居住*/
	char   user_field100[80+1];  /*备用字段100*/
		/*备用字段100*/
	char   user_field101[80+1];  /*备用字段101*/
		/*备用字段101*/
	char   user_field102[80+1];  /*备用字段102*/
		/*备用字段102*/
	char   user_field103[19+1];  /*备用字段103*/
		/*备用字段103*/
	char   user_field104[20+1];  /*备用字段104*/
		/*备用字段104*/
	char   user_field105[32+1];  /*备用字段105*/
		/*备用字段105*/
	char   user_field106[40+1];  /*备用字段106*/
		/*备用字段106*/
	char   user_field107[1+1];  /*备用字段107*/
		/*备用字段107*/
	char   user_field108[2+1];  /*备用字段108*/
		/*备用字段108*/
	char   user_field109[40+1];  /*备用字段109*/
		/*备用字段109*/
	char   user_field110[40+1];  /*备用字段110*/
		/*备用字段110*/
	char   user_field111[14+1];  /*备用字段111*/
		/*备用字段111*/
	char   user_field112[14+1];  /*备用字段112*/
		/*备用字段112*/
	int   jpa_version;  /*乐观锁*/
		/*乐观锁*/
	char   cust_no[20+1];  /*客户号*/
		/*客户号*/
	char   acct_no[20+1];  /*账户号*/
		/*账户号*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_APP_INFO;

#define SD_DATA  ICPS_WB_TM_APP_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  id, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field53, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field54, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  emb_logo, 0),\
	APP_DEFSDMEMBER(T_STRING,  gender, 0),\
	APP_DEFSDMEMBER(T_STRING,  nationality, 0),\
	APP_DEFSDMEMBER(T_STRING,  residency_country_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field55, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field56, 0),\
	APP_DEFSDMEMBER(T_STRING,  birthday, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field57, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field58, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field59, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field60, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field61, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field62, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field63, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field64, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field65, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field66, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field67, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field68, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field69, 0),\
	APP_DEFSDMEMBER(T_STRING,  cellphone, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field70, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field71, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field72, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field73, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field74, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field75, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field76, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field77, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field78, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field79, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field80, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field81, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field82, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field83, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field84, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field85, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field86, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field87, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field88, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field89, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field90, 4),\
	APP_DEFSDMEMBER(T_STRING,  user_field91, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field92, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field93, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field94, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field95, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field96, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field97, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field98, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field99, 0),\
	APP_DEFSDMEMBER(T_STRING,  pr_of_country, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field100, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field101, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field102, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field103, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field104, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field105, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field106, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field107, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field108, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field109, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field110, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field111, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field112, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  acct_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_APP_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_APP_INFO_H__*/
