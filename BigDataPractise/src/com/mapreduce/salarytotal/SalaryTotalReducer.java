package com.mapreduce.salarytotal;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapreduce.Reducer;

public class SalaryTotalReducer extends Reducer<IntWritable, IntWritable, IntWritable, IntWritable>{

	@Override
	protected void reduce(IntWritable key, Iterable<IntWritable> value,
			Reducer<IntWritable, IntWritable, IntWritable, IntWritable>.Context context)
			throws IOException, InterruptedException {

		int total=0;
		for(IntWritable v:value) {
			total += v.get();
		}
		
		context.write(key, new IntWritable(total));
	}

}
