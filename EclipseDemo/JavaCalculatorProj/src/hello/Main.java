package hello;

import org.springframework.context.ApplicationContext;
import org.springframework.context.support.ClassPathXmlApplicationContext;

public class Main {
    public static void main(String[] args) {
            // 1. ����spring��IOC��������
            ApplicationContext ctx = new ClassPathXmlApplicationContext("applicationContext.xml");
 
             // 2. ��IOC�����л�ȡBeanʵ��
             HelloWorld helloWorld = (HelloWorld) ctx.getBean("helloWorld");
             // 3. ����ʵ���з���
             helloWorld.hello();
             
             HelloWorld helloWorld2 = (HelloWorld) ctx.getBean("helloWorld2");
             helloWorld2.hello();
    }
}