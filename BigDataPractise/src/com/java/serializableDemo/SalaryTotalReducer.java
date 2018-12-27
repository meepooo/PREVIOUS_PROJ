package com.java.serializableDemo;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapreduce.Reducer;

public class SalaryTotalReducer extends Reducer<IntWritable, Emp, IntWritable, IntWritable>{

	@Override
	protected void reduce(IntWritable key, Iterable<Emp> value,
			Reducer<IntWritable, Emp, IntWritable, IntWritable>.Context context) throws IOException, InterruptedException {
		// TODO Auto-generated method stub
		int total=0;
		
		for(Emp e:value) {
			total+=e.getSal();
		}
		
		context.write(key, new IntWritable(total));
	}

}
