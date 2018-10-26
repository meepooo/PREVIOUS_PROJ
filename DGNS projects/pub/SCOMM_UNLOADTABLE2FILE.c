/********************************************************************
  版权所有:恒生电子股份有限公司
  项目名称:综合应用平台（GAPS）项目
  版    本:V1.0.00
  操作系统:LIUNX64
  文件名称:SCOMM_UNLOADTABLE2FILE.c
  文件描述:GAPS个性化公共组件
  项 目 组:
  程 序 员:llh
  发布日期:
  修    订:
  修改日期:  
 *********************************************************************/

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.00"
#define MAX_RES_BUF_SIZE 5*1024

#include "gaps_head.h"
#include <string.h>

/*
   注：本函数为组件库公共函数,用于在发布状态下显示内部版本信息
       在生产环境下，每次更新均应修改版本号、填入相应信息
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
             "<soname>SCOMM_UNLOADTABLE2FILE.so</soname>"
             "<sosrcname>SCOMM_UNLOADTABLE2FILE.c</sosrcname>"
             "<sonote>个性化公共组件</sonote>"
             "<version>"
               "<rec ver=\"1.0.00\" modify=\"2018-01-22 17:18:33\" programer=\"[黎灵海]\" filesize=\"FILE\">初始发布版</rec>"
             "</version>"
     "</root>";
  printf("\n================动态组件基本信息================\n");
  printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
  printf("%s-%s\n",__PROJECTSNAME,__VERSION);
  if (strlen(sversion) >= isize)
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
  组件函数名称: SCOMM_UNLOADTABLE2FILE
  组件名称: 完全导出SQL查询内容到指定文件

  组件功能: 
  执行shell命令并取输出结果
  组件参数: 
  序号 参数名称        资源类别       缺省值   是否可空  参数说明
  1    SHELL命令       XML解析字符串           不可为空  需要执行的SHELL命令
  2    结果保存节点    XML解析字符串           不可为空  执行SHELL命令后输出屏幕的结果保存至某节点

  组件结果状态: 
  结果状态码         结果说明
  0                  成功
  -1　　　　　　　　 失败

  主要操作库表:
  表名              操作
  无

  项 目 组: 
  程 序 员: llh
  发布日期: 2018年01月22日
  修改日期: 
  修改日期: 
  参数使用示例: pwd /sys/shelloutput 
 ************************************************************************/
IRESULT SCOMM_UNLOADTABLE2FILE(HXMLTREE lXmlhandle)
{
    int iParas;
    char sBuf[512+1];
    char sFilestr[1024+1];
    char sPathfilename[256+1];
    char sCmdsql[1024+1];
    char sDelim[2+1];
    char sOutnode[100+1];
    char sQuerynum[10+1];
    FILE* fp = NULL;
    int iRet = 0;
    int iNum = 0;
    int i = 0;
    int iQuerynum = 0;
    CURSOR cur;

    fpub_InitSoComp(lXmlhandle); 
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)

    COMP_PARACOUNTCHKMIN(5);
    memset(sBuf,0x00,sizeof(sBuf));
    memset(sFilestr,0x00,sizeof(sFilestr));
    memset(sPathfilename,0x00,sizeof(sPathfilename));
    memset(sCmdsql,0x00,sizeof(sCmdsql));
    memset(sDelim,0x00,sizeof(sDelim));
    memset(sOutnode,0x00,sizeof(sOutnode));
    memset(sQuerynum,0x00,sizeof(sQuerynum));
    
    COMP_GETPARSEPARAS(1, sPathfilename, "导出文件存储路径");
    LOG(LM_DEBUG,Fmtmsg("sPathfilename=[%s]",sPathfilename),"DEBUG");
    COMP_GETPARSEPARAS(2, sCmdsql, "SQL查询语句");
    COMP_GETPARSEPARAS(3, sDelim, "导出文件中的分隔符");
    COMP_GETPARSEPARAS(4, sOutnode, "导出记录数储蓄结点");
    COMP_GETPARSEPARAS(5, sQuerynum, "查询SQL域值数目");
    trim(sPathfilename);
    trim(sCmdsql);
    trim(sDelim);
    trim(sOutnode);
    trim(sQuerynum);
    
    fp = fopen(sPathfilename, "w");
    if(fp == NULL)
    {
      LOG(LM_STD, "打开文件失败", "ERROR");
      fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      return COMPRET_FAIL;
    }
    
    if ((cur = DCIDeclareCursor(sCmdsql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fclose(fp);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("数据库操作失败,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        fclose(fp);
        return COMPRET_FAIL;
    }
    
    iQuerynum=atoi(sQuerynum);
    while( ( iRet = DCIFetch2(cur, DCI_FETCH_NEXT, 0) ) > 0 )
    {
        iNum++;
        memset(sFilestr,0x00,sizeof(sFilestr));
        for(i=0;i<iQuerynum;i++)
        {
            LOG(LM_DEBUG,Fmtmsg("i=[%d]",i),"DEBUG");
            memset(sBuf,0x00,sizeof(sBuf));
            sprintf(sBuf, "%s", DCIFieldAsString( cur, i  ) );
            LOG(LM_DEBUG,Fmtmsg("sBuf=[%s]",sBuf),"DEBUG");
            strcat(sFilestr,sBuf);
            strcat(sFilestr,sDelim);
            LOG(LM_DEBUG,Fmtmsg("sFilestr=[%s]",sFilestr),"DEBUG");
        }
        strcat(sFilestr,"\n");
        LOG(LM_DEBUG,Fmtmsg("sFilestr=[%s]",sFilestr),"DEBUG");
        iRet = fwrite(sFilestr,strlen(sFilestr),1,fp);
        iRet = fflush(fp);
        if(iRet < 0)
        {
            LOG(LM_STD,Fmtmsg("写文件失败,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fclose(fp);
            return COMPRET_FAIL;
        }
        
    }
          
    LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}

