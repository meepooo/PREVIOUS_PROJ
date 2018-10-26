#ifndef __PABYBH_TRADER_H__
#define __PABYBH_TRADER_H__ 

typedef struct TDB_PABYBH_TRADER
{
		char   STOCKCODE     [8+1];           /*券商代码 */
		char   STOCKNAME     [120+1];         /*券商名称 */
		char   EXTFLD1       [32+1];          /*备用字段1*/
		char   EXTFLD2       [64+1];          /*备用字段2*/
		char   EXTFLD3       [64+1];          /*备用字段3*/
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
