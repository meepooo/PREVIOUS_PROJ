/***********************************************************************
°æÈ¨ËùÓÐ:ºãÉúµç×Ó¹É·ÝÓÐÏÞ¹«Ë¾
ÏîÄ¿Ãû³Æ:×ÛºÏ¼¼ÊõÆ½Ì¨(Turandot)ÏîÄ¿
°æ    ±¾:V1.00
²Ù×÷ÏµÍ³:
Êý ¾Ý ¿â:INFORMIX
ÎÄ ¼þ Ãû:APP_DRLS.h
ÎÄ¼þÃèÊö:½á¹¹¶¨ÒåÊý¾Ý¿â¿ª·¢Ç¶CÍ·ÎÄ¼þ
Ïî Ä¿ ×é:
³Ì Ðò Ô±:[Ñî¶«]
·¢²¼Ê±¼ä:2009-4-29 19:40:39 [Gen]
ÐÞ    ¶©:
ÐÞ¸ÄÊ±¼ä:
************************************************************************
±í    Ãû:APP_DRLS (Æ½Ì¨¹«¹²Á÷Ë®±í)
Ëµ    Ã÷:
************************************************************************
ÐÞ¸Ä¼ÇÂ¼:
ÐÞ¸ÄÈÕÆÚ:
ÐÞ¸ÄÄÚÈÝ:
ÐÞ ¸Ä ÈË:
ÐÞ¸ÄÄÚÈÝ:
************************************************************************/
#ifndef __APP_DRLS_H__
#define __APP_DRLS_H__
typedef struct TDB_APP_DRLS
{
  char   ptrq[8+1];              /*Æ½Ì¨ÈÕÆÚ*/
              /*Æ½Ì¨ÈÕÆÚ yyyymmdd*/
  int    ptls;              /*Æ½Ì¨Á÷Ë®ºÅ*/
              /*Æ½Ì¨Á÷Ë®ºÅ*/
  char   ptsj[6+1];              /*Æ½Ì¨Ê±¼ä*/
              /*Æ½Ì¨Ê±¼ä hhmmss*/
  char   rzbz[1+1];              /*ÈëÕÊ±êÖ¾*/
              /*ÈëÕÊ±êÖ¾ 0ÈëÕÊ 1·ÇÈëÕÊ*/
  char   jylx[1+1];              /*½»Ò×ÀàÐÍ*/
              /*½»Ò×ÀàÐÍ 0Õý½»Ò× 1·´½»Ò 9ÆäËû*/
  int    yptls;              /*Ô­Æ½Ì¨Á÷Ë®ºÅ*/
              /*Ô­Æ½Ì¨Á÷Ë®ºÅ*/
  char   jyjg[16+1];              /*½»Ò×»ú¹¹*/
              /*½»Ò×»ú¹¹*/
  char   jygy[16+1];              /*½»Ò×¹ñÔ±*/
              /*½»Ò×¹ñÔ±*/
  char   qdbs[3+1];              /*ÇþµÀ±êÊ¶*/
              /*ÇþµÀ±êÊ¶ */
  char   zdsbbh[8+1];              /*ÖÕ¶ËÉè±¸±àºÅ*/
              /*ÖÕ¶ËÉè±¸±àºÅ*/
  char   yybs[8+1];              /*Ó¦ÓÃ±êÊ¶*/
              /*Ó¦ÓÃ±êÊ¶ */
  char   cpdm[16+1];              /*²úÆ·´úÂë*/
              /*²úÆ·´úÂë*/
  char   ywbh[16+1];              /*ÒµÎñ±àºÅ*/
              /*ÒµÎñ±àºÅ*/
  char   jydm[8+1];              /*½»Ò×´úÂë*/
              /*½»Ò×´úÂë*/
  char   yhbh[32+1];              /*ÓÃ»§±àºÅ*/
              /*ÓÃ»§±àºÅ ÈçÊÖ»úºÅ*/
  char   xzbz[1+1];              /*ÏÖ×ª±êÖ¾*/
              /*ÏÖ×ª±êÖ¾  0ÏÖ½ð 1×ªÕÊ*/
  char   jdbz[1+1];              /*½è´û±êÖ¾*/
              /*½è´û±êÖ¾  ¼ûÊý¾Ý×Öµäkey=k_jdbz*/
  char   zhlx[2+1];              /*ÕÊ»§ÀàÐÍ*/
              /*ÕÊ»§ÀàÐÍ  ¼ûÊý¾Ý×Öµäkey=k_zhlx*/
  char   yhzh[32+1];              /*ÒøÐÐÕÊºÅ*/
              /*ÒøÐÐÕÊºÅ*/
  char   dfzh[32+1];              /*¶Ô·½ÕÊºÅ*/
              /*¶Ô·½ÕÊºÅ*/
  double  jyje;              /*½»Ò×½ð¶î*/
              /*½»Ò×½ð¶î*/
  double  sxf;              /*ÊÖÐø·Ñ*/
              /*ÊÖÐø·Ñ*/
  int    pcbh;              /*Åú´Î±àºÅ*/
              /*Åú´Î±àºÅ*/
  char   jyxym[8+1];              /*½»Ò×ÏìÓ¦Âë*/
              /*½»Ò×ÏìÓ¦Âë*/
  char   jyxyxx[60+1];              /*½»Ò×ÏìÓ¦ÐÅÏ¢*/
              /*½»Ò×ÏìÓ¦ÐÅÏ¢*/
  char   jyzt[1+1];              /*½»Ò××´Ì¬*/
              /*½»Ò××´Ì¬¼ûÊý¾Ý×ÖµäKEY=K_JYZT*/
  char   extfld1[40+1];              /*À©Õ¹1*/
              /*À©Õ¹1*/
  char   extfld2[40+1];              /*À©Õ¹2*/
              /*À©Õ¹2*/
}APP_DRLS;

#define SD_DATA  APP_DRLS
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  ptsj, 0),\
	DEFSDMEMBER(T_STRING,  rzbz, 0),\
	DEFSDMEMBER(T_STRING,  jylx, 0),\
	DEFSDMEMBER(T_LONG,  yptls, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  zdsbbh, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  jydm, 0),\
	DEFSDMEMBER(T_STRING,  yhbh, 0),\
	DEFSDMEMBER(T_STRING,  xzbz, 0),\
	DEFSDMEMBER(T_STRING,  jdbz, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  yhzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_DOUBLE,  sxf, 2),\
	DEFSDMEMBER(T_LONG,  pcbh, 0),\
	DEFSDMEMBER(T_STRING,  jyxym, 0),\
	DEFSDMEMBER(T_STRING,  jyxyxx, 0),\
	DEFSDMEMBER(T_STRING,  jyzt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0)


	DECLAREFIELDS(SD_APP_DRLS)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_DRLS_H__*/
