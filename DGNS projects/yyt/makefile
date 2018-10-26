#
# 用libtool工具编译目标系统
# 以 SESB_DOTRANS.c  ==>生成DRC_esb.so
include ${HOME}/src/etc/makefile.${GAPSPLATFORM}
DATE=`date +"%Y%m%d%H%M"`
BUILDDATETIME=$(DATE)
RELEASE_VERSION=4.0.2
LIBDIR=${HOME}/lib -L${HOME}/libevent/lib -L${HOME}/sqlite/lib
SHLIBDIR=${HOME}/shlib
BINDIR=${HOME}/bin
LIBINCL=${HOME}/libincl -I${HOME}/libevent/include -I${HOME}/sqlite/include
INCLUDE=${HOME}/incl
DEBUG=${MOS} -DBUILDDATETIME=\"$(BUILDDATETIME)\"
CC=cc ${OS_CCFLAG}
VPATH=.libs

all:clean DRC_esb.so

.SUFFIXES:
.SUFFIXES: .c .lo
.c.lo:
	libtool --mode=compile --tag=CC ${CC} -g -O $(DEBUG) $(CCFLAG) -I$(LIBINCL) -I$(INCLUDE) -c $<

install:
	install-shlib.sh DRC_esb.la   ${SHLIBDIR}
	
uninstall: 
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/DRC_esb.so ${SHLIBDIR}/DRC_esb-*.so 

DRC_esb.so: DATA_DELNUMNODE.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG} ${OS_LDFLAG} -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module
	install-shlib.sh DRC_esb.la    ${SHLIBDIR} 
	SOAtool upd $@

clean:
	@rm -f lib*.a *~ *core *.lo *.o *.la 
	@rm -rf .libs
