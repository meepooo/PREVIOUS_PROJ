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
comment on column gab_dxzp_xdxx.gaywsqbh is
'公安业务申请编号';
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
