#ifndef __FSJK_DZDJ_H__
#define __FSJK_DZDJ_H__ 

typedef struct TDB_FSJK_DZDJ
{
char   CHKDATE      [8+1];         /*��������                  */ 
char   CHKSERIAL    [20+1];        /*������ˮ��                */
int 	 CHKSUM       ;        			 /*���˴���                  */
char   RESPCODE     [10+1];        /*��Ӧ��                    */
char   RESPMSG      [50+1];        /*��Ӧ��Ϣ                  */
char   PAYCHKSTATUS [2+1];         /*֧��ƽ̨����״̬          */
int 	 PAYTRANSNUM  ;        			 /*֧��ƽ̨���׼�¼��        */
int    PAYREFOUNDNUM;              /*֧��ƽ̨�˿��¼��        */
char   PFCHKSTATUS  [2+1];         /*��������״̬              */
int    PFSUM        ;              /*�����ܼ�¼��              */
int    PFSUCCSUM    ;              /*�����ɹ���¼��            */
int    PFERRSUM     ;              /*����ʧ�ܼ�¼��            */
int    PFTBCSUM     ;              /*������ȷ�ϼ�¼��          */
int    YHDZLASTSUM  ;              /*���������ļ�������      */
int    DZJGLASTSUM  ;              /*�������˽��������      */
int    SXDZJGLASTSUM;              /*���ض��˽��������      */
int    TFJGLASTSUM  ;              /*�����˷ѽ��������      */
char   HOSTDVDSTATUS[2+1];         /*���ķֳ�״̬              */
int    HOSTDVDSUM   ;              /*���ķֳ��ļ��ܱ���        */
char   REMARK1      [150+1];       /*��ע1                     */
char   REMARK2      [150+1];       /*��ע2                     */
char   REMARK3      [150+1]        /*��ע3                     */
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
