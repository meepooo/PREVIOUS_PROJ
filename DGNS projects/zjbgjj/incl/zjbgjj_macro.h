/* *******************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:ס����������ǰ��ϵͳ
��    ��:V2.0
����ϵͳ:LINUX
�� �� ��:ORACLE
�ļ�����:ͨ��XMLԪ�����ƺ궨��ͷ�ļ�
�ļ�����:zjbgjj_macro.h
�� Ŀ ��:���е�����ҵ��.Ӧ�ü��ɲ�Ʒ��
�� �� Ա:
��������:2016-10-19
��    ��:
�޸�����:
******************************************************************** */

/*
�޸ļ�¼
�޸�����:
�޸�����:
�޸���:
 */

#ifndef __ZJB_GJJ_MACRO_H__
#define __ZJB_GJJ_MACRO_H__

/* ���ú�������ֵ*/
#define ZJB_GJJ_FUNCRET_SUCC           0             /*�������óɹ� */
#define ZJB_GJJ_FUNCRET_ONE            1             /*�������������� */
#define ZJB_GJJ_FUNCRET_TWO            2             /*�������������� */
#define ZJB_GJJ_FUNCRET_PARAERR        -1            /*�����������*/
#define ZJB_GJJ_FUNCRET_RCDUVLD        -2            /*��¼�ѹ���*/
#define ZJB_GJJ_FUNCRET_KEYERR         -11           /*�����ظ�*/
#define ZJB_GJJ_FUNCRET_SQLERR         -12           /*SQL��������*/
#define ZJB_GJJ_FUNCRET_NOTFOUND       1403         /*����δ�ҵ�*/
#define ZJB_GJJ_FUNCRET_FAIL           -99           /*����ͨ�ô��� */

#define ZJB_GJJ_STRING_BLANK           " "           /*�ո�*/
#define ZJB_GJJ_COMMIT_CNT             1000          /*1k���ύһ������*/
/*XML�ڵ����� */
#define ZJB_GJJ_NODEATTR_STRING        "1"             /*  �ַ��� */
#define ZJB_GJJ_NODEATTR_NUMBER        "0"             /*  ���ֽ�� */
/*XML�ڵ��Ƿ�������*/
#define XML_NODE_NOTNULL           1             /*  XML�ڵ�������     */
#define XML_NODE_NULL              0             /*  XML�ڵ����Ϊ��     */
#define XML_NODE_EXIST             1             /*  ��鷢��XML�ڵ���� */
#define XML_NODE_NOTFOUND          203           /*  �ڵ㲻���� */


/* SQLCODE DCI����ֵ�ж�*/
#define ZJB_GJJ_SQLCDCHK_NOTSUCC(lXmlhandle, iRet, sErrInfo)   if( iRet < 0 ) \
        { \
            LOG(LM_STD, Fmtmsg("SQLERR[%d][%s]", iRet, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* ���ܺ�������ֵ�ж� */
#define ZJB_GJJ_FUNCCHK_NOTSUCC(lXmlhandle, iRet, sErrInfo)   if( iRet != 0 ) \
        { \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ZJB_GJJ_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* ���ܺ�������ֵ�ж�(���˵ǼǱ������ظ�) */
#define ZJB_GJJ_FUNCCHK_NOTSUCC_REKEYERR(lXmlhandle, iRet, sErrInfo)   if( iRet <0 && iRet != ZJB_GJJ_FUNCRET_KEYERR ) \
        { \
            DCICommit(); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ZJB_GJJ_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* ���ܺ�������ֵ�ж�(����ǿ������ع�) */
#define ZJB_GJJ_FUNCCHK_NOTSUCC_ROLLBACK(lXmlhandle, iRet, sErrInfo)   if( iRet != 0 ) \
        { \
            DCIRollback(); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ZJB_GJJ_CALLFUNC_FAIL, sErrInfo), fpub_GetCompname(lXmlhandle)); \
        }

/* �Կ��ַ������鸳�ո�,sFieldΪ�ַ�����������*/
#define ZJB_GJJ_FIELD_SETNULLTOBLANK( sField )   \
        { \
          if (sField[0] == '\0') \
          { \
              pstrcopy(sField, ZJB_GJJ_STRING_BLANK, sizeof(sField)); \
          } \
        }

/* �����丳ֵ */
#define ZJB_GJJ_PSTRCOPY( sYbhqzDes, sYbhqzSrc )   \
        { \
          pstrcopy(sYbhqzDes, sYbhqzSrc, sizeof(sYbhqzDes)); \
        }

/* Ŀ�Ĵ�Ϊ����ֵ */
#define ZJB_GJJ_PSTRCOPY_NULL( sYbhqzDes, sYbhqzSrc )   if ( sYbhqzDes[0] == '\0') \
        { \
          pstrcopy(sYbhqzDes, sYbhqzSrc, sizeof(sYbhqzDes)); \
        }

/* ҵ��Ҫ�ز�Ϊ�շ���ֵ�ж� */
#define ZJB_GJJ_NODECHK_NOTNULL(lXmlhandle, iRet, sCnElemName)   if( iRet < 0 ) \
        { \
            fpub_SetMsg( lXmlhandle, MID_ZJB_GJJ_BIZELEM_NOTNULL, Fmtmsg(MSG_ZJB_GJJ_BIZELEM_NOTNULL, sCnElemName) ); \
            LOGRET(iRet, LM_STD, Fmtmsg(MSG_ZJB_GJJ_NODECHK_NULL, sCnElemName), fpub_GetCompname(lXmlhandle)); \
        }

/* ȡ�ַ���ֵ������Ϊ�� */
#define ZJB_GJJ_GETXMLSTR_NOTNULL( sXmlNode, sField, sCnField )   \
        { \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sXmlNode, ZJB_GJJ_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NOTNULL); \
          ZJB_GJJ_NODECHK_NOTNULL(lXmlhandle, iRet, sCnField); \
        }

/* ȡ�ַ���ֵ����Ϊ�� */
#define ZJB_GJJ_GETXMLSTR_NULL( sXmlNode, sField, sCnField )   \
        { \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sXmlNode, ZJB_GJJ_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NULL); \
        }

/* ȡ�ַ���ֵ������Ϊ��(����) */
#define ZJB_GJJ_GETXMLSTR_NOTNULL_MULTI( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                              \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i);                      \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, ZJB_GJJ_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NOTNULL); \
          ZJB_GJJ_NODECHK_NOTNULL(lXmlhandle, iRet, sCnField); \
        }

/* ȡ�ַ���ֵ����Ϊ��(����) */
#define ZJB_GJJ_GETXMLSTR_NULL_MULTI( sXmlNode, sField, sCnField )   \
        { \
          memset(sBuf, 0x00, sizeof(sBuf));                          \
          snprintf(sBuf, sizeof(sBuf), sXmlNode, i);                  \
          iRet = ffunc_xml_getNodeValue(lXmlhandle, sBuf, ZJB_GJJ_NODEATTR_STRING, \
                                        sField, sizeof(sField), XML_NODE_NULL); \
        }

#endif


