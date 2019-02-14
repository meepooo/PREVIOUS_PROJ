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
import org.apache.zookeeper.proto.WatcherEvent;
import org.junit.Before;
import org.junit.Test;

public class ZKDemo {

	private String connectString = "114.115.222.76:32770,114.115.222.76:32773,114.115.222.76:32776";
	private int sessionTimeout = 3000;
	ZooKeeper zooKeeper = null;
	private String parentNode = "/server";
	
	//����zkServer
	@Before
	public void init() {
		
		try {
			zooKeeper = new ZooKeeper(connectString, sessionTimeout, new Watcher() {
				//���ӿڻص��ļ���
				public void process(WatchedEvent event) {
					String path = event.getPath();
					KeeperState state = event.getState();
					EventType type = event.getType();
					WatcherEvent wrapper = event.getWrapper();
					
					System.out.println("path:" + path 
							+ ",state:" + state
							+ ",type:" + type
							+ ",wrapper:" + wrapper);
					
					//�����ӽڵ�
					try {
						List<String> childrens = zooKeeper.getChildren("/", true);
						
						for(String children:childrens) {
							System.out.println(children.toString());
						}
					} catch (KeeperException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
			});
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	//�����ӽڵ�,create
	@Test
	public void createZnode() throws KeeperException, InterruptedException {
		String childNode = zooKeeper.create("/lucky", "hello zookeeper".getBytes(), Ids.OPEN_ACL_UNSAFE, CreateMode.PERSISTENT);
		System.out.println(childNode);		
	}
	
	//��ȡ�ӽڵ㣬get
	@Test
	public void getZnode() throws KeeperException, InterruptedException {
		List<String> childrens = zooKeeper.getChildren("/", true);
		for(String children:childrens) {
			System.out.println(children);
		}
	}
	
	//ɾ���ڵ�,delete
	@Test
	public void deleteZnode() throws InterruptedException, KeeperException {
		// -1 ɾ�����а汾��
		int version = -1;
		zooKeeper.delete("/lucky", version);
	}
	
	//�޸�����
	@Test
	public void updateZnode() throws KeeperException, InterruptedException {
		zooKeeper.setData("/hello", "18".getBytes(), -1);
	}
	
	//ע��ڵ�
	@Test
	public void registerZnode(String hostname) throws KeeperException, InterruptedException {
		zooKeeper.create( parentNode + "", hostname.getBytes(), Ids.OPEN_ACL_UNSAFE, CreateMode.EPHEMERAL_SEQUENTIAL);
		zooKeeper.register(new Watcher() {			
			public void process(WatchedEvent event) {
				System.out.println("ע��һ���ڵ�");
			}
		});
	}
	
	//��������
	@Test
	public void build(String hostname) throws InterruptedException   {
		System.out.println(hostname + "����������");
		
		Thread.sleep(Long.MAX_VALUE);
	}
}
