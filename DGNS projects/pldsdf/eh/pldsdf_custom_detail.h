/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:agent_plkhqymx.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:agent_plkhqymx(批量客户签约明细表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __PLDSDF_CUSTOM_DETAIL_EH__
#define __PLDSDF_CUSTOM_DETAIL_EH__
typedef struct TDB_PLDSDF_CUSTOM_DETAIL
{
	char   pch[32+1];     
    int    wjxh;        
    char   wjmc[150+1];   
    char   hth[20+1];     
    char   tyxybh[30+1];  
    char   xybh[20+1];    
    char   xydm[12+1];    
    char   khh[32+1];    
    char   yhzh[32+1];    
    char   yhzhmc[150+1]; 
    char   zjhm[40+1];    
    char   xyjlzt[1+1];   
    char   lxdh[15+1];    
    char   lxdz[150+1];   
    char   bz[80+1];      
    char   bz1[80+1];     
    char   bz2[80+1];     
    char   qysxrq[8+1];   
    char   qydqrq[8+1];   
    char   qyrq[8+1];     
    char   jyrq[8+1];     
    char   qygy[16+1];    
    char   jygy[16+1];    
    char   qyjg[16+1];    
    char   fhxxm[7+1];    
    char   cwzwms[512+1]; 
    char   djzt[1+1]; 
    char   extfld1[80+1]; 
    char   extfld2[80+1]; 
    char   extfld3[80+1]; 
    char   extfld4[80+1]; 
    char   extfld5[80+1]; 
    char   extfld6[160+1];
}SDB_PLDSDF_CUSTOM_DETAIL;

#define SD_DATA  SDB_PLDSDF_CUSTOM_DETAIL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,pch,0),\
	DEFSDMEMBER(T_LONG,wjxh,0),\
	DEFSDMEMBER(T_STRING,wjmc,0),\
	DEFSDMEMBER(T_STRING,hth,0),\
	DEFSDMEMBER(T_STRING,tyxybh,0),\
	DEFSDMEMBER(T_STRING,xybh,0),\
	DEFSDMEMBER(T_STRING,xydm,0),\
	DEFSDMEMBER(T_STRING,khh,0),\
	DEFSDMEMBER(T_STRING,yhzh,0),\
	DEFSDMEMBER(T_STRING,yhzhmc,0),\
	DEFSDMEMBER(T_STRING,zjhm,0),\
	DEFSDMEMBER(T_STRING,xyjlzt,0),\
	DEFSDMEMBER(T_STRING,lxdh,0),\
	DEFSDMEMBER(T_STRING,lxdz,0),\
	DEFSDMEMBER(T_STRING,bz,0),\
	DEFSDMEMBER(T_STRING,bz1,0),\
	DEFSDMEMBER(T_STRING,bz2,0),\
	DEFSDMEMBER(T_STRING,qysxrq,0),\
	DEFSDMEMBER(T_STRING,qydqrq,0),\
	DEFSDMEMBER(T_STRING,qyrq,0),\
	DEFSDMEMBER(T_STRING,jyrq,0),\
	DEFSDMEMBER(T_STRING,qygy,0),\
	DEFSDMEMBER(T_STRING,jygy,0),\
	DEFSDMEMBER(T_STRING,qyjg,0),\
	DEFSDMEMBER(T_STRING,fhxxm,0),\
	DEFSDMEMBER(T_STRING,cwzwms,0),\
	DEFSDMEMBER(T_STRING,djzt,0),\
	DEFSDMEMBER(T_STRING,extfld1,0),\
	DEFSDMEMBER(T_STRING,extfld2,0),\
	DEFSDMEMBER(T_STRING,extfld3,0),\
	DEFSDMEMBER(T_STRING,extfld4,0),\
	DEFSDMEMBER(T_STRING,extfld5,0),\
	DEFSDMEMBER(T_STRING,extfld6,0)

	DECLAREFIELDS(SD_PLDSDF_CUSTOM_DETAIL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __PLDSDF_CUSTOM_DETAIL_EH__*/

