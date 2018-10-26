#
# 用libtool工具编译目标系统
# 以 SETC.c   ==>生成SETC.so
include ${HOME}/src/etc/makefile.${GAPSPLATFORM}
DATE=`date +"%Y%m%d%H%M"`
BUILDDATETIME=$(DATE)
RELEASE_VERSION=4.0.1
LIBDIR=${HOME}/lib -L${HOME}/sqlite/lib
SHLIBDIR=${HOME}/shlib
BINDIR=${HOME}/bin
LIBINCL=${HOME}/libincl
INCLUDE=${HOME}/incl -I${HOME}/sqlite/include
DEBUG=${MOS} -DBUILDDATETIME=\"$(BUILDDATETIME)\"
CC=cc ${OS_CCFLAG}
VPATH=.libs

all:SSERIAL.so STRAC_DEMO.so SEXTRA_CleanYCJY.so

.SUFFIXES:
.SUFFIXES: .c .lo
.c.lo:
	libtool --mode=compile --tag=CC ${CC} -g -O $(DEBUG) $(CCFLAG) -I$(LIBINCL) -I$(INCLUDE) -c $<

install:
	install-shlib.sh SSERIAL.la   ${SHLIBDIR}
	install-shlib.sh STRAC_DEMO.la   ${SHLIBDIR}
	install-shlib.sh SEXTRA_CleanYCJY.la   ${SHLIBDIR}
	
	
uninstall: 
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SSERIAL.so ${SHLIBDIR}/SSERIAL-*.so 


SSERIAL.so: SSERIAL.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG} ${OS_LDFLAG} -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release 4.0.1 -export-dynamic -no-undefined -module -L${LIBDIR} -lgapssfs -ldci -lhsbase -lsxml
	install-shlib.sh SSERIAL.la   ${SHLIBDIR} 

STRAC_DEMO.so: STRAC_DEMO.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG} ${OS_LDFLAG} -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release 4.0.1 -export-dynamic -no-undefined -module -L${LIBDIR} -lgapssfs -ldci -lhsbase -lsha
	install-shlib.sh STRAC_DEMO.la   ${SHLIBDIR} 

SEXTRA_CleanYCJY.so: SEXTRA_CleanYCJY.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG} ${OS_LDFLAG} -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release 4.0.0 -export-dynamic -no-undefined -module -L${LIBDIR} -lsqlite3 -lsxml -lhsbase -lgapssfs -ldci
	install-shlib.sh SEXTRA_CleanYCJY.la   ${SHLIBDIR}

clean:
	@rm -f lib*.a *~ *core *.lo *.o *.la 
	@rm -rf .libs
