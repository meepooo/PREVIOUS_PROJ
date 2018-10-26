/* *******************************************************************
版权所有:恒生电子股份有限公司
项目名称:住建部公积金前置系统
版    本:V2.0
操作系统:LINUX
数 据 库:ORACLE
文件名称:通用XML元素名称宏定义头文件
文件描述:zjbgjj_macro.h
项 目 组:银行第四事业部.应用集成产品部
程 序 员:
发布日期:2016-10-19
修    订:
修改日期:
******************************************************************** */

/*
修改记录
修改日期:
修改内容:
修改人:
 */

#ifndef __ZJB_GJJ_MACRO_H__
#define __ZJB_GJJ_MACRO_H__

/* 调用函数返回值*/
#define ZJB_GJJ_FUNCRET_SUCC           0             /*函数调用成功 */
#define ZJB_GJJ_FUNCRET_ONE            1             /*组件调用其他情况 */
#define ZJB_GJJ_FUNCRET_TWO            2             /*组件调用其他情况 */
#define ZJB_GJJ_FUNCRET_PARAERR        -1            /*输入参数有误*/
#define ZJB_GJJ_FUNCRET_RCDUVLD        -2            /*记录已过期*/
#define ZJB_GJJ_FUNCRET_KEYERR         -11           /*主键重复*/
#define ZJB_GJJ_FUNCRET_SQLERR         -12           /*SQL其他错误*/
#define ZJB_GJJ_FUNCRET_NOTFOUND       1403         /*数据未找到*/
#define ZJB_GJJ_FUNCRET_FAIL           -99           /*函数通用错误 */

#define ZJB_GJJ_STRING_BLANK           " "           /*空格*/
#define ZJB_GJJ_COMMIT_CNT             1000          /*1k笔提交一次事务*/
/*XML节点属性 */
#define ZJB_GJJ_NODEATTR_STRING        "1"             /*  字符串 */
#define ZJB_GJJ_NODEATTR_NUMBER        "0"             /*  数字金额 */
/*XML节点是否必须存在*/
#define XML_NODE_NOTNULL           1             /*  XML节点必须存在     */
#define XML_NODE_NULL              0             /*  XML节点可以为空     */
#define XML_NODE_EXIST             1             /*  检查发现XML节点存在 */
#define XML_NODE_NOTFOUND          203           /*  节点不存在 */


/* SQLCODE DCI返回值判断*/
#define ZJB_GJJ_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, sErrInfo)   if( iRet < 0 ) \
        { \
            LOG(LM_STD, Fmtmsg("SQLERR[%d][%s]", iRet, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* 功能函数返回值判断 */
#define ZJB_GJJ_FUNCCHK_NOTSUCC(lXmlhandle, iRet, sErrInfo)   if( iRet != 0 ) \
        { \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ZJB_GJJ_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* 功能函数返回值判断(过滤登记表主键重复) */
#define ZJB_GJJ_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, sErrInfo)   if( iRet <0 && iRet != ZJB_GJJ_FUNCRET_KEYERR ) \
        { \
            DCICommit(); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ZJB_GJJ_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* 功能函数返回值判断(出错强制事务回滚) */
#define ZJB_GJJ_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, sErrInfo)   if( iRet != 0 ) \
        { \
            DCIRollback(); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ZJB_GJJ_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* 对空字符串数组赋空格,sField为字符串数组类型*/
#define ZJB_GJJ_FIELD_SETNULLTOBLANK( sField )   \
        { \
          if (sField[0] == '\0') \
          { \
              pstrcopy(sField, ZJB_GJJ_STRING_BLANK, sizeof(sField)); \
          } \
        }

/* 变量间赋值 */
#define ZJB_GJJ_PSTRCOPY( sYbhqzDes, sYbhqzSrc )   \
        { \
          pstrcopy(sYbhqzDes, sYbhqzSrc, sizeof(sYbhqzDes)); \
        }

/* 目的串为空则赋值 */
#define ZJB_GJJ_PSTRCOPY_NULL( sYbhqzDes, sYbhqzSrc )   if ( sYbhqzDes[0] == '\0') \
        { \
          pstrcopy(sYbhqzDes, sYbhqzSrc, sizeof(sYbhqzDes)); \
        }

/* 业务要素不为空返回值判断 */
#define ZJB_GJJ_NODECHK_NOTNULL(lXmlhandle, iRet, sCnElemName)   if( iRet < 0 ) \
        { \
            fpub_SetMsg( lXmlhandle, MID_ZJB_GJJ_BIZELEM_NOTNULL, Fmtmsg(MSG_ZJB_GJJ_BIZELEM_NOTNULL, sCnElemName) ); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ZJB_GJJ_NODECHK_NULL, sCnElemName), fpub_GetCompname(lXmlhandle)); \
        }

/* 取字符串值不允许为空 */
#define ZJB_GJJ_GETXMLSTR_NOTNULL( sXmlNode, sField, sCnField )   \
        { \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sXmlNode, ZJB_GJJ_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NOTNULL); \
          ZJB_GJJ_NODECHK_NOTNULL(lXmlhandle, iRet, sCnField); \
        }

/* 取字符串值允许为空 */
#define ZJB_GJJ_GETXMLSTR_NULL( sXmlNode, sField, sCnField )   \
        { \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sXmlNode, ZJB_GJJ_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NULL); \
        }

/* 取字符串值不允许为空(多条) */
#define ZJB_GJJ_GETXMLSTR_NOTNULL_MULTI( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                              \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i);                      \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, ZJB_GJJ_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NOTNULL); \
          ZJB_GJJ_NODECHK_NOTNULL(lXmlhandle, iRet, sCnField); \
        }

/* 取字符串值允许为空(多条) */
#define ZJB_GJJ_GETXMLSTR_NULL_MULTI( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                          \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i);                  \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, ZJB_GJJ_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NULL); \
        }

#endif


