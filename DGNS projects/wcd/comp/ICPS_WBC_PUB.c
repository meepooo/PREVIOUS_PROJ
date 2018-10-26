#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#include "gaps_head.h"
#include "../incl/icps_head.h"
#include "../incl/ICPS_ALLTABLES.h"

/************************************************************************
��̬�����������
�����������:ICPS_GEN_MSG_ID
�������:ICPS_GEN_MSG_ID
�������: ���ɵ��������ı�ʾ��
�������:
 ��� ��������  ��������                ��Դ���         ȱʡֵ           �ɿ�  ����˵��
  1   1-����   ��ϸ�ļ���               XML�����ַ���                      N    ��ϸ�ļ���
ʹ������:
�� �� Ա:
��������:2009��12��11��
�޸�����:
����ʹ��ʾ��:
************************************************************************/
IRESULT ICPS_GEN_MSG_ID(HXMLTREE lXmlhandle)
{
    int iRet = -1;
    char sBuf[255];
    char sMsg_Id[64 + 1]; /*���ı�ʾ��*/

    PARA_GENMSGID st_para_genmsgid;

    memset(&st_para_genmsgid, 0, sizeof(st_para_genmsgid));
    ICPS_GETPARSEPARAS_STRING_NOTNULL(1, sBuf, st_para_genmsgid.busi_no, "ҵ����");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(2, sBuf, st_para_genmsgid.plt_date, "ƽ̨����");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(3, sBuf, st_para_genmsgid.plt_serial, "ƽ̨��ˮ��");
    ICPS_GETPARSEPARAS_STRING_NOTNULL(4, sBuf, st_para_genmsgid.msg_id_path, "���ı�ʾ�Ŵ��·��");

    LOG(LM_STD,
            Fmtmsg("ҵ����=[%s],ƽ̨����=[%s],ƽ̨��ˮ��=[%s]\n���ı�ʾ�Ŵ��·��=[%s]", st_para_genmsgid.busi_no, st_para_genmsgid.plt_date,
                    st_para_genmsgid.plt_serial, st_para_genmsgid.msg_id_path), "INFO");

    /*�ж�ҵ���ţ���ֻ֧�ֽ���*/
    if (0 == strcmp(st_para_genmsgid.busi_no, "jiebei"))
    {
        snprintf(sMsg_Id, sizeof(sMsg_Id), "%08.8s%08d", st_para_genmsgid.plt_date, atol(st_para_genmsgid.plt_serial));
        LOG(LM_STD, Fmtmsg("���ı�ʾ��=[%s]", sMsg_Id), "INFO");
    }
    else
    {
        LOG(LM_STD, Fmtmsg("�ݲ�֧�ֵ�ҵ��"), "ERROR")
        fpub_SetMsg(lXmlhandle, 99999, "�ݲ�֧�ֵ�ҵ��");
        fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
        return COMPRET_FAIL;
    }

    COMP_SOFTSETXML(st_para_genmsgid.msg_id_path, sMsg_Id);

    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
    return COMPRET_SUCC;
}
