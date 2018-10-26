/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:BATCH_WBWJDJ.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:BATCH_WBWJDJ (批量业务外部文件登记表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __BATCH_WBWJDJ_H__
#define __BATCH_WBWJDJ_H__
typedef struct TDB_BATCH_WBWJDJ
{
  char   djrq[8+1];/*登记日期*/
  /**/
  long    djlsh;/*登记流水号*/
  /**/
  char   djsj[6+1];/*登记时间*/
  /**/
  char   ywbh[16+1];/*业务编号*/
              /**/
  char   djjg[16+1];              /*登记机构*/
              /**/
  char   djgy[16+1];              /*登记柜员*/
              /**/
  char   shjg[16+1];              /*审核机构*/
              /**/
  char   shgy[16+1];              /*审核柜员*/
              /**/
  char   shpch[32+1];              /*商户批次号*/
              /**/
  char   pkrq[8+1];              /*批扣日期*/
              /**/
  char   ptpch[8+1];              /*平台批次号*/
              /**/
  char   lpwjlj[254+1];              /*来盘文件路径*/
              /**/
  char   lpwjm[60+1];              /*来盘文件名*/
              /**/
  char   zbs[8+1];              /*总笔数*/
              /**/
  double  zje;              /*总金额*/
              /**/
  long    threadno;              /*线程数*/
              /*（高级选项默认为1）*/
  char   taskmode[1+1];              /*任务开始方式*/
              /*1：立即，2：手动（默认为1）*/
  char   pczt[1+1];              /*批次状态*/
              /*1：正在上传，2：就绪，3：正在处理，4：已返回，5：处理失败，X：撤销*/
  char   shzt[1+1];              /*审核状态*/
              /*0：审核通过，1：未审核，2：审核失败*/
  char   note[128+1];              /*注释*/
 
  long    breakdata;                  /* */

  char   extfld1[40+1];              /*扩展字段一*/
              /**/
  char   extfld2[40+1];              /*扩展字段二*/
              /**/
  char   extfld3[40+1];              /*扩展字段三*/
              /**/

}BATCH_WBWJDJ;

#define SD_DATA  BATCH_WBWJDJ
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  djrq, 0),\
	DEFSDMEMBER(T_LONG,  djlsh, 0),\
	DEFSDMEMBER(T_STRING,  djsj, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  djjg, 0),\
	DEFSDMEMBER(T_STRING,  djgy, 0),\
	DEFSDMEMBER(T_STRING,  shjg, 0),\
	DEFSDMEMBER(T_STRING,  shgy, 0),\
	DEFSDMEMBER(T_STRING,  shpch, 0),\
	DEFSDMEMBER(T_STRING,  pkrq, 0),\
	DEFSDMEMBER(T_STRING,  ptpch, 0),\
	DEFSDMEMBER(T_STRING,  lpwjlj, 0),\
	DEFSDMEMBER(T_STRING,  lpwjm, 0),\
	DEFSDMEMBER(T_STRING,  zbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  zje, 2),\
	DEFSDMEMBER(T_LONG,  threadno, 0),\
	DEFSDMEMBER(T_STRING,  taskmode, 0),\
	DEFSDMEMBER(T_STRING,  pczt, 0),\
	DEFSDMEMBER(T_STRING,  shzt, 0),\
	DEFSDMEMBER(T_STRING,  note, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0)


	DECLAREFIELDS(SD_BATCH_WBWJDJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_WBWJDJ_H__*/
