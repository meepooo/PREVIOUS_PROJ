/***********************************************************************
°æÈ¨ËùÓÐ:ºãÉúµç×Ó¹É·ÝÓÐÏÞ¹«Ë¾
ÏîÄ¿Ãû³Æ:×ÛºÏ¼¼ÊõÆ½Ì¨(Turandot)ÏîÄ¿
°æ    ±¾:V1.00
²Ù×÷ÏµÍ³:
Êý ¾Ý ¿â:INFORMIX
ÎÄ ¼þ Ãû:APP_JYXX.h
ÎÄ¼þÃèÊö:½á¹¹¶¨ÒåÊý¾Ý¿â¿ª·¢Ç¶CÍ·ÎÄ¼þ
Ïî Ä¿ ×é:
³Ì Ðò Ô±:[Ñî¶«]
·¢²¼Ê±¼ä:2009-4-29 19:40:39 [Gen]
ÐÞ    ¶©:
ÐÞ¸ÄÊ±¼ä:
************************************************************************
±í    Ãû:APP_JYXX (½»Ò×ÐÅÏ¢±í)
Ëµ    Ã÷:
************************************************************************
ÐÞ¸Ä¼ÇÂ¼:
ÐÞ¸ÄÈÕÆÚ:
ÐÞ¸ÄÄÚÈÝ:
ÐÞ ¸Ä ÈË:
ÐÞ¸ÄÄÚÈÝ:
************************************************************************/
#ifndef __APP_JYXX_H__
#define __APP_JYXX_H__
typedef struct TDB_APP_JYXX
{
  char   jydm[8+1];              /*½»Ò×´úÂë*/
              /*½»Ò×´úÂë*/
  char   jymc[40+1];              /*½»Ò×Ãû³Æ*/
              /*½»Ò×Ãû³Æ*/
  char   yybs[8+1];              /*Ó¦ÓÃ±êÊ¶*/
              /*Ó¦ÓÃ±êÊ¶ Ó¦ÓÃ±êÊ¶ ¼ûapp_yyxx±í*/
  char   jylx[1+1];              /*½»Ò×ÀàÐÍ*/
              /*½»Ò×ÀàÐÍ 0Õý½»Ò× 1·´½»Ò 9ÆäËû*/
  char   lsjlbz[1+1];              /*Á÷Ë®¼ÇÂ¼±êÖ¾*/
              /*Á÷Ë®¼ÇÂ¼±êÖ¾ 0¼ÇÂ¼ 1²»¼ÇÂ¼*/
  char   rzbz[1+1];              /*ÈëÕÊ±êÖ¾*/
              /*ÈëÕÊ±êÖ¾ 0ÈëÕÊ 1·ÇÈëÕÊ*/
  char   bbbz[1+1];              /*±¨±í±êÖ¾*/
              /*±¨±í±êÖ¾ 0±¨±í 1·Ç±¨±í*/
  char   cpxg[1+1];              /*²úÆ·Ïà¹Ø*/
              /*²úÆ·Ïà¹Ø 0Ïà¹Ø 1²»Ïà¹Ø(½»Ò×Óë²úÆ·ÎÞ¹ØÊ±£¬½»Ò×µÄ»ú¹¹£¬ÇþµÀ£¬½»Ò×Ê±¼ä£¬ÏÞ¶îµÈ¶¼²»×ö¿ØÖÆ)*/
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
  char   qtbz[1+1];              /*ÆôÍ£±êÖ¾*/
              /*ÆôÍ£±êÖ¾ 0¿ªÆô 1¹Ø±Õ*/
}APP_JYXX;

#define SD_DATA  APP_JYXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  jymc, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  lsjlbz, 0),\
	DEFSDMEMBER(T_STRING,  rzbz, 0),\
	DEFSDMEMBER(T_STRING,  bbbz, 0),\
	DEFSDMEMBER(T_STRING,  cpxg, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  qtbz, 0)


	DECLAREFIELDS(SD_APP_JYXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_JYXX_H__*/

