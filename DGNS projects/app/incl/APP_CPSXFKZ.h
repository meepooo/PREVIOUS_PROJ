/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_CPSXFKZ.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_CPSXFKZ (产品手续费控制表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_CPSXFKZ_H__
#define __APP_CPSXFKZ_H__
typedef struct TDB_APP_CPSXFKZ
{
  char   cpdm[16+1];              /*产品代码*/
              /*产品代码*/
  char   xh[2+1];              /*序号*/
              /*产品有多个控制属性时，各属性自动生成序号排列，从1开始，与关系表的条件位置对应*/
  char   kzsx[32+1];              /*控制属性节点名*/
              /*如：/app/sxf/khlx*/
  char   kzsxm[40+1];              /*控制属性说名*/
              /*控制属性的中文说明*/
  char   sxlylx[1+1];              /*属性来源类型*/
              /*控制属性值的来源，1 数据库  数据字典，用于维护手续费关系时选择控制属性的输入来源*/
  char   kzsxly[40+1];              /*控制属性来源*/
              /*如果来源类型为 数据字典，存放字典键值;如果来源是数据库，存放库名和字段名中间逗号隔开,如 T_ORG,org_i  表示控制属性来自机构表的机构号*/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
  char   extfld1[40+1];              /*扩展字段1*/
              /*说明 */
  char   extfld2[40+1];              /*扩展字段2*/
              /*说明 */
}APP_CPSXFKZ;

#define SD_DATA  APP_CPSXFKZ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  xh, 0),\
	DEFSDMEMBER(T_STRING,  kzsx, 0),\
	DEFSDMEMBER(T_STRING,  kzsxm, 0),\
	DEFSDMEMBER(T_STRING,  sxlylx, 0),\
	DEFSDMEMBER(T_STRING,  kzsxly, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_APP_CPSXFKZ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPSXFKZ_H__*/

