##########################################################################
# 版权所有：杭州恒生电子股份有限公司
# 项目名称：综合应用前置（GAPS）项目
# 版    本：V1.0
# 操作系统：AIX4.3
# 文件描述：函数组件动态连接库通用MAKEFILE
# 数 据 库: ORACLE
##########################################################################
# 修改记录
# 修改日期:
# 修改内容:
# 修改人:
##########################################################################
include ${HOME}/src/etc/makefile.${GAPSPLATFORM}
include ${HOME}/src/etc/${DB}/makefile.${DB}
##########################################################################
DATE=`date +"%Y%m%d%H%M"`
BUILDDATETIME=$(DATE)
RELEASE_VERSION=4.0.0
LIBDIR=${HOME}/lib
SHLIBDIR=${HOME}/shlib
BINDIR=${HOME}/bin
LIBINCL=${HOME}/libincl
INCL=${HOME}/incl

DEBUG=${MOS} -DBUILDDATETIME=\"$(BUILDDATETIME)\"
CC=cc ${OS_CCFLAG}

VPATH=.libs
all :SYW_TIPS.so SYW_TIPS_BATCH.so SYW_TIPS_BILL.so SYW_TIPS_CHKACCT.so \
	SYW_TIPS_ONLINE.so SYW_TIPS_REPORT.so SYW_TIPS_FUNDRT.so SYW_TIPS_PQUERY.so SYW_TIPS_GENZHQZLSH_EH.so
.SUFFIXES:  .c .lo

.c.lo:
	libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${DBS} ${MOS} ${DB_CCFLAGS} ${CCFLAG} -I$(LIBINCL) -I${INCL} -c $<
		
uninstall: 
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SYW_TIPS.so ${SHLIBDIR}/SYW_TIPS-*.so
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SYW_TIPS_BATCH.so ${SHLIBDIR}/SYW_TIPS_BATCH-*.so
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SYW_TIPS_BILL.so ${SHLIBDIR}/SYW_TIPS_BILL-*.so
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SYW_TIPS_CHKACCT.so ${SHLIBDIR}/SYW_TIPS_CHKACCT-*.so
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SYW_TIPS_ONLINE.so ${SHLIBDIR}/SYW_TIPS_ONLINE-*.so
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SYW_TIPS_REPORT.so ${SHLIBDIR}/SYW_TIPS_REPORT-*.so
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SYW_TIPS_FUNDRT.so ${SHLIBDIR}/SYW_TIPS_FUNDRT-*.so
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SYW_TIPS_PQUERY.so ${SHLIBDIR}/SYW_TIPS_PQUERY-*.so

SYW_TIPS.so: SYW_TIPS.lo SYW_TIPS_PUBLIC.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -ltips$(OBJECT_MODE)
	install-shlib.sh SYW_TIPS.la   ${SHLIBDIR} upd

SYW_TIPS_BATCH.so: SYW_TIPS_BATCH.lo SYW_TIPS_PUBLIC.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lbsd
	install-shlib.sh SYW_TIPS_BATCH.la   ${SHLIBDIR} upd

SYW_TIPS_BILL.so: SYW_TIPS_BILL.lo SYW_TIPS_PUBLIC.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lbsd -lm
	install-shlib.sh SYW_TIPS_BILL.la   ${SHLIBDIR} upd

SYW_TIPS_CHKACCT.so: SYW_TIPS_CHKACCT.lo SYW_TIPS_PUBLIC.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lbsd
	install-shlib.sh SYW_TIPS_CHKACCT.la   ${SHLIBDIR} upd

SYW_TIPS_ONLINE.so: SYW_TIPS_ONLINE.lo SYW_TIPS_PUBLIC.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc
	install-shlib.sh SYW_TIPS_ONLINE.la   ${SHLIBDIR} upd

SYW_TIPS_REPORT.so: SYW_TIPS_REPORT.lo SYW_TIPS_PUBLIC.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc
	install-shlib.sh SYW_TIPS_REPORT.la   ${SHLIBDIR} upd

SYW_TIPS_FUNDRT.so: SYW_TIPS_FUNDRT.lo SYW_TIPS_PUBLIC.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lbsd
	install-shlib.sh SYW_TIPS_FUNDRT.la   ${SHLIBDIR} upd
	
SYW_TIPS_PQUERY.so: SYW_TIPS_PQUERY.lo SYW_TIPS_PUBLIC.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lbsd
	install-shlib.sh SYW_TIPS_PQUERY.la   ${SHLIBDIR} upd

SYW_TIPS_GENZHQZLSH_EH.so: SYW_TIPS_GENZHQZLSH_EH.lo SYW_TIPS_PUBLIC.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lbsd
	install-shlib.sh SYW_TIPS_GENZHQZLSH_EH.la   ${SHLIBDIR} upd

clean:
	@rm -f lib*.a *~ *core *.lo *.o *.la *.lis tp*
	@rm -rf .libs
cleantp:
	@rm -f tp*
##########################################################################
