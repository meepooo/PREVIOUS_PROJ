#�������ݿ�
db2 connect to gapsdb user gapsusr using qwer1234

#1.	����������ݣ�
db2 �Ctvf  yytyl_20170426.sql

db2 connect reset

#2.	������̬���ӿ⣺
mv $HOME/shlib/AGT_PTGL-4.0.0.so $HOME/shlib/AGT_PTGL-4.0.0.so_`date +%Y%m%d%H%M%S`
cp ./shlib/AGT_PTGL-4.0.0.so $HOME/shlib

#3.	ˢ��̬�����ӿ⣺
cd  $HOME/shlib
SOAtool upd AGT_PTGL.so
cd -

#4.	������ʱ��������ļ�
cp ./tools/systask/yytyl700296_276.xml   $HOME/tools/systask

#5.	����������Դ��
loadres.pl �Cf  GAPS20170426.tar.gz  -m 0 -t 60 �Cb
