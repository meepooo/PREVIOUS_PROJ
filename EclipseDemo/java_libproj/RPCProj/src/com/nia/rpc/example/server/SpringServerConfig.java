package com.nia.rpc.example.server;
import com.nia.rpc.core.utils.NetUtils;
import com.nia.rpc.example.service.HelloWorld;
import com.nia.rpc.example.service.HelloWorldImpl;
import com.nia.rpc.factory.ServerFactoryBean;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.context.annotation.Bean;
/**
 * Author  ֪��
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
       //�˴��Զ����ע�����־��൱��ע���ˣ�δ��������ʱ�������Զ���ע�ⷽʽ
        serverFactoryBean.setServiceName("hello");
        serverFactoryBean.setServiceImpl(hello());
        serverFactoryBean.setZkConn("127.0.0.1:2181");
        new Thread(() -> {
            try {
                serverFactoryBean.start();
            } catch (Exception e) {
                e.printStackTrace();
            }
        }, "RpcServer").start();
        return serverFactoryBean;
    }
    public static void main(String[] args) {
       
        SpringApplication.run(SpringServerConfig.class, "--server.port=8082");
    }
}