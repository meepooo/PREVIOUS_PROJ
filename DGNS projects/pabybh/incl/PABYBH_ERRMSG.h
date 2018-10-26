/**********************************************************************
版权所有:恒生电子股份有限公司
项目名称:综合应用平台（GAPS）项目
版    本:V2.1.0.1
操作系统:AIX LINUX 
数 据 库:
文 件 名:pabybh_midmsg.h
文件描述:系统信息宏定义头文件
项 目 组:中间业务产品研发组
程 序 员:中间业务产品研发组
发布时间:2017年08月03日
**********************************************************************/
/*
修改记录
修改日期:
修改内容:
修改人:
*/
#ifndef __PABYBH_MID_H__
#define __PABYBH_MID_H__
 
/*---------------平台增加定义的响应码和响应信息-----BEGIN----------*/

#define MID_PABYBH_ERR_JYCG             00000
#define MSG_PABYBH_ERR_JYCG             "交易成功"

#define MID_PABYBH_ERR_TXCS    				    98798
#define MSG_PABYBH_ERR_TXCS           "通讯超时"

#define MID_PABYBH_ERR_XTGZ    				    98799
#define MSG_PABYBH_ERR_XTGZ				"系统故障"

#define MID_PABYBH_ERR_MYMY    				    98601
#define MSG_PABYBH_ERR_MYMY				"没有可更新的密钥"

#define MID_PABYBH_ERR_MYGXSB    				    98602
#define MSG_PABYBH_ERR_MYGXSB				"密钥更新失败"

#define MID_PABYBH_ERR_JYJGWZ    				    98603
#define MSG_PABYBH_ERR_JYJGWZ				"交易结果未知"

#define MID_PABYBH_ERR_YWK    				    98604
#define MSG_PABYBH_ERR_YWK				"有必须域为空"

#define MID_PABYBH_ERR_YCZ    				    98605
#define MSG_PABYBH_ERR_YCZ				"已冲正/撤销"

#define MID_PABYBH_ERR_ZJYC  				    98606
#define MSG_PABYBH_ERR_ZJYC				"资金异常"

#define MID_PABYBH_ERR_JYCZ  				    98607
#define MSG_PABYBH_ERR_JYCZ				"交易重帐"

#define MID_PABYBH_ERR_JYBCZ 				    98608
#define MSG_PABYBH_ERR_JYBCZ				"原交易不存在"

#define MID_PABYBH_ERR_WZCW 				    98797
#define MSG_PABYBH_ERR_WZCW				"通讯未知错误"

#define MID_PABYBH_ERR_CS 				    98609
#define MSG_PABYBH_ERR_CS				"处理异常或超时，请稍后再试"

#define MID_PABYBH_ERR_LJSB 				    98610
#define MSG_PABYBH_ERR_LJSB			"连接失败"

#define MID_PABYBH_ERR_ZHCX 				    98611
#define MSG_PABYBH_ERR_ZHCX			"交易帐户已撤销"

#define MID_PABYBH_ERR_ZHCZ 				    98612
#define MSG_PABYBH_ERR_ZHCZ			"交易帐户已存在"

#define MID_PABYBH_ERR_ZHDJ 				    98613
#define MSG_PABYBH_ERR_ZHDJ			"交易帐户已冻结"

#define MID_PABYBH_ERR_ZHGS				    98614
#define MSG_PABYBH_ERR_ZHGS			"交易帐户已挂失"

#define MID_PABYBH_ERR_ZHXH				    98615
#define MSG_PABYBH_ERR_ZHXH			"交易帐户已销户"

#define MID_PABYBH_ERR_ZEFF				    98616
#define MSG_PABYBH_ERR_ZEFF			"金额非法"

#define MID_PABYBH_ERR_RZZT				    98617
#define MSG_PABYBH_ERR_RZZT			"现为日终状态，还未日初，不能进行业务受理"

#define MID_PABYBH_ERR_QQCS				    98618
#define MSG_PABYBH_ERR_QQCS			"请求超时"

#define MID_PABYBH_ERR_SCLSSB				    98619
#define MSG_PABYBH_ERR_SCLSSB			"生成平台流水失败"

#define MID_PABYBH_ERR_CRLSSB				    98620
#define MSG_PABYBH_ERR_CRLSSB			"插入流水失败"

#define MID_PABYBH_ERR_GXLSSB				    98621
#define MSG_PABYBH_ERR_GXLSSB			"更新流水失败"

#define MID_PABYBH_ERR_GXLSSB				    98621
#define MSG_PABYBH_ERR_GXLSSB			"更新流水失败"

#define MID_PABYBH_ERR_TXCS2    				    98622
#define MSG_PABYBH_ERR_TXCS2           "通讯超时"

#define MID_PABYBH_ERR_LJSB2 				    98623
#define MSG_PABYBH_ERR_LJSB2			"连接失败"

#define MID_PABYBH_ERR_SJKSB 				    98624
#define MSG_PABYBH_ERR_SJKSB			"数据库操作失败"

#define MID_PABYBH_ERR_ZHYQY 				    98625
#define MSG_PABYBH_ERR_ZHYQY			"此账户已在其他行签过约"

#define MID_PABYBH_ERR_ZFPLTZ 				    98626
#define MSG_PABYBH_ERR_ZFPLTZ			"重复发批量通知"

#define MID_PABYBH_ERR_CZYC 				    98627
#define MSG_PABYBH_ERR_CZYC			"资金划转超时后转冲正异常 "

#define MID_PABYBH_ERR_HZSB 				    98628
#define MSG_PABYBH_ERR_HZSB			"资金划转失败 "

#define MID_PABYBH_ERR_LSHBCZ 				    98629
#define MSG_PABYBH_ERR_LSHBCZ		"流水号不存在"

#define MID_PABYBH_ERR_KHBCZ 				    98630
#define MSG_PABYBH_ERR_KHBCZ		"客户不存在 "

#define MID_PABYBH_ERR_ZTBZC 				    98631
#define MSG_PABYBH_ERR_ZTBZC		"客户状态不正常 "

#define MID_PABYBH_ERR_BNZZ 				    98632
#define MSG_PABYBH_ERR_BNZZ		"不允许进行转账交易 "

#define MID_PABYBH_ERR_YEBZ 				    98633
#define MSG_PABYBH_ERR_YEBZ		"余额不足 "

#define MID_PABYBH_ERR_ZHYC 				    98634
#define MSG_PABYBH_ERR_ZHYC		"账户状态异常 "

#define MID_PABYBH_ERR_ZHBZ 				    98635
#define MSG_PABYBH_ERR_ZHBZ		"账户不存在 "


#define MID_PABYBH_ERR_MMCW 				    98636
#define MSG_PABYBH_ERR_MMCW		"密码错误"

#define MID_PABYBH_ERR_RQBYZ 				    98637
#define MSG_PABYBH_ERR_RQBYZ		"业务日期不一致"

#define MID_PABYBH_ERR_ZJDJ 				    98638
#define MSG_PABYBH_ERR_ZJDJ		"资金冻结/解冻失败"

#define MID_PABYBH_ERR_CZSB 				    98639
#define MSG_PABYBH_ERR_CZSB		"资金冲正失败"

#define MID_PABYBH_ERR_JYMAC 				    98640
#define MSG_PABYBH_ERR_JYMAC		"MAC校验错误 "

#define MID_PABYBH_ERR_SCMAC 				    98641
#define MSG_PABYBH_ERR_SCMAC		"生成MAC错误 "

#define MID_PABYBH_ERR_ZJYCZ 				    98642
#define MSG_PABYBH_ERR_ZJYCZ		"资金已冲正 "

#define MID_PABYBH_ERR_QDCWDY 				    98643
#define MSG_PABYBH_ERR_QDCWDY		"交易未在渠道接入层定义"

#define MID_PABYBH_ERR_JEBYZ 				    98644
#define MSG_PABYBH_ERR_JEBYZ			"文件与报文的金额、记录不一致"

#define MID_PABYBH_ERR_WJBCZ 				    98645
#define MSG_PABYBH_ERR_WJBCZ		"文件不存在"

#define MID_PABYBH_ERR_TCBCZ 				    98646
#define MSG_PABYBH_ERR_TCBCZ		"找不到合作行头寸信息"

#define MID_PABYBH_ERR_XZZJJY 				    98647
#define MSG_PABYBH_ERR_XZZJJY		"合作行已经被限制做资金交易"

#define MID_PABYBH_ERR_LWHTCBZ 				    98648
#define MSG_PABYBH_ERR_LWHTCBZ		"头寸不足，合作行已停止扣款交易!!"

#define MID_PABYBH_ERR_TCTZ 				    98649
#define MSG_PABYBH_ERR_TCTZ		"合作行已开始透支，交易金额不允许高于小额标准!!"

#define MID_PABYBH_ERR_YYTCBZ 				    98650
#define MSG_PABYBH_ERR_YYTCBZ		"头寸不足以完成本次交易!!"

#define MID_PABYBH_ERR_JECX 				    98651
#define MSG_PABYBH_ERR_JECX		"交易金额超出设定的合作行业务交易额上限!!"

#define MID_PABYBH_ERR_GYWK 				    98652
#define MSG_PABYBH_ERR_GYWK		"交易柜员不能为空"

#define MID_PABYBH_ERR_YCZBNQR 				    98653
#define MSG_PABYBH_ERR_YCZBNQR		"原交易已被撤销或冲正过,不允许做确认"

#define MID_PABYBH_ERR_YJYSB 				    98654
#define MSG_PABYBH_ERR_YJYSB 		"原交易失败 "

#define MID_PABYBH_ERR_ZHWK 				    98655
#define MSG_PABYBH_ERR_ZHWK 		"交易帐号不能为空"

#define MID_PABYBH_ERR_ZHBCZ 				    98656
#define MSG_PABYBH_ERR_ZHBCZ 		"账户不存在"

#define MID_PABYBH_ERR_ZJBF 				    98657
#define MSG_PABYBH_ERR_ZJBF 		"证件信息不符"

#define MID_PABYBH_ERR_SJHMBF 				    98658
#define MSG_PABYBH_ERR_SJHMBF 		"手机号码不符"

#define MID_PABYBH_ERR_HMBF 				    98659
#define MSG_PABYBH_ERR_HMBF 		"户名不符"

#define MID_PABYBH_ERR_ZHYDJ 				    98660
#define MSG_PABYBH_ERR_ZHYDJ 		"帐号已冻结"

#define MID_PABYBH_ERR_ZHYGS 				    98661
#define MSG_PABYBH_ERR_ZHYGS 		"帐号已挂失"

#define MID_PABYBH_ERR_ZHYZX 				    98662
#define MSG_PABYBH_ERR_ZHYZX 		"帐号已注销 "

#define MID_PABYBH_ERR_ZHZTYC 				    98663
#define MSG_PABYBH_ERR_ZHZTYC		"帐号状态异常"

#define MID_PABYBH_ERR_CXYESB 				    98664
#define MSG_PABYBH_ERR_CXYESB		"查询余额失败"

#define MID_PABYBH_ERR_BZWK 				    98665
#define MSG_PABYBH_ERR_BZWK		"交易币种不能为空"

#define MID_PABYBH_ERR_ZHXXBCZ 				    98666
#define MSG_PABYBH_ERR_ZHXXBCZ		"帐号信息不存在"

#define MID_PABYBH_ERR_JYJEWK 				    98667
#define MSG_PABYBH_ERR_JYJEWK		"交易金额不能为空"

#define MID_PABYBH_ERR_ZHMMBF				    98668
#define MSG_PABYBH_ERR_ZHMMBF		"帐号密码不符"       

#define MID_PABYBH_ERR_QLSSB				    98669
#define MSG_PABYBH_ERR_QLSSB		"取流水表数据失败"           

#define MID_PABYBH_ERR_DJLSSB				    98670
#define MSG_PABYBH_ERR_DJLSSB		"登记流水表失败"   

#define MID_PABYBH_ERR_QLBSB				    98671
#define MSG_PABYBH_ERR_QLBSB		"清理表内容失败"

#define MID_PABYBH_ERR_DJHMHHSB				    98672
#define MSG_PABYBH_ERR_DJHMHHSB		"登记行名行号信息表失败"   

#define MID_PABYBH_ERR_DJCDBSB				    98673
#define MSG_PABYBH_ERR_DJCDBSB		"登记磁道信息表失败"

#define MID_PABYBH_ERR_HETDZMXSB				    98674
#define MSG_PABYBH_ERR_HETDZMXSB		"登记行E通对账明细表失败"

#define MID_PABYBH_ERR_DJZJZWSB				    98675
#define MSG_PABYBH_ERR_DJZJZWSB			"登记主机账务信息失败"

#define MID_PABYBH_ERR_JYYC				    98676
#define MSG_PABYBH_ERR_JYYC			"交易异常"

#define MID_PABYBH_ERR_YJYJEBF				    98677
#define MSG_PABYBH_ERR_YJYJEBF			"与原交易金额不符"

#define MID_PABYBH_ERR_YJYBZBF				    98678
#define MSG_PABYBH_ERR_YJYBZBF			"与原交易币种不符"

#define MID_PABYBH_ERR_YJYZHBF				    98679
#define MSG_PABYBH_ERR_YJYZHBF			"与原交易账号不符"

#define MID_PABYBH_ERR_ZNQRDRJY				    98680
#define MSG_PABYBH_ERR_ZNQRDRJY			"只能确认当日交易"

#define MID_PABYBH_ERR_ZJYCBNQR				    98681
#define MSG_PABYBH_ERR_ZJYCBNQR			"主机交易异常，不允许做确认"

#define MID_PABYBH_ERR_KZBZBNWK			    98682
#define MSG_PABYBH_ERR_KZBZBNWK			"卡折标志不能为空"

#define MID_PABYBH_ERR_HZHHWK			    98683
#define MSG_PABYBH_ERR_HZHHWK			"合作行行号不能为空"

#define MID_PABYBH_ERR_HQZHSB			    98684
#define MSG_PABYBH_ERR_HQZHSB			"获取帐号失败"

#define MID_PABYBH_ERR_HCBZWK			    98685
#define MSG_PABYBH_ERR_HCBZWK			"钞汇标志不能为空"

#define MID_PABYBH_ERR_HZHWKTFW			    98686
#define MSG_PABYBH_ERR_HZHWKTFW			"合作行未开通服务"

#define MID_PABYBH_ERR_ZHWQY			    98687
#define MSG_PABYBH_ERR_ZHWQY			"该账户无成功签约信息"

#define MID_PABYBH_ERR_JYZCL			    98688
#define MSG_PABYBH_ERR_JYZCL			"交易正在处理中"

#define MID_PABYBH_ERR_DKWJSB			    98689
#define MSG_PABYBH_ERR_DKWJSB			"打开文件失败"

#define MID_PABYBH_ERR_WJMWK			    98690
#define MSG_PABYBH_ERR_WJMWK			"文件名不能为空"

#define MID_PABYBH_ERR_SYBCZWWC		    98691
#define MSG_PABYBH_ERR_SYBCZWWC			"请先完成前一步点操作"

#define MID_PABYBH_ERR_ZHBPP		    98692
#define MSG_PABYBH_ERR_ZHBPP			"帐号不匹配"

#define MID_PABYBH_ERR_ZJHMBF		    98693
#define MSG_PABYBH_ERR_ZJHMBF			"证件号码不符"

#define MID_PABYBH_ERR_KHMCWK		    98694
#define MSG_PABYBH_ERR_KHMCWK			"客户名称不能为空"

#define MID_PABYBH_ERR_ZJLXWK		    98695
#define MSG_PABYBH_ERR_ZJLXWK			"证件类型不能为空"

#define MID_PABYBH_ERR_ZJHMWK		    98696
#define MSG_PABYBH_ERR_ZJHMWK			"证件号码不能为空"

#define MID_PABYBH_ERR_JSWK		    98697
#define MSG_PABYBH_ERR_JSWK			"劵商代码不能为空"

#define MID_PABYBH_ERR_ZJTZHWK		    98698
#define MSG_PABYBH_ERR_ZJTZHWK			"资金台账号不能为空"

#define MID_PABYBH_ERR_MMWK		    98699
#define MSG_PABYBH_ERR_MMWK			"密码不能为空"

#define MID_PABYBH_ERR_KHLXWK		    98700
#define MSG_PABYBH_ERR_KHLXWK			"客户类型不能为空"

#define MID_PABYBH_ERR_KHJGWK		    98701
#define MSG_PABYBH_ERR_KHJGWK			"开户机构不能为空"

#define MID_PABYBH_ERR_FWDMWK		    98702
#define MSG_PABYBH_ERR_FWDMWK			"服务代码不能空"

#define MID_PABYBH_ERR_JBRXMWK		    98703
#define MSG_PABYBH_ERR_JBRXMWK			"经办人姓名不能为空"

#define MID_PABYBH_ERR_JBRLXWK		    98704
#define MSG_PABYBH_ERR_JBRLXWK			"经办人类型不能为空"

#define MID_PABYBH_ERR_JBRZJHMWK		    98705
#define MSG_PABYBH_ERR_JBRZJHMWK			"经办人证件号码不能为空"

#define MID_PABYBH_ERR_YQDCG		    98706
#define MSG_PABYBH_ERR_YQDCG			"已签到成功"

#define MID_PABYBH_ERR_QYXXBCZ		    98707
#define MSG_PABYBH_ERR_QYXXBCZ			"该签约信息不存在"

#define MID_PABYBH_ERR_QYXXJY		    98708
#define MSG_PABYBH_ERR_QYXXJY			"签约信息已解约"

#define MID_PABYBH_ERR_XZHWK		    98709
#define MSG_PABYBH_ERR_XZHWK			"新账号不能为空"

#define MID_PABYBH_ERR_JZHWK		    98710
#define MSG_PABYBH_ERR_JZHWK			"旧账号不能为空"

#define MID_PABYBH_ERR_JSTJWK		    98711
#define MSG_PABYBH_ERR_JSTJWK			"检索条件不能为空"

#define MID_PABYBH_ERR_JSGJZWK		    98712
#define MSG_PABYBH_ERR_JSGJZWK			"检索关键字不能为空"

#define MID_PABYBH_ERR_QSWKS		    98713
#define MSG_PABYBH_ERR_QSWKS			"日终清算未开始"

#define MID_PABYBH_ERR_QSHZYKS		    98714
#define MSG_PABYBH_ERR_QSHZYKS			"清算汇划已成功"

#define MID_PABYBH_ERR_DZXXBCZ		    98715
#define MSG_PABYBH_ERR_DZXXBCZ			"对账信息不存在"

#define MID_PABYBH_ERR_ZXBDWK		    98716
#define MSG_PABYBH_ERR_ZXBDWK			"执行步点不能为空"

#define MID_PABYBH_ERR_HXLSCF		    98717
#define MSG_PABYBH_ERR_HXLSCF			"核心流水号重复"

#define MID_PABYBH_ERR_HXHMC		    98718
#define MSG_PABYBH_ERR_HXHMC			"核心户名错"

#define MID_PABYBH_ERR_YQYXXBCZ		    98719
#define MSG_PABYBH_ERR_YQYXXBCZ			"原签约信息不存在"

#define MID_PABYBH_ERR_TZSB		    98720
#define MSG_PABYBH_ERR_TZSB			"该对账结果不允许调账，请人工处理"

#define MID_PABYBH_ERR_YTZCG		    98721
#define MSG_PABYBH_ERR_YTZCG			"已调账成功"

#define MID_PABYBH_ERR_RJWFZDTZ		    98722
#define MSG_PABYBH_ERR_RJWFZDTZ			"非资金划转入金交易,无法自动调账,请人工处理"

#define MID_PABYBH_ERR_CJWFZDTZ		    98723
#define MSG_PABYBH_ERR_CJWFZDTZ			"非资金划转出金交易,无法自动调账,请人工处理"

#define MID_PABYBH_ERR_WJXZSB		    98724
#define MSG_PABYBH_ERR_WJXZSB		"文件下载失败"

#define MID_PABYBH_ERR_WJZHSB		    98725
#define MSG_PABYBH_ERR_WJZHSB		"文件转换失败"

#define MID_PABYBH_ERR_YWWKZ		    98726
#define MSG_PABYBH_ERR_YWWKZ		"业务未到开展时间"

#define MID_PABYBH_ERR_YWYJS		    98727
#define MSG_PABYBH_ERR_YWYJS		"业务已过结束时间"

#define MID_PABYBH_ERR_FWWSX		    98728
#define MSG_PABYBH_ERR_FWWSX		"服务尚未生效"

#define MID_PABYBH_ERR_WJMXBF		    98729
#define MSG_PABYBH_ERR_WJMXBF		"文件明细数与总明细数不符"

#define MID_PABYBH_ERR_WJZJEBF	    98730
#define MSG_PABYBH_ERR_WJZJEBF		"文件总金额与明细总金额不符"

#define MID_PABYBH_ERR_HXYCZ	    98731
#define MSG_PABYBH_ERR_HXYCZ		"核心已冲正"

#define MID_PABYBH_ERR_HXJZBZ	    98732
#define MSG_PABYBH_ERR_HXJLBZ		"核心原记录不存在"

#define MID_PABYBH_ERR_WJZDWK	    98733
#define MSG_PABYBH_ERR_WJZDWK		"文件关键字段不能为空"

#define MID_PABYBH_ERR_CXHMCC	    98734
#define MSG_PABYBH_ERR_CXHMCC		"查询户名出错"

#define MID_PABYBH_ERR_KMZHBD	    98735
#define MSG_PABYBH_ERR_KMZHBD		"科目账号信息不准确"

#define MID_PABYBH_ERR_YWLSWK	    98736
#define MSG_PABYBH_ERR_YWLSWK		"业务流水号不能为空"

#define MID_PABYBH_ERR_PAJYWPZ	    98737
#define MSG_PABYBH_ERR_PAJYWPZ		"平安交易未配置"

#define MID_PABYBH_ERR_BWJXYC	    98738
#define MSG_PABYBH_ERR_BWJXYC		"报文解析异常"

#define MID_PABYBH_ERR_QYZHBYZ	    98739
#define MSG_PABYBH_ERR_QYZHBYZ		"该资金账户签约账号不一致"

#define MID_PABYBH_ERR_KHYCZ	    98740
#define MSG_PABYBH_ERR_KHYCZ		"客户已存在"

#define MID_PABYBH_ERR_JJDZ	    98741
#define MSG_PABYBH_ERR_JJDZ		"资金对账已对平或正在处理中"
/*---------------平台增加定义的响应码和响应信息------END-------------*/

#endif

