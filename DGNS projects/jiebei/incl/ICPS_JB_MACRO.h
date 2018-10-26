/* *******************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:����������������ǰ��ϵͳ
��    ��:V2.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:DB2
�ļ�����:ͨ��XMLԪ�����ƺ궨��ͷ�ļ�
�ļ�����:icps_jb_macro.h
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

#ifndef __ICPS_JB_MACRO_H__
#define __ICPS_JB_MACRO_H__

/* ���ú�������ֵ*/
#define ICPS_JB_FUNCRET_SUCC           0             /*�������óɹ� */
#define ICPS_JB_FUNCRET_ONE            1             /*�������������� */
#define ICPS_JB_FUNCRET_TWO            2             /*�������������� */
#define ICPS_JB_FUNCRET_PARAERR        -1            /*�����������*/
#define ICPS_JB_FUNCRET_RCDUVLD        -2            /*��¼�ѹ���*/
#define ICPS_JB_FUNCRET_KEYERR         -11           /*�����ظ�*/
#define ICPS_JB_FUNCRET_SQLERR         -12           /*SQL��������*/
#define ICPS_JB_FUNCRET_NOTFOUND       1403         /*����δ�ҵ�*/
#define ICPS_JB_FUNCRET_FAIL           -99           /*����ͨ�ô��� */

#define ICPS_JB_STRING_BLANK           " "           /*�ո�*/
#define ICPS_JB_COMMIT_CNT             1000          /*1k���ύһ������*/
/*XML�ڵ����� */
#define ICPS_JB_NODEATTR_STRING        "1"             /*  �ַ��� */
#define ICPS_JB_NODEATTR_NUMBER        "0"             /*  ���ֽ�� */
/*XML�ڵ��Ƿ�������*/
#define XML_NODE_NOTNULL           1             /*  XML�ڵ�������     */
#define XML_NODE_NULL              0             /*  XML�ڵ����Ϊ��     */
#define XML_NODE_EXIST             1             /*  ��鷢��XML�ڵ���� */
#define XML_NODE_NOTFOUND          203           /*  �ڵ㲻���� */
/*��Ӧ�� */
#define MID_ICPS_JB_XMLOP                   9003       /* XML��ز���ʧ��*/
#define MID_ICPS_JB_COMMBUF                 9004       /* COMMBUF��ز���ʧ��*/
#define MID_ICPS_JB_MALLOC                  9005       /* �ڴ���ز���ʧ��*/
#define MID_ICPS_JB_FILEOP                  9006       /* �ļ���ز���ʧ��*/
#define MID_ICPS_JB_DBOP                    9001       /* �����ز���ʧ��*/
#define MID_ICPS_JB_DBOP_NOTFOUND           9002       /* δ�ҵ���ؼ�¼*/
#define MID_ICPS_JB_BIZELEM_NOTNULL     9007       /* ҵ������Ҫ�ز���Ϊ��*/
/*��Ӧ��Ϣ */
#define MSG_ICPS_JB_CALLFUNC_FAIL        "�������ó���[%s]"
#define MSG_ICPS_JB_XMLOP                "XML��ز���ʧ��"
#define MSG_ICPS_JB_COMMBUF              "COMMBUF��ز���ʧ��"
#define MSG_ICPS_JB_MALLOC               "�ڴ���ز���ʧ��[%d]"
#define MSG_ICPS_JB_FILEOP               "�ļ���ز���ʧ��[%s]"
#define MSG_ICPS_JB_DBOP                 "�����ز���ʧ��"
#define MSG_ICPS_JB_DBOP_NOTFOUND        "δ�ҵ���ؼ�¼"
#define MSG_ICPS_JB_BIZELEM_NOTNULL      "[%s]Ҫ�ز���Ϊ��"
#define MSG_ICPS_JB_NODECHK_NULL         "[%s]�ڵ㲻��Ϊ��"


/* SQLCODE DCI����ֵ�ж�*/
#define ICPS_JB_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, sErrInfo)   if( iRet < 0 ) \
        { \
            LOG(LM_STD, Fmtmsg("SQLERR[%d][%s]", iRet, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* ���ܺ�������ֵ�ж� */
#define ICPS_JB_FUNCCHK_NOTSUCC(lXmlhandle, iRet, sErrInfo)   if( iRet != 0 ) \
        { \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ICPS_JB_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* ���ܺ�������ֵ�ж�(���˵ǼǱ������ظ�) */
#define ICPS_JB_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, sErrInfo)   if( iRet <0 && iRet != ICPS_JB_FUNCRET_KEYERR ) \
        { \
            DCICommit(); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ICPS_JB_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* ���ܺ�������ֵ�ж�(����ǿ������ع�) */
#define ICPS_JB_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, sErrInfo)   if( iRet != 0 ) \
        { \
            DCIRollback(); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ICPS_JB_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* �Կ��ַ������鸳�ո�,sFieldΪ�ַ�����������*/
#define ICPS_JB_FIELD_SETNULLTOBLANK( sField )   \
        { \
          if (sField[0] == '\0') \
          { \
              pstrcopy(sField, ICPS_JB_STRING_BLANK, sizeof(sField)); \
          } \
        }

/* �����丳ֵ */
#define ICPS_JB_PSTRCOPY( sYbhqzDes, sYbhqzSrc )   \
        { \
          pstrcopy(sYbhqzDes, sYbhqzSrc, sizeof(sYbhqzDes)); \
        }

/* Ŀ�Ĵ�Ϊ����ֵ */
#define ICPS_JB_PSTRCOPY_NULL( sYbhqzDes, sYbhqzSrc )   if ( sYbhqzDes[0] == '\0') \
        { \
          pstrcopy(sYbhqzDes, sYbhqzSrc, sizeof(sYbhqzDes)); \
        }

/* ҵ��Ҫ�ز�Ϊ�շ���ֵ�ж� */
#define ICPS_JB_NODECHK_NOTNULL(lXmlhandle, iRet, sCnElemName)   if( iRet < 0 ) \
        { \
            fpub_SetMsg( lXmlhandle, MID_ICPS_JB_BIZELEM_NOTNULL, Fmtmsg(MSG_ICPS_JB_BIZELEM_NOTNULL, sCnElemName) ); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ICPS_JB_NODECHK_NULL, sCnElemName), fpub_GetCompname(lXmlhandle)); \
        }

/* ȡ�ַ���ֵ������Ϊ�� */
#define ICPS_JB_GETXMLSTR_NOTNULL( sXmlNode, sField, sCnField )   \
        { \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sXmlNode, ICPS_JB_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NOTNULL); \
          ICPS_JB_NODECHK_NOTNULL(lXmlhandle, iRet, sCnField); \
        }

/* ȡ�ַ���ֵ����Ϊ�� */
#define ICPS_JB_GETXMLSTR_NULL( sXmlNode, sField, sCnField )   \
        { \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sXmlNode, ICPS_JB_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NULL); \
        }

/* ȡ�ַ���ֵ������Ϊ��(����) */
#define ICPS_JB_GETXMLSTR_NOTNULL_MULTI( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                              \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i);                      \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, ICPS_JB_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NOTNULL); \
          ICPS_JB_NODECHK_NOTNULL(lXmlhandle, iRet, sCnField); \
        }

/* ȡ�ַ���ֵ����Ϊ��(����) */
#define ICPS_JB_GETXMLSTR_NULL_MULTI( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                          \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i);                  \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, ICPS_JB_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NULL); \
        }

#endif


