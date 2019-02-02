package demo.pig;

import java.io.IOException;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.mapreduce.InputFormat;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.RecordReader;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.input.TextInputFormat;
import org.apache.pig.LoadFunc;
import org.apache.pig.backend.hadoop.executionengine.mapReduceLayer.PigSplit;
import org.apache.pig.data.BagFactory;
import org.apache.pig.data.DataBag;
import org.apache.pig.data.Tuple;
import org.apache.pig.data.TupleFactory;

/*
 * �Զ���ļ��غ�����
 * ʵ�֣�WordCountǰ�������ݣ�ÿһ��������Ϊһ��Tuple
 */
public class MyLoadFunction extends LoadFunc {

	//����������
	private RecordReader reader;
	
	@Override
	public InputFormat getInputFormat() throws IOException {
		// ָ���������ݵ����ͣ��ַ���
		return new TextInputFormat();
	}

	@Override
	public Tuple getNext() throws IOException {
		//���������У�����һ�����ݺ���ν���
		//1��ÿ��������Ϊһ��Tuple
		//2����Щtuple�ٷ���һ��bag��
		//3���ٰ����bag���뷵�ص�tuple��
		//����: I love Beijing
		Tuple result = null;
		try{
			//�ж��Ƿ�������
			if(!reader.nextKeyValue()){
				//û������
				return result; //���ǿ�ֵ
			}
			
			//�����ݶ���
			String data = reader.getCurrentValue().toString();
			//�ִ�
			String[] words = data.split(" ");
			
			//���ɷ��ؽ����Tuple
			result = TupleFactory.getInstance().newTuple();
			
			//ÿ�����ʷ���һ��Tuple�У��ٰ���ЩTuple����һ������
			//����һ�ű�
			DataBag bag = BagFactory.getInstance().newDefaultBag();
			for(String w:words){
				//ȡ��ÿ������
				Tuple aTuple = TupleFactory.getInstance().newTuple();
				aTuple.append(w);
				
				//�����
				bag.add(aTuple);
			}
			
			//�ѱ����Tuple��
			result.append(bag);
		}catch(Exception ex){
			ex.printStackTrace();
		}		
		return result;
	}

	@Override
	public void prepareToRead(RecordReader reader, PigSplit arg1) throws IOException {
		// ʹ�ø÷�������ʼ�������� : RecordReader
		this.reader= reader;
	}

	@Override
	public void setLocation(String path, Job job) throws IOException {
		//ָ��HDFS��Ŀ¼
		FileInputFormat.setInputPaths(job, new Path(path));
	}
}












