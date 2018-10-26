E_DBS=-EDDBS_DB2_8 -EDDBS_DB2
DBS=-DDBS_DB2_8 -DDBS_DB2
#######################################
#DB2 --S
DB2ESQL=db2 prep
DB2_LIBS=-L${DB2PATH}/lib${FIX}
DB2_INCL=-I${DB2PATH}/include
#DB2 --E

DB2_CCFLAGS=$(DB2_INCL) -DBUILDDATETIME=\"$(BUILDDATETIME)\"
DB_CCFLAGS=${DB2_CCFLAGS}
DB_LIBS=${DB2_LIBS} -ldb2
##########################################################################
.SUFFIXES: .sqc .c

.sqc.c:
	@rm -f $*.c $*.bnd
	db2 connect to $(DBALIAS) user $(DBUSER) using $(DBPASS)
	db2 prep $< bindfile using $*.bnd
	db2 bind $*.bnd

##########################################################################
