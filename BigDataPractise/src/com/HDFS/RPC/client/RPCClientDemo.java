package com.HDFS.RPC.client;

import java.io.IOException;
import java.net.InetSocketAddress;

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.ipc.RPC;

import com.HDFS.RPC.server.RPCInterface;

public class RPCClientDemo {

	public static void main(String[] args) throws IOException {
		// 使用hadoop RPC框架调用 server
		RPCInterface client = RPC.getProxy(RPCInterface.class, 
				RPCInterface.versionID, 
				new InetSocketAddress("localhost",7788), 
				new Configuration());

		// 使用代理对象调用
		String result = client.sayHello("Lucky");
		System.out.println(result);
	}

}
