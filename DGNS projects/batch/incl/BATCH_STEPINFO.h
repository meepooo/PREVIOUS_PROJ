/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_STEPINFO.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[������]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_STEPINFO (����������Ϣ)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_STEPINFO_H__
#define __BATCH_STEPINFO_H__
typedef struct TDB_BATCH_STEPINFO
{
    char   pkrq[8+1];           /*��������*/
    char   ptpch[8+1];          /*ƽ̨���κ�*/
    char   cpdm[16+1];          /*��Ʒ����*/
    char   ywbh[16+1];          /*ҵ����*/
    char   flowid[32+1];        /*���̱�ʶ*/
    char   ywb[32+1];           /*ҵ���*/
    char   zjysbs[32+1];        /*����ӳ���ʶ*/
    char   wwysbs[32+1];        /*��Χӳ���ʶ*/
    char   curstep[2+1];        /*��ǰ����*/
    char   curassstep[2+1];     /*��ǰ��������*/
    char   curstatus[1+1];      /*����״̬*/
    char   taskstatus[1+1];     /*����״̬*/
    char   nextstep[2+1];       /*��һ����*/
    char   stepid[32+1];        /*�����ʶ*/
    char   stepnm[32+1];        /*��������*/
    int    flowsn;              /*ִ�����*/
    char   extfld1[40+1];       /*��չ�ֶ�1*/
    char   extfld2[40+1];       /*��չ�ֶ�2*/
}BATCH_STEPINFO;

#endif  /*end of __BATCH_STEPINFO_H__*/