/********************************************************************
版权所有:杭州恒生电子股份有限公司
项目名称:中间业务平台项目(AGENT2.0)
版    本:V4.1.0.1
操作系统:
文件名称:fprv_app.c
文件描述:平台私有EC函数集合(方便各组件调用)
项 目 组: AGENT2.0项目组
程 序 员: YangDong 聂瑞
发布日期: 

修    订:
修改日期:20090702
修改内容:生成序列号，流水号时，使用for update行锁数据。

程 序 员: YangDong
修改日期:20140828
修改内容:DCI改造
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

/* dci 二层封装函数 */
/* 查询一条记录到结构体中 */
/*
功能: 查询，结果存入结构体
返回值:
    <0 失败
    =0 查无记录
    >0 查询成功
*/
int fprv_SelToStruct( const char* sSql, FLD_DESC desc_arr[], int desc_num, void* pdes)
{
    CURSOR cur;
    char szErrMsg[512];

    if( sSql == NULL || pdes == NULL || desc_arr == NULL || desc_num <= 0)
    {
        LOG(LM_STD, Fmtmsg("传入参数空"), "WARNING");
        return -1;
    }
    cur = DCIDeclareCursor( sSql, DCI_DEFAULT);
    if (cur == INVALID_CURSOR)
    {
        LOG(LM_STD, Fmtmsg("游标定义失败[%s]-[%s]",  DCILastError(), sSql), "ERROR");
        return -1;
    }
    if(DCIExecute(cur) == -1)
    {
        LOG(LM_STD, Fmtmsg("数据库操作失败[%s]", DCILastError() ), "ERROR");
        DCIFreeCursor(cur);
        return -1;
    }

    int rs = 0;
    if( 0 > ( rs = DBFetch( cur, desc_arr, desc_num, pdes, szErrMsg ) ) )
    {
        LOG(LM_STD, Fmtmsg("游标获取记录错误[%s]",  szErrMsg ), "ERROR");
        return -1;
    }
    DCIFreeCursor(cur);  /*被遗漏过*/
    return rs;
}
  
/************************************************************************
功能： 生成序列编号
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
        LOG(LM_STD,Fmtmsg("序列键值不能为空[%s]",sXlJz),"ERROR");
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
        LOG(LM_STD,Fmtmsg("请检查环境变量DB设置[%s]", sDbType),"ERROR");

    iRet = fprv_SelToStruct( sSql, SD_APP_XLKZ, NUMELE(SD_APP_XLKZ), &sdb_app_xlkz );
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("取序列控制信息失败[app_xlkz],pkey=[%s][%d]",sXlJz, iRet ),"ERROR");
        DCIRollback();
        return -1;
    }
    if ( iRet == 0 )
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("序列信息不存在[%s]",sXlJz ),"ERROR");
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
        LOG(LM_STD,Fmtmsg("更新序列控制信息失败[app_xlkz],pkey=[%s],[%s]",sXlJz,DCILastError() ),"ERROR");
        DCIRollback();
        return -1;
    }

    /* informix 事务嵌套不支持 */
    if( memcmp( sDbType,"INFORMIX",8 ) != 0 )
    {
        if( DCICommit() == -1 )
        {
            LOG(LM_STD,Fmtmsg("更新序列控制信息失败[%s]",DCILastError() ),"ERROR");
            DCIRollback();
            return -1;
        }
    }

    LOG(LM_DEBUG,Fmtmsg("  -->取取序列当前值[%ld]",sdb_app_xlkz.curr_value),"INFO");
    
    *iSeqno = sdb_app_xlkz.curr_value;
    return (*iSeqno);
}

/* 生成私有流水号 */
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
        LOG(LM_STD,Fmtmsg("请检查环境变量DB设置[%s]", sDbType),"ERROR");
  
    iRet = fprv_SelToStruct( sSql, SD_APP_YWRQ, NUMELE(SD_APP_YWRQ), &sdb_app_ywrq);
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("取业务日期信息失败[app_xlkz],pkey=[%s],ret[%d][%s]",sCpdm,iRet,DCILastError() ),"ERROR");
        DCIRollback();
        return -1;
    }
    if ( iRet == 0 )
    {
        DCIRollback();
        LOG(LM_STD,Fmtmsg("业务日期不存在[%s]",sCpdm),"ERROR");
        return -1;
    }

    iLshNew=0;
    iLshNew= sdb_app_ywrq.lsh + 1;
    
    /* 循环处理 */
    if ( iLshNew >=  APP_CPDM_MAXSERIAL )
        iLshNew=1;
    
    memset( sSql, 0x00, sizeof( sSql ) );
    snprintf( sSql, sizeof( sSql ), "UPDATE app_ywrq SET lsh = %d WHERE pkey ='%s' ",iLshNew, sCpdm );
    iRet = DCIExecuteDirect( sSql );
    if( iRet <= 0 )
    {
        LOG(LM_STD,Fmtmsg("更新业务私有流水表失败: 产品代码[%s],[%s]",sCpdm,DCILastError()),"ERROR") ;
        DCIRollback();
        return -1;
    }

    /* informix 事务嵌套不支持 */
    if( memcmp( sDbType,"INFORMIX",8 ) != 0 )
    {  
        if( DCICommit() == -1 )
        {
            LOG(LM_STD,Fmtmsg("更新业务私有流水表失败: 产品代码[%s],[%s]",sCpdm,DCILastError() ),"ERROR") ;
            DCIRollback();
            return -1;
        }
    }
    
    /* 业务流水 */
    *llsh = sdb_app_ywrq.lsh ;
    /* 业务日期 */
    strcpy( sywrq, sdb_app_ywrq.ywrq );
    /* 场次号 */
    strcpy( scch, sdb_app_ywrq.cch );

    return (*llsh);
}
  
/* 获取时间戳处理 */
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
  
  /*统计字符串中某一字符个数*/
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
  
  /* 私有函数 */
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

  /* 私有函数 */
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
  
  /* 获取分割符子串函数 */
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
   函数名称:  fprv_checkDate(char *date)
   函数功能:  校验日期的合法性
   函数参数:  date : 日期字符串
                  格式：YYYYMMDD
   函数返回:   =  0: 日期合法
               = -1: 年份非法
               = -2：月份非法
               = -3：日期非法
   函数说明:  
   修改说明:  
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
    /*年份校验*/
    if (iYear  <= 0 || iYear > 9999)
        return -1;
    /*月份校验*/
    if (iMonth <= 0 || iMonth > 12)
        return -2;
    /*日期校验*/
    if (iDay   <= 0 || iDay >RMONTHDAYS(iMonth, iYear))
        return -3;
    return 0;
}
  
/*****************************************************
   函数名称:  fprv_dateOffSet()
   函数功能:  日期偏移计算
   函数参数:  date : 日期字符串
                  格式：YYYYMMDD
           steps: 偏移天数
   函数返回: >0  偏移后的日期
             <0  日期非法
   函数说明:  
   修改说明:  
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
    /*日期非法*/
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
函数声明:int GetValueFromStr(char *str,char *buff,char *buff2)
函数功能:取字符串后面以数字组成的串
函数参数: 
         str   原字符串
         buff  存放结果字符串
         buff2 存放剩余字符串
函数返回: 0
例子：  
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
函数声明:int calcadd(char *strsrc , int num, char *buff)
函数功能:长字符串加法运算
函数参数: 
         str  原数字存放的字符串
         num  需要加的数字，只能是正数 
         buff 存放结果字符串
函数返回: 0
例子：  
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
    
    /*sprintf(tmp, "%%0%ds",     ilen);  linux 下 %04s,补充的是空格而不是0*/
    
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
函数声明:int get_ch_count(char *buf, int n)
函数功能:取半个汉字的个数
函数参数: 
         buf  目标字符串
         n    需要运算的长度
函数返回: 半个汉字的个数
例子：  
         get_ch_count("你好",4) == 4
         get_ch_count("你好吗?",7) == 6
         get_ch_count("你好吗？",8) == 8
         一般配合 get_ch_count()%2 使用，用来判断字符串是否存在半个汉字
**************************************************************************/
int get_ch_count(char *buf, int n)
{
    int i, count;

    for (i = 0, count = 0; i < n; i++)
        if ((unsigned char)buf[i] >= 0xa0)
            count++;
    return count;
}

/*写系统类日志*/
int LOG_Ctrl(HXMLTREE lXmlhandle, char *file, int line, int msglevel, char *mainmsg, char * secmsg)
{
    char sbuf[3]={0};
    char sTmp1[1024]={0},sTmp2[32]={0};
    SFmtmsg(sTmp1,sizeof(sTmp1),"%s",mainmsg);
    SFmtmsg(sTmp2,sizeof(sTmp2),"%s",secmsg);

    /* 取日志模式 */
    COMP_SOFTGETXML(XMLNM_APP_CPXX_RZMS,sbuf);
    trim(sbuf);

    /*LOG(LM_STD,Fmtmsg("获取msglevel[%d]sbuf[%s]执行开始",msglevel,sbuf),"");*/
    if (sbuf[0] == '0') /* 调试模式 */
    {
        WriteSBLLog(LM_STD, SYS_LOGNAME, file, line, LLOG_HEAD, "[%s] [%s]",sTmp1,sTmp2);
        return 0;
    }
    else if (sbuf[0] == '1' && msglevel <= LM_STD)  /* 生产模式 */
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

/* 统计表记录数
   支持分组汇总,联合查询汇总*/
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
        strcpy(errmsg, "查询语句为空");
        return -1;
    }

    memset(sSqltmp, 0, sizeof(sSqltmp));
    snprintf(sSqltmp,sizeof(sSqltmp),"%s",sCntSql);

    iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqltmp);
    if( iRet == -1)
    {
        strcpy( errmsg, "数据库操作失败" );
        return -1;
    }
   
    *iCntVal = atoi( sBuf );

    LOG(LM_DEBUG,Fmtmsg("统计语句[%s],记录合计=[%d]",sSqltmp,*iCntVal),"DEBUG");

    return 0;
}
