/**********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V2.1.0.1
操作系统:AIX LINUX
数 据 库:
文 件 名:agent_mid.h
文件描述:系统信息宏定义头文件
项 目 组:中间业务产品研发组
程 序 员:中间业务产品研发组
发布时间:2011年11月1日
**********************************************************************/
/*
修改记录
修改日期:
修改内容:
修改人:
*/
#ifndef __AGENT_MSG_H__
#define __AGENT_MSG_H__

#define MSG_AGENT_NOYWBH              "AGENT:代收付无此业务编号"
#define MSG_AGENT_NOYWLX              "AGENT:代收付无此业务类型"
#define MSG_AGENT_YWLX_ZT             "AGENT:本业务类型状态无效"
#define MSG_AGENT_YWLX                "AGENT:本业务类型状态非法"
#define MSG_AGENT_YWBH_ZT             "AGENT:本业务编号状态无效"
#define MSG_AGENT_YWBH                "AGENT:本业务编号状态非法"
#define MSG_AGENT_DRLS_TJ             "AGENT:统计代收付应用流水失败"
#define MSG_AGENT_ZJMXDZ_CURERR       "AGENT:获取主机流水游标定义错误" 
#define MSG_AGENT_ZJMXDZ_OPENERR      "AGENT:打开主机流水游标错误"
#define MSG_AGENT_ZJMXDZ_DRLSERR      "AGENT:获取平台流水游标定义错误"
#define MSG_AGENT_DZBPB_INSERT        "AGENT:记录对账不平表失败"
#define MSG_AGENT_ZJMXDZ_DRLSOPEN     "AGENT:获取平台流水游标打开错误"
#define MSG_AGENT_DRLS_INSERT         "AGENT:记录当日流水表失败"
#define MSG_AGENT_DRLS_UPDATE         "AGENT:更新当日流水表失败"
#define MSG_AGENT_DRLS_UNCHECK        "AGENT:有未和主机对账记录"
#define MSG_AGENT_DRLS_UNPROC         "AGENT:有未处理同主机不平流水"
#define MSG_AGENT_DZBPB_QUYFAIL       "AGENT:查询对账不平流水失败"
#define MSG_AGENT_DZBPB_NOTEXIST      "AGENT:无此不平流水信息"
#define MSG_AGENT_YWRQLX_COMMON       "AGENT:业务日期类型为公有,无需单独日切" 
#define MSG_AGENT_DRLS_QUYFAIL        "AGENT:查询当日流水失败"
#define MSG_AGENT_DRLS_NOTFOUND        "AGENT:无此流水号对应的流水"
#define MSG_AGENT_REPORT_CURERR       "AGENT:汇总报表定义流水游标错误"
#define MSG_AGENT_REPORT_OPENERR      "AGENT:汇总报表打开流水游标错误"
#define MSG_AGENT_REPORT_YWBHERR      "AGENT:查询业务编号表失败"
#define MSG_AGENT_QUERY_MODEERR       "AGENT:系统不支持该查询模式"
#define MSG_AGENT_QUERY_PQRYERR       "AGENT:分页查询失败"
#define MSG_AGENT_REPEAT_SIGN         "AGENT:已签到或者尚未签退"
#define MSG_AGENT_REPEAT_UNSIGN       "AGENT:已签退或者尚未签到"
#define MSG_AGENT_YWBH_NONEED_SIGN    "AGENT:产品不控制签到签退"
#define MSG_AGENT_BILLNOTFOUND        "AGENT:发票信息不存在"
#define MSG_AGENT_PZXX_INSERT         "AGENT:插入发票信息失败,[%d]"
#define MSG_AGENT_PZXX_UPDATE         "AGENT:更新发票信息失败,[%d]"
#define MSG_AGENT_PZXX_DELETE         "AGENT:删除发票信息失败,[%d]"
#define MSG_AGENT_DRLS_CANCEL         "AGENT:撤销当日流水表失败,[%d]"
#define MSG_AGENT_DRLS_REPEAL         "AGENT:冲正当日流水表失败,[%d]"
#define MSG_AGENT_SERIAL_ZT           "AGENT:流水状态不正常"
#define MSG_AGENT_CANCEL_TELLER       "AGENT:撤销非本交易柜员"
#define MSG_AGENT_SERIAL_NOTFOUND     "AGENT:流水不存在"
#define MSG_AGENT_BILL_NOTVAL         "AGENT:发票信息不存在或已打印"
#define MSG_AGENT_CPRQ_SAME           "AGENT:业务日期同日切后日期相同 "AGENT:
#define MSG_AGENT_DRLS_NULL           "AGENT:当日流水号为空"
#define MSG_AGENT_BILL_QUYCOND        "AGENT:发票查询，帐号,客户号,流水号不能同时为空"
#define MSG_AGENT_RZZT_INSERT         "AGENT:插入日终状态流水表错误"
#define MSG_AGENT_RZZT_UPDATE         "AGENT:更新日终状态流水表错误"
#define MSG_AGENT_ZJDZSB              "AGENT:主机对账失败,正在对账中"
#define MSG_AGENT_DSFDZSB             "AGENT:第三方对账失败,正在对账中"
#define MSG_AGENT_QSRQ_NULL           "AGENT:起始日期为空"

#endif                                                                               
