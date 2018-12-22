package com.HDFS;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.junit.Test;

public class MkdirDemo3 {
	
	@Test
	public void testMkdir3() throws IOException {
		
		// use java -D
		Configuration conf = new Configuration();
		conf.set("fs.defaultFS", "hdfs://172.16.26.111:9000");

		FileSystem fs = FileSystem.get(conf);
		
		fs.mkdirs(new Path("/folder3"));
		
		fs.close();
	}
}
