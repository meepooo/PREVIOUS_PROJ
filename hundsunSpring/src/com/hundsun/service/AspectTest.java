package com.hundsun.service;

import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;
import org.aspectj.lang.annotation.Pointcut;
import org.springframework.stereotype.Component;

@Aspect
@Component
public class AspectTest {

	@Before(value = "AspectTest.pointcut()")
	public void aspectBefore() {
		System.out.println("aspectBefore()");
	}
	
	@After(value = "AspectTest.pointcut()")
	public void aspectAfter() {
		System.out.println("aspectAfter()");
	}
	
	@Pointcut(value="execution(* com.hundsun.service.ServiceTest.service())")
	public void pointcut() {}
}
