package com.HDFS.RPC.server;

import org.apache.hadoop.ipc.VersionedProtocol;

public interface RPCInterface extends VersionedProtocol{

	// versionID
	// static����ֱ�ӵ��ýӿ���.versionID
	public static long versionID = 1;
	
	public String sayHello(String name) ;
}
