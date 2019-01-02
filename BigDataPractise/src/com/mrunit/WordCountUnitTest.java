package com.mrunit;

import java.util.ArrayList;
import java.util.List;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mrunit.mapreduce.MapDriver;
import org.apache.hadoop.mrunit.mapreduce.MapReduceDriver;
import org.apache.hadoop.mrunit.mapreduce.ReduceDriver;
import org.junit.Test;

public class WordCountUnitTest {
	@Test
	public void testMapper() throws Exception {
		System.setProperty("hadoop.home.dir", "E:\\BigData\\hadoop_jar\\hadoop-2.4.1\\hadoop-2.4.1\\hadoop-2.4.1");
		
		WordCountMapper mapper = new WordCountMapper();
		
		//map Driver
		MapDriver<LongWritable, Text, Text, IntWritable> driver = new MapDriver<>(mapper);
		//map input
		driver.withInput(new LongWritable(), new Text("I love Beijing"));
		
		//map output
		driver.withOutput(new Text("I"), new IntWritable(1))
			.withOutput(new Text("love"), new IntWritable(1))
			.withOutput(new Text("Beijing"), new IntWritable(1));
	
		//compare
		driver.runTest();
	}
	
	@Test
	public void testReducer() throws Exception{
		System.setProperty("hadoop.home.dir", "E:\\BigData\\hadoop_jar\\hadoop-2.4.1\\hadoop-2.4.1\\hadoop-2.4.1");
		
		WordCountReducer reducer = new WordCountReducer();
		
		//reducer Driver
		ReduceDriver<Text, IntWritable, Text, IntWritable> driver = new ReduceDriver<>(reducer);

		// k3,v3
		List<IntWritable> value = new ArrayList<>();
		value.add(new IntWritable(1));
		value.add(new IntWritable(1));
		value.add(new IntWritable(1));
		
		// reducer input
		driver.withInput(new Text("I"), value);
		driver.withInput(new Text("love"), value);
		driver.withInput(new Text("Beijing"), value);
		//map output
		driver.withOutput(new Text("I"), new IntWritable(3))
			.withOutput(new Text("love"), new IntWritable(3))
			.withOutput(new Text("Beijing"), new IntWritable(3));
	
		//compare
		driver.runTest();
	}
	
	@Test
	public void testJob() throws Exception{
		System.setProperty("hadoop.home.dir", "E:\\BigData\\hadoop_jar\\hadoop-2.4.1\\hadoop-2.4.1\\hadoop-2.4.1");
		
		WordCountMapper mapper = new WordCountMapper();
		WordCountReducer reducer = new WordCountReducer();
		
		//reducer Driver
		MapReduceDriver<LongWritable, Text, Text, IntWritable, Text, IntWritable> 
			driver = new MapReduceDriver<>(mapper,reducer);
		
		//map input
		driver.withInput(new LongWritable(), new Text("I love Beijing"))
			.withInput(new LongWritable(), new Text("I love China"))
			.withInput(new LongWritable(), new Text("Beijing is the capital of China"));
		
		//reducer output
		//sort
		driver.withOutput(new Text("Beijing"), new IntWritable(2))
			.withOutput(new Text("China"), new IntWritable(2))
			.withOutput(new Text("I"), new IntWritable(2))
			.withOutput(new Text("capital"), new IntWritable(1))
			.withOutput(new Text("is"), new IntWritable(1))
			.withOutput(new Text("love"), new IntWritable(2))
			.withOutput(new Text("of"), new IntWritable(1))
			.withOutput(new Text("the"), new IntWritable(1));
		
		driver.runTest();
	}
}
