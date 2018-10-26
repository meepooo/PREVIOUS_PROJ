/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:APP_TXAQXX.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[杨东]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:APP_TXAQXX (通讯安全信息表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __APP_TXAQXX_H__
#define __APP_TXAQXX_H__
typedef struct TDB_APP_TXAQXX
{
  char   ljbs[8+1];              /*联机标识*/
              /*联机标识 L_*/
  char   ljmc[40+1];              /*联机名称*/
              /*联机名称*/
  char   ljlx[1+1];              /*联机类型*/
              /*联机类型 1行内主机 2行内其他系统 3外联单位 9其他*/
  char   dwbh[16+1];              /*单位编号*/
              /*单位编号 联机方编号*/
  char   qdkz[1+1];              /*签到控制*/
              /*是否控制签到状态（默认1）
                0 控制 1不控制*/
  char   txms[1+1];              /*通讯模式*/
              /*通讯模式见数据字典 KEY=K_TXMS*/
  char   txdz[100+1];              /*通讯地址*/
              /*通讯地址*/
  char   txdk[6+1];              /*通讯端口*/
              /*通讯端口*/
  int    fscs;              /*发送超时*/
              /*发送超时*/
  int    jscs;              /*接收超时*/
              /*接收超时*/
  char   ljjgh[16+1];              /*联机机构号*/
              /*联机机构号*/
  char   ljgyh[16+1];              /*联机柜员号*/
              /*联机柜员号*/
  char   ljzdh[16+1];              /*联机终端号*/
              /*联机终端号*/
  char   key1[128+1];              /*密钥1*/
              /*密钥1*/
  char   key2[128+1];              /*密钥2*/
              /*密钥2*/
  char   key3[128+1];              /*密钥3*/
              /*密钥3*/
  char   ftpdz[16+1];              /*FTP地址*/
              /*ftp地址，默认同通讯地址*/
  char   ftpyh[16+1];              /*FTP用户*/
              /*ftp用户名称*/
  char   ftpmm[32+1];              /*FTP密码*/
              /*ftp用户密码*/
  char   ftpgzfs[1+1];              /*FTP工作方式*/
              /*(1 主动模式 2 被动模式ii)*/
  char   ftpcsfs[1+1];              /*FTP传输方式*/
              /*ftp传输方式(1 bin 2 ascii)*/
  char   ftpzdms[1+1];              /*FTP主动被动模式*/
              /*0-主动PORT 1-被动PASV*/
  char   ftpdflj[40+1];              /*对方文件路径*/
              /*对方文件存放路径*/
  char   ftpbdlj[40+1];              /*本地文件路径*/
              /*本地文件存放路径*/
  char   whjg[16+1];              /*维护机构*/
              /**/
  char   whgy[16+1];              /*维护柜员*/
              /**/
  char   whsj[14+1];              /*维护时间*/
              /**/
  char   extfld1[40+1];              /*扩展字段1*/
              /*扩展字段1*/
  char   extfld2[254+1];              /*扩展字段2*/
              /*扩展字段2*/
  char   txzt[1+1];              /*通讯状态*/
              /*通讯状态 0正常 9无效*/
  char   qdzt[1+1];              /*签到状态*/
              /*签到状态  1签退 2签到 */
}APP_TXAQXX;

#define SD_DATA  APP_TXAQXX
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  ljbs, 0),\
	DEFSDMEMBER(T_STRING,  ljmc, 0),\
	DEFSDMEMBER(T_STRING,  ljlx, 0),\
	DEFSDMEMBER(T_STRING,  dwbh, 0),\
	DEFSDMEMBER(T_STRING,  qdkz, 0),\
	DEFSDMEMBER(T_STRING,  txms, 0),\
	DEFSDMEMBER(T_STRING,  txdz, 0),\
	DEFSDMEMBER(T_STRING,  txdk, 0),\
	DEFSDMEMBER(T_LONG,  fscs, 0),\
	DEFSDMEMBER(T_LONG,  jscs, 0),\
	DEFSDMEMBER(T_STRING,  ljjgh, 0),\
	DEFSDMEMBER(T_STRING,  ljgyh, 0),\
	DEFSDMEMBER(T_STRING,  ljzdh, 0),\
	DEFSDMEMBER(T_STRING,  key1, 0),\
	DEFSDMEMBER(T_STRING,  key2, 0),\
	DEFSDMEMBER(T_STRING,  key3, 0),\
	DEFSDMEMBER(T_STRING,  ftpdz, 0),\
	DEFSDMEMBER(T_STRING,  ftpyh, 0),\
	DEFSDMEMBER(T_STRING,  ftpmm, 0),\
	DEFSDMEMBER(T_STRING,  ftpgzfs, 0),\
	DEFSDMEMBER(T_STRING,  ftpcsfs, 0),\
	DEFSDMEMBER(T_STRING,  ftpzdms, 0),\
	DEFSDMEMBER(T_STRING,  ftpdflj, 0),\
	DEFSDMEMBER(T_STRING,  ftpbdlj, 0),\
	DEFSDMEMBER(T_STRING,  whjg, 0),\
	DEFSDMEMBER(T_STRING,  whgy, 0),\
	DEFSDMEMBER(T_STRING,  whsj, 0),\
	DEFSDMEMBER(T_STRING,  extfld1, 0),\
	DEFSDMEMBER(T_STRING,  extfld2, 0),\
	DEFSDMEMBER(T_STRING,  txzt, 0),\
	DEFSDMEMBER(T_STRING,  qdzt, 0)


	DECLAREFIELDS(SD_APP_TXAQXX)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __APP_TXAQXX_H__*/

