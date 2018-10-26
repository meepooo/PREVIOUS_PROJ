/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_CUSTOMER.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_CUSTOMER (F_WB8.客户信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_CUSTOMER_H__
#define __ICPS_WB_TM_CUSTOMER_H__
typedef struct TDB_ICPS_WB_TM_CUSTOMER
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	char   org[12+1];  /*机构号*/
		/*机构号*/
	char   cust_id[20+1];  /*客户编号*/
		/*客户编号*/
	char   id_num[30+1];  /*证件号码*/
		/*证件号码*/
	char   id_type[1+1];  /*证件类型*/
		/*证件类型*/
	char   title[1+1];  /*称谓*/
		/*称谓*/
	char   name[80+1];  /*姓名*/
		/*姓名*/
	char   gender[1+1];  /*性别*/
		/*性别*/
	char   brith_date[8+1];  /*生日*/
		/*生日*/
	char   user_field177[1+1];  /*备用字段177*/
		/*备用字段177*/
	char   user_field178[20+1];  /*备用字段178*/
		/*备用字段178*/
	char   nationality[3+1];  /*国籍*/
		/*国籍*/
	char   pr_of_country[1+1];  /*是否永久居住*/
		/*是否永久居住*/
	char   residency_country_cd[3+1];  /*永久居住地国家代码*/
		/*永久居住地国家代码*/
	char   user_field179[1+1];  /*备用字段179*/
		/*备用字段179*/
	char   user_field180[1+1];  /*备用字段180*/
		/*备用字段180*/
	char   user_field181[1+1];  /*备用字段181*/
		/*备用字段181*/
	char   user_field182[200+1];  /*备用字段182*/
		/*备用字段182*/
	char   user_field183[20+1];  /*备用字段183*/
		/*备用字段183*/
	char   user_field184[1+1];  /*备用字段184*/
		/*备用字段184*/
	char   user_field185[1+1];  /*备用字段185*/
		/*备用字段185*/
	char   user_field186[14+1];  /*备用字段186*/
		/*备用字段186*/
	char   user_field187[1+1];  /*备用字段187*/
		/*备用字段187*/
	char   mobile_no[20+1];  /*移动电话*/
		/*移动电话*/
	char   user_field188[80+1];  /*备用字段188*/
		/*备用字段188*/
	char   user_field189[1+1];  /*备用字段189*/
		/*备用字段189*/
	int   user_field190;  /*备用字段190*/
		/*备用字段190*/
	char   language_ind[4+1];  /*语言代码*/
		/*语言代码*/
	char   user_field191[14+1];  /*备用字段191*/
		/*备用字段191*/
	double   user_field192;  /*备用字段192*/
		/*备用字段192*/
	char   user_field193[20+1];  /*备用字段193*/
		/*备用字段193*/
	char   user_field194[14+1];  /*备用字段194*/
		/*备用字段194*/
	char   user_field195[80+1];  /*备用字段195*/
		/*备用字段195*/
	char   user_field196[80+1];  /*备用字段196*/
		/*备用字段196*/
	char   user_field197[1+1];  /*备用字段197*/
		/*备用字段197*/
	char   user_field198[200+1];  /*备用字段198*/
		/*备用字段198*/
	char   user_field199[4+1];  /*备用字段199*/
		/*备用字段199*/
	char   user_field200[4+1];  /*备用字段200*/
		/*备用字段200*/
	char   user_field201[4+1];  /*备用字段201*/
		/*备用字段201*/
	char   user_field202[4+1];  /*备用字段202*/
		/*备用字段202*/
	char   user_field203[4+1];  /*备用字段203*/
		/*备用字段203*/
	char   user_field204[4+1];  /*备用字段204*/
		/*备用字段204*/
	char   user_field205[14+1];  /*备用字段205*/
		/*备用字段205*/
	char   user_field206[14+1];  /*备用字段206*/
		/*备用字段206*/
	char   user_field207[14+1];  /*备用字段207*/
		/*备用字段207*/
	char   user_field208[14+1];  /*备用字段208*/
		/*备用字段208*/
	char   user_field209[14+1];  /*备用字段209*/
		/*备用字段209*/
	char   user_field210[14+1];  /*备用字段210*/
		/*备用字段210*/
	int   user_field211;  /*备用字段211*/
		/*备用字段211*/
	int   user_field212;  /*备用字段212*/
		/*备用字段212*/
	int   user_field213;  /*备用字段213*/
		/*备用字段213*/
	int   user_field214;  /*备用字段214*/
		/*备用字段214*/
	int   user_field215;  /*备用字段215*/
		/*备用字段215*/
	int   user_field216;  /*备用字段216*/
		/*备用字段216*/
	char   user_field217[40+1];  /*备用字段217*/
		/*备用字段217*/
	char   user_field218[40+1];  /*备用字段218*/
		/*备用字段218*/
	char   user_field219[40+1];  /*备用字段219*/
		/*备用字段219*/
	char   user_field220[40+1];  /*备用字段220*/
		/*备用字段220*/
	char   user_field221[40+1];  /*备用字段221*/
		/*备用字段221*/
	char   user_field222[40+1];  /*备用字段222*/
		/*备用字段222*/
	double   user_field223;  /*备用字段223*/
		/*备用字段223*/
	double   user_field224;  /*备用字段224*/
		/*备用字段224*/
	double   user_field225;  /*备用字段225*/
		/*备用字段225*/
	double   user_field226;  /*备用字段226*/
		/*备用字段226*/
	double   user_field227;  /*备用字段227*/
		/*备用字段227*/
	double   user_field228;  /*备用字段228*/
		/*备用字段228*/
	char   user_field229[20+1];  /*备用字段229*/
		/*备用字段229*/
	char   emb_name[26+1];  /*拼音名*/
		/*拼音名*/
	int   jpa_version;  /*乐观锁版本号*/
		/*乐观锁版本号*/
	char   cust_limit_id[20+1];  /*客户额度ID*/
		/*客户额度ID*/
	char   last_modified_datetime[14+1];  /*修改时间*/
		/*修改时间*/
	char   user_field230[10+1];  /*备用字段230*/
		/*备用字段230*/
	char   user_field231[2+1];  /*备用字段231*/
		/*备用字段231*/
	char   surname[20+1];  /*姓氏*/
		/*姓氏*/
	char   user_field232[14+1];  /*备用字段232*/
		/*备用字段232*/
	char   user_field233[3+1];  /*备用字段233*/
		/*备用字段233*/
	char   user_field234[53+1];  /*备用字段234*/
		/*备用字段234*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_CUSTOMER;

#define SD_DATA  ICPS_WB_TM_CUSTOMER
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_STRING,  org, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_num, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  title, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  gender, 0),\
	APP_DEFSDMEMBER(T_STRING,  brith_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field177, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field178, 0),\
	APP_DEFSDMEMBER(T_STRING,  nationality, 0),\
	APP_DEFSDMEMBER(T_STRING,  pr_of_country, 0),\
	APP_DEFSDMEMBER(T_STRING,  residency_country_cd, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field179, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field180, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field181, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field182, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field183, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field184, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field185, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field186, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field187, 0),\
	APP_DEFSDMEMBER(T_STRING,  mobile_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field188, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field189, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field190, 0),\
	APP_DEFSDMEMBER(T_STRING,  language_ind, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field191, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field192, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field193, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field194, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field195, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field196, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field197, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field198, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field199, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field200, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field201, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field202, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field203, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field204, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field205, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field206, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field207, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field208, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field209, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field210, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field211, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field212, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field213, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field214, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field215, 0),\
	APP_DEFSDMEMBER(T_LONG,  user_field216, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field217, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field218, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field219, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field220, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field221, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field222, 0),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field223, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field224, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field225, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field226, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field227, 2),\
	APP_DEFSDMEMBER(T_DOUBLE,  user_field228, 2),\
	APP_DEFSDMEMBER(T_STRING,  user_field229, 0),\
	APP_DEFSDMEMBER(T_STRING,  emb_name, 0),\
	APP_DEFSDMEMBER(T_LONG,  jpa_version, 0),\
	APP_DEFSDMEMBER(T_STRING,  cust_limit_id, 0),\
	APP_DEFSDMEMBER(T_STRING,  last_modified_datetime, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field230, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field231, 0),\
	APP_DEFSDMEMBER(T_STRING,  surname, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field232, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field233, 0),\
	APP_DEFSDMEMBER(T_STRING,  user_field234, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_CUSTOMER)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_CUSTOMER_H__*/
