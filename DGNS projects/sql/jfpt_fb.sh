#1.	����&�޸ı�
db2 -tvf  jfpt_create_alter.sql

#2.	����������ݣ�
db2 �Ctvf  jfpt_insert.sql

#3.	�������������ļ���
mv $HOME/etc/esb_field.cfg $HOME/etc/esb_field.cfg_`date +%Y%m%d%H%M%S`
cp esb_field.cfg   $HOME/etc/

#4.	������̬���ӿ⣺
mv $HOME/shlib/AGT_PTGL-4.0.0.so $HOME/shlib/AGT_PTGL-4.0.0.so_`date +%Y%m%d%H%M%S`
mv $HOME/shlib/APP_COMPANY-4.0.0.so $HOME/shlib/APP_COMPANY-4.0.0.so_`date +%Y%m%d%H%M%S`
cp AGT_PTGL-4.0.0.so $HOME/shlib
cp APP_COMPANY-4.0.0.so $HOME/shlib
cp APP_SXF-4.0.0.so $HOME/shlib

#5.	������̬�����ӣ�
cd  $HOME/shlib
ln -s -f  AGT_PTGL-4.0.0.so  AGT_PTGL.so
ln -s -f  APP_COMPANY-4.0.0.so  APP_COMPANY.so
ln -s -f  APP_SXF-4.0.0.so  APP_SXF.so
SOAtool upd AGT_PTGL.so
SOAtool upd APP_COMPANY.so 
SOAtool upd APP_SXF.so
cd -

#6.	������ʱ��������ļ�
cp jfpt700675.xml   $HOME/tools/systask
cp jfpt700679.xml   $HOME/tools/systask

#7.	��GAPS�������ֶ���Ӷ�ʱ����
#����700675�����ˣ���ʱ����
#����700679�����㣩��ʱ����

#8.	��Ŀ¼��
mkdir �Cp $HOME/file/jfpt/recv/jfxx

#9.	����������Դ��
loadres.pl �Cf  GAPS20160713.tar.gz  -m 0 -t 60 �Cb

#10.	����"GAPS��־��ѯ����"�����ļ���
#mv $HOME/cfg/query.htm $HOME/cfg/query.htm_`date +%Y%m%d%H%M%S`
#cp query.htm $HOME/cfg

#11.	����&����cs_KKGLTJR�������
cp cs_KKGLTJR.ini $HOME/etc
cp cs_KKGLTJR $HOME/bin
chmod +x $HOME/bin/cs_KKGLTJR
startcs KKGLTJR