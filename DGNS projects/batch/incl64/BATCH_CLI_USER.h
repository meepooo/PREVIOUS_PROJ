/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:BATCH_CLI_USER.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:BATCH_CLI_USER (�����ͻ���_�û���Ϣ��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __BATCH_CLI_USER_H__
#define __BATCH_CLI_USER_H__
typedef struct TDB_BATCH_CLI_USER
{
  char   contract_no[32+1];              /*Э����*/
              /**/
  char   user_id[32+1];              /*�û�ID*/
              /**/
  char   user_name[80+1];              /*�û���*/
              /**/
  char   contact[32+1];              /*��ϵ��*/
              /**/
  char   phone[16+1];              /*�绰����*/
              /**/
  char   mobile[12+1];              /*�ֻ���*/
              /**/
  char   email[50+1];              /*EMAIL*/
              /**/
  char   ptrq[8+1];              /*�Ǽ�����*/
              /**/
  char   tran_time[6+1];              /*�Ǽ�ʱ��*/
              /**/
  char   ptls[16+1];              /*�Ǽ���ˮ*/
              /**/
  char   branch[16+1];              /*�Ǽǻ���*/
              /**/
  char   oper[16+1];              /*�Ǽǹ�Ա*/
              /**/
  char   acct_manager[32+1];              /*�ͻ�����*/
              /**/
  char   acct_name[80+1];              /*ǩԼ����*/
              /**/
  char   acct_no[32+1];              /*ǩԼ�˺�*/
              /**/
  char   status[1+1];              /*ǩԼ״̬*/
              /*0 δ����
                n ����n��
                */
  long    send_flag;              /*���ͱ�־*/
              /*0 δ����
                n ����n��
                */
  char   key[32+1];              /*KEY*/
              /**/
  char   extfld1[16+1];              /*��չ�ֶ�һ*/
              /**/
  char   extfld2[32+1];              /*��չ�ֶζ�*/
              /**/
  char   extfld3[50+1];              /*��չ�ֶ���*/
              /**/
  char   extfld4[64+1];              /*��չ�ֶ���*/
              /**/
}BATCH_CLI_USER;

#define SD_DATA  BATCH_CLI_USER
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  contract_no, 0),\
	DEFSDMEMBER(T_STRING,  user_id, 0),\
	DEFSDMEMBER(T_STRING,  user_name, 0),\
	DEFSDMEMBER(T_STRING,  contact, 0),\
	DEFSDMEMBER(T_STRING,  phone, 0),\
	DEFSDMEMBER(T_STRING,  mobile, 0),\
	DEFSDMEMBER(T_STRING,  email, 0),\
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  tran_time, 0),\
	DEFSDMEMBER(T_STRING,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  branch, 0),\
	DEFSDMEMBER(T_STRING,  oper, 0),\
	DEFSDMEMBER(T_STRING,  acct_manager, 0),\
	DEFSDMEMBER(T_STRING,  acct_name, 0),\
	DEFSDMEMBER(T_STRING,  acct_no, 0),\
	DEFSDMEMBER(T_STRING,  status, 0),\
	DEFSDMEMBER(T_LONG,  send_flag, 0),\
	DEFSDMEMBER(T_STRING,  key, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0),\
	DEFSDMEMBER(T_STRING,  extfld4, 0)


	DECLAREFIELDS(SD_BATCH_CLI_USER)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_CLI_USER_H__*/
