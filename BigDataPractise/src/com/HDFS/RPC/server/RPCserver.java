package com.HDFS.RPC.server;

import java.io.IOException;

import org.apache.hadoop.HadoopIllegalArgumentException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.ipc.RPC;
import org.apache.hadoop.ipc.Server;

public class RPCserver {

	public static void main(String[] args) throws HadoopIllegalArgumentException, IOException {
		// 利用hadoop RPC框架实现server
		
		//利用RPC Builder 构造
		RPC.Builder builder = new RPC.Builder(new Configuration());
		
		//server参数
		builder.setBindAddress("localhost");
		builder.setPort(7788);
		
		//部署接口与实现类
		builder.setProtocol(RPCInterface.class);
		builder.setInstance(new RPCInterfaceImpl());
		
		Server server = builder.build();
		server.start();
	}

}
