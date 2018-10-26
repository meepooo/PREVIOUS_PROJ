#!/bin/bash

filepath=$1
busi_date=$2
namestring=$3
newfilename=$4

cd $filepath/tmp;pwd
fileZIP=`ls *$namestring*`
for file1 in $fileZIP
do
	echo $file1
	mv $file1 ../$busi_date
	unzip -o $filepath/$busi_date/$file1 -d $filepath/$busi_date
done

cd $filepath/$busi_date;pwd
rm -f $newfilename
fileW006=`ls *W006*`
touch $newfilename
for file2 in $fileW006;
do
	cat $file2 | tail -n +2 >> $newfilename;
done

