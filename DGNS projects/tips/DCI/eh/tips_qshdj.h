/***********************************************************************
��Ȩ����:��ҵ���пƼ��������з�����
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_qshdj.eh
�ļ�����:tips_qshdj;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_qshdj (��ҵ���������еǼǱ�)
˵    ��:�����еǼǱ�
������Ӧ���ʺ�,��Բ�ͬ�Ļ���,
�ǼǴ����ʺż������˺���ʹ�õ�ҵ�����/���
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_QSHDJ_EH__
#define __TIPS_QSHDJ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_QSHDJ
{
  char   dqdh[10+1];              /*��������*/
              /*��������*/
  char   jgdh[10+1];              /*��������*/
              /*�������*/
  char   yybs[30+1];              /*Ӧ�ñ�ʶ*/
              /*Ӧ�ñ�ʶ
                �����ڲ�ͬ��ʹ����,������Ӧ����ʺ�ʹ��
                ȱʡΪTIPS*/
  char   dfzh[32+1];              /*�����˺�*/
              /*�����˺�ҵ�����
                ���������ۿ�׼����ʽ��׼����ʺ�
                */
  char   gzzh[32+1];              /*�����˺�*/
              /*�����˺�ҵ�����
                ���ڹ��ʽ���(������),�����˺�*/
  char   paybkcode[12+1];              /*�������к�*/
              /*������ӦTIPSϵͳ�е�֧��ϵͳ�к�(������)
                */
  char   paybkname[12+1];              /*����������*/
              /*������ӦTIPSϵͳ�е�֧��ϵͳ������
                */
  char   note[50+1];              /*˵����Ϣ*/
              /*˵����Ϣ*/
  char   modidate[8+1];              /*��������*/
              /*��������*/
  char   modiinfo[50+1];              /*����˵����Ϣ*/
              /*����˵����Ϣ
                ϵͳ�Զ��������һ�β�������Ϣ*/
  char   kzbz[8+1];              /*��չ��־*/
              /*��չ��־
                �����Զ�����չ*/
  char   byzd[80+1];              /*�����ֶ�*/
              /*�����ֶ�*/
}SDB_TIPS_QSHDJ;

#define SD_DATA SDB_TIPS_QSHDJ
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,yybs,0),\
  DEFSDMEMBER(T_STRING,dfzh,0),\
  DEFSDMEMBER(T_STRING,gzzh,0),\
  DEFSDMEMBER(T_STRING,paybkcode,0),\
  DEFSDMEMBER(T_STRING,paybkname,0),\
  DEFSDMEMBER(T_STRING,note,0),\
  DEFSDMEMBER(T_STRING,modidate,0),\
  DEFSDMEMBER(T_STRING,modiinfo,0),\
  DEFSDMEMBER(T_STRING,kzbz,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_QSHDJ)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_QSHDJ_EH__*/
