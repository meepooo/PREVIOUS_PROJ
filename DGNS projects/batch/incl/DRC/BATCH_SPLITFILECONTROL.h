/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_SPLITFILECONTROL.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�����]
����ʱ��:2017-7-20 09:04:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_SPLITFILECONTROL (����ƽ̨�ļ��ָ���Ʊ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_SPLITFILECONTROL_H__
#define __BATCH_SPLITFILECONTROL_H__
typedef struct TDB_BATCH_SPLITFILECONTROL
{
    char    host_batch_no[26+1];
    char    host_no[2+1];
    char    o_file_req[512+1];
    char    file_req[512+1];
    char    file_resp[512+1];
    char    n_file_resp[512+1];
    char    state[1+1];
    char    remark1[10+1];
    char    remark2[20+1];
    char    remark3[50+1];
    char    remark4[100+1];
    char    remark5[200+1];
}BATCH_SPLITFILECONTROL;

#define SD_DATA  BATCH_SPLITFILECONTROL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  host_batch_no, 0),\
	DEFSDMEMBER(T_STRING,  host_no, 0),\
	DEFSDMEMBER(T_STRING,  o_file_req, 0),\
	DEFSDMEMBER(T_STRING,  file_req, 0),\
	DEFSDMEMBER(T_STRING,  file_resp, 0),\
	DEFSDMEMBER(T_STRING,  n_file_resp, 0),\
	DEFSDMEMBER(T_STRING,  state, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0),\
	DEFSDMEMBER(T_STRING,  remark5, 0)

	DECLAREFIELDS(SD_BATCH_SPLITFILECONTROL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_SPLITFILECONTROL_H__*/
