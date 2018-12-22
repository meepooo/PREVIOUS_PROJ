package com.HDFS;

import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.FileSystem;
import org.apache.hadoop.fs.Path;
import org.apache.hadoop.hdfs.DistributedFileSystem;
import org.apache.hadoop.io.IOUtils;
import org.junit.Test;

public class UpLoadDemo {

	@Test
	public void HDFSUploadTest() throws IOException{
		
		// root permission -- operation user
		System.setProperty("HADOOP_USER_NAME", "root");
		
		// need Configration
		Configuration conf = new Configuration();
		conf.set("fs.defaultFS", "hdfs://172.16.26.111:9000");
		
		// create a client
		FileSystem fs = FileSystem.get(conf);
		
		// need a InputStream
		InputStream input = new FileInputStream("E:\\BigData\\hadoop-2.7.3.tar.gz");
	
		// hdfs OutputStream
		OutputStream output = fs.create(new Path("/folder1/a.tar.gz"));
		
		// use IOUtils class instead
		if ( 1== 0) {
			byte[] buf = new byte[1024] ;
			int len;
			while ( (len=input.read(buf)) > 0 ) {
				output.write(buf);
			}
			output.flush();
			
			output.close();
			input.close();
		}
		
		IOUtils.copyBytes(input, output, conf);
		output.close();
		input.close();
		fs.close();
	}

	@Test
	public void DownloadTest() throws IOException {

		// root permission -- operation user
		System.setProperty("HADOOP_USER_NAME", "root");
				
		// need Configuration
		Configuration conf = new Configuration();
		conf.set("fs.defaultFS", "hdfs://172.16.26.111:9000");

		// create dfs client
//		DistributedFileSystem dfs = new DistributedFileSystem();
//		dfs.get(conf);
		
		FileSystem fs = FileSystem.get(conf);
		fs.get(conf);
		
		InputStream input = fs.open(new Path("/folder1/a1.tar.gz"));
		OutputStream output = new FileOutputStream("E:\\BigData\\ÎÄµµ\\a.tar.gz");
		IOUtils.copyBytes(input, output, conf);
		
		output.close();
		input.close();
		fs.close();
	}
	
	@Test
	public void DeleteTest() throws IOException {
		
		Configuration conf = new Configuration();
		conf.set("fs.defaultFS", "hdfs://172.16.26.111:9000");
		
		FileSystem fs = FileSystem.get(conf);
		
		//fs.delete(new Path("/folder1/a1.tar.gz"));
		fs.deleteOnExit(new Path("/folder1/a.tar.gz"));
		
		fs.close();
	}

	@Test
	public void DataNodeTest() {

	}

	@Test
	public void FileBlockLocationTest() {

	}
}
