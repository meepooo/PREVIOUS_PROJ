package com.wraperdemo;

/*
 * 包装类
 */
public class WaitressWrap implements Waiter {

	Waiter waiter = null;

	public WaitressWrap(Waitress waiter) {
		this.waiter=waiter;
	}

	@Override
	public void service() {
		System.out.println("service包装类");
		waiter.service();
	}

}
