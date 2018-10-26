##########################################################################
# 版权所有：杭州恒生电子股份有限公司
# 项目名称：综合应用前置（GAPS）项目
# 版    本：V1.0
# 操作系统：AIX4.3
# 文件描述：函数组件动态连接库通用MAKEFILE
# 数 据 库:Informix 7(64)
##########################################################################
# 修改记录
# 修改日期:
# 修改内容:
# 修改人:
##########################################################################
include ${HOME}/src/etc/makefile.${GAPSPLATFORM}
include ${HOME}/src/etc/${DB}/makefile.${DB}
##########################################################################
LO_OBJS=SCOMM_CALLGXP.o
DATE=`date +"%Y%m%d%H%M"`
BUILDDATETIME=$(DATE)
RELEASE_VERSION=4.0.0
LIBDIR=${HOME}/lib -L${HOME}/libevent/lib -L${HOME}/sqlite/lib ${DB_LIBS}
SHLIBDIR=${HOME}/shlib
BINDIR=${HOME}/bin
LIBINCL=${HOME}/libincl -I${HOME}/libevent/include -I${HOME}/sqlite/include
INCLUDE=${HOME}/incl
#APPEH_INCL用法(在oracle用户下，加入ec文件所需头文件查找路径，格式为include=${HOME}/app/***/include)
APPEH_INCL=
DEBUG=${MOS} -DBUILDDATETIME=\"$(BUILDDATETIME)\"
CC=cc -m64
VPATH=.libs
all : DRC_BASE64.so DRCESB_PUB.so FILE_LineToDesToBase64.so DRC_GETMD5.so
.SUFFIXES:  .c .lo

.c.lo:
	libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${DBS} ${MOS} ${DB_CCFLAGS} ${CCFLAG} -I$(LIBINCL) -I$(INCLUDE) -c $<

#将编译好的动态库从.libs目录copy到shlib目录，并备份原库文件
#install-shlib.sh ***.la   ${SHLIBDIR}后面如果加参数upd 即执行SOAtool upd ***.so,不加就不会刷新只拷贝
install:
	install-shlib.sh DRCESB_PUB.la   ${SHLIBDIR}
	install-shlib.sh FILE_LineToDesToBase64.la   ${SHLIBDIR}
	install-shlib.sh DRC_GETMD5.la   ${SHLIBDIR}

uninstall:
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/DRCESB_PUB.so ${SHLIBDIR}/DRCESB_PUB-*.so
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/DRCESB_PUB.so ${SHLIBDIR}/FILE_LineToDesToBase64.so
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/DRC_GETMD5.so ${SHLIBDIR}/DRC_GETMD5.so
	
DRCESB_PUB.so: DRCESB_PUB.lo DRCESB_MD5.lo DRCESB_des.lo DRCESB_FTP.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lssl
	install-shlib.sh DRCESB_PUB.la   ${SHLIBDIR} upd

FILE_LineToDesToBase64.so: FILE_LineToDesToBase64.lo DRCESB_des.lo base64.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci
	install-shlib.sh FILE_LineToDesToBase64.la   ${SHLIBDIR} upd

DRC_BASE64.so: DRC_BASE64.lo DRCESB_des.lo base64.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci
	install-shlib.sh DRC_BASE64.la   ${SHLIBDIR} upd

DRC_GETMD5.so: DRC_GetMd5.lo DRCESB_MD5.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci
	install-shlib.sh DRC_GETMD5.la   ${SHLIBDIR} upd

clean:
	@rm -f *.o *.la *.lo
	@rm -rf .libs


##########################################################################




