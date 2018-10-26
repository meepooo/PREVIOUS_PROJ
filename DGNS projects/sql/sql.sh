for i in *.sql
do
	sqlplus gaps/gaps@gapsdb <${i}
done
