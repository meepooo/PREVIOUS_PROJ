/***********************************************************************
°æÈ¨ËùÓÐ:ºãÉúµç×Ó¹É·ÝÓÐÏÞ¹«Ë¾
ÏîÄ¿Ãû³Æ:×ÛºÏ¼¼ÊõÆ½Ì¨(Turandot)ÏîÄ¿
°æ    ±¾:V1.00
²Ù×÷ÏµÍ³:
Êý ¾Ý ¿â:INFORMIX
ÎÄ ¼þ Ãû:APP_SXFLS.h
ÎÄ¼þÃèÊö:½á¹¹¶¨ÒåÊý¾Ý¿â¿ª·¢Ç¶CÍ·ÎÄ¼þ
Ïî Ä¿ ×é:
³Ì Ðò Ô±:[Ñî¶«]
·¢²¼Ê±¼ä:2009-4-29 19:40:39 [Gen]
ÐÞ    ¶©:
ÐÞ¸ÄÊ±¼ä:
************************************************************************
±í    Ãû:APP_SXFLS (ÊÖÐø·ÑÁ÷Ë®±í)
Ëµ    Ã÷:
************************************************************************
ÐÞ¸Ä¼ÇÂ¼:
ÐÞ¸ÄÈÕÆÚ:
ÐÞ¸ÄÄÚÈÝ:
ÐÞ ¸Ä ÈË:
ÐÞ¸ÄÄÚÈÝ:
************************************************************************/
#ifndef __APP_SXFLS_H__
#define __APP_SXFLS_H__
typedef struct TDB_APP_SXFLS
{
  char   ptrq[8+1];              /*Æ½Ì¨ÈÕÆÚ*/
              /*Æ½Ì¨ÈÕÆÚ*/
  char   ptls[16+1];              /*Æ½Ì¨Á÷Ë®ºÅ*/
              /*Æ½Ì¨Á÷Ë®ºÅ*/
  char   flbs[32+1];              /*·ÑÂÊ±êÊ¶*/
              /*·ÑÂÊ±êÊ¶*/
  char   yybs[3+1];              /*Ó¦ÓÃ±êÊ¶*/
              /**/
  char   ywbh[16+1];              /*ÒµÎñ±àºÅ*/
              /**/
  char   cpdm[16+1];              /*²úÆ·´úÂë*/
              /**/
  char   qdbs[3+1];              /*ÇþµÀ±êÊ¶*/
              /**/
  char   jgbs[16+1];              /*»ú¹¹±êÊ¶*/
              /**/
  char   khlx[1+1];              /*¿Í»§ÀàÐÍ*/
              /**/
  char   khbh[32+1];              /*¿Í»§±àºÅ*/
              /*¿Í»§ÔÚÒøÐÐ±àºÅ*/
  char   yhh[32+1];              /*ÓÃ»§ºÅ*/
              /*ÓÃ»§ÔÚµÚÈý·½¿Í»§ºÅ*/
  char   dwbh[16+1];              /*µ¥Î»±àºÅ*/
              /**/
  char   xtnbz[1+1];              /*ÏµÍ³ÄÚ±êÖ¾*/
              /*1 ÏµÍ³ÄÚ   ÏµÍ³Íâ*/
  char   jylsh[16+1];              /*½»Ò×Á÷Ë®ºÅ*/
              /*ÊÕÈ¡ÊÖÐø·ÑµÄÔ­½»Ò×Á÷Ë®ºÅ*/
  char   jylx[1+1];              /*½»Ò×ÀàÐÍ*/
              /*½»Ò×ÀàÐÍ 0 Áª» 1ÅúÁ¿*/
  char   jyrq[8+1];              /*½»Ò×ÈÕÆÚ*/
              /**/
  char   jygy[16+1];              /*½»Ò×¹ñÔ±*/
              /**/
  char   jyjg[16+1];              /*½»Ò×»ú¹¹*/
              /**/
  double  jyje;              /*½»Ò×½ð¶î*/
              /*½»Ò×½ð¶î*/
  int    jybs;              /*½»Ò×±ÊÊý*/
              /**/
  double  sxfje;              /*ÊÖÐø·Ñ½ð¶î*/
              /*·ÑÓÃ½ð¶î*/
  char   sfzt[1+1];              /*ÊÕ·Ñ×´Ì¬*/
              /*ÊÕÈ¡×´Ì¬ 0 Î´ÊÕÈ 1ÒÑÊÕÈ¡*/
  char   jfzh[32+1];              /*½è·½ÕÊ»§*/
              /*½è·½ÕÊ»§*/
  char   dfzh[32+1];              /*´û·½ÕÊ»§*/
              /*´û·½ÕÊ»§*/
  char   sfrq[8+1];              /*ÊÕ·ÑÈÕÆÚ*/
              /*ÊÕ·ÑÈÕÆÚ*/
  char   sfjygy[16+1];              /*ÊÕ·Ñ½»Ò×¹ñÔ±*/
              /**/
  char   sfjyjg[16+1];              /*ÊÕ·Ñ½»Ò×»ú¹¹*/
              /**/
  char   sfls[16+1];              /*ÊÕ·ÑÁ÷Ë®ºÅ*/
              /**/
  char   lszt[1+1];              /*Á÷Ë®×´Ì¬*/
              /*Á÷Ë®×´Ì¬ 0 Õý³ 1È¡Ïû*/
  char   extfld2[40+1];              /*À©Õ¹×Ö¶Î2*/
              /**/
  char   extfld1[20+1];              /*À©Õ¹×Ö¶Î1*/
              /**/
  char   sm[40+1];              /*ËµÃ÷*/
              /*ËµÃ÷*/
}APP_SXFLS;

#define SD_DATA  APP_SXFLS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_STRING,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  flbs, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  jgbs, 0),\
	DEFSDMEMBER(T_STRING,  khlx, 0),\
	DEFSDMEMBER(T_STRING,  khbh, 0),\
	DEFSDMEMBER(T_STRING,  yhh, 0),\
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  xtnbz, 0),\
	DEFSDMEMBER(T_STRING,  jylsh, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_STRING,  jyrq, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_LONG,  jybs, 0),\
	DEFSDMEMBER(T_DOUBLE,  sxfje, 2),\
	DEFSDMEMBER(T_STRING,  sfzt, 0),\
	DEFSDMEMBER(T_STRING,  jfzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_STRING,  sfrq, 0),\
	DEFSDMEMBER(T_STRING,  sfjygy, 0),\
	DEFSDMEMBER(T_STRING,  sfjyjg, 0),\
	DEFSDMEMBER(T_STRING,  sfls, 0),\
	DEFSDMEMBER(T_STRING,  lszt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  sm, 0)


	DECLAREFIELDS(SD_APP_SXFLS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_SXFLS_H__*/

