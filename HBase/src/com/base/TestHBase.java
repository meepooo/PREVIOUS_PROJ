package com.base;

import java.io.IOException;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.hbase.HColumnDescriptor;
import org.apache.hadoop.hbase.HTableDescriptor;
import org.apache.hadoop.hbase.MasterNotRunningException;
import org.apache.hadoop.hbase.TableName;
import org.apache.hadoop.hbase.ZooKeeperConnectionException;
import org.apache.hadoop.hbase.client.Connection;
import org.apache.hadoop.hbase.client.ConnectionFactory;
import org.apache.hadoop.hbase.client.Get;
import org.apache.hadoop.hbase.client.HBaseAdmin;
import org.apache.hadoop.hbase.client.HTable;
import org.apache.hadoop.hbase.client.Put;
import org.apache.hadoop.hbase.client.Result;
import org.apache.hadoop.hbase.client.ResultScanner;
import org.apache.hadoop.hbase.client.Scan;
import org.apache.hadoop.hbase.util.Bytes;
import org.junit.Test;

public class TestHBase {

	@Test
	public void testCreateTable() throws MasterNotRunningException, ZooKeeperConnectionException, IOException {
		// config
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "172.16.26.111");
		
		// HBase client
		HBaseAdmin client = new HBaseAdmin(conf);
//		Connection client = ConnectionFactory.createConnection(conf);
		
		// 指定表的描述符
		HTableDescriptor htd = new HTableDescriptor(TableName.valueOf("mytable"));
		
		// 指定列族
		htd.addFamily(new HColumnDescriptor("info"));
		htd.addFamily(new HColumnDescriptor("grade"));
		
		System.out.println("helloworld1");
		client.createTable(htd);
		System.out.println("helloworld2");
		client.close();
	}
	
	@Test
	public void testPutTable() throws IOException {
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "172.16.26.111");
		
		// get client
		HTable client = new HTable(conf, "Student");
		Put put = new Put(Bytes.toBytes("info"));
		put.addColumn(Bytes.toBytes("info"), Bytes.toBytes("name"), Bytes.toBytes("Tom"));
		
		client.put(put);
		client.close();
	}
	
	@Test
	public void testGetTable() throws IOException {
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "172.16.26.111");
		
		// get client
		HTable client = new HTable(conf, "Student");
		
		Get get = new Get(Bytes.toBytes("info"));
		
		Result r = client.get(get);
		
		r.getValue(Bytes.toBytes("info"), Bytes.toBytes("name"));
		
		String name = r.toString();
		
		System.out.println(name);
		
		client.close();
	}
	
	@Test
	public void testScanData() throws IOException {
		Configuration conf = new Configuration();
		conf.set("hbase.zookeeper.quorum", "172.16.26.111");
		
		// get client
		HTable client = new HTable(conf, "Student");

		Scan scan = new Scan();
		//过滤器 filter
		
		//通过扫描器查询所有的数据，相当于JDBC的ResultSet
		ResultScanner rs = client.getScanner(scan);
		
		for(Result r:rs) {
			r.getValue(Bytes.toBytes("info"), Bytes.toBytes("name"));
			
			String name = r.toString();
			
			System.out.println(name);
		}
	}	
}
