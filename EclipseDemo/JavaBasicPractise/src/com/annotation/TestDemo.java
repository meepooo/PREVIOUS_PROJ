package com.annotation;

import org.junit.Test;

/*
 * @author Lucky
 */

@Deprecated
@SuppressWarnings("unused")
public class TestDemo extends People {

	@Override
	@Deprecated
	@Test(timeout=3)
	public void test1() {
		
		int id;
		
		System.out.println("test111111");
	}

	@Override
	public void test2() {
		String name;
//		test1();
	}
	
	@AnnotationDemo("hello test3")
	public void test3() {
		
	}
	
	@AnnotationDemo("hello test4")
	public void test4() {
		
	}
}
