#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include <iconv.h>

int ffunc_getfile_to_local(HXMLTREE lXmlhandle, char* sDate, char* busi_no, char* sPath)
{
    char sExecScript[255];

    memset(sExecScript, 0x00, sizeof(sExecScript));
    snprintf(sExecScript, sizeof(sExecScript), "icps_sftp_%s_get_file.sh", busi_no);
    LOG(LM_DEBUG, Fmtmsg("�ű�����[%s]", sExecScript), "DEBUG");

    Execle_Shell(sExecScript, sDate, sPath, NULL);

    return 0;
}
/*TODO:*/
int ffunc_getfilename_to_xml(HXMLTREE lXmlhandle, char* busi_no, char* sPath)
{
    int iRet = -1;
    char sBuf[255];
    char sFile_Type[32];
    char sFile[255];
    char sFileLine[1024];
    FILE* fp;

    memset(sFile,0x00,sizeof(sFile));
    snprintf(sFile, sizeof(sFile), "%s/.filelist", sPath);
    if ((fp = fopen(sFile, "r")) == NULL)
    {
        LOG(LM_STD, Fmtmsg("���ļ��嵥ʧ��[%s]", sFile), "ERROR");
        return -1;
    }

    if (0 == strcmp(busi_no, "jiebei"))
    {
        while (!feof(fp))
        {
            fgets(sFileLine, sizeof(sFileLine), fp);
            chomp_CRLF(sFileLine);

            if (sFileLine[0] == '\0')
                continue;
            trim(sFileLine);


        }
    }

    return 0;
}

int ffunc_ins_file_info(const char* busi_date, const char* busi_no, const char* file_type)
{
    int iRet = -1;
    char sBuf[255];
    char sErrmsg[256];
    ICPS_FILE_INFO st_icps_file_info;

    memset(&st_icps_file_info, 0x00, sizeof(st_icps_file_info));
    pstrcopy(st_icps_file_info.busi_date, busi_date, sizeof(st_icps_file_info.busi_date)); /*ҵ������*/
    pstrcopy(st_icps_file_info.busi_no, busi_no, sizeof(st_icps_file_info.busi_no)); /*ҵ����*/
    pstrcopy(st_icps_file_info.file_type, file_type, sizeof(st_icps_file_info.file_type)); /*�ļ�����*/
    pstrcopy(st_icps_file_info.file_status, "0", sizeof(st_icps_file_info.file_status)); /*�ļ�״̬*/

    /*�������ݿ�*/
    memset(sErrmsg, 0x00, sizeof(sErrmsg));
    iRet = APP_DBInsert("ICPS_FILE_INFO", SD_ICPS_FILE_INFO, NUMELE(SD_ICPS_FILE_INFO), &st_icps_file_info, sErrmsg);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return iRet;
    }

    if (DCICommit() != MID_SYS_SUCC)
    {
        LOG(LM_STD, Fmtmsg("���ݿ��ύʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        DCIRollback();
        return -1;
    }

    return 0;
}

int ffunc_upd_file_info(const char* busi_date, const char* busi_no, const char* file_type, int status)
{
    int iRet, iParas;
    char sBuf[256];
    char file_status[1 + 1];
    char sUpdSql[4096];

    LOG(LM_DEBUG, Fmtmsg("status:[%d]", status), "INFO");
    if (-404 == status)
        pstrcopy(file_status, "0", sizeof(file_status)); //���ļ���Ĭ��δ���
    else if (0 == status)
        pstrcopy(file_status, "1", sizeof(file_status)); //���ɹ�
    else
        pstrcopy(file_status, "2", sizeof(file_status)); //���ʧ��

    memset(sUpdSql, 0x00, sizeof(sUpdSql));
    snprintf(sUpdSql, sizeof(sUpdSql), "UPDATE ICPS_FILE_INFO SET FILE_STATUS='%s'"
            " WHERE BUSI_DATE='%s' AND BUSI_NO='%s' AND  FILE_TYPE='%s'",
            file_status,
            busi_date,
            busi_no,
            file_type);
    LOG(LM_DEBUG, Fmtmsg("�������:[%s]", sUpdSql), "INFO");

    DCIBegin();
    iRet = DCIExecuteDirect(sUpdSql);
    if (iRet < 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ���²���ʧ��, sqlerr[%s]", DCILastError()), "ERROR");
        DCIRollback();
        return -1;
    }

    /* �ύ���� */
    if (DCICommit() != 0)
    {
        LOG(LM_STD, Fmtmsg("���ݿ��ύ����ʧ��, sqlerr[%s]", DCILastError()), "ERROR");
        DCIRollback();
        return -1;
    }

    if (iRet == 0)
    {
        LOG(LM_STD, Fmtmsg("���²����޷��������ļ�¼"), "INFO")
        return -1;
    }

    return 0;
}


int ffunc_file_pre_check(HXMLTREE lXmlhandle, PARA_FILEPRECHK st_para_fileprechk)
{
    char sExecScript[255];

    memset(sExecScript, 0x00, sizeof(sExecScript));
    snprintf(sExecScript, sizeof(sExecScript), "icps_%s_check_file.sh", st_para_fileprechk.busi_no);
    LOG(LM_DEBUG, Fmtmsg("�ű�����[%s]", sExecScript), "DEBUG");

    Execle_Shell(sExecScript, st_para_fileprechk.date, st_para_fileprechk.bank_id, st_para_fileprechk.path);

    return 0;
}
/**�жϻ��ܽ���Ƿ����**/
int ffunc_mxzz_check(HXMLTREE lXmlhandle, char* subject, char* busi_date, char* flag, double* je)
{
      int iRet = -1;
      char sBuf[1024];
      char sErrmsg[256];
      char sBusi_Date[8 + 1]; /**ҵ������**/
      char sSqlStr[1024];
	  char sSubject[40];/**��Ŀ��**/
	  char sFlag[4];/**�����־**/
	  char sZje[20];
	  char sHje[20];
	  
	  double iBje=0.00;
	  double iRje=0.00;
	  double iZje=0.00;
	  double iHje=0.00;
	  
	  pstrcopy(sSubject, subject, sizeof(subject)); 
	  pstrcopy(sBusi_Date, sBusi_Date, sizeof(sBusi_Date));
	  pstrcopy(sFlag, flag, sizeof(sFlag));  
	  trim(sSubject);
	  trim(sBusi_Date);
	  trim(sFlag);
	  
	  memset(sSubject, 0x00, sizeof(sSubject));
	  memset(sFlag, 0x00, sizeof(sFlag));
	  memset(sErrmsg, 0x00, sizeof(sErrmsg));
      memset(sSqlStr, 0, sizeof(sSqlStr));
      memset(sBuf, 0, sizeof(sBuf));
    

    	 snprintf(sSqlStr, sizeof(sSqlStr),
			"select nvl(sum(post_amt),0) as zje1 from  ICPS_WB_DS_ACCOUNTING_FLOW where red_flag='B' and db_cr_ind='%s' and subject='%s' and busi_date='%s'",sFlag, sSubject, sBusi_Date);
    	 LOG(LM_DEBUG, Fmtmsg("��ѯ���ܽ��[%s]", sSqlStr), "DEBUG");
       iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
         if (iRet < 0)
    	 {
        	LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        	DCIRollback();
        	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        	return COMPRET_FAIL;
    	 }
		  trim(sBuf);
	   	iBje=atof(sBuf);
   		LOG(LM_STD, Fmtmsg("iBje=[%f]", iBje), "ERROR")

  		memset(sErrmsg, 0x00, sizeof(sErrmsg));
    	memset(sSqlStr, 0, sizeof(sSqlStr));
    	memset(sBuf, 0, sizeof(sBuf));
    	snprintf(sSqlStr, sizeof(sSqlStr),
			"select nvl(sum(post_amt),0) as zje2 from  ICPS_WB_DS_ACCOUNTING_FLOW where red_flag='R' and db_cr_ind='%s' and subject='%s' and busi_date='%s'",sFlag, sSubject, sBusi_Date);

    	 LOG(LM_DEBUG, Fmtmsg("��ѯ�����������[%s]", sSqlStr), "DEBUG");
         iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
         if (iRet < 0)
    	 {
        	LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        	DCIRollback();
        	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        	return COMPRET_FAIL;
    	 }
	   trim(sBuf);
	   iRje=atof(sBuf);
   	LOG(LM_STD, Fmtmsg("iRje=[%s]", iRje), "ERROR")

  		memset(sErrmsg, 0x00, sizeof(sErrmsg));
    	memset(sSqlStr, 0, sizeof(sSqlStr));
    	memset(sBuf, 0, sizeof(sBuf));
    	if (0==strcmp(sFlag,"D"))
    	{
    		snprintf(sSqlStr, sizeof(sSqlStr),
					"select  nvl(sum(db_amt),0) as zje from  ICPS_WB_TM_GL_BAL where subject='%s' and busi_date='%s'",sSubject, sBusi_Date);
			}
			else
		  {
		  	snprintf(sSqlStr, sizeof(sSqlStr),
					"select  nvl(sum(cr_amt),0) as zje from  ICPS_WB_TM_GL_BAL where subject='%s' and busi_date='%s'",sSubject, sBusi_Date);
		  }
    	 	LOG(LM_DEBUG, Fmtmsg("��ѯ������˱�ָ����Ŀ���շ�����[%s],����[%s]", sSqlStr, sFlag), "DEBUG");
         iRet = DBSelectToVarChar(sErrmsg, sBuf, sSqlStr);
         if (iRet < 0)
    	 {
        	LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        	DCIRollback();
        	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        	fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        	return COMPRET_FAIL;
    	 }
	  trim(sBuf);
	  iZje=atof(sBuf);
	  LOG(LM_STD, Fmtmsg("iZje=[%s]", iZje), "ERROR")
	  iHje=iBje - iRje;
	  
	  memset(sZje, 0x00, sizeof(sZje));
	  memset(sHje, 0x00, sizeof(sHje));
	  sprintf(sZje, "%.2f", iZje);
	  sprintf(sHje, "%.2f", iHje);
	  if (0==strncmp(sZje, sHje, sizeof(sHje)))
	  {
	  	LOG(LM_STD, Fmtmsg("��Ŀ[%s]������[%s] �ܽ����ڻ��ܽ��", sSubject, sFlag), "DEBUG")
	  	*je=iHje;
		return 0;
	  }
	  else if(0<strncmp(sZje, sHje, sizeof(sHje)))
	  {
	  	LOG(LM_STD, Fmtmsg("��Ŀ[%s]������[%s] �ܽ��С�ڻ��ܽ��", sSubject, sFlag), "DEBUG")
	  	*je=iHje;
	  	return 1;
	  }	
	  else  
	  {
	  	LOG(LM_STD, Fmtmsg("��Ŀ[%s]������[%s] �ܽ����ڻ��ܽ��", sSubject, sFlag), "DEBUG")
	  	*je=iHje;
	  	return 2;
	  }
}  
