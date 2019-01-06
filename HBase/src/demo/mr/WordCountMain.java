package demo.mr;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.mapreduce.TableMapReduceUtil;
import org.apache.hadoop.hbase.util.Bytes;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Job;

public class WordCountMain {

	public static void main(String[] args) throws Exception {
		//ָ��Zookeeper��ַ
		//ָ����������Ϣ: ZooKeeper
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "192.168.157.111");
		
		//����һ������
		Job job = Job.getInstance(conf);
		job.setJarByClass(WordCountMain.class);
		
		//����һ��ɨ����ֻ��ȡ content:info����е�����
		Scan scan = new Scan();
		scan.addColumn(Bytes.toBytes("content"), Bytes.toBytes("info"));
		
		//ָ��mapper
		TableMapReduceUtil.initTableMapperJob(Bytes.toBytes("word"),      //����ı�
				                              scan,    //����һ��ɨ����������������Ҫ���������
				                              WordCountMapper.class, 
				                              Text.class, 
				                              IntWritable.class, 
				                              job);
		
		//ָ��reducer
		TableMapReduceUtil.initTableReducerJob("stat", WordCountReducer.class, job);
		
		//ִ������
		job.waitForCompletion(true);
	}
}



















