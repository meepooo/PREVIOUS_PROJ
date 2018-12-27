package com.java.serializableDemo;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

import com.mapreduce.salarytotal.SalaryTotalMapper;
import com.mapreduce.salarytotal.SalaryTotalReducer;

public class SalaryTotalMain {
	public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {
		// 创建任务并指定任务入口
		Job job = Job.getInstance(new Configuration());
		job.setJarByClass(SalaryTotalMain.class);

		// 指定mapper
		job.setMapperClass(SalaryTotalMapper.class);
		job.setMapOutputKeyClass(IntWritable.class);
		job.setMapOutputValueClass(IntWritable.class);

		// 指定比较器
		job.setSortComparatorClass(MyNumberComparator.class);
		
		// 指定reducer
		job.setReducerClass(SalaryTotalReducer.class);
		job.setOutputKeyClass(IntWritable.class);
		job.setOutputValueClass(IntWritable.class);

		// 指定路径
		FileInputFormat.setInputPaths(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));

		// 执行任务
		job.waitForCompletion(true);
	}
}
