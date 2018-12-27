package com.java.serializableDemo;

import org.apache.hadoop.io.IntWritable;

//针对数字比较
public class MyNumberComparator extends IntWritable.Comparator {

	@Override
	public int compare(byte[] b1, int s1, int l1, byte[] b2, int s2, int l2) {
		// TODO Auto-generated method stub
		// 减号，变为降序
		return -super.compare(b1, s1, l1, b2, s2, l2);
	}
	

}
