#ifndef __PABYBH_CUSTINFO_H__
#define __PABYBH_CUSTINFO_H__ 

typedef struct TDB_PABYBH_CUSTINFO
{
		char CERTTYPE   [2+1];    /*֤������      */
		char CERTNO     [32+1];   /*֤������      */
		char CUSTTYPE   [2+1];    /*�ͻ�����      */
		char CUSTNAME   [120+1];  /*�ͻ�����      */
		char POST       [6+1];    /*��������      */
		char ADDR       [128+1];  /*��ϵ��ַ      */
		char EMAIL      [120+1];  /*�����ʼ���ַ  */
		char PHONE      [16+1];   /*��ϵ�绰      */
		char MOBILE     [11+1];   /*�ƶ��绰      */
		char FAX        [16+1];   /*����          */
		char UPDATEDATE [8+1];    /*��������      */
		char UPDATETIME [6+1];    /*����ʱ��      */
		char CREATEDATE [8+1];	  /*��������      */
		char CREATETIME [6+1];	  /*����ʱ��      */
		char EXTFLD1    [32+1];   /*�����ֶ�1     */
		char EXTFLD2    [64+1];   /*�����ֶ�2     */
		char EXTFLD3    [64+1]    /*�����ֶ�3     */
}PABYBH_CUSTINFO;	

#define SD_DATA  PABYBH_CUSTINFO
#define SD_MEMBERS \
		DEFSDMEMBER(T_STRING, CERTTYPE  , 0),\
		DEFSDMEMBER(T_STRING, CERTNO    , 0),\
		DEFSDMEMBER(T_STRING, CUSTTYPE  , 0),\
		DEFSDMEMBER(T_STRING, CUSTNAME  , 0),\
		DEFSDMEMBER(T_STRING, POST      , 0),\
		DEFSDMEMBER(T_STRING, ADDR      , 0),\
		DEFSDMEMBER(T_STRING, EMAIL     , 0),\
		DEFSDMEMBER(T_STRING, PHONE     , 0),\
		DEFSDMEMBER(T_STRING, MOBILE    , 0),\
		DEFSDMEMBER(T_STRING, FAX       , 0),\
		DEFSDMEMBER(T_STRING, UPDATEDATE, 0),\
		DEFSDMEMBER(T_STRING, UPDATETIME, 0),\
		DEFSDMEMBER(T_STRING, CREATEDATE, 0),\
		DEFSDMEMBER(T_STRING, CREATETIME, 0),\
		DEFSDMEMBER(T_STRING, EXTFLD1   , 0),\
		DEFSDMEMBER(T_STRING, EXTFLD2   , 0),\
		DEFSDMEMBER(T_STRING, EXTFLD3   , 0)  

  DECLAREFIELDS(SD_PABYBH_CUSTINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PABYBH_CUSTINFO_H__*/
