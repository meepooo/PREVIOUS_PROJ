#ifndef __PABYBH_CUSTINFO_H__
#define __PABYBH_CUSTINFO_H__ 

typedef struct TDB_PABYBH_CUSTINFO
{
		char CERTTYPE   [2+1];    /*证件类型      */
		char CERTNO     [32+1];   /*证件号码      */
		char CUSTTYPE   [2+1];    /*客户类型      */
		char CUSTNAME   [120+1];  /*客户名称      */
		char POST       [6+1];    /*邮政编码      */
		char ADDR       [128+1];  /*联系地址      */
		char EMAIL      [120+1];  /*电子邮件地址  */
		char PHONE      [16+1];   /*联系电话      */
		char MOBILE     [11+1];   /*移动电话      */
		char FAX        [16+1];   /*传真          */
		char UPDATEDATE [8+1];    /*更新日期      */
		char UPDATETIME [6+1];    /*更新时间      */
		char CREATEDATE [8+1];	  /*创建日期      */
		char CREATETIME [6+1];	  /*创建时间      */
		char EXTFLD1    [32+1];   /*备用字段1     */
		char EXTFLD2    [64+1];   /*备用字段2     */
		char EXTFLD3    [64+1]    /*备用字段3     */
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
