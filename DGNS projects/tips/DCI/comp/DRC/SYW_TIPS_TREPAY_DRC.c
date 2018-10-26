/********************************************************************
  ��Ȩ����:�������ӹɷ����޹�˾
  ��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
  ��    ��:V3.0.00
  ����ϵͳ:AIX5.3
  �ļ�����:SYW_TIPS_PUBLIC_DRC.c
  �ļ�����:TIPS���Ի��������
  �� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
  �� �� Ա:sunpj
  ��������:
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

#include "../../eh/DRC/tips_trepayfileinfo_drc.h"
#include "../../eh/DRC/tips_trepayfiledetail_drc.h"

/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_TREPAY_INDB
  �������: ���⼯��֧���ļ���Ϣ���

  �������: 
  ���⼯��֧���ļ���Ϣ���
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  �ɹ�
  -1���������������� ʧ��

  ��Ҫ�������:
  ����              ����

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: sunpj
  ��������: 2017��05��31��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
 IRESULT SYW_TIPS_TREPAY_INDB(HXMLTREE lXmlhandle)
{
    int    iParas;
    int    iRet = 0;
    long   lFileLine = 0;
    double dTotalAmt = 0.00;
    char   cFileType[1 + 1]            = {0};
    char   cFileName[128 + 1]          = {0};
    char   cFilePath[512 + 1]          = {0};
    char   cFileNameAll[1024 + 1]      = {0};
    char   cTmp[512 + 1]               = {0};
    char   cBuf[2048 + 1]              = {0};
    char   cErrMsg[512 + 1]            = {0};
    FILE   *fp = NULL;
    
    SDB_TIPS_TREPAYFILEINFO      stTrePayFileInfo;
    SDB_TIPS_TREPAYFILEDETAIL    stTrePayFileDetail;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_TREPAY_INDB...����ʼ"), "INFO")
    
    memset(&stTrePayFileInfo, 0x00, sizeof(stTrePayFileInfo));
    
    COMP_PARACOUNTCHK(3);
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cFileType, 0x00, sizeof(cFileType));
    COMP_GETPARSEPARAS(1, cTmp, "�ļ�����");
    pstrcopy(cFileType, cTmp, sizeof(cFileType));
    LOG(LM_DEBUG, Fmtmsg("�ļ�����[%s]", cFileType), "INFO")
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cFileName, 0x00, sizeof(cFileName));
    COMP_GETPARSEPARAS(2, cTmp, "�ļ���");
    pstrcopy(cFileName, cTmp, sizeof(cFileName));
    LOG(LM_DEBUG, Fmtmsg("�ļ���[%s]", cFileName), "INFO")
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cFilePath, 0x00, sizeof(cFilePath));
    COMP_GETPARSEPARAS(3, cTmp, "�ļ�·��");
    pstrcopy(cFilePath, cTmp, sizeof(cFilePath));
    LOG(LM_DEBUG, Fmtmsg("�ļ�·��[%s]", cFilePath), "INFO")
    
    /**��ȡ����**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/zwrq", cTmp)
    pstrcopy(stTrePayFileInfo.trandate, cTmp, sizeof(stTrePayFileInfo.trandate));
    
    /**��ȡ��ˮ**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/pub/zhqzlsh", cTmp)
    stTrePayFileInfo.transeq = atol(cTmp);
    
    /**��ȡ����ˮ��**/
    pstrcopy(stTrePayFileInfo.packno, cTmp, sizeof(stTrePayFileInfo.packno));
    
    /**��ȡ���׻���**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/pub/jgdh", cTmp)
    pstrcopy(stTrePayFileInfo.brc, cTmp, sizeof(stTrePayFileInfo.brc));
    
    /**��ȡ���׹�Ա**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/pub/jygy", cTmp)
    pstrcopy(stTrePayFileInfo.tel, cTmp, sizeof(stTrePayFileInfo.tel));
    
    /**��ȡϵͳʱ��**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/sys/systime", cTmp)
    pstrcopy(stTrePayFileInfo.tel, cTmp, sizeof(stTrePayFileInfo.tel));
    
    /**��ȡ������Ϣ**/
    pstrcopy(stTrePayFileInfo.step, "0", sizeof(stTrePayFileInfo.step));
    
    /**��ȡ״̬��Ϣ**/
    pstrcopy(stTrePayFileInfo.state, "0", sizeof(stTrePayFileInfo.state));
    
    /**��ȡ�ļ�����**/
    pstrcopy(stTrePayFileInfo.filetype, cFileType, sizeof(stTrePayFileInfo.filetype));
    
    /**��ȡ�ļ���**/
    pstrcopy(stTrePayFileInfo.filename, cFileName, sizeof(stTrePayFileInfo.filename));
    
    /**��ȡ�������**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/TreCode", cTmp)
    pstrcopy(stTrePayFileInfo.trecode, cTmp, sizeof(stTrePayFileInfo.trecode));
    
    /**��ȡ�������ش���**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/FinOrgCode", cTmp)
    pstrcopy(stTrePayFileInfo.finorgcode, cTmp, sizeof(stTrePayFileInfo.finorgcode));
    
    /**��ȡ֧��ƾ֤����**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayoutVouType", cTmp)
    pstrcopy(stTrePayFileInfo.payoutvoutype, cTmp, sizeof(stTrePayFileInfo.payoutvoutype));
    
    /**��ȡ֧����ʽ**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayMode", cTmp)
    pstrcopy(stTrePayFileInfo.paytype, cTmp, sizeof(stTrePayFileInfo.paytype));
    
    /**��ȡ�տ����˺�**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayeeAcct", cTmp)
    pstrcopy(stTrePayFileInfo.payeeacct, cTmp, sizeof(stTrePayFileInfo.payeeacct));
    
    /**��ȡ�տ�������**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayeeName", cTmp)
    pstrcopy(stTrePayFileInfo.payeename, cTmp, sizeof(stTrePayFileInfo.payeename));
    
    /**��ȡ�տ��˵�ַ**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayeeAddr", cTmp)
    pstrcopy(stTrePayFileInfo.payeeaddr, cTmp, sizeof(stTrePayFileInfo.payeeaddr));
    
    /**��ȡ�տ��˿������к�**/
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips/req/PayeeOpBkNo", cTmp)
    pstrcopy(stTrePayFileInfo.payeeopbk, cTmp, sizeof(stTrePayFileInfo.payeeopbk));
    
    /**��ȡ�ļ���Ϣ&�Ǽ��ļ���Ϣ����----BEGIN**/
    sprintf(cFileNameAll, "%s/%s", cFilePath, cFileName);
    if (NULL == (fp = fopen(cFileNameAll, "r")))
    {
        LOG(LM_STD, Fmtmsg("��ȡ�ļ�ʧ��[%s]", cFileNameAll), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 100001, "��ȡ�ļ�ʧ��");
        return COMPRET_FAIL;
    }
    
    while (NULL != fgets(cBuf, sizeof(cBuf), fp))
    {
        lFileLine++;
        //LOG(LM_DEBUG, Fmtmsg("%d---[%s]", lFileLine, cBuf), "INFO")
        if (1 == lFileLine)
        {
            /**��ȡƾ֤����**/
            GetListbyDiv(cBuf, 2, stTrePayFileInfo.vouno, ',','\\');
            
            /**��ȡƾ֤����**/
            GetListbyDiv(cBuf, 3, stTrePayFileInfo.voudate, ',','\\');
            
            /**��ȡ�������˺�**/
            GetListbyDiv(cBuf, 4, stTrePayFileInfo.payacct, ',','\\');
            
            /**��ȡ����������**/
            GetListbyDiv(cBuf, 5, stTrePayFileInfo.payname, ',','\\');
            
            /**��ȡ�����˵�ַ**/
            GetListbyDiv(cBuf, 6, stTrePayFileInfo.payaddr, ',','\\');
            
            /**��ȡ����**/
            GetListbyDiv(cBuf, 11, stTrePayFileInfo.addword, ',','\\');
            
            /**��ȡԤ������**/
            GetListbyDiv(cBuf, 12, stTrePayFileInfo.budgettype, ',','\\');
            
            /**��ȡ�����ڱ�־**/
            GetListbyDiv(cBuf, 13, stTrePayFileInfo.trimsign, ',','\\');
            
            /**��ȡ�������**/
            GetListbyDiv(cBuf, 14, stTrePayFileInfo.ofyear, ',','\\');
            
            /**��ȡ�ܽ��**/
            memset(cTmp, 0x00, sizeof(cTmp));
            GetListbyDiv(cBuf, 15, cTmp, ',','\\');
            stTrePayFileInfo.totalamt = atof(cTmp);
            
            /**��ȡ�ܱ���**/
            memset(cTmp, 0x00, sizeof(cTmp));
            GetListbyDiv(cBuf, 16, cTmp, ',','\\');
            stTrePayFileInfo.totalnum = atol(cTmp);
            
            //LOG(LM_DEBUG, Fmtmsg("%s---%d---%.2f", stTrePayFileInfo.ofyear, stTrePayFileInfo.totalnum, stTrePayFileInfo.totalamt), "INFO")
            
            /**�Ǽ��ļ���Ϣ��**/
            memset(cErrMsg, 0x00, sizeof(cErrMsg));
            iRet = DBInsert("tips_trepayfileinfo", SD_TIPS_TREPAYFILEINFO, NUMELE(SD_TIPS_TREPAYFILEINFO), &stTrePayFileInfo, cErrMsg);
            if(0 > iRet)
            {
                fclose(fp);
                fp = NULL;
                DCIRollback();
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������֧���ļ���Ϣʧ��"),
                fpub_GetCompname(lXmlhandle))
            }
        }
        else
        {
            memset(&stTrePayFileDetail, 0x00, sizeof(stTrePayFileDetail));
            
            /**��ȡ����**/
            pstrcopy(stTrePayFileDetail.trandate, stTrePayFileInfo.trandate, sizeof(stTrePayFileDetail.trandate));
    
            /**��ȡ��ˮ**/
            stTrePayFileDetail.transeq = stTrePayFileInfo.transeq;
            
            /**��ȡ���**/
            memset(cTmp, 0x00, sizeof(cTmp));
            GetListbyDiv(cBuf, 1, cTmp, ',','\\');
            stTrePayFileDetail.seqno = atol(cTmp);
            
            /**��ȡԤ�㵥λ����**/
            GetListbyDiv(cBuf, 2, stTrePayFileDetail.bdgorgcode,  ',','\\');
            
            /**��ȡ���ܿ�Ŀ����**/
            GetListbyDiv(cBuf, 3, stTrePayFileDetail.funcsbtcode,  ',','\\');
            
            /**��ȡ���ÿ�Ŀ����**/
            GetListbyDiv(cBuf, 4, stTrePayFileDetail.ecnomicsubjectcode,  ',','\\');
            
            /**��ȡ���**/
            memset(cTmp, 0x00, sizeof(cTmp));
            GetListbyDiv(cBuf, 5, cTmp, ',','\\');
            stTrePayFileDetail.amt = atof(cTmp);
            dTotalAmt +=stTrePayFileDetail.amt;
            
            /**��ȡ�ʻ�����**/
            GetListbyDiv(cBuf, 6, stTrePayFileDetail.acctprop,  ',','\\');
            
            /**�Ǽ���ϸ��**/
            memset(cErrMsg, 0x00, sizeof(cErrMsg));
            iRet = DBInsert("tips_trepayfiledetail", SD_TIPS_TREPAYFILEDETAIL, NUMELE(SD_TIPS_TREPAYFILEDETAIL), &stTrePayFileDetail, cErrMsg);
            if(0 > iRet)
            {
                fclose(fp);
                fp = NULL;
                DCIRollback();
                LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError() ),"ERROR")
                fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
                LOGRET(COMPRET_FAIL,LM_STD,Fmtmsg("��������֧����ϸ��Ϣʧ��"),
                fpub_GetCompname(lXmlhandle))
            }
        }
    }
    fclose(fp);
    fp = NULL;
    /**��ȡ�ļ���Ϣ&�Ǽ��ļ���Ϣ����----END**/
    
    /**�ļ��ܱ���У��**/
    if (lFileLine - 1 != stTrePayFileInfo.totalnum)
    {
        DCIRollback();
        LOG(LM_STD, Fmtmsg("�ļ��ܱ�����һ��"), "ERROR")  
        fpub_SetMsg(lXmlhandle, 100001, Fmtmsg("�ļ��ܱ�����һ��"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;  
    }
    
    /**�ļ��ܽ��У��**/
    if (dTotalAmt - stTrePayFileInfo.totalamt < -0.01 || dTotalAmt - stTrePayFileInfo.totalamt > 0.01)
    {
        DCIRollback();
        LOG(LM_STD, Fmtmsg("�ļ��ܽ�һ��"), "ERROR")  
        fpub_SetMsg(lXmlhandle, 100001, Fmtmsg("�ļ��ܽ�һ��"));
        fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
        return COMPRET_FAIL;  
    }
    
    /**�����ύ**/
    if (0 > DCICommit())
    {
        DCIRollback();
        LOG(LM_STD, Fmtmsg("���ݿ����ʧ��,sqlerr[%s]", DCILastError()), "ERROR")  
        fpub_SetMsg(lXmlhandle, 100001, Fmtmsg("�ύ���ݿ�ʧ��"));
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;     
    }
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_TREPAY_INDB...�������"), "INFO")
    fpub_SetCompStatus(lXmlhandle, 0);
    return 0;
}