package com.mapreduce.compare;

import java.io.IOException;

import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class EmpPartitionMain {
	public static void main(String[] args) throws IOException, InterruptedException, ClassNotFoundException {
		Job job = Job.getInstance();
		
		job.setJarByClass(EmpPartitionMain.class);
		
		job.setMapperClass(EmpPartitionerMapper.class);
		job.setMapOutputKeyClass(IntWritable.class);
		job.setMapOutputValueClass(Emp.class);
		
		job.setPartitionerClass(EmpPartitioner.class);
		job.setNumReduceTasks(3);
		
		job.setReducerClass(EmpPartitionerReducer.class);
		job.setOutputKeyClass(IntWritable.class);
		job.setOutputValueClass(Emp.class);
		
		FileInputFormat.setInputPaths(job, new Path(args[0]));
		FileOutputFormat.setOutputPath(job, new Path(args[1]));
		
		job.waitForCompletion(true);
	}
}
