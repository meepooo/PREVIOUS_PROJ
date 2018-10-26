#ifndef __APP_DW_CPXY_H__
#define __APP_DW_CPXY_H__
typedef struct TDB_APP_DW_CPXY
{
  char   dwbh[16+1];              /*µ¥Î»±àºÅ*/
              /*µ¥Î»±àºÅ*/
  char   cpdm[16+1];              /*²úÆ·´úÂë*/
              /*²úÆ·´úÂë*/
  char   ywbh[16+1];              /*ÒµÎñ±àºÅ*/
              /*ÒµÎñ±àºÅ ´úÊÕ¸¶ÒµÎñÌî´úÀíÒµÎñ±àºÅ£¬Òø±£Í¨ÌîÏÕÖÖ*/
  char   ywmc[40+1];              /*ÒµÎñÃû³Æ*/
              /**/
  char   xybh[20+1];              /*Ð­Òé±àºÅ*/
              /*ºÏÍ¬±àºÅ*/
  char   yhdm[16+1];              /*ÒøÐÐ´úÂë*/
              /*ÒøÐÐ´úÂë*/
  char   ljbs[8+1];              /*Áª»ú±êÊ¶*/
              /**/
  char   zhlx[2+1];              /*ÕË»§ÀàÐÍ*/
              /*ÕË»§ÀàÐÍ ¼ûÊý¾Ý×Öµä KEY=K_ZHLX*/
  char   sfbz[1+1];              /*ÊÕ¸¶±êÊ¶*/
              /*1 ÊÕ  ¸  ÆäË */
  char   dszh[32+1];              /*´úÊÕÕË»§*/
              /*´úÊÕÕË»§*/
  char   dszhmc[80+1];              /*´úÊÕÕË»§»§Ãû*/
              /*´úÊÕÕË»§»§Ãû*/
  char   dfzh[32+1];              /*´ú¸¶ÕË»§*/
              /*´ú¸¶ÕË»§*/
  char   dfzhmc[80+1];              /*´ú¸¶ÕË»§»§Ãû*/
              /*´ú¸¶ÕË»§»§Ãû*/
  char   khjl[20+1];              /*¿Í»§¾­Àí*/
              /*¿Í»§¾­Àí*/
  char   lxr[20+1];              /*ÒµÎñÁªÏµÈË*/
              /**/
  char   email[32+1];              /*ÒµÎñÁªÏµEMAIL*/
              /**/
  char   lxdh[16+1];              /*ÒµÎñÁªÏµµç»°*/
              /**/
  char   hyksrq[8+1];              /*ºÏÔ¼¿ªÊ¼ÈÕÆÚ*/
              /*ºÏÔ¼¿ªÊ¼ÈÕÆÚ*/
  char   hyjsrq[8+1];              /*ºÏÔ¼½áÊøÈÕÆÚ*/
              /*ºÏÔ¼½áÊøÈÕÆÚ*/
  char   bljg[16+1];              /*°ìÀí»ú¹¹*/
              /*°ìÀí»ú¹¹*/
  char   blgy[16+1];              /*°ìÀí¹ñÔ±*/
              /*°ìÀí¹ñÔ±*/
  char   blrq[16+1];              /*°ìÀíÈÕÆÚ*/
              /*°ìÀíÈÕÆÚ*/
  double  zhzded;              /*ÕË»§×îµÍ¶î¶È*/
              /*ÕË»§×îµÍ¶î¶È*/
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
  char   qyzt[1+1];              /*Ç©Ô¼×´Ì¬*/
              /*Ç©Ô¼×´Ì¬ 0Õý³£ 1³·Ïû*/
  char   fwrx[32+1];        /*·þÎñÈÈÏß*/
              /*·þÎñÈÈÏß*/
  char   jfbhxsmc[100+1];        /*½É·Ñ±àºÅÏÔÊ¾Ãû³Æ*/
              /*½É·Ñ±àºÅÏÔÊ¾Ãû³Æ*/
  char   khh[32+1];        /*¿Í»§ºÅ*/
              /*¿Í»§ºÅ*/
  char   nbhzhmc[100+1];        /*ÄÚ²¿»§ÕËºÅÃû³Æ*/
              /*ÄÚ²¿»§ÕËºÅÃû³Æ*/
  char   nbhzh[32+1];        /*ÄÚ²¿»§ÕËºÅ*/
              /*ÄÚ²¿»§ÕËºÅ*/
  char   sxfnbhzhmc[100+1];        /*ÊÖÐø·ÑÄÚ²¿»§ÕËºÅÃû³Æ*/
              /*ÊÖÐø·ÑÄÚ²¿»§ÕËºÅÃû³Æ*/
  char   sxfnbhzh[32+1];        /*ÊÖÐø·ÑÄÚ²¿»§ÕËºÅ*/
              /*ÊÖÐø·ÑÄÚ²¿»§ÕËºÅ*/
  char   scfs[2+1];        /*ÉÏ´«·½Ê½*/
              /*01-½É·ÑÆ½Ì¨ 02-×ÔÓÐÏµÍ³ 03-ÏßÏÂ´úÀí*/
  char   shzt[1+1];        /*ÉóºË×´Ì¬*/
              /*9-Î´ÉóºË 1-ÉóºËÍ¨¹ý 2-ÉóºË¾Ü¾ø*/
  char   shsj[14+1];        /*ÉóºËÊ±¼ä*/
              /*ÉóºËÊ±¼ä*/
  char   shgy[16+1];        /*ÉóºË¹ñÔ±*/
              /*ÉóºË¹ñÔ±*/
  char   shjg[32+1];        /*ÉóºË»ú¹¹*/
  char   dwbh1[16+1];/*µ¥Î»±àºÅ*/
  /**/
  char   dwmc[80+1];/*µ¥Î»Ãû³Æ*/
  /*µ¥Î»Ãû³Æ*/
  char   dwzjlx[2+1];/*µ¥Î»Ö¤¼þÀàÐÍ*/
  /*µ¥Î»Ö¤¼þÀàÐÍ ¼ûÊý¾Ý×Öµä KEY=K_DWZJLX*/
  char   dwzjhm[32+1];/*µ¥Î»Ö¤¼þºÅÂë*/
              /*µ¥Î»Ö¤¼þºÅÂë*/
  char   dwlxr[16+1];              /*µ¥Î»ÁªÏµÈËÃû³Æ*/
              /*µ¥Î»ÁªÏµÈËÃû³Æ*/
  char   dwlxrdh[16+1];              /*µ¥Î»ÁªÏµÈËµç»°*/
              /*µ¥Î»ÁªÏµÈËµç»°*/
  char   dwdz[60+1];              /*µ¥Î»ÁªÏµµØÖ·*/
              /*µ¥Î»ÁªÏµµØÖ·*/
  char   dwemail[32+1];              /*µ¥Î»ÁªÏµemail*/
              /*µ¥Î»ÁªÏµemail*/
  char   whjg1[16+1];              /*Î¬»¤»ú¹¹*/
              /**/
  char   whgy1[16+1];              /*Î¬»¤¹ñÔ±*/
              /**/
  char   whsj1[14+1];              /*Î¬»¤Ê±¼ä*/
              /**/
  char   extfld11[40+1];              /*À©Õ¹²ÎÊý1*/
              /*À©Õ¹²ÎÊý1*/
  char   extfld12[40+1];              /*À©Õ¹²ÎÊý2*/
              /*À©Õ¹²ÎÊý2*/
  char   zt1[1+1];              /*×´Ì¬*/

}APP_DW_CPXY;

#define SD_DATA  APP_DW_CPXY
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  cpdm, 0),\
	DEFSDMEMBER(T_STRING,  ywbh, 0),\
	DEFSDMEMBER(T_STRING,  ywmc, 0),\
	DEFSDMEMBER(T_STRING,  xybh, 0),\
	DEFSDMEMBER(T_STRING,  yhdm, 0),\
	DEFSDMEMBER(T_STRING,  ljbs, 0),\
	DEFSDMEMBER(T_STRING,  zhlx, 0),\
	DEFSDMEMBER(T_STRING,  sfbz, 0),\
	DEFSDMEMBER(T_STRING,  dszh, 0),\
	DEFSDMEMBER(T_STRING,  dszhmc, 0),\
	DEFSDMEMBER(T_STRING,  dfzh, 0),\
	DEFSDMEMBER(T_STRING,  dfzhmc, 0),\
	DEFSDMEMBER(T_STRING,  khjl, 0),\
	DEFSDMEMBER(T_STRING,  lxr, 0),\
	DEFSDMEMBER(T_STRING,  email, 0),\
	DEFSDMEMBER(T_STRING,  lxdh, 0),\
	DEFSDMEMBER(T_STRING,  hyksrq, 0),\
	DEFSDMEMBER(T_STRING,  hyjsrq, 0),\
	DEFSDMEMBER(T_STRING,  bljg, 0),\
	DEFSDMEMBER(T_STRING,  blgy, 0),\
	DEFSDMEMBER(T_STRING,  blrq, 0),\
	DEFSDMEMBER(T_DOUBLE,  zhzded, 2),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  qyzt, 0),\
	DEFSDMEMBER(T_STRING,  fwrx, 0),\
	DEFSDMEMBER(T_STRING,  jfbhxsmc, 0),\
	DEFSDMEMBER(T_STRING,  khh, 0),\
	DEFSDMEMBER(T_STRING,  nbhzhmc, 0),\
	DEFSDMEMBER(T_STRING,  nbhzh, 0),\
	DEFSDMEMBER(T_STRING,  sxfnbhzhmc, 0),\
	DEFSDMEMBER(T_STRING,  sxfnbhzh, 0),\
	DEFSDMEMBER(T_STRING,  scfs, 0),\
	DEFSDMEMBER(T_STRING,  shzt, 0),\
	DEFSDMEMBER(T_STRING,  shsj, 0),\
	DEFSDMEMBER(T_STRING,  shgy, 0),\
	DEFSDMEMBER(T_STRING,  shjg, 0),\
        DEFSDMEMBER(T_STRING,  dwbh1, 0),\
        DEFSDMEMBER(T_STRING,  dwmc, 0),\
        DEFSDMEMBER(T_STRING,  dwzjlx, 0),\
        DEFSDMEMBER(T_STRING,  dwzjhm, 0),\
        DEFSDMEMBER(T_STRING,  dwlxr, 0),\
        DEFSDMEMBER(T_STRING,  dwlxrdh, 0),\
        DEFSDMEMBER(T_STRING,  dwdz, 0),\
        DEFSDMEMBER(T_STRING,  dwemail, 0),\
        DEFSDMEMBER(T_STRING,  whjg1, 0),\
        DEFSDMEMBER(T_STRING,  whgy1, 0),\
        DEFSDMEMBER(T_STRING,  whsj1, 0),\
        DEFSDMEMBER(T_STRING,  extfld11, 0),\
        DEFSDMEMBER(T_STRING,  extfld12, 0),\
        DEFSDMEMBER(T_STRING,  zt1, 0)


	DECLAREFIELDS(SD_APP_DW_CPXY)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_DW_CPXY_H__*/
