package com.nia.rpc.core.client;
import com.google.common.base.Splitter;
import com.nia.rpc.core.exception.RequestTimeoutException;
import com.nia.rpc.core.protocol.Request;
import com.nia.rpc.core.protocol.Response;
import com.nia.rpc.core.rpcproxy.CglibRpcProxy;
import com.nia.rpc.core.rpcproxy.RpcProxy;
import com.nia.rpc.core.utils.ResponseMapHelper;
import io.netty.channel.Channel;
import io.netty.channel.EventLoopGroup;
import io.netty.channel.nio.NioEventLoopGroup;
import org.apache.commons.collections4.CollectionUtils;
import org.apache.curator.framework.CuratorFramework;
import org.apache.curator.framework.CuratorFrameworkFactory;
import org.apache.curator.framework.api.GetChildrenBuilder;
import org.apache.curator.framework.recipes.cache.PathChildrenCache;
import org.apache.curator.retry.ExponentialBackoffRetry;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import java.lang.reflect.Method;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicLong;
import static com.nia.rpc.core.utils.Constant.ZK_DATA_PATH;
/**
 * Author  ֪��
 * Created by Auser on 2017/2/18.
 */
public class ClientImpl implements Client{
    private static final Logger LOGGER = LoggerFactory.getLogger(ClientImpl.class);
    private static AtomicLong atomicLong = new AtomicLong();
    // ͨ���˷����ķ�������,��Ѱ�Ҷ�Ӧ�ķ����ṩ��
    private String serviceName;
    private int requestTimeoutMillis = 10 * 1000;
    private EventLoopGroup eventLoopGroup = new NioEventLoopGroup(2);
    private String zkConn;
    private CuratorFramework curatorFramework;
    private Class<? extends RpcProxy> clientProxyClass;
    private RpcProxy rpcProxy;
    // ���ChannelConf��һ��CopyOnWriteArrayList�У���������Ƕ���д�ٵĳ���(����ע�����ٻᷢ��״̬�ı�)�����Ժ�����
    public static CopyOnWriteArrayList<ChannelConf> channelWrappers = new CopyOnWriteArrayList<>();
    public ClientImpl(String serviceName) {
        this.serviceName = serviceName;
    }
    public void init() {
     
        curatorFramework = CuratorFrameworkFactory.newClient(getZkConn(), new ExponentialBackoffRetry(1000, 3));
        curatorFramework.start();
        final GetChildrenBuilder children = curatorFramework.getChildren();
        try {
            final String serviceZKPath = ZK_DATA_PATH + serviceName;
            //ͨ��curator API ��Path Cache�������һ��ZNode���ӽڵ�.
            // ��һ���ӽڵ����ӣ� ���£�ɾ��ʱ�� Path Cache��ı�����״̬��
            // ��������µ��ӽڵ㣬 �ӽڵ�����ݺ�״̬��
            // ��Ҳ�����������ֱ�ʾ�������� �Ǽ��path��
            PathChildrenCache pathChildrenCache = new PathChildrenCache(curatorFramework, serviceZKPath, true);
            pathChildrenCache.start();
            pathChildrenCache.getListenable().addListener((client, event) -> {
                LOGGER.info("Listen Event {}", event);
                //ͨ��·���õ��˽ڵ��¿����ṩ�����ʵ����ڵ����ӵ�ַ
                List<String> newServiceData = children.forPath(serviceZKPath);
                LOGGER.info("Server {} list change {}", serviceName, newServiceData);
                // �ر�ɾ�����ػ����ж����channel
                for (ChannelConf cw : channelWrappers) {
                    String connStr = cw.getConnStr();
                    if (!newServiceData.contains(connStr)) {
                        cw.close();
                        LOGGER.info("Remove channel {}", connStr);
                        channelWrappers.remove(cw);
                    }
                }
                // ���ӱ��ػ����в����ڵ����ӵ�ַ
                for (String connStr : newServiceData) {
                    boolean containThis = false;
                    for (ChannelConf cw : channelWrappers) {
                        if (connStr != null && connStr.equals(cw.getConnStr())) {
                            containThis = true;
                        }
                    }
                    if (!containThis) {
                        addNewChannel(connStr);
                    }
                }
            });
            List<String> strings = children.forPath(serviceZKPath);
            if (CollectionUtils.isEmpty(strings)) {
                throw new RuntimeException("No Service available for " + serviceName);
            }
            LOGGER.info("Found Server {} List {}", serviceName, strings);
            for (String connStr : strings) {
                try {
                    addNewChannel(connStr);
                } catch (Exception e) {
                    LOGGER.error("Add New Channel Exception", e);
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private void addNewChannel(String connStr) {
        try {
            List<String> strings = (List<String>) Splitter.on(":").split(connStr);
            if (strings.size() != 2) {
                throw new RuntimeException("Error connection str " + connStr);
            }
            String host = strings.get(0);
            int port = Integer.parseInt(strings.get(1));
            ChannelConf channelWrapper = new ChannelConf(host, port);
            channelWrappers.add(channelWrapper);
            LOGGER.info("Add New Channel {}, {}", connStr, channelWrapper);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    private ChannelConf selectChannel() {
        Random random = new Random();
        //ͬһ���������кü������ӵ�ַ��ʵ�֣��Ǿ�ѡһ�����ǣ���ʵΪ��Ⱥ�����ǣ�
        // ÿһ̨��������������ͬ�ķ���ѡ����һ�������ɣ�������nginx�����Ǿ�����ν��
        int size = channelWrappers.size();
        if (size < 1) {
            return null;
        }
        int i = random.nextInt(size);
        return channelWrappers.get(i);
    }
    @Override
    public Response sendMessage(Class<?> clazz, Method method, Object[] args) {
        Request request = new Request();
        request.setRequestId(atomicLong.incrementAndGet());
        request.setMethod(method.getName());
        request.setParams(args);
        request.setClazz(clazz);
        request.setParameterTypes(method.getParameterTypes());
        ChannelConf channelWrapper = selectChannel();
        if (channelWrapper == null) {
            Response response = new Response();
            RuntimeException runtimeException = new RuntimeException("Channel is not active now");
            response.setThrowable(runtimeException);
            return response;
        }
        //��channel���������Ӳ�Ϊ�յ�ʱ�򣬾Ϳ���ȡ��channel��
        Channel channel = null;
        try {
            channel = channelWrapper.getChannelObjectPool().borrowObject();
        } catch (Exception e) {
            e.printStackTrace();
        }
        if (channel == null) {
            Response response = new Response();
            RuntimeException runtimeException = new RuntimeException("Channel is not available now");
            response.setThrowable(runtimeException);
            return response;
        }
        try {
            channel.writeAndFlush(request);
            //����һ��ResponseMap����RequestId��Ϊ��������˻�Ӧ��������Ϊֵ������BlockingQueue��
            // ���һ�𱣴������ResponseMap��
            BlockingQueue<Response> blockingQueue = new ArrayBlockingQueue<>(1);
            ResponseMapHelper.responseMap.put(request.getRequestId(), blockingQueue);
            //poll(time):ȡ��BlockingQueue��������λ�Ķ���,����������ȡ��,����Ե�time�����涨��ʱ��,ȡ����ʱ����null
            return blockingQueue.poll(requestTimeoutMillis, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
          //����쳣���Զ���ģ�ֻ��Ϊ��˵��������˼
//            throw new RequestTimeoutException("service" + serviceName + " method " + method + " timeout");
        	e.printStackTrace();
        } finally {
            try {
                //�ó�ȥ��channel�ǵû���ȥ
                channelWrapper.getChannelObjectPool().returnObject(channel);
            } catch (Exception e) {
                e.printStackTrace();
            }
            //ɾ���˼�ֵ�ԣ�help GC
            ResponseMapHelper.responseMap.remove(request.getRequestId());
        }
		return null;
    }
    @Override
    public <T> T proxyInterface(Class<T> serviceInterface) {
        if (clientProxyClass == null) {
            clientProxyClass = CglibRpcProxy.class;
        }
        try {
            rpcProxy = clientProxyClass.newInstance();
        } catch (InstantiationException | IllegalAccessException e) {
            e.printStackTrace();
        }
        return rpcProxy.proxyInterface(this, serviceInterface);
    }
    @Override
    public void close() {
        //ע��Ҫ�������ط���һ�����ȹر�zookeeper�����ӣ���һ����channel�ض��������netty�ĶϿ��ر�
        if (curatorFramework != null) {
            curatorFramework.close();
        }
        try {
            for (ChannelConf cw : channelWrappers) {
                cw.close();
            }
        } finally {
            eventLoopGroup.shutdownGracefully();
        }
    }
    public String getZkConn() {
        return zkConn;
    }
    public void setZkConn(String zkConn) {
        this.zkConn = zkConn;
    }
    public int getRequestTimeoutMillis() {
        return requestTimeoutMillis;
    }
    public void setRequestTimeoutMillis(int requestTimeoutMillis) {
        this.requestTimeoutMillis = requestTimeoutMillis;
    }
}