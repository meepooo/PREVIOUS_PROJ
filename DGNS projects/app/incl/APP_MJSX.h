/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:INFORMIX
�� �� ��:APP_MJSX.h
�ļ�����:�ṹ�������ݿ⿪��ǶCͷ�ļ�
�� Ŀ ��:
�� �� Ա:[�]
����ʱ��:2009-4-29 19:40:39 [Gen]
��    ��:
�޸�ʱ��:
************************************************************************
��    ��:APP_MJSX (ö�����Կ��Ʊ�)
˵    ��:
************************************************************************
�޸ļ�¼:
�޸�����:
�޸�����:
�� �� ��:
�޸�����:
************************************************************************/
#ifndef __APP_MJSX_H__
#define __APP_MJSX_H__
typedef struct TDB_APP_MJSX
{
  char   mjid[16+1];              /*ö��ID*/
              /*ö��ID*/
  char   mjsm[40+1];              /*ö��˵��*/
              /*ö��˵��*/
  char   sxlx[1+1];              /*��������*/
              /*�������� 1���� 2���*/
  char   sxxh[2+1];              /*�������*/
              /*���Ը����������ͣ���1��ʼ�����ܴ���10�����ϵ���λ�����Ӧ*/
  char   sxmc[16+1];              /*��������*/
              /*��������*/
  char   sxnr[40+1];              /*��������λ��*/
              /*�������Ϊ��������ʾ���ݵ���Դ���������Ϊ��������ݵ�Ŀ��*/
  char   sxsm[40+1];              /*����˵��*/
              /*���Ե�����˵��*/
  char   whjg[16+1];              /*ά������*/
              /**/
  char   whgy[16+1];              /*ά����Ա*/
              /**/
  char   whsj[14+1];              /*ά��ʱ��*/
              /**/
}APP_MJSX;

#define SD_DATA  APP_MJSX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mjid, 0),\
	DEFSDMEMBER(T_STRING,  mjsm, 0),\
	DEFSDMEMBER(T_STRING,  sxlx, 0),\
	DEFSDMEMBER(T_STRING,  sxxh, 0),\
	DEFSDMEMBER(T_STRING,  sxmc, 0),\
	DEFSDMEMBER(T_STRING,  sxnr, 0),\
	DEFSDMEMBER(T_STRING,  sxsm, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_APP_MJSX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_MJSX_H__*/

