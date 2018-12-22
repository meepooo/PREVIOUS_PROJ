package com.HDFS.RPC.server;

import java.io.IOException;

import org.apache.hadoop.ipc.ProtocolSignature;

public class RPCInterfaceImpl implements RPCInterface {

	@Override
	public String sayHello(String name) {
		System.out.println("********** 服务端被调用 ***********");
		return "hello" + name ;
	}

	@Override
	public ProtocolSignature getProtocolSignature(String arg0, long arg1, int arg2) throws IOException {
		// TODO Auto-generated method stub
		return new ProtocolSignature();
	}

	@Override
	public long getProtocolVersion(String arg0, long arg1) throws IOException {
		// TODO Auto-generated method stub
		return RPCInterface.versionID;
	}

}
