##########################################################################
# 版权所有:杭州恒生电子股份有限公司
# 项目名称:综合应用前置（GAPS）项目
# 版    本:V4.0
# 操作系统:AIX5.3
# 文件描述:函数组件动态连接库通用MAKEFILE
# 数 据 库:
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
###########################################################################
INCLUDE=-I${HOME}/app/agent/incl -I${HOME}/app/batch/incl -I${HOME}/app/app/incl
#APPEH_INCL=include=${HOME}/app/agent/incl include=${HOME}/app/batch/incl include=${HOME}/app/app/incl
APPLIBDIR=-L${HOME}/app/agent/lib
###########################################################################
DEBUG=${MOS} -DBUILDDATETIME=\"$(BUILDDATETIME)\"
CC=cc ${OS_CCFLAG}
VPATH=.libs
all:APP_COMPANY.so APP_SXF.so APP_CUSTOM.so
.SUFFIXES:  .c .lo
.c.lo:
	#libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${DBS} ${MOS} ${DB_CCFLAGS} ${CCFLAG} -I$(LIBINCL) -I${INCL} $(INCLUDE) -c $<
	libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${MOS} ${CCFLAG} -I$(LIBINCL) -I${INCL} $(INCLUDE) -c $<

libfprv_app.la: fprv_app.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG} ${OS_LDFLAG} -g -O -o libfprv_app.la fprv_app.lo -rpath ${LIBDIR}  -release ${RELEASE_VERSION} -no-undefined -export-dynamic -L${LIBDIR} ${APPLIBDIR} -lsxml -lhsbase
	libtool --mode=install install-sh -c libfprv_app.la ${LIBDIR}/libfprv_app.la

APP_PUB.so: APP_PUB.lo 
#	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lfprv_app
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lfprv_app
	install-shlib.sh APP_PUB.la   ${SHLIBDIR} upd
        
APP_CUSTOM.so: APP_CUSTOM.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lfprv_app
	install-shlib.sh APP_CUSTOM.la   ${SHLIBDIR} upd
        
APP_YWGL.so: APP_YWGL.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lfprv_app
	install-shlib.sh APP_YWGL.la   ${SHLIBDIR} upd
        
APP_SXF.so: APP_SXF.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lfprv_app
	install-shlib.sh APP_SXF.la   ${SHLIBDIR} upd
        
APP_TASK.so: APP_TASK.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lfprv_app
	install-shlib.sh APP_TASK.la   ${SHLIBDIR} upd
        
APP_COMPANY.so: APP_COMPANY.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc  -lfprv_app
	install-shlib.sh APP_COMPANY.la   ${SHLIBDIR} upd

APP_COMPEX.so: APP_COMPEX.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc  -lfprv_app
	install-shlib.sh APP_COMPEX.la   ${SHLIBDIR} upd

clean:
	@rm -rf .libs *.lo *.la *.lis fprv_app.o APP_PUB.o APP_CUSTOM.o APP_YWGL.o APP_TASK.o APP_COMPANY.o APP_SXF.o APP_COMPEX.o
	
