package demo.pig;

import java.io.IOException;

import org.apache.pig.FilterFunc;
import org.apache.pig.data.Tuple;

/*
 * ʵ��Pig���Զ�����˺���
 * 
 * ��ѯ���ʴ���2000��Ա��
 */
public class IsSalaryTooHigh extends FilterFunc {

	@Override
	public Boolean exec(Tuple tuple) throws IOException {
		/*
		 * ���˵��߼�����ѯ���ʴ���2000��Ա��
		 * ���ã�result1 = filter emp by demo.pig.IsSalaryTooHigh(sal);
		 */
		//ȡ��нˮ
		int salary = (int) tuple.get(0);
		return salary>2000?true:false;
	}
}


















