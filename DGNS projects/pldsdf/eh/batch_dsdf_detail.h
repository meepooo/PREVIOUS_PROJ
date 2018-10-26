/***********************************************************************
版权所有:批量代收代付
项目名称:批量代收代付
版    本:V3.0
操作系统:AIX SCO LINUX SunOS HP-UX
数 据 库:DB2
文 件 名:batch_dsdf_detail.h
文件描述:batch_dsdf_detail
项 目 组:批量代收代付
程 序 员:
发布时间:2017-10-24
修    订:
修改时间:
************************************************************************
表    名:batch_dsdf_detail (批量代收付业务表)
说    明:批量代收付业务表
用于登记批量代收代付文件导入明细信息
************************************************************************
修改记录:
修改日期:
修改内容:
修改内容:
修 改 人:
************************************************************************/
#ifndef __BATCH_DSDF_DETAIL_EH__
#define __BATCH_DSDF_DETAIL_EH__

typedef struct TDB_BATCH_DSDF_DETAIL
{
	char pkrq[8+1];
	char ptpch[8+1];
	int lsxh;
	int wjxh;
	char jdbz[1+1];
	char zydm[16+1];
	char ywbh[16+1];
	char dwbh[16+1];
	char jlbs[32+1];
	char yhh1[32+1];
	char yhxm[200+1];
	char zjhm[32+1];
	char yhzh[32+1];
	char fkrzh[32+1];
	char fkrxm[200+1];
	char fkhhh[12+1];
	char fkhhm[200+1];
	char skrzh[32+1];
	char skrxm[200+1];
	char skhhh[12+1];
	char skhhm[200+1];
	double jyje;
	double sjje;
	char ptlsh[32+1];
	char ywlsh[32+1];
	char jylsh[32+1];
	char ptdm[32+1];
	char bfkkbz[1+1];
	char bz[8+1];
	char gylsh[32+1];
	char zwrq[8+1];
	char czlsh[32+1];
	char czrq[8+1];
	char djxtrq[8+1];
	char djxtsj[6+1];
	char zhgxrq[8+1];
	char zhgxsj[6+1];
	char byzd1[40+1];
	char byzd2[40+1];
	double byzd3;
	int byzd4;
	char jlzt[8+1];
	char zjyxq[8+1];
	char zjlx[3+1];
	char xb[1+1];
	char csrq[8+1];
	char fzjg[60+1];
	char dz[120+1];
	char yzbm[7+1];
	char dhhm[15+1];
	char zy[40+1];
	char gzdw[120+1];
	char ssjmsf[8+1];
	char kxrq[8+1];
	double ywje;
	double sjywje;
	double fyje1;
	double sjfyje1;
	double fyje2;
	double sjfyje2;
	double fyje3;
	double sjfyje3;
	double fyje4;
	double sjfyje4;
	double fyje5;
	double sjfyje5;
	double sxfje;
	double sjsxfje;
	char shzt[1+1];
	char clzt[1+1];
	char cgbz[1+1];
	char xym[8+1];
	char xyxx[60+1];
	char zjrq[8+1];
	char zjsj[6+1];
	char zjlsh[32+1];
	char zjxym[8+1];
	char zjxyxx[60+1];
	char dsfrq[8+1];
	char dsfsj[6+1];
	char dsflsh[32+1];
	char dsfxym[8+1];
	char dsfxyxx[60+1];
	char wbrq[8+1];
	char wbpch[32+1];
	int wbxh;
	char zjpch[32+1];
	char kzzd1[100+1];
	char kzzd2[100+1];
	char kzzd3[100+1];
	char kzzd4[100+1];
	char kzzd5[200+1];
	char kzzd6[256+1];
	char kzzd7[512+1];
	char kzzd8[1024+1];
	char kzzd9[1024+1];
	double kzzd10;
	char remark1[1024+1];
	char remark2[1024+1];
}SDB_BATCH_DSDF_DETAIL;

#define SD_DATA SDB_BATCH_DSDF_DETAIL
#define	SD_MEMBERS\
	DEFSDMEMBER(T_STRING, pkrq, 0),\
	DEFSDMEMBER(T_STRING, ptpch, 0),\
	DEFSDMEMBER(T_LONG, lsxh, 0),\
	DEFSDMEMBER(T_LONG, wjxh, 0),\
	DEFSDMEMBER(T_STRING, jdbz, 0),\
	DEFSDMEMBER(T_STRING, zydm, 0),\
	DEFSDMEMBER(T_STRING, ywbh, 0),\
	DEFSDMEMBER(T_STRING, dwbh, 0),\
	DEFSDMEMBER(T_STRING, jlbs, 0),\
	DEFSDMEMBER(T_STRING, yhh1, 0),\
	DEFSDMEMBER(T_STRING, yhxm, 0),\
	DEFSDMEMBER(T_STRING, zjhm, 0),\
	DEFSDMEMBER(T_STRING, yhzh, 0),\
	DEFSDMEMBER(T_STRING, fkrzh, 0),\
	DEFSDMEMBER(T_STRING, fkrxm, 0),\
	DEFSDMEMBER(T_STRING, fkhhh, 0),\
	DEFSDMEMBER(T_STRING, fkhhm, 0),\
	DEFSDMEMBER(T_STRING, skrzh, 0),\
	DEFSDMEMBER(T_STRING, skrxm, 0),\
	DEFSDMEMBER(T_STRING, skhhh, 0),\
	DEFSDMEMBER(T_STRING, skhhm, 0),\
	DEFSDMEMBER(T_DOUBLE, jyje, 2),\
	DEFSDMEMBER(T_DOUBLE, sjje, 2),\
	DEFSDMEMBER(T_STRING, ptlsh, 0),\
	DEFSDMEMBER(T_STRING, ywlsh, 0),\
	DEFSDMEMBER(T_STRING, jylsh, 0),\
	DEFSDMEMBER(T_STRING, ptdm, 0),\
	DEFSDMEMBER(T_STRING, bfkkbz, 0),\
	DEFSDMEMBER(T_STRING, bz, 0),\
	DEFSDMEMBER(T_STRING, gylsh, 0),\
	DEFSDMEMBER(T_STRING, zwrq, 0),\
	DEFSDMEMBER(T_STRING, czlsh, 0),\
	DEFSDMEMBER(T_STRING, czrq, 0),\
	DEFSDMEMBER(T_STRING, djxtrq, 0),\
	DEFSDMEMBER(T_STRING, djxtsj, 0),\
	DEFSDMEMBER(T_STRING, zhgxrq, 0),\
	DEFSDMEMBER(T_STRING, zhgxsj, 0),\
	DEFSDMEMBER(T_STRING, byzd1, 0),\
	DEFSDMEMBER(T_STRING, byzd2, 0),\
	DEFSDMEMBER(T_DOUBLE, byzd3, 2),\
	DEFSDMEMBER(T_LONG, byzd4, 0),\
	DEFSDMEMBER(T_STRING, jlzt, 0),\
	DEFSDMEMBER(T_STRING, zjyxq, 0),\
	DEFSDMEMBER(T_STRING, zjlx, 0),\
	DEFSDMEMBER(T_STRING, xb, 0),\
	DEFSDMEMBER(T_STRING, csrq, 0),\
	DEFSDMEMBER(T_STRING, fzjg, 0),\
	DEFSDMEMBER(T_STRING, dz, 0),\
	DEFSDMEMBER(T_STRING, yzbm, 0),\
	DEFSDMEMBER(T_STRING, dhhm, 0),\
	DEFSDMEMBER(T_STRING, zy, 0),\
	DEFSDMEMBER(T_STRING, gzdw, 0),\
	DEFSDMEMBER(T_STRING, ssjmsf, 0),\
	DEFSDMEMBER(T_STRING, kxrq, 0),\
	DEFSDMEMBER(T_DOUBLE, ywje, 2),\
	DEFSDMEMBER(T_DOUBLE, sjywje, 2),\
	DEFSDMEMBER(T_DOUBLE, fyje1, 2),\
	DEFSDMEMBER(T_DOUBLE, sjfyje1, 2),\
	DEFSDMEMBER(T_DOUBLE, fyje2, 2),\
	DEFSDMEMBER(T_DOUBLE, sjfyje2, 2),\
	DEFSDMEMBER(T_DOUBLE, fyje3, 2),\
	DEFSDMEMBER(T_DOUBLE, sjfyje3, 2),\
	DEFSDMEMBER(T_DOUBLE, fyje4, 2),\
	DEFSDMEMBER(T_DOUBLE, sjfyje4, 2),\
	DEFSDMEMBER(T_DOUBLE, fyje5, 2),\
	DEFSDMEMBER(T_DOUBLE, sjfyje5, 2),\
	DEFSDMEMBER(T_DOUBLE, sxfje, 2),\
	DEFSDMEMBER(T_DOUBLE, sjsxfje, 2),\
	DEFSDMEMBER(T_STRING, shzt, 0),\
	DEFSDMEMBER(T_STRING, clzt, 0),\
	DEFSDMEMBER(T_STRING, cgbz, 0),\
	DEFSDMEMBER(T_STRING, xym, 0),\
	DEFSDMEMBER(T_STRING, xyxx, 0),\
	DEFSDMEMBER(T_STRING, zjrq, 0),\
	DEFSDMEMBER(T_STRING, zjsj, 0),\
	DEFSDMEMBER(T_STRING, zjlsh, 0),\
	DEFSDMEMBER(T_STRING, zjxym, 0),\
	DEFSDMEMBER(T_STRING, zjxyxx, 0),\
	DEFSDMEMBER(T_STRING, dsfrq, 0),\
	DEFSDMEMBER(T_STRING, dsfsj, 0),\
	DEFSDMEMBER(T_STRING, dsflsh, 0),\
	DEFSDMEMBER(T_STRING, dsfxym, 0),\
	DEFSDMEMBER(T_STRING, dsfxyxx, 0),\
	DEFSDMEMBER(T_STRING, wbrq, 0),\
	DEFSDMEMBER(T_STRING, wbpch, 0),\
	DEFSDMEMBER(T_LONG, wbxh, 0),\
	DEFSDMEMBER(T_STRING, zjpch, 0),\
	DEFSDMEMBER(T_STRING, kzzd1, 0),\
	DEFSDMEMBER(T_STRING, kzzd2, 0),\
	DEFSDMEMBER(T_STRING, kzzd3, 0),\
	DEFSDMEMBER(T_STRING, kzzd4, 0),\
	DEFSDMEMBER(T_STRING, kzzd5, 0),\
	DEFSDMEMBER(T_STRING, kzzd6, 0),\
	DEFSDMEMBER(T_STRING, kzzd7, 0),\
	DEFSDMEMBER(T_STRING, kzzd8, 0),\
	DEFSDMEMBER(T_STRING, kzzd9, 0),\
	DEFSDMEMBER(T_DOUBLE, kzzd10, 2),\
	DEFSDMEMBER(T_STRING, remark1, 0),\
	DEFSDMEMBER(T_STRING, remark2, 0)

	DECLAREFIELDS(SD_BATCH_DSDF_DETAIL)

#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __BATCH_DSDF_DETAIL_EH__*/
