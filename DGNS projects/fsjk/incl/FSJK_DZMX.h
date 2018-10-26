#ifndef __FSJK_DZMX_H__
#define __FSJK_DZMX_H__ 

typedef struct TDB_FSJK_DZMX
{
char   UNITNO          [20+1];        /*ִ�յ�λ����             */ 
char   PAYNOTENO       [40+1];        /*�ɿ�֪ͨ�����           */
char   ORDERNO         [19+1];        /*������                   */
char   PAYSERIAL       [30+1];        /*֧��ƽ̨��ˮ��           */
char   SIGNDATE        [8+1];         /*�Ǽ�����                 */
char   SIGNTIME        [6+1];         /*�Ǽ�ʱ��                 */
char   PAYERNAME       [100+1];       /*�ɿ���                   */
double PNAMOUNT        ;        			/*�շѽ��                */
double PNOVERDUEAMT    ;              /*���ɽ�                   */
double AMOUNT          ;              /*�����ܽ��               */
char   PFTRANSDATETIME [14+1];        /*��������ʱ��             */
char   PAYDATETIME     [14+1];        /*֧��ƽ̨����ʱ��         */
char   RECEIPTTYPENO   [6+1];         /*Ʊ�����ͱ���             */
char   RECEIPTNO       [20+1];        /*Ʊ�ݺ���                 */
char   PAYCHANNEL      [1+1];         /*�ɷ�����                 */
char   DISTRICTNO      [10+1];        /*��������                 */
char   ITEMNUMBER      [1+1];         /*�շ���Ŀ����             */
char   PAYSTATUS       [2+1];         /*֧��ƽ̨���˽��         */
char   PAYCLEARDATE    [8+1];         /*֧��ƽ̨��������         */
char   TRANSSTATUS     [2+1];         /*����״̬                 */
char   PFCHKSTATUS     [2+1];         /*�������˽��             */
char   PFCHKERRCODE    [3+1];         /*��������ԭ�����         */ 
char   PFCHKERRMSG     [500+1];       /*��������ԭ��˵��         */
char   MFCHKSTATUS     [2+1];         /*���ض��˽��             */
char   MFCHKERRDATE    [8+1];         /*���ض�����������         */
char   MFCHKERRMSG     [500+1];       /*���ض�����������˵��     */
char   HOSTDVDSTATUS   [2+1];         /*���ķֳ�״̬             */
char   NUMCHKCD        [5+1];         /*����У����               */
char   TOTCHKCD        [5+1];         /*ȫ��У����               */
char   AMOUNTTYPE      [2+1];         /*����                     */
char   ORDERDATE       [14+1];        /*��������                 */
char   BUSCODE         [20+1];        /*ҵ�����                 */
char   QUANTITY        [1+1];         /*�Ӷ�������               */
char   COMM_PARA       [150+1];       /*ͨ�ò���                 */
char   APPNAME         [20+1];        /*Ӧ������                 */
char   APPVERSION      [15+1];        /*Ӧ�ð汾                 */
char   REDIRECTURL     [128+1];       /*��ת��ַ                 */
char   NOTIFYURL       [128+1];       /*֪ͨ��ַ                 */
char   REMARK1         [150+1];       /*��ע1                    */
char   REMARK2         [150+1];       /*��ע2                    */
char   REMARK3         [150+1]        /*��ע3                    */
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
