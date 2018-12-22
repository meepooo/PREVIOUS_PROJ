package com.HDFS.RPC.server;

import java.io.IOException;

import org.apache.hadoop.HadoopIllegalArgumentException;
import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.ipc.RPC;
import org.apache.hadoop.ipc.Server;

public class RPCserver {

	public static void main(String[] args) throws HadoopIllegalArgumentException, IOException {
		// ����hadoop RPC���ʵ��server
		
		//����RPC Builder ����
		RPC.Builder builder = new RPC.Builder(new Configuration());
		
		//server����
		builder.setBindAddress("localhost");
		builder.setPort(7788);
		
		//����ӿ���ʵ����
		builder.setProtocol(RPCInterface.class);
		builder.setInstance(new RPCInterfaceImpl());
		
		Server server = builder.build();
		server.start();
	}

}
