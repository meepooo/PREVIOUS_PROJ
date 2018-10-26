#ifndef __PABYBH_HOSCHKINFO_H__
#define __PABYBH_HOSCHKINFO_H__ 

typedef struct TDB_PABYBH_HOSCHKINFO
{
		char   COBANKNO     [10+1];          /*合作行号                                */
		char   CHECKDATE    [8+1];           /*对账日期                                */
		char   WORKSERIALNO [32+1];          /*平台业务流水号                          */
		char   HOSTDATE     [8+1];           /*主机日期                                */
		char   HOSTSERIALNO [32+1];          /*主机流水号                              */
		char   HOSTBACKDATE [8+1];           /*主机冲正日期                            */
		char   HOSTBACKSERNO[32+1];          /*主机冲正流水号                          */
		char   HOSTTRANSCODE[16+1];          /*核心交易代码                            */
		char   ACCTNO       [32+1];          /*账号                                    */
		double TRANSAMT           ;          /*交易金额                                */
		double TRANSFARE          ;          /*手续费                                  */
		char   CASHFLAG     [1+1];           /*现转标志1-现金 2-转账                   */
		char   STAT         [1+1];           /*交易状态0-正常 7-被冲正 8-被撤销 1-失败 */
		char   CDFLAG       [1+1];           /*借贷标志                                */
		char   SVRTYPE      [10+1];          /*业务种类                                */
		char   REMARKCODE   [32+1];          /*摘要码                                  */
		char   REMARK       [50+1];          /*摘要信息                                */
		char   TRANSBRANCHNO[10+1];          /*交易网点                                */
		char   TRANSORG     [10+1];          /*交易机构                                */
		char   TRANSOPER    [10+1];          /*交易柜员                                */
		char   JOINCHKFLAG  [1+1];           /*参与对账标志，0-不参与，1-参与          */
		char   EXTFLD1      [32+1];          /*备用字段1                               */
		char   EXTFLD2      [64+1];          /*备用字段2                               */
		char   EXTFLD3      [64+1]           /*备用字段3                               */

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
