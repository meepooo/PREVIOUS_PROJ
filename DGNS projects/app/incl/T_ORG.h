/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:t_org.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:t_org (机构信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __T_ORG_H__
#define __T_ORG_H__
typedef struct TDB_T_ORG
{
  char   org_id[16+1];              /*机构号*/
              /*主键*/
  char   org_name[50+1];              /*机构名称*/
              /**/
  char   org_desc[60+1];              /*机构描述*/
              /**/
  char   org_type[1+1];              /*机构类别*/
              /*来自于数据字典表 0:交易机构 1:非交易机构*/
  char org_level[1+1];              /*机构级别*/
              /**/
  char   above_org_id[16+1];              /*上级机构号*/
              /**/
  char   inner_org_id[27+1];              /*内部机构标识*/
              /*内部机构标识用于程序内部查询方便，内部标识符以100为最上级，往下一级扩展如100100,100100100,以此类推*/
  char   tel[32+1];              /*机构电话*/
              /**/
  char   email[50+1];              /*电子邮箱*/
              /**/
  char   org_adress[120+1];              /*机构地址*/
              /**/
  char   bak1[30+1];              /*备用信息1*/
              /**/
  char   bak2[60+1];              /*备用信息2*/
              /**/
  char   bak3[120+1];              /*备用信息3*/
              /**/
}T_ORG;

#define SD_DATA  T_ORG
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  org_id, 0),\
	DEFSDMEMBER(T_STRING,  org_name, 0),\
	DEFSDMEMBER(T_STRING,  org_desc, 0),\
	DEFSDMEMBER(T_STRING,  org_type, 0),\
	DEFSDMEMBER(T_STRING,  org_level, 0),\
	DEFSDMEMBER(T_STRING,  above_org_id, 0),\
	DEFSDMEMBER(T_STRING,  inner_org_id, 0),\
	DEFSDMEMBER(T_STRING,  tel, 0),\
	DEFSDMEMBER(T_STRING,  email, 0),\
	DEFSDMEMBER(T_STRING,  org_adress, 0),\
	DEFSDMEMBER(T_STRING,  bak1, 0),\
	DEFSDMEMBER(T_STRING,  bak2, 0),\
	DEFSDMEMBER(T_STRING,  bak3, 0)


	DECLAREFIELDS(SD_T_ORG)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __T_ORG_H__*/
