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
all : AGT_PTGL.so AGT_WIAMP.so 
.SUFFIXES:  .c .lo
.c.lo:
	libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${DBS} ${MOS} ${DB_CCFLAGS} ${CCFLAG} -I$(LIBINCL) -I${INCL} $(INCLUDE) -c $<
AGT_PTGL.so: AGT_PTGL.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lfprv_app
	install-shlib.sh AGT_PTGL.la   ${SHLIBDIR} upd
AGT_WIAMP.so: AGT_WIAMP.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lfprv_app
	install-shlib.sh AGT_WIAMP.la ${SHLIBDIR} upd
        
clean:
	@rm -rf .libs *.lo *.la *.lis fprv_agent.o AGT_PUB.o AGT_CUSTOM.o AGT_PTGL.o AGT_RZZT.o AGT_PQUERY.o  AGT_REPORT.o AGT_YWCL.o AGT_WIAMP.o
