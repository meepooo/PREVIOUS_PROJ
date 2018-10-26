#ifndef __PABYBH_NOTBAL_H__
#define __PABYBH_NOTBAL_H__ 

typedef struct TDB_PABYBH_NOTBAL
{
		char   CHECKDATE         [8+1];          /*对账日期                                                                        */
		char   COBANKNO          [12+1];         /*合作行号                                                                        */
		char   SVRCODE           [4+1];          /*服务代码                                                                        */
		char   TRANSFERTYPE      [1+1];          /*资金类型'0--出金，银转证1--证转银，入金'                                        */
		char   STOCKCODE         [8+1];          /*券商代码                                                                        */
		char   CAPITALACCTNO     [30+1];         /*证券资金台账号                                                                  */
		char   WORKSERIALNO      [30+1];         /*合作行流水号                                                                    */
		char   BANKSTAT          [1+1];          /*合作行状态                                                                      */
		char   BANKACCTNO        [32+1];         /*平台银行账号                                                                    */
		double BANKAMT           ;               /*平台交易金额                                                                    */
		char   BANKTRANSCODE		 [8+1];          /*平台交易代码                                                                    */
		char   IEPSERIALNO       [30+1];         /*行E通流水号                                                                     */
		char   IEPSTAT           [1+1];          /*行E通状态                                                                       */
		char   IEPACCTNO         [32+1];         /*行E通银行账号                                                                   */
		double IEPAMT                ;           /*行E通交易金额                                                                   */
		char   IEPTRANSCODE		   [8+1];          /*行E通交易代码                                                                   */
		char   HOSTDATE          [8+1];          /*主机日期                                                                        */
		char   HOSTSERIALNO      [30+1];         /*主机流水号                                                                      */
		char   HOSTSTAT          [1+1];          /*主机状态                                                                        */
		char   HOSTACCTNO        [32+1];         /*主机银行账号                                                                    */
		double HOSTAMT           ;               /*主机交易金额                                                                    */
		char   HOSTTRANSCODE		 [8+1];          /*主机交易代码                                                                    */
		char   CHECKSTAT         [1+1];          /*对账结果标志,0-未对账1-已对平2-平安多3-核心多  4-账号不符 5-金额不符 6-状态不符 */
		char   ADJUSTSTAT        [1+1];          /*调账状态 0-成功 1-失败 7-超时 9-初始                                            */
		char   ADJUSTTRANSORG    [10+1];         /*调账交易机构                                                                    */
		char   ADJUSTTRANSOPER   [10+1];         /*调账交易柜员                                                                    */
		char   ADJUSTDATE        [8+1];          /*调账日期                                                                        */
		char   ADJUSTSERIALNO    [32+1];         /*调账业务流水号                                                                  */
		char   ADJUSTHOSTBSIDATE [8+1];          /*主机账务日期                                                                    */
		char   ADJUSTHOSTSERIALNO[32+1];         /*主机流水号                                                                      */
		char   ADJUSTRESPCODE    [10+1];         /*调账响应码                                                                      */
		char   ADJUSTRESPMSG     [120+1];        /*调账响应信息                                                                    */
		char   EXTFLD1           [32+1];         /*备用字段1                                                                       */
		char   EXTFLD2           [64+1]         /*备用字段2                                                                       */
}PABYBH_NOTBAL;	

#define SD_DATA  PABYBH_NOTBAL
#define SD_MEMBERS \
		DEFSDMEMBER(T_STRING,   COBANKNO     , 0),\
		DEFSDMEMBER(T_STRING,   CHECKDATE         , 0),\
		DEFSDMEMBER(T_STRING,   COBANKNO          , 0),\
		DEFSDMEMBER(T_STRING,   SVRCODE           , 0),\
		DEFSDMEMBER(T_STRING,   TRANSFERTYPE      , 0),\
		DEFSDMEMBER(T_STRING,   STOCKCODE         , 0),\
		DEFSDMEMBER(T_STRING,   CAPITALACCTNO     , 0),\
		DEFSDMEMBER(T_STRING,   WORKSERIALNO      , 0),\
		DEFSDMEMBER(T_STRING,   BANKSTAT          , 0),\
		DEFSDMEMBER(T_STRING,   BANKACCTNO        , 0),\
		DEFSDMEMBER(T_DOUBLE,   BANKAMT           , 0),\
		DEFSDMEMBER(T_STRING,   BANKTRANSCODE		  , 0),\
		DEFSDMEMBER(T_STRING,   IEPSERIALNO       , 0),\
		DEFSDMEMBER(T_STRING,   IEPSTAT           , 0),\
		DEFSDMEMBER(T_STRING,   IEPACCTNO         , 0),\
		DEFSDMEMBER(T_DOUBLE,   IEPAMT            , 0),\
		DEFSDMEMBER(T_STRING,   IEPTRANSCODE			, 0),\
		DEFSDMEMBER(T_STRING,   HOSTDATE          , 0),\
		DEFSDMEMBER(T_STRING,   HOSTSERIALNO      , 0),\
		DEFSDMEMBER(T_STRING,   HOSTSTAT          , 0),\
		DEFSDMEMBER(T_STRING,   HOSTACCTNO        , 0),\
		DEFSDMEMBER(T_DOUBLE,   HOSTAMT           , 0),\
		DEFSDMEMBER(T_STRING,   HOSTTRANSCODE		  , 0),\
		DEFSDMEMBER(T_STRING,   CHECKSTAT         , 0),\
		DEFSDMEMBER(T_STRING,   ADJUSTSTAT        , 0),\
		DEFSDMEMBER(T_STRING,   ADJUSTTRANSORG    , 0),\
		DEFSDMEMBER(T_STRING,   ADJUSTTRANSOPER   , 0),\
		DEFSDMEMBER(T_STRING,   ADJUSTDATE        , 0),\
		DEFSDMEMBER(T_STRING,   ADJUSTSERIALNO    , 0),\
		DEFSDMEMBER(T_STRING,   ADJUSTHOSTBSIDATE , 0),\
		DEFSDMEMBER(T_STRING,   ADJUSTHOSTSERIALNO, 0),\
		DEFSDMEMBER(T_STRING,   ADJUSTRESPCODE    , 0),\
		DEFSDMEMBER(T_STRING,   ADJUSTRESPMSG     , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD1           , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD2           , 0)

  DECLAREFIELDS(SD_PABYBH_NOTBAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PABYBH_NOTBAL_H__*/
