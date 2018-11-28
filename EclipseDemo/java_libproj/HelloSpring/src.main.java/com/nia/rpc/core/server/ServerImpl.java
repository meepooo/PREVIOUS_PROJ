package com.nia.rpc.core.server;
import com.nia.rpc.core.protocol.RpcDecoder;
import com.nia.rpc.core.protocol.RpcEncoder;
import com.nia.rpc.core.utils.NetUtils;
import io.netty.bootstrap.ServerBootstrap;
import io.netty.channel.Channel;
import io.netty.channel.ChannelFuture;
import io.netty.channel.ChannelInitializer;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import io.netty.channel.socket.SocketChannel;
import io.netty.channel.socket.nio.NioServerSocketChannel;
import io.netty.handler.logging.LogLevel;
import io.netty.handler.logging.LoggingHandler;

import org.apache.curator.RetryPolicy;
import org.apache.curator.framework.CuratorFramework;
import org.apache.curator.framework.CuratorFrameworkFactory;
import org.apache.curator.retry.ExponentialBackoffRetry;
import org.apache.zookeeper.CreateMode;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import static com.nia.rpc.core.utils.Constant.ZK_DATA_PATH;
/**
 * Author  ֪��
 * Created by Auser on 2017/2/17.
 */
public class ServerImpl implements Server {
    private static final Logger LOGGER = LoggerFactory.getLogger(ServerImpl.class);
    private String localIp;
    private int port;
    private boolean started = false;
    private Channel channel;
    private Object serviceImpl;
    private String serviceName;
    private String zkConn;
    private String serviceRegisterPath;
    private EventLoopGroup bossGroup = new NioEventLoopGroup();
    private EventLoopGroup workerGroup = new NioEventLoopGroup();
    private CuratorFramework curatorFramework;
    public ServerImpl(int port, Object serviceImpl, String serviceName) {
        this.port = port;
        this.serviceImpl = serviceImpl;
        this.serviceName = serviceName;
    }
    public ServerImpl(int port, Object serviceImpl, String serviceName, String zkConn) {
        this.port = port;
        this.serviceImpl = serviceImpl;
        this.serviceName = serviceName;
        this.zkConn = zkConn;
    }
    @Override
    public void start() {
        ServerBootstrap serverBootstrap = new ServerBootstrap();
        serverBootstrap.group(bossGroup,workerGroup)
                       .channel(NioServerSocketChannel.class)
                       .childHandler(new ChannelInitializer<SocketChannel>() {
                           @Override
                           protected void initChannel(SocketChannel socketChannel) throws Exception {
                               socketChannel.pipeline()
                                            .addLast(new LoggingHandler(LogLevel.INFO))
                                            .addLast(new RpcDecoder(10 * 1024 * 1024))
                                            .addLast(new RpcEncoder())
                                            .addLast(new RpcServerHandler(serviceImpl));
                           }
                       });
        try {
            //����bind�ȴ��ͻ���������
            ChannelFuture future = serverBootstrap.bind(port).sync();
            //����ע�����
            registerService();
            LOGGER.info("Server Started At {}", port);
            started = true;
            this.channel = future.channel();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }
    private void registerService() {
         zkConn = getZkConn();
         localIp = NetUtils.getLocalIp();
        String serviceIp=localIp+":"+port;
        /*CuratorFramework curatorFramework = CuratorFrameworkFactory.newClient(zkConn,
                new ExponentialBackoffRetry(1000, 3));*/
        /*RetryPolicy retryPolicy = new ExponentialBackoffRetry(1000, 3);
		CuratorFramework curatorFramework = CuratorFrameworkFactory.newClient(zkConn,retryPolicy);
        curatorFramework.start();*/
        final String connectString = "127.0.0.1:2181";
        RetryPolicy retryPolicy = new ExponentialBackoffRetry(1000, 3);
        CuratorFramework client = CuratorFrameworkFactory.newClient(connectString, retryPolicy);
        client.start();
        //������zkȻ��ʼע�����ڵ�
        String serviceBasePath=ZK_DATA_PATH+serviceName;
        //��ӻ�������ڵ�
        try {
            curatorFramework.create()
                            .creatingParentContainersIfNeeded()
                            .forPath(serviceBasePath);
        } catch (Exception e) {
            if (e.getMessage().contains("NodeExist")) {
                LOGGER.info("This Path Service has already Exist");
            } else {
                LOGGER.error("Create Path Error ", e);
                throw new RuntimeException("Register error");
            }
        }
        boolean registerSuccess=false;
        //�����ӳɹ�����ӱ�ʶ�������·���Ľڵ�
        while (!registerSuccess){
            try {
                curatorFramework.create()
                                .withMode(CreateMode.EPHEMERAL)
                                .forPath(serviceBasePath+"/"+serviceIp);
                //������Գ�������ע�ᣬ��ô�����ˣ������״̬�޸���
                registerSuccess = true;
            } catch (Exception e) {
                //��������ע��(Ҫ��ɾ���½ڵ�������ע��)
                try {
                    Thread.sleep(1000);
                } catch (InterruptedException e1) {
                    e1.printStackTrace();
                }
                LOGGER.info("Retry Register ZK, {}", e.getMessage());
                try {
                    curatorFramework.delete().forPath(serviceBasePath + "/" + serviceIp);
                } catch (Exception e1) {
                    e1.printStackTrace();
                }
            }
        }
    }
    @Override
    public void shutdown() {
        //��ͣ��ط�����߼�
        LOGGER.info("Shutting down server {}", serviceName);
        unRegister();
        if (curatorFramework != null) {
            curatorFramework.close();
        }
        bossGroup.shutdownGracefully();
        workerGroup.shutdownGracefully();
    }
    private void unRegister() {
        LOGGER.info("unRegister zookeeper");
        try {
            curatorFramework.delete().forPath(ZK_DATA_PATH+serviceName+"/"+localIp+":"+port);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    public String getZkConn() {
        return zkConn;
    }
    public void setZkConn(String zkConn) {
        this.zkConn = zkConn;
    }
    public String getLocalIp() {
        return localIp;
    }
    public void setLocalIp(String localIp) {
        this.localIp = localIp;
    }
    public Channel getChannel() {
        return channel;
    }
    public void setChannel(Channel channel) {
        this.channel = channel;
    }
}