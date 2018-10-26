#ifndef __PABYBH_DEPCHKINFO_H__
#define __PABYBH_DEPCHKINFO_H__ 

typedef struct TDB_PABYBH_DEPCHKINFO
{
char   CHECKDATE    [8+1];         /*对账日期                    */ 
char   TRANSDATE    [8+1];         /*交易日期                    */
char   TRANSTIME    [6+1];         /*交易时间                    */
char   TRANSFERTYPE [1+1];         /*资金类型'0--银转证1--证转银'*/
char   ACCTNO       [32+1];        /*银行账号                    */
char   STOCKCODE    [8+1];         /*券商代码                    */
char   CAPITALACCTNO[30+1];        /*证券资金台账号              */
double AMT                ;        /*金额                        */
char   WORKSERIALNO [30+1];        /*合作行流水号                */
char   IEPSERIALNO  [30+1];        /*行E通流水号                 */
char   COBANKNO     [12+1];        /*合作行号                    */
char   EXTFLD1      [32+1];        /*备用字段1                   */
char   EXTFLD2      [64+1]         /*备用字段2                   */
}PABYBH_DEPCHKINFO;	

#define SD_DATA  PABYBH_DEPCHKINFO
#define SD_MEMBERS \
		DEFSDMEMBER(T_STRING,   CHECKDATE    , 0),\ 
		DEFSDMEMBER(T_STRING,   TRANSDATE    , 0),\
		DEFSDMEMBER(T_STRING,   TRANSTIME    , 0),\
		DEFSDMEMBER(T_STRING,   TRANSFERTYPE , 0),\
		DEFSDMEMBER(T_STRING,   ACCTNO       , 0),\
		DEFSDMEMBER(T_STRING,   STOCKCODE    , 0),\
		DEFSDMEMBER(T_STRING,   CAPITALACCTNO, 0),\
		DEFSDMEMBER(T_DOUBLE,   AMT          , 0),\
		DEFSDMEMBER(T_STRING,   WORKSERIALNO , 0),\
		DEFSDMEMBER(T_STRING,   IEPSERIALNO  , 0),\
		DEFSDMEMBER(T_STRING,   COBANKNO     , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD1      , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD2      , 0)
 

  DECLAREFIELDS(SD_PABYBH_DEPCHKINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PABYBH_DEPCHKINFO_H__*/
