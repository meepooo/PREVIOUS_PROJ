package com.HDFS.RPC.server;

import org.apache.hadoop.ipc.VersionedProtocol;

public interface RPCInterface extends VersionedProtocol{

	// versionID
	// static可以直接调用接口名.versionID
	public static long versionID = 1;
	
	public String sayHello(String name) ;
}
