package com.nia.rpc.core.client;
import java.lang.reflect.Method;

import com.nia.rpc.core.protocol.Response;
/**
 * ����ķ�����ʹ��
 *
 * Author  ֪��
 * Created by Auser on 2017/2/18.
 */
public interface Client {
    Response sendMessage(Class<?> clazz, Method method, Object[] args);
    <T> T proxyInterface(Class<T> serviceInterface);
    void close();
}
