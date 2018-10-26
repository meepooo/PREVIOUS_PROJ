#!/bin/sh
function loadfile2database()
{   
  src_filename_utf=rep_gold_flow_wepower.txt
  src_filename_gbk=rep_gold_flow_wepower_gbk.txt
  des_filename=rep_gold_flow_wepower_new.txt 
  iconv $src_filename_utf -f utf-8  -t  gbk  -o $src_filename_gbk
  awk -F\| '{for(i=1;i<=NF;i++)
      {
        if(i<NF)
        {
          if(i==7||i==8)
            printf $i"," >> "'$des_filename'"
          else
            printf "\""$i"\"""," >> "'$des_filename'"
              fi
        }
        else
        {
          printf "\""$i"\"" >> "'$des_filename'"
        }
      }
      {printf "\n" >> "'$des_filename'" }
    }' "$src_filename_gbk" 
    db2 connect to gapsdb user $DBUSER using $DBPASS
    db2 "import from rep_gold_flow_wepower_new.txt of del insert into yw_wzyh_hjjymx"
    echo "$1导入数据库成功"
    rm -f rep_gold_flow_wepower_gbk.txt rep_gold_flow_wepower_new.txt
}

cd /home/gapsv4/file/wzyh
declare begin_date=$1
declare end_date=$2
declare curr_date=$1

while [ $curr_date -le $end_date ]
do
  echo $curr_date
  cd $curr_date
  loadfile2database $curr_date
  curr_date=`date -d "$curr_date +1 days" +%Y%m%d`
  cd ..
done

echo "导入数据库结束"

