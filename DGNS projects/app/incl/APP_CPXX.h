/***********************************************************************
°æÈ¨ËùÓÐ:ºãÉúµç×Ó¹É·ÝÓÐÏÞ¹«Ë¾
ÏîÄ¿Ãû³Æ:×ÛºÏ¼¼ÊõÆ½Ì¨(Turandot)ÏîÄ¿
°æ    ±¾:V1.00
²Ù×÷ÏµÍ³:
Êý ¾Ý ¿â:INFORMIX
ÎÄ ¼þ Ãû:APP_CPXX.h
ÎÄ¼þÃèÊö:½á¹¹¶¨ÒåÊý¾Ý¿â¿ª·¢Ç¶CÍ·ÎÄ¼þ
Ïî Ä¿ ×é:
³Ì Ðò Ô±:[Ñî¶«]
·¢²¼Ê±¼ä:2009-4-29 19:40:39 [Gen]
ÐÞ    ¶©:
ÐÞ¸ÄÊ±¼ä:
************************************************************************
±í    Ãû:APP_CPXX (²úÆ·»ù´¡ÐÅÏ¢±í)
Ëµ    Ã÷:
************************************************************************
ÐÞ¸Ä¼ÇÂ¼:
ÐÞ¸ÄÈÕÆÚ:
ÐÞ¸ÄÄÚÈÝ:
ÐÞ ¸Ä ÈË:
ÐÞ¸ÄÄÚÈÝ:
************************************************************************/
#ifndef __APP_CPXX_H__
#define __APP_CPXX_H__
typedef struct TDB_APP_CPXX
{
  char   cpdm[16+1];              /*²úÆ·´úÂë*/
              /*²úÆ·´úÂë*/
  char   cpmc[40+1];              /*²úÆ·Ãû³Æ*/
              /*²úÆ·Ãû³Æ*/
  char   yybs[8+1];              /*Ó¦ÓÃ±êÊ¶*/
              /*Ó¦ÓÃ±êÊ¶*/
  char   zbjg[16+1];              /*Ö÷°ì»ú¹¹*/
              /*Ö÷°ì»ú¹¹*/
  char   zbgy[16+1];              /*Ö÷°ì¹ñÔ±*/
              /*Ö÷°ì¹ñÔ±*/
  char   khjl[20+1];              /*¿Í»§¾­Àí*/
              /*¿Í»§¾­Àí*/
  char   ywrqlx[1+1];              /*ÒµÎñÈÕÆÚÀàÐÍ*/
              /*ÒµÎñÈÕÆÚÀàÐÍ 1¹«¹² 2Ë½Ó Ä¬È 1*/
  char   qdkzbz[1+1];              /*ÇþµÀ¿ØÖÆ±êÖ¾*/
              /*ÇþµÀ¿ØÖÆ±êÖ¾ 0¿ØÖÆ 1²»¿ØÖ Ä¬ÈÏ1*/
  char   jgkzcs[1+1];              /*»ú¹¹¿ØÖÆ²ÎÊý*/
              /*»ú¹¹¿ØÖÆ²ÎÊý ¼ûÊý¾Ý×Öµä KEY=K_JGKZC Ä¬ÈÏ ²»¿ØÖÆ*/
  char   sxfbz[1+1];              /*ÊÖÐø·ÑÊÕÈ¡±êÖ¾*/
              /*ÊÖÐø·ÑÊÕÈ¡±êÖ¾ 0ÊÕÈ¡ 1ÃâÊ Ä¬ÈÏ1*/
  char   sfqybz[1+1];              /*Èý·½Ç©Ô¼±êÖ¾*/
              /*0²»ÐèÒªÇ©Ô¼£¬1 µÚÈý·½Ç©Ô¼£¬2Ö÷»úÇ©Ô¼£¬3 Í¬Ê±Ç©Ô  Ä¬ÈÏ */
  char   qyms[1+1];              /*Ç©Ô¼Ä£Ê½*/
              /*1  ²úÆ·´úÂë£«ÒøÐÐÕÊºÅ  ²úÆ·´úÂë£«ÓÃ»§º  ²úÆ·´úÂë£«ÒøÐÐÕÊºÅ£«ÓÃ»§º  Ä¬ÈÏ2*/
  char   xyxljz[16+1];              /*Ð­ÒéÐòÁÐ¼üÖµ*/
              /*Ð­ÒéÐòÁÐ¼üÖµ Ä¬ÈÏ K_KHCPQY*/
  char   kkfs[1+1];              /*¿Û¿î·½Ê½*/
              /*1È«¶î¿Û¿î£¬2 ²¿·Ö¿Û¿î Ä¬ÈÏ1*/
  char   jzsx[1+1];              /*¼ÇÕËË³Ðò*/
              /*0ÏÈÖ÷»úºóµÚÈý·½£¬1ÏÈµÚÈý·½ºóÖ÷»ú Ä¬ÈÏ0*/
  char   dzms[1+1];              /*¶ÔÕÊÄ£Ê½*/
              /*¶ÔÕÊÄ£Ê½ 1ÒøÐÐÎªÖ÷ 2µÚÈý·½ÎªÖ÷*/
  char   zjyyh[8+1];              /*Ö÷»úÓ¦ÓÃºÅ*/
              /**/
  char   zjzyyh[8+1];              /*Ö÷»ú×ÓÓ¦ÓÃºÅ*/
              /**/
  int    lsblts;              /*Á÷Ë®±£ÁôÌìÊý*/
              /*Á÷Ë®±£ÁôÌìÊý*/
  int    pdblts;              /*Æ¾µ¥±£ÁôÌìÊý*/
              /*Æ¾µ¥±£ÁôÌìÊý*/
  char   jyfs[1+1];              /*½»Ò×·½Ê½*/
              /*½»Ò×·½Ê½ ¼ûÊý¾Ý×Öµä KEY=K_JYFS*/
  char   rzms[1+1];              /*ÈÕÖ¾Ä£Ê½*/
              /*0µ÷ÊÔ  1 Éú² Ä¬È 1*/
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
  char   cpzt[1+1];              /*²úÆ·×´Ì¬*/
              /*²úÆ·×´Ì¬ ¼ûÊý¾Ý×Öµä KEY=K_CPZT*/
}APP_CPXX;

#define SD_DATA  APP_CPXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  cpmc, 0),\
	DEFSDMEMBER(T_STRING,  yybs, 0),\
	DEFSDMEMBER(T_STRING,  zbjg, 0),\
	DEFSDMEMBER(T_STRING,  zbgy, 0),\
	DEFSDMEMBER(T_STRING,  khjl, 0),\
	DEFSDMEMBER(T_STRING,  ywrqlx, 0),\
	DEFSDMEMBER(T_STRING,  qdkzbz, 0),\
	DEFSDMEMBER(T_STRING,  jgkzcs, 0),\
	DEFSDMEMBER(T_STRING,  sxfbz, 0),\
	DEFSDMEMBER(T_STRING,  sfqybz, 0),\
	DEFSDMEMBER(T_STRING,  qyms, 0),\
	DEFSDMEMBER(T_STRING,  xyxljz, 0),\
	DEFSDMEMBER(T_STRING,  kkfs, 0),\
	DEFSDMEMBER(T_STRING,  jzsx, 0),\
	DEFSDMEMBER(T_STRING,  dzms, 0),\
	DEFSDMEMBER(T_STRING,  zjyyh, 0),\
	DEFSDMEMBER(T_STRING,  zjzyyh, 0),\
	DEFSDMEMBER(T_LONG,  lsblts, 0),\
	DEFSDMEMBER(T_LONG,  pdblts, 0),\
	DEFSDMEMBER(T_STRING,  jyfs, 0),\
	DEFSDMEMBER(T_STRING,  rzms, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  cpzt, 0)


	DECLAREFIELDS(SD_APP_CPXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_CPXX_H__*/
