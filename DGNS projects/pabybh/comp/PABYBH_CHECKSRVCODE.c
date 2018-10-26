/********************************************************************
  版权所有:恒生电子股份有限公司
  项目名称:综合应用平台（GAPS）项目
  版    本:V3.0.00
  操作系统:AIX5.3
  文件名称:PABYBH_CHECKSRVCODE.c.c
  文件描述:批量业务处理文件映射-数据提回处理转换组件集
  项 目 组:中间业务项目组
  程 序 员:sunpj
  发布日期:2017-06-12
  修    订:
  修改日期:  
 *********************************************************************/
/*
   总体说明:
   函数说明
   组件函数名称                 组件名称                      发布日期  程序员 修改日期 修改人

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gaps_head.h"
#include "xml.h"
#include "DCI.h"
#include "../incl/pabybh_xmlmacro.h"
#include "../incl/PABYBH_ERRMSG.h"
#include "../incl/PABYBH_SVRINFO.h"
#include "../incl/pab_pubfunc.h"


IRESULT SPABYBH_CHECKSRVCODE( HXMLTREE lXmlhandle )
{
  char sSql[512+1];
  char sBuffer[1042],sTmp[128+1];
  char sSvrCode[6+1];
  int  iRet=0;
  char sSysTime[6+1];
  long lSysTime=0;
  PABYBH_SVRINFO SDB_SvrInfo;

  /*取服务代码*/
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), "DEBUG");
  memset(sSvrCode,0x00,sizeof(sSvrCode));
  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_SVRCODE, sSvrCode);
 LOG( LM_DEBUG, Fmtmsg( "服务代码为=[%s]",sSvrCode), "INFO" );
  if( strlen(trim(sSvrCode)) == 0 )
  {
      LOG( LM_DEBUG, "服务代码不能为空!", "Error" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle,98702 , "服务代码不能为空");
     return COMPRET_FAIL ;
//      SetErrorMsg(lXmlhandle,BFE_ERR_SVRCODENULL,"服务代码不能为空!");
  //    return -1;
  }
   
  memset(sSql,0x00,sizeof(sSql));
  memset(sBuffer,0x00,sizeof(sBuffer));  
  sprintf(sSql,"select * from PABYBH_SVRINFO where SVRCODE = '%s'",sSvrCode);
  LOG( LM_DEBUG, Fmtmsg( "sSql=[%s]",sSql), "INFO" );
  iRet = Prv_SelTabToBuf(sSql,sBuffer);
  if( iRet < 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( "执行[%s]异常", sSql), "INFO" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle, MID_SQL_ERROR,"执行异常");
     return COMPRET_FAIL ;
    //  SetErrorMsg(lXmlhandle,BFE_ERR_DCIEXECSQL,"执行sql异常!");
     // return -2;     
  }
   LOG( LM_DEBUG, Fmtmsg("查询返回值iRet[%d]",iRet), "INFO" );

  if( iRet == 0 )
  {
      LOG( LM_DEBUG, "服务信息表尚未配置!", "Error" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle, 98686, "服务信息表尚未配置");
     return COMPRET_FAIL ;
     // SetErrorMsg(lXmlhandle,BFE_ERR_SVRINFONULL,"服务信息表尚未配置!");
     // return -3;     
  }  

  memset(&SDB_SvrInfo,0x00,sizeof(SDB_SvrInfo));
  memcpy(&SDB_SvrInfo,sBuffer,sizeof(SDB_SvrInfo)-1);
  
  /*服务标识*/
//  trim(SDB_SvrInfo.SVRSIGN);
 // COMP_SOFTSETXML("/pab/icc/svrSign", SDB_SvrInfo.SVRSIGN)

  /*服务名称*/
  trim(SDB_SvrInfo.SVRNAME);
  COMP_SOFTSETXML("/pabybh/req/svrName", SDB_SvrInfo.SVRNAME)  


  /*业务开展时间段*/
  if( strlen(trim(SDB_SvrInfo.WORKTIME)) != 0 )
  {
      /*获取机器时间：一定要准确*/
      memset(sSysTime,0x00,sizeof(sSysTime));
      COMP_SOFTGETXML("/sys/systime", sSysTime)
      lSysTime = atol(trim(sSysTime));
     
      /*业务开始时间*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(SDB_SvrInfo.WORKTIME,1,sTmp,'|','\\');
      trim(sTmp);  
      LOG( LM_DEBUG, Fmtmsg("start time [%s]",sTmp), "Error" );
      COMP_SOFTSETXML("/pabybh/req/beginTime", sTmp)  
      
      /*是否到业务开始时间*/
      if( lSysTime < atol(sTmp) )
      {
          LOG( LM_DEBUG, Fmtmsg( "业务未到开展时间,开始时间=[%s]",sTmp), "INFO" );
     	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
          fpub_SetMsg(lXmlhandle,98726 , "业务未到开展时间");
          return COMPRET_FAIL ;
        //  SetErrorMsg(lXmlhandle,BFE_ERR_SVRNOBEGIN,"业务未到开展时间!");
          //return -4;               
      }
           
      /*业务结束时间*/
      memset(sTmp,0x00,sizeof(sTmp));

      GetListbyDiv(SDB_SvrInfo.WORKTIME,2,sTmp,'|','\\');
      LOG( LM_DEBUG, Fmtmsg("end time [%s]",sTmp), "Error" );
      trim(sTmp);  
      COMP_SOFTSETXML("/pabybh/req/endTime", sTmp) 

      /*是否到业务结束时间*/
      if( lSysTime > atol(sTmp) )
      {
          LOG( LM_DEBUG, Fmtmsg( "业务已过结束时间,结束时间=[%s]",sTmp), "INFO" );
     	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
          fpub_SetMsg(lXmlhandle, 98727,"业务已过结束时间");
          return COMPRET_FAIL ;
          //SetErrorMsg(lXmlhandle,BFE_ERR_SVRISEND,"业务已过结束时间!");
          //return -5;               
      }     
  }
    
  /*服务状态：0-生效;其他不生效*/
  trim(SDB_SvrInfo.SVRSTATUS);
  if( SDB_SvrInfo.SVRSTATUS[0] != '0' )
  {
      LOG( LM_DEBUG, Fmtmsg( "服务尚未生效!状态=[%s]",SDB_SvrInfo.SVRSTATUS), "INFO" );
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      fpub_SetMsg(lXmlhandle,98728 , "服务尚未生效");
      return COMPRET_FAIL ;
    //  SetErrorMsg(lXmlhandle,BFE_ERR_SVRNOTBEGIN,"服务尚未生效!");
     // return -6;     
  }
  
  COMP_SOFTSETXML("/pabybh/req/svrStatus", SDB_SvrInfo.SVRSTATUS)
   LOG(LM_DEBUG,Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), "DEBUG")
    fpub_SetCompStatus(lXmlhandle, 0);

  return 0; 
}
