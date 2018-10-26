#
# 用libtool工具编译目标系统
# 以 gaps_userfreg.c     ufunc_sample.c   ==>生成libgapsfuncapp.a
include ${HOME}/src/etc/makefile.${GAPSPLATFORM}
OBJS=gaps_userfreg.o ufunc_sample.o 
LO_OBJS=gaps_userfreg.lo ufunc_sample.lo 
RELEASE_VERSION=1.0.1
LIBDIR=${HOME}/lib
BINDIR=${HOME}/bin
LIBINCL=${HOME}/libincl
INCLUDE=${HOME}/include
DEBUG=${MOS} 
CC=cc ${OS_CCFLAG}
INCLUDE=-I./ -I${HOME}/incl -I${HOME}/libincl 
LIB=-L${HOME}/lib -lsxml -lhsbase

all:libgapsfuncapp.la

install: libgapsfuncapp.la
	libtool --mode=install install-sh -c libgapsfuncapp.la ${LIBDIR}/libgapsfuncapp.la
	
uninstall: ${LIBDIR}/libgapsfuncapp.la
	libtool --mode=uninstall /bin/rm ${LIBDIR}/libgapsfuncapp.la

gaps_userfreg.o: gaps_userfreg.c
	libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${CCFLAG} ${INCLUDE} -c gaps_userfreg.c 

ufunc_sample.o: ufunc_sample.c
	libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${CCFLAG} ${INCLUDE} -c ufunc_sample.c

libgapsfuncapp.la: $(OBJS)
	libtool --mode=link --tag=CC ${CC} ${LDFLAG} ${OS_LDFLAG} ${LIB} -g -O -o libgapsfuncapp.la $(LO_OBJS) -rpath ${LIBDIR}  -release ${RELEASE_VERSION} -no-undefined -export-dynamic

clean:
	@rm -f lib*.a *~ *core *.lo *.o *.la *.loT
	@rm -rf .libs
