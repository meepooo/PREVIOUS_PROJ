/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_zygsbw.eh
�ļ�����:tips_zygsbw;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_zygsbw (���ɸ�ʽ����)
˵    ��:���ɸ�ʽ����
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_ZYGSBW_EH__
#define __TIPS_ZYGSBW_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_ZYGSBW
{
  char   zwrq[8+1];              /*��������*/
              /*��������,��Ӧ������������������*/
  int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
              /*�ۺ�ǰ����ˮ��
                ƽ̨�Զ����ɵ����*/
  char   workdate[8+1];              /*��������*/
              /*���׺�ʱ
                ��λ��ms*/
  char   msgtype[1+1];              /*��Ϣ����*/
              /*��Ϣ����
                1-���� 2-����
                */
  char   srcnodecode[12+1];              /*Դ�ڵ����*/
              /*Դ�ڵ����
                �������ɸ�ʽ���Ľ��׵�ԭʼ�ڵ����*/
  char   desnodecode[12+1];              /*Ŀ�Ľڵ����*/
              /*Ŀ�Ľڵ����
                �������ɸ�ʽ���Ľ��׵�����Ŀ�Ľڵ����*/
  char   sendorgcode[12+1];              /*�����������*/
              /*�����������
                ��Ϣ�����߻������롣�������ɸ�ʽ�������շ���Ϊ��������������*/
  char   rcvorgcode[12+1];              /*���ջ�������*/
              /*���ջ�������
                ��Ϣ�����߻������롣�������ɸ�ʽ�������ս��ܷ�Ϊ��������������*/
  char   ydbz[1+1];              /*�Ķ���־*/
              /*�Ķ���־
                ���ձ��ĵ��Ķ�״̬��
                0 δ�Ķ�
                1 ���Ķ�
                */
  char   content[2048+1];              /*����*/
              /*����
                ���ɸ�ʽ����*/
  char   jyrq[8+1];              /*��������*/
              /*��������*/
  char   jysj[8+1];              /*����ʱ��*/
              /*����ʱ��*/
  char   dqdh[10+1];              /*��������*/
              /*��������
                ����ʱ��Ϊ���ͱ��ĵĲ���Ա��������
                ����ʱ��Ϊ��һ���Ķ����ĵĲ���Ա��������
                */
  char   jgdh[10+1];              /*��������*/
              /*��������
                ����ʱ��Ϊ���ͱ��ĵĲ���Ա��������
                ����ʱ��Ϊ��һ���Ķ����ĵĲ���Ա��������
                */
  char   jygy[16+1];              /*���׹�Ա*/
              /*����Ա��
                ����ʱ��Ϊ���ͱ��ĵĲ���Ա����
                ����ʱ��Ϊ��һ���Ķ����ĵĲ���Ա����*/
  char   zddh[16+1];              /*�ն˴���*/
              /**/
  char   byzd[128+1];              /*�����ֶ�*/
              /*�����ֶ�*/
}SDB_TIPS_ZYGSBW;

#define SD_DATA SDB_TIPS_ZYGSBW
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,msgtype,0),\
  DEFSDMEMBER(T_STRING,srcnodecode,0),\
  DEFSDMEMBER(T_STRING,desnodecode,0),\
  DEFSDMEMBER(T_STRING,sendorgcode,0),\
  DEFSDMEMBER(T_STRING,rcvorgcode,0),\
  DEFSDMEMBER(T_STRING,ydbz,0),\
  DEFSDMEMBER(T_STRING,content,0),\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jysj,0),\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_ZYGSBW)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_ZYGSBW_EH__*/
