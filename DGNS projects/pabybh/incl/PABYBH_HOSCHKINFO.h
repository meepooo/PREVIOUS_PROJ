#ifndef __PABYBH_HOSCHKINFO_H__
#define __PABYBH_HOSCHKINFO_H__ 

typedef struct TDB_PABYBH_HOSCHKINFO
{
		char   COBANKNO     [10+1];          /*�����к�                                */
		char   CHECKDATE    [8+1];           /*��������                                */
		char   WORKSERIALNO [32+1];          /*ƽ̨ҵ����ˮ��                          */
		char   HOSTDATE     [8+1];           /*��������                                */
		char   HOSTSERIALNO [32+1];          /*������ˮ��                              */
		char   HOSTBACKDATE [8+1];           /*������������                            */
		char   HOSTBACKSERNO[32+1];          /*����������ˮ��                          */
		char   HOSTTRANSCODE[16+1];          /*���Ľ��״���                            */
		char   ACCTNO       [32+1];          /*�˺�                                    */
		double TRANSAMT           ;          /*���׽��                                */
		double TRANSFARE          ;          /*������                                  */
		char   CASHFLAG     [1+1];           /*��ת��־1-�ֽ� 2-ת��                   */
		char   STAT         [1+1];           /*����״̬0-���� 7-������ 8-������ 1-ʧ�� */
		char   CDFLAG       [1+1];           /*�����־                                */
		char   SVRTYPE      [10+1];          /*ҵ������                                */
		char   REMARKCODE   [32+1];          /*ժҪ��                                  */
		char   REMARK       [50+1];          /*ժҪ��Ϣ                                */
		char   TRANSBRANCHNO[10+1];          /*��������                                */
		char   TRANSORG     [10+1];          /*���׻���                                */
		char   TRANSOPER    [10+1];          /*���׹�Ա                                */
		char   JOINCHKFLAG  [1+1];           /*������˱�־��0-�����룬1-����          */
		char   EXTFLD1      [32+1];          /*�����ֶ�1                               */
		char   EXTFLD2      [64+1];          /*�����ֶ�2                               */
		char   EXTFLD3      [64+1]           /*�����ֶ�3                               */

}PABYBH_HOSCHKINFO;	

#define SD_DATA  PABYBH_HOSCHKINFO
#define SD_MEMBERS \
		DEFSDMEMBER(T_STRING,   COBANKNO     , 0),\
		DEFSDMEMBER(T_STRING,   CHECKDATE    , 0),\
		DEFSDMEMBER(T_STRING,   WORKSERIALNO , 0),\
		DEFSDMEMBER(T_STRING,   HOSTDATE     , 0),\
		DEFSDMEMBER(T_STRING,   HOSTSERIALNO , 0),\
		DEFSDMEMBER(T_STRING,   HOSTBACKDATE , 0),\
		DEFSDMEMBER(T_STRING,   HOSTBACKSERNO, 0),\
		DEFSDMEMBER(T_STRING,   HOSTTRANSCODE, 0),\
		DEFSDMEMBER(T_STRING,   ACCTNO       , 0),\
		DEFSDMEMBER(T_DOUBLE,   TRANSAMT     , 0),\
		DEFSDMEMBER(T_DOUBLE,   TRANSFARE    , 0),\
		DEFSDMEMBER(T_STRING,   CASHFLAG     , 0),\
		DEFSDMEMBER(T_STRING,   STAT         , 0),\
		DEFSDMEMBER(T_STRING,   CDFLAG       , 0),\
		DEFSDMEMBER(T_STRING,   SVRTYPE      , 0),\
		DEFSDMEMBER(T_STRING,   REMARKCODE   , 0),\
		DEFSDMEMBER(T_STRING,   REMARK       , 0),\
		DEFSDMEMBER(T_STRING,   TRANSBRANCHNO, 0),\
		DEFSDMEMBER(T_STRING,   TRANSORG     , 0),\
		DEFSDMEMBER(T_STRING,   TRANSOPER    , 0),\
		DEFSDMEMBER(T_STRING,   JOINCHKFLAG  , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD1      , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD2      , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD3      , 0)

  DECLAREFIELDS(SD_PABYBH_HOSCHKINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PABYBH_HOSCHKINFO_H__*/
