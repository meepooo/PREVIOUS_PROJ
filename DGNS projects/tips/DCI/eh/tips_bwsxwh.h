/***********************************************************************
��Ȩ����:��������TIPSר��ǰ�ò�Ʒ��
��Ŀ����:TIPSר��ǰ�ò�Ʒ
��    ��:V3.0
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:INFORMIX
�� �� ��:tips_bwsxwh.eh
�ļ�����:tips_bwsxwh;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:TIPSר��ǰ�ò�Ʒ��
�� �� Ա:
����ʱ��:2009-3-19 14:48:58 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:tips_bwsxwh (��������ά����)
˵    ��:TIPS��������ά�����ı�š��������͡��������͡���֧���͡��˶Ա�־����Ϣ��
��������һ����SQL���г�ʼ��
�޸Ĵ˱�Ҫ��Ȩ
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __TIPS_BWSXWH_EH__
#define __TIPS_BWSXWH_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif


typedef struct TDB_TIPS_BWSXWH
{
  char   msgno[4+1];              /*���ı��*/
              /**/
  char   bwmc[40+1];              /*��������*/
              /**/
  char   bwlx[4+1];              /*��������*/
              /*�������ͣ�send-���ͱ��� recv-���ձ���*/
  char   bwms[1+1];              /*����ģʽ*/
              /*tips�ӿڵı���ģʽ
                ����6��ģʽ*/
  char   ywhz[4+1];              /*ҵ���ִ*/
              /*ҵ���ִ����Ӧ���ı��(����)*/
  char   ycydtz1[4+1];              /*�쳣Ӧ��֪ͨ1*/
              /*����ʱ���صı��ı��1*/
  char   ycydtz2[4+1];              /*�쳣Ӧ��֪ͨ2*/
              /**/
  char   ssdl[1+1];              /*��������*/
              /*������������ O-ʵʱ(����)���ģ�B-��������*/
  char   sfcj[1+1];              /*�Ƿ�־�*/
              /*�Ƿ��ǳ־ö��� 0-�� 1-��*/
  char   sfgq[1+1];              /*�Ƿ����*/
              /*0-������(��) 1-����*/
  char   bwppjz[3+1];              /*����ƥ�����*/
              /*����ƥ�����
                ��һλ MQ��ϢID 0-�� 1-��
                �ڶ�λ ���Ĳο��� 0-�� 1-��
                ����λ ҵ��Ҫ�� 0-�� 1-��*/
  char   byzd[40+1];              /*�����ֶ�*/
              /**/
}SDB_TIPS_BWSXWH;

#define SD_DATA SDB_TIPS_BWSXWH
#define	 SD_MEMBERS\
  DEFSDMEMBER(T_STRING,msgno,0),\
  DEFSDMEMBER(T_STRING,bwmc,0),\
  DEFSDMEMBER(T_STRING,bwlx,0),\
  DEFSDMEMBER(T_STRING,bwms,0),\
  DEFSDMEMBER(T_STRING,ywhz,0),\
  DEFSDMEMBER(T_STRING,ycydtz1,0),\
  DEFSDMEMBER(T_STRING,ycydtz2,0),\
  DEFSDMEMBER(T_STRING,ssdl,0),\
  DEFSDMEMBER(T_STRING,sfcj,0),\
  DEFSDMEMBER(T_STRING,sfgq,0),\
  DEFSDMEMBER(T_STRING,bwppjz,0),\
  DEFSDMEMBER(T_STRING,byzd,0)
	DECLAREFIELDS(SD_TIPS_BWSXWH)
#undef SD_DATA
#undef SD_MEMBERS
#endif  /*end of __TIPS_BWSXWH_EH__*/
