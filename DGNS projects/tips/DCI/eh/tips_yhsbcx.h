/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_yhsbcx.eh
�ļ�����:tips_yhsbcx;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-5 14:07:20 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_yhsbcx (�����걨��ѯ��)
˵    ��:˰�������걨��ѯ��
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_YHSBCX_EH__
#define __TIPS_YHSBCX_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_YHSBCX
{
  char   zwrq[8+1];              /*��������*/
              /*��Ӧ�����걨��ѯ���걨���׵�ί������*/
  int    zhqzlsh;              /*�ۺ�ǰ����ˮ��*/
              /*��Ӧ�����걨��ѯ���걨���׵Ĳ�ѯ���*/
  char   jyqd[10+1];              /*��������*/
              /*�������ַ����׵�����
                tips   tips����
                hx9996 hx9996ת�� */
  char   dqdh[10+1];              /*��������*/
              /**/
  char   jgdh[10+1];              /*��������*/
              /**/
  char   jygy[16+1];              /*���׹�Ա*/
              /**/
  char   zddh[16+1];              /*�ն˴���*/
              /**/
  char   workdate[8+1];              /*��������*/
              /*tips��������*/
  char   jyrq[8+1];              /*��������*/
              /*��������*/
  char   jysj[8+1];              /*����ʱ��*/
              /*����ʱ��*/
  char   bankno[12+1];              /*��ҵ�����к�*/
              /*��ҵ�����к�
                �����ѯ�������е�֧��ϵͳ�к�*/
  char   entrustdate[8+1];              /*ί������*/
              /*ʵʱ�ۿ�����������*/
  char   queryno[8+1];              /*��ѯ���*/
              /*��ѯ���
                ͬ�ۺ�ǰ����ˮ��
                */
  char   payopbkcode[12+1];              /*��������к�*/
              /*��������к�
                ָ��˰�˿������кţ����ջ��ر�����д*/
  char   bankname[60+1];              /*����������*/
              /*����������*/
  char   taxorgcode[12+1];              /*���ջ��ش���*/
              /*���ջ��ش���*/
  char   corpcode[20+1];              /*��ҵ����*/
              /*�տλ����
                ��ҵ���о���ʱ��ָ�տ��˿������кţ�
                ���⾭��ʱ��ָ�տ�������*/
  char   taxpaycode[20+1];              /*��˰�˱���*/
              /*��˰�˱���*/
  char   outerlevyno[20+1];              /*�ⲿ�걨�������*/
              /*�ⲿ�걨�������*/
  char   addword[12+1];              /*����*/
              /*����*/
  double  jyje;              /*���׽��*/
              /*���׽��
                ����ʵʱ�ۿ���ܽ��*/
  int    detailnum;              /*������ϸ��*/
              /**/
  char   result[5+1];              /*������*/
              /*������
                ���ظ�TIPS�Ĵ�����*/
  char   spxxwjm[40+1];              /*˰Ʊ��Ϣ�ļ���*/
              /*˰����ϸ
                payment1001��XML��ʽ��¼�����ڲ���˰Ʊ*/
}SDB_TIPS_YHSBCX;

#define SD_DATA SDB_TIPS_YHSBCX
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,zwrq,0),\
  DEFSDMEMBER(T_LONG,zhqzlsh,0),\
  DEFSDMEMBER(T_STRING,jyqd,0),\
  DEFSDMEMBER(T_STRING,dqdh,0),\
  DEFSDMEMBER(T_STRING,jgdh,0),\
  DEFSDMEMBER(T_STRING,jygy,0),\
  DEFSDMEMBER(T_STRING,zddh,0),\
  DEFSDMEMBER(T_STRING,workdate,0),\
  DEFSDMEMBER(T_STRING,jyrq,0),\
  DEFSDMEMBER(T_STRING,jysj,0),\
  DEFSDMEMBER(T_STRING,bankno,0),\
  DEFSDMEMBER(T_STRING,entrustdate,0),\
  DEFSDMEMBER(T_STRING,queryno,0),\
  DEFSDMEMBER(T_STRING,payopbkcode,0),\
  DEFSDMEMBER(T_STRING,bankname,0),\
  DEFSDMEMBER(T_STRING,taxorgcode,0),\
  DEFSDMEMBER(T_STRING,corpcode,0),\
  DEFSDMEMBER(T_STRING,taxpaycode,0),\
  DEFSDMEMBER(T_STRING,outerlevyno,0),\
  DEFSDMEMBER(T_STRING,addword,0),\
  DEFSDMEMBER(T_DOUBLE,jyje,2),\
  DEFSDMEMBER(T_LONG,detailnum,0),\
  DEFSDMEMBER(T_STRING,result,0),\
  DEFSDMEMBER(T_STRING,spxxwjm,0)
	DECLAREFIELDS(SD_TIPS_YHSBCX)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_YHSBCX_EH__*/
