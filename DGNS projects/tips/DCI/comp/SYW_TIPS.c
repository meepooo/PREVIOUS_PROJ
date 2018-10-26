/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V3.0.00
操作系统:AIX5.3
文件名称:SYW_TIPS.ec
文件描述:TIPS公共组件集
项 目 组:TIPS专用前置产品组
程 序 员:Tuql
发布日期:
修    订:
修改日期:  
*********************************************************************/
/*
总体说明:

函数说明
组件函数名称                 组件名称                      发布日期  程序员 修改日期 修改人

*/

#include <stdio.h>
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/time.h> 
#include <stdlib.h>
#include <unistd.h> 
#include "gaps_head.h"
/* mod dci 20141103    
EXEC SQL INCLUDE  "gaps_head.eh";
EXEC SQL INCLUDE  "../eh/tips_bwdj.eh"; 报文登记表 
EXEC SQL INCLUDE  "../eh/tips_sjgxhz.eh"; 数据更新汇总表 
EXEC SQL INCLUDE  "../eh/tips_taxcodeinfo.eh"; 征收机关代码表 
EXEC SQL INCLUDE  "../eh/tips_bankcodeinfo.eh"; 清算银行代码表 
EXEC SQL INCLUDE  "../eh/tips_nodecodeinfo.eh"; 节点代码表 
EXEC SQL INCLUDE  "../eh/tips_trecodeinfo.eh"; 国库代码表 
EXEC SQL INCLUDE  "../eh/tips_budgetsubject.eh"; 预算科目代码表 
EXEC SQL INCLUDE  "../eh/tips_returnreason.eh"; 退库原因代码表 
EXEC SQL INCLUDE  "../eh/tips_correctreason.eh"; 更正原因代码表 
EXEC SQL INCLUDE  "../eh/tips_taxtypeinfo.eh"; 税种代码表 
EXEC SQL INCLUDE  "../eh/tips_taxsubject.eh"; 税目代码表 
EXEC SQL INCLUDE  "../eh/tips_zygsbw.eh"; 自由格式报文 
EXEC SQL INCLUDE  "../eh/tips_9120.eh"; 报文登记表 add by tuql 20091022
EXEC SQL INCLUDE  "../eh/tips_yxcs.eh"; 报文登记表 add by tuql 20091022
EXEC SQL INCLUDE  "../eh/tips_xibhxmx.eh"; 核心明细表 add by wangw 20120802
*/

/* add dci 20141103 */
#include "../eh/tips_bwdj.h"/* 报文登记表 */
#include "../eh/tips_sjgxhz.h"/* 数据更新汇总表 */
#include "../eh/tips_taxcodeinfo.h"/* 征收机关代码表 */
#include "../eh/tips_bankcodeinfo.h"/* 清算银行代码表 */
#include "../eh/tips_nodecodeinfo.h"/* 节点代码表 */
#include "../eh/tips_trecodeinfo.h"/* 国库代码表 */
#include "../eh/tips_budgetsubject.h"/* 预算科目代码表 */
#include "../eh/tips_returnreason.h"/* 退库原因代码表 */
#include "../eh/tips_correctreason.h"/* 更正原因代码表 */
#include "../eh/tips_taxtypeinfo.h"/* 税种代码表 */
#include "../eh/tips_taxsubject.h"/* 税目代码表 */
#include "../eh/tips_zygsbw.h"/* 自由格式报文 */
#include "../eh/tips_9120.h"/* 报文登记表 add by tuql 20091022 */
#include "../eh/tips_yxcs.h"/* 报文登记表 add by tuql 20091022 */
#include "../eh/tips_xibhxmx.h" /* 核心明细表 add by wangw 20120802*/
/* end add dci 20141103 */

#define    LEN_COMM                64000                   /*通讯缓冲区长度*/
#define TIPS_MAX_PKG       8192000 /* 20150512改为动态分配 8M报文慎用 */   /*通讯报文最大长度*/
#define XML_TMPNODE     "/systmp"   /*系统用的XML路径*/

#define XML_TMPNODE     "/systmp"   /*系统用的XML路径*/

#define SQLNOTFOUND_TIPS ( \
                (sqlca.sqlcode == 100) \
             || (sqlca.sqlcode == 1403) \
             || (sqlca.sqlcode == 0 && sqlca.sqlerrd[2] == 0) \
             )
             
/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_MMTIME
组件名称: 取时间毫秒
组件功能: 
  取时间毫秒
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作


项 目 组: TIPS专用前置产品组
程 序 员: 
发布日期: 2014年09月22日
修改日期: 
参数使用示例: 
************************************************************************/             
IRESULT SYW_TIPS_MMTIME(HXMLTREE lXmlhandle)
{
	int iReturn = COMPRET_SUCC;
	int iReturnStatus = COMPSTATUS_SUCC;
	
	char szBuf[255];
	char szBuf1[255];
	char pMMTime[255];
	struct timeval tv; 
	long lMMTime;
	
  
	memset(szBuf, 0, sizeof(szBuf));
	memset(szBuf1, 0, sizeof(szBuf1));
	memset(pMMTime, 0, sizeof(pMMTime));
		
	fpub_InitSoComp( lXmlhandle );

	LOG( LM_DEBUG, Fmtmsg( "-------------------[%s]", fpub_GetCompname( lXmlhandle ) ), "INFO" );
	LOG( LM_DEBUG, Fmtmsg( "组件[%s]开始执行", fpub_GetCompname( lXmlhandle ) ), "INFO" );	

	COMP_GETPARSEPARAS(1, pMMTime, "精确时间");

	/*调用生成函数*/
	
	gettimeofday(&tv,NULL);    
  lMMTime = tv.tv_sec * 1000 + tv.tv_usec / 1000;  
  LOG( LM_DEBUG, Fmtmsg( "精确时间[%3ld]",  lMMTime), "INFO" ); 
  
  sprintf(szBuf1,"%ld",lMMTime);
  LOG( LM_DEBUG, Fmtmsg( "精确时间[%s]",  szBuf1), "INFO" ); 
  
  strncpy(szBuf,szBuf1+(strlen(szBuf1)-3),3);
  
	LOG( LM_DEBUG, Fmtmsg( "精确时间[%s]",  szBuf), "INFO" ); 
	COMP_HARDSETXML(pMMTime, szBuf);
	LOG( LM_DEBUG, Fmtmsg( "精确时间[%s]",  pMMTime), "INFO" );

	fpub_SetCompStatus( lXmlhandle, COMPSTATUS_SUCC );
	LOG( LM_DEBUG, Fmtmsg( "组件[%s]结束执行", fpub_GetCompname( lXmlhandle ) ), "INFO" );
	return COMPRET_SUCC;	
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_COMM
组件名称: 与TIPS转发器通讯
组件功能: 
  与TIPS转发器通讯
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作


项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月11日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_COMM(HXMLTREE lXmlhandle)
{
    int iParas;
    /*char sBuffer[TIPS_MAX_PKG]; 20150512 改为动态分配 */
    char *pBuffer = NULL;
    char sIp[50];
    char sTxms[1+1];/* 通讯模式1,2,3 3-无应答 */
    char sTmpBuf[254];
    char sBuf[254];
    char sXym[5+1];
    char sXyxx[60+1];
    char commbuf1[TIPS_MAX_PKG];
    
    int  iSock = -1;
    int  iPort;
    int  iTime;
    int  iRet;
    int  iLen;
    int  iSize;
    char syncbuf[3]={"\x02\x00\x00"};
    
    char sJydm[4+1];/* 交易代码 */
    char sMode[1+1];/* 模式, 1-put 2-get */
    char sPutMode[1+1];/* put模式 get时不使用 1-以请求方式put 2-以响应方式put */
    char sMsgID[56];/* 发送消息的CorrelId ，响应模式发送时使用 */
    char sXh[30];/* 序号 */
    char sQmgr[60];/* 队列管理器 */
    char sRespQueue[60];/* 应答队列名 */
    char sCssj[30];/* 超时时间 */
    char sFileName[256];/* 文件名 */

    fpub_InitSoComp(lXmlhandle);

    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
    #endif 
  
    /*获取组件参数  --S*/
    COMP_PARACOUNTCHK(4)

    /*IP*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sIp, 0x00, sizeof(sIp));
    COMP_GETPARSEPARAS(1, sBuf, "IP地址")
    pstrcopy(sIp, sBuf, sizeof(sIp));
    trim(sIp);
    /*PORT*/
    memset(sBuf, 0x00, sizeof(sBuf));
    iPort = 0 ;
    COMP_GETPARSEPARAS(2, sBuf, "PORT")
    iPort = atoi(sBuf);
    /*TIMOUT*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "超时时间")
    if (sBuf[0] != '\0')
      iTime = atoi(sBuf);
    else
      iTime = 60;
    /*通讯模式*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTxms, 0x00, sizeof(sTxms));
    COMP_GETPARSEPARAS(4, sBuf, "通讯模式")
    pstrcopy(sTxms, sBuf, sizeof(sTxms));
    trim(sTxms);
    
    LOG(LM_STD,Fmtmsg("通讯区：IP地址[%s] PORT[%d], 超时时间[%d]",sIp, iPort, iTime), fpub_GetCompname(lXmlhandle))
    
    /* 取通讯区内容 */
    /* 20150512 修改为动态获取 */
   /*memset(sBuffer, 0x00, sizeof(sBuffer));*/
    iSize = xml_GetBinElementLen(lXmlhandle, "/commbuf");
    if (iSize < 0)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"获取通讯报文长度失败",fpub_GetCompname(lXmlhandle));
	  }
	  iSize = iSize +1;
	  pBuffer = malloc(iSize);
	  if(NULL == pBuffer)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("malloc失败[%s]",strerror(errno)),fpub_GetCompname(lXmlhandle));
	  }	
	  memset(pBuffer, 0, iSize);
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, "/commbuf", pBuffer, iSize)) == FAIL )
    {
    	  free(pBuffer);
        fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"获取通讯区内容失败",fpub_GetCompname(lXmlhandle));
    }
    /* end 20150512 修改为动态获取 */
	/* 通讯连接 */
    itcp_sethead(0);
    itcp_setenv( iPort, &iSock);
    itcp_setsync(3,syncbuf);
    itcp_setmaxlen(1024); 
  
    iRet = itcp_call(sIp);
    if (iRet != 0)
    {
		fpub_SetMsg(lXmlhandle, 24106, "与tips转发器连接失败");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"连接失败",fpub_GetCompname(lXmlhandle));
    }
	
	/* 20150512 mmap未释放core修改
	memset(commbuf1,0x00, sizeof(commbuf1));
	memcpy(commbuf1, sBuffer, iLen); 
	iRet=itcp_send(commbuf1,iLen,iTime);
	LOG(LM_STD,Fmtmsg("commbuf1[%s]", commbuf1),"itcp_send");
	*/
	
	iRet=itcp_send(pBuffer,iLen,iTime);
	LOG(LM_STD,Fmtmsg("pBuffer[%s]", pBuffer),"itcp_send");
	if (iRet<0)
	{
		itcp_clear();
		fpub_SetMsg(lXmlhandle, 24107, "向tips转发器发送数据失败");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"向tips转发器发送数据失败",fpub_GetCompname(lXmlhandle));
	}
	
    /*接收有效数据*/
	/* 20150512 修改 
	memset(sBuffer, 0x00, sizeof(sBuffer));
	iRet=itcp_recv(sBuffer,sizeof(sBuffer),iTime);
	trim(sBuffer);
	LOG(LM_STD,Fmtmsg("sBuffer1[%s]", sBuffer),"itcp_recv");
	end 20150512 */
	memset(commbuf1,0x00, sizeof(commbuf1));
	iRet=itcp_recv(commbuf1,sizeof(commbuf1),iTime);
	trim(commbuf1);
	LOG(LM_STD,Fmtmsg("接收报文长度[%d][%s]", strlen(commbuf1),commbuf1),"itcp_recv");
	
	if (iRet<0)
	{
        itcp_clear();
		fpub_SetMsg(lXmlhandle, 24108, "向tips转发器接收数据失败");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"向tips转发器接收数据失败",fpub_GetCompname(lXmlhandle));
	}
	itcp_clear();
	/* 20150512 
	if (( iRet = xml_RelSetBinElement(lXmlhandle,"/commbuf",sBuffer,strlen(sBuffer))) == FAIL)*/
	if (( iRet = xml_RelSetBinElement(lXmlhandle,"/commbuf",commbuf1,strlen(commbuf1))) == FAIL)
	{
		fpub_SetMsg(lXmlhandle, 24109, "回写通讯区内容失败");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"回写通讯区内容失败",fpub_GetCompname(lXmlhandle));
	}
        
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;    

}   

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitPKGHEAD
组件名称: 初始化报文头数据项
组件功能: 
  初始化报文头数据项
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
批量交易登记表	tips_nbcsb

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月11日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitPKGHEAD(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sDqzt[1+1];/* 当前状态 */
         char sQdqt[1+1];/* 签到签退 */
         char sVer[10+1];/* 版本号 */
         char sSrc[12+1];/* 发起节点代码 */
         char sDes[12+1];/* 接收节点代码 */
         char sWorkDate[8+1];/* 工作日期 */
         char sMsgNo[4+1];/* 报文编号 */
         int iCount;
    /*EXEC SQL END   DECLARE SECTION;*/
    
    char sBuf[256];
    char sMsgID[20+1];/* 报文标识号 */
    char sMsgRef[20+1];/* 报文参考号 */
    
    int iRet=0;
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		
    fpub_InitSoComp(lXmlhandle);
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif 
    
    COMP_PARACOUNTCHK(3);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sMsgNo, 0x00, sizeof(sMsgNo));
    COMP_GETPARSEPARAS(1, sBuf, "报文编号")
    pstrcopy( sMsgNo, sBuf, sizeof(sMsgNo));
    trim(sMsgNo);            

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sMsgID, 0x00, sizeof(sMsgID));
    COMP_GETPARSEPARAS(2, sBuf, "报文标识号")
    pstrcopy( sMsgID, sBuf, sizeof(sMsgID));
    trim(sMsgID); 

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sMsgRef, 0x00, sizeof(sMsgRef));
    COMP_GETPARSEPARAS(3, sBuf, "报文参考号")
    pstrcopy( sMsgRef, sBuf, sizeof(sMsgRef));
    trim(sMsgRef); 

    LOG(LM_STD,Fmtmsg("初始化报文头数据项开始 报文编号[%s],报文标识号[%s],报文参考号[%s]", 
        sMsgNo, sMsgID, sMsgRef), fpub_GetCompname(lXmlhandle));
    
    /* 查询内部参数表 */
    memset(sWorkDate, 0x00, sizeof(sWorkDate));
    memset(sVer, 0x00, sizeof(sVer));
    memset(sSrc, 0x00, sizeof(sSrc));
    memset(sDes, 0x00, sizeof(sDes));
    memset(sDqzt, 0x00, sizeof(sDqzt));
    memset(sQdqt, 0x00, sizeof(sQdqt));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT workdate, ver, src, des, dqzt, qdqt FROM tips_nbcsb WHERE 1=1");     
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&sWorkDate, &sVer, &sSrc, &sDes, &sDqzt, &sQdqt);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24102, Fmtmsg("查询内部参数表失败"));
        LOG(LM_STD,Fmtmsg("查询内部参数表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
        
    }
    /* end add dci 20141103 */
    

    /* mod dci 20141103
    EXEC SQL SELECT workdate, ver, src, des, dqzt, qdqt 
         INTO :sWorkDate, :sVer, :sSrc, :sDes, :sDqzt, :sQdqt
         FROM tips_nbcsb
         WHERE 1=1;
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT, sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
        fpub_SetMsg(lXmlhandle, 24102, Fmtmsg("查询内部参数表失败"));
        LOG(LM_STD,Fmtmsg("查询内部参数表失败"), fpub_GetCompname(lXmlhandle));        
        return COMPRET_FAIL; 	
    }
    */
    
    trim(sWorkDate);trim(sVer);trim(sQdqt);
    trim(sSrc);trim(sDes);trim(sDqzt);
    LOG(LM_STD,Fmtmsg("当前状态[%s],工作日期[%s],版本号[%s],发起节点代码[%s],接收节点代码[%s]", 
        sDqzt, sWorkDate, sVer, sSrc, sDes), fpub_GetCompname(lXmlhandle));
    
    /* 若当前状态不为0-正常或8-日切或0-签到,则不充许发交易到TIPS端,
     * 除连接测试及签到交易外
     */
    /*  
    if (   ( sDqzt[0] =='1' || sDqzt[0] =='2' || sDqzt[0] =='3' || sQdqt[0] != '0' )
        && ( !( strncmp(sMsgNo, "9005", 4)==0 || strncmp(sMsgNo, "9006", 4)==0 ) )
        )
    {
        iCount = 0;
        EXEC SQL SELECT COUNT(*) INTO :iCount
             FROM tips_bwsxwh
             WHERE msgno = :sMsgNo;
               AND ssdl = 'O';
        if ( SQLERR )
        {
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
            fpub_SetMsg(lXmlhandle, 24102, Fmtmsg("查询报文属性表失败"));
            LOG(LM_STD,Fmtmsg("查询报文属性表失败"), fpub_GetCompname(lXmlhandle));        
            return COMPRET_FAIL; 	
        }
        if ( iCount > 0 )
        {
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);	
            fpub_SetMsg(lXmlhandle, 24102, Fmtmsg("未向TIPS系统签到或TIPS系统正处于维护期！"));
            LOG(LM_STD,Fmtmsg("未向TIPS系统签到或TIPS系统正处于维护期！"), fpub_GetCompname(lXmlhandle));        
            return COMPRET_FAIL;            
        }    
    }    
     */   
    /* 设置报文头数据项 */
    COMP_HARDSETXML("/CFX/HEAD/VER", sVer)/* 版本号 */
    COMP_HARDSETXML("/CFX/HEAD/SRC", sSrc)/* 发起节点代码 */
    COMP_HARDSETXML("/CFX/HEAD/DES", sDes)/* 接收节点代码 */    
    COMP_HARDSETXML("/CFX/HEAD/APP", "TIPS")/* 应用名称 */
    COMP_HARDSETXML("/CFX/HEAD/MsgNo", sMsgNo)/* 报文编号 */
    COMP_HARDSETXML("/CFX/HEAD/MsgID", sMsgID)/* 报文标识号 */
    COMP_HARDSETXML("/CFX/HEAD/MsgRef", sMsgRef)/* 报文参考号 */
    COMP_HARDSETXML("/CFX/HEAD/WorkDate", sWorkDate)/* 工作日期 */
    COMP_HARDSETXML("/CFX/HEAD/Reserve", "")/* 预留字段 */    

    LOG(LM_STD,Fmtmsg("初始化报文头数据项结束"), fpub_GetCompname(lXmlhandle));
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;     
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitBWDJ
组件名称: 初始化报文登记表
组件功能: 
  初始化报文登记表
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
报文登记表	tips_bwdj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月13日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitBWDJ(HXMLTREE lXmlhandle)
{
    int iParas;
    /* EXEC SQL BEGIN DECLARE SECTION; mod dci 20141103 */ 		
			SDB_TIPS_BWDJ  stBwdj;
    /* EXEC SQL BEGIN DECLARE SECTION;  mod dci 20141103 */ 
		
		
    
    char sBuf[256];
    char sBwdjbz[1+1];
    char sNode[64];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);
    
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif 

    memset(&stBwdj, 0x00, sizeof(stBwdj));
    /* 4.报文编号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/MsgNo", sBuf)
    pstrcopy(stBwdj.msgno, sBuf, sizeof(stBwdj.msgno));           
    if (!(   strncmp(stBwdj.msgno, "3102", 4)==0 
           ||strncmp(stBwdj.msgno, "2102", 4)==0
           ||strncmp(stBwdj.msgno, "1123", 4)==0
        ))
    {
        fpub_SetMsg(lXmlhandle, 0, "不记报文流水,登记成功");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("不记报文登记,成功退出"),
            fpub_GetCompname(lXmlhandle))        
    }    

    /* 取报文登记各值信息 */
    /* 1.发起机构代码 */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/SendOrgCode", sBuf)
    pstrcopy(stBwdj.sendorgcode, sBuf, sizeof(stBwdj.sendorgcode));
    /* 2.委托日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/EntrustDate", sBuf)
    pstrcopy(stBwdj.entrustdate, sBuf, sizeof(stBwdj.entrustdate));
    /* 3.包流水号 */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/PackNo", sBuf)
    pstrcopy(stBwdj.packno, sBuf, sizeof(stBwdj.packno));
    /* 5.报文类型 */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/bwlx", sBuf)
    pstrcopy(stBwdj.bwlx, sBuf, sizeof(stBwdj.bwlx));
    /* 6.付款行行号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/PayBkCode", sBuf)
    pstrcopy(stBwdj.paybkcode, sBuf, sizeof(stBwdj.paybkcode));
    /* 7.报文文件名 */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/bwwjm", sBuf)
    pstrcopy(stBwdj.bwwjm, sBuf, sizeof(stBwdj.bwwjm));
    /* 8.帐务日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/zwrq", sBuf)
    pstrcopy(stBwdj.zwrq, sBuf, sizeof(stBwdj.zwrq));    
    /* 9.处理时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/clsj", sBuf)
    pstrcopy(stBwdj.clsj, sBuf, sizeof(stBwdj.clsj));
    /* 10.综合前置流水号 */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/zhqzlsh", sBuf)
    pstrcopy(stBwdj.zhqzlsh, sBuf, sizeof(stBwdj.zhqzlsh));
    /* 11.当前状态 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/dqzt", sBuf)
    pstrcopy(stBwdj.dqzt, sBuf, sizeof(stBwdj.dqzt));
    /* 12.工作日期 */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/WorkDate", sBuf)
    pstrcopy(stBwdj.workdate, sBuf, sizeof(stBwdj.workdate));
    /* 13.总笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/allnum", sBuf)
    stBwdj.allnum=atoi(sBuf); 
    /* 14.总金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/allamt", sBuf)
    stBwdj.allamt=atof(sBuf);
    /* 15.成功笔数 */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/succnum", sBuf)
    stBwdj.succnum = atoi(sBuf);
    /* 16.成功金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/succamt", sBuf)
    stBwdj.succamt=atof(sBuf);
    /* 16.止付笔数 */      
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/zfbs", sBuf)
    stBwdj.zfbs = atoi(sBuf);
    /* 17.止付金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/bwdj/zfje", sBuf)
    stBwdj.zfje=atof(sBuf); 
    /* 24.处理次数 */
    stBwdj.clcs=1;

		/* add dci 20141103 */
		memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_bwdj", SD_TIPS_BWDJ, NUMELE(SD_TIPS_BWDJ), &stBwdj, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
			fpub_SetMsg(lXmlhandle, 24103, "初始化报文登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitBWDJ初始化报文登记表失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;   
    }

		/* end add dci 20141103 */
		
		/* mod dci 20141103 
    EXEC SQL INSERT INTO tips_bwdj  VALUES (:stBwdj);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24103, "初始化报文登记表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("InitBWDJ初始化报文登记表失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	    
    */
    
    fpub_SetMsg(lXmlhandle, 0, "初始化报文登记表成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC; 
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_GetCOMMPARAS
组件名称: 获取与tips通讯的各参数
组件功能: 
  获取与tips通讯的参数
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
报文登记表	tips_bwdj

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月13日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_GetCOMMPARAS(HXMLTREE lXmlhandle)
{
    int iParas;
    /*EXEC SQL BEGIN DECLARE SECTION;*/
         char sMsgNo[4+1];/* 报文编号 */
         char sBwlx[4+1];/* 报文类型 */
         char sBwms[1+1];/* 报文模式 */
         char sYwhz[4+1];/* 业务回执 */
         char sSsdl[1+1];/* 所属队列 */
         char sBwppjz[3+1];/* 报文匹配机制 */
    /*EXEC SQL END   DECLARE SECTION;*/
    
    char sBuf[256];
    char sQmgr[60];/* 队列管理器 */
    char sQmgrPath[60];/* 队列管理器结点 */
    char sReqQueue[60];/* 请求队列名 */
    char sReqQueuePath[60];/* 请求队列名结点 */
    char sRespQueue[60];/* 应答队列名 */
    char sRespQueuePath[60];/* 应答队列名结点 */
    char sBwmsPath[60+1];/* 报文模式路径 */
    int  iBwppjz = 2 ;/* 报文匹配机制 2-报文参考号*/
    int  iXxscq = -1 ;/* 消息生存期 */
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		/* end add dci 20141103 */

    fpub_InitSoComp(lXmlhandle);
    
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    LOG(LM_STD,Fmtmsg("获取与tips通讯的各参数开始..."), fpub_GetCompname(lXmlhandle))
    
    COMP_PARACOUNTCHK(5);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sMsgNo, 0x00, sizeof(sMsgNo));
    COMP_GETPARSEPARAS(1, sBuf, "报文编号")
    pstrcopy( sMsgNo, sBuf, sizeof(sMsgNo));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sQmgrPath, 0x00, sizeof(sQmgrPath));
    COMP_GETPARAS(2, sBuf, "队列管理器结点")
    pstrcopy( sQmgrPath, sBuf, sizeof(sQmgrPath)); 
    trim(sQmgrPath);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sReqQueuePath, 0x00, sizeof(sReqQueuePath));
    COMP_GETPARAS(3, sBuf, "请求队列名结点")
    pstrcopy( sReqQueuePath, sBuf, sizeof(sReqQueuePath)); 
    trim(sReqQueuePath);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRespQueuePath, 0x00, sizeof(sRespQueuePath));
    COMP_GETPARAS(4, sBuf, "应答队列名结点")
    pstrcopy( sRespQueuePath, sBuf, sizeof(sRespQueuePath));
    trim(sRespQueuePath);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sBwmsPath, 0x00, sizeof(sBwmsPath));
    COMP_GETPARAS(5, sBuf, "报文模式结点")
    pstrcopy( sBwmsPath, sBuf, sizeof(sBwmsPath));
    trim(sBwmsPath);
        
    LOG(LM_STD,Fmtmsg("报文编号[%s]...", sMsgNo), fpub_GetCompname(lXmlhandle))
    
    /* 从报文属性维护表中获取报文类型、报文模式、报文批单性质等信息 */
    memset(sBwlx, 0x00, sizeof(sBwlx));
    memset(sBwms, 0x00, sizeof(sBwms));
    memset(sYwhz, 0x00, sizeof(sYwhz));
    memset(sSsdl, 0x00, sizeof(sSsdl));
    memset(sBwppjz, 0x00, sizeof(sBwppjz));
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
		snprintf( sSql1, sizeof(sSql1), "SELECT bwlx, bwms, ywhz, ssdl, bwppjz FROM tips_bwsxwh \
			WHERE msgno='%s'",sMsgNo);     
    iRet = DBSelectToMultiVar(sErrmsg, sSql1,&sBwlx, &sBwms, &sYwhz, &sSsdl, &sBwppjz);
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24104, "查询报文属性维护表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GetCOMMPARAS查询报文属性维护表失败"),
            fpub_GetCompname(lXmlhandle))	
        
    }
    if ( iRet == 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
             
        fpub_SetMsg(lXmlhandle, 24104, "在表中未找到相应的报文编号");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GetCOMMPARAS在表中未找到相应的报文编号"),
            fpub_GetCompname(lXmlhandle))	
        
    }
    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL SELECT bwlx, bwms, ywhz, ssdl, bwppjz
         INTO :sBwlx, :sBwms, :sYwhz, :sSsdl, :sBwppjz 
         FROM tips_bwsxwh
         WHERE msgno = :sMsgNo;            
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_SELECT,sqlca.sqlcode),"ERROR")
    if ( SQLERR )
    {
        fpub_SetMsg(lXmlhandle, 24104, "查询报文属性维护表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GetCOMMPARAS查询报文属性维护表失败"),
            fpub_GetCompname(lXmlhandle))	
    }
    if ( SQLNOTFOUND_TIPS )
    {
        fpub_SetMsg(lXmlhandle, 24104, "在表中未找到相应的报文编号");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("GetCOMMPARAS在表中未找到相应的报文编号"),
            fpub_GetCompname(lXmlhandle))	
    } 
    */
       
    /* 从环境变量中拼接组成队列管理器 */
    memset(sQmgr, 0x00, sizeof(sQmgr));
    snprintf(sQmgr, sizeof(sQmgr), "%s%s%s", getenv("QMGRPREFIX"), getenv("EXTNODECODE"), getenv("RESERVENO"));
    trim(sQmgr);
    
    /* 拼接请求、应答队列名 */
    memset(sReqQueue, 0x00, sizeof(sReqQueue));
    memset(sRespQueue, 0x00, sizeof(sRespQueue));
    if ( sSsdl[0]=='O') /* 单笔实时 */
    {
        snprintf(sReqQueue, sizeof(sReqQueue), "PBC.EXT.%s.IN", "ONLINE"); 
        memset(sBuf, 0x00, sizeof(sBuf));
        /*COMP_SOFTGETXML("/tips/HEAD/MsgNo", sBuf)*/
        COMP_SOFTGETXML("/tipso/MsgNo", sBuf)
        trim(sBuf);
        LOG(LM_DEBUG,Fmtmsg("MsgNo[%s]...",sBuf),"INFO")      
        if (strcmp(sBuf, "9120") == 0 )
        {
            snprintf(sReqQueue, sizeof(sReqQueue), "%s", "TIPS.INTERNAL.RESP");
        }
    }else
    {
       snprintf(sReqQueue, sizeof(sReqQueue), "PBC.EXT.%s.IN", "BATCH");  
    }        
    if (sBwms[0]=='1' || sBwms[0]=='4')/* 有实时回执 */
    {
        snprintf(sRespQueue, sizeof(sRespQueue), "PBC.%s.ONLINE.OUT", getenv("EXTNODECODE")); 
        iXxscq = 10000 ;/* 消息生存期 */
        iBwppjz = 1 ; /* 报文匹配机制 1-MQ消息ID */      
    }else
    {
        snprintf(sRespQueue, sizeof(sRespQueue), "TIPS.INTERNAL.RESP");
    }
    trim(sReqQueue);
    trim(sRespQueue);       
    
    /* mod by tuql 20090909 将COMP_SOFTSETXML改成COMP_HARDSETXML */
    COMP_HARDSETXML(sQmgrPath, sQmgr) 
    COMP_HARDSETXML(sReqQueuePath, sReqQueue)  
    COMP_HARDSETXML(sRespQueuePath, sRespQueue)
    COMP_HARDSETXML(sBwmsPath, sBwms)
    
    memset(sBuf, 0x00, sizeof(sBuf)); 
    sprintf(sBuf, "%d", iBwppjz);
    COMP_HARDSETXML("/tipso/bwppjz", sBuf)/* 报文匹配机制 */

    memset(sBuf, 0x00, sizeof(sBuf)); 
    sprintf(sBuf, "%d", iXxscq);
    COMP_HARDSETXML("/tipso/xxscq", sBuf)/* 消息生存期 */

    LOG(LM_STD,Fmtmsg("获取与tips通讯的各参数结束...."),"INFO");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;               
}    

/************************************************************************
动态组件函数定义
组件函数名称: prv_tips_UpdPUBDATA
函数名称: 更新公共数据
函数功能: 
  更新公共数据
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
数据更新汇总表	tips_sjgxhz

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA(HXMLTREE lXmlhandle, char *sZwrq, int iZhqzlsh, char *sWorkDate, char *sUpdateBatch)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_SJGXHZ stSjgxhz;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_SJGXHZ stSjgxhz;
		/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);
    
    memset(&stSjgxhz, 0x00, sizeof(stSjgxhz));
    pstrcopy(stSjgxhz.zwrq, sZwrq, sizeof(stSjgxhz.zwrq));
    stSjgxhz.zhqzlsh = iZhqzlsh;
    pstrcopy(stSjgxhz.workdate, sWorkDate, sizeof(sWorkDate));
    pstrcopy(stSjgxhz.updatebatch, sUpdateBatch, sizeof(stSjgxhz.updatebatch));
            
    /*取征收机关更新条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    		stSjgxhz.num_101 = 0;
    else
     	stSjgxhz.num_101 = atoi(sBuf);
    /*取征收机关更新成功条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num101succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    		stSjgxhz.num_101_succ = 0;
    else
     	stSjgxhz.num_101_succ = atoi(sBuf);
    /*取清算银行更新条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/BankCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	stSjgxhz.num_102 = 0;
    else
      	stSjgxhz.num_102 = atoi(sBuf);
    /*取清算银行更新成功条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num102succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_102_succ = 0;
    else
      	stSjgxhz.num_102_succ = atoi(sBuf);   
    /*取节点更新条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/NodeCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_103 = 0;
    else
      	stSjgxhz.num_103 = atoi(sBuf);
    /*取节点更新成功条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num103succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_103_succ = 0;
    else
     	stSjgxhz.num_103_succ = atoi(sBuf);     	
    /*取国库更新条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TreCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_104 = 0;
    else
         stSjgxhz.num_104 = atoi(sBuf);
    /*取国库更新成功条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num104succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_104_succ = 0;
    else
         stSjgxhz.num_104_succ = atoi(sBuf);   	
     /*取预算科目更新条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/BudgetSubjectCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_105 = 0;
    else
      	stSjgxhz.num_105 = atoi(sBuf);
     /*取预算科目更新成功条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num105succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_105_succ = 0;
    else
     	stSjgxhz.num_105_succ = atoi(sBuf);
    /*取退库原因更新条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/ReturnReasonCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    		stSjgxhz.num_106 = 0;
    else
     	stSjgxhz.num_106 = atoi(sBuf);
    /*取退库原因更新成功条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num106succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    		stSjgxhz.num_106_succ = 0;
    else
     	stSjgxhz.num_106_succ = atoi(sBuf);   
    /*取更新原因更新条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/CorrectReasonCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_107 = 0;
    else
      	stSjgxhz.num_107 = atoi(sBuf);
    /*取更新原因更新成功条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num107succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
     	stSjgxhz.num_107_succ = 0;
    else
      	stSjgxhz.num_107_succ = atoi(sBuf);   
    /*取税种代码更新条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxTypeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_108 = 0;
    else
         stSjgxhz.num_108 = atoi(sBuf);
    /*取税种代码更新成功条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num108succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_108_succ = 0;
    else
         stSjgxhz.num_108_succ = atoi(sBuf);   
    /*取税目代码更新条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxSubjectInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_109 = 0;
    else
        stSjgxhz.num_109 = atoi(sBuf);
    /*取税目代码更新成功条数*/
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/num109succ", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
         stSjgxhz.num_109_succ = 0;
    else
         stSjgxhz.num_109_succ = atoi(sBuf);
    
    /* add dci 20141103 */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_sjgxhz", SD_TIPS_SJGXHZ, NUMELE(SD_TIPS_SJGXHZ), &stSjgxhz, sErrmsg);
    if( iRet < 0 )
    {
    	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
			fpub_SetMsg(lXmlhandle, 24456, "新增数据更新汇总信息失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("UpdPUBDATA新增数据更新汇总信息失败"),
             fpub_GetCompname(lXmlhandle))
    }

    /* end add dci 20141103 */
    
    /* mod dci 20141103
    EXEC SQL INSERT INTO tips_sjgxhz VALUES(:stSjgxhz);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
    if ( SQLERR )
    {
         fpub_SetMsg(lXmlhandle, 24456, "新增数据更新汇总信息失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("UpdPUBDATA新增数据更新汇总信息失败"),
             fpub_GetCompname(lXmlhandle))
    }
    */
    
    fpub_SetMsg(lXmlhandle, 0, "更新公共数据处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;   
}
/************************************************************************
动态组件函数定义
组件函数名称: prv_tips_UpdPUBDATA_Tax
函数名称: 更新公共数据-征收机关代码
函数功能: 
  更新公共数据-征收机关代码
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
征收机关代码	tips_taxcodeinfo

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Tax(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
				SDB_TIPS_TAXCODEINFO stTaxCode;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum101;
    int iNum101Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_TAXCODEINFO stTaxCode;
		/* end add dci 20141103 */

    fpub_InitSoComp(lXmlhandle);
    
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif

    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum101 = 0;
    else
     	iNum101 = atoi(sBuf);
    
    if ( iNum101 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "无需更新公共数据-征收机关代码");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("无需更新公共数据-征收机关代码,共[%d]条", iNum101),
            fpub_GetCompname(lXmlhandle))        
    }
    /*取征收机关节点明细*/
    for(i = 1; i <= iNum101; i ++)
    {
   		memset(&stTaxCode, 0x00, sizeof(stTaxCode));
   		/*1.征收机关代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/TaxOrgCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.taxorgcode, sTmpBuf, sizeof(stTaxCode.taxorgcode));
   		/*2.征收机关名称*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/TaxOrgName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.taxorgname, sTmpBuf, sizeof(stTaxCode.taxorgname));
   		/*3.征收机关类型*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/TaxOrgType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.taxorgtype, sTmpBuf, sizeof(stTaxCode.taxorgtype));
   		/*4.机构级次*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OrgLevel",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.orglevel, sTmpBuf, sizeof(stTaxCode.orglevel));
   		/*5.管理国库代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/UpTreCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.uptrecode, sTmpBuf, sizeof(stTaxCode.uptrecode));
   		/*6.所属节点代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OfNodeCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.ofnodecode, sTmpBuf, sizeof(stTaxCode.ofnodecode));
   		/*7.所属省级征收机关*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OfProvOrg",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.ofprovorg, sTmpBuf, sizeof(stTaxCode.ofprovorg));
   		/*8.所属市级征收机关*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OfCityOrg",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.ofcityorg, sTmpBuf, sizeof(stTaxCode.ofcityorg));
   		/*9.所属县级征收机关*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OfCountyOrg",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.ofcountyorg, sTmpBuf, sizeof(stTaxCode.ofcountyorg));
   		/*10.地址*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/Address",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.address, sTmpBuf, sizeof(stTaxCode.address));
   		/*11.邮政编码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/PostalCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.postalcode, sTmpBuf, sizeof(stTaxCode.postalcode));
   		/*12.联系人名称*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/PeopleName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.peoplename, sTmpBuf, sizeof(stTaxCode.peoplename));
   		/*13.联系人座机*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/PeoplePhone",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.peoplephone, sTmpBuf, sizeof(stTaxCode.peoplephone));
   		/*14.联系人手机*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/PeopleMobile",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.peoplemobile, sTmpBuf, sizeof(stTaxCode.peoplemobile));
   		/*15.电子邮箱*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/Email",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.email, sTmpBuf, sizeof(stTaxCode.email));
   		/*16.操作标志*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.opersign, sTmpBuf, sizeof(stTaxCode.opersign));
   		/*17.生效日期*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.effectdate, sTmpBuf, sizeof(stTaxCode.effectdate));
   		/*18.更新范围*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxCodeInfo9100/TaxCodeInfo101|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxCode.updatearea, sTmpBuf, sizeof(stTaxCode.updatearea));

   		switch(atoi(stTaxCode.opersign))
   		{
   			case 1: /*新增*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_taxcodeinfo", SD_TIPS_TAXCODEINFO, NUMELE(SD_TIPS_TAXCODEINFO), &stTaxCode, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
						fpub_SetMsg(lXmlhandle, 24457, "新增征收机关代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增征收机关代码失败[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    		iNum101Succ ++;
   				/* end add dci 20141103 */   				

   				/* mod dci 20141103 
   				EXEC SQL INSERT INTO tips_taxcodeinfo VALUES(:stTaxCode);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24457, "新增征收机关代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增征收机关代码失败[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    		iNum101Succ ++;
      		*/
   				break;
   				
   			case 2: /*修改*/
   				/*if(atol(GetSysDate()) <= atol(stTaxCode.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "taxorgcode ='%s'", stTaxCode.taxorgcode); 
    			iRet = DBUpdate("tips_taxcodeinfo", SD_TIPS_TAXCODEINFO, NUMELE(SD_TIPS_TAXCODEINFO), &stTaxCode, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24458, "更新征收机关代码失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOG(LM_STD,Fmtmsg("更新征收机关代码失败[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                fpub_GetCompname(lXmlhandle))
      		}else
      			iNum101Succ ++;  
    			/* end add dci 20141103 */  

   				/* mod dci 20141103 
   				EXEC SQL update tips_taxcodeinfo
   					 set taxorgname=:stTaxCode.taxorgname,
   						 taxorgtype=:stTaxCode.taxorgtype,
   						 uptrecode=:stTaxCode.uptrecode,
   						 orglevel=:stTaxCode.orglevel,
   						 ofnodecode=:stTaxCode.ofnodecode,
   						 ofprovorg=:stTaxCode.ofprovorg,
   						 ofcityorg=:stTaxCode.ofcityorg,
   						 ofcountyorg=:stTaxCode.ofcountyorg,
   						 address=:stTaxCode.address,
   						 postalcode=:stTaxCode.postalcode,
   						 peoplename=:stTaxCode.peoplename,
   						 peoplephone=:stTaxCode.peoplephone,
   						 peoplemobile=:stTaxCode.peoplemobile,
   						 email=:stTaxCode.email,
   						 opersign=:stTaxCode.opersign,
   						 effectdate=:stTaxCode.effectdate,
   						 updatearea=:stTaxCode.updatearea
   				   where taxorgcode=:stTaxCode.taxorgcode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24458, "更新征收机关代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新征收机关代码失败[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    		iNum101Succ ++;
      		*/
   				break;
   			case 3: /*注销*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_taxcodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where taxorgcode ='%s'"  , stTaxCode.effectdate,stTaxCode.opersign, stTaxCode.taxorgcode);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24459, "注销征收机关代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销征收机关代码失败[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum101Succ ++;
    
   				/* end add dci 20141103 */
   				
   				/* mod dci 20141103 
   				EXEC SQL UPDATE tips_taxcodeinfo
   					 SET  effectdate=:stTaxCode.effectdate,
   						  opersign=:stTaxCode.opersign
   					WHERE taxorgcode=:stTaxCode.taxorgcode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24459, "注销征收机关代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销征收机关代码失败[%d],taxorgcode=[%s]", i, stTaxCode.taxorgcode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum101Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum101Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num101succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "更新公共数据[征收机关代码]处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("更新征收机关代码表结束，成功笔数[%d]", iNum101Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: prv_tips_UpdPUBDATA_Bank
函数名称: 更新公共数据-清算银行代码
函数功能: 
  更新公共数据-清算银行代码
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
清算银行代码	tips_bankcodeinfo

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Bank(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_BANKCODEINFO stBankCode;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum102;
    int iNum102Succ;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_BANKCODEINFO stBankCode;
		/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("更新清算银行代码表数据开始"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/BankCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum102 = 0;
    else
     	iNum102 = atoi(sBuf);
    
    if ( iNum102 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "无需更新公共数据-清算银行代码");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("无需更新公共数据-清算银行代码,共[%d]条", iNum102),
            fpub_GetCompname(lXmlhandle))        
    }
    /*取清算银行节点明细*/
    for(i = 1; i <= iNum102; i ++)
    {
        memset(&stBankCode, 0x00, sizeof(stBankCode));
   		/*1.清算银行行号*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/ReckBankNo",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.reckbankno, sTmpBuf, sizeof(stBankCode.reckbankno));
   		/*2.清算银行名称*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/GenBankName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.genbankname, sTmpBuf, sizeof(stBankCode.genbankname));
   		/*3.清算渠道*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/ReckonType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.reckontype, sTmpBuf, sizeof(stBankCode.reckontype));
   		/*4.所属节点代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/OfNodeCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.ofnodecode, sTmpBuf, sizeof(stBankCode.ofnodecode));
   		/*5.地址*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/Address",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.address, sTmpBuf, sizeof(stBankCode.address));
   		/*6.邮政编码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/PostalCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.postalcode, sTmpBuf, sizeof(stBankCode.postalcode));
   		/*7.联系人姓名*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/PeopleName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.peoplename, sTmpBuf, sizeof(stBankCode.peoplename));
   		/*8.联系人座机*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/PeoplePhone",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.peoplephone, sTmpBuf, sizeof(stBankCode.peoplephone));   		
   		/*9.联系人手机*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/PeopleMobile",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.peoplemobile, sTmpBuf, sizeof(stBankCode.peoplemobile)); 
   		/*10.电子邮箱*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/Email",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.email, sTmpBuf, sizeof(stBankCode.email));
   		/*11.操作标志*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.opersign, sTmpBuf, sizeof(stBankCode.opersign));
   		/*12.生效日期*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.effectdate, sTmpBuf, sizeof(stBankCode.effectdate));
   		/*12.更新范围*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BankCodeInfo9100/BankCodeInfo102|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBankCode.updatearea, sTmpBuf, sizeof(stBankCode.updatearea));
   		switch(atoi(stBankCode.opersign))
   		{
   			case 1: /*新增*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_bankcodeinfo", SD_TIPS_BANKCODEINFO, NUMELE(SD_TIPS_BANKCODEINFO), &stBankCode, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24460, "新增清算银行代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增清算银行代码失败[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum102Succ ++;
   				/* end add dci 20141103 */
   				
   				/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_bankcodeinfo VALUES(:stBankCode);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24460, "新增清算银行代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增清算银行代码失败[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum102Succ ++;
      		*/
   				break;
   			case 2: /*修改*/
   				/*if(atol(GetSysDate()) <= atol(stBankCode.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "reckbankno ='%s'", stBankCode.reckbankno); 
    			iRet = DBUpdate("tips_bankcodeinfo", SD_TIPS_BANKCODEINFO, NUMELE(SD_TIPS_BANKCODEINFO), &stBankCode, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24461, "更新清算银行代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新清算银行代码失败[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum102Succ ++;
      		/* end add dci 20141103 */
   				
   				/* mod dci 20141103
   				EXEC SQL update tips_bankcodeinfo
   					 set genbankname=:stBankCode.genbankname,
   						 reckontype=:stBankCode.reckontype,
   						 ofnodecode=:stBankCode.ofnodecode,
   						 address=:stBankCode.address,
   						 postalcode=:stBankCode.postalcode,
   						 peoplename=:stBankCode.peoplename,
   						 peoplephone=:stBankCode.peoplephone,
   						 peoplemobile=:stBankCode.peoplemobile,
   						 email=:stBankCode.email,
   						 opersign=:stBankCode.opersign,
   						 effectdate=:stBankCode.effectdate,
   						 updatearea=:stBankCode.updatearea
   				   where reckbankno=:stBankCode.reckbankno;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24461, "更新清算银行代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新清算银行代码失败[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum102Succ ++;
      		*/
   				break;
   			case 3: /*注销*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_bankcodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where reckbankno ='%s'" , stBankCode.effectdate,stBankCode.opersign,stBankCode.reckbankno);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24462, "注销清算银行代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销清算银行代码失败[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum102Succ ++;
    
   				/* end add dci 20141103 */
   				
   				/* mod dci 20141103 
   				EXEC SQL UPDATE tips_bankcodeinfo
   					 SET  effectdate=:stBankCode.effectdate,
   						  opersign=:stBankCode.opersign
   					WHERE reckbankno=:stBankCode.reckbankno;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24462, "注销清算银行代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销清算银行代码失败[%d],reckbankno=[%s]", i, stBankCode.reckbankno),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum102Succ ++;
   				*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum102Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num102succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "更新公共数据[清算银行代码]处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("更新清算银行代码表结束，成功笔数[%d]", iNum102Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: prv_tips_UpdPUBDATA_Node
函数名称: 更新公共数据-节点代码
函数功能: 
  更新公共数据-节点代码
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
节点代码	tips_nodecodeinfo

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Node(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_NODECODEINFO stNodeCode;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum103;
    int iNum103Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_NODECODEINFO stNodeCode;
		/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("更新节点代码表数据开始"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/NodeCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum103 = 0;
    else
     	iNum103 = atoi(sBuf);
    
    if ( iNum103 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "无需更新公共数据-节点代码");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("无需更新公共数据-节点代码,共[%d]条", iNum103),
            fpub_GetCompname(lXmlhandle))        
    }
    /*取节点代码明细*/
    for(i = 1; i <= iNum103; i ++)
    {
        memset(&stNodeCode, 0x00, sizeof(stNodeCode));
   		/*1.节点代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/NodeCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.nodecode, sTmpBuf, sizeof(stNodeCode.nodecode));
   		/*2.节点名称*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/NodeName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.nodename, sTmpBuf, sizeof(stNodeCode.nodename));
   		/*3.节点所属类型*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/OfNodeType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.ofnodetype, sTmpBuf, sizeof(stNodeCode.ofnodetype));
   		/*4.节点认证标志*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/NodeDN",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.nodedn, sTmpBuf, sizeof(stNodeCode.nodedn));
   		/*5.操作标志*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.opersign, sTmpBuf, sizeof(stNodeCode.opersign));
   		/*6.生效日期*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.effectdate, sTmpBuf, sizeof(stNodeCode.effectdate));
   		/*7.更新范围*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/NodeCodeInfo9100/NodeCodeInfo103|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stNodeCode.updatearea, sTmpBuf, sizeof(stNodeCode.updatearea));
   		switch(atoi(stNodeCode.opersign))
   		{
   			case 1: /*新增*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_nodecodeinfo", SD_TIPS_NODECODEINFO, NUMELE(SD_TIPS_NODECODEINFO), &stNodeCode, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24463, "新增节点代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增节点代码失败[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum103Succ ++;
   				/* end add dci 20141103 */
   				
   				/* mod dci 20141103 
   				EXEC SQL INSERT INTO tips_nodecodeinfo VALUES(:stNodeCode);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24463, "新增节点代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增节点代码失败[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum103Succ ++;
      		*/
   				break;
   			case 2: /*修改*/
   				/*if(atol(GetSysDate()) <= atol(stNodeCode.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "nodecode ='%s'", stNodeCode.nodecode); 
    			iRet = DBUpdate("tips_nodecodeinfo", SD_TIPS_NODECODEINFO, NUMELE(SD_TIPS_NODECODEINFO), &stNodeCode, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24464, "更新节点代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新节点代码失败[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum103Succ ++;
      			    
   				/* end add dci 20141103 */
   				
   				/* mod dci 20141103
   				EXEC SQL UPDATE tips_nodecodeinfo
   					 SET nodename=:stNodeCode.nodename,
   						 ofnodetype=:stNodeCode.ofnodetype,
   						 nodedn=:stNodeCode.nodedn,
   						 opersign=:stNodeCode.opersign,
   						 effectdate=:stNodeCode.effectdate,
   						 updatearea=:stNodeCode.updatearea
   				   WHERE nodecode=:stNodeCode.nodecode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24464, "更新节点代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新节点代码失败[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum103Succ ++;
      		*/
   				break;
   			case 3: /*注销*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_nodecodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where nodecode ='%s'" , stNodeCode.effectdate,stNodeCode.opersign,stNodeCode.nodecode);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24465, "注销节点代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销节点代码失败[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum103Succ ++;
      		/* end add dci 20141103 */
   				
   				/* mod dci 20141103   				
   				EXEC SQL UPDATE tips_nodecodeinfo
   					 SET  effectdate=:stNodeCode.effectdate,
   						  opersign=:stNodeCode.opersign
   					WHERE nodecode=:stNodeCode.nodecode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24465, "注销节点代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销节点代码失败[%d],nodecode=[%s]", i, stNodeCode.nodecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum103Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum103Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num103succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "更新公共数据[节点代码]处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("更新节点代码表结束，成功笔数[%d]", iNum103Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: prv_tips_UpdPUBDATA_Tre
函数名称: 更新公共数据-国库代码
函数功能: 
  更新公共数据-国库代码
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
节点代码	tips_trecodeinfo

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Tre(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_TRECODEINFO stTreCode;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum104;
    int iNum104Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_TRECODEINFO stTreCode;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("更新国库代码表数据开始"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TreCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum104 = 0;
    else
     	iNum104 = atoi(sBuf);
    
    if ( iNum104 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "无需更新公共数据-国库代码");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("无需更新公共数据-国库代码,共[%d]条", iNum104),
            fpub_GetCompname(lXmlhandle))        
    }
    /*取国库代码明细*/
    for(i = 1; i <= iNum104; i ++)
    {
        memset(&stTreCode, 0x00, sizeof(stTreCode));
   		/*1.国库代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/TreCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.trecode, sTmpBuf, sizeof(stTreCode.trecode));
   		/*2.国库名称*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/TreName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.trename, sTmpBuf, sizeof(stTreCode.trename));
   		/*3.国库级次*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/TreLevel",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.trelevel, sTmpBuf, sizeof(stTreCode.trelevel));
   		/*4.支付行号*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/PayBankNo",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.paybankno, sTmpBuf, sizeof(stTreCode.paybankno));
   		/*5.清算国库代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/ReckonTreCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.reckontrecode, sTmpBuf, sizeof(stTreCode.reckontrecode));
   		/*6.管理国库代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/UpTreCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.uptrecode, sTmpBuf, sizeof(stTreCode.uptrecode));
   		/*7.所属节点代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/OfNodeCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.ofnodecode, sTmpBuf, sizeof(stTreCode.ofnodecode));
   		/*8.所属省分库代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/OfProvTrea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.ofprovtrea, sTmpBuf, sizeof(stTreCode.ofprovtrea));
   		/*9.所属中心支库代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/OfCityTrea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.ofcitytrea, sTmpBuf, sizeof(stTreCode.ofcitytrea));
   		/*10.所属县支库代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/ofCountyTrea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.ofcountytrea, sTmpBuf, sizeof(stTreCode.ofcountytrea));
   		/*11.地址*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/Address",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.address, sTmpBuf, sizeof(stTreCode.address));
   		/*12.邮政编码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/PostalCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.postalcode, sTmpBuf, sizeof(stTreCode.postalcode));
   		/*13.联系人姓名*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/PeopleName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.peoplename, sTmpBuf, sizeof(stTreCode.peoplename));
   		/*14.联系人座机*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/PeoplePhone",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.peoplephone, sTmpBuf, sizeof(stTreCode.peoplephone));
   		/*15.联系人手机*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/PeopleMobile",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.peoplemobile, sTmpBuf, sizeof(stTreCode.peoplemobile));
   		/*16.Email*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/Email",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.email, sTmpBuf, sizeof(stTreCode.email));
   		/*17.操作标志*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.opersign, sTmpBuf, sizeof(stTreCode.opersign));
   		/*18.生效日期*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.effectdate, sTmpBuf, sizeof(stTreCode.effectdate));
   		/*19.更新范围*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TreCodeInfo9100/TreCodeInfo104|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTreCode.updatearea, sTmpBuf, sizeof(stTreCode.updatearea));
   		switch(atoi(stTreCode.opersign))
   		{
   			case 1: /*新增*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_trecodeinfo", SD_TIPS_TRECODEINFO, NUMELE(SD_TIPS_TRECODEINFO), &stTreCode, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24466, "新增国库代码失败");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            LOG(LM_STD,Fmtmsg("新增国库代码失败[%d],trecode=[%s]", i, stTreCode.trecode),
                fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum104Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_trecodeinfo VALUES(:stTreCode);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24466, "新增国库代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增国库代码失败[%d],trecode=[%s]", i, stTreCode.trecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum104Succ ++;
      		*/
   				break;
   			case 2: /*修改*/
   				/*if(atol(GetSysDate()) <= atol(stTreCode.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "trecode ='%s'", stTreCode.trecode); 
    			iRet = DBUpdate("tips_trecodeinfo", SD_TIPS_TRECODEINFO, NUMELE(SD_TIPS_TRECODEINFO), &stTreCode, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24467, "更新国库代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新国库代码失败[%d],trecode=[%s]", i, stTreCode.trecode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum104Succ ++;
      		
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL UPDATE tips_trecodeinfo
   					 SET trename=:stTreCode.trename,
   					     trelevel=:stTreCode.trelevel,
   					     paybankno=:stTreCode.paybankno,
   					     reckontrecode=:stTreCode.reckontrecode,
   					     uptrecode=:stTreCode.uptrecode,
   					     ofprovtrea=:stTreCode.ofprovtrea,
   					     ofcitytrea=:stTreCode.ofcitytrea,
   					     ofcountytrea=:stTreCode.ofcountytrea,
   						 ofnodecode=:stTreCode.ofnodecode,
   						 address=:stTreCode.address,
   						 postalcode=:stTreCode.postalcode,
   						 peoplename=:stTreCode.peoplename,
   						 peoplephone=:stTreCode.peoplephone,
   						 peoplemobile=:stTreCode.peoplemobile,
   						 email=:stTreCode.email,
   						 opersign=:stTreCode.opersign,
   						 effectdate=:stTreCode.effectdate,
   						 updatearea=:stTreCode.updatearea
   				   WHERE trecode=:stTreCode.trecode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24467, "更新国库代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新国库代码失败[%d],trecode=[%s]", i, stTreCode.trecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum104Succ ++;
      		*/
   				break;
   			case 3: /*注销*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_trecodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where trecode ='%s'" , stTreCode.effectdate,stTreCode.opersign,stTreCode.trecode);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24468, "注销国库代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销国库代码失败[%d],trecode=[%s]", i, stTreCode.trecode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum104Succ ++;
      		/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL UPDATE tips_trecodeinfo
   					 SET  effectdate=:stTreCode.effectdate,
   						  opersign=:stTreCode.opersign
   					WHERE trecode=:stTreCode.trecode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24468, "注销国库代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销国库代码失败[%d],trecode=[%s]", i, stTreCode.trecode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum104Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum104Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num104succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "更新公共数据[国库代码]处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("更新国库代码表结束，成功笔数[%d]", iNum104Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: prv_tips_UpdPUBDATA_Bud
函数名称: 更新公共数据-预算科目
函数功能: 
  更新公共数据-预算科目
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
预算科目	tips_budgetsubjec

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Bud(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_BUDGETSUBJECT stBudget;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum105;
    int iNum105Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_BUDGETSUBJECT stBudget;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("更新预算科目表数据开始"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/BudgetSubjectCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum105 = 0;
    else
     	iNum105 = atoi(sBuf);
    
    if ( iNum105 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "无需更新公共数据-预算科目");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("无需更新公共数据-预算科目,共[%d]条", iNum105),
            fpub_GetCompname(lXmlhandle))        
    }
    /*取预算科目明细*/
    for(i = 1; i <= iNum105; i ++)
    {
        memset(&stBudget, 0x00, sizeof(stBudget));
   		/*1.预算科目代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/BudgetSubjectCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.budgetsubjectcode, sTmpBuf, sizeof(stBudget.budgetsubjectcode));
   		/*2.预算科目名称*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/BudgetSubjectName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.budgetsubjectname, sTmpBuf, sizeof(stBudget.budgetsubjectname));
   		/*3.科目类型*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/SubjectType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.subjecttype, sTmpBuf, sizeof(stBudget.subjecttype));
   		/*4.收支标志*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/IESign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.iesign, sTmpBuf, sizeof(stBudget.iesign));
   		/*5.科目属性*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/BudgetAttrib",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.budgetattrib, sTmpBuf, sizeof(stBudget.budgetattrib));
   		/*6.操作标志*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.opersign, sTmpBuf, sizeof(stBudget.opersign));
   		/*7.生效日期*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.effectdate, sTmpBuf, sizeof(stBudget.effectdate));
   		/*8.更新范围*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/BudgetSubjectCodeInfo9100/BudgetSubjectCodeInfo105|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stBudget.updatearea, sTmpBuf, sizeof(stBudget.updatearea));
   		switch(atoi(stBudget.opersign))
   		{
   			case 1: /*新增*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_budgetsubject", SD_TIPS_BUDGETSUBJECT, NUMELE(SD_TIPS_BUDGETSUBJECT), &stBudget, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24469, "新增预算科目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增预算科目代码失败[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum105Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_budgetsubject VALUES(:stBudget);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24469, "新增预算科目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增预算科目代码失败[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum105Succ ++;
      		*/
   				break;
   			case 2: /*修改*/
   				/*if(atol(GetSysDate()) <= atol(stBudget.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "budgetsubjectcode ='%s' and subjecttype='%s' and iesign='%s'", \
		    		stBudget.budgetsubjectcode,stBudget.subjecttype,stBudget.iesign); 
    			iRet = DBUpdate("tips_budgetsubject", SD_TIPS_BUDGETSUBJECT, NUMELE(SD_TIPS_BUDGETSUBJECT), &stBudget, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24470, "更新预算科目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新预算科目代码失败[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum105Succ ++;
					/* end add dci 20141103 */
					
					/* mod dci 20141103 
   				EXEC SQL UPDATE tips_budgetsubject
   					 SET budgetsubjectname=:stBudget.budgetsubjectname,
   						 budgetattrib=:stBudget.budgetattrib,
   						 opersign=:stBudget.opersign,
   						 effectdate=:stBudget.effectdate,
   						 updatearea=:stBudget.updatearea
   				   WHERE budgetsubjectcode=:stBudget.budgetsubjectcode
   				     AND subjecttype=:stBudget.subjecttype
   				     AND iesign=:stBudget.iesign;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24470, "更新预算科目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新预算科目代码失败[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum105Succ ++;
      		*/
   				break;
   			case 3: /*注销*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_bankcodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where budgetsubjectcode ='%s' and subjecttype='%s' and iesign='%s'", \
		    		stBudget.effectdate,stBudget.opersign,stBudget.budgetsubjectcode,stBudget.subjecttype,stBudget.iesign);      			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24471, "注销预算科目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销预算科目代码失败[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum105Succ ++;
    
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL UPDATE tips_budgetsubject
   					 SET  effectdate=:stBudget.effectdate,
   						  opersign=:stBudget.opersign
   				   WHERE budgetsubjectcode=:stBudget.budgetsubjectcode
   				     AND subjecttype=:stBudget.subjecttype
   				     AND iesign=:stBudget.iesign;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24471, "注销预算科目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销预算科目代码失败[%d],budgetsubject=[%s],subjecttype=[%s],iesign=[%s]",
                        i, stBudget.budgetsubjectcode, stBudget.subjecttype, stBudget.iesign),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum105Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum105Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num105succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "更新公共数据[预算科目代码]处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("更新预算科目代码表结束，成功笔数[%d]", iNum105Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: prv_tips_UpdPUBDATA_Rea
函数名称: 更新公共数据-退库原因代码
函数功能: 
  更新公共数据-退库原因代码
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
节点代码	tips_returnreason

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Rea(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_RETURNREASON stReturn;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum106;
    int iNum106Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_RETURNREASON stReturn;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("更新退库原因代码表数据开始"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/ReturnReasonCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum106 = 0;
    else
     	iNum106 = atoi(sBuf);
    
    if ( iNum106 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "无需更新公共数据-退库原因代码");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("无需更新公共数据-退库原因代码,共[%d]条", iNum106),
            fpub_GetCompname(lXmlhandle))        
    }
    /*取退库原因代码明细*/
    for(i = 1; i <= iNum106; i ++)
    {
        memset(&stReturn, 0x00, sizeof(stReturn));
   		/*1.退库原因代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/ReturnReasonCodeInfo9100/ReturnReasonCodeInfo106|%d/ReasonCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stReturn.reasoncode, sTmpBuf, sizeof(stReturn.reasoncode));
   		/*2.描述*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/ReturnReasonCodeInfo9100/ReturnReasonCodeInfo106|%d/Description",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stReturn.description, sTmpBuf, sizeof(stReturn.description));
   		/*3.操作标志*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/ReturnReasonCodeInfo9100/ReturnReasonCodeInfo106|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stReturn.opersign, sTmpBuf, sizeof(stReturn.opersign));
   		/*4.生效日期*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/ReturnReasonCodeInfo9100/ReturnReasonCodeInfo106|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stReturn.effectdate, sTmpBuf, sizeof(stReturn.effectdate));
   		/*5.更新范围*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/ReturnReasonCodeInfo9100/ReturnReasonCodeInfo106|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stReturn.updatearea, sTmpBuf, sizeof(stReturn.updatearea));
   		switch(atoi(stReturn.opersign))
   		{
   			case 1: /*新增*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_returnreason", SD_TIPS_RETURNREASON, NUMELE(SD_TIPS_RETURNREASON), &stReturn, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24472, "新增退库原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增退库原因代码失败[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum106Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_returnreason VALUES(:stReturn);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24472, "新增退库原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增退库原因代码失败[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum106Succ ++;
      		*/	    
      			    
   				break;
   			case 2: /*修改*/
   				/*if(atol(GetSysDate()) <= atol(stReturn.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "reasoncode ='%s'", stReturn.reasoncode); 
    			iRet = DBUpdate("tips_returnreason", SD_TIPS_RETURNREASON, NUMELE(SD_TIPS_RETURNREASON), &stReturn, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24473, "更新退库原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新退库原因代码失败[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum106Succ ++;
      		
					/* end add dci 20141103 */
					
					/* mod dci 20141103 
   				EXEC SQL UPDATE tips_returnreason
   					 SET description=:stReturn.description,
   						 opersign=:stReturn.opersign,
   						 effectdate=:stReturn.effectdate,
   						 updatearea=:stReturn.updatearea
   				   WHERE reasoncode=:stReturn.reasoncode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24473, "更新退库原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新退库原因代码失败[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum106Succ ++;
      		*/
   				break;
   			case 3: /*注销*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_returnreason \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where reasoncode ='%s'" , stReturn.effectdate,stReturn.opersign,stReturn.reasoncode);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24474, "注销退库原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销退库原因代码失败[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum106Succ ++;
    
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL UPDATE tips_returnreason
   					 SET  effectdate=:stReturn.effectdate,
   						  opersign=:stReturn.opersign
   					WHERE reasoncode=:stReturn.reasoncode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24474, "注销退库原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销退库原因代码失败[%d],reasoncode=[%s]", i, stReturn.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum106Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum106Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num106succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "更新公共数据[退库原因代码]处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("更新退库原因代码表结束，成功笔数[%d]", iNum106Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: prv_tips_UpdPUBDATA_Cor
函数名称: 更新公共数据-更正原因代码
函数功能: 
  更新公共数据-更正原因代码
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
节点代码	tips_corretreason

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_Cor(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
					SDB_TIPS_CORRECTREASON stCorrect;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum107;
    int iNum107Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_CORRECTREASON stCorrect;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("更新更正原因代码表数据开始"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/CorrectReasonCodeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum107 = 0;
    else
     	iNum107 = atoi(sBuf);
    
    if ( iNum107 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "无需更新公共数据-更新原因代码");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("无需更新公共数据-更正原因代码,共[%d]条", iNum107),
            fpub_GetCompname(lXmlhandle))        
    }
    /*取更正原因代码明细*/
    for(i = 1; i <= iNum107; i ++)
    {
        memset(&stCorrect, 0x00, sizeof(stCorrect));
   		/*1.更正原因代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/CorrectReasonCodeInfo9100/CorrectReasonCode107|%d/ReasonCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stCorrect.reasoncode, sTmpBuf, sizeof(stCorrect.reasoncode));
   		/*2.描述*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/CorrectReasonCodeInfo9100/CorrectReasonCode107|%d/Description",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stCorrect.description, sTmpBuf, sizeof(stCorrect.description));
   		/*3.操作标志*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/CorrectReasonCodeInfo9100/CorrectReasonCode107|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stCorrect.opersign, sTmpBuf, sizeof(stCorrect.opersign));
   		/*4.生效日期*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/CorrectReasonCodeInfo9100/CorrectReasonCode107|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stCorrect.effectdate, sTmpBuf, sizeof(stCorrect.effectdate));
   		/*5.更新范围*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/CorrectReasonCodeInfo9100/CorrectReasonCode107|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stCorrect.updatearea, sTmpBuf, sizeof(stCorrect.updatearea));
   		switch(atoi(stCorrect.opersign))
   		{
   			case 1: /*新增*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_correctreason", SD_TIPS_CORRECTREASON, NUMELE(SD_TIPS_CORRECTREASON), &stCorrect, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24475, "新增更正原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增更正原因代码失败[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum107Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_correctreason VALUES(:stCorrect);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24475, "新增更正原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增更正原因代码失败[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum107Succ ++;
      		*/
   				break;
   			case 2: /*修改*/
   				/*if(atol(GetSysDate()) <= atol(stCorrect.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "reasoncode ='%s'", stCorrect.reasoncode); 
    			iRet = DBUpdate("tips_correctreason", SD_TIPS_CORRECTREASON, NUMELE(SD_TIPS_CORRECTREASON), &stCorrect, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24476, "更新更正原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新更正原因代码失败[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum107Succ ++;
					/* end add dci 20141103 */
					
					/* mod dci 20141103 

   				EXEC SQL UPDATE tips_correctreason
   					 SET description=:stCorrect.description,
   						 opersign=:stCorrect.opersign,
   						 effectdate=:stCorrect.effectdate,
   						 updatearea=:stCorrect.updatearea
   				   WHERE reasoncode=:stCorrect.reasoncode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24476, "更新更正原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新更正原因代码失败[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum107Succ ++;
      		*/
   				break;
   			case 3: /*注销*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_correctreason \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where reasoncode ='%s'" , stCorrect.effectdate,stCorrect.opersign,stCorrect.reasoncode);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24477, "注销更正原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销更正原因代码失败[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum107Succ ++;
    
   				/* end add dci 20141103 */
					
					/* mod dci 20141103
   				EXEC SQL UPDATE tips_correctreason
   					 SET  effectdate=:stCorrect.effectdate,
   						  opersign=:stCorrect.opersign
   					WHERE reasoncode=:stCorrect.reasoncode;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24477, "注销更正原因代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销更正原因代码失败[%d],reasoncode=[%s]", i, stCorrect.reasoncode),
                        fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum107Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum107Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num107succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "更新公共数据[更正原因代码]处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("更新更正原因代码表结束，成功笔数[%d]", iNum107Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: prv_tips_UpdPUBDATA_TaxT
函数名称: 更新公共数据-税种代码
函数功能: 
  更新公共数据-税种代码
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
税种代码	tips_taxtypeinfo

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_TaxT(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_TAXTYPEINFO stTaxType;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum108;
    int iNum108Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_TAXTYPEINFO stTaxType;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("更新税种代码表数据开始"),fpub_GetCompname(lXmlhandle));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxTypeInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum108 = 0;
    else
     	iNum108 = atoi(sBuf);
    
    if ( iNum108 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "无需更新公共数据-税种代码");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("无需更新公共数据-税种代码,共[%d]条", iNum108),
            fpub_GetCompname(lXmlhandle))        
    }
    /*取税种代码明细*/
    for(i = 1; i <= iNum108; i ++)
    {
        memset(&stTaxType, 0x00, sizeof(stTaxType));
   		/*1.税种代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/TaxTypeCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.taxtypecode, sTmpBuf, sizeof(stTaxType.taxtypecode));
   		/*2.征收机关类型*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/TaxOrgType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.taxorgtype, sTmpBuf, sizeof(stTaxType.taxorgtype));
   		/*3.税种名称*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/TaxTypeName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.taxtypename, sTmpBuf, sizeof(stTaxType.taxtypename));
   		/*4.描述*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/Description",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.description, sTmpBuf, sizeof(stTaxType.description));
   		/*5.操作标志*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.opersign, sTmpBuf, sizeof(stTaxType.opersign));
   		/*6.生效日期*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.effectdate, sTmpBuf, sizeof(stTaxType.effectdate));
   		/*7.更新范围*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxTypeInfo9100/TaxTypeCode108|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxType.updatearea, sTmpBuf, sizeof(stTaxType.updatearea));
   		switch(atoi(stTaxType.opersign))
   		{
   			case 1: /*新增*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_taxtypeinfo", SD_TIPS_TAXTYPEINFO, NUMELE(SD_TIPS_TAXTYPEINFO), &stTaxType, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24478, "新增税种代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增税种代码失败[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum108Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_taxtypeinfo VALUES(:stTaxType);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24478, "新增税种代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增税种代码失败[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum108Succ ++;
      		*/
   				break;
   			case 2: /*修改*/
   				/*if(atol(GetSysDate()) <= atol(stTaxType.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "taxtypecode ='%s' and taxorgtype='%s'", stTaxType.taxtypecode,stTaxType.taxorgtype); 
    			iRet = DBUpdate("tips_taxtypeinfo", SD_TIPS_TAXTYPEINFO, NUMELE(SD_TIPS_TAXTYPEINFO), &stTaxType, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24479, "更新税种代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新税种代码失败[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum108Succ ++;
      		
					/* end add dci 20141103 */
					
					/* mod dci 20141103 
   				EXEC SQL UPDATE tips_taxtypeinfo
   					 SET taxorgtype=:stTaxType.taxorgtype,
   					     taxtypename=:stTaxType.taxtypename,
   					     description=:stTaxType.description,
   						 opersign=:stTaxType.opersign,
   						 effectdate=:stTaxType.effectdate,
   						 updatearea=:stTaxType.updatearea
   				   WHERE taxtypecode=:stTaxType.taxtypecode
   				     AND taxorgtype=:stTaxType.taxorgtype;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24479, "更新税种代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新税种代码失败[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum108Succ ++;
      		*/
   				break;
   			case 3: /*注销*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_bankcodeinfo \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where taxtypecode ='%s' and taxorgtype='%s'" ,\
    									stTaxType.effectdate,stTaxType.opersign,stTaxType.taxtypecode,stTaxType.taxorgtype);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24480, "注销税种代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销税种代码失败[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum108Succ ++;
    
   				/* end add dci 20141103 */
					
					/* mod dci 20141103
   				EXEC SQL UPDATE tips_taxtypeinfo
   					 SET  effectdate=:stTaxType.effectdate,
   						  opersign=:stTaxType.opersign
   					WHERE taxtypecode=:stTaxType.taxtypecode
   					  AND taxorgtype=:stTaxType.taxorgtype;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24480, "注销税种代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销税种代码失败[%d],taxtypecode=[%s],taxorgtype",
                       i, stTaxType.taxtypecode, stTaxType.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum108Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum108Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num108succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "更新公共数据[税种代码]处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("更新税种代码表结束，成功笔数[%d]", iNum108Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: prv_tips_UpdPUBDATA_TaxS
函数名称: 更新公共数据-税目代码
函数功能: 
  更新公共数据-税目代码
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
税目代码	tips_taxsubject

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT prv_tips_UpdPUBDATA_TaxS(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_TAXSUBJECT stTaxSubject;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sTmpBuf[256];
    int iNum109;
    int iNum109Succ=0;
    int i;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_TAXSUBJECT stTaxSubject;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("更新税目代码表数据开始"),fpub_GetCompname(lXmlhandle));
    iNum109Succ=0;
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MSG/TaxSubjectInfo9100/UpdateNum", sBuf);
    trim(sBuf);
    if(strlen(sBuf) == 0)
    	iNum109 = 0;
    else
     	iNum109 = atoi(sBuf);
    
    if ( iNum109 == 0 )
    {
        fpub_SetMsg(lXmlhandle, 0, "无需更新公共数据-税目代码");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOGRET(COMPRET_SUCC,LM_STD,Fmtmsg("无需更新公共数据-税目代码,共[%d]条", iNum109),
            fpub_GetCompname(lXmlhandle))        
    }
    /*取税目代码明细*/
    for(i = 1; i <= iNum109; i ++)
    {
        memset(&stTaxSubject, 0x00, sizeof(stTaxSubject));
   		/*1.税目代码*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/TaxSubjectCode",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.taxsubjectcode, sTmpBuf, sizeof(stTaxSubject.taxsubjectcode));
   		/*2.征收机关类型*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/TaxOrgType",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.taxorgtype, sTmpBuf, sizeof(stTaxSubject.taxorgtype));
   		/*3.税目名称*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/TaxSubjectName",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.taxsubjectname, sTmpBuf, sizeof(stTaxSubject.taxsubjectname));
   		/*4.描述*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/Description",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.description, sTmpBuf, sizeof(stTaxSubject.description));
   		/*5.操作标志*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/OperSign",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.opersign, sTmpBuf, sizeof(stTaxSubject.opersign));
   		/*6.生效日期*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/EffectDate",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.effectdate, sTmpBuf, sizeof(stTaxSubject.effectdate));
   		/*7.更新范围*/
   		memset(sBuf, 0, sizeof(sBuf));
   		memset(sTmpBuf, 0x00, sizeof(sTmpBuf));
   		sprintf(sBuf, "/tips/MSG/TaxSubjectInfo9100/TaxSubjectCode109|%d/UpdateArea",i);
   		COMP_SOFTGETXML(sBuf, sTmpBuf);
   		pstrcopy(stTaxSubject.updatearea, sTmpBuf, sizeof(stTaxSubject.updatearea));
   		switch(atoi(stTaxSubject.opersign))
   		{
   			case 1: /*新增*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			iRet = DBInsert("tips_taxsubject", SD_TIPS_TAXSUBJECT, NUMELE(SD_TIPS_TAXSUBJECT), &stTaxSubject, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      			fpub_SetMsg(lXmlhandle, 24481, "新增税目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增税目代码失败[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum109Succ ++;
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL INSERT INTO tips_taxsubject VALUES(:stTaxSubject);
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24481, "新增税目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("新增税目代码失败[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum109Succ ++;
      		*/
   				break;
   			case 2: /*修改*/
   				/*if(atol(GetSysDate()) <= atol(stTaxSubject.effectdate))*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
		    	snprintf( sSql1, sizeof(sSql1), "taxsubjectcode ='%s' and taxorgtype='%s'", \
		    		stTaxSubject.taxsubjectcode,stTaxSubject.taxorgtype); 
    			iRet = DBUpdate("tips_taxsubject", SD_TIPS_TAXSUBJECT, NUMELE(SD_TIPS_TAXSUBJECT), &stTaxSubject, sSql1, sErrmsg);
    			if( iRet < 0 )
    			{
    				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    				
    				fpub_SetMsg(lXmlhandle, 24482, "更新税目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新税目代码失败[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum109Succ ++;
					/* end add dci 20141103 */
					
					/* mod dci 20141103 

   				EXEC SQL UPDATE tips_taxsubject
   					 SET taxorgtype=:stTaxSubject.taxorgtype,
   					     taxsubjectname=:stTaxSubject.taxsubjectname,
   					     description=:stTaxSubject.description,
   						 opersign=:stTaxSubject.opersign,
   						 effectdate=:stTaxSubject.effectdate,
   						 updatearea=:stTaxSubject.updatearea
   				   WHERE taxsubjectcode=:stTaxSubject.taxsubjectcode
   				     AND taxorgtype=:stTaxSubject.taxorgtype;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24482, "更新税目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("更新税目代码失败[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum109Succ ++;
      		*/
   				break;
   			case 3: /*注销*/
   				/* add dci 20141103 */
   				memset( sSql1, 0x00, sizeof( sSql1 ) );
    			snprintf( sSql1, sizeof(sSql1), "update tips_taxsubject \
    						set  effectdate='%s',\
											opersign=='%s'\
    									where taxsubjectcode ='%s' and taxorgtype='%s'", \
		    		stTaxSubject.effectdate,stTaxSubject.opersign,stTaxSubject.taxsubjectcode,stTaxSubject.taxorgtype);     			    			
    			iRet = DCIExecuteDirect(sSql1);	 
    			if ( iRet < 0 )
    			{
        		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
        
        		fpub_SetMsg(lXmlhandle, 24483, "注销税目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销税目代码失败[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		}else
      			    iNum109Succ ++;
    
   				/* end add dci 20141103 */

					/* mod dci 20141103
   				EXEC SQL UPDATE tips_taxsubject
   					 SET  effectdate=:stTaxSubject.effectdate,
   						  opersign=:stTaxSubject.opersign
   					WHERE taxsubjectcode=:stTaxSubject.taxsubjectcode
   					  AND taxorgtype=:stTaxSubject.taxorgtype;
   				SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_UPDATE,sqlca.sqlcode),"ERROR");
   				if ( SQLERR )
   				{
                    fpub_SetMsg(lXmlhandle, 24483, "注销税目代码失败");
                    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                    LOG(LM_STD,Fmtmsg("注销税目代码失败[%d],taxsubjectcode=[%s]taxorgtype=[%s]", 
                        i, stTaxSubject.taxsubjectcode, stTaxSubject.taxorgtype),fpub_GetCompname(lXmlhandle))
      		    }else
      			    iNum109Succ ++;
      		*/
   				break;
   			default:
   				break;
   		}
    }

    memset(sBuf, 0x00, sizeof(sBuf));
    snprintf(sBuf, sizeof(sBuf), "%d", iNum109Succ);
    trim(sBuf);
    COMP_SOFTSETXML("/tips/num109succ", sBuf)
    
    fpub_SetMsg(lXmlhandle, 0, "更新公共数据[税目代码]处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("更新税目代码表结束，成功笔数[%d]", iNum109Succ), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_UpdPUBDATA
组件名称: 更新公共数据
组件功能: 
  更新公共数据
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
数据更新汇总表	tips_sjgxhz

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_UpdPUBDATA(HXMLTREE lXmlhandle)
{
    int iParas;
    char sZwrq[8+1];
    int  iZhqzlsh;
    char sWorkDate[8+1];
    char sUpdateBatch[8+1];    
    char sBuf[256];
    int iRet;
    
    fpub_InitSoComp(lXmlhandle);
    
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif
    
    COMP_PARACOUNTCHK(4);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sZwrq, 0x00, sizeof(sZwrq));
    COMP_GETPARSEPARAS(1, sBuf, "帐务日期")
    pstrcopy( sZwrq, sBuf, sizeof(sZwrq));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "综合前置流水号")
    iZhqzlsh=atoi(sBuf);   

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sWorkDate, 0x00, sizeof(sWorkDate));
    COMP_GETPARSEPARAS(3, sBuf, "工作日期")
    pstrcopy( sWorkDate, sBuf, sizeof(sWorkDate));
        
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sUpdateBatch, 0x00, sizeof(sUpdateBatch));
    COMP_GETPARSEPARAS(4, sBuf, "更新批次")
    pstrcopy( sUpdateBatch, sBuf, sizeof(sUpdateBatch));

    LOG(LM_STD,Fmtmsg("更新公共数据开始处理..."), fpub_GetCompname(lXmlhandle))
    LOG(LM_STD,Fmtmsg("帐务日期[%s],前置流水号[%d],工作日期[%s],更新批次[%s]...",
        sZwrq, iZhqzlsh, sWorkDate, sUpdateBatch), fpub_GetCompname(lXmlhandle))   
    
    /* 更新征收机关代码 */
    iRet = prv_tips_UpdPUBDATA_Tax(lXmlhandle);
    /* 更新清算银行代码 */
    iRet = prv_tips_UpdPUBDATA_Bank(lXmlhandle);   
    /* 更新节点代码 */
    iRet = prv_tips_UpdPUBDATA_Node(lXmlhandle);
    /* 更新国库代码 */
    iRet = prv_tips_UpdPUBDATA_Tre(lXmlhandle);
    /* 更新预算科目代码 */
    iRet = prv_tips_UpdPUBDATA_Bud(lXmlhandle);   
    /* 更新退库原因代码 */
    iRet = prv_tips_UpdPUBDATA_Rea(lXmlhandle);
    /* 更新更正原因代码 */
    iRet = prv_tips_UpdPUBDATA_Cor(lXmlhandle);
    /* 更新税种代码 */
    iRet = prv_tips_UpdPUBDATA_TaxT(lXmlhandle);
    /* 更新税目代码 */
    iRet = prv_tips_UpdPUBDATA_TaxS(lXmlhandle);
    /* 登记数据更新汇总表 */
    iRet = prv_tips_UpdPUBDATA(lXmlhandle, sZwrq, iZhqzlsh, sWorkDate, sUpdateBatch);
        
    fpub_SetMsg(lXmlhandle, 0, "更新公共数据处理结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("更新公共数据处理结束..."), fpub_GetCompname(lXmlhandle))
    return COMPRET_SUCC;   
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitZYGSBW
组件名称: 初始自由格式报文表
组件功能: 
  初始自由格式报文表
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
自由格式报文	tips_zygsbw

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年02月19日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitZYGSBW(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_ZYGSBW stZygsbw;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[2050];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_ZYGSBW stZygsbw;
		/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("初始自由格式报文表数据开始处理..."),fpub_GetCompname(lXmlhandle))

    memset(&stZygsbw, 0x00, sizeof(stZygsbw));
    COMP_PARACOUNTCHK(2);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"帐务日期")
    pstrcopy(stZygsbw.zwrq, sBuf, sizeof(stZygsbw.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"综合前置流水号")
    stZygsbw.zhqzlsh=atoi(sBuf);

    LOG(LM_STD,Fmtmsg("帐务日期[%s],前置流水号[%d]...", stZygsbw.zwrq, stZygsbw.zhqzlsh),fpub_GetCompname(lXmlhandle))

    /* 3.工作日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stZygsbw.workdate, sBuf, sizeof(stZygsbw.workdate));
    /* 4.消息类型 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/MsgType", sBuf)
    pstrcopy(stZygsbw.msgtype, sBuf, sizeof(stZygsbw.msgtype));
    /* 5.源节点代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/SrcNodeCode", sBuf)
    pstrcopy(stZygsbw.srcnodecode, sBuf, sizeof(stZygsbw.srcnodecode));
    /* 6.目的节点代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/DesNodeCode", sBuf)
    pstrcopy(stZygsbw.desnodecode, sBuf, sizeof(stZygsbw.desnodecode));    
    /* 7.发起机构代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/SendOrgCode", sBuf)
    pstrcopy(stZygsbw.sendorgcode, sBuf, sizeof(stZygsbw.sendorgcode));
    /* 8.接收机构代码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/RcvOrgCode", sBuf)
    pstrcopy(stZygsbw.rcvorgcode, sBuf, sizeof(stZygsbw.rcvorgcode));      
    /* 9.阅读标志 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ydbz", sBuf)
    pstrcopy(stZygsbw.ydbz, sBuf, sizeof(stZygsbw.ydbz));
    /* 10.内容 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/Content", sBuf)
    pstrcopy(stZygsbw.content, sBuf, sizeof(stZygsbw.content));    
    /* 11.交易日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/sysdate", sBuf)
    pstrcopy(stZygsbw.jyrq, sBuf, sizeof(stZygsbw.jyrq));
    /* 12.交易时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/sys/systime", sBuf)
    pstrcopy(stZygsbw.jysj, sBuf, sizeof(stZygsbw.jysj)); 
    /* 13.地区代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/dqdh", sBuf)
    pstrcopy(stZygsbw.dqdh, sBuf, sizeof(stZygsbw.dqdh));
    /* 14.机构代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jgdh", sBuf)
    pstrcopy(stZygsbw.jgdh, sBuf, sizeof(stZygsbw.jgdh));    
    /* 15.交易柜员 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/jygy", sBuf)
    pstrcopy(stZygsbw.jygy, sBuf, sizeof(stZygsbw.jygy));
    /* 16.终端代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/zddh", sBuf)
    pstrcopy(stZygsbw.zddh, sBuf, sizeof(stZygsbw.zddh)); 
    /* 17.备用字段 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/pub/byzd", sBuf)
    pstrcopy(stZygsbw.byzd, sBuf, sizeof(stZygsbw.byzd));
		/* add dci 20141103 */
   	memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_zygsbw", SD_TIPS_ZYGSBW, NUMELE(SD_TIPS_ZYGSBW), &stZygsbw, sErrmsg);
    if( iRet < 0 )
    {
    		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      	fpub_SetMsg(lXmlhandle, 24484, "初始化自由格式报文表数据失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("InitZYGSBW初始化自由格式报文表数据失败"),
          fpub_GetCompname(lXmlhandle))  
    }	 
   	/* end add dci 20141103 */
		
		/* mod dci 20141103
    EXEC SQL INSERT INTO tips_zygsbw  VALUES (:stZygsbw);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24484, "初始化自由格式报文表数据失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("InitZYGSBW初始化自由格式报文表数据失败"),
            fpub_GetCompname(lXmlhandle))  
    }	 
    */   

    fpub_SetMsg(lXmlhandle, 0, "初始化自由格式报文表数据成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("初始化自由格式报文表数据成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;     
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_AddBEGIN
组件名称: 在文件头加BEGIN
组件功能: 
  在文件头加BEGIN
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年03月4日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_AddBEGIN(HXMLTREE lXmlhandle)
{
    int iParas;
    char sOutFileName[255];
    FILE *Outfp;

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(1)
    memset(sOutFileName, 0x00, sizeof(sOutFileName));
    COMP_GETPARSEPARAS(1,sOutFileName,"合并的文件名");
      
    /*先建传出文件,校验*/
    Outfp = fopen(sOutFileName,"w+");
    if ( Outfp == NULL )
    {
         fpub_SetMsg(lXmlhandle, 24114, "在文件头加BEGIN失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("在文件头加BEGIN失败[%s]", 
             strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
     
    fprintf(Outfp,"BEGIN\n");       

    fclose(Outfp);
    fpub_SetMsg(lXmlhandle, 0, "增加文件应BEGIN成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("增加文件应BEGIN成功"), fpub_GetCompname(lXmlhandle));             
    return COMPRET_SUCC;
   
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_AddFileBEGIN
组件名称: 在文件头加BEGIN
组件功能: 
  在文件头加特定字符串
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作

项 目 组: TIPS专用前置产品组
程 序 员: 
发布日期: 2014年09月03日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_AddFileBEGIN(HXMLTREE lXmlhandle)
{
    int iParas;
    char sOutFileName[255];
    char sBeginStr[255];
    FILE *Outfp;

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(1)
    memset(sOutFileName, 0x00, sizeof(sOutFileName));
    COMP_GETPARSEPARAS(1,sOutFileName,"合并的文件名");
    COMP_PARACOUNTCHK(2)
    memset(sBeginStr, 0x00, sizeof(sBeginStr));
    COMP_GETPARSEPARAS(2,sBeginStr,"追加文件头部字符串");
      
    /*先建传出文件,校验*/
    Outfp = fopen(sOutFileName,"w+");
    if ( Outfp == NULL )
    {
         fpub_SetMsg(lXmlhandle, 24114, "在文件头加头失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("在文件头加头失败[%s]", 
             strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
    
    if ( strlen(sBeginStr) <=0 )
    {
         fpub_SetMsg(lXmlhandle, 24114, "追加字符串为空");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("在文件头加头失败[%s]", 
             strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
     
    fprintf(Outfp,"%s\n",sBeginStr);       

    fclose(Outfp);
    fpub_SetMsg(lXmlhandle, 0, "增加文件应BEGIN成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("增加文件应BEGIN成功"), fpub_GetCompname(lXmlhandle));             
    return COMPRET_SUCC;
   
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_AddEND
组件名称: 在文件尾加END
组件功能: 
  在文件尾加END
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年03月4日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_AddEND(HXMLTREE lXmlhandle)
{
    int iParas;
    char sOutFileName[255];
    FILE *Outfp;

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(1)
    memset(sOutFileName, 0x00, sizeof(sOutFileName));
    COMP_GETPARSEPARAS(1,sOutFileName,"合并的文件名");
      
    /*先建传出文件,校验*/
    Outfp = fopen(sOutFileName,"a+");
    if ( Outfp == NULL )
    {
         fpub_SetMsg(lXmlhandle, 24115, "在文件尾加END失败");
         fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("在文件尾加END失败[%s]", 
             strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
     
    fprintf(Outfp,"END\n");       

    fclose(Outfp);
    fpub_SetMsg(lXmlhandle, 0, "在文件尾加END成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("在文件尾加END成功"), fpub_GetCompname(lXmlhandle));             
    return COMPRET_SUCC;
   
}    
 
/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_UniteTWOFILE
组件名称: 合并两个文件
组件功能: 
  合并两个文件
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年03月4日
修改日期: 
参数使用示例: 
************************************************************************/    
IRESULT SYW_TIPS_UniteTWOFILE(HXMLTREE lXmlhandle)
{

    int iParas;
    char sDrFileName[255],sOutFileName[255];
    char sLine[1024];
    FILE *Drfp,*Outfp;
    int i;
    int iFlag;

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(2)
    memset(sDrFileName, 0x00, sizeof(sDrFileName));    
    COMP_GETPARSEPARAS(1,sDrFileName,"子文件名");
    memset(sOutFileName, 0x00, sizeof(sOutFileName));
    COMP_GETPARSEPARAS(2,sOutFileName,"母文件名");
    trim(sDrFileName);trim(sOutFileName);

    LOG(LM_STD,Fmtmsg("子文件名[%s],母文件名[%s]", sDrFileName, sOutFileName), fpub_GetCompname(lXmlhandle));
          
    /*先建母文件,校验*/
    Outfp = fopen(sOutFileName,"a+");
    if ( Outfp == NULL )
    {
        fpub_SetMsg(lXmlhandle, 24116, "打开文件失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开文件失败[%s]", 
            strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
   
    /*打开子文件,校验*/
    Drfp = fopen(sDrFileName,"r");
    if ( Drfp == NULL )
    {
   	    fclose(Outfp);
        fpub_SetMsg(lXmlhandle, 24116, "打开文件失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("打开文件失败[%s]", 
            strerror(errno)), fpub_GetCompname(lXmlhandle))
    }
   
    /*文件体处理,将当日流水文件逐条写入合并文件*/
    for (iFlag=0,i=1; ;i++)
    {   	
        memset(sLine,0x00,sizeof(sLine)); 
        if (fgets(sLine,sizeof(sLine),Drfp)	== NULL)
            break;                   /*文件结束 跳出*/
        sLine[strlen(sLine)-1]=0;   /*去除最后一个换行符*/       
        fprintf(Outfp,"%s\n",sLine);       
    }/*end for*/
    fclose(Drfp);
    fclose(Outfp);
   
    fpub_SetMsg(lXmlhandle, 0, "合并文件成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("合并文件成功"), fpub_GetCompname(lXmlhandle));             
    return COMPRET_SUCC;   
}
    
/*将通讯缓冲区内容放入指定的XML结点中*/
IRESULT STIPS_Hex2Asc(HXMLTREE lXmlhandle)
{
    char sSrcPara[50], spara[50], sBz[30];
    char sCommbuf[32000];  
    long lCommlen;
    int iParas;
    
    fpub_InitSoComp(lXmlhandle);
    COMP_PARACOUNTCHK(3);
    COMP_GETPARAS(1,sSrcPara,"源XML项");
    COMP_GETPARAS(2,spara,"目标XML项");
    COMP_GETPARSEPARAS(3,sBz,"标志0 BCD->ASC 非0 ASC->BCD");
    trim(sBz);
    if (sBz[0]=='0')
    {  
        if ( (lCommlen=xml_GetBinElement(lXmlhandle,sSrcPara,sCommbuf,sizeof(sCommbuf))) < 0 )
        {
            LOG(LM_STD,Fmtmsg(MSG_SYS_XMLGET,XMLNM_COMMBUF,GETXMLERR),"")
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            LOGRET(MID_SYS_FAIL,LM_STD,Fmtmsg(MSG_SYS_XMLPARSE,spara,GETXMLERR),"")
        } 
        COMP_HARDSETXML(spara,sCommbuf);
    }
    else
    {
        COMP_HARDGETXML(sSrcPara,sCommbuf);
        if ( (lCommlen=xml_SetBinElement(lXmlhandle,spara,sCommbuf,strlen(sCommbuf))) < 0 ) //modefy by lrj 20180810
        {
            LOG(LM_STD,Fmtmsg(MSG_SYS_XMLGET,XMLNM_COMMBUF,GETXMLERR),"")
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            LOGRET(MID_SYS_FAIL,LM_STD,Fmtmsg(MSG_SYS_XMLPARSE,spara,GETXMLERR),"")
        }   
    }
   
    fpub_SetCompStatus(lXmlhandle,COMPRET_SUCC);
    return COMPRET_SUCC;  	
}

/*比较日期1是否大于日期2
 *1-真 0-否
 *因系统组件(DATA_VarCompare)不好用，故写此组件
 */
IRESULT STIPS_DateCompare(HXMLTREE lXmlhandle)
{
    char sBuf[256];
    char sDate1[8+1];
    char sDate2[8+1];
    char sDate1Year[4+1], sDate1Mon[2+1], sDate1Day[2+1]; 
    char sDate2Year[4+1], sDate2Mon[2+1], sDate2Day[2+1];  
    int iParas;
    int iResult = 0 ;/* 日期一小于日期二,假 */
    
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHK(2);
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDate1, 0x00, sizeof(sDate1));
    COMP_GETPARSEPARAS(1,sBuf,"日期1");
    pstrcopy(sDate1, sBuf, sizeof(sDate1));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sDate2, 0x00, sizeof(sDate2));
    COMP_GETPARSEPARAS(2,sBuf,"日期2");
    pstrcopy(sDate2, sBuf, sizeof(sDate2));
    
    LOG(LM_STD,Fmtmsg("比较日期1[%s]是否大于日期2[%s]开始处理", 
        sDate1, sDate2), fpub_GetCompname(lXmlhandle))
    
    /* 把两日期分别放到各自的年月日变量中去 */
    memset(sDate1Year, 0x00, sizeof(sDate1Year));
    memset(sDate1Mon, 0x00, sizeof(sDate1Mon));
    memset(sDate1Day, 0x00, sizeof(sDate1Day));
    pstrcopy(sDate1Year, sDate1, sizeof(sDate1Year));
    pstrcopy(sDate1Mon, sDate1+4, sizeof(sDate1Mon));
    pstrcopy(sDate1Day, sDate1+4+2, sizeof(sDate1Day));
    LOG(LM_STD,Fmtmsg("日期1-->year[%s],mon[%s],day[%s]", 
        sDate1Year, sDate1Mon, sDate1Day), fpub_GetCompname(lXmlhandle))
    memset(sDate2Year, 0x00, sizeof(sDate2Year));
    memset(sDate2Mon, 0x00, sizeof(sDate2Mon));
    memset(sDate2Day, 0x00, sizeof(sDate2Day));
    pstrcopy(sDate2Year, sDate2, sizeof(sDate2Year));
    pstrcopy(sDate2Mon, sDate2+4, sizeof(sDate2Mon));
    pstrcopy(sDate2Day, sDate2+4+2, sizeof(sDate2Day));    
    LOG(LM_STD,Fmtmsg("日期2-->year[%s],mon[%s],day[%s]", 
        sDate2Year, sDate2Mon, sDate2Day), fpub_GetCompname(lXmlhandle))    
    /* 开始进行日期比较 */
    if(atoi(sDate1Year) > atoi(sDate2Year))
    {
        iResult = 1 ;
    }else/* 年份相等,进行月份比较 */
    {
        if(atoi(sDate1Mon) > atoi(sDate2Mon))
        {
            iResult = 1 ;
        }else/* 年月份相等，进行日份比较 */
        {
            if(atoi(sDate1Day) > atoi(sDate2Day))
                 iResult = 1 ;
        }        
    }        

    fpub_SetCompStatus(lXmlhandle,iResult);
    return COMPRET_SUCC;  	
}

/******************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_FileToBuf
组件名称: 将文件内容倒入到commbuf
组件功能: 
          
组件参数: 
序号 参数名称         资源类别   缺省值         是否可空  参数说明
 

组件结果状态: 
  结果状态码         结果说明
  缺省

日志信息: 
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息
  
主要操作元素:
  元素路径          操作

主要操作库表:
  表名              操作

使用限制:
          
项 目 组: 中间业务产品研发组
程 序 员: tuql
发布日期: 2009年04月29日
修改日期: 
参数使用示例: 
******************************************************************************/ 
IRESULT SYW_TIPS_FileToBuf(HXMLTREE lXmlhandle)
{ 
   
    int iParas,iRet,ilen2;
    char sfile[256];
    char *sbuf;
    char snode[30];
    FILE *fp;
    struct stat struStat;
    char *pstr;/* add by tuql 20090831 */
    int ilen=0;/* add by tuql 20090831 */
    char sBaseNode[256];
       
    fpub_InitSoComp(lXmlhandle);

    memset(sfile, 0x00, sizeof(sfile));
    COMP_GETPARSEPARAS(1,sfile,"导入文件路径");
    trim(sfile);
    memset(sBaseNode, 0x00, sizeof(sBaseNode));
    COMP_GETPARSEPARAS(2,sBaseNode,"基准结点");
    trim(sBaseNode);
    if (sBaseNode[0]=='\0')
    {
        snprintf(sBaseNode, sizeof(sBaseNode), "%s", "/commbuf");
    }    

    LOG(LM_STD,Fmtmsg("将文件导入XML树执行开始,basenode[%s]file=[%s]", 
        sBaseNode,sfile),fpub_GetCompname(lXmlhandle))

    if((fp=fopen(sfile,"r"))==NULL)
    {
    	LOG(LM_STD,Fmtmsg(" 获得文件失败[%s]", strerror(errno)),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" 获得文件失败"));
        fpub_SetCompStatus(lXmlhandle,-1);
        return -1;
    }
    fstat(fileno(fp), &struStat);
    ilen = struStat.st_size;
    ilen2 = ilen * 1.5;
    if((sbuf=malloc(ilen2))==NULL)
    {
        fclose(fp);
        LOG(LM_STD,Fmtmsg(" 动态分配内存失败[%s]",sfile),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" 动态分配内存失败"));
        fpub_SetCompStatus(lXmlhandle,-1);
        return -1;          	 	  	
    }	
    fread(sbuf,ilen,1,fp);
    fclose(fp);
    sbuf[ilen]=0; 
      
    /* 将数字签名去掉  add by tuql 20090831 
    pstr = strstr(sbuf,"<!--");
    if (pstr != NULL )
    {
       *pstr = 0;
    }*/
    /*sbuf[strlen(sbuf)-1]=0;*/	   
    /*写入通讯区数据*/
    iRet = 0;
    if ( (iRet= xml_RelSetBinElement ( lXmlhandle, sBaseNode, sbuf, ilen)) <0 )
    {
        free(sbuf);
        LOG(LM_STD,Fmtmsg("保存XML结点数据失败,ret[%d]",iRet),"ERROR");	
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("保存XML结点数据失败"));
        fpub_SetCompStatus(lXmlhandle,-1);
        return -1;
    }
    free(sbuf);
   
    #ifdef DEBUG
          LOG(LM_DEBUG,Fmtmsg("将缓冲数据导入文件组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif
      
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称: STIPS_ImpFromBuf
组件名称: 从COMMBUF中导入XML组件
组件功能: 
  将COMMBUF中的内容导入
  可视为  XML 解包组件
组件参数: 
  序号 参数名称     资源类别     缺省值   是否可空  参数说明
1 NODE         结点名      无   否      COMMBUF的NODE名，一般为/COMMBUF
2 导入路径     XML节点     无   否      XML导入后存放的基准节点
3 导入方式     字符串      1    否      覆盖方式:  1-覆盖方式, 0-不覆盖方式(跳过)
4 是否格式化                            0-不处理, 1-XML 2.0->1.0转换(简写)


组件结果状态: 
  结果状态码         结果说明
  缺省

日志信息: 
  日志级别           日志宏

响应信息:
  内部响应码         内部响应信息

  
项 目 组: 中间业务产品研发组
程 序 员: 中间业务产品发展部研发组
发布日期: 2000年01月01日
修改日期: 2005-11-23 21:12
参数使用示例: 
************************************************************************/
IRESULT STIPS_ImpFromBuf(HXMLTREE lXmlhandle) 
{
  char snode[100],dest[50],smode[20],sroot[20];
  int mode ,ret, iParas;
  char sxmlpath[50],stwo[20];
  char *buf;
  int ilen;  
  
  fpub_InitSoComp(lXmlhandle);
  COMP_PARACOUNTCHKMIN(4)
  COMP_GETPARSEPARAS(1,snode,   "COMMBUFNODE");
  COMP_GETPARSEPARAS(2,dest,    "导入路径");
  COMP_GETPARSEPARAS(3,smode,   "导入方式");
  COMP_GETPARSEPARAS(4,stwo,    "是否进行格式化处理");  /*将<node1/>==><node1></node1>*/
  mode=atoi(smode);
  
  /*取节点数据长度*/
  ilen=xml_GetElementLen(lXmlhandle,snode);
  if (ilen <= 0)
  {
  	  LOG(LM_STD,Fmtmsg("  -->XML IMP ERR, node[%s]不存在或内容为空",snode),"ERROR");
      fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" XML导入失败,源数据内容为空"));
      fpub_SetCompStatus(lXmlhandle,-1);
      return -1;
  }		
  ilen = ilen / 2 ;       /*HEX方式*/
  ilen = ilen *1.5;
  if((buf=malloc(ilen))==NULL)
  {
    fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML导入失败,异常1"));
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    LOGRET(-1,LM_STD,
           Fmtmsg("malloc err,len[%d]",ilen),fpub_GetCompname(lXmlhandle)) 
    return -1; 	  	
  }
  if((ret=xml_GetBinElement(lXmlhandle,snode,buf,ilen))== FAIL)
  {
    free(buf);
    LOG(LM_DEBUG,Fmtmsg(MSG_SYS_XMLBINGET,snode,GETXMLERR),"ERROR");
    fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" XML导入失败,获取数据失败"));
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
    return -1;
  }
  buf[ret]=0;   
  if (strcmp(stwo,"1")==0) 
  {
     ret=xml_Conv2to1(buf,ilen);
  }
  ret=xml_ElementExist( lXmlhandle, XML_TMPNODE );
  if (ret==1)
  {
    LOG(LM_DEBUG,Fmtmsg("XML_IMPFROM Warning:系统临时节点[%s]已存在,将被删除!!",XML_TMPNODE),"");
    if ( xml_DelElement( lXmlhandle,XML_TMPNODE)==-1 ) 
    {
       free(buf);
       fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML导入失败,处理异常"));
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       LOG(LM_STD,Fmtmsg("删除临时结果出错!,ret[%d]",-9),"");
       return -9;   
    }
  }
  COMP_SOFTSETXML(XML_TMPNODE,"");	
  if (xml_ImportXMLString( lXmlhandle, buf, XML_TMPNODE, 0 )==-1)
  {
     free(buf);
     /* 
     LOG(LM_STD,Fmtmsg("XMLERR[%s],ilen[%d],buf[%-100.100s]",
         xml_StringError(xml_GetLastError()),ilen,buf),"ERROR");
         */
     xml_DelElement( lXmlhandle,XML_TMPNODE); /*删除不成功不影响结果*/
     fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML导入失败,请检查格式是否正确"));
     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     LOG(LM_STD,Fmtmsg("从BUF导入XML失败,请检查XML格式是否正确!"),"ERROR");
     return -8; 
  }
  free(buf);
  LOG(LM_DEBUG,Fmtmsg("  -->5导入内容长度[%d]",ilen),"DEBUG");
  /*在此获取根结点名*/
  if (xml_GetChildElementName(lXmlhandle,XML_TMPNODE,1,sroot,sizeof(sroot)) < 0)
  {
     fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML导入失败,异常3"));
     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     LOG(LM_STD,Fmtmsg("从文件导入XML失败,请检查XML根结点是否正确!"),"");
     return -9; 
  }	
  sprintf(sxmlpath,"%s/%s",XML_TMPNODE,sroot);
  ret=xml_ElementExist( lXmlhandle, dest );
  if (ret!=1)
  {
    COMP_HARDSETXML(dest,"");	
  }	
  /*导入方式为1-覆盖时,直接采用node move方式*/
/*  xml_NodeMove 函数有BUG,尚在测试期,停止使用,对于较大的XML树,move方式效率很高
    Tianhc 2006-3-19 15:05
  if (mode == 1 )
  {
  	  if (xml_NodeMove( lXmlhandle,dest,sxmlpath) < 0 )
      {
         xml_DelElement( lXmlhandle,XML_TMPNODE); 
		     fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML导入失败,异常4"));
		     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		     LOG(LM_STD,Fmtmsg("XML导入失败,xml_NodeMove err!"),"ERROR");
		     return -10; 
      }		
      xml_DelElement( lXmlhandle,XML_TMPNODE); 
		  fpub_SetCompStatus(lXmlhandle,0);
		  LOG(LM_STD,Fmtmsg("  -->从BUF导入XML成功,node[%s]=>[%s],[%s]",snode,dest,sroot),"MOVE");  
		  return 0;
  }
*/  	
  ret=xml_XCopy(lXmlhandle, sxmlpath, dest, mode);
  xml_DelElement( lXmlhandle,XML_TMPNODE); /*删除不成功不影响结果*/
  if (ret<0)
  {
    LOG(LM_STD,Fmtmsg("从BUF导入XML失败, ret[%d],note[%s]",ret,snode),"ERROR");	
    fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("XML导入失败,数据处理失败"));
    fpub_SetCompStatus(lXmlhandle,-1);
    return -1;
  }	
  fpub_SetCompStatus(lXmlhandle,0);
  LOG(LM_STD,Fmtmsg("  -->从BUF导入XML成功,node[%s]=>[%s],ret[%d]",snode,dest,ret),"XCOPY");  
  return 0;
}	

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InitYXCS
组件名称: 登记运行参数表
组件功能: 
  登记运行参数表
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
自由格式报文	tips_yxcs

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年10月22日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_InitYXCS(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_YXCS stYxcs;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[128];
    int iTypeList=0;/* 参数类型信息条数 */
    int iDetailList=0;/* 参数明细信息条数 */
    char sTypeList[128];/* 参数类型信息节点路径 */
    char sDetailList[128];/* 参数明细信息节点路径 */
    char sParaNode[128];/* 某个节点路径 */
    char sRootNode[32];/* 根节点 */
    int i,j,iFlag1,iFlag2;
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_YXCS stYxcs;
		/* end add dci 20141103 */
		
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("登记运行参数表数据开始处理..."),fpub_GetCompname(lXmlhandle))

    memset(&stYxcs, 0x00, sizeof(stYxcs));
    COMP_PARACOUNTCHK(3);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"帐务日期")
    pstrcopy(stYxcs.zwrq, sBuf, sizeof(stYxcs.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"综合前置流水号")
    stYxcs.zhqzlsh=atoi(sBuf);

    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRootNode, 0x00, sizeof(sRootNode));
    COMP_GETPARAS(3,sBuf,"根节点")
    pstrcopy(sRootNode, sBuf, sizeof(sRootNode));
    trim(sRootNode);

    LOG(LM_STD,Fmtmsg("帐务日期[%s],前置流水号[%d],根节点[%s]...", 
        stYxcs.zwrq, stYxcs.zhqzlsh, sRootNode),fpub_GetCompname(lXmlhandle))

    /* 3.工作日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(stYxcs.workdate, sBuf, sizeof(stYxcs.workdate));
        
    /* 获取参数类型信息条数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    iTypeList=0;
    snprintf(sBuf, sizeof(sBuf), "%s/%s", sRootNode, "ParamTypeList9106");
    trim(sBuf);
    if ((iTypeList=xml_ElementCount(lXmlhandle,sBuf))==-1)
    { 
        LOG(LM_DEBUG,Fmtmsg("组件[%s]:%s:[%s]",fpub_GetCompname(lXmlhandle),"获取参数类型信息条数失败！",sBuf),fpub_GetCompname(lXmlhandle))  
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,
            Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(MID_SYS_FAIL,LM_STD,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)),
           fpub_GetCompname(lXmlhandle))
    }
    for  (i=1,iFlag1=0; i<=iTypeList; i++ )
    {   
        memset(sTypeList, 0x00, sizeof(sTypeList));
        snprintf(sTypeList, sizeof(sTypeList),"%s/%s|%d", sRootNode, "ParamTypeList9106", i);
        memset(stYxcs.paramtypeno, 0x00, sizeof(stYxcs.paramtypeno));
        memset(stYxcs.paramdescrip, 0x00, sizeof(stYxcs.paramdescrip));
        
        /* 4.参数类型编号 */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sParaNode, 0x00, sizeof(sParaNode));
        snprintf(sParaNode, sizeof(sParaNode), "%s/ParamTypeNo", sTypeList);
        COMP_SOFTGETXML(sParaNode, sBuf)
        pstrcopy(stYxcs.paramtypeno, sBuf, sizeof(stYxcs.paramtypeno));
        trim(stYxcs.paramtypeno);
        /* 5.参数类型描述 */
        memset(sBuf, 0x00, sizeof(sBuf));
        memset(sParaNode, 0x00, sizeof(sParaNode));
        snprintf(sParaNode, sizeof(sParaNode), "%s/Description", sTypeList);
        COMP_SOFTGETXML(sParaNode, sBuf)
        pstrcopy(stYxcs.paramdescrip, sBuf, sizeof(stYxcs.paramdescrip));
        trim(stYxcs.paramdescrip);        
        /* 获取参数明细信息条数 */
        memset(sBuf, 0x00, sizeof(sBuf));
        iDetailList=0;
        snprintf(sBuf, sizeof(sBuf), "%s/%s", sTypeList, "ParamList9106");
        trim(sBuf);
        if ((iDetailList=xml_ElementCount(lXmlhandle,sBuf))==-1)
        { 
            LOG(LM_DEBUG,Fmtmsg("组件[%s]:%s:[%s]",fpub_GetCompname(lXmlhandle),"获取参数明细信息条数失败！", sBuf),fpub_GetCompname(lXmlhandle))  
            fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,
                Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            LOGRET(MID_SYS_FAIL,LM_STD,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)),
                fpub_GetCompname(lXmlhandle))
        }
        
        for (j=1,iFlag2=0; j<=iDetailList; j++ )
        {
            memset(sDetailList, 0x00, sizeof(sDetailList));
            snprintf(sDetailList, sizeof(sDetailList),"%s/%s|%d", sTypeList, "ParamList9106", j);
            memset(stYxcs.detailno, 0x00, sizeof(stYxcs.detailno));
            memset(stYxcs.detaildescri, 0x00, sizeof(stYxcs.detaildescri));
            memset(stYxcs.detailvalue, 0x00, sizeof(stYxcs.detailvalue));
        
            /* 6.明细序号 */
            memset(sBuf, 0x00, sizeof(sBuf));
            memset(sParaNode, 0x00, sizeof(sParaNode));
            snprintf(sParaNode, sizeof(sParaNode), "%s/DetailNo", sDetailList);
            COMP_SOFTGETXML(sParaNode, sBuf)
            pstrcopy(stYxcs.detailno, sBuf, sizeof(stYxcs.detailno));
            trim(stYxcs.detailno);
            /* 7.明细序号描述 */
            memset(sBuf, 0x00, sizeof(sBuf));
            memset(sParaNode, 0x00, sizeof(sParaNode));
            snprintf(sParaNode, sizeof(sParaNode), "%s/Description", sDetailList);
            COMP_SOFTGETXML(sParaNode, sBuf)
            pstrcopy(stYxcs.detaildescri, sBuf, sizeof(stYxcs.detaildescri));
            trim(stYxcs.detaildescri);
            /* 8.明细序号取值 */
            memset(sBuf, 0x00, sizeof(sBuf));
            memset(sParaNode, 0x00, sizeof(sParaNode));
            snprintf(sParaNode, sizeof(sParaNode), "%s/ParamValue", sDetailList);
            COMP_SOFTGETXML(sParaNode, sBuf)
            pstrcopy(stYxcs.detailvalue, sBuf, sizeof(stYxcs.detailvalue));
            trim(stYxcs.detailvalue);                        
						
						/* add dci 20141103 */
   					memset( sSql1, 0x00, sizeof( sSql1 ) );
    				iRet = DBInsert("tips_yxcs", SD_TIPS_YXCS, NUMELE(SD_TIPS_YXCS), &stYxcs, sErrmsg);
    				if( iRet < 0 )
    				{
    					LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      				fpub_SetMsg(lXmlhandle, 24484, "登记运行参数表数据失败");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记运行参数表数据失败,参数类型编号[%s],明细序号[%s]", 
                    stYxcs.paramtypeno, stYxcs.detailno),fpub_GetCompname(lXmlhandle))  
            }
   					/* end add dci 20141103 */

						/* mod dci 20141103
            EXEC SQL INSERT INTO tips_yxcs  VALUES (:stYxcs);
            SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
            if ( SQLERR )
            {    	
                fpub_SetMsg(lXmlhandle, 24484, "登记运行参数表数据失败");
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记运行参数表数据失败,参数类型编号[%s],明细序号[%s]", 
                    stYxcs.paramtypeno, stYxcs.detailno),fpub_GetCompname(lXmlhandle))  
            }
            */
        }        
    }

    fpub_SetMsg(lXmlhandle, 0, "登记运行参数表数据成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("登记运行参数表数据成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC;     
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_Init9120
组件名称: 登记9120通用应答表
组件功能: 
  登记9120通用应答表
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作
自由格式报文	tips_9120

项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2009年10月23日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_Init9120(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_9120 st9120;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[2048];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_9120 st9120;
		/* end add dci 20141103 */
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("登记9120通用应答表数据开始处理..."),fpub_GetCompname(lXmlhandle))

    memset(&st9120, 0x00, sizeof(st9120));
    COMP_PARACOUNTCHK(2);
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"帐务日期")
    pstrcopy(st9120.zwrq, sBuf, sizeof(st9120.zwrq));
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"综合前置流水号")
    st9120.zhqzlsh=atoi(sBuf);
    
    /* 3.工作日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/WorkDate", sBuf)
    pstrcopy(st9120.workdate, sBuf, sizeof(st9120.workdate));    
    
    /* 4.应答时间 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/ydsj", sBuf)
    pstrcopy(st9120.systime, sBuf, sizeof(st9120.systime));       

    /* 5.原报文标识号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/OriMsgID", sBuf)
    pstrcopy(st9120.orimsgid, sBuf, sizeof(st9120.orimsgid));    
    
    /* 6.原报文编号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/OriMsgNo", sBuf)
    pstrcopy(st9120.orimsgno, sBuf, sizeof(st9120.orimsgno)); 

    /* 7.处理结果 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/Result", sBuf)
    pstrcopy(st9120.result, sBuf, sizeof(st9120.result));       

    /* 8.附言 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/AddWord", sBuf)
    pstrcopy(st9120.addword, sBuf, sizeof(st9120.addword));    
    
    /* 9.详细信息 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/Information", sBuf)
    pstrcopy(st9120.information, sBuf, sizeof(st9120.information));

		/* add dci 20141103 */
   	memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_9120", SD_TIPS_9120, NUMELE(SD_TIPS_9120), &st9120, sErrmsg);
   	if( iRet < 0 )
    {
    		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      	fpub_SetMsg(lXmlhandle, 24484, "登记9120通用应答表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记9120通用应答表失败"),fpub_GetCompname(lXmlhandle))  
    }
   	/* end add dci 20141103 */

		/* mod dci 20141103
    EXEC SQL INSERT INTO tips_9120  VALUES (:st9120);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24484, "登记9120通用应答表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg("登记9120通用应答表失败"),fpub_GetCompname(lXmlhandle))  
    } 
    */      
            
    fpub_SetMsg(lXmlhandle, 0, "登记9120通用应答表成功");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG(LM_STD,Fmtmsg("登记9120通用应答表成功"), fpub_GetCompname(lXmlhandle));
    return COMPRET_SUCC; 
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_InsHxmx
组件名称: 登记核心对账明细表
组件功能: 
  登记核心对账明细表
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作
报文登记表	tips_xibhxmx

项 目 组: TIPS专用前置产品组
程 序 员: wangw
发布日期: 2012年08月02日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_XIB_InsHxmx(HXMLTREE lXmlhandle)
{
    int iParas;
    /* mod dci 20141103
		EXEC SQL BEGIN DECLARE SECTION; 
         SDB_TIPS_XIBHXMX  stHxmx;
    EXEC SQL END   DECLARE SECTION;
		*/
    
    char sBuf[256];
    char sBwdjbz[1+1];
    char sNode[64];
    
    /* add DCI 20141103 */
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/
		char sErrmsg[256]; /*DCI 执行sql语句返回错误信息 add 20141103*/ 
		int iRet=0;
		SDB_TIPS_XIBHXMX  stHxmx;
		/* end add dci 20141103 */

    fpub_InitSoComp(lXmlhandle);
    
    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG")
    #endif 

    memset(&stHxmx, 0x00, sizeof(stHxmx));
    /* 账务日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/tips/dzrq", sBuf)
    pstrcopy(stHxmx.zwrq, sBuf, sizeof(stHxmx.zwrq));           

    /* 客户名称 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/khmc", sBuf)
    pstrcopy(stHxmx.khmc, sBuf, sizeof(stHxmx.khmc));           

    /* 客户编号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/khbh", sBuf)
    pstrcopy(stHxmx.khbh, sBuf, sizeof(stHxmx.khbh));           

    /* 扣税账号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/kszh", sBuf)
    pstrcopy(stHxmx.khzh, sBuf, sizeof(stHxmx.khzh));           

    /* 交易金额 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/jyje", sBuf)
    stHxmx.jyje = atof(sBuf);           

    /* 税票日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/sprq", sBuf)
    pstrcopy(stHxmx.sprq, sBuf, sizeof(stHxmx.sprq));           

    /* 核心记账日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/hxjzrq", sBuf)
    pstrcopy(stHxmx.hxrq, sBuf, sizeof(stHxmx.hxrq));           

    /* 核心冲销日期 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/hxcxrq", sBuf)
    pstrcopy(stHxmx.hxcxrq, sBuf, sizeof(stHxmx.hxcxrq));           

    /* 摘要 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/zy", sBuf)
    pstrcopy(stHxmx.zy, sBuf, sizeof(stHxmx.zy));           

    /* 状态 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/zt", sBuf)
    pstrcopy(stHxmx.status, sBuf, sizeof(stHxmx.status));           

    /* 备注 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/bz", sBuf)
    pstrcopy(stHxmx.bz, sBuf, sizeof(stHxmx.bz));           

    /* 状态码 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/ztm", sBuf)
    pstrcopy(stHxmx.ztm, sBuf, sizeof(stHxmx.ztm));           

    /* 核心流水号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/hxlsh", sBuf)
    pstrcopy(stHxmx.dzlsh, sBuf, sizeof(stHxmx.dzlsh));           
    /* 机构代号 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML("/switch/90038/record/mx/jgdh", sBuf)
    pstrcopy(stHxmx.jgdh, sBuf, sizeof(stHxmx.jgdh));           

    /* 对账标志 */
    pstrcopy(stHxmx.dzbz, "0", sizeof(stHxmx.dzbz));           

		/* add dci 20141103 */
   	memset( sSql1, 0x00, sizeof( sSql1 ) );
    iRet = DBInsert("tips_xibhxmx", SD_TIPS_XIBHXMX, NUMELE(SD_TIPS_XIBHXMX), &stHxmx, sErrmsg);
    if( iRet < 0 )
    {
    		LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
    	
      	fpub_SetMsg(lXmlhandle, 24103, "登记核心明细表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("登记核心明细表失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	
    /* end add dci 20141103 */

		/* mod dci 20141103
    EXEC SQL INSERT INTO tips_xibhxmx VALUES (:stHxmx);
    SQLERRLOG(LM_STD,Fmtmsg(MSG_SQL_INSERT,sqlca.sqlcode), fpub_GetCompname(lXmlhandle))
    if ( SQLERR )
    {    	
        fpub_SetMsg(lXmlhandle, 24103, "登记核心明细表失败");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD, Fmtmsg("登记核心明细表失败"), fpub_GetCompname(lXmlhandle))
        return COMPRET_FAIL;         
    }	
    */
        
    fpub_SetMsg(lXmlhandle, 0, "登记核心明细表失败");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC; 
}

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_DelStr
组件名称: 去掉字符串头尾字符
组件功能: 
  去掉字符串头尾字符
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名         操作

项 目 组: TIPS专用前置产品组
程 序 员: wangw
发布日期: 2012年08月1日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_DelStr(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[1024*100],sBuf1[1024*100];
    char sNode[256];

    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHK(2)
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"处理字符串");
    memset(sNode, 0x00, sizeof(sNode));
    COMP_GETPARSEPARAS(2,sNode,"存放节点");
    
    trim(sBuf);
      
    memset(sBuf1, 0x00, sizeof(sBuf1));
    memcpy(sBuf1,sBuf+1,strlen(sBuf)-2);
    
    COMP_SOFTSETXML(sNode, sBuf1)
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;  
}    

/*************************************************************************
 * 函数名称: set_xml
 * 函数功能: 设置xml结点的值, 从s总截取len长度作为xml结点的值(len=0, 取到'\0')
 * 输入参数: lXmlhandle - xml树句柄
 *           xmlnode - xml结点名
 *           s - 字符串
 *           len - 长度
 *           type - 方式(0: ascii, 1: bin)
 * 输出参数: 无
 * 返回值: -99 内存不足
 *         -1  设置值失败
 *         0   成功
 * 发布日期: 2009-07-08
 * 修改日期: 2009-07-08
 * 程序员: renyh
 *
*************************************************************************/
int set_xml(HXMLTREE lXmlhandle, const char *xmlnode, const char *s, int len, int type)
{
    char *sval;
	int ret = 0;

    if (len == 0)
		len = strlen(s);
    sval = (char *)malloc(len+1);
	if (sval == NULL)
		return -99;
    memset(sval, 0, len+1);
    strncpy(sval, s, len);
	if (type == 0)
		ret = xml_SetElement(lXmlhandle, xmlnode, sval);
	else if (type == 1)
		ret = xml_SetBinElement(lXmlhandle, xmlnode, sval, len);
    free(sval);
    
    return ret;
}

int handle_express(HXMLTREE lXmlhandle, const char *sexp, int type)
{
	int ret = 0;
	char sStart[10], sLen[10];
	char *sXmlNode, *sValue;
	const char *s;
    char *sTmp;
	int flag = 0x00;
	int node_len, len = strlen(sexp);
	int iStart = 1, iLen = 0;
	int i;

	s = strchr(sexp, '=');
	if (s == NULL)
		return ret;
	node_len = (int)(s - sexp);

	sXmlNode = (char *)malloc(node_len+1);
	if (sXmlNode == NULL)
		return -99;
	sValue = (char *)malloc(len-node_len+1);
	if (sValue == NULL)
	{
		free(sXmlNode);
		return -99;
	}
	memset(sXmlNode, 0, node_len+1);
	memset(sValue, 0, len-node_len+1);
	memset(sStart, 0, sizeof(sStart));
	memset(sLen, 0, sizeof(sLen));
	i = 0;
	for (s = sexp; *s != '\0'; s++)
	{
		switch(flag)
		{
		case 0x00:
			if (*s == '=')
			{
				flag = 0x10;
				i = 0;
			}
			else
				*(sXmlNode+i++) = *s;
			break;
		case 0x10:
			if (*s == '#')
			{
				flag = 0x11;
				i = 0;
			}
			else
				*(sValue+i++) = *s;
			break;
		case 0x11:
			if (*s == ',')
			{
				flag = 0x12;
				i = 0;
			}
			else if (i < sizeof(sStart)-1)
				*(sStart+i++) = *s;
			break;
		case 0x12:
			if (i < sizeof(sLen)-1)
				*(sLen+i++) = *s;
			break;
		default:
			break;
		}
	}

	iStart = atoi(sStart);
	iLen = atoi(sLen);

	if (iStart == 0)
		iStart = 1;

	LOG(LM_STD, Fmtmsg("xml node: [%s]", sXmlNode), "");
	LOG(LM_STD, Fmtmsg("xml value: [%s]", sValue), "");
	LOG(LM_STD, Fmtmsg("start: [%d]", iStart), "");
	LOG(LM_STD, Fmtmsg("len: [%d]", iLen), "");

	ret = set_xml(lXmlhandle, sXmlNode, sValue+iStart-1, iLen, type);
	free(sXmlNode);
	free(sValue);
	return ret;
}

/**********************************************************************
动态组件函数定义
组件函数名称:DATA_MEnSetValue
组件名称: DATA_MEnSetValue, 增强型设置xml结点值
组件功能: 增强型设置xml结点值
组件参数:
序号 参数名称   资源类别     缺省值   是否可空  参数说明


组件结果状态:
  结果状态码         结果说明
项 目 组: 中间业务产品研发组
程 序 员: 中间业务产品发展部研发组 
发布日期: 2009年07月20日 
修改日期: 2009年07月20日
参数使用示例:
************************************************************************/
IRESULT DATA_MEnSetValue(HXMLTREE lXmlhandle)
{
    char sBuf[81920];
    int iFlag;           /* 0-ascii, 1-bin  */
    int iParaCount,i;

    int iRet=0; 
	int iStatus= COMPSTATUS_SUCC;
	int iResult = COMPRET_SUCC;


    fpub_InitSoComp(lXmlhandle);

#ifdef _DEBUG
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"");
#endif

    iParaCount = fpub_GetPARAcount(lXmlhandle);
 
    memset(sBuf,'\0',sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "赋值方式");
    iFlag = atoi(sBuf);
   
    for ( i = 1; i < iParaCount; i++ )
    { 
        memset(sBuf,'\0',sizeof(sBuf));
        COMP_GETPARSEPARAS(i+1, sBuf, "赋值解析式");
        trim(sBuf);
		LOG(LM_STD, Fmtmsg("表达式[%s]赋值", sBuf), "");
		iRet = handle_express(lXmlhandle, sBuf, iFlag);
		
		if (iRet == -99)
		{
			LOG(LM_STD, Fmtmsg("表达式[%s]赋值失败, 内存不足!", sBuf), "");
		}
		else if (iRet == -1)
		{
			LOG(LM_STD, Fmtmsg("表达式[%s]赋值失败", sBuf), "");
		}
		
    }

#ifdef _DEBUG
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"");
#endif

    fpub_SetCompStatus(lXmlhandle, iStatus);
    return iResult;
}


/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_SZQM
组件名称: 给TIPS通讯添加数字签名
组件功能: 
  给TIPS通讯添加数字签名
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败

主要操作库表:
  表名              操作


项 目 组: TIPS专用前置产品组
程 序 员: LIUY
发布日期: 2011年11月09日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_SZQM(HXMLTREE lXmlhandle)
{
	 	int iParas;
   	char sBuf[254];
   	/*char sReqbuf[TIPS_MAX_PKG]; 20150512 8M改为64000 */
   	char sReqbuf[LEN_COMM];
   	/* end 20150512 */
   	char sTxms[1+1];/* 通讯模式1,2,3 3-无应答 */
   	char stranscode[30],smode[10],sputmode[10],smsgid[100],slsh[30],sqm_name[50];
   	char squeue[50],sexpir_time[30],sfile[100],sRcombuf[20],sRespbuf[50];
   	FILE *fp1;
   	char *commbuf;
   	int iret=0,messlen=0,ilen=0,iRet=0,iLen=0;
   	caddr_t pUpfileHead;
   	struct stat struStat;
   	char recvcommbuf[4096000]; /*先定1M大小*/   
   	
   	LOG( LM_DEBUG, Fmtmsg( "组件[%s]开始执行", fpub_GetCompname( lXmlhandle ) ), "INFO" ); 
     	  
   	memset(sBuf, 0x00, sizeof(sBuf));
    memset(sReqbuf, 0x00, sizeof(sReqbuf));
    memset(sTxms, 0x00, sizeof(sTxms));  
    memset(smode, 0x00, sizeof(smode));
    memset(sputmode, 0x00, sizeof(sputmode));
    memset(smsgid, 0x00, sizeof(smsgid));
    memset(slsh, 0x00, sizeof(slsh));
    memset(sqm_name, 0x00, sizeof(sqm_name));
    memset(squeue, 0x00, sizeof(squeue));  
    memset(sfile, 0x00, sizeof(sfile));
    memset(sRcombuf, 0x00, sizeof(sRcombuf));
    memset(recvcommbuf, 0x00, sizeof(recvcommbuf));
    memset(sexpir_time, 0x00, sizeof(sexpir_time));
    memset(stranscode, 0x00, sizeof(stranscode));
   	       	
   	fpub_InitSoComp(lXmlhandle);
   	
   	/*获取组件参数  --S*/
   	COMP_PARACOUNTCHK(3)
   	
   	/*sReqbuf*/
   	memset(sBuf, 0x00, sizeof(sBuf));
   	memset(sReqbuf, 0x00, sizeof(sReqbuf));
   	COMP_GETPARSEPARAS(1, sBuf, "请求sReqbuf")
   	pstrcopy(sRcombuf, sBuf, sizeof(sRcombuf));
   	trim(sRcombuf);
   	
   	/*通讯模式*/
   	memset(sBuf, 0x00, sizeof(sBuf));
   	memset(sTxms, 0x00, sizeof(sTxms));
   	COMP_GETPARSEPARAS(2, sBuf, "通讯模式")
   	pstrcopy(sTxms, sBuf, sizeof(sTxms));
   	trim(sTxms);
   	
   	/*返回报文节点*/
   	memset(sBuf, 0x00, sizeof(sBuf));
   	memset(sRespbuf, 0x00, sizeof(sRespbuf));
   	COMP_GETPARSEPARAS(3, sBuf, "返回报文节点")
   	pstrcopy(sRespbuf, sBuf, sizeof(sRespbuf));
   	trim(sRespbuf);
   	
   	LOG(LM_STD,Fmtmsg("-[%s]-[%s]-[%s]-",sRcombuf,sTxms,sRespbuf),"INFO");
   	
	 	if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, sReqbuf, sizeof(sReqbuf))) == FAIL )
   	{
   	    fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
   	    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	    LOGRET(COMPRET_FAIL,LM_STD,"获取通讯区内容失败",fpub_GetCompname(lXmlhandle));
   	    return COMPSTATUS_FAIL;
   	}
   	
   	LOG(LM_STD,Fmtmsg("通讯区：请求sReqbuf[%s]\n 通讯模式[%s]",sReqbuf, sTxms), fpub_GetCompname(lXmlhandle))
   	
   	GetListbyDiv(sReqbuf,1,stranscode,  '|','\\');     /*第1个字段为交易代码*/
   	GetListbyDiv(sReqbuf,2,smode,       '|','\\');     /*第2个字段为模式 1 发送put 2 接收get*/
   	GetListbyDiv(sReqbuf,3,sputmode,    '|','\\');     /*第3个字段为put模式 get时不使用  1 以请求方式put 2 以响应方式put*/   
   	GetListbyDiv(sReqbuf,4,smsgid,      '|','\\');     /*第4个字段为消息ID msgid */ 
   	GetListbyDiv(sReqbuf,5,slsh,        '|','\\');     /*第5个字段为流水号*/
   	GetListbyDiv(sReqbuf,6,sqm_name,    '|','\\');     /*第6个字段为MQ管理器名*/
   	GetListbyDiv(sReqbuf,7,squeue,      '|','\\');     /*第7个字段为队列名*/
   	GetListbyDiv(sReqbuf,8,sexpir_time, '|','\\');     /*第8个字段为生存期-发送 超时-接收*/
   	iret=GetListbyDiv(sReqbuf,9,sfile,'|','\\');       /*第9个字段为数据包文件名*/
   	if (iret<0)
   	{
   	   LOG(LM_STD,Fmtmsg("数据格式非法,取报文数据失败,请检查"),"ERROR");
   	   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	   return COMPSTATUS_FAIL;
   	}
   	LOG(LM_STD,Fmtmsg("stranscode[%s],smode[%s],sputmode[%s],smsgid[%s],slsh[%s],sqm_name[%s],squeue[%s],sexpir_time[%s],sfile[%s]",
   	  stranscode,smode,sputmode,smsgid,slsh,sqm_name,squeue,sexpir_time,sfile), fpub_GetCompname(lXmlhandle))
   	trim(sfile);
   	
   	/*打开文件,读入数据到commbuf*/
   	fp1=fopen(sfile,"r");
   	if (fp1==NULL)
   	{
  		  LOG(LM_STD,Fmtmsg("打开pkg文件失败"),"ERROR");
   	   fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" 打开文件失败"));
   	   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	   return COMPSTATUS_FAIL;
   	}		
   	fstat(fileno(fp1), &struStat);
   	ilen = struStat.st_size;
   	if ((pUpfileHead = mmap(NULL, (size_t)ilen, PROT_READ, MAP_SHARED, fileno(fp1), (off_t)0)) == (caddr_t) - 1)
   	{
   	   munmap(fp1, (size_t)struStat.st_size);
   	   fclose(fp1);
   	   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	   return COMPSTATUS_FAIL;
   	}
   	commbuf = pUpfileHead;
   	   	
   	memset(recvcommbuf,0,sizeof(recvcommbuf));
   	pstrcopy(recvcommbuf,commbuf,sizeof(recvcommbuf));
   	LOG(LM_STD,Fmtmsg("  -->recvcommbuf[%s]",recvcommbuf),"INFO");
   	
   	/*生成ca码*/
   	iret = prv_genca(recvcommbuf,sizeof(recvcommbuf));
   	if (iret < 0)
   	{
   		  LOG(LM_STD,Fmtmsg("  -->生成ca失败!iret[%d]",iret),"ERROR");
   	   munmap(pUpfileHead, (size_t)struStat.st_size);
   	   fclose(fp1);
   		  fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   		  return COMPSTATUS_FAIL;
   	}
   	LOG(LM_STD,Fmtmsg("  -->recvcommbuf1[%s]",recvcommbuf),"INFO");
   	if(strcmp(sputmode,"2")==0)
   	{
   		  strcat(smsgid,recvcommbuf);
   		  memset(recvcommbuf,0,sizeof(recvcommbuf));
   		  strcpy(recvcommbuf,smsgid);
   	}
   	
   	messlen = strlen(recvcommbuf);  
   	LOG(LM_STD,Fmtmsg("  -->genca后Buf![%d]sendcommbuf[%s][%d]",iret,recvcommbuf,messlen),"INFO"); 
   	
   	/*正常情况也需释放 20150512增加 */
    munmap(pUpfileHead, (size_t)struStat.st_size);       
   	fclose(fp1); 
    
		if (( iRet = xml_RelSetBinElement(lXmlhandle,sRespbuf,recvcommbuf,strlen(recvcommbuf))) == FAIL)
		{
			fpub_SetMsg(lXmlhandle, 24109, "回写通讯区内容失败");
			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,"回写通讯区内容失败",fpub_GetCompname(lXmlhandle));
			return COMPSTATUS_FAIL;
		}
  	      
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;  

} 

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_UnSZQM
组件名称: TIPS通讯数字签名验证
组件功能: 
  TIPS通讯数字签名验证
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败

主要操作库表:
  表名              操作


项 目 组: TIPS专用前置产品组
程 序 员: LIUY
发布日期: 2011年11月09日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_UnSZQM(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[254];
    char sRcombuf[50],sTxms[10],sRespbuf[50];
    /*char sReqbuf[TIPS_MAX_PKG]; 20150512 改为动态分配 */
    int iSize = 0;
    /*char *sReqbuf = NULL;*/
    char sReqbuf[4096000];
    /* end 20150512 */
    
    char *pstr;
    char stranscode[30],slsh[30],sfile2[100],gsCommbuf[254];
    int irecvlen,iRet,iLen,iret;
    FILE *fp1;
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRcombuf, 0x00, sizeof(sRcombuf));
    memset(sTxms, 0x00, sizeof(sTxms));
    memset(sRespbuf, 0x00, sizeof(sRespbuf));
    /*memset(sReqbuf, 0x00, sizeof(sReqbuf)); 20150512 */
    memset(stranscode, 0x00, sizeof(stranscode));
    memset(slsh, 0x00, sizeof(slsh));
    memset(sfile2, 0x00, sizeof(sfile2));
    memset(gsCommbuf, 0x00, sizeof(gsCommbuf));

    fpub_InitSoComp(lXmlhandle);

    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
    #endif 
  
    /*获取组件参数  --S*/
    COMP_PARACOUNTCHK(3)

    /*sReqbuf*/
    memset(sBuf, 0x00, sizeof(sBuf));
    /*memset(sReqbuf, 0x00, sizeof(sReqbuf)); 20150512 */
    COMP_GETPARSEPARAS(1, sBuf, "请求sReqbuf")
    pstrcopy(sRcombuf, sBuf, sizeof(sRcombuf));
    trim(sRcombuf);

    /*通讯模式*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sTxms, 0x00, sizeof(sTxms));
    COMP_GETPARSEPARAS(2, sBuf, "通讯模式")
    pstrcopy(sTxms, sBuf, sizeof(sTxms));
    trim(sTxms);
    
    /*返回报文节点*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRespbuf, 0x00, sizeof(sRespbuf));
    COMP_GETPARSEPARAS(3, sBuf, "返回报文节点")
    pstrcopy(sRespbuf, sBuf, sizeof(sRespbuf));
    trim(sRespbuf);
    
    if(strcmp(sTxms,"02")==0)
    {
    	  memset(gsCommbuf, 0x00, sizeof(gsCommbuf));
    	  sprintf(gsCommbuf,"%s|%s|02|%s|%s|%s|","","","","接收MQ失败","");
    		if (( iRet = xml_RelSetBinElement(lXmlhandle,sRespbuf,gsCommbuf,strlen(gsCommbuf))) == FAIL)
	      {
		      fpub_SetMsg(lXmlhandle, 24109, "回写通讯区内容失败");
		      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		      LOGRET(COMPRET_FAIL,LM_STD,"回写通讯区内容失败",fpub_GetCompname(lXmlhandle));
		      return COMPSTATUS_FAIL;
	      }
	       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
         return COMPRET_SUCC;
    }
    
    /* 20150512 改为动态分配 */
    /*
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, sReqbuf, sizeof(sReqbuf))) == FAIL )
    {
        fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"获取通讯区内容失败",fpub_GetCompname(lXmlhandle));
        return COMPSTATUS_FAIL;
    }
    */
    
    iSize = xml_GetBinElementLen(lXmlhandle, sRcombuf);
    if (iSize < 0)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"获取通讯报文长度失败",fpub_GetCompname(lXmlhandle));
	  }
	  iSize = iSize +1;
	  /*sReqbuf = malloc(iSize);*/
	  
	  if(NULL == sReqbuf)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("malloc失败[%s]",strerror(errno)),fpub_GetCompname(lXmlhandle));
	  }	
	  memset(sReqbuf, 0, iSize);
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, sReqbuf, iSize)) == FAIL )
    {
    	  free(sReqbuf);
        fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"获取通讯区内容失败",fpub_GetCompname(lXmlhandle));
        return COMPSTATUS_FAIL;
    }
    /* end 20150512 */    
    
    /* 20150815 test 
    /*打开文件,读入数据到commbuf
    char *commbuf;
   	
   	char recvcommbuf[4096000]; /*先定1M大小
    int ilen;
    caddr_t pUpfileHead;
   	struct stat struStat;
   	fp1=fopen("/home/gaps/file/tips/pkg/test","r");
   	if (fp1==NULL)
   	{
  		  LOG(LM_STD,Fmtmsg("打开pkg文件失败"),"ERROR");
   	   fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(" 打开文件失败"));
   	   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	   return COMPSTATUS_FAIL;
   	}		
   	
   	fstat(fileno(fp1), &struStat);
   	ilen = struStat.st_size;
   	
   	if ((pUpfileHead = mmap(NULL, (size_t)ilen, PROT_READ, MAP_SHARED, fileno(fp1), (off_t)0)) == (caddr_t) - 1)
   	{
   	   munmap(fp1, (size_t)struStat.st_size);
   	   fclose(fp1);
   	   fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
   	   return COMPSTATUS_FAIL;
   	}
   	commbuf = pUpfileHead;
   	   	
   	memset(sReqbuf,0,sizeof(sReqbuf));
   	pstrcopy(sReqbuf,commbuf,sizeof(sReqbuf));
   	LOG(LM_STD,Fmtmsg("  -->sReqbuf[%s]",sReqbuf),"INFO");
   	
   	munmap(pUpfileHead, (size_t)struStat.st_size);       
   	fclose(fp1);    
     end test */
    
    LOG(LM_STD,Fmtmsg("通讯区：请求sReqbuf[%s]\n 通讯模式相应码[%s]",sReqbuf, sTxms),"INFO")
    
   /*校验ca */
   iret = prv_checkca(sReqbuf,sizeof(sReqbuf));
   if (iret < 0)
   {
     LOG(LM_STD,Fmtmsg("  -->校验ca失败!iret[%d]",iret),"ERROR");
     fpub_SetMsg(lXmlhandle, 24105, "  -->校验ca失败!");
     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     return COMPSTATUS_FAIL;
   }
   LOG(LM_STD,Fmtmsg("  -->校验ca成功!iret[%d]",iret),"INFO");
   
   pstr = strstr(sReqbuf,"<!--");
   if (pstr != NULL )
   {
   	   *pstr = 0; 
   }
   LOG(LM_STD,Fmtmsg("  -->校验ca成功后-----sReqbuf[%s]",sReqbuf),"INFO");
   memset(stranscode, 0x00, sizeof(stranscode));
   COMP_SOFTGETXML("/tipso/req/jydm", stranscode)
   memset(slsh, 0x00, sizeof(slsh));
   COMP_SOFTGETXML("/tipso/req/xh", slsh)
    
	 /*接收成功,写回应答*/
	 memset(sfile2, 0x00, sizeof(sfile2));
	 snprintf(sfile2, sizeof(sfile2),"%s/file/tips/pkg/%s_%s_resp",getenv("HOME"),stranscode,slsh);
	 fp1=fopen(sfile2,"w");
	 if (fp1 == NULL )
	 {
	     fpub_SetMsg(lXmlhandle, 24105, "  -->gen resppkgfile fail!");
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       return COMPSTATUS_FAIL;
	 }		
	 irecvlen = strlen(sReqbuf);
	 fwrite(sReqbuf,irecvlen,1,fp1);
	 fclose(fp1);
	 memset(gsCommbuf, 0x00, sizeof(gsCommbuf));
   sprintf(gsCommbuf,"%s|%s|00|%s|%s|%s|",stranscode,slsh,sfile2,"校验数字签名成功","");
    
	if (( iRet = xml_RelSetBinElement(lXmlhandle,sRespbuf,gsCommbuf,strlen(gsCommbuf))) == FAIL)
	{
		fpub_SetMsg(lXmlhandle, 24109, "回写通讯区内容失败");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"回写通讯区内容失败",fpub_GetCompname(lXmlhandle));
		return COMPSTATUS_FAIL;
	}
        
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;   

} 


/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_UNSZQM_TIPSJR
组件名称: TIPS接入数字签名验证
组件功能: 
  TIPS接入数字签名验证
组件参数: 
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败

主要操作库表:
  表名              操作


项 目 组: TIPS专用前置产品组
程 序 员: LIUY
发布日期: 2011年11月09日
修改日期: 
参数使用示例: 
************************************************************************/
IRESULT SYW_TIPS_UNSZQM_TIPSJR(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[254];
    char sRcombuf[50],sRespbuf[50];
    /*char sReqbuf[TIPS_MAX_PKG]; 20150512 改为动态分配 */
    int iSize = 0;
    char *pReqbuf = NULL;
    /* end 20150512 */
    char *pstr;
    char stranscode[30],slsh[30],sfile2[100],gsCommbuf[254];
    int irecvlen,iRet,iLen,iret;
    FILE *fp1;
    char *pmsgidstr,*pbuf;
    char msgidstr[100],szwrq[10],szhqzlsh[10];
    
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRcombuf, 0x00, sizeof(sRcombuf));
    memset(sRespbuf, 0x00, sizeof(sRespbuf)); 
    /*memset(sReqbuf, 0x00, sizeof(sReqbuf));20150512*/
    memset(stranscode, 0x00, sizeof(stranscode));
    memset(slsh, 0x00, sizeof(slsh));
    memset(sfile2, 0x00, sizeof(sfile2));
    memset(msgidstr, 0x00, sizeof(msgidstr));
    memset(szwrq, 0x00, sizeof(szwrq));
    memset(szhqzlsh, 0x00, sizeof(szhqzlsh));

    fpub_InitSoComp(lXmlhandle);

    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
    #endif 
  
    /*获取组件参数  --S*/
    COMP_PARACOUNTCHK(2)

    /*sReqbuf*/
    memset(sBuf, 0x00, sizeof(sBuf));
    /*memset(sReqbuf, 0x00, sizeof(sReqbuf)); 20150512 */
    COMP_GETPARSEPARAS(1, sBuf, "请求sReqbuf")
    pstrcopy(sRcombuf, sBuf, sizeof(sRcombuf));
    trim(sRcombuf);

    /*返回报文节点*/
    memset(sBuf, 0x00, sizeof(sBuf));
    memset(sRespbuf, 0x00, sizeof(sRespbuf));
    COMP_GETPARSEPARAS(2, sBuf, "返回报文节点")
    pstrcopy(sRespbuf, sBuf, sizeof(sRespbuf));
    trim(sRespbuf);
    
    /* 20150512 改为动态分配 */
    /*
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, sReqbuf, sizeof(sReqbuf))) == FAIL )
    {
        fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"获取通讯区内容失败",fpub_GetCompname(lXmlhandle));
        return COMPSTATUS_FAIL;
    }
    */
    
    iSize = xml_GetBinElementLen(lXmlhandle, sRcombuf);
    if (iSize < 0)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"获取通讯报文长度失败",fpub_GetCompname(lXmlhandle));
	  }
	  iSize = iSize +1;
	  pReqbuf = malloc(iSize);
	  if(NULL == pReqbuf)
	  {
	  	  fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("malloc失败[%s]",strerror(errno)),fpub_GetCompname(lXmlhandle));
	  }	
	  memset(pReqbuf, 0, iSize);
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, pReqbuf, iSize)) == FAIL )
    {
    	  free(pReqbuf); 
        fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"获取通讯区内容失败",fpub_GetCompname(lXmlhandle));
        return COMPSTATUS_FAIL;
    }
    /* end 20150512 */

    pbuf=pReqbuf;
    memset(msgidstr, 0x00, sizeof(msgidstr));
    pmsgidstr = strstr(pbuf,"<?xml");
    if (pmsgidstr == NULL )
    {
   	  fpub_SetMsg(lXmlhandle, 24105, "  -->报文格式有问题!");
      fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
      return COMPSTATUS_FAIL;
    }
    else
    {
    	LOG(LM_STD,Fmtmsg("  -->pbuf[%s]",pbuf),"ERROR");
    	strncpy(msgidstr,pbuf,pmsgidstr-pbuf);
    	msgidstr[pmsgidstr-pbuf]='\0';
    }
   
   LOG(LM_STD,Fmtmsg("  -->msgidstr[%s],pmsgidstr-pbuf[%d]",msgidstr,pmsgidstr-pbuf),"ERROR");
   
   LOG(LM_STD,Fmtmsg("  -->pmsgidstr[%s]",pmsgidstr),"ERROR");
    
   /*校验ca*/
   iret = prv_checkca(pmsgidstr,sizeof(pmsgidstr));
   if (iret < 0)
   {
   	 LOG(LM_STD,Fmtmsg("  -->校验ca失败!iret[%d]",iret),"ERROR");
     fpub_SetMsg(lXmlhandle, 24105, "  -->校验ca失败!");
     fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
     return COMPSTATUS_FAIL;
   }
   LOG(LM_STD,Fmtmsg("  -->校验ca成功!iret[%d]",iret),"INFO");
   /*去掉注释*/
   pstr = strstr(pmsgidstr,"<!--");
   if (pstr != NULL )
   {
   	   *pstr = 0; 
   }
   LOG(LM_STD,Fmtmsg("  -->校验ca成功后-----pmsgidstr[%s]",pmsgidstr),"ERROR");
    
   COMP_HARDGETXML(XMLNM_ZWRQ,szwrq);
   COMP_HARDGETXML(XMLNM_ZHQZLSH,szhqzlsh);
	 /*接收成功,写回应答*/
	 memset(sfile2, 0x00, sizeof(sfile2));
	 snprintf(sfile2, sizeof(sfile2),"%s/tmp/tipsjr_%s_%s",getenv("HOME"),szwrq,szhqzlsh);
	 fp1=fopen(sfile2,"w");
	 if (fp1 == NULL )
	 {
	     fpub_SetMsg(lXmlhandle, 24105, "  -->gen resppkgfile fail!");
       fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
       return COMPSTATUS_FAIL;
	 }		
	 irecvlen = strlen(pmsgidstr);
	 fwrite(pmsgidstr,irecvlen,1,fp1);
	 fclose(fp1);
   sprintf(gsCommbuf,"%s|%s",msgidstr,sfile2);
    
	if (( iRet = xml_RelSetBinElement(lXmlhandle,sRespbuf,gsCommbuf,strlen(gsCommbuf))) == FAIL)
	{
		fpub_SetMsg(lXmlhandle, 24109, "回写通讯区内容失败");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		LOGRET(COMPRET_FAIL,LM_STD,"回写通讯区内容失败",fpub_GetCompname(lXmlhandle));
		return COMPSTATUS_FAIL;
	}
        
	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;   

}

              

/************************************************************************
动态组件函数定义
组件函数名称: SYW_TIPS_PREHXCOMM
组件名称: 核心通讯报文预处理
组件功能:
  与TIPS转发器通讯
组件参数:
序号 参数名称     资源类别       缺省值   是否可空  参数说明

组件结果状态:
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 其它失败　　

主要操作库表:
  表名              操作


项 目 组: TIPS专用前置产品组
程 序 员: TUQL
发布日期: 2015年07月13日
修改日期:
参数使用示例:
************************************************************************/
IRESULT SYW_TIPS_PREHXCOMM(HXMLTREE lXmlhandle)
{
		int iParas;
		char sJydm[9];
		char sBuf[254];
		char sRcombuf[50];
		char sReqbuf[LEN_COMM];
		char sReqbuf1[LEN_COMM];
		int iRet,iLen;
		
		fpub_InitSoComp(lXmlhandle);

    #ifdef DEBUG
        LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"")
    #endif

    /*获取组件参数  --S*/
    COMP_PARACOUNTCHK(2)

		/* jydm */
		memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "jydm")
    memcpy(sJydm, sBuf, sizeof(sJydm));
    
    /* commbuf */
		memset(sBuf, 0x00, sizeof(sBuf));
		memset(sRcombuf, 0x00, sizeof(sRcombuf));
    COMP_GETPARSEPARAS(2, sBuf, "commbuf")
    memcpy(sRcombuf, sBuf, sizeof(sRcombuf));
    trim(sRcombuf);
    
    if ( (iLen= xml_RelGetBinElement ( lXmlhandle, sRcombuf, sReqbuf, sizeof(sReqbuf))) == FAIL )
    {
        fpub_SetMsg(lXmlhandle, 24105, "获取通讯区内容失败");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        LOGRET(COMPRET_FAIL,LM_STD,"获取通讯区内容失败",fpub_GetCompname(lXmlhandle));
        return COMPSTATUS_FAIL;
    } 

		LOG(LM_STD,Fmtmsg("预处理前：jydm[%s] commbuf[%s]",sJydm,sReqbuf), fpub_GetCompname(lXmlhandle))
		
		memset(sReqbuf1, 0x00, sizeof(sReqbuf1));
		sprintf(sReqbuf1,"%8.8s%s",sJydm,sReqbuf);
		
		LOG(LM_STD,Fmtmsg("预处理后：jydm[%s] commbuf[%s]",sJydm,sReqbuf1), fpub_GetCompname(lXmlhandle))
		
		if (( iRet = xml_RelSetBinElement(lXmlhandle, sRcombuf, sReqbuf1, strlen(sReqbuf1))) == FAIL)
		{
			fpub_SetMsg(lXmlhandle, 24109, "回写通讯区内容失败");
			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,"回写通讯区内容失败",fpub_GetCompname(lXmlhandle));
			return COMPSTATUS_FAIL;
		}
        
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;   

}
