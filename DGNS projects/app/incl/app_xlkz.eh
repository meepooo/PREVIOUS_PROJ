/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϷ���ƽ̨(GAPS)��Ŀ
��    ��:V2.1
����ϵͳ:AIX SCO LINUX SunOS HP-UX
�� �� ��:DB2
�� �� ��:APP_XLKZ.eh
�ļ�����:APP_XLKZ;�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:����.��Ʒ����
�� �� Ա:SC
����ʱ��:2011-5-27 11:00:48 [By GenEHFromPDMTools]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_XLKZ (���п��Ʊ�)
˵    ��:���п��Ʊ�
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�޸�����:
�� �� ��:
************************************************************************/
#ifndef __APP_XLKZ_EH__
#define __APP_XLKZ_EH__
#ifdef DBS_ORACLE
  #include "gaps_lenmacro.eh"
#endif

EXEC SQL BEGIN DECLARE SECTION;
struct TDB_APP_XLKZ
{
  char   pkey[20+1];              /*KEYֵ*/
              /**/
  sqlint32    curr_value;              /*��ǰֵ*/
              /**/
  sqlint32    pinc;              /*����ֵ*/
              /**/
  sqlint32    min_value;              /*��Сֵ*/
              /**/
  sqlint32    max_value;              /*���ֵ*/
              /**/
  char   remark[40+1];              /*˵��*/
              /**/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
}sdb_app_xlkz;
EXEC SQL END DECLARE SECTION;
#endif  /*end of __APP_XLKZ_EH__*/
