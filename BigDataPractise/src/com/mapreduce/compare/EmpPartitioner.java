package com.mapreduce.compare;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.mapreduce.Partitioner;

public class EmpPartitioner extends Partitioner<IntWritable,Emp>{

	@Override
	public int getPartition(IntWritable depno, Emp emp, int numTask) {
		int deptno = emp.getDeptno();
		
		if(deptno==10)
			return 1%numTask;
		else if(deptno==20)
			return 2%numTask;
		else
			return 3%numTask;
	}

}
