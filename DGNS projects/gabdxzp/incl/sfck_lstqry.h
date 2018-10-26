/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:恒生司法查控前置系统
版    本:V2.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:ORACLE\INFORMIX\DB2
文件名称:sfck_lstqry.h
文件描述:列表查询函数头文件
项 目 组:
程 序 员:
发布日期:2016-02-26
修    订:
修改日期:
*********************************************************************/
/*  
修改记录
修改日期:
修改内容:
修改人:
*/

#ifndef __SFCK_LSTQRY_H__
#define __SFCK_LSTQRY_H__
/* 8通用查询 */

#define XMLNM_STARTNUM                 "/sfxt/startnum"                   /* 起始笔数   */
#define XMLNM_QUERYNUM                 "/sfxt/querynum"                   /* 查询笔数   */
#define XMLNM_LISTQRYTYPE              "/sfxt/qrytype"                    /*列表查询类型*/
#define XMLNM_RSPTYPE                  "/sfxt/rsptype"                    /*返回方式*/
#define XMLNM_SQL                      "/sfxt/qrysql"                     /*列表查询语句*/
#define XMLNM_RESP_LISTQRY             "/sfxt/resp/db|%d/%s"              /*列表查询返回结点*/
#define XMLNM_RESP_TOTALNUM            "/sfxt/resp/totalnum"              /* 总笔数     */
#define XMLNM_RESP_SURPNUM             "/sfxt/resp/surpnum"               /* 剩余笔数   */
#define XMLNM_RESP_REALNUM             "/sfxt/resp/realnum"               /* 实际返回笔数 */
#define XMLNM_RESP_STARTNUM            "/sfxt/resp/startnum"              /* 起始笔数   */
#define XMLNM_RESP_QUERYNUM            "/sfxt/resp/querynum"              /* 查询笔数 */

#define XMLNM_RESP_FILEFLAG            "/sfxt/resp/fileflag"              /* 文件标识   */
#define XMLNM_RESP_FILENAME            "/sfxt/resp/filename"              /* 文件名称   */


#endif
