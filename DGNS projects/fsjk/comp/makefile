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
all :FSJK_CHK.so
.SUFFIXES:  .c .lo

.c.lo:
	libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${DBS} ${MOS} ${DB_CCFLAGS} ${CCFLAG} -I$(LIBINCL) -I${INCL} -c $< 
		
uninstall: 
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/FSJK_*.so

FSJK_CHK.so: FSJK_CHK.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc
	install-shlib.sh FSJK_CHK.la   ${SHLIBDIR} upd


clean:
	@rm -f lib*.a *~ *core *.lo *.o *.la *.lis tp*
	@rm -rf .libs
cleantp:
	@rm -f tp*
##########################################################################
