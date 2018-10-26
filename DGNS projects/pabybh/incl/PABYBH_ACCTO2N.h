#ifndef __PABYBH_ACCTO2N_H__
#define __PABYBH_ACCTO2N_H__ 

typedef struct TDB_PABYBH_ACCTO2N
{
    char COBANKNO[12+1];  /*�����к�  */
		char OLDACCT [32+1];  /*���˺�    */
		char OLDORG  [10+1];  /*�ϻ���    */
		char NEWACCT [32+1];  /*���˺�    */
		char NEWORG  [10+1];  /*�»���    */
		char EXTFLD1 [32+1];  /*�����ֶ�1 */
		char EXTFLD2 [64+1];  /*�����ֶ�2 */
		char EXTFLD3 [64+1]   /*�����ֶ�3 */

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
