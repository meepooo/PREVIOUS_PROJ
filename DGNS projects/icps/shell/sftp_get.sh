#!/bin/bash

USER=upip
#密码
PASSWORD=upip
#IP
IP=localhost

DATE=$(date +%Y%m%d)

if [ -d "$HOME/file/icps/${DATE}" ]; then
    mkdir $HOME/file/icps/${DATE}
fi

if [ ! -f "$HOME/file/icps/${DATE}/checkfiles" ];then
    touch checkfiles
else
    rm -rf $HOME/file/icps/${DATE}/checkfiles
fi

#汇总文件
#lftp -u ${USER},${PASSWORD} sftp://${IP}<<EOF
sftp $USER@$IP <<EOF
cd download/accounting/${DATE}
lcd $HOME/file/icps/${DATE}
get check_accounting* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_ACCOUNTING=`ls check_accounting*`
if [ ! -n "$CHECK_ACCOUNTING" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_ACCOUNTING"
    sftp $USER@$IP <<EOF

    cd download/accounting/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get accounting_*
    bye
EOF
fi

#在途支用明细文件
sftp $USER@$IP <<EOF
cd download/loan/${DATE}
lcd $HOME/file/icps/${DATE}
get check_lending_detail* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_LENDING_DETAIL=`ls check_lending_detail*`
if [ ! -n "$CHECK_LENDING_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_LENDING_DETAIL"
    sftp $USER@$IP <<EOF

    cd download/loan/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get lending_detail_*
    bye
EOF
fi

#放款（借据）明细文件
sftp $USER@$IP <<EOF
cd download/loan/${DATE}
lcd $HOME/file/icps/${DATE}
get check_loan_detail* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_LOAN_DETAIL=`ls check_loan_detail*`
if [ ! -n "$CHECK_LOAN_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_LOAN_DETAIL"
    sftp $USER@$IP <<EOF

    cd download/loan/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get loan_detail_*
    bye
EOF
fi

#放款（分期）明细文件
sftp $USER@$IP <<EOF
cd download/loan/${DATE}
lcd $HOME/file/icps/${DATE}
get check_repay_plan* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_REPAY_PLAN=`ls check_repay_plan*`
if [ ! -n "$CHECK_REPAY_PLAN" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_REPAY_PLAN"
    sftp $USER@$IP <<EOF

    cd download/loan/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get repay_plan_*
    bye
EOF
fi

#还款（借据）明细文件
sftp $USER@$IP <<EOF
cd download/repay/${DATE}
lcd $HOME/file/icps/${DATE}
get check_repay_loan_detail* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_REPAY_LOAN_DETAIL=`ls check_repay_loan_detail*`
if [ ! -n "$CHECK_REPAY_LOAN_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_REPAY_LOAN_DETAIL"
    sftp $USER@$IP <<EOF

    cd download/repay/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get repay_loan_detail_*
    bye
EOF
fi

#还款（分期）明细文件
sftp $USER@$IP <<EOF
cd download/repay/${DATE}
lcd $HOME/file/icps/${DATE}
get check_repay_instmnt_detail* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_REPAY_INSTMNT_DETAIL=`ls check_repay_instmnt_detail*`
if [ ! -n "$CHECK_REPAY_INSTMNT_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_REPAY_INSTMNT_DETAIL"
    sftp $USER@$IP <<EOF

    cd download/repay/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get repay_instmnt_detail_*
    bye
EOF
fi

#减免（借据）明细文件
sftp $USER@$IP <<EOF
cd download/exempt/${DATE}
lcd $HOME/file/icps/${DATE}
get check_exempt_loan_detail* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_EXEMPT_LOAN_DETAIL=`ls check_exempt_loan_detail*`
if [ ! -n "$CHECK_EXEMPT_LOAN_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_EXEMPT_LOAN_DETAIL"
    sftp $USER@$IP <<EOF

    cd download/exempt/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get exempt_loan_detail_*
    bye
EOF
fi

#减免（分期）明细文件
sftp $USER@$IP <<EOF
cd download/exempt/${DATE}
lcd $HOME/file/icps/${DATE}
get check_exempt_instmnt_detail* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_EXEMPT_INSTMNT_DETAIL=`ls check_exempt_instmnt_detail*`
if [ ! -n "$CHECK_EXEMPT_INSTMNT_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_EXEMPT_INSTMNT_DETAIL"
    sftp $USER@$IP <<EOF

    cd download/exempt/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get exempt_instmnt_detail_*
    bye
EOF
fi

#日初（借据）信息文件
sftp $USER@$IP <<EOF
cd download/init/${DATE}
lcd $HOME/file/icps/${DATE}
get check_loan_init* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_LOAN_INIT=`ls check_loan_init*`
if [ ! -n "$CHECK_LOAN_INIT" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_LOAN_INIT"
    sftp $USER@$IP <<EOF

    cd download/init/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get loan_init_*
    bye
EOF
fi

#日初（分期）信息文件
sftp $USER@$IP <<EOF
cd download/init/${DATE}
lcd $HOME/file/icps/${DATE}
get check_instmnt_init* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_INSTMNT_INIT=`ls check_instmnt_init*`
if [ ! -n "$CHECK_INSTMNT_INIT" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_INSTMNT_INIT"
    sftp $USER@$IP <<EOF

    cd download/init/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get instmnt_init_*
    bye
EOF
fi

#利息计提明细文件
sftp $USER@$IP <<EOF
cd download/accrued_int/${DATE}
lcd $HOME/file/icps/${DATE}
get check_loan_calc* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_LOAN_CALC=`ls check_loan_calc*`
if [ ! -n "$CHECK_LOAN_CALC" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_LOAN_CALC"
    sftp $USER@$IP <<EOF

    cd download/accrued_int/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get loan_calc_*
    bye
EOF
fi

#借据形态转移流水文件
sftp $USER@$IP <<EOF
cd download/change/${DATE}
lcd $HOME/file/icps/${DATE}
get check_arg_status_change* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_ARG_STATUS_CHANGE=`ls check_arg_status_change*`
if [ ! -n "$CHECK_ARG_STATUS_CHANGE" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_ARG_STATUS_CHANGE"
    sftp $USER@$IP <<EOF

    cd download/change/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get arg_status_change_*
    bye
EOF
fi

#网商银行资金对账文件
sftp $USER@$IP <<EOF
cd download/fund/${DATE}
lcd $HOME/file/icps/${DATE}
get check_fund_detail* 
bye
EOF
cd /home/icps/file/icps/${DATE}
CHECK_FUND_DETAIL=`ls check_fund_detail*`
if [ ! -n "$CHECK_FUND_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_FUND_DETAIL"
    sftp $USER@$IP <<EOF

    cd download/fund/${DATE}
    lcd /home/icps/file/icps/${DATE}
    get fund_detail_*
    bye
EOF
fi