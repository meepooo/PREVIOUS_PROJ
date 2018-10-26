/********************************************************************
  ��Ȩ����:�������ӹɷ����޹�˾
  ��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
  ��    ��:V3.0.00
  ����ϵͳ:AIX5.3
  �ļ�����:PABYBH_CHECKSRVCODE.c.c
  �ļ�����:����ҵ�����ļ�ӳ��-������ش���ת�������
  �� Ŀ ��:�м�ҵ����Ŀ��
  �� �� Ա:sunpj
  ��������:2017-06-12
  ��    ��:
  �޸�����:  
 *********************************************************************/
/*
   ����˵��:
   ����˵��
   �����������                 �������                      ��������  ����Ա �޸����� �޸���

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

  /*ȡ�������*/
   LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG");
  memset(sSvrCode,0x00,sizeof(sSvrCode));
  COMP_SOFTGETXML(XMLNM_PABYBH_REQ_SVRCODE, sSvrCode);
 LOG( LM_DEBUG, Fmtmsg( "�������Ϊ=[%s]",sSvrCode), "INFO" );
  if( strlen(trim(sSvrCode)) == 0 )
  {
      LOG( LM_DEBUG, "������벻��Ϊ��!", "Error" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle,98702 , "������벻��Ϊ��");
     return COMPRET_FAIL ;
//      SetErrorMsg(lXmlhandle,BFE_ERR_SVRCODENULL,"������벻��Ϊ��!");
  //    return -1;
  }
   
  memset(sSql,0x00,sizeof(sSql));
  memset(sBuffer,0x00,sizeof(sBuffer));  
  sprintf(sSql,"select * from PABYBH_SVRINFO where SVRCODE = '%s'",sSvrCode);
  LOG( LM_DEBUG, Fmtmsg( "sSql=[%s]",sSql), "INFO" );
  iRet = Prv_SelTabToBuf(sSql,sBuffer);
  if( iRet < 0 )
  {
      LOG( LM_DEBUG, Fmtmsg( "ִ��[%s]�쳣", sSql), "INFO" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle, MID_SQL_ERROR,"ִ���쳣");
     return COMPRET_FAIL ;
    //  SetErrorMsg(lXmlhandle,BFE_ERR_DCIEXECSQL,"ִ��sql�쳣!");
     // return -2;     
  }
   LOG( LM_DEBUG, Fmtmsg("��ѯ����ֵiRet[%d]",iRet), "INFO" );

  if( iRet == 0 )
  {
      LOG( LM_DEBUG, "������Ϣ����δ����!", "Error" );
     fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
     fpub_SetMsg(lXmlhandle, 98686, "������Ϣ����δ����");
     return COMPRET_FAIL ;
     // SetErrorMsg(lXmlhandle,BFE_ERR_SVRINFONULL,"������Ϣ����δ����!");
     // return -3;     
  }  

  memset(&SDB_SvrInfo,0x00,sizeof(SDB_SvrInfo));
  memcpy(&SDB_SvrInfo,sBuffer,sizeof(SDB_SvrInfo)-1);
  
  /*�����ʶ*/
//  trim(SDB_SvrInfo.SVRSIGN);
 // COMP_SOFTSETXML("/pab/icc/svrSign", SDB_SvrInfo.SVRSIGN)

  /*��������*/
  trim(SDB_SvrInfo.SVRNAME);
  COMP_SOFTSETXML("/pabybh/req/svrName", SDB_SvrInfo.SVRNAME)  


  /*ҵ��չʱ���*/
  if( strlen(trim(SDB_SvrInfo.WORKTIME)) != 0 )
  {
      /*��ȡ����ʱ�䣺һ��Ҫ׼ȷ*/
      memset(sSysTime,0x00,sizeof(sSysTime));
      COMP_SOFTGETXML("/sys/systime", sSysTime)
      lSysTime = atol(trim(sSysTime));
     
      /*ҵ��ʼʱ��*/
      memset(sTmp,0x00,sizeof(sTmp));
      GetListbyDiv(SDB_SvrInfo.WORKTIME,1,sTmp,'|','\\');
      trim(sTmp);  
      LOG( LM_DEBUG, Fmtmsg("start time [%s]",sTmp), "Error" );
      COMP_SOFTSETXML("/pabybh/req/beginTime", sTmp)  
      
      /*�Ƿ�ҵ��ʼʱ��*/
      if( lSysTime < atol(sTmp) )
      {
          LOG( LM_DEBUG, Fmtmsg( "ҵ��δ����չʱ��,��ʼʱ��=[%s]",sTmp), "INFO" );
     	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
          fpub_SetMsg(lXmlhandle,98726 , "ҵ��δ����չʱ��");
          return COMPRET_FAIL ;
        //  SetErrorMsg(lXmlhandle,BFE_ERR_SVRNOBEGIN,"ҵ��δ����չʱ��!");
          //return -4;               
      }
           
      /*ҵ�����ʱ��*/
      memset(sTmp,0x00,sizeof(sTmp));

      GetListbyDiv(SDB_SvrInfo.WORKTIME,2,sTmp,'|','\\');
      LOG( LM_DEBUG, Fmtmsg("end time [%s]",sTmp), "Error" );
      trim(sTmp);  
      COMP_SOFTSETXML("/pabybh/req/endTime", sTmp) 

      /*�Ƿ�ҵ�����ʱ��*/
      if( lSysTime > atol(sTmp) )
      {
          LOG( LM_DEBUG, Fmtmsg( "ҵ���ѹ�����ʱ��,����ʱ��=[%s]",sTmp), "INFO" );
     	  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
          fpub_SetMsg(lXmlhandle, 98727,"ҵ���ѹ�����ʱ��");
          return COMPRET_FAIL ;
          //SetErrorMsg(lXmlhandle,BFE_ERR_SVRISEND,"ҵ���ѹ�����ʱ��!");
          //return -5;               
      }     
  }
    
  /*����״̬��0-��Ч;��������Ч*/
  trim(SDB_SvrInfo.SVRSTATUS);
  if( SDB_SvrInfo.SVRSTATUS[0] != '0' )
  {
      LOG( LM_DEBUG, Fmtmsg( "������δ��Ч!״̬=[%s]",SDB_SvrInfo.SVRSTATUS), "INFO" );
      fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
      fpub_SetMsg(lXmlhandle,98728 , "������δ��Ч");
      return COMPRET_FAIL ;
    //  SetErrorMsg(lXmlhandle,BFE_ERR_SVRNOTBEGIN,"������δ��Ч!");
     // return -6;     
  }
  
  COMP_SOFTSETXML("/pabybh/req/svrStatus", SDB_SvrInfo.SVRSTATUS)
   LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    fpub_SetCompStatus(lXmlhandle, 0);

  return 0; 
}
