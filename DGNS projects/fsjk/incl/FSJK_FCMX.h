#ifndef __FSJK_FCMX_H__
#define __FSJK_FCMX_H__ 

typedef struct TDB_FSJK_FCMX
{
char   SIGNDATE       [8+1];         /*登记日期                 */ 
char   SIGNTIME       [6+1];         /*登记时间                 */
char   TRANSDATE      [8+1];         /*交易日期                 */
char   UNITNO         [20+1];        /*执收单位编码             */ 
char   PAYNOTENO      [40+1];        /*缴款通知书号码           */
char   ORDERNO        [19+1];        /*订单号                   */
char   ITEMNO         [10+1];        /*收费项目编码             */
int    ITEMID;                       /*收费项目序号             */
char   ITEMNAME       [100+1];       /*收费项目名称             */
char   ITEMUNIT       [10+1];        /*计量单位                 */
double ITEMPRICE;        			 			 /*单价                     */
double ITEMQUANTITY;                 /*数量                     */
double ITEMAMOUNT;                   /*应收金额小计             */
double ITEMOVERDUEAMT;               /*滞纳金                   */
char   REMARK1        [150+1];       /*备注1                    */
char   REMARK2        [150+1];       /*备注2                    */
char   REMARK3        [150+1]        /*备注3                    */
}FSJK_FCMX;	

#define SD_DATA  FSJK_FCMX
#define SD_MEMBERS \
		DEFSDMEMBER(T_STRING,   SIGNDATE      , 0),\ 
		DEFSDMEMBER(T_STRING,   SIGNTIME      , 0),\
		DEFSDMEMBER(T_STRING,   TRANSDATE     , 0),\
		DEFSDMEMBER(T_STRING,   UNITNO        , 0),\ 
		DEFSDMEMBER(T_STRING,   PAYNOTENO     , 0),\
		DEFSDMEMBER(T_STRING,   ORDERNO       , 0),\
		DEFSDMEMBER(T_STRING,   ITEMNO        , 0),\
		DEFSDMEMBER(T_LONG,     ITEMID        , 0),\
		DEFSDMEMBER(T_STRING,   ITEMNAME      , 0),\
		DEFSDMEMBER(T_STRING,   ITEMUNIT      , 0),\
		DEFSDMEMBER(T_DOUBLE,   ITEMPRICE     , 0),\
		DEFSDMEMBER(T_DOUBLE,   ITEMQUANTITY  , 0),\
		DEFSDMEMBER(T_DOUBLE,   ITEMAMOUNT    , 0),\
		DEFSDMEMBER(T_DOUBLE,   ITEMOVERDUEAMT, 0),\
		DEFSDMEMBER(T_STRING,   REMARK1       , 0),\
		DEFSDMEMBER(T_STRING,   REMARK2       , 0),\
		DEFSDMEMBER(T_STRING,   REMARK3       , 0)
 

  DECLAREFIELDS(SD_FSJK_FCMX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __FSJK_FCMX_H__*/
