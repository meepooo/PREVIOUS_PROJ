/********************************************************************
  ��Ȩ����:�������ӹɷ����޹�˾
  ��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
  ��    ��:V3.0.00
  ����ϵͳ:AIX5.3
  �ļ�����:SYW_TIPS_HXDZ_BATCH_DRC.ec
  �ļ�����:TIPS���ʽ��������
  �� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
  �� �� Ա:�����
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
  
#include  "../../eh/tips_ssplksfmx.h"
#include  "../../eh/tips_pljydj.h"
#include  "../../eh/tips_dzbpdj.h"

/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_HXDZ_PL
  �������: TIPS���Ķ�����������

  �������: 
  TIPS���Ķ��˶�������˰��ϸ�Ĵ���
  �������: 
  ��� ��������     ��Դ���       ȱʡֵ   �Ƿ�ɿ�  ����˵��

  ������״̬: 
  ���״̬��         ���˵��
  0                  ������ϸ��ӵ���ƽ��ϸ�ǼǱ�ɹ�
  -1���������������� ������ϸ����ʧ��

  ��Ҫ�������:
  ����              ����
  ������˰��ϸ��    tips_ssplksfmx
  �������׵ǼǱ�    tips_pljydj
  ���˲�ƽ�ǼǱ�    tips_dzbpdj

  �� Ŀ ��: TIPSר��ǰ�ò�Ʒ��
  �� �� Ա: �����
  ��������: 2017��06��16��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_HXDZ_PL(HXMLTREE lXmlhandle)
{
    int iParas;
    int iSqlRet = 0;
    int iRet = 0;        /* �Ӻ����ķ��ؽ�� */
    char cCountNum[12+1];   /* ����û��ȡ�ؽ�����������ۿ�ɹ��ļ�¼���� */
    int iCountNum = 0;
    
    char cSql[1024+1];   /* SQL��� */
    char cDzrq[8+1];     /* �������� */
    char cPljylsh[8+1];   /* ����������ˮ�� */
    char cTmp[128+1];
    char cErrmsg[256+1];
    

    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_HXDZ_PL...����ʼ"), "INFO") 
    
    COMP_PARACOUNTCHK(2);
    
    memset(cTmp, 0x00, sizeof(cTmp)); 
    memset(cDzrq, 0x00, sizeof(cDzrq));   
    COMP_GETPARSEPARAS(1, cTmp, "��������");
    pstrcopy(cDzrq, cTmp, sizeof(cDzrq)); 
    LOG(LM_DEBUG, Fmtmsg("��������[%s]", cDzrq), "INFO") 
    
    memset(cTmp, 0x00, sizeof(cTmp)); 
    memset(cPljylsh, 0x00, sizeof(cPljylsh));   
    COMP_GETPARSEPARAS(2, cTmp, "����������ˮ��");
    pstrcopy(cPljylsh, cTmp, sizeof(cPljylsh)); 
    LOG(LM_DEBUG, Fmtmsg("����������ˮ��[%s]", cPljylsh), "INFO") 
    
    memset(cSql, 0x00, sizeof(cSql)); 
    memset(cErrmsg, 0x00, sizeof(cErrmsg));   
    sprintf(cSql, "select count(*) from tips_ssplksfmx where zwrq='%s' and pljylsh='%s' and czbd='7'", cDzrq, cPljylsh);
    LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO");
    iSqlRet = DBSelectToVarChar(cErrmsg, cCountNum, cSql);
   /* iSqlRet = DCIExecuteDirect(cSql); */
    if (0 > iSqlRet)
    	{
    		LOG(LM_STD, Fmtmsg("��ѯ������˰����ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, 100001, "��ѯ������˰����ϸ��ʧ��");
        return COMPRET_FAIL;
    	}
    else 
    	{
    		iCountNum = atoi(cCountNum);
    		if (0 == iCountNum)
    		{
    			LOG(LM_STD, Fmtmsg("������û�пۿ�ɹ�����ϸ��ȫ��ȱʡǰ������Ķ�ƽ"), "INFO")
        	memset(cSql, 0x00, sizeof(cSql));
    			sprintf(cSql, "update tips_pljydj set czbd='7',wcbz='2',xyxx='���к���Ķ��˲�ȡ�ؽ����������ִǿ����7' where zwrq='%s' and pljylsh=%s", cDzrq, cPljylsh);
    			LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO");
    			iSqlRet = DCIExecuteDirect(cSql);
    			if (iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
						fpub_SetCompStatus(lXmlhandle, -1);
        		fpub_SetMsg(lXmlhandle, 100001, "�����������׵ǼǱ���ɱ�־ʧ��");
						LOG(LM_STD,Fmtmsg("[update...sql][%s]", cSql),"ERROR");
						return -1;
					}	
					LOG(LM_STD, Fmtmsg("�����������׵ǼǱ�,��ɱ�־�ɹ�"), "INFO")
    		}
   		 else
    		{
    			LOG(LM_STD, Fmtmsg("�����δ��ڿۿ�ɹ�����ϸ��ȫ���������Ķദ��"), "INFO")
    			iRet = djdzbpdjb(lXmlhandle, cDzrq, cPljylsh, iCountNum);
    			if (0 != iRet)
    				{
    					LOG(LM_STD, Fmtmsg("�ǼǶ��˲�ƽ��ϸ��ʧ��"), "ERROR")
        			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        			fpub_SetMsg(lXmlhandle, 100001, "�ǼǶ��˲�ƽ��ϸ��ʧ��");
        			return COMPRET_FAIL;
    				}
    		}
    	}
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
       
}


int djdzbpdjb(HXMLTREE lXmlhandle, char* cDzrq, char* cPljylsh, int iCountNum) 
{
    int iSqlRet = 0;
    int iFlag = 0;
	  char cSql[1024+1];   /* SQL��� */
    char cTmp[128+1];
    char cErrmsg[256+1];	
    

    SDB_TIPS_SSPLKSFMX stPlksfmx;  //SD_TIPS_SSPLKSFMX
    SDB_TIPS_DZBPDJ stDzbpdj;    //SD_TIPS_DZBPDJ
    int rows = 1;
    for (rows=1; rows<=iCountNum; ++rows)
    {
    	memset(cSql, 0x00, sizeof(cSql));
    	memset(&stPlksfmx, 0x00, sizeof(stPlksfmx));
    	memset(&stDzbpdj, 0x00, sizeof(stDzbpdj));
    	memset(cErrmsg, 0x00, sizeof(cErrmsg));
    	sprintf(cSql, "select * from (select ta.*,rownumber()over(order by ta.plmxxh asc) as rownum from tips_ssplksfmx as ta where ta.zwrq='%s' and ta.pljylsh='%s' and ta.czbd='7') as a where a.rownum=%d"
                , cDzrq, cPljylsh, rows);
    	LOG(LM_DEBUG, Fmtmsg("[select...sql][%s]", cSql), "INFO")
    	iSqlRet = prv_SelMulToStruct(&cSql, SD_TIPS_SSPLKSFMX, NUMELE(SD_TIPS_SSPLKSFMX), &stPlksfmx);
    	if (0 > iSqlRet)
    	{
        LOG(LM_STD, Fmtmsg("��ѯ������˰����ϸ��ʧ��, sqlerr[%s], iSqlRet[%d]", DCILastError() ,iSqlRet), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "��ѯ������˰����ϸ��ʧ��");
        return -1;
    	}
    	else if(0 == iSqlRet)
    	{
        LOG(LM_STD, Fmtmsg("������˰����ϸ������"), "ERROR")
        fpub_SetCompStatus(lXmlhandle, -1);
        fpub_SetMsg(lXmlhandle, 100001, "������˰����ϸ�����ڣ���ȷ��");
        return -1;
    	}
    	else
    	{
    		/*����Ѳ�ѯ�Ľ���������˲�ƽ�Ľṹ�壬Ȼ���ٲ�����˲�ƽ��ϸ��*/
    		trim(stPlksfmx.payeebankno);
    		trim(stPlksfmx.payacct);
    		pstrcopy(stDzbpdj.zwrq, stPlksfmx.zwrq, sizeof(stDzbpdj.zwrq));
    		stDzbpdj.zhqzlsh = stPlksfmx.plmxxh;  /*������ϸ���*/
    		pstrcopy(stDzbpdj.workdate, stPlksfmx.workdate, sizeof(stDzbpdj.workdate));
    		pstrcopy(stDzbpdj.dqdh, stPlksfmx.dqdh, sizeof(stDzbpdj.dqdh));
				pstrcopy(stDzbpdj.jgdh, stPlksfmx.jgdh, sizeof(stDzbpdj.jgdh));
				pstrcopy(stDzbpdj.jygy, stPlksfmx.jygy, sizeof(stDzbpdj.jygy));
				pstrcopy(stDzbpdj.zddh, stPlksfmx.zddh, sizeof(stDzbpdj.zddh));
				stDzbpdj.dzlx[0] = '1';
				pstrcopy(stDzbpdj.zjlsh, stPlksfmx.zjlsh, sizeof(stDzbpdj.zjlsh));
				pstrcopy(stDzbpdj.taxorgcode, stPlksfmx.taxorgcode, sizeof(stDzbpdj.taxorgcode));
				pstrcopy(stDzbpdj.entrustdate, stPlksfmx.entrustdate, sizeof(stDzbpdj.entrustdate));
				pstrcopy(stDzbpdj.trano, stPlksfmx.trano, sizeof(stDzbpdj.trano));
				pstrcopy(stDzbpdj.chkdate, stPlksfmx.chkdate, sizeof(stDzbpdj.chkdate));  /*��ʱ����ȡ*/
				pstrcopy(stDzbpdj.chkacctord, stPlksfmx.chkacctord, sizeof(stDzbpdj.chkacctord));/*��ʱ����ȡ*/
				pstrcopy(stDzbpdj.payeebankno, stPlksfmx.payeebankno, sizeof(stDzbpdj.payeebankno));
				pstrcopy(stDzbpdj.paybkcode, stPlksfmx.paybkcode, sizeof(stDzbpdj.paybkcode));
				/*stDzbpdj.czyh ����Ա�� Ϊ��
				  stDzbpdj.jyqd �������� Ϊ��*/
				pstrcopy(stDzbpdj.jyrq, stPlksfmx.zwrq, sizeof(stDzbpdj.jyrq));
				pstrcopy(stDzbpdj.jysj, stPlksfmx.zjsj, sizeof(stDzbpdj.jysj));
				pstrcopy(stDzbpdj.jymc, "3102", sizeof(stDzbpdj.jymc));
				pstrcopy(stDzbpdj.khmc, stPlksfmx.handorgname, sizeof(stDzbpdj.khmc));
				pstrcopy(stDzbpdj.jyzh, stPlksfmx.payacct, sizeof(stDzbpdj.jyzh));
				/*stDzbpdj.zhzl �ʻ����� Ϊ�� */
				pstrcopy(stDzbpdj.dfzh, stPlksfmx.dfzh, sizeof(stDzbpdj.dfzh));
				pstrcopy(stDzbpdj.bzh, "01", sizeof(stDzbpdj.bzh));
				stDzbpdj.jyje = stPlksfmx.jyje;
				pstrcopy(stDzbpdj.reason_info, "ǰ��<->����;����������", sizeof(stDzbpdj.reason_info));
				pstrcopy(stDzbpdj.dzjg, "39", sizeof(stDzbpdj.dzjg));
				stDzbpdj.clzt[0]='0';
				stDzbpdj.jdbz[0]='1';
				pstrcopy(stDzbpdj.clrq, GetSysDate(), sizeof(stDzbpdj.clrq));
				pstrcopy(stDzbpdj.clsj, GetSysTime(), sizeof(stDzbpdj.clsj));
				stDzbpdj.cllsh = 0;
				/*stDzbpdj.clzjlsh ����������ˮ�� Ϊ�� */
				pstrcopy(stDzbpdj.clxx, "δ����", sizeof(stDzbpdj.clxx));
				pstrcopy(stDzbpdj.kzbz, stPlksfmx.kzbz, sizeof(stDzbpdj.kzbz));
				pstrcopy(stDzbpdj.byzd, stPlksfmx.packno, sizeof(stDzbpdj.byzd));
				
				iSqlRet = DBInsert("tips_dzbpdj", SD_TIPS_DZBPDJ, NUMELE(SD_TIPS_DZBPDJ), &stDzbpdj, cErrmsg);
				if (iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
						fpub_SetCompStatus(lXmlhandle, -1);
        		fpub_SetMsg(lXmlhandle, 100001, "������ʲ�ƽ��ϸ�ǼǱ�ʧ��");
						LOG(LM_STD,Fmtmsg("������ʵǼǱ�ʧ��"),"ERROR");
						iFlag = -1;
						break;
					}	
    	}
    }
    LOG(LM_STD, Fmtmsg("�ǼǶ��˲�ƽ��ϸ��ɹ�"), "INFO")
    if (0 == iFlag)
    {
    	/* ��������������׵ǼǱ�,��ɱ�־Ϊ�ɹ���������˰����ϸ�����չ��־ */
    	memset(cSql, 0x00, sizeof(cSql));
    	sprintf(cSql, "update tips_pljydj set czbd='7',wcbz='2',xyxx='���к���Ķ��˲�ȡ�ؽ����������ִǿ����7' where zwrq='%s' and pljylsh=%s", cDzrq, cPljylsh);
    	LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO");
    	iSqlRet = DCIExecuteDirect(cSql);
    	if (iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
						fpub_SetCompStatus(lXmlhandle, -1);
        		fpub_SetMsg(lXmlhandle, 100001, "�����������׵ǼǱ���ɱ�־����������ʧ��");
						LOG(LM_STD,Fmtmsg("[update...sql][%s]", cSql),"ERROR");
						return -1;
					}	
			LOG(LM_STD, Fmtmsg("�����������׵ǼǱ�,��ɱ�־Ϊ�ɹ�����������Ϊ7"), "INFO")
			memset(cSql, 0x00, sizeof(cSql));		
			sprintf(cSql, "update tips_ssplksfmx set kzbz='39'||substr(kzbz,3,6) where zwrq='%s' and pljylsh='%s' and czbd='7'", cDzrq, cPljylsh);
    	LOG(LM_DEBUG, Fmtmsg("[update...sql][%s]", cSql), "INFO");
    	iSqlRet = DCIExecuteDirect(cSql);
    	if (iSqlRet < 0)
					{
						LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s],iRet[%d]",DCILastError() ,iSqlRet),"ERROR")
						fpub_SetCompStatus(lXmlhandle, -1);
        		fpub_SetMsg(lXmlhandle, 100001, "����������˰����ϸ���־ʧ��");
						LOG(LM_STD,Fmtmsg("[update...sql][%s]", cSql),"ERROR");
						return -1;
					}
			LOG(LM_STD, Fmtmsg("������˰����ϸ�����չ��־�ɹ�"), "INFO")			
    }
    return 0;
}