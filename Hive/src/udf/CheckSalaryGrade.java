package udf;

import org.apache.hadoop.hive.ql.exec.UDF;

/*
 * ����Ա����нˮ���ж�нˮ�ļ���
 (*) sal < 1000     ----> Grade A
 (*) 1000<=sal <3000 ---> Grade B
 (*) sal >=3000      ---> Grade C
 */
public class CheckSalaryGrade extends UDF {

	public String evaluate(String salary){
		int sal = Integer.parseInt(salary);
		
		if(sal < 1000) return "Grade A";
		else if(sal>=1000 && sal<3000) return "Grade B";
		else return "Grade C";
	}
}
