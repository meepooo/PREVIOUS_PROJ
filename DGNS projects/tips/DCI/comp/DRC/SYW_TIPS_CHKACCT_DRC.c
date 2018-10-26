/********************************************************************
  ��Ȩ����:�������ӹɷ����޹�˾
  ��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
  ��    ��:V3.0.00
  ����ϵͳ:AIX5.3
  �ļ�����:SYW_TIPS_CHKACCT_DRC.ec
  �ļ�����:TIPS���ʽ��������
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
#include <math.h>
#include <sys/types.h>
#include <unistd.h>
#include "gaps_head.h"

#include  "../../eh/tips_drls.h"   
#include  "../../eh/tips_ssplksfmx.h"
#include  "../../eh/tips_pljydj.h"
#include  "../../eh/tips_dzbpdj.h"

/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_RZTZ
  �������: TIPS���յ���

  �������: 
  TIPS���յ���
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  1                  ���Ϻ��ĵ���
  0                  ���˳ɹ�
  -1���������������� ����ʧ��

  ��Ҫ�������:
  ����              ����
  ������ˮ��        tips_drls
  ������˰��ϸ��    tips_ssplksfmx
  �������׵ǼǱ�    tips_pljydj
  ���˲�ƽ�ǼǱ�    tips_dzbpdj

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: sunpj
  ��������: 2017��04��26��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_RZTZ(HXMLTREE lXmlhandle)
{
    int iParas;
    int iSqlRet = 0;
    int iRet = 0;
    
    char cTranDate[8+1]; /* ԭ�������� */
    char cTranSeq[16+1]; /* ԭ������ˮ */
    char cChkType[1+1];  /* �������� */
    char cChgDate[8+1];  /* �������� */
    char cChgTime[6+1];  /* ����ʱ�� */
    char cChgSeq[16+1];  /* ������ˮ */
    char cChgFlag[4+1];  /* ���˱�־ 0-���� 1-�ֹ����� */
    char cIsBatch[1+1];  /* ������˰�ѱ�־ */
    char cChkFlag[1+1];  /* ��ˮ����˱�־ */
    char cSql[1024+1];   /* SQL��� */
    char cTmp[128+1];
    char cErrmsg[256+1];
    
    SDB_TIPS_DRLS stDrls;
    SDB_TIPS_SSPLKSFMX stPlksfmx;
    SDB_TIPS_DZBPDJ stDzbpdj;
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_RZTZ...����ʼ"), "INFO") 
    
    COMP_PARACOUNTCHK(4);
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cTranDate, 0x00, sizeof(cTranDate));
    COMP_GETPARSEPARAS(1, cTmp, "ԭ��������");
    pstrcopy(cTranDate, cTmp, sizeof(cTranDate));
    LOG(LM_DEBUG, Fmtmsg("ԭ��������[%s]", cTranDate), "INFO") 
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cTranSeq, 0x00, sizeof(cTranSeq));
    COMP_GETPARSEPARAS(2, cTmp, "ԭ������ˮ");
    pstrcopy(cTranSeq, cTmp, sizeof(cTranSeq));
    LOG(LM_DEBUG, Fmtmsg("ԭ������ˮ[%s]", cTranSeq), "INFO") 
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cChkType, 0x00, sizeof(cChkType));
    COMP_GETPARSEPARAS(3, cTmp, "��������");
    pstrcopy(cChkType, cTmp, sizeof(cChkType));
    LOG(LM_DEBUG, Fmtmsg("��������[%s]", cChkType), "INFO") 
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cChgFlag, 0x00, sizeof(cChgFlag));
    COMP_GETPARSEPARAS(4, cTmp, "���˱�־");
    pstrcopy(cChgFlag, cTmp, sizeof(cChgFlag));
    LOG(LM_DEBUG, Fmtmsg("���˱�־[%s]", cChgFlag), "INFO") 
    
    memset(cSql, 0x00, sizeof(cSql));
    memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));
    sprintf(cSql, "select * from tips_dzbpdj where zwrq='%s' and zhqzlsh=%ld and dzlx='%s'"
                , cTranDate, atol(cTranSeq), cChkType);
    LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
    iSqlRet = prv_SelMulToStruct(&cSql, SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj);
    if (0 > iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("��ѯ��ƽ��ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "��ѯ��ƽ��ϸ��ʧ��");
        return -1;
    }
    else if(0 == iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("���˲�ƽ��Ϣ������"), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "���˲�ƽ��Ϣ�����ڣ���ȷ��");
        return -1;
    }
    if (0 == memcmp(stDzbpdj.clzt, "3", 1))
    {
        LOG(LM_STD, Fmtmsg("�ѵ���"), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "�ѵ���");
        return -1;
    }
    else if (0 == memcmp(stDzbpdj.clzt, "9", 1))
    {
        LOG(LM_STD, Fmtmsg("������..."), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "�����У���ȷ��");
        return -1;
    }
    else if (0 == memcmp(stDzbpdj.clzt, "0", 1))
    {
        trim(stDzbpdj.jyzh);
        if (0 == strlen(stDzbpdj.jyzh) && 0 == memcmp(cChgFlag, "ZCTZ", 4))
        {
            LOG(LM_STD, Fmtmsg("�ֽ��ױ����ֹ�����"), "ERROR")
            memset(cSql, 0x00, sizeof(cSql));
            memset(cChgDate, 0x00, sizeof(cChgDate));
        		memset(cChgTime, 0x00, sizeof(cChgTime));
        		memset(cChgSeq, 0x00, sizeof(cChgSeq));
       			COMP_SOFTGETXML("/pub/zwrq", cChgDate);
        		COMP_SOFTGETXML("/sys/systime", cChgTime);
        		COMP_SOFTGETXML("/pub/zhqzlsh", cChgSeq);
						sprintf(cSql, "update tips_dzbpdj set clrq='%s',clsj='%s',cllsh=%ld, clzt='1' where zwrq='%s' and zhqzlsh=%ld and dzlx='%s'"
                ,cChgDate, cChgTime, atol(cChgSeq), cTranDate, atol(cTranSeq), cChkType);
    				LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
    				iSqlRet = DCIExecuteDirect(cSql);
    				if (0 > iSqlRet)
    				{
        			LOG(LM_STD, Fmtmsg("���¶��˲�ƽ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
       				fpub_SetCompStatus(lXmlhandle, -1);
        			fpub_SetMsg(lXmlhandle, 100001, "���¶��˲�ƽ��ʧ��");
       				return -1;
    				}
    				iSqlRet = DCICommit();
    				if ( iSqlRet < 0 )
   					 {
      					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      					DCIRollback();     	
    				  	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
       					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
  				     	return COMPRET_FAIL;     
   					 }
            fpub_SetCompStatus(lXmlhandle, -1);
            fpub_SetMsg(lXmlhandle, 100001, "�ֽ��������ֹ�����");
            return -1;
        }
        if (0 != strlen(stDzbpdj.jyzh) && 0 == memcmp(cChgFlag, "SGTZ", 4))
        {
            LOG(LM_STD, Fmtmsg("�ý��ײ����ֹ�����"), "ERROR")
            fpub_SetCompStatus(lXmlhandle, -1);
            fpub_SetMsg(lXmlhandle, 100001, "�ý��ײ����ֹ�����,���ȵ���");
            return -1;
        }
        memset(cSql, 0x00, sizeof(cSql));
        memset(cChgDate, 0x00, sizeof(cChgDate));
        memset(cChgTime, 0x00, sizeof(cChgTime));
        memset(cChgSeq, 0x00, sizeof(cChgSeq));
        COMP_SOFTGETXML("/pub/zwrq", cChgDate);
        COMP_SOFTGETXML("/sys/systime", cChgTime);
        COMP_SOFTGETXML("/pub/zhqzlsh", cChgSeq);
        sprintf(cSql, "update tips_dzbpdj set clrq='%s',clsj='%s',cllsh=%ld,clzt='9' where zwrq='%s' and zhqzlsh=%ld and dzlx='%s'"
                    , cChgDate, cChgTime, atol(cChgSeq), cTranDate, atol(cTranSeq), cChkType);
        pstrcopy(stDzbpdj.clrq, cChgDate, sizeof(stDzbpdj.clrq));
        stDzbpdj.cllsh=atol(cChgSeq);
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
    } 
    else
    {
    	  trim(stDzbpdj.jyzh);
        if (0 == strlen(stDzbpdj.jyzh) && 0 == memcmp(cChgFlag, "ZCTZ", 4))
        {
            LOG(LM_STD, Fmtmsg("�ֽ��ױ����ֹ�����"), "ERROR")
            memset(cSql, 0x00, sizeof(cSql));
            memset(cChgDate, 0x00, sizeof(cChgDate));
        		memset(cChgTime, 0x00, sizeof(cChgTime));
        		memset(cChgSeq, 0x00, sizeof(cChgSeq));
       			COMP_SOFTGETXML("/pub/zwrq", cChgDate);
        		COMP_SOFTGETXML("/sys/systime", cChgTime);
        		COMP_SOFTGETXML("/pub/zhqzlsh", cChgSeq);
						sprintf(cSql, "update tips_dzbpdj set clrq='%s',clsj='%s',cllsh=%ld, clzt='1' where zwrq='%s' and zhqzlsh=%ld and dzlx='%s'"
                ,cChgDate, cChgTime, atol(cChgSeq), cTranDate, atol(cTranSeq), cChkType);
    				LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
    				iSqlRet = DCIExecuteDirect(cSql);
    				if (0 > iSqlRet)
    				{
        			LOG(LM_STD, Fmtmsg("���¶��˲�ƽ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
       				fpub_SetCompStatus(lXmlhandle, -1);
        			fpub_SetMsg(lXmlhandle, 100001, "���¶��˲�ƽ��ʧ��");
       				return -1;
    				}
    				iSqlRet = DCICommit();
    				if ( iSqlRet < 0 )
   					 {
      					LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")  
      					DCIRollback();     	
    				  	fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
       					fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
  				     	return COMPRET_FAIL;     
   					 }
            fpub_SetCompStatus(lXmlhandle, -1);
            fpub_SetMsg(lXmlhandle, 100001, "�ֽ��������ֹ�����");
            return -1;
        }
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "update tips_dzbpdj set clzt='9' where zwrq='%s' and zhqzlsh=%ld and dzlx='%s'"
                    , cTranDate, atol(cTranSeq), cChkType);
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
    }
    iSqlRet = DCIExecuteDirect(cSql);
    if (0 > iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("���¶��˲�ƽ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "���¶��˲�ƽ��ʧ��");
        return -1;
    }
    /*modify by liurj 20181018 add commit begin*/
	iSqlRet = DCICommit();
	if ( iSqlRet < 0 )
	{
	  LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
	  DCIRollback();
	  fpub_SetMsg(lXmlhandle, 24101,Fmtmsg("�ύ���ݿ�ʧ��"));
	  fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
	  return COMPRET_FAIL;
	}
    /*modify by liurj 20181018 add commit end*/

    
    /* ��ѯԭ������Ϣ */
    memset(cSql, 0x00, sizeof(cSql));
    sprintf(cSql, "select * from tips_drls where zwrq='%s' and zhqzlsh=%ld", cTranDate, atol(cTranSeq));
    LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
    iSqlRet = prv_SelMulToStruct(&cSql, SD_TIPS_DRLS, NUMELE(SD_TIPS_DRLS), &stDrls);
    if (0 > iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("��ѯ������ˮ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "��ѯ������ˮ��ʧ��");
        return -1;
    }
    else if (0 == iSqlRet)
    {
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "select * from tips_ssplksfmx where zwrq='%s' and plmxxh=%ld", cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
        iSqlRet = prv_SelMulToStruct(&cSql, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx);
        if(0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("��ѯ������ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetCompStatus(lXmlhandle, -1);
            fpub_SetMsg(lXmlhandle, 100001, "��ѯ������ϸ��ʧ��");
            return -1;
        }
        else if(0 == iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("ԭ������Ϣ������"), "ERROR")
            fpub_SetCompStatus(lXmlhandle, -1);
            fpub_SetMsg(lXmlhandle, 100001, "ԭ������Ϣ�����ڣ���ȷ��");
            return -1;
        }
        strcpy(cIsBatch, "Y");
        memcpy(cChkFlag, stPlksfmx.kzbz, 2);
        memcpy(stDrls.workdate, stPlksfmx.workdate, sizeof(stDrls.workdate));
        memcpy(stDrls.paybkcode, stPlksfmx.paybkcode, sizeof(stDrls.paybkcode));
        memcpy(stDrls.payeebankno, stPlksfmx.payeebankno, sizeof(stDrls.payeebankno));
        COMP_SOFTSETXML("/tips/ylsxx/msgno", "3102");
    }
    else
    {
        strcpy(cIsBatch, "N");
        memcpy(cChkFlag, stDrls.dzbz, 2);
        COMP_SOFTSETXML("/tips/ylsxx/msgno", stDrls.msgno);
    }
    
    LOG(LM_STD, Fmtmsg("��������[%s]...���˽��[%s]...��ˮ����˱�־[%s]", stDzbpdj.dzlx, stDzbpdj.dzjg, cChkFlag), "ERROR")
    if (0 == memcmp(stDzbpdj.dzlx, "1", 1) && 0 == memcmp(stDzbpdj.dzjg, "2", 1))
    {
        //���Ķ��� ǰ�ö�
        iRet = prv_rztz_qzdz(lXmlhandle, 1, cIsBatch, stDrls.workdate, stDrls.paybkcode
                              , stDrls.payeebankno, cTranDate, cTranSeq);
        fpub_SetCompStatus(lXmlhandle, iRet);
        if (-1 == iRet)
        {
            LOG(LM_STD, Fmtmsg("����ʧ��...[%d]", iRet), "ERROR")
            return -1;
        }
    }
    else if (0 == memcmp(stDzbpdj.dzlx, "1", 1) && 0 == memcmp(stDzbpdj.dzjg, "3", 1))
    {
        //���Ķ��� ���Ķ�
        iRet = prv_rztz_hxdz(lXmlhandle, cIsBatch, stDrls.workdate, stDrls.paybkcode
                              , stDrls.payeebankno, cTranDate, cTranSeq);
        fpub_SetCompStatus(lXmlhandle, iRet);
        if (-1 == iRet)
        {
            LOG(LM_STD, Fmtmsg("����ʧ��...[%d]", iRet), "ERROR")
            return -1;
        }
    }
    else if ((0 == memcmp(stDzbpdj.dzlx, "2", 1) || 0 == memcmp(stDzbpdj.dzlx, "3", 1))
             && 0 == memcmp(stDzbpdj.dzjg + 1, "2", 1))
    {
        //���ж��� ǰ�ö�
        iRet = prv_rztz_qzdz(lXmlhandle, 2, cIsBatch, stDrls.workdate, stDrls.paybkcode
                              , stDrls.payeebankno, cTranDate, cTranSeq);
        fpub_SetCompStatus(lXmlhandle, iRet);
        if (-1 == iRet)
        {
            LOG(LM_STD, Fmtmsg("����ʧ��...[%d]", iRet), "ERROR")
            return -1;
        }
    }
    else if ((0 == memcmp(stDzbpdj.dzlx, "2", 1) || 0 == memcmp(stDzbpdj.dzlx, "3", 1))
             && 0 == memcmp(stDzbpdj.dzjg + 1, "3", 1))
    {
        //���ж��� ���ж�
        iRet = prv_rztz_rhdz(lXmlhandle, cIsBatch, stDrls.workdate, cTranDate, cTranSeq);
        fpub_SetCompStatus(lXmlhandle, iRet);
        if (-1 == iRet)
        {
            LOG(LM_STD, Fmtmsg("����ʧ��...[%d]", iRet), "ERROR")
            return iRet;
        }
    }
    else
    {
        LOG(LM_STD, Fmtmsg("�ý���δ���˻��Ѷ�ƽ"), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "�ý���δ���˻��Ѷ�ƽ");
        return -1;
    }
    
    memset(cTmp, 0x00, sizeof(cTmp));
    COMP_SOFTGETXML("/tips_host/req/jydm", cTmp);
    LOG(LM_DEBUG, Fmtmsg("��������[%s]���˱�־[%s]", cChgFlag, cTmp), "INFO")
    if (0 == memcmp(cChgFlag, "ZCTZ", 4) && 0 == memcmp(cTmp, "dbzz", 4))
    {
        COMP_SOFTSETXML("/tips/dzbpxx/detail/clrq", stDzbpdj.zwrq);
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "%d", stDzbpdj.zhqzlsh);
        COMP_SOFTSETXML("/tips/dzbpxx/detail/cllsh", cTmp);
    }
    else
    {
        COMP_SOFTSETXML("/tips/dzbpxx/detail/clrq", stDzbpdj.clrq);
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "%d", stDzbpdj.cllsh);
        COMP_SOFTSETXML("/tips/dzbpxx/detail/cllsh", cTmp);
    }
    COMP_SOFTSETXML("/tips/dzbpxx/detail/paybkcode", stDzbpdj.paybkcode);
    COMP_SOFTSETXML("/tips/dzbpxx/detail/jyzh", stDzbpdj.jyzh);
    COMP_SOFTSETXML("/tips/dzbpxx/detail/dfzh", stDzbpdj.dfzh);
    memset(cTmp, 0x00, sizeof(cTmp));
    sprintf(cTmp, "%.2f", stDzbpdj.jyje);
    COMP_SOFTSETXML("/tips/dzbpxx/detail/jyje", cTmp);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_RZTZ...�������"), "INFO") 
    return iRet;
}

int prv_rztz_hxdz(HXMLTREE lXmlhandle, char *cIsBatch, char *cChkDate
                   , char *cPayBkCode, char *cPayeeBankNo
                   , char *cTranDate, char *cTranSeq)
{
    int iSqlRet = 0;
    
    char cSql[1024+1];  /* SQL��� */
    char cChkRlt[2+1];  /* ���˽�� */
    char cErrmsg[256+1];
    char cChkAcctOrd[4+1];/* �������κ� */
    
    memset(cChkRlt, 0x00, sizeof(cChkRlt));
    memset(cSql, 0x00, sizeof(cSql));
    sprintf(cSql, "select dzjg from tips_dzbpdj where zwrq='%s' and zhqzlsh=%ld and dzlx='3' and (clzt='0' or clzt='1')"
                 , cTranDate, atol(cTranSeq));
    LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
    iSqlRet = DBSelectToVar(cErrmsg, cChkRlt, cSql);
    if (0 > iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("��ѯ���˲�ƽ��ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetMsg(lXmlhandle, 100001, "��ѯ���˲�ƽ��ϸ��ʧ��");
        return -1;
    }
    if (0 == iSqlRet)
    {
        /* ��tips_ssdzplt����ȥ��ѯ�˹������Ƿ��Ѷ��� */
        memset(cChkAcctOrd, 0x00, sizeof(cChkAcctOrd));
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "select chkacctord from tips_ssdzplt where chkdate='%s' and paybkcode='%s'"
                " and payeebankno='%s' and chkaccttype='1'", cChkDate, cPayBkCode, cPayeeBankNo);
        LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO") 
        iSqlRet = DBSelectToVar(cErrmsg, cChkAcctOrd, cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("��ѯTIPS���˱�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "��ѯTIPS���˱�ʧ��");
            return -1;
        }
        if (0 == iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("������¼,���ں��Ķ�,δ��TIPS����,�ݲ�����."), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "TIPSδ���ˣ��ݲ�����");
            return -1;
        }
        LOG(LM_STD, Fmtmsg("������¼,���ں��Ķ�,ǰ����TIPS��ʧ��,���Ϻ���Ĩ�˴���."), "ERROR")
        COMP_SOFTSETXML("/tips_host/req/jydm", "dbmz");
        COMP_SOFTSETXML("/tips/xyxx", "������Ĩ��");
        COMP_SOFTSETXML("/tips/jyzt", "3");
        return 1;
        
    }
    
    trim(cChkRlt);
    if (0 == memcmp(cChkRlt + 1, "3", 1)) /* �����˽��Ϊ93-��TIPS����,������,ֻ�轫ԭ��ˮ״̬����Ϊ�ɹ� */
    {
        LOG(LM_STD,Fmtmsg("������¼,���ں��Ķ�,TIPSҲ��,�轫ԭ��ˮ״̬����Ϊ�ɹ�����."),"INFO");
        
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "update tips_dzbpdj set clzt='3' where zwrq='%s' and zhqzlsh=%ld"
                    , cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("���¶��˲�ƽ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "���¶��˲�ƽ��ʧ��");
            return -1;
        }
        memset(cSql, 0x00, sizeof(cSql));
        if (0 == memcmp(cIsBatch, "Y", 1))
        {
            sprintf(cSql, "update tips_ssplksfmx set kzbz='11'||substr(kzbz,3,6),czbd='7' where zwrq='%s' and plmxxh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        else
        {
            sprintf(cSql, "update tips_drls set dzbz='11',jyzt='0' where zwrq='%s' and zhqzlsh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("������ˮ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "������ˮ��ʧ��");
            return -1;
        }
        return 0;
    }
    else /* �����˽��Ϊ92-��TIPS����,�ҷ��� */
    {
        LOG(LM_STD,Fmtmsg("TIPS���˽��[%c]", cChkRlt[1]),"INFO");
        fpub_SetMsg(lXmlhandle, 100001, "ϵͳ�����޷����ˣ���ȷ��");
        return -1;
    }
    
    return 0;
}

int prv_rztz_rhdz(HXMLTREE lXmlhandle, char *cIsBatch, char *cChkDate
                   , char *cTranDate, char *cTranSeq)
{
    int iSqlRet = 0;
    char cErrmsg[256+1];
    
    char cSql[1024+1];  /* SQL��� */
    char cChkRlt[2+1];  /* ���˽�� */
    char cBuf[256];
    char cIniFile[256];
    char cIsPldz[1+1];/* ���������Ƿ������� */
    char cChkState[1+1];
    
    if (0 == memcmp(cIsBatch, "Y", 1))
    {
        memset(cIniFile, 0x00, sizeof(cIniFile));
        snprintf(cIniFile, sizeof(cIniFile), "%s/etc/tips.ini", getenv("HOME"));
        memset(cBuf, 0x00, sizeof(cBuf));
        memset(cIsPldz, 0x00, sizeof(cIsPldz));
        if(ExGetCfgItem(cIniFile, "HXDZ", "PLDZ", cBuf,sizeof(cBuf))<0)
        {
            cBuf[0]='1';/* 1-�μ�(ȱʡ) */
        }
        pstrcopy(cIsPldz, cBuf, sizeof(cIsPldz));

        if (0 == memcmp(cIsPldz, "0", 1))/* �����������������,��ʱ�����ͺ��Ĳ��� */
        {
            LOG(LM_STD,Fmtmsg("������¼,����TIPS��,ǰ������Ĳ�����,ȱʡ��ƽ,���Ϻ��Ĳ��˴���."),"INFO");
            COMP_SOFTSETXML("/tips_host/req/jydm", "dbzz");
            COMP_SOFTSETXML("/tips/xyxx", "�����ղ���");
            COMP_SOFTSETXML("/tips/jyzt", "4");
            return 1;
        }
    }
    
    memset(cChkRlt, 0x00, sizeof(cChkRlt));
    memset(cSql, 0x00, sizeof(cSql));
    sprintf(cSql, "select dzjg from tips_dzbpdj where zwrq='%s' and zhqzlsh=%ld and dzlx='1' and (clzt='0' or clzt='1')"
                 , cTranDate, atol(cTranSeq));
    LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
    iSqlRet = DBSelectToVar(cErrmsg, cChkRlt, cSql);
    if (0 > iSqlRet)
    {
        LOG(LM_STD, Fmtmsg("��ѯ���˲�ƽ��ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetMsg(lXmlhandle, 100001, "��ѯ���˲�ƽ��ϸ��ʧ��");
        return -1;
    }
    else if (0 == iSqlRet)
    {
        /* ��tips_checkresult����ȥ��ѯ�˹������Ƿ��Ѷ��� */
        memset(cChkState, 0x00, sizeof(cChkState));
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "select checkstate from tips_checkresult where checkdate='%s' and checksystem='00' and checkstate='0'", cChkDate);
        LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO") 
        iSqlRet = DBSelectToVar(cErrmsg, cChkState, cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("��ѯ���Ķ��˱�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "��ѯ���Ķ��˱�ʧ��");
            return -1;
        }
        if (0 == iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("������¼,����TIPS��,δ����Ķ���,�ݲ�����."), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "����δ���ˣ��ݲ�����");
            return -1;
        }
        LOG(LM_STD, Fmtmsg("������¼,����TIPS��,ǰ������Ķ�ʧ��,���Ϻ��Ĳ��ʴ���."), "ERROR")
        COMP_SOFTSETXML("/tips_host/req/jydm", "dbzz");
        COMP_SOFTSETXML("/tips/xyxx", "�����ղ���");
        COMP_SOFTSETXML("/tips/jyzt", "4");
        return 1;
    }
    
    trim(cChkRlt);
    if (0 == memcmp(cChkRlt, "3", 1)) /* �����˽��Ϊ39-����Ķ���,���Ķ�,ֻ�轫ԭ��ˮ״̬����Ϊ�ɹ� */
    {
        LOG(LM_STD,Fmtmsg("������¼,���ں��Ķ�,TIPSҲ��,�轫ԭ��ˮ״̬����Ϊ�ɹ�����."),"INFO");
        
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "update tips_dzbpdj set clzt='3' where zwrq='%s' and zhqzlsh=%ld"
                    , cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("���¶��˲�ƽ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "���¶��˲�ƽ��ʧ��");
            return -1;
        }
        memset(cSql, 0x00, sizeof(cSql));
        if (0 == memcmp(cIsBatch, "Y", 1))
        {
            sprintf(cSql, "update tips_ssplksfmx set kzbz='11'||substr(kzbz,3,6),czbd='7' where zwrq='%s' and plmxxh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        else
        {
            sprintf(cSql, "update tips_drls set dzbz='11',jyzt='0' where zwrq='%s' and zhqzlsh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("������ˮ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "������ˮ��ʧ��");
            return -1;
        }
        return 0;
    }
    else /* �����˽��Ϊ29-����Ķ���,ǰ�ö� */
    {
        LOG(LM_STD,Fmtmsg("���Ķ��˽��[%c]", cChkRlt[0]),"INFO");
        fpub_SetMsg(lXmlhandle, 100001, "ϵͳ�����޷����ˣ���ȷ��");
        return -1;
    }
    
    return 0;
}

int prv_rztz_qzdz(HXMLTREE lXmlhandle, int iChkType, char *cIsBatch
                   , char *cChkDate , char *cPayBkCode, char *cPayeeBankNo
                   , char *cTranDate, char *cTranSeq)
{
    int iSqlRet = 0;
    int iIsFailed = 0;
    
    char cSql[1024+1];  /* SQL��� */
    char cChkRlt[2+1];  /* ���˽�� */
    char cBuf[256];
    char cIniFile[256];
    char cIsPldz[1+1];/* ���������Ƿ������� */
    char cChkState[1+1];
    char cErrmsg[256+1];
    char cChkAcctOrd[4+1];/* �������κ� */
    
    if (1 == iChkType)/* ����Ķ��� ǰ�ö� */
    {
        memset(cChkRlt, 0x00, sizeof(cChkRlt));
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "select dzjg from tips_dzbpdj where zwrq='%s' and zhqzlsh=%ld and dzlx='3' and (clzt='0' or clzt='1')"
                     , cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
        iSqlRet = DBSelectToVar(cErrmsg, cChkRlt, cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("��ѯ���˲�ƽ��ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "��ѯ���˲�ƽ��ϸ��ʧ��");
            return -1;
        }
        if (0 == iSqlRet)
        {
            /* ��tips_ssdzplt����ȥ��ѯ�˹������Ƿ��Ѷ��� */
            memset(cChkAcctOrd, 0x00, sizeof(cChkAcctOrd));
            memset(cSql, 0x00, sizeof(cSql));
            sprintf(cSql, "select chkacctord from tips_ssdzplt where chkdate='%s' and paybkcode='%s'"
                    " and payeebankno='%s' and chkaccttype='1'", cChkDate, cPayBkCode, cPayeeBankNo);
            LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO") 
            iSqlRet = DBSelectToVar(cErrmsg, cChkAcctOrd, cSql);
            if (0 > iSqlRet)
            {
                LOG(LM_STD, Fmtmsg("��ѯTIPS���˱�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "��ѯTIPS���˱�ʧ��");
                return -1;
            }
            if (0 == iSqlRet)
            {
                LOG(LM_STD, Fmtmsg("������¼,����ǰ�ö�,δ��TIPS����,�ݲ�����."), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "TIPSδ���ˣ��ݲ�����");
                return -1;
            }
            LOG(LM_STD, Fmtmsg("������¼,����TIPS��ǰ�ö�,����δ����,���Ϻ��Ĳ��ʴ���."), "ERROR")
            COMP_SOFTSETXML("/tips_host/req/jydm", "dbzz");
            COMP_SOFTSETXML("/tips/xyxx", "�����ղ���");
            COMP_SOFTSETXML("/tips/jyzt", "4");
            return 1;
        }
        
        trim(cChkRlt);
        if (0 == memcmp(cChkRlt + 1, "2", 1))/* �����˽��Ϊ92-��TIPS����,ǰ�ö� */
        {
            LOG(LM_STD,Fmtmsg("������¼,����ǰ�ö�,TIPS������δ����,�轫ԭ��ˮ״̬����Ϊʧ�ܼ���."),"INFO");
            iIsFailed = 1;
        }
        else
        {
            LOG(LM_STD,Fmtmsg("TIPS���˽��[%c]", cChkRlt[1]),"INFO");
            fpub_SetMsg(lXmlhandle, 100001, "ϵͳ�����޷����ˣ���ȷ��");
            return -1;
        }
    }
    else /* ��TIPS���� ǰ�ö� */
    {
        if (0 == memcmp(cIsBatch, "Y", 1))
        {
            memset(cIniFile, 0x00, sizeof(cIniFile));
            snprintf(cIniFile, sizeof(cIniFile), "%s/etc/tips.ini", getenv("HOME"));
            memset(cBuf, 0x00, sizeof(cBuf));
            memset(cIsPldz, 0x00, sizeof(cIsPldz));
            if(ExGetCfgItem(cIniFile, "HXDZ", "PLDZ", cBuf,sizeof(cBuf))<0)
            {
                cBuf[0]='1';/* 1-�μ�(ȱʡ) */
            }
            pstrcopy(cIsPldz, cBuf, sizeof(cIsPldz));
    
            if (0 == memcmp(cIsPldz, "0", 1))/* �����������������,��ʱ�����ͺ���Ĩ�� */
            {
                LOG(LM_STD,Fmtmsg("������¼,����TIPS��,ǰ������Ĳ�����,ȱʡ��ƽ,���Ϻ���Ĩ�˴���."),"INFO");               
                COMP_SOFTSETXML("/tips_host/req/jydm", "dbmz");
                COMP_SOFTSETXML("/tips/xyxx", "������Ĩ��");
                COMP_SOFTSETXML("/tips/jyzt", "3");
                return 1;
            }
        }
        
        memset(cChkRlt, 0x00, sizeof(cChkRlt));
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "select dzjg from tips_dzbpdj where zwrq='%s' and zhqzlsh=%ld and dzlx='1' and (clzt='0' or clzt='1')"
                     , cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
        iSqlRet = DBSelectToVar(cErrmsg, cChkRlt, cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("��ѯ���˲�ƽ��ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "��ѯ���˲�ƽ��ϸ��ʧ��");
            return -1;
        }
        else if (0 == iSqlRet)
        {
            /* ��tips_checkresult����ȥ��ѯ�˹������Ƿ��Ѷ��� */
            memset(cChkState, 0x00, sizeof(cChkState));
            memset(cSql, 0x00, sizeof(cSql));
            sprintf(cSql, "select checkstate from tips_checkresult where checkdate='%s' and checksystem='00' and checkstate='0'", cChkDate);
            LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO") 
            iSqlRet = DBSelectToVar(cErrmsg, cChkState, cSql);
            if (0 > iSqlRet)
            {
                LOG(LM_STD, Fmtmsg("��ѯ���Ķ��˱�ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "��ѯ���Ķ��˱�ʧ��");
                return -1;
            }
            if (0 == iSqlRet)
            {
                LOG(LM_STD, Fmtmsg("������¼,����TIPS�٣�ǰ�ö�,δ����Ķ���,�ݲ�����."), "ERROR")
                fpub_SetMsg(lXmlhandle, 100001, "����δ���ˣ��ݲ�����");
                return -1;
            }
            LOG(LM_STD, Fmtmsg("������¼,����TIPSδ���ˣ�ǰ�á����Ķ�����,���Ϻ���Ĩ�˴���."), "ERROR")     
            COMP_SOFTSETXML("/tips_host/req/jydm", "dbmz");
            COMP_SOFTSETXML("/tips/xyxx", "������Ĩ��");
            COMP_SOFTSETXML("/tips/jyzt", "3");
            return 1;
        }
        
        trim(cChkRlt);
        if (0 == memcmp(cChkRlt, "2", 1))/* �����˽��Ϊ29-����Ķ���,ǰ�ö� */
        {
            LOG(LM_STD,Fmtmsg("������¼,����ǰ�ö�,TIPS������δ����,�轫ԭ��ˮ״̬����Ϊʧ�ܼ���."),"INFO");
            iIsFailed = 1;
        }
        else
        {
            LOG(LM_STD,Fmtmsg("���Ķ��˽��[%c]", cChkRlt[0]),"INFO");
            fpub_SetMsg(lXmlhandle, 100001, "ϵͳ�����޷����ˣ���ȷ��");
            return -1;
        }
    }
    
    if (1 == iIsFailed)
    {
        memset(cSql, 0x00, sizeof(cSql));
        sprintf(cSql, "update tips_dzbpdj set clzt='3' where zwrq='%s' and zhqzlsh=%ld"
                    , cTranDate, atol(cTranSeq));
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("���¶��˲�ƽ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "���¶��˲�ƽ��ʧ��");
            return -1;
        }
        memset(cSql, 0x00, sizeof(cSql));
        if (0 == memcmp(cIsBatch, "Y", 1))
        {
            sprintf(cSql, "update tips_ssplksfmx set kzbz='11'||substr(kzbz,3,6),czbd='8' where zwrq='%s' and plmxxh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        else
        {
            sprintf(cSql, "update tips_drls set dzbz='11',jyzt='1' where zwrq='%s' and zhqzlsh=%ld"
                        , cTranDate, atol(cTranSeq));
        }
        LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO")
        iSqlRet = DCIExecuteDirect(cSql);
        if (0 > iSqlRet)
        {
            LOG(LM_STD, Fmtmsg("������ˮ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
            fpub_SetMsg(lXmlhandle, 100001, "������ˮ��ʧ��");
            return -1;
        }
    }
    
    return 0;
}
