package udf;

import org.apache.hadoop.hive.ql.exec.UDF;

//ʵ�ֹ�ϵ�����ݿ���concat����
public class MyConcatString extends UDF{

	//������дһ�����������ֱ����: evaluate
	public String evaluate(String a,String b){
		return a+"**************"+b;
	}
}
