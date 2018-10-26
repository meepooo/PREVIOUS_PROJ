/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V1.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:
文 件 名:SYW_TIPS_PQUERY.ec
文件描述:综合前置分页查询组件集合
项 目 组:综合前置产品组
程 序 员:leejn
发布时间:20141220
修    订:
修改时间:
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <dlfcn.h>
#include <string.h>
#include "gaps_head.h"

#include "../eh/tips_wtgxdj.h"/* 委托关系登记 */ 
#include "../eh/tips_pzsj.h"/* 凭证数据 */ 
#include "../eh/tips_dzbpdj.h"/* 对账不平登记 */ 
#define DEBUG



/**********************************************************************
组件函数: SYW_TIPS_QrySFXY
组件名称: 支持分页查询功能,必须遵循接口设计
组件参数：
输入参数：
输出参数：
处理说明: 支持外围分页查询功能
          参数配置：
                    外围上翻时必须送上次应答的上翻ID.
                    外围下翻时必须送上次应答的下翻ID.          
*************************************************************************/
IRESULT SYW_TIPS_PQrySFXY(HXMLTREE lXmlhandle)
{
    /* 组件参数1-10 */    
    char querysql[1024+1];
    char countsql[1024+1];
    char querydirect[1+1];
    int querynum=0;
    int queryoffset=0;
    char countNode[128+1];
    char pageNode[128+1];
    char firstNode[128+1];
    char lastNode[128+1];
    char resultNode[512]; 
    
    int  i,iParas;
    char tmpstr[512+1];
    int  iRet=-1;    
    int  ipagefirst=0, ipagelast=0;
    int  iZbs=0;
    int  iCount=0;
    char sCount[128];
    char sXmlnode[128];
    char sErrmsg[256];       
    
    char sBuf[256];
    CURSOR cur;
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/   
    
    char sProtocolno[60+1]; 
    SDB_TIPS_WTGXDJ stWtgxdj;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /*组件参数检查*/
    COMP_PARACOUNTCHKMIN(10)
    
    memset(querysql, 0, sizeof(querysql));
    COMP_GETPARSEPARAS(1,querysql,"查询语句")
    trim(querysql);
    
    memset(countsql, 0, sizeof(countsql));
    COMP_GETPARSEPARAS(2,countsql,"汇总语句")
    trim(countsql);
    
    memset(tmpstr, 0, sizeof(tmpstr));
    memset(querydirect, 0, sizeof(querydirect));
    COMP_GETPARSEPARAS(3,tmpstr,"查询方向: 0首次:1上翻:2下翻") 
    trim(tmpstr);
    strncpy(querydirect, tmpstr, sizeof(querydirect)-1);
    
    memset(tmpstr, 0, sizeof(tmpstr));    
    COMP_GETPARSEPARAS(4,tmpstr,"最大记录数")
    trim(tmpstr);
    querynum= atoi(  tmpstr );
        
    memset(tmpstr, 0, sizeof(tmpstr));
    COMP_GETPARSEPARAS(5,tmpstr,"请求偏移量")
    trim(tmpstr);
    queryoffset = atoi(  tmpstr );
    
    memset(countNode, 0, sizeof(countNode));
    COMP_GETPARSEPARAS(6,countNode,"总记录数")
    trim(countNode);
    
    memset(pageNode, 0, sizeof(pageNode));
    COMP_GETPARSEPARAS(7,pageNode,"本页记录数")
    trim(pageNode);
    
    memset(firstNode, 0, sizeof(firstNode));
    COMP_GETPARSEPARAS(8,firstNode,"首记录ID节点")
    trim(firstNode);
    
    memset(lastNode, 0, sizeof(lastNode));
    COMP_GETPARSEPARAS(9,lastNode,"尾记录ID节点")
    trim(lastNode);

    /*返回节点*/
    memset(resultNode, 0, sizeof(resultNode));
    COMP_GETPARSEPARAS(10,resultNode,"输出节点名称")
    trim(resultNode);
    
    LOG(LM_DEBUG,Fmtmsg("组件输入参数"),"INFO")
		LOG(LM_DEBUG,Fmtmsg("querysql[%s]",querysql ),"INFO")
		LOG(LM_DEBUG,Fmtmsg("countsql[%s]",countsql ),"INFO")
		LOG(LM_DEBUG,Fmtmsg("querydirect[%s]querynum[%d]queryoffset[%d]",querydirect, querynum, queryoffset ),"INFO")
		LOG(LM_DEBUG,Fmtmsg("resultNode[%s]",resultNode ),"INFO")
		
    if ((cur = DCIDeclareCursor(querysql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
       
    iRet = DCIFetch2(cur, DCI_FETCH_ABSOLUTE, queryoffset );   
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    iCount = 0;
    while( iRet > 0 )
    {
    		if( iCount >= querynum )
            break;
        iCount ++;        
        
        memset( &stWtgxdj, 0x00, sizeof( stWtgxdj ) );        
        memset( &sProtocolno,0x00,sizeof( sProtocolno));
        
        i = 0;
        sprintf( sProtocolno, "%s", DCIFieldAsString( cur, 0 ) ); 
        trim(sProtocolno);
               
				sprintf( stWtgxdj.protocolno      , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.taxorgcode      , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.paybkcode       , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.payacct         , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.bankprotocolno  , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.taxpaycode      , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.payopbkcode     , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.taxpayname      , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.handorgname     , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.khh             , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.wtgxzt          , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.gxdjrq          , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.djlsh           , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.djdqdh          , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.djjgdh          , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.djjygy          , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.djzddh          , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.xgrq            , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.xglsh           , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.xgdqdh          , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.xgjgdh          , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.xgjygy          , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.xgzddh          , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.kzbz            , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.yzbz            , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.byzd            , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stWtgxdj.opbankno				, "%s", DCIFieldAsString( cur, i++ ) );

        /*        
        memset( sSql1, 0x00, sizeof( sSql1 ) );
    		snprintf( sSql1, sizeof(sSql1), "select * from tips_wtgxdj where protocolno='%s'",sProtocolno);     	
    		LOG(LM_DEBUG,Fmtmsg("sSql1[%s]...",sSql1),"INFO")    
    		iRet = prv_SelMulToStruct( &sSql1, SD_TIPS_WTGXDJ, NUMELE(SD_TIPS_WTGXDJ), &stWtgxdj);
    		LOG(LM_DEBUG,Fmtmsg("iRet[%d]...",iRet),"INFO")   
    		if ( iRet < 0)
    		{
        	LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")        
               
        	fpub_SetMsg(lXmlhandle, 24310, "查询委托关系表失败");
         	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
         	LOG(LM_STD, Fmtmsg("查询委托关系表失败"), fpub_GetCompname(lXmlhandle))	
         	return COMPRET_FAIL ;          
    		}
        */
        
        /*报文返回*/  
        /* 1 */      
        memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/protocolno", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.protocolno     );   
				
				/* 2 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/taxorgcode", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.taxorgcode     );
				
				/* 3 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/paybkcode", resultNode,iCount );				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.paybkcode      );
				
				/* 4 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/payacct", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.payacct        );
				
				/* 5 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/bankprotocolno", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.bankprotocolno );
				
				/* 6 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/taxpaycode", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.taxpaycode     );
				
				/* 7 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/payopbkcode", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.payopbkcode    );
				
				/* 8 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/taxpayname", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.taxpayname     );
				
				/* 9 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/handorgname", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.handorgname    );
				
				/* 10 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/khh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.khh            );
				
				/* 11 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/wtgxzt", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.wtgxzt         );
				
				/* 12 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/gxdjrq", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.gxdjrq         );
				
				/* 13 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/djlsh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.djlsh          );
				
				/* 14 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/djdqdh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.djdqdh         );
				
				/* 15 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/djjgdh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.djjgdh         );
				
				/* 16 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/djjygy", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.djjygy         );
				
				/* 17 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/djzddh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.djzddh         );
				
				/* 18 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/xgrq", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.xgrq           );
				
				/* 19 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/xglsh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.xglsh          );
				
				/* 20 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/xgdqdh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.xgdqdh         );
				
				/* 21 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/xgjgdh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.xgjgdh         );
				
				/* 22 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/xgjygy", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.xgjygy         );
				
				/* 23 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/xgzddh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.xgzddh         );
				
				/* 24 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/kzbz", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.kzbz           );
				
				/* 25 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/byzd", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.yzbz           );
				
				/* 26 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/byzd", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.byzd           );
				
				/* 27 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/opbankno", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stWtgxdj.opbankno       );        

        if (  querydirect[0] == '1' )        /* 1：向上翻 */
            iRet = DCIFetch2(cur, DCI_FETCH_PRIOR, 0 );
        else 
            iRet = DCIFetch2(cur, DCI_FETCH_NEXT,  0 );
        
    }
		LOG(LM_STD,Fmtmsg("iCount[%d]",iCount ),"INFO")		
    
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    } 
            
    DCIFreeCursor(cur);

    if (  querydirect[0] == '1' )        /* 1：向上翻 */
    {
        ipagefirst = queryoffset ;
        ipagelast = queryoffset - iCount ;
    }
    else /* 默认向下翻页 */
    {
        ipagefirst = queryoffset ;
        ipagelast = queryoffset + iCount ;
    }

    /* 首记录ID */
    COMP_HARDSETXML(firstNode,itoa(ipagefirst));
    /* 尾记录ID */
    COMP_HARDSETXML(lastNode,itoa(ipagelast));
    /* 返回记录数 */
    COMP_HARDSETXML(pageNode,itoa( iCount ));
    
    /* 返回汇总记录数 */
    
    iCount = 0;
    /* 20150807测试发现DBSelectToVar复杂count sql语句存在数值不准且会有coredump情况 */ 
    /*iRet = DBSelectToVar(sErrmsg, &iCount, countsql);*/
           
    LOG(LM_STD,Fmtmsg("countsql[%s]",countsql ),"INFO")
    /* 20150807 修改 */ 
    iRet = DBSelectToMultiVarChar(sErrmsg, countsql, &sCount);    
    if(iRet < 0)
		{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
					
				LOG(LM_STD,Fmtmsg("查询总笔数错误"),"ERROR");
								
		}
		LOG(LM_STD,Fmtmsg("sCount[%s]",sCount ),"INFO")      
		iCount=atol(sCount);
		LOG(LM_DEBUG,Fmtmsg("iCount[%d]",iCount),"INFO");
    COMP_HARDSETXML(countNode,itoa( iCount ));
        
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC;
}


/**********************************************************************
组件函数: SYW_TIPS_PQryPZSJ
组件名称: 支持分页查询功能,必须遵循接口设计
组件参数：
输入参数：
输出参数：
处理说明: 支持外围分页查询功能
          参数配置：
                    外围上翻时必须送上次应答的上翻ID.
                    外围下翻时必须送上次应答的下翻ID.          
*************************************************************************/
IRESULT SYW_TIPS_PQryPZSJ(HXMLTREE lXmlhandle)
{
    /* 组件参数1-10 */    
    char querysql[1024+1];
    char countsql[512+1];
    char querydirect[1+1];
    int querynum=0;
    int queryoffset=0;
    char countNode[128+1];
    char pageNode[128+1];
    char firstNode[128+1];
    char lastNode[128+1];
    char resultNode[512]; 
    
    int  i,iParas;
    char tmpstr[512+1];
    int  iRet=-1;    
    int  ipagefirst=0, ipagelast=0;
    int  iCount=0;
    char sCount[128];
    char sXmlnode[128];
    char sErrmsg[256];       
    
    char sBuf[256];
    CURSOR cur;
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/   
    
    char sZwrq[8+1]; 
    int iZhqzlsh=0;
    SDB_TIPS_PZSJ stPzsj;

    fpub_InitSoComp(lXmlhandle);     
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /*组件参数检查*/
    COMP_PARACOUNTCHKMIN(10)
    
    memset(querysql, 0, sizeof(querysql));
    COMP_GETPARSEPARAS(1,querysql,"查询语句")
    trim(querysql);
    
    memset(countsql, 0, sizeof(countsql));
    COMP_GETPARSEPARAS(2,countsql,"汇总语句")
    trim(countsql);
    
    memset(tmpstr, 0, sizeof(tmpstr));
    memset(querydirect, 0, sizeof(querydirect));
    COMP_GETPARSEPARAS(3,tmpstr,"查询方向: 0首次:1上翻:2下翻") 
    trim(tmpstr);
    strncpy(querydirect, tmpstr, sizeof(querydirect)-1);
    
    memset(tmpstr, 0, sizeof(tmpstr));    
    COMP_GETPARSEPARAS(4,tmpstr,"最大记录数")
    trim(tmpstr);
    querynum= atoi(  tmpstr );    
    
    memset(tmpstr, 0, sizeof(tmpstr));
    COMP_GETPARSEPARAS(5,tmpstr,"请求偏移量")
    trim(tmpstr);
    queryoffset = atoi(  tmpstr );
    
    memset(countNode, 0, sizeof(countNode));
    COMP_GETPARSEPARAS(6,countNode,"总记录数")
    trim(countNode);
    
    memset(pageNode, 0, sizeof(pageNode));
    COMP_GETPARSEPARAS(7,pageNode,"本页记录数")
    trim(pageNode);
    
    memset(firstNode, 0, sizeof(firstNode));
    COMP_GETPARSEPARAS(8,firstNode,"首记录ID节点")
    trim(firstNode);
    
    memset(lastNode, 0, sizeof(lastNode));
    COMP_GETPARSEPARAS(9,lastNode,"尾记录ID节点")
    trim(lastNode);

    /*返回节点*/
    memset(resultNode, 0, sizeof(resultNode));
    COMP_GETPARSEPARAS(10,resultNode,"输出节点名称")
    trim(resultNode);
    
		LOG(LM_DEBUG,Fmtmsg("组件输入参数"),"INFO")
		LOG(LM_DEBUG,Fmtmsg("querysql[%s]",querysql ),"INFO")
		LOG(LM_DEBUG,Fmtmsg("countsql[%s]",countsql ),"INFO")
		LOG(LM_DEBUG,Fmtmsg("querydirect[%s]querynum[%d]queryoffset[%d]",querydirect, querynum, queryoffset ),"INFO")
		LOG(LM_DEBUG,Fmtmsg("resultNode[%s]",resultNode ),"INFO")
		
    if ((cur = DCIDeclareCursor(querysql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
         
    iRet = DCIFetch2(cur, DCI_FETCH_ABSOLUTE, queryoffset );
    iCount = 0;
    while( iRet > 0 )
    {
        /*LOG(LM_STD,Fmtmsg("iCount[%d]",iCount ),"INFO")		*/
        if( iCount >= querynum )
            break;
        iCount ++;
        
        memset( &stPzsj, 0x00, sizeof( stPzsj ) );        
        memset( &sZwrq,0x00,sizeof( sZwrq));
        iZhqzlsh=0;
        
        i = 0;
        sprintf( stPzsj.zwrq, "%s", DCIFieldAsString( cur, i++ ) ); 
        stPzsj.zhqzlsh=atoi(DCIFieldAsString( cur, i++ ) );         
        sprintf( stPzsj.jyrq        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.dqdh        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.jgdh        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.jygy        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.zddh        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.msgno       , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.entrustdate , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.taxorgcode  , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.packno      , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.trano       , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.payeebankno , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.payeename   , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.paybkcode   , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.payopbkcode , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.payacct     , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.handorgname , "%s", DCIFieldAsString( cur, i++ ) );
				stPzsj.jyje = atof(DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.corpcode    , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.taxvouno    , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.taxpaycode  , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.pzlx        , "%s", DCIFieldAsString( cur, i++ ) );
				stPzsj.dycs = atoi(DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.dzbz        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.pzsjwjm     , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.jyqd        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.zjrq        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.zjsj        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.zjlsh       , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.jyzt        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.hxdzbz      , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.qsbz        , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.taxpayname  , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.qspch				, "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.chkdate     , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.chkacctord	, "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.opbankno		, "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.opbankname  , "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.khh					, "%s", DCIFieldAsString( cur, i++ ) );
				sprintf( stPzsj.chjyje			, "%s", DCIFieldAsString( cur, i++ ) );
								         
        /*报文返回*/
        
        /* 1 */
        memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/zwrq", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.zwrq     );   
				
				/* 2 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/zhqzlsh", resultNode,iCount ); 	
				memset(tmpstr,0,sizeof(tmpstr));
				sprintf(tmpstr, "%d", stPzsj.zhqzlsh);	
        trim(tmpstr);		
				COMP_SOFTSETXML(sXmlnode, tmpstr     );
				
				/* 3 */			
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jyrq", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.jyrq      );
				
				/* 4 */				
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/dqdh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.dqdh        );
				
				/* 5 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jgdh", resultNode,iCount );				
				COMP_SOFTSETXML(sXmlnode, stPzsj.jgdh );
				
				/* 6 */				
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jygy", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.jygy     );
				
				/* 7 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/zddh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.zddh    );
				
				/* 8 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/msgno", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.msgno     );
				
				/* 9 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/entrustdate", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.entrustdate    );
				
				/* 10 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/taxorgcode", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.taxorgcode            );
				
				/* 11 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/packno", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.packno         );
				
				/* 12 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/trano", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.trano         );
				
				/* 13 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/payeebankno", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.payeebankno          );
				
				/* 14 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/payeename", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.payeename         );
				
				/* 15 */				
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/paybkcode", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.paybkcode         );
				
				/* 16 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/payopbkcode", resultNode,iCount );				
				COMP_SOFTSETXML(sXmlnode, stPzsj.payopbkcode         );
				
				/* 17 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/payacct", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.payacct         );
				
				/* 18 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/handorgname", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.handorgname           );
				
				/* 19 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jyje", resultNode,iCount ); 
				memset(tmpstr,0,sizeof(tmpstr));
				sprintf(tmpstr, "%16.2f", stPzsj.jyje);	
        trim(tmpstr);		
				COMP_SOFTSETXML(sXmlnode, tmpstr     );				
								
				/* 20 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/corpcode", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.corpcode         );
				
				/* 21 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/taxvouno", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.taxvouno         );
				
				/* 22 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/taxpaycode", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.taxpaycode         );
				
				/* 23 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/pzlx", resultNode,iCount ); 
				COMP_SOFTSETXML(sXmlnode, stPzsj.pzlx         );
				
				/* 24 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/dycs", resultNode,iCount ); 
				memset(tmpstr,0,sizeof(tmpstr));
				sprintf(tmpstr, "%d", stPzsj.dycs);	
        trim(tmpstr);		
				COMP_SOFTSETXML(sXmlnode, tmpstr     );					
								
				/* 25 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/dzbz", resultNode,iCount );				
				COMP_SOFTSETXML(sXmlnode, stPzsj.dzbz           );
				
				/* 26 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/pzsjwjm", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.pzsjwjm           );
				
				/* 27 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jyqd", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.jyqd       );
				
				/* 28 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/zjrq", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.zjrq       );
				
				/* 29 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/zjsj", resultNode,iCount ); 
				COMP_SOFTSETXML(sXmlnode, stPzsj.zjsj       );
				
				/* 30 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/zjlsh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.zjlsh       );
				
				/* 31 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jyzt", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.jyzt       );
				
				/* 32 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/hxdzbz", resultNode,iCount ); 
				COMP_SOFTSETXML(sXmlnode, stPzsj.hxdzbz       );
				
				/* 33 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/qsbz", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.qsbz       );
				
				/* 34 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/taxpayname", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.taxpayname       );
				
				/* 35 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/qspch", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.qspch       );
				
				/* 36 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/chkdate", resultNode,iCount );				
				COMP_SOFTSETXML(sXmlnode, stPzsj.chkdate       );
				
				/* 37 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/chkacctord", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.chkacctord       );
				
				/* 38 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/opbankno", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.opbankno       );
				
				/* 39 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/opbankname", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.opbankname       );
				
				/* 40 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/khh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.khh       );
				
				/* 41 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/chjyje", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stPzsj.chjyje       );
				
        if (  querydirect[0] == '1' )        /* 1：向上翻 */
            iRet = DCIFetch2(cur, DCI_FETCH_PRIOR, 0 );
        else 
            iRet = DCIFetch2(cur, DCI_FETCH_NEXT,  0 );
    }
    LOG(LM_STD,Fmtmsg("iCount[%d]",iCount ),"INFO")		
    
    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);

    if (  querydirect[0] == '1' )        /* 1：向上翻 */
    {
        ipagefirst = queryoffset ;
        ipagelast = queryoffset - iCount ;
    }
    else /* 默认向下翻页 */
    {
        ipagefirst = queryoffset ;
        ipagelast = queryoffset + iCount ;
    }

    /* 首记录ID */
    COMP_HARDSETXML(firstNode,itoa(ipagefirst));
    /* 尾记录ID */
    COMP_HARDSETXML(lastNode,itoa(ipagelast));
    /* 返回记录数 */
    COMP_HARDSETXML(pageNode,itoa( iCount ));
    
    /* 返回汇总记录数 */
    iCount = 0;
        
    /* 20150807测试发现DBSelectToVar复杂count sql语句存在数值不准且会有coredump情况 */ 
    /*iRet = DBSelectToVar(sErrmsg, &iCount, countsql);*/
           
    LOG(LM_STD,Fmtmsg("countsql[%s]",countsql ),"INFO")
    /* 20150807 修改 */ 
    iRet = DBSelectToMultiVarChar(sErrmsg, countsql, &sCount);    
    if(iRet < 0)
		{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
					
				LOG(LM_STD,Fmtmsg("查询总笔数错误"),"ERROR");
				
		}
		LOG(LM_STD,Fmtmsg("sCount[%s]",sCount ),"INFO")      
		iCount=atol(sCount);
		LOG(LM_DEBUG,Fmtmsg("iCount[%d]",iCount),"INFO");
    COMP_HARDSETXML(countNode,itoa( iCount ));
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC;
}/**********************************************************************
组件函数: SYW_TIPS_PQryDZBPDJ
组件名称: 支持分页查询功能,必须遵循接口设计
组件参数：
输入参数：
输出参数：
处理说明: 支持外围分页查询功能
          参数配置：
                    外围上翻时必须送上次应答的上翻ID.
                    外围下翻时必须送上次应答的下翻ID.          
*************************************************************************/
IRESULT SYW_TIPS_PQryDZBPDJ(HXMLTREE lXmlhandle)
{
    int  i,iParas;
    char tmpstr[512+1];
    
    /* 组件参数1-10 */    
    char querysql[1024+1];
    char countsql[512+1];
    char querydirect[1+1];
    int querynum=0;
    int queryoffset=0;
    char countNode[128+1];
    char pageNode[128+1];
    char firstNode[128+1];
    char lastNode[128+1];
    char resultNode[512]; 
    
    int  iRet=-1;    
    int  ipagefirst=0, ipagelast=0;
    int  iCount=0;
    char sXmlnode[128];
    char sErrmsg[256];       
    
    char sBuf[256];
    CURSOR cur;
    char sSql1[512];  /*DCI 执行sql语句 add 20141103*/   
    
    char sProtocolno[60+1]; 
    SDB_TIPS_DZBPDJ stDzbpdj;

    fpub_InitSoComp(lXmlhandle);

    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /*组件参数检查*/
    COMP_PARACOUNTCHKMIN(10)
    
    memset(querysql, 0, sizeof(querysql));
    COMP_GETPARSEPARAS(1,querysql,"查询语句")
    trim(querysql);
    
    memset(countsql, 0, sizeof(countsql));
    COMP_GETPARSEPARAS(2,countsql,"汇总语句")
    trim(countsql);
    
    memset(tmpstr, 0, sizeof(tmpstr));
    memset(querydirect, 0, sizeof(querydirect));
    COMP_GETPARSEPARAS(3,tmpstr,"查询方向: 0首次:1上翻:2下翻") 
    trim(tmpstr);
    strncpy(querydirect, tmpstr, sizeof(querydirect)-1);
    
    memset(tmpstr, 0, sizeof(tmpstr));
    COMP_GETPARSEPARAS(4,tmpstr,"最大记录数")
    trim(tmpstr);
    querynum= atoi(  tmpstr );
    
    memset(tmpstr, 0, sizeof(tmpstr));
    COMP_GETPARSEPARAS(5,tmpstr,"请求偏移量")
    trim(tmpstr);
    queryoffset = atoi(  tmpstr );
    
    memset(countNode, 0, sizeof(countNode));
    COMP_GETPARSEPARAS(6,countNode,"总记录数")
    trim(countNode);
    
    memset(pageNode, 0, sizeof(pageNode));
    COMP_GETPARSEPARAS(7,pageNode,"本页记录数")
    trim(pageNode);
    
    memset(firstNode, 0, sizeof(firstNode));
    COMP_GETPARSEPARAS(8,firstNode,"首记录ID节点")
    trim(firstNode);
    
    memset(lastNode, 0, sizeof(lastNode));
    COMP_GETPARSEPARAS(9,lastNode,"尾记录ID节点")
    trim(lastNode);

    /*返回节点*/
    memset(resultNode, 0, sizeof(resultNode));
    COMP_GETPARSEPARAS(10,resultNode,"输出节点名称")
    trim(resultNode);
    
		LOG(LM_DEBUG,Fmtmsg("组件输入参数"),"INFO")
		LOG(LM_DEBUG,Fmtmsg("querysql[%s]",querysql ),"INFO")
		LOG(LM_DEBUG,Fmtmsg("countsql[%s]",countsql ),"INFO")
		LOG(LM_DEBUG,Fmtmsg("querydirect[%s]querynum[%d]queryoffset[%d]",querydirect, querynum, queryoffset ),"INFO")
		LOG(LM_DEBUG,Fmtmsg("resultNode[%s]",resultNode ),"INFO")
		
    if ((cur = DCIDeclareCursor(querysql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
         
    iRet = DCIFetch2(cur, DCI_FETCH_ABSOLUTE, queryoffset );
    iCount = 0;
    while( iRet > 0 )
    {
        if( iCount >= querynum )
            break;
        iCount ++;
        
        memset( &stDzbpdj, 0x00, sizeof( stDzbpdj ) );        
                
        i = 0;
        sprintf( stDzbpdj.zwrq, "%s", DCIFieldAsString( cur, i++ ) ); 
        stDzbpdj.zhqzlsh = atoi(DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.workdate   , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.dqdh       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.jgdh       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.jygy       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.zddh       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.dzlx       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.zjlsh      , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.taxorgcode , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.entrustdate, "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.trano      , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.chkdate    , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.chkacctord , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.payeebankno, "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.paybkcode  , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.czyh       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.jyqd       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.jyrq       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.jysj       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.jymc       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.khmc       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.jyzh       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.zhzl       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.dfzh       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.bzh        , "%s", DCIFieldAsString( cur, i++ ) ); 
        stDzbpdj.jyje = atof(DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.reason_info, "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.dzjg       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.clzt       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.jdbz       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.clrq       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.clsj       , "%s", DCIFieldAsString( cur, i++ ) ); 
        stDzbpdj.cllsh = atoi(DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.clzjlsh    , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.clxx       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.kzbz       , "%s", DCIFieldAsString( cur, i++ ) ); 
        sprintf( stDzbpdj.byzd       , "%s", DCIFieldAsString( cur, i++ ) ); 
               
        /*报文返回*/
        
        /* 1 */
        memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/zwrq", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.zwrq     );   
				
				/* 2 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/zhqzlsh", resultNode,iCount ); 	
				memset(tmpstr,0,sizeof(tmpstr));
        sprintf(tmpstr, "%d", stDzbpdj.zhqzlsh );
        trim(tmpstr);
        COMP_SOFTSETXML(sXmlnode, tmpstr);			
								
				/* 3 */			
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/workdate", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.workdate      );
				
				/* 4 */				
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/dqdh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.dqdh        );
				
				/* 5 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jgdh", resultNode,iCount );				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.jgdh );
				
				/* 6 */				
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jygy", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.jygy     );
				
				/* 7 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/zddh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.zddh    );
				
				/* 8 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/dzlx", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.dzlx     );
				
				/* 9 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/zjlsh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.zjlsh    );
				
				/* 10 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/taxorgcode", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.taxorgcode            );
				
				/* 11 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/entrustdate", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.entrustdate         );
				
				/* 12 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/trano", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.trano         );
				
				/* 13 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/chkdate", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.chkdate          );
				
				/* 14 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/chkacctord", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.chkacctord         );
				
				/* 15 */				
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/payeebankno", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.payeebankno         );
				
				/* 16 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/paybkcode", resultNode,iCount );				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.paybkcode         );
				
				/* 17 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/czyh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.czyh         );
				
				/* 18 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jyqd", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.jyqd           );
				
				/* 19 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jyrq", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.jyrq          );
				
				/* 20 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jysj", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.jysj         );
				
				/* 21 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jymc", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.jymc         );
				
				/* 22 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/khmc", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.khmc         );
				
				/* 23 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jyzh", resultNode,iCount ); 
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.jyzh         );
				
				/* 24 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/zhzl", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.zhzl           );
				
				/* 25 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/dfzh", resultNode,iCount );				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.dfzh           );
				
				/* 26 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/bzh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.bzh           );
				
				/* 27 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jyje", resultNode,iCount );
				memset(tmpstr,0,sizeof(tmpstr));
        sprintf(tmpstr, "%16.2f", stDzbpdj.jyje );
        trim(tmpstr);
        COMP_SOFTSETXML(sXmlnode, tmpstr);			 				
								
				/* 28 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/reason_info", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.reason_info       );
				
				/* 29 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/dzjg", resultNode,iCount ); 
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.dzjg       );
				
				/* 30 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/clzt", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.clzt       );
				
				/* 31 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/jdbz", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.jdbz       );
				
				/* 32 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/clrq", resultNode,iCount ); 
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.clrq       );
				
				/* 33 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/clsj", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.clsj       );
				
				/* 34 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/cllsh", resultNode,iCount ); 				
				memset(tmpstr,0,sizeof(tmpstr));
        sprintf(tmpstr, "%d", stDzbpdj.cllsh );
        trim(tmpstr);
        COMP_SOFTSETXML(sXmlnode, tmpstr);			 
								
				/* 35 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/clzjlsh", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.clzjlsh       );
				
				/* 36 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/clxx", resultNode,iCount );				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.clxx       );
				
				/* 37 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/kzbz", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.kzbz       );
				
				/* 38 */
				memset(sXmlnode,0,sizeof(sXmlnode));                
				sprintf( sXmlnode, "%s|%d/byzd", resultNode,iCount ); 				
				COMP_SOFTSETXML(sXmlnode, stDzbpdj.byzd       );

        if (  querydirect[0] == '1' )        /* 1：向上翻 */
            iRet = DCIFetch2(cur, DCI_FETCH_PRIOR, 0 );
        else 
            iRet = DCIFetch2(cur, DCI_FETCH_NEXT,  0 );
    }

    if ( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    DCIFreeCursor(cur);

    if (  querydirect[0] == '1' )        /* 1：向上翻 */
    {
        ipagefirst = queryoffset ;
        ipagelast = queryoffset - iCount ;
    }
    else /* 默认向下翻页 */
    {
        ipagefirst = queryoffset ;
        ipagelast = queryoffset + iCount ;
    }

    /* 首记录ID */
    COMP_HARDSETXML(firstNode,itoa(ipagefirst));
    /* 尾记录ID */
    COMP_HARDSETXML(lastNode,itoa(ipagelast));
    /* 返回记录数 */
    COMP_HARDSETXML(pageNode,itoa( iCount ));
    
    /* 返回汇总记录数 */
    iCount = 0;
    LOG(LM_STD,Fmtmsg("countsql[%s]",countsql ),"INFO")
    iRet = DBSelectToVar(sErrmsg, &iCount, countsql);
    if(iRet < 0)
		{
				LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s],iRet[%d]",DCILastError() ,iRet),"ERROR")
					
				LOG(LM_STD,Fmtmsg("查询总笔数错误"),"ERROR");
				
		}
		LOG(LM_DEBUG,Fmtmsg("iCount[%d]",iCount),"INFO");
    COMP_HARDSETXML(countNode,itoa( iCount ));
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC;
}
