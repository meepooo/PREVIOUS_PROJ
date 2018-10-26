/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:住建部公积金前置系统
版    本:V2.0
操作系统:LINUX
数 据 库:ORACLE
文件名称:zjbgjj_msg.h
文件描述:响应信息 宏定义文件
项 目 组:
程 序 员:
发布日期:
修    订:
修改日期:
*******************************************************************/
/*
修改记录
修改日期:
修改内容:
修改人:
*/

#ifndef __ZJB_GJJ_MSG_H__
#define __ZJB_GJJ_MSG_H__

#define MSG_ZJB_GJJ_CALLFUNC_FAIL        "函数调用出错[%s]"
#define MSG_ZJB_GJJ_XMLOP                "XML相关操作失败"
#define MSG_ZJB_GJJ_COMMBUF              "COMMBUF相关操作失败"
#define MSG_ZJB_GJJ_MALLOC               "内存相关操作失败[%d]"
#define MSG_ZJB_GJJ_FILEOP               "文件相关操作失败[%s]"
#define MSG_ZJB_GJJ_DBOP                 "库表相关操作失败"
#define MSG_ZJB_GJJ_DBOP_NOTFOUND        "未找到相关记录"

#define MSG_ZJB_GJJ_BIZELEM_NOTNULL      "[%s]要素不能为空"
#define MSG_ZJB_GJJ_BIZELEM_UNVALID      "[%s]要素无效"
#define MSG_ZJB_GJJ_NODECHK_NULL         "[%s]节点不能为空"

#define MSG_ZJB_GJJ_EXEC_FLOW        "函数调用出错[%s]"

#define MSG_ZJB_GJJ_CHKSTS               "状态不符,请确认"
#define MSG_ZJB_GJJ_DEALING              "业务正在处理中,不允许再次触发"
#define MSG_ZJB_GJJ_BATCH_BREAK          "核心批量模式,数据提交核心成功"

#define MSG_ZJB_GJJ_ZIPFILE_LEN          "请求ZIP文件名长度不符"
#define MSG_ZJB_GJJ_ZIPFILE_ERR          "暂不支持该ZIP批次文件"

#endif


