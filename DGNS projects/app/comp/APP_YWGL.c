/********************************************************************
��Ȩ����:���ݺ������ӹɷ����޹�˾
��Ŀ����:�м�ҵ��ƽ̨��Ŀ(AGENT2.0)
��    ��:V4.1.0.1
����ϵͳ:
�ļ�����:APP_YWGL.c
�ļ�����:ҵ�����������������������չ鵵����������ͣ�����еȡ�
�� Ŀ ��:
�� �� Ա: YangDong ����
��������: 20090624
��    ��: SC
�޸�����: 20110905
�޸����ݣ����SApp_SysShell�����������shell�������У�Ŀǰ��system����ֵ�ж������⣬ִ�гɹ�Ҳ����-1
��    ��: YangDong

�޸�����: 20140915
�޸����ݣ�dci����
*********************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/types.h>
/*#include <unistd.h>
#include <fcntl.h>*/

#include "gaps_head.h"
#include "../incl/app_head.h"

#define SOCOMPVERSION "V4.1.0.1"

int ShowSocompVersion(char *sinfo,int isize)
{
    char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>\
    <root>\
    <soname>APP_YWGL.so</soname>\
    <sosrcname>APP_YWGL.c</sosrcname>\
    <sonote>ҵ�����ͨ���������</sonote>\
    <version>\
    <rec ver=\"2.0.0.1\" modify=\"2010-4-1  15:08\" programer=\"YangDong\" filesize=\"1309408\">HS-AgentV2.0����</rec>\
    <rec ver=\"2.1.0.1\" modify=\"2011-11-01 10:08\" programer=\"S..C..\"   filesize=\"1309408\">HS-AgentV2.1����</rec>\
    <rec ver=\"4.1.0.1\" modify=\"2014-9-15 10:08\" programer=\"YangDong\"  filesize=\"1309408\">DCI����</rec>\
    </version>\
    </root>";

    printf("\n================��̬���������Ϣ================\n");
    printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
    printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
    printf("%s-%s\n",__PROJECTSNAME,__VERSION);
    if (strlen(sversion) >= isize)
    {
        printf(" -->ȡ��ϸ��Ϣʧ��...\n");
        return -2;
    }
    strcpy(sinfo,sversion);
    printf(" -->��鿴��ϸ��Ϣ...\n");
    return 0;
}
char sSql1[512];


/* ˽�к������ж��Ƿ�Ϊ���꣬���򷵻�1�����Ƿ���0 */
IRESULT isLeapYear(int i)
{
    if (i%100 != 0 && i%4 == 0)
        return 1;
    if ( i%100 == 0 && i%400 == 0)
        return 1;
    return 0;
}

/* ˽�к�����ȡ��ǰ���ڵ���һ�� */
IRESULT GetSysNextDate(char * sNextDate)
{
    char sCurDate[9]={0};
    char sYear[5]={0};
    char sMon[3]={0};
    char sDay[3]={0};
    int  iYear=0;
    int  iMon=0;
    int  iDay=0;
    int  monthday[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    
    sprintf(sCurDate, "%s", GetFmtSysDate("%Y%m%d"));
    LOG(LM_DEBUG,Fmtmsg("��ȡϵͳ����[%s]",sCurDate),"DEBUG");
    memcpy(sYear, sCurDate, 4);
    memcpy(sMon,  sCurDate+4, 2);
    memcpy(sDay,  sCurDate+6, 2);
    iYear = atoi(sYear);
    iMon  = atoi(sMon);
    iDay  = atoi(sDay);
    /* ����2�·���28��Ļ���������1�� */
    monthday[1] += isLeapYear(iYear);
    iDay ++;
    if(iDay > monthday[iMon-1])
    {
        iDay = 1;
        iMon ++;
        if(iMon == 13)
        {
            iMon = 1;
            iYear ++;
        }
    }
    sprintf(sNextDate,"%4d%02d%02d", iYear, iMon, iDay);
    LOG(LM_DEBUG,Fmtmsg("��ȡ�ڶ�������[%s]",sNextDate),"DEBUG");
    return 0;
}

/*********************************************************************
��̬�����������
�����������:SApp_SysInitDate
�������:SApp_SysInitDate
�������:ƽ̨����
�������:
 ��� ��������  ��������    ��Դ���    ȱʡֵ  �ɿ�  ����˵��
  1   1-����    ��������  416-�����ַ���  N     ���к�����

������״̬:
  ���״̬��         ���˵��
  ȱʡ

�� Ŀ ��: 
�� �� Ա: 
��������:
*********************************************************************/
IRESULT SApp_SysInitDate(HXMLTREE lXmlhandle)
{
    char sNextDate[8+1];
    char sDate[8+1];
    int  iZhqzlsh=0;
    char sSql[256];
    char sBuf[256];
    int  iParas;
    
    /*add by SC 20120925 �޸�GAPS��ˮ�л��󣬹����ڴ�����ˮ����Ҫ���µ����ݿ��*/
    char sLshStep[10];
    char sMaxLsh[15];
    int  iLshStep=0;
    int  iMaxLsh=0;
    /*add by SC 20120925 end*/
    
    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1)
  
    memset( sBuf, 0x00, sizeof( sBuf ) );
    memset( sNextDate, 0x00, sizeof( sNextDate ) );
    COMP_GETPARSEPARAS( 1, sBuf, "��������" )
    pstrcopy( sNextDate, sBuf, sizeof( sNextDate ) );
    if (strlen(sNextDate) == 0)
    {
        GetSysNextDate( sNextDate );
    }
    memset( sSql, 0x00, sizeof( sSql ) );
    memset( sDate, 0x00, sizeof( sDate ) );
    
    /* ��ȡ��ǰ�������ڣ��жϣ�������ȣ���ʾ�Ѿ����У�ֱ�ӷ��� */
    memset(sBuf,0,sizeof(sBuf));
    COMP_SOFTGETXML(XMLNM_ZWRQ, sBuf);
    strcpy( sDate, sBuf );
    
    if( memcmp( sDate, sNextDate , 8 ) == 0 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg(" ϵͳ����[%s],�Ѿ����� ",sDate ),"ERROR");
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
        return 0;
    }
    
    memset( sSql, 0x00, sizeof( sSql ) );

    /* ��ˮ�����ñ�־ */
    COMP_SOFTGETXML( XMLNM_APP_LSH_RETURN, sBuf);
    trim(sBuf);
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg(" ������ˮ�ű�־[%s] ", sBuf ),"INFO");
    if( sBuf[0] == '0' ) /* 0 ���� */
    {
        /* ҵ����ʼ��ˮ��ȡ */
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_APP_CSKZ_ZXLSH, sBuf);
        trim(sBuf);
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg(" ��С��ˮ��[%s] ", sBuf ),"INFO");
        iZhqzlsh = atoi(sBuf);
        if( iZhqzlsh == 0 )  /* δ������С��ˮ�� */
        {
            iZhqzlsh = 1;   /* Ĭ��1 */
        } 
    }
    else /* ��������ˮ�� 20120925 ���ӶԲ�������ˮ�Ŵ��� */
    {
        memset(sBuf,0,sizeof(sBuf));
        COMP_SOFTGETXML(XMLNM_ZHQZLSH, sBuf);
        iZhqzlsh = atoi(sBuf);
        
        if ( ExGetCfgItem("gaps.ini", "RESOURCE", "SERIALNOSTEP", sLshStep, sizeof( sLshStep ) ) != 0 ) 
        {
            LOG( LM_STD,Fmtmsg("gaps.ini�ļ�����!sLshStep=[%s]", sLshStep ),"WORN" )
            iLshStep = 100;
        }
        else
            iLshStep=atoi(sLshStep);
  
        if ( ExGetCfgItem("gaps.ini", "RESOURCE", "SERIALMAX", sMaxLsh, sizeof( sMaxLsh ) ) != 0 ) 
        {
            LOG( LM_STD,Fmtmsg("gaps.ini�ļ�����!sMaxLsh=[%s]", sMaxLsh ),"WORN" )
            iMaxLsh = 99999999;
        }
        else
            iMaxLsh=atoi(sMaxLsh);
        
        /* ������ˮ���ظ������������ֵ��Χ */
        iZhqzlsh += iLshStep;
        if (iZhqzlsh >= iMaxLsh)
        {
            memset(sBuf,0,sizeof(sBuf));
            COMP_SOFTGETXML(XMLNM_APP_CSKZ_ZXLSH, sBuf);
            trim(sBuf);
            iZhqzlsh = atoi(sBuf);
            if( iZhqzlsh == 0)  /* δ������С��ˮ�� */
            {
                iZhqzlsh = 1;   /* Ĭ��1 */
            }
        }
    }

    sprintf(sBuf, "%d", iZhqzlsh);
    /* ����ϵͳ�����ļ�syspara.ini */
    fpub_WriteSysPara(FILE_SYSPARA, "zwrq", sNextDate);
    fpub_WriteSysPara(FILE_SYSPARA, "zhqzlsh", sBuf );
    fpub_WriteSysPara(FILE_SYSPARA, "pch", "1" );
    /* ˢ��SPA */

    /* modified by yangdong 20090921 */
    iParas = 0;
    iParas = system("initGSA rp -y >/dev/null 2>&1");
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("[%d]iparas",iParas),"DEBUG");
    /*
    if( ( ! WIFEXITED( iParas ) ) || ( WEXITSTATUS( iParas ) != 0 ) )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("[%d]iparas",iParas),"");
        fpub_SetMsg(lXmlhandle, MID_SYS_RMAREFRESHRES, Fmtmsg( MSG_SYS_RMAREFRESHRES,"",0 )  );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    */
    /* end of mod */

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
  
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}

/********************************************************************
�����������: SApp_Archive
�������: ���ݹ鵵
�������:�������ݹ鵵����
     
�������:
��� ��������   ��Դ���   ȱʡֵ    �Ƿ�ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
 
�� Ŀ ��: 
�� �� Ա:
��������: 2009��2��
�޸�����:
*********************************************************************/
IRESULT SApp_Archive(HXMLTREE lXmlhandle)
{
    char     sYybs[3+1],sYymc[40+1];
    char    sGdrq[8+1],sGdqsrq[8+1];
    char    sColKey[32],sColValue[64];
    char    sRunSql[1024],sWhsql[512];
    char    sCurSql[1024],sHisSql[1024];
    char    sTmpSql[512];
    int     iCount,iHisCount;
    int     iLsts;
    APP_RZPZ sdb_app_rzpz;
  
    int    iParas;
    int iRet,iTjs,iColVaue;
    int i,iResult;
    int  iFail = 0;
    char    sBuf[256];
    char    sSrcDir[128],sDesDir[128];
    char    sType[1+1],sColName[32+1];
    char    sLopper[4+1],sOP[6+1];
    char    sCmd[512];
    CURSOR cur;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");    
    /*����������*/
    COMP_PARACOUNTCHK(2)
            
    /*��ȡ�������*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"Ӧ�ñ�ʶ");
    trim(sBuf);
    memset(sYybs,0,sizeof(sYybs));
    memcpy(sYybs,sBuf,sizeof(sYybs));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"�鵵����");
    trim(sBuf);
    memset(sGdrq,0,sizeof(sGdrq));
    memcpy(sGdrq,sBuf,sizeof(sGdrq));
    
    memset(sBuf,0,sizeof(sBuf));        /*Ӧ������*/
    COMP_SOFTGETXML(XMLNM_APP_YYXX_YYMC,sBuf);
    memset(sYymc,0,sizeof(sYymc));
    memcpy(sYymc,sBuf,sizeof(sYymc));
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("yybs=[%s],yymc=[%s],gdrq=[%s]",sYybs,sYymc,sGdrq),"DEBUG");
    
    /*�����������ñ��α�*/
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_rzpz WHERE ssyy='%s'AND czlx='1'",sYybs );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
     
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("�����������ñ��α����,[%s]",DCILastError()),"ERROR");
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
  
    while(1)
    {
        /*ȡ��־���ñ���Ҫ�鵵�Ķ���*/
        memset(&sdb_app_rzpz,0,sizeof(sdb_app_rzpz));
        iRet = DBFetch(cur, SD_APP_RZPZ, NUMELE(SD_APP_RZPZ), &sdb_app_rzpz, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }
        trim(sdb_app_rzpz.dxlx);
        trim(sdb_app_rzpz.czdx1);
        trim(sdb_app_rzpz.czdx2);
        trim(sdb_app_rzpz.cztj);
            
        if( strncmp(sdb_app_rzpz.dxlx,"1",1)==0 )        /*���ݿ�鵵*/
        {
            /*��֯�鵵��SQL*/
            memset(sRunSql,0,sizeof(sRunSql));
            sprintf(sRunSql, "INSERT INTO %s SELECT * FROM %s WHERE 1=1 ",\
                sdb_app_rzpz.czdx2,sdb_app_rzpz.czdx1);
        
            /*ͳ�Ƶ��ձ����������ļ�¼��*/
            memset(sCurSql,0,sizeof(sCurSql));
            sprintf(sCurSql, "SELECT count(*) FROM %s WHERE 1=1 ",sdb_app_rzpz.czdx1);
            /*ͳ����ʷ����ɹ��ļ�¼��*/
            memset(sHisSql,0,sizeof(sHisSql));
            sprintf(sHisSql, "SELECT count(*) FROM %s WHERE 1=1 ", sdb_app_rzpz.czdx2);
        
        
            /*ͳ����������*/
            iTjs = 0;
            iTjs = fprv_countchar(sdb_app_rzpz.cztj,'|');
        
            /*ȡ�������*/
            for(i=0;i<iTjs;i++)
            {
                memset(sTmpSql,0,sizeof(sTmpSql));
                fprv_getSubItem(sdb_app_rzpz.cztj,i,"|",sTmpSql);
            
                /*����SQL����*/
                memset(sType,0,sizeof(sType));
                memset(sColName,0,sizeof(sColName));
                memset(sLopper,0,sizeof(sLopper));
                memset(sColKey,0,sizeof(sColKey));
                memset(sOP,0,sizeof(sOP));
                fprv_getSubItem(sTmpSql,0,";",sType);
                fprv_getSubItem(sTmpSql,1,";",sColName);
            
                fprv_getSubItem(sTmpSql,2,";",sLopper);
                fprv_getSubItem(sTmpSql,3,";",sColKey);
            
                if(i < iTjs-1)
                {
                    fprv_getSubItem(sTmpSql,4,";",sOP);
                }
            
                /*��ѯ�������Ʊ�*/
                trim(sColKey);
                /* 20111010 modified by yangdong ���ӶԷǼ�ֵ������ */
                if( sColKey[0] == 'K' )
                { 
                    memset(sColValue,0,sizeof(sColValue));
                    snprintf( sSql1, sizeof( sSql1 ),"SELECT jdz FROM app_cskz WHERE csjz='%s'",sColKey );
                    iRet = DBSelectToVarChar( sErrmsg,  sColValue, sSql1 );
                    if ( iRet < 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                            Fmtmsg("��ѯ�������Ʊ�ʧ��,[%s]", DCILastError() ),"ERROR");
                        DCIRollback();
                        DCIFreeCursor(cur); 
                        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    if ( iRet == 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                            Fmtmsg("��Ӧ������ֵ������,csjz=[%s]",sColKey),"ERROR");
                        DCIFreeCursor(cur);
                        DCIRollback();
                        fpub_SetMsg(lXmlhandle,MID_APP_SJGD_NOFUND,MSG_APP_SJGD_NOFUND);
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                }
                else
                {
                     snprintf( sColValue, sizeof( sColValue ), "%s", sColKey );
                }
                trim(sColValue);
            
                if( i==0 )  /*��һ������Ϊ��������*/
                {
                    iLsts = 0;
                    iColVaue = atoi(sColValue);
                    iLsts = 0 - iColVaue;
                
                    /*��������*/
                    iRet = 0;
                    memset(sGdqsrq,0,sizeof(sGdqsrq));
                    iRet=fprv_dateOffSet(sGdrq,iLsts);
                    sprintf(sGdqsrq, "%d", iRet);

                    memset(sWhsql,0,sizeof(sWhsql));
                    /* modified by yangdong 20111010 
                    sprintf(sWhsql, "AND %s='%s' %s", sColName,sGdqsrq,sOP);
                    */
                    sprintf(sWhsql, "AND %s<='%s' %s", sColName,sGdqsrq,sOP);
                    strcat(sRunSql,sWhsql);
                    strcat(sCurSql,sWhsql);
                    strcat(sHisSql,sWhsql);
                }
                else
                {
                    memset(sWhsql,0,sizeof(sWhsql));
                    if( strncmp(sType,"D",1)==0 )
                    {
                        sprintf(sWhsql, " %s%s%.2f%s ", sColName,sLopper,sColValue,sOP);
                    }
                    else if( strncmp(sType,"I",1)==0 )
                    {
                        sprintf(sWhsql, " %s%s%d%s ", sColName,sLopper,sColValue,sOP);
                    }
                    else
                        sprintf(sWhsql, " %s%s'%s'%s ", sColName,sLopper,sColValue,sOP);
                    
                    strcat(sRunSql,sWhsql);
                    strcat(sCurSql,sWhsql);
                    strcat(sHisSql,sWhsql);
                }
            }
        
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("sRunSql=[%s]",sRunSql),"DEBUG");
        
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("sCurSql=[%s]",sCurSql),"DEBUG");

            /*ͳ�Ƶ�ǰ������鵵�����ļ�¼��*/
           iRet = DBSelectToVar( sErrmsg, &iCount, sCurSql) ;
           if( iRet < 0 )
           {
               LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
               DCIFreeCursor(cur);
               DCIRollback();
               fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
               fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
               return COMPRET_FAIL;
           }
        
            if( iCount==0 )  /*������ˮ�������������ļ�¼*/
            {
                continue;
            }
            else
            {
                /*ִ�й鵵����*/
                iResult = 0;
                iRet = DCIExecuteDirect( sRunSql );
                if ( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                        Fmtmsg("�鵵ʧ��[%d],�鵵Դ=[%s],Ŀ��=[%s]",\
                        DCILastErrno(), sdb_app_rzpz.czdx1,sdb_app_rzpz.czdx2),"ERROR");

                    /* �鵵ʧ�ܣ������ж��Ƿ��ظ��鵵 */
                    /*ͳ����ʷ������鵵�����ļ�¼��*/
                    memset( sRunSql, 0x00, sizeof( sRunSql ) );
                    sprintf(sRunSql, "SELECT count(*) FROM %s WHERE 1=1 %s ",sdb_app_rzpz.czdx1, sWhsql);
                    iRet = DBSelectToVar( sErrmsg, &iHisCount, sRunSql) ;
                    if( iRet < 0 )
                    {
                        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                        DCIFreeCursor(cur);
                        DCIRollback();
                        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                        return COMPRET_FAIL;
                    }
                    if( iHisCount >= iCount )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("�ظ��鵵[%d][%d]",iHisCount,iCount),"DEBUG");
                        continue;
                    }

                    iFail ++;
                }
            }
        }
        else        /*�ļ��鵵*/
        {
            memset(sSrcDir,0,sizeof(sSrcDir));
            memset(sDesDir,0,sizeof(sDesDir));
            sprintf(sSrcDir, "%s/%s", getenv("HOME"),sdb_app_rzpz.czdx1);
            sprintf(sDesDir, "%s/%s", getenv("HOME"),sdb_app_rzpz.czdx2);
        
            memset(sCmd,0,sizeof(sCmd));        /*�ļ����й鵵*/
            sprintf(sCmd, "cp %s* %s.", sSrcDir,sDesDir);
            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("sCmd=[%s]",sCmd),"DEBUG");

            iParas = 0;
            iParas = system( sCmd );
            if ( iParas != 0 )
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("[%d]iparas",iParas),"DEBUG");
            /*
            if( ( ! WIFEXITED( iParas ) ) || ( WEXITSTATUS( iParas ) != 0 ) )
            {
                fpub_SetMsg(lXmlhandle, MID_SYS_RMAREFRESHRES, Fmtmsg( MSG_SYS_RMAREFRESHRES,"",0 )  );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            */
            /* end of mod */
        }
    }
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    DCIFreeCursor(cur);

    DCICommit();

    if( iFail > 0  )
    {
        fpub_SetMsg(lXmlhandle,MID_APP_SJGD_GDERR,Fmtmsg("[%d]�ű�鵵ʧ��",iFail ) );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /* end of add */
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC;
}

/********************************************************************
�����������: SApp_Clean
�������: ��������
�������:��������������
     
�������:
��� ��������   ��Դ���   ȱʡֵ    �Ƿ�ɿ�  ����˵��

������״̬:
  ���״̬��         ���˵��
 
�� Ŀ ��: 
�� �� Ա:
��������: 2009��6��
�޸�����:
*********************************************************************/
IRESULT SApp_Clean(HXMLTREE lXmlhandle)
{
    char    sYybs[3+1],sYymc[40+1];
    char    sQlrq[8+1],sQlqsrq[8+1];
    char    sColKey[32],sColValue[64];
    char    sRunSql[1024],sWhsql[512];
    char    sCurSql[1024],sHisSql[1024];
    char    sTmpSql[512],sHisTable[128], sDateSql[1024];
    char    sMinDate[10+1];
    int     iCount,iHisCount;
    int     iLsts,iFlag;
    APP_RZPZ sdb_app_rzpz;
    int  iRet = -1;
    CURSOR cur;
    char sErrmsg[512];
    int iParas;
    int iTjs,iColVaue;
    int i,iResult;
    char    sBuf[256];
    char    sSrcDir[128],sCmd[512];
    char    sType[1+1],sColName[32+1];
    char    sLopper[4+1],sOP[6+1];
    char    sDateCol[16+1];  /* �����ֶ��� */

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    /*����������*/
    COMP_PARACOUNTCHK(2)
            
    /*��ȡ�������*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"Ӧ�ñ�ʶ");
    trim(sBuf);
    memset(sYybs,0,sizeof(sYybs));
    memcpy(sYybs,sBuf,sizeof(sYybs));
    
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"��������");
    trim(sBuf);
    memset(sQlrq,0,sizeof(sQlrq));
    memcpy(sQlrq,sBuf,sizeof(sQlrq));
    
    memset(sBuf,0,sizeof(sBuf));        /*Ӧ������*/
    COMP_SOFTGETXML(XMLNM_APP_YYXX_YYMC,sBuf);
    memset(sYymc,0,sizeof(sYymc));
    memcpy(sYymc,sBuf,sizeof(sYymc));
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,\
        Fmtmsg("yybs=[%s],yymc=[%s],qlrq=[%s]",sYybs,sYymc,sQlrq),"DEBUG");
    
    /*�����������ñ��α�*/
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_rzpz WHERE ssyy='%s'AND czlx='2'",sYybs );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("�����������ñ��α����,[%s]",DCILastError()),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    iRet = DCIBegin();
    if( iRet < 0 )
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    while(1)
    {
        /*ȡ��־���ñ���Ҫ�鵵�Ķ���*/
        memset(&sdb_app_rzpz,0,sizeof(sdb_app_rzpz));
        iRet = DBFetch(cur, SD_APP_RZPZ, NUMELE(SD_APP_RZPZ), &sdb_app_rzpz, sErrmsg );
        if ( iRet <= 0 )
        {
            break;
        }

        trim(sdb_app_rzpz.dxlx);
        trim(sdb_app_rzpz.czdx1);
        trim(sdb_app_rzpz.cztj);
    
        if( strncmp(sdb_app_rzpz.dxlx,"1",1)==0 )        /*���ݿ������*/
        {
            /*��֯�����SQL*/
            memset(sRunSql,0,sizeof(sRunSql));
            trim(sdb_app_rzpz.czdx1);
            sprintf(sRunSql, "DELETE FROM %s WHERE 1=1 ",sdb_app_rzpz.czdx1);
        
            /*��ѯ������Ӧ����ʷ��*/
            iFlag = 0;
            memset(sHisTable,0,sizeof(sHisTable));
            snprintf( sSql1, sizeof( sSql1 ), "SELECT czdx2 FROM app_rzpz\
                WHERE ssyy='%s'AND czlx='1' AND dxlx='1' AND czdx1='%s'", sYybs, sdb_app_rzpz.czdx1);
            iRet = DBSelectToMultiVar( sErrmsg, sSql1, sHisTable ) ;
            if( iRet < 0 )
            {
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
                DCIRollback();
                DCIFreeCursor(cur);
                fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
                return COMPRET_FAIL;
            }

            if ( iRet == 0 )
            {
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("δ��ѯ����Ӧ����ʷ��,ֱ������"),"DEBUG");
                iFlag = 1;
            }
            memset(sCurSql,0,sizeof(sCurSql));
            sprintf(sCurSql, "SELECT COUNT(*) FROM %s WHERE 1=1 ",sdb_app_rzpz.czdx1);
            memset(sHisSql,0,sizeof(sHisSql));
            sprintf(sHisSql, "SELECT COUNT(*) FROM %s WHERE 1=1 ",sHisTable);
        
            /*ͳ����������*/
            iTjs = 0;
            iTjs = fprv_countchar(sdb_app_rzpz.cztj,'|');
            /*ȡ�������*/
            for(i=0;i<iTjs;i++)
            {
                memset(sTmpSql,0,sizeof(sTmpSql));
                fprv_getSubItem(sdb_app_rzpz.cztj,i,"|",sTmpSql);
            
                /*����SQL����*/
                memset(sType,0,sizeof(sType));
                memset(sColName,0,sizeof(sColName));
                memset(sLopper,0,sizeof(sLopper));
                memset(sColKey,0,sizeof(sColKey));
                memset(sOP,0,sizeof(sOP));
                fprv_getSubItem(sTmpSql,0,";",sType);
                fprv_getSubItem(sTmpSql,1,";",sColName);
                fprv_getSubItem(sTmpSql,2,";",sLopper);
                fprv_getSubItem(sTmpSql,3,";",sColKey);
            
                if(i < iTjs-1)
                {
                    fprv_getSubItem(sTmpSql,4,";",sOP);
                }
            
                /*��ѯ�������Ʊ�*/
                trim(sColKey);
                /* 20111010 modified by yangdong ���ӶԷǼ�ֵ������ */
                if( sColKey[0] == 'K' )
                { 
                    memset(sColValue,0,sizeof(sColValue));
/* for test
                    snprintf( sSql1, sizeof( sSql1 ),"SELECT jdz FROM app_cskz WHERE csjz='%s'",sColKey );
*/
                    snprintf( sSql1, sizeof( sSql1 ),"SELECT 111 jdz FROM app_cskz WHERE csjz='%s'",sColKey );
                    iRet = DBSelectToVarChar( sErrmsg,  sColValue, sSql1 );

                    if ( iRet < 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                Fmtmsg("��ѯ�������Ʊ�ʧ��,[%s]",DCILastError() ),"ERROR");
                        DCIRollback();
                        DCIFreeCursor(cur);
                        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    if ( iRet == 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                 Fmtmsg("��Ӧ������ֵ������,csjz=[%s]",sColKey),"ERROR");
                        DCIFreeCursor(cur);
                        DCIRollback();
                        fpub_SetMsg(lXmlhandle,MID_APP_SJGD_NOFUND,MSG_APP_SJGD_NOFUND);
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                }
                else
                {
                     snprintf( sColValue, sizeof( sColValue ), "%s", sColKey );
                }
                trim(sColValue);
            
                if( i==0 )  /*��һ������Ϊ��������*/
                {
                    iLsts = 0;
                    iColVaue = atoi(sColValue);
                    iLsts = 0 - iColVaue;
                
                    /*��������*/
                    iRet = 0;
                    memset(sQlqsrq,0,sizeof(sQlqsrq));
                    iRet=fprv_dateOffSet(sQlrq,iLsts);
                    sprintf(sQlqsrq, "%d", iRet);
                
                    memset(sWhsql,0,sizeof(sWhsql));
                    /* modified by yangdong 20111010 
                    sprintf(sWhsql, "AND %s='%s' %s", sColName,sGdqsrq,sOP);
                    */
                    sprintf(sWhsql, "AND %s<='%s' %s", sColName,sQlqsrq,sOP);
                    strcat(sRunSql,sWhsql);
                    strcat(sCurSql,sWhsql);
                    strcat(sHisSql,sWhsql);
                    memset(sDateSql,0,sizeof(sDateSql));
                    sprintf(sDateSql, "SELECT min(%s) FROM %s WHERE 1=1 %s ",\
                            sColName, sdb_app_rzpz.czdx1,sWhsql );
                    snprintf( sDateCol,  sizeof( sDateCol ), "%s", sColName );
                }
                else
                {
                    memset(sWhsql,0,sizeof(sWhsql));
                    if( strncmp(sType,"D",1)==0 )
                    {
                        sprintf(sWhsql, " %s%s%.2f%s ", sColName,sLopper,sColValue,sOP);
                    }
                    else if( strncmp(sType,"I",1)==0 )
                    {
                        sprintf(sWhsql, " %s%s%d%s ", sColName,sLopper,sColValue,sOP);
                    }
                    else
                        sprintf(sWhsql, " %s%s'%s'%s ", sColName,sLopper,sColValue,sOP);
                    
                    strcat(sRunSql,sWhsql);
                    strcat(sCurSql,sWhsql);
                    strcat(sHisSql,sWhsql);
                    strcat(sDateSql,sWhsql);
                }
            }
        
            if( iFlag==0 )
            {
                /*��ȡ�����¼����*/
                iRet = DBSelectToVarChar(sErrmsg, sMinDate, sDateSql);
                if ( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                           Fmtmsg("��ȡ��С����ʧ��,[%s]",DCILastError()),"ERROR");
                    DCIFreeCursor(cur);
                    DCIRollback();
                    fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
                iCount = 0;

                trim( sMinDate );
                if( strlen( sMinDate)  > 1 )
                {
                    memset( sBuf, 0x00, sizeof( sBuf ) );
                    sprintf( sBuf, " AND %s >= '%s'", sDateCol, sMinDate );
                    strcat ( sCurSql , sBuf );
                    strcat ( sHisSql , sBuf );
                }
                /*ͳ�Ƶ�ǰ���¼��*/
                iCount = 0;
                iRet = DBSelectToVar(sErrmsg, &iCount , sCurSql );
                if ( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                           Fmtmsg("ͳ�Ƶ�ǰ���¼��ʧ��,[%s]",DCILastError() ),"ERROR");
                    DCIFreeCursor(cur);
                    DCIRollback();
                    fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }

                if( iCount > 0 )  /* �������¼ */
                {
                    /*ͳ����ʷ��鵵�ɹ��ļ�¼��*/
                    iHisCount = 0;
                    iRet = DBSelectToVar(sErrmsg, &iHisCount , sHisSql);
                    if ( iRet < 0 )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                             Fmtmsg("ͳ����ʷ���¼��ʧ��,[%s]",DCILastError()),"ERROR");
                        DCIFreeCursor(cur);
                        DCIRollback();
                        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    /*�Ƚϵ�ǰ������ʷ��ļ�¼��*/
                    if( iCount > iHisCount )
                    {
                        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                            Fmtmsg("δ���鵵,��������.iCount=[%d],iHisCount=[%d]",iCount,iHisCount),"ERROR");
                        DCIFreeCursor(cur);
                        DCIRollback();
                        fpub_SetMsg(lXmlhandle,MID_APP_SJQL_NOTGD,\
                                  Fmtmsg(MSG_APP_SJQL_NOTGD,sdb_app_rzpz.czdx1));
                        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                        return COMPRET_FAIL;
                    }
                    else
                    {
                        /*ִ���������*/
                        iResult = 0;
                        iRet = 0;
                        iRet = DCIExecuteDirect( sRunSql );
                        if ( iRet < 0 )
                        {
                            LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                 Fmtmsg("����[%s]ʧ��,[%s],iRet=[%d]",\
                                 sdb_app_rzpz.czdx1,DCILastError() ,iRet),"ERROR");
                            DCIFreeCursor(cur);
                            DCIRollback();
                            fpub_SetMsg(lXmlhandle,MID_APP_SJQL_QLERR,MSG_APP_SJQL_QLERR);
                            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                            return COMPRET_FAIL;
                        }
                    }
                }
            }
            else
            {
                /*ִ���������*/
                iResult = 0;
                iRet = 0;
                iRet = DCIExecuteDirect( sRunSql );
                if ( iRet < 0 )
                {
                    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,\
                                 Fmtmsg("����[%s]ʧ��,[%s],iRet=[%d]",\
                                 sdb_app_rzpz.czdx1,DCILastError() ,iRet),"ERROR");
                    DCIFreeCursor(cur);
                    DCIRollback();
                    fpub_SetMsg(lXmlhandle,MID_APP_SJQL_QLERR,MSG_APP_SJQL_QLERR);
                    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                    return COMPRET_FAIL;
                }
            }
        }
        else        /*�ļ�����*/
        {
            memset(sSrcDir,0,sizeof(sSrcDir));
            trim(sdb_app_rzpz.czdx1);
            sprintf(sSrcDir, "%s/%s", getenv("HOME"),sdb_app_rzpz.czdx1);
            memset(sCmd,0,sizeof(sCmd));        /*�ļ���������*/
            /* modified by yangdong 20090921 */
            /*
            sprintf(sCmd, "rm -rf %s*", sSrcDir);
            system(sCmd);
            */

            iParas = 0;
            sprintf(sCmd, "rm -f %s*", sSrcDir);
            iParas = system( sCmd );
            if( iParas != 0 )
                LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("[%d]iparas",iParas),"DEBUG");
            /* 
            if( ( ! WIFEXITED( iParas ) ) || ( WEXITSTATUS( iParas ) != 0 ) )
            {
                fpub_SetMsg(lXmlhandle, MID_SYS_RMAREFRESHRES, Fmtmsg( MSG_SYS_RMAREFRESHRES,"",0 )  );
                fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
                return COMPRET_FAIL;
            }
            */
            /* end of mod */
        }
    }
    DCIFreeCursor(cur);
    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC;
}

/********************************************************************
�����������: SApp_DataBackup
�������: ���ݱ���
�������: �������ݱ��ݴ���
     
�������:
��� ��������   ��Դ���   ȱʡֵ    �Ƿ�ɿ�  ����˵��
1    Ӧ�ñ�ʶ                           N


������״̬:
  ���״̬��         ���˵��
 
�� Ŀ ��: 
�� �� Ա: YangDong 
��������: 2009��6��
�޸�����:
*********************************************************************/
IRESULT SApp_DataBackup(HXMLTREE lXmlhandle)
{
    char sYybs[8+1];
    char sTable[48+1];
    char sSql[2048];
    char sBackDir[128];
    APP_RZPZ sdb_app_rzpz;
  
    int    iParas;
    char    sBuf[256];
    char    sFullFileName[256];
    /* 20120203 modified by yangdong �������ȵ���
    char    sTmp[32];
    */
    char    sTmp[128];
    char    sCmd[512];
    long   lResult;
    int  iRet = -1;
    CURSOR cur;
    char sErrmsg[512];

    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    /*����������*/
    COMP_PARACOUNTCHK(1)
            
    /*��ȡ�������*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"Ӧ�ñ�ʶ");
    trim(sBuf);
    memset(sYybs,0,sizeof(sYybs));
    memcpy(sYybs,sBuf,sizeof(sYybs));
    
    /* ȡƽ̨���ںͽ�����ˮ,ƴ�ļ���ʱʹ�� */
    memset( sTmp, 0, sizeof( sTmp ) );
    COMP_HARDGETXML( "/pub/zwrq", sTmp )
    memset(sBuf,0,sizeof(sBuf));
    COMP_HARDGETXML( "/pub/zhqzlsh", sBuf )
    strcat( sTmp, sBuf );
    trim( sTmp );
    
    /* �����ļ�·�� */ 
    snprintf( sSql1, sizeof( sSql1 ), "SELECT jdz FROM APP_CSKZ WHERE csjz='K_APP_BACKDIR'" );
    iRet = DBSelectToVarChar(sErrmsg, sBackDir, sSql1);
    if ( iRet < 0 )  
    {
        fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    if ( iRet == 0 )  /* Ĭ�ϴ����$HOME/file�� */   
    { 
        memset( sBackDir, 0x00, sizeof( sBackDir ) );
        memset(sBuf,0,sizeof(sBuf));
        sprintf( sBackDir, "%s/file/backup", getenv( "HOME" ) );
    }        
    trim( sBackDir );

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg(" ��ʼ����Ӧ��[%s] ����·��[%s] ", sYybs, sBackDir ),"INFO" );
    
    /* ��ѯ������Ҫ���ݵĿ�� */
    memset( sSql1, 0x00, sizeof( sSql1 ) );
    snprintf( sSql1, sizeof( sSql1 ), "SELECT * FROM app_rzpz WHERE ssyy='%s'AND czlx='1' AND dxlx='1'",sYybs );
    if ((cur = DCIDeclareCursor(sSql1, DCI_STMT_LOCATOR)) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
    if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("�����������ñ��α����,[%s]",DCILastError()),"ERROR");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

    while(1)
    {
        memset( &sdb_app_rzpz, 0x00, sizeof( sdb_app_rzpz ) );
        /*ȡ��־���ñ���Ҫ�鵵�Ķ���*/
        iRet = DBFetch(cur, SD_APP_RZPZ, NUMELE(SD_APP_RZPZ), &sdb_app_rzpz, sErrmsg );
        if ( iRet < 0 )
        {
            LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
            DCIFreeCursor(cur);
            /*DCIRollback(); deleted by chenxm 2015-1-7*/
            fpub_SetMsg(lXmlhandle,MID_SQL_ERROR,MSG_SQL_ERROR);
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        if ( iRet == 0 )
        {
            break;
        }
        /* �����ļ��� �����_ƽ̨����_��ˮ�� */
        memset( sSql, 0x00, sizeof( sSql ) );
        memset( sFullFileName, 0x00, sizeof( sFullFileName ) );
        sprintf( sSql, "SELECT * FROM %s WHERE 1=1", sTable );
        trim( sTable );
        sprintf( sFullFileName, "%s/%s_%s", sBackDir, sTable, sTmp );
        iRet=sql_UnloadToFile( sFullFileName,sSql,'|','\\', &lResult);
        if ( iRet != MID_SYS_SUCC )
        {
            DCIFreeCursor(cur);
            fpub_SetMsg(lXmlhandle,MID_APP_BACKUP_FAIL, MSG_APP_BACKUP_FAIL );
            fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
            return COMPRET_FAIL;
        }
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("��[%s] �ɹ����ݵ��ļ�[%s]", sTable, sFullFileName ),"INFO" );
    }
    DCIFreeCursor(cur);

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC;
}

/********************************************************************
�����������: SApp_DataRecover
�������: ���ݻָ�?�������: 
     
�������:
��� ��������   ��Դ���   ȱʡֵ    �Ƿ�ɿ�  ����˵��
1    Ӧ�ñ�ʶ                           N


������״̬:
  ���״̬��         ���˵��
 
�� Ŀ ��: 
�� �� Ա: YangDong
��������: 2009��6��
�޸�����:
*********************************************************************/
IRESULT SApp_DataRecover(HXMLTREE lXmlhandle)
{
    char sBuf[256];
    char sTable[256];
    char sFullFileName[256];
    int  iParas;
    int  iRet;
    long lResult;

    /*����������*/
    COMP_PARACOUNTCHK(2)
            
    /*��ȡ�������*/
    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(1,sBuf,"���ָ�����");
    trim(sBuf);
    memset(sTable,0,sizeof(sTable));
    memcpy(sTable,sBuf,sizeof(sTable));

    memset(sBuf,0,sizeof(sBuf));
    COMP_GETPARSEPARAS(2,sBuf,"���������ļ���");
    trim(sBuf);
    memset(sFullFileName,0,sizeof(sFullFileName));
    memcpy(sFullFileName,sBuf,sizeof(sFullFileName));
    
    if( iRet=sql_LoadFromFile( sFullFileName, sTable, '|', '\\', &lResult) != MID_SYS_SUCC )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("�ָ�ʧ��,[%s]",DCILastError() ),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_RECOVER_FAIL, MSG_APP_RECOVER_FAIL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    return COMPRET_SUCC;
}

/*********************************************************************
��̬�����������
�����������:SApp_SysShell
�������:SApp_SysShell
�������:Shell�������е���
�������:
 ��� ��������  ��������    ��Դ���    ȱʡֵ  �ɿ�  ����˵��
  1   1-����    SHELL����  416-�����ַ���  N     ���������ַ���

������״̬:
  ���״̬��         ���˵��
  ȱʡ

�� Ŀ ��: 
�� �� Ա: 
��������:
*********************************************************************/
IRESULT SApp_SysShell(HXMLTREE lXmlhandle)
{
    char sBuf[512];
    char sDate[9];
    char sTime[7];
    char sFileName[100];
    char sShellFile[100];
    char sShell[1024];
    char sResp[512];
    int  iParas;
    FILE *fp1,*fp2;
    fpub_InitSoComp(lXmlhandle);

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"DEBUG");

    COMP_PARACOUNTCHKMIN(1)

    memset( sBuf, 0x00, sizeof( sBuf ) );
    memset( sShell, 0x00, sizeof( sShell ) );
    memset( sFileName, 0x00, sizeof( sFileName ) );
    memset( sDate, 0x00, sizeof( sDate ) );
    memset( sTime, 0x00, sizeof( sTime ) );
    memset( sResp, 0x00, sizeof( sResp ) );
    COMP_GETPARSEPARAS( 1, sShell, "SHELL������" )
    if (strlen(sShell) == 0)
    {
        fpub_SetMsg(lXmlhandle, MID_APP_SHELL_NULL, MSG_APP_SHELL_NULL);
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    /*ƽ̨����*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_ZWRQ,sBuf);
    pstrcopy( sDate, sBuf, sizeof( sDate ) );
    if ( 0 == sDate[0] ) 
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD,Fmtmsg(MSG_APP_PTRQ_NULL),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_APP_PTRQ_NULL,MSG_APP_PTRQ_NULL );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    /*ƽ̨ʱ��*/
    memset( sBuf, 0x00, sizeof( sBuf ) );
    COMP_SOFTGETXML(XMLNM_SYSTIME, sBuf);
    pstrcopy( sTime, sBuf, sizeof( sTime ) );

    /* modify by yr 20121018 */
    sprintf(sFileName, "%s/tmp/shell_%s_%s.log", getenv("HOME"), sDate, sTime);
    sprintf(sShellFile, "%s/tmp/shell.sh", getenv("HOME"));
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, Fmtmsg("����shell--[%s] > [%s] 2>&1", sShell, sFileName),"INFO");
    
    fp1 = NULL;
    fp2 = NULL;
    fp1 = fopen(sShellFile, "w+");
    if ( fp1 == NULL )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("���ļ�ʧ��shell.sh,error=[%s]",strerror(errno)),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("���ļ�ʧ��"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    iParas=chmod(sShellFile, 0777);
    /*iParas=chmod(sShellFile, S_IXUSR);
    iParas=chmod(sShellFile, S_IXGRP);
    iParas=chmod(sShellFile, S_IRUSR); 
    iParas=chmod(sShellFile, S_IWUSR);
    iParas=chmod(sShellFile, S_IXUSR);
    iParas=chmod(sShellFile, S_IRGRP);
    iParas=chmod(sShellFile, S_IWGRP);
    iParas=chmod(sShellFile, S_IXGRP);
    iParas=chmod(sShellFile, S_IROTH);
    iParas=chmod(sShellFile, S_IWOTH);
    iParas=chmod(sShellFile, S_IXOTH);*/
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_STD, Fmtmsg("[%d]chmod[%d]errno",iParas,errno),"INFO");
    
    fprintf(fp1, "cd $HOME/file/shell/ \n");
    fprintf(fp1, "%s >%s 2>&1 \n", sShell, sFileName);
    fclose(fp1);
    iParas=0;
    iParas=system(sShellFile);
    
    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG, Fmtmsg("[%d]iParas",iParas),"DEBUG");

    fp2 = fopen(sFileName, "rt");
    if ( fp2 == NULL )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_STD,Fmtmsg("���ɽ���ļ�ʧ��file=[%s],error=[%s]",sFileName,strerror(errno)),"ERROR");
        fpub_SetMsg(lXmlhandle,MID_YW_ERROR,Fmtmsg("���ļ�ʧ��"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }
    fread(sResp, sizeof(sResp)-1, 1, fp2);
    trim(sResp);
    fclose(fp2);
    /*if( iParas == -1 || iParas == 127 )
    {
        LOG_Ctrl(lXmlhandle,__FILE__,__LINE__, LM_DEBUG, "SHELL����ʧ��", "ERR");
        fpub_SetMsg(lXmlhandle, MID_APP_SHELL_SB, MSG_APP_SHELL_SB );
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }*/
    COMP_HARDSETXML( XMLNM_APP_RESP_RESPMSG, sResp );
    COMP_HARDSETXML( XMLNM_APP_RESP_WJMC, sFileName );

    LOG_Ctrl(lXmlhandle,__FILE__,__LINE__,LM_DEBUG,Fmtmsg("���[%s]ִ�н���",fpub_GetCompname(lXmlhandle)),"DEBUG");
    
    fpub_SetCompStatus(lXmlhandle,COMPSTATUS_SUCC);
    return 0;
}
