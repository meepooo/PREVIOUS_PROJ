/*==============================================================*/
/* Table: gab_dxzp_lltj                                         */
/*==============================================================*/
comment on table gab_dxzp_lltj is
'记录电信诈骗流量统计表';

comment on column gab_dxzp_lltj.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_lltj.ywsqbh is
'请求单标识 请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_lltj.tgjgbm is
'托管机构编码';

comment on column gab_dxzp_lltj.ywlx is
'业务类型';

comment on column gab_dxzp_lltj.ptywlx is
'业务类型';

comment on column gab_dxzp_lltj.qssj is
'起始时间';

comment on column gab_dxzp_lltj.jzsj is
'截止时间';

comment on column gab_dxzp_lltj.tjsm is
'案件说明';

comment on column gab_dxzp_lltj.llzz is
'流量总值';

comment on column gab_dxzp_lltj.wfkllzz is
'未反馈流量总值';

comment on column gab_dxzp_lltj.qttjz is
'其他统计值';

comment on column gab_dxzp_lltj.qttjsjsm is
'其他统计数据说明';

comment on column gab_dxzp_lltj.bz is
'备注';

comment on column gab_dxzp_lltj.zwrq is
'gaps日期';

comment on column gab_dxzp_lltj.systime is
'gaps时间';

comment on column gab_dxzp_lltj.by1 is
'备用1';

comment on column gab_dxzp_lltj.by2 is
'备用2';

comment on column gab_dxzp_lltj.by3 is
'备用3';

/*==============================================================*/
/* Table: gab_dxzp_gajgbm                                       */
/*==============================================================*/
comment on table gab_dxzp_gajgbm is
'记录电信诈骗公安机构编码表';

comment on column gab_dxzp_gajgbm.jgbm is
'机构编码';

comment on column gab_dxzp_gajgbm.jgmc is
'机构名称';

comment on column gab_dxzp_gajgbm.by1 is
'备用1';

comment on column gab_dxzp_gajgbm.by2 is
'备用2';

comment on column gab_dxzp_gajgbm.by3 is
'备用3';

/*==============================================================*/
/* Table: gab_dxzp_jghh                                         */
/*==============================================================*/
comment on table gab_dxzp_jghh is
'记录电信诈骗机构行号信息';

comment on column gab_dxzp_jghh.jgh is
'机构号，一般指托管机构号';

comment on column gab_dxzp_jghh.hh is
'行号';

comment on column gab_dxzp_jghh.jgmc is
'机构名称';

comment on column gab_dxzp_jghh.by1 is
'备用1';

comment on column gab_dxzp_jghh.by2 is
'备用2';

comment on column gab_dxzp_jghh.by3 is
'备用3';

/*==============================================================*/
/* Table: gab_dxzp_pcgy                                         */
/*==============================================================*/
comment on table gab_dxzp_pcgy is
'电信诈骗上报信息_批次概要信息';

comment on column gab_dxzp_pcgy.sbpch is
'上报批次号';

comment on column gab_dxzp_pcgy.scrq is
'生成日期';

comment on column gab_dxzp_pcgy.sjgs is
'事件归属 yckk-异常开卡 sazh-涉案账户 ycsj-异常事件';

comment on column gab_dxzp_pcgy.sjtzm is
'事件特征码';

comment on column gab_dxzp_pcgy.sbjg is
'上报机构';

comment on column gab_dxzp_pcgy.sbgy is
'上报柜员';

comment on column gab_dxzp_pcgy.sbrq is
'上报日期';

comment on column gab_dxzp_pcgy.sbsj is
'上报时间';

comment on column gab_dxzp_pcgy.ysbjls is
'预上报记录数';

comment on column gab_dxzp_pcgy.wsbjls is
'已上报记录数';

comment on column gab_dxzp_pcgy.zwrq is
'gaps日期';

comment on column gab_dxzp_pcgy.systime is
'gaps时间';

comment on column gab_dxzp_pcgy.by1 is
'备用1';

comment on column gab_dxzp_pcgy.by2 is
'备用2';

comment on column gab_dxzp_pcgy.by3 is
'备用3';

/*==============================================================*/
/* Table: gab_dxzp_hmhh                                         */
/*==============================================================*/
comment on table gab_dxzp_hmhh is
'记录电信诈骗行名行号信息';

comment on column gab_dxzp_hmhh.hh is
'行号';

comment on column gab_dxzp_hmhh.xh is
'序号';

comment on column gab_dxzp_hmhh.hm is
'行名';

comment on column gab_dxzp_hmhh.hb is
'行别  1-全国性银行 2-城市商业银行 3-省级农信联社  4-农村商业银行 5-民营银行 9-外资银行 t-托管银行 T-本法人行';

comment on column gab_dxzp_hmhh.hbsm is
'行别说明';

comment on column gab_dxzp_hmhh.jbjg is
'经办机构';

comment on column gab_dxzp_hmhh.jbgy is
'经办柜员';

comment on column gab_dxzp_hmhh.lxdh is
'经办人电话';

comment on column gab_dxzp_hmhh.by1 is
'备用1';

comment on column gab_dxzp_hmhh.by2 is
'备用2';

comment on column gab_dxzp_hmhh.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_sbxx_plzt                                    */
/*==============================================================*/
comment on table gab_dxzp_sbxx_plzt is
'记录上报信息_批量状态信息';

comment on column gab_dxzp_sbxx_plzt.sbpch is
'上报批次号';

comment on column gab_dxzp_sbxx_plzt.sbpcxh is
'上报批次序号';

comment on column gab_dxzp_sbxx_plzt.sbjydm is
'上报交易代码  案件举报—945111,异常开卡—945112,涉案账户—945113,异常事件-945114,动态查询-945123';

comment on column gab_dxzp_sbxx_plzt.sbzt is
'上报状态 0-初始 1-成功 2-失败 3-超时 9-上报中';

comment on column gab_dxzp_sbxx_plzt.respcode is
'响应码';

comment on column gab_dxzp_sbxx_plzt.respmsg is
'响应信息';

comment on column gab_dxzp_sbxx_plzt.zwrq is
'gaps日期';

comment on column gab_dxzp_sbxx_plzt.systime is
'gaps时间';

comment on column gab_dxzp_sbxx_plzt.by1 is
'备用1';

comment on column gab_dxzp_sbxx_plzt.by2 is
'备用2';

comment on column gab_dxzp_sbxx_plzt.by3 is
'备用3';

/*==============================================================*/
/* Table: gab_dxzp_sbxx_zhxx                                    */
/*==============================================================*/
comment on table gab_dxzp_sbxx_zhxx is
'电信诈骗上报信息_账户信息表';

comment on column gab_dxzp_sbxx_zhxx.sbpch is
'上报批次号';

comment on column gab_dxzp_sbxx_zhxx.sbpcxh is
'上报批次序号';

comment on column gab_dxzp_sbxx_zhxx.zhxh is
'交易序号';

comment on column gab_dxzp_sbxx_zhxx.jybm is
'交易编码';

comment on column gab_dxzp_sbxx_zhxx.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_sbxx_zhxx.ywsqbh is
'业务申请编号';

comment on column gab_dxzp_sbxx_zhxx.zh is
'账号';

comment on column gab_dxzp_sbxx_zhxx.kksj is
'开卡时间';

comment on column gab_dxzp_sbxx_zhxx.kkdd is
'开卡地点';

comment on column gab_dxzp_sbxx_zhxx.zwrq is
'gaps日期';

comment on column gab_dxzp_sbxx_zhxx.systime is
'gaps时间';

comment on column gab_dxzp_sbxx_zhxx.by1 is
'备用1';

comment on column gab_dxzp_sbxx_zhxx.by2 is
'备用2';

comment on column gab_dxzp_sbxx_zhxx.by3 is
'备用3';

/*==============================================================*/
/* Table: gab_dxzp_sbxx_glzhxx                                  */
/*==============================================================*/
comment on table gab_dxzp_sbxx_glzhxx is
'电信诈骗上报信息_关联账户信息表';

comment on column gab_dxzp_sbxx_glzhxx.sbpch is
'上报批次号';

comment on column gab_dxzp_sbxx_glzhxx.sbpcxh is
'上报批次序号';

comment on column gab_dxzp_sbxx_glzhxx.zhxh is
'交易序号';

comment on column gab_dxzp_sbxx_glzhxx.jybm is
'交易编码';

comment on column gab_dxzp_sbxx_glzhxx.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_sbxx_glzhxx.ywsqbh is
'业务申请编号';

comment on column gab_dxzp_sbxx_glzhxx.zh is
'账号';

comment on column gab_dxzp_sbxx_glzhxx.zhlx is
'账户类型';

comment on column gab_dxzp_sbxx_glzhxx.zhzt is
'账户状态';

comment on column gab_dxzp_sbxx_glzhxx.bz is
'币种';

comment on column gab_dxzp_sbxx_glzhxx.chbz is
'钞汇标志';

comment on column gab_dxzp_sbxx_glzhxx.zwrq is
'gaps日期';

comment on column gab_dxzp_sbxx_glzhxx.systime is
'gaps时间';

comment on column gab_dxzp_sbxx_glzhxx.by1 is
'备用1';

comment on column gab_dxzp_sbxx_glzhxx.by2 is
'备用2';

comment on column gab_dxzp_sbxx_glzhxx.by3 is
'备用3';



/*==============================================================*/
/* Table: gab_dxzp_sbxx_jymx                                    */
/*==============================================================*/
comment on table gab_dxzp_sbxx_jymx is
'记录上报信息交易明细信息';

comment on column gab_dxzp_sbxx_jymx.sbpch is
'上报批次号';

comment on column gab_dxzp_sbxx_jymx.sbpcxh is
'上报批次序号';

comment on column gab_dxzp_sbxx_jymx.zhxh is
'账户序号';

comment on column gab_dxzp_sbxx_jymx.jyxh is
'交易序号';

comment on column gab_dxzp_sbxx_jymx.jybm is
'交易编码';

comment on column gab_dxzp_sbxx_jymx.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_sbxx_jymx.ywsqbh is
'业务申请编号';

comment on column gab_dxzp_sbxx_jymx.sjtzm is
'事件特征码';

comment on column gab_dxzp_sbxx_jymx.zh is
'账卡号';

comment on column gab_dxzp_sbxx_jymx.zhm is
'账户名';

comment on column gab_dxzp_sbxx_jymx.zjlx is
'证件类型';

comment on column gab_dxzp_sbxx_jymx.zjhm is
'证件号';

comment on column gab_dxzp_sbxx_jymx.jylsh is
'交易流水号';

comment on column gab_dxzp_sbxx_jymx.jysj is
'交易时间';

comment on column gab_dxzp_sbxx_jymx.jylx is
'交易类型';

comment on column gab_dxzp_sbxx_jymx.bz is
'币种';

comment on column gab_dxzp_sbxx_jymx.jyje is
'交易金额';

comment on column gab_dxzp_sbxx_jymx.zczhyhjg is
'转出账户银行机构';

comment on column gab_dxzp_sbxx_jymx.zczhyhmc is
'转出账户银行名称';

comment on column gab_dxzp_sbxx_jymx.zczhm is
'转出账户银行名称';

comment on column gab_dxzp_sbxx_jymx.zczh is
'转出账号';

comment on column gab_dxzp_sbxx_jymx.ddzhyhjg is
'对端账户银行机构';

comment on column gab_dxzp_sbxx_jymx.ddzhyhmc is
'对端账户银行名称';

comment on column gab_dxzp_sbxx_jymx.ddzhm is
'对端账户名';

comment on column gab_dxzp_sbxx_jymx.ddzh is
'对端账号';

comment on column gab_dxzp_sbxx_jymx.ip is
'ip地址';

comment on column gab_dxzp_sbxx_jymx.mac is
'mac地址';

comment on column gab_dxzp_sbxx_jymx.sbid is
'设备id';

comment on column gab_dxzp_sbxx_jymx.jydd is
'交易地点';

comment on column gab_dxzp_sbxx_jymx.beiz is
'备注';

comment on column gab_dxzp_sbxx_jymx.zfbz is
'止付标志 0-已止付；1-未止付；';

comment on column gab_dxzp_sbxx_jymx.zwrq is
'gaps日期';

comment on column gab_dxzp_sbxx_jymx.systime is
'gaps时间';

comment on column gab_dxzp_sbxx_jymx.by1 is
'备用1';

comment on column gab_dxzp_sbxx_jymx.by2 is
'备用2';

comment on column gab_dxzp_sbxx_jymx.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_hhmd                                         */
/*==============================================================*/
comment on table gab_dxzp_hhmd is
'记录公安部黑灰名单信息';

comment on column gab_dxzp_hhmd.mdlx is
'名单类型 0-账号名单 1-证件名单';

comment on column gab_dxzp_hhmd.mdjz is
'名单键值 Hash值  ChinaFinancialCertificationAuthority_原始值,经使用SM3算法进行哈希得到的值,如为证照号码的 01_000000000000000000，目前只支持身份证';

comment on column gab_dxzp_hhmd.mdly is
'名单来源 1-公安';

comment on column gab_dxzp_hhmd.ajlx is
'案件类型 1-电信诈骗';

comment on column gab_dxzp_hhmd.xm is
'名单所对应的姓名';

comment on column gab_dxzp_hhmd.mdjb is
'名单级别 0-白名单 1-黑名单 2-灰名单 ';

comment on column gab_dxzp_hhmd.gxrq is
'更新日期';

comment on column gab_dxzp_hhmd.gxsj is
'更新时间';

comment on column gab_dxzp_hhmd.by1 is
'备用1';

comment on column gab_dxzp_hhmd.by2 is
'备用2';

comment on column gab_dxzp_hhmd.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_bwpz                                         */
/*==============================================================*/
comment on table gab_dxzp_bwpz is
'记录报文属性配置信息';

comment on column gab_dxzp_bwpz.jylxbm is
'交易类型编码';

comment on column gab_dxzp_bwpz.jylxmc is
'交易类型名称';

comment on column gab_dxzp_bwpz.jydm is
'交易代码';

comment on column gab_dxzp_bwpz.jymc is
'交易名称';

comment on column gab_dxzp_bwpz.xxlzms is
'信息流转模式 1-标准信息 2-点对点加密';

comment on column gab_dxzp_bwpz.ldhzdbz is
'落地后中断标志 0-不中断 1-中断';

comment on column gab_dxzp_bwpz.fkqzdbz is
'反馈前中断标志 0-不中断 1-中断';

comment on column gab_dxzp_bwpz.by1 is
'备用1';

comment on column gab_dxzp_bwpz.by2 is
'备用2';

comment on column gab_dxzp_bwpz.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_lxdx                                         */
/*==============================================================*/
comment on table gab_dxzp_lxdx is
'记录轮询下达信息';

comment on column gab_dxzp_lxdx.lxrq is
'轮询日期';

comment on column gab_dxzp_lxdx.lxpch is
'轮询批次号';

comment on column gab_dxzp_lxdx.lxsj is
'轮询时间';

comment on column gab_dxzp_lxdx.respcode is
'返回码';

comment on column gab_dxzp_lxdx.respmsg is
'返回信息';

comment on column gab_dxzp_lxdx.lxbs is
'轮询笔数';

comment on column gab_dxzp_lxdx.lxwj is
'轮询文件';

comment on column gab_dxzp_lxdx.by1 is
'备用1';

comment on column gab_dxzp_lxdx.by2 is
'备用2';

comment on column gab_dxzp_lxdx.by3 is
'备用3';



/*==============================================================*/
/* Table: gab_dxzp_sbxx                                         */
/*==============================================================*/
comment on table gab_dxzp_sbxx is
'记录电信诈骗上报信息记录';

comment on column gab_dxzp_sbxx.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_sbxx.jybm is
'交易编码';

comment on column gab_dxzp_sbxx.sbpch is
'上报批次号';

comment on column gab_dxzp_sbxx.ywsqbh is
'请求单标识 请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_sbxx.sqjgdm is
'申请机构代码 公安机关机构编码';

comment on column gab_dxzp_sbxx.mbjgdm is
'目标机构代码 将协助请求单发送给目标机构的代码';

comment on column gab_dxzp_sbxx.ywlx is
'业务类型';

comment on column gab_dxzp_sbxx.sjms is
'事件描述';

comment on column gab_dxzp_sbxx.sbjgdm is
'上报机构代码';

comment on column gab_dxzp_sbxx.sbjgmc is
'上报机构名称';

comment on column gab_dxzp_sbxx.jbrxm is
'经办人姓名';

comment on column gab_dxzp_sbxx.jbrdh is
'经办人电话';

comment on column gab_dxzp_sbxx.ywrq is
'业务日期';

comment on column gab_dxzp_sbxx.ywlsh is
'业务流水号';

comment on column gab_dxzp_sbxx.jbjg is
'经办机构';

comment on column gab_dxzp_sbxx.jbgy is
'经办柜员';

comment on column gab_dxzp_sbxx.clrq is
'处理日期';

comment on column gab_dxzp_sbxx.clsj is
'处理时间';

comment on column gab_dxzp_sbxx.sbjls is
'上报记录数';

comment on column gab_dxzp_sbxx.sbjg is
'上报结果';

comment on column gab_dxzp_sbxx.respcode is
'响应码';

comment on column gab_dxzp_sbxx.respmsg is
'响应信息';

comment on column gab_dxzp_sbxx.zwrq is
'gaps日期';

comment on column gab_dxzp_sbxx.systime is
'gaps时间';

comment on column gab_dxzp_sbxx.zhqzlsh is
'gaps流水号';

comment on column gab_dxzp_sbxx.sbpcwjm is
'上报批次文件名';

comment on column gab_dxzp_sbxx.by1 is
'备用1';

comment on column gab_dxzp_sbxx.by2 is
'备用2';

comment on column gab_dxzp_sbxx.by3 is
'备用3';



/*==============================================================*/
/* Table: gab_dxzp_xdxx                                         */
/*==============================================================*/
comment on table gab_dxzp_xdxx is
'记录电信诈骗下达指令公共信息';

comment on column gab_dxzp_xdxx.ywsqbh is
'请求单标识 请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_xdxx.jybm is
'交易编码';

comment on column gab_dxzp_xdxx.xxlzms is
'消息流转模式';

comment on column gab_dxzp_xdxx.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_xdxx.fsjgbm is
'发送机构编号';

comment on column gab_dxzp_xdxx.sqjgdm is
'申请机构代码 公安机关机构编码';

comment on column gab_dxzp_xdxx.mbjgdm is
'目标机构代码 将协助请求单发送给目标机构的代码';

comment on column gab_dxzp_xdxx.cxztlb is
'查控主体类别 01代表个人主体 02代表对公（单位）主体';

comment on column gab_dxzp_xdxx.ywlx is
'业务类型';

comment on column gab_dxzp_xdxx.jjcd is
'紧急程度 01代表正常；02代表加急';

comment on column gab_dxzp_xdxx.ajbh is
'案件编号 案件类型名称';

comment on column gab_dxzp_xdxx.ajlx is
'案件类型 案件类型名称';

comment on column gab_dxzp_xdxx.ajsy is
'案件事由';

comment on column gab_dxzp_xdxx.ajsm is
'案件说明';

comment on column gab_dxzp_xdxx.sqrq is
'发送请求给目标机构时的系统日期时间';

comment on column gab_dxzp_xdxx.sqsj is
'发送请求给目标机构时的系统日期时间';

comment on column gab_dxzp_xdxx.sqjgbm is
'申请机构编码';

comment on column gab_dxzp_xdxx.sqjgmc is
'请求人单位名称 查询申请人所属单位名称';

comment on column gab_dxzp_xdxx.jbrxm is
'请求人姓名';

comment on column gab_dxzp_xdxx.jbrzjlx is
'请求人证件类型 此处默认为110031 警官证';

comment on column gab_dxzp_xdxx.jbrzjhm is
'请求人证件号码 请求人警号';

comment on column gab_dxzp_xdxx.jbrdh is
'经办人手机号 查询经办人的手机号码';

comment on column gab_dxzp_xdxx.xcrxm is
'协查人姓名';

comment on column gab_dxzp_xdxx.xcrzjlx is
'协查人证件类型 此处默认为110031 警官证';

comment on column gab_dxzp_xdxx.xcrzjhm is
'协查人证件号码';

comment on column gab_dxzp_xdxx.ywrq is
'业务日期';

comment on column gab_dxzp_xdxx.ywlsh is
'业务流水号';

comment on column gab_dxzp_xdxx.jbjg is
'经办机构';

comment on column gab_dxzp_xdxx.jbgy is
'经办柜员';

comment on column gab_dxzp_xdxx.jbxm is
'银行经办姓名';

comment on column gab_dxzp_xdxx.jbdh is
'银行经办电话';

comment on column gab_dxzp_xdxx.rwsl is
'任务数量';

comment on column gab_dxzp_xdxx.jgfkxdsj is
'结果反馈限定时间';

comment on column gab_dxzp_xdxx.fkxdrq is
'反馈限定日期';

comment on column gab_dxzp_xdxx.fkxdsj is
'反馈限定时间';

comment on column gab_dxzp_xdxx.fkddrq is
'反馈兜底日期';

comment on column gab_dxzp_xdxx.fkddsj is
'反馈兜底时间';

comment on column gab_dxzp_xdxx.szclbz is
'手自处理标志 0-系统 1-手工';

comment on column gab_dxzp_xdxx.clrq is
'处理日期';

comment on column gab_dxzp_xdxx.clsj is
'处理时间';

comment on column gab_dxzp_xdxx.zwrq is
'gaps日期';

comment on column gab_dxzp_xdxx.systime is
'gaps时间';

comment on column gab_dxzp_xdxx.zhqzlsh is
'gaps流水号';

comment on column gab_dxzp_xdxx.qqdzt is
'请求单状态 第一位：0-初始 1-落地 2-处理(提交) 3-提回 4-反馈  第二位：0-初始 1-不成功；2-成功; 3-超时; 9-处理中';

comment on column gab_dxzp_xdxx.ywydm is
'业务应答码 详见人行业务应答码定义';

comment on column gab_dxzp_xdxx.ywydxx is
'业务应答信息 详见人行业务应答码定义';

comment on column gab_dxzp_xdxx.zxjg is
'执行结果 0-不成功；1-成功';

comment on column gab_dxzp_xdxx.respcode is
'错误码';

comment on column gab_dxzp_xdxx.respmsg is
'错误原因';

comment on column gab_dxzp_xdxx.zjrq is
'主机日期';

comment on column gab_dxzp_xdxx.zjlsh is
'主机流水号';

comment on column gab_dxzp_xdxx.dzxh is
'冻止序号';

comment on column gab_dxzp_xdxx.sbpch is
'上报批次号';

comment on column gab_dxzp_xdxx.lxrq is
'轮询日期';

comment on column gab_dxzp_xdxx.lxpch is
'轮询批次号';

comment on column gab_dxzp_xdxx.pcxh is
'批次序号';

comment on column gab_dxzp_xdxx.tjhxcs is
'提交核心次数';

comment on column gab_dxzp_xdxx.fkqzcs is
'反馈前置次数';

comment on column gab_dxzp_xdxx.by11 is
'备用11';

comment on column gab_dxzp_xdxx.by12 is
'备用12';

comment on column gab_dxzp_xdxx.by13 is
'备用13';

comment on table gab_dxzp_ztcx is
'记录电信诈骗主体查询相关信息';

comment on column gab_dxzp_ztcx.ywsqbh is
'主键，请求单标识，用于标识查控请求单';

comment on column gab_dxzp_ztcx.rwxh is
'任务序号';

comment on column gab_dxzp_ztcx.khyh is
'查询账户所属银行机构编码';

comment on column gab_dxzp_ztcx.khyhmc is
'查询账户所属银行名称';

comment on column gab_dxzp_ztcx.zhlb is
'查询账号类别';

comment on column gab_dxzp_ztcx.zhmc is
'查询账户名';

comment on column gab_dxzp_ztcx.zh is
'查询账卡号';

comment on column gab_dxzp_ztcx.jgfksj is
'结果反馈限定时间';

comment on column gab_dxzp_ztcx.zxjg is
'执行结果 0-不成功；1-成功';

comment on column gab_dxzp_ztcx.respcode is
'错误码';

comment on column gab_dxzp_ztcx.respmsg is
'错误原因';

comment on column gab_dxzp_ztcx.fksm is
'反馈说明';

comment on column gab_dxzp_ztcx.fkjgmc is
'反馈机构名称';

comment on column gab_dxzp_ztcx.zwrq is
'gaps日期';

comment on column gab_dxzp_ztcx.systime is
'gaps时间';

comment on column gab_dxzp_ztcx.by1 is
'备用1';

comment on column gab_dxzp_ztcx.by2 is
'备用2';

comment on column gab_dxzp_ztcx.by3 is
'备用3';

comment on table gab_dxzp_djxj is
'记录电信诈骗冻结续解相关信息';

comment on column gab_dxzp_djxj.ywsqbh is
'主键，请求单标识，用于标识查控请求单';

comment on column gab_dxzp_djxj.rwxh is
'任务序号';

comment on column gab_dxzp_djxj.yywsqbh is
'原业务申请编号 原紧急止付的任务流水号识；措施为解除紧急止付时使用；';

comment on column gab_dxzp_djxj.khyh is
'冻结账户所属银行机构编码';

comment on column gab_dxzp_djxj.khyhmc is
'冻结账户所属银行名称';

comment on column gab_dxzp_djxj.zhlb is
'冻结账号类别';

comment on column gab_dxzp_djxj.zhmc is
'冻结账户名';

comment on column gab_dxzp_djxj.zh is
'冻结账卡号';

comment on column gab_dxzp_djxj.zjlx is
'冻结账户证件类型';

comment on column gab_dxzp_djxj.zjhm is
'冻结账号证件号码';

comment on column gab_dxzp_djxj.djfs is
'冻结方式';

comment on column gab_dxzp_djxj.bz is
'币种';

comment on column gab_dxzp_djxj.je is
'金额';

comment on column gab_dxzp_djxj.dqr is
'冻结到期日';

comment on column gab_dxzp_djxj.djqssj is
'冻结起始时间';

comment on column gab_dxzp_djxj.djjssj is
'冻结结束时间';

comment on column gab_dxzp_djxj.jgfksj is
'结果反馈限定时间';

comment on column gab_dxzp_djxj.zxjg is
'执行结果 0-不成功；1-成功';

comment on column gab_dxzp_djxj.respcode is
'错误码';

comment on column gab_dxzp_djxj.respmsg is
'错误原因';

comment on column gab_dxzp_djxj.kh is
'卡号 请求止付的卡号';

comment on column gab_dxzp_djxj.zxqssj is
'执行起始时间  执行措施的时间';

comment on column gab_dxzp_djxj.zxjssj is
'执行起始时间  执行措施的时间';

comment on column gab_dxzp_djxj.fksm is
'反馈说明';

comment on column gab_dxzp_djxj.fkjgmc is
'反馈机构名称';

comment on column gab_dxzp_djxj.djje is
'执行冻结金额';

comment on column gab_dxzp_djxj.zhye is
'账户余额';

comment on column gab_dxzp_djxj.zxdjje is
'在先冻结金额';

comment on column gab_dxzp_djxj.zxdjrq is
'在先冻结到期日';

comment on column gab_dxzp_djxj.zhkyye is
'账户可用余额';

comment on column gab_dxzp_djxj.zxdjjg is
'在先冻结机关';

comment on column gab_dxzp_djxj.zwrq is
'gaps日期';

comment on column gab_dxzp_djxj.systime is
'gaps时间';

comment on column gab_dxzp_djxj.by1 is
'备用1';

comment on column gab_dxzp_djxj.by2 is
'备用2';

comment on column gab_dxzp_djxj.by3 is
'备用3';


comment on table gab_dxzp_jymx is
'记录电信诈骗交易明细相关信息';

comment on column gab_dxzp_jymx.ywsqbh is
'主键，请求单标识，用于标识查控请求单';

comment on column gab_dxzp_jymx.rwxh is
'任务序号';

comment on column gab_dxzp_jymx.khyh is
'查询账户所属银行机构编码';

comment on column gab_dxzp_jymx.khyhmc is
'查询账户所属银行名称';

comment on column gab_dxzp_jymx.zhlb is
'查询账号类别';

comment on column gab_dxzp_jymx.zhmc is
'查询账户名';

comment on column gab_dxzp_jymx.zh is
'查询账卡号';

comment on column gab_dxzp_jymx.cxnr is
'查询内容';

comment on column gab_dxzp_jymx.cxqsrq is
'查询起始日期';

comment on column gab_dxzp_jymx.cxqssj is
'查询起始时间';

comment on column gab_dxzp_jymx.cxjzrq is
'查询截止日期';

comment on column gab_dxzp_jymx.cxjzsj is
'查询截止时间';

comment on column gab_dxzp_jymx.jgfksj is
'结果反馈限定时间';

comment on column gab_dxzp_jymx.zxjg is
'执行结果 0-不成功；1-成功';

comment on column gab_dxzp_jymx.respcode is
'错误码';

comment on column gab_dxzp_jymx.respmsg is
'错误原因';

comment on column gab_dxzp_jymx.fksm is
'反馈说明';

comment on column gab_dxzp_jymx.fkjgmc is
'反馈机构名称';

comment on column gab_dxzp_jymx.zwrq is
'gaps日期';

comment on column gab_dxzp_jymx.systime is
'gaps时间';

comment on column gab_dxzp_jymx.by1 is
'备用1';

comment on column gab_dxzp_jymx.by2 is
'备用2';

comment on column gab_dxzp_jymx.by3 is
'备用3';


comment on table gab_dxzp_qhcx is
'记录电信诈骗全户查询相关信息';

comment on column gab_dxzp_qhcx.ywsqbh is
'主键，请求单标识，用于标识查控请求单';

comment on column gab_dxzp_qhcx.rwxh is
'任务序号';

comment on column gab_dxzp_qhcx.zhlb is
'查询账号类别';

comment on column gab_dxzp_qhcx.cxzjlx is
'查询证照类型代码';

comment on column gab_dxzp_qhcx.cxzjhm is
'查询证照号码';

comment on column gab_dxzp_qhcx.zhmc is
'查询主体名称';

comment on column gab_dxzp_qhcx.cxnr is
'查询内容 01-账户基本信息；02-账户信息(含强制措施、共有权/优先权信息)';

comment on column gab_dxzp_qhcx.jgfksj is
'结果反馈限定时间';

comment on column gab_dxzp_qhcx.bankname is
'查询银行名称';

comment on column gab_dxzp_qhcx.zxjg is
'执行结果 0-不成功；1-成功';

comment on column gab_dxzp_qhcx.respcode is
'错误码';

comment on column gab_dxzp_qhcx.respmsg is
'错误原因';

comment on column gab_dxzp_qhcx.fksm is
'反馈说明';

comment on column gab_dxzp_qhcx.fkjgmc is
'反馈机构名称';

comment on column gab_dxzp_qhcx.zwrq is
'gaps日期';

comment on column gab_dxzp_qhcx.systime is
'gaps时间';

comment on column gab_dxzp_qhcx.by1 is
'备用1';

comment on column gab_dxzp_qhcx.by2 is
'备用2';

comment on column gab_dxzp_qhcx.by3 is
'备用3';


comment on table gab_dxzp_jjzf is
'记录电信诈骗紧急止付相关信息';

comment on column gab_dxzp_jjzf.ywsqbh is
'主键，请求单标识，用于标识查控请求单';

comment on column gab_dxzp_jjzf.rwxh is
'任务序号';

comment on column gab_dxzp_jjzf.yywsqbh is
'原业务申请编号 原紧急止付的任务流水号识；措施为解除紧急止付时使用；';

comment on column gab_dxzp_jjzf.sfblc is
'是否补流程 00-初次提交正常止付人民币活期账户；01-初次提交正常止付外币活期账户；02-银行举报案件止付人民币活期账户；03-银行举报案件止付外币活期账户；04-后补人民币活期止付流程；05-后补外币活期止付流程';

comment on column gab_dxzp_jjzf.yjbsqbh is
'原举报申请编号';

comment on column gab_dxzp_jjzf.kh is
'卡号 请求止付的卡号';

comment on column gab_dxzp_jjzf.zczhyh is
'转出账户所属银行机构编码';

comment on column gab_dxzp_jjzf.zczhyhmc is
'转出账户银行名称';

comment on column gab_dxzp_jjzf.zczhm is
'转出账户名';

comment on column gab_dxzp_jjzf.zczh is
'转出账号';

comment on column gab_dxzp_jjzf.bz is
'币种';

comment on column gab_dxzp_jjzf.zcje is
'转出金额';

comment on column gab_dxzp_jjzf.zcrq is
'转出日期';

comment on column gab_dxzp_jjzf.zcsj is
'转出时间';

comment on column gab_dxzp_jjzf.khyh is
'止付账户所属银行机构编码';

comment on column gab_dxzp_jjzf.khyhmc is
'止付账户所属银行名称';

comment on column gab_dxzp_jjzf.zhlb is
'止付账号类别';

comment on column gab_dxzp_jjzf.zhmc is
'止付账户名';

comment on column gab_dxzp_jjzf.zh is
'止付账卡号';

comment on column gab_dxzp_jjzf.dqr is
'止付到期日';

comment on column gab_dxzp_jjzf.jgfksj is
'结果反馈限定时间';

comment on column gab_dxzp_jjzf.zfqssj is
'止付起始时间';

comment on column gab_dxzp_jjzf.zfjssj is
'止付结束时间';

comment on column gab_dxzp_jjzf.zxjg is
'执行结果 0-执行成功 1-执行失败';

comment on column gab_dxzp_jjzf.respcode is
'错误码';

comment on column gab_dxzp_jjzf.respmsg is
'错误原因';

comment on column gab_dxzp_jjzf.zxqssj is
'执行起始时间';

comment on column gab_dxzp_jjzf.zxjssj is
'执行结束时间';

comment on column gab_dxzp_jjzf.fksm is
'反馈说明';

comment on column gab_dxzp_jjzf.fkjgmc is
'反馈机构名称';

comment on column gab_dxzp_jjzf.zhye is
'账户余额';

comment on column gab_dxzp_jjzf.zwrq is
'gaps日期';

comment on column gab_dxzp_jjzf.systime is
'gaps时间';

comment on column gab_dxzp_jjzf.by1 is
'备用1';

comment on column gab_dxzp_jjzf.by2 is
'备用2';

comment on column gab_dxzp_jjzf.by3 is
'备用3';

comment on table gab_dxzp_dtcx is
'记录电信诈骗动态查询相关信息';

comment on column gab_dxzp_dtcx.ywsqbh is
'主键，请求单标识，用于标识查控请求单';

comment on column gab_dxzp_dtcx.rwxh is
'任务序号';

comment on column gab_dxzp_dtcx.yywsqbh is
'原业务申请编号 原紧急止付的任务流水号识；措施为解除紧急止付时使用；';

comment on column gab_dxzp_dtcx.bz is
'币种';

comment on column gab_dxzp_dtcx.khyh is
'查询账户所属银行机构编码';

comment on column gab_dxzp_dtcx.khyhmc is
'查询账户所属银行名称';

comment on column gab_dxzp_dtcx.zhlb is
'查询账号类别';

comment on column gab_dxzp_dtcx.zhmc is
'查询账户名';

comment on column gab_dxzp_dtcx.kh is
'卡号 请求止付的卡号';

comment on column gab_dxzp_dtcx.zh is
'查询账卡号';

comment on column gab_dxzp_dtcx.dtml is
'动态命令 0-解除；1-执行';

comment on column gab_dxzp_dtcx.zxqsrq is
'执行起始日期';

comment on column gab_dxzp_dtcx.zxjzrq is
'执行截止日期';

comment on column gab_dxzp_dtcx.dtcxqssj is
'动态查询起始时间';

comment on column gab_dxzp_dtcx.dtcxjzsj is
'动态查询截止时间';

comment on column gab_dxzp_dtcx.jgfksj is
'结果反馈限定时间';

comment on column gab_dxzp_dtcx.zxjg is
'执行结果 0-不成功；1-成功';

comment on column gab_dxzp_dtcx.respcode is
'错误码';

comment on column gab_dxzp_dtcx.respmsg is
'错误原因';

comment on column gab_dxzp_dtcx.fksm is
'反馈说明';

comment on column gab_dxzp_dtcx.fkjgmc is
'反馈机构名称';

comment on column gab_dxzp_dtcx.zwrq is
'gaps日期';

comment on column gab_dxzp_dtcx.systime is
'gaps时间';

comment on column gab_dxzp_dtcx.by1 is
'备用1';

comment on column gab_dxzp_dtcx.by2 is
'备用2';

comment on column gab_dxzp_dtcx.by3 is
'备用3';




/*==============================================================*/
/* Table: gab_dxzp_ycsj                                         */
/*==============================================================*/
comment on table gab_dxzp_ycsj is
'记录电信诈骗异常事件记录';

comment on column gab_dxzp_ycsj.sbpch is
'上报批次号';

comment on column gab_dxzp_ycsj.sbpcxh is
'上报批次序号';

comment on column gab_dxzp_ycsj.jybm is
'交易编码';

comment on column gab_dxzp_ycsj.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_ycsj.ywsqbh is
'请求单标识 请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_ycsj.ywlx is
'业务类型';

comment on column gab_dxzp_ycsj.sjtzm is
'事件特征码';

comment on column gab_dxzp_ycsj.yywsqbh is
'原上报编号';

comment on column gab_dxzp_ycsj.jylsh is
'交易流水号';

comment on column gab_dxzp_ycsj.jysj is
'交易时间';

comment on column gab_dxzp_ycsj.jylx is
'交易类型';

comment on column gab_dxzp_ycsj.bz is
'币种';

comment on column gab_dxzp_ycsj.je is
'交易金额';

comment on column gab_dxzp_ycsj.zcyhjg is
'转出账户所属银行机构编码';

comment on column gab_dxzp_ycsj.zcyhmc is
'转出账户所属银行名称';

comment on column gab_dxzp_ycsj.zczhhm is
'转出账户名';

comment on column gab_dxzp_ycsj.zczh is
'转出账卡号';

comment on column gab_dxzp_ycsj.ddyhjg is
'交易对端账户所属银行机构编码';

comment on column gab_dxzp_ycsj.ddyhmc is
'交易对端账户所属银行名称';

comment on column gab_dxzp_ycsj.ddzhm is
'交易对端账户名';

comment on column gab_dxzp_ycsj.ddzh is
'交易对端账卡号';

comment on column gab_dxzp_ycsj.ipdz is
'ip地址';

comment on column gab_dxzp_ycsj.mac is
'mac地址';

comment on column gab_dxzp_ycsj.sbid is
'设备id';

comment on column gab_dxzp_ycsj.jydd is
'交易地点';

comment on column gab_dxzp_ycsj.beiz is
'备注';

comment on column gab_dxzp_ycsj.zwrq is
'gaps日期';

comment on column gab_dxzp_ycsj.systime is
'gaps时间';

comment on column gab_dxzp_ycsj.by1 is
'备用1';

comment on column gab_dxzp_ycsj.by2 is
'备用2';

comment on column gab_dxzp_ycsj.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_yckk                                         */
/*==============================================================*/
comment on table gab_dxzp_yckk is
'记录电信诈骗异常开卡记录';

comment on column gab_dxzp_yckk.sbpch is
'上报批次号';

comment on column gab_dxzp_yckk.sbpcxh is
'上报批次序号';

comment on column gab_dxzp_yckk.jybm is
'交易编码';

comment on column gab_dxzp_yckk.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_yckk.ywsqbh is
'请求单标识 请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_yckk.ywlx is
'业务类型';

comment on column gab_dxzp_yckk.sjtzm is
'事件特征码';

comment on column gab_dxzp_yckk.yywsqbh is
'原上报编号';

comment on column gab_dxzp_yckk.zjlx is
'证件类型';

comment on column gab_dxzp_yckk.zjhm is
'证件号';

comment on column gab_dxzp_yckk.xm is
'姓名';

comment on column gab_dxzp_yckk.zwrq is
'gaps日期';

comment on column gab_dxzp_yckk.systime is
'gaps时间';

comment on column gab_dxzp_yckk.by1 is
'备用1';

comment on column gab_dxzp_yckk.by2 is
'备用2';

comment on column gab_dxzp_yckk.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_sajb                                         */
/*==============================================================*/
comment on table gab_dxzp_sajb is
'记录电信诈骗涉案举报记录';

comment on column gab_dxzp_sajb.sbpch is
'上报批次号';

comment on column gab_dxzp_sajb.sbpcxh is
'上报批次序号';

comment on column gab_dxzp_sajb.jybm is
'交易编码';

comment on column gab_dxzp_sajb.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_sajb.ywsqbh is
'业务申请编号';

comment on column gab_dxzp_sajb.jsjgid is
'接收机构id';

comment on column gab_dxzp_sajb.tgjgbm is
'托管机构编码';

comment on column gab_dxzp_sajb.ywlx is
'业务类型';

comment on column gab_dxzp_sajb.shrxm is
'受害人姓名';

comment on column gab_dxzp_sajb.shrlxdh is
'受害人联系电话';

comment on column gab_dxzp_sajb.zjlx is
'证件类型';

comment on column gab_dxzp_sajb.zjhm is
'证件号';

comment on column gab_dxzp_sajb.sjms is
'事件描述';

comment on column gab_dxzp_sajb.ajjblx is
'案件举报类型  01-报案,02-止付后补流程';

comment on column gab_dxzp_sajb.zjrq is
'主机日期';

comment on column gab_dxzp_sajb.zjlsh is
'主机流水号';

comment on column gab_dxzp_sajb.dzxh is
'冻止序号';

comment on column gab_dxzp_sajb.yxbz is
'影像标志 0-有影像 1-无影像';

comment on column gab_dxzp_sajb.qqdzt is
'请求单状态 第一位：0-初始 1-落地 2-处理(提交) 3-提回 4-反馈  第二位：0-初始 1-不成功；2-成功; 3-超时; 9-处理中';

comment on column gab_dxzp_sajb.zxjg is
'执行结果 0-不成功；1-成功';

comment on column gab_dxzp_sajb.respcode is
'错误码';

comment on column gab_dxzp_sajb.respmsg is
'错误原因';

comment on column gab_dxzp_sajb.fkdjjzsj is
'反馈冻结截止时间';

comment on column gab_dxzp_sajb.cxjg is
'查询结果';

comment on column gab_dxzp_sajb.zwrq is
'gaps日期';

comment on column gab_dxzp_sajb.systime is
'gaps时间';

comment on column gab_dxzp_sajb.by1 is
'备用1';

comment on column gab_dxzp_sajb.by2 is
'备用2';

comment on column gab_dxzp_sajb.by3 is
'备用3';

comment on table gab_dxzp_sazh is
'记录电信诈骗涉案账户记录';

comment on column gab_dxzp_sazh.sbpch is
'上报批次号';

comment on column gab_dxzp_sazh.sbpcxh is
'上报批次序号';

comment on column gab_dxzp_sazh.jybm is
'交易编码';

comment on column gab_dxzp_sazh.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_sazh.ywsqbh is
'请求单标识 请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_sazh.ywlx is
'业务类型';

comment on column gab_dxzp_sazh.sjtzm is
'事件特征码';

comment on column gab_dxzp_sazh.yywsqbh is
'原上报编号';

comment on column gab_dxzp_sazh.kh is
'卡/折号';

comment on column gab_dxzp_sazh.zhm is
'账户名';

comment on column gab_dxzp_sazh.zjlx is
'证件类型';

comment on column gab_dxzp_sazh.zjhm is
'证件号';

comment on column gab_dxzp_sazh.lxdh is
'联系电话';

comment on column gab_dxzp_sazh.txdz is
'通讯地址';

comment on column gab_dxzp_sazh.yzbm is
'邮政编码';

comment on column gab_dxzp_sazh.zhlx is
'账户类型';

comment on column gab_dxzp_sazh.zhzt is
'账户状态';

comment on column gab_dxzp_sazh.khrq is
'开户日期';

comment on column gab_dxzp_sazh.xhrq is
'销户日期';

comment on column gab_dxzp_sazh.kkdd is
'开卡地点';

comment on column gab_dxzp_sazh.zwrq is
'gaps日期';

comment on column gab_dxzp_sazh.systime is
'gaps时间';

comment on column gab_dxzp_sazh.by1 is
'备用1';

comment on column gab_dxzp_sazh.by2 is
'备用2';

comment on column gab_dxzp_sazh.by3 is
'备用3';

comment on table gab_dxzp_zhsa is
'记录电信诈骗账户涉案记录';

comment on column gab_dxzp_zhsa.jybm is
'交易编码';

comment on column gab_dxzp_zhsa.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_zhsa.ywsqbh is
'请求单标识 请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_zhsa.ywlx is
'业务类型';

comment on column gab_dxzp_zhsa.zh is
'账卡号';

comment on column gab_dxzp_zhsa.zhm is
'账户名';

comment on column gab_dxzp_zhsa.zt is
'状态(0-不在涉案/可疑名单；1-在涉案名单；2-在可疑名单)';

comment on column gab_dxzp_zhsa.zwrq is
'gaps日期';

comment on column gab_dxzp_zhsa.systime is
'gaps时间';

comment on column gab_dxzp_zhsa.by1 is
'备用1';

comment on column gab_dxzp_zhsa.by2 is
'备用2';

comment on column gab_dxzp_zhsa.by3 is
'备用3';

comment on table gab_dxzp_sfsa is
'记录电信诈骗身份涉案记录';

comment on column gab_dxzp_sfsa.jybm is
'交易编码';

comment on column gab_dxzp_sfsa.csbwlsh is
'传输报文流水号';

comment on column gab_dxzp_sfsa.ywsqbh is
'请求单标识 请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_sfsa.ywlx is
'业务类型';

comment on column gab_dxzp_sfsa.zjlx is
'证件类型';

comment on column gab_dxzp_sfsa.zjhm is
'证件号';

comment on column gab_dxzp_sfsa.zhhm is
'证件所有人姓名';

comment on column gab_dxzp_sfsa.zt is
'状态(0-不在涉案/可疑名单；1-在涉案名单；2-在可疑名单)';

comment on column gab_dxzp_sfsa.zwrq is
'gaps日期';

comment on column gab_dxzp_sfsa.systime is
'gaps时间';

comment on column gab_dxzp_sfsa.by1 is
'备用1';

comment on column gab_dxzp_sfsa.by2 is
'备用2';

comment on column gab_dxzp_sfsa.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_zhxx_zhjyxx                                  */
/*==============================================================*/
comment on table gab_dxzp_zhxx_zhjyxx is
'记录电信诈骗 账户信息_账号交易信息';

comment on column gab_dxzp_zhxx_zhjyxx.ywsqbh is
'主键，请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_zhxx_zhjyxx.rwxh is
'任务序号';

comment on column gab_dxzp_zhxx_zhjyxx.zhxh is
'账户序号';

comment on column gab_dxzp_zhxx_zhjyxx.zhjyxh is
'账号交易序号';

comment on column gab_dxzp_zhxx_zhjyxx.jylx is
'交易类型';

comment on column gab_dxzp_zhxx_zhjyxx.jdbz is
'借贷标志';

comment on column gab_dxzp_zhxx_zhjyxx.bz is
'币种';

comment on column gab_dxzp_zhxx_zhjyxx.jyje is
'交易金额';

comment on column gab_dxzp_zhxx_zhjyxx.jyye is
'交易余额';

comment on column gab_dxzp_zhxx_zhjyxx.jysj is
'交易时间';

comment on column gab_dxzp_zhxx_zhjyxx.jylsh is
'交易流水号';

comment on column gab_dxzp_zhxx_zhjyxx.jydfmc is
'交易对方名称';

comment on column gab_dxzp_zhxx_zhjyxx.jydfzh is
'交易对方账号';

comment on column gab_dxzp_zhxx_zhjyxx.jydfzjhm is
'交易对方证件号码';

comment on column gab_dxzp_zhxx_zhjyxx.jydfzhkhh is
'交易对方账号开户行';

comment on column gab_dxzp_zhxx_zhjyxx.jyzy is
'交易摘要';

comment on column gab_dxzp_zhxx_zhjyxx.jywdmc is
'交易网点名称';

comment on column gab_dxzp_zhxx_zhjyxx.jywddm is
'交易网点代码';

comment on column gab_dxzp_zhxx_zhjyxx.rzh is
'日志号';

comment on column gab_dxzp_zhxx_zhjyxx.cph is
'传票号';

comment on column gab_dxzp_zhxx_zhjyxx.pzzl is
'凭证种类';

comment on column gab_dxzp_zhxx_zhjyxx.pzh is
'凭证号';

comment on column gab_dxzp_zhxx_zhjyxx.xjbz is
'现金标志';

comment on column gab_dxzp_zhxx_zhjyxx.zdh is
'终端号';

comment on column gab_dxzp_zhxx_zhjyxx.jysfcg is
'交易是否成功';

comment on column gab_dxzp_zhxx_zhjyxx.jyfsd is
'交易发生地';

comment on column gab_dxzp_zhxx_zhjyxx.shmc is
'商户名称';

comment on column gab_dxzp_zhxx_zhjyxx.shh is
'商户号';

comment on column gab_dxzp_zhxx_zhjyxx.ip is
'ip地址';

comment on column gab_dxzp_zhxx_zhjyxx.mac is
'mac地址';

comment on column gab_dxzp_zhxx_zhjyxx.jygyh is
'交易柜员号';

comment on column gab_dxzp_zhxx_zhjyxx.beiz is
'备注';

comment on column gab_dxzp_zhxx_zhjyxx.zwrq is
'gaps日期';

comment on column gab_dxzp_zhxx_zhjyxx.systime is
'gaps时间';

comment on column gab_dxzp_zhxx_zhjyxx.by1 is
'备用1';

comment on column gab_dxzp_zhxx_zhjyxx.by2 is
'备用2';

comment on column gab_dxzp_zhxx_zhjyxx.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_zhjbxx_zhxx                                  */
/*==============================================================*/
comment on table gab_dxzp_zhjbxx_zhxx is
'记录电信诈骗 账户基本信息_账号信息';

comment on column gab_dxzp_zhjbxx_zhxx.ywsqbh is
'主键，请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_zhjbxx_zhxx.rwxh is
'任务序号';

comment on column gab_dxzp_zhjbxx_zhxx.zhxh is
'账户序号';

comment on column gab_dxzp_zhjbxx_zhxx.zh is
'账号';

comment on column gab_dxzp_zhjbxx_zhxx.zhlx is
'账户类型';

comment on column gab_dxzp_zhjbxx_zhxx.zhzt is
'账户状态';

comment on column gab_dxzp_zhjbxx_zhxx.bz is
'币种';

comment on column gab_dxzp_zhjbxx_zhxx.chbz is
'钞汇标志';

comment on column gab_dxzp_zhjbxx_zhxx.zhye is
'账户余额';

comment on column gab_dxzp_zhjbxx_zhxx.kyye is
'可用余额';

comment on column gab_dxzp_zhjbxx_zhxx.zhjysj is
'最后交易时间';

comment on column gab_dxzp_zhjbxx_zhxx.zwrq is
'gaps日期';

comment on column gab_dxzp_zhjbxx_zhxx.systime is
'gaps时间';

comment on column gab_dxzp_zhjbxx_zhxx.by1 is
'备用1';

comment on column gab_dxzp_zhjbxx_zhxx.by2 is
'备用2';

comment on column gab_dxzp_zhjbxx_zhxx.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_jymx_zhjbxx                                */
/*==============================================================*/
comment on table gab_dxzp_jymx_zhjbxx is
'记录电信诈骗交易明细账户基本信息';

comment on column gab_dxzp_jymx_zhjbxx.ywsqbh is
'主键，请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_jymx_zhjbxx.rwxh is
'任务序号';

comment on column gab_dxzp_jymx_zhjbxx.zhm is
'账户名';

comment on column gab_dxzp_jymx_zhjbxx.kzh is
'卡/折号';

comment on column gab_dxzp_jymx_zhjbxx.khwd is
'开户网点';

comment on column gab_dxzp_jymx_zhjbxx.khwddm is
'开户网点代码';

comment on column gab_dxzp_jymx_zhjbxx.khrq is
'开户日期';

comment on column gab_dxzp_jymx_zhjbxx.xhrq is
'销户日期';

comment on column gab_dxzp_jymx_zhjbxx.xhwd is
'销户网点';

comment on column gab_dxzp_jymx_zhjbxx.beiz is
'备注';

comment on column gab_dxzp_jymx_zhjbxx.zwrq is
'gaps日期';

comment on column gab_dxzp_jymx_zhjbxx.systime is
'gaps时间';

comment on column gab_dxzp_jymx_zhjbxx.by1 is
'备用1';

comment on column gab_dxzp_jymx_zhjbxx.by2 is
'备用2';

comment on column gab_dxzp_jymx_zhjbxx.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_qhcx_sfqzxx                                */
/*==============================================================*/
comment on table gab_dxzp_qhcx_sfqzxx is
'记录电信诈骗全户查询_司法强制信息';

comment on column gab_dxzp_qhcx_sfqzxx.ywsqbh is
'主键，请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_qhcx_sfqzxx.rwxh is
'任务序号';

comment on column gab_dxzp_qhcx_sfqzxx.csxh is
'措施序号';

comment on column gab_dxzp_qhcx_sfqzxx.zh is
'账号';

comment on column gab_dxzp_qhcx_sfqzxx.kh is
'卡折号';

comment on column gab_dxzp_qhcx_sfqzxx.djksr is
'冻结开始日';

comment on column gab_dxzp_qhcx_sfqzxx.djjzr is
'冻结截止日';

comment on column gab_dxzp_qhcx_sfqzxx.djjgmc is
'冻结机关名称';

comment on column gab_dxzp_qhcx_sfqzxx.bz is
'币种';

comment on column gab_dxzp_qhcx_sfqzxx.djje is
'冻结金额';

comment on column gab_dxzp_qhcx_sfqzxx.beiz is
'备注';

comment on column gab_dxzp_qhcx_sfqzxx.djcslx is
'冻结措施类型';

comment on column gab_dxzp_qhcx_sfqzxx.zwrq is
'gaps日期';

comment on column gab_dxzp_qhcx_sfqzxx.systime is
'gaps时间';

comment on column gab_dxzp_qhcx_sfqzxx.by1 is
'备用1';

comment on column gab_dxzp_qhcx_sfqzxx.by2 is
'备用2';

comment on column gab_dxzp_qhcx_sfqzxx.by3 is
'备用3';

/*==============================================================*/
/* Table: gab_dxzp_qhcx_zzhxx                                 */
/*==============================================================*/
comment on table gab_dxzp_qhcx_zzhxx is
'记录电信诈骗全户查询_子账号信息';

comment on column gab_dxzp_qhcx_zzhxx.ywsqbh is
'主键，请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_qhcx_zzhxx.rwxh is
'任务序号';

comment on column gab_dxzp_qhcx_zzhxx.zzhxh is
'子账户序号';

comment on column gab_dxzp_qhcx_zzhxx.zh is
'账（卡）号';

comment on column gab_dxzp_qhcx_zzhxx.zzhlb is
'子账户类别';

comment on column gab_dxzp_qhcx_zzhxx.zhzt is
'账户状态';

comment on column gab_dxzp_qhcx_zzhxx.bz is
'币种';

comment on column gab_dxzp_qhcx_zzhxx.chbz is
'钞汇标志';

comment on column gab_dxzp_qhcx_zzhxx.zhye is
'账户余额';

comment on column gab_dxzp_qhcx_zzhxx.kyye is
'可用余额';

comment on column gab_dxzp_qhcx_zzhxx.zhjysj is
'最后交易时间';

comment on column gab_dxzp_qhcx_zzhxx.zwrq is
'gaps日期';

comment on column gab_dxzp_qhcx_zzhxx.systime is
'gaps时间';

comment on column gab_dxzp_qhcx_zzhxx.by1 is
'备用1';

comment on column gab_dxzp_qhcx_zzhxx.by2 is
'备用2';

comment on column gab_dxzp_qhcx_zzhxx.by3 is
'备用3';

/*==============================================================*/
/* Table: gab_dxzp_qhcx_qlxx                                  */
/*==============================================================*/
comment on table gab_dxzp_qhcx_qlxx is
'记录电信诈骗全户查询_权利人信息';

comment on column gab_dxzp_qhcx_qlxx.ywsqbh is
'主键，请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_qhcx_qlxx.rwxh is
'任务序号';

comment on column gab_dxzp_qhcx_qlxx.xh is
'序号';

comment on column gab_dxzp_qhcx_qlxx.zh is
'账号';

comment on column gab_dxzp_qhcx_qlxx.kh is
'卡折号';

comment on column gab_dxzp_qhcx_qlxx.zjlx is
'证件类型代码';

comment on column gab_dxzp_qhcx_qlxx.zjhm is
'证件号码';

comment on column gab_dxzp_qhcx_qlxx.qllx is
'权利类型';

comment on column gab_dxzp_qhcx_qlxx.qlrxm is
'权利人姓名';

comment on column gab_dxzp_qhcx_qlxx.qlje is
'权利金额';

comment on column gab_dxzp_qhcx_qlxx.qlrtxdz is
'权利人通讯地址';

comment on column gab_dxzp_qhcx_qlxx.qlrlxfs is
'权利人联系方式';

comment on column gab_dxzp_qhcx_qlxx.zwrq is
'gaps日期';

comment on column gab_dxzp_qhcx_qlxx.systime is
'gaps时间';

comment on column gab_dxzp_qhcx_qlxx.by1 is
'备用1';

comment on column gab_dxzp_qhcx_qlxx.by2 is
'备用2';

comment on column gab_dxzp_qhcx_qlxx.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_dtcx_resp                                  */
/*==============================================================*/
comment on table gab_dxzp_dtcx_resp is
'记录电信诈骗 动态查询响应';

comment on column gab_dxzp_dtcx_resp.sbpch is
'上报批次号';

comment on column gab_dxzp_dtcx_resp.sbpcxh is
'上报批次序号';

comment on column gab_dxzp_dtcx_resp.ywsqbh is
'主键，请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_dtcx_resp.rwxh is
'任务序号';

comment on column gab_dxzp_dtcx_resp.zhm is
'账户名';

comment on column gab_dxzp_dtcx_resp.zh is
'账号';

comment on column gab_dxzp_dtcx_resp.jylx is
'交易类型';

comment on column gab_dxzp_dtcx_resp.jdbz is
'借贷标志';

comment on column gab_dxzp_dtcx_resp.bz is
'币种';

comment on column gab_dxzp_dtcx_resp.jyje is
'交易金额';

comment on column gab_dxzp_dtcx_resp.jyye is
'交易余额';

comment on column gab_dxzp_dtcx_resp.jysj is
'交易时间';

comment on column gab_dxzp_dtcx_resp.jylsh is
'交易流水号';

comment on column gab_dxzp_dtcx_resp.jydfmc is
'交易对方名称';

comment on column gab_dxzp_dtcx_resp.jydfzh is
'交易对方账号';

comment on column gab_dxzp_dtcx_resp.jydfzjhm is
'交易对方证件号码';

comment on column gab_dxzp_dtcx_resp.jydfzhkhh is
'交易对方账号开户行';

comment on column gab_dxzp_dtcx_resp.jyzy is
'交易摘要';

comment on column gab_dxzp_dtcx_resp.jywdmc is
'交易网点名称';

comment on column gab_dxzp_dtcx_resp.jywddm is
'交易网点代码';

comment on column gab_dxzp_dtcx_resp.rzh is
'日志号';

comment on column gab_dxzp_dtcx_resp.cph is
'传票号';

comment on column gab_dxzp_dtcx_resp.pzzl is
'凭证种类';

comment on column gab_dxzp_dtcx_resp.pzh is
'凭证号';

comment on column gab_dxzp_dtcx_resp.xjbz is
'现金标志';

comment on column gab_dxzp_dtcx_resp.zdh is
'终端号';

comment on column gab_dxzp_dtcx_resp.jysfcg is
'交易是否成功';

comment on column gab_dxzp_dtcx_resp.jyfsd is
'交易发生地';

comment on column gab_dxzp_dtcx_resp.shmc is
'商户名称';

comment on column gab_dxzp_dtcx_resp.shh is
'商户号';

comment on column gab_dxzp_dtcx_resp.ip is
'ip地址';

comment on column gab_dxzp_dtcx_resp.mac is
'mac地址';

comment on column gab_dxzp_dtcx_resp.jygyh is
'交易柜员号';

comment on column gab_dxzp_dtcx_resp.beiz is
'备注';

comment on column gab_dxzp_dtcx_resp.fksm is
'反馈说明';

comment on column gab_dxzp_dtcx_resp.fkjgmc is
'反馈机构名称';

comment on column gab_dxzp_dtcx_resp.zwrq is
'gaps日期';

comment on column gab_dxzp_dtcx_resp.systime is
'gaps时间';

comment on column gab_dxzp_dtcx_resp.by1 is
'备用1';

comment on column gab_dxzp_dtcx_resp.by2 is
'备用2';

comment on column gab_dxzp_dtcx_resp.by3 is
'备用3';

/*==============================================================*/
/* Table: gab_dxzp_dtjc_resp                                  */
/*==============================================================*/
comment on table gab_dxzp_dtjc_resp is
'记录电信诈骗动态解除响应';

comment on column gab_dxzp_dtjc_resp.ywsqbh is
'主键，请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_dtjc_resp.rwxh is
'任务序号';

comment on column gab_dxzp_dtjc_resp.jcdtcxsm is
'解除动态查询说明';

comment on column gab_dxzp_dtjc_resp.fksm is
'反馈说明';

comment on column gab_dxzp_dtjc_resp.zwrq is
'gaps日期';

comment on column gab_dxzp_dtjc_resp.systime is
'gaps时间';

comment on column gab_dxzp_dtjc_resp.by1 is
'备用1';

comment on column gab_dxzp_dtjc_resp.by2 is
'备用2';

comment on column gab_dxzp_dtjc_resp.by3 is
'备用3';

/*==============================================================*/
/* Table: gab_dxzp_ztcx_resp                                    */
/*==============================================================*/
comment on table gab_dxzp_ztcx_resp is
'记录电信诈骗持卡主体查询响应';

comment on column gab_dxzp_ztcx_resp.ywsqbh is
'主键，请求单流水号，用于标识查控请求单';

comment on column gab_dxzp_ztcx_resp.rwxh is
'任务序号';

comment on column gab_dxzp_ztcx_resp.fkjgmc is
'反馈机构名称';

comment on column gab_dxzp_ztcx_resp.fksm is
'查询反馈说明';

comment on column gab_dxzp_ztcx_resp.zjlx is
'查询证照类型代码';

comment on column gab_dxzp_ztcx_resp.zjhm is
'查询证照号码';

comment on column gab_dxzp_ztcx_resp.ztmc is
'查询主体名称';

comment on column gab_dxzp_ztcx_resp.lxsj is
'联系手机';

comment on column gab_dxzp_ztcx_resp.dbrxm is
'账/卡代办人姓名';

comment on column gab_dxzp_ztcx_resp.dbrzjlx is
'账/卡代办人证件类型';

comment on column gab_dxzp_ztcx_resp.dbrzjhm is
'账/卡代办人证件号码';

comment on column gab_dxzp_ztcx_resp.zzdz is
'住宅地址';

comment on column gab_dxzp_ztcx_resp.zzdh is
'住宅电话';

comment on column gab_dxzp_ztcx_resp.gzdw is
'工作单位';

comment on column gab_dxzp_ztcx_resp.dwdz is
'单位地址';

comment on column gab_dxzp_ztcx_resp.dwdh is
'单位电话';

comment on column gab_dxzp_ztcx_resp.yxdz is
'邮箱地址';

comment on column gab_dxzp_ztcx_resp.frdb is
'法人代表';

comment on column gab_dxzp_ztcx_resp.frdbzjlx is
'法人代表证件类型';

comment on column gab_dxzp_ztcx_resp.frdbzjhm is
'法人代表证件号码';

comment on column gab_dxzp_ztcx_resp.khgszzhm is
'客户工商执照号码';

comment on column gab_dxzp_ztcx_resp.gsnsh is
'国税纳税号';

comment on column gab_dxzp_ztcx_resp.dsnsh is
'地税纳税号';

comment on column gab_dxzp_ztcx_resp.zwrq is
'gaps日期';

comment on column gab_dxzp_ztcx_resp.systime is
'gaps时间';

comment on column gab_dxzp_ztcx_resp.by1 is
'备用1';

comment on column gab_dxzp_ztcx_resp.by2 is
'备用2';

comment on column gab_dxzp_ztcx_resp.by3 is
'备用3';


comment on table gab_dxzp_kzhzh is
'卡账号综合信息表';

comment on column gab_dxzp_kzhzh.zh is
'账号';

comment on column gab_dxzp_kzhzh.kh is
'卡号';

comment on column gab_dxzp_kzhzh.zhmc is
'账户名';

comment on column gab_dxzp_kzhzh.dccs is
'动查次数';

comment on column gab_dxzp_kzhzh.dczt is
'0-动查  1-解除';

comment on column gab_dxzp_kzhzh.dcywsqbh is
'动查最新业务号';

comment on column gab_dxzp_kzhzh.dcqssj is
'动查起始时间';

comment on column gab_dxzp_kzhzh.dcjssj is
'动查结束时间';

comment on column gab_dxzp_kzhzh.djcs is
'冻结次数';

comment on column gab_dxzp_kzhzh.djzt is
'0-冻结  1-解除 2-续冻 9-初始';

comment on column gab_dxzp_kzhzh.djljje is
'冻结累计金额';

comment on column gab_dxzp_kzhzh.djywsqbh is
'冻结最新业务号';

comment on column gab_dxzp_kzhzh.djqssj is
'冻结起始时间';

comment on column gab_dxzp_kzhzh.djjssj is
'冻结结束时间';

comment on column gab_dxzp_kzhzh.zfcs is
'0-止付  1-解除 2-续止  9-初始';

comment on column gab_dxzp_kzhzh.zfzt is
'止付状态';

comment on column gab_dxzp_kzhzh.zfljje is
'止付累计金额';

comment on column gab_dxzp_kzhzh.zfywsqbh is
'止付最新业务号';

comment on column gab_dxzp_kzhzh.zfqssj is
'止付起始时间';

comment on column gab_dxzp_kzhzh.zfjssj is
'止付结束时间';

comment on column gab_dxzp_kzhzh.khcs is
'扣划次数';

comment on column gab_dxzp_kzhzh.khljje is
'扣划累计金额';

comment on column gab_dxzp_kzhzh.khywsqbh is
'扣划最新业务号';

comment on column gab_dxzp_kzhzh.by1 is
'备用1';

comment on column gab_dxzp_kzhzh.by2 is
'备用2';

comment on column gab_dxzp_kzhzh.by3 is
'备用3';


/*==============================================================*/
/* Table: gab_dxzp_smjfj                                        */
/*==============================================================*/
comment on table gab_dxzp_smjfj is
'记录法律文书、协查民警证件扫描件等附件信息';

comment on column gab_dxzp_smjfj.ywsqbh is
'业务申请编号';

comment on column gab_dxzp_smjfj.xh is
'序号';

comment on column gab_dxzp_smjfj.wjm is
'文件名';

comment on column gab_dxzp_smjfj.wjdx is
'文件大小';

comment on column gab_dxzp_smjfj.yxjz is
'影像健值';

comment on column gab_dxzp_smjfj.zwrq is
'gaps日期';

comment on column gab_dxzp_smjfj.systime is
'gaps时间';

comment on column gab_dxzp_smjfj.by1 is
'备用1';

comment on column gab_dxzp_smjfj.by2 is
'备用2';

comment on column gab_dxzp_smjfj.by3 is
'备用3';
