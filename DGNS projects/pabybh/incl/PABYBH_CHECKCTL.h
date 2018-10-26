#ifndef __PABYBH_CHECKCTL_H__
#define __PABYBH_CHECKCTL_H__ 

typedef struct TDB_PABYBH_CHECKCTL
{
		char   CHECKDATE          [8+1];          /*-对账日期                                                                                                                                    */
		char   COBANKNO           [12+1];         /*-合作行号                                                                                                                                    */
		char   SVRCODE            [6+1];          /*-服务码 业务类型                                                                                                                             */
		char   MSGTYPE            [1+1];         /*-对账类型0资金类1账户类（正常）2账户类（解约&销户）                                                                                          */
		int    TOTALCOUNT         ;                /*-总笔数                                                                                                                                      */
		double TOTALAMT           ;               /*-总金额                                                                                                                                      */
		int    INTOTCNT           ;               /*-转入总笔数                                                                                                                                  */
		double INTOTAMT           ;               /*-转入总金额                                                                                                                                  */
		int    OUTTOTCNT          ;               /*-转出总笔数                                                                                                                                  */
		double OUTTOTAMT          ;               /*-转出总金额                                                                                                                                  */
		int    BACKTOTALCOUNT     ;               /*-冲正总笔数                                                                                                                                  */
		double BACKTOTALAMT       ;               /*-冲正总金额                                                                                                                                  */
		int    LOCALTOTALCOUNT    ;               /*-平台总笔数                                                                                                                                  */
		double LOCALTOTALAMT      ;               /*-平台总金额                                                                                                                                  */
		int    LOCALBACKTOTALCOUNT;               /*-平台冲正总笔数                                                                                                                              */
		double LOCALBACKTOTALAMT  ;               /*-平台冲正总金额                                                                                                                              */
		int    HOSTTOTALCOUNT     ;               /*-主机总笔数                                                                                                                                  */
		double HOSTTOTALAMT       ;               /*-主机总金额                                                                                                                                  */
		int    HOSTBACKTOTALCOUNT ;               /*-主机冲正总笔数                                                                                                                              */
		double HOSTBACKTOTALAMT   ;               /*-主机冲正总金额                                                                                                                              */
		double NETAMT             ;               /*-轧差金额                                                                                                                                    */
		char   NETTYPE            [1+1];          /*-轧差方向  '0收入 1支出'                                                                                                                     */
		char   IEPCHKFILE         [100+1];        /*-平安对账文件名                                                                                                                              */
		char   HOSTCHKFILE        [100+1];        /*-主机对账文件名                                                                                                                              */
		char   EXECSTEP           [2+1];          /*-执行步点'0-获取平安对账信息 1-平安对账文件入库 2-平安明细对账完成 3-请求提交主机 4-获取主机对账文件,主机生成对账文件入库 5-主机明细对账完成'*/
		char   EXECSTAT           [1+1];          /*-执行状态'1-成功 2-失败9-处理中'                                                                                                             */
		char   CHKDETAILRESULT    [1+1];          /*-明细对账结果'0 未对账 1 对账平 2对账不平 3对账出错 9 对账中'                                                                                */
		char   CHKPABTOTALRESULT  [1+1];          /*-中心对总账结果'0 未对账 1 对账平 2对账不平 3对账出错 9 对账中'                                                                              */
		char   CHKHOSTTOTALRESULT [1+1];          /*-核心对总账结果'0 未对账 1 对账平 2对账不平 3对账出错 9 对账中'                                                                              */
		char   SETTLEDATE         [8+1];          /*-清算日期                                                                                                                                    */
		char   SETTLESERNO        [40+1];         /*-清算流水号                                                                                                                                  */
		char   TRANSDATE          [8+1];          /*-交易日期                                                                                                                                    */
		char   TRANSSERIALNO      [40+1];         /*-交易流水号                                                                                                                                  */
		char   HOSTDATE           [40+1];         /*-清算核心日期                                                                                                                                */
		char   HOSTSERIALNO       [40+1];         /*-清算核心流水号                                                                                                                              */
		char   TRANSORG           [10+1];         /*-交易机构                                                                                                                                    */
		char   TRANSOPER          [10+1];         /*-交易柜员                                                                                                                                    */
		char   RESPCODE           [10+1];         /*-响应码                                                                                                                                      */
		char   RESPMSG            [120+1];        /*-响应信息                                                                                                                                    */
		char   STAT               [1+1];          /*-交易状态 0成功 1失败 6状态未知 7被冲正 8被撤销 9初始                                                                                        */
		char   EXTFLD1            [32+1];         /*-备用字段1                                                                                                                                   */
		char   EXTFLD2            [64+1];         /*-备用字段2                                                                                                                                   */
		char   EXTFLD3            [128+1]         /*-备用字段3                                                                                                                                   */

}PABYBH_CHECKCTL;	

#define SD_DATA  PABYBH_CHECKCTL
#define SD_MEMBERS \
		DEFSDMEMBER(T_STRING,   CHECKDATE          , 0),\
		DEFSDMEMBER(T_STRING,   COBANKNO           , 0),\
		DEFSDMEMBER(T_STRING,   SVRCODE            , 0),\
		DEFSDMEMBER(T_STRING,   MSGTYPE            , 0),\
		DEFSDMEMBER(T_LONG,     TOTALCOUNT         , 0),\
		DEFSDMEMBER(T_DOUBLE,   TOTALAMT           , 0),\
		DEFSDMEMBER(T_LONG,     INTOTCNT           , 0),\
		DEFSDMEMBER(T_DOUBLE,   INTOTAMT           , 0),\
		DEFSDMEMBER(T_LONG,     OUTTOTCNT          , 0),\
		DEFSDMEMBER(T_DOUBLE,   OUTTOTAMT          , 0),\
		DEFSDMEMBER(T_LONG,     BACKTOTALCOUNT     , 0),\
		DEFSDMEMBER(T_DOUBLE,   BACKTOTALAMT       , 0),\
		DEFSDMEMBER(T_LONG,     LOCALTOTALCOUNT    , 0),\
		DEFSDMEMBER(T_DOUBLE,   LOCALTOTALAMT      , 0),\
		DEFSDMEMBER(T_LONG,     LOCALBACKTOTALCOUNT, 0),\
		DEFSDMEMBER(T_DOUBLE,   LOCALBACKTOTALAMT  , 0),\
		DEFSDMEMBER(T_LONG,     HOSTTOTALCOUNT     , 0),\
		DEFSDMEMBER(T_DOUBLE,   HOSTTOTALAMT       , 0),\
		DEFSDMEMBER(T_LONG,     HOSTBACKTOTALCOUNT , 0),\
		DEFSDMEMBER(T_DOUBLE,   HOSTBACKTOTALAMT   , 0),\
		DEFSDMEMBER(T_DOUBLE,   NETAMT             , 0),\
		DEFSDMEMBER(T_STRING,   NETTYPE            , 0),\
		DEFSDMEMBER(T_STRING,   IEPCHKFILE         , 0),\
		DEFSDMEMBER(T_STRING,   HOSTCHKFILE        , 0),\
		DEFSDMEMBER(T_STRING,   EXECSTEP           , 0),\
		DEFSDMEMBER(T_STRING,   EXECSTAT           , 0),\
		DEFSDMEMBER(T_STRING,   CHKDETAILRESULT    , 0),\
		DEFSDMEMBER(T_STRING,   CHKPABTOTALRESULT  , 0),\
		DEFSDMEMBER(T_STRING,   CHKHOSTTOTALRESULT , 0),\
		DEFSDMEMBER(T_STRING,   SETTLEDATE         , 0),\
		DEFSDMEMBER(T_STRING,   SETTLESERNO        , 0),\
		DEFSDMEMBER(T_STRING,   TRANSDATE          , 0),\
		DEFSDMEMBER(T_STRING,   TRANSSERIALNO      , 0),\
		DEFSDMEMBER(T_STRING,   HOSTDATE           , 0),\
		DEFSDMEMBER(T_STRING,   HOSTSERIALNO       , 0),\
		DEFSDMEMBER(T_STRING,   TRANSORG           , 0),\
		DEFSDMEMBER(T_STRING,   TRANSOPER          , 0),\
		DEFSDMEMBER(T_STRING,   RESPCODE           , 0),\
		DEFSDMEMBER(T_STRING,   RESPMSG            , 0),\
		DEFSDMEMBER(T_STRING,   STAT               , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD1            , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD2            , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD3            , 0)
 

  DECLAREFIELDS(SD_PABYBH_CHECKCTL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PABYBH_CHECKCTL_H__*/
