/***********************************************************************
°æÈ¨ËùÓÐ:ºãÉúµç×Ó¹É·ÝÓÐÏÞ¹«Ë¾
ÏîÄ¿Ãû³Æ:×ÛºÏ¼¼ÊõÆ½Ì¨(Turandot)ÏîÄ¿
°æ    ±¾:V1.00
²Ù×÷ÏµÍ³:
Êý ¾Ý ¿â:INFORMIX
ÎÄ ¼þ Ãû:APP_SXFFL.h
ÎÄ¼þÃèÊö:½á¹¹¶¨ÒåÊý¾Ý¿â¿ª·¢Ç¶CÍ·ÎÄ¼þ
Ïî Ä¿ ×é:
³Ì Ðò Ô±:[Ñî¶«]
·¢²¼Ê±¼ä:2009-4-29 19:40:39 [Gen]
ÐÞ    ¶©:
ÐÞ¸ÄÊ±¼ä:
************************************************************************
±í    Ãû:APP_SXFFL (ÊÖÐø·Ñ·ÑÂÊ±í)
Ëµ    Ã÷:
************************************************************************
ÐÞ¸Ä¼ÇÂ¼:
ÐÞ¸ÄÈÕÆÚ:
ÐÞ¸ÄÄÚÈÝ:
ÐÞ ¸Ä ÈË:
ÐÞ¸ÄÄÚÈÝ:
************************************************************************/
#ifndef __APP_SXFFL_H__
#define __APP_SXFFL_H__
typedef struct TDB_APP_SXFFL
{
  char   flbs[32+1];              /*·ÑÂÊ±êÊ¶*/
              /*ÊÖ¹¤ÊäÈë*/
  char   xh[2+1];              /*ÐòºÅ*/
              /*¸¡¶¯·ÑÂÊÊ±¶à¸ö·ÑÂÊ·Ö¶ÎµÄÐòºÅ*/
  char   fdbz[1+1];              /*¸¡¶¯±êÖ¾*/
              /*0 ²»¸¡¶¯£¬  ¸¡¶ */
  char   nwkbz[1+1];              /*ÄÚÍâ¿Û±êÖ¾*/
              /*0Íâ¿Û  1 ÄÚ¿  Ä¬È 0*/
  char   sxxkz[1+1];              /*ÉÏÏÂÏÞ¿ØÖÆ*/
              /*0 ¿ØÖÆ   ²»¿ØÖ */
  double  sxje;              /*ÉÏÏÞ½ð¶î*/
              /**/
  double  xxje;              /*ÏÂÏÞ½ð¶î*/
              /**/
  char   jslx[1+1];              /*¼ÆËã²ÎÊýÀàÐÍ*/
              /*¼ÆËã²ÎÊýÀàÐÍ 1 ½ð¶  2°Ù·Ö±   Èç¹ûÎª £¬±íÊ¾ÊÖÐø·Ñ¼ÆËãÕë¶Ô½»Ò×±ÊÊýµÄ£¬Èç¹ûÊÇ°Ù·Ö±È£¬±íÊ¾ÊÖÐø·Ñ¼ÆËãÕë¶Ô½»Ò×½ð¶î¡£*/
  double  jscs;              /*¼ÆËã²ÎÊý*/
              /*¼ÆËã²ÎÊý ¼ÆËãÀàÐÍÎª1 ÊäÈë½ð¶ ÊäÈë ±íÊ¾1Ôª£»ÀàÐÍÎª2£¬ÊäÈë°Ù·Ö± ÈçÊäÈë £¬±íÊ¾1£¥*/
  char   kjbz[1+1];              /*ÓÅ»Ý±êÖ¾*/
              /*0ÎÞÓÅ»Ý 1 ´òÕ  ½ð¶î¿Û¼ Ä¬ÈÏ0*/
  double  kjcs;              /*¿Û¼õ²ÎÊý*/
              /*ÓÅ»Ý %½áÎ²±êÊ¶ÕÛ¿ÛÂÊ ·ñÔòÎª¿Û¼õ½ð¶î*/
  char   fdlx[1+1];              /*¸¡¶¯ÀàÐÍ*/
              /*¸¡¶¯ÀàÐÍ 1 ½»Ò×±ÊÊý¸¡¶  ½»Ò×½ð¶î¸¡¶¯*/
  char   ljbz[1+1];              /*ÀÛ½ ±êÖ¾*/
              /*0 ²»ÀÛ½ø   ÀÛ½ Ä¬ÈÏ0*/
  char   bhbz[1+1];              /*°üº¬ÉÏÏÞ±êÖ¾*/
              /*¼ÆËã²ÎÊý°üº¬ÉÏÏÞ±êÖ¾  1 °üº¬ÉÏÏ 0°üº¬ÏÂÏÞ*/
  char   qss[16+1];              /*ÆðÊ¼²ÎÊý*/
              /**/
  char   jss[16+1];              /*½áÊø²ÎÊý*/
              /**/
  char   sm[40+1];              /*ËµÃ÷*/
              /*ËµÃ÷*/
  char   whjg[16+1];              /*Î¬»¤»ú¹¹*/
              /**/
  char   whgy[16+1];              /*Î¬»¤¹ñÔ±*/
              /**/
  char   whsj[14+1];              /*Î¬»¤Ê±¼ä*/
              /**/
}APP_SXFFL;

#define SD_DATA  APP_SXFFL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  flbs, 0),\
	DEFSDMEMBER(T_STRING,  xh, 0),\
	DEFSDMEMBER(T_STRING,  fdbz, 0),\
	DEFSDMEMBER(T_STRING,  nwkbz, 0),\
	DEFSDMEMBER(T_STRING,  sxxkz, 0),\
	DEFSDMEMBER(T_DOUBLE,  sxje, 2),\
	DEFSDMEMBER(T_DOUBLE,  xxje, 2),\
	DEFSDMEMBER(T_STRING,  jslx, 0),\
	DEFSDMEMBER(T_DOUBLE,  jscs, 6),\
	DEFSDMEMBER(T_STRING,  kjbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  kjcs, 6),\
	DEFSDMEMBER(T_STRING,  fdlx, 0),\
	DEFSDMEMBER(T_STRING,  ljbz, 0),\
	DEFSDMEMBER(T_STRING,  bhbz, 0),\
	DEFSDMEMBER(T_STRING,  qss, 0),\
	DEFSDMEMBER(T_STRING,  jss, 0),\
	DEFSDMEMBER(T_STRING,  sm, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0)

	DECLAREFIELDS(SD_APP_SXFFL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_SXFFL_H__*/

