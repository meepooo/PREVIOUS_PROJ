/***********************************************************************
°æÈ¨ËùÓÐ:ºãÉúµç×Ó¹É·ÝÓÐÏÞ¹«Ë¾
ÏîÄ¿Ãû³Æ:×ÛºÏ¼¼ÊõÆ½Ì¨(Turandot)ÏîÄ¿
°æ    ±¾:V1.00
²Ù×÷ÏµÍ³:
Êý ¾Ý ¿â:INFORMIX
ÎÄ ¼þ Ãû:APP_QDXX.h
ÎÄ¼þÃèÊö:½á¹¹¶¨ÒåÊý¾Ý¿â¿ª·¢Ç¶CÍ·ÎÄ¼þ
Ïî Ä¿ ×é:
³Ì Ðò Ô±:[Ñî¶«]
·¢²¼Ê±¼ä:2009-4-29 19:40:39 [Gen]
ÐÞ    ¶©:
ÐÞ¸ÄÊ±¼ä:
************************************************************************
±í    Ãû:APP_QDXX (ÇþµÀÐÅÏ¢±í)
Ëµ    Ã÷:
************************************************************************
ÐÞ¸Ä¼ÇÂ¼:
ÐÞ¸ÄÈÕÆÚ:
ÐÞ¸ÄÄÚÈÝ:
ÐÞ ¸Ä ÈË:
ÐÞ¸ÄÄÚÈÝ:
************************************************************************/
#ifndef __APP_QDXX_H__
#define __APP_QDXX_H__
typedef struct TDB_APP_QDXX
{
  char   qdbs[3+1];              /*ÇþµÀ±êÊ¶*/
              /*ÇþµÀ±êÊ¶ ¼ûÊý¾Ý×Öµä KEY=K_QDB */
  char   qdmc[40+1];              /*ÇþµÀÃû³Æ*/
              /*ÇþµÀÃû³Æ*/
  char   qdsm[80+1];              /*ÇþµÀÖÐÎÄËµÃ÷*/
              /*ÇþµÀÖÐÎÄËµÃ÷*/
  char   sjkzbz[1+1];              /*Ê±¼ä¿ØÖÆ±êÖ¾*/
              /*Ê±¼ä¿ØÖÆ±êÖ¾ 0 ¿ØÖ 1²»¿ØÖÆ*/
  char   qssj[8+1];              /*ÆðÊ¼Ê±¼ä*/
              /*ÆðÊ¼Ê±¼ä */
  char   jssj[8+1];              /*½áÊøÊ±¼ä*/
              /*½áÊøÊ±¼ä*/
  char   czbz[1+1];              /*³åÕý±êÖ¾*/
              /*ÊÇ·ñÔÊÐí³åÕý  0ÔÊÐí 1²»ÔÊÐí*/
  char   zdczbz[1+1];              /*×Ô¶¯³åÕý±êÖ¾*/
              /*ÏµÍ³Òì³£ÊÇ·ñ×Ô¶¯³åÕý  0ÊÇ 1·ñ*/
  char   whjg[16+1];              /*Î¬»¤»ú¹¹*/
              /**/
  char   whgy[16+1];              /*Î¬»¤¹ñÔ±*/
              /**/
  char   whsj[14+1];              /*Î¬»¤Ê±¼ä*/
              /**/
  char   extfld1[40+1];              /*À©Õ¹×Ö¶Î1*/
              /*À©Õ¹×Ö¶Î1*/
  char   extfld2[40+1];              /*À©Õ¹×Ö¶Î2*/
              /*À©Õ¹×Ö¶Î2*/
  char   qdzt[1+1];              /*ÇþµÀ×´Ì¬*/
              /*ÇþµÀ×´Ì¬ 0¿ªÆô 1¹Ø±Õ*/
}APP_QDXX;

#define SD_DATA  APP_QDXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  qdbs, 0),\
	DEFSDMEMBER(T_STRING,  qdmc, 0),\
	DEFSDMEMBER(T_STRING,  qdsm, 0),\
	DEFSDMEMBER(T_STRING,  sjkzbz, 0),\
	DEFSDMEMBER(T_STRING,  qssj, 0),\
	DEFSDMEMBER(T_STRING,  jssj, 0),\
	DEFSDMEMBER(T_STRING,  czbz, 0),\
	DEFSDMEMBER(T_STRING,  zdczbz, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  qdzt, 0)


	DECLAREFIELDS(SD_APP_QDXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_QDXX_H__*/
