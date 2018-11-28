package com.nia.rpc.example.server;
import com.nia.rpc.core.utils.NetUtils;
import com.nia.rpc.example.service.HelloWorld;
import com.nia.rpc.example.service.HelloWorldImpl;
import com.nia.rpc.factory.ServerFactoryBean;

import org.apache.curator.RetryPolicy;
import org.apache.curator.framework.CuratorFramework;
import org.apache.curator.framework.CuratorFrameworkFactory;
import org.apache.curator.retry.ExponentialBackoffRetry;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.ApplicationContext;
import org.springframework.context.annotation.Bean;
import org.springframework.context.support.ClassPathXmlApplicationContext;
/**
 * Author  知秋
 * Created by Auser on 2017/2/19.
 */
//@SpringBootApplication
public class SpringServerConfig {
    @Bean
    public HelloWorld hello() {
        return new HelloWorldImpl();
    }
    @Bean
    public ServerFactoryBean serverFactoryBean() {
        final ServerFactoryBean serverFactoryBean = new ServerFactoryBean();
        serverFactoryBean.setPort(9090);
        serverFactoryBean.setServiceInterface(HelloWorld.class);
       //此处自定义的注册名字就相当于注解了，未来迭代的时候会加入自定义注解方式
        serverFactoryBean.setServiceName("hello");
        serverFactoryBean.setServiceImpl(hello());
        serverFactoryBean.setZkConn("127.0.0.1:2181");
        /*new Thread(() -> {
            try {
                serverFactoryBean.start();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }, "RpcServer").start();*/
        serverFactoryBean.start();
        return serverFactoryBean;
    }
    public static void main(String[] args) {
    	
/*        final String connectString = "127.0.0.1:2181";
        RetryPolicy retryPolicy = new ExponentialBackoffRetry(1000, 3);
        CuratorFramework client = CuratorFrameworkFactory.newClient(connectString, retryPolicy);
        client.start();
        System.out.println("zk operation");
        client.close();*/

      
        SpringApplication.run(SpringServerConfig.class, "--server.port=8082");
    }
}