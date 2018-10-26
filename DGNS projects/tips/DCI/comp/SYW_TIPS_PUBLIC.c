/*#include <mp.h>;
*/
#include <stdio.h>;
#include <math.h>;
#include "gaps_head.h"
#include "gaps_icxp.h"
#include "gaps_func.h"

/********************************************************
* ����: FuncICXPPKG
* ����: ���ݱ���������ϳ�ͨѶ����
* ����˵��: 1:XML���
*     2:��������
*     3:����ͨѶ��ָ��
* ����: -1:ʧ��
*   >=0:�򱨺����ݳ���(�ɹ�)
********************************************************/
int SBATCH_FuncICXPPKG (HXMLTREE lXmlhandle, char * sPkgName, char *sDataBuf)
{
int iRet;
int iTotal,iCol,iCount,iOffset,ii,iFlag=0;
int iStartMM[COUNT_CYCLE],iLoopMM[COUNT_CYCLE],iEndMM[COUNT_CYCLE],iRecordMM[COUNT_CYCLE];
int iFlagMM[COUNT_CYCLE],iZCount[COUNT_CYCLE];
RMA_ICXPITEM  *ptrBwpz;


char sCyclePath[COUNT_CYCLE][LEN_TRC_ICXPCFG_FLDREF]; /*ѭ����λ��ʶ*/
char sZbwmc[LEN_TRC_ICXPCFG_RESNAME];
char sTmpStr[2048],sTmpStr2[2048],sTmpStr3[2048],sTmp[200],sTmp2[200],sZdcd[200];
char sFmt[20],sFgf[21],sfld_tmpbuf[1000];
int iTmp,iCd,iLen,ifdlen;
double dTmp;
/*************֧��ת������*************************/
IRESULT (*pConvfunc)();
long lConvfunc;
int iOffset0,iBuflen;
/*************֧��ת������*************************/

ICXPCFG SBwpz;

char sBuf[256];

  iTotal=0;
  iCol = -1;
  iCount = 0;
  iOffset = 0;
  memset(sCyclePath, 0, sizeof(sCyclePath));
  
  for (ii=0; ii<COUNT_CYCLE; ii++)
  {
    iRecordMM[ii] = 1;
    iFlagMM[ii] = LOOP_FALSE;
    iEndMM[ii] = 0;
  }
  if( prv_GetIcxpCfg(lXmlhandle ,(ICXPCFG *)&SBwpz,sPkgName)!= MID_SYS_SUCC ) 
  {
      LOGRET(FAIL,LM_STD,"��ȡICXP����[%s]����ʧ��",sPkgName )
  }

  
  /*���Ĳ�����*/
  iTotal = SBwpz.items;

  while (iCol < iTotal-1)
  {
    memset(sTmpStr2, 0, sizeof(sTmpStr2));
    memset(sTmpStr, 0, sizeof(sTmpStr));
    iCol++;
    ptrBwpz = (RMA_ICXPITEM *) &(SBwpz.itemcfg[iCol]);
    
    
    switch (toupper(ptrBwpz->fldtype[0]))     /*��������*/
    {   
    case VAL_TRC_ICXPCFG_FLDTYPE_S:    /*�ӱ���*/
           LOGRET(FAIL,LM_STD,"�ӱ����ݲ�֧��",ptrBwpz->fldref)
           break;
    case VAL_TRC_ICXPCFG_FLDTYPE_B:   /*�ɱ䱨��*/
           LOGRET(FAIL,LM_STD,"�ɱ䱨���ݲ�֧��",ptrBwpz->fldref)
           break;
    case VAL_TRC_ICXPCFG_FLDTYPE_M :  /*ѭ����ʼ*/
      /*ѭ��Ƕ��*/
 
      if ( (iFlag > 0) && ((iFlag -iCount)>0) )
        iCount++;
      iFlag++;
  
      if (iFlagMM[iCount] == LOOP_FALSE )  /*��һ��ѭ��*/
      {
        iStartMM[iCount] = iCol-1;/*��¼ѭ����ʼ*/          

        XMLPathGetParent(ptrBwpz->convexp,sZdcd,sTmp);
        func_GetPath(sZdcd, (char*)sCyclePath, iRecordMM, sBuf);
        strcat(sBuf, "/");
        strcat(sBuf, sTmp);
        /*ȡ��ѭ���Ĵ���(��ϸ��)*/

        if ( (iZCount[iCount] = xml_ElementCount( lXmlhandle, sBuf ))==-1 )
        { /* ʧ�� */
  
 
          LOGRET(FAIL,LM_STD,MSG_SYS_FAIL,"ȡXML���ݴ���")
        }

        /*�������ֵ�ȷ��ѭ���ֶ��Ƿ�Ϸ�*/
        sprintf(sCyclePath[iCount], ptrBwpz->convexp);
        for (ii=iCount+1;ii<COUNT_CYCLE;ii++)
          memset(sCyclePath[ii], 0, sizeof(sCyclePath[ii]));
      }

      /*���ظ���ʽ�ֱ���*/
      switch( ptrBwpz->cycletype[0] ) 
      {
      case VAL_TRC_ICXPCFG_CYCLETYPE_NULL:  /*������ѭ������ϸ����*/
        iFlagMM[iCount] = LOOP_TRUE;
        if (iRecordMM[iCount] > iZCount[iCount])
        {
          iFlagMM[iCount] = LOOP_FALSE;
        }
        break;

      case VAL_TRC_ICXPCFG_CYCLETYPE_DOWHILE: 
        /*����ѭ����ʽ*/
        /*!������,=����  ����������Ϊ�������ʽ*/
        /*$####...$Ϊ����Ϊ####...��Ŀ�ֵ�ֵ�Ƚ�*/
        /*"####..."Ϊ��####...�ַ����Ƚ�*/
        /*|####...|Ϊ��## ## ..ʮ�����ƴ��Ƚ�*/
        /*\####...\Ϊ����ֵ####..�Ƚ�*/
        if (iFlagMM[iCount] == LOOP_FALSE)
        {
          iFlagMM[iCount] = LOOP_TRUE;
          break;
        }
        else
        {
          iRecordMM[iCount]--;
          strcpy(sZdcd,ptrBwpz->tranlen);
        
          if (func_GetData(lXmlhandle,ptrBwpz->fldref,sTmpStr, sizeof(sTmpStr),(char*)sCyclePath, iRecordMM)!=0)
          {
            LOGRET(FAIL,LM_STD,MSG_SYS_FAIL,ptrBwpz->fldref)
          }

          switch ( getCond(sZdcd+2,sTmp) )
          {
          case VAL_ICXPCFG_CYCLECON_V:
                
            if (func_GetData(lXmlhandle,sTmp,sTmp2,sizeof(sTmp2),(char*)sCyclePath, iRecordMM)!=0)
            {
              LOGRET(FAIL,LM_STD,MSG_SYS_FAIL,sTmp)
            }

            if (sZdcd[0]=='!' )
            {
              if ( memcmp( sTmp2,sTmpStr,strlen(sTmp))!=0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            else 
            if ( sZdcd[0] == '=' )
            {
              if ( memcmp( sTmp2,sTmpStr,strlen(sTmp))==0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            break;
          case VAL_ICXPCFG_CYCLECON_H:
            iRet = convertH2C( sTmp,sTmp );
            if (sZdcd[0]=='!' )
            {
              if ( memcmp( sTmp, sTmpStr, iRet)!=0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            else
            if ( sZdcd[0] == '=' )
            {
              if ( memcmp( sTmp, sTmpStr, iRet)==0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            break;
        
          case VAL_ICXPCFG_CYCLECON_D:
            if (sZdcd[0]=='!' )
            {
              if ( atoi(sTmpStr)!=atoi(sTmp) )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            else
            if ( sZdcd[0] == '=' )
            {
              if ( atoi(sTmpStr)==atoi(sTmp) )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            break;
          case VAL_ICXPCFG_CYCLECON_S:
            if (sZdcd[0]=='!' )
            {
              if ( memcmp( sTmp,sTmpStr,strlen(sTmp))!=0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            else 
            if ( sZdcd[0] == '=' )
            {
              if ( memcmp( sTmp,sTmpStr,strlen(sTmp))==0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            break;
          default:
            break;
          /*�޴�������ʽ*/
          }
          iRecordMM[iCount]++;
        }
      break;
      
      case VAL_TRC_ICXPCFG_CYCLETYPE_FOR:
        if ( iFlagMM[iCount] == LOOP_TRUE )
        {
          if ( iLoopMM[iCount] <=0 )
          {
            iFlagMM[iCount] = LOOP_FALSE;
          }
        }
        else
        {
          if ( strlen(ptrBwpz->fldref) != 0 )
          {
            if (func_GetData(lXmlhandle,ptrBwpz->fldref, sTmpStr,sizeof(sTmpStr),(char*)sCyclePath, iRecordMM)!=0)
            {
              LOGRET(FAIL,LM_STD,MSG_SYS_FAIL,ptrBwpz->fldref)
            }
            iLoopMM[iCount] = atoi (sTmpStr);
            iFlagMM[iCount] = LOOP_TRUE;
          }
          else
          {
            iFlagMM[iCount] = LOOP_FALSE;
          }
        }
        break;
      default:
        LOGRET(FAIL,LM_STD,"�ظ���ʽ����",ptrBwpz->cycletype)
    
      }
        
      if (iFlagMM[iCount] == LOOP_FALSE)
      {
        if (iEndMM[iCount]==0)
        {
          for (ii=iCol; ii<iTotal; ii++)
          {
            if (SBwpz.itemcfg[ii].fldtype[0]==VAL_TRC_ICXPCFG_FLDTYPE_W)
            {
              iEndMM[iCount] = ii;
              break;
            }
          }
        }
          
        iCol = iEndMM[iCount];
        iEndMM[iCount] = 0;
        iRecordMM[iCount] = 1;
        iFlag--;
        if (iCount > 0 )
          iCount--;
      }
      break;
    case  VAL_TRC_ICXPCFG_FLDTYPE_W:  /*ѭ������*/
      iLoopMM[iCount]--;        /*ѭ����������һ*/
      iRecordMM[iCount]++;      /*�±��������һ*/
      iEndMM[iCount] = iCol;    /*��¼����λ��*/
      iCol = iStartMM[iCount];  /*ָ��ʼ*/
      iFlag--;
      break;
    default:/*ʵ������*/
      if ( (toupper(ptrBwpz->fldtype[0]) != VAL_TRC_ICXPCFG_FLDTYPE_H) &&
        (toupper(ptrBwpz->fldtype[0]) != VAL_TRC_ICXPCFG_FLDTYPE_A) ) 
      {
        /*
          Tianhc 2004-4-18 15:02
          �޸ģ�����û�ҵ��ڵ㣬��Ϊ�ǿն�����Ϊ�Ǵ�
        */
        if (xml_ElementExist(lXmlhandle,ptrBwpz->fldref) == 0)	/*������*/
              strcpy(sTmpStr,"");
        else
        {
	        iRet = func_GetData(lXmlhandle,ptrBwpz->fldref,sTmpStr,sizeof(sTmpStr),(char*)sCyclePath, iRecordMM);
	        if ((iRet == XML_ENONODE) || (iRet == XML_ENOATTR))
	        {
	          memset(sTmpStr, 0, sizeof(sTmpStr));
	          memset(sTmpStr, ptrBwpz->cfiller, sizeof(sTmpStr)-1);
	        }
	        else
	        if (iRet!=0)
	        {
	          LOGRET(FAIL,LM_STD,MSG_SYS_FAIL,ptrBwpz->fldref)
	        }
        }
      }
      else  /*����*/
        sprintf(sTmpStr,ptrBwpz->fldref);



      if (( ptrBwpz->tranlen[0] != '0') && (atoi(ptrBwpz->tranlen) == 0))
      {
        if (func_GetData(lXmlhandle,ptrBwpz->tranlen,sBuf,sizeof(sBuf),(char*)sCyclePath, iRecordMM)!=0)
        {
          LOGRET(FAIL,LM_STD,MSG_SYS_FAIL,ptrBwpz->tranlen)
        }
        iLen =  atoi(sBuf);
      }
      else
        iLen =  atoi(ptrBwpz->tranlen);
      iOffset0=iOffset;
      iBuflen=sizeof(sDataBuf);
      /*ת������������ֵת��*/
      if( strlen(ptrBwpz->convfunc)>0)    
      {
        /*�ԵǼǺ�������У���Ƿ� ���纯�������ڷ���ת�������������*/
        if ( fpub_GetFuncEntry(ptrBwpz->convfunc,&lConvfunc) != MID_SYS_SUCC )
        {
          LOGRET(MID_SYS_FUNCGETENTRY,LM_STD,
                 Fmtmsg(MSG_SYS_FUNCGETENTRY,ptrBwpz->convfunc),
                 "FuncICXPPKG")
        }
        pConvfunc=lConvfunc;

        if((ifdlen=xml_RelGetElement(lXmlhandle,ptrBwpz->fldref,
            sfld_tmpbuf,sizeof(sfld_tmpbuf)))==FAIL)
        {
          if(xml_GetLastError()==XML_ENONODE)
          {
            memset(sfld_tmpbuf,0,sizeof(sfld_tmpbuf));
            ifdlen=0;
          }
          else
          {         
            LOG(LM_DEBUG,Fmtmsg(MSG_SYS_XMLGET,ptrBwpz->fldref,GETXMLERR),
                "FuncICXPPKG")
            LOGRET(MID_SYS_PKGCONVFAIL,LM_STD,
                   Fmtmsg("ICXP�����ȡԪ������ʧ��"),
                   "FuncICXPPKG")
          }   
        }
        
        if((iRet=(IRESULT)(pConvfunc(lXmlhandle,sTmpStr,&ifdlen,
                       sizeof(sTmpStr),sDataBuf,&iBuflen,
                       &iOffset0,ptrBwpz->convexp,
                       NULL,NULL)))!=MID_SYS_SUCC)
        {
          LOGRET(MID_SYS_PKGEXECFUNC,LM_STD,
              Fmtmsg(MSG_SYS_PKGEXECFUNC,ptrBwpz->convfunc,
              ptrBwpz->convexp,iRet),"FuncICXPPKG")
        }
      }

      /*���ݴ������ͽ��д���*/
      switch (toupper(ptrBwpz->fldtype[0]))
      {
      case VAL_TRC_ICXPCFG_FLDTYPE_X: /*ʮ��������*/
        iCd=convertH2C(sTmpStr,sTmpStr2);
        break;
      case VAL_TRC_ICXPCFG_FLDTYPE_N: /*�����ֽ�����*/
        iTmp=atoi(sTmpStr)*pow(10,ptrBwpz->izoom);

        iCd = sizeof(short);
        iTmp = htons(iTmp);
        memcpy(sTmpStr2, &iTmp, iCd);
        break;        
      case VAL_TRC_ICXPCFG_FLDTYPE_I: /*����*/
        iTmp=atoi(sTmpStr)*pow(10,ptrBwpz->izoom);

        iCd = sizeof(long);
        memcpy(sTmpStr2, &iTmp, iCd);
        break;
      case VAL_TRC_ICXPCFG_FLDTYPE_D: /*����*/
        dTmp=atof(sTmpStr)*pow(10,ptrBwpz->izoom);

        iCd = sizeof(double);
        memcpy(sTmpStr2, &dTmp, iCd);
        break;
      case VAL_TRC_ICXPCFG_FLDTYPE_C: /*�ַ���*/
        if ( ptrBwpz->izoom != 0 || ptrBwpz->iprecision != 0)
        {
          dTmp=atof(sTmpStr)*pow(10,ptrBwpz->izoom);
          sprintf(sFmt,"%%.%df",ptrBwpz->iprecision);
          sprintf(sTmpStr,sFmt,dTmp);
        }

        if (ptrBwpz->cfiller!=0)
        {
          sprintf(sTmpStr2,sTmpStr);
          trim(sTmpStr2);
          iCd=strlen(sTmpStr2);
        }
        else
        {
          memset(sTmpStr2, 0, sizeof(sTmpStr2));
          memcpy(sTmpStr2, sTmpStr, iLen);
          iCd=iLen;
        }
        break;
      case VAL_TRC_ICXPCFG_FLDTYPE_A: /*�ַ�����*/
        sprintf(sTmpStr2,ptrBwpz->fldref);
        iCd=strlen(sTmpStr2);
        break;
      case VAL_TRC_ICXPCFG_FLDTYPE_H: /*ʮ�����Ƴ���*/
        iCd=convertH2C(ptrBwpz->fldref,sTmpStr2);
        break;
      default:
        LOGRET(FAIL,LM_STD,"δ֪����������",ptrBwpz->fldtype)
      }

      if (iLen > 0)
      {
        if (iCd < iLen)
        {
          memset(sTmpStr,ptrBwpz->cfiller,iLen);
          sTmpStr[iLen]=0;
          switch (toupper(ptrBwpz->iregular[0]))  
          {
          case VAL_TRC_ICXPCFG_IREGULAR_R:
            memcpy(sTmpStr+iLen-iCd,sTmpStr2,iCd);
            break;
          case VAL_TRC_ICXPCFG_IREGULAR_L:
          default:
            memcpy(sTmpStr,sTmpStr2,iCd);
          }
          if ( strcmp(ptrBwpz->fldref+strlen(ptrBwpz->fldref)-2,"mm") )
          {
          }
          else
          {
              strcpy(sTmpStr3,sTmpStr);
              memset(sTmpStr3,'*',strlen(sTmpStr));
          }

          memcpy( sDataBuf+iOffset,sTmpStr, iLen);
        }
        else
        {
          if ( strcmp(ptrBwpz->fldref+strlen(ptrBwpz->fldref)-2,"mm") )
          {
          }
          else
          {
             strcpy(sTmpStr3,sTmpStr2);
             memset(sTmpStr3,'*',strlen(sTmpStr2));
          }

          memcpy( sDataBuf+iOffset,sTmpStr2, iLen);
        }
        iOffset += iLen;
      }
      else
      {
        
        iLen = func_GetDiv(ptrBwpz->bseparator, ICXP_DIV, sFgf);
        
        if ( strcmp(ptrBwpz->fldref+strlen(ptrBwpz->fldref)-2,"mm") )
        {
        }
        else
        {
          strcpy(sTmpStr3,sTmpStr2);
          memset(sTmpStr3,'*',strlen(sTmpStr2));
        }
        
        memcpy( sDataBuf+iOffset, sTmpStr2, iCd);
        iOffset += iCd;
        if (iLen > 0)
        {
          memcpy( sDataBuf+iOffset, sFgf, iLen );
          iOffset += iLen;
        }
      }
    }

  }
  return iOffset;
}


/********************************************************
* ����: FuncICXPUPKG
* ����: ����ͨѶ�����ⱨ���ý��нⱨ
* ����˵��: 1:XML���
*     2:��������
*     3:����ͨѶ��ָ��
*     4:���ĳ���
* ����: -1:ʧ��
*   >=0:������ݳ���(�ɹ�)
********************************************************/
int SBATCH_FuncICXPUPKG (HXMLTREE lXmlhandle, char * sPkgName, char *sDataBuf, int iPkglen)
{
int iRet;
int iTotal,iCol,iCount,iOffset,ii,iFlag=0;
int iStartMM[COUNT_CYCLE],iLoopMM[COUNT_CYCLE],iEndMM[COUNT_CYCLE],iRecordMM[COUNT_CYCLE];
int iFlagMM[COUNT_CYCLE];
RMA_ICXPITEM  *ptrBwpz;

char sCyclePath[COUNT_CYCLE][LEN_TRC_ICXPCFG_FLDREF]; /*ѭ����λ��ʶ*/
char sZbwmc[LEN_TRC_ICXPCFG_RESNAME];
char sTmpStr[1000],sTmpStr2[1000],sTmpStr3[1000],sTmp[200],sTmp2[200],sZdcd[200];
char sFmt[20],sFgf[LEN_TRC_ICXPCFG_RESNAME];
int iTmp,iCd,iLen;
double dTmp;
ICXPCFG SBwpz;  

char sBuf[256];

/*************֧��ת������*************************/
IRESULT (*pConvfunc)();
long lConvfunc;
int iOffset0,iBuflen;
/*************֧��ת������*************************/
  iTotal=0;
  iCol = -1;
  iCount = 0;
  iOffset = 0;
  memset(sCyclePath, 0, sizeof(sCyclePath));  

  for (ii=0; ii<COUNT_CYCLE; ii++)
  {
    iRecordMM[ii] = 1;
    iFlagMM[ii] = LOOP_FALSE;
    iEndMM[ii] = 0;
  }
   /********************************************************************   
�޸�ȡ������Ϣ��ʽ,����֧�ֹ����ڴ�����ݿ�
  iRet = func_InsPack ( sPkgName, (ST_TRC_ICXPCFG *)&SBwpz, iCol, &iTotal );
**********************************************************************/ 
  if( prv_GetIcxpCfg(lXmlhandle,(ICXPCFG *)&SBwpz,sPkgName)!= MID_SYS_SUCC )
  {
       LOGRET(FAIL,LM_STD,Fmtmsg("��ȡICXP��������:[%s]ʧ��",sPkgName) , "")
  }
    
  
  /*��������������*/
  iTotal = SBwpz.items;
  printf("sPkgName:[%s],[%d]",sPkgName,iTotal);
  while (iCol < iTotal-1)
  {

    memset(sTmpStr2, 0, sizeof(sTmpStr2));
    memset(sTmpStr, 0, sizeof(sTmpStr));
    iCol++;
    /**************************
    ptrBwpz = &(SBwpz[iCol]);
    ***************************/
    ptrBwpz = (RMA_ICXPITEM *) &(SBwpz.itemcfg[iCol]);
    switch (toupper(ptrBwpz->fldtype[0]))     /*��������*/
    {  
     
    case VAL_TRC_ICXPCFG_FLDTYPE_S:    /*�ӱ���*/
   /**********************************************************
     �ݲ�֧�� ,��Ҫ�ݹ�ʵ�� 
      if ( (iRet = func_InsPack ( ptrBwpz->fldref, (ST_TRC_ICXPCFG*)&SBwpz, iCol, &iTotal )) !=0 )
      {
        LOGRET(FAIL,LM_DEBUG,"ȡ�ӱ��Ĵ���",ptrBwpz->fldref)
      }
      iCol--;
    ***************************************************************/ 
    LOGRET(FAIL,LM_STD,"�ɱ䱨���ݲ�֧��",ptrBwpz->fldref)
    break;
    case VAL_TRC_ICXPCFG_FLDTYPE_B:   /*�ɱ䱨��*/
          LOGRET(FAIL,LM_STD,"�ɱ䱨���ݲ�֧��",ptrBwpz->fldref)
          break;
    case VAL_TRC_ICXPCFG_FLDTYPE_M :  /*ѭ����ʼ*/
      /*ѭ��Ƕ��*/
      if ( (iFlag > 0) && ((iFlag -iCount)>0) )
        iCount++;
      iFlag++;
      if (iFlagMM[iCount] == LOOP_FALSE )  /*��һ��ѭ��*/
      {
        iStartMM[iCount] = iCol-1;/*��¼ѭ����ʼ*/

        sprintf(sCyclePath[iCount], ptrBwpz->convexp);
        for (ii=iCount+1;ii<COUNT_CYCLE;ii++)
          memset(sCyclePath[ii], 0, sizeof(sCyclePath[ii]));

      }

      /*���ظ���ʽ�ֱ���*/
      switch( ptrBwpz->cycletype[0] )
      {
      case VAL_TRC_ICXPCFG_CYCLETYPE_NULL:  /*������ѭ������ϸ����*/
        iFlagMM[iCount] = LOOP_TRUE;
        if (strlen(ptrBwpz->bseparator)>0)
        {
          iRet = func_GetDiv(ptrBwpz->bseparator, ICXP_DIV, sFgf);
          if (memcmp(sDataBuf+iOffset, sFgf, iRet)==0)
          {
            iFlagMM[iCount] = LOOP_FALSE;
            iOffset += iRet;
          }
        }
        break;
      case VAL_TRC_ICXPCFG_CYCLETYPE_DOWHILE:
        /*����ѭ����ʽ*/
        /*!������,=����  ����������Ϊ�������ʽ*/
        /*$####...$Ϊ����Ϊ####...��Ŀ�ֵ�ֵ�Ƚ�*/
        /*"####..."Ϊ��####...�ַ����Ƚ�*/
        /*|####...|Ϊ��## ## ..ʮ�����ƴ��Ƚ�*/
        /*\####...\Ϊ����ֵ####..�Ƚ�*/
        if (iFlagMM[iCount] == LOOP_FALSE)
        {
          iFlagMM[iCount] = LOOP_TRUE;
          break;
        }
        else
        {
          iRecordMM[iCount]--;
          strcpy(sZdcd,ptrBwpz->tranlen);
          if (func_GetData(lXmlhandle,ptrBwpz->fldref,sTmpStr,sizeof(sTmpStr),(char*)sCyclePath, iRecordMM)!=0)
          {
            LOGRET(FAIL,LM_STD,MSG_SYS_FAIL,ptrBwpz->fldref)
          }

          switch ( getCond(sZdcd+2,sTmp) )
          {
          case VAL_ICXPCFG_CYCLECON_V:
            if (func_GetData(lXmlhandle,sTmp, sTmp2,sizeof(sTmp2),(char*)sCyclePath, iRecordMM)!=0)
            {
              LOGRET(FAIL,LM_STD,MSG_SYS_FAIL,sTmp)
            }

            if (sZdcd[0]=='!' )
            {
              if ( memcmp( sTmp2,sTmpStr,strlen(sTmp))!=0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            else 
            if ( sZdcd[0] == '=' )
            {
              if ( memcmp( sTmp2,sTmpStr,strlen(sTmp))==0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            break;
          case VAL_ICXPCFG_CYCLECON_H:
            iRet = convertH2C( sTmp,sTmp );
            if (sZdcd[0]=='!' )
            {
              if ( memcmp( sTmp, sTmpStr, iRet)!=0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            else 
            if ( sZdcd[0] == '=' )
            {
              if ( memcmp( sTmp, sTmpStr, iRet)==0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            break;
          case VAL_ICXPCFG_CYCLECON_D:
            if (sZdcd[0]=='!' )
            {
              if ( atoi(sTmpStr)!=atoi(sTmp) )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            else
            if ( sZdcd[0] == '=' )
            {
              if ( atoi(sTmpStr)==atoi(sTmp) )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            break;
          case VAL_ICXPCFG_CYCLECON_S:
            if (sZdcd[0]=='!' )
            {
              if ( memcmp( sTmp,sTmpStr,strlen(sTmp))!=0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }
            else 
            if ( sZdcd[0] == '=' )
            {
              if ( memcmp( sTmp,sTmpStr,strlen(sTmp))==0 )
                iFlagMM[iCount] = LOOP_FALSE;
              else
                iFlagMM[iCount] = LOOP_TRUE; 
            }

            break;
          default:
            break;
          /*�޴�������ʽ*/
          }
          iRecordMM[iCount]++;
        }
        break;
      case VAL_TRC_ICXPCFG_CYCLETYPE_FOR:
        if ( iFlagMM[iCount] == LOOP_TRUE )
        {
          if ( iLoopMM[iCount] <=0 )
          {
            iFlagMM[iCount] = LOOP_FALSE;
          }
        }
        else
        {
          if ( strlen(ptrBwpz->fldref) != 0 )
          {
            if (func_GetData(lXmlhandle,ptrBwpz->fldref,sTmpStr,sizeof(sTmpStr),(char*)sCyclePath, iRecordMM)!=0)
            {
              LOGRET(FAIL,LM_STD,MSG_SYS_FAIL,ptrBwpz->fldref)
            }
            iLoopMM[iCount] = atoi (sTmpStr);
            iFlagMM[iCount] = LOOP_TRUE;
          }
          else
          {
            iFlagMM[iCount] = LOOP_FALSE;
          }
        }
        break;
      default:
        LOGRET(FAIL,LM_STD,"�ظ���ʽ����",ptrBwpz->cycletype)
      }
        
      if (iFlagMM[iCount] == LOOP_FALSE)
      {
        if (iEndMM[iCount]==0)
        {
          /*��ѭ������*/
          for (ii=iCol; ii<iTotal; ii++)
          {
            if (SBwpz.itemcfg[ii].fldtype[0]==VAL_TRC_ICXPCFG_FLDTYPE_W)
            {
              iEndMM[iCount] = ii;
              break;
            }
          }
        }
          
        iCol = iEndMM[iCount];
        iEndMM[iCount] = 0;
        iRecordMM[iCount] = 1;
        iFlag--;
        if (iCount > 0 )
          iCount--;
      }
      /*
      else
      {
        ��ӽڵ�
        iRet = xml_AddElement( lXmlhandle, ptrBwpz->convexp, NULL);
      }
      */
    break;
      
    case  VAL_TRC_ICXPCFG_FLDTYPE_W:  /*ѭ������*/
      iLoopMM[iCount]--;       /*ѭ����������һ*/
      iRecordMM[iCount]++;     /*�±��������һ*/
      iEndMM[iCount] = iCol;   /*��¼����λ��*/
      iCol = iStartMM[iCount]; /*ָ��ʼ*/
      iFlag--;
      break;
    case VAL_TRC_ICXPCFG_FLDTYPE_A:     /*�ַ�����*/
    case VAL_TRC_ICXPCFG_FLDTYPE_H: /*ʮ�����Ƴ���*/ 
      iOffset=iOffset+atoi(ptrBwpz->tranlen);  /*��������*/
      break;
    default: /*ʵ������*/
      if ( (ptrBwpz->tranlen[0] != '0') && (atoi(ptrBwpz->tranlen) == 0))
      {
        if (func_GetData(lXmlhandle,ptrBwpz->tranlen,sBuf,sizeof(sBuf), (char*)sCyclePath, iRecordMM)!=0)
        {
          LOGRET(FAIL,LM_STD,MSG_SYS_FAIL,ptrBwpz->tranlen)
        }
        iLen =  atoi(sBuf);
      }
      else
        iLen =  atoi(ptrBwpz->tranlen);
 
      memset(sTmpStr,0,sizeof(sTmpStr));
      if ( iLen!=0 )
      {/*����ģʽ*/
        memcpy(sTmpStr , sDataBuf + iOffset , iLen);
        iOffset += iLen;
        sTmpStr[iLen]='\0'; 

      }
      else
      {/*�ָ���*/
        iLen = 0;
        iTmp = func_GetWithDiv(sTmpStr,sDataBuf+iOffset,ptrBwpz->bseparator, &iLen);
        iOffset+=iTmp;

      }

      /*���к���ת��;*/
/*************֧��ת������*************************/
      iOffset0=iOffset;
      iBuflen=sizeof(sDataBuf);
      /*ת������������ֵת��*/
      if( strlen(ptrBwpz->convfunc)>0)    
      {
        /*�ԵǼǺ�������У���Ƿ� ���纯�������ڷ���ת�������������*/
        if ( fpub_GetFuncEntry(ptrBwpz->convfunc,&lConvfunc) != MID_SYS_SUCC )
        {
          LOGRET(MID_SYS_FUNCGETENTRY,LM_STD,
                 Fmtmsg(MSG_SYS_FUNCGETENTRY,ptrBwpz->convfunc),
                 "FuncICXPUPKG")
        }
        pConvfunc=lConvfunc;
        if((iRet=(IRESULT)(pConvfunc(lXmlhandle,sTmpStr,&iLen,
                       sizeof(sTmpStr),sDataBuf,&iBuflen,
                       &iOffset0,ptrBwpz->convexp,
                       NULL,NULL)))!=MID_SYS_SUCC)
        {
          LOGRET(MID_SYS_PKGEXECFUNC,LM_STD,
              Fmtmsg(MSG_SYS_PKGEXECFUNC,ptrBwpz->convfunc,
              ptrBwpz->convexp,iRet),"FuncICXPUPKG")
        }
      }
 
      switch (toupper(ptrBwpz->fldtype[0]))
      {
      case VAL_TRC_ICXPCFG_FLDTYPE_X: /*ʮ��������*/
        iLen = convertC2H( sTmpStr, iLen, sTmpStr2);
        sprintf(sTmpStr,sTmpStr2);
        break;
      case VAL_TRC_ICXPCFG_FLDTYPE_N: /*�����ֽ�����*/
        iTmp = *((short *)sTmpStr);
        iTmp = ntohs(iTmp)*pow(10,ptrBwpz->izoom);
        sprintf(sFmt,"%%.%dd",ptrBwpz->iprecision);
        sprintf(sTmpStr,sFmt,iTmp);
        break;
      case VAL_TRC_ICXPCFG_FLDTYPE_I: /*����*/
        iTmp=*((long *)sTmpStr)*pow(10,ptrBwpz->izoom);
        sprintf(sFmt,"%%.%dd",ptrBwpz->iprecision);
        sprintf(sTmpStr,sFmt,iTmp);
        break;
      case VAL_TRC_ICXPCFG_FLDTYPE_D: /*����*/
        dTmp=*((double*)sTmpStr)*pow(10,ptrBwpz->izoom);
        sprintf(sFmt,"%%.%df",ptrBwpz->iprecision);
        sprintf(sTmpStr,sFmt,dTmp);
        break;
      case VAL_TRC_ICXPCFG_FLDTYPE_C: /*�ַ���*/
        if ( ptrBwpz->izoom != 0 )
        {
          dTmp=atof(sTmpStr)*pow(10,ptrBwpz->izoom);
          sprintf(sFmt,"%%.%df",ptrBwpz->iprecision);
          sprintf(sTmpStr,sFmt,dTmp);
        }
        trim(sTmpStr);
        break;
      default:
        LOGRET(FAIL,LM_STD,Fmtmsg("δ֪����������[%s]",ptrBwpz->fldtype),"")
      }
      
      if ( strcmp(ptrBwpz->fldref+strlen(ptrBwpz->fldref)-2,"mm") )
      {
      	/***
            LOG(LM_DEBUG,Fmtmsg("��[%d],·��[%s] ֵ[%s]",ptrBwpz->fldsn,ptrBwpz->fldref,sTmpStr),"DEBUG-mm")
        ****/
      }
      else
      {
    	strcpy(sTmpStr3,sTmpStr);
        memset(sTmpStr3,'*',strlen(sTmpStr));
        /***
        LOG(LM_DEBUG,Fmtmsg("��[%d],·��[%s] ֵ[%s]",ptrBwpz->fldsn,ptrBwpz->fldref,sTmpStr3),"DEBUG")
        ****/
      }      
      if (func_SetData(lXmlhandle,ptrBwpz->fldref, sTmpStr,iLen,(char*)sCyclePath, iRecordMM)!=0)
      {
        LOGRET(FAIL,LM_STD,MSG_SYS_FAIL,ptrBwpz->fldref)
      }
    }
    
    if ( iOffset>=iPkglen )
      break;
  } 
  return iOffset; 
}


IRESULT prv_GetIcxpCfg(HXMLTREE lXmlHandle,ICXPCFG *pIcxpcfg,char *sIResname)
{
/*#ifdef USE_SHMRMA*/
long lResStart;
char sBuf[50];
long lRmaStart;

  if ( !lXmlHandle || !*sIResname || !sIResname)
    LOGRET(MID_SYS_INVALID,LM_WARNING,MSG_SYS_INVALID,"fpub_GetIcxpCfg")
  
  pstrcopy(pIcxpcfg->resname,sIResname,sizeof(pIcxpcfg->resname));
#ifdef DEBUG
/*
  LOG(LM_DEBUG,Fmtmsg("��ȡ��Դ=[%s]����",sIResname),"fpub_GetIcxpCfg")
*/
#endif
  pIcxpcfg->curitem=0;

  if ( xml_GetElement(lXmlHandle,XMLNM_RMAHEAD,sBuf,sizeof(sBuf)) ==FAIL )
    LOGRET(MID_SYS_FAIL,LM_WARNING,
           Fmtmsg(MSG_SYS_XMLGET,XMLNM_RMAHEAD,GETXMLERR),
           "fpub_GetIcxpCfg")
  lRmaStart = atol(sBuf);
    
  if ( rma_GetResCfg(lRmaStart,VAL_RESCLASS_PICXP,sIResname,&lResStart) 
       != MID_SYS_SUCC )
    LOGRET(MID_SYS_FAIL,LM_WARNING,
           Fmtmsg(MSG_SYS_RMAGETICXP,sIResname),"fpub_GetIcxpCfg")
  pIcxpcfg->items=((RMA_ICXP*)lResStart)->items;
  
  memcpy(pIcxpcfg->itemcfg,(char*)(lResStart+sizeof(RMA_ICXP)),
         sizeof(RMA_ICXPITEM)*pIcxpcfg->items);
/*#else  /*Else of USE_SHMRMA*/
  /*LOG(LM_STD,Fmtmsg("��֧�ַǹ����ڴ�ȡICXP�������õķ�ʽ!"),"ERROR");
  return -9; 
#endif End of USE_SHMRMA*/
  return MID_SYS_SUCC; 
}

/*ת��Ϊ��д���*/
int prv_get_dxje(double dInJe,char *obj)
{
	int i, j, c, k, l;  /*������*/
	static char *larr[]={"��","��","Ԫ","ʰ","��",
                        "Ǫ","��","ʰ","��","Ǫ",
                        "��","ʰ","��","Ǫ","��"};
	static char *sarr[]={"��","Ҽ","��","��","��",
                        "��","½","��","��","��"};
	char  *parr[30],src[30];

	sprintf(src,"%.2f",dInJe);

	c=k=l=0;
	i=strlen(src);

	obj[0]=src[i-1];
	obj[1]=src[i-2];
	for(j=2;j<i-1;j++) 
		obj[j]=src[i-j-2]; /*С���㲻Ҫ*/

	i=i-1;
	obj[j]=0;

	for(j=i-1;j>=0;j--)     /*����ת�ɺ���,��ָ����parr*/
	{
		k=obj[j]-'0';
		if (k==0)       /*��λֵΪ��*/
		{
			if(strcmp(larr[j],"Ԫ")==0||strcmp(larr[j],"��")==0
                                ||strcmp(larr[j],"��")==0)
			{
				if (c==1)       /*��һλ����*/
				{
					if ((l<2)||(strcmp(parr[l-2],"��")!=0)
                                                || (strcmp(larr[j],"��")!=0))
					{
						parr[l]=parr[l-1];
						parr[l-1]=larr[j];
						l++;
					}
				}
				else
				{
					parr[l]=larr[j];
					l++;
					parr[l]=sarr[k];
					l++;
					c=1; /*��λ����*/
				}
			}               /*"��"��"��"��"Ԫ" λ����*/
			else
			{
				if (c==1);      /*���� "��" ������*/

				else
				{
					parr[l]=sarr[k];
					l++;
					c=1;
				}
			}
		}
		else
		{
			c=0;                    /*��λ������*/
			parr[l]=sarr[k];
			l++;
			parr[l]=larr[j];
			l++;
		}
	}

	if(strcmp(parr[l-1],"��")==0)
		parr[l-1]=larr[14];             /*���һλ�����������滻*/

	obj[0]=0;
	for(j=0;j<l;j++)
		strcat(obj,parr[j]);            /*ƴװ������Ĵ�*/

	/*������Ϊ0.01Ԫ��ԭ����������Ԫ��Ҽ�֡����ڴ��޸�*/
	if(1.000000 > dInJe)
		{
			char temp[30] = {0};			
			strcpy(temp, "��");
			strcat(temp, obj);
			strcpy(obj, temp);						
		}
		
	return 0;
} 

int prv_GenSerino(HXMLTREE lXmlhandle, char *pnode, int nodeSize)
{
	int iMode = 0;
	int iRet = 0;
	char sBuf[255];

	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_SOFTGETXML("/tipsx/pub/mode", sBuf);
	if (strlen(sBuf) == 0) {
		LOG(LM_STD, "������ˮ��ʧ�ܣ���ȡ��ˮ��ģʽʧ��", "ERROR");
		return -1;
	}
	iMode = atoi(sBuf);
	if (0 == iMode) {
		iRet = prv_GenSerinoSingle(lXmlhandle,pnode,nodeSize);
	}
	else if (1 == iMode) {
		iRet = prv_GenSerinoHA(lXmlhandle,pnode,nodeSize);
	}
	else {
		LOG(LM_STD, Fmtmsg("δ֪��ģʽ��%d��", iMode), "ERROR");
		return -1;
	}
	return iRet;
}

/*����ģʽ�����µ��ۺ�ǰ����ˮ��*/
int prv_GenSerinoSingle(HXMLTREE lXmlhandle, char *pnode, int nodeSize)
{
    int ret;
    char sLSHPath[60];
    char sBuf[32];
    fpub_InitSoComp(lXmlhandle);
    LOG(LM_DEBUG, "prv_GenSerinoSingle", "INFO");
	
    memset(sLSHPath, 0x00, sizeof(sLSHPath));
    snprintf(sLSHPath, sizeof(sLSHPath), "/tmp/newzhqzlsh");
    
    ret=fpub_ExGenSerialno(lXmlhandle,sLSHPath);
    if (ret!=MID_SYS_SUCC)
    {
        LOG(LM_STD,Fmtmsg("�����µ��ۺ�ǰ����ˮ��ʧ�ܣ�"),"");
        return -1;
    }	
    memset(sBuf, 0x00, sizeof(sBuf));
    COMP_SOFTGETXML(sLSHPath, sBuf)
    pstrcopy(pnode, sBuf, nodeSize);   
    ret = atoi(sBuf);
    return ret;  
}


/*��Ⱥģʽ�����µ��ۺ�ǰ����ˮ��*/
int prv_GenSerinoHA(HXMLTREE lXmlhandle, char *pnode, int nodeSize)
{
    int ret;
	
    char sErrmsg[1024];
	char sValue[16];
    char sSql[255];
	LOG(LM_DEBUG, "prv_GenSerinoEH", "INFO");
	memset(sErrmsg, 0x00, sizeof(sErrmsg));
	memset(sValue, 0x00, sizeof(sValue));
	snprintf(sSql, sizeof(sSql), "select SEQ_SERIAL.nextval from ywty_xtywzt");

	LOG(LM_DEBUG, Fmtmsg("%s", sSql), "DEBUG");
	ret = DBSelectToMultiVarChar(sErrmsg, sSql, sValue);
	LOG(LM_DEBUG, Fmtmsg("������ˮ�� %s", sValue), "DEBUG");
    if (ret <= 0)
    {
        LOG(LM_STD,Fmtmsg("�����µ��ۺ�ǰ����ˮ��ʧ�ܣ�"),"");
        return -1;
    }	 
	pstrcopy(pnode, sValue, nodeSize); 
    ret = atoi(sValue);
    return ret;  
}


/********************************************************
* ����: prv_SelMulToStruct
* ����: DCI��ѯ����ֶ����ṹ��
* ����˵��: 1:
*     2:
*     3:
*			4:
* ����: -1:ʧ��
*   >=0:�򱨺����ݳ���(�ɹ�)
********************************************************/
int prv_SelMulToStruct( const char* sSql, FLD_DESC desc_arr[], int desc_num, void* pdes)
{
    CURSOR cur;
    char szErrMsg[512];
    
    if( sSql == NULL || pdes == NULL || desc_arr == NULL || desc_num <= 0)
    {
        LOG(LM_STD, Fmtmsg("���������"), "WARNING");
        return -1;
    }
    LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"DEBUG");
    cur = DCIDeclareCursor( sSql, DCI_DEFAULT);
    if (cur == INVALID_CURSOR)
    {
        LOG(LM_STD, Fmtmsg("�α궨��ʧ��[%s]-[%s]",  DCILastError(), sSql), "ERROR");
        return -1;
    }
    LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"DEBUG");
    if(DCIExecute(cur) == -1)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��[%s]", DCILastError() ), "ERROR");
        DCIFreeCursor(cur);
        return -1;
    }
 		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"DEBUG");
    int rs = 0;
    if( 0 > ( rs = DBFetch( cur, desc_arr, desc_num, pdes, szErrMsg ) ) )
    {
        LOG(LM_STD, Fmtmsg("�α��ȡ��¼����[%s]",  szErrMsg ), "ERROR");
        return -1;
    }
 		
 		DCIFreeCursor(cur);
    return rs;
}
