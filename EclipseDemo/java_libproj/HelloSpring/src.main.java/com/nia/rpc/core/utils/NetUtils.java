package com.nia.rpc.core.utils;
import java.net.InetAddress;
import java.net.UnknownHostException;
/**
 * IP and Port Helper for RPC
 * Author  ֪��
 * Created by Auser on 2017/2/17.
 */
public class NetUtils {
    /**
     * �˴�ʵ�ֵĲ�����λ����ʱ�����������
     * ��Java��ȡ����IP��ַ����Ҫ����
     *1. ���������
     *2. �ų�loopback�豸����������
     *���Ƽ򵥵Ĵ��룬д��������ҪС��һЩ�ġ�
     * @return
     */
    public static String getLocalIp() {
        try {
            return InetAddress.getLocalHost().getHostAddress();
        } catch (UnknownHostException e) {
            e.printStackTrace();
        }
        return null;
    }
}