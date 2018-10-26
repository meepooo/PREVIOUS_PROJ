#ifndef __PABYBH_CHECKCTL_H__
#define __PABYBH_CHECKCTL_H__ 

typedef struct TDB_PABYBH_CHECKCTL
{
		char   CHECKDATE          [8+1];          /*-��������                                                                                                                                    */
		char   COBANKNO           [12+1];         /*-�����к�                                                                                                                                    */
		char   SVRCODE            [6+1];          /*-������ ҵ������                                                                                                                             */
		char   MSGTYPE            [1+1];         /*-��������0�ʽ���1�˻��ࣨ������2�˻��ࣨ��Լ&������                                                                                          */
		int    TOTALCOUNT         ;                /*-�ܱ���                                                                                                                                      */
		double TOTALAMT           ;               /*-�ܽ��                                                                                                                                      */
		int    INTOTCNT           ;               /*-ת���ܱ���                                                                                                                                  */
		double INTOTAMT           ;               /*-ת���ܽ��                                                                                                                                  */
		int    OUTTOTCNT          ;               /*-ת���ܱ���                                                                                                                                  */
		double OUTTOTAMT          ;               /*-ת���ܽ��                                                                                                                                  */
		int    BACKTOTALCOUNT     ;               /*-�����ܱ���                                                                                                                                  */
		double BACKTOTALAMT       ;               /*-�����ܽ��                                                                                                                                  */
		int    LOCALTOTALCOUNT    ;               /*-ƽ̨�ܱ���                                                                                                                                  */
		double LOCALTOTALAMT      ;               /*-ƽ̨�ܽ��                                                                                                                                  */
		int    LOCALBACKTOTALCOUNT;               /*-ƽ̨�����ܱ���                                                                                                                              */
		double LOCALBACKTOTALAMT  ;               /*-ƽ̨�����ܽ��                                                                                                                              */
		int    HOSTTOTALCOUNT     ;               /*-�����ܱ���                                                                                                                                  */
		double HOSTTOTALAMT       ;               /*-�����ܽ��                                                                                                                                  */
		int    HOSTBACKTOTALCOUNT ;               /*-���������ܱ���                                                                                                                              */
		double HOSTBACKTOTALAMT   ;               /*-���������ܽ��                                                                                                                              */
		double NETAMT             ;               /*-������                                                                                                                                    */
		char   NETTYPE            [1+1];          /*-�����  '0���� 1֧��'                                                                                                                     */
		char   IEPCHKFILE         [100+1];        /*-ƽ�������ļ���                                                                                                                              */
		char   HOSTCHKFILE        [100+1];        /*-���������ļ���                                                                                                                              */
		char   EXECSTEP           [2+1];          /*-ִ�в���'0-��ȡƽ��������Ϣ 1-ƽ�������ļ���� 2-ƽ����ϸ������� 3-�����ύ���� 4-��ȡ���������ļ�,�������ɶ����ļ���� 5-������ϸ�������'*/
		char   EXECSTAT           [1+1];          /*-ִ��״̬'1-�ɹ� 2-ʧ��9-������'                                                                                                             */
		char   CHKDETAILRESULT    [1+1];          /*-��ϸ���˽��'0 δ���� 1 ����ƽ 2���˲�ƽ 3���˳��� 9 ������'                                                                                */
		char   CHKPABTOTALRESULT  [1+1];          /*-���Ķ����˽��'0 δ���� 1 ����ƽ 2���˲�ƽ 3���˳��� 9 ������'                                                                              */
		char   CHKHOSTTOTALRESULT [1+1];          /*-���Ķ����˽��'0 δ���� 1 ����ƽ 2���˲�ƽ 3���˳��� 9 ������'                                                                              */
		char   SETTLEDATE         [8+1];          /*-��������                                                                                                                                    */
		char   SETTLESERNO        [40+1];         /*-������ˮ��                                                                                                                                  */
		char   TRANSDATE          [8+1];          /*-��������                                                                                                                                    */
		char   TRANSSERIALNO      [40+1];         /*-������ˮ��                                                                                                                                  */
		char   HOSTDATE           [40+1];         /*-�����������                                                                                                                                */
		char   HOSTSERIALNO       [40+1];         /*-���������ˮ��                                                                                                                              */
		char   TRANSORG           [10+1];         /*-���׻���                                                                                                                                    */
		char   TRANSOPER          [10+1];         /*-���׹�Ա                                                                                                                                    */
		char   RESPCODE           [10+1];         /*-��Ӧ��                                                                                                                                      */
		char   RESPMSG            [120+1];        /*-��Ӧ��Ϣ                                                                                                                                    */
		char   STAT               [1+1];          /*-����״̬ 0�ɹ� 1ʧ�� 6״̬δ֪ 7������ 8������ 9��ʼ                                                                                        */
		char   EXTFLD1            [32+1];         /*-�����ֶ�1                                                                                                                                   */
		char   EXTFLD2            [64+1];         /*-�����ֶ�2                                                                                                                                   */
		char   EXTFLD3            [128+1]         /*-�����ֶ�3                                                                                                                                   */

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
