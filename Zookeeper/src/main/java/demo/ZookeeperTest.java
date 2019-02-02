package demo;

import org.apache.curator.RetryPolicy;
import org.apache.curator.framework.CuratorFramework;
import org.apache.curator.framework.CuratorFrameworkFactory;
import org.apache.curator.framework.recipes.locks.InterProcessMutex;
import org.apache.curator.retry.ExponentialBackoffRetry;

public class ZookeeperTest {

	//����һ��������Դ
	private static int NUMBER = 10;
	private static void getNumber(){
		//ҵ�񷽷�
		System.out.println("*******ҵ�񷽷���ʼ*******");
		System.out.println("��ǰֵ��" + NUMBER);
		NUMBER --;
		
		//˯2�룬�ÿͻ�����Ȼ���������
		try {
			Thread.sleep(2000);
		} catch (InterruptedException e) {
			e.printStackTrace();
		}
		
		System.out.println("*******ҵ�񷽷�����*******\n\n");
	}
	
	
	public static void main(String[] args) {
		//����һ��retry policy�����Բ��ԣ�
		/*
		 * 1000: ÿ�εȴ���ʱ��
		 * 10:���ԵĴ���
		 */
		RetryPolicy policy = new ExponentialBackoffRetry(1000, 10);
		
		//����һ��ZK�Ŀͻ���
		CuratorFramework cf = CuratorFrameworkFactory.builder()
				              .connectString("192.168.157.111:2181")  //ZK�ĵ�ַ
				              .retryPolicy(policy)
				              .build();
		//�����ͻ���
		cf.start();
		
		//��ZK�ж���һ����
		final InterProcessMutex lock = new InterProcessMutex(cf, "/mylock");
		
		//����10���߳�
		for(int i=0;i<10;i++){
			new Thread(new Runnable() {
				
				public void run() {
					try{
						//����õ��������û�еõ�����ʹ��retrypolicy����
						lock.acquire();
						
						//���ʹ�����Դ
						getNumber();
					}catch(Exception ex){
						ex.printStackTrace();
					}finally{
						//�ͷ���
						try {
							lock.release();
						} catch (Exception e) {
							e.printStackTrace();
						}
					}
				}
			}).start();
		}
	}

}