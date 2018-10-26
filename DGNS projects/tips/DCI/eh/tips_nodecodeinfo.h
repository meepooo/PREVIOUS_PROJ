/***********************************************************************
版权所有:恒生电子TIPS专用前置产品组
项目名称:TIPS专用前置产品
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:INFORMIX
文 件 名:tips_nodecodeinfo.eh
文件描述:tips_nodecodeinfo;结构定义数据库开发嵌C头文件
项 目 组:TIPS专用前置产品组
程 序 员:
发布时间:2009-3-5 14:07:20 [By GenEHFromPDMTools]
修    订:
修改时间:
************************************************************************
表    名:tips_nodecodeinfo (节点代码)
说    明:节点代码

************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __TIPS_NODECODEINFO_EH__
#define __TIPS_NODECODEINFO_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_NODECODEINFO
{
  char   nodecode[12+1];              /*节点代码*/
              /*节点代码*/
  char   nodename[60+1];              /*节点名称*/
              /*节点名称*/
  char   ofnodetype[1+1];              /*节点所属类型*/
              /*节点所属类型*/
  char   nodedn[150+1];              /*节点认证标识*/
              /*节点认证标识*/
  char   opersign[1+1];              /*操作标志*/
              /*操作标志
                用于标识数据更新的类型，详见附录代码表*/
  char   effectdate[10+1];              /*生效日期*/
              /*生效日期
                此条记录的生效日期，更新类型为增加时，为增加日期；更新类型为更正时，为更新日期；更新类型为删除时，为失效日期*/
  char   updatearea[10+1];              /*更新范围*/
              /*更新范围
                国库代码*/
  char   nodestatus[1+1];              /*节点状态*/
              /*节点状态(自增加字段)
                1登录
                2故障
                3签退
                4停用
                */
}SDB_TIPS_NODECODEINFO;

#define SD_DATA SDB_TIPS_NODECODEINFO
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,nodecode,0),\
  DEFSDMEMBER(T_STRING,nodename,0),\
  DEFSDMEMBER(T_STRING,ofnodetype,0),\
  DEFSDMEMBER(T_STRING,nodedn,0),\
  DEFSDMEMBER(T_STRING,opersign,0),\
  DEFSDMEMBER(T_STRING,effectdate,0),\
  DEFSDMEMBER(T_STRING,updatearea,0),\
  DEFSDMEMBER(T_STRING,nodestatus,0)
	DECLAREFIELDS(SD_TIPS_NODECODEINFO)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_NODECODEINFO_EH__*/
