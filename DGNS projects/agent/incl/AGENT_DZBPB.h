/***********************************************************************
°æÈ¨ËùÓÐ:ºãÉúµç×Ó¹É·ÝÓÐÏÞ¹«Ë¾
ÏîÄ¿Ãû³Æ:×ÛºÏ¼¼ÊõÆ½Ì¨(Turandot)ÏîÄ¿
°æ    ±¾:V1.00
²Ù×÷ÏµÍ³:
Êý ¾Ý ¿â:INFORMIX
ÎÄ ¼þ Ãû:AGENT_DZBPB.h
ÎÄ¼þÃèÊö:½á¹¹¶¨ÒåÊý¾Ý¿â¿ª·¢Ç¶CÍ·ÎÄ¼þ
Ïî Ä¿ ×é:
³Ì Ðò Ô±:[Ñî¶«]
·¢²¼Ê±¼ä:2009-4-29 19:40:39 [Gen]
ÐÞ    ¶©:
ÐÞ¸ÄÊ±¼ä:
************************************************************************
±í    Ãû:AGENT_DZBPB (¶ÔÕÊ²»Æ½±í)
Ëµ    Ã÷:
************************************************************************
ÐÞ¸Ä¼ÇÂ¼:
ÐÞ¸ÄÈÕÆÚ:
ÐÞ¸ÄÄÚÈÝ:
ÐÞ ¸Ä ÈË:
ÐÞ¸ÄÄÚÈÝ:
************************************************************************/
#ifndef __AGENT_DZBPB_H__
#define __AGENT_DZBPB_H__
typedef struct TDB_AGENT_DZBPB
{
  char   dzrq[8+1];              /*¶ÔÕËÈÕÆÚ*/
              /**/
  char   ptrq[8+1];              /*Æ½Ì¨ÈÕÆÚ*/
              /**/
  int    ptls;              /*Æ½Ì¨Á÷Ë®ºÅ*/
              /*Æ½Ì¨Á÷Ë®ºÅ*/
  char   zjrq[8+1];              /*Ö÷»úÈÕÆÚ*/
              /*Ö÷»úÈÕÆÚ*/
  char   zjls[32+1];              /*Ö÷»úÁ÷Ë®ºÅ*/
              /*Ö÷»úÁ÷Ë®ºÅ*/
  char   jyjg[16+1];              /*½»Ò×»ú¹¹*/
              /*½»Ò×»ú¹¹*/
  char   jygy[16+1];              /*½»Ò×¹ñÔ±*/
              /*½»Ò×¹ñÔ±*/
  char   jybz[3+1];              /*½»Ò×±ÒÖÖ*/
              /*½»Ò×±ÒÖÖ ¼ûÊý¾Ý×Öµä KE  K_JYBZ*/
  char   ywbh[16+1];              /*ÒµÎñ±àºÅ*/
              /*ÒµÎñ±àºÅ*/
  char   xzbz[1+1];              /*ÏÖ×ª±êÖ¾*/
              /*ÏÖ×ª±êÖ¾ 0ÏÖ½ð 1×ªÕÊ*/
  char   jdbz[1+1];              /*½è´û±êÊ¶*/
              /*½è´û±êÖ¾(d ½è C´û)*/
  double  jyje;              /*½»Ò×½ð¶î*/
              /*½»Ò×½ð¶î*/
  double  ptjyje;              /*Æ½Ì¨½»Ò×½ð¶î*/
              /*Æ½Ì¨½»Ò×½ð¶î*/
  char   jfzh[32+1];              /*½è·½ÕÊºÅ*/
              /*½è·½ÕÊºÅ*/
  char   jffzh[10+1];              /*½è·½·ÖÕÊºÅ*/
              /*½è·½·ÖÕÊºÅ*/
  char   dfzh[32+1];              /*´û·½ÕÊºÅ*/
              /*´û·½ÕÊºÅ*/
  char   dffzh[10+1];              /*´û·½·ÖÕÊºÅ*/
              /*´û·½·ÖÕÊºÅ*/
  char   ywlsh[16+1];              /*ÒµÎñÁ÷Ë®ºÅ*/
              /*ÒµÎñÁ÷Ë®ºÅ*/
  char   ywrq[8+1];              /*ÒµÎñÈÕÆÚ*/
              /*ÒµÎñÈÕÆÚ*/
  char   lslx[1+1];              /*Á÷Ë®ÀàÐÍ*/
              /*Á÷Ë®ÀàÐÍ  1 Ö÷»ú¶ÔÕ  µÚÈý·½¶ÔÕË*/
  char   dzbz[1+1];              /*¶ÔÕÊ±êÖ¾*/
              /*¶ÔÕÊ±êÖ¾  0 Î´¶ÔÕ  Æ  Æ½Ì¨¶  Æ½Ì¨ÉÙ*/
  char   tzlsh[22+1];              /*µ÷ÕËÁ÷Ë®ºÅ*/
              /*µ÷ÕËÁ÷Ë®ºÅ*/
  char   clzt[1+1];              /*´¦Àí×´Ì¬*/
              /*´¦Àí×´Ì¬ 0Î´´¦Àí 1ÒÑ´¦À 8´¦Àí¹ý³Ì³ö´ 9´¦ÀíÖÐ*/
  char   extfld1[20+1];              /*À©Õ¹×Ö¶Î1*/
              /*À©Õ¹×Ö¶Î1*/
  char   extfld2[20+1];              /*À©Õ¹×Ö¶Î2*/
              /*À©Õ¹×Ö¶Î2*/
  char   extfld3[20+1];              /*À©Õ¹×Ö¶Î3*/
              /*À©Õ¹×Ö¶Î3*/
}AGENT_DZBPB;

#define SD_DATA  AGENT_DZBPB
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  dzrq, 0),\
	DEFSDMEMBER(T_STRING,  ptrq, 0),\
	DEFSDMEMBER(T_LONG,  ptls, 0),\
	DEFSDMEMBER(T_STRING,  zjrq, 0),\
	DEFSDMEMBER(T_STRING,  zjls, 0),\
	DEFSDMEMBER(T_STRING,  jyjg, 0),\
	DEFSDMEMBER(T_STRING,  jygy, 0),\
	DEFSDMEMBER(T_STRING,  jybz, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  xzbz, 0),\
	DEFSDMEMBER(T_STRING,  jdbz, 0),\
	DEFSDMEMBER(T_DOUBLE,  jyje, 2),\
	DEFSDMEMBER(T_DOUBLE,  ptjyje, 2),\
	DEFSDMEMBER(T_STRING,  jfzh, 0),\
	DEFSDMEMBER(T_STRING,  jffzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_STRING,  dffzh, 0),\
	DEFSDMEMBER(T_STRING,  ywlsh, 0),\
	DEFSDMEMBER(T_STRING,  ywrq, 0),\
	DEFSDMEMBER(T_STRING,  lslx, 0),\
	DEFSDMEMBER(T_STRING,  dzbz, 0),\
	DEFSDMEMBER(T_STRING,  tzlsh, 0),\
	DEFSDMEMBER(T_STRING,  clzt, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  extfld3, 0)


	DECLAREFIELDS(SD_AGENT_DZBPB)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __AGENT_DZBPB_H__*/

