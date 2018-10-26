#!/bin/bash

#lftp -u ${user},${password} sftp://${ip} <<EOF
#set sftp:auto-confirm yes


SFTP_IP=localhost
SFTP_USER=upip
SFTP_PASSWORD=upip

TIME=$[$(date +%H%M%S%N)/1000000]
DATE=$1
LOCAL_DIR=$2


if [ ! -d "$LOCAL_DIR" ]; then
    echo "No local dir!"
    mkdir -p $LOCAL_DIR
fi

if [ -f "$LOCAL_DIR/.filelist" ]; then
    echo "Having .filelist"
    rm -rf $LOCAL_DIR/.filelist
fi

#汇总文件
#lftp -u ${SFTP_USER},${SFTP_PASSWORD} sftp://${SFTP_IP}<<EOF
#set sftp:auto-confirm yes
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/accounting/${DATE}
lcd $LOCAL_DIR
get check_accounting* 
bye
EOF
cd $LOCAL_DIR
CHECK_ACCOUNTING=`ls check_accounting*`
if [ ! -n "$CHECK_ACCOUNTING" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_ACCOUNTING"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/accounting/${DATE}
    lcd $LOCAL_DIR
    get accounting_*
    bye
EOF
fi

cd $LOCAL_DIR
FILE_ACCOUNTING=`ls accounting_*`
if [ -n "$FILE_ACCOUNTING" ]; then
    echo "accounting" >>.filelist
    echo $FILE_ACCOUNTING >>.filelist
fi

#在途支用明细文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/loan/${DATE}
lcd $LOCAL_DIR
get check_lending_detail* 
bye
EOF
cd $LOCAL_DIR
CHECK_LENDING_DETAIL=`ls check_lending_detail*`
if [ ! -n "$CHECK_LENDING_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_LENDING_DETAIL"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/loan/${DATE}
    lcd $LOCAL_DIR
    get lending_detail_*
    bye
EOF
fi

#放款（借据）明细文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/loan/${DATE}
lcd $LOCAL_DIR
get check_loan_detail* 
bye
EOF
cd $LOCAL_DIR
CHECK_LOAN_DETAIL=`ls check_loan_detail*`
if [ ! -n "$CHECK_LOAN_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_LOAN_DETAIL"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/loan/${DATE}
    lcd $LOCAL_DIR
    get loan_detail_*
    bye
EOF
fi

#放款（分期）明细文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/loan/${DATE}
lcd $LOCAL_DIR
get check_repay_plan* 
bye
EOF
cd $LOCAL_DIR
CHECK_REPAY_PLAN=`ls check_repay_plan*`
if [ ! -n "$CHECK_REPAY_PLAN" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_REPAY_PLAN"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/loan/${DATE}
    lcd $LOCAL_DIR
    get repay_plan_*
    bye
EOF
fi

#还款（借据）明细文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/repay/${DATE}
lcd $LOCAL_DIR
get check_repay_loan_detail* 
bye
EOF
cd $LOCAL_DIR
CHECK_REPAY_LOAN_DETAIL=`ls check_repay_loan_detail*`
if [ ! -n "$CHECK_REPAY_LOAN_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_REPAY_LOAN_DETAIL"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/repay/${DATE}
    lcd $LOCAL_DIR
    get repay_loan_detail_*
    bye
EOF
fi

#还款（分期）明细文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/repay/${DATE}
lcd $LOCAL_DIR
get check_repay_instmnt_detail* 
bye
EOF
cd $LOCAL_DIR
CHECK_REPAY_INSTMNT_DETAIL=`ls check_repay_instmnt_detail*`
if [ ! -n "$CHECK_REPAY_INSTMNT_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_REPAY_INSTMNT_DETAIL"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/repay/${DATE}
    lcd $LOCAL_DIR
    get repay_instmnt_detail_*
    bye
EOF
fi

#减免（借据）明细文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/exempt/${DATE}
lcd $LOCAL_DIR
get check_exempt_loan_detail* 
bye
EOF
cd $LOCAL_DIR
CHECK_EXEMPT_LOAN_DETAIL=`ls check_exempt_loan_detail*`
if [ ! -n "$CHECK_EXEMPT_LOAN_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_EXEMPT_LOAN_DETAIL"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/exempt/${DATE}
    lcd $LOCAL_DIR
    get exempt_loan_detail_*
    bye
EOF
fi

#减免（分期）明细文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/exempt/${DATE}
lcd $LOCAL_DIR
get check_exempt_instmnt_detail* 
bye
EOF
cd $LOCAL_DIR
CHECK_EXEMPT_INSTMNT_DETAIL=`ls check_exempt_instmnt_detail*`
if [ ! -n "$CHECK_EXEMPT_INSTMNT_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_EXEMPT_INSTMNT_DETAIL"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/exempt/${DATE}
    lcd $LOCAL_DIR
    get exempt_instmnt_detail_*
    bye
EOF
fi

#日初（借据）信息文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/init/${DATE}
lcd $LOCAL_DIR
get check_loan_init* 
bye
EOF
cd $LOCAL_DIR
CHECK_LOAN_INIT=`ls check_loan_init*`
if [ ! -n "$CHECK_LOAN_INIT" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_LOAN_INIT"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/init/${DATE}
    lcd $LOCAL_DIR
    get loan_init_*
    bye
EOF
fi

#日初（分期）信息文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/init/${DATE}
lcd $LOCAL_DIR
get check_instmnt_init* 
bye
EOF
cd $LOCAL_DIR
CHECK_INSTMNT_INIT=`ls check_instmnt_init*`
if [ ! -n "$CHECK_INSTMNT_INIT" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_INSTMNT_INIT"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/init/${DATE}
    lcd $LOCAL_DIR
    get instmnt_init_*
    bye
EOF
fi

#利息计提明细文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/accrued_int/${DATE}
lcd $LOCAL_DIR
get check_loan_calc* 
bye
EOF
cd $LOCAL_DIR
CHECK_LOAN_CALC=`ls check_loan_calc*`
if [ ! -n "$CHECK_LOAN_CALC" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_LOAN_CALC"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/accrued_int/${DATE}
    lcd $LOCAL_DIR
    get loan_calc_*
    bye
EOF
fi

#借据形态转移流水文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/change/${DATE}
lcd $LOCAL_DIR
get check_arg_status_change* 
bye
EOF
cd $LOCAL_DIR
CHECK_ARG_STATUS_CHANGE=`ls check_arg_status_change*`
if [ ! -n "$CHECK_ARG_STATUS_CHANGE" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_ARG_STATUS_CHANGE"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/change/${DATE}
    lcd $LOCAL_DIR
    get arg_status_change_*
    bye
EOF
fi

#网商银行资金对账文件
sftp $SFTP_USER@$SFTP_IP <<EOF
cd download/fund/${DATE}
lcd $LOCAL_DIR
get check_fund_detail* 
bye
EOF
cd $LOCAL_DIR
CHECK_FUND_DETAIL=`ls check_fund_detail*`
if [ ! -n "$CHECK_FUND_DETAIL" ]; then
    echo "Not found!"
else
    echo "Found! $CHECK_FUND_DETAIL"
    sftp $SFTP_USER@$SFTP_IP <<EOF

    cd download/fund/${DATE}
    lcd $LOCAL_DIR
    get fund_detail_*
    bye
EOF
fi

