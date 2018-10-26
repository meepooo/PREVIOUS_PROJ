/**********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V1.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:
文 件 名:ICC_PABFE.h
文件描述:系统信息宏定义头文件
项 目 组:中间业务产品发展部研发组
程 序 员:中间业务产品发展部研发组
发布时间:2013年3月12日
修 订:中间业务产品发展部研发组
修改时间:2013年3月12日
**********************************************************************/
#ifndef __PAB_ICC_DLCG_ERRMSG_H__
#define __PAB_ICC_DLCG_ERRMSG_H__

#define BFE_ERR_DLCG_SECINFO        "FE0701"     /*登记券商信息表失败*/
#define BFE_ERR_DLCG_CHKINFOLOAD    "FE0702"     /*登记对账明细表失败*/
#define BFE_ERR_DLCG_APPOINTSEL     "FE0703"     /*获取预指定关系表信息失败*/
#define BFE_ERR_DLCG_APPOINTLOAD    "FE0704"     /*登记预指定关系表失败*/
#define BFE_ERR_DLCG_UPDAPTSTAT     "FE0705"     /*更新预指定关系表对账状态失败*/
#define BFE_ERR_DLCG_CHKERROR       "FE0706"     /*对账异常*/
#define BFE_ERR_DLCG_APPOINTNO      "FE0707"     /*预指定关系不存在*/
#define BFE_ERR_DLCG_CHKACCTNO      "FE0708"     /*原银行帐号不符*/
#define BFE_ERR_DLCG_CHKCERTTYPE    "FE0709"     /*证件类型不符*/
#define BFE_ERR_DLCG_CHKCERTNO      "FE0710"     /*证件号码不符*/
#define BFE_ERR_DLCG_CHKCUSTTYPE    "FE0711"     /*商户类型不符*/
#define BFE_ERR_DLCG_APPOINTYBCX    "FE0712"     /*预指定关系已被撤销*/
#define BFE_ERR_DLCG_CHEBPLOAD      "FE0713"     /*登记对账不平明细表失败*/
#define BFE_ERR_DLCG_APPOINTAV      "FE0714"     /*预指定关系已存在*/
#define BFE_ERR_SVRCODENULL	   "FE0715"     /*服务代码不能为空*/
#define BFE_ERR_DCIEXECSQL	   "FE0716"     /*执行sql异常!*/
#define BFE_ERR_SVRINFONULL	  "FE0717"     /*服务信息表尚未配置*/
#define BFE_ERR_SVRNOBEGIN             "FE0718"     /*业务未到开展时间*/
#define BFE_ERR_SVRISEND         	 "FE0719"     /*业务已过结束时间*/
#define BFE_ERR_SVRNOTBEGIN	 "FE0720"     /*服务尚未生效*/
#define BFE_ERR_FILEOPEN	"FE0721"    /*打开文件失败*/  
#define BFE_ERR_DCICOMMIT	"FE0722"    /*事务提交失败*/  
#define BFE_ERR_XLKY_CHKINFO	"FE0723"    /*事务提交失败*/  
#endif
