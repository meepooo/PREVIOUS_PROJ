package com.mapreduce.compare;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapreduce.Reducer;

public class EmpPartitionerReducer extends Reducer<IntWritable, Emp, IntWritable, Emp> {

	@Override
	protected void reduce(IntWritable deptno, Iterable<Emp> emp,
			Reducer<IntWritable, Emp, IntWritable, Emp>.Context context) throws IOException, InterruptedException {
		for(Emp e:emp) {
			context.write(deptno, e);
		}
	}

}
