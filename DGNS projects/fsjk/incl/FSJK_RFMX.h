#ifndef __FSJK_RFMX_H__
#define __FSJK_RFMX_H__ 

typedef struct TDB_FSJK_RFMX
{
char   FILENAME        [100+1];       /*文件名称              */ 
char   SIGNDATE        [8+1];         /*登记日期              */
char   SIGNTIME        [6+1];         /*登记时间              */
char   UNITNO          [20+1];        /*执收单位编码          */ 
char   PAYNOTENO       [40+1];        /*缴款通知书号码        */
char   ORDERNO         [19+1];        /*订单号                */
char   RFSTATUS        [2+1];         /*退费状态              */
char   RFFLAG          [2+1];         /*退费标志              */
char   RFSERIAL        [20+1];        /*退费流水号            */
char   RFDATETIME      [14+1];        /*退费时间              */
char   RFRESPCODE      [10+1];        /*退费响应码            */
char   RFRESPMSG       [100+1];       /*退费响应信息          */
char   PAYERNAME       [100+1];       /*缴款人                */
double RFAMTOVER;                     /*需退费总金额          */
double RFAMTOVERARD;                  /*实际退费总金额        */
char   TRANSTIME       [14+1];        /*缴费时间              */
char   RECEIPTTYPENO   [6+1];         /*票据类型编码          */
char   RECEIPTNO       [20+1];        /*票据号码              */
char   RFREASON        [200+1];       /*退费原因              */
char   RFNAME			     [100+1];       /*退款人                */
char   RFTEL			     [30+1];        /*退款人联系电话        */
char   RFCOUNT		     [20+1];        /*退款账号              */
char   COUNTBANK	     [50+1];        /*开户行名称            */
char   PAYCHANNEL      [1+1];         /*缴费渠道              */
char   REMARK          [500+1]        /*备注                  */
}FSJK_RFMX;	

#define SD_DATA  FSJK_RFMX
#define SD_MEMBERS \
		DEFSDMEMBER(T_STRING,   FILENAME       , 0),\ 
		DEFSDMEMBER(T_STRING,   SIGNDATE       , 0),\
		DEFSDMEMBER(T_STRING,   SIGNTIME       , 0),\
		DEFSDMEMBER(T_STRING,   UNITNO         , 0),\
		DEFSDMEMBER(T_STRING,   PAYNOTENO      , 0),\
		DEFSDMEMBER(T_STRING,   ORDERNO        , 0),\
		DEFSDMEMBER(T_STRING,   RFSTATUS       , 0),\
		DEFSDMEMBER(T_STRING,   RFFLAG         , 0),\
		DEFSDMEMBER(T_STRING,   RFSERIAL       , 0),\
		DEFSDMEMBER(T_STRING,   RFDATETIME     , 0),\
		DEFSDMEMBER(T_STRING,   RFRESPCODE     , 0),\
		DEFSDMEMBER(T_STRING,   RFRESPMSG      , 0),\
		DEFSDMEMBER(T_STRING,   PAYERNAME      , 0),\
		DEFSDMEMBER(T_DOUBLE,   RFAMTOVER      , 0),\
		DEFSDMEMBER(T_DOUBLE,   RFAMTOVERARD   , 0),\
		DEFSDMEMBER(T_STRING,   TRANSTIME      , 0),\
		DEFSDMEMBER(T_STRING,   RECEIPTTYPENO  , 0),\
		DEFSDMEMBER(T_STRING,   RECEIPTNO      , 0),\
		DEFSDMEMBER(T_STRING,   RFREASON       , 0),\
		DEFSDMEMBER(T_STRING,   RFNAME         , 0),\
		DEFSDMEMBER(T_STRING,   RFTEL          , 0),\
		DEFSDMEMBER(T_STRING,   RFCOUNT        , 0),\
		DEFSDMEMBER(T_STRING,   COUNTBANK      , 0),\
		DEFSDMEMBER(T_STRING,   PAYCHANNEL     , 0),\
		DEFSDMEMBER(T_STRING,   REMARK         , 0)

  DECLAREFIELDS(SD_FSJK_RFMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __FSJK_RFMX_H__*/
