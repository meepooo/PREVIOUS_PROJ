#ifndef __FSJK_FCMX_H__
#define __FSJK_FCMX_H__ 

typedef struct TDB_FSJK_FCMX
{
char   SIGNDATE       [8+1];         /*�Ǽ�����                 */ 
char   SIGNTIME       [6+1];         /*�Ǽ�ʱ��                 */
char   TRANSDATE      [8+1];         /*��������                 */
char   UNITNO         [20+1];        /*ִ�յ�λ����             */ 
char   PAYNOTENO      [40+1];        /*�ɿ�֪ͨ�����           */
char   ORDERNO        [19+1];        /*������                   */
char   ITEMNO         [10+1];        /*�շ���Ŀ����             */
int    ITEMID;                       /*�շ���Ŀ���             */
char   ITEMNAME       [100+1];       /*�շ���Ŀ����             */
char   ITEMUNIT       [10+1];        /*������λ                 */
double ITEMPRICE;        			 			 /*����                     */
double ITEMQUANTITY;                 /*����                     */
double ITEMAMOUNT;                   /*Ӧ�ս��С��             */
double ITEMOVERDUEAMT;               /*���ɽ�                   */
char   REMARK1        [150+1];       /*��ע1                    */
char   REMARK2        [150+1];       /*��ע2                    */
char   REMARK3        [150+1]        /*��ע3                    */
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
