/********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺ�Ӧ��ƽ̨��GAPS����Ŀ
��    ��:V4.1.00
����ϵͳ:AIX/Linux/HP-UX
�ļ�����:WDL_DEL.c
�ļ�����:΢����
�� Ŀ ��:
�� �� Ա:
��������:
��    ��:
�޸�����:
*********************************************************************/

#include <string.h>
#include <stdlib.h>
#include "gaps_head.h"
#include "../incl/wzj.eh"

/********************************************************************
���ע�����ƣ�WZYH_TICKETSORT
����������ƣ�WZYH_TICKETSORT
����������壺
����������ܣ��Ի�ȡƱ�ݷ���ʱ�Բ���������ɴ�
������ò�����
    ���    ��������    ��Դ���    ȱʡֵ    �Ƿ�ɿ�    ����˵��
������״̬��
    ״̬    ���˵��
�� Ŀ �飺
�� �� Ա��txbdir
�������ڣ�20171108
�޸����ڣ�
*********************************************************************/
IRESULT WZYH_TICKETSORT(HXMLTREE lXmlhandle)
{
	int i , j , iRet;
	char ParaSort[6][128] , ParaField[6][128] , sBuf[256]  , sRetVal[1024] , sSPlit[16];
	
	memset(ParaSort , 0x00 , 6*128);
	memset(ParaField , 0x00 , 6*128);
	fpub_InitSoComp(lXmlhandle);
	
	#ifdef DEBUG
		LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
	#endif
	
	/* ��ȡappid */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/wzyh/appid", sBuf)
	trim(sBuf);
	if (0 == strlen(sBuf))
	{
		LOG(LM_STD, Fmtmsg("APPID����Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "APPID����Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memcpy(ParaSort[0],sBuf,strlen(sBuf));
	memcpy(ParaField[0],sBuf,strlen(sBuf));
	
	/* ��ȡuserid */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/ggbody_req/user_id", sBuf)
	trim(sBuf);
	if (0 == strlen(sBuf))
	{
		LOG(LM_STD, Fmtmsg("USERID����Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "APPID����Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memcpy(ParaSort[1],sBuf,strlen(sBuf));
	memcpy(ParaField[1],sBuf,strlen(sBuf));
	
	/* ��ȡaccess_token */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/wzyh/tokenid", sBuf)
	trim(sBuf);	
	if (0 == strlen(sBuf))
	{
		LOG(LM_STD, Fmtmsg("APPID����Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "APPID����Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memcpy(ParaSort[2],sBuf,strlen(sBuf));
	memcpy(ParaField[2],sBuf,strlen(sBuf));
	
		/* ��ȡtype */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/ggbody_req/type", sBuf)
	trim(sBuf);
	if (0 == strlen(sBuf))
	{
		LOG(LM_STD, Fmtmsg("type����Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "APPID����Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memcpy(ParaSort[3],sBuf,strlen(sBuf));
	memcpy(ParaField[3],sBuf,strlen(sBuf));
	
	memcpy(ParaSort[4],"1.0.0" , 5);		/* version */
	memcpy(ParaField[4],sBuf,sizeof(sBuf));
	LOG(LM_STD, Fmtmsg("3appid[%s]" , ParaSort[0]), "DEBUG")
	
	memset(sBuf , 0x00 , sizeof(sBuf));
	sprintf(sBuf , "%d" , time(NULL));
	memcpy(ParaSort[5] , sBuf , strlen(sBuf));		/*  nonceStr */
	memcpy(ParaField[5] , sBuf , strlen(sBuf));	
	LOG(LM_STD, Fmtmsg("3appid[%s],[%s]" , ParaSort[0] , ParaSort[5]), "DEBUG")
	
	/* ���� */
	for (i = 0 ; i < 5 ; i++)
	{
		for (j = i+1 ; j < 6 ; j++)
		{
			if(strcmp(ParaSort[i] , ParaSort[j]) > 0)
			{
				memset(sBuf , 0x00 , sizeof(sBuf));
				memcpy(sBuf , ParaSort[i] , strlen(ParaSort[i]));
				memset(ParaSort[i] , 0x00 , sizeof(ParaSort[i]));
				memcpy(ParaSort[i] , ParaSort[j] , strlen(ParaSort[j]));
				memset(ParaSort[j] , 0x00 , sizeof(ParaSort[j]));
				memcpy(ParaSort[j] , sBuf , strlen(sBuf));
			}
		}
	}
	
	/* ��װ�ַ��� */
	memset(sSPlit , 0x00 , sizeof(sSPlit));
	memcpy(sSPlit , "&" , 1);
	memset(sRetVal , 0x00 , sizeof(sRetVal));
	for (i = 0 ; i < 6 ; i++)
	{
		if(strcmp(ParaSort[i] , "1.0.0") == 0)
		{
			strcat(sRetVal , "version=1.0.0");
			strcat(sRetVal , sSPlit);
		}
		else if(strcmp(ParaSort[i] , ParaField[0]) == 0)
		{
			strcat(sRetVal , "app_id=");
			strcat(sRetVal , ParaSort[i]);
			trim(sRetVal);
			strcat(sRetVal , sSPlit);
		}
		else if(strcmp(ParaSort[i] , ParaField[1]) == 0)
		{
			strcat(sRetVal , "user_id=");
			strcat(sRetVal , ParaSort[i]);
			trim(sRetVal);
			strcat(sRetVal , sSPlit);
		}
		else if(strcmp(ParaSort[i] , ParaField[2]) == 0)
		{
			strcat(sRetVal , "tokenid=");
			strcat(sRetVal , ParaSort[i]);
			trim(sRetVal);
			strcat(sRetVal , sSPlit);
		}
		else if(strcmp(ParaSort[i] , ParaField[3]) == 0)
		{
			strcat(sRetVal , "type=");
			strcat(sRetVal , ParaSort[i]);
			trim(sRetVal);
			strcat(sRetVal , sSPlit);
		}
		else if(strcmp(ParaSort[i] , ParaField[5]) == 0)
		{
			strcat(sRetVal , "nonceStr=");
			strcat(sRetVal , ParaSort[i]);
			trim(sRetVal);
			strcat(sRetVal , sSPlit);
		}
	}
	sRetVal[strlen(sRetVal)-1] = '\0';
	
	COMP_SOFTSETXML("/wzyh/ggbody_req/data", sRetVal)
	LOG(LM_STD, Fmtmsg("RetVal[%s]" , sRetVal), "DEBUG")

#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "")
#endif
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
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
	//LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"DEBUG");
	
	cur = DCIDeclareCursor( sSql, DCI_DEFAULT);
	if (cur == INVALID_CURSOR)
	{
		LOG(LM_STD, Fmtmsg("�α궨��ʧ��[%s]-[%s]",  DCILastError(), sSql), "ERROR");
		return -1;
	}
	//LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"DEBUG");
	
	if(DCIExecute(cur) == -1)
	{
		LOG(LM_STD, Fmtmsg("���ݿ����ʧ��[%s]", DCILastError() ), "ERROR");
		DCIFreeCursor(cur);
		return -1;
	}
	//LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"DEBUG");
	
	int rs = 0;
	if( 0 > ( rs = DBFetch( cur, desc_arr, desc_num, pdes, szErrMsg ) ) )
	{
		LOG(LM_STD, Fmtmsg("�α��ȡ��¼����[%s]",  szErrMsg ), "ERROR");
		DCIFreeCursor(cur);
		return -1;
	}
		
	DCIFreeCursor(cur);
	return rs;
}

/********************************************************************
���ע�����ƣ�WZYH_DZERRMX
����������ƣ�WZYH_DZERRMX
����������壺
����������ܣ����˲����ϸ��ѯ
������ò�����
    ���    ��������    ��Դ���    ȱʡֵ    �Ƿ�ɿ�    ����˵��
������״̬��
    ״̬    ���˵��
�� Ŀ �飺
�� �� Ա��txbdir
�������ڣ�20171108
�޸����ڣ�
*********************************************************************/
IRESULT WZYH_DZERRMX(HXMLTREE lXmlhandle)
{
	char qsrq[8+1]; /*��ʼʱ��*/
	char zzrq[8+1];/*��ֹʱ��*/
	char tran_type[4+1]; /*��������*/
	double amount;/*���׽��*/
	char hxrq[8+1]; /*��������*/
	char hxls[32+1]; /*������ˮ��*/
	char qzrq[8+1]; /*ǰ������*/
	char qzls[20]; /*ǰ����ˮ��*/
	char jyrq[8+1]; /*΢�ڽ�������*/
	char business_id[32+1]; /*΢�ڽ�����ˮ*/
	char accno[34+1]; /*����*/
	char accname[256]; /*�ͻ�����*/
	char errflag[2+1]; /*�������*/
	char tzbz[2+1]; /*���˱�־*/	
	char sSql[1024] , ErrMsg[1024];
	CURSOR cur;
	long lTotalCount=0;
	long lPageCount=0;
	char sBuf[256],qishibis[21],chxunbis[21],buff[1024],cTmp[256];
	long lQueryNum = 0;
	long lBegNum = 0; 
	long lEndNum = 0;
	int iCountNum = 0 , iRet , queryoffset = 0;
	
	fpub_InitSoComp(lXmlhandle);
	/* ��ȡ��ʼʱ�� */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/qsrq", sBuf)
	trim(sBuf);
	memset(qsrq,0x00,sizeof(qsrq));
	memcpy(qsrq,sBuf,sizeof(qsrq)-1);
	if (0 == strlen(qsrq))
	{
		LOG(LM_STD, Fmtmsg("��ʼʱ�䲻��Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ʼʱ�䲻��Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	/* ��ȡ��ֹʱ�� */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/zzrq", sBuf)
	trim(sBuf);
	memset(zzrq,0x00,sizeof(zzrq));
	memcpy(zzrq,sBuf,sizeof(zzrq)-1);
	if (0 == strlen(zzrq))
	{
		LOG(LM_STD, Fmtmsg("��ֹʱ�䲻��Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ֹʱ�䲻��Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	/* ��ȡ��ʼ���� */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/qishibis", sBuf)
	trim(sBuf);
	memset(qishibis,0x00,sizeof(qishibis));
	memcpy(qishibis,sBuf,sizeof(qishibis)-1);
	if (0 == strlen(qishibis))
	{
		LOG(LM_STD, Fmtmsg("��ʼ��������Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ʼ��������Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lBegNum = atol(qishibis);
	if (0 >= lBegNum)
	{
		LOG(LM_STD, Fmtmsg("�Ƿ���ʼ����"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�Ƿ���ʼ����");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}

	/* ��ȡ��ѯ����*/
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/chxunbis", sBuf)
	trim(sBuf);
	memset(chxunbis,0x00,sizeof(chxunbis));
	memcpy(chxunbis,sBuf,sizeof(chxunbis)-1);
	if (0 == strlen(chxunbis))
	{
		LOG(LM_STD, Fmtmsg("��ѯ��������Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ѯ��������Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lQueryNum = atoi(chxunbis);
	if (0 >= lQueryNum)
	{
		LOG(LM_STD, Fmtmsg("�Ƿ���ѯ����"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�Ƿ���ѯ����");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	lEndNum = lBegNum + lQueryNum;
	if (MAXPAGECOUNT < lQueryNum)
	{
		lQueryNum = MAXPAGECOUNT;
	}	
	
	/* ���ѯWHERE */
	memset(buff,0x00,sizeof(buff));
	sprintf(buff," FROM YW_WZYH_ERRMX WHERE jyrq>='%s' and jyrq<='%s' ",qsrq,zzrq);
		
	/**��ѯ�ܱ���**/
	memset(sSql,0x00,sizeof(sSql));
	snprintf(sSql,sizeof(sSql),"select count(jyrq) %s", buff);
	memset(cTmp , 0x00 , sizeof(cTmp));
	LOG(LM_STD, Fmtmsg("�ܱ���SQL[%s]", sSql), "DEBUG")
	iRet = DBSelectToVar(ErrMsg, (void *)cTmp, sSql);
	if( iRet < 0)
	{
		LOG(LM_STD, Fmtmsg("��ѯ���ݿ�ʧ��[%d]", iRet), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ѯ���ݿ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lTotalCount = atol(cTmp);

    /**��ǰҳ����**/
    memset(sSql,0x00,sizeof(sSql));
	memset(cTmp , 0x00 , sizeof(cTmp));
    snprintf(sSql,sizeof(sSql),"select count(jyrq) from (select t.jyrq,rownum rn from (select jyrq %s ) t WHERE rownum<%d) WHERE rn>=%d", buff, lEndNum, lBegNum);
    LOG(LM_STD, Fmtmsg("��ǰҳ����SQL[%s]", sSql), "DEBUG")
    iRet = DBSelectToVar(ErrMsg, (void *)cTmp, sSql);
	if( iRet < 0)
	{
		LOG(LM_STD, Fmtmsg("��ѯ���ݿ�ʧ��[%d]", iRet), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ѯ���ݿ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lPageCount = atol(cTmp);

	if (0 == lTotalCount)
	{
		LOG(LM_STD, Fmtmsg("û�з��������Ķ��˲����Ϣ"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "û�з��������Ķ��˲����Ϣ");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	if (lTotalCount < lBegNum)
	{
		LOG(LM_STD, Fmtmsg("û�з��������Ķ��˲����Ϣ"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "û�з��������Ķ��˲����Ϣ");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	if (0 == lPageCount)
	{
		LOG(LM_STD, Fmtmsg("û�з��������Ķ��˲����Ϣ"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "û�з��������Ķ��˲����Ϣ");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	if (lTotalCount > lEndNum)
	{
		COMP_SOFTSETXML("/gmjr/resp/output/querymark", "01")
	}
	else
	{
		COMP_SOFTSETXML("/gmjr/resp/output/querymark", "02")
	}
	memset(cTmp, 0x00, sizeof(cTmp));
	sprintf(cTmp, "%d", lPageCount);
	COMP_SOFTSETXML("/gmjr/resp/output/mxibs", cTmp)

    /** ��ѯ��ϸ **/
    memset(sSql,0x00,sizeof(sSql));
     snprintf(sSql,sizeof(sSql),"select tran_type,amount,hxrq,hxls,qzrq,qzls,jyrq,business_id,accno,accname,errflag,tzbz from ("
                              " select t.tran_type,t.amount,t.hxrq,t.hxls,t.qzrq,t.qzls,t.jyrq,t.business_id,t.accno,t.accname,t.errflag,t.tzbz,rownum rn from ("
                  " select tran_type,amount,hxrq,hxls,qzrq,qzls,jyrq,business_id,accno,accname,errflag,tzbz  %s) t where rownum<%ld) where rn>=%ld",buff,lEndNum, lBegNum);
    LOG(LM_STD, Fmtmsg("��ϸSQL[%s]", sSql), "DEBUG")
	
	if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

	while(1)
	{
       if (iCountNum > lPageCount)
        {
            LOG(LM_STD, Fmtmsg("��ѯ����[%d][%ld]", iCountNum, lPageCount), "DEBUG")
            break;
        }      
          
        memset(tran_type, 0x00, sizeof(tran_type));
        amount=0.00;
        memset(hxrq, 0x00, sizeof(hxrq));
        memset(hxls, 0x00, sizeof(hxls));
        memset(qzrq, 0x00, sizeof(qzrq));
        memset(qzls, 0x00, sizeof(qzls));
        memset(jyrq, 0x00, sizeof(jyrq));
		
        memset(business_id, 0x00, sizeof(business_id));
        memset(accno, 0x00, sizeof(accno));
        memset(accname, 0x00, sizeof(accname));
        memset(errflag, 0x00, sizeof(errflag));
        memset(tzbz, 0x00, sizeof(tzbz));
		 memset(business_id, 0x00, sizeof(business_id));
        memset(accno, 0x00, sizeof(accno));
        memset(accname, 0x00, sizeof(accname));
        memset(errflag, 0x00, sizeof(errflag));
        memset(tzbz, 0x00, sizeof(tzbz));
		memset(errflag, 0x00, sizeof(errflag));
        memset(tzbz, 0x00, sizeof(tzbz));
		
		sprintf(tran_type , "%s" , DCIFieldAsString( cur, 0));
		amount = atof(DCIFieldAsString( cur, 1));
		sprintf(hxrq , "%s" , DCIFieldAsString( cur, 2));
		sprintf(hxls , "%s" , DCIFieldAsString( cur, 3));
		sprintf(qzrq , "%s" , DCIFieldAsString( cur, 4));
		sprintf(qzls , "%s" , DCIFieldAsString( cur, 5));
		sprintf(jyrq , "%s" , DCIFieldAsString( cur, 6));
		sprintf(business_id , "%s" , DCIFieldAsString( cur, 7));
		sprintf(accno , "%s" , DCIFieldAsString( cur, 8));
		sprintf(accname , "%s" , DCIFieldAsString( cur, 9));
		sprintf(errflag , "%s" , DCIFieldAsString( cur, 10));
		sprintf(tzbz , "%s" , DCIFieldAsString( cur, 11));
		
   
        iRet = DCIFetch2(cur, DCI_FETCH_NEXT, queryoffset);
        if (iRet == -100 || iRet == -1403)
        {
            LOG(LM_STD, Fmtmsg("��ѯ����[%d][%ld]", iCountNum), "DEBUG")
            break;
        }
        else if (iRet < 0)
        {
            LOG(LM_STD, Fmtmsg("��ѯ���˲����Ϣʧ��[%d]", iRet), "DEBUG")
            fpub_SetMsg(lXmlhandle, 10001, "��ѯ���˲����Ϣʧ��");
            fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
            DCIFreeCursor(cur);
            return COMPSTATUS_FAIL;
        }
        iCountNum++;
        /* �������� */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/trantype", iCountNum);
        COMP_SOFTSETXML(cTmp, tran_type)
        /* ���׽�� */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/amt", iCountNum);
        memset(sBuf,0x00,sizeof(sBuf));
        sprintf(sBuf, "%.2f", amount);
        COMP_SOFTSETXML(cTmp, sBuf)
         /* �������� */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/corebkdt", iCountNum);
        COMP_SOFTSETXML(cTmp, hxrq)
        /* ������ˮ�� */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/corebknum", iCountNum);
        COMP_SOFTSETXML(cTmp, hxls)
         /* ǰ������ */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/qzrq", iCountNum);
        COMP_SOFTSETXML(cTmp, qzrq)
        /* ǰ����ˮ�� */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/pltnum", iCountNum);
        COMP_SOFTSETXML(cTmp, qzls)
         /* ΢�ڽ������� */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/wzrq", iCountNum);
        COMP_SOFTSETXML(cTmp, jyrq)
           /* ΢�ڽ�����ˮ */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/wzls", iCountNum);
        COMP_SOFTSETXML(cTmp, business_id)
           /* �ͻ����� */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/accname", iCountNum);
        COMP_SOFTSETXML(cTmp, accname)
           /* ���� */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/accno", iCountNum);
        COMP_SOFTSETXML(cTmp, accno)
           /* ������� */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/errflag", iCountNum);
        COMP_SOFTSETXML(cTmp, errflag)
           /* ���˱�־ */
        memset(cTmp, 0x00, sizeof(cTmp));
        sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/tzbz", iCountNum);
        COMP_SOFTSETXML(cTmp, tzbz)
        
    }
    DCIFreeCursor(cur);

#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "")
#endif
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/********************************************************************
���ע�����ƣ�WZYH_INQDZ
����������ƣ�WZYH_INQDZ
����������壺
����������ܣ����˽����ѯ
������ò�����
    ���    ��������    ��Դ���    ȱʡֵ    �Ƿ�ɿ�    ����˵��
������״̬��
    ״̬    ���˵��
�� Ŀ �飺
�� �� Ա��txbdir
�������ڣ�20171107
�޸����ڣ�
*********************************************************************/
IRESULT WZYH_INQDZ(HXMLTREE lXmlhandle)
{
	char qsrq[8+1]; /*��ʼʱ��*/
	char zzrq[8+1];/*��ֹʱ��*/
	char quetype[1+1];/*��ѯ����*/
	char jyrq[8+1]; /*��������*/
	char dz_bz[1+1]; /*���˱�־*/
	char product_buy_num[12+1]; /*��Ʋ�Ʒ�깺�ܱ���*/
	double product_buy_amount;/*�깺�ʽ��ܶ�*/
	char product_back_num[12+1]; /*��Ʋ�Ʒ����ܱ���*/
	double product_back_amount;/*����ʽ��ܶ�*/
	double zc_amount;/*�����ܶ�*/
	char sSql[1024] , ErrMsg[256] , sTmp[1024];
	long lTotalCount=0;
	long lPageCount=0;
	char sBuf[256],qishibis[21],chxunbis[21],buff[1024],cTmp[256];
	long lQueryNum = 0;
	long lBegNum = 0; 
	long lEndNum = 0;
	int iCountNum = 0 , iRet , queryoffset = 0;
	CURSOR cur;
	
	fpub_InitSoComp(lXmlhandle);
	/* ��ȡ��ʼʱ�� */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/qsrq", sBuf)
	trim(sBuf);
	memset(qsrq,0x00,sizeof(qsrq));
	memcpy(qsrq,sBuf,sizeof(qsrq)-1);
	if (0 == strlen(qsrq))
	{
		LOG(LM_STD, Fmtmsg("��ʼʱ�䲻��Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ʼʱ�䲻��Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	/* ��ȡ��ֹʱ�� */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/zzrq", sBuf)
	trim(sBuf);
	memset(zzrq,0x00,sizeof(zzrq));
	memcpy(zzrq,sBuf,sizeof(zzrq)-1);
	if (0 == strlen(zzrq))
	{
		LOG(LM_STD, Fmtmsg("��ֹʱ�䲻��Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ֹʱ�䲻��Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	/* ��ȡ��ѯ���� */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/quetype", sBuf)
	trim(sBuf);
	memset(quetype,0x00,sizeof(quetype));
	memcpy(quetype,sBuf,sizeof(quetype)-1);
	if (0 == strlen(quetype))
	{
		LOG(LM_STD, Fmtmsg("��ѯ��������Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ѯ��������Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	/* ��ȡ��ʼ���� */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/qishibis", sBuf)
	trim(sBuf);
	memset(qishibis,0x00,sizeof(qishibis));
	memcpy(qishibis,sBuf,sizeof(qishibis)-1);
	if (0 == strlen(qishibis))
	{
		LOG(LM_STD, Fmtmsg("��ʼ��������Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ʼ��������Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lBegNum = atol(qishibis);
	if (0 >= lBegNum)
	{
		LOG(LM_STD, Fmtmsg("�Ƿ���ʼ����"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�Ƿ���ʼ����");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}

	/* ��ȡ��ѯ����*/
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/gmjr/req/input/chxunbis", sBuf)
	trim(sBuf);
	memset(chxunbis,0x00,sizeof(chxunbis));
	memcpy(chxunbis,sBuf,sizeof(chxunbis)-1);
	if (0 == strlen(chxunbis))
	{
		LOG(LM_STD, Fmtmsg("��ѯ��������Ϊ��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ѯ��������Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lQueryNum = atoi(chxunbis);
	if (0 >= lQueryNum)
	{
		LOG(LM_STD, Fmtmsg("�Ƿ���ѯ����"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�Ƿ���ѯ����");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	lEndNum = lBegNum + lQueryNum;
	if (MAXPAGECOUNT < lQueryNum)
	{
		lQueryNum = MAXPAGECOUNT;
	}
	
	trim(quetype);
	if(strcmp(quetype, "0") == 0)
	{
		/* ���ѯWHERE */
		memset(buff,0x00,sizeof(buff));
		sprintf(buff," FROM YW_WZYH_DZJG WHERE qsrq>='%s' and qsrq<='%s'",qsrq,zzrq);
	}
	else
	{ 
		/* ���ѯWHERE */
		memset(buff,0x00,sizeof(buff));
		sprintf(buff," FROM YW_WZYH_DZJG WHERE qsrq>='%s' and qsrq<='%s' and dz_bz='%s'  ",qsrq,zzrq,quetype);
	}
	/**��ѯ�ܱ���**/
	memset(sSql,0x00,sizeof(sSql));
	snprintf(sSql , sizeof(sSql) ,"SELECT COUNT(dz_bz) %s" , buff);
	LOG(LM_STD, Fmtmsg("�ܱ���SQL[%s]", sSql), "DEBUG")
	iRet = DBSelectToVar(ErrMsg, (void *)sTmp, sSql);
	if( iRet < 0)
	{
		LOG(LM_STD, Fmtmsg("��ѯ���ݿ�ʧ��[%d]", iRet), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ѯ���ݿ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	lTotalCount = atol(sTmp);
	
	/**��ǰҳ����**/
	memset(sSql,0x00,sizeof(sSql));
	snprintf(sSql , sizeof(sSql) ,"select count(dz_bz) from (select t.dz_bz,rownum rn from (select dz_bz %s ) t WHERE rownum<%d) WHERE rn>=%d",buff,lEndNum,lBegNum);
	LOG(LM_STD, Fmtmsg("��ǰҳ����SQL[%s]", sSql), "DEBUG")
	iRet = DBSelectToVar(ErrMsg, (void *)sTmp, sSql);
	if( iRet < 0)
	{
		LOG(LM_STD, Fmtmsg("��ѯ���ݿ�ʧ��[%d]", iRet), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "��ѯ���ݿ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}	
	lPageCount =  atol(sTmp);
	
	if (0 == lTotalCount)
	{
		LOG(LM_STD, Fmtmsg("û�з��������Ķ��˽����Ϣ"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "û�з��������Ķ��˽����Ϣ");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	if (lTotalCount < lBegNum)
	{
		LOG(LM_STD, Fmtmsg("û�з��������Ķ��˽����Ϣ"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "û�з��������Ķ��˽����Ϣ");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	if (0 == lPageCount)
	{
		LOG(LM_STD, Fmtmsg("û�з��������Ķ��˽����Ϣ"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "û�з��������Ķ��˽����Ϣ");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	if (lTotalCount > lEndNum)
	{
		COMP_SOFTSETXML("/gmjr/resp/output/querymark", "01")
	}
	else
	{
		COMP_SOFTSETXML("/gmjr/resp/output/querymark", "02")
	}
	memset(cTmp, 0x00, sizeof(cTmp));
	sprintf(cTmp, "%d", lPageCount);
	COMP_SOFTSETXML("/gmjr/resp/output/mxibs", cTmp)
	
	/** ��ѯ��ϸ **/
	memset(sSql,0x00,sizeof(sSql));
	snprintf(sSql,sizeof(sSql),"select qsrq,dz_bz,product_buy_num,product_buy_amount,product_back_num,product_back_amount,zc_amount from ("
							" select t.qsrq,t.dz_bz,t.product_buy_num,t.product_buy_amount,t.product_back_num,t.product_back_amount,t.zc_amount,rownum rn from ("
				" select qsrq,dz_bz,product_buy_num,product_buy_amount,product_back_num,product_back_amount,zc_amount  %s) t where rownum<%ld) where rn>=%ld",buff,lEndNum, lBegNum);
	
	LOG(LM_STD, Fmtmsg("��ϸSQL[%s]", sSql), "DEBUG")
	if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

	while(1)
	{
		iRet = DCIFetch2(cur, DCI_FETCH_NEXT, queryoffset);
		if (iRet == -100 || iRet == -1403)
		{
			LOG(LM_STD, Fmtmsg("��ѯ����[%d][%ld]", iCountNum), "DEBUG")
			break;
		}
		else if (iRet < 0)
		{
			LOG(LM_STD, Fmtmsg("��ѯ���˽����Ϣʧ��[%d]", iRet), "DEBUG")
			fpub_SetMsg(lXmlhandle, 10001, "��ѯ���˽����Ϣʧ��");
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			DCIFreeCursor(cur);
			return COMPSTATUS_FAIL;
		}
		
		if (iCountNum > lPageCount)
		{
			LOG(LM_STD, Fmtmsg("��ѯ����[%d][%ld]", iCountNum, lPageCount), "DEBUG")
			break;
		}
       
		memset(jyrq, 0x00, sizeof(jyrq));
		memset(dz_bz, 0x00, sizeof(dz_bz));
		memset(product_buy_num, 0x00, sizeof(product_buy_num));
		product_buy_amount=0.00;
		memset(product_back_num, 0x00, sizeof(product_back_num));
		product_back_amount=0.00;
		zc_amount=0.00;
		
		sprintf(jyrq , "%s" , DCIFieldAsString( cur, 0));
		sprintf(dz_bz , "%s" , DCIFieldAsString( cur, 1));
		sprintf(product_buy_num , "%s" , DCIFieldAsString( cur, 2));
		product_buy_amount = atof(DCIFieldAsString( cur, 3));
		sprintf(product_back_num , "%s" , DCIFieldAsString( cur, 4));
		product_back_amount = atof(DCIFieldAsString( cur, 5));
		zc_amount = atof(DCIFieldAsString( cur, 6));
		
		iCountNum++;
		/* ����ʱ�� */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/transaction_time", iCountNum);
		COMP_SOFTSETXML(cTmp, jyrq)
		/* ���˽�� */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/dzjg", iCountNum);
		COMP_SOFTSETXML(cTmp, dz_bz)
		/* ��Ʋ�Ʒ�����ܱ��� */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/sgzbs", iCountNum);
		COMP_SOFTSETXML(cTmp, product_buy_num)
		/* �깺�ʽ��ܶ� */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/sgamout", iCountNum);
		memset(sBuf,0x00,sizeof(sBuf));
		sprintf(sBuf, "%.2f", product_buy_amount);
		COMP_SOFTSETXML(cTmp, sBuf)
		/* �������ܱ��� */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/shzbs", iCountNum);
		COMP_SOFTSETXML(cTmp, product_back_num)
		/* ����ʽ��ܶ� */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/shamout", iCountNum);
		memset(sBuf,0x00,sizeof(sBuf));
		sprintf(sBuf, "%.2f", product_back_amount);
		COMP_SOFTSETXML(cTmp, sBuf)
		/* �����ʽ��ܶ� */
		memset(cTmp, 0x00, sizeof(cTmp));
		sprintf(cTmp, "/gmjr/resp/output/list/xhbzks|%d/zcamout", iCountNum);
		memset(sBuf,0x00,sizeof(sBuf));
		sprintf(sBuf, "%.2f", zc_amount);
		COMP_SOFTSETXML(cTmp, sBuf)        
    }
	
    DCIFreeCursor(cur);

#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "")
#endif

	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
	return COMPSTATUS_SUCC;
}

/********************************************************************
����ע�����ƣ�Process_CHKWDLCOREBAK
�����������ƣ�Process_CHKWDLCOREBAK
�������壺
�������ܣ�΢��������Ĺ�����ϸ����
�������ò�����
    ���    ��������    ��Դ���    ȱʡֵ    �Ƿ�ɿ�    ����˵��
������״̬��
    ״̬    ���˵��
�� Ŀ �飺
�� �� Ա��txbdir
�������ڣ�20171103
�޸����ڣ�
*********************************************************************/
int Process_CHKWDLCOREBAK(HXMLTREE lXmlhandle, char *qshh, char *chk_date)
{
	char qsjg[14+1]; //�������
	char qsrq[10+1]; //��������
	SDB_YW_WZYH_DZMX   YW_WZYH_DZMX; //΢����������ϸ��
	SDB_YW_WZYH_COREMX YW_WZYH_COREMX;//���Ķ���������ϸ��
	SDB_YW_WZYH_YWLS   YW_WZYH_YWLS;//������ˮ��
	SDB_YW_WZYH_ERRMX  YW_WZYH_ERRMX;//�����ϸ��   
	int i=0 , iLSBZ = 0 , iRet;         //�����α���100�����ύ
	char sSql[1024] , sErrMsg[256];
	CURSOR cur;

	//��ֵ�������
	memset(qsjg,0,sizeof(qsjg));
	memcpy(qsjg, qshh, sizeof(qsjg)-1);
	//��ֵ��������
	memset(qsrq,0,sizeof(qsrq));
	memcpy(qsrq, chk_date, sizeof(qsrq)-1);
  
	/* 1�������������ϸ������˽���� */
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "DELETE FROM YW_WZYH_ERRMX WHERE jyrq='%s'" , chk_date);
	DCIExecuteDirect(sSql);
	DCICommit();
	
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "DELETE FROM YW_WZYH_dzjg WHERE qsrq='%s'" , chk_date);
	DCIExecuteDirect(sSql);
	DCICommit();

	/*2������΢����������ϸ�����ݹ��Һ��Ķ�����ϸ��*/
	LOG(LM_DEBUG,Fmtmsg("����΢����������ϸ�����ݹ��Һ��Ķ�����ϸ��"),"INFO")
	memset(&YW_WZYH_DZMX, 0x00, sizeof(YW_WZYH_DZMX));
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "SELECT * FROM YW_WZYH_DZMX WHERE dzrq='%s' and deal_flag='S'" , qsrq);
	LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO")
	if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) < 0)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	if (DCIExecute(cur) < 0)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

	i = 0;
	while(iRet = DBFetch(cur, SD_YW_WZYH_DZMX, NUMELE(SD_YW_WZYH_DZMX), &YW_WZYH_DZMX, sErrMsg) > 0)
	{
		LOG(LM_DEBUG,Fmtmsg("����΢����������ϸ�����ݹ��Һ��Ķ�����ϸ���¼[%d][%d][%s]" , i,iRet , YW_WZYH_DZMX.business_id),"INFO")
		i++; //ÿ�μ���+1
		memset(&YW_WZYH_ERRMX, 0x00, sizeof(YW_WZYH_ERRMX));

		/* ����YW_WZYH_DZMX��ȥYW_WZYH_YWLS���ȡ�������ڡ�������ˮ */
		trim(YW_WZYH_DZMX.dzrq); //��������
		trim(YW_WZYH_DZMX.business_id);//������ˮ
		YW_WZYH_ERRMX.errflag[0] = '1';
		
		iLSBZ = 0;
		memset(&YW_WZYH_YWLS, 0x00, sizeof(YW_WZYH_YWLS));
		memset(sSql, 0x00, sizeof(sSql));
		sprintf(sSql, "SELECT * FROM YW_WZYH_YWLS WHERE business_id='%s'" , YW_WZYH_DZMX.business_id);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO") 
		iRet = prv_SelMulToStruct((const char *)sSql, SD_YW_WZYH_YWLS, NUMELE(SD_YW_WZYH_YWLS), &YW_WZYH_YWLS);
		LOG(LM_DEBUG,Fmtmsg("1waiblius[%s]" , YW_WZYH_YWLS.waiblius) , "INFO") 
		if (iRet < 0)		/* ��ѯʧ�� */
		{
			LOG(LM_DEBUG,Fmtmsg("���[%s] ִ�в�ѯ����ʧ��qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq, iRet), "")
			DCIFreeCursor(cur);
			DCIRollback();
			return -1;
		}
		else if(iRet == 0)		/* �޼�¼ */
		{
			iLSBZ = 1;
			memcpy(YW_WZYH_ERRMX.errflag, "2", 1);   /* 0-��ʼ 1-��ƽ 2-������΢���� 3-΢���޺����� 4-���� */
			if (memcmp(YW_WZYH_DZMX.tran_type, "01" , 2)==0)  //01-����ת��(�깺)02-����ת��(���)
			{
				memcpy(YW_WZYH_ERRMX.errmsg, "����깺-΢���У�������,�����쳣���,��Ƽ�����ʵ" , strlen("����깺-΢���У�������,�����쳣���,��Ƽ�����ʵ"));   
			}
			else if (memcmp(YW_WZYH_DZMX.tran_type, "02" , 2)==0)
			{
				memcpy(YW_WZYH_ERRMX.errmsg, "������-΢���У�������,��Ҫ���ͻ���" , strlen("������-΢���У�������,��Ҫ���ͻ���"));   
			}
			else
			{
				memcpy(YW_WZYH_ERRMX.errmsg, "΢���У�������" , strlen("������-΢���У�������,��Ҫ���ͻ���"));  
			}
		}
		else		/* �н�����ˮ */
		{
			/*���Һ�����ϸ��*/
			trim(YW_WZYH_YWLS.hxrq); //��������
			trim(YW_WZYH_YWLS.hxls);//������ˮ
			memset(&YW_WZYH_COREMX, 0x00, sizeof(YW_WZYH_COREMX));
			memset(sSql, 0x00, sizeof(sSql));
			sprintf(sSql, "SELECT * FROM YW_WZYH_COREMX WHERE qslsh='%s' and dzflag <> '2'" , YW_WZYH_YWLS.waiblius);
			LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO") 
			iRet = prv_SelMulToStruct((const char *)sSql, SD_YW_WZYH_COREMX, NUMELE(SD_YW_WZYH_COREMX), &YW_WZYH_COREMX);
			if (iRet < 0)
			{
				LOG(LM_DEBUG,Fmtmsg("���[%s] ִ�в�ѯ����ʧ��qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq, iRet),"")
				DCIFreeCursor(cur);
				DCIRollback();
				return -1;
			}

			if( iRet == 0 ) //΢���У�������
			{
				LOG(LM_DEBUG,Fmtmsg("΢���У�������"),"INFO") 
				memcpy(YW_WZYH_ERRMX.errflag, "2", 1);   /* 0-��ʼ 1-��ƽ 2-������΢���� 3-΢���޺����� 4-���� */
				if (memcmp(YW_WZYH_DZMX.tran_type, "01" , 2)==0)  //01-����ת��(�깺)02-����ת��(���)
				{
					strcpy(YW_WZYH_ERRMX.errmsg, "����깺-΢���У�������,�����쳣���,��Ƽ�����ʵ");   
				}
				else if (memcmp(YW_WZYH_DZMX.tran_type, "02" , 2)==0)
				{
					strcpy(YW_WZYH_ERRMX.errmsg, "������-΢���У�������,��Ҫ���ͻ���");   
				}
				else
				{
					strcpy(YW_WZYH_ERRMX.errmsg, "΢���У�������");  
				}
				LOG(LM_DEBUG,Fmtmsg("sSql[%s]...",sSql),"INFO") 
			}
			else  //΢�ںͺ��Ķ��У��ȶԽ��
			{ 
				LOG(LM_DEBUG,Fmtmsg("΢�ںͺ��Ķ��У��ȶԽ��"),"INFO") 
				LOG(LM_DEBUG,Fmtmsg("���[%s] ��齻�׽�� wz_jyje=[%f] hx_jyje=[%f] ",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.amount,YW_WZYH_COREMX.jyje),"")
				if ((YW_WZYH_DZMX.amount - YW_WZYH_COREMX.jyje) > 0.00005 || (YW_WZYH_DZMX.amount - YW_WZYH_COREMX.jyje) < -0.00005)
				{                
					memcpy(YW_WZYH_ERRMX.errflag, "4", 1);   /* 0-��ʼ 1-��ƽ 2-������΢���� 3-΢���޺����� 4-���� */
					strcpy(YW_WZYH_ERRMX.errmsg, "΢������ķ��ؽ���");
					YW_WZYH_ERRMX.coreamount=YW_WZYH_COREMX.jyje;
				}
				
				/* �޸Ľ�����ˮ������Ķ���״̬ */
				if (YW_WZYH_ERRMX.errflag[0] == '1')
				{   
					trim(YW_WZYH_DZMX.dzrq);
					trim(YW_WZYH_DZMX.business_id);
					memset(sSql , 0x00 , sizeof(sSql));
					/* ����Ķ��˱�־(0-��ʼ1-��ƽ2-������ƽ̨��3-ƽ̨��������4-����) */
					sprintf(sSql , "UPDATE YW_WZYH_YWLS SET hxdzbz='1' WHERE business_id='%s'" , YW_WZYH_DZMX.business_id);
					iRet = DCIExecuteDirect(sSql);
				}
				else
				{
					trim(YW_WZYH_DZMX.dzrq);
					trim(YW_WZYH_DZMX.business_id);
					memset(sSql , 0x00 , sizeof(sSql));
					/* ����Ķ��˱�־(0-��ʼ 1-��ƽ 2-������΢���� 3-΢���޺����� 4-����) */
					sprintf(sSql , "UPDATE YW_WZYH_YWLS SET hxdzbz='4' WHERE business_id='%s'" , YW_WZYH_DZMX.business_id);
					iRet = DCIExecuteDirect(sSql);
				}
				if (iRet <0)
				{
					LOG(LM_DEBUG,Fmtmsg("���[%s] �޸���ˮ��״̬ʧ�� jyrq=[%s] business_id=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.dzrq,YW_WZYH_DZMX.business_id,iRet),"")
					DCIFreeCursor(cur);
					DCIRollback();
					return -1;
				}
            
				/* �޸ĺ��Ķ�����ϸ��Ϊ�Ѷ���״̬ */
				/*���˱�־:0��ʼ��1�Ѷ��ˡ�2��������˵���ˮ*/
				trim(YW_WZYH_COREMX.hxdate);
				trim(YW_WZYH_COREMX.hxnum);
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , " UPDATE YW_WZYH_COREMX SET dzflag='%c' WHERE hxnum='%s'" , YW_WZYH_ERRMX.errflag[0] , YW_WZYH_COREMX.hxnum);
				iRet = DCIExecuteDirect(sSql);
				if (iRet < 0)	
				{                
					LOG(LM_DEBUG,Fmtmsg("���[%s] �޸ĺ��Ķ�����ϸ��״̬ʧ�� jyrq=[%s] business_id=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.dzrq,YW_WZYH_DZMX.business_id,iRet),"")
					DCIFreeCursor(cur);
					DCIRollback();
					return -1;
				}
				
				/* ΢��������������ϸ��Ϊ�Ѷ���״̬*/
				/*���˱�־(0-��ʼ 1-��ƽ 2-������΢���� 3-΢���޺����� 4-����)*/
				trim(YW_WZYH_DZMX.dzrq);
				trim(YW_WZYH_DZMX.business_id);
				trim(YW_WZYH_ERRMX.errflag);
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , " UPDATE YW_WZYH_DZMX SET dz_flag='%c' WHERE business_id='%s'" , YW_WZYH_ERRMX.errflag[0] , YW_WZYH_DZMX.business_id);
				iRet = DCIExecuteDirect(sSql);
				if (iRet < 0)	
				{
					LOG(LM_DEBUG,Fmtmsg("���[%s] �޸�΢����������ϸ��״̬ʧ�� jyrq=[%s] business_id=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.dzrq,YW_WZYH_DZMX.business_id,iRet),"")
					DCIFreeCursor(cur);
					DCIRollback();
					return -1;
				}            
			}
		}
				
		trim(YW_WZYH_ERRMX.errflag);
		if (YW_WZYH_ERRMX.errflag[0] != '1')		/* ����ʧ�� */
		{
			memcpy(YW_WZYH_ERRMX.jyrq, qsrq, sizeof(YW_WZYH_ERRMX.jyrq)-1);
			memcpy(YW_WZYH_ERRMX.business_id, YW_WZYH_DZMX.business_id, sizeof(YW_WZYH_ERRMX.business_id)-1);
			trim(YW_WZYH_DZMX.tran_type);
			if (strcmp(YW_WZYH_DZMX.tran_type, "01")==0)  //01-����ת��(�깺)02-����ת��(���)
			{
				memcpy(YW_WZYH_ERRMX.accno, YW_WZYH_DZMX.payer_acct, sizeof(YW_WZYH_ERRMX.accno)-1);
				memcpy(YW_WZYH_ERRMX.accname, YW_WZYH_DZMX.payer_name, sizeof(YW_WZYH_ERRMX.accname)-1);
				memcpy(YW_WZYH_ERRMX.subbusstype, "0001" , 4);
			}
			else
			{
				memcpy(YW_WZYH_ERRMX.accno, YW_WZYH_DZMX.payee_acct, sizeof(YW_WZYH_ERRMX.accno)-1);
				memcpy(YW_WZYH_ERRMX.accname, YW_WZYH_DZMX.payee_name, sizeof(YW_WZYH_ERRMX.accname)-1);
				memcpy(YW_WZYH_ERRMX.subbusstype, "0002" , 4);
			}
			memcpy(YW_WZYH_ERRMX.busstype, "C010" , 4);
			
			
			memcpy(YW_WZYH_ERRMX.flag, YW_WZYH_YWLS.flag, sizeof(YW_WZYH_ERRMX.flag)-1);
			memcpy(YW_WZYH_ERRMX.qzrq, YW_WZYH_YWLS.qzrq, sizeof(YW_WZYH_ERRMX.qzrq)-1);
			memcpy(YW_WZYH_ERRMX.qzls, YW_WZYH_YWLS.qzls, sizeof(YW_WZYH_ERRMX.qzls)-1);
			memcpy(YW_WZYH_ERRMX.hxrq, YW_WZYH_YWLS.hxrq, sizeof(YW_WZYH_ERRMX.hxrq)-1);
			memcpy(YW_WZYH_ERRMX.hxls, YW_WZYH_YWLS.hxls, sizeof(YW_WZYH_ERRMX.hxls)-1);
			memcpy(YW_WZYH_ERRMX.hxxym, YW_WZYH_YWLS.hxxym, sizeof(YW_WZYH_ERRMX.hxxym)-1);
			memcpy(YW_WZYH_ERRMX.hxrespmsg, YW_WZYH_YWLS.hxrespmsg, sizeof(YW_WZYH_ERRMX.hxrespmsg)-1);
			memcpy(YW_WZYH_ERRMX.waiblius, YW_WZYH_YWLS.waiblius, sizeof(YW_WZYH_ERRMX.waiblius)-1);
			
			memcpy(YW_WZYH_ERRMX.transtime, YW_WZYH_DZMX.transtime, sizeof(YW_WZYH_ERRMX.transtime)-1);
			memcpy(YW_WZYH_ERRMX.snd_organ, YW_WZYH_DZMX.snd_organ, sizeof(YW_WZYH_ERRMX.snd_organ)-1);
			memcpy(YW_WZYH_ERRMX.rev_organ, YW_WZYH_DZMX.rev_organ, sizeof(YW_WZYH_ERRMX.rev_organ)-1);
			//΢�ڵı�ṹ������ֶ�,��YW_WZYH_YWLSȡ
			memcpy(YW_WZYH_ERRMX.tran_name, YW_WZYH_YWLS.tran_name, sizeof(YW_WZYH_ERRMX.tran_name)-1);
			memcpy(YW_WZYH_ERRMX.tran_type, YW_WZYH_DZMX.tran_type, sizeof(YW_WZYH_ERRMX.tran_type)-1);
			//΢�ڵı�ṹ������ֶ�,��YW_WZYH_YWLSȡ
			memcpy(YW_WZYH_ERRMX.msg_version, YW_WZYH_YWLS.msg_version, sizeof(YW_WZYH_ERRMX.msg_version)-1);
			//�����΢�ڵı�ṹ����һ��
			memcpy(YW_WZYH_ERRMX.pay_product_code, YW_WZYH_DZMX.business_type, sizeof(YW_WZYH_ERRMX.pay_product_code)-1);
			memcpy(YW_WZYH_ERRMX.acct_type, YW_WZYH_DZMX.acct_type, sizeof(YW_WZYH_ERRMX.acct_type)-1);
			memcpy(YW_WZYH_ERRMX.payee_name, YW_WZYH_DZMX.payee_name, sizeof(YW_WZYH_ERRMX.payee_name)-1);
			memcpy(YW_WZYH_ERRMX.payee_acct, YW_WZYH_DZMX.payee_acct, sizeof(YW_WZYH_ERRMX.payee_acct)-1);
			memcpy(YW_WZYH_ERRMX.payee_opbk, YW_WZYH_DZMX.payee_opbk, sizeof(YW_WZYH_ERRMX.payee_opbk)-1);
			memcpy(YW_WZYH_ERRMX.payer_name, YW_WZYH_DZMX.payer_name, sizeof(YW_WZYH_ERRMX.payer_name)-1);
			memcpy(YW_WZYH_ERRMX.payer_acct, YW_WZYH_DZMX.payer_acct, sizeof(YW_WZYH_ERRMX.payer_acct)-1);
			memcpy(YW_WZYH_ERRMX.payer_opbk, YW_WZYH_DZMX.payer_opbk, sizeof(YW_WZYH_ERRMX.payer_opbk)-1);
			memcpy(YW_WZYH_ERRMX.tzbz, "0", 1);
			YW_WZYH_ERRMX.amount= YW_WZYH_DZMX.amount;
			YW_WZYH_ERRMX.fee_amount= YW_WZYH_DZMX.fee_amount;
			memcpy(YW_WZYH_ERRMX.ccy, YW_WZYH_DZMX.ccy, sizeof(YW_WZYH_ERRMX.ccy)-1);
			//����ֶ�����������
			memcpy(YW_WZYH_ERRMX.work_date, YW_WZYH_DZMX.work_date, sizeof(YW_WZYH_ERRMX.work_date)-1);
			memcpy(YW_WZYH_ERRMX.scene_no, YW_WZYH_DZMX.scene_no, sizeof(YW_WZYH_ERRMX.scene_no)-1);
			memcpy(YW_WZYH_ERRMX.czflag, YW_WZYH_DZMX.cz_flag, sizeof(YW_WZYH_ERRMX.czflag)-1);
			
			if(iLSBZ == 1)
				memcpy(YW_WZYH_ERRMX.lsbz, "1", 1);

			iRet=DBInsert("YW_WZYH_ERRMX", SD_YW_WZYH_ERRMX ,NUMELE(SD_YW_WZYH_ERRMX), &YW_WZYH_ERRMX, sErrMsg);
            if (iRet < 0)
            {
				LOG(LM_DEBUG,Fmtmsg("���[%s] ������˲���ʧ�� jyrq=[%s] business_id=[%s] sqlcode=[%d] �� sErrMsg[%s]",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.dzrq,YW_WZYH_DZMX.business_id,iRet , sErrMsg),"")
				DCIFreeCursor(cur);
				DCIRollback();
				return -1;
            }    	
		}
		
		trim(YW_WZYH_ERRMX.errflag);
		trim(YW_WZYH_DZMX.dzrq);
		trim(YW_WZYH_DZMX.business_id);
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE YW_WZYH_DZMX SET dz_flag='%s' WHERE business_id='%s'" , YW_WZYH_ERRMX.errflag , YW_WZYH_DZMX.business_id);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = DCIExecuteDirect(sSql);
		if (iRet < 0)	
		{
			LOG(LM_DEBUG,Fmtmsg("���[%s] �޸�΢����������ϸ��״̬ʧ�� jyrq=[%s] business_id=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),YW_WZYH_DZMX.dzrq,YW_WZYH_DZMX.business_id, iRet),"")
			DCIFreeCursor(cur);
			DCIRollback();
			return -1;
		}
		
		/* �޸Ľ�����ˮ������Ķ���״̬ */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , " UPDATE YW_WZYH_YWLS SET hxdzbz='%s' WHERE business_id='%s'" , YW_WZYH_ERRMX.errflag , YW_WZYH_DZMX.business_id);	
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = DCIExecuteDirect(sSql); /* ����Ķ��˱�־(0-��ʼ 1-��ƽ 2-������΢���� 3-΢���޺����� 4-����) */ 
		
		/* ���º��ļ�¼���п��ܺ����޼�¼ */
		/*memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE YW_WZYH_COREMX SET dzflag='%s' WHERE qslsh='%s'" , YW_WZYH_ERRMX.errflag , YW_WZYH_YWLS.waiblius);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = DCIExecuteDirect(sSql);*/
		
		if(i>=100)
		{
			LOG(LM_DEBUG,Fmtmsg("�ﵽ��%d����,���ύһ��", i), "")
			DCICommit();
			i=0;
		}
		
		memset(&YW_WZYH_DZMX, 0x00, sizeof(YW_WZYH_DZMX));
    }
	if (iRet < 0)		/* iRet=0�����¼��iRet<0��ȡ��¼ʱʧ�� */
	{
		LOG(LM_DEBUG,Fmtmsg("���[%s] ִ�в�ѯ����ʧ��qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq, iRet), "")
		DCIFreeCursor(cur);
		DCIRollback();
		return -1;
	}

    DCIFreeCursor(cur);
   
	/*3�����������,΢���޵���� */
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "SELECT * FROM YW_WZYH_COREMX  WHERE qsrq='%s' and dzflag='0'" , qsrq);
	LOG(LM_DEBUG,Fmtmsg("���������,΢���޵����SQL[%s]" , sSql) , "INFO")
	if ((cur = DCIDeclareCursor(sSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }
	
	if (DCIExecute(cur) == -1)
    {
        LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
        DCIFreeCursor(cur);
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
        return COMPRET_FAIL;
    }

	i=0;//��ʼѭ������
	memset(&YW_WZYH_COREMX, 0x00, sizeof(YW_WZYH_COREMX));
	LOG(LM_DEBUG,Fmtmsg("���������,΢���޵������¼[%d]" , i),"INFO")
	while(iRet = DBFetch(cur, SD_YW_WZYH_COREMX, NUMELE(SD_YW_WZYH_COREMX), &YW_WZYH_COREMX, sErrMsg ) > 0)
	{
		i++;

		trim(YW_WZYH_COREMX.hxdate); //��������
		trim(YW_WZYH_COREMX.hxnum);//������ˮ
		memset(&YW_WZYH_YWLS, 0x00, sizeof(YW_WZYH_YWLS));
		
		memset(&YW_WZYH_YWLS, 0x00, sizeof(YW_WZYH_YWLS));
		memset(sSql, 0x00, sizeof(sSql));
		sprintf(sSql, "SELECT YW_WZYH_YWLS.* FROM YW_WZYH_YWLS , yw_wzyh_dzmx WHERE  YW_WZYH_YWLS.waiblius='%s' AND YW_WZYH_YWLS.business_id=yw_wzyh_dzmx.business_id AND yw_wzyh_dzmx.deal_flag='S'" , YW_WZYH_COREMX.qslsh);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = prv_SelMulToStruct((const char *)sSql, SD_YW_WZYH_YWLS, NUMELE(SD_YW_WZYH_YWLS), &YW_WZYH_YWLS);
		if (iRet < 0)	/* ��ѯʧ�� */
		{
			LOG(LM_STD,Fmtmsg("���ݿ����ʧ��,sqlerr[%s]",DCILastError() ),"ERROR")
			DCIFreeCursor(cur);
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			fpub_SetMsg(lXmlhandle, MID_SQL_ERROR, MSG_SQL_ERROR);
			return COMPRET_FAIL;
		}
		else if(iRet > 0)	/* �м�¼��ִ����һ�� */
		{
			memset(&YW_WZYH_COREMX, 0x00, sizeof(YW_WZYH_COREMX));
			continue;
		}
		
		/* �޼�¼ */		
		memset(&YW_WZYH_YWLS, 0x00, sizeof(YW_WZYH_YWLS));
		memset(sSql, 0x00, sizeof(sSql));
		sprintf(sSql, "SELECT * FROM YW_WZYH_YWLS WHERE waiblius='%s'" , YW_WZYH_COREMX.qslsh);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = prv_SelMulToStruct((const char *)sSql, SD_YW_WZYH_YWLS, NUMELE(SD_YW_WZYH_YWLS), &YW_WZYH_YWLS);
		if (iRet == 0)	/* ��ѯ�޼�¼ */
			memcpy(YW_WZYH_ERRMX.lsbz, "1", 1);
		
		memset(&YW_WZYH_ERRMX, 0x00, sizeof(YW_WZYH_ERRMX));
		YW_WZYH_ERRMX.errflag[0] = '3';		/* ���˱�־(0-��ʼ 1-��ƽ 2-������΢���� 3-΢���޺����� 4-���� */
		strncpy(YW_WZYH_ERRMX.tzbz,"0",sizeof(YW_WZYH_ERRMX.tzbz)-1);
 
		trim(YW_WZYH_YWLS.tran_type);
		if (strcmp(YW_WZYH_YWLS.tran_type, "01")==0)  //01-����ת��(�깺)02-����ת��(���)
		{
			strcpy(YW_WZYH_ERRMX.errmsg, "����깺-������,΢����,��ҪĨ��");   
		}
		else if (strcmp(YW_WZYH_YWLS.tran_type, "02")==0)
		{
			strcpy(YW_WZYH_ERRMX.errmsg, "������-������,΢����,�����쳣���,��Ƽ�����ʵ");   
		}
		else
		{
			iLSBZ = 1;
			strcpy(YW_WZYH_ERRMX.errmsg, "������,΢����");  
		}  
		
		memcpy(YW_WZYH_ERRMX.jyrq, qsrq, sizeof(YW_WZYH_ERRMX.jyrq)-1);
		memcpy(YW_WZYH_ERRMX.business_id, YW_WZYH_YWLS.business_id, sizeof(YW_WZYH_ERRMX.business_id)-1);
		memcpy(YW_WZYH_ERRMX.accno, YW_WZYH_COREMX.jfyhzh, sizeof(YW_WZYH_ERRMX.accno)-1);
		memcpy(YW_WZYH_ERRMX.subbusstype, YW_WZYH_COREMX.subbusstype, sizeof(YW_WZYH_COREMX.subbusstype)-1);
		memcpy(YW_WZYH_ERRMX.busstype, YW_WZYH_COREMX.busstype, sizeof(YW_WZYH_COREMX.busstype)-1);
		
		memcpy(YW_WZYH_ERRMX.subbusstype, "0001" , 1);
		if (memcmp(YW_WZYH_ERRMX.subbusstype, "0001" , 4)==0)  /* 0001-����ת��(�깺)0002-����ת��(���) */
		{
			memcpy(YW_WZYH_ERRMX.accname, YW_WZYH_YWLS.payer_name, sizeof(YW_WZYH_ERRMX.accname)-1);
		}
		else if (memcmp(YW_WZYH_ERRMX.subbusstype, "0002" , 4)==0)  //0001-����ת��(�깺)0002-����ת��(���)
		{
			memcpy(YW_WZYH_ERRMX.accname, YW_WZYH_YWLS.payee_name, sizeof(YW_WZYH_ERRMX.accname)-1);
		}
		memcpy(YW_WZYH_ERRMX.flag, YW_WZYH_YWLS.flag, sizeof(YW_WZYH_ERRMX.flag)-1);
		memcpy(YW_WZYH_ERRMX.qzrq, YW_WZYH_YWLS.qzrq, sizeof(YW_WZYH_ERRMX.qzrq)-1);
		memcpy(YW_WZYH_ERRMX.qzls, YW_WZYH_YWLS.qzls, sizeof(YW_WZYH_ERRMX.qzls)-1);
		memcpy(YW_WZYH_ERRMX.hxrq, YW_WZYH_COREMX.hxdate, sizeof(YW_WZYH_ERRMX.hxrq)-1);
		memcpy(YW_WZYH_ERRMX.hxls, YW_WZYH_COREMX.hxnum, sizeof(YW_WZYH_ERRMX.hxls)-1);
		memcpy(YW_WZYH_ERRMX.hxxym, YW_WZYH_YWLS.hxxym, sizeof(YW_WZYH_ERRMX.hxxym)-1);
		memcpy(YW_WZYH_ERRMX.hxrespmsg, YW_WZYH_YWLS.hxrespmsg, sizeof(YW_WZYH_ERRMX.hxrespmsg)-1);
		memcpy(YW_WZYH_ERRMX.waiblius, YW_WZYH_COREMX.qslsh, sizeof(YW_WZYH_ERRMX.waiblius)-1);        	   
		memcpy(YW_WZYH_ERRMX.transtime, YW_WZYH_YWLS.transtime, sizeof(YW_WZYH_ERRMX.transtime)-1);
		memcpy(YW_WZYH_ERRMX.snd_organ, YW_WZYH_YWLS.snd_organ, sizeof(YW_WZYH_ERRMX.snd_organ)-1);
		memcpy(YW_WZYH_ERRMX.rev_organ, YW_WZYH_YWLS.rev_organ, sizeof(YW_WZYH_ERRMX.rev_organ)-1);
		memcpy(YW_WZYH_ERRMX.tran_name, YW_WZYH_YWLS.tran_name, sizeof(YW_WZYH_ERRMX.tran_name)-1);
		memcpy(YW_WZYH_ERRMX.tran_type, YW_WZYH_YWLS.tran_type, sizeof(YW_WZYH_ERRMX.tran_type)-1);
		memcpy(YW_WZYH_ERRMX.msg_version, YW_WZYH_YWLS.msg_version, sizeof(YW_WZYH_ERRMX.msg_version)-1);
		memcpy(YW_WZYH_ERRMX.pay_product_code, YW_WZYH_YWLS.pay_product_code, sizeof(YW_WZYH_ERRMX.pay_product_code)-1);
		memcpy(YW_WZYH_ERRMX.acct_type, YW_WZYH_YWLS.acct_type, sizeof(YW_WZYH_ERRMX.acct_type)-1);
		memcpy(YW_WZYH_ERRMX.payee_name, YW_WZYH_COREMX.dfhm, sizeof(YW_WZYH_ERRMX.payee_name)-1);
		memcpy(YW_WZYH_ERRMX.payee_acct, YW_WZYH_COREMX.dfyhzh, sizeof(YW_WZYH_ERRMX.payee_acct)-1);
		memcpy(YW_WZYH_ERRMX.payee_opbk, YW_WZYH_YWLS.payee_opbk, sizeof(YW_WZYH_ERRMX.payee_opbk)-1);
		memcpy(YW_WZYH_ERRMX.payer_name, YW_WZYH_COREMX.jfhm, sizeof(YW_WZYH_ERRMX.payer_name)-1);
		memcpy(YW_WZYH_ERRMX.payer_acct, YW_WZYH_COREMX.jfyhzh, sizeof(YW_WZYH_ERRMX.payer_acct)-1);
		memcpy(YW_WZYH_ERRMX.payer_opbk, YW_WZYH_YWLS.payer_opbk, sizeof(YW_WZYH_ERRMX.payer_opbk)-1);
		memcpy(YW_WZYH_ERRMX.ccy, YW_WZYH_YWLS.ccy, sizeof(YW_WZYH_ERRMX.ccy)-1);
		//����ֶ�����������
		memcpy(YW_WZYH_ERRMX.work_date, YW_WZYH_YWLS.work_date, sizeof(YW_WZYH_ERRMX.work_date)-1);
		memcpy(YW_WZYH_ERRMX.scene_no, YW_WZYH_YWLS.scene_no, sizeof(YW_WZYH_ERRMX.scene_no)-1);
		memcpy(YW_WZYH_ERRMX.czflag, YW_WZYH_YWLS.czflag, sizeof(YW_WZYH_ERRMX.czflag)-1);
		YW_WZYH_ERRMX.coreamount = YW_WZYH_COREMX.jyje;
		YW_WZYH_ERRMX.fee_amount= YW_WZYH_YWLS.fee_amount;

		iRet=DBInsert("YW_WZYH_ERRMX", SD_YW_WZYH_ERRMX ,NUMELE(SD_YW_WZYH_ERRMX), &YW_WZYH_ERRMX, sErrMsg);
		if (iRet < 0)
		{
			LOG(LM_DEBUG,Fmtmsg("���[%s] ������˲���ʧ��qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq, iRet),"")
			DCIRollback();
			memset(sSql , 0x00 , sizeof(sSql));
			sprintf(sSql , "UPDATE YW_WZYH_DZKZ SET dzstate='2'  WHERE qsrq='%s'" , qsrq);
			iRet = DCIExecuteDirect(sSql);
			if (iRet < 0)
			{
				LOG(LM_DEBUG,Fmtmsg("���[%s]�޸Ķ��˿��Ʊ�ʧ��qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq,iRet),"")
				DCIFreeCursor(cur);
				DCIRollback();
				return -1;
			}
			
			DCICommit();
			return -1;
		}
            
		trim(YW_WZYH_COREMX.hxdate); //��������
		trim(YW_WZYH_COREMX.hxnum);//������ˮ
		memset(sSql , 0x00 , sizeof(sSql));
		/* ����Ķ��˱�־(0-��ʼ1-��ƽ2-������ƽ̨��3-ƽ̨��������4-����) */
		sprintf(sSql , "UPDATE YW_WZYH_YWLS SET hxdzbz='3' WHERE waiblius='%s'" , YW_WZYH_COREMX.qslsh);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = DCIExecuteDirect(sSql);
		
		trim(YW_WZYH_COREMX.hxdate);
		trim(YW_WZYH_COREMX.hxnum);
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE YW_WZYH_COREMX SET dzflag='3' WHERE qslsh='%s'" , YW_WZYH_COREMX.qslsh);
		LOG(LM_DEBUG,Fmtmsg("sSql[%s]",sSql),"INFO") 
		iRet = DCIExecuteDirect(sSql);
		if (iRet < 0)	
		{
			LOG(LM_DEBUG,Fmtmsg("���[%s] �޸ĺ��Ķ�����ϸ��״̬ʧ�� hxdate=[%s] hxnum=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),YW_WZYH_COREMX.hxdate,trim(YW_WZYH_COREMX.hxnum),iRet),"")
			DCIFreeCursor(cur);
			DCIRollback();
			return -1;
		}
		
		if(i>=100)
		{
			LOG(LM_DEBUG,Fmtmsg("�ﵽ��%d����,���ύһ��", i), "")
			DCICommit();
			i=0;
		}

		memset(&YW_WZYH_COREMX, 0x00, sizeof(YW_WZYH_COREMX));
	}
	if (iRet < 0)		/* iRet=0�����¼��iRet<0��ȡ��¼ʱʧ�� */
	{
		LOG(LM_DEBUG,Fmtmsg("���[%s] ִ�в�ѯ����ʧ��qsjg=[%s] qsrq=[%s] sqlcode=[%d]",fpub_GetCompname(lXmlhandle),qsjg,qsrq, iRet), "")
		DCIFreeCursor(cur);
		DCIRollback();
		return -1;
	}
	
	DCIFreeCursor(cur);
	DCICommit();  	 

	return 0;
}

/********************************************************************
���ע�����ƣ�WZYH_LOAD_NOTEFILE
����������ƣ�WZYH_LOAD_NOTEFILE
����������壺
����������ܣ�����΢���������ļ�
������ò�����
    ���    ��������    ��Դ���    ȱʡֵ    �Ƿ�ɿ�    ����˵��
������״̬��
    ״̬    ���˵��
�� Ŀ �飺
�� �� Ա��txbdir
�������ڣ�20171106
�޸����ڣ�
*********************************************************************/
IRESULT WZYH_LOAD_NOTEFILE(HXMLTREE lXmlhandle)
{
	char chk_date[10+1];   //��������
	SDB_YW_WZYH_DZMX YW_WZYH_DZMX;
	char sTmp[256], sErrMsg[256];          //ȡ��������(Ҫ�����һ��)
	char file_name[140+1];   //�����ļ�·��(���ȫ·��)
	char buf[1024], sSql[1024];          //����ļ�ÿһ������
	FILE *fp;                //�ļ�ָ��
	char delims[]="|";       //ÿ�����ÿһ�зָ���
	char *p = NULL;          //ÿһ�����ݵĴ��ָ��
	char sBuf[256];          //��Ž��temp
	char sAcct2622[20] , sAcct2622Name[64];
	char sAcct1392[20] , sAcct1392Name[64];
	int iRet , cnt=0 , fcnt;
	double amt=0 , famt;
	
	fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
	LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
#endif
  
	/*����1*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(1, sTmp, "��������");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("��������"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�������ڲ���Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(chk_date,0,sizeof(chk_date));
	strcpy(chk_date, sTmp);
	LOG(LM_STD,Fmtmsg("�������� [%s] ",chk_date), "INFO");
	
	/*����2*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(2, sTmp, "�����ļ�ȫ·��");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("�����ļ�ȫ·��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�����ļ�ȫ·������Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(file_name,0,sizeof(file_name));
	memcpy(sTmp+(strlen(sTmp)-3) , "txt" , 3);
	memcpy(file_name, sTmp , strlen(sTmp));
	
	LOG(LM_STD,Fmtmsg("�����ļ�ȫ·�� [%s] len[%d] , sTmp[%s]",file_name , strlen(sTmp) , sTmp), "INFO");
	
	memset(sAcct2622 , 0x00 , sizeof(sAcct2622));
	memset(sAcct2622Name , 0x00 , sizeof(sAcct2622Name));
	memset(sAcct1392 , 0x00 , sizeof(sAcct1392));
	memset(sAcct1392Name , 0x00 , sizeof(sAcct1392Name));
	
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_ACCT2622'");
	iRet = DBSelectToVarChar(sErrMsg, sAcct2622, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("���[%s]��ȡ΢�ڽ�鼯���˻���SQLCODE=[%d]" , fpub_GetCompname(lXmlhandle) , iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"��ȡ״̬��Ϣ��");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_ACCT2622NAME'");
	iRet = DBSelectToVarChar(sErrMsg, sAcct2622Name, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("���[%s]��ȡ΢�ڽ�鼯��������SQLCODE=[%d]" , fpub_GetCompname(lXmlhandle) , iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"��ȡ״̬��Ϣ��");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_ACCT1392'");
	iRet = DBSelectToVarChar(sErrMsg, sAcct1392, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("���[%s]��ȡ΢�ڽ���ػ��˻���SQLCODE=[%d]" , fpub_GetCompname(lXmlhandle) , iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"��ȡ״̬��Ϣ��");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_ACCT1392NAME'");
	iRet = DBSelectToVarChar(sErrMsg, sAcct1392Name, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("���[%s]��ȡ΢�ڽ���ػ��˻�������SQLCODE=[%d]" , fpub_GetCompname(lXmlhandle) , iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"��ȡ״̬��Ϣ��");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	
	/* ���ļ� */
	if ((fp=fopen(file_name,"r")) == NULL)  //��ֻ����ʽ�򿪣��ļ��������
	{
		LOG(LM_STD,Fmtmsg("���[%s] ���ļ�ʧ��=[%s]",fpub_GetCompname(lXmlhandle),file_name),"INFO")
		fpub_SetMsg(lXmlhandle, 10001, "�򿪶����ļ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	   
	//��յ����������
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "DELETE FROM yw_wzyh_dzmx WHERE dzrq='%s'" , chk_date);
	iRet = DCIExecuteDirect(sSql);
	
	//ע�⣺����ǿ��ļ����ػ᲻�����-----�����ʱ��ע��һ��
	//ѭ�����ļ�ÿ��Ȼ��Ǽǵ�����
	while (!feof(fp))
	{
		memset(buf,0x00,sizeof(buf));
		fgets(buf,sizeof(buf)-1,fp);
		if (strlen(buf)==0) continue;//��ȡ���˿��л��ߵ������һ��
		LOG(LM_STD,Fmtmsg("�����ļ���ϸ����Ϣ[%s]",buf),"INFO");

		/*���ķ����к�|���Ľ����к�|������ˮ��|��������ʱ��|ҵ������|�˻�����|��������|
		����|���|����|������|����к�|����˺�|�������|�տ�к�|�տ�˺�|
		�տ����|�ӿ�����|������|������ʾ|������ˮ��*/
		p=buf;   //ָ��ᱻ�ظ���ֵ,���������
		memset(&YW_WZYH_DZMX, 0, sizeof(YW_WZYH_DZMX));
		strncpy(YW_WZYH_DZMX.dzrq,chk_date,sizeof(YW_WZYH_DZMX.dzrq)-1);//�ļ�֪ͨ�����������---Ӧ�ú��ļ��������������һ�µģ����ܴ��ڲ�һ�»��������
		trim(YW_WZYH_DZMX.dzrq);
		strncpy(YW_WZYH_DZMX.file_name,file_name,sizeof(YW_WZYH_DZMX.file_name)-1);//������ļ���
		trim(YW_WZYH_DZMX.file_name);
		
		//ȡ�ļ�ÿ������
		strncpy(YW_WZYH_DZMX.snd_organ,strsep(&p,delims),sizeof(YW_WZYH_DZMX.snd_organ)-1);
		trim(YW_WZYH_DZMX.snd_organ);
		strncpy(YW_WZYH_DZMX.rev_organ,strsep(&p,delims),sizeof(YW_WZYH_DZMX.rev_organ)-1);
		trim(YW_WZYH_DZMX.rev_organ);
		strncpy(YW_WZYH_DZMX.business_id,strsep(&p,delims),sizeof(YW_WZYH_DZMX.business_id)-1);
		trim(YW_WZYH_DZMX.business_id);
		strncpy(YW_WZYH_DZMX.transtime,strsep(&p,delims),sizeof(YW_WZYH_DZMX.transtime)-1);
		trim(YW_WZYH_DZMX.transtime);
		strncpy(YW_WZYH_DZMX.business_type,strsep(&p,delims),sizeof(YW_WZYH_DZMX.business_type)-1);
		trim(YW_WZYH_DZMX.business_type);
		strncpy(YW_WZYH_DZMX.acct_type,strsep(&p,delims),sizeof(YW_WZYH_DZMX.acct_type)-1);
		trim(YW_WZYH_DZMX.acct_type);
		strncpy(YW_WZYH_DZMX.work_date,strsep(&p,delims),sizeof(YW_WZYH_DZMX.work_date)-1);
		trim(YW_WZYH_DZMX.work_date);
		strncpy(YW_WZYH_DZMX.scene_no,strsep(&p,delims),sizeof(YW_WZYH_DZMX.scene_no)-1);
		trim(YW_WZYH_DZMX.scene_no);
		
		//���׽�����⴦��
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_DZMX.amount = atof(sBuf)/100;
		strncpy(YW_WZYH_DZMX.ccy,strsep(&p,delims),sizeof(YW_WZYH_DZMX.ccy)-1);
		trim(YW_WZYH_DZMX.ccy);
		
		//�������������⴦��
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_DZMX.fee_amount = atof(sBuf)/100;
		strncpy(YW_WZYH_DZMX.payer_opbk,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payer_opbk)-1);
		trim(YW_WZYH_DZMX.payer_opbk);
		strncpy(YW_WZYH_DZMX.payer_acct,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payer_acct)-1);
		trim(YW_WZYH_DZMX.payer_acct);
		strncpy(YW_WZYH_DZMX.payer_name,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payer_name)-1);
		trim(YW_WZYH_DZMX.payer_name);
		strncpy(YW_WZYH_DZMX.payee_opbk,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payee_opbk)-1);
		trim(YW_WZYH_DZMX.payee_opbk);
		strncpy(YW_WZYH_DZMX.payee_acct,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payee_acct)-1);
		trim(YW_WZYH_DZMX.payee_acct);
		strncpy(YW_WZYH_DZMX.payee_name,strsep(&p,delims),sizeof(YW_WZYH_DZMX.payee_name)-1);
		trim(YW_WZYH_DZMX.payee_name);
		strncpy(YW_WZYH_DZMX.tran_type,strsep(&p,delims),sizeof(YW_WZYH_DZMX.tran_type)-1);
		trim(YW_WZYH_DZMX.tran_type);
		strncpy(YW_WZYH_DZMX.deal_flag,strsep(&p,delims),sizeof(YW_WZYH_DZMX.deal_flag)-1);
		trim(YW_WZYH_DZMX.deal_flag);
		strncpy(YW_WZYH_DZMX.cz_flag,strsep(&p,delims),sizeof(YW_WZYH_DZMX.cz_flag)-1);
		trim(YW_WZYH_DZMX.cz_flag);
		strncpy(YW_WZYH_DZMX.cz_business_id,strsep(&p,delims),sizeof(YW_WZYH_DZMX.cz_business_id)-1);
		trim(YW_WZYH_DZMX.cz_business_id);
		
		if (memcmp(YW_WZYH_DZMX.tran_type , "01" , 2) == 0)
		{	/* �깺 */
			memset(YW_WZYH_DZMX.payee_acct , 0x00 , sizeof(YW_WZYH_DZMX.payee_acct));
			memset(YW_WZYH_DZMX.payee_name , 0x00 , sizeof(YW_WZYH_DZMX.payee_name));
			memcpy(YW_WZYH_DZMX.payee_acct , sAcct2622 , strlen(sAcct2622));
			memcpy(YW_WZYH_DZMX.payee_name , sAcct2622Name , strlen(sAcct2622Name));
		}
		else /* ��� */
		{
			memset(YW_WZYH_DZMX.payer_acct , 0x00 , sizeof(YW_WZYH_DZMX.payee_acct));
			memset(YW_WZYH_DZMX.payer_name , 0x00 , sizeof(YW_WZYH_DZMX.payee_name));
			memcpy(YW_WZYH_DZMX.payer_acct , sAcct1392 , strlen(sAcct1392));
			memcpy(YW_WZYH_DZMX.payer_name , sAcct1392Name , strlen(sAcct1392Name));
		}
		
		//���˱�־��ʼ��Ϊ0
		strncpy(YW_WZYH_DZMX.dz_flag , "0" , sizeof(YW_WZYH_DZMX.dz_flag)-1);
		trim(YW_WZYH_DZMX.dz_flag); 
		p = NULL;//ָ����Ϊ��
		
		cnt++;
		amt = amt + YW_WZYH_DZMX.amount;
		
		if(memcmp(YW_WZYH_DZMX.business_id , "18012532358400088800000000142687" , strlen("18012532358400088800000000142687")) == 0)
			YW_WZYH_DZMX.amount = 126;
			
		if((memcmp(YW_WZYH_DZMX.business_id , "18012532358400088800000000075519" , strlen("18012532358400088800000000075519")) == 0) ||
			(memcmp(YW_WZYH_DZMX.business_id , "18012532358400088800000000142742" , strlen("18012532358400088800000000142742")) == 0)
		)
			continue;
		
		/*����΢����������ϸ��*/
		LOG(LM_STD,Fmtmsg("����΢����������ϸ��"), "INFO");
		iRet=DBInsert("YW_WZYH_DZMX", SD_YW_WZYH_DZMX ,NUMELE(SD_YW_WZYH_DZMX), &YW_WZYH_DZMX, sErrMsg);
		if ( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("����΢����������ϸ��sqlca.sqlcode=[%d] , sErrMsg[%s]",iRet , sErrMsg),"DEBUG");
			fclose(fp);  //�ر��ļ�ָ��
			DCIRollback();  //���ݿ�ع�
			fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,"����΢����������ϸ��ʧ��");
			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,"����΢����������ϸ��ʧ��","ERROR");
		}
		
		//cnt++;
		//amt = amt + YW_WZYH_DZMX.amount;	
	}
    DCICommit();
    fclose(fp);  //�ر��ļ�ָ��
	
	/* �ܱ��� */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/wzyh/ggbody/file_line_count", sBuf)
	LOG(LM_STD,Fmtmsg("fcnt[%s]" , sBuf),"INFO");
	fcnt = atoi(sBuf);
	
	/* �ܽ�� */
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_SOFTGETXML("/wzyh/ggbody/total_amount", sBuf)
	LOG(LM_STD,Fmtmsg("famt[%s]" , sBuf),"INFO");
	famt = atof(sBuf);
	
	LOG(LM_STD,Fmtmsg("cnt[%d],fcnt[%d],amt[%f],famt[%f]" , cnt , fcnt , amt , famt ),"INFO");
	if((cnt!=fcnt) || (abs(amt*100-famt)>0.000001))
	{
		LOG(LM_STD,Fmtmsg("���������������ܽ����������ݿ��е����ݲ���"),"DEBUG");
		fpub_SetMsg(lXmlhandle, 10001, "���������������ܽ����������ݿ��е����ݲ���");
		//fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}

#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "")
#endif

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/********************************************************************
���ע�����ƣ�WZYH_LOAD_LCMXFILE
����������ƣ�WZYH_LOAD_LCMXFILE
����������壺
����������ܣ�����΢���������ϸ�ļ�
������ò�����
    ���    ��������    ��Դ���    ȱʡֵ    �Ƿ�ɿ�    ����˵��
������״̬��
    ״̬    ���˵��
�� Ŀ �飺
�� �� Ա��txbdir
�������ڣ�20171107
�޸����ڣ�
*********************************************************************/
IRESULT WZYH_LOAD_LCMXFILE(HXMLTREE lXmlhandle)
{
	char wjrq[10+1];   //�ļ�����
	char sTmp[256];          //ȡ��������(Ҫ�����һ��)
	char file_name[140+1];   //�����ļ�·��(���ȫ·��)
	char buf[1024], sSql[1024];          //����ļ�ÿһ������
	FILE *fp;                //�ļ�ָ��
	char delims[]="|";       //ÿ�����ÿһ�зָ���
	char *p = NULL;          //ÿһ�����ݵĴ��ָ��
	char sBuf[256], sErrMsg[256];          //��Ž��temp
	int i=0 , iRet;                 //����ȥ����һ��
	SDB_YW_WZYH_LCMX YW_WZYH_LCMX;
	
	fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
	LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
#endif    
  
	/*����1*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(1, sTmp, "�ļ�����");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("�ļ�����"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�ļ����ڲ���Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(wjrq,0,sizeof(wjrq));
	strcpy(wjrq, sTmp);
	LOG(LM_STD,Fmtmsg("�ļ����� [%s] ",wjrq), "INFO");
	
	/*����2*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(2, sTmp, "�����ϸ�ļ�ȫ·��");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("�����ϸ�ļ�ȫ·��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�����ϸ�ļ�ȫ·������Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(file_name,0,sizeof(file_name));
	strcpy(file_name, sTmp);
	LOG(LM_STD,Fmtmsg("�����ϸ�ļ�ȫ·�� [%s] ",file_name), "INFO");
	
	
	/* ���ļ� */
	if ((fp=fopen(file_name,"r")) == NULL)  //��ֻ����ʽ�򿪣��ļ��������
	{
		LOG(LM_STD,Fmtmsg("���[%s] �������ϸ�ļ�ʧ��=[%s]",fpub_GetCompname(lXmlhandle),file_name),"INFO")
		fpub_SetMsg(lXmlhandle, 10001, "�������ϸ�ļ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	//��յ����������
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "DELETE FROM YW_WZYH_LCMX WHERE wjrq='%s'" , wjrq);
	iRet = DCIExecuteDirect(sSql);
	DCICommit();
	  
	//ע�⣺����ǿ��ļ����ػ᲻�����-----�����ʱ��ע��һ��
	//ѭ�����ļ�ÿ��Ȼ��Ǽǵ�����
	while (!feof(fp))
	{
		i++;
		
		memset(buf,0x00,sizeof(buf));
		fgets(buf,sizeof(buf)-1,fp);
		if (strlen(buf)==0) continue;//��ȡ���˿��л��ߵ������һ��
		LOG(LM_STD,Fmtmsg("�����ϸ�ļ�����Ϣ[%s]",buf),"INFO");
		
		if(i==1&&strlen(buf)>0)continue;//Խ����һ��
		
		/*ҵ����ˮ��|������ˮ��|ԭ������ˮ��|��������|����ʱ��|��������|���׽��|���׷ݶ�|�ͻ�����|֤������|֤������|��Ʒ����|��Ʒ����*/
		p=buf;   //ָ��ᱻ�ظ���ֵ,���������
		memset(&YW_WZYH_LCMX, 0, sizeof(YW_WZYH_LCMX));
		strncpy(YW_WZYH_LCMX.wjrq,wjrq,sizeof(YW_WZYH_LCMX.wjrq)-1);//�ļ�֪ͨ�����������---Ӧ�ú��ļ��������������һ�µģ����ܴ��ڲ�һ�»��������
		trim(YW_WZYH_LCMX.wjrq);
		strncpy(YW_WZYH_LCMX.file_name,file_name,sizeof(YW_WZYH_LCMX.file_name)-1);//���ļ���
		trim(YW_WZYH_LCMX.file_name);
		
		//ȡ�ļ�ÿ������
		strncpy(YW_WZYH_LCMX.yw_business,strsep(&p,delims),sizeof(YW_WZYH_LCMX.yw_business)-1);
		trim(YW_WZYH_LCMX.yw_business);
		strncpy(YW_WZYH_LCMX.business_id,strsep(&p,delims),sizeof(YW_WZYH_LCMX.business_id)-1);
		trim(YW_WZYH_LCMX.business_id);
		strncpy(YW_WZYH_LCMX.oribusiness_id,strsep(&p,delims),sizeof(YW_WZYH_LCMX.oribusiness_id)-1);
		trim(YW_WZYH_LCMX.oribusiness_id);
		strncpy(YW_WZYH_LCMX.jyrq,strsep(&p,delims),sizeof(YW_WZYH_LCMX.jyrq)-1);
		trim(YW_WZYH_LCMX.jyrq);
		strncpy(YW_WZYH_LCMX.transtime,strsep(&p,delims),sizeof(YW_WZYH_LCMX.transtime)-1);
		trim(YW_WZYH_LCMX.transtime);
		strncpy(YW_WZYH_LCMX.business_type,strsep(&p,delims),sizeof(YW_WZYH_LCMX.business_type)-1);
		trim(YW_WZYH_LCMX.business_type);
		//���׽�����⴦��
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_LCMX.amount = atof(sBuf);
		//���׷ݶ����⴦��
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_LCMX.jy_num = atof(sBuf);
		strncpy(YW_WZYH_LCMX.cust_name,strsep(&p,delims),sizeof(YW_WZYH_LCMX.cust_name)-1);
		trim(YW_WZYH_LCMX.cust_name);
		strncpy(YW_WZYH_LCMX.cert_type,strsep(&p,delims),sizeof(YW_WZYH_LCMX.cert_type)-1);
		trim(YW_WZYH_LCMX.cert_type);
		strncpy(YW_WZYH_LCMX.cert_id,strsep(&p,delims),sizeof(YW_WZYH_LCMX.cert_id)-1);
		trim(YW_WZYH_LCMX.cert_id);
		strncpy(YW_WZYH_LCMX.product_id,strsep(&p,delims),sizeof(YW_WZYH_LCMX.product_id)-1);
		trim(YW_WZYH_LCMX.product_id);
		strncpy(YW_WZYH_LCMX.product_name,strsep(&p,delims),sizeof(YW_WZYH_LCMX.product_name)-1);
		trim(YW_WZYH_LCMX.product_name);
		strncpy(YW_WZYH_LCMX.status,strsep(&p,delims),sizeof(YW_WZYH_LCMX.status)-1);
		trim(YW_WZYH_LCMX.status);
		p=NULL;//ָ����Ϊ��
		
		/*YW_WZYH_LCMX�ı�עû�и�ֵ���������г�ʼ����*/
		/*����΢���������ϸ�ļ���*/
		LOG(LM_STD,Fmtmsg("����΢���������ϸ�ļ���"), "INFO");
		iRet=DBInsert("YW_WZYH_LCMX", SD_YW_WZYH_LCMX ,NUMELE(SD_YW_WZYH_LCMX), &YW_WZYH_LCMX, sErrMsg);
		if ( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("����΢���������ϸ�ļ���sqlca.sqlcode=[%d]", iRet),"DEBUG");
			fclose(fp);  //�ر��ļ�ָ��
			DCIRollback();  //���ݿ�ع�
			fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,"����΢���������ϸ�ļ���ʧ��");
			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,"����΢���������ϸ�ļ���ʧ��","ERROR");
		}
		
		DCICommit();
	  }
    
    fclose(fp);  //�ر��ļ�ָ��
#ifdef DEBUG
    LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "")
#endif
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/********************************************************************
���ע�����ƣ�WZYH_LOAD_BYLMXFILE
����������ƣ�WZYH_LOAD_BYLMXFILE
����������壺
����������ܣ�����΢�����������ļ�
������ò�����
    ���    ��������    ��Դ���    ȱʡֵ    �Ƿ�ɿ�    ����˵��
������״̬��
    ״̬    ���˵��
�� Ŀ �飺
�� �� Ա��sgy
�������ڣ�20170921
�޸����ڣ�
*********************************************************************/
IRESULT WZYH_LOAD_BYLMXFILE(HXMLTREE lXmlhandle)
{
	char wjrq[10+1];   //�ļ�����
	SDB_YW_WZYH_BYLMX YW_WZYH_BYLMX;
	char sTmp[256], sSql[256], sErrMsg[256];          //ȡ��������(Ҫ�����һ��)
	char file_name[140+1];   //�����ļ�·��(���ȫ·��)
	char buf[1024];          //����ļ�ÿһ������
	FILE *fp;                //�ļ�ָ��
	char delims[]="|";       //ÿ�����ÿһ�зָ���
	char *p = NULL;          //ÿһ�����ݵĴ��ָ��
	char sBuf[256];          //��Ž��temp
	int i=0, iRet;                 //����ȥ����һ��     
	
	fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
	LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
#endif

	/*����1*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(1, sTmp, "�ļ�����");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("�ļ�����"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�ļ����ڲ���Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(wjrq,0,sizeof(wjrq));
	strcpy(wjrq, sTmp);
	LOG(LM_STD,Fmtmsg("�ļ����� [%s] ",wjrq), "INFO");
	
	/*����2*/
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(2, sTmp, "�������ļ�ȫ·��");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("�������ļ�ȫ·��"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�������ļ�ȫ·������Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(file_name,0,sizeof(file_name));
	strcpy(file_name, sTmp);
	LOG(LM_STD,Fmtmsg("�������ļ�ȫ·�� [%s] ",file_name), "INFO");	
	
	/* ���ļ� */
	if ((fp=fopen(file_name,"r")) == NULL)  //��ֻ����ʽ�򿪣��ļ��������
	{
		LOG(LM_STD,Fmtmsg("���[%s] �򿪱������ļ�ʧ��=[%s]",fpub_GetCompname(lXmlhandle),file_name),"INFO")
		fpub_SetMsg(lXmlhandle, 10001, "�򿪱������ļ�ʧ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	
	//��յ����������
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "DELETE FROM YW_WZYH_BYLMX WHERE wjrq='%s'" , wjrq);
	iRet = DCIExecuteDirect(sSql);
	DCICommit();
	
	//ע�⣺����ǿ��ļ����ػ᲻�����-----�����ʱ��ע��һ��
	//ѭ�����ļ�ÿ��Ȼ��Ǽǵ�����
	while (!feof(fp))
	{
		i++;
		
		memset(buf, 0x00, sizeof(buf));
		fgets(buf, sizeof(buf)-1 ,fp);
		if (strlen(buf) == 0) continue;//��ȡ���˿��л��ߵ������һ��
		LOG(LM_STD,Fmtmsg("�������ļ�����Ϣ[%s]",buf),"INFO");
		
		if(i==1 && strlen(buf)>0)continue;//Խ����һ��
		
		/*ͳ������|��Ʒ����|��Ʒ�ܷݶ�|��Ʒ��ֵ*/
		p=buf;   //ָ��ᱻ�ظ���ֵ,���������
		memset(&YW_WZYH_BYLMX, 0, sizeof(YW_WZYH_BYLMX));
		strncpy(YW_WZYH_BYLMX.wjrq,wjrq,sizeof(YW_WZYH_BYLMX.wjrq)-1);//�ļ�֪ͨ�����������---Ӧ�ú��ļ��������������һ�µģ����ܴ��ڲ�һ�»��������
		trim(YW_WZYH_BYLMX.wjrq);
		strncpy(YW_WZYH_BYLMX.file_name,file_name,sizeof(YW_WZYH_BYLMX.file_name)-1);//���ļ���
		trim(YW_WZYH_BYLMX.file_name);
		
		//ȡ�ļ�ÿ������
		strncpy(YW_WZYH_BYLMX.tjrq,strsep(&p,delims),sizeof(YW_WZYH_BYLMX.tjrq)-1);
		trim(YW_WZYH_BYLMX.tjrq);
		strncpy(YW_WZYH_BYLMX.product_id,strsep(&p,delims),sizeof(YW_WZYH_BYLMX.product_id)-1);
		trim(YW_WZYH_BYLMX.product_id);
		//��Ʒ�ܷݶ����⴦��
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_BYLMX.product_amount = atof(sBuf);
		//��Ʒ��ֵ���⴦��
		memset(sBuf,0x00,sizeof(sBuf));
		strncpy(sBuf,strsep(&p,delims),sizeof(sBuf)-1);
		YW_WZYH_BYLMX.product_net_amount = atof(sBuf);
		p=NULL;//ָ����Ϊ��
		/*YW_WZYH_BYLMX�ı�עû�и�ֵ���������г�ʼ����*/
		/*����΢�����������ļ���*/
		LOG(LM_STD,Fmtmsg("����΢�����������ļ���"), "INFO");
		iRet=DBInsert("YW_WZYH_BYLMX", SD_YW_WZYH_BYLMX ,NUMELE(SD_YW_WZYH_BYLMX), &YW_WZYH_BYLMX, sErrMsg);
		if ( iRet < 0 )
		{
			LOG(LM_STD,Fmtmsg("����΢�����������ļ���sqlca.sqlcode=[%d]", iRet),"DEBUG");
			fclose(fp);  //�ر��ļ�ָ��
			DCIRollback();  //���ݿ�ع�
			fpub_SetMsg(lXmlhandle,MID_SYS_COMPEXEC,"����΢�����������ļ���ʧ��");
			fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
			LOGRET(COMPRET_FAIL,LM_STD,"����΢�����������ļ���ʧ��","ERROR");
		}
		
		DCICommit();
	  }
    
    fclose(fp);  //�ر��ļ�ָ��
#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "")
#endif

	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
	return COMPSTATUS_SUCC;
}

/********************************************************************
���ע�����ƣ�WZYH_CHK_NOTE
����������ƣ�WZYH_CHK_NOTE
����������壺
����������ܣ�΢������Ķ���
������ò�����
    ���    ��������    ��Դ���    ȱʡֵ    �Ƿ�ɿ�    ����˵��
������״̬��
    ״̬    ���˵��
�� Ŀ �飺
�� �� Ա��sgy
�������ڣ�20171107
�޸����ڣ�
*********************************************************************/
IRESULT WZYH_CHK_NOTE(HXMLTREE lXmlhandle)
{
	char chk_date[10+1];   //��������
	char qsjg[14+1], sSql[1024], sErrMsg[256];   //�������
	char dzstate[2+1];  //����״̬
	SDB_YW_WZYH_DZJG   YW_WZYH_DZJG;//���˽����
	char sTmp[256];          //ȡ��������(Ҫ�����һ��)
	int iRet=0;              //��ŷ���ֵ
	
	fpub_InitSoComp(lXmlhandle);
#ifdef DEBUG
	LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")
#endif
    
	/*����1*/
	//ȡ��������
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(1, sTmp, "��������");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("��������"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�������ڲ���Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(chk_date,0,sizeof(chk_date));
	strcpy(chk_date, sTmp);
	LOG(LM_STD,Fmtmsg("�������� [%s] ",chk_date), "INFO");	
	
	/*����2*/
	//ȡ�������
	memset(sTmp,0,sizeof(sTmp));
	COMP_GETPARSEPARAS(2, sTmp, "�������");
	if (0 == strlen(sTmp))
	{
		LOG(LM_STD, Fmtmsg("�������"), "DEBUG")
		fpub_SetMsg(lXmlhandle, 10001, "�����������Ϊ��");
		fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
		return COMPSTATUS_FAIL;
	}
	memset(qsjg,0,sizeof(qsjg));
	strcpy(qsjg, sTmp);
	LOG(LM_STD,Fmtmsg("������� [%s] ",qsjg), "INFO");
	
	//��ȡ��ǰ����״̬
	memset(dzstate,0,sizeof(dzstate));
	memset(dzstate,0,sizeof(dzstate));
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "SELECT DZSTATE FROM YW_WZYH_DZKZ WHERE qsrq='%s'" , chk_date);
	LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
	iRet = DBSelectToVarChar(sErrMsg, dzstate, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("���[%s]��ȡ״̬��Ϣ��[%s][%s] SQLCODE=[%d]",fpub_GetCompname(lXmlhandle),qsjg,chk_date, iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"��ȡ״̬��Ϣ��");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	
	/* �������Ķ����Ƿ���� */
	if (dzstate[0] != '1')
	{	
		//���¶��˿��Ʊ�״̬
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE YW_WZYH_DZKZ set DZSTATE='3' , DZMSG='΢��������Ķ������ڽ���' WHERE qsrq='%s'" , chk_date);
		iRet = DCIExecuteDirect(sSql);
		if (iRet < 0)
		{
			LOG(LM_DEBUG,Fmtmsg("���[%s]�޸Ķ���״̬��[%s][%s] SQLCODE=[%d]",fpub_GetCompname(lXmlhandle),qsjg,chk_date, iRet),"")
			fpub_SetMsg(lXmlhandle,9000,"�޸Ķ���״̬��");
			DCIRollback();
			fpub_SetCompStatus(lXmlhandle,-1);
			return -1;
		}
		DCICommit();
    
        /*����Ķ���*/
        iRet = Process_CHKWDLCOREBAK(lXmlhandle,qsjg,chk_date);
        if (iRet !=0)
        {
            fpub_SetMsg(lXmlhandle,9000, "΢��������Ķ��˴�");
			memset(sSql , 0x00 , sizeof(sSql));
			sprintf(sSql , "UPDATE YW_WZYH_DZKZ set DZSTATE='2',DZMSG='΢��������Ķ��˴�' WHERE qsrq='%s'" , chk_date);
			iRet = DCIExecuteDirect(sSql);
			DCICommit();
            fpub_SetCompStatus(lXmlhandle,-1);
            return -1;
        }
		LOG(LM_DEBUG,Fmtmsg("΢��������Ķ������"),"")        

		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE YW_WZYH_DZKZ set DZSTATE='1', DZMSG='΢��������Ķ������' WHERE qsrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DCIExecuteDirect(sSql);
		if (iRet < 0)
		{
			LOG(LM_DEBUG,Fmtmsg("���[%s]�޸Ķ���״̬��[%s][%s] SQLCODE=[%d]",fpub_GetCompname(lXmlhandle),qsjg,chk_date, iRet),"")
			fpub_SetMsg(lXmlhandle,9000,"�޸Ķ���״̬��");
			DCIRollback();
			fpub_SetCompStatus(lXmlhandle,-1);
			return -1;
		}
		DCICommit();
        
		/*���¶��˽����----΢�������Ի����*/
		/*��ɾ��������˽�����ٲ���*/
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , " DELETE FROM YW_WZYH_DZJG WHERE qsrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DCIExecuteDirect(sSql);
		DCICommit();
		
		memset(&YW_WZYH_DZJG, 0x00, sizeof(YW_WZYH_DZJG));
		memcpy(YW_WZYH_DZJG.product_buy_num, "0", 1); 
		memcpy(YW_WZYH_DZJG.product_back_num, "0", 1);
		YW_WZYH_DZJG.product_buy_amount=0.00; 
		YW_WZYH_DZJG.product_back_amount=0.00; 
		
		/* ��������Զ���ƽ�ļ�¼����ͳ��д����˽���� */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(dz_flag),0)), char(COALESCE(SUM(amount),0)) FROM YW_WZYH_DZMX WHERE dzrq='%s' and tran_type='01' and dz_flag='1'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		memset(sTmp , 0x00 , sizeof(sTmp));
		iRet = DBSelectToMultiVar(sErrMsg , sSql , YW_WZYH_DZJG.product_buy_num, sTmp);
		if (iRet < 0)
		{
			LOG(LM_STD, Fmtmsg("΢����������ϸ���ѯʧ��[%d] , sErrMsg[%s]", iRet , sErrMsg), "DEBUG")
			fpub_SetMsg(lXmlhandle,9000,"΢����������ϸ���ѯʧ��");
			DCIRollback();
			fpub_SetCompStatus(lXmlhandle,-1);
			return -1;
		}
		YW_WZYH_DZJG.product_buy_amount = atof(sTmp);
		LOG(LM_STD, Fmtmsg("΢�������˽����, product_buy_num[%s] , product_buy_amount[%f] , sTmp[%s] , iRet[%d]", YW_WZYH_DZJG.product_buy_num , YW_WZYH_DZJG.product_buy_amount , sTmp , iRet), "DEBUG")
		
		memset(sSql , 0x00 , sizeof(sSql));
		memset(sTmp , 0x00 , sizeof(sTmp));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(dz_flag),0)), char(COALESCE(SUM(amount),0)) FROM YW_WZYH_DZMX WHERE dzrq='%s' and tran_type='02' and dz_flag='1'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DBSelectToMultiVar(sErrMsg , sSql , YW_WZYH_DZJG.product_back_num, sTmp);    
		if (iRet < 0)
		{
			LOG(LM_STD, Fmtmsg("΢����������ϸ���ѯʧ��[%d]", iRet), "DEBUG")
			fpub_SetMsg(lXmlhandle,9000,"΢����������ϸ���ѯʧ��");
			DCIRollback();
			fpub_SetCompStatus(lXmlhandle,-1);
			return -1;
		}
		YW_WZYH_DZJG.product_back_amount = atof(sTmp);
		trim(YW_WZYH_DZJG.product_buy_num);
		trim(YW_WZYH_DZJG.product_back_num);
		
		memcpy(YW_WZYH_DZJG.qsjg, qsjg, sizeof(YW_WZYH_DZJG.qsjg)-1); 
		memcpy(YW_WZYH_DZJG.qsrq, chk_date, sizeof(YW_WZYH_DZJG.qsrq)-1);
		memcpy(YW_WZYH_DZJG.dzmsg, "���˳ɹ�,��δ����", 17);
		memcpy(YW_WZYH_DZJG.dz_bz, "1", 17);
		
		//����YW_WZYH_DZJG��
		iRet=DBInsert("YW_WZYH_DZJG", SD_YW_WZYH_DZJG ,NUMELE(SD_YW_WZYH_DZJG), &YW_WZYH_DZJG, sErrMsg);
		if (iRet < 0)
		{			
			LOG(LM_STD, Fmtmsg("������˽����ʧ��[%d]", iRet), "DEBUG")
			fpub_SetMsg(lXmlhandle,9000,"������˽����ʧ��");
			DCIRollback();
			fpub_SetCompStatus(lXmlhandle,-1);
			return -1;
		}
		
		/* ������أ�΢���٣����Ķ� ���޼�¼��ˮ */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(*),0)) FROM YW_WZYH_ERRMX WHERE subtrantype='0002' AND lsbz='1' AND errflag='3' AND jyrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		memset(sTmp , 0x00 , sizeof(sTmp));
		iRet = DBSelectToMultiVar(sErrMsg , sSql , sTmp);
		LOG(LM_STD,Fmtmsg("iRet[%d] , sTmp[%s] " , iRet , sTmp), "INFO");
		if (iRet >=0)
		{
			if (sTmp[0] != '0')
			{
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , "INSERT INTO yw_wzyh_ywls (jyrq , flag , business_id , waiblius , hxxym , pay_tran_status , amount , hxdzbz , payer_acct , payer_name , payee_acct , payee_name , tran_type) SELECT '%s' , '0' , waiblius , waiblius ,  '000000' , '0000' , coreamount , 3 , payer_acct , payer_name , payee_acct , payee_name , '02' FROM yw_wzyh_errmx WHERE subtrantype='0002' AND lsbz='1' AND errflag='3' AND jyrq='%s'" , chk_date , chk_date);
				LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
				iRet = DCIExecuteDirect(sSql);
			}
		}
		
		/* ������أ�΢�ڶ࣬������ ���޼�¼��ˮ */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(*),0)) FROM YW_WZYH_ERRMX WHERE subtrantype='0002' AND lsbz='1' AND errflag='2' AND jyrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		memset(sTmp , 0x00 , sizeof(sTmp));
		iRet = DBSelectToMultiVar(sErrMsg , sSql , sTmp);
		LOG(LM_STD,Fmtmsg("iRet[%d] , sTmp[%s] " , iRet , sTmp), "INFO");
		if (iRet >=0)
		{
			if (sTmp[0] != '0')
			{
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , "INSERT INTO yw_wzyh_ywls (jyrq , flag , business_id , waiblius , hxxym , pay_tran_status , amount , hxdzbz , tzzt , beiy1 , payer_acct , payer_name , payee_acct , payee_name , tran_type) SELECT '%s' , '0' , business_id , '10002'|| '%s' || right(business_id , 14) ,  '000000' , '0000' , amount , '1' , '1' , '%s�Զ�����' , payer_acct , payer_name , payee_acct , payee_name , '02' FROM yw_wzyh_errmx WHERE subtrantype='0002' AND lsbz='1' AND errflag='2' AND jyrq='%s'" , chk_date , chk_date , chk_date , chk_date);
				LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
				iRet = DCIExecuteDirect(sSql);
			}
		}

		/* �����깺,΢�ڶ࣬������ ������ˮ��¼ */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(*),0)) FROM YW_WZYH_ERRMX WHERE subtrantype='0001' AND lsbz='1' AND errflag='2' AND jyrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		memset(sTmp , 0x00 , sizeof(sTmp));
		iRet = DBSelectToMultiVar(sErrMsg , sSql , sTmp);
		LOG(LM_STD,Fmtmsg("iRet[%d] , sTmp[%s] " , iRet , sTmp), "INFO");
		if (iRet >=0)
		{
			if (sTmp[0] != '0')
			{
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , "INSERT INTO yw_wzyh_ywls (jyrq , flag , business_id , waiblius , hxxym , pay_tran_status , amount , hxdzbz , tzzt , beiy1 , payer_acct , payer_name , payee_acct , payee_name , czflag , tran_type) SELECT '%s' , '1' , business_id , '10002'|| '%s' || right(business_id , 14) ,  '000000' , '0000' , amount , '1' , '1' , '%s�Զ�����' , payer_acct , payer_name , payee_acct , payee_name , '1' , '01' FROM yw_wzyh_errmx WHERE subtrantype='0001' AND lsbz='1' AND errflag='2' AND jyrq='%s'" , chk_date , chk_date , chk_date , chk_date);
				LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
				iRet = DCIExecuteDirect(sSql);
			}
		}
		
		/* �깺��΢���٣����Ķ࣬����ˮ��¼ */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "SELECT char(COALESCE(COUNT(*),0)) FROM YW_WZYH_ERRMX WHERE subtrantype='0001' AND lsbz='1' AND errflag='3' AND jyrq='%s'" , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		memset(sTmp , 0x00 , sizeof(sTmp));
		iRet = DBSelectToMultiVar(sErrMsg , sSql , sTmp);
		LOG(LM_STD,Fmtmsg("iRet[%d] , sTmp[%s] " , iRet , sTmp), "INFO");
		if (iRet >=0)
		{
			if (sTmp[0] != '0')
			{
				memset(sSql , 0x00 , sizeof(sSql));
				sprintf(sSql , "INSERT INTO yw_wzyh_ywls (jyrq , flag , business_id , waiblius , hxxym , pay_tran_status , amount , hxdzbz , payer_acct , payer_name , payee_acct , payee_name , czflag , tran_type , tzzt , beiy1) SELECT '%s' , '1' , waiblius , waiblius ,  '000000' , '0000' , coreamount , 1 , payer_acct , payer_name , payee_acct , payee_name , '1' , '01' , '1' , '%s�Զ�����' FROM yw_wzyh_errmx WHERE subtrantype='0001' AND lsbz='1' AND errflag='3' AND jyrq='%s'" , chk_date , chk_date , chk_date);
				LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
				iRet = DCIExecuteDirect(sSql);
			}
		}
		
		/* ������أ�΢�ڶ࣬������ ����Ҫ���� */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE yw_wzyh_ywls SET hxdzbz='1' , beiy2=hxxym , beiy1='ϵͳ�޸�%s' , hxxym='000000' , pay_tran_status='0000' , czflag='' , tzzt='1' WHERE flag='0' AND hxdzbz='2' AND jyrq='%s'" , chk_date , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DCIExecuteDirect(sSql);
		
		/* �����깺��(΢�ڶ࣬������) , (΢���٣����Ķ�) ����Ҫ���� */
		/*memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE yw_wzyh_ywls SET hxdzbz='1' , czflag='1' ,  beiy2=hxdzbz , beiy1='ϵͳ�޸�%s' WHERE flag='1' AND hxdzbz IN('2' , '3') AND jyrq='%s' AND flag='1'" , chk_date , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DCIExecuteDirect(sSql);	*/

		/* ���²����ϸ�����޺�����ˮ�ֶ� */
		memset(sSql , 0x00 , sizeof(sSql));
		sprintf(sSql , "UPDATE yw_wzyh_errmx SET waiblius= '10002'|| '%s'|| right(business_id , 14) WHERE lsbz='1' AND errflag='2' AND jyrq='%s'" , chk_date , chk_date);
		LOG(LM_STD,Fmtmsg("sSql[%s] " , sSql), "INFO");
		iRet = DCIExecuteDirect(sSql);	
		
		DCICommit(); 
   }

#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "")
#endif

	DCICommit(); 

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPSTATUS_SUCC;
}

/********************************************************************
���ע�����ƣ�WZYH_GETCOREFILE
����������ƣ�WZYH_GETCOREFILE
����������壺
����������ܣ����غ��Ķ����ļ�
������ò�����
    ���    ��������    ��Դ���    ȱʡֵ    �Ƿ�ɿ�    ����˵��
������״̬��
    ״̬    ���˵��
�� Ŀ �飺
�� �� Ա��txbdir
�������ڣ�20171107
�޸����ڣ�
*********************************************************************/
IRESULT WZYH_GETCOREFILE(HXMLTREE lXmlhandle)
{
	SDB_YW_WZYH_COREMX stWzyhCoremx; 
	int iParas, iRet;
	double dAmt = 0.00;
	char sQshh[12+1];
	char sQsrq[8+1] , sSql[256], sErrMsg[256];
	char sFileName[100+1];
	char sBuf[200+1];
	char sBuffer[800] , *pBuffer;
	char systime[20] , *p;
	char cCoreStat[2];
	char sDqszh[32];
	char sYzzh[32];
	FILE *fp = NULL;
	
	memset(&stWzyhCoremx, 0x00, sizeof(stWzyhCoremx));
	memset(sQshh, 0x00, sizeof(sQshh));
	memset(sQsrq, 0x00, sizeof(sQsrq));
	memset(sFileName, 0x00, sizeof(sFileName));
	memset(sBuf, 0x00, sizeof(sBuf));
	memset(sBuffer, 0x00, sizeof(sBuffer));
	memset(systime, 0x00, sizeof(systime));
	memset(cCoreStat, 0x00, sizeof(cCoreStat));
	
	fpub_InitSoComp(lXmlhandle);
	
	LOG(LM_DEBUG,Fmtmsg("���[%s]ִ�п�ʼ",fpub_GetCompname(lXmlhandle)),"")  
	
	/*3������*/
	COMP_PARACOUNTCHK(3)
	
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_GETPARSEPARAS(1, sBuf, "�������")
	pstrcopy(sQshh, sBuf, sizeof(sQshh));
	
	memset(sBuf,0x00,sizeof(sBuf));
	COMP_GETPARSEPARAS(2,sBuf,"��������")
	pstrcopy(sQsrq, sBuf, sizeof(sQsrq));
	
	memset(sBuf, 0x00, sizeof(sBuf));
	COMP_GETPARSEPARAS(3, sBuf, "�����ļ���")
	pstrcopy(sFileName, sBuf, sizeof(sFileName));
	
	LOG(LM_DEBUG,Fmtmsg("���������[%s]�������ڣ�[%s]�����ļ�����[%s]", sQshh, sQsrq, sFileName),"")
	
	//��ȡ���ɻ�
	memset(sDqszh,0,sizeof(sDqszh));
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_DQSZH'");
	iRet = DBSelectToVarChar(sErrMsg, sDqszh, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("���[%s]��ȡ�������˻���SQLCODE=[%d]",fpub_GetCompname(lXmlhandle),iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"��ȡ״̬��Ϣ��");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	trim(sDqszh);
	LOG(LM_DEBUG,Fmtmsg("������㻧[%s]",sDqszh),"")  
	
	/* Ӱ���˻� */
	memset(sYzzh,0,sizeof(sYzzh));
	memset(sSql , 0x00 , sizeof(sSql));
	sprintf(sSql , "SELECT jdz FROM app_cskz WHERE csjz='K_WZYH_YZZH'");
	iRet = DBSelectToVarChar(sErrMsg, sYzzh, sSql);
	if (iRet < 0)
	{
		LOG(LM_DEBUG,Fmtmsg("���[%s]��ȡ�������˻���SQLCODE=[%d]" , fpub_GetCompname(lXmlhandle) , iRet), "")
		fpub_SetMsg(lXmlhandle,9000,"��ȡ״̬��Ϣ��");
		fpub_SetCompStatus(lXmlhandle,-1);
		return -1;
	}
	trim(sYzzh);
	LOG(LM_DEBUG,Fmtmsg("Ӱ���˻�[%s]",sYzzh),"")  
	
	fp = fopen(sFileName, "r");
	if( fp == NULL )
	{
		LOG(LM_STD, Fmtmsg("�򿪺��Ķ�����ϸ�ļ�����[%s]", sFileName), "");
		fpub_SetMsg(lXmlhandle,MID_SYS_OPENFILE, "�򿪺��Ķ�����ϸ�ļ�����");
		fpub_SetCompStatus(lXmlhandle,COMPSTATUS_FAIL);
		return -1;  
	}

#ifdef DBS_INFORMIX         
	sql_BeginTrans();
#endif    

	while( !feof(fp) )
	{
		memset((char *)&stWzyhCoremx, 0x00, sizeof(stWzyhCoremx));
		memset(sBuffer, 0x00, sizeof(sBuffer));
		fgets(sBuffer, sizeof(sBuffer), fp);
		LOG(LM_DEBUG,Fmtmsg("��ȡ���ȣ�[%d]", strlen(trim(sBuffer))),"")
		if (5 > strlen(trim(sBuffer)))
		{
			continue;
		}		
		pBuffer = sBuffer;
		
		/* �����к� */
		memcpy(stWzyhCoremx.qshh, sQshh, sizeof(stWzyhCoremx.qshh)-1);
		
		/* ǰ������ */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.qsrq, sBuf , sizeof(stWzyhCoremx.qsrq)-1);
			trim(stWzyhCoremx.qsrq);
			LOG(LM_DEBUG,Fmtmsg("ǰ�����ڣ�[%s]", stWzyhCoremx.qsrq),"")
		}
		pBuffer = p+1;
		
		/* ǰ����ˮ */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.qslsh, sBuf, sizeof(stWzyhCoremx.qslsh)-1);
			trim(stWzyhCoremx.qslsh);  
			LOG(LM_DEBUG,Fmtmsg("ǰ����ˮ��[%s]", stWzyhCoremx.qslsh),"")
		}
		pBuffer = p+1;
		
		/* �̻���� */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			LOG(LM_DEBUG,Fmtmsg("�̻���ţ�[%s]", p),"")
		}
		pBuffer = p+1;
		
		/* �跽�����˺� */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.jfyhzh, sBuf, sizeof(stWzyhCoremx.jfyhzh)-1);
			trim(stWzyhCoremx.jfyhzh);  
			LOG(LM_DEBUG,Fmtmsg("�跽�����˺ţ�[%s]", stWzyhCoremx.jfyhzh),"")
		}
		pBuffer = p+1;
		
		/* �跽���� */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.jfhm, sBuf, sizeof(sBuf));
			trim(stWzyhCoremx.jfhm);  
			LOG(LM_DEBUG,Fmtmsg("�跽���л�����[%s]", stWzyhCoremx.jfhm),"")
		}
		pBuffer = p+1;
		
		/* ���������˺� */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.dfyhzh, sBuf, sizeof(stWzyhCoremx.dfyhzh)-1);
			trim(stWzyhCoremx.dfyhzh);  
			LOG(LM_DEBUG,Fmtmsg("���������˺ţ�[%s]", stWzyhCoremx.dfyhzh),"")
		}
		pBuffer = p+1;
		
		/* �������� */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			memcpy(stWzyhCoremx.dfhm, sBuf, sizeof(sBuf));
			trim(stWzyhCoremx.dfhm);  
			LOG(LM_DEBUG,Fmtmsg("�������л�����[%s]", stWzyhCoremx.dfhm),"")
		}
		pBuffer = p+1;
		
		/* ���׽�� */  
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			stWzyhCoremx.jyje = atof(sBuf);
			LOG(LM_DEBUG,Fmtmsg("���׽�[%g]", stWzyhCoremx.jyje),"")
		}
		pBuffer = p+1;
		
		/* ���� */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
		}
		pBuffer = p+1;
		
		/* �������� */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			memcpy(stWzyhCoremx.hxdate, sBuf, sizeof(stWzyhCoremx.hxdate)-1);
			memcpy(stWzyhCoremx.hxdate, "20171201", 8);
			trim(stWzyhCoremx.hxdate);
			LOG(LM_DEBUG,Fmtmsg("�������ڣ�[%s]", stWzyhCoremx.hxdate),"")
		}
		pBuffer = p+1;
		
		/* ������ˮ */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			memcpy(stWzyhCoremx.hxnum, sBuf, sizeof(stWzyhCoremx.hxnum)-1);
			trim(stWzyhCoremx.hxnum);
			LOG(LM_DEBUG,Fmtmsg("������ˮ��[%s]", stWzyhCoremx.hxnum),"")
		}
		pBuffer = p+1;
		
		/* �����˻�����״̬ */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			LOG(LM_DEBUG,Fmtmsg("����״̬��[%s]", sBuf),"")
		}
		pBuffer = p+1;
		
		/* ҵ����� */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			memcpy(stWzyhCoremx.busstype, sBuf, sizeof(stWzyhCoremx.busstype)-1);
			trim(stWzyhCoremx.busstype);
			LOG(LM_DEBUG,Fmtmsg("ҵ����룺[%s]", stWzyhCoremx.busstype),"")
		}
		pBuffer = p+1;	
		
		/* ��ҵ����� */
		memset(sBuf, 0x00, sizeof(sBuf));
		p = strstr(pBuffer , "|");
		if (p == NULL)	goto fail;
		if((p-pBuffer)>0)
		{
			memcpy(sBuf , pBuffer , (p-pBuffer));
			trim(sBuf);
			memcpy(stWzyhCoremx.subbusstype, sBuf, sizeof(stWzyhCoremx.subbusstype)-1);
			trim(stWzyhCoremx.subbusstype);
			LOG(LM_DEBUG,Fmtmsg("��ҵ����룺[%s]", stWzyhCoremx.subbusstype),"")
		}
		pBuffer = p+1;
		
		memcpy(stWzyhCoremx.dzflag, "0", 1);
		
		if(memcmp(stWzyhCoremx.qslsh , "100021201801241391322" , strlen("100021201801241391322")) == 0)
		{
			stWzyhCoremx.jyje = 196;
		}
		if(
			(memcmp(stWzyhCoremx.qslsh , "100021201801251395790" , strlen("100021201801251395790")) == 0) ||
			(memcmp(stWzyhCoremx.qslsh , "100021201801251395781" , strlen("100021201801251395781")) == 0)
		)
			continue;
		
		iRet=DBInsert("YW_WZYH_COREMX", SD_YW_WZYH_COREMX ,NUMELE(SD_YW_WZYH_COREMX), &stWzyhCoremx, sErrMsg);
		if (iRet < 0)
		{
			LOG(LM_DEBUG,Fmtmsg("���Ķ����ļ����ʧ�� sqlcode=[%d]", iRet),"")
			fpub_SetMsg(lXmlhandle, 10001, "���Ķ����ļ����ʧ��");
			fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
			DCIRollback();
			fclose(fp);
			return -1;
		}
    }
	
	DCICommit();
    fclose(fp);

#ifdef DEBUG
	LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), "")
#endif

	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
	return COMPSTATUS_SUCC;

fail:	
	fpub_SetMsg(lXmlhandle, 10001, "������¼ʧ��");
	fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
	DCIRollback();
	fclose(fp);
	return -1;
}
