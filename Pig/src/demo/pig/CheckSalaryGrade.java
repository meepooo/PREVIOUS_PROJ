package demo.pig;

import java.io.IOException;

import org.apache.pig.EvalFunc;
import org.apache.pig.data.Tuple;

/*
 * ʵ��Pig���Զ�������㺯��
 * 
 * ����Ա����нˮ���жϼ���
 * 
 * ���ͣ���������󣬷��صĽ��ֵ������
 */
public class CheckSalaryGrade extends EvalFunc<String> {

	@Override
	public String exec(Tuple tuple) throws IOException {
		// ����
		// result2 = foreach emp generate ename,sal,demo.pig.CheckSalaryGrade(sal);
		
		//ȡ��нˮ
		int salary = (int) tuple.get(0);
		if(salary<1000) return "Grade A";
		else if(salary>=1000 &&salary < 3000) return "Grade B";
		else return "Grade C";
	}
}



















