#ifndef __PABYBH_DEPCHKINFO_H__
#define __PABYBH_DEPCHKINFO_H__ 

typedef struct TDB_PABYBH_DEPCHKINFO
{
char   CHECKDATE    [8+1];         /*��������                    */ 
char   TRANSDATE    [8+1];         /*��������                    */
char   TRANSTIME    [6+1];         /*����ʱ��                    */
char   TRANSFERTYPE [1+1];         /*�ʽ�����'0--��ת֤1--֤ת��'*/
char   ACCTNO       [32+1];        /*�����˺�                    */
char   STOCKCODE    [8+1];         /*ȯ�̴���                    */
char   CAPITALACCTNO[30+1];        /*֤ȯ�ʽ�̨�˺�              */
double AMT                ;        /*���                        */
char   WORKSERIALNO [30+1];        /*��������ˮ��                */
char   IEPSERIALNO  [30+1];        /*��Eͨ��ˮ��                 */
char   COBANKNO     [12+1];        /*�����к�                    */
char   EXTFLD1      [32+1];        /*�����ֶ�1                   */
char   EXTFLD2      [64+1]         /*�����ֶ�2                   */
}PABYBH_DEPCHKINFO;	

#define SD_DATA  PABYBH_DEPCHKINFO
#define SD_MEMBERS \
		DEFSDMEMBER(T_STRING,   CHECKDATE    , 0),\ 
		DEFSDMEMBER(T_STRING,   TRANSDATE    , 0),\
		DEFSDMEMBER(T_STRING,   TRANSTIME    , 0),\
		DEFSDMEMBER(T_STRING,   TRANSFERTYPE , 0),\
		DEFSDMEMBER(T_STRING,   ACCTNO       , 0),\
		DEFSDMEMBER(T_STRING,   STOCKCODE    , 0),\
		DEFSDMEMBER(T_STRING,   CAPITALACCTNO, 0),\
		DEFSDMEMBER(T_DOUBLE,   AMT          , 0),\
		DEFSDMEMBER(T_STRING,   WORKSERIALNO , 0),\
		DEFSDMEMBER(T_STRING,   IEPSERIALNO  , 0),\
		DEFSDMEMBER(T_STRING,   COBANKNO     , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD1      , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD2      , 0)
 

  DECLAREFIELDS(SD_PABYBH_DEPCHKINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PABYBH_DEPCHKINFO_H__*/
