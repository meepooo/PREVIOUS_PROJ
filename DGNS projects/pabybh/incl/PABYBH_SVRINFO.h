#ifndef __PABYBH_SVRINFO_H__
#define __PABYBH_SVRINFO_H__ 

typedef struct TDB_PABYBH_SVRINFO
{
    char COBANKNO[12+1];                 /*  �����к�  */
    char SVRCODE[6+1];                 /*  �������  */
    char SVRNAME[100+1];                 /*  ��������  */
    char WORKTIME[32+1];              /*  ҵ��չʱ���  */
    char SVRSTATUS[32+1];                   /*  ����״̬  */
    char EXTFLD1[128+1];                  /*  �����ֶ�1  */
    char EXTFLD2[128+1];                  /*  �����ֶ�2  */
    char EXTFLD3[128+1];                  /*  �����ֶ�3 */
}PABYBH_SVRINFO;	

#define SD_DATA  PABYBH_SVRINFO
#define SD_MEMBERS \
    DEFSDMEMBER(T_STRING,  COBANKNO, 0),\
    DEFSDMEMBER(T_STRING,  SVRCODE, 0),\
    DEFSDMEMBER(T_STRING,  SVRNAME, 0),\
    DEFSDMEMBER(T_STRING,  WORKTIME, 0),\
    DEFSDMEMBER(T_STRING,  SVRSTATUS, 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD1, 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD2, 0),\
    DEFSDMEMBER(T_STRING,  EXTFLD3, 0)

  DECLAREFIELDS(SD_PABYBH_SVRINFO)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PAB_ICC_DLCG_CHKINFO_H__*/
