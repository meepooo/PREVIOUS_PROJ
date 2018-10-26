/***********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合技术平台(Turandot)项目
版    本:V1.00
操作系统:
数 据 库:INFORMIX
文 件 名:yw_gjj_sendserial.h
文件描述:结构定义数据库开发嵌C头文件
项 目 组:
程 序 员:[刘凯强]
发布时间:2009-4-29 19:40:39 [Gen]
修    订:
修改时间:
************************************************************************
表    名:yw_gjj_sendserial (住建部公积金往帐流水表)
说    明:
************************************************************************
修改记录:
修改日期:
修改内容:
修 改 人:
修改内容:
************************************************************************/
#ifndef __YW_GJJ_SENDSERIAL_H__
#define __YW_GJJ_SENDSERIAL_H__
typedef struct TDB_YW_GJJ_SENDSERIAL
{
	char   sendseqno[32+1];  /*发送方流水号*/
		/*发送方流水号-银行流水号*/
	char   sendnode[6+1];  /*发送方节点号*/
		/*发送方节点号-参见银行代码表*/
	char   senddate[8+1];  /*发送方日期*/
		/*发送方日期*/
	char   sendtime[6+1];  /*发送方时间*/
		/*发送方时间*/
	char   transcode[7+1];  /*交易码*/
		/*交易码*/
	char   receivenode[6+1];  /*接收方节点号*/
		/*接收方节点号-参见公积金中心代码表*/
	char   receivedate[8+1];  /*接收方日期*/
		/*接收方日期*/
	char   receivetime[6+1];  /*接收方时间*/
		/*接收方时间*/
	char   receiveseqno[32+1];  /*接收方流水号*/
		/*接收方流水号-数据应用系统接收流水号*/
	char   jbjg[16+1];  /*银行经办机构*/
		/*经办机构*/
	char   jbgy[16+1];  /*银行经办柜员*/
		/*经办柜员*/
	char   txstatus[1+1];  /*交易状态*/
		/*0：成功 1：失败 9：初始 */
	char   qzlsh[10+1];  /*前置流水号*/
		/*前置流水号*/
	char   qqdzt[2+1];  /*请求单状态*/
		/*20-初始,41-反馈失败,43-反馈超时,99-已反馈*/
	char   respcode[8+1];  /*错误码*/
		/**/
	char   respmsg[254+1];  /*错误原因*/
		/**/
	char   zwrq[8+1];  /*前置日期*/
		/*前置日期*/
	char   systime[6+1];  /*前置时间*/
		/*前置时间*/
	char   remark[32+1];  /*备注*/
		/*备注*/
	char   remark1[64+1];  /*备用1*/
		/*备用1*/
	char   remark2[128+1];  /*备注2*/
		/*备注2*/
	char   remark3[254+1];  /*备用3*/
		/*备用3*/
	char   remark4[254+1];  /*备用4*/
		/*备用4*/

}YW_GJJ_SENDSERIAL;

#define SD_DATA  YW_GJJ_SENDSERIAL
#define SD_MEMBERS \
	DEFSDMEMBER(T_STRING,  sendseqno, 0),\
	DEFSDMEMBER(T_STRING,  sendnode, 0),\
	DEFSDMEMBER(T_STRING,  senddate, 0),\
	DEFSDMEMBER(T_STRING,  sendtime, 0),\
	DEFSDMEMBER(T_STRING,  transcode, 0),\
	DEFSDMEMBER(T_STRING,  receivenode, 0),\
	DEFSDMEMBER(T_STRING,  receivedate, 0),\
	DEFSDMEMBER(T_STRING,  receivetime, 0),\
	DEFSDMEMBER(T_STRING,  receiveseqno, 0),\
	DEFSDMEMBER(T_STRING,  jbjg, 0),\
	DEFSDMEMBER(T_STRING,  jbgy, 0),\
	DEFSDMEMBER(T_STRING,  txstatus, 0),\
	DEFSDMEMBER(T_STRING,  qzlsh, 0),\
	DEFSDMEMBER(T_STRING,  qqdzt, 0),\
	DEFSDMEMBER(T_STRING,  respcode, 0),\
	DEFSDMEMBER(T_STRING,  respmsg, 0),\
	DEFSDMEMBER(T_STRING,  zwrq, 0),\
	DEFSDMEMBER(T_STRING,  systime, 0),\
	DEFSDMEMBER(T_STRING,  remark, 0),\
	DEFSDMEMBER(T_STRING,  remark1, 0),\
	DEFSDMEMBER(T_STRING,  remark2, 0),\
	DEFSDMEMBER(T_STRING,  remark3, 0),\
	DEFSDMEMBER(T_STRING,  remark4, 0)


	DECLAREFIELDS(SD_YW_GJJ_SENDSERIAL)
#undef SD_DATA
#undef SD_MEMBERS

#endif  /*end of __YW_GJJ_SENDSERIAL_H__*/
