#ifndef __FSJK_DZDJ_H__
#define __FSJK_DZDJ_H__ 

typedef struct TDB_FSJK_DZDJ
{
char   CHKDATE      [8+1];         /*对账日期                  */ 
char   CHKSERIAL    [20+1];        /*对账流水号                */
int 	 CHKSUM       ;        			 /*对账次数                  */
char   RESPCODE     [10+1];        /*响应码                    */
char   RESPMSG      [50+1];        /*响应信息                  */
char   PAYCHKSTATUS [2+1];         /*支付平台对账状态          */
int 	 PAYTRANSNUM  ;        			 /*支付平台交易记录数        */
int    PAYREFOUNDNUM;              /*支付平台退款记录数        */
char   PFCHKSTATUS  [2+1];         /*财厅对账状态              */
int    PFSUM        ;              /*财厅总记录数              */
int    PFSUCCSUM    ;              /*财厅成功记录数            */
int    PFERRSUM     ;              /*财厅失败记录数            */
int    PFTBCSUM     ;              /*财厅待确认记录数          */
int    YHDZLASTSUM  ;              /*财厅对账文件最后序号      */
int    DZJGLASTSUM  ;              /*财厅对账结果最后序号      */
int    SXDZJGLASTSUM;              /*市县对账结果最后序号      */
int    TFJGLASTSUM  ;              /*财厅退费结果最后序号      */
char   HOSTDVDSTATUS[2+1];         /*核心分成状态              */
int    HOSTDVDSUM   ;              /*核心分成文件总笔数        */
char   REMARK1      [150+1];       /*备注1                     */
char   REMARK2      [150+1];       /*备注2                     */
char   REMARK3      [150+1]        /*备注3                     */
}FSJK_DZDJ;	

#define SD_DATA  FSJK_DZDJ
#define SD_MEMBERS \
		DEFSDMEMBER(T_STRING,   CHKDATE      , 0),\ 
		DEFSDMEMBER(T_STRING,   CHKSERIAL    , 0),\
		DEFSDMEMBER(T_LONG,     CHKSUM       , 0),\
		DEFSDMEMBER(T_STRING,   RESPCODE     , 0),\
		DEFSDMEMBER(T_STRING,   RESPMSG      , 0),\
		DEFSDMEMBER(T_STRING,   PAYCHKSTATUS , 0),\
		DEFSDMEMBER(T_LONG,     PAYTRANSNUM  , 0),\
		DEFSDMEMBER(T_LONG,     PAYREFOUNDNUM, 0),\
		DEFSDMEMBER(T_STRING,   PFCHKSTATUS  , 0),\
		DEFSDMEMBER(T_LONG,     PFSUM        , 0),\
		DEFSDMEMBER(T_LONG,     PFSUCCSUM    , 0),\
		DEFSDMEMBER(T_LONG,     PFERRSUM     , 0),\
		DEFSDMEMBER(T_LONG,     PFTBCSUM     , 0),\
		DEFSDMEMBER(T_LONG,     YHDZLASTSUM  , 0),\
		DEFSDMEMBER(T_LONG,     DZJGLASTSUM  , 0),\
		DEFSDMEMBER(T_LONG,     SXDZJGLASTSUM, 0),\
		DEFSDMEMBER(T_LONG,     TFJGLASTSUM  , 0),\
		DEFSDMEMBER(T_STRING,   HOSTDVDSTATUS, 0),\
		DEFSDMEMBER(T_LONG,     HOSTDVDSUM   , 0),\
		DEFSDMEMBER(T_STRING,   REMARK1      , 0),\
		DEFSDMEMBER(T_STRING,   REMARK2      , 0),\
		DEFSDMEMBER(T_STRING,   REMARK3      , 0)

  DECLAREFIELDS(SD_FSJK_DZDJ)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __FSJK_DZDJ_H__*/
