package com.mrunit;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

public class WordCountMapper extends Mapper<LongWritable, Text, Text, IntWritable> {

	@Override
	protected void map(LongWritable key, Text value, Mapper<LongWritable, Text, Text, IntWritable>.Context context)
			throws IOException, InterruptedException {
		
		// Context: map的上下文
		// 上文：HDFS
		// 下文：Reducer
		//得到数据
		String data = value.toString();
		
		//分词
		String words[] = data.split(" ");
		
		for(String word : words) {
			context.write(new Text(word), new IntWritable(1));
		}
		
	}
	
	

}
