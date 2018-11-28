package com.nia.rpc.core.rpcproxy;
import com.nia.rpc.core.client.Client;
import net.sf.cglib.proxy.Enhancer;
import net.sf.cglib.proxy.MethodInterceptor;
import net.sf.cglib.proxy.MethodProxy;
import java.lang.reflect.Method;
/**
 * Author  ֪��
 * Created by Auser on 2017/2/18.
 */
public class CglibRpcProxy implements RpcProxy {
    @Override
    public <T> T proxyInterface(Client client, Class<T> serviceInterface) {
        Enhancer enhancer = new Enhancer();
        enhancer.setSuperclass(serviceInterface);
        enhancer.setCallback(new CglibInteceptor(client, serviceInterface));
        Object enhancedObject = enhancer.create();
        return (T)enhancedObject;
    }
    /**
     * �����̬�ڲ�������Method��cglib����
     */
    private static class CglibInteceptor implements MethodInterceptor {
        //�����ж���Ҫ����ķ�����ͨ�÷������ǵĻ��ʹ˷��ش˴��������������
        private static Method hashCodeMethod;
        private static Method equalsMethod;
        private static Method toStringMethod;
        static {
            try {
                hashCodeMethod = Object.class.getMethod("hashCode");
                equalsMethod = Object.class.getMethod("equals", Object.class);
                toStringMethod = Object.class.getMethod("toString");
            } catch (NoSuchMethodException e) {
                throw new NoSuchMethodError(e.getMessage());
            }
        }
        /**
         * ����⼸����������Ӧ�Ĳ���
         * @param proxy
         * @return
         */
        private int proxyHashCode(Object proxy) {
            return System.identityHashCode(proxy);
        }
        private boolean proxyEquals(Object proxy, Object other) {
            return (proxy == other);
        }
        private String proxyToString(Object proxy) {
            return proxy.getClass().getName() + '@' + Integer.toHexString(proxy.hashCode());
        }
        /**
         * ����rpc�ͻ��˺ʹ��������÷���Ľӿ�
         */
        private Client client;
        private Class<?> serviceInterface;
        public CglibInteceptor(Client client, Class<?> serviceInterface) {
            this.client = client;
            this.serviceInterface = serviceInterface;
        }
        @Override
        public Object intercept(Object o, Method method, Object[] args, MethodProxy proxy) throws Throwable {
            //�ȶԷ��������ж��Ƿ���ͨ�÷��������綼���ǣ������ͨ��client������
            if (hashCodeMethod.equals(method)) {
                return proxyHashCode(proxy);
            }
            if (equalsMethod.equals(method)) {
                return proxyEquals(proxy, args[0]);
            }
            if (toStringMethod.equals(method)) {
                return proxyToString(proxy);
            }
            return client.sendMessage(serviceInterface, method, args).getResponse();
        }
    }
}