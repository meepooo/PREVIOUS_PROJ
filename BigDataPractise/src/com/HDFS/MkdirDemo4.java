package com.HDFS;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.junit.Test;

public class MkdirDemo4 {
	
	@Test
	public void testMkdir4() throws IOException {
		
		//use chmod 777 to change folder1's permission
		
		Configuration conf = new Configuration();
		conf.set("fs.defaultFS", "hdfs://172.16.26.111:9000");

		FileSystem fs = FileSystem.get(conf);

		fs.mkdirs(new Path("/folder1/folder111"));
		
		fs.close();
	}
}
