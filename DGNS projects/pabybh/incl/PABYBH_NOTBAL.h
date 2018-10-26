#ifndef __PABYBH_NOTBAL_H__
#define __PABYBH_NOTBAL_H__ 

typedef struct TDB_PABYBH_NOTBAL
{
		char   CHECKDATE         [8+1];          /*��������                                                                        */
		char   COBANKNO          [12+1];         /*�����к�                                                                        */
		char   SVRCODE           [4+1];          /*�������                                                                        */
		char   TRANSFERTYPE      [1+1];          /*�ʽ�����'0--������ת֤1--֤ת�������'                                        */
		char   STOCKCODE         [8+1];          /*ȯ�̴���                                                                        */
		char   CAPITALACCTNO     [30+1];         /*֤ȯ�ʽ�̨�˺�                                                                  */
		char   WORKSERIALNO      [30+1];         /*��������ˮ��                                                                    */
		char   BANKSTAT          [1+1];          /*������״̬                                                                      */
		char   BANKACCTNO        [32+1];         /*ƽ̨�����˺�                                                                    */
		double BANKAMT           ;               /*ƽ̨���׽��                                                                    */
		char   BANKTRANSCODE		 [8+1];          /*ƽ̨���״���                                                                    */
		char   IEPSERIALNO       [30+1];         /*��Eͨ��ˮ��                                                                     */
		char   IEPSTAT           [1+1];          /*��Eͨ״̬                                                                       */
		char   IEPACCTNO         [32+1];         /*��Eͨ�����˺�                                                                   */
		double IEPAMT                ;           /*��Eͨ���׽��                                                                   */
		char   IEPTRANSCODE		   [8+1];          /*��Eͨ���״���                                                                   */
		char   HOSTDATE          [8+1];          /*��������                                                                        */
		char   HOSTSERIALNO      [30+1];         /*������ˮ��                                                                      */
		char   HOSTSTAT          [1+1];          /*����״̬                                                                        */
		char   HOSTACCTNO        [32+1];         /*���������˺�                                                                    */
		double HOSTAMT           ;               /*�������׽��                                                                    */
		char   HOSTTRANSCODE		 [8+1];          /*�������״���                                                                    */
		char   CHECKSTAT         [1+1];          /*���˽����־,0-δ����1-�Ѷ�ƽ2-ƽ����3-���Ķ�  4-�˺Ų��� 5-���� 6-״̬���� */
		char   ADJUSTSTAT        [1+1];          /*����״̬ 0-�ɹ� 1-ʧ�� 7-��ʱ 9-��ʼ                                            */
		char   ADJUSTTRANSORG    [10+1];         /*���˽��׻���                                                                    */
		char   ADJUSTTRANSOPER   [10+1];         /*���˽��׹�Ա                                                                    */
		char   ADJUSTDATE        [8+1];          /*��������                                                                        */
		char   ADJUSTSERIALNO    [32+1];         /*����ҵ����ˮ��                                                                  */
		char   ADJUSTHOSTBSIDATE [8+1];          /*������������                                                                    */
		char   ADJUSTHOSTSERIALNO[32+1];         /*������ˮ��                                                                      */
		char   ADJUSTRESPCODE    [10+1];         /*������Ӧ��                                                                      */
		char   ADJUSTRESPMSG     [120+1];        /*������Ӧ��Ϣ                                                                    */
		char   EXTFLD1           [32+1];         /*�����ֶ�1                                                                       */
		char   EXTFLD2           [64+1]         /*�����ֶ�2                                                                       */
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
