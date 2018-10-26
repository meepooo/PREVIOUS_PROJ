##########################################################################
# 版权所有：杭州恒生电子股份有限公司
# 项目名称：综合应用前置（GAPS）项目
# 版    本：V4.0
# 操作系统：AIX5.3
# 文件描述：函数组件动态连接库通用MAKEFILE
# 数 据 库:
##########################################################################
# 修改记录
# 修改日期:
# 修改内容:
# 修改人:
##########################################################################
include ${HOME}/src/etc/makefile.${GAPSPLATFORM}
#include ${HOME}/src/etc/${DB}/makefile.${DB}
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
INCLUDE=-I./ -I${HOME}/app/agent/incl -I${HOME}/app/batch/incl -I${HOME}/app/app/incl
APPEH_INCL=include=${HOME}/app/agent/incl include=${HOME}/app/batch/incl include=${HOME}/app/app/incl
APPLIBDIR=-L${HOME}/lib
###########################################################################
DEBUG=${MOS} -DBUILDDATETIME=\"$(BUILDDATETIME)\"
CC=cc ${OS_CCFLAG}
VPATH=.libs
all : BAT_PUB.so BAT_CTRL.so  BAT_CHECK.so BAT_SJRK.so BAT_SJTJ.so BAT_SJHP.so BAT_SJTH.so BAT_SECU.so  BAT_CANCEL.so BAT_COMM.so BAT_RWQT.so  BAT_PQUERY.so BAT_BREAK.so BAT_SJCT.so
.SUFFIXES:  .c .lo
.c.lo:
	libtool --mode=compile --tag=CC ${CC} -g -O ${DEBUG} ${MOS} ${CCFLAG} -I$(LIBINCL) -I${INCL} $(INCLUDE) -c $<

BAT_PUB.so: BAT_PUB.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_PUB.la   ${SHLIBDIR} 
	
BAT_CTRL.so: BAT_CTRL.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_CTRL.la   ${SHLIBDIR} 

BAT_CHECK.so: BAT_CHECK.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_CHECK.la   ${SHLIBDIR} 
	
BAT_SJRK.so: BAT_SJRK.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_SJRK.la   ${SHLIBDIR} 

BAT_SJTJ.so: BAT_SJTJ.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_SJTJ.la   ${SHLIBDIR} 
	
BAT_SJHP.so: BAT_SJHP.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_SJHP.la   ${SHLIBDIR} 				
		
BAT_SJTH.so: BAT_SJTH.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_SJTH.la   ${SHLIBDIR} 			
		
BAT_SECU.so: BAT_SECU.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_SECU.la   ${SHLIBDIR} 					

BAT_CANCEL.so: BAT_CANCEL.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_CANCEL.la   ${SHLIBDIR} 
	
BAT_COMM.so: BAT_COMM.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_COMM.la   ${SHLIBDIR} 

BAT_RWQT.so: BAT_RWQT.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_RWQT.la   ${SHLIBDIR} 

BAT_PQUERY.so: BAT_PQUERY.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_PQUERY.la   ${SHLIBDIR} 

BAT_BREAK.so: BAT_BREAK.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_BREAK.la   ${SHLIBDIR} 

BAT_SJCT.so: BAT_SJCT.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_SJCT.la   ${SHLIBDIR} 			

BAT_P2LJ.so: BAT_P2LJ.lo 
	libtool --mode=link --tag=CC ${CC} ${LDFLAG}  -g -O -o $(@:.so=.la) $? -rpath ${SHLIBDIR}  -release ${RELEASE_VERSION} -export-dynamic -no-undefined -module -L${LIBDIR} ${DB_LIBS} ${APPLIBDIR} -lsha -lsxml -lhsbase -lgapssfs -lgapssql -ldci -lc -lm -lagent
	install-shlib.sh BAT_P2LJ.la   ${SHLIBDIR} 	
			
clean:
	@rm -rf .libs *.lo *.la *.lis
	@rm -f tp* BAT*.o
