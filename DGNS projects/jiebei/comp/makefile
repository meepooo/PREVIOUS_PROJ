
include ${HOME}/src/etc/makefile.${GAPSPLATFORM}
#include ${HOME}/src/etc/${DB}/makefile.${DB}
##########################################################################
DATE=`date +"%Y%m%d%H%M"`
BUILDDATETIME=$(DATE)
RELEASE_VERSION=1.0.0
LIBDIR=${HOME}/lib
SHLIBDIR=${HOME}/shlib
BINDIR=${HOME}/bin
LIBINCL=${HOME}/libincl
INCL=${HOME}/incl
###########################################################################
INCLUDE=-I./ -I${AGENT_HOME}/agent/incl64 -I${AGENT_HOME}/batch/incl64 -I${AGENT_HOME}/app/incl64
APPEH_INCL=include=${AGENT_HOME}/agent/incl64 include=${AGENT_HOME}/batch/incl64 include=${AGENT_HOME}/app/incl64
###########################################################################
DEBUG=${MOS} -DBUILDDATETIME=\"$(BUILDDATETIME)\"
#CC=cc ${OS_CCFLAG} -fprofile-arcs -ftest-coverage
CC=cc ${OS_CCFLAG} 
VPATH=.libs
all:  ICPS_JB_FILE.so ICPS_JB_SERIAL.so ICPS_JB_CHK.so ICPS_JB_APPLY.so 
.SUFFIXES:  .c .lo
.c.lo:
	libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${MOS} ${CCFLAG} -I$(LIBINCL) -I${INCL} $(INCLUDE) -c $<

ICPS_JB_FILE.so: ICPS_JB_FILE.lo app_dbop.lo fprv_file.lo fprv_file_jiebei.lo fprv_pub.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc 
	install-shlib.sh ICPS_JB_FILE.la ${SHLIBDIR} upd

ICPS_JB_SERIAL.so: ICPS_JB_SERIAL.lo app_dbop.lo fprv_pub.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc 
	install-shlib.sh ICPS_JB_SERIAL.la ${SHLIBDIR} upd
        
ICPS_JB_CHK.so: ICPS_JB_CHK.lo app_dbop.lo fprv_pub.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc 
	install-shlib.sh ICPS_JB_CHK.la ${SHLIBDIR} upd

ICPS_JB_APPLY.so: ICPS_JB_APPLY.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc
	install-shlib.sh ICPS_JB_APPLY.la ${SHLIBDIR} upd
	
clean:
	rm -rf .libs *.lo *.la *.lis *.o
