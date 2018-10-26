/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:db2
文 件 名:ICPS_WBC_KDPL_ZHMINX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[fuwd22392]
发布时间:2018-06-12 10:00:00 [Gen]
修    订:
修改时间:
************************************************************************
表    名:ICPS_WBC_KDPL_ZHMINX
说    明:按照合作方的账号，该账号下面的所有存款交易明细表
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __ICPS_WBC_KDPL_ZHMINX_H__
#define __ICPS_WBC_KDPL_ZHMINX_H__
typedef struct TDB_ICPS_WBC_KDPL_ZHMINX
{
	char		busi_date[8+1];            /*    业务日期               */
	int			file_order;                /*     文件序号              */ 
	char		zhanghao[40+1];            /*   负债账号                */ 
	double		mxixuhao;                  /*   明细序号                */ 
	char		jiaoyirq[8+1];             /*   交易日期                */ 
	char		khjymxlb[1+1];             /*   客户交易明细类别        */ 
	char		jyyyjigo[10+1];            /*   交易营业机构            */ 
	char		kaihjigo[10+1];            /*   账户开户机构            */ 
	char		zhhuzwmc[100+1];           /*   账户名称                */ 
	char		jiedaibz[1+1];             /*   借贷标志              */   
	char		jiaoybiz[2+1];             /*   交易币种              */   
	char		chaohubz[1+1];             /*   账户钞汇标志          */   
	double		jiaoyije;                  /*   交易金额              */   
	double		zhanghye;                  /*   账户余额              */   
	char		kahaoooo[35+1];            /*   卡号                  */   
	char		kehuzhao[35+1];            /*   客户账号              */   
	char		zhhaoxuh[8+1];             /*   子账户序号            */   
	char		pngzzlei[4+1];             /*   凭证种类              */   
	char		pngzxhao[22+1];            /*   凭证号                */   
	char		zhaiyodm[10+1];            /*   摘要代码              */   
	char		zhaiyoms[80+1];            /*   摘要描述              */   
	char		duifjgdm[20+1];            /*   对方金融机构          */   
	char		duifjgmc[60+1];            /*   对方金融机构名称      */   
	char		duifkhzh[35+1];            /*   对方客户账号          */   
	char		duifminc[100+1];           /*   对方户名              */   
	char		duifbezh[200+1];           /*   对方备注              */   
	char		beizhuuu[200+1];           /*   备注                  */   
	char		qixiriqi[8+1];             /*   起息日期              */   
	char		qdaoleix[3+1];             /*   交易渠道              */   
	char		waibclma[20+1];            /*   对账代码              */   
	char		nbjoyima[10+1];            /*   内部交易码            */   
	char		xianzzbz[1+1];             /*   现转标志              */   
	char		guiylius[32+1];            /*   柜员流水(即交易流水)  */   
	char		caozguiy[8+1];             /*   操作柜员              */   
	char		zhujriqi[8+1];             /*   主机日期              */   
	char		zjyilush[32+1];            /*   主交易流水            */   
	char		yewulush[32+1];            /*   业务流水              */   
	char		jiaoyisj[16+1];            /*   交易时间              */   
	char		bchongbz[1+1];             /*   交易明细状态          */   
	char		cuozriqi[8+1];             /*   原错账日期            */   
	char		cuozlius[32+1];            /*   原错账交易流水        */   
	char		yszjylsh[32+1];            /*   原始主交易流水        */   
	char		ysyewush[32+1];            /*   原始业务流水          */   
	char		czczflei[1+1];             /*   冲正冲账分类          */   
	char		mozhanbz[1+1];             /*   抹账标志              */   
	char		tokennnn[35+1];            /*   token                 */   
	char		dsftoken[35+1];            /*   对手方token           */   
	double		lilvlilv;                  /*   利率                  */   
	char		jioyshij[10+1];            /*   交易事件              */   
	char		huidxhao[80+1];            /*   回单序号              */   
	char		farendma[20+1];            /*   法人代码              */   
	char		weihguiy[8+1];             /*   维护柜员              */   
	char		weihjigo[10+1];            /*   维护机构              */   
	char		weihriqi[8+1];             /*   维护日期              */   
	double          shijchuo;                  /*   时间戳                */   
	char		is_check_flag[1+1];                  /*'参与对账标识     */   
	char		extend_param1[100+1];                /*'扩展1            */   
	char		extend_param2[250+1];                /*'扩展2            */   
	char		extend_param3[40+1];                 /*'扩展3            */   
}ICPS_WBC_KDPL_ZHMINX;

#define SD_DATA  ICPS_WBC_KDPL_ZHMINX
#define SD_MEMBERS \ 
  APP_DEFSDMEMBER(T_STRING,  busi_date      ,0),\
  APP_DEFSDMEMBER(T_LONG,    file_order     ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhanghao       ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  mxixuhao       ,2),\
  APP_DEFSDMEMBER(T_STRING,  jiaoyirq       ,0),\
  APP_DEFSDMEMBER(T_STRING,  khjymxlb       ,0),\
  APP_DEFSDMEMBER(T_STRING,  jyyyjigo       ,0),\
  APP_DEFSDMEMBER(T_STRING,  kaihjigo       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhhuzwmc       ,0),\
  APP_DEFSDMEMBER(T_STRING,  jiedaibz       ,0),\
  APP_DEFSDMEMBER(T_STRING,  jiaoybiz       ,0),\
  APP_DEFSDMEMBER(T_STRING,  chaohubz       ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  jiaoyije       ,2),\
  APP_DEFSDMEMBER(T_DOUBLE,  zhanghye       ,2),\
  APP_DEFSDMEMBER(T_STRING,  kahaoooo       ,0),\
  APP_DEFSDMEMBER(T_STRING,  kehuzhao       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhhaoxuh       ,0),\
  APP_DEFSDMEMBER(T_STRING,  pngzzlei       ,0),\
  APP_DEFSDMEMBER(T_STRING,  pngzxhao       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhaiyodm       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhaiyoms       ,0),\
  APP_DEFSDMEMBER(T_STRING,  duifjgdm       ,0),\
  APP_DEFSDMEMBER(T_STRING,  duifjgmc       ,0),\
  APP_DEFSDMEMBER(T_STRING,  duifkhzh       ,0),\
  APP_DEFSDMEMBER(T_STRING,  duifminc       ,0),\
  APP_DEFSDMEMBER(T_STRING,  duifbezh       ,0),\
  APP_DEFSDMEMBER(T_STRING,  beizhuuu       ,0),\
  APP_DEFSDMEMBER(T_STRING,  qixiriqi       ,0),\
  APP_DEFSDMEMBER(T_STRING,  qdaoleix       ,0),\
  APP_DEFSDMEMBER(T_STRING,  waibclma       ,0),\
  APP_DEFSDMEMBER(T_STRING,  nbjoyima       ,0),\
  APP_DEFSDMEMBER(T_STRING,  xianzzbz       ,0),\
  APP_DEFSDMEMBER(T_STRING,  guiylius       ,0),\
  APP_DEFSDMEMBER(T_STRING,  caozguiy       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zhujriqi       ,0),\
  APP_DEFSDMEMBER(T_STRING,  zjyilush       ,0),\
  APP_DEFSDMEMBER(T_STRING,  yewulush       ,0),\
  APP_DEFSDMEMBER(T_STRING,  jiaoyisj       ,0),\
  APP_DEFSDMEMBER(T_STRING,  bchongbz       ,0),\
  APP_DEFSDMEMBER(T_STRING,  cuozriqi       ,0),\
  APP_DEFSDMEMBER(T_STRING,  cuozlius       ,0),\
  APP_DEFSDMEMBER(T_STRING,  yszjylsh       ,0),\
  APP_DEFSDMEMBER(T_STRING,  ysyewush       ,0),\
  APP_DEFSDMEMBER(T_STRING,  czczflei       ,0),\
  APP_DEFSDMEMBER(T_STRING,  mozhanbz       ,0),\
  APP_DEFSDMEMBER(T_STRING,  tokennnn       ,0),\
  APP_DEFSDMEMBER(T_STRING,  dsftoken       ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  lilvlilv       ,6),\
  APP_DEFSDMEMBER(T_STRING,  jioyshij       ,0),\
  APP_DEFSDMEMBER(T_STRING,  huidxhao       ,0),\
  APP_DEFSDMEMBER(T_STRING,  farendma       ,0),\
  APP_DEFSDMEMBER(T_STRING,  weihguiy       ,0),\
  APP_DEFSDMEMBER(T_STRING,  weihjigo       ,0),\
  APP_DEFSDMEMBER(T_STRING,  weihriqi       ,0),\
  APP_DEFSDMEMBER(T_DOUBLE,  shijchuo       ,2),\
  APP_DEFSDMEMBER(T_STRING,  is_check_flag  ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param1  ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param2  ,0),\
  APP_DEFSDMEMBER(T_STRING,  extend_param3  ,0)
  APP_DECLAREFIELDS(SD_ICPS_WBC_KDPL_ZHMINX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __ICPS_WBC_KDPL_ZHMINX_H__*/
