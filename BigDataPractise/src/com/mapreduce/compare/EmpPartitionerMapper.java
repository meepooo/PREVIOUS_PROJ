package com.mapreduce.compare;

import java.io.IOException;

import org.apache.hadoop.io.IntWritable;
import org.apache.hadoop.io.LongWritable;
import org.apache.hadoop.io.Text;
import org.apache.hadoop.mapreduce.Mapper;

import com.java.serializableDemo.Emp;

public class EmpPartitionerMapper extends Mapper<LongWritable, Text, IntWritable, Emp> {

	@Override
	protected void map(LongWritable key, Text value, Mapper<LongWritable, Text, IntWritable, Emp>.Context context)
			throws IOException, InterruptedException {
		String data = value.toString();
		
		String[] words = data.split(",");
		
		Emp emp = new Emp();
		emp.setEmpno(Integer.parseInt(words[0]));
		emp.setEname(words[1]);
		emp.setJob(words[2]);
		emp.setMgr(Integer.parseInt(words[3]));
		emp.setHiredate(words[4]);
		emp.setSal(Integer.parseInt(words[5]));
		emp.setComm(Integer.parseInt(words[6]));
		emp.setDeptno(Integer.parseInt(words[7]));
		
		context.write(new IntWritable(emp.getDeptno()), emp);
	}
	
}
