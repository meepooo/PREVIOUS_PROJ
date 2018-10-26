/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
文 件 名:DATA_DEC_DATE.c
文件描述:
项 目 组:
程 序 员:[]
创建时间:2015-7-31 18:33:21[Gen]
修    订:
修改时间:
****************************************************************************/
#include <string.h>
#include <math.h>
#include "DCI.h"
#include "gaps_head.h"

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#define PI  3.1415926
#define EARTH_RADIUS 6378.137//地球近似半径
#define	MAXCOUNTCINEMAS	20
typedef struct st_Cinemas
{
	char szCinemaId[20+1];
	char szCinemaName [128+1];
	char szSpCode [10+1];
	char szCityid [6+1];
	char szCountyCode [6+1];
	char szCountyName [40+1];
	char dLongitude[11+1];
	char szLatitude[11+1];
	char szAddress [128+1];
	char	szImgUrl[300+1];
	double dDistance;
} STCIMEMAS;

typedef struct st_Facility
{
	char szCinemaId[50];
	char ICON_ID[50];
	char ICON_NAME[150];
	char ICON_URL[300];
	char SMALL_ICON_URL[300];
} ST_FACILITY;
	
STCIMEMAS stCinemas[MAXCOUNTCINEMAS];

/*
   注：本函数为组件库公共函数,用于在发布状态下显示内部版本信息
       在生产环境下，每次更新均应修改版本号、填入相应信息
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
	     "<soname>DATA_DEC_DATE.so</soname>"
	     "<sosrcname>DATA_DEC_DATE.c</sosrcname>"
	     "<sonote></sonote>"
	     "<version>"
	       "<rec ver=\"1.0.00\" modify=\"2015-7-31 18:33:21\" programer=\"[傅阳伟]\" filesize=\"FILE\">初始发布版</rec>"
	     "</version>"
     "</root>";
  printf("\n================动态组件基本信息================\n");
  printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
  printf("%s-%s\n",__PROJECTSNAME,__VERSION);
  if (strlen(sversion) >= isize)
  {
  	printf(" -->取详细信息失败...\n");
  	return -2;
  }
 	strcpy(sinfo,sversion);
 	printf(" -->请查看详细信息...\n");
  return 0;
}

 
// 求弧度
double radian(double d)
{
	return d * PI / 180.0;   //角度1? = π / 180
}
 
//计算距离
double get_distance(double lat1, double lng1, double lat2, double lng2)
{
	double radLat1 = radian(lat1);
	double radLat2 = radian(lat2);
	double a = radLat1 - radLat2;
	double b = radian(lng1) - radian(lng2);
	double dtemp = -1.0000;


	double dst = 2 * asin((sqrt(pow(sin(a / 2), 2) + cos(radLat1) * cos(radLat2) * pow(sin(b / 2), 2) )));

	dst = dst * EARTH_RADIUS;
	dst= round(dst * 10000) / 100;
	return dst;
}
 

int nSortCineams(STCIMEMAS stCinema,int nLoop)
{
	int i = -1;
	int j = -1; 
	int nMaxCount = sizeof(stCinemas)/sizeof(STCIMEMAS);
	
	for(i=0;i<nLoop;i++)
	{		
			if ((stCinema.dDistance-stCinemas[i].dDistance) < 0.000001)
			{	
					for(j=nLoop-1;j>i;j--)
					{
						memcpy(&stCinemas[j],&stCinemas[j-1],sizeof(stCinema));
					}
					memcpy(&stCinemas[i],&stCinema,sizeof(stCinema));
					break;
			}
	}
}

					
/************************************************************************
动态组件函数定义
组件函数名称:DATA_DEC_DATE
组件名称:DATA_DEC_DATE
组件功能:
组件参数列表：
	序号      参数类型   参数名称           资源类别            缺省值                        可空      参数说明
	1         输入      para1               ICXP报文                                          0         元素名=字符赋值公式
组件结果状态:
	结果状态码          结果说明
	-9999               缺省
	0                   成功
日志信息:
	日志级别            日志宏 

响应信息:
	内部响应码           内部响应信息 

主要操作元素:
	元素路径             操作 

主要操作库表:
	表名                 操作 

使用限制:

项 目 组:
程 序 员:
发布日期:
修改日期:/2015-7-31 18:33:21(gen)
参数使用示例:
************************************************************************/
IRESULT DB_QRY_NEARCINEMA(HXMLTREE lXmlhandle)
{
	
	char szSql[1024];
	char szCity[160];
	double dLongitude;
	double dLatitude;
	char szRootPath[256];
	char szDescPath[256];
	
	int	nParas=-1;
	int	nRet = -1;
	int	nRows = -1;
	int nMaxCount = -1;
	int	i = -1;
	int	j = -1;
	char *qerrmsg = NULL;
	char *qSqlInfo = NULL;
	char szColname[64];
	STCIMEMAS stCinema;
	ST_FACILITY stFacility;
	CURSOR cur_QryCinemas;
	CURSOR cur_Facilitys;

	fpub_InitSoComp(lXmlhandle);
	
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行开始", fpub_GetCompname(lXmlhandle)), __func__)
#endif
	
	
	nParas=fpub_GetPARAcount(lXmlhandle);
	
	/*XXX处理失败*/
  if ( nParas <	5 )
  {
    LOG(LM_STD, Fmtmsg("  -->处理失败:XXXX"), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }	
  
  
  for(i=0;i<MAXCOUNTCINEMAS;i++)
  {
  		stCinemas[i].dDistance=999999999.999;
  }
  
  COMP_GETPARSEPARAS(1, szCity, "查询城市");
  memset(szSql,0x00,sizeof(szSql));
  COMP_GETPARSEPARAS(2, szSql, "经度:");
  dLongitude = atof(szSql);
  memset(szSql,0x00,sizeof(szSql)); 
  COMP_GETPARSEPARAS(3, szSql, "纬度:");
  dLatitude = atof(szSql);
  memset(szSql,0x00,sizeof(szSql)); 
  COMP_GETPARSEPARAS(4, szSql, "最大数据量:");
  nMaxCount = atoi(szSql);
	COMP_GETPARSEPARAS(5, szRootPath, "基础路径:");
  
  LOG(LM_STD, Fmtmsg("  -->查询城市:[%s]",szCity), __func__);
	LOG(LM_STD, Fmtmsg("  -->基础路径:[%s]",szRootPath), __func__);
	LOG(LM_STD, Fmtmsg("  -->所在经度:[%lf]纬度[%lf]",dLongitude,dLatitude), __func__);
	sprintf(szSql,"select cinemaId,cinemaName,spCode,cityid,countyCode,countyName,longitude,latitude,address,imgurl "
	 "from yxt_cinemas "
	 " where cityid='%s' and (latitude !='' and latitude is not null) and (longitude !='' and longitude is not null) ",szCity);
		 
	LOG(LM_STD, Fmtmsg("  -->SQL:[%s]",szSql), __func__); 
		 
	if ((cur_QryCinemas = DCIDeclareCursor(szSql,0),DCI_STMT_LOCATOR) == -1)
	{
		DCIFreeCursor(cur_QryCinemas);
		LOGRET(COMPRET_FAIL,LM_STD,"准备游标失败","DCIDeclareCursor");
	}
	
	if( -1 == (nRet = DCIExecute(cur_QryCinemas)))
	{
		DCIFreeCursor(cur_QryCinemas);
		LOGRET(COMPRET_FAIL,LM_STD,"准备游标失败","DCIDeclareCursor");
	}


	while(1 == DCIFetch2(cur_QryCinemas,DCI_FETCH_NEXT,0))
	{
			memset(&stCinema,0x00,sizeof(stCinema));

			strncpy(stCinema.szCinemaId,DCIFieldAsString(cur_QryCinemas,0),sizeof(stCinema.szCinemaId));
			strncpy(stCinema.szCinemaName,DCIFieldAsString(cur_QryCinemas,1),sizeof(stCinema.szCinemaName));
			strncpy(stCinema.szSpCode,DCIFieldAsString(cur_QryCinemas,2),sizeof(stCinema.szSpCode));
			strncpy(stCinema.szCityid,DCIFieldAsString(cur_QryCinemas,3),sizeof(stCinema.szCityid));
			strncpy(stCinema.szCountyCode,DCIFieldAsString(cur_QryCinemas,4),sizeof(stCinema.szCountyCode));
			strncpy(stCinema.szCountyName,DCIFieldAsString(cur_QryCinemas,5),sizeof(stCinema.szCountyName));
			strncpy(stCinema.dLongitude,DCIFieldAsString(cur_QryCinemas,6),sizeof(stCinema.dLongitude));
			strncpy(stCinema.szLatitude,DCIFieldAsString(cur_QryCinemas,7),sizeof(stCinema.szLatitude));
			strncpy(stCinema.szAddress,DCIFieldAsString(cur_QryCinemas,8),sizeof(stCinema.szAddress));
			strncpy(stCinema.szImgUrl,DCIFieldAsString(cur_QryCinemas,9),sizeof(stCinema.szImgUrl));
		

	/**/LOG(LM_STD, Fmtmsg("  -->szCinemaId:[%s]szCinemaId[%s]",stCinema.szCinemaId,stCinema.szCinemaId), __func__);
			LOG(LM_STD, Fmtmsg("  -->szCinemaId:[%s]szCinemaName[%s]",stCinema.szCinemaId,stCinema.szCinemaName), __func__);
			LOG(LM_STD, Fmtmsg("  -->szCinemaId:[%s]szSpCode[%s]",stCinema.szCinemaId,stCinema.szSpCode), __func__);
			LOG(LM_STD, Fmtmsg("  -->szCinemaId:[%s]szCityid[%s]",stCinema.szCinemaId,stCinema.szCityid), __func__);
			LOG(LM_STD, Fmtmsg("  -->szCinemaId:[%s]szCountyCode[%s]",stCinema.szCinemaId,stCinema.szCountyCode), __func__);
			LOG(LM_STD, Fmtmsg("  -->szCinemaId:[%s]szCountyName[%s]",stCinema.szCinemaId,stCinema.szCountyName), __func__);
			LOG(LM_STD, Fmtmsg("  -->szCinemaId:[%s]dLongitude[%s]",stCinema.szCinemaId,stCinema.dLongitude), __func__);
			LOG(LM_STD, Fmtmsg("  -->szCinemaId:[%s]szLatitude[%s]",stCinema.szCinemaId,stCinema.szLatitude), __func__);
			LOG(LM_STD, Fmtmsg("  -->szCinemaId:[%s]szAddress[%s]",stCinema.szCinemaId,stCinema.szAddress), __func__);
			LOG(LM_STD, Fmtmsg("  -->szCinemaId:[%s]szImgUrl[%s]",stCinema.szCinemaId,stCinema.szImgUrl), __func__);
			
			stCinema.dDistance=get_distance(atof(stCinema.szLatitude),atof(stCinema.dLongitude),dLatitude,dLongitude);
		
			LOG(LM_STD, Fmtmsg("  -->CinemaId:[%s][%lf]",stCinema.szCinemaId,stCinema.dDistance), __func__);
		
			nSortCineams(stCinema,nMaxCount);
				
	}
	

  for(i=0;i<nMaxCount;i++)
  {
			sprintf(szDescPath,"%s/ROWS|%d/CINEMA_ID%c",szRootPath,i+1,'\0')	;	
			xml_SetElement(lXmlhandle, szDescPath, alltrim(stCinemas[i].szCinemaId)); 	
				
			sprintf(szDescPath,"%s/ROWS|%d/CINEMA_NAME%c",szRootPath,i+1,'\0')	;	
			xml_SetElement(lXmlhandle, szDescPath, alltrim(stCinemas[i].szCinemaName)); 	

			sprintf(szDescPath,"%s/ROWS|%d/SP_CODE%c",szRootPath,i+1,'\0')	;	
			xml_SetElement(lXmlhandle, szDescPath, alltrim(stCinemas[i].szSpCode)); 	
			
			sprintf(szDescPath,"%s/ROWS|%d/ZONE_CODE%c",szRootPath,i+1,'\0')	;	
			xml_SetElement(lXmlhandle, szDescPath, alltrim(stCinemas[i].szCountyCode)); 	
			
			sprintf(szDescPath,"%s/ROWS|%d/COUNTY_NAME%c",szRootPath,i+1,'\0')	;	
			xml_SetElement(lXmlhandle, szDescPath, alltrim(stCinemas[i].szCountyName)); 	
							
			sprintf(szDescPath,"%s/ROWS|%d/LONGITUDE_VALUE%c",szRootPath,i+1,'\0')	;	
			xml_SetElement(lXmlhandle, szDescPath, alltrim(stCinemas[i].dLongitude)); 	
			
			sprintf(szDescPath,"%s/ROWS|%d/LATITUDE_VALUE%c",szRootPath,i+1,'\0')	;	
			xml_SetElement(lXmlhandle, szDescPath, alltrim(stCinemas[i].szLatitude)); 	
			
			sprintf(szDescPath,"%s/ROWS|%d/ADDRESS%c",szRootPath,i+1,'\0')	;	
			xml_SetElement(lXmlhandle, szDescPath, alltrim(stCinemas[i].szAddress)); 	
			
			sprintf(szDescPath,"%s/ROWS|%d/PICTURE_URL_ADDRESS%c",szRootPath,i+1,'\0')	;	
			xml_SetElement(lXmlhandle, szDescPath, alltrim(stCinemas[i].szImgUrl)); 	
			
			sprintf(szDescPath,"%s/ROWS|%d/DISTANCE_VALUE%c",szRootPath,i+1,'\0')	;	
			sprintf(szSql,"%.2lf",stCinemas[i].dDistance);
			xml_SetElement(lXmlhandle, szDescPath, alltrim(szSql)); 	
			
			sprintf(szSql,"select ICON_ID,ICON_NAME,ICON_URL,SMALL_ICON_URL from yxt_facilitys "
			 " where cinemaId='%s'",alltrim(stCinemas[i].szCinemaId));
			LOG(LM_STD, Fmtmsg("  -->SQL:[%s]",szSql), __func__); 
			 
			if ((cur_Facilitys = DCIDeclareCursor(szSql,0),DCI_STMT_LOCATOR) == -1)
			{
				DCIFreeCursor(cur_Facilitys);
				LOGRET(COMPRET_FAIL,LM_STD,"准备游标失败","DCIDeclareCursor");
			}
		
			if( -1 == (nRet = DCIExecute(cur_Facilitys)))
			{
				DCIFreeCursor(cur_Facilitys);
				LOGRET(COMPRET_FAIL,LM_STD,"准备游标失败","DCIDeclareCursor");
			}

			for(j =1;1 == DCIFetch2(cur_Facilitys,DCI_FETCH_NEXT,0);j++)
			{	
				memset(&stFacility,0x00,sizeof(stFacility));

				strncpy(stFacility.ICON_ID,DCIFieldAsString(cur_Facilitys,0),sizeof(stFacility.ICON_ID));
				stFacility.ICON_ID[sizeof(stFacility.ICON_ID)-1]='\0';
				strncpy(stFacility.ICON_NAME,DCIFieldAsString(cur_Facilitys,1),sizeof(stFacility.ICON_NAME));
				strncpy(stFacility.ICON_URL,DCIFieldAsString(cur_Facilitys,2),sizeof(stFacility.ICON_URL));
				strncpy(stFacility.SMALL_ICON_URL,DCIFieldAsString(cur_Facilitys,3),sizeof(stFacility.SMALL_ICON_URL));
				
				
				sprintf(szDescPath,"%s/ROWS|%d/facilitys|%d/ICON_ID",szRootPath,i+1,j)	;	
				xml_SetElement(lXmlhandle, szDescPath, alltrim(stFacility.ICON_ID)); 	
				
				sprintf(szDescPath,"%s/ROWS|%d/facilitys|%d/ICON_NAME",szRootPath,i+1,j)	;	
				xml_SetElement(lXmlhandle, szDescPath, alltrim(stFacility.ICON_NAME)); 
				
				sprintf(szDescPath,"%s/ROWS|%d/facilitys|%d/ICON_URL",szRootPath,i+1,j)	;	
				xml_SetElement(lXmlhandle, szDescPath, alltrim(stFacility.ICON_URL)); 
				
				sprintf(szDescPath,"%s/ROWS|%d/facilitys|%d/SMALL_ICON_URL",szRootPath,i+1,j)	;	
				xml_SetElement(lXmlhandle, szDescPath, alltrim(stFacility.SMALL_ICON_URL)); 

			}
			
			DCIFreeCursor(cur_Facilitys);
		
		
  }
	
	DCIFreeCursor(cur_Facilitys);
	DCIFreeCursor(cur_QryCinemas);
	
#ifdef DEBUG
  LOG(LM_DEBUG, Fmtmsg("组件[%s]执行结束", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}



 
