
INSERT INTO APP_YYXX VALUES ('037', 'jiebei', '借呗', '', '', '20180725', '1.0.0.0', '', '', 'zdd', 'zdd', '0', '', '', '', '');
INSERT INTO APP_QDXX VALUES ('311', 'sysicps', '借呗渠道', '1', null, null, '0', '0', '00000', 'admin', '20171118105555', null, null, '0');

INSERT INTO APP_JYXX (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ) VALUES ('702500', '借呗获取日终文件', '037', '0', '0', '0', '0', '1', '00000', 'admin', '20171118105555', null, null, '0');
INSERT INTO APP_JYXX (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ) VALUES ('702501', '借呗日终对账', '037', '0', '0', '0', '0', '1', '00000', 'admin', '20171118105555', null, null, '0');
INSERT INTO APP_JYXX (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ) VALUES ('702511', '借呗授信申请', '037', '0', '0', '0', '0', '1', '00000', 'admin', '20171118105555', null, null, '0');
INSERT INTO APP_JYXX (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ) VALUES ('702512', '借呗机构初审', '037', '0', '0', '0', '0', '1', '00000', 'admin', '20171118105555', null, null, '0');
INSERT INTO APP_JYXX (JYDM, JYMC, YYBS, JYLX, LSJLBZ, RZBZ, BBBZ, CPXG, WHJG, WHGY, WHSJ, EXTFLD1, EXTFLD2, QTBZ) VALUES ('702513', '借呗终审确认', '037', '0', '0', '0', '0', '1', '00000', 'admin', '20171118105555', null, null, '0');

INSERT INTO APP_CSKZ (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ) VALUES ('K_ICPS_JIEB_SFTP_PRT', '2', '037', '/icps/cskz/jieb_get_port', '22', '借呗远程SFTP端口', '0', '00000', 'admin', null);
INSERT INTO APP_CSKZ (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ) VALUES ('K_ICPS_JIEB_SFTP_PWD', '2', '037', '/icps/cskz/jieb_get_passwd', '123456', '借呗远程SFTP密码', '0', '00000', 'admin', null);
INSERT INTO APP_CSKZ (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ) VALUES ('K_ICPS_JIEB_SFTP_USR', '2', '037', '/icps/cskz/jieb_get_user', 'loanplat', '借呗远程SFTP用户名', '0', '00000', 'admin', null);
INSERT INTO APP_CSKZ (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ) VALUES ('K_ICPS_JIEB_SFTP_ADR', '2', '037', '/icps/cskz/jieb_get_addr', '115.124.16.69', '借呗远程SFTP地址', '0', '00000', 'admin', null);
INSERT INTO APP_CSKZ (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ) VALUES ('K_ICPS_JIEB_FILEPATH', '2', '037', '/icps/cskz/jieb_remotefile_path', '/download/accounting', '借呗远程SFTP文件目录', '0', '00000', 'admin', null);
INSERT INTO APP_CSKZ (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ) VALUES ('K_ICPS_JB_MPPLISDS', '2', '037', '/icps/cskz/jieb_mpp_lisds', 'MPP_liSDS', '借呗MPP异步服务名', '0', '00000', 'admin', '20171118105555');
INSERT INTO APP_CSKZ (CSJZ, CSLX, CSTJ, JDM, JDZ, REMARK, JZLX, WHJG, WHGY, WHSJ) VALUES ('K_ICPS_JB_CALLCHK', '2', '037', '/icps/cskz/jieb_call_chk', '1', '借呗联动对账0否 1是', '0', '00000', 'admin', '20171118105555');

