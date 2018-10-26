#db2 connect to gapsdb user gapsusr
db2 connect to $DBALIAS user $DBUSER using $DBPASS

db2 "delete from LOAN_SUB_CHECK WHERE BUSI_TYPE = 'WCD'"
db2 "import from WBC_LOAN_SUB_CHECK.txt of del insert into LOAN_SUB_CHECK"
db2 "delete from LOAN_SUB_ACCT_PARA WHERE BUSI_TYPE = 'WCD'"
db2 "import from WBC_LOAN_SUB_ACCT_PARA.txt of del insert into LOAN_SUB_ACCT_PARA"
