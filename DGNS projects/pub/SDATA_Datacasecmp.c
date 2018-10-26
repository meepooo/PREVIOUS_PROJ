/***********************************************************************
 * 版权所有:恒生电子股份有限公司
 * 项目名称:台州银行中间业务平台
 * 版    本:V1.00
 * 操作系统:
 * 文 件 名:SDATA_Datacasecmp.c
 * 文件描述:台州银行中间业务
 * 项 目 组:
 * 程 序 员:[ZFF]
 * 创建时间:2013-1-24 18:37:39
 * 修    订:
 * 修改时间:
 * ****************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gaps_head.h"
#include "xml.h"

#define MAX_LENGTH 5120000


/***********************************************************************
 * 动态组件函数定义
 * 组件函数名称:SDATA_Datacasecmp
 * 组件名称:台州银行XML报文转换
 * 组件功能:
 * 组件参数列表：
 * 序号  参数类型  参数名称     资源类别    缺省值        可空      参数说明
 * 1     文件名称
 * 组件结果状态:
 * 结果状态码          结果说明
 * -9999               缺省
 * 0                   成功
 * 日志信息:
 * 日志级别                                                                              日志宏
 * 响应信息:
 * 内部响应码                                                                           内部响应信息
 * 主要操作元素:
 * 元素路径                                                                               操作
 * 主要操作库表:
 * 表名                                                                               操作
 * 使用限制:
 * 项 目 组:
 * 程 序 员:zhouff
 * 发布日期:2013-1-24 18:39:13
 * 修改日期:
 ************************************************************************/

IRESULT SDATA_Datacasecmp(HXMLTREE lXmlhandle)
{
    char outstr[MAX_LENGTH + 1];
    char *instr;
    char s_ms[1+1];
    char srcdata[2048] ;
    char decdata[2048] ;
    int iParas,iRet=0;
    int iLen;

    fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
#endif

    COMP_PARACOUNTCHK(3);

    /* 获取模式 */
    memset(s_ms,0x00,sizeof(s_ms));
    COMP_GETPARSEPARAS(1,s_ms,"模式")
    trim(s_ms);

    memset(srcdata,0x00,sizeof(srcdata));
    COMP_GETPARSEPARAS(2,srcdata,"源数据")
    trim(srcdata);

    memset(decdata,0x00,sizeof(decdata));
    COMP_GETPARSEPARAS(3,decdata,"比较数据")
    trim(decdata);

    /* 判断模式是否为空 */
    if(strlen(s_ms) ==0)
    {
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        /*fpub_SetMsg(lXmlhandle,atol(BS_ERR_NOBLANK),Fmtmsg("模式不能为空!"));*/
        LOGRET(-1,LM_STD,Fmtmsg("模式不能为空!"),"ERR");
    }

    LOG(LM_DEBUG,Fmtmsg("模式[%s]源数据[%s]比较数据[%s]", s_ms, srcdata, decdata),"DEBUG");

    iRet = strcasecmp(srcdata, decdata) ;
    LOG(LM_DEBUG,Fmtmsg("[%d]模式[%s]源数据[%s]比较数据[%s]", iRet, s_ms, srcdata, decdata),"DEBUG");

    if ( iRet==0 )
    {
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
	return 0;
    }
    else if ( iRet>0 )
    {
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	return 1;
    }
    else if ( iRet<0 )
    {
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	return 2;
    }
    else
    {
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	return COMPRET_FAIL;
    }
}
