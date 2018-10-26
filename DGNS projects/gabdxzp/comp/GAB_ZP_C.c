/********************************************************************
 版权所有:恒生电子股份有限公司（杭州）
 项目名称:恒生公安部电信诈骗前置项目(GABDXZP4.1)
 版    本:V2.1.0.1
 操作系统:
 文件名称:GAB_ZP_C.c
 文件描述:电信诈骗组件集
 程 序 员:tuql
 发布日期:2015-9-29
 程 序 员:
 修改日期:
 修改说明: 
 *********************************************************************/
#include "gaps_head.h"
#include "gabdxzp_head.h"
#include "gabdxzp_alltables.h"
#include <string.h>

char * fpub_base64_decode(char *src, int *size);
char * fpub_base64_encode(char *src, int *size, int maxlen);
#define SOCOMPVERSION "V2.0.0.1"
#define SOCOMPBUILDNO "V2.0.0.1"
#define  MAXSIZE 1024*1024  /*1M*/
/************************************************************************
 动态组件函数定义
 组件函数名称:ShowSocompVersion
 组件功能:组件版本入口函数
 ************************************************************************/
IRESULT ShowSocompVersion(char *sinfo, int isize)
{
    char sversion[] =
        "<?xml version=\"1.0\" encoding=\"GB2312\"?>\
   <root>\
      <soname>GAB_ZP_C.so</soname>\
      <sosrcname>GAB_ZP_C.*c </sosrcname>\
      <sonote>公安部电信诈骗下载模块</sonote>\
      <version>\
         <rec ver=\"2.0.0.1\" modify=\"2016-01-21 09:08\" programer=\"公安部电信诈骗前置产品组\" filesize=\"1000\">单元测试完成</rec>\
      </version>\
   </root>";
    printf("\n================动态组件基本信息================\n");
    printf("SOCOMPBUILDNO:%s.\n", SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n", SOCOMPVERSION);
    printf("%s-%s\n", __PROJECTSNAME, __VERSION);
    if (strlen(sversion) >= isize)
    {
        printf(" -->取详细信息失败...\n");
        return -2;
    }
    strcpy(sinfo, sversion);
    printf(" -->请查看详细信息...\n");
    return 0;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_XDXX_INS
 组件名称:登记下达信息表
 组件功能:登记下达信息表
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_XDXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    GAB_DXZP_XDXX st_gab_dxzp_xdxx;/*下达信息表*/

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("登记下达信息表->开始处理"), fpub_GetCompname(lXmlhandle));
    /*1.装载下达信息表*/
    memset(&st_gab_dxzp_xdxx, 0x00, sizeof(st_gab_dxzp_xdxx));
    iRet = ffunc_gabdxzp_getXml_XDXX_Req(lXmlhandle, &st_gab_dxzp_xdxx);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载下达信息表");
    LOG(LM_STD, Fmtmsg("登记下达信息表->完成装载下达信息表"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*3.登记下达信息表*/
    iRet = fdbop_ins_gab_dxzp_xdxx(lXmlhandle, &st_gab_dxzp_xdxx);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记下达信息表");
    LOG(LM_STD, Fmtmsg("登记下达信息表->完成登记下达信息表"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, st_gab_dxzp_xdxx.qqdzt)
    COMP_SOFTSETXML(XMLNM_SFXT_HOST_REQ_CLLX, "2")
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记下达信息表->处理成功[%s]", st_gab_dxzp_xdxx.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_JJZF_INS
 组件名称:登记紧急止付表
 组件功能:登记紧急止付表
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_JJZF_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char JJZF_JYDM[10];
    GAB_DXZP_JJZF st_gab_dxzp_jjzf;/*止付解止表*/

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("登记紧急止付表->开始处理"), fpub_GetCompname(lXmlhandle));
    /*2.装载止付解止表*/
    memset(&st_gab_dxzp_jjzf, 0x00, sizeof(st_gab_dxzp_jjzf));
    GAB_DXZP_GETXMLSTR_NOTNULL("/pub/jydm",JJZF_JYDM,"交易代码");
    if(0==strcmp(JJZF_JYDM,"945100"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945100_Req(lXmlhandle, &st_gab_dxzp_jjzf);
    	}
    if (0==strcmp(JJZF_JYDM,"945101"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945101_Req(lXmlhandle, &st_gab_dxzp_jjzf);
    	}
    if(0==strcmp(JJZF_JYDM,"945102"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945102_Req(lXmlhandle, &st_gab_dxzp_jjzf);
    	} 
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载止付解止表");
    LOG(LM_STD, Fmtmsg("登记紧急止付表->完成装载止付解止表"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.登记止付解止表*/
    iRet = fdbop_ins_gab_dxzp_jjzf(lXmlhandle, &st_gab_dxzp_jjzf);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记止付解止表");
    LOG(LM_STD, Fmtmsg("登记紧急止付表->完成登记止付解止表"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记紧急止付表->处理成功[%s]",st_gab_dxzp_jjzf.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}





/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_DJXJ_INS
 组件名称:登记冻结续解表
 组件功能:登记冻结续解表
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_DJXJ_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char DJXJ_JYDM[10];
    GAB_DXZP_DJXJ st_gab_dxzp_djxj;/*止付解止表*/

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("登记冻结续解表->开始处理"), fpub_GetCompname(lXmlhandle));
    /*2.装载冻结续解表*/
    memset(&st_gab_dxzp_djxj, 0x00, sizeof(st_gab_dxzp_djxj));
    GAB_DXZP_GETXMLSTR_NOTNULL("/pub/jydm",DJXJ_JYDM,"交易代码");
    if(0==strcmp(DJXJ_JYDM,"945103"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945103_Req(lXmlhandle, &st_gab_dxzp_djxj);
    	}
    if (0==strcmp(DJXJ_JYDM,"945104"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945104_Req(lXmlhandle, &st_gab_dxzp_djxj);
    	}
    if(0==strcmp(DJXJ_JYDM,"945105"))
    	{
    		iRet = ffunc_gabdxzp_getXml_945105_Req(lXmlhandle, &st_gab_dxzp_djxj);
    	} 
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载冻结续解表");
    LOG(LM_STD, Fmtmsg("登记冻结续解表->完成装载冻结续解表"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.登记冻结续解表*/
    iRet = fdbop_ins_gab_dxzp_djxj(lXmlhandle, &st_gab_dxzp_djxj);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记冻结续解表");
    LOG(LM_STD, Fmtmsg("登记冻结续解表->完成登记冻结续解表"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记冻结续解表->处理成功[%s]",st_gab_dxzp_djxj.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}



/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_SBXX_INS
 组件名称:记录电信诈骗上报信息记录
 组件功能:记录电信诈骗上报信息记录
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_SBXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
    char sXhNodepath[200];
    int n=-1;
   
    GAB_DXZP_SBXX st_gab_dxzp_sbxx;/*上报信息表*/

    fpub_InitSoComp(lXmlhandle);
    memset(sPath,0x00,sizeof(sPath));
    memset(sXhNodepath,0x00,sizeof(sXhNodepath));
    COMP_PARACOUNTCHKMIN(2)
    COMP_GETPARSEPARAS(1,sPath,"传输报文流水号存放路径")
    COMP_GETPARSEPARAS(2,sXhNodepath,"循环节点存放路径")
    
    trim(sPath);
    trim(sXhNodepath);
    LOG(LM_STD, Fmtmsg("登记上报信息表->开始处理"), fpub_GetCompname(lXmlhandle));
    /*2.装载上报信息表*/
    memset(&st_gab_dxzp_sbxx, 0x00, sizeof(st_gab_dxzp_sbxx));
    
    iRet = ffunc_gabdxzp_getXml_SBXX_Req(lXmlhandle, &st_gab_dxzp_sbxx);
    
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载上报信息表");
    memset(st_gab_dxzp_sbxx.csbwlsh,0x00,sizeof(st_gab_dxzp_sbxx.csbwlsh));
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"传输报文流水号");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_sbxx.csbwlsh,"%s",sCsBwlsh);
    if(0<strlen(sXhNodepath))
    	{
   			 n=xml_ElementCount(lXmlhandle,sXhNodepath);
   			 if(n<0)
   			   {
   			  		LOG(LM_STD,Fmtmsg("%s节点不存在",sXhNodepath), fpub_GetCompname(lXmlhandle));
   			      return n;
   			   }
   			 if(0==n)
   			 	{
   			 		st_gab_dxzp_sbxx.sbjls=1;
   			 	 }
   			 else
   			 	{
   			    st_gab_dxzp_sbxx.sbjls=n;
   			   }
      }
    LOG(LM_STD, Fmtmsg("登记上报信息表->完成装载上报信息表"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.登记上报信息表*/
    iRet = fdbop_ins_gab_dxzp_sbxx(lXmlhandle, &st_gab_dxzp_sbxx);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记上报信息表");
    LOG(LM_STD, Fmtmsg("登记上报信息表->完成登记上报信息表"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记上报信息表->处理成功[%s]",st_gab_dxzp_sbxx.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}


/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_SAJB_INS
 组件名称:记录电信诈骗涉案举报记录
 组件功能:记录电信诈骗涉案举报记录
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_SAJB_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
    
    
    GAB_DXZP_SAJB st_gab_dxzp_sajb;/*涉案举报表*/

    fpub_InitSoComp(lXmlhandle);
    
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"传输报文流水号存放路径")
    trim(sPath);
    
    LOG(LM_STD, Fmtmsg("登记涉案举报表->开始处理"), fpub_GetCompname(lXmlhandle));
    /*2.装载涉案举报表*/
    memset(&st_gab_dxzp_sajb, 0x00, sizeof(st_gab_dxzp_sajb));
    
    iRet = ffunc_gabdxzp_getXml_945111_Req(lXmlhandle, &st_gab_dxzp_sajb);
    
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载涉案举报表");
    
    memset(st_gab_dxzp_sajb.csbwlsh,0x00,sizeof(st_gab_dxzp_sajb.csbwlsh));
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"传输报文流水号");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_sajb.csbwlsh,"%s",sCsBwlsh);
    
    LOG(LM_STD, Fmtmsg("登记涉案举报表->完成装载涉案举报表"), fpub_GetCompname(lXmlhandle));
    /*此处只用于单笔上报取止付申请表信息*/
    COMP_SOFTSETXML("/gabdxzp/sbpch",st_gab_dxzp_sajb.sbpch);
    /*此处只用于单笔上报取止付申请表信息*/
    DCIBegin();
    /*4.登记涉案举报表*/
    iRet = fdbop_ins_gab_dxzp_sajb(lXmlhandle, &st_gab_dxzp_sajb);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记涉案举报表");
    LOG(LM_STD, Fmtmsg("登记涉案举报表->完成登记涉案举报表"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记涉案举报表->处理成功[%s]",st_gab_dxzp_sajb.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_YCKK_INS
 组件名称:记录电信诈骗异常开卡记录
 组件功能:记录电信诈骗异常开卡记录
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_YCKK_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
    GAB_DXZP_YCKK st_gab_dxzp_yckk;/*异常开卡表*/

    fpub_InitSoComp(lXmlhandle);
    
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"传输报文流水号存放路径")
    trim(sPath);
    LOG(LM_STD, Fmtmsg("异常开卡表->开始处理"), fpub_GetCompname(lXmlhandle));
    /*2.装载涉案举报表*/

  	memset(&st_gab_dxzp_yckk, 0x00, sizeof(st_gab_dxzp_yckk));
  	iRet = ffunc_gabdxzp_getXml_945112_Req(lXmlhandle, &st_gab_dxzp_yckk);
  	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载异常开卡表");
  	
  	memset(st_gab_dxzp_yckk.csbwlsh,0x00,sizeof(st_gab_dxzp_yckk.csbwlsh));
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"传输报文流水号");
    trim(sCsBwlsh);
  	sprintf(st_gab_dxzp_yckk.csbwlsh,"%s",sCsBwlsh);
  	LOG(LM_STD, Fmtmsg("登记异常开卡表->完成装载异常开卡表"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.登记异常开卡表*/
    iRet = fdbop_ins_gab_dxzp_yckk(lXmlhandle, &st_gab_dxzp_yckk);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记异常开卡表");

    LOG(LM_STD, Fmtmsg("登记异常开卡表->完成登记异常开卡表"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记异常开卡表->处理成功[%s]",st_gab_dxzp_yckk.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}



/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_SAZH_INS
 组件名称:记录电信诈骗涉案账户记录
 组件功能:记录电信诈骗涉案账户记录
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_SAZH_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
   
    GAB_DXZP_SAZH st_gab_dxzp_sazh;/*涉案账户表*/

    fpub_InitSoComp(lXmlhandle);
    
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"传输报文流水号存放路径")
    trim(sPath);
    LOG(LM_STD, Fmtmsg("涉案账户表->开始处理"), fpub_GetCompname(lXmlhandle));
    /*2.装载涉案账户表*/
   
   
    memset(&st_gab_dxzp_sazh, 0x00, sizeof(st_gab_dxzp_sazh));
    iRet = ffunc_gabdxzp_getXml_945113_Req(lXmlhandle, &st_gab_dxzp_sazh);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载涉案账户表");
    memset(st_gab_dxzp_sazh.csbwlsh,0x00,sizeof(st_gab_dxzp_sazh.csbwlsh));
    
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"传输报文流水号");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_sazh.csbwlsh,"%s",sCsBwlsh);
   
    LOG(LM_STD, Fmtmsg("登记->完成装载涉案账户表"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.登记涉案账户表*/
   
    iRet = fdbop_ins_gab_dxzp_sazh(lXmlhandle, &st_gab_dxzp_sazh);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记涉案账户表");
     
  
    LOG(LM_STD, Fmtmsg("登记涉案账户表->完成登记涉案账户表"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记涉案账户表->处理成功[%s]",st_gab_dxzp_sazh.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}


/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_YCSJ_INS
 组件名称:记录电信诈骗异常事件记录
 组件功能:记录电信诈骗异常事件记录
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_YCSJ_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
   
    GAB_DXZP_YCSJ st_gab_dxzp_ycsj;/*异常事件表*/

    fpub_InitSoComp(lXmlhandle);
    
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"传输报文流水号存放路径")
    trim(sPath);
    LOG(LM_STD, Fmtmsg("异常事件表->开始处理"), fpub_GetCompname(lXmlhandle));
    /*2.装载异常事件表*/
   
   
    memset(&st_gab_dxzp_ycsj, 0x00, sizeof(st_gab_dxzp_ycsj));
    iRet = ffunc_gabdxzp_getXml_945114_Req(lXmlhandle, &st_gab_dxzp_ycsj);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载异常事件表");
    memset(st_gab_dxzp_ycsj.csbwlsh,0x00,sizeof(st_gab_dxzp_ycsj.csbwlsh));
    
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"传输报文流水号");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_ycsj.csbwlsh,"%s",sCsBwlsh);
    LOG(LM_STD, Fmtmsg("登记->完成装载异常事件表"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.登记异常事件表*/
   
    iRet = fdbop_ins_gab_dxzp_ycsj(lXmlhandle, &st_gab_dxzp_ycsj);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记异常事件表");
   
  
    LOG(LM_STD, Fmtmsg("登记异常事件表->完成登记异常事件表"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记异常事件表->处理成功[%s]",st_gab_dxzp_ycsj.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_ZHSA_INS
 组件名称:记录电信诈骗账户涉案记录
 组件功能:记录电信诈骗账户涉案记录
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_ZHSA_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
    
    GAB_DXZP_ZHSA st_gab_dxzp_zhsa;/*账户涉案表*/

    fpub_InitSoComp(lXmlhandle);
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"传输报文流水号存放路径")
    trim(sPath);
    LOG(LM_STD, Fmtmsg("登记账户涉案表->开始处理"), fpub_GetCompname(lXmlhandle));
    /*2.装载账户涉案表*/
    memset(&st_gab_dxzp_zhsa, 0x00, sizeof(st_gab_dxzp_zhsa));
   
    iRet = ffunc_gabdxzp_getXml_945115_Req(lXmlhandle, &st_gab_dxzp_zhsa);

    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载账户涉案表");
    
    memset(st_gab_dxzp_zhsa.csbwlsh,0x00,sizeof(st_gab_dxzp_zhsa.csbwlsh));
        
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"传输报文流水号");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_zhsa.csbwlsh,"%s",sCsBwlsh);
    LOG(LM_STD, Fmtmsg("登记账户涉案表->完成装载账户涉案表"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.登记账户涉案表*/
    iRet = fdbop_ins_gab_dxzp_zhsa(lXmlhandle, &st_gab_dxzp_zhsa);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记账户涉案表");
    LOG(LM_STD, Fmtmsg("登记账户涉案表->完成登记账户涉案表"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记账户涉案表->处理成功[%s]",st_gab_dxzp_zhsa.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}




/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_SFSA_INS
 组件名称:记录电信诈骗身份涉案记录
 组件功能:记录电信诈骗身份涉案记录
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_SFSA_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    char sCsBwlsh[53+1];
    
    GAB_DXZP_SFSA st_gab_dxzp_sfsa;/*身份涉案表*/

    fpub_InitSoComp(lXmlhandle);
    
    memset(sPath,0x00,sizeof(sPath));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
   
    COMP_PARACOUNTCHKMIN(1)
    COMP_GETPARSEPARAS(1,sPath,"传输报文流水号存放路径")
    trim(sPath);
    LOG(LM_STD, Fmtmsg("登记身份涉案表->开始处理"), fpub_GetCompname(lXmlhandle));
    /*2.装载身份涉案表*/
    memset(&st_gab_dxzp_sfsa, 0x00, sizeof(st_gab_dxzp_sfsa));
   
    iRet = ffunc_gabdxzp_getXml_945116_Req(lXmlhandle, &st_gab_dxzp_sfsa);

    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载身份涉案表");
    
    memset(st_gab_dxzp_sfsa.csbwlsh,0x00,sizeof(st_gab_dxzp_sfsa.csbwlsh));
        
    GAB_DXZP_GETXMLSTR_NOTNULL(sPath,sCsBwlsh,"传输报文流水号");
    trim(sCsBwlsh);
    sprintf(st_gab_dxzp_sfsa.csbwlsh,"%s",sCsBwlsh);
    
    LOG(LM_STD, Fmtmsg("登记身份涉案表->完成装载身份涉案表"), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    /*4.登记账户涉案表*/
    iRet = fdbop_ins_gab_dxzp_sfsa(lXmlhandle, &st_gab_dxzp_sfsa);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记身份涉案表");
    LOG(LM_STD, Fmtmsg("登记身份涉案表->完成登记身份涉案表"), fpub_GetCompname(lXmlhandle));
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记身份涉案表->处理成功[%s]",st_gab_dxzp_sfsa.ywsqbh), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}





/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_DATA_DEAL
 组件名称:数据处理
 组件功能:数据处理
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_DATA_DEAL(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sStartTime[40];
    char sStopTime[40];
    char sStrq[9];
    char sSprq[9];
    char sStsj[7];
    char sSpsj[7];
    fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

    memset(sStartTime,0x00,sizeof(sStartTime));
    memset(sStopTime,0x00,sizeof(sStopTime));
    memset(sStrq,0x00,sizeof(sStrq));
    memset(sSprq,0x00,sizeof(sSprq));
    memset(sStsj,0x00,sizeof(sStsj));
    memset(sSpsj,0x00,sizeof(sSpsj));
    COMP_PARACOUNTCHKMIN(2)
    COMP_GETPARSEPARAS(1,sStartTime,"开始时间")
    COMP_GETPARSEPARAS(2,sStopTime,"结束时间")
    LOG(LM_STD,Fmtmsg("开始时间=[%s],结束时间=[%s]",sStartTime,sStopTime),fpub_GetCompname(lXmlhandle));
    
    
    if('\0' != sStartTime[0] || '\0' != sStopTime[0])
    	{
    		strncpy( sStrq,sStartTime,8); 
      	strncpy( sStsj,sStartTime+8,6); 
      	strncpy( sSprq,sStopTime,8); 
      	strncpy( sSpsj,sStopTime+8,6); 
      	iRet = xml_SetElement(lXmlhandle,"/sfck/host/resp/zxqsrq",sStrq);
      	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "节点设值");
      	iRet = xml_SetElement(lXmlhandle,"/sfck/host/resp/zxqssj",sStsj);
      	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "节点设值");
      	iRet = xml_SetElement(lXmlhandle,"/sfck/host/resp/zxjsrq",sSprq);
      	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "节点设值");
      	iRet = xml_SetElement(lXmlhandle,"/sfck/host/resp/zxjssj",sSpsj);
      	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "节点设值");
    	}
    	
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif    
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   
    return COMPSTATUS_SUCC;
}



/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_CSBWLSH_SC
 组件名称:传输报文流水号生成
 组件功能:传输报文流水号生成
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
 

IRESULT GAB_DXZP_CSBWLSH_SC(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sMbJgBm[40];
    char sCsBwlsh[53+1];
    char sZwrq[8+1];
    char sPath[200];
    char sSql[256];
    char sYwlsh[40];
    char sTGJGBM[100];
    GAB_DXZP_DUAL st_gab_dxzp_dual;
    
    fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
    LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif
    memset(sMbJgBm,0x00,sizeof(sMbJgBm));
    memset(sCsBwlsh,0x00,sizeof(sCsBwlsh));
    memset(sZwrq,0x00,sizeof(sZwrq));
    memset(sPath,0x00,sizeof(sPath));
    
    COMP_PARACOUNTCHKMIN(2)
    COMP_GETPARSEPARAS(1,sMbJgBm,"目标机构编码")
    COMP_GETPARSEPARAS(2,sPath,"传输报文流水号存放路径")
    trim(sMbJgBm);
    trim(sPath);
    
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,sZwrq,"gaps日期");
    trim(sZwrq);
    memset(sSql, 0x00, sizeof(sSql));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_DXZP_XL,sSql,"业务流水号");
    memset(&st_gab_dxzp_dual, 0x00, sizeof(st_gab_dxzp_dual));
    LOG(LM_STD, Fmtmsg("sfxt_xl[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet=fdbop_qry_dual(lXmlhandle, &st_gab_dxzp_dual, sSql);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "获取业务流水号");
    GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/tgjgbm",sTGJGBM,"托管机构编码");
    if( '\0' == sTGJGBM[0] || 0 == strcmp(sTGJGBM," ") )
    	{
    		strcpy(sTGJGBM,"000000000000");
    	}
    sprintf(sCsBwlsh,"%12.12s_%12.12s%s%s%014ld",sMbJgBm,sTGJGBM,sZwrq,GetSysTime(),st_gab_dxzp_dual.nextval);
    trim(sCsBwlsh);
    LOG(LM_STD,Fmtmsg("传输报文流水号[%s]",sCsBwlsh),fpub_GetCompname(lXmlhandle));
    
    iRet = xml_SetElement(lXmlhandle,sPath,sCsBwlsh);
    
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "节点设值");
    
    	
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif    
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   
    return COMPSTATUS_SUCC;
}


/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_APPLICATIONID_SC
 组件名称:业务申请编号生成
 组件功能:业务申请编号生成
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
 

IRESULT GAB_DXZP_APPLICATIONID_SC(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sPath[200];
    char sApplicationID[36+1];
    char sZwrq[8+1];
    char sJyDm[20];
    char sValue[4+1];
    char sSql[256];
    char sYwlsh[40];
    char sYwlx[4+1];
    GAB_DXZP_DUAL st_gab_dxzp_dual;
    fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
    LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif
   
    memset(sPath,0x00,sizeof(sPath));
    memset(sApplicationID,0x00,sizeof(sApplicationID));
    memset(sZwrq,0x00,sizeof(sZwrq));
    COMP_PARACOUNTCHKMIN(2)
    COMP_GETPARSEPARAS(1,sJyDm,"交易代码") 
    COMP_GETPARSEPARAS(2,sPath,"业务申请编号存放路径")
    trim(sJyDm);
    trim(sPath);
    LOG(LM_STD,Fmtmsg("交易代码[%s]",sJyDm),fpub_GetCompname(lXmlhandle));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,sZwrq,"gaps日期");
    GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/ywlx",sYwlx,"业务类型");
    
    trim(sZwrq);
    memset(sValue,0x00,sizeof(sValue));
    if(0 == strcmp(sJyDm,"945111"))
    	{
    		strcpy(sValue,"0401");
    	}
     else if(0 == strcmp(sJyDm,"945112"))
     	{
     	  strcpy(sValue,"0403");	
     	}
     else if(0 == strcmp(sJyDm,"945113"))
     	{
     		strcpy(sValue,"0404");
      }
     else if(0 == strcmp(sJyDm,"945114"))
     	{
     		strcpy(sValue,"0405");
      }
     else if(0 == strcmp(sJyDm,"945115"))
     	{
     		strcpy(sValue,"0501");
      }
     else if(0 == strcmp(sJyDm,"945116"))
     	{
     		strcpy(sValue,"0502");
      }
      else if(0 == strcmp(sJyDm,"945123"))
     	{
     		strcpy(sValue,"0305");
      }
      else if(sYwlx[0] != '\0')
      	{
      		strncpy(sValue,sYwlx,4);
      	}
      else 
      {
        LOG(LM_STD,Fmtmsg("此交易代码不存在！"),fpub_GetCompname(lXmlhandle));
        return -1;
      }
    
    memset(sSql, 0x00, sizeof(sSql));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_DXZP_XL,sSql,"业务流水号");
    memset(&st_gab_dxzp_dual, 0x00, sizeof(st_gab_dxzp_dual));
    LOG(LM_STD, Fmtmsg("sfxt_xl[%s]", sSql), fpub_GetCompname(lXmlhandle));
    iRet=fdbop_qry_dual(lXmlhandle, &st_gab_dxzp_dual, sSql);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "获取业务流水号");
    sprintf(sApplicationID,"%s%s%s%018ld",sValue,sZwrq,GetSysTime(),st_gab_dxzp_dual.nextval);
    iRet = xml_SetElement(lXmlhandle,sPath,sApplicationID);
    LOG(LM_STD,Fmtmsg("业务申请编号[%s]",sApplicationID),fpub_GetCompname(lXmlhandle));
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "节点设值");
    
    	
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif    
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   
    return COMPSTATUS_SUCC;
}






/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_ATTACHMENT_LOAD
组件名称:GAB_DXZP_ATTACHMENT_LOAD
组件功能:
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
	1         输入      para1               XML报文             [/Response/Body/Attachments]  0         
	2         输入      para2               XML报文                                           0         
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-27 10:29:10(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_ATTACHMENT_LOAD(HXMLTREE lXmlhandle)
{
  int iRet = -1;
  char sbuf[1024];
  char xmlnode[1024];
  char attachments[255];
  char path[255];
  char filename[256];
  int  iParas;
  int childcount = 0;
  int i = 0;
  int elementlen = 0;
  char * pcontentbase64 = NULL;
  int alloclen = 0;
  char * pcontent = NULL;
  FILE * fp = NULL;
  GAB_DXZP_SMJFJ st_gab_dxzp_smjfj;/*电信诈骗扫描件附件表*/
  
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

	COMP_PARACOUNTCHKMIN(2);
	
	memset(sbuf, 0x00, sizeof(sbuf));
	COMP_GETPARSEPARAS(1, sbuf, "法律文书存放节点");
	memset(attachments, 0x00, sizeof(attachments));
	pstrcopy(attachments, sbuf, sizeof(attachments));
	
	memset(sbuf, 0x00, sizeof(sbuf));
	COMP_GETPARSEPARAS(2, sbuf, "法律文书存放路径");
	memset(path, 0x00, sizeof(path));
	pstrcopy(path, sbuf, sizeof(path));
	
	LOG(LM_STD, Fmtmsg("  -->[%s],[%s]",attachments,path), __func__);

	if (strlen(attachments) == 0 || strlen(path) == 0) {
		LOG(LM_STD, Fmtmsg("传入的参数1：【%s】，参数2:【%s】 无效，不能为空", attachments, path), __func__);
		fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}

	if ('/' == attachments[strlen(attachments)-1]) {
		attachments[strlen(attachments)-1] = '\0';
	}

	if ('/' == path[strlen(path)-1]) {
		path[strlen(path)-1] = '\0';
	}
	
	if (-1 == (childcount = xml_ChildElementCount(lXmlhandle, attachments))) {
		LOG(LM_STD, Fmtmsg(" xml_ChildElementCount-->处理失败:attachments=%s", attachments), __func__);
		fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}

	for (i = 0 ; i < childcount; ++i) {
		memset(sbuf, 0x00, sizeof(sbuf));
		memset(xmlnode, 0x00, sizeof(xmlnode));
		snprintf(xmlnode, sizeof(xmlnode)-1, "%s/Attachment|%d/Filename", attachments, i+1);
		if (-1 == xml_GetElement(lXmlhandle, xmlnode, sbuf, sizeof(sbuf)-1)) {
			LOG(LM_STD, Fmtmsg(" xml_GetElement-->处理失败:xmlnode=%s, bufsize=%d", xmlnode, sizeof(sbuf)-1), __func__);
			fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;
		}
		
		memset(filename, 0x00, sizeof(filename));
		snprintf(filename, sizeof(filename)-1, "%s/%s", path, sbuf);
		
		
		memset(xmlnode, 0x00, sizeof(xmlnode));
		snprintf(xmlnode, sizeof(xmlnode)-1, "%s/Attachment|%d/Content", attachments, i+1);
		if (-1 == (elementlen = xml_GetElementLen(lXmlhandle, xmlnode))) {
			LOG(LM_STD, Fmtmsg(" xml_GetElementLen-->处理失败:xmlnode=%s", xmlnode), __func__);
			fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;		
		}
		
		if (elementlen+1 > alloclen) {
			if ( NULL == (pcontentbase64 = (char *)realloc(pcontentbase64, elementlen+1))) {
				if (pcontentbase64) {
					free(pcontentbase64);
				}
				LOG(LM_STD, Fmtmsg(" realloc-->处理失败:分配%d字节内存失败", elementlen+1), __func__);
				fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
				fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
				return COMPRET_FAIL;			
			}
			alloclen = elementlen+1;
		}
		memset(pcontentbase64, 0x00, alloclen);
		
		if (-1 == xml_GetElement(lXmlhandle, xmlnode, pcontentbase64, elementlen+1)) {
			LOG(LM_STD, Fmtmsg(" xml_GetElement-->处理失败:xmlnode=%s, bufsize=%d", xmlnode, elementlen), __func__);
			free(pcontentbase64);
			fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;
		}
		
		if (NULL == (pcontent = fpub_base64_decode(pcontentbase64, &elementlen))) {
			LOG(LM_STD, Fmtmsg(" fpub_base64_decode-->处理失败:pcontentbase64=[%s] elementlen=%d", pcontentbase64, elementlen), __func__);
			free(pcontentbase64);
			fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;		
		}
		memset(&st_gab_dxzp_smjfj,0x00,sizeof(st_gab_dxzp_smjfj));
		iRet = ffunc_gabdxzp_getXml_SMJFJ_Req(lXmlhandle, &st_gab_dxzp_smjfj);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载电信诈骗扫描件附件表");
    LOG(LM_STD, Fmtmsg("登记电信诈骗扫描件附件表->完成装载电信诈骗扫描件附件表"), fpub_GetCompname(lXmlhandle));
    st_gab_dxzp_smjfj.xh=i;
    sprintf(st_gab_dxzp_smjfj.wjm,"%s",filename);
    sprintf(st_gab_dxzp_smjfj.wjdx,"%d",elementlen);
    DCIBegin();

    iRet = fdbop_ins_gab_dxzp_smjfj(lXmlhandle, &st_gab_dxzp_smjfj);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记电信诈骗扫描件附件表");
    LOG(LM_STD, Fmtmsg("登记电信诈骗扫描件附件表->完成电信诈骗扫描件附件表"), fpub_GetCompname(lXmlhandle));
    DCICommit();
		
		
		
		if (NULL == (fp = fopen(filename, "w+"))) {
			LOG(LM_STD, Fmtmsg(" fopen-->处理失败:filename=%s", filename), __func__);
			free(pcontentbase64);
			free(pcontent);
			fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			return COMPRET_FAIL;		
		}
		LOG(LM_STD,Fmtmsg("elementlen[%d],pcontent[%s]",elementlen,pcontent), __func__);
		fwrite(pcontent, 1, elementlen, fp);
		fclose(fp);
		free(pcontent);
	}
	if (pcontentbase64) {
		free(pcontentbase64);
	}
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}





/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_CKZTCX_INS
组件名称:GAB_DXZP_CKZTCX_INS
组件功能:
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:33:46(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_CKZTCX_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  
  GAB_DXZP_ZTCX st_gab_dxzp_ztcx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  
  /* 装载持卡主体查询表 */
  memset(&st_gab_dxzp_ztcx, 0x00, sizeof(st_gab_dxzp_ztcx));

  iRet = ffunc_gabdxzp_getXml_945107_Req(lXmlhandle, &st_gab_dxzp_ztcx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载电信诈骗主体查询表");
  LOG(LM_STD, Fmtmsg("登记电信诈骗主体查询表->完成装载电子诈骗主体查询表"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_ztcx(lXmlhandle, &st_gab_dxzp_ztcx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记电信诈骗主体查询表");
  LOG(LM_STD, Fmtmsg("登记电信诈骗主体查询表->完成登记电信诈骗主体查询表"), fpub_GetCompname(lXmlhandle));
  DCICommit();
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}








/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_DTCX_INS
组件名称:GAB_DXZP_DTCX_INS
组件功能:
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-26 17:00:02(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_DTCX_INS(HXMLTREE lXmlhandle)
{
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  
  GAB_DXZP_DTCX st_gab_dxzp_dtcx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  
  /* 装载动态查询表 */
  memset(&st_gab_dxzp_dtcx, 0x00, sizeof(st_gab_dxzp_dtcx));

  iRet = ffunc_gabdxzp_getXml_945108_Req(lXmlhandle, &st_gab_dxzp_dtcx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载动态查询表");
  LOG(LM_STD, Fmtmsg("登记动态查询表->完成装载动态查询表"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_dtcx(lXmlhandle, &st_gab_dxzp_dtcx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记动态查询表");
  LOG(LM_STD, Fmtmsg("登记动态查询表->完成动态查询表"), fpub_GetCompname(lXmlhandle));
  DCICommit();
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}








/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_DTCXJC_INS
组件名称:GAB_DXZP_DTCXJC_INS
组件功能:
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-27 10:10:10(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_DTCXJC_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  
  GAB_DXZP_DTCX st_gab_dxzp_dtcx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* 装载动态查询表 */
  memset(&st_gab_dxzp_dtcx, 0x00, sizeof(st_gab_dxzp_dtcx));

  iRet = ffunc_gabdxzp_getXml_945109_Req(lXmlhandle, &st_gab_dxzp_dtcx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载动态查询表");
  LOG(LM_STD, Fmtmsg("登记动态查询表->完成装载动态查询表"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_dtcx(lXmlhandle, &st_gab_dxzp_dtcx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记动态查询表");
  LOG(LM_STD, Fmtmsg("登记动态查询表->完成动态查询表"), fpub_GetCompname(lXmlhandle));
  DCICommit();
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}








/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_JYMXCX_INS
组件名称:GAB_DXZP_JYMXCX_INS
组件功能:
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:25:19(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_JYMXCX_INS(HXMLTREE lXmlhandle)
{

  char sbuf[255];
  int  iParas;
  int iRet = -1;

  GAB_DXZP_JYMX st_gab_dxzp_jymx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif
  /*装载交易明细查询表*/
  memset(&st_gab_dxzp_jymx, 0x00, sizeof(st_gab_dxzp_jymx));
  iRet = ffunc_gabdxzp_getXml_945106_Req(lXmlhandle, &st_gab_dxzp_jymx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载交易明细查询表");
  LOG(LM_STD, Fmtmsg("登记交易明细查询表->完成装载交易明细查询表"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_jymx(lXmlhandle, &st_gab_dxzp_jymx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记交易明细查询表");
  LOG(LM_STD, Fmtmsg("登记交易明细查询表->完成登记交易明细查询表"), fpub_GetCompname(lXmlhandle));
  DCICommit();
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return COMPSTATUS_SUCC;
}








/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_KEQZHCX_INS
组件名称:GAB_DXZP_KEQZHCX_INS
组件功能:
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_KEQZHCX_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  GAB_DXZP_QHCX st_gab_dxzp_qhcx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* 装载客户全账户查询表 */
  memset(&st_gab_dxzp_qhcx, 0x00, sizeof(st_gab_dxzp_qhcx));

  iRet = ffunc_gabdxzp_getXml_945110_Req(lXmlhandle, &st_gab_dxzp_qhcx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载客户全账户查询表 ");
  LOG(LM_STD, Fmtmsg("登记客户全账户查询表->完成装载客户全账户查询表"), fpub_GetCompname(lXmlhandle));
  LOG(LM_STD,Fmtmsg("cxzjlx[%s]",st_gab_dxzp_qhcx.cxzjlx), fpub_GetCompname(lXmlhandle));
  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_qhcx(lXmlhandle, &st_gab_dxzp_qhcx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记客户全账户查询表");
  LOG(LM_STD, Fmtmsg("登记客户全账户查询表->完成登记客户全账户查询表"), fpub_GetCompname(lXmlhandle));
  DCICommit();
  
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}















/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_ZHJBXX_ZHXX_INS
 组件名称:登记电信诈骗账户基本信息_账号信息
 组件功能:登记电信诈骗账户基本信息_账号信息
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_ZHJBXX_ZHXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    int i=1,j=1,t=1,n=1,iCnts1=0,iCnts2=0;/*总任务数*/
    char sPath[200];
    GAB_DXZP_ZHJBXX_ZHXX st_gab_dxzp_zhjbxx_zhxx;/*账户基本信息_账号信息表*/
    GAB_DXZP_ZHXX_ZHJYXX st_gab_dxzp_zhxx_zhjyxx;/*账户信息_账号交易信息*/
    fpub_InitSoComp(lXmlhandle);

    /*获取总任务数*/
    iCnts1=xml_ElementCount(lXmlhandle,"/sfck/host/resp/zhjbxx/zhxx");
    if(iCnts1<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/sfck/host/resp/zhjbxx/zhxx节点不存在"),fpub_GetCompname(lXmlhandle));
   			 if(0==iCnts1)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return iCnts1;
   		}
    LOG(LM_STD, Fmtmsg("登记账户基本信息_账号信息表->开始处理[%d]", iCnts1), fpub_GetCompname(lXmlhandle));
    
    /*2.装载及登记账户基本信息_账号信息表*/
    DCIBegin();
    for ( i=1,j=1; i<=iCnts1; i++,j++)
    {
        memset(&st_gab_dxzp_zhjbxx_zhxx, 0x00, sizeof(st_gab_dxzp_zhjbxx_zhxx));
        iRet = ffunc_gabdxzp_getXml_ZHJBXX_ZHXX_Resp(lXmlhandle, &st_gab_dxzp_zhjbxx_zhxx, i);
        GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载账户基本信息_账号信息表");
  
        LOG(LM_STD, Fmtmsg("登记账户基本信息_账号信息表->完成账户基本信息_账号信息表[%d]", i), fpub_GetCompname(lXmlhandle));
        
        /*登记账户基本信息_账号信息表->完成装载账户基本信息_账号信息表*/
        iRet = fdbop_ins_gab_dxzp_zhjbxx_zhxx(lXmlhandle, &st_gab_dxzp_zhjbxx_zhxx);
        GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "登记账户基本信息_账号信息表->完成装载账户基本信息_账号信息表");
        LOG(LM_STD, Fmtmsg("登记账户基本信息_账号信息表->完成装载账户基本信息_账号信息表[%d]", i), fpub_GetCompname(lXmlhandle));
        
        /*获取总任务数*/
        iCnts2=0;
        memset(sPath,0x00,sizeof(sPath));
        sprintf(sPath,"/sfck/host/resp/zhjbxx/zhxx|%d/zhjyxx",i);
        trim(sPath);
        iCnts2=xml_ElementCount(lXmlhandle,sPath);
        if(iCnts2<=0)
   	    	{
   			     LOG(LM_STD,Fmtmsg("/sfck/host/resp/zhjbxx/zhxx|%d/zhjyxx节点不存在",i),fpub_GetCompname(lXmlhandle));
   			     if(0==iCnts2)
   			       {
   			         continue;
   			       }
   			     return iCnts2;
   		    }
   		  LOG(LM_STD,Fmtmsg("/sfck/host/resp/zhjbxx/zhxx|%d/zhjyxx",i),fpub_GetCompname(lXmlhandle));
        LOG(LM_STD, Fmtmsg("登记电信诈骗账户信息_账号交易信息->开始处理[%d]", iCnts2), fpub_GetCompname(lXmlhandle));
        
        
        for(t=1,n=1;t<=iCnts2;t++,n++)
        {
        		 memset(&st_gab_dxzp_zhxx_zhjyxx,0x00,sizeof(st_gab_dxzp_zhxx_zhjyxx));
        		 iRet = ffunc_gabdxzp_getXml_ZHXX_ZHJYXX_Resp(lXmlhandle, &st_gab_dxzp_zhxx_zhjyxx, i,t);
        	   GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载账户信息_账号交易信息表");
             strcpy(st_gab_dxzp_zhxx_zhjyxx.zhxh,st_gab_dxzp_zhjbxx_zhxx.zhxh);
             LOG(LM_STD, Fmtmsg("登记账户信息_账号交易信息表->完成账户信息_账号交易信息表[%d]", t), fpub_GetCompname(lXmlhandle));
             /*登记账户信息_账号交易信息表->完成装载账户信息_账号交易信息表*/
             iRet = fdbop_ins_gab_dxzp_zhxx_zhjyxx(lXmlhandle, &st_gab_dxzp_zhxx_zhjyxx);
             GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "登记账户信息_账号交易信息表->完成装载账户基本信息_账号信息表");
             LOG(LM_STD, Fmtmsg("登记账户信息_账号交易信息表->完成装载账户信息_账号交易信息表[%d]", t), fpub_GetCompname(lXmlhandle));
             
        	   if ( n > GAB_DXZP_COMMIT_CNT )
             {/*达到提交记录数才提交事务*/
                DCICommit();
                DCIBegin();
                n = 1;
             }
        	
        }
        
        if ( j > GAB_DXZP_COMMIT_CNT )
        {/*达到提交记录数才提交事务*/
            DCICommit();
            DCIBegin();
            j = 1;
        }
    }
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记账户基本信息_账号信息表->处理成功[%d][%d]", i,t), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}













/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_JYMX_ZHJBXX_INS
组件名称:GAB_DXZP_JYMX_ZHJBXX_INS
组件功能:记录电信诈骗交易明细账户基本信息
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_JYMX_ZHJBXX_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  GAB_DXZP_JYMX_ZHJBXX st_gab_dxzp_jymx_zhjbxx;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* 装载交易明细_账户基本信息表 */
  memset(&st_gab_dxzp_jymx_zhjbxx, 0x00, sizeof(st_gab_dxzp_jymx_zhjbxx));

  iRet = ffunc_gabdxzp_getXml_JYMX_ZHJBXX_Resp(lXmlhandle, &st_gab_dxzp_jymx_zhjbxx);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载交易明细_账户基本信息表 ");
  LOG(LM_STD, Fmtmsg("登记交易明细_账户基本信息表->完成装载交易明细_账户基本信息表"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_jymx_zhjbxx(lXmlhandle, &st_gab_dxzp_jymx_zhjbxx);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记交易明细_账户基本信息表");
  LOG(LM_STD, Fmtmsg("登记交易明细_账户基本信息表->完成登记交易明细_账户基本信息表"), fpub_GetCompname(lXmlhandle));
  DCICommit();
  
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}










/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_QHCX_SFQZXX_INS
组件名称:GAB_DXZP_QHCX_SFQZXX_INS
组件功能:记录电信诈骗全户查询_司法强制信息
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/

IRESULT GAB_DXZP_QHCX_SFQZXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    int i=1,j=1, iCnts=0;/*总任务数*/
    GAB_DXZP_QHCX_SFQZXX st_gab_dxzp_qhcx_sfqzxx;/*全户查询_司法强制信息表*/

    fpub_InitSoComp(lXmlhandle);

    /*获取总任务数*/
    iCnts=xml_ElementCount(lXmlhandle,"/sfck/host/resp/sfqzxx");
    if(iCnts<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/sfck/host/resp/sfqzxx节点不存在"),fpub_GetCompname(lXmlhandle));
   			  if(0==iCnts)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return iCnts;
   		}
    LOG(LM_STD, Fmtmsg("登记全户查询_司法强制信息表->开始处理[%d]", iCnts), fpub_GetCompname(lXmlhandle));
    
    /*2.装载及登记全户查询_司法强制信息表*/
    DCIBegin();
    for ( i=1,j=1; i<=iCnts; i++,j++)
    {
        memset(&st_gab_dxzp_qhcx_sfqzxx, 0x00, sizeof(st_gab_dxzp_qhcx_sfqzxx));
        iRet = ffunc_gabdxzp_getXml_QHCX_SFQZXX_Resp(lXmlhandle, &st_gab_dxzp_qhcx_sfqzxx, i);
        GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载全户查询_司法强制信息表");
  
        LOG(LM_STD, Fmtmsg("登记全户查询_司法强制信息表->完成全户查询_司法强制信息表[%d]", i), fpub_GetCompname(lXmlhandle));
        
        /*登记全户查询_司法强制信息表->完成装载全户查询_司法强制信息表*/
        iRet = fdbop_ins_gab_dxzp_qhcx_sfqzxx(lXmlhandle, &st_gab_dxzp_qhcx_sfqzxx);
        GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "登记全户查询_司法强制信息表->完成装载全户查询_司法强制信息表");
        LOG(LM_STD, Fmtmsg("登记全户查询_司法强制信息表->完成装载全户查询_司法强制信息表[%d]", i), fpub_GetCompname(lXmlhandle));
        if ( j > GAB_DXZP_COMMIT_CNT )
        {/*达到提交记录数才提交事务*/
            DCICommit();
            DCIBegin();
            j = 1;
        }
    }
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记全户查询_司法强制信息表->处理成功[%d]", i), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}














/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_QHCX_ZHJBXX_ZZHXX_INS
组件名称:GAB_DXZP_QHCX_ZHJBXX_ZZHXX_INS
组件功能:记录电信诈骗全户查询账户基本信息_子账号信息
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/

IRESULT GAB_DXZP_QHCX_ZHJBXX_ZZHXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPath[200];
    int i=1,j=1,t=1,n=1, iCnts=0,iCnts2=0;/*总任务数*/
    
    GAB_DXZP_JYMX_ZHJBXX st_gab_dxzp_jymx_zhjbxx;/*全户查询_账户基本信息表*/
    GAB_DXZP_QHCX_ZZHXX st_gab_dxzp_qhcx_zzhxx;/*全户查询_子账号信息表*/
    
    fpub_InitSoComp(lXmlhandle);
    
    /*获取总任务数*/
    iCnts=xml_ElementCount(lXmlhandle,"/sfck/host/resp/zhjbxx");
    if(iCnts<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/sfck/host/resp/zhjbxx节点不存在"),fpub_GetCompname(lXmlhandle));
   			  if(0==iCnts)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return iCnts;
   		}
    LOG(LM_STD, Fmtmsg("登记全户查询_账户基本信息表->开始处理[%d]", iCnts), fpub_GetCompname(lXmlhandle));
    DCIBegin();
    for(t=1,n=1;t<=iCnts;t++,n++)
    {
    	memset(&st_gab_dxzp_jymx_zhjbxx,0x00,sizeof(st_gab_dxzp_jymx_zhjbxx));
    	iRet =ffunc_gabdxzp_getXml_QHCX_ZHJBXX_Resp(lXmlhandle,&st_gab_dxzp_jymx_zhjbxx,t);
    	GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载全户查询_账户基本信息表");
  
      LOG(LM_STD, Fmtmsg("登记全户查询_账户基本信息表->完成全户查询_账户基本信息表[%d]", t), fpub_GetCompname(lXmlhandle));
        
      /*登记全户查询_账户基本信息表->完成全户查询_账户基本信息表*/
      iRet = fdbop_ins_gab_dxzp_jymx_zhjbxx(lXmlhandle, &st_gab_dxzp_jymx_zhjbxx);
      GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "登记全户查询_账户基本信息表->完成全户查询_账户基本信息表");
      LOG(LM_STD, Fmtmsg("登记全户查询_子账号信息表->完成装载全户查询_账户基本信息表[%d]", t), fpub_GetCompname(lXmlhandle));
      if ( n > GAB_DXZP_COMMIT_CNT )
         {/*达到提交记录数才提交事务*/
             DCICommit();
             DCIBegin();
             n = 1;
         }
       memset(sPath,0x00,sizeof(sPath));
       sprintf(sPath,"/sfck/host/resp/zhjbxx|%d/zzhxx",t);
      /*获取总任务数*/
      iCnts2=xml_ElementCount(lXmlhandle,sPath);
      if(iCnts2<=0)
   		 {
   			  LOG(LM_STD,Fmtmsg("%s节点不存在",sPath),fpub_GetCompname(lXmlhandle));
   			   if(0==iCnts2)
   			    {
   			      continue;
   			    }
   			  return iCnts2;
   		 }
      LOG(LM_STD, Fmtmsg("登记全户查询_子账号信息表->开始处理[%d]", iCnts2), fpub_GetCompname(lXmlhandle));
    
      /*2.装载及登记全户查询_子账号信息表*/
    
      for ( i=1,j=1; i<=iCnts2; i++,j++)
       {
         memset(&st_gab_dxzp_qhcx_zzhxx, 0x00, sizeof(st_gab_dxzp_qhcx_zzhxx));
         iRet = ffunc_gabdxzp_getXml_QHCX_ZZHXX_Resp(lXmlhandle, &st_gab_dxzp_qhcx_zzhxx, t,i);
         GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载全户查询_子账号信息表");
  
         LOG(LM_STD, Fmtmsg("登记全户查询_子账号信息表->完成全户查询_子账号信息表[%d]", i), fpub_GetCompname(lXmlhandle));
        
         /*登记全户查询_子账号信息表->完成装载全户查询_子账号信息表*/
         iRet = fdbop_ins_gab_dxzp_qhcx_zzhxx(lXmlhandle, &st_gab_dxzp_qhcx_zzhxx);
         GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "登记全户查询_子账号信息表->完成装载全户查询_子账号信息表");
         LOG(LM_STD, Fmtmsg("登记全户查询_子账号信息表->完成装载全户查询_子账号信息表[%d]", i), fpub_GetCompname(lXmlhandle));
         if ( j > GAB_DXZP_COMMIT_CNT )
          {/*达到提交记录数才提交事务*/
             DCICommit();
             DCIBegin();
             j = 1;
          }
       }
     }
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记全户查询_子账号信息表->处理成功[%d]", i), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}















/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_QHCX_QLXX_INS
组件名称:GAB_DXZP_QHCX_QLXX_INS
组件功能:记录电信诈骗全户查询_权利人信息
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/

IRESULT GAB_DXZP_QHCX_QLXX_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    int i=1,j=1, iCnts=0;/*总任务数*/
    GAB_DXZP_QHCX_QLXX st_gab_dxzp_qhcx_qlxx;/*全户查询_权利人信息*/

    fpub_InitSoComp(lXmlhandle);

    /*获取总任务数*/
    iCnts=xml_ElementCount(lXmlhandle,"/sfck/host/resp/qzxx");
    if(iCnts<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/sfck/host/resp/qzxx节点不存在"),fpub_GetCompname(lXmlhandle));
   			  if(0==iCnts)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return iCnts;
   		}
    LOG(LM_STD, Fmtmsg("登记全户查询_权利人信息表->开始处理[%d]", iCnts), fpub_GetCompname(lXmlhandle));
    
    /*2.装载及登记全户查询_权利人信息表*/
    DCIBegin();
    for ( i=1,j=1; i<=iCnts; i++,j++)
    {
        memset(&st_gab_dxzp_qhcx_qlxx, 0x00, sizeof(st_gab_dxzp_qhcx_qlxx));
        iRet = ffunc_gabdxzp_getXml_QHCX_QLXX_Resp(lXmlhandle, &st_gab_dxzp_qhcx_qlxx, i);
        GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载全户查询_权利人信息表");
  
        LOG(LM_STD, Fmtmsg("登记全户查询_权利人信息表->完成全户查询_权利人信息表[%d]", i), fpub_GetCompname(lXmlhandle));
        
        /*登记全户查询_权利人信息表->完成装载全户查询_权利人信息表*/
        iRet = fdbop_ins_gab_dxzp_qhcx_qlxx(lXmlhandle, &st_gab_dxzp_qhcx_qlxx);
        GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "登记全户查询_权利人信息表->完成装载全户查询_权利人信息表");
        LOG(LM_STD, Fmtmsg("登记全户查询_权利人信息表->完成装载全户查询_权利人信息表[%d]", i), fpub_GetCompname(lXmlhandle));
        if ( j > GAB_DXZP_COMMIT_CNT )
        {/*达到提交记录数才提交事务*/
            DCICommit();
            DCIBegin();
            j = 1;
        }
    }
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记全户查询_权利人信息表->处理成功[%d]", i), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}



























/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_DTCX_RESP_INS
组件名称:GAB_DXZP_DTCX_RESP_INS
组件功能:记录电信诈骗动态查询响应
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_DTCX_RESP_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  int iCnts=0;
  int i=1,j=1;
  GAB_DXZP_DTCX_RESP st_gab_dxzp_dtcx_resp;
  GAB_DXZP_SBXX_PLZT st_gab_dxzp_sbxx_plzt;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* 装载动态查询响应表 */
  memset(&st_gab_dxzp_dtcx_resp, 0x00, sizeof(st_gab_dxzp_dtcx_resp));
  iCnts=xml_ElementCount(lXmlhandle,"/sfck/host/resp/zhjyxx");
  if(iCnts<=0)
  	{
        LOG(LM_STD,Fmtmsg("/sfck/host/resp/zhjyxx节点不存在"),fpub_GetCompname(lXmlhandle));
         if(0==iCnts)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
  			return iCnts;
  	}
  LOG(LM_STD, Fmtmsg("登记动态查询响应表->开始处理[%d]", iCnts), fpub_GetCompname(lXmlhandle));
  DCIBegin();  
  for(i=1,j=1;i<=iCnts;i++,j++)
    {
       iRet = ffunc_gabdxzp_getXml_DTCX_RESP_Resp(lXmlhandle, &st_gab_dxzp_dtcx_resp,i);
       GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载动态查询响应表 ");
       LOG(LM_STD, Fmtmsg("登记动态查询响应表->完成装载动态查询响应表"), fpub_GetCompname(lXmlhandle));
       
       iRet = ffunc_gabdxzp_getXml_SBXX_PLZT_Req(lXmlhandle,&st_gab_dxzp_sbxx_plzt,i); 
       GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载动态查询响应表 ");
       strcpy(st_gab_dxzp_sbxx_plzt.sbjydm,"945123");
       LOG(LM_STD, Fmtmsg("登记上报信息_批量状态表->完成装载上报信息_批量状态表"), fpub_GetCompname(lXmlhandle));
              
       iRet = fdbop_ins_gab_dxzp_dtcx_resp(lXmlhandle, &st_gab_dxzp_dtcx_resp);
       GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "登记动态查询响应表->完成装载登记动态查询响应表");
       iRet = fdbop_ins_gab_dxzp_sbxx_plzt(lXmlhandle, &st_gab_dxzp_sbxx_plzt);
       GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "登记上报信息_批量状态表->完成装载登记上报信息_批量状态表");
       
       LOG(LM_STD, Fmtmsg("登记动态查询响应表->完成登记动态查询响应表[%d]",i), fpub_GetCompname(lXmlhandle));
       LOG(LM_STD, Fmtmsg("登记上报信息_批量状态表->完成登记上报信息_批量状态表[%d]",i), fpub_GetCompname(lXmlhandle));
       if ( j > GAB_DXZP_COMMIT_CNT )
           {/*达到提交记录数才提交事务*/
                 DCICommit();
                 DCIBegin();
                 j = 1;
           }
       
   }
  DCICommit();
  
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}















/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_DTJC_RESP_INS
组件名称:GAB_DXZP_DTJC_RESP_INS
组件功能:记录电信诈骗动态解除响应
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_DTJC_RESP_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  GAB_DXZP_DTJC_RESP st_gab_dxzp_dtjc_resp;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* 装载动态解除响应表 */
  memset(&st_gab_dxzp_dtjc_resp, 0x00, sizeof(st_gab_dxzp_dtjc_resp));

  iRet = ffunc_gabdxzp_getXml_DTJC_RESP_Resp(lXmlhandle, &st_gab_dxzp_dtjc_resp);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载动态解除响应表 ");
  LOG(LM_STD, Fmtmsg("登记动态解除响应表->完成装载动态解除响应表"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_dtjc_resp(lXmlhandle, &st_gab_dxzp_dtjc_resp);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记动态解除响应表");
  LOG(LM_STD, Fmtmsg("登记动态解除响应表->完成登记动态解除响应表"), fpub_GetCompname(lXmlhandle));
  DCICommit();
  
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}














/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_ZTCX_RESP_INS
组件名称:GAB_DXZP_ZTCX_RESP_INS
组件功能:记录电信诈骗持卡主体查询响应
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_ZTCX_RESP_INS(HXMLTREE lXmlhandle)
{
  
  char sbuf[255];
  int  iParas;
  int iRet = -1;
  GAB_DXZP_ZTCX_RESP st_gab_dxzp_ztcx_resp;
  fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  /* 装载持卡主体查询响应表 */
  memset(&st_gab_dxzp_ztcx_resp, 0x00, sizeof(st_gab_dxzp_ztcx_resp));

  iRet = ffunc_gabdxzp_getXml_ZTCX_RESP_Resp(lXmlhandle, &st_gab_dxzp_ztcx_resp);
  GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载持卡主体查询响应表 ");
  LOG(LM_STD, Fmtmsg("登记持卡主体查询响应表->完成装载持卡主体查询响应表"), fpub_GetCompname(lXmlhandle));

  DCIBegin();

  iRet = fdbop_ins_gab_dxzp_ztcx_resp(lXmlhandle, &st_gab_dxzp_ztcx_resp);
  GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "登记持卡主体查询响应表");
  LOG(LM_STD, Fmtmsg("登记持卡主体查询响应表->完成登记持卡主体查询响应表"), fpub_GetCompname(lXmlhandle));
  DCICommit();
  
#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}

















/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_QUERY_JYMX
组件名称:GAB_DXZP_QUERY_JYMX
组件功能:取交易明细查询信息
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_QUERY_JYMX(HXMLTREE lXmlhandle)
{
    int  iParas;
    int iRet=-1;
    char sErrmsg[1000];
    char sSql[512];
    char sYwsqbh[100];
    char sBuf[200];
    char sSql_jyxx[512];
    int i=0;
    
    CURSOR query_jymx_cur;
    CURSOR zhxx_jyxx_cur;
    
   
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHKMIN(1);
    memset(sYwsqbh,0x00,sizeof(sYwsqbh));
    COMP_GETPARSEPARAS(1, sYwsqbh, "业务申请编号");
     
    GAB_DXZP_ZHJBXX_ZHXX st_gab_dxzp_zhjbxx_zhxx;
    GAB_DXZP_ZHXX_ZHJYXX st_gab_dxzp_zhxx_zhjyxx;
      
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"SELECT * \
     FROM gab_dxzp_zhjbxx_zhxx  WHERE  ywsqbh='%s' ORDER BY zhxh asc",sYwsqbh);
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((query_jymx_cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(query_jymx_cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(query_jymx_cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    while(1)
    {
        memset(&st_gab_dxzp_zhjbxx_zhxx, 0x00, sizeof(st_gab_dxzp_zhjbxx_zhxx));
        iRet = DBFetch(query_jymx_cur, SD_GAB_DXZP_ZHJBXX_ZHXX, NUMELE(SD_GAB_DXZP_ZHJBXX_ZHXX), &st_gab_dxzp_zhjbxx_zhxx, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zh);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhxh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zhxh);
       
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhlx",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zhlx);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhzt",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zhzt);

        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/bz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.bz);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/chbz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.chbz);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhye",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zhye);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/kyye",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.kyye);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjysj",st_gab_dxzp_zhjbxx_zhxx.zhxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhjbxx_zhxx.zhjysj);
        
        LOG(LM_STD,Fmtmsg("zhxh=[%s]",st_gab_dxzp_zhjbxx_zhxx.zhxh),fpub_GetCompname(lXmlhandle));
          
        memset(sSql_jyxx, 0x00, sizeof(sSql_jyxx));
        snprintf(sSql_jyxx,sizeof(sSql_jyxx),"SELECT *\
        FROM gab_dxzp_zhxx_zhjyxx  WHERE  ywsqbh='%s' and rwxh=1 and zhxh='%s' ORDER BY zhjyxh asc",sYwsqbh,st_gab_dxzp_zhjbxx_zhxx.zhxh);
        LOG(LM_STD,Fmtmsg("sSql_jyxx[%s]", sSql_jyxx),fpub_GetCompname(lXmlhandle));
        
        if ((zhxx_jyxx_cur = DCIDeclareCursor(sSql_jyxx, DCI_STMT_LOCATOR)) == -1)
         {
           LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
        if (DCIExecute(zhxx_jyxx_cur) == -1)
         {
           LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
           DCIFreeCursor(zhxx_jyxx_cur);
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
         i=0;
         while(1)
         {
         	   i++;
         	   memset(&st_gab_dxzp_zhxx_zhjyxx, 0x00, sizeof(st_gab_dxzp_zhxx_zhjyxx));
             iRet = DBFetch(zhxx_jyxx_cur, SD_GAB_DXZP_ZHXX_ZHJYXX, NUMELE(SD_GAB_DXZP_ZHXX_ZHJYXX), &st_gab_dxzp_zhxx_zhjyxx, sErrmsg );
             if ( iRet <= 0 )
             {
                 if(1 == i)  
                 	{
                 		 memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jylx",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jdbz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/bz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jyje",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jyye",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jysj",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jylsh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jydfmc",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jydfzh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jydfzjhm",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jydfzhkhh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jyzy",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jywdmc",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jywddm",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/rzh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/cph",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/pzzl",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/pzh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/xjbz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/zdh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jysfcg",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jyfsd",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/shmc",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/shh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/ip",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/mac",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/jygyh",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|1/beiz",st_gab_dxzp_zhjbxx_zhxx.zhxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                 		
                 	}       	
                 break;
             }
         	   memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jylx",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jylx);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jdbz",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jdbz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/bz",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.bz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jyje",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jyje);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jyye",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jyye);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jysj",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jysj);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jylsh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jylsh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jydfmc",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jydfmc);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jydfzh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jydfzh);
             
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jydfzjhm",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jydfzjhm);
             
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jydfzhkhh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jydfzhkhh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jyzy",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jyzy);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jywdmc",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jywdmc);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jywddm",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jywddm);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/rzh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.rzh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/cph",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.cph);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/pzzl",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.pzzl);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/pzh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.pzh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/xjbz",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.xjbz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/zdh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.zdh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jysfcg",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jysfcg);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jyfsd",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jyfsd);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/shmc",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.shmc);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/shh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.shh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/ip",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.ip);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/mac",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.mac);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/jygyh",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.jygyh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/zhjbxx/zhxx|%s/zhjyxx|%s/beiz",st_gab_dxzp_zhjbxx_zhxx.zhxh,st_gab_dxzp_zhxx_zhjyxx.zhjyxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_zhxx_zhjyxx.beiz);
             
         }
         DCIFreeCursor(zhxx_jyxx_cur);
         if( iRet < 0 )
         {
             LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
             fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return COMPRET_FAIL;
         }
       
    }
    DCIFreeCursor(query_jymx_cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"公安部电信诈骗交易明细查询结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_PROC_COMMBUF
 组件名称:处理通讯报文
 组件功能:处理通讯报文
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_PROC_COMMBUF(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sPkgHead[30+1];
    char sYwLxBm[6+1];/*业务类型编码*/
    char sXxLzMs[2+1];/*消息流转模式*/
    char sJgID[14+1];/*机构ID*/
    char sAddPkg[64];/*额外报文*/
    char *pCommbuf = NULL;
    char *pUTF8 = NULL;
    int  iCommbufLen=0;
    int  iUTF8Len=0;
    int  iRealCommLen=0;
    int  iAddPkg=0;

    fpub_InitSoComp(lXmlhandle);
    
    memset(sYwLxBm, 0x00, sizeof(sYwLxBm));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_QZJ_YWLXBM, sYwLxBm,"业务类型编码");
    if (sYwLxBm[0] == '\0')
    {
        GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_PUB_JYBM, sYwLxBm,"业务类型编码");
    }
    memset(sXxLzMs, 0x00, sizeof(sXxLzMs));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_QZJ_MODE, sXxLzMs,"消息流转模式");
    trim(sXxLzMs);
    if(sXxLzMs[0] == '\0')
    {
        pstrcopy(sXxLzMs, "01", sizeof(sXxLzMs));
    }
    memset(sJgID, 0x00, sizeof(sJgID));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_QZJ_JGID, sJgID,"机构ID");
    trim(sJgID);
    if (sJgID[0] == '\0')
    {
        GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_QSJGID, sJgID,"机构ID");
    }
    if ( atoi(sYwLxBm)>100101 && atoi(sYwLxBm) <= 100310)
    {/*若为反馈报文,则直接从/gabdxzp/xdxx/fsjgbm节点中获取*/
        memset(sJgID, 0x00, sizeof(sJgID));
        GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/xdxx/fsjgbm", sJgID,"机构ID");
        if (sJgID[0] == '\0')
        {
            GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/FSJGBM", sJgID,"机构ID");
        }
    }
    memset(sAddPkg, 0x00, sizeof(sAddPkg));
    snprintf(sAddPkg, sizeof(sAddPkg),"<Mode>%s</Mode><To>%s</To>",sXxLzMs, sJgID);
    iAddPkg=strlen(sAddPkg);
    iCommbufLen = xml_GetBinElementLen(lXmlhandle, "/commbuf");
    if (iCommbufLen <= 0 )
    {
        LOG(LM_STD,Fmtmsg("/commbuf长度为[%s],请确认", iCommbufLen ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD, Fmtmsg("处理通讯报文->开始处理,ywlxbm[%s][%d]", sYwLxBm, iCommbufLen), fpub_GetCompname(lXmlhandle));
    /* 根据获取到的长度申请内存 */
    pCommbuf = (char *)malloc( iCommbufLen+30+1 );
    if ( pCommbuf == NULL )
    {
        LOG(LM_STD,Fmtmsg("动态申请commbuf内存失败" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
	/*获取通讯区内容*/
	memset(pCommbuf, 0x00, iCommbufLen+30+1);
	if(0 > (iRet = xml_RelGetBinElement(lXmlhandle, "/commbuf", pCommbuf, iCommbufLen+30+1)))
	{
		free(pCommbuf);pCommbuf=NULL;
		LOG(LM_STD, Fmtmsg("取通讯区错误iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "与前置机通讯失败,获取通讯区错误");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	LOG(LM_STD, Fmtmsg("get pCommbuf[%d][%s]", iRet, pCommbuf), fpub_GetCompname(lXmlhandle));
    iRealCommLen=strlen(pCommbuf);
    if (strcmp(sYwLxBm,"100501")==0 || 
        strcmp(sYwLxBm,"100502")==0 || 
        strcmp(sYwLxBm,"100503")==0)
    {/*名单验证,什么都不做*/
        
    }else if (strcmp(sYwLxBm,"000000")==0 || strcmp(sYwLxBm,"000001")==0 )
    {/*获取消息*/
        /*去XML头*/
        iRealCommLen -=40;
        memmove(pCommbuf, pCommbuf+40, iRealCommLen);
        /*alter by liukq 20160420 BEGIN*/
        /*加业务种类编码*/
        /*
        memset(sPkgHead, 0x00, sizeof(sPkgHead));
        snprintf(sPkgHead, sizeof(sPkgHead), "%6.6s", sYwLxBm);
        memmove(pCommbuf+6, pCommbuf, iRealCommLen);
        memcpy(pCommbuf, sPkgHead, 6);
        iRealCommLen += 6;*/
        /*alter by liukq 20160420 END*/
    }else
    {/*其余业务报文*/
        /*去XML头*/
        iRealCommLen -=40;
        memmove(pCommbuf, pCommbuf+40, iRealCommLen);
         /*alter by liukq 20160420 BEGIN*/
        /*加业务种类编码*/
        /*memset(sPkgHead, 0x00, sizeof(sPkgHead));
        snprintf(sPkgHead, sizeof(sPkgHead), "%6.6s", sYwLxBm);
        memmove(pCommbuf+6, pCommbuf, iRealCommLen);
        memcpy(pCommbuf, sPkgHead, 6);
        iRealCommLen += 6;*/
        /*alter by liukq 20160420 END*/
        /*加额外信息
        memmove(pCommbuf+15+iAddPkg, pCommbuf+15, iRealCommLen-15);
        memcpy(pCommbuf+15, sAddPkg, iAddPkg);
        iRealCommLen += iAddPkg;
        */
        pCommbuf[iRealCommLen]='\0';
    }
    iUTF8Len=iRealCommLen * 1.5;
    pUTF8 = (char *)malloc( iUTF8Len );
    if ( pUTF8 == NULL )
    {
		free(pCommbuf);pCommbuf=NULL;
		LOG(LM_STD, Fmtmsg("申请UTF-8内存失败[%d]", iUTF8Len), fpub_GetCompname(lXmlhandle));
		/*alter by liukq 20160503 BEGIN
		fpub_SetMsg(lXmlhandle, 99999, "与前置机通讯超时,申请内存错误");
		END*/
		/*alter by liukq 20160503 BEGIN*/
		fpub_SetMsg(lXmlhandle, 98601, "与前置机通讯失败,申请内存错误");
		/*alter by liukq 20160503 END*/
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
    }   
    memset(pUTF8, 0x00, iUTF8Len);
    iRet = convert("GB18030", "UTF-8", pCommbuf, iRealCommLen, pUTF8, &iUTF8Len);
    if ( iRet < 0 )
    {
		free(pCommbuf);pCommbuf=NULL;
		free(pUTF8);pUTF8=NULL;
		LOG(LM_STD, Fmtmsg("转换GB18030 -> UTF-8内存失败[%d]", iRealCommLen), fpub_GetCompname(lXmlhandle));
		/*alter by liukq 20160503 BEGIN
		fpub_SetMsg(lXmlhandle, 99999, "与前置机通讯超时,转换报文格式错误");
		END*/
		/*alter by liukq 20160503 BEGIN*/
		fpub_SetMsg(lXmlhandle, 98601, "与前置机通讯失败,转换报文格式错误");
		/*alter by liukq 20160503 END*/
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
    }
    free(pCommbuf);pCommbuf=NULL;
    iUTF8Len=strlen(pUTF8);
    LOG(LM_STD, Fmtmsg("proc pCommbuf[%d][%s]", iUTF8Len, pUTF8), fpub_GetCompname(lXmlhandle));
    /*写通讯区*/
    if(0 > (iRet = xml_RelSetBinElement(lXmlhandle, "/commbuf", pUTF8, iUTF8Len)))
	{
		free(pUTF8);pUTF8=NULL;
		LOG(LM_STD, Fmtmsg("写通讯区错误iRet=[%d]", iRet), fpub_GetCompname(lXmlhandle));
		/*alter by liukq 20160503 BEGIN
		fpub_SetMsg(lXmlhandle, 99999, "与前置机通讯超时,写通讯区错误");
		END*/
		/*alter by liukq 20160503 BEGIN*/
		fpub_SetMsg(lXmlhandle, 98601, "与前置机通讯失败,写通讯区错误");
		/*alter by liukq 20160503 END*/
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	free(pUTF8);pUTF8=NULL;
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("处理通讯报文->处理成功"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}


/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_945120_LAST
 组件名称:定时获取消息后处理
 组件功能:定时获取消息后处理
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_945120_LAST(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sXmlNode[64+1];
    char sPkgFileName[256];
    char sPkgFilePath[256];
    char sFsjgbm[12+1];
    int iXmlCnts=0;
    char *pCommbuf = NULL;
    char *pUTF8 = NULL;
    char *pAscII = NULL;
    int  iCommbufLen=0;
    int  iUTF8Len=0;
    int  iAscIILen=0;
    int  iRealCommLen=0;
    int  iNodePkgLen=0;
    int  i=0;
    char sNodePkg[1024000];
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("定时获取消息后处理->开始处理"), fpub_GetCompname(lXmlhandle));
    /*获取保存文件名*/
    memset(sPkgFilePath, 0x00, sizeof(sPkgFilePath));
    snprintf(sPkgFilePath, sizeof(sPkgFilePath), "%s/file/dxzpqzdata/%s", getenv("HOME"), GetSysDate());
    ffunc_file_crtLocalPath(lXmlhandle, sPkgFilePath);
    memset(sPkgFileName, 0x00, sizeof(sPkgFileName));
    snprintf(sPkgFileName, sizeof(sPkgFileName), "%s/pkg%s", sPkgFilePath, GetSysTime());
    /*获取定时消息*/
    iCommbufLen = xml_GetBinElementLen(lXmlhandle, "/commbuf");
    if (iCommbufLen <= 0 )
    {
        LOG(LM_STD,Fmtmsg("/commbuf长度为[%s],请确认", iCommbufLen ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 根据获取到的长度申请内存 */
    pCommbuf = (char *)malloc( iCommbufLen+1 );
    if ( pCommbuf == NULL )
    {
        LOG(LM_STD,Fmtmsg("动态申请commbuf内存失败" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
	/*获取通讯区内容*/
	memset(pCommbuf, 0x00, iCommbufLen+1);
	if(0 > (iRet = xml_RelGetBinElement(lXmlhandle, "/commbuf", pCommbuf, iCommbufLen+1)))
	{
		free(pCommbuf);pCommbuf=NULL;
		LOG(LM_STD, Fmtmsg("取通讯区错误iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "与前置机通讯失败,获取通讯区错误");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	LOG(LM_STD, Fmtmsg("get pCommbuf[%d][%s]", iRet, pCommbuf), fpub_GetCompname(lXmlhandle));
    /*写获取消息文件*/
    iRet = ffunc_file_wrtFile(lXmlhandle, sPkgFileName, pCommbuf, iCommbufLen);
	free(pCommbuf);pCommbuf=NULL;
	if ( iRet < 0 )
	{
		LOG(LM_STD, Fmtmsg("写获取消息文件错误iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99997, "写获取消息文件失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
    /*获取处理记录数*/
    iXmlCnts=xml_ChildElementCount(lXmlhandle, "/Response/Body/MessageList");
    if ( iXmlCnts < 0 )
    {
		LOG(LM_STD, Fmtmsg("获取处理记录数错误iRet=[%d]", iXmlCnts), "ERROR");
		fpub_SetMsg(lXmlhandle, 99996, "获取处理记录数失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
    }
    LOG(LM_STD, Fmtmsg("获取处理记录数[%d]", iXmlCnts), fpub_GetCompname(lXmlhandle));
    for(i=0;i<iXmlCnts;i++)
    {
        memset(sXmlNode, 0x00, sizeof(sXmlNode));
        snprintf(sXmlNode, sizeof(sXmlNode),"/Response/Body/MessageList/Message|%d", i);
        memset(sNodePkg, 0x00, sizeof(sNodePkg));
        COMP_SOFTGETXML(sXmlNode, sNodePkg)
        LOG(LM_STD, Fmtmsg("sXmlNode[%s][%s]", sXmlNode, sNodePkg), fpub_GetCompname(lXmlhandle));
        iNodePkgLen=strlen(sNodePkg);
        pUTF8 = fpub_base64_decode(sNodePkg, &iNodePkgLen);
        iUTF8Len = strlen(pUTF8);
        iAscIILen=iUTF8Len * 1.5;
        pAscII = (char *)malloc( iAscIILen );
        if ( pAscII == NULL )
        {
            free(pUTF8);pUTF8=NULL;
	    	LOG(LM_STD, Fmtmsg("申请GB18030内存失败[%d]", iAscIILen), fpub_GetCompname(lXmlhandle));
	    	continue;
        } 
        memset(pAscII, 0x00, iAscIILen);
        iRet = convert( "UTF-8", "GB18030", pUTF8, iUTF8Len, pAscII, &iAscIILen);
        if ( iRet < 0 )
        {
            free(pUTF8);pUTF8=NULL;
            free(pAscII);pAscII=NULL;
	    	LOG(LM_STD, Fmtmsg("转换UTF-8 -> GB18030报文内容失败[%d]", iUTF8Len), fpub_GetCompname(lXmlhandle));
	    	continue;
        }
        free(pUTF8);pUTF8=NULL;
        iAscIILen=strlen(pAscII);
        LOG(LM_STD, Fmtmsg("base64->ascii=[%d][%s]", iAscIILen,pAscII), fpub_GetCompname(lXmlhandle));
        if(0 > (iRet = xml_RelSetBinElement(lXmlhandle, "/commbuf", pAscII, iAscIILen)))
	    {
	    	free(pAscII);pAscII=NULL;
	    	LOG(LM_STD, Fmtmsg("[%d]写通讯区错误iRet=[%s]", i+1, sNodePkg), fpub_GetCompname(lXmlhandle));
	    	continue;
	    }
	    free(pAscII);pAscII=NULL;
	    if( fpub_CallFlow(lXmlhandle,"subflow_gabdxzp_945120") != MID_SYS_SUCC)
	    {
	    	LOG(LM_STD, Fmtmsg("[%d]调用分发子流程失败", i+1), fpub_GetCompname(lXmlhandle));
	    	continue;
	    }
    }
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("定时获取消息后处理->处理成功"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_CHKSTS
 组件名称:待处理业务状态检查
 组件功能:待处理业务状态检查
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_CHKSTS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sSql[256];
    char sYwsqbh[36+1];/*业务申请编号*/
    char sCllx[1+1];/*处理类型*/
    char sOriQqdZt[2+1];/*原请求单状态*/
    char sNewQqdZt[2+1];/*新请求单状态*/
    char sHostfcflat[20];
    GAB_DXZP_XDXX st_gab_dxzp_xdxx;/*下达信息表*/
    GAB_DXZP_DUAL st_gab_dxzp_dual;
    
    memset(sYwsqbh, 0x00, sizeof(sYwsqbh));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH, sYwsqbh,"业务申请编号");
    memset(sCllx, 0x00, sizeof(sCllx));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CLLX, sCllx,"处理类型");
    
    LOG(LM_STD, Fmtmsg("待处理业务状态检查->处理开始,ywsqbh[%s],cllx[%s]",
        sYwsqbh, sCllx), fpub_GetCompname(lXmlhandle));
    /*查询信息下达表*/
    memset(&st_gab_dxzp_xdxx, 0x00, sizeof(st_gab_dxzp_xdxx));
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.ywsqbh, sYwsqbh);
    iRet=fdbop_qry_gab_dxzp_xdxx(lXmlhandle, &st_gab_dxzp_xdxx);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "查询信息下达表");
    LOG(LM_STD, Fmtmsg("完成查询信息下达表,qqdzt[%s]", 
        st_gab_dxzp_xdxx.qqdzt), fpub_GetCompname(lXmlhandle));
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, st_gab_dxzp_xdxx.qqdzt)
    memset(sOriQqdZt, 0x00, sizeof(sOriQqdZt));
    GAB_DXZP_PSTRCOPY(sOriQqdZt, st_gab_dxzp_xdxx.qqdzt)
    
    memset(sHostfcflat,0x00,sizeof(sHostfcflat));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_HXFCBZ,sHostfcflat,"核心超时是否防重标志");

    /*检查正在处理状态*/
    if ( strcmp(sOriQqdZt, "99" ) == 0 )
    {
	    LOG(LM_STD, Fmtmsg("本指令已反馈,不允许再次发起"), "ERROR");
	    fpub_SetMsg(lXmlhandle, 99903, "本指令已反馈,不需要再次发起");
	    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	    return COMPRET_FAIL;
    }

    /*检查正在处理状态*/
    if ( sOriQqdZt[1] == '9')
    {
	    LOG(LM_STD, Fmtmsg("业务正在处理中,不允许再次触发,状态不符[%s]", sOriQqdZt), "ERROR");
	    fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DEALING, MSG_GAB_DXZP_DEALING);
	    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	    return COMPRET_FAIL;
    }
    /*根据处理类型作状态检查,为空则不作检查*/
    if(sCllx[0]=='2')
    {/*要求提交核心,请求单状态务必12-落地成功或21-提交失败*/
        /*alter by liukq 20160324 BEGIN*/
        if (strcmp(sOriQqdZt, "20") != 0 && strcmp(sOriQqdZt, "21") != 0 && strcmp(sOriQqdZt, "23") != 0 && strcmp(sOriQqdZt, "33") != 0 )
        {
	        LOG(LM_STD, Fmtmsg("要求提交核心,状态不符[%s]", sOriQqdZt), "ERROR");
	        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_CHKSTS, MSG_GAB_DXZP_CHKSTS);
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	        return COMPRET_FAIL;
        }
        if(0==strcmp(sHostfcflat,"1"))
        {/*核心防重*/
            if(0== strcmp(sOriQqdZt, "21") || 0 == strcmp(sOriQqdZt, "23") || 0 == strcmp(sOriQqdZt, "33") )
            {
                strcpy(st_gab_dxzp_xdxx.qqdzt,"20");
            	iRet=fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
                GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "更新信息下达表");
                DCICommit();
                COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, "20")
                COMP_SOFTSETXML("/gabdxzp/xxxd/qqdzt","20")
                strcpy(sOriQqdZt,"20");
            }
         }else 
         {/*核心不防重*/
            if (0 == strcmp(sOriQqdZt, "21"))
            {/*重新生成业务流水号*/
                /*业务流水号*/
                memset(sSql, 0x00, sizeof(sSql));
                GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_DXZP_XL,sSql,"业务流水号");
                memset(&st_gab_dxzp_dual, 0x00, sizeof(st_gab_dxzp_dual));
                LOG(LM_STD, Fmtmsg("登记下达信息表->sfxt_xl[%s]", sSql), fpub_GetCompname(lXmlhandle));
                iRet=fdbop_qry_dual(lXmlhandle, &st_gab_dxzp_dual, sSql);
                GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "获取业务流水号");
                snprintf(st_gab_dxzp_xdxx.ywlsh, sizeof(st_gab_dxzp_xdxx.ywlsh), 
                    "08%ld", st_gab_dxzp_dual.nextval);
                
                GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,st_gab_dxzp_xdxx.ywrq,"业务日期");
                strcpy(st_gab_dxzp_xdxx.qqdzt,"20");
            	iRet=fdbop_upd_gab_dxzp_xdxx_ywlsh(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
                GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "更新信息下达表");
                DCICommit();
                COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, "20")
                COMP_SOFTSETXML("/gabdxzp/xxxd/qqdzt","20")
                strcpy(sOriQqdZt,"20");
            }else if( 0 == strcmp(sOriQqdZt, "23") || 0 == strcmp(sOriQqdZt, "33") )
            {
                LOG(LM_STD, Fmtmsg("原交易提交核心超时,核心不防重,请查证后再处理!"), "ERROR");
	            fpub_SetMsg(lXmlhandle, 99999, "原交易提交核心超时,核心不防重,请查证后再处理");
	            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	            return COMPRET_FAIL;
            }
        }
        /*alter by liukq 20160324 END*/
        
    }else if(sCllx[0]=='3')
    {/*要求核心提回,请求单状态务必22-提交成功 或 31-提回失败*/
    	   /*alter by liukq 20160324 BEGIN*/
        if (strcmp(sOriQqdZt, "30") != 0 && strcmp(sOriQqdZt, "23") != 0 && strcmp(sOriQqdZt, "31") != 0 && strcmp(sOriQqdZt, "33") != 0)
        {
	        LOG(LM_STD, Fmtmsg("要求提回核心,状态不符[%s]", sOriQqdZt), "ERROR");
	        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_CHKSTS, MSG_GAB_DXZP_CHKSTS);
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	        return COMPRET_FAIL;
        }
        if(0==strcmp(sHostfcflat,"1"))
        	{
           if(0== strcmp(sOriQqdZt, "31") ||  0 == strcmp(sOriQqdZt, "23") || 0== strcmp(sOriQqdZt, "33") )
           	{
           		/*alter 22-->30 by liukq 20160426  BEGIB*/
           		strcpy(st_gab_dxzp_xdxx.qqdzt,"30");
           		iRet=fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
              GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "更新信息下达表");
              DCICommit();
              COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, "30")
              COMP_SOFTSETXML("/gabdxzp/xxxd/qqdzt","30")
              strcpy(sOriQqdZt,"30");
              /*alter by liukq 20160426  END*/
           	}
         }
         else 
         	{
         		if( 0 == strcmp(sOriQqdZt, "23") || 0 == strcmp(sOriQqdZt, "33") )
         			{
         				 LOG(LM_STD, Fmtmsg("核心不防重提交失败!"), "ERROR");
	               fpub_SetMsg(lXmlhandle, 99999, "核心不防重提交失败");
	               fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	               return COMPRET_FAIL;
           	}
         }
        /*alter by liukq 20160324 END*/
    }else if(sCllx[0]=='4')
    {/*要求反馈前置,请求单状态务必32-提回成功 或41-反馈失败*/
    	  /*add by liukq 20160323 sOriQqdZt=43,add 20160406 sOriQqdZt=31*/
        if (strcmp(sOriQqdZt, "31") != 0 &&strcmp(sOriQqdZt, "40") != 0 && strcmp(sOriQqdZt, "41") != 0 && strcmp(sOriQqdZt, "43") != 0)
        {
	        LOG(LM_STD, Fmtmsg("要求反馈前置,状态不符[%s]", sOriQqdZt), "ERROR");
	        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_CHKSTS, MSG_GAB_DXZP_CHKSTS);
	        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	        return COMPRET_FAIL;
        }
    }else
    {/*其他情况,不做任务检查*/
        
    }
    /*获取新的请求单状态*/
    memset(sNewQqdZt, 0x00, sizeof(sNewQqdZt));
    sNewQqdZt[0]=sCllx[0];
    sNewQqdZt[1]='9';
    /*更新请求单状态*/
    DCIBegin();
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.qqdzt, sNewQqdZt);
    iRet=fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "查询信息下达表");
    DCICommit();
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, st_gab_dxzp_xdxx.qqdzt)
    COMP_SOFTSETXML(XMLNM_SFXT_HOST_REQ_CLLX, sCllx)
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("待处理业务状态检查->处理成功"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_CALLHOST_COMMPROC
 组件名称:调核心后公共处理
 组件功能:调核心后公共处理
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_CALLHOST_COMMPROC(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sYwsqBh[36+1];/*业务申请编号*/
    char sOriQqdZt[2+1];/*请求单状态*/
    char sHxSynMode[1+1];/*核心同异步模式*/
    char sYwlxBm[6+1];/*业务类型编码*/
    char sTableName[4+1];
    char sSbPch[36+1];/*上报批次号*/
    char sMAXTJHXCS[20];/*提交核心最大次数*/
    GAB_DXZP_XDXX st_gab_dxzp_xdxx;/*下达信息表*/
    /*add by liukq 20160331 BEGIN*/
    GAB_DXZP_XDXX st_gab_dxzp_xdxx_tjhxcs;/*下达信息表专用于tjhxcs*/
    /*add by liukq 20160331 END*/
    memset(sYwsqBh, 0x00, sizeof(sYwsqBh));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH, sYwsqBh,"业务申请编号");
    memset(sOriQqdZt, 0x00, sizeof(sOriQqdZt));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QQDZT, sOriQqdZt,"请求单状态");
    memset(sHxSynMode, 0x00, sizeof(sHxSynMode));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_HXSYNFLG, sHxSynMode,"核心同异步模式");
    memset(sSbPch, 0x00, sizeof(sSbPch));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_GAB_DXZP_DTCX_RESP_SBPCH, sSbPch,"上报批次号");
    LOG(LM_STD, Fmtmsg("调核心后公共处理->ywsqbh[%s],sOriQqdZt[%s],sHxSynMode[%s],sSbPch[%s]", 
        sYwsqBh, sOriQqdZt, sHxSynMode, sSbPch), fpub_GetCompname(lXmlhandle));
    /*获取核心响应结果*/
    memset(&st_gab_dxzp_xdxx, 0x00, sizeof(st_gab_dxzp_xdxx));
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.ywsqbh, sYwsqBh)
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.qqdzt, sOriQqdZt);
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.sbpch, sSbPch);
    /*add by liukq 20160408 BEGIN*/
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_YwyDm, st_gab_dxzp_xdxx.ywydm,"业务应答码");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_sYwyDxx, st_gab_dxzp_xdxx.ywydxx,"业务应答信息");
    trim(st_gab_dxzp_xdxx.ywydm);
    trim( st_gab_dxzp_xdxx.ywydxx);
    /*add by liukq 20160408 END*/
    /*add by liukq 20160331 BEGIN*/
    memset(&st_gab_dxzp_xdxx_tjhxcs, 0x00, sizeof(st_gab_dxzp_xdxx_tjhxcs));
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx_tjhxcs.ywsqbh, sYwsqBh)
    /*add by liukq 20160331 END*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_RESPCODE, st_gab_dxzp_xdxx.respcode,"响应码");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_RESPMSG, st_gab_dxzp_xdxx.respmsg,"响应信息");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_HOST_RESP_ZJRQ, st_gab_dxzp_xdxx.zjrq,"主机日期");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_HOST_RESP_ZJLSH, st_gab_dxzp_xdxx.zjlsh,"主机流水号");
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_DZXH, st_gab_dxzp_xdxx.dzxh,"冻止序号");
    
    /*add by liukq 20160328*/
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSDATE,st_gab_dxzp_xdxx.clrq,"处理日期");
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SYSTIME,st_gab_dxzp_xdxx.clsj,"处理时间");
    /*add by liukq 20160328*/
    st_gab_dxzp_xdxx.zxjg[0]='0';/*执行结果 0-不成功*/
    if(strcmp(st_gab_dxzp_xdxx.respcode, "00000") == 0)
    {/*成功*/
        st_gab_dxzp_xdxx.qqdzt[0]='4';
        st_gab_dxzp_xdxx.qqdzt[1]='0';
        st_gab_dxzp_xdxx.zxjg[0]='1';/*执行结果 1-成功*/
        if (sHxSynMode[0] == '1')
        {/*核心同异步模式 0-同步 ,则请求单状态强制为3-提回*/
          st_gab_dxzp_xdxx.qqdzt[0]='3';
         }
    }else if (strcmp(st_gab_dxzp_xdxx.respcode, "99999") == 0 || strcmp(st_gab_dxzp_xdxx.respcode, "98501") == 0)
    {/*超时*/
    	  /*st_gab_dxzp_xdxx.qqdzt[1]='3';*/
    	  /*add by liukq 20160331 BEGIN*/
    	  if (sHxSynMode[0] == '0')
        {/*核心同异步模式 0-同步 ,则请求单状态强制为3-提回*/
          st_gab_dxzp_xdxx.qqdzt[0]='3';
         }
    	  iRet=fdbop_qry_gab_dxzp_xdxx(lXmlhandle, &st_gab_dxzp_xdxx_tjhxcs);
        GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "查询信息下达表");
        memset(sMAXTJHXCS,0x00,sizeof(sMAXTJHXCS));
        GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/maxtjhxcs", sMAXTJHXCS,"提交核心最大次数");
        LOG(LM_STD,Fmtmsg("tjhxcs[%d],sMAXTJHXCS[%s]",st_gab_dxzp_xdxx_tjhxcs.tjhxcs,sMAXTJHXCS),"DEBUG");
        if(st_gab_dxzp_xdxx_tjhxcs.tjhxcs<atoi(sMAXTJHXCS) || 0==strcmp(st_gab_dxzp_xdxx_tjhxcs.jybm,"100305"))
        {
          st_gab_dxzp_xdxx.qqdzt[1]='3';
        }
        else
        {
        	st_gab_dxzp_xdxx.qqdzt[1]='1';
        }
        /*add by liukq 20160331 END*/
    }else
    {/*失败*/
    	  if (sHxSynMode[0] == '0')
        {/*核心同异步模式 0-同步 ,则请求单状态强制为3-提回*/
          st_gab_dxzp_xdxx.qqdzt[0]='3';
         }
        st_gab_dxzp_xdxx.qqdzt[1]='1';
    }
    COMP_SOFTSETXML("/host/resp/zjjg", st_gab_dxzp_xdxx.zxjg);
    
    /*获取分表名*/
    memset(sYwlxBm, 0x00, sizeof(sYwlxBm));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWLXBM, sYwlxBm,"业务类型编码");
    switch(atoi(sYwlxBm))
    {
        case 100101:/*止付*/
        case 100103:/*止付解除*/
        case 100105:/*止付延期*/
            GAB_DXZP_PSTRCOPY(sTableName, "jjzf");
            break;
        case 100201:/*冻结*/
        case 100203:/*冻结解除*/
        case 100205:/*冻结延期*/
            GAB_DXZP_PSTRCOPY(sTableName, "djxj");
            break;
        case 100301:/*交易明细查询*/
            GAB_DXZP_PSTRCOPY(sTableName, "jymx");
            break;
        case 100303:/*主体查询*/
            GAB_DXZP_PSTRCOPY(sTableName, "ztcx");
            break;
        case 100305:/*动态查询*/
        case 100307:/*动态解除查询*/
            GAB_DXZP_PSTRCOPY(sTableName, "dtcx");
            break;
        case 100309:/*客户全账号查询*/
            GAB_DXZP_PSTRCOPY(sTableName, "qhcx");
            break;
        default:
            break;
    }
    LOG(LM_STD, Fmtmsg("调核心后公共处理->sNewQqdZt[%s],sTableName[%s]", 
        st_gab_dxzp_xdxx.qqdzt, sTableName), fpub_GetCompname(lXmlhandle));
    
    
    
    DCIBegin();
    iRet=fdbop_upd_gab_dxzp_xdxx_aftCallHost(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "更新信息下达表");
    iRet=fdbop_upd_gab_dxzp_busi(lXmlhandle, &st_gab_dxzp_xdxx, sTableName);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "更新业务表");
    DCICommit();
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, st_gab_dxzp_xdxx.qqdzt)
    COMP_SOFTSETXML(XMLNM_SFXT_HOST_RESP_ZXJG, st_gab_dxzp_xdxx.zxjg)
    //if (sHxSynMode[0] == '1' && strcmp(st_gab_dxzp_xdxx.qqdzt, "21") == 0)
    if (sHxSynMode[0] == '1' && strcmp(st_gab_dxzp_xdxx.qqdzt, "30") == 0)
    {/*异步且提交核心成功,则人为退出*/
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
        LOG(LM_STD, Fmtmsg("调核心后公共处理->异步且提交核心成功,人为停下来"), fpub_GetCompname(lXmlhandle));
        //fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_BATCH_BREAK, MSG_GAB_DXZP_BATCH_BREAK);
        return COMPSTATUS_SUCC;
    }
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("调核心后公共处理->处理成功"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_UPDSTS
 组件名称:更新请求单状态
 组件功能:更新请求单状态
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_UPDSTS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    char sYwsqBh[36+1];/*业务申请编号*/
    char sOriQqdZt[2+1];/*请求单状态*/
    char sNewQqdZt[2+1];/*请求单状态*/
    char sCllx[1+1];/*处理类型*/
    char sYwlxBm[6+1];/*业务类型编码*/
    char sSuccFail[16+1];
    GAB_DXZP_XDXX st_gab_dxzp_xdxx;/*下达信息表*/
    
    memset(sSuccFail, 0, sizeof(sSuccFail));
    COMP_GETPARSEPARAS(1,sSuccFail,"成失标志")
    
    memset(sNewQqdZt, 0, sizeof(sNewQqdZt));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"请求单状态")
    
    GAB_DXZP_PSTRCOPY(sNewQqdZt, sBuf);
    memset(sYwsqBh, 0x00, sizeof(sYwsqBh));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_YWSQBH, sYwsqBh,"业务申请编号");
   
    memset(sOriQqdZt, 0x00, sizeof(sOriQqdZt));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_QQDZT, sOriQqdZt,"请求单状态");
   
    /*处理类型为1-落地时，默认为落地实时提交核心*/
    memset(sCllx, 0x00, sizeof(sCllx));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_SFXT_HOST_REQ_CLLX, sCllx, "处理类型");

    LOG(LM_STD, Fmtmsg("更新请求单状态->ywsqbh[%s],sOriQqdZt[%s],sSuccFail[%s],sNewQqdZt[%s]", 
        sYwsqBh, sOriQqdZt, sSuccFail, sNewQqdZt), fpub_GetCompname(lXmlhandle));
    if (sSuccFail[0] != '\0')
    {/*传进成失标志*/
        GAB_DXZP_PSTRCOPY(sNewQqdZt, sOriQqdZt);
        sNewQqdZt[1] = sSuccFail[0];
    }else
    {/*否则传进新请求单状态*/
       if (sCllx[0] == '3')
        {/*若为3-核心提回,则新状态也应保持一致*/
            sNewQqdZt[0] = sCllx[0];
        }
    }
    
    /*更新请求单状态*/
    memset(&st_gab_dxzp_xdxx, 0x00, sizeof(st_gab_dxzp_xdxx));
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.ywsqbh, sYwsqBh);
    GAB_DXZP_PSTRCOPY(st_gab_dxzp_xdxx.qqdzt, sNewQqdZt);
    DCIBegin();
    iRet=fdbop_upd_gab_dxzp_xdxx_qqdzt(lXmlhandle, &st_gab_dxzp_xdxx, sOriQqdZt);
    GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "查询信息下达表");
    DCICommit();
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_QQDZT, st_gab_dxzp_xdxx.qqdzt)
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("更新请求单状态->处理成功"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_AUTOPROC
组件名称: GAB_DXZP_AUTOPROC
组件功能: 公安部电信诈骗自动处理
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    
输出：  
0   成功
-1  失败
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_945118(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sSysDate[8+1];
    char sSysTime[6+1];
    char errmsg[256];
    char sProcKind[2+1];/*1-正常+失败,2-统一兜底,3-动态查询*/
    char sProcDate[8+1];
    char sBusiTable[64+1];
    int  iAutoProcs=10;/*自动任务处理笔数*/
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    char sHxSynMode[1+1];
    CURSOR cur;
    GAB_DXZP_AUTOPROC gab_dxzp_autoproc;
    
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHKMIN(1);
    memset(sProcKind, 0x00, sizeof(sProcKind));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "处理类型"); 
    pstrcopy(sProcKind, sBuf, sizeof(sProcKind));

    memset(sSysDate, 0x00, sizeof(sSysDate));
    COMP_SOFTGETXML(XMLNM_SYSDATE, sSysDate)
    memset(sSysTime, 0x00, sizeof(sSysTime));
    COMP_SOFTGETXML(XMLNM_SYSTIME, sSysTime)
    
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_DXZP_AUTOPROCS, sBuf)
    if ( sBuf[0] != '\0')
    {
        iAutoProcs = atoi(sBuf);
    }
    /*add by liukq 20160331 BEGIN*/
    memset(sHxSynMode, 0x00, sizeof(sHxSynMode));
    GAB_DXZP_GETXMLSTR_NULL(XMLNM_DXZP_HXSYNFLG, sHxSynMode,"核心同异步模式");
    /*add by liukq 20160331 END*/
    
    LOG(LM_STD,Fmtmsg("公安部电信诈骗自动处理执行开始[%d]",iAutoProcs),fpub_GetCompname(lXmlhandle));
    
    /* 查询需要处理的任务 */
    memset(sSql, 0x00, sizeof(sSql));
    /*add jybm !='100305' by liukq 20160316  add qqdzt in 23,33 20160331 add qqdzt in 31 20160406 begin */
    /*alter by liukq 20160504 将正常业务和超时业务分开 BEGIN*/
    if (sProcKind[0] == '2')
    {
        snprintf(sSql,sizeof(sSql),"SELECT ywsqbh,jjcd,qqdzt,'' FROM gab_dxzp_xdxx \
            WHERE qqdzt in ('20', '30', '31','40') and jybm !='100305' ORDER BY jjcd desc, ywsqbh asc ");
    }else if (sProcKind[0] == '3')
    {
        snprintf(sSql,sizeof(sSql),"SELECT ywsqbh,jjcd,qqdzt,'' FROM gab_dxzp_xdxx \
            WHERE qqdzt in ('23','33') and jybm !='100305' ORDER BY jjcd desc, ywsqbh asc ");
    }else if (sProcKind[0] == '4')
    {
        snprintf(sSql,sizeof(sSql),"SELECT ywsqbh,jjcd,qqdzt,'' FROM gab_dxzp_xdxx \
            WHERE qqdzt in ('43') and jybm !='100305' ORDER BY jjcd desc, ywsqbh asc ");
    }
    else
    {
        snprintf(sSql,sizeof(sSql),"SELECT ywsqbh,jjcd,qqdzt,'' FROM gab_dxzp_xdxx \
            WHERE ( fkddrq <'%s' or ( fkddrq ='%s' and fkddsj < '%s') ) and qqdzt in ('20', '30','31','40')  and jybm !='100305' ORDER BY jjcd desc, ywsqbh asc ", 
            sSysDate, sSysDate, sSysTime );
    }
    /*alter by liukq 20160504 将正常业务和超时业务分开 END*/
    /*add jybm !='100305' by liukq 20160316 end */
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    for ( i=1; i<=iAutoProcs; i++)
    {
        memset(&gab_dxzp_autoproc, 0x00, sizeof(gab_dxzp_autoproc));
        iRet = DBFetch(cur, SD_GAB_DXZP_AUTOPROC, NUMELE(SD_GAB_DXZP_AUTOPROC), &gab_dxzp_autoproc, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        
        /* 公共交易信息赋值 */
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_YWSQBH, gab_dxzp_autoproc.ywsqbh);/*业务申请编号*/
        /*alter by liukq 20160316 begin*/
        memset(sProcKind,0x00,sizeof(sProcKind));
        if(0 == strcmp(gab_dxzp_autoproc.qqdzt,"20") || 0 == strcmp(gab_dxzp_autoproc.qqdzt,"23") ||  0 == strcmp(gab_dxzp_autoproc.qqdzt,"33"))
        	{
        		if( 0 == strcmp(gab_dxzp_autoproc.qqdzt,"33") || 0 == strcmp(gab_dxzp_autoproc.qqdzt,"23"))
        			{
        		   if (sHxSynMode[0] == '0')
                 {/*核心同异步模式 0-同步 */
        		       strcpy(sProcKind,"2");
        	       }
        	      else
        	      	{
        	      		strcpy(sProcKind,"3");
        	      	}
        	    }
        	   else
        	    {
        	    	strcpy(sProcKind,"2");
        	    }
        	}
        if(0 == strcmp(gab_dxzp_autoproc.qqdzt,"30"))
        	{
        		strcpy(sProcKind,"3");
        	}
        if(0 == strcmp(gab_dxzp_autoproc.qqdzt,"31") || 0 == strcmp(gab_dxzp_autoproc.qqdzt,"40") || 0 == strcmp(gab_dxzp_autoproc.qqdzt,"43"))
        	{
        		strcpy(sProcKind,"4");
        	}
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_CLLX,sProcKind);/*处理类型*/
        /*alter by liukq 20160316 begin*/
        LOG(LM_STD,Fmtmsg("即将调用待处理业务流程flow_gabdxzp_945117处理,ywsqbh[%s],jjcd[%s],qqdzt[%s]",
            gab_dxzp_autoproc.ywsqbh, gab_dxzp_autoproc.jjcd, gab_dxzp_autoproc.qqdzt),"INFO");
        /* 调用待处理业务入口 */
        if(fpub_CallFlow(lXmlhandle,"subflow_gabdxzp_945117")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("调用待处理业务流程flow_gabdxzp_945117[%s]失败",
                gab_dxzp_autoproc.ywsqbh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("执行待处理业务流程失败"));
            return COMPRET_FAIL ;
        }
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_STD,Fmtmsg("公安部电信诈骗自动处理执行结束,共处理[%d]条业务", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"公安部电信诈骗自动处理执行结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_945118_DTCX
组件名称: GAB_DXZP_945118_DTCX
组件功能: 公安部电信诈骗动态查询
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    
输出：  
0   成功
-1  失败
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_945118_DTCX(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sSysDate[8+1];
    char sSysTime[6+1];
    char sCurDateTime[14+1];
    char errmsg[256];
    char sProcKind[2+1];/*1-正常+失败,2-统一兜底,32-动态查询核心取数,34-动态查询反馈前置*/
    int i=1;
    int iRet=-1;
    
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHKMIN(1);
    memset(sProcKind, 0x00, sizeof(sProcKind));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "处理类型"); 
    pstrcopy(sProcKind, sBuf, sizeof(sProcKind));

    memset(sSysDate, 0x00, sizeof(sSysDate));
    COMP_SOFTGETXML(XMLNM_SYSDATE, sSysDate)
    memset(sSysTime, 0x00, sizeof(sSysTime));
    COMP_SOFTGETXML(XMLNM_SYSTIME, sSysTime)
    memset(sCurDateTime, 0x00, sizeof(sCurDateTime));
    snprintf(sCurDateTime, sizeof(sCurDateTime),"%s%s", sSysDate, sSysTime);
    
    LOG(LM_STD,Fmtmsg("公安部电信诈骗自动处理执行开始"),fpub_GetCompname(lXmlhandle));
    
    /* 查询需要处理的任务 */
    memset(sSql, 0x00, sizeof(sSql));
    if (strcmp(sProcKind, "32") == 0 )
    {/*核心取数*/
        snprintf(sSql,sizeof(sSql),"SELECT a.ywsqbh,a.jjcd,a.qqdzt,b.zh FROM gab_dxzp_dtcx b, gab_dxzp_xdxx a \
            WHERE a.ywsqbh = b.ywsqbh and b.zxjzrq > '%s' and b.dtml='1' and a.qqdzt != '40' ORDER BY ywsqbh asc ", sCurDateTime );
        LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
        iRet = ffunc_dxzp_945118_DTCX_hxqs(lXmlhandle, sSql, sCurDateTime);
    }else
    {/*反馈前置*/
        COMP_SOFTSETXML("/gabdxzp/dtcxplfk", "1")/*动态查询批量反馈*/
        snprintf(sSql,sizeof(sSql),"SELECT a.ywsqbh,a.jjcd,a.qqdzt,b.zh FROM gab_dxzp_dtcx b, gab_dxzp_xdxx a \
            WHERE a.ywsqbh = b.ywsqbh and b.zxjzrq > '%s' and b.dtml='1' and a.qqdzt = '40' ORDER BY ywsqbh asc ", sCurDateTime );
        LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
        iRet = ffunc_dxzp_945118_DTCX_fkqz(lXmlhandle, sSql, sCurDateTime);
    }
    
    LOG(LM_STD,Fmtmsg("公安部电信诈骗自动处理执行结束"), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"公安部电信诈骗自动处理执行结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}


/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_945124
组件名称: GAB_DXZP_945124
组件功能: 电信诈骗动态查询核心推送
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    
输出：  
0   成功
-1  失败
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_945124(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sSysDate[8+1];
    char sSysTime[6+1];
    char sCurDateTime[14+1];
    char sZh[32+1];
    char errmsg[256];
    int i=1;
    int iRet=-1;
    
    fpub_InitSoComp(lXmlhandle);

    COMP_PARACOUNTCHKMIN(1);
    memset(sZh, 0x00, sizeof(sZh));
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "账号"); 
    pstrcopy(sZh, sBuf, sizeof(sZh));

    memset(sSysDate, 0x00, sizeof(sSysDate));
    COMP_SOFTGETXML(XMLNM_SYSDATE, sSysDate)
    memset(sSysTime, 0x00, sizeof(sSysTime));
    COMP_SOFTGETXML(XMLNM_SYSTIME, sSysTime)
    memset(sCurDateTime, 0x00, sizeof(sCurDateTime));
    snprintf(sCurDateTime, sizeof(sCurDateTime),"%s%s", sSysDate, sSysTime);
    
    LOG(LM_STD,Fmtmsg("公安部电信诈骗动态查询实时推送反馈执行开始"),fpub_GetCompname(lXmlhandle));
    
    /* 查询需要处理的任务 */
    memset(sSql, 0x00, sizeof(sSql));
    /*反馈前置*/
    COMP_SOFTSETXML("/gabdxzp/dtcxplfk", "1")/*动态查询批量反馈*/
    snprintf(sSql,sizeof(sSql),"SELECT a.ywsqbh,a.jjcd,a.qqdzt,b.zh FROM gab_dxzp_dtcx b, gab_dxzp_xdxx a \
        WHERE a.ywsqbh = b.ywsqbh and b.zxjzrq > '%s' and b.dtml='1' and b.zh = '%s' ORDER BY ywsqbh asc ", sCurDateTime, sZh );
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    iRet = ffunc_dxzp_DTCX_sstsfk(lXmlhandle, sSql, sCurDateTime);

    LOG(LM_STD,Fmtmsg("公安部电信诈骗动态查询实时推送反馈执行结束"), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"公安部电信诈骗动态查询实时推送反馈执行结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_COMMQZJ
组件名称:与前置机通讯
组件功能:与前置机通讯
组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

组件结果状态:
  结果状态码         结果说明
  缺省

主要操作库表:
  表名                       操作

处理流程:

项 目 组: 
程 序 员:屠秋龙 
发布日期:2016-03-10
修改日期:
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_COMMQZJ(HXMLTREE lXmlhandle)
{
    int iParas;
    int iSock;                          /*套接字*/
    uint32_t lCommbufLen=0;         /*通讯区长度*/
    uint32_t lCommbufLen2=0;                /*通讯区长度*/
    char sBuf[256];             /*参数内容*/
    char sIp[16+1];                 /*IP*/
    int iPort;                          /*端口*/
    int iOuttime;                   /*超时时间*/
    char sCommBufLen[8+1];  /*通讯区长度*/
    char *pCommBuf=NULL;    /*通讯区*/
    int iRet=-1;
    
    /*1-组件开始*/
    fpub_InitSoComp(lXmlhandle);

    /*2-获取参数*/
    COMP_PARACOUNTCHK(3)
    memset(sBuf, 0x00, sizeof ( sBuf));
    COMP_GETPARSEPARAS(1, sBuf, "服务器IP");
    pstrcopy(sIp, sBuf, sizeof(sIp));

    memset(sBuf, 0x00, sizeof ( sBuf));
    COMP_GETPARSEPARAS(2, sBuf, "服务器端口");
    iPort = atoi(sBuf);

    memset(sBuf, 0x00, sizeof ( sBuf));
    COMP_GETPARSEPARAS(3, sBuf, "超时时间");
    iOuttime = atoi(sBuf);

    LOG(LM_STD, Fmtmsg("与前置机通讯执行开始[%s][%d][%d]",
        sIp, iPort, iOuttime), fpub_GetCompname(lXmlhandle));

    lCommbufLen = xml_GetBinElementLen(lXmlhandle, "/commbuf");
    if (lCommbufLen <= 0 )
    {
        LOG(LM_STD,Fmtmsg("/commbuf长度为[%s],请确认", lCommbufLen ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /* 根据获取到的长度申请内存 */
    pCommBuf = (char *)malloc( lCommbufLen+1 );
    if ( pCommBuf == NULL )
    {
        LOG(LM_STD,Fmtmsg("动态申请commbuf内存失败" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*2-组通讯区内容*/
    memset(pCommBuf, 0x00, lCommbufLen+1);
    if(0 > (iRet = xml_RelGetBinElement(lXmlhandle, "/commbuf", pCommBuf, lCommbufLen+1)))
    {
        LOG(LM_STD, Fmtmsg("取前置机通讯区错误iRet=[%d]", iRet), "DEBUG");
        /*alter by liukq 20160427 BEGIN
        fpub_SetMsg(lXmlhandle, 99999, "与前置机通讯失败,获取通讯区错误");
        */
        /*alter by liukq 20160427 BEGIN*/
        fpub_SetMsg(lXmlhandle, 98601, "与前置机通讯失败,获取通讯区错误");
        /*alter by liukq 20160427 END*/
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*去掉业务类型编码*/
    /*alter by liukq 20160427 BEGIN
    lCommbufLen -= 6;
    memmove(pCommBuf, pCommBuf+6, lCommbufLen);
    pCommBuf[lCommbufLen] = '\0'; END*/
    LOG(LM_STD, Fmtmsg("lCommbufLen=[%d][%s]", lCommbufLen, pCommBuf), fpub_GetCompname(lXmlhandle));
    /*3-与服务端建立连接*/
    itcp_sethead(1);
    itcp_setenv(iPort, &iSock);
    if(0 > (iRet = itcp_calln(sIp,3)))
    {
        free(pCommBuf);pCommBuf=NULL;
        LOG(LM_STD, Fmtmsg("与前置机建立连接错误iRet=[%d]", iRet), "DEBUG");
        /*alter by liukq 20160427 BEGIN
        fpub_SetMsg(lXmlhandle, 99999, "与前置机通讯失败,建立连接错误");
        */
        /*alter by liukq 20160427 BEGIN*/
        fpub_SetMsg(lXmlhandle, 98601, "与前置机通讯失败,建立连接错误"); 
        /*alter by liukq 20160427 END*/
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*3-发送通讯区长度*/
    LOG(LM_STD, Fmtmsg("发送前置机通讯区长度=[%d]", lCommbufLen+4), fpub_GetCompname(lXmlhandle));
    lCommbufLen2 = htonl(lCommbufLen);
    if(0 > (iRet = itcp_send((char *)&lCommbufLen2, 4, iOuttime)))
    {
        itcp_clear();
        free(pCommBuf);pCommBuf=NULL;
        LOG(LM_STD, Fmtmsg("发送前置机通讯区长度错误iRet=[%d]", iRet), fpub_GetCompname(lXmlhandle));
        fpub_SetMsg(lXmlhandle, 99999, "与前置机通讯失败,发送通讯区长度错误");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*5-发送通讯区*/
    if(0 > (iRet = itcp_send(pCommBuf, lCommbufLen, iOuttime)))
    {
        itcp_clear();
        free(pCommBuf);pCommBuf=NULL;
        LOG(LM_STD, Fmtmsg("发送前置机通讯区错误iRet=[%d]", iRet), "DEBUG");
        fpub_SetMsg(lXmlhandle, 99999, "与前置机通讯失败,发送通讯区错误");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    free(pCommBuf);pCommBuf=NULL;
    /*6-接收通讯区长度*/
    lCommbufLen2 = 0;
    if(0 > (iRet = itcp_recv((char *)&lCommbufLen2, 4, iOuttime)))
    {
        LOG(LM_STD, Fmtmsg("接收前置机通讯区长度错误iRet=[%d]", iRet), "DEBUG");
        itcp_clear();
        fpub_SetMsg(lXmlhandle, 99999, "与前置机通讯超时,接收通讯区长度错误");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    lCommbufLen = ntohl(lCommbufLen2);
    LOG(LM_STD, Fmtmsg("接收前置机响应报文长度=[%ld]", lCommbufLen), fpub_GetCompname(lXmlhandle));
    /* 根据获取到的长度申请内存 */
    pCommBuf = (char *)malloc( lCommbufLen+1 );
    if ( pCommBuf == NULL )
    {
        LOG(LM_STD,Fmtmsg("动态申请commbuf内存失败" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    memset(pCommBuf, 0x00, lCommbufLen+1);
    /*7-接收通讯区*/
    if(0 > (iRet = itcp_recv(pCommBuf, lCommbufLen, iOuttime)))
    {
        itcp_clear();
        free(pCommBuf);pCommBuf=NULL;
        LOG(LM_STD, Fmtmsg("接收通讯区错误iRet=[%d]", iRet), "DEBUG");
        fpub_SetMsg(lXmlhandle, 99999, "与前置机通讯超时,接收通讯区错误");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD, Fmtmsg("接收前置机响应报文=[%d][%s]", lCommbufLen, pCommBuf), fpub_GetCompname(lXmlhandle));
    itcp_clear();
    
    /*9-写回commbuf*/
    if(0 > (iRet = xml_RelSetBinElement(lXmlhandle, "/commbuf", pCommBuf, lCommbufLen)))
    {
        free(pCommBuf);pCommBuf=NULL;
        LOG(LM_STD, Fmtmsg("写前置机通讯区错误iRet=[%d]", iRet), "DEBUG");
        /*alter by liukq 20160427 BEGIN
        fpub_SetMsg(lXmlhandle, 99999, "与前置机通讯超时,写通讯区错误");
        */
        /*alter by liukq 20160427 BEGIN*/
        fpub_SetMsg(lXmlhandle, 98601, "与前置机通讯失败,写通讯区错误");
        /*alter by liukq 20160427 END*/
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    free(pCommBuf);pCommBuf=NULL;
    /*14-组件结束*/
    LOG(LM_STD,Fmtmsg("与前置机通讯执行结束"),fpub_GetCompname(lXmlhandle));
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_945122
组件名称: GAB_DXZP_945122
组件功能: 公安部电信诈骗批量信息上报
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    
输出：  
0   成功
-1  失败
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_945122(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sSbPch[36+1];
    char sSbJydm[6+1];
    char sJybm[6+1];
    char errmsg[256];
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    CURSOR cur;
    GAB_DXZP_SBXX_PLZT gab_dxzp_sbxx_plzt;
    
    fpub_InitSoComp(lXmlhandle);
    
    memset(sSbPch, 0x00, sizeof(sSbPch));
    GAB_DXZP_GETXMLSTR_NOTNULL("/gabdxzp/sbpch",sSbPch,"上报批次号");
    
    LOG(LM_STD,Fmtmsg("批量信息上报执行开始[%s],sbjydm[%s],jybm[%s]",
        sSbPch, sSbJydm, sJybm),fpub_GetCompname(lXmlhandle));
    COMP_SOFTSETXML("/gabdxzp/YorNbatch", "1");
    /* 查询需要处理的任务 */
    memset(sSql, 0x00, sizeof(sSql));
    /*add sbzt=3超时上报 by liukq 20160324 BEGIN*/
    snprintf(sSql,sizeof(sSql),"SELECT * FROM gab_dxzp_sbxx_plzt WHERE sbpch='%s' and sbzt in ('0', '2','3')", sSbPch);
    /*add by liukq 20160324 END*/
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    for ( i=1; ; i++)
    {
        memset(&gab_dxzp_sbxx_plzt, 0x00, sizeof(gab_dxzp_sbxx_plzt));
        iRet = DBFetch(cur, SD_GAB_DXZP_SBXX_PLZT, NUMELE(SD_GAB_DXZP_SBXX_PLZT), &gab_dxzp_sbxx_plzt, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        #if 0
        memset(sJybm, 0x00, sizeof(sJybm));
        if (strcmp(gab_dxzp_sbxx_plzt.sbjydm, "945111") == 0 )
        {/*案件举报*/
            strcpy(sJybm, "100401");
        }else if (strcmp(gab_dxzp_sbxx_plzt.sbjydm, "945112") == 0 )
        {/*异常开卡*/
            strcpy(sJybm, "100402");
        }else if (strcmp(gab_dxzp_sbxx_plzt.sbjydm, "945113") == 0 )
        {/*涉案账户*/
            strcpy(sJybm, "100403");
        }else if (strcmp(gab_dxzp_sbxx_plzt.sbjydm, "945114") == 0 )
        {/*异常事件*/
            strcpy(sJybm, "100404");
        }
        #endif
        /* 公共交易信息赋值 */
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_SBPCXH, itoa(gab_dxzp_sbxx_plzt.sbpcxh));/*上报批次序号*/
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_SBZT, gab_dxzp_sbxx_plzt.sbzt);/*上报状态*/
        COMP_SOFTSETXML(XMLNM_GAB_DXZP_SBJYDM, gab_dxzp_sbxx_plzt.sbjydm);/*上报交易代码*/
        LOG(LM_STD,Fmtmsg("即将调用批量上报子流程subflow_gabdxzp_945122处理,sbpch[%s],sbpcxh[%d],sbzt[%s],sbjydm[%s]",
            gab_dxzp_sbxx_plzt.sbpch, gab_dxzp_sbxx_plzt.sbpcxh, gab_dxzp_sbxx_plzt.sbzt,
            gab_dxzp_sbxx_plzt.sbjydm),"INFO");
        /* 调用待处理业务入口 */
        if(fpub_CallFlow(lXmlhandle,"subflow_gabdxzp_945122")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("调用批量上报子流程subflow_gabdxzp_945122[%s-%d]失败",
                gab_dxzp_sbxx_plzt.sbpch, gab_dxzp_sbxx_plzt.sbpcxh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("执行批量上报子流程失败"));
            return COMPRET_FAIL ;
        }
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("电信诈骗批量信息上报执行结束,共处理[%d]条业务", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"电信诈骗批量信息上报执行结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}


/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_945125
组件名称: GAB_DXZP_945125
组件功能: 司法查控超时查证
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    
输出：  
0   成功
-1  失败
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_945125(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sHxFcBz[1+1];/*核心防重标志0-不防重,1-防重*/
    char sSbJydm[6+1];
    char sJybm[6+1];
    char errmsg[256];
    int i=1;
    int iRet=-1;
    char sErrmsg[1000];
    CURSOR cur;
    SFCK_TIMEOUT sfck_timeout;
    
    fpub_InitSoComp(lXmlhandle);
    
    memset(sHxFcBz, 0x00, sizeof(sHxFcBz));
    COMP_SOFTGETXML(XMLNM_SFXT_HXFCBZ, sHxFcBz)
    
    LOG(LM_STD,Fmtmsg("司法查控超时查证执行开始[%s]",sHxFcBz),fpub_GetCompname(lXmlhandle));
    if (sHxFcBz[0] != '0')
    {/*0-不防,需自动上核心查证状态*/
        LOG(LM_STD,Fmtmsg("司法查控,核心防重,可重发交易处理,跳过"),"INFO");
        fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"司法查控,核心防重,可重发交易处理,跳过");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return COMPRET_SUCC;
    }
    
    /* 查询需要处理的任务 */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"SELECT * FROM sfck_timeout WHERE 1=1");
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    for ( i=1; ; i++)
    {
        memset(&sfck_timeout, 0x00, sizeof(sfck_timeout));
        iRet = DBFetch(cur, SD_SFCK_TIMEOUT, NUMELE(SD_SFCK_TIMEOUT), &sfck_timeout, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }

        /* 公共交易信息赋值 */
        COMP_SOFTSETXML("/sfck/tmout/xtbh", sfck_timeout.xtbh);/*系统编号*/
        COMP_SOFTSETXML("/sfck/tmout/ywbm", sfck_timeout.ywbm);/*业务表名*/
        COMP_SOFTSETXML("/sfck/tmout/ywsqbh", sfck_timeout.ywsqbh);/*业务申请编号*/
        COMP_SOFTSETXML("/sfck/tmout/ywrq", sfck_timeout.ywrq);/*业务日期*/
        COMP_SOFTSETXML("/sfck/tmout/ywlsh", sfck_timeout.ywlsh);/*业务流水号*/
        COMP_SOFTSETXML("/sfck/tmout/qqdzt", sfck_timeout.qqdzt);/*请求单状态*/
        LOG(LM_STD,Fmtmsg("即将调用超时查证子流程subflow_gabdxzp_945125处理,xtbh[%s],ywsqbh[%s],ywrq[%s],ywlsh[%s]",
            sfck_timeout.xtbh, sfck_timeout.ywsqbh, sfck_timeout.ywrq, sfck_timeout.ywlsh),"INFO");
        /* 调用待处理业务入口 */
        if(fpub_CallFlow(lXmlhandle,"subflow_gabdxzp_945125")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("调用批量上报子流程subflow_gabdxzp_945125[%s]失败",
                sfck_timeout.ywsqbh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("执行超时查证子流程失败"));
            return COMPRET_FAIL ;
        }
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    LOG(LM_STD,Fmtmsg("司法查控超时查证执行结束,共处理[%d]条业务", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"司法查控超时查证执行结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}


/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_HHMD_INS
组件名称: GAB_DXZP_HHMD_INS
组件功能: 登记公安部电信诈骗会黑名单
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    
输出：  
0   成功
-1  失败
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/

IRESULT GAB_DXZP_HHMD_INS(HXMLTREE lXmlhandle)
{
  
    char sbuf[1024+1];
    int  iParas;
    int  iRet = -1;
    int  iRet1= -1;
    char szFilePath[255];
    char sFlag[20];
    char sHhLevel[40];
    FILE *fp=NULL;
    GAB_DXZP_HHMD st_gab_dxzp_hhmd;
    
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHK(2)
    memset(szFilePath, 0x00, sizeof(szFilePath));
    COMP_GETPARSEPARAS(1, szFilePath, "灰黑名单文件路径");
    COMP_GETPARSEPARAS(2, sHhLevel, "名单级别");
    trim(szFilePath);
    trim(sHhLevel);
	  LOG(LM_STD,Fmtmsg("  -->灰黑名单文件路径[%s]",szFilePath),"INFO")
	  fp = fopen( szFilePath, "r" );
	  if ( fp == NULL )
	     {
	      	LOG(LM_STD,Fmtmsg("打开文件失败,file=[%s]",szFilePath),fpub_GetCompname(lXmlhandle));
	      	fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg("打开文件失败"));
	      	fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	      	return COMPRET_FAIL;
	     }
	     
	  DCIBegin();
    memset(sbuf, 0x00, sizeof(sbuf));
	  while (fgets(sbuf, 1024, fp) != NULL)
	   {
		     trim(sbuf);
		     if (0 == strlen(sbuf))
			   continue;
			   
			   memset(&st_gab_dxzp_hhmd,0x00,sizeof(st_gab_dxzp_hhmd));
			   
			   /*名单键值*/
			   GetItemValueT(sbuf, "$" ,st_gab_dxzp_hhmd.mdjz, 1); 
		     trim(st_gab_dxzp_hhmd.mdjz); 
			   /*操作标识*/
		     memset(sFlag,0x00,sizeof(sFlag));
		     GetItemValueT(sbuf, "$" ,sFlag, 2); 
		     trim(sFlag); 
		     
         if(0 == strcmp(sFlag,"+"))
		     	{
		     		 LOG(LM_STD,Fmtmsg("开始查询-->灰黑名单表,mdjz[%s]",st_gab_dxzp_hhmd.mdjz),fpub_GetCompname(lXmlhandle));   
		         iRet = fdbop_qry_gab_dxzp_hhmd(lXmlhandle,&st_gab_dxzp_hhmd);

		         if( iRet < 0 )
               {
               	   fclose(fp);
                   fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
                   LOGRET( GAB_DXZP_FUNCRET_SQLERR, LM_STD, Fmtmsg("查询电信诈骗黑灰名单表失败,mdjz[%s]", 
                   st_gab_dxzp_hhmd.mdjz),fpub_GetCompname(lXmlhandle));
               }
             else if ( iRet == 0 )
               {
               	  memset(&st_gab_dxzp_hhmd,0x00,sizeof(st_gab_dxzp_hhmd));
		              ffunc_gabdxzp_getXml_HHMD(lXmlhandle,&st_gab_dxzp_hhmd,sbuf);
		              LOG(LM_STD,Fmtmsg("完成装载黑灰名单信息"),fpub_GetCompname(lXmlhandle));
		              strncpy(st_gab_dxzp_hhmd.mdjb,sHhLevel,1);
		              
                  iRet1 = fdbop_ins_gab_dxzp_hhmd(lXmlhandle,&st_gab_dxzp_hhmd);
                  if( iRet1 <0 && iRet1 != GAB_DXZP_FUNCRET_KEYERR ) 
                    { 
                        DCICommit();
                        fclose(fp);
                        LOGRET(iRet1, LM_STD, Fmtmsg(MSG_GAB_DXZP_CALLFUNC_FAIL, "插入电信诈骗黑灰名单表失败"), fpub_GetCompname(lXmlhandle)); 
                     }
                  LOG(LM_STD, Fmtmsg("登记黑灰名单表->完成登记黑灰名单表"), fpub_GetCompname(lXmlhandle));
                  
               }
             else
		          {
		          	  memset(&st_gab_dxzp_hhmd,0x00,sizeof(st_gab_dxzp_hhmd));
		              ffunc_gabdxzp_getXml_HHMD(lXmlhandle,&st_gab_dxzp_hhmd,sbuf);
		              LOG(LM_STD,Fmtmsg("完成装载黑灰名单信息"),fpub_GetCompname(lXmlhandle));
		              strncpy(st_gab_dxzp_hhmd.mdjb,sHhLevel,1);
		              
		         	    iRet1 =fdbop_upd_gab_dxzp_hhmd(lXmlhandle,&st_gab_dxzp_hhmd);
		         	    if(iRet1<0)
		         	    	{
		         	    	  DCICommit();
		         	    		fclose(fp);
                      LOGRET(iRet1, LM_STD, Fmtmsg(MSG_GAB_DXZP_CALLFUNC_FAIL, "更新电信诈骗黑灰名单表失败"), fpub_GetCompname(lXmlhandle)); 
		         	    	}
		         	}
		    }
		   if(0 == strcmp(sFlag,"-"))
		    	{
		    		iRet1 =fdbop_del_gab_dxzp_hhmd(lXmlhandle,&st_gab_dxzp_hhmd);
		    		if(iRet1<0)
		         	{       
		         		DCICommit();
		         		fclose(fp);
                LOGRET(iRet1, LM_STD, Fmtmsg(MSG_GAB_DXZP_CALLFUNC_FAIL, "删除电信诈骗黑灰名单表失败"), fpub_GetCompname(lXmlhandle)); 
		         	}
		    	}
     }
   DCICommit();
   fclose(fp);
   
   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   return 0;
}
/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_XDXX_UPDATE
组件名称: GAB_DXZP_XDXX_UPDATE
组件功能: 更新公安部电信诈骗下达信息
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    
输出：  
0   成功
-1  失败
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/

IRESULT GAB_DXZP_XDXX_UPDATE(HXMLTREE lXmlhandle)
{
  
    char sbuf[1024+1];
    int  iParas;
    int iRet=-1;
    GAB_DXZP_XDXX st_gab_dxzp_xdxx;
    memset(&st_gab_dxzp_xdxx,0x00,sizeof(st_gab_dxzp_xdxx));
    
    fpub_InitSoComp(lXmlhandle);
    
		GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/jbjg",st_gab_dxzp_xdxx.jbjg,"经办机构");
    GAB_DXZP_GETXMLSTR_NULL("/gabdxzp/jbgy",st_gab_dxzp_xdxx.jbgy,"经办柜员");
    GAB_DXZP_GETXMLSTR_NOTNULL("/gabdxzp/ywsqbh",st_gab_dxzp_xdxx.ywsqbh,"业务申请编号");
    trim(st_gab_dxzp_xdxx.jbjg);
    trim(st_gab_dxzp_xdxx.jbgy);
    trim(st_gab_dxzp_xdxx.ywsqbh);

    if( 0 == strcmp(st_gab_dxzp_xdxx.jbjg," ") || '\0' == st_gab_dxzp_xdxx.jbjg[0])
    	{
    		GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_XNJG,st_gab_dxzp_xdxx.jbjg,"经办机构");
    	}
    if( 0 == strcmp(st_gab_dxzp_xdxx.jbgy," ") || '\0' == st_gab_dxzp_xdxx.jbgy[0])
    	{
    		GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_SFXT_XNGY,st_gab_dxzp_xdxx.jbgy,"经办柜员");
    	}
		 iRet =fdbop_upd_gab_dxzp_xdxx_qdxx(lXmlhandle,&st_gab_dxzp_xdxx);
		 GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, "更新信息下达表");
		 DCICommit();      
   xml_SetElement(lXmlhandle,"/gabdxzp/jbjg" ,st_gab_dxzp_xdxx.jbjg);
   fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
   return 0;
}



/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_SET_ATTACHMENT_INFO
组件名称: GAB_DXZP_SET_ATTACHMENT_INFO
组件功能: 公安部电信诈骗设置文书信息
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    
输出：  
0   成功
-1  失败
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/

IRESULT GAB_DXZP_SET_ATTACHMENT_INFO(HXMLTREE lXmlhandle)
{
    char sbuf[256];
    int  iParas;
    int  iRet=-1;
    int  ilen=0;
    char YorNbase[2];
    char *psFileContents=NULL;
    char sSql[512];
    char sSbPch[36+1];
    char sbase64en[MAXSIZE];
    char *psBase64=NULL;
    int  iBase64Malloc=0;
    char sCommBuf[32768];/*32k*/
    int  iCommBuf=0;
    char *psBodyEnd=NULL;
    int  iBodyLen=0;
    char sYxxx[3145728];/*3M*/
    char sYwSqBh[36+1];
    char sReplFilename[200+1];
    int i=1;
    char psFileName[200];
    char sErrmsg[1000];
    CURSOR cur;
    GAB_DXZP_SMJFJ st_gab_dxzp_smjfj;/*电信诈骗扫描件附件表*/
    
    
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHK(1)
    memset(YorNbase, 0x00, sizeof(YorNbase));
    COMP_GETPARSEPARAS(1, YorNbase, "是否进行base64加密");
    trim(YorNbase);
    
    memset(sSbPch, 0x00, sizeof(sSbPch));
    GAB_DXZP_GETXMLSTR_NOTNULL("/gabdxzp/sbpch",sSbPch,"上报批次号");
    /*alter by liukq 20160504 BEGIN*/
    memset(sYwSqBh,0x00,sizeof(sYwSqBh));
    GAB_DXZP_GETXMLSTR_NOTNULL("/gabdxzp_ywbm/ApplicationID",sYwSqBh,"业务申请编号");
    /*alter by liukq 20160504 END*/
    memset(sCommBuf, 0x00, sizeof(sCommBuf));
	if(0 > (iRet = xml_RelGetBinElement(lXmlhandle, "/commbuf", sCommBuf, sizeof(sCommBuf)-1)))
	{
		LOG(LM_STD, Fmtmsg("取通讯区错误iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "与前置机通讯失败,获取通讯区错误");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	iCommBuf=strlen(sCommBuf);
	/*定位报文体标识符*/
	psBodyEnd=strstr(sCommBuf,"</Body>");
	if (psBodyEnd==NULL)
	{
		LOG(LM_STD, Fmtmsg("定位报文体结束符失败"), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "未找到报文体,组报异常");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
    memset(sSql, 0x00, sizeof(sSql));
   
    snprintf(sSql,sizeof(sSql),"SELECT * FROM gab_dxzp_smjfj WHERE ywsqbh='%s'", sSbPch);

    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    memset(sYxxx, 0x00, sizeof(sYxxx));
	  iBodyLen = iCommBuf - strlen(psBodyEnd);
    memcpy(sYxxx, sCommBuf, iBodyLen);
    psBodyEnd=NULL;
    
     for ( i=1; ; i++)
    {
        memset(&st_gab_dxzp_smjfj, 0x00, sizeof(st_gab_dxzp_smjfj));
        memset(sbase64en,0x00,sizeof(sbase64en));
        memset(psFileName,0x00,sizeof(psFileName));
        /*alter  by liukq 20160504 BEGIN*/
        memset(sReplFilename,0x00,sizeof(sReplFilename));
        /*alter  by liukq 20160504 END*/
        iRet = DBFetch(cur, SD_GAB_DXZP_SMJFJ, NUMELE(SD_GAB_DXZP_SMJFJ), &st_gab_dxzp_smjfj, sErrmsg );
        if ( iRet <= 0 )
        {
        	  if(i!=1)
        	  {
        	  	strcat(sYxxx, "</Attachments>");
        	  }
            break;
        }
        if(1==i)
        	{
        	 strcat(sYxxx, "<Attachments>");
        	}
        ffunc_file_getFileName(lXmlhandle,st_gab_dxzp_smjfj.wjm,psFileName);
        if('\0' == psFileName[0])
        {
        	LOG(LM_STD,Fmtmsg("---->获取文件名失败"),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_GAB_DXZP_FILEOP,"获取文件名");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
		    strcat(sYxxx, "<Attachment><Filename>");
		    memset(sbuf,0x00,sizeof(sbuf));
		    sprintf(sbuf,"/Attachments/Attachment|%d/Filename",i);
		    LOG(LM_STD,Fmtmsg("i=[%d],Filename=[%s],ilen=[%d]",i,psFileName,ilen),"DEBUG");
		    /*alter by liukq 20160504 BEGIN
		    strcat(sYxxx, psFileName);
		    END*/
		    /*alter by liukq 20160504 BEGIN*/
		    strcpy(sReplFilename,psFileName);
		    memcpy(sReplFilename+3,sYwSqBh,36);
		    strcat(sYxxx, sReplFilename);
		    /*alter by liukq 20160504 END*/
		    strcat(sYxxx, "</Filename><Content>");
		    COMP_SOFTSETXML(sbuf,psFileName);
        ilen=0;
        psFileContents=ffunc_file_getJPEGContents(lXmlhandle,st_gab_dxzp_smjfj.wjm, &ilen);
        if(NULL==psFileContents)
        {
        	free(psFileContents);
        	psFileContents=NULL;
        	LOG(LM_STD,Fmtmsg("---->获取文件内容失败"),"ERROR");
            fpub_SetMsg(lXmlhandle,MID_GAB_DXZP_FILEOP,"获取文件内容失败");
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
		   LOG(LM_STD,Fmtmsg("i=[%d],psFileContents=[%s],ilen=[%d]",i,psFileName,ilen),"DEBUG");
        if( 0 == strcmp(YorNbase,"0"))
        {
        	strncpy(sbase64en,psFileContents,MAXSIZE);
        	psBase64=psFileContents;
        	iBase64Malloc=0;
        }else
         {
            psBase64=fpub_base64_encode(psFileContents,&ilen,MAXSIZE);
            if(NULL == psBase64)
     	    {
     	       free(psFileContents);
        		 psFileContents=NULL;
			       LOG(LM_STD, Fmtmsg(" fpub_base64_encode-->加密处理失败 "), __func__);
			       fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
			       fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			       return COMPRET_FAIL;		
		     }
		     iBase64Malloc=1;  
		  }
		    

		    memset(sbuf,0x00,sizeof(sbuf));
		    sprintf(sbuf,"/Attachments/Attachment|%d/Content",i);
		    COMP_SOFTSETXML(sbuf,sbase64en);
		    LOG(LM_STD,Fmtmsg("i=[%d],psBase64=[%s],ilen=[%d]",i,psBase64,ilen),"DEBUG");
		    strcat(sYxxx, psBase64);
		    strcat(sYxxx, "</Content></Attachment>");
		    if (iBase64Malloc==1) free(psBase64);psBase64=NULL;
		    free(psFileContents);psFileContents=NULL;
        
    }
    DCIFreeCursor(cur);
    strcat(sYxxx, "</Body></Request>");
    iCommBuf=strlen(sYxxx);
    if(0 > (iRet = xml_RelSetBinElement(lXmlhandle, "/commbuf", sYxxx, iCommBuf)))
	{
		LOG(LM_STD, Fmtmsg("写通讯区错误iRet=[%d]", iRet), "DEBUG");
		/*alter by liukq 20160503 BEGIN
		fpub_SetMsg(lXmlhandle, 99999, "组请求报文失败,写通讯区错误");
		END*/
		/*alter by liukq 20160503 BEGIN*/
		fpub_SetMsg(lXmlhandle, 98601, "组请求报文失败,写通讯区错误");
		/*alter by liukq 20160503 END*/
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
    
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return 0;
}
/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_SMJFJ_INS
组件名称:GAB_DXZP_SMJFJ_INS
组件功能:记录电信诈骗扫描件附件表(次组建为案件举报专用)
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/

IRESULT GAB_DXZP_SMJFJ_INS(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    int i=1,j=1, iCnts=0;/*总任务数*/
    char sSbpch[36+1];
    GAB_DXZP_SMJFJ st_gab_dxzp_smjfj;/*电信诈骗扫描件附件表*/

    fpub_InitSoComp(lXmlhandle);
    memset(sSbpch,0x00,sizeof(sSbpch));
    GAB_DXZP_GETXMLSTR_NOTNULL(XMLNM_GAB_DXZP_CHANLE_YWSQBH,sSbpch,"上报批次号");
    COMP_SOFTSETXML(XMLNM_GAB_DXZP_APPLICATIONID,sSbpch);

    /*获取总任务数*/
    iCnts=xml_ElementCount(lXmlhandle,"/gabdxzp/yxxx");
    if(iCnts<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/gabdxzp/yxxx节点不存在"),fpub_GetCompname(lXmlhandle));
   			 if(0==iCnts)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return iCnts;
   		}
    LOG(LM_STD, Fmtmsg("登记电信诈骗扫描件附件表->开始处理[%d]", iCnts), fpub_GetCompname(lXmlhandle));
    
    /*2.装载及登记电信诈骗扫描件附件表*/
    DCIBegin();
    for ( i=1,j=1; i<=iCnts; i++,j++)
    {
        memset(&st_gab_dxzp_smjfj, 0x00, sizeof(st_gab_dxzp_smjfj));
        iRet = ffunc_gabdxzp_getXml_SMJFJ_Req(lXmlhandle, &st_gab_dxzp_smjfj);
        GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "装载电信诈骗扫描件附件表");
        st_gab_dxzp_smjfj.xh=i;
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/yxxx|%d/wjm",i);
        GAB_DXZP_GETXMLSTR_NOTNULL(sBuf,st_gab_dxzp_smjfj.wjm,"文件名");
        LOG(LM_STD, Fmtmsg("登记电信诈骗扫描件附件表->完成电信诈骗扫描件附件表[%d]", i), fpub_GetCompname(lXmlhandle));
        
        /*登记电信诈骗扫描件附件表->完成装载电信诈骗扫描件附件表*/
        iRet = fdbop_ins_gab_dxzp_smjfj(lXmlhandle, &st_gab_dxzp_smjfj);
        GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, "登记电信诈骗扫描件附件表->完成装载电信诈骗扫描件附件表");
        LOG(LM_STD, Fmtmsg("登记电信诈骗扫描件附件表->完成装载电信诈骗扫描件附件表[%d]", i), fpub_GetCompname(lXmlhandle));
        if ( j > GAB_DXZP_COMMIT_CNT )
        {/*达到提交记录数才提交事务*/
            DCICommit();
            DCIBegin();
            j = 1;
        }
    }
    DCICommit();
    
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("登记电信诈骗扫描件附件表->处理成功[%d]", i), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}







/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_QUERY_QHCX_ZHJBXX_ZZHXX
组件名称:GAB_DXZP_QUERY_QHCX_ZHJBXX_ZZHXX
组件功能:取全户查询账户基本信息子账户信息
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_QUERY_QHCX_ZHJBXX_ZZHXX(HXMLTREE lXmlhandle)
{
    int  iParas;
    int iRet=-1;
    char sErrmsg[1000];
    char sSql[512];
    char sYwsqbh[100];
    char sBuf[200];
    char sSql_zzhxx[512];
    int i=0;
    
    CURSOR query_qhcx_zhjbxxcur;
    CURSOR query_qhcx_zhxx_cur;
    
    GAB_DXZP_JYMX_ZHJBXX st_gab_dxzp_jymx_zhjbxx;/*全户查询_账户基本信息表*/
    GAB_DXZP_QHCX_ZZHXX st_gab_dxzp_qhcx_zzhxx;/*全户查询_子账号信息表*/
   
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHKMIN(1);
    memset(sYwsqbh,0x00,sizeof(sYwsqbh));
    COMP_GETPARSEPARAS(1, sYwsqbh, "业务申请编号");
     
    
    
      
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"SELECT * \
     FROM gab_dxzp_jymx_zhjbxx  WHERE  ywsqbh='%s' ORDER BY rwxh asc",sYwsqbh);
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((query_qhcx_zhjbxxcur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(query_qhcx_zhjbxxcur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(query_qhcx_zhjbxxcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    while(1)
    {
        memset(&st_gab_dxzp_jymx_zhjbxx, 0x00, sizeof(st_gab_dxzp_jymx_zhjbxx));
        iRet = DBFetch(query_qhcx_zhjbxxcur, SD_GAB_DXZP_JYMX_ZHJBXX, NUMELE(SD_GAB_DXZP_JYMX_ZHJBXX), &st_gab_dxzp_jymx_zhjbxx, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zhm",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.zhm);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/kzh",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.kzh);
       
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/khwd",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.khwd);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/khwddm",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.khwddm);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/khrq",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.khrq);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/xhrq",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.xhrq);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/xhwd",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.xhwd);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/beiz",st_gab_dxzp_jymx_zhjbxx.rwxh);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_jymx_zhjbxx.beiz);
        
        LOG(LM_STD,Fmtmsg("rwxh=[%d]",st_gab_dxzp_jymx_zhjbxx.rwxh),fpub_GetCompname(lXmlhandle));
          
        memset(sSql_zzhxx, 0x00, sizeof(sSql_zzhxx));
        snprintf(sSql_zzhxx,sizeof(sSql_zzhxx),"SELECT *\
        FROM gab_dxzp_qhcx_zzhxx  WHERE  ywsqbh='%s' and rwxh=%d  ORDER BY zzhxh asc",sYwsqbh,st_gab_dxzp_jymx_zhjbxx.rwxh);
        LOG(LM_STD,Fmtmsg("sSql_zzhxx[%s]", sSql_zzhxx),fpub_GetCompname(lXmlhandle));
        
        if ((query_qhcx_zhxx_cur = DCIDeclareCursor(sSql_zzhxx, DCI_STMT_LOCATOR)) == -1)
         {
           LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
        if (DCIExecute(query_qhcx_zhxx_cur) == -1)
         {
           LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
           DCIFreeCursor(query_qhcx_zhxx_cur);
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
         i=0;
         while(1)
         {
         	   i++;
         	   memset(&st_gab_dxzp_qhcx_zzhxx, 0x00, sizeof(st_gab_dxzp_qhcx_zzhxx));
             iRet = DBFetch(query_qhcx_zhxx_cur, SD_GAB_DXZP_QHCX_ZZHXX, NUMELE(SD_GAB_DXZP_QHCX_ZZHXX), &st_gab_dxzp_qhcx_zzhxx, sErrmsg );
             if ( iRet <= 0 )
             {
                 if(1 == i)  
                 	{
                 		 memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zzhxh",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                 		 memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zh",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zzhlb",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zhzt",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/bz",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/chbz",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zhye",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/kyye",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|1/zhjysj",st_gab_dxzp_jymx_zhjbxx.rwxh);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                 		
                 	}       	
                 break;
             }
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zzhxh",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             
         	   memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zh",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zzhlb",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zzhlb);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zhzt",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zhzt);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/bz",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.bz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/chbz",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.chbz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zhye",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zhye);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/kyye",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.kyye);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/qhcx/zhjbxx|%d/zzhxx|%s/zhjysj",st_gab_dxzp_jymx_zhjbxx.rwxh,st_gab_dxzp_qhcx_zzhxx.zzhxh);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_qhcx_zzhxx.zhjysj);
            
         }
         DCIFreeCursor(query_qhcx_zhxx_cur);
         if( iRet < 0 )
         {
             LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
             fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return COMPRET_FAIL;
         }
       
    }
    DCIFreeCursor(query_qhcx_zhjbxxcur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"公安部电信诈骗交易明细查询结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_HQTGJGXX
组件名称: GAB_DXZP_HQTGJGXX
组件功能: 获取托管机构消息
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明    
输出：  
0   成功
-1  失败
使用限制:
程 序 员: 
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_HQTGJGXX(HXMLTREE lXmlhandle)
{
    int  iParas;
    char sBuf[256];
    char sSql[512];
    char sErrmsg[256];
    int  iAutoProcs=10;/*自动任务处理笔数*/
    int i=1;
    int iRet=-1;
    CURSOR cur;
    GAB_DXZP_HMHH gab_dxzp_hmhh;
    
    fpub_InitSoComp(lXmlhandle);

    LOG(LM_STD,Fmtmsg("获取托管机构消息自动处理执行开始"),fpub_GetCompname(lXmlhandle));
    
    /* 查询需要处理的任务 */
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"select * from gab_dxzp_hmhh where hb='t' ");
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    for ( i=1; ; i++)
    {
        memset(&gab_dxzp_hmhh, 0x00, sizeof(gab_dxzp_hmhh));
        iRet = DBFetch(cur, SD_GAB_DXZP_HMHH, NUMELE(SD_GAB_DXZP_HMHH), &gab_dxzp_hmhh, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        
        /* 公共交易信息赋值 */
        COMP_SOFTSETXML("/gabdxzp/jgid", gab_dxzp_hmhh.hh);/*托管行号*/
        LOG(LM_STD,Fmtmsg("即将调用获取托管机构流程subflow_gabdxzp_945128处理,hh[%s]",gab_dxzp_hmhh.hh),"INFO");
        /* 调用待处理业务入口 */
        if(fpub_CallFlow(lXmlhandle,"subflow_gabdxzp_945128")!=MID_SYS_SUCC)
        {
            LOG(LM_STD,Fmtmsg("调用待处理业务流程subflow_gabdxzp_945128[%s]失败",
                gab_dxzp_hmhh.hh),"ERROR");
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle,99993,Fmtmsg("执行获取托管机构消息流程失败"));
            return COMPRET_FAIL ;
        }
    }
    DCIFreeCursor(cur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    LOG(LM_STD,Fmtmsg("获取托管机构消息自动处理执行结束,共处理[%d]条业务", i-1), fpub_GetCompname(lXmlhandle));
    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"获取托管机构消息自动处理执行结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}









/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_QUERY_SAZH_GLZHXX_JYMX
组件名称:GAB_DXZP_QUERY_SAZH_GLZHXX_JYMX
组件功能:取账户涉案关联账户-交易信息
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2016-1-25 16:46:21(gen)
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_QUERY_SAZH_GLZHXX_JYMX(HXMLTREE lXmlhandle)
{
    int  iParas;
    int iRet=-1;
    char sErrmsg[1000];
    char sSql[512];
    char sSbpch[40];
    char sSbpcxh[20];
    int pcxh=0;
    char sBuf[200];
    char sSql_glzhxx_jymx[512];
    int i=0,iZHXH=0;
    char sZHXH[20];
    
    CURSOR query_glzhxxcur;
    CURSOR query_glzhxx_jymxcur;
    
    GAB_DXZP_SBXX_GLZHXX st_gab_dxzp_sbxx_glzhxx;/*上报信息_关联账户信息表*/
    GAB_DXZP_SBXX_JYMX st_gab_dxzp_sbxx_jymx;/*上报信息_交易明细表*/
   
    fpub_InitSoComp(lXmlhandle);
    
    COMP_PARACOUNTCHKMIN(2);
    memset(sSbpch,0x00,sizeof(sSbpch));
    COMP_GETPARSEPARAS(1, sSbpch, "上报批次号");
    memset(sSbpcxh,0x00,sizeof(sSbpcxh));
    COMP_GETPARSEPARAS(2, sSbpcxh, "上报批次序号"); 
    trim(sSbpch);
    trim(sSbpcxh);
    pcxh=atoi(sSbpcxh);  
    memset(sSql, 0x00, sizeof(sSql));
    snprintf(sSql,sizeof(sSql),"SELECT * \
     FROM gab_dxzp_sbxx_glzhxx  WHERE  sbpch='%s' and sbpcxh=%d ORDER BY zhxh asc",sSbpch,pcxh);
    LOG(LM_STD,Fmtmsg("sSql[%s]", sSql),fpub_GetCompname(lXmlhandle));
    if ((query_glzhxxcur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(query_glzhxxcur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
        DCIFreeCursor(query_glzhxxcur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    
    while(1)
    {
        memset(&st_gab_dxzp_sbxx_glzhxx, 0x00, sizeof(st_gab_dxzp_sbxx_glzhxx));
        iRet = DBFetch(query_glzhxxcur, SD_GAB_DXZP_SBXX_GLZHXX, NUMELE(SD_GAB_DXZP_SBXX_GLZHXX), &st_gab_dxzp_sbxx_glzhxx, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        iZHXH++;
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/zh",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_glzhxx.zh);
        
        memset(sZHXH,0x00,sizeof(sZHXH));
        memset(sBuf,0x00,sizeof(sBuf));
        strcpy(sZHXH,itoa(iZHXH));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/zzhxh",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,sZHXH);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/zhlx",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_glzhxx.zhlx);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/zhzt",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_glzhxx.zhzt);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/bz",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_glzhxx.bz);
        
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf,"/gabdxzp/glzhxx|%d/chbz",iZHXH);
        trim(sBuf);
        xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_glzhxx.chbz);
        
        LOG(LM_STD,Fmtmsg("rwxh=[%d]",iZHXH),fpub_GetCompname(lXmlhandle));
          
        memset(sSql_glzhxx_jymx, 0x00, sizeof(sSql_glzhxx_jymx));
        snprintf(sSql_glzhxx_jymx,sizeof(sSql_glzhxx_jymx),"SELECT *\
        FROM gab_dxzp_sbxx_jymx  WHERE  sbpch='%s' and sbpcxh=%d and zhxh='%s'  ORDER BY jyxh asc",sSbpch,pcxh,st_gab_dxzp_sbxx_glzhxx.zhxh);
        LOG(LM_STD,Fmtmsg("sSql_glzhxx_jymx[%s]", sSql_glzhxx_jymx),fpub_GetCompname(lXmlhandle));
        
        if ((query_glzhxx_jymxcur = DCIDeclareCursor(sSql_glzhxx_jymx, DCI_STMT_LOCATOR)) == -1)
         {
           LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
        if (DCIExecute(query_glzhxx_jymxcur) == -1)
         {
           LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR");
           DCIFreeCursor(query_glzhxx_jymxcur);
           fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
           fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
           return COMPRET_FAIL;
         }
         i=0;
         while(1)
         {
         	   i++;
         	   memset(&st_gab_dxzp_sbxx_jymx, 0x00, sizeof(st_gab_dxzp_sbxx_jymx));
             iRet = DBFetch(query_glzhxx_jymxcur, SD_GAB_DXZP_SBXX_JYMX, NUMELE(SD_GAB_DXZP_SBXX_JYMX), &st_gab_dxzp_sbxx_jymx, sErrmsg );
             if ( iRet <= 0 )
             {
                 if(1 == i)  
                 	{
                 		 memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/jylsh",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/jysj",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/jylx",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/bz",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/jyje",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/fkkhhhh",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/fkkhhmc",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/fkfxm",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/fkfzh",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/skkhhhh",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/skkhhmc",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/skfxm",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/skfzh",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"-");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/ip",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/mac",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/sbid",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/jydd",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                     
                     memset(sBuf,0x00,sizeof(sBuf));
                     sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|1/beiz",iZHXH);
                     trim(sBuf);
                     xml_SetElement(lXmlhandle,sBuf ,"");
                 	}       	
                 break;
             }
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/jylsh",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.jylsh);
             
         	   memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/jysj",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.jysj);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/jylx",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.jylx);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/bz",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.bz);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/jyje",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.jyje);
            
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/fkkhhhh",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.zczhyhjg);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/fkkhhmc",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.zczhyhmc);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/fkfxm",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.zczhm);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/fkfzh",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.zczh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/skkhhhh",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.ddzhyhjg);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/skkhhmc",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.ddzhyhmc);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/skfxm",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.ddzhm);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/skfzh",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.ddzh);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/ip",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.ip);
            
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/mac",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.mac);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/sbid",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.sbid);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/jydd",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.jydd);
             
             memset(sBuf,0x00,sizeof(sBuf));
             sprintf(sBuf,"/gabdxzp/glzhxx|%d/jyxx|%d/beiz",iZHXH,i);
             trim(sBuf);
             xml_SetElement(lXmlhandle,sBuf ,st_gab_dxzp_sbxx_jymx.beiz);
             
         }
         DCIFreeCursor(query_glzhxx_jymxcur);
         if( iRet < 0 )
         {
             LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
             fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
             fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
             return COMPRET_FAIL;
         }
       
    }
    DCIFreeCursor(query_glzhxxcur);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%d][%s]", iRet, DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetMsg(lXmlhandle,COMPSTATUS_SUCC,"公安部电信诈骗交易明细查询结束");
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}




/************************************************************************
动态组件函数定义
组件函数名称:GAB_DXZP_2LOOP_CHECK_SAZH
组件名称: GAB_DXZP_2LOOP_CHECK_SAZH
组件功能: 公安部电信诈骗2层循环报文检测关联账户交易信息
组件参数:
序号 参数类型  参数名称             资源类别           缺省值     可空  参数说明

输出：
0   成功
-1  失败
使用限制:
程 序 员:
发布日期:
修改日期:
参数使用示例:
************************************************************************/
IRESULT GAB_DXZP_2LOOP_CHECK_SAZH(HXMLTREE lXmlhandle)
{
    int  iParas;
    int  count=-1;/*循环次数*/
    char s1Looppath[200];/*一层循环路径*/
    char s2Looppath[200];/*二层循环路径*/
    char sBuf[254];
    char sCatXml[254];
    int  iRet=-1;
    int i=1;

    fpub_InitSoComp(lXmlhandle);

#ifdef DEBUG
    LOG(LM_STD, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif

    memset(s1Looppath,0x00,sizeof(s1Looppath));
    memset(s2Looppath,0x00,sizeof(s2Looppath));
    memset(sBuf,0x00,sizeof(sBuf));

    COMP_PARACOUNTCHKMIN(2)
    COMP_GETPARSEPARAS(1,s1Looppath,"一层循环路径")
    COMP_GETPARSEPARAS(2,s2Looppath,"二层循环路径")
    trim(s1Looppath);
    trim(s2Looppath);
    
    count=xml_ElementCount(lXmlhandle,"/gabdxzp/glzhxx");
    if(count<=0)
   		{
   			 LOG(LM_STD,Fmtmsg("/gabdxzp/glzhxx节点不存在"),fpub_GetCompname(lXmlhandle));
   			  if(0==count)
   			 {
   			  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);	
   			 }
   			 return count;
   		}
   		
    LOG(LM_STD,Fmtmsg("s1Looppath[%s],s2Looppath[%s]",s1Looppath,s2Looppath),fpub_GetCompname(lXmlhandle));

    for(i=1;i<=count;i++)
      {
         memset(sBuf,0x00,sizeof(sBuf));
         sprintf(sBuf,"%s|%d/%s",s1Looppath,i,s2Looppath);
     	   iRet = xml_ElementExist(lXmlhandle,sBuf);
     	   if(0 == iRet)
     	   	{
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/jylsh",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/jysj",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/jylx",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/bz",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/jyje",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/fkkhhhh",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/fkkhhmc",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/fkfxm",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/fkfzh",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/skkhhhh",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/skkhhmc",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/skfxm",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/skfzh",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "-");
     	   		

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/ip",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/mac",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");

     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/sbid",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/jydd",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");
     	   		
     	   		memset(sCatXml,0x00,sizeof(sCatXml));
     	   		sprintf(sCatXml,"%s|1/beiz",sBuf);
     	   		xml_SetElement(lXmlhandle,sCatXml, "");
     	   		
     	   	}
     	   if(0 > iRet)
     	   	{
     	   		GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, " xml_ElementExist 判断节点存在失败");
     	   	}
      }


#ifdef DEBUG
  LOG(LM_STD, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);

    return COMPSTATUS_SUCC;
}

/************************************************************************
 动态组件函数定义
 组件函数名称:GAB_DXZP_UTF8TOGBK
 组件名称:转换UTF-8
 组件功能:转换UTF-8
 组件参数:
 序号 参数类型  参数名称      资源类别         缺省值            可空   参数说明

 组件结果状态:
 结果状态码         结果说明
 缺省

 主要操作库表:
 表名                       操作

 处理流程:

 项 目 组:
 程 序 员:
 发布日期:
 修改日期:
 参数使用示例:
 ************************************************************************/
IRESULT GAB_DXZP_UTF8TOGBK(HXMLTREE lXmlhandle)
{
    int iParas;
    int iRet = -1;
    char sBuf[256+1];
    int iUTF8Len=0;
    int iGBKLen=0;
    char *pUTF8 = NULL;
    char *pGBK = NULL;

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_STD, Fmtmsg("转换UTF-8->开始处理"), fpub_GetCompname(lXmlhandle));

    /*获取定时消息*/
    iUTF8Len = xml_GetBinElementLen(lXmlhandle, "/commbuf");
    if (iUTF8Len <= 0 )
    {
        LOG(LM_STD,Fmtmsg("/commbuf长度为[%s],请确认", iUTF8Len ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* 根据获取到的长度申请内存 */
    pUTF8 = (char *)malloc( iUTF8Len+1 );
    if ( pUTF8 == NULL )
    {
        LOG(LM_STD,Fmtmsg("动态申请commbuf内存失败" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
	/*获取通讯区内容*/
	memset(pUTF8, 0x00, iUTF8Len+1);
	if(0 > (iRet = xml_RelGetBinElement(lXmlhandle, "/commbuf", pUTF8, iUTF8Len+1)))
	{
		free(pUTF8);pUTF8=NULL;
		LOG(LM_STD, Fmtmsg("取通讯区错误iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "转换UTF-8,获取通讯区错误");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
	}
	LOG(LM_STD, Fmtmsg("get pUTF8[%d][%s]", iRet, pUTF8), fpub_GetCompname(lXmlhandle));
    
    iGBKLen = iUTF8Len * 1.5 ;
    pGBK = (char *)malloc( iGBKLen+1 );
    if ( pGBK == NULL )
    {
        free(pUTF8);pUTF8=NULL;
        LOG(LM_STD,Fmtmsg("动态申请commbuf内存失败" ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,Fmtmsg(MSG_SYS_COMPEXEC,fpub_GetCompname(lXmlhandle)));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    
    memset(pGBK, 0x00, iGBKLen+1);
    iRet = convert( "UTF-8", "GB18030", pUTF8, iUTF8Len, pGBK, &iGBKLen);
    if ( iRet < 0 )
    {
		free(pUTF8);pUTF8=NULL;
		free(pGBK);pGBK=NULL;
		LOG(LM_STD, Fmtmsg("转换UTF-8,转换GB18030报文内容失败iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "转换UTF-8,转换GB18030报文内容失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
    }
    free(pUTF8);pUTF8=NULL;
    iGBKLen=strlen(pGBK);
    LOG(LM_STD, Fmtmsg("utf-8->gbk=[%d][%s]", iGBKLen,pGBK), fpub_GetCompname(lXmlhandle));
    if(0 > (iRet = xml_RelSetBinElement(lXmlhandle, "/commbuf", pGBK, iGBKLen)))
    {
    	free(pGBK);pGBK=NULL;
		LOG(LM_STD, Fmtmsg("回写/commbuf报文内容失败iRet=[%d]", iRet), "ERROR");
		fpub_SetMsg(lXmlhandle, 99998, "转换UTF-8,回写/commbuf报文内容失败");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPRET_FAIL;
    }
    free(pGBK);pGBK=NULL;
    /* 交易结束 */
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    LOG(LM_STD, Fmtmsg("转换UTF-8->处理成功"), fpub_GetCompname(lXmlhandle));
    return COMPSTATUS_SUCC;
}
