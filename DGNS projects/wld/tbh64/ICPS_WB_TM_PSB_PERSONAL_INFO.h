/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:ICPS_WB_TM_PSB_PERSONAL_INFO.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[wangzh14925]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WB_TM_PSB_PERSONAL_INFO (F_WB19.身份信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WB_TM_PSB_PERSONAL_INFO_H__
#define __ICPS_WB_TM_PSB_PERSONAL_INFO_H__
typedef struct TDB_ICPS_WB_TM_PSB_PERSONAL_INFO
{
	char   busi_date[8+1];  /*业务日期*/
		/*业务日期*/
	int   file_order;  /*文件序号*/
		/*文件序号*/
	int   id;  /*ID*/
		/*ID*/
	char   app_no[20+1];  /*申请件编号*/
		/*申请件编号*/
	char   id_type[1+1];  /*证件类型*/
		/*证件类型*/
	char   certi_no[18+1];  /*身份证号*/
		/*身份证号*/
	char   name[90+1];  /*姓名*/
		/*姓名*/
	char   gender[1+1];  /*性别*/
		/*性别*/
	char   birth_date[14+1];  /*出生日期*/
		/*出生日期*/
	char   marital_status[2+1];  /*婚姻状况*/
		/*婚姻状况*/
	char   mobile_no[20+1];  /*手机号码*/
		/*手机号码*/
	char   home_phone[30+1];  /*家庭电话*/
		/*家庭电话*/
	char   unit_phone[30+1];  /*单位电话*/
		/*单位电话*/
	char   qualification[2+1];  /*学历*/
		/*学历*/
	char   degree[2+1];  /*学位*/
		/*学位*/
	char   address[700+1];  /*通讯地址*/
		/*通讯地址*/
	char   reside_addr[700+1];  /*户籍地址*/
		/*户籍地址*/
	char   mate_certp[1+1];  /*配偶证件类型*/
		/*配偶证件类型*/
	char   mate_cerno[18+1];  /*配偶证件号码*/
		/*配偶证件号码*/
	char   mate_name[30+1];  /*配偶姓名*/
		/*配偶姓名*/
	char   mate_corp[500+1];  /*配偶工作单位*/
		/*配偶工作单位*/
	char   mate_phone[30+1];  /*配偶联系电话*/
		/*配偶联系电话*/
	char   addr[700+1];  /*居住地址*/
		/*居住地址*/
	char   reside_state[2+1];  /*居住状况*/
		/*居住状况*/
	char   comp_nm[700+1];  /*工作单位*/
		/*工作单位*/
	char   unit_addr[700+1];  /*单位地址*/
		/*单位地址*/
	char   profession[2+1];  /*职业*/
		/*职业*/
	char   comp_trade[2+1];  /*行业*/
		/*行业*/
	char   position[2+1];  /*职务*/
		/*职务*/
	char   teach_pose[2+1];  /*职称*/
		/*职称*/
	char   work_date[4+1];  /*本单位工作起始年份*/
		/*本单位工作起始年份*/
	char   infodate[14+1];  /*信息更新日期*/
		/*信息更新日期*/
	char   create_time[14+1];  /*创建时间*/
		/*创建时间*/
	char   is_check_flag[1+1];  /*参与对账标识*/
		/*参与对账标识*/
	char   extend_param1[100+1];  /*扩展1*/
		/*扩展1*/
	char   extend_param2[250+1];  /*扩展2*/
		/*扩展2*/
	char   extend_param3[40+1];  /*扩展3*/
		/*扩展3*/

}ICPS_WB_TM_PSB_PERSONAL_INFO;

#define SD_DATA  ICPS_WB_TM_PSB_PERSONAL_INFO
#define SD_MEMBERS \ 
	APP_DEFSDMEMBER(T_STRING,  busi_date, 0),\
	APP_DEFSDMEMBER(T_LONG,  file_order, 0),\
	APP_DEFSDMEMBER(T_LONG,  id, 0),\
	APP_DEFSDMEMBER(T_STRING,  app_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  id_type, 0),\
	APP_DEFSDMEMBER(T_STRING,  certi_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  name, 0),\
	APP_DEFSDMEMBER(T_STRING,  gender, 0),\
	APP_DEFSDMEMBER(T_STRING,  birth_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  marital_status, 0),\
	APP_DEFSDMEMBER(T_STRING,  mobile_no, 0),\
	APP_DEFSDMEMBER(T_STRING,  home_phone, 0),\
	APP_DEFSDMEMBER(T_STRING,  unit_phone, 0),\
	APP_DEFSDMEMBER(T_STRING,  qualification, 0),\
	APP_DEFSDMEMBER(T_STRING,  degree, 0),\
	APP_DEFSDMEMBER(T_STRING,  address, 0),\
	APP_DEFSDMEMBER(T_STRING,  reside_addr, 0),\
	APP_DEFSDMEMBER(T_STRING,  mate_certp, 0),\
	APP_DEFSDMEMBER(T_STRING,  mate_cerno, 0),\
	APP_DEFSDMEMBER(T_STRING,  mate_name, 0),\
	APP_DEFSDMEMBER(T_STRING,  mate_corp, 0),\
	APP_DEFSDMEMBER(T_STRING,  mate_phone, 0),\
	APP_DEFSDMEMBER(T_STRING,  addr, 0),\
	APP_DEFSDMEMBER(T_STRING,  reside_state, 0),\
	APP_DEFSDMEMBER(T_STRING,  comp_nm, 0),\
	APP_DEFSDMEMBER(T_STRING,  unit_addr, 0),\
	APP_DEFSDMEMBER(T_STRING,  profession, 0),\
	APP_DEFSDMEMBER(T_STRING,  comp_trade, 0),\
	APP_DEFSDMEMBER(T_STRING,  position, 0),\
	APP_DEFSDMEMBER(T_STRING,  teach_pose, 0),\
	APP_DEFSDMEMBER(T_STRING,  work_date, 0),\
	APP_DEFSDMEMBER(T_STRING,  infodate, 0),\
	APP_DEFSDMEMBER(T_STRING,  create_time, 0),\
	APP_DEFSDMEMBER(T_STRING,  is_check_flag, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param1, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param2, 0),\
	APP_DEFSDMEMBER(T_STRING,  extend_param3, 0)


	APP_DECLAREFIELDS(SD_ICPS_WB_TM_PSB_PERSONAL_INFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WB_TM_PSB_PERSONAL_INFO_H__*/
