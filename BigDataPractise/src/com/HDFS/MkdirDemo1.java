package com.HDFS;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.junit.Test;

public class MkdirDemo1 {
	
	@Test
	public void testMkDir() throws Exception{
		
		//set configuration
		//set namenode conf
		Configuration conf = new Configuration();
		conf.set("fs.defaultFS", "hdfs://172.16.26.111:9000");
		//Create a client
		FileSystem client = FileSystem.get(conf);
		
		//Create a folder
		client.mkdirs(new Path("/folder111"));
		
		client.close();
	}
}