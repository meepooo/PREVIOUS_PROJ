package com.nia.rpc.factory;
import com.nia.rpc.core.bootstrap.ServerBuilder;
import com.nia.rpc.core.server.Server;
import com.nia.rpc.core.server.ServerImpl;
import lombok.Data;
import org.springframework.beans.factory.FactoryBean;
/**
 * Author  ֪��
 * Created by Auser on 2017/2/19.
 */
@Data
public class ServerFactoryBean implements FactoryBean<Object>{
    private Class<?> serviceInterface;
    private Object serviceImpl;
    private String ip;
    private int port;
    private String serviceName;
    private String zkConn;
    private ServerImpl rpcServer;
    //����ע�Ტ�ṩ
    public void start(){
        Server rpcServer = ServerBuilder
                .builder()
                .serviceImpl(serviceImpl)
                .serviceName(serviceName)
                .zkConn(zkConn)
                .port(port)
                .build();
        rpcServer.start();
    }
    //��������
    public void serviceOffline(){
        rpcServer.shutdown();
    }
    @Override
    public Object getObject() throws Exception {
        return this;
    }
    @Override
    public Class<?> getObjectType() {
        return this.getClass();
}
    @Override
    public boolean isSingleton() {
        return true;
    }
}