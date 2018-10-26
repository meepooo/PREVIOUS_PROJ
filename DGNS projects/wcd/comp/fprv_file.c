#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"
#include <iconv.h>
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
    snprintf(sExecScript, sizeof(sExecScript), "icps_%s_check_file.sh", "wbankcar");
    LOG(LM_DEBUG, Fmtmsg("�ű�����[%s]", sExecScript), "DEBUG");
    LOG(LM_DEBUG, Fmtmsg("�ű�����[%s],[%s]", st_para_fileprechk.date, st_para_fileprechk.bank_id), "DEBUG");

    Execle_Shell(sExecScript, st_para_fileprechk.date, st_para_fileprechk.bank_id, st_para_fileprechk.path);

    return 0;
}

/**΢�����жϻ��ܽ���Ƿ����**/
int ffunc_check_mxzz(HXMLTREE lXmlhandle, ICPS_WBC_TM_GL_BAL tm_gl_bal, char* busi_date, char* flag, double* hzje, int* bs)
{
      int iRet = -1;
      char sBuf[1024];
      char sErrmsg[256];
      char sBusi_Date[8 + 1]; /**ҵ������**/
      char sSqlStr[1024];
	    char sFlag[1+1];/**�����־**/
	    char sZje[20];
	    char sHje[20];
	 char Buf[20]; 
	    double iBje=0.00;
	    double iRje=0.00;
	    double iHje=0.00;
		int iBcnt=0;
		int iRcnt=0;
	    
	    memset(sFlag, 0x00, sizeof(sFlag));
	    memset(sErrmsg, 0x00, sizeof(sErrmsg));
      memset(sSqlStr, 0x00, sizeof(sSqlStr));
      memset(sBuf, 0x00, sizeof(sBuf));
	  memset(Buf,0x00,sizeof(Buf));

	  pstrcopy(sBusi_Date, busi_date, sizeof(sBusi_Date));
	  pstrcopy(sFlag, flag, sizeof(sFlag));  
	  trim(sBusi_Date);
	  trim(sFlag);
	  memset(sZje, 0x00, sizeof(sZje));
	  if (strncmp(sFlag, "D", 2) == 0)
	  {
	  	  sprintf(sZje, "%.2f", tm_gl_bal.db_amt);
	  }
      else
	 {  
	  	  sprintf(sZje, "%.2f", tm_gl_bal.cr_amt);
	 }
    

    	 snprintf(sSqlStr, sizeof(sSqlStr),
			"select nvl(sum(post_amt),0) as zje1,count(1) as bcnt from  ICPS_WBC_TM_ACCOUNTING_FLOW where red_flag='B' and db_cr_ind='%s' and subject='%s' and bank_group_id='%s' and busi_date='%s'",sFlag, tm_gl_bal.subject,tm_gl_bal.bank_group_id,sBusi_Date);
    	 LOG(LM_DEBUG, Fmtmsg("���ֻ��ܽ��and������ѯsql[%s]", sSqlStr), "DEBUG");
       iRet = DBSelectToMultiVarChar(sErrmsg, sSqlStr,sBuf,Buf);
         if (iRet < 0)
    	 {
        	LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        	return 0;
    	 }
			trim(sBuf);
			trim(Buf);
	   	iBje=atof(sBuf);
		iBcnt=atof(Buf);
   		LOG(LM_STD, Fmtmsg("iBje=[%.2f]", iBje), "DEBUG")

  		memset(sErrmsg, 0x00, sizeof(sErrmsg));
    	memset(sSqlStr, 0x00, sizeof(sSqlStr));
    	memset(sBuf, 0x00, sizeof(sBuf));
		memset(Buf,0x00,sizeof(Buf));
    	snprintf(sSqlStr, sizeof(sSqlStr),
			"select nvl(sum(post_amt),0) as zje2,count(1) as rcnt from  ICPS_WBC_TM_ACCOUNTING_FLOW where red_flag='R' and db_cr_ind='%s' and subject='%s' and bank_group_id='%s' and busi_date='%s'",sFlag, tm_gl_bal.subject, tm_gl_bal.bank_group_id,sBusi_Date);

    	 LOG(LM_DEBUG, Fmtmsg("��ѯ���ֽ��ͱ���SQL[%s]", sSqlStr), "DEBUG");
         iRet = DBSelectToMultiVarChar(sErrmsg, sSqlStr,sBuf,Buf);
         if (iRet < 0)
    	 {
        	LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
        	return 0;
    	 }
	   trim(sBuf);
	   iRje=atof(sBuf);
	   iRcnt=atof(Buf);
    LOG(LM_DEBUG, Fmtmsg("break1"), "DEBUG");
   	LOG(LM_STD, Fmtmsg("iRje=[%.2f]", iRje), "ERROR")
      
	  iHje=iBje - iRje;
	  *hzje=iHje;
	  *bs=iRcnt+iBcnt;

	  memset(sHje, 0x00, sizeof(sHje));
	  sprintf(sHje, "%.2f", iHje);
	  LOG(LM_STD, Fmtmsg("sZje=[%s]", sZje), "ERROR")
	  LOG(LM_STD, Fmtmsg("sHje=[%s]", sHje), "ERROR")
	  iRet=strncmp(sZje, sHje, sizeof(sHje));
	  if (0 == iRet)
	  {
	  	LOG(LM_STD, Fmtmsg("��Ŀ[%s]������[%s] ---��ϸ���ܽ��[%s]", tm_gl_bal.subject, sFlag, sHje ), "DEBUG")
		return 1;
	  }
	  else if(iRet > 0) 
	  {
	  	LOG(LM_STD, Fmtmsg("��Ŀ[%s]������[%s] ---��ϸ���ܽ��[%s]", tm_gl_bal.subject, sFlag, sHje), "DEBUG")
	  	return 2;
	  }
	  else
	  {
	  	LOG(LM_STD, Fmtmsg("��Ŀ[%s]������[%s] ---��ϸ���ܽ��[%s]", tm_gl_bal.subject, sFlag, sHje), "DEBUG")
		return 3;
	  }
}  
