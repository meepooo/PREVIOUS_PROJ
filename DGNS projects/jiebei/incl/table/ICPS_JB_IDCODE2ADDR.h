/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϷ���ƽ̨(GAPS)��Ŀ
��    ��:V1.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:ORACLE
�� �� ��:icps_jb_idcode2addr.h
�ļ�����:ICPS_JB_IDCODE2ADDR;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:����֧�������Ʒ��
�� �� Ա:
����ʱ��:2017-08-10 15:06:30 [By qinsb@hundsun.com]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:ICPS_JB_IDCODE2ADDR ()
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __ICPS_JB_IDCODE2ADDR_H__
#define __ICPS_JB_IDCODE2ADDR_H__

typedef struct
{
    char	id6code[6+1];         /*���֤ǰ6λ����*/
    char	shrtnm[60+1];         /*������*/
    char	fullnm[100+1];        /*����ȫ��*/
    char	upcode[6+1];          /*�ϼ�����*/
    char	lvl[1+1];             /*�㼶*/
}ST_ICPS_JB_IDCODE2ADDR;
#define SD_DATA  ST_ICPS_JB_IDCODE2ADDR
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,id6code, 0),\
    DEFSDMEMBER(T_STRING,shrtnm, 0),\
    DEFSDMEMBER(T_STRING,fullnm, 0),\
    DEFSDMEMBER(T_STRING,upcode, 0),\
    DEFSDMEMBER(T_STRING,lvl, 0)
DECLAREFIELDS(SD_ICPS_JB_IDCODE2ADDR)
#undef SD_DATA
#undef SD_MEMBERS

#endif
