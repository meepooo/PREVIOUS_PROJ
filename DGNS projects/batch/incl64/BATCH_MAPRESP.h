/***********************************************************************
°æÈ¨ËùÓÐ:ºãÉúµç×Ó¹É·ÝÓÐÏÞ¹«Ë¾
ÏîÄ¿Ãû³Æ:×ÛºÏ¼¼ÊõÆ½Ì¨(Turandot)ÏîÄ¿
°æ    ±¾:V1.00
²Ù×÷ÏµÍ³:
Êý ¾Ý ¿â:INFORMIX
ÎÄ ¼þ Ãû:BATCH_MAPRESP.h
ÎÄ¼þÃèÊö:½á¹¹¶¨ÒåÊý¾Ý¿â¿ª·¢Ç¶CÍ·ÎÄ¼þ
Ïî Ä¿ ×é:
³Ì Ðò Ô±:[Ñî¶«]
·¢²¼Ê±¼ä:2009-4-29 19:40:39 [Gen]
ÐÞ    ¶©:
ÐÞ¸ÄÊ±¼ä:
************************************************************************
±í    Ãû:BATCH_MAPRESP (ÅúÁ¿ÏìÓ¦ÂëÓ³Éä)
Ëµ    Ã÷:
************************************************************************
ÐÞ¸Ä¼ÇÂ¼:
ÐÞ¸ÄÈÕÆÚ:
ÐÞ¸ÄÄÚÈÝ:
ÐÞ ¸Ä ÈË:
ÐÞ¸ÄÄÚÈÝ:
************************************************************************/
#ifndef __BATCH_MAPRESP_H__
#define __BATCH_MAPRESP_H__
typedef struct TDB_BATCH_MAPRESP
{
	char   mapid[32+1];  /*Ó³Éä±êÊ¶*/
		/**/
	char   note[40+1];  /*Ó³ÉäËµÃ÷*/
		/**/
	char   resp_s[10+1];  /*Ô´ÏìÓ¦Âë*/
		/**/
	char   resp_d[10+1];  /*Ó³ÉäÏìÓ¦Âë*/
		/**/
	char   msg_d[40+1];  /*ÏìÓ¦ÐÅÏ¢*/
		/**/
	char   bz[1+1];  /*Ä¬ÈÏ×ª»»±êÊ¶*/
		/*Ä¬ÈÏ×ª»»±êÊ¶ 0 Ê  · Ä¬È  Ò»¸öÏìÓ¦Âë×ÊÔ´£¬×î¶àÒ»¸ Ä¬ÈÏ×ª»»*/
	char   whjg[16+1];  /*Î¬»¤»ú¹¹*/
		/**/
	char   whgy[16+1];  /*Î¬»¤¹ñÔ±*/
		/**/
	char   whsj[14+1];  /*Î¬»¤Ê±¼ä*/
		/**/

}BATCH_MAPRESP;

#define SD_DATA  BATCH_MAPRESP
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  mapid, 0),\
	DEFSDMEMBER(T_STRING,  note, 0),\
	DEFSDMEMBER(T_STRING,  resp_s, 0),\
	DEFSDMEMBER(T_STRING,  resp_d, 0),\
	DEFSDMEMBER(T_STRING,  msg_d, 0),\
	DEFSDMEMBER(T_STRING,  bz, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)


	DECLAREFIELDS(SD_BATCH_MAPRESP)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_MAPRESP_H__*/
