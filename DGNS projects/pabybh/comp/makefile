##########################################################################
# ��Ȩ���У����ݺ������ӹɷ����޹�˾
# ��Ŀ���ƣ��ۺ�Ӧ��ǰ�ã�GAPS����Ŀ
# ��    ����V1.0
# ����ϵͳ��AIX4.3
# �ļ����������������̬���ӿ�ͨ��MAKEFILE
# �� �� ��: ORACLE
##########################################################################
# �޸ļ�¼
# �޸�����:
# �޸�����:
# �޸���:
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
all :PABYBH_SERIAL.so PABYBH_SIGNCHK.so PABYBH_CHECK.so PABYBH_HOSTCHECK.so PABYBH_JMJ.so PABYBH_PUB.so
.SUFFIXES:  .c .lo

.c.lo:
	libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${DBS} ${MOS} ${DB_CCFLAGS} ${CCFLAG} -I$(LIBINCL) -I${INCL} -c $< 
		
uninstall: 
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/PABYBH_*.so

PABYBH_SERIAL.so: PABYBH_SERIAL.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc
	install-shlib.sh PABYBH_SERIAL.la   ${SHLIBDIR} upd

PABYBH_SIGNCHK.so: PABYBH_SIGNCHK.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc
	install-shlib.sh PABYBH_SIGNCHK.la   ${SHLIBDIR} upd

PABYBH_CHECK.so: PABYBH_CHECK.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc
	install-shlib.sh PABYBH_CHECK.la   ${SHLIBDIR} upd

PABYBH_HOSTCHECK.so: PABYBH_HOSTCHECK.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc
	install-shlib.sh PABYBH_HOSTCHECK.la   ${SHLIBDIR} upd

PABYBH_JMJ.so: PABYBH_JMJ.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc
	install-shlib.sh PABYBH_JMJ.la   ${SHLIBDIR} upd

PABYBH_PUB.so: PABYBH_PUB.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc
	install-shlib.sh PABYBH_PUB.la   ${SHLIBDIR} upd



clean:
	@rm -f lib*.a *~ *core *.lo *.o *.la *.lis tp*
	@rm -rf .libs
cleantp:
	@rm -f tp*
##########################################################################