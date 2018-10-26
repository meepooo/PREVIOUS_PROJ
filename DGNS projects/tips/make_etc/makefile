include ${HOME}/src/etc/makefile.${GAPSPLATFORM}

DATE=`date +%Y%m%d%H%M`
LIBDIR=-L${HOME}/lib 

#使用MPP方式连接SDS
LINK=-lhsbase -lsxml -lcommanz_MPP -lchannel
#使用MQ方式连接SDS
#LINK=-lhsbase -lsxml -lcommanz_MQ -lchannel -laresmq

LIBINCL=-I${HOME}/libincl -I${HOME}/incl -I./ -I${HOME}/include 
BINDIR=${HOME}/bin
DEBUG=${MOS} -DDEBUG -DBUILDNO=\"${DATE}\"
CC=cc ${OS_CCFLAG}

all: cs_TIPSJR

install:
	cp cs_TIPSJR ${BINDIR} 

uninstall:
	rm -f ${BINDIR}/cs_TIPSJR

cs_TIPSJR: cs_TIPSJR.c
	${CC} -g cs_TIPSJR.c -o cs_TIPSJR ${DEBUG} ${CCFLAG} ${LDFLAG} ${LIBINCL} ${LIBDIR} ${LINK}


simcli_TIPSJR: simcli_TIPSJR.c
	${CC} -g simcli_TIPSJR.c -o simcli_TIPSJR ${DEBUG} ${CCFLAG} ${LDFLAG} ${LIBINCL} ${LIBDIR} ${LINK}

clean:
	rm -f cs_TIPSJR
