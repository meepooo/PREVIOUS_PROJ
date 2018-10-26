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
LO_OBJS=SCOMM_ESB_XMLCOV.o
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
#CC=cc -m32
VPATH=.libs
.SUFFIXES:  .c .lo

.c.lo:
	libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${DBS} ${MOS} ${DB_CCFLAGS} ${CCFLAG} -I$(LIBINCL) -I$(INCLUDE) -c $<


all : SCOMM_ESB_XMLCOV.so  SDATA_TRIMSPECHAR.so DATA_HSMEnSetValue.so SDATA_MSetLoopValue.so SCOMM_GACK_XMLCOV.so CUSTOM_PUBLIC_DRC.so

#将编译好的动态库从.libs目录copy到shlib目录，并备份原库文件
#install-shlib.sh ***.la   ${SHLIBDIR}后面如果加参数upd 即执行SOAtool upd ***.so,不加就不会刷新只拷贝
install:
	install-shlib.sh SCOMM_GACK_XMLCOV.la   ${SHLIBDIR}
	install-shlib.sh SCOMM_ESB_XMLCOV.la   ${SHLIBDIR}
	install-shlib.sh  SDATA_TRIMSPECHAR.la   ${SHLIBDIR}	
	install-shlib.sh  DATA_HSMEnSetValue.la   ${SHLIBDIR}	
	install-shlib.sh  SDATA_MSetLoopValue.la   ${SHLIBDIR}	
	install-shlib.sh  CUSTOM_PUBLIC_DRC.la   ${SHLIBDIR}	
uninstall: 
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SCOMM_GACK_XMLCOV.so ${SHLIBDIR}/SCOMM_GACK_XMLCOV-*.so 
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SCOMM_ESB_XMLCOV.so ${SHLIBDIR}/SCOMM_ESB_XMLCOV-*.so 
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SDATA_TRIMSPECHAR.so ${SHLIBDIR}/ SDATA_TRIMSPECHAR-*.so 
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/DATA_HSMEnSetValue.so ${SHLIBDIR}/ DATA_HSMEnSetValue-*.so 
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/SDATA_MSetLoopValue.so ${SHLIBDIR}/ SDATA_MSetLoopValue-*.so 
	libtool --mode=uninstall /bin/rm ${SHLIBDIR}/CUSTOM_PUBLIC_DRC.so ${SHLIBDIR}/ CUSTOM_PUBLIC_DRC-*.so 

SCOMM_GACK_XMLCOV.so: SCOMM_GACK_XMLCOV.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci
	install-shlib.sh SCOMM_GACK_XMLCOV.la   ${SHLIBDIR} upd

SCOMM_ESB_XMLCOV.so: SCOMM_ESB_XMLCOV.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci
	install-shlib.sh SCOMM_ESB_XMLCOV.la   ${SHLIBDIR} upd

 SDATA_TRIMSPECHAR.so:  SDATA_TRIMSPECHAR.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci
	install-shlib.sh  SDATA_TRIMSPECHAR.la   ${SHLIBDIR} upd
	
DATA_HSMEnSetValue.so: DATA_HSMEnSetValue.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci
	install-shlib.sh DATA_HSMEnSetValue.la   ${SHLIBDIR} upd
	
SDATA_MSetLoopValue.so: SDATA_MSetLoopValue.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci
	install-shlib.sh SDATA_MSetLoopValue.la   ${SHLIBDIR} upd	

SDATA_Datacasecmp.so: SDATA_Datacasecmp.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci
	install-shlib.sh SDATA_Datacasecmp.la   ${SHLIBDIR} upd

CUSTOM_PUBLIC_DRC.so: CUSTOM_PUBLIC_DRC.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci
	install-shlib.sh CUSTOM_PUBLIC_DRC.la   ${SHLIBDIR} upd

SCOMM_UNLOADTABLE2FILE.so: SCOMM_UNLOADTABLE2FILE.lo
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci
	install-shlib.sh SCOMM_UNLOADTABLE2FILE.la   ${SHLIBDIR} upd

clean:
	@rm -f lib*.a *~ *core *.lo *.o *.la 
	@rm -rf .libs
	@rm -f *.lis  *.bnd

##########################################################################
