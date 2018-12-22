package com.mapreduce.wc;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Reducer;

public class WordCountReducer extends Reducer<Text, IntWritable, Text, IntWritable>{

	@Override
	protected void reduce(Text key, Iterable<IntWritable> value,
			Reducer<Text, IntWritable, Text, IntWritable>.Context context) throws IOException, InterruptedException {
		
		// context: reducer的上下文
		// 上文：Map
		// 下文：HDFS
		int total=0;
		
		for(IntWritable v: value) {
			total += v.get();
		}
		
		context.write(key, new IntWritable(total));
	}
	
}
