package demo.pig;

import java.io.IOException;

import org.apache.pig.EvalFunc;
import org.apache.pig.data.Tuple;

/*
 * 实现Pig的自定义的运算函数
 * 
 * 根据员工的薪水，判断级别
 * 
 * 泛型：经过运算后，返回的结果值的类型
 */
public class CheckSalaryGrade extends EvalFunc<String> {

	@Override
	public String exec(Tuple tuple) throws IOException {
		// 调用
		// result2 = foreach emp generate ename,sal,demo.pig.CheckSalaryGrade(sal);
		
		//取出薪水
		int salary = (int) tuple.get(0);
		if(salary<1000) return "Grade A";
		else if(salary>=1000 &&salary < 3000) return "Grade B";
		else return "Grade C";
	}
}



















