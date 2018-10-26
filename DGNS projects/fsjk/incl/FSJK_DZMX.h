#ifndef __FSJK_DZMX_H__
#define __FSJK_DZMX_H__ 

typedef struct TDB_FSJK_DZMX
{
char   UNITNO          [20+1];        /*执收单位编码             */ 
char   PAYNOTENO       [40+1];        /*缴款通知书号码           */
char   ORDERNO         [19+1];        /*订单号                   */
char   PAYSERIAL       [30+1];        /*支付平台流水号           */
char   SIGNDATE        [8+1];         /*登记日期                 */
char   SIGNTIME        [6+1];         /*登记时间                 */
char   PAYERNAME       [100+1];       /*缴款人                   */
double PNAMOUNT        ;        			/*收费金额                */
double PNOVERDUEAMT    ;              /*滞纳金                   */
double AMOUNT          ;              /*订单总金额               */
char   PFTRANSDATETIME [14+1];        /*财厅交易时间             */
char   PAYDATETIME     [14+1];        /*支付平台交易时间         */
char   RECEIPTTYPENO   [6+1];         /*票据类型编码             */
char   RECEIPTNO       [20+1];        /*票据号码                 */
char   PAYCHANNEL      [1+1];         /*缴费渠道                 */
char   DISTRICTNO      [10+1];        /*区划代码                 */
char   ITEMNUMBER      [1+1];         /*收费项目数量             */
char   PAYSTATUS       [2+1];         /*支付平台对账结果         */
char   PAYCLEARDATE    [8+1];         /*支付平台清算日期         */
char   TRANSSTATUS     [2+1];         /*交易状态                 */
char   PFCHKSTATUS     [2+1];         /*财厅对账结果             */
char   PFCHKERRCODE    [3+1];         /*财厅对账原因代码         */ 
char   PFCHKERRMSG     [500+1];       /*财厅对账原因说明         */
char   MFCHKSTATUS     [2+1];         /*市县对账结果             */
char   MFCHKERRDATE    [8+1];         /*市县对账问题账务         */
char   MFCHKERRMSG     [500+1];       /*市县对账问题账务说明     */
char   HOSTDVDSTATUS   [2+1];         /*核心分成状态             */
char   NUMCHKCD        [5+1];         /*号码校验码               */
char   TOTCHKCD        [5+1];         /*全书校验码               */
char   AMOUNTTYPE      [2+1];         /*币种                     */
char   ORDERDATE       [14+1];        /*订单日期                 */
char   BUSCODE         [20+1];        /*业务代码                 */
char   QUANTITY        [1+1];         /*子订单数量               */
char   COMM_PARA       [150+1];       /*通用参数                 */
char   APPNAME         [20+1];        /*应用名称                 */
char   APPVERSION      [15+1];        /*应用版本                 */
char   REDIRECTURL     [128+1];       /*跳转地址                 */
char   NOTIFYURL       [128+1];       /*通知地址                 */
char   REMARK1         [150+1];       /*备注1                    */
char   REMARK2         [150+1];       /*备注2                    */
char   REMARK3         [150+1]        /*备注3                    */
}FSJK_DZMX;	

#define SD_DATA  FSJK_DZMX
#define SD_MEMBERS \
		DEFSDMEMBER(T_STRING,   UNITNO            , 0),\ 
		DEFSDMEMBER(T_STRING,   PAYNOTENO         , 0),\
		DEFSDMEMBER(T_STRING,   ORDERNO           , 0),\
		DEFSDMEMBER(T_STRING,   PAYSERIAL         , 0),\
		DEFSDMEMBER(T_STRING,   SIGNDATE          , 0),\
		DEFSDMEMBER(T_STRING,   SIGNTIME          , 0),\
		DEFSDMEMBER(T_STRING,   PAYERNAME         , 0),\
		DEFSDMEMBER(T_DOUBLE,   PNAMOUNT          , 0),\
		DEFSDMEMBER(T_DOUBLE,   PNOVERDUEAMT      , 0),\
		DEFSDMEMBER(T_DOUBLE,   AMOUNT            , 0),\
		DEFSDMEMBER(T_STRING,   PFTRANSDATETIME   , 0),\
		DEFSDMEMBER(T_STRING,   PAYDATETIME       , 0),\
		DEFSDMEMBER(T_STRING,   RECEIPTTYPENO     , 0),\
		DEFSDMEMBER(T_STRING,   RECEIPTNO         , 0),\
		DEFSDMEMBER(T_STRING,   PAYCHANNEL        , 0),\
		DEFSDMEMBER(T_STRING,   DISTRICTNO        , 0),\
		DEFSDMEMBER(T_STRING,   ITEMNUMBER        , 0),\
		DEFSDMEMBER(T_STRING,   PAYSTATUS         , 0),\
		DEFSDMEMBER(T_STRING,   PAYCLEARDATE      , 0),\
		DEFSDMEMBER(T_STRING,   TRANSSTATUS       , 0),\
		DEFSDMEMBER(T_STRING,   PFCHKSTATUS       , 0),\ 
		DEFSDMEMBER(T_STRING,   PFCHKERRCODE      , 0),\
		DEFSDMEMBER(T_STRING,   PFCHKERRMSG       , 0),\
		DEFSDMEMBER(T_STRING,   MFCHKSTATUS       , 0),\
		DEFSDMEMBER(T_STRING,   MFCHKERRDATE      , 0),\
		DEFSDMEMBER(T_STRING,   MFCHKERRMSG       , 0),\
		DEFSDMEMBER(T_STRING,   HOSTDVDSTATUS     , 0),\
		DEFSDMEMBER(T_STRING,   NUMCHKCD          , 0),\
		DEFSDMEMBER(T_STRING,   TOTCHKCD          , 0),\
		DEFSDMEMBER(T_STRING,   AMOUNTTYPE        , 0),\
		DEFSDMEMBER(T_STRING,   ORDERDATE         , 0),\
		DEFSDMEMBER(T_STRING,   BUSCODE           , 0),\
		DEFSDMEMBER(T_STRING,   QUANTITY          , 0),\
		DEFSDMEMBER(T_STRING,   COMM_PARA         , 0),\
		DEFSDMEMBER(T_STRING,   APPNAME           , 0),\
		DEFSDMEMBER(T_STRING,   APPVERSION        , 0),\
		DEFSDMEMBER(T_STRING,   REDIRECTURL       , 0),\
		DEFSDMEMBER(T_STRING,   NOTIFYURL         , 0),\
		DEFSDMEMBER(T_STRING,   REMARK1           , 0),\
		DEFSDMEMBER(T_STRING,   REMARK2           , 0),\
		DEFSDMEMBER(T_STRING,   REMARK3           , 0)
 

  DECLAREFIELDS(SD_FSJK_DZMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __FSJK_DZMX_H__*/
