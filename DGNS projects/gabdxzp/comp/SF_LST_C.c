/********************************************************************
版权所有:恒生电子股份有限公司
项目名称:恒生司法查控前置系统
版    本:V2.0
操作系统:AIX
数 据 库:ORA
文件名称:SF_C_LST.c
文件描述:列表查询模块
项 目 组:
程 序 员:屠秋龙
发布日期:2016-02-26

修    订:
修改日期:
*********************************************************************/

#include "gaps_head.h"
#include "gabdxzp_head.h"
#include "sfxt_lstqry.h"

#define SOCOMPVERSION "V2.0.0.1"
#define SOCOMPBUILDNO "V2.0.0.1"
/************************************************************************
动态组件函数定义
组件函数名称:ShowSocompVersion
组件功能:组件版本入口函数
************************************************************************/
IRESULT ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
   <root>\
      <soname>SFXT_LST.so</soname>\
      <sosrcname>SF_*_LST.*c </sosrcname>\
      <sonote>司法查控列表查询模块</sonote>\
      <version>\
         <rec ver=\"2.0.0.1\" modify=\"2016-02-26 09:08\" programer=\"司法查控产品组\" filesize=\"1000\">单元测试完成</rec>\
      </version>\
   </root>";
  printf("\n================动态组件基本信息================\n");
  printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
  printf("%s-%s\n",__PROJECTSNAME,__VERSION);
  if ( strlen(sversion) >= isize )
  {
    printf(" -->取详细信息失败...\n");
    return -2;
  }
  strcpy(sinfo,sversion);
  printf(" -->请查看详细信息...\n");
  return 0;
}

/************************************************************************
动态组件函数定义
组件函数名称: SFXT_COMMLST
组件名称: 司法查控通用查询 
组件功能:
  
 组件参数
 序号 参数类型  参数名称         资源类别     缺省值      可空  参数说明


组件结果状态:
  结果状态码         结果说明
    COMPSTATUS_SUCC
函数流程说明：
    

项 目 组: 
程 序 员: 屠秋龙
发布日期: 2016年2月26日
修改日期: 
参数使用示例:
************************************************************************/
IRESULT SFXT_COMMLST(HXMLTREE lXmlhandle)
{
    char sSql[4096];
    int  iRet = -1;
    int  iRealNum = 0;
    int iStartNum = 0;
    int iQueryNum = 20;
    int iEndNum = 0;
    int iCntNum = 0;
    int iTmp = 0;
    char sRspType[1+1];
    char sBuf[256];
    
    fpub_InitSoComp(lXmlhandle);
        
    memset(sSql, 0x00, sizeof(sSql));
    COMP_GETPARSEPARAS(1, sSql, "通用查询语句")

    /* 获取起始笔数，查询笔数 */
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "起始笔数")
    if( sBuf[0] == '\0' )
    {
        sBuf[0] == '1' ;
    }
    iStartNum = atoi(sBuf);

    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "查询笔数")
    if( sBuf[0] == '\0' )
    {
        sBuf[0] == '1' ;
    }
    iQueryNum = atoi(sBuf);
    
    iEndNum = iStartNum + iQueryNum ;
    /* 列表查询返回方式 */
    memset(sRspType, 0x00, sizeof(sRspType));
    GAB_DXZP_GETXMLSTR_NULL( XMLNM_RSPTYPE, sRspType, "返回方式" )
    /* 获取总笔数 */
    iRet = ffunc_sfxt_listQry_getCntNum(lXmlhandle, sSql, strlen(sSql), &iCntNum);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "获取总笔数");
    LOG(LM_STD,Fmtmsg("司法查控通用查询->完成获取总笔数[%d]", iCntNum), fpub_GetCompname(lXmlhandle)); 
    LOG( LM_DEBUG, Fmtmsg("司法查控通用查询->列表查询sql:[%s]", sSql), fpub_GetCompname(lXmlhandle));
    if ( sRspType[0] == '0' )/* 写文件*/
    {
        iRet= ffunc_sfxt_listQry_wrtRndFile(lXmlhandle, sSql, iStartNum, iEndNum, &iRealNum);
    }else
    {
        iRet= ffunc_sfxt_listQry_wrtRndXml(lXmlhandle, sSql, iStartNum, iEndNum, &iRealNum);
    }
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "提取数据及写文件");
    LOG(LM_STD,Fmtmsg("司法查控通用查询->完成获取并回写记录"), fpub_GetCompname(lXmlhandle));  
    /* 设返回值 */
    COMP_SOFTSETXML(XMLNM_RESP_TOTALNUM, itoa(iCntNum))
    COMP_SOFTSETXML(XMLNM_RESP_REALNUM, itoa(iRealNum))
    iTmp = iCntNum-iEndNum ;
    if ( iTmp < 0 )
    {
        iTmp = 0;
    }
    COMP_SOFTSETXML(XMLNM_RESP_SURPNUM, itoa(iTmp))
    COMP_SOFTSETXML(XMLNM_RESP_STARTNUM, itoa(iStartNum))
    COMP_SOFTSETXML(XMLNM_RESP_QUERYNUM, itoa(iQueryNum))
    
    fpub_SetMsg(lXmlhandle, COMPSTATUS_SUCC, "司法查控通用查询成功");
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}
