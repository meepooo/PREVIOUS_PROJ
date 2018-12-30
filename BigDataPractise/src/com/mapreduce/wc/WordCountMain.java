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
		// 创建一个任务
		Job job = Job.getInstance();
				
		// 任务入口，也就是main方法的class
		job.setJarByClass(WordCountMain.class);
		
		
		// 指定任务的Map和输出数据类型
		job.setMapperClass(WordCountMapper.class);
		job.setMapOutputKeyClass(Text.class);
		job.setMapOutputValueClass(IntWritable.class);
		
		// 指定任务的Reduce和输出数据类型
		job.setReducerClass(WordCountReducer.class);
		job.setOutputKeyClass(Text.class);
		job.setOutputValueClass(IntWritable.class);
		
		//add Combiner
		job.setCombinerClass(WordCountReducer.class);
		
		// 指定任务的输入路径和输出路径
		FileInputFormat.setInputPaths(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));
		//执行任务
		job.waitForCompletion(true);
	}
}
