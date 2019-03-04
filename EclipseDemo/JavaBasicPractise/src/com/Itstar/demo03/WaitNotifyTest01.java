package com.Itstar.demo03;

/**
 * wait:等待 notify 唤醒 notify:唤醒等待的 wait
 * 
 * @author Young
 * @version 1.0
 * 
 */
public class WaitNotifyTest01 {
	// 初始化一个公共访问对象
	public static Object mutex = new Object();

	// 静态成员内部类 可以无条件访问成员变量 作为了一个线程
	static class Thread1 implements Runnable {

		@Override
		public void run() {
			// TODO Auto-generated method stub
			synchronized (mutex) {
				// 唤醒正在等待对象监视器的单个线程
				mutex.notify();
				System.out.println(Thread.currentThread().getName() + "调用了notify方法");

			}
			// 执行完同步代码块之后，释放锁 可以让其他线程访问操作 敏感数据了
			System.out.println(Thread.currentThread().getName() + "释放了锁");
		}
	}

	// 静态成员内部类 可以无条件访问成员变量 作为了一个线程
	static class Thread2 implements Runnable {

		@Override
		public void run() {
			// TODO Auto-generated method stub
			synchronized (mutex) {

				try {
					mutex.wait();
					System.out.println(Thread.currentThread().getName() + "在等待");

				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				// 被唤醒
				System.out.println(Thread.currentThread().getName() + "被唤醒，获得了锁");
			}
		}

	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		// 建立两个不同的线程 一个 notify 一个 wait
		// 相当于 Thread1 thread1=new Thread1()；
		Thread th1 = new Thread(new Thread1());
		// Thread2 thread2=new Thread2();
		Thread th2 = new Thread(new Thread2());
		th1.setName("线程1--有notify");
		th2.setName("线程2--有wait");
		// 虽然线程2 开启线程，但是 因为 wait 线程阻塞。
		th2.start();
		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		th1.start();

	}

}
