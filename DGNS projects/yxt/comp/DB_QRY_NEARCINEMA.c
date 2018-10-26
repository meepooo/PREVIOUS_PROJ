/***********************************************************************
��Ȩ����:�������ӹɷ����޹�˾
��Ŀ����:�ۺϼ���ƽ̨(Turandot)��Ŀ
��    ��:V1.00
����ϵͳ:
�� �� ��:DATA_DEC_DATE.c
�ļ�����:
�� Ŀ ��:
�� �� Ա:[]
����ʱ��:2015-7-31 18:33:21[Gen]
��    ��:
�޸�ʱ��:
****************************************************************************/
#include <string.h>
#include <math.h>
#include "DCI.h"
#include "gaps_head.h"

#define SOCOMPBUILDNO BUILDDATETIME
#define SOCOMPVERSION "V1.0.0"

#define PI  3.1415926
#define EARTH_RADIUS 6378.137//������ư뾶
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
   ע��������Ϊ����⹫������,�����ڷ���״̬����ʾ�ڲ��汾��Ϣ
       �����������£�ÿ�θ��¾�Ӧ�޸İ汾�š�������Ӧ��Ϣ
*/
int ShowSocompVersion(char *sinfo,int isize)
{
  char sversion[]="<?xml version=\"1.0\" encoding=\"GB2312\"?>"
     "<root>"
	     "<soname>DATA_DEC_DATE.so</soname>"
	     "<sosrcname>DATA_DEC_DATE.c</sosrcname>"
	     "<sonote></sonote>"
	     "<version>"
	       "<rec ver=\"1.0.00\" modify=\"2015-7-31 18:33:21\" programer=\"[����ΰ]\" filesize=\"FILE\">��ʼ������</rec>"
	     "</version>"
     "</root>";
  printf("\n================��̬���������Ϣ================\n");
  printf("SOCOMPBUILDNO:%s.\n",SOCOMPBUILDNO);
  printf("SOCOMPVERSION:%s.\n",SOCOMPVERSION);
  printf("%s-%s\n",__PROJECTSNAME,__VERSION);
  if (strlen(sversion) >= isize)
  {
  	printf(" -->ȡ��ϸ��Ϣʧ��...\n");
  	return -2;
  }
 	strcpy(sinfo,sversion);
 	printf(" -->��鿴��ϸ��Ϣ...\n");
  return 0;
}

 
// �󻡶�
double radian(double d)
{
	return d * PI / 180.0;   //�Ƕ�1? = �� / 180
}
 
//�������
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
��̬�����������
�����������:DATA_DEC_DATE
�������:DATA_DEC_DATE
�������:
��������б�
	���      ��������   ��������           ��Դ���            ȱʡֵ                        �ɿ�      ����˵��
	1         ����      para1               ICXP����                                          0         Ԫ����=�ַ���ֵ��ʽ
������״̬:
	���״̬��          ���˵��
	-9999               ȱʡ
	0                   �ɹ�
��־��Ϣ:
	��־����            ��־�� 

��Ӧ��Ϣ:
	�ڲ���Ӧ��           �ڲ���Ӧ��Ϣ 

��Ҫ����Ԫ��:
	Ԫ��·��             ���� 

��Ҫ�������:
	����                 ���� 

ʹ������:

�� Ŀ ��:
�� �� Ա:
��������:
�޸�����:/2015-7-31 18:33:21(gen)
����ʹ��ʾ��:
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
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�п�ʼ", fpub_GetCompname(lXmlhandle)), __func__)
#endif
	
	
	nParas=fpub_GetPARAcount(lXmlhandle);
	
	/*XXX����ʧ��*/
  if ( nParas <	5 )
  {
    LOG(LM_STD, Fmtmsg("  -->����ʧ��:XXXX"), __func__);
    fpub_SetMsg(lXmlhandle, MID_YW_ERROR, MSG_YW_ERROR);
    fpub_SetCompStatus(lXmlhandle, COMPSTATUS_FAIL);
    return COMPRET_FAIL;
  }	
  
  
  for(i=0;i<MAXCOUNTCINEMAS;i++)
  {
  		stCinemas[i].dDistance=999999999.999;
  }
  
  COMP_GETPARSEPARAS(1, szCity, "��ѯ����");
  memset(szSql,0x00,sizeof(szSql));
  COMP_GETPARSEPARAS(2, szSql, "����:");
  dLongitude = atof(szSql);
  memset(szSql,0x00,sizeof(szSql)); 
  COMP_GETPARSEPARAS(3, szSql, "γ��:");
  dLatitude = atof(szSql);
  memset(szSql,0x00,sizeof(szSql)); 
  COMP_GETPARSEPARAS(4, szSql, "���������:");
  nMaxCount = atoi(szSql);
	COMP_GETPARSEPARAS(5, szRootPath, "����·��:");
  
  LOG(LM_STD, Fmtmsg("  -->��ѯ����:[%s]",szCity), __func__);
	LOG(LM_STD, Fmtmsg("  -->����·��:[%s]",szRootPath), __func__);
	LOG(LM_STD, Fmtmsg("  -->���ھ���:[%lf]γ��[%lf]",dLongitude,dLatitude), __func__);
	sprintf(szSql,"select cinemaId,cinemaName,spCode,cityid,countyCode,countyName,longitude,latitude,address,imgurl "
	 "from yxt_cinemas "
	 " where cityid='%s' and (latitude !='' and latitude is not null) and (longitude !='' and longitude is not null) ",szCity);
		 
	LOG(LM_STD, Fmtmsg("  -->SQL:[%s]",szSql), __func__); 
		 
	if ((cur_QryCinemas = DCIDeclareCursor(szSql,0),DCI_STMT_LOCATOR) == -1)
	{
		DCIFreeCursor(cur_QryCinemas);
		LOGRET(COMPRET_FAIL,LM_STD,"׼���α�ʧ��","DCIDeclareCursor");
	}
	
	if( -1 == (nRet = DCIExecute(cur_QryCinemas)))
	{
		DCIFreeCursor(cur_QryCinemas);
		LOGRET(COMPRET_FAIL,LM_STD,"׼���α�ʧ��","DCIDeclareCursor");
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
				LOGRET(COMPRET_FAIL,LM_STD,"׼���α�ʧ��","DCIDeclareCursor");
			}
		
			if( -1 == (nRet = DCIExecute(cur_Facilitys)))
			{
				DCIFreeCursor(cur_Facilitys);
				LOGRET(COMPRET_FAIL,LM_STD,"׼���α�ʧ��","DCIDeclareCursor");
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
  LOG(LM_DEBUG, Fmtmsg("���[%s]ִ�н���", fpub_GetCompname(lXmlhandle)), __func__)
#endif

  fpub_SetCompStatus(lXmlhandle, COMPSTATUS_SUCC);
  return 0;
}



 
