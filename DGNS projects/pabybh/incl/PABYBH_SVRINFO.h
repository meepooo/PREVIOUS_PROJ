#ifndef __PABYBH_SVRINFO_H__
#define __PABYBH_SVRINFO_H__ 

typedef struct TDB_PABYBH_SVRINFO
{
    char COBANKNO[12+1];                 /*  合作行号  */
    char SVRCODE[6+1];                 /*  服务代码  */
    char SVRNAME[100+1];                 /*  服务名称  */
    char WORKTIME[32+1];              /*  业务开展时间段  */
    char SVRSTATUS[32+1];                   /*  服务状态  */
    char EXTFLD1[128+1];                  /*  备用字段1  */
    char EXTFLD2[128+1];                  /*  备用字段2  */
    char EXTFLD3[128+1];                  /*  备用字段3 */
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
