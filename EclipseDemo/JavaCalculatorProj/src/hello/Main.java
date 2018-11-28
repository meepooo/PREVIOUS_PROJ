package hello;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Main {
    public static void main(String[] args) {
            // 1. 创建spring的IOC容器对象
            ApplicationContext ctx = new ClassPathXmlApplicationContext("applicationContext.xml");
 
             // 2. 从IOC容器中获取Bean实例
             HelloWorld helloWorld = (HelloWorld) ctx.getBean("helloWorld");
             // 3. 调用实例中方法
             helloWorld.hello();
             
             HelloWorld helloWorld2 = (HelloWorld) ctx.getBean("helloWorld2");
             helloWorld2.hello();
    }
}