package com.lucky;

import java.io.IOException;
import java.util.List;

import org.apache.zookeeper.CreateMode;
import org.apache.zookeeper.KeeperException;
import org.apache.zookeeper.WatchedEvent;
import org.apache.zookeeper.Watcher;
import org.apache.zookeeper.Watcher.Event.EventType;
import org.apache.zookeeper.Watcher.Event.KeeperState;
import org.apache.zookeeper.ZooDefs.Ids;
import org.apache.zookeeper.ZooKeeper;
import org.apache.zookeeper.data.Stat;
import org.apache.zookeeper.proto.WatcherEvent;
import org.junit.Before;
import org.junit.Test;

public class ZKCli {

	int sessionTimeout = 5000 ;
	String connectString = "192.168.17.111:2181";
	ZooKeeper zooKeeper = null;
	
	@Before
	public void connect() {		
		try {
			zooKeeper = new ZooKeeper(connectString, sessionTimeout, new Watcher() {

				public void process(WatchedEvent event) {
					String path = event.getPath();
					KeeperState state = event.getState();
					EventType type = event.getType();
					WatcherEvent wrapper = event.getWrapper();
					
					System.out.println("ZkServer==="
							+ "path:" + path 
							+ ",state:" + state
							+ ",type:" + type
							+ ",wrapper:" + wrapper);					
				}
				
			});
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
	
	@Test
	public void createZnode() throws KeeperException, InterruptedException {
//		connect();
		System.out.println("createZnode");
//		String create = zooKeeper.create("/ZkApiTest", "This is a ZkApiTest".getBytes(), Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT);
		String create = zooKeeper.create("/ZkApiTest/ChildTest", "This is a ChildTest".getBytes(), Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT);
		System.out.println(create);
	}
	
	@Test
	public void setZnode() throws KeeperException, InterruptedException {
		System.out.println("setZnode");
		zooKeeper.setData("/ZkApiTest/ChildTest", "This is a ChildTest4".getBytes(), -1);
		zooKeeper.setData("/ZkApiTest/ChildTest", "This is a ChildTest100".getBytes(), -1);
	}
	
	@Test
	public void delZnode() throws InterruptedException, KeeperException {
		System.out.println("delZnode");
		zooKeeper.delete("/ZkApiTest/ChildTest", -1);
	}
	
	@Test 
	public void getZnode() throws KeeperException, InterruptedException {
//		connect();
		System.out.println("getZnode");
		List<String> children = zooKeeper.getChildren("/", true);
		for(String child : children) {
			System.out.println(child);
		}
		
	}
	
}
