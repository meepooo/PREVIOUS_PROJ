/* *******************************************************************
版权所有:恒生电子股份有限公司
项目名称:恒生公安部网络查控前置系统
版    本:V2.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:DB2
文件名称:通用XML元素名称宏定义头文件
文件描述:icps_jb_macro.h
项 目 组:银行第四事业部.应用集成产品部
程 序 员:
发布日期:2016-01-22
修    订:
修改日期:
******************************************************************** */

/*
修改记录
修改日期:
修改内容:
修改人:
 */

#ifndef __ICPS_JB_MACRO_H__
#define __ICPS_JB_MACRO_H__

/* 调用函数返回值*/
#define ICPS_JB_FUNCRET_SUCC           0             /*函数调用成功 */
#define ICPS_JB_FUNCRET_ONE            1             /*组件调用其他情况 */
#define ICPS_JB_FUNCRET_TWO            2             /*组件调用其他情况 */
#define ICPS_JB_FUNCRET_PARAERR        -1            /*输入参数有误*/
#define ICPS_JB_FUNCRET_RCDUVLD        -2            /*记录已过期*/
#define ICPS_JB_FUNCRET_KEYERR         -11           /*主键重复*/
#define ICPS_JB_FUNCRET_SQLERR         -12           /*SQL其他错误*/
#define ICPS_JB_FUNCRET_NOTFOUND       1403         /*数据未找到*/
#define ICPS_JB_FUNCRET_FAIL           -99           /*函数通用错误 */

#define ICPS_JB_STRING_BLANK           " "           /*空格*/
#define ICPS_JB_COMMIT_CNT             1000          /*1k笔提交一次事务*/
/*XML节点属性 */
#define ICPS_JB_NODEATTR_STRING        "1"             /*  字符串 */
#define ICPS_JB_NODEATTR_NUMBER        "0"             /*  数字金额 */
/*XML节点是否必须存在*/
#define XML_NODE_NOTNULL           1             /*  XML节点必须存在     */
#define XML_NODE_NULL              0             /*  XML节点可以为空     */
#define XML_NODE_EXIST             1             /*  检查发现XML节点存在 */
#define XML_NODE_NOTFOUND          203           /*  节点不存在 */
/*响应码 */
#define MID_ICPS_JB_XMLOP                   9003       /* XML相关操作失败*/
#define MID_ICPS_JB_COMMBUF                 9004       /* COMMBUF相关操作失败*/
#define MID_ICPS_JB_MALLOC                  9005       /* 内存相关操作失败*/
#define MID_ICPS_JB_FILEOP                  9006       /* 文件相关操作失败*/
#define MID_ICPS_JB_DBOP                    9001       /* 库表相关操作失败*/
#define MID_ICPS_JB_DBOP_NOTFOUND           9002       /* 未找到相关记录*/
#define MID_ICPS_JB_BIZELEM_NOTNULL     9007       /* 业务请求要素不能为空*/
/*响应信息 */
#define MSG_ICPS_JB_CALLFUNC_FAIL        "函数调用出错[%s]"
#define MSG_ICPS_JB_XMLOP                "XML相关操作失败"
#define MSG_ICPS_JB_COMMBUF              "COMMBUF相关操作失败"
#define MSG_ICPS_JB_MALLOC               "内存相关操作失败[%d]"
#define MSG_ICPS_JB_FILEOP               "文件相关操作失败[%s]"
#define MSG_ICPS_JB_DBOP                 "库表相关操作失败"
#define MSG_ICPS_JB_DBOP_NOTFOUND        "未找到相关记录"
#define MSG_ICPS_JB_BIZELEM_NOTNULL      "[%s]要素不能为空"
#define MSG_ICPS_JB_NODECHK_NULL         "[%s]节点不能为空"


/* SQLCODE DCI返回值判断*/
#define ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, sErrInfo)   if( iRet < 0 ) \
        { \
            LOG(LM_STD, Fmtmsg("SQLERR[%d][%s]", iRet, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* 功能函数返回值判断 */
#define ICPS_JB_FUNCCHK_NOTSUCC(lXmlhandle, iRet, sErrInfo)   if( iRet != 0 ) \
        { \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ICPS_JB_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* 功能函数返回值判断(过滤登记表主键重复) */
#define ICPS_JB_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, sErrInfo)   if( iRet <0 && iRet != ICPS_JB_FUNCRET_KEYERR ) \
        { \
            DCICommit(); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ICPS_JB_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* 功能函数返回值判断(出错强制事务回滚) */
#define ICPS_JB_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, sErrInfo)   if( iRet != 0 ) \
        { \
            DCIRollback(); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ICPS_JB_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* 对空字符串数组赋空格,sField为字符串数组类型*/
#define ICPS_JB_FIELD_SETNULLTOBLANK( sField )   \
        { \
          if (sField[0] == '\0') \
          { \
              pstrcopy(sField, ICPS_JB_STRING_BLANK, sizeof(sField)); \
          } \
        }

/* 变量间赋值 */
#define ICPS_JB_PSTRCOPY( sYbhqzDes, sYbhqzSrc )   \
        { \
          pstrcopy(sYbhqzDes, sYbhqzSrc, sizeof(sYbhqzDes)); \
        }

/* 目的串为空则赋值 */
#define ICPS_JB_PSTRCOPY_NULL( sYbhqzDes, sYbhqzSrc )   if ( sYbhqzDes[0] == '\0') \
        { \
          pstrcopy(sYbhqzDes, sYbhqzSrc, sizeof(sYbhqzDes)); \
        }

/* 业务要素不为空返回值判断 */
#define ICPS_JB_NODECHK_NOTNULL(lXmlhandle, iRet, sCnElemName)   if( iRet < 0 ) \
        { \
            fpub_SetMsg( lXmlhandle, MID_ICPS_JB_BIZELEM_NOTNULL, Fmtmsg(MSG_ICPS_JB_BIZELEM_NOTNULL, sCnElemName) ); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ICPS_JB_NODECHK_NULL, sCnElemName), fpub_GetCompname(lXmlhandle)); \
        }

/* 取字符串值不允许为空 */
#define ICPS_JB_GETXMLSTR_NOTNULL( sXmlNode, sField, sCnField )   \
        { \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sXmlNode, ICPS_JB_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NOTNULL); \
          ICPS_JB_NODECHK_NOTNULL(lXmlhandle, iRet, sCnField); \
        }

/* 取字符串值允许为空 */
#define ICPS_JB_GETXMLSTR_NULL( sXmlNode, sField, sCnField )   \
        { \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sXmlNode, ICPS_JB_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NULL); \
        }

/* 取字符串值不允许为空(多条) */
#define ICPS_JB_GETXMLSTR_NOTNULL_MULTI( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                              \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i);                      \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, ICPS_JB_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NOTNULL); \
          ICPS_JB_NODECHK_NOTNULL(lXmlhandle, iRet, sCnField); \
        }

/* 取字符串值允许为空(多条) */
#define ICPS_JB_GETXMLSTR_NULL_MULTI( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                          \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i);                  \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, ICPS_JB_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NULL); \
        }

#endif


