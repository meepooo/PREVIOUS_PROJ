#!/bin/bash

busi_date=$1
bank_no=$2
filepath=$HOME/file/icps/wbank/$busi_date
cd $filepath;pwd

if [ -f .filelist ];then
    rm -f .filelist
fi

CheckFile=`ls *${bank_no}_${busi_date}.tar.gz.check`

for checkfilename in $CheckFile;
do
    filemd5=`cat $checkfilename | awk '{print $1}'`;
    filename=`cat $checkfilename | awk '{printf $2}' | tr -d '\n\r'`;
    #echo $filemd5;
    #echo $filename;
    calmd5=`md5sum $filename|awk '{print $1}'`
    #echo "calmd5:$calmd5"
    if [ "$filemd5" == "$calmd5" ];then
        foldername=`echo $filename|awk -F '.' '{print $1}'`
        subfoldername=`echo $foldername|awk '{gsub(/_'$bank_no'_'$busi_date'/,"");print}'`
        #echo "foldername:$foldername"
        #echo "subfoldername:$subfoldername"
        if [ -d "$foldername" ];then
            echo "folder exist!"
            rm -rf $foldername
        fi
        tar zxf $filename
    fi
    
    cd $foldername/$subfoldername;pwd
    packages=`cat md5sum.txt.asc`
    i=0
    touch .filelist
    for package in $packages;
    do
        echo "have package:$package"
        echo "i = $i"
        if [ $i == 0 ];then
            p_filemd5=`echo $package | awk '{print $1}'`;
            i=1
        else
            p_filename=`echo $package | awk '{print $1}'`;
            i=0
            echo "p_filemd5:$p_filemd5"
            echo "p_filename:$p_filename"
            p_calmd5=`md5sum $p_filename|awk '{print $1}'`
            if [ "$p_filemd5" == "$p_calmd5" ];then
                gunzip $p_filename
                echo $p_filename | awk -F '.' '{print $1}'>>.filelist
            fi
        fi
    done
    cd $filepath;pwd
    
done

cd $filepath;pwd
G4file=`ls G4*.tar.gz`
if [ ! -f $G4file ];then
    echo "no G4 file"
else
    G4folder=`echo $G4file | awk -F '.' '{print $1}'` 
    if [ -d $G4folder ];then
        echo "Having G4 folder"
        rm -rf $G4folder
    fi
    tar zxf $G4file
    cd $filepath/$G4folder/rrs_bdm_udf_clear_detail;pwd
    if [ -f rrs_bdm_udf_clear_detail.gz ];then
        gunzip rrs_bdm_udf_clear_detail.gz
        echo "rrs_bdm_udf_clear_detail">.filelist
        cd $filepath/$G4folder/rrs_bdm_udf_clear_other_detail;pwd
        if [ -f rrs_bdm_udf_clear_other_detail.gz ];then
            gunzip rrs_bdm_udf_clear_other_detail.gz
            echo "rrs_bdm_udf_clear_other_detail">.filelist
            cd $filepath/$G4folder/rrs_bdm_udf_clear_tot;pwd
            if [ -f rrs_bdm_udf_clear_tot.gz ];then
                gunzip rrs_bdm_udf_clear_tot.gz
                echo "rrs_bdm_udf_clear_tot">.filelist
            fi
        fi
    fi
fi
