/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.0)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:fprv_app.c
�ļ�����:ƽ̨˽��EC��������(������������)
�� Ŀ ��: AGENT2.0��Ŀ��
�� �� Ա: YangDong ����
��������: 

��    ��:
�޸�����:20090702
�޸�����:�������кţ���ˮ��ʱ��ʹ��for update�������ݡ�

�� �� Ա: YangDong
�޸�����:20140828
�޸�����:DCI����
*********************************************************************/
#include <stdio.h>
#include <math.h>
#include <dlfcn.h>
#include <ctype.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <sys/timeb.h>

#include "gaps_head.h"
#include "../incl/app_head.h"

/* dci �����װ���� */
/* ��ѯһ����¼���ṹ���� */
/*
����: ��ѯ���������ṹ��
����ֵ:
    <0 ʧ��
    =0 ���޼�¼
    >0 ��ѯ�ɹ�
*/
int fprv_SelToStruct( const char* sSql, FLD_DESC desc_arr[], int desc_num, void* pdes)
{
    CURSOR cur;
    char szErrMsg[512];

    if( sSql == NULL || pdes == NULL || desc_arr == NULL || desc_num <= 0)
    {
        LOG(LM_STD, Fmtmsg("���������"), "WARNING");
        return -1;
    }
    cur = DCIDeclareCursor( sSql, DCI_DEFAULT);
    if (cur == INVALID_CURSOR)
    {
        LOG(LM_STD, Fmtmsg("�α궨��ʧ��[%s]-[%s]",  DCILastError(), sSql), "ERROR");
        return -1;
    }
    if(DCIExecute(cur) == -1)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��[%s]", DCILastError() ), "ERROR");
        DCIFreeCursor(cur);
        return -1;
    }

    int rs = 0;
    if( 0 > ( rs = DBFetch( cur, desc_arr, desc_num, pdes, szErrMsg ) ) )
    {
        LOG(LM_STD, Fmtmsg("�α��ȡ��¼����[%s]",  szErrMsg ), "ERROR");
        return -1;
    }
    DCIFreeCursor(cur);  /*����©��*/
    return rs;
}
  
/************************************************************************
���ܣ� �������б��
************************************************************************/
long fprv_getSeqno(char *pKey, long *iSeqno)
{
    long iValueNew=0;
    char sXlJz[20+1];
    char sValue[51];
    char sSql[512];
    int  iRet = -1;
    char sDbType[128];

    APP_XLKZ sdb_app_xlkz;
    
    *iSeqno=0;
    
    memset(sXlJz,0,sizeof(sXlJz));
    memset(&sdb_app_xlkz,0,sizeof(APP_XLKZ));
    strncpy(sXlJz, pKey, sizeof(sXlJz)-1);
    if ( 0 == sXlJz[0] )
    {
        LOG(LM_STD,Fmtmsg("���м�ֵ����Ϊ��[%s]",sXlJz),"ERROR");
        return -1;
    }    
    trim(sXlJz);
    
    memset( sSql, 0x00, sizeof( sSql ) );
    
    memset( sDbType, 0x00, sizeof( sDbType ) );
    sprintf(sDbType, "%s", getenv("DB"));
    trim( sDbType );
    
    DCIBegin(); /*add by chenxm 20140114*/
    
    if( memcmp( sDbType,"INFORMIX",8 ) == 0 )
        snprintf( sSql, sizeof( sSql ), "SELECT * FROM app_xlkz WHERE pkey='%s' FOR UPDATE OF curr_value", sXlJz );
    else if( memcmp( sDbType,"DB2",3 ) == 0 )
        snprintf( sSql, sizeof( sSql ), "SELECT * FROM app_xlkz WHERE pkey='%s' WITH RS USE AND KEEP UPDATE LOCKS", sXlJz );
    else if( memcmp( sDbType,"ORACLE",6 ) == 0 )
        snprintf( sSql, sizeof( sSql ), "SELECT * FROM app_xlkz WHERE pkey='%s' FOR UPDATE", sXlJz );
    else
        LOG(LM_STD,Fmtmsg("���黷������DB����[%s]", sDbType),"ERROR");

    iRet = fprv_SelToStruct( sSql, SD_APP_XLKZ, NUMELE(SD_APP_XLKZ), &sdb_app_xlkz );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("ȡ���п�����Ϣʧ��[app_xlkz],pkey=[%s][%d]",sXlJz, iRet ),"ERROR");
        DCIRollback();
        return -1;
    }
    if ( iRet == 0 )
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("������Ϣ������[%s]",sXlJz ),"ERROR");
        return -1;
    }
    trim(sdb_app_xlkz.remark);
    
    iValueNew = sdb_app_xlkz.pinc + sdb_app_xlkz.curr_value;

    if( iValueNew > sdb_app_xlkz.max_value )
    {
        iValueNew = sdb_app_xlkz.min_value;
    }

    memset( sSql, 0x00, sizeof( sSql ) );
    snprintf( sSql, sizeof( sSql ) , " UPDATE app_xlkz SET curr_value=%d WHERE pkey='%s'",iValueNew, sXlJz  );
    iRet = DCIExecuteDirect( sSql );
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("�������п�����Ϣʧ��[app_xlkz],pkey=[%s],[%s]",sXlJz,DCILastError() ),"ERROR");
        DCIRollback();
        return -1;
    }

    /* informix ����Ƕ�ײ�֧�� */
    if( memcmp( sDbType,"INFORMIX",8 ) != 0 )
    {
        if( DCICommit() == -1 )
        {
            LOG(LM_STD,Fmtmsg("�������п�����Ϣʧ��[%s]",DCILastError() ),"ERROR");
            DCIRollback();
            return -1;
        }
    }

    LOG(LM_DEBUG,Fmtmsg("  -->ȡȡ���е�ǰֵ[%ld]",sdb_app_xlkz.curr_value),"INFO");
    
    *iSeqno = sdb_app_xlkz.curr_value;
    return (*iSeqno);
}

/* ����˽����ˮ�� */
IRESULT fprv_getPrivate(char *pkey, int *llsh, char *scch, char *sywrq)
{
    int iLshNew=0;
    char sCpdm[ 16+1 ];
    char sSql[512];
    APP_YWRQ  sdb_app_ywrq;
    int  iRet = -1;
    char sDbType[128];

    char sLsh[51];
    
    memset( &sdb_app_ywrq, 0x00, sizeof( sdb_app_ywrq ) );
    memset(sCpdm, 0, sizeof( sCpdm ) );

    strncpy( sCpdm, pkey, sizeof( sCpdm ) - 1 );
    trim( sCpdm );

    memset( sDbType, 0x00, sizeof( sDbType ) );
    sprintf(sDbType, "%s", getenv("DB"));
    trim( sDbType );

    DCIBegin(); /*add by chenxm 20140114*/
    
    if( memcmp( sDbType,"INFORMIX",8 ) == 0 )
        snprintf( sSql, sizeof( sSql ),  "SELECT * FROM app_ywrq WHERE pkey ='%s' FOR UPDATE OF curr_value", sCpdm );
    else if( memcmp( sDbType,"DB2",3 ) == 0 )
        snprintf( sSql, sizeof( sSql ),  "SELECT * FROM app_ywrq WHERE pkey ='%s' WITH RS USE AND KEEP UPDATE LOCKS ", sCpdm );
    else if( memcmp( sDbType,"ORACLE",6 ) == 0 )
        snprintf( sSql, sizeof( sSql ),  "SELECT * FROM app_ywrq WHERE pkey ='%s' FOR UPDATE", sCpdm );
    else
        LOG(LM_STD,Fmtmsg("���黷������DB����[%s]", sDbType),"ERROR");
  
    iRet = fprv_SelToStruct( sSql, SD_APP_YWRQ, NUMELE(SD_APP_YWRQ), &sdb_app_ywrq);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("ȡҵ��������Ϣʧ��[app_xlkz],pkey=[%s],ret[%d][%s]",sCpdm,iRet,DCILastError() ),"ERROR");
        DCIRollback();
        return -1;
    }
    if ( iRet == 0 )
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("ҵ�����ڲ�����[%s]",sCpdm),"ERROR");
        return -1;
    }

    iLshNew=0;
    iLshNew= sdb_app_ywrq.lsh + 1;
    
    /* ѭ������ */
    if ( iLshNew >=  APP_CPDM_MAXSERIAL )
        iLshNew=1;
    
    memset( sSql, 0x00, sizeof( sSql ) );
    snprintf( sSql, sizeof( sSql ), "UPDATE app_ywrq SET lsh = %d WHERE pkey ='%s' ",iLshNew, sCpdm );
    iRet = DCIExecuteDirect( sSql );
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("����ҵ��˽����ˮ��ʧ��: ��Ʒ����[%s],[%s]",sCpdm,DCILastError()),"ERROR") ;
        DCIRollback();
        return -1;
    }

    /* informix ����Ƕ�ײ�֧�� */
    if( memcmp( sDbType,"INFORMIX",8 ) != 0 )
    {  
        if( DCICommit() == -1 )
        {
            LOG(LM_STD,Fmtmsg("����ҵ��˽����ˮ��ʧ��: ��Ʒ����[%s],[%s]",sCpdm,DCILastError() ),"ERROR") ;
            DCIRollback();
            return -1;
        }
    }
    
    /* ҵ����ˮ */
    *llsh = sdb_app_ywrq.lsh ;
    /* ҵ������ */
    strcpy( sywrq, sdb_app_ywrq.ywrq );
    /* ���κ� */
    strcpy( scch, sdb_app_ywrq.cch );

    return (*llsh);
}
  
/* ��ȡʱ������� */
int fprv_gettimeStamp(char *pdate,char *ptime,char *timeStamp)
{
    static  struct timeb tp;
    static  struct tm *ptm;
  
    if ( pdate == NULL || ptime==NULL || timeStamp==NULL )
        return -1;
                
    ftime(&tp);
    ptm = localtime(&tp.time);
  
    snprintf(pdate,9,"%d%02d%02d", ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday);
    snprintf(ptime,7,"%02d%02d%02d", ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    snprintf(timeStamp,18,"%d%02d%02d%02d%02d%02d%03d", ptm->tm_year+1900,\
        ptm->tm_mon+1, ptm->tm_mday, ptm->tm_hour, ptm->tm_min, ptm->tm_sec, tp.millitm);
    return 0;
}
  
  /*ͳ���ַ�����ĳһ�ַ�����*/
int fprv_countchar(char *src,char ch)
{
    int i,iCount;
    int iLen,iCnt=0;
  
    iLen = strlen(src);
    iCount = 0;
    for(i=0;i<iLen;i++)
    {
        if(src[i]==ch)
        {
            iCount++;
        }
    }
      
    return iCount;
}
  
  /* ˽�к��� */
static char * getItemValue(char * src, char * split, char * out)
{
     char * p;
     int n = 0;
    
     while ( src != NULL )
     {
         if ( strncmp(src, split, strlen(split)) == 0 )
             break;
          out[n++] = *src ++;
     }
     out[n] = 0; 
     return out;
}

  /* ˽�к��� */
static char * getItemAddr(char * src, int index, char * split)
{
    char * p;
    int n;
    
    if (index < 0)
    return NULL;
    p = src;
    for (n = 0; n < index; n++)
    {
        p = (char *)strstr(p, split);
        if (p == NULL)
           return NULL;
        p += strlen(split);
    } 
    return p;
}
  
  /* ��ȡ�ָ���Ӵ����� */
char * fprv_getSubItem(char * src, int index, char * split, char *out)
{
    char * p;
     
    p = getItemAddr(src, index, split);
          
    if (p == NULL)
    {
        return NULL;
    }
    else
    {   
        getItemValue(p, split, out);
    }

    return out;
}
  
/*****************************************************
   ��������:  fprv_checkDate(char *date)
   ��������:  У�����ڵĺϷ���
   ��������:  date : �����ַ���
                  ��ʽ��YYYYMMDD
   ��������:   =  0: ���ںϷ�
               = -1: ��ݷǷ�
               = -2���·ݷǷ�
               = -3�����ڷǷ�
   ����˵��:  
   �޸�˵��:  
*****************************************************/
int fprv_checkDate(char *date) 
{
    int iYear, iMonth, iDay;
    char sYear[5], sMonth[3], sDay[3];
    int i;
      
    if ( strlen(date)<=0 || strlen(date)>8 )
        return -1;
             
    for ( i=0; i<strlen(date); i++)
    {
        if ( !isdigit(date[i]) )
            return -1;
    }
    memset(sYear, 0x00, sizeof(sYear));
    memset(sMonth, 0x00, sizeof(sMonth));
    memset(sDay, 0x00, sizeof(sDay));
    strncpy(sYear, date, 4);
    strncpy(sMonth, date+4, 2);
    strncpy(sDay, date+6, 2);
      
    iYear = atoi(sYear); iMonth = atoi(sMonth); iDay = atoi(sDay);
    /*���У��*/
    if (iYear  <= 0 || iYear > 9999)
        return -1;
    /*�·�У��*/
    if (iMonth <= 0 || iMonth > 12)
        return -2;
    /*����У��*/
    if (iDay   <= 0 || iDay >RMONTHDAYS(iMonth, iYear))
        return -3;
    return 0;
}
  
/*****************************************************
   ��������:  fprv_dateOffSet()
   ��������:  ����ƫ�Ƽ���
   ��������:  date : �����ַ���
                  ��ʽ��YYYYMMDD
           steps: ƫ������
   ��������: >0  ƫ�ƺ������
             <0  ���ڷǷ�
   ����˵��:  
   �޸�˵��:  
*****************************************************/
int fprv_dateOffSet(char *currdate,int steps)
{
    time_t  now,time1;
    int retdate,ndays=0,n;
    struct tm *ptm,tm1;
    char yy[5],mm[3],dd[3];
    
    memset(yy,0,sizeof(yy));
    memset(mm,0,sizeof(mm));
    memset(dd,0,sizeof(dd));
    memcpy(yy,currdate,4);yy[4]=0;
    memcpy(mm,currdate+4,2);mm[2]=0;
    memcpy(dd,currdate+6,2);dd[2]=0;
    ndays=steps;
    /*���ڷǷ�*/
    if ( fprv_checkDate(currdate) != 0)
        return -1;
    time(&now);
    tm1 = *localtime(&now);
    tm1.tm_year = atoi(yy)-1900;
    tm1.tm_mon = atoi(mm)-1;
    tm1.tm_mday = atoi(dd);
    time1 = mktime(&tm1);
  
    n=(int)(difftime(time1,now)/(60*60*24));
    ndays+=n;
    now += ndays * 3600 * 24;
  
    ptm = localtime(&now);
    retdate = (ptm->tm_year+1900) * 10000 + (ptm->tm_mon + 1) * 100 + ptm->tm_mday;
    return retdate;
}

/**************************************************************************
��������:int GetValueFromStr(char *str,char *buff,char *buff2)
��������:ȡ�ַ���������������ɵĴ�
��������: 
         str   ԭ�ַ���
         buff  ��Ž���ַ���
         buff2 ���ʣ���ַ���
��������: 0
���ӣ�  
         str = "HUNDSUN12345" 
         GetValueFromStr( str, buff)
         buff = "12345"
         buff2 ="HUNDSUN"
**************************************************************************/
int GetValueFromStr(char *str,char *buff,char *buff2)
{

    int i,ilen;
    ilen = strlen(str);
    for(i=ilen;i>0;i--)
        if (str[i-1]<'0' || str[i-1]>'9')
            break;
    memcpy(buff,str+i,ilen-i);
    memcpy(buff2,str,i);
    return 0;
}
/**************************************************************************
��������:int calcadd(char *strsrc , int num, char *buff)
��������:���ַ����ӷ�����
��������: 
         str  ԭ���ִ�ŵ��ַ���
         num  ��Ҫ�ӵ����֣�ֻ�������� 
         buff ��Ž���ַ���
��������: 0
���ӣ�  
         strsrc = "199999999999999" num = 11         
         calcadd( strsrc, num, buff) 
         buff = "200000000000010"
**************************************************************************/
int calcadd(char *strsrc , int num,char *buff)
{
    char tmp[20],srcstr[100],deststr[100];
    int ilen,ii,inum,nReserve;
    long lnum;
    
    memset(srcstr,0,sizeof(srcstr));
    strcpy(srcstr,strsrc);
    ilen = strlen(srcstr);
    inum = ilen / 4;
    nReserve = ilen % 4;
    
    for(ii=inum; ii>0; ii--)
    {
        memset(tmp , 0, sizeof(tmp));
        memcpy(tmp , srcstr + ilen - (inum-ii+1)*4, 4);
        lnum = atoi(tmp) + num;
        sprintf(tmp,"%ld",lnum);
        if (strlen(tmp) > 4)
        {
            memcpy(srcstr + ilen - (inum-ii+1)*4,tmp + strlen(tmp) - 4,4);
            tmp[strlen(tmp) - 4] = 0;
            num = atoi(tmp);
        }
        else
        {
            sprintf(tmp,"%04ld",lnum);
            memcpy(srcstr + ilen - (inum-ii+1)*4,tmp + strlen(tmp) - 4,4);
            num = 0;
            break;
        }
    }
    if(nReserve)
    {
        memset(tmp , 0, sizeof(tmp));
        memcpy(tmp , srcstr , nReserve);
        lnum = atol(tmp) + num;
        sprintf(tmp,"%ld",lnum);
    }
    else
    {
        memset(tmp , 0, sizeof(tmp));
        if(num > 0) 
            sprintf(tmp,"%ld",num);
    }
    
    trim(tmp);
    strcpy(buff,tmp);
    strcat(buff,srcstr + nReserve);
    memset(tmp, 0, sizeof(tmp));
    memset(deststr, 0, sizeof(deststr));
    
    /*sprintf(tmp, "%%0%ds",     ilen);  linux �� %04s,������ǿո������0*/
    
    if (ilen - strlen(buff)>0)
    {
        sprintf(tmp, "%%0%dd%%s",     ilen - strlen(buff));
        sprintf(deststr, tmp, 0,buff);
    }
    else
        sprintf(deststr, "%s", buff);

    memset(buff, 0, sizeof(buff));
    strcpy(buff, deststr);
    return 0;
}
/**************************************************************************
��������:int get_ch_count(char *buf, int n)
��������:ȡ������ֵĸ���
��������: 
         buf  Ŀ���ַ���
         n    ��Ҫ����ĳ���
��������: ������ֵĸ���
���ӣ�  
         get_ch_count("���",4) == 4
         get_ch_count("�����?",7) == 6
         get_ch_count("�����",8) == 8
         һ����� get_ch_count()%2 ʹ�ã������ж��ַ����Ƿ���ڰ������
**************************************************************************/
int get_ch_count(char *buf, int n)
{
    int i, count;

    for (i = 0, count = 0; i < n; i++)
        if ((unsigned char)buf[i] >= 0xa0)
            count++;
    return count;
}

/*дϵͳ����־*/
int LOG_Ctrl(HXMLTREE lXmlhandle, char *file, int line, int msglevel, char *mainmsg, char * secmsg)
{
    char sbuf[3]={0};
    char sTmp1[1024]={0},sTmp2[32]={0};
    SFmtmsg(sTmp1,sizeof(sTmp1),"%s",mainmsg);
    SFmtmsg(sTmp2,sizeof(sTmp2),"%s",secmsg);

    /* ȡ��־ģʽ */
    COMP_SOFTGETXML(XMLNM_APP_CPXX_RZMS,sbuf);
    trim(sbuf);

    /*LOG(LM_STD,Fmtmsg("��ȡmsglevel[%d]sbuf[%s]ִ�п�ʼ",msglevel,sbuf),"");*/
    if (sbuf[0] == '0') /* ����ģʽ */
    {
        WriteSBLLog(LM_STD, SYS_LOGNAME, file, line, LLOG_HEAD, "[%s] [%s]",sTmp1,sTmp2);
        return 0;
    }
    else if (sbuf[0] == '1' && msglevel <= LM_STD)  /* ����ģʽ */
    {
        WriteSBLLog(msglevel, SYS_LOGNAME, file, line, LLOG_HEAD, "[%s] [%s]",sTmp1,sTmp2);
        return 0;
    }
    else 
    { 
        WriteSBLLog(msglevel, SYS_LOGNAME, file, line, LLOG_HEAD, "[%s] [%s]",sTmp1,sTmp2);
        return 0;
    }
}

/* ͳ�Ʊ��¼��
   ֧�ַ������,���ϲ�ѯ����*/
int prv_CntSql(char * sCntSql, int *iCntVal, char *errmsg)
{
    char     sSqltmp[1024];
    char     sBuf[32];
    char     sErrmsg[512];
    int      iRet = -1;

    *iCntVal=0;
    trim(sCntSql);
    if(strlen(sCntSql) <= 0)
    {
        strcpy(errmsg, "��ѯ���Ϊ��");
        return -1;
    }

    memset(sSqltmp, 0, sizeof(sSqltmp));
    snprintf(sSqltmp,sizeof(sSqltmp),"%s",sCntSql);

    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqltmp);
    if( iRet == -1)
    {
        strcpy( errmsg, "���ݿ����ʧ��" );
        return -1;
    }
   
    *iCntVal = atoi( sBuf );

    LOG(LM_DEBUG,Fmtmsg("ͳ�����[%s],��¼�ϼ�=[%d]",sSqltmp,*iCntVal),"DEBUG");

    return 0;
}
