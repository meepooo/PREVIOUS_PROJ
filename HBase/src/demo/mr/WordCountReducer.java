package demo.mr;

import java.io.IOException;

import org.apache.hadoop.hbase.client.Mutation;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.io.ImmutableBytesWritable;
import org.apache.hadoop.hbase.mapreduce.TableReducer;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;

//                                                  k3      v3      keyout���������һ����¼��ָ���м�
public class WordCountReducer extends TableReducer<Text, IntWritable, ImmutableBytesWritable> {

	@Override
	protected void reduce(Text k3, Iterable<IntWritable> v3,Context context)
			throws IOException, InterruptedException {
		//��v3���
		int total = 0;
		for(IntWritable v:v3){
			total = total + v.get();
		}
		
		//�����Ҳ�Ǳ��е�һ����¼
		//����һ��Put���󣬰ѵ�����Ϊrowkey
		Put put = new Put(Bytes.toBytes(k3.toString()));
		put.add(Bytes.toBytes("content"),  //����
				Bytes.toBytes("result"),   // ��
				Bytes.toBytes(String.valueOf(total)));  //ֵ
		
		//���
		context.write(new ImmutableBytesWritable(Bytes.toBytes(k3.toString())), 
				     put);//�õ����
	}

}
















