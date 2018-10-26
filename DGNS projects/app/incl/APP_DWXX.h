/***********************************************************************
°æÈ¨ËùÓÐ:ºãÉúµç×Ó¹É·ÝÓÐÏÞ¹«Ë¾
ÏîÄ¿Ãû³Æ:×ÛºÏ¼¼ÊõÆ½Ì¨(Turandot)ÏîÄ¿
°æ    ±¾:V1.00
²Ù×÷ÏµÍ³:
Êý ¾Ý ¿â:INFORMIX
ÎÄ ¼þ Ãû:APP_DWXX.h
ÎÄ¼þÃèÊö:½á¹¹¶¨ÒåÊý¾Ý¿â¿ª·¢Ç¶CÍ·ÎÄ¼þ
Ïî Ä¿ ×é:
³Ì Ðò Ô±:[Ñî¶«]
·¢²¼Ê±¼ä:2009-4-29 19:40:39 [Gen]
ÐÞ    ¶©:
ÐÞ¸ÄÊ±¼ä:
************************************************************************
±í    Ãû:APP_DWXX (µ¥Î»ÐÅÏ¢±í)
Ëµ    Ã÷:
************************************************************************
ÐÞ¸Ä¼ÇÂ¼:
ÐÞ¸ÄÈÕÆÚ:
ÐÞ¸ÄÄÚÈÝ:
ÐÞ ¸Ä ÈË:
ÐÞ¸ÄÄÚÈÝ:
************************************************************************/
#ifndef __APP_DWXX_H__
#define __APP_DWXX_H__
typedef struct TDB_APP_DWXX
{
  char   dwbh[16+1];              /*µ¥Î»±àºÅ*/
              /**/
  char   dwmc[80+1];              /*µ¥Î»Ãû³Æ*/
              /*µ¥Î»Ãû³Æ*/
  char   dwzjlx[2+1];              /*µ¥Î»Ö¤¼þÀàÐÍ*/
              /*µ¥Î»Ö¤¼þÀàÐÍ ¼ûÊý¾Ý×Öµä KEY=K_DWZJLX*/
  char   dwzjhm[32+1];              /*µ¥Î»Ö¤¼þºÅÂë*/
              /*µ¥Î»Ö¤¼þºÅÂë*/
  char   dwlxr[16+1];              /*µ¥Î»ÁªÏµÈËÃû³Æ*/
              /*µ¥Î»ÁªÏµÈËÃû³Æ*/
  char   dwlxrdh[16+1];              /*µ¥Î»ÁªÏµÈËµç»°*/
              /*µ¥Î»ÁªÏµÈËµç»°*/
  char   dwdz[60+1];              /*µ¥Î»ÁªÏµµØÖ·*/
              /*µ¥Î»ÁªÏµµØÖ·*/
  char   dwemail[32+1];              /*µ¥Î»ÁªÏµemail*/
              /*µ¥Î»ÁªÏµemail*/
  char   whjg[16+1];              /*Î¬»¤»ú¹¹*/
              /**/
  char   whgy[16+1];              /*Î¬»¤¹ñÔ±*/
              /**/
  char   whsj[14+1];              /*Î¬»¤Ê±¼ä*/
              /**/
  char   extfld1[40+1];              /*À©Õ¹²ÎÊý1*/
              /*À©Õ¹²ÎÊý1*/
  char   extfld2[40+1];              /*À©Õ¹²ÎÊý2*/
              /*À©Õ¹²ÎÊý2*/
  char   zt[1+1];              /*×´Ì¬*/
              /*×´Ì¬ 0 Õý³ XÉ¾³ý*/
}APP_DWXX;

#define SD_DATA  APP_DWXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  dwmc, 0),\
	DEFSDMEMBER(T_STRING,  dwzjlx, 0),\
	DEFSDMEMBER(T_STRING,  dwzjhm, 0),\
	DEFSDMEMBER(T_STRING,  dwlxr, 0),\
	DEFSDMEMBER(T_STRING,  dwlxrdh, 0),\
	DEFSDMEMBER(T_STRING,  dwdz, 0),\
	DEFSDMEMBER(T_STRING,  dwemail, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  zt, 0)


	DECLAREFIELDS(SD_APP_DWXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_DWXX_H__*/
