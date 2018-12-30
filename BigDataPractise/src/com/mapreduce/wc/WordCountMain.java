package com.mapreduce.wc;

import java.io.IOException;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import com.sun.jersey.core.impl.provider.entity.XMLJAXBElementProvider.Text;

public class WordCountMain {
	public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {
		// ����һ������
		Job job = Job.getInstance();
				
		// ������ڣ�Ҳ����main������class
		job.setJarByClass(WordCountMain.class);
		
		
		// ָ�������Map�������������
		job.setMapperClass(WordCountMapper.class);
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(IntWritable.class);
		
		// ָ�������Reduce�������������
		job.setReducerClass(WordCountReducer.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);
		
		//add Combiner
		job.setCombinerClass(WordCountReducer.class);
		
		// ָ�����������·�������·��
		FileInputFormat.setInputPaths(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));
		//ִ������
		job.waitForCompletion(true);
	}
}
