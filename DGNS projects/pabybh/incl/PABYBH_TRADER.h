#ifndef __PABYBH_TRADER_H__
#define __PABYBH_TRADER_H__ 

typedef struct TDB_PABYBH_TRADER
{
		char   STOCKCODE     [8+1];           /*ȯ�̴��� */
		char   STOCKNAME     [120+1];         /*ȯ������ */
		char   EXTFLD1       [32+1];          /*�����ֶ�1*/
		char   EXTFLD2       [64+1];          /*�����ֶ�2*/
		char   EXTFLD3       [64+1];          /*�����ֶ�3*/
}PABYBH_TRADER;	

#define SD_DATA  PABYBH_TRADER
#define SD_MEMBERS \
		DEFSDMEMBER(T_STRING,   STOCKCODE     , 0),\
		DEFSDMEMBER(T_STRING,   STOCKNAME     , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD1       , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD2       , 0),\
		DEFSDMEMBER(T_STRING,   EXTFLD3       , 0)

  DECLAREFIELDS(SD_PABYBH_TRADER)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PABYBH_TRADER_H__*/
