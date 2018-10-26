#ifndef __FSJK_RFMX_H__
#define __FSJK_RFMX_H__ 

typedef struct TDB_FSJK_RFMX
{
char   FILENAME        [100+1];       /*�ļ�����              */ 
char   SIGNDATE        [8+1];         /*�Ǽ�����              */
char   SIGNTIME        [6+1];         /*�Ǽ�ʱ��              */
char   UNITNO          [20+1];        /*ִ�յ�λ����          */ 
char   PAYNOTENO       [40+1];        /*�ɿ�֪ͨ�����        */
char   ORDERNO         [19+1];        /*������                */
char   RFSTATUS        [2+1];         /*�˷�״̬              */
char   RFFLAG          [2+1];         /*�˷ѱ�־              */
char   RFSERIAL        [20+1];        /*�˷���ˮ��            */
char   RFDATETIME      [14+1];        /*�˷�ʱ��              */
char   RFRESPCODE      [10+1];        /*�˷���Ӧ��            */
char   RFRESPMSG       [100+1];       /*�˷���Ӧ��Ϣ          */
char   PAYERNAME       [100+1];       /*�ɿ���                */
double RFAMTOVER;                     /*���˷��ܽ��          */
double RFAMTOVERARD;                  /*ʵ���˷��ܽ��        */
char   TRANSTIME       [14+1];        /*�ɷ�ʱ��              */
char   RECEIPTTYPENO   [6+1];         /*Ʊ�����ͱ���          */
char   RECEIPTNO       [20+1];        /*Ʊ�ݺ���              */
char   RFREASON        [200+1];       /*�˷�ԭ��              */
char   RFNAME			     [100+1];       /*�˿���                */
char   RFTEL			     [30+1];        /*�˿�����ϵ�绰        */
char   RFCOUNT		     [20+1];        /*�˿��˺�              */
char   COUNTBANK	     [50+1];        /*����������            */
char   PAYCHANNEL      [1+1];         /*�ɷ�����              */
char   REMARK          [500+1]        /*��ע                  */
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
