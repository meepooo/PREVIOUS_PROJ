#include "gaps_head.h"
#include "gabdxzp_head.h"
#include "sfxt_lstqry.h"

/************************************************************************
��̬�����������
�����������:ffunc_sfxt_listQry_getFileName
��������:��ȡ��д�ļ���
����:

������״̬:
  ���״̬��        ���˵��
  < 0               ����׼��ʧ��
  = 0               �ɹ�
  
�� Ŀ ��: 
�� �� Ա:������ 
��������:20160226
�޸�����:
����ʹ��ʾ��:
************************************************************************/
int ffunc_sfxt_listQry_getFileName(HXMLTREE lXmlhandle, char* psFileName)
{
    char sPltDate[8+1];
    char sPltNum[8+1];
    char sJyjg[16+1];
    char sJygy[16+1];
    char sFilePath[256];
    int  iRet = -1;
    
    memset(sPltDate, 0x00, sizeof(sPltDate));
    memset(sPltNum, 0x00, sizeof(sPltNum));
    memset(sJyjg, 0x00, sizeof(sJyjg));
    memset(sJygy, 0x00, sizeof(sJygy));
    GAB_DXZP_GETXMLSTR_NOTNULL( "/sfxt/jyjg", sJyjg, "���׻���" )
    GAB_DXZP_GETXMLSTR_NOTNULL( "/sfxt/jygy", sJygy, "���׹�Ա" )
    GAB_DXZP_GETXMLSTR_NOTNULL( XMLNM_SYSDATE, sPltDate, "ƽ̨����" )
    GAB_DXZP_GETXMLSTR_NOTNULL( XMLNM_ZHQZLSH, sPltNum, "ƽ̨��ˮ��" )
    
    memset(sFilePath, 0x00, sizeof(sFilePath));
    /* XMLNM_SYS_LISTQRYFP */
    GAB_DXZP_GETXMLSTR_NULL( "/sfxt/listqryfp", sFilePath, "�б��ѯ·��" )
    if (sFilePath[0] == '\0')
    {
        snprintf(sFilePath, sizeof(sFilePath),"%s/file", getenv("HOME"));
    }
    sprintf(psFileName, "%s/sfxtlist_%s%s_%s_%s", 
        sFilePath, sJyjg, sJygy, sPltDate, sPltNum);
    return 0;
}

/************************************************************************
��̬�����������
�����������:ffunc_sfxt_listQry_getCntNum
��������:��ȡ�ܱ���
����:

������״̬:
  ���״̬��        ���˵��
  < 0               ����׼��ʧ��
  = 0               �ɹ�
  
�� Ŀ ��: 
�� �� Ա:������ 
��������:20160226
�޸�����:
����ʹ��ʾ��:
************************************************************************/
int ffunc_sfxt_listQry_getCntNum(HXMLTREE lXmlhandle, char* psSql, int iSqlLen, int* piCntNum)
{
    char sSql[8192];   /*���洫��sql���*/
    char sSql1[4076];  /*������*/
    char sSql2[4096];  /*countͳ�ƴ�*/
    char* pStr1 = NULL;
    char* pStr2 = NULL;
    int iSql1 = 0;
    int iRet = -1;
    int iLen = 0;
    int iRelPos = 0;  /*sql�������ƫ��λ��*/

    if (iSqlLen > sizeof (sSql) - 1)
    {
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("�б��ѯSQL�������,len:psSql[%d],size:sSql[%d]", iSqlLen, sizeof (sSql)), fpub_GetCompname(lXmlhandle));
    }

    memset(sSql, 0x00, sizeof (sSql));
    pstrcopy(sSql, psSql, sizeof (sSql) - 1);
    strtoupper(sSql);
    pStr1 = (char *)strstr(sSql, "SELECT ");
    pStr2 = (char *)strstr(sSql, " FROM ");
    if ( pStr2 == NULL )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("�б��ѯSQL�������,[%s]", psSql), fpub_GetCompname(lXmlhandle));
    }
    /*�����������ƫ��*/
    iRelPos = pStr2 - sSql;
    /*SELECT�б�����*/
    iLen = (int)(pStr2 - pStr1);
    /*ORDER BY����λ��*/
    pStr2 = strstr(sSql, "ORDER BY");
    if (pStr2 != NULL)
    {
        iLen += (iSqlLen - (int)(pStr2 - sSql));
    }
    memset(sSql1, 0x00, sizeof(sSql1));
    /*ȡ��������*/
    pstrcopy(sSql1, psSql + iRelPos, iSqlLen-iLen+1);
    LOG(LM_DEBUG, Fmtmsg("sSql1[%s]\npSql[%s]", sSql1, psSql), fpub_GetCompname(lXmlhandle));
    COMP_SOFTSETXML("/sfxt/qrywhere", sSql1);
    memset(sSql2, 0x00, sizeof(sSql2));
    snprintf(sSql2, sizeof(sSql2), "select count(*) %s", sSql1);

    if ( (iRet = sql_CountSql( sSql2 )) == -1 )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("�б��ѯ��ȡ�ܼ�¼��ʧ��,[%d]", iRet), fpub_GetCompname(lXmlhandle));
    }
    *piCntNum = iRet;
    return 0;
}

/************************************************************************
��̬�����������
�����������:ffunc_sfxt_listQry_wrtRndFile
��������:�б��ѯд�ļ���ʽ
����:

������״̬:
  ���״̬��        ���˵��
  < 0               ����׼��ʧ��
  = 0               �ɹ�
  
�� Ŀ ��: 
�� �� Ա:������ 
��������:20160226
�޸�����:
����ʹ��ʾ��:
************************************************************************/
int ffunc_sfxt_listQry_wrtRndFile(HXMLTREE lXmlhandle, char* psSql, int iStartNum, int iEndNum, int* piRealNum)
{
    char sFileName[256];
    FILE* fp;
    int iRet = -1;
    /* ��ȡ�ļ��� */
    memset(sFileName, 0x00, sizeof(sFileName));
    iRet = ffunc_sfxt_listQry_getFileName(lXmlhandle, sFileName);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "��ȡ�б��ļ���");
    COMP_SOFTSETXML(XMLNM_RESP_FILENAME, sFileName)
    /* ���ļ� */
    LOG(LM_DEBUG, Fmtmsg("�б��ѯ->�ļ���[%s]", sFileName), fpub_GetCompname(lXmlhandle)); 
    fp = fopen(sFileName, "w+");
    if ( fp == NULL )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_FILEOP, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)));
        LOGRET(COMPRET_FAIL,LM_STD, Fmtmsg(MSG_GAB_DXZP_FILEOP, strerror(errno)), fpub_GetCompname(lXmlhandle)); 
    }
    /* �����ݿ����� 
    iRet = fbasc_db_openDB(lXmlhandle);
    GAB_DXZP_FUNCCHK_NOTSUCC_CLSFP(lXmlhandle, iRet, "�����ݿ�����");
    */
    /* ���� */
    iRet = ffunc_sfxt_listQry_fetAndWrtRndFile(lXmlhandle, psSql, fp, iStartNum, iEndNum, piRealNum);
    /* �ر����ݿ����ӡ��ļ���� 
    fclose(fp);
    fbasc_db_closeDB(lXmlhandle);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "�����б��ѯ");
    */
    COMP_SOFTSETXML(XMLNM_RESP_FILEFLAG, "1")
    return 0;
}

/************************************************************************
��̬�����������
�����������:ffunc_sfxt_listQry_fetAndWrtRndFile
��������:�ļ���ʽ��ȡ����д��¼
����:

������״̬:
  ���״̬��        ���˵��
  < 0               ����׼��ʧ��
  = 0               �ɹ�
  
�� Ŀ ��: 
�� �� Ա:������ 
��������:20160226
�޸�����:
����ʹ��ʾ��:
************************************************************************/
int ffunc_sfxt_listQry_fetAndWrtRndFile(HXMLTREE lXmlhandle, char* psSql, FILE* fp, int iStartNum, int iEndNum, int* piRealNum)
{
    char sBuf[1024];
    char sLine[4096];
    int i = 0;
    int iCurNum = 1;
    int iRealNum = 0;
    int iQueryNum = 0;
    int iRet = -1;
    int iNumCols=0;
    int j=0;
    int iFlag=-1;
    char sColName[100];
    CURSOR cur;

    /* �����α� */
    if ((cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("����C01LSTQRY�α�ʧ��,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    }
    if (DCIExecute(cur) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("��C01LSTQRY�α�ʧ��,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    }
    /* ��ȡ���� */
    iNumCols = DCINumCols(cur);
    memset(sLine, 0x00, sizeof(sLine));
    for (j=0; j<iNumCols; 	j++)
    {
        memset(sColName, 0x00, sizeof(sColName));
        DCIColName(cur, j, sColName, sizeof(sColName));   /* ȡ�ֶ��� */
        snprintf(sLine+strlen(sLine), sizeof(sLine), "%s,", sColName);
    }
    strcat(sLine, "\n");
    fwrite(sLine, strlen(sLine), 1, fp);
    LOG(LM_STD, Fmtmsg("COLNAME:[%s]", sLine), fpub_GetCompname(lXmlhandle));    

    /*��ʼѭ��ȡ��¼��*/
    iQueryNum = iEndNum-iStartNum;
    for ( iRealNum=0; iRealNum<iQueryNum; iRealNum++)
    {
        iCurNum = iStartNum + iRealNum ;
        iRet = DCIFetch2(cur, DCI_FETCH_ABSOLUTE, iCurNum);
	    if (iRet == -1)
        {
    	    fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
    	    LOG(LM_STD, Fmtmsg("��C01LSTQRY�α�ʧ��,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    	    iFlag=-1;
    	    break;
        }	  	
        if (iRet == 0)  	/*�޼�¼*/
        {
    	    break;
    	}
        memset(sLine, 0, sizeof(sLine));
        for (j=0; j<iNumCols; j++)
        {
    	    memset(sBuf, 0x00, sizeof(sBuf));
    	    snprintf( sBuf, sizeof(sBuf), "%s", DCIFieldAsString(cur, j) );
    	    trim(sBuf);
    	    snprintf(sLine+strlen(sLine), sizeof(sLine), "%s|", sBuf );
        }
        LOG(LM_DEBUG, Fmtmsg("ROW[%d]:[%s]", i, sLine), fpub_GetCompname(lXmlhandle));
        strcat(sLine, "\n");
        fwrite(sLine, strlen(sLine), 1, fp);
        
    }
    DCIFreeCursor(cur);
    *piRealNum = iRealNum;
    if ( iFlag < 0 )
    {
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("��C01LSTQRY�α�ʧ��"),fpub_GetCompname(lXmlhandle));
    }
    return 0;
}

/************************************************************************
��̬�����������
�����������:ffunc_sfxt_listQry_wrtRndXml
��������:�б��ѯдXML����ʽ
����:

������״̬:
  ���״̬��        ���˵��
  < 0               ����׼��ʧ��
  = 0               �ɹ�
  
�� Ŀ ��: 
�� �� Ա:������ 
��������:20160226
�޸�����:
����ʹ��ʾ��:
************************************************************************/
int ffunc_sfxt_listQry_wrtRndXml(HXMLTREE lXmlhandle, char* psSql, int iStartNum, int iEndNum, int* piRealNum)
{
    int iRet = -1;
    /* �����ݿ����� 
    LOG( LM_DEBUG, Fmtmsg("˾�����ͨ�ò�ѯ->------------1-----------"), fpub_GetCompname(lXmlhandle));
    iRet = fbasc_db_openDB(lXmlhandle);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "�����ݿ�����");
    LOG( LM_DEBUG, Fmtmsg("˾�����ͨ�ò�ѯ->------------2-----------"), fpub_GetCompname(lXmlhandle));
    */
    /* ���� */
    iRet = ffunc_sfxt_listQry_fetAndWrtRndXml(lXmlhandle, psSql, iStartNum, iEndNum, piRealNum);
    /* �ر����ݿ����ӡ��ļ���� 
    fbasc_db_closeDB(lXmlhandle);
    GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, "�����б��ѯ");
    */
    COMP_SOFTSETXML(XMLNM_RESP_FILEFLAG, "1")
    return 0;
}

/************************************************************************
��̬�����������
�����������:ffunc_sfxt_listQry_fetAndWrtRndXml
��������:XML��ʽ��ȡ����д��¼
����:

������״̬:
  ���״̬��        ���˵��
  < 0               ����׼��ʧ��
  = 0               �ɹ�
  
�� Ŀ ��: 
�� �� Ա:������ 
��������:20160226
�޸�����:
����ʹ��ʾ��:
************************************************************************/
int ffunc_sfxt_listQry_fetAndWrtRndXml(HXMLTREE lXmlhandle, char* psSql, int iStartNum, int iEndNum, int* piRealNum)
{
    char sBuf[1024];
    char sLine[1024];
    int i = 0;
    int iCurNum = 1;
    int iRealNum = 0;
    int iQueryNum = 0;
    int iRet = -1;
    int iNumCols=0;
    int j=0;
    int iFlag=0;
    char sColName[100];
    char sSfxtNodePath[128];
    CURSOR cur;
    /* �����α� */
    if ((cur = DCIDeclareCursor(psSql, DCI_STMT_LOCATOR)) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("����C01LSTQRY�α�ʧ��,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    }
    if (DCIExecute(cur) == -1)
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("��C01LSTQRY�α�ʧ��,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    }
    /* ��ȡ���� */
    iNumCols = DCINumCols(cur);  
    /*��ʼѭ��ȡ��¼��*/
    iQueryNum = iEndNum-iStartNum;
    for ( iRealNum=0; iRealNum<iQueryNum; iRealNum++)
    {
        iCurNum = iStartNum + iRealNum ;
        iRet = DCIFetch2(cur, DCI_FETCH_ABSOLUTE, iCurNum);
	    if (iRet == -1)
        {
    	    fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_DBOP, MSG_GAB_DXZP_DBOP);
    	    LOG(LM_STD, Fmtmsg("��C01LSTQRY�α�ʧ��,[%s]", DCILastError()), fpub_GetCompname(lXmlhandle));
    	    iFlag=-1;
    	    break;
        }	  	
        if (iRet == 0)  	/*�޼�¼*/
        {
    	    break;
    	}
        memset(sLine, 0, sizeof(sLine));
        for (j=0; j<iNumCols; j++)
        {
    	    memset(sColName, 0x00, sizeof(sColName));
            DCIColName(cur, j, sColName, sizeof(sColName));   /* ȡ�ֶ��� */
            strtolower(sColName);
            memset(sSfxtNodePath, 0x00, sizeof(sSfxtNodePath));
            snprintf(sSfxtNodePath, sizeof(sSfxtNodePath), XMLNM_RESP_LISTQRY, iRealNum+1, sColName);
            trim(sSfxtNodePath);
    	    snprintf(sLine, sizeof(sLine), "%s", DCIFieldAsString(cur, j));
    	    trim(sLine);
    	    COMP_SOFTSETXML(sSfxtNodePath, sLine);
            LOG(LM_DEBUG, Fmtmsg("[%s]:[%s]", sSfxtNodePath, sLine), fpub_GetCompname(lXmlhandle));
        }
    }
    DCIFreeCursor(cur);
    *piRealNum = iRealNum ;
    if ( iFlag < 0 )
    {
        LOGRET( GAB_DXZP_FUNCRET_FAIL, LM_STD, Fmtmsg("��C01LSTQRY�α�ʧ��"),fpub_GetCompname(lXmlhandle));
    }
    return 0;
}

/*****************************************************
   ��������:  int ffunc_xml_getNodeValue(HXMLTREE lXmlhandle, const char* szPath, const char* nodeAttr, char* szValue, unsigned int size, int iFlag)
   ��������:  ��ȡXML�ڵ�ֵ,���ַ����ڵ�Ϊ����'-';����������ͽڵ�Ϊ����0
   ��������:  lXmlhandle  XML���������
              Path  �ڵ�·��
              nodeAttr �ڵ����� 0-�ַ���, 1-�����ֵ�
              szValue �ڵ�ֵ����ַ���
              size  ���ֵ�Ŀռ��С
              iFlag �ڵ��Ƿ������� GAB_DXZP_XML_NULL GAB_DXZP_XML_NOTNULL
             
   ��������:  >0: �ڵ�ֵ��ʵ�ʳ���
              -1:�������Ϊ�ջ��������ΪNULL
              -2:��Ϊ�յ�XML�ڵ㲻����
              -3:����ԭ��ʧ��

   ����˵��:  
            
   �޸�˵��:  
*****************************************************/
int ffunc_xml_getNodeValue(HXMLTREE lXmlhandle, char* psPath, char* psNodeAttr, char* psValue, unsigned int size, int iFlag)
{
    int  iRet = 0;
    char sBuf[1024];
    int  iNodeValueLen = 0;
    char* psNodeValue = NULL;
    
    if ( psValue == NULL )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!�ڵ�[%s]��Ŀ�����ΪNULL!", MSG_GAB_DXZP_XMLOP, psPath),"")
        return -1;
    }
    
    memset(sBuf, 0x00, sizeof(sBuf));
    iNodeValueLen = sizeof(sBuf);
    if ( iNodeValueLen > size )
    {
        psNodeValue = sBuf;
        iRet = xml_GetElement(lXmlhandle, psPath, psNodeValue, iNodeValueLen);
        pstrcopy(psValue, psNodeValue, size);
    }else
    {
        iNodeValueLen = size;
        psNodeValue = psValue ;
        iRet = xml_GetElement(lXmlhandle, psPath, psNodeValue, iNodeValueLen);
    }
    psNodeValue = NULL;
    if( iRet == FAIL && XML_NODE_NOTNULL == iFlag )
    {        
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!�ڵ�[%s]������[%d]!", MSG_GAB_DXZP_XMLOP, psPath, iRet),"") 
        return -2;
    }
    
    if( (psValue[0] == '\0') && (XML_NODE_NOTNULL == iFlag) )
    {
        fpub_SetMsg(lXmlhandle, MID_GAB_DXZP_XMLOP, Fmtmsg(MSG_GAB_DXZP_XMLOP));
        LOG(LM_STD,Fmtmsg("%s!�ڵ�[%s]ֵΪ��!", MSG_GAB_DXZP_XMLOP, psPath),"")
        return -2;
    }    
    trim(psValue);       
    return strlen(psValue);
}
