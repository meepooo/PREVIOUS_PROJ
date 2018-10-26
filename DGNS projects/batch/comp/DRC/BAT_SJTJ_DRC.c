/********************************************************************
  ��Ȩ����:�������ӹɷ����޹�˾
  ��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
  ��    ��:V3.0.00
  ����ϵͳ:AIX5.3
  �ļ�����:SYW_BATCH_B2S_DRC.c
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
#include "../../incl/DRC/BATCH_SPLITFILECONTROL.h"

/************************************************************************
  ��̬�����������
  �����������: SYW_BATCH_B2S_PN
  �������: ��ת��������̸���

  �������: 
  ��ת����������
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: �м�ҵ����Ŀ��
  �� �� Ա: sunpj
  ��������: 2017��06��09��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
 IRESULT SYW_BATCH_B2S_PN(HXMLTREE lXmlhandle)
{
    int  iProNum = 0;
    int  iMaxProNum = 0;
    long lTotalNum = 0;
    long lFileLimitLine = 0;
    
    char cTmp[1024 + 1];
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG")
    
    /**�ļ��ܱ���**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/batch/total_num", cTmp);
    lTotalNum = atol(cTmp);
    LOG(LM_DEBUG, Fmtmsg("�ļ��ܱ���[%ld]", lTotalNum), "INFO")
    
    /**�ļ���������**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/batch/zjmapinfo/jlsxz", cTmp);
    lFileLimitLine = atol(cTmp);
    LOG(LM_DEBUG, Fmtmsg("�ļ���������[%ld]", lFileLimitLine), "INFO")
    
    /**��ת����������**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/batch/b2s/ps_num", cTmp);
    iMaxProNum = atoi(cTmp);
    LOG(LM_DEBUG, Fmtmsg("��ת����������[%d]", iMaxProNum), "INFO")
    
    /**����ת��������**/
    if (0 == lTotalNum % lFileLimitLine)
    {
        iProNum = lTotalNum / lFileLimitLine;
    }
    else
    {
        iProNum = lTotalNum / lFileLimitLine + 1;
    }
    if (iProNum > iMaxProNum)
    {
        iProNum = iMaxProNum;
        lFileLimitLine = lTotalNum / iMaxProNum;
        if (0 != lTotalNum % iMaxProNum)
        {
            lFileLimitLine = lFileLimitLine + 1;
            if (0 == lTotalNum % lFileLimitLine)
            {
                iProNum = lTotalNum / lFileLimitLine;
            }
            else
            {
                iProNum = lTotalNum / lFileLimitLine + 1;
            }
        }
    }
    LOG(LM_DEBUG, Fmtmsg("�ļ���������[%ld]��ת��������[%d]", lFileLimitLine, iProNum), "INFO")
    
    /**��ת�������������̴������**/
    memset(cTmp, 0x00, sizeof(cTmp));
    sprintf(cTmp, "%d", iProNum);
    COMP_SOFTSETXML("/batch/ps_num", cTmp);
    memset(cTmp, 0x00, sizeof(cTmp));
    sprintf(cTmp, "%ld", lFileLimitLine);
    COMP_SOFTSETXML("/batch/ps_per_bum", cTmp);
    
    fpub_SetCompStatus(lXmlhandle, 0);
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    fpub_SetCompStatus(lXmlhandle, 0);
    return 0;
}

/************************************************************************
  ��̬�����������
  �����������: SYW_BATCH_B2S_UPDDETAIL
  �������: ��ת������ҵ����ϸ��

  �������: 
  ��ת����������
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: �м�ҵ����Ŀ��
  �� �� Ա: sunpj
  ��������: 2017��06��09��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
 IRESULT SYW_BATCH_B2S_UPDDETAIL(HXMLTREE lXmlhandle)
{
    int    iParas;
    int    iRet = 0;
    int    iRepeats = 0;
    int    iHostRespNum = 0;
    int    iColCount = 0;
    int    iIsHaveRespCode = 0;
    int    iIsUpdOnce = 0; 
    char   cTmp[1024 + 1];
    char   cBuf[1024 + 1];
    char   cTableName[128 + 1];
    char   cSqlStr1[1024 + 1];
    char   cSqlStr2[10 * 1024 + 1];
    char   cSqlWhere[2 * 1024 + 1];
    char   cTableColName[128 + 1];
    char   cUpdFlag[32 + 1];
    char   cBatchDate[8 + 1];
    char   cPatBatchNo[16 + 1];
    char   cColCount[16 + 1];
    char   cFldType[32 + 1];
    char   cErrmsg[256+1];
    char   cIsRespCodeConv[16 + 1];
    char   cRespCodeMapId[128 + 1];
    char   cRespCodeSrc[32 + 1];
    char   cRespCodeDes[16 + 1];
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG")
    
    memset(cErrmsg, 0x00, sizeof(cErrmsg));
    
    /**��������**/
    memset(cBatchDate, 0x00, sizeof(cBatchDate));
    COMP_SOFTGETXML("/batch/pkrq", cBatchDate);
    
    /**ƽ̨���κ�**/
    memset(cPatBatchNo, 0x00, sizeof(cPatBatchNo));
    COMP_SOFTGETXML("/batch/ptpch", cPatBatchNo);
    
    /**ҵ�����**/
    memset(cTableName, 0x00, sizeof(cTableName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", cTableName);
    LOG(LM_DEBUG, Fmtmsg("ҵ�����[%s]", cTableName), "INFO")
    
    /**�������λ�ø���**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/batch/sjtj/zjjgwz", cTmp);
    iHostRespNum = atoi(cTmp);
    LOG(LM_DEBUG, Fmtmsg("�˻����λ����[%d]", iHostRespNum), "INFO")
    
    /**��Ӧ��ת����־**/
    memset(cIsRespCodeConv, 0x00, sizeof(cIsRespCodeConv));
    COMP_SOFTGETXML("/batch/zjmapinfo/zhbz", cIsRespCodeConv);
    LOG(LM_DEBUG, Fmtmsg("��Ӧ��ת����־[%s]", cIsRespCodeConv), "INFO")
    
    /**��Ӧ��ת��ID**/
    memset(cRespCodeMapId, 0x00, sizeof(cRespCodeMapId));
    COMP_SOFTGETXML("/batch/zjmapinfo/zhbs", cRespCodeMapId);
    LOG(LM_DEBUG, Fmtmsg("��Ӧ��ת��ID[%s]", cRespCodeMapId), "INFO")
    
    /**��������**/
    memset(cSqlStr2, 0x00, sizeof(cSqlStr2));
    memset(cSqlWhere, 0x00, sizeof(cSqlWhere));
    sprintf(cSqlStr2, "update %s set ", cTableName);
    sprintf(cSqlWhere, " where pkrq='%s' and ptpch='%s'", cBatchDate, cPatBatchNo);
    while (iRepeats < iHostRespNum)
    {
        memset(cSqlStr1, 0x00, sizeof(cSqlStr1));
        
        /**����**/
        memset(cTmp, 0x00, sizeof(cTmp));
        memset(cTableColName, 0x00, sizeof(cTableColName));
        sprintf(cTmp, "/batch/sjtj/filemapinfo2|%d/columnid", iRepeats);
        COMP_SOFTGETXML(cTmp, cTableColName);
        trim(cTableColName);
        
        /**���±�־**/
        memset(cTmp, 0x00, sizeof(cTmp));
        memset(cUpdFlag, 0x00, sizeof(cUpdFlag));
        sprintf(cTmp, "/batch/sjtj/filemapinfo2|%d/thgxbz", iRepeats);
        COMP_SOFTGETXML(cTmp, cUpdFlag);
        trim(cUpdFlag);
        
        /**�������λ��**/
        memset(cTmp, 0x00, sizeof(cTmp));
        memset(cColCount, 0x00, sizeof(cColCount));
        sprintf(cTmp, "/batch/sjtj/filemapinfo2|%d/zjjgwz", iRepeats);
        COMP_SOFTGETXML(cTmp, cColCount);
        iColCount = atoi(cColCount);
        
        /**��ѯ������**/
        memset(cSqlStr1, 0x00, sizeof(cSqlStr1));
        memset(cFldType, 0x00, sizeof(cFldType));
        sprintf(cSqlStr1, "select fldtype from app_tablereg where tablename='%s' and fldid='%s'"
                        ,cTableName , cTableColName);
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSqlStr1), "INFO")
        iRet = DBSelectToVarChar(cErrmsg, cFldType, cSqlStr1);
        if (0 > iRet)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("��ѯ����Ϣ���ñ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "��ѯ����Ϣ���ñ�ʧ��");
            return COMPRET_FAIL;
        }
        trim(cFldType);
        
        /**��ȡ����ֵ**/
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/batch/custom/resp/%s", cTableColName);
        COMP_SOFTGETXML(cTmp, cBuf);
        memset(cTmp, 0x00, sizeof(cTmp));
        
        if (0 == strcmp(cUpdFlag, "1"))/**��������**/
        {
            if (0 == strcmp(cTableColName, "xym"))
            {
                iIsHaveRespCode = 1;
            }
            
            /**�����ֶ�**/
            if (0 == strcmp(cFldType, "C") || 0 == strcmp(cFldType, "V"))
            {
                if (0 == iIsUpdOnce)
                {
                    sprintf(cTmp, "%s='%s'", cTableColName, cBuf);
                }
                else
                {
                    sprintf(cTmp, ",%s='%s'", cTableColName, cBuf);
                }
            }
            else if (0 == strcmp(cFldType, "I"))
            {
                if (0 == iIsUpdOnce)
                {
                    sprintf(cTmp, "%s=%ld", cTableColName, atol(cBuf));
                }
                else
                {
                    sprintf(cTmp, ",%s=%ld", cTableColName, atol(cBuf));
                }
            }
            else if (0 == strcmp(cFldType, "D"))
            {
                if (0 == iIsUpdOnce)
                {
                    sprintf(cTmp, "%s=%.2f", cTableColName, atof(cBuf));
                }
                else
                {
                    sprintf(cTmp, ",%s=%.2f", cTableColName, atof(cBuf));
                }
            }
            else
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("��֧�ֵ���������[%s]", cFldType), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "��֧�ֵ���������");
                return COMPRET_FAIL;
            }
            strcat(cSqlStr2, cTmp);
            if (0 == strcmp(cTableColName, "xym"))
            {
                strcpy(cRespCodeSrc, cBuf);
            }
            iIsUpdOnce++;
        }
        else if (0 == strcmp(cUpdFlag, "2"))/**��������**/
        {
           if (0 == strcmp(cFldType, "C") || 0 == strcmp(cFldType, "V"))
            {
                sprintf(cTmp, " and %s='%s'", cTableColName, cBuf);
            }
            else if (0 == strcmp(cFldType, "I"))
            {
                sprintf(cTmp, " and %s=%ld", cTableColName, atol(cBuf));
            }
            else if (0 == strcmp(cFldType, "D"))
            {
                sprintf(cTmp, " and %s=%.2f", cTableColName, atof(cBuf));
            }
            else
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("��֧�ֵ���������[%s]", cFldType), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "��֧�ֵ���������");
                return COMPRET_FAIL;
            }
            strcat(cSqlWhere, cTmp);
        }
        else
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("��֧�ֵĸ��±�־[%s]", cUpdFlag), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "��֧�ֵĸ��±�־");
            return COMPRET_FAIL;
        }
        
        iRepeats++;
    }
    
    /**���³ɹ���־  δ���ø�����Ӧ���򲻸��³ɹ���־**/
    if (1 == iIsHaveRespCode)
    {
        if (0 == strcmp(cIsRespCodeConv, "0"))
        {
            memset(cSqlStr1, 0x00, sizeof(cSqlStr1));
            memset(cRespCodeDes, 0x00, sizeof(cRespCodeDes));
            sprintf(cSqlStr1, "select resp_d from batch_mapresp where mapid='%s' and resp_s='%s'"
                ,cRespCodeMapId , cRespCodeSrc);
            LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSqlStr1), "INFO")
            iRet = DBSelectToVarChar(cErrmsg, cRespCodeDes, cSqlStr1);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("��ѯ��Ӧ��ӳ���ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "��ѯ��Ӧ��ӳ���ʧ��");
                return COMPRET_FAIL;
            }
            //LOG(LM_DEBUG, Fmtmsg("��Ӧ��[%s]", cRespCodeDes), "INFO")
            trim(cRespCodeDes);
        }
        else
        {
            /**��ת����Ĭ��ʧ��**/
            memset(cRespCodeDes, 0x00, sizeof(cRespCodeDes));
            strcpy(cRespCodeDes, "2");
        }
        
        sprintf(cTmp, ",cgbz='%s'", cRespCodeDes);
        strcat(cSqlStr2, cTmp);
    }
    
    /**��������**/
    strcat(cSqlStr2, cSqlWhere);
    LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", cSqlStr2), "INFO")
    
    iRet = DCIExecuteDirect(cSqlStr2);
    if (0 > iRet)
    {
        DCIRollback();
        fpub_SetCompStatus(lXmlhandle, -1);
        LOG(LM_STD, Fmtmsg("��������ҵ����ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
        fpub_SetMsg(lXmlhandle, 100001, "��������ҵ����ϸ��ʧ��");
        return COMPRET_FAIL;
    }
    
    DCICommit();
    
    fpub_SetCompStatus(lXmlhandle, 0);
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    fpub_SetCompStatus(lXmlhandle, 0);
    return 0;
}

/************************************************************************
  ��̬�����������
  �����������: SYW_BATCH_SPLIT_FILE
  �������: ��ϵͳ��Ų���ļ�

  �������: 
  ��ϵͳ��Ų���ļ�
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: �м�ҵ����Ŀ��
  �� �� Ա: sunpj
  ��������: 2017��06��09��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
 IRESULT SYW_BATCH_SPLIT_FILE(HXMLTREE lXmlhandle)
{
    int  iRet = 0;
    int  iHostNum = 0;
    int  iRepeatNum = 0;
    long lPatBatchNo = 0;
    long lTotalNum = 0;
    long lFileNum = 0;
    
    double dTotalAmt = 0.00;
    
    char cBuf[1024+1];
    char cSql[1024+1];
    char cErrmsg[1024+1];
    char cHostNo[64+1];
    char cHostBatchNo[64+1];
    char cLineBuf[1024+1];
    char cTotalAmt[32+1];
    char cTotalNum[32+1];
    char cBatchDate[32+1];
    char cPatBatchNo[32+1];
    char cProductNo[32+1];
    char cFileHostNo[2+1];
    char cTbaleName[128+1];
    char cPayeeAcctNo[32+1];
    char cOFileName[256+1];
    char cOfileNameAll[512+1];
    
    FILE *fp_read = NULL;
    FILE *fp_write[100+1];
    
    CURSOR cur;
    
    BATCH_SPLITFILECONTROL stSplitFileControl;
    
    LOG(LM_DEBUG, Fmtmsg("ϵͳ���Ƹ���[%d]", (sizeof(fp_write)/sizeof(FILE *)) - 1), "INFO")
    while (iRepeatNum < (sizeof(fp_write)/sizeof(FILE *)))
    {
        fp_write[iRepeatNum] = NULL;
        iRepeatNum++;
    }
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), "DEBUG")
    
    /**��������**/
    memset(cBatchDate, 0x00, sizeof(cBatchDate));
    COMP_SOFTGETXML("/batch/pkrq", cBatchDate);
    
    /**ƽ̨���κ�**/
    memset(cPatBatchNo, 0x00, sizeof(cPatBatchNo));
    COMP_SOFTGETXML("/batch/ptpch", cPatBatchNo);
    lPatBatchNo = atol(cPatBatchNo);
    
    /**�ļ����**/
    memset(cBuf, 0x00, sizeof(cBuf));
    COMP_SOFTGETXML("/batch/sjtj/wjxh", cBuf);
    lFileNum = atol(cBuf);
    LOG(LM_DEBUG, Fmtmsg("�ļ����[%ld]", lFileNum), "INFO")
    
    /**ҵ�����**/
    memset(cTbaleName, 0x00, sizeof(cTbaleName));
    COMP_SOFTGETXML("/batch/wwmapinfo/ywbm", cTbaleName);
    
    /**��Ʒ����**/
    memset(cProductNo, 0x00, sizeof(cProductNo));
    COMP_SOFTGETXML("/batch/req/cpdm", cProductNo);
    
    /**ԭ�ļ�ȫ��**/
    memset(cBuf, 0x00, sizeof(cBuf)); 
    memset(cOfileNameAll, 0x00, sizeof(cOfileNameAll));
    sprintf(cBuf, "/batch/sjtj/wjxx|%ld/wjqm", lFileNum);
    COMP_SOFTGETXML(cBuf, cOfileNameAll);
    LOG(LM_DEBUG, Fmtmsg("ԭ�ļ�ȫ��[%s]", cOfileNameAll), "INFO")
    
    /**ԭ�ļ���**/
    memset(cOFileName, 0x00, sizeof(cOFileName));
    COMP_SOFTGETXML("/batch/file/des/name", cOFileName);
    LOG(LM_DEBUG, Fmtmsg("ԭ�ļ���[%s]", cOFileName), "INFO")
    
    /** add by llh 20180115
     * �����ѹ�����־
     * **/
    char sSxfgsbz[1+1];
    memset(sSxfgsbz, 0x00, sizeof(sSxfgsbz));
    COMP_SOFTGETXML("/batch/req/sxfgsbz", sSxfgsbz);
    LOG(LM_DEBUG, Fmtmsg("�����ѹ�����־[%s]", sSxfgsbz), "INFO")
    /** add by llh 20180115 **/

    /**ͳ�Ƶ�ǰ�����漰��ϵͳ����**/
    memset(cSql, 0x00, sizeof(cSql));
    memset(cErrmsg, 0x00, sizeof(cErrmsg));
    sprintf(cSql, "select count(distinct byzd1) from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and shzt !='1' and clzt='9'"
                  , cTbaleName, cBatchDate, lPatBatchNo, lFileNum);
    LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
    iRet = DBSelectToVar(cErrmsg, &iHostNum, cSql);
    if (0 > iRet)
    {
        fpub_SetCompStatus(lXmlhandle, -1);
        LOG(LM_STD, Fmtmsg("��ѯ������ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
        fpub_SetMsg(lXmlhandle, 100001, "��ѯ������ϸ��ʧ��");
        return COMPRET_FAIL;
    }
    if ((sizeof(fp_write)/sizeof(FILE *)) - 1 < iHostNum)
    {
        fpub_SetCompStatus(lXmlhandle, -1);
        LOG(LM_STD, Fmtmsg("����ϵͳ������"), "ERROR")
        fpub_SetMsg(lXmlhandle, 100001, "����ϵͳ�����ޣ��޷�����");
        return COMPRET_FAIL;
    }
    
    /**����ļ�����**/
    iRepeatNum = 0;
    memset(cHostBatchNo, 0x00, sizeof(cHostBatchNo));
    COMP_SOFTGETXML("/batch/batch_no", cHostBatchNo);
    LOG(LM_DEBUG, Fmtmsg("cHostBatchNo[%s]", cHostBatchNo), "INFO")
    LOG(LM_DEBUG, Fmtmsg("iHostNum[%d]", iHostNum), "INFO")
    if (1 < iHostNum)
    {
        /**��ȡ��ǰ���ε�ϵͳ���**/
        memset(cSql, 0x00, sizeof(cSql));
        memset(cErrmsg, 0x00, sizeof(cErrmsg));
        sprintf(cSql, "select distinct byzd1 from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and shzt !='1' and clzt='9'"
                  , cTbaleName, cBatchDate, lPatBatchNo, lFileNum);
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
        if (-1 == (cur = DCIDeclareCursor(cSql, DCI_STMT_LOCATOR)))
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD,Fmtmsg("��ѯ������ϸ��ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, 100001, "��ѯ������ϸ��ʧ��");
            return COMPRET_FAIL;
        }
        if (-1 == DCIExecute(cur))
        {
            DCIFreeCursor(cur);
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD,Fmtmsg("���α�ʧ��,sqlerr[%s]", DCILastError()), "ERROR")
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            fpub_SetMsg(lXmlhandle, 100001, "��ѯ������ϸ��ʧ��");
            return COMPRET_FAIL;
        }
        
        while (iRepeatNum < iHostNum)
        {
            iRepeatNum++;
            memset(cHostNo, 0x00, sizeof(cHostNo));
            memset(&stSplitFileControl, 0x00, sizeof(stSplitFileControl));
            iRet = DCIFetch(cur);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("��ѯ������ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "��ѯ������ϸ��ʧ��");
                return COMPRET_FAIL;
            }
            else if (0 == iRet)
            {
                break;
            }
            strncpy(cHostNo, DCIFieldAsString(cur, 0), sizeof(cHostNo));
            trim(cHostNo);
            LOG(LM_DEBUG, Fmtmsg("hostno[%s]", cHostNo), "INFO")
        
            memset(cSql, 0x00, sizeof(cSql));
            memset(cErrmsg, 0x00, sizeof(cErrmsg));
            sprintf(cSql, "select * from batch_splitfilecontrol where host_batch_no='%s' and host_no='%s'",
                      cHostBatchNo, cHostNo);
            LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
            iRet = prv_SelMulToStruct(&cSql, SD_BATCH_SPLITFILECONTROL, NUMELE(SD_BATCH_SPLITFILECONTROL), &stSplitFileControl);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("��ѯ����ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "��ѯ����ƽ̨�ļ��ָ���Ʊ�ʧ��");
                return COMPRET_FAIL;
            }
            else if (0 == iRet)
            {
                /**�Ǽǲ�ֿ��Ʊ�**/
                memset(&stSplitFileControl, 0x00, sizeof(stSplitFileControl));
                strncpy(stSplitFileControl.host_batch_no, cHostBatchNo, sizeof(stSplitFileControl.host_batch_no));
                strncpy(stSplitFileControl.host_no, cHostNo, sizeof(stSplitFileControl.host_no));
                strncpy(stSplitFileControl.o_file_req, cOfileNameAll, sizeof(stSplitFileControl.o_file_req));
                sprintf(stSplitFileControl.file_req, "%s/file/batch/%s/%s/%s_%s", getenv("HOME"), cProductNo
                        , cBatchDate, cHostNo, cOFileName);
                strcpy(stSplitFileControl.state, "9");
                memset(cErrmsg, 0x00, sizeof(cErrmsg));
                iRet = DBInsert("batch_splitfilecontrol", SD_BATCH_SPLITFILECONTROL, NUMELE(SD_BATCH_SPLITFILECONTROL)
                                , &stSplitFileControl, cErrmsg);
                if (0 > iRet)
                {
                    fpub_SetCompStatus(lXmlhandle, -1);
                    LOG(LM_STD, Fmtmsg("�Ǽ�����ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                    fpub_SetMsg(lXmlhandle, 100001, "�Ǽ�����ƽ̨�ļ��ָ���Ʊ�ʧ��");
                    return COMPRET_FAIL;
                }
                //LOG(LM_DEBUG, Fmtmsg("insert batch_splitfilecontrol success"), "INFO")
                
                /**Ĭ�ϲ��ļ��ɹ� ʧ�ܱ���**/
                memset(cBuf, 0x00, sizeof(cBuf));
                sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/state", iRepeatNum);
                COMP_SOFTSETXML(cBuf, "0");
            }
            else
            {
                LOG(LM_DEBUG, Fmtmsg("state[%s]", stSplitFileControl.state), "INFO")
                memset(cBuf, 0x00, sizeof(cBuf));
                sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/state", iRepeatNum);
                COMP_SOFTSETXML(cBuf, stSplitFileControl.state);
                if (0 == strncmp(stSplitFileControl.state, "9", 1))
                {
                    fpub_SetCompStatus(lXmlhandle, -1);
                    LOG(LM_STD, Fmtmsg("�ļ���ִ�����"), "ERROR")
                    fpub_SetMsg(lXmlhandle, 100001, "�ļ���ִ�����");
                    return COMPRET_FAIL;
                }
                else if (0 == strncmp(stSplitFileControl.state, "1", 1))
                {
                    memset(cSql, 0x00, sizeof(cSql));
                    memset(cErrmsg, 0x00, sizeof(cErrmsg));
                    sprintf(cSql, "update batch_splitfilecontrol set state='9' where host_batch_no='%s' and host_no"
                            , cHostBatchNo, cHostNo);
                    LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", cSql), "INFO")
                    iRet = DCIExecuteDirect(cSql);
                    if (0 > iRet)
                    {
                        fpub_SetCompStatus(lXmlhandle, -1);
                        LOG(LM_STD, Fmtmsg("��������ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                        fpub_SetMsg(lXmlhandle, 100001, "��������ƽ̨�ļ��ָ���Ʊ�ʧ��");
                        return COMPRET_FAIL;
                    }
                }
                else if (0 != strncmp(stSplitFileControl.state, "0", 1))
                {
                    continue;
                }
            }
            memset(cSql, 0x00, sizeof(cSql));
            memset(cErrmsg, 0x00, sizeof(cErrmsg));
            memset(cTotalNum, 0x00, sizeof(cTotalNum));
            memset(cTotalAmt, 0x00, sizeof(cTotalAmt));
            /**** ��������ѹ�����־Ϊ2-����ʱ,��Ҫ�������Ѽ��㵽���׽����  ****/
            if(strcmp(sSxfgsbz,"2") == 0)
            {
                sprintf(cSql, "select count(*),sum(jyje)+sum(sxfje) from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and trim(byzd1)='%s' and shzt!='1' and clzt='9'"
                  , cTbaleName, cBatchDate, lPatBatchNo, lFileNum, cHostNo);
            }else
            {
                sprintf(cSql, "select count(*),sum(jyje) from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and trim(byzd1)='%s' and shzt!='1' and clzt='9'"
                  , cTbaleName, cBatchDate, lPatBatchNo, lFileNum, cHostNo);
            }
            LOG(LM_DEBUG,Fmtmsg("cSql [%s]",cSql),"DEBUG")
            iRet = DBSelectToMultiVarChar(cErrmsg, cSql, &cTotalNum, &cTotalAmt);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("��ѯ������ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "��ѯ������ϸ��ʧ��");
                return COMPRET_FAIL;
            }
            
            memset(cBuf, 0x00, sizeof(cBuf));
            sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/hostno", iRepeatNum);
            COMP_SOFTSETXML(cBuf, stSplitFileControl.host_no);
            memset(cBuf, 0x00, sizeof(cBuf));
            sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/zbs", iRepeatNum);
            COMP_SOFTSETXML(cBuf, cTotalNum);
            memset(cBuf, 0x00, sizeof(cBuf));
            sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/zje", iRepeatNum);
            COMP_SOFTSETXML(cBuf, cTotalAmt);
            memset(cBuf, 0x00, sizeof(cBuf));
            sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/file_req", iRepeatNum);
            COMP_SOFTSETXML(cBuf, stSplitFileControl.file_req);
        }
        
        COMP_SOFTSETXML("/batch/sjtj/splitfile/hostnum", itoa(iHostNum));
        
        iRet =DCICommit();
        if (0 > iRet)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("�Ǽ�����ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "�Ǽ�����ƽ̨�ļ��ָ���Ʊ�ʧ��");
            return COMPRET_FAIL;
        }
        
        if (0 == strncmp(stSplitFileControl.state, "9", 1) || 0 == strncmp(stSplitFileControl.state, "1", 1))
        {
            /**��Դ�ļ�**/
            fp_read = fopen(cOfileNameAll, "r");
            if (NULL == fp_read)
            {
                memset(cSql, 0x00, sizeof(cSql));
                memset(cErrmsg, 0x00, sizeof(cErrmsg));
                sprintf(cSql, "update batch_splitfilecontrol set state='1' where host_batch_no='%s'", cHostBatchNo);
                LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", cSql), "INFO")
                iRet = DCIExecuteDirect(cSql);
                if (0 > iRet)
                {
                    fpub_SetCompStatus(lXmlhandle, -1);
                    LOG(LM_STD, Fmtmsg("��������ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                    fpub_SetMsg(lXmlhandle, 100001, "��������ƽ̨�ļ��ָ���Ʊ�ʧ��");
                    return COMPRET_FAIL;
                }
                
                iRet =DCICommit();
                if (0 > iRet)
                {
                    fpub_SetCompStatus(lXmlhandle, -1);
                    LOG(LM_STD, Fmtmsg("��������ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                    fpub_SetMsg(lXmlhandle, 100001, "��������ƽ̨�ļ��ָ���Ʊ�ʧ��");
                    return COMPRET_FAIL;
                }
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", cOfileNameAll), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "���ļ�ʧ��");
                return COMPRET_FAIL;
            }
            
            /**���ļ�**/
            memset(cLineBuf, 0x00, sizeof(cLineBuf));
            while (NULL != fgets(cLineBuf, sizeof(cLineBuf), fp_read))
            {
                memset(cBuf, 0x00, sizeof(cBuf));
                strncpy(cBuf, cLineBuf + 634, 40);
                trim(cBuf);
                strncpy(cFileHostNo, cBuf, sizeof(cFileHostNo));
                LOG(LM_DEBUG, Fmtmsg("cFileHostNo[%s]", cBuf), "INFO")
                iRepeatNum = 0;
                while (iRepeatNum < iHostNum)
                {
                    iRepeatNum++;
                    memset(cBuf, 0x00, sizeof(cBuf));
                    memset(&stSplitFileControl, 0x00, sizeof(stSplitFileControl));
                    sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/hostno", iRepeatNum);
                    COMP_SOFTGETXML(cBuf, stSplitFileControl.host_no);
                    if (0 == strcmp(cFileHostNo, stSplitFileControl.host_no))
                    {
                        memset(cBuf, 0x00, sizeof(cBuf));
                        sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/file_req", iRepeatNum);
                        COMP_SOFTGETXML(cBuf, stSplitFileControl.file_req);
                        if (NULL == fp_write[iRepeatNum-1])
                        {
                            fp_write[iRepeatNum-1] = fopen(stSplitFileControl.file_req, "w+");
                            LOG(LM_DEBUG, Fmtmsg("���ļ�"), "INFO")
                            if (NULL == fp_write[iRepeatNum-1])
                            {
                                fclose(fp_read);
                                fp_read = NULL;
                                memset(cSql, 0x00, sizeof(cSql));
                                memset(cErrmsg, 0x00, sizeof(cErrmsg));
                                sprintf(cSql, "update batch_splitfilecontrol set state='1' where host_batch_no='%s'", cHostBatchNo);
                                LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", cSql), "INFO")
                                iRet = DCIExecuteDirect(cSql);
                                if (0 > iRet)
                                {
                                    fpub_SetCompStatus(lXmlhandle, -1);
                                    LOG(LM_STD, Fmtmsg("��������ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                                    fpub_SetMsg(lXmlhandle, 100001, "��������ƽ̨�ļ��ָ���Ʊ�ʧ��");
                                    return COMPRET_FAIL;
                                }
                                
                                iRet =DCICommit();
                                if (0 > iRet)
                                {
                                    fpub_SetCompStatus(lXmlhandle, -1);
                                    LOG(LM_STD, Fmtmsg("��������ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                                    fpub_SetMsg(lXmlhandle, 100001, "��������ƽ̨�ļ��ָ���Ʊ�ʧ��");
                                    return COMPRET_FAIL;
                                }
                                fpub_SetCompStatus(lXmlhandle, -1);
                                LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", stSplitFileControl.file_req), "ERROR")
                                fpub_SetMsg(lXmlhandle, 100001, "���ļ�ʧ��");
                                return COMPRET_FAIL;
                            }
                            memset(cPayeeAcctNo, 0x00, sizeof(cPayeeAcctNo));
                            strncpy(cPayeeAcctNo, cLineBuf + 301, 32);
                            /* add 20171113 zengy �ж����տ��˺�Ϊ����ȡ�����˺���Ϊѡȡ�������� beg */
                            trim(cPayeeAcctNo);
                            if(strlen(cPayeeAcctNo) == 0)
                            {
                                memset(cPayeeAcctNo, 0x00, sizeof(cPayeeAcctNo));
                                strncpy(cPayeeAcctNo, cLineBuf + 133, 32);
                                trim(cPayeeAcctNo);
                            }
                            /* add 20171113 zengy �ж����տ��˺�Ϊ����ȡ�����˺���Ϊѡȡ�������� end */
                            memset(cBuf, 0x00, sizeof(cBuf));
                            sprintf(cBuf, "/batch/sjtj/splitfile/list|%d/payeeacctno", iRepeatNum);
                            COMP_SOFTSETXML(cBuf, cPayeeAcctNo);
                        }
                        break;
                    }
                }
                fprintf(fp_write[iRepeatNum-1], "%s", cLineBuf);
                memset(cLineBuf, 0x00, sizeof(cLineBuf));
            }
            fclose(fp_read);
            fp_read = NULL;
            iRepeatNum = 0;
            while (iRepeatNum < iHostNum)
            {
                LOG(LM_DEBUG, Fmtmsg("�ر��ļ�"), "INFO")
                fclose(fp_write[iRepeatNum]);
                fp_write[iRepeatNum] = NULL;
                iRepeatNum++;
            }
            
            memset(cSql, 0x00, sizeof(cSql));
            memset(cErrmsg, 0x00, sizeof(cErrmsg));
            sprintf(cSql, "update batch_splitfilecontrol set state='0' where host_batch_no='%s'", cHostBatchNo);
            LOG(LM_DEBUG, Fmtmsg("UPDATE[%s]", cSql), "INFO")
            iRet = DCIExecuteDirect(cSql);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("��������ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "��������ƽ̨�ļ��ָ���Ʊ�ʧ��");
                return COMPRET_FAIL;
            }
            
            iRet =DCICommit();
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("��������ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "��������ƽ̨�ļ��ָ���Ʊ�ʧ��");
                return COMPRET_FAIL;
            }
        }
    }
    else
    {
        /**��ȡ��ǰ���ε�ϵͳ���**/
        memset(cSql, 0x00, sizeof(cSql));
        memset(cHostNo, 0x00, sizeof(cHostNo));
        memset(cErrmsg, 0x00, sizeof(cErrmsg));
        memset(&stSplitFileControl, 0x00, sizeof(stSplitFileControl));
        sprintf(cSql, "select distinct byzd1 from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld"
                  , cTbaleName, cBatchDate, lPatBatchNo, lFileNum);
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
        iRet = DBSelectToVarChar(cErrmsg, cHostNo, cSql);
        if (0 >= iRet)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("��ѯ������ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "��ѯ������ϸ��ʧ��");
            return COMPRET_FAIL;
        }
        LOG(LM_DEBUG, Fmtmsg("hostno[%s]", cHostNo), "INFO")
        trim(cHostNo);
        LOG(LM_DEBUG, Fmtmsg("hostno[%s]", cHostNo), "INFO")
        
        memset(cSql, 0x00, sizeof(cSql));
        memset(cErrmsg, 0x00, sizeof(cErrmsg));
        sprintf(cSql, "select * from batch_splitfilecontrol where host_batch_no='%s' and host_no='%s'",
                  cHostBatchNo, cHostNo);
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
        iRet = prv_SelMulToStruct(&cSql, SD_BATCH_SPLITFILECONTROL, NUMELE(SD_BATCH_SPLITFILECONTROL), &stSplitFileControl);
        if (0 > iRet)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("��ѯ����ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "��ѯ����ƽ̨�ļ��ָ���Ʊ�ʧ��");
            return COMPRET_FAIL;
        }
        else if (0 == iRet)
        {
            /**�Ǽǲ�ֿ��Ʊ�**/
            memset(&stSplitFileControl, 0x00, sizeof(stSplitFileControl));
            strncpy(stSplitFileControl.host_batch_no, cHostBatchNo, sizeof(stSplitFileControl.host_batch_no));
            strncpy(stSplitFileControl.host_no, cHostNo, sizeof(stSplitFileControl.host_no));
            strncpy(stSplitFileControl.o_file_req, cOfileNameAll, sizeof(stSplitFileControl.o_file_req));
            strncpy(stSplitFileControl.file_req, cOfileNameAll, sizeof(stSplitFileControl.file_req));
            strcpy(stSplitFileControl.state, "0");
            memset(cErrmsg, 0x00, sizeof(cErrmsg));
            iRet = DBInsert("batch_splitfilecontrol", SD_BATCH_SPLITFILECONTROL, NUMELE(SD_BATCH_SPLITFILECONTROL)
                            , &stSplitFileControl, cErrmsg);
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("�Ǽ�����ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "�Ǽ�����ƽ̨�ļ��ָ���Ʊ�ʧ��");
                return COMPRET_FAIL;
            }
            
            iRet =DCICommit();
            if (0 > iRet)
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("�Ǽ�����ƽ̨�ļ��ָ���Ʊ�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "�Ǽ�����ƽ̨�ļ��ָ���Ʊ�ʧ��");
                return COMPRET_FAIL;
            }
            
            COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/state", "0");
        }
        else
        {
            LOG(LM_DEBUG, Fmtmsg("state[%s]", stSplitFileControl.state), "INFO")
            COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/state", stSplitFileControl.state);
            if (0 == strncmp(stSplitFileControl.state, "9", 1) || 0 == strncmp(stSplitFileControl.state, "1", 1))
            {
                fpub_SetCompStatus(lXmlhandle, -1);
                LOG(LM_STD, Fmtmsg("ϵͳ����"), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "ϵͳ����");
                return COMPRET_FAIL;
            }
        }
        
        /**ͳ�ƽ�����**/
        memset(cSql, 0x00, sizeof(cSql));
        memset(cErrmsg, 0x00, sizeof(cErrmsg));
        memset(cTotalNum, 0x00, sizeof(cTotalNum));
        memset(cTotalAmt, 0x00, sizeof(cTotalAmt));
        /**** ��������ѹ�����־Ϊ2-����ʱ,��Ҫ�������Ѽ��㵽���׽����  ****/
        if(strcmp(sSxfgsbz,"2") == 0)
        {
            sprintf(cSql, "select count(*),sum(jyje)+sum(sxfje) from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and shzt!='1' and clzt='9'", cTbaleName, cBatchDate, lPatBatchNo, lFileNum);
        }else
        {
            sprintf(cSql, "select count(*),sum(jyje) from %s where pkrq='%s' and ptpch=%ld and wjxh=%ld and shzt!='1' and clzt='9'", cTbaleName, cBatchDate, lPatBatchNo, lFileNum);
        }
        LOG(LM_DEBUG, Fmtmsg("SELECT[%s]", cSql), "INFO")
        iRet = DBSelectToMultiVarChar(cErrmsg, cSql, &cTotalNum, &cTotalAmt);
        if (0 > iRet)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("��ѯ������ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "��ѯ������ϸ��ʧ��");
            return COMPRET_FAIL;
        }
        
        /**ȡ�˺�**/
        memset(cLineBuf, 0x00, sizeof(cLineBuf));
        memset(cPayeeAcctNo, 0x00, sizeof(cPayeeAcctNo));
        fp_read = fopen(cOfileNameAll, "r");
        if (NULL == fopen)
        {
            fpub_SetCompStatus(lXmlhandle, -1);
            LOG(LM_STD, Fmtmsg("���ļ�ʧ��[%s]", cOfileNameAll), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "���ļ�ʧ��");
            return COMPRET_FAIL;
        }
        fgets(cLineBuf, sizeof(cLineBuf), fp_read);
        strncpy(cPayeeAcctNo, cLineBuf + 301, 32);
        /* add 20171113 zengy �ж����տ��˺�Ϊ����ȡ�����˺���Ϊѡȡ�������� beg */
        trim(cPayeeAcctNo);
        if(strlen(cPayeeAcctNo) == 0)
        {
            memset(cPayeeAcctNo, 0x00, sizeof(cPayeeAcctNo));
            strncpy(cPayeeAcctNo, cLineBuf + 133, 32);
            trim(cPayeeAcctNo);
        }
        /* add 20171113 zengy �ж����տ��˺�Ϊ����ȡ�����˺���Ϊѡȡ�������� end */
        COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/payeeacctno", cPayeeAcctNo);
        
        COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/hostno", cHostNo);
        COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/zbs", cTotalNum);
        COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/zje", cTotalAmt);
        COMP_SOFTSETXML("/batch/sjtj/splitfile/list|1/file_req", stSplitFileControl.file_req);
        COMP_SOFTSETXML("/batch/sjtj/splitfile/hostnum", "1");
        fclose(fp_read);
        fp_read = NULL;
    }
    
    fpub_SetCompStatus(lXmlhandle, 0);
    LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "DEBUG")
    fpub_SetCompStatus(lXmlhandle, 0);
    return 0;
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
 		
 		DCIFreeCursor(cur);
    return rs;
}
