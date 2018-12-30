package com.mapreduce.sort;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.NullWritable;
import org.apache.hadoop.mapreduce.Job;
import org.apache.hadoop.mapreduce.lib.input.FileInputFormat;
import org.apache.hadoop.mapreduce.lib.output.FileOutputFormat;

public class EmpSortMain {
	public static void main(String[] args) throws IOException, ClassNotFoundException, InterruptedException {
		Job job = Job.getInstance(new Configuration());
		
		job.setJarByClass(EmpSortMain.class);
		job.setMapOutputKeyClass(Emp.class);
		job.setMapOutputValueClass(NullWritable.class);
		
		job.setOutputKeyClass(Emp.class);
		job.setOutputValueClass(NullWritable.class);
		
		FileInputFormat.setInputPaths(job, new Path("emp.in"));
		FileOutputFormat.setOutputPath(job, new Path("emp.out"));
		
		job.waitForCompletion(true);
	}
}
