/* *******************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:��������������թƭǰ��ϵͳ
��    ��:V2.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:DB2
�ļ�����:ͨ��XMLԪ�����ƺ궨��ͷ�ļ�
�ļ�����:gabdxzp_macro.h
�� Ŀ ��:���е�����ҵ��.Ӧ�ü��ɲ�Ʒ��
�� �� Ա:
��������:2016-01-22
��    ��:
�޸�����:
******************************************************************** */

/*
�޸ļ�¼
�޸�����:
�޸�����:
�޸���:
 */

#ifndef __GAB_DXZP_MACRO_H__
#define __GAB_DXZP_MACRO_H__

/* ���ú�������ֵ*/
#define GAB_DXZP_FUNCRET_SUCC           0             /*�������óɹ� */
#define GAB_DXZP_FUNCRET_ONE            1             /*�������������� */
#define GAB_DXZP_FUNCRET_TWO            2             /*�������������� */
#define GAB_DXZP_FUNCRET_PARAERR        -1            /*�����������*/
#define GAB_DXZP_FUNCRET_RCDUVLD        -2            /*��¼�ѹ���*/
#define GAB_DXZP_FUNCRET_KEYERR         -11           /*�����ظ�*/
#define GAB_DXZP_FUNCRET_SQLERR         -12           /*SQL��������*/
#define GAB_DXZP_FUNCRET_NOTFOUND       1403         /*����δ�ҵ�*/
#define GAB_DXZP_FUNCRET_FAIL           -99           /*����ͨ�ô��� */

#define GAB_DXZP_STRING_BLANK           " "           /*�ո�*/
/*XML�ڵ����� */
#define GAB_DXZP_NODEATTR_STRING        "1"             /*  �ַ��� */
#define GAB_DXZP_NODEATTR_NUMBER        "0"             /*  ���ֽ�� */
/*XML�ڵ��Ƿ�������*/
#define XML_NODE_NOTNULL           1             /*  XML�ڵ�������     */
#define XML_NODE_NULL              0             /*  XML�ڵ����Ϊ��     */
#define XML_NODE_EXIST             1             /*  ��鷢��XML�ڵ���� */
#define XML_NODE_NOTFOUND          203           /*  �ڵ㲻���� */

#define GAB_DXZP_COMMIT_CNT             1000          /*1k���ύһ������*/




/* SQLCODE DCI����ֵ�ж�*/
#define GAB_DXZP_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, sErrInfo)   if( iRet < 0 ) \
        { \
            LOG(LM_STD, Fmtmsg("SQLERR[%d][%s]", iRet, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* ���ܺ�������ֵ�ж� */
#define GAB_DXZP_FUNCCHK_NOTSUCC(lXmlhandle, iRet, sErrInfo)   if( iRet != 0 ) \
        { \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_GAB_DXZP_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* ���ܺ�������ֵ�ж�(����ǿ������ع�) */
#define GAB_DXZP_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, sErrInfo)   if( iRet != 0 ) \
        { \
            DCIRollback(); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_GAB_DXZP_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* �Կ��ַ������鸳�ո�,sFieldΪ�ַ�����������*/
#define GAB_DXZP_FIELD_SETNULLTOBLANK( sField )   \
        { \
          if (sField[0] == '\0') \
          { \
              pstrcopy(sField, GAB_DXZP_STRING_BLANK, sizeof(sField)); \
          } \
        }

/* �����丳ֵ */
#define GAB_DXZP_PSTRCOPY( sYbhqzDes, sYbhqzSrc )   \
        { \
          pstrcopy(sYbhqzDes, sYbhqzSrc, sizeof(sYbhqzDes)); \
        }

/* Ŀ�Ĵ�Ϊ����ֵ */
#define GAB_DXZP_PSTRCOPY_NULL( sYbhqzDes, sYbhqzSrc )   if ( sYbhqzDes[0] == '\0') \
        { \
          pstrcopy(sYbhqzDes, sYbhqzSrc, sizeof(sYbhqzDes)); \
        }

/* ҵ��Ҫ�ز�Ϊ�շ���ֵ�ж� */
#define GAB_DXZP_NODECHK_NOTNULL(lXmlhandle, iRet, sCnElemName)   if( iRet < 0 ) \
        { \
            fpub_SetMsg( lXmlhandle, MID_GAB_DXZP_BIZELEM_NOTNULL, Fmtmsg(MSG_GAB_DXZP_BIZELEM_NOTNULL, sCnElemName) ); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_GAB_DXZP_NODECHK_NULL, sCnElemName), fpub_GetCompname(lXmlhandle)); \
        }

/* ȡ�ַ���ֵ������Ϊ�� */
#define GAB_DXZP_GETXMLSTR_NOTNULL( sXmlNode, sField, sCnField )   \
        { \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sXmlNode, GAB_DXZP_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NOTNULL); \
          GAB_DXZP_NODECHK_NOTNULL(lXmlhandle, iRet, sCnField); \
        }

/* ȡ�ַ���ֵ����Ϊ�� */
#define GAB_DXZP_GETXMLSTR_NULL( sXmlNode, sField, sCnField )   \
        { \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sXmlNode, GAB_DXZP_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NULL); \
        }



/* ȡ�ַ���ֵ������Ϊ��(����) */
#define GAB_DXZP_GETXMLSTR_NOTNULL_MULTI( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                              \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i);                      \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, GAB_DXZP_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NOTNULL); \
          GAB_DXZP_NODECHK_NOTNULL(lXmlhandle, iRet, sCnField); \
        }

/* ȡ�ַ���ֵ����Ϊ��(����) */
#define GAB_DXZP_GETXMLSTR_NULL_MULTI( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                          \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i);                  \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, GAB_DXZP_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NULL); \
        }



/* ȡ�ַ���ֵ������Ϊ��(����) */
#define GAB_DXZP_GETXMLSTR_NOTNULL_MULTI2( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                              \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i,j);                      \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, GAB_DXZP_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NOTNULL); \
          GAB_DXZP_NODECHK_NOTNULL(lXmlhandle, iRet, sCnField); \
        }

/* ȡ�ַ���ֵ����Ϊ��(����) */
#define GAB_DXZP_GETXMLSTR_NULL_MULTI2( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                          \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i,j);                  \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, GAB_DXZP_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NULL); \
        }




/* ���ܺ�������ֵ�ж�(���˵ǼǱ������ظ�) */
#define GAB_DXZP_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, sErrInfo)   if( iRet <0 && iRet != GAB_DXZP_FUNCRET_KEYERR ) \
        { \
            DCICommit(); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_GAB_DXZP_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }



#endif
