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

/************************************************************************
  ��̬�����������
  �����������: SYW_TIPS_TRIMMSG
  �������: TIPS����ȥ���ո�

  �������: 
  TIPS����ȥ���ո�
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
  ��������: 2017��05��23��
  �޸�����: 
  �޸�����: 
  ����ʹ��ʾ��: 
 ************************************************************************/
IRESULT SYW_TIPS_TRIMMSG(HXMLTREE lXmlhandle)
{
    int iParas;
    char   cRootNodeName[64 + 1]       = {0};
    char   cTmp[512 + 1]               = {0};
    
    
    fpub_InitSoComp(lXmlhandle);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_TRIMMSG...����ʼ"), "INFO") 
    
    COMP_PARACOUNTCHK(1);
    
    memset(cTmp, 0x00, sizeof(cTmp));
    memset(cRootNodeName, 0x00, sizeof(cRootNodeName));
    COMP_GETPARSEPARAS(1, cTmp, "���Ľڵ���");
    pstrcopy(cRootNodeName, cTmp, sizeof(cRootNodeName));
    LOG(LM_DEBUG, Fmtmsg("���Ľڵ���[%s]", cRootNodeName), "INFO")
    
    prv_trimLeafNodeValue(lXmlhandle, cRootNodeName);
    
    LOG(LM_DEBUG, Fmtmsg("SYW_TIPS_TRIMMSG...�������"), "INFO")
    fpub_SetCompStatus(lXmlhandle, 0);
    return 0;
}

void prv_trimLeafNodeValue(HXMLTREE lXmlhandle, const char* cRootNodeName)
{
    int    iElementCount               = 0;
    int    iRepeats                    = 0;
    char   cSubNodeName[64 + 1]        = {0};
    char   cValue[10*1024 + 1]         = {0};
    char   cNodePath[1024 + 1]         = {0};
    
    iElementCount = xml_ChildElementCount(lXmlhandle, cRootNodeName);
    //LOG(LM_DEBUG, Fmtmsg("�ڵ���[%d]", iElementCount), "INFO")
    
    if (0 != iElementCount)
    {
        iRepeats = 0;
        while (iRepeats < iElementCount)
        {
            if (0 == xml_GetChildElementName(lXmlhandle, cRootNodeName, iRepeats + 1, cSubNodeName, sizeof(cSubNodeName)))
            {
                sprintf(cNodePath, "%s/%s", cRootNodeName, cSubNodeName);
                if (1 == xml_IsLeafNode(lXmlhandle, cNodePath))
                {
                    //LOG(LM_DEBUG, Fmtmsg("�ڵ�[%s]��Ҷ�ӽڵ�", cNodePath), "INFO")
                    memset(cValue, 0x00, sizeof(cValue));
                    COMP_SOFTGETXML(cNodePath, cValue);
                    trim(cValue);
                    COMP_SOFTSETXML(cNodePath, cValue);
					iRepeats++;
                }
                else if (1 == xml_ElementExist(lXmlhandle, cNodePath))
                {
                    //LOG(LM_DEBUG, Fmtmsg("�ڵ�[%s]��Ҷ�ӽڵ�", cNodePath), "INFO")
                    prv_trimLeafNodeValue(lXmlhandle, cNodePath);
					iRepeats++;
                }
                else
                {
                    LOG(LM_DEBUG, Fmtmsg("�����쳣����"), "INFO")
                    break;
                }
            }
        }
    }
}