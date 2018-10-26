#ifndef __PABYBH_ACCTO2N_H__
#define __PABYBH_ACCTO2N_H__ 

typedef struct TDB_PABYBH_ACCTO2N
{
    char COBANKNO[12+1];  /*合作行号  */
		char OLDACCT [32+1];  /*老账号    */
		char OLDORG  [10+1];  /*老机构    */
		char NEWACCT [32+1];  /*新账号    */
		char NEWORG  [10+1];  /*新机构    */
		char EXTFLD1 [32+1];  /*备用字段1 */
		char EXTFLD2 [64+1];  /*备用字段2 */
		char EXTFLD3 [64+1]   /*备用字段3 */

}PABYBH_ACCTO2N;	

#define SD_DATA  PABYBH_ACCTO2N
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,  COBANKNO, 0),\
    DEFSDMEMBER(T_STRING,  OLDACCT , 0),\
    DEFSDMEMBER(T_STRING,  OLDORG  , 0),\
    DEFSDMEMBER(T_STRING,  NEWACCT , 0),\
    DEFSDMEMBER(T_STRING,  NEWORG  , 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD1 , 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD2 , 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD3 , 0)

  DECLAREFIELDS(SD_PABYBH_ACCTO2N)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PABYBH_ACCTO2N_H__*/
