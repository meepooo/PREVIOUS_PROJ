/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:AGENT_RZZT.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:AGENT_RZZT (����״̬��)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __AGENT_RZZT_H__
#define __AGENT_RZZT_H__
typedef struct TDB_AGENT_RZZT
{
  char   ywbh[16+1];         /*ҵ����*/
              /**/
  char   ptrq[8+1];          /*ƽ̨����*/
              /**/
  char   ywrq[8+1];          /*ҵ������*/
              /**/
  char   zjmxdzzt[1+1];      /*������ϸ����״̬*/
              /**/
  char   zjzzdzzt[1+1];       /*�����ܶ���״̬*/
              /**/
  char   dsfmxdzzt[1+1];     /*��������ϸ����״̬*/
              /**/
  char   dsfzzdzzt[1+1];      /*�������ܶ���״̬*/
              /**/
  double  zjzje;             /*���������ܽ��*/
              /**/
  int    zjzbs;              /*���������ܱ���*/
  
  double  dsfzje;            /*�����������ܽ��*/
              /**/
  int    dsfzbs;             /*�����������ܱ���*/
              /**/
  char   gdzt[1+1];          /*�鵵״̬*/
              /**/
  char   qlzt[1+1];          /*����״̬*/
              /**/
  char   extfld1[20+1];
  char   extfld2[20+1];
}AGENT_RZZT;

#define SD_DATA  AGENT_RZZT
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  zjmxdzzt, 0),\
	DEFSDMEMBER(T_STRING,  zjzzdzzt, 0),\
	DEFSDMEMBER(T_STRING,  dsfmxdzzt, 0),\
	DEFSDMEMBER(T_STRING,  dsfzzdzzt, 0),\
	DEFSDMEMBER(T_DOUBLE,  zjzje, 2),\
	DEFSDMEMBER(T_LONG,  zjzbs, 0),\
	DEFSDMEMBER(T_DOUBLE,  dsfzje, 2),\
	DEFSDMEMBER(T_LONG,  dsfzbs, 0),\
	DEFSDMEMBER(T_STRING,  gdzt, 0),\
	DEFSDMEMBER(T_STRING,  qlzt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_AGENT_RZZT)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __AGENT_RZZT_H__*/

