package com.webank.openapi.sdk.util;/**
 * Created by jonyang on 2016/1/11.
 */

import org.apache.http.client.CookieStore;
import org.apache.http.client.config.CookieSpecs;
import org.apache.http.client.config.RequestConfig;
import org.apache.http.config.Registry;
import org.apache.http.config.RegistryBuilder;
import org.apache.http.config.SocketConfig;
import org.apache.http.conn.socket.ConnectionSocketFactory;
import org.apache.http.conn.ssl.SSLConnectionSocketFactory;
import org.apache.http.conn.ssl.TrustSelfSignedStrategy;
import org.apache.http.impl.client.BasicCookieStore;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.impl.client.HttpClients;
import org.apache.http.impl.conn.PoolingHttpClientConnectionManager;
import org.apache.http.ssl.SSLContexts;

import javax.net.ssl.SSLContext;
import java.io.ByteArrayInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.security.KeyStore;
import java.security.KeyStoreException;
import java.util.concurrent.TimeUnit;

/**
 * Copyright (C) @2016 Webank Group Holding Limited
 * <p/>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
public class HttpClientUtils {
    public static CloseableHttpClient createHttpClientWithCert(KeyStore keyStore,String keyStorePassword,KeyStore trustStoreFile,
                                                               int connMaxTotal,
                                                               int connDefaultMaxPerRoute,
                                                               int validateInactivityMillSeconds,
                                                               int connEvictIdleConnectionsTimeoutMillSeconds) {
        SSLContext sslcontext = null;
        try {
            sslcontext = SSLContexts.custom()
                    .loadKeyMaterial(keyStore,keyStorePassword.toCharArray())
                    .loadTrustMaterial(trustStoreFile,new TrustSelfSignedStrategy()).build();
        } catch (Exception e) {
            throw new RuntimeException("key store fail", e);
        }

        // Allow TLSv1 protocol only
        SSLConnectionSocketFactory sslsf = new SSLConnectionSocketFactory(
                sslcontext,
                new String[]{"TLSv1"},
                null,
                SSLConnectionSocketFactory.getDefaultHostnameVerifier());

        // Create a registry of custom connection socket factories for supported
        // protocol schemes.
        Registry<ConnectionSocketFactory> socketFactoryRegistry = RegistryBuilder.<ConnectionSocketFactory>create()
                .register("https", sslsf)
                .build();


        // Create a connection manager with custom configuration.
        PoolingHttpClientConnectionManager connManager = new PoolingHttpClientConnectionManager(socketFactoryRegistry);

        // Create socket configuration
        SocketConfig socketConfig = SocketConfig.custom().setTcpNoDelay(true).build();// 小数据网络包
        // Configure the connection manager to use socket configuration either
        // by default or for a specific host.
        connManager.setDefaultSocketConfig(socketConfig);
        // Validate connections after 1 sec of inactivity
        connManager.setValidateAfterInactivity(validateInactivityMillSeconds);


        // Configure total max or per route limits for persistent connections
        // that can be kept in the pool or leased by the connection manager.
        connManager.setMaxTotal(connMaxTotal);
        connManager.setDefaultMaxPerRoute(connDefaultMaxPerRoute);

        // Use custom cookie store if necessary.
        CookieStore cookieStore = new BasicCookieStore();
        // Use custom credentials provider if necessary.
        //CredentialsProvider credentialsProvider = new BasicCredentialsProvider();
        // Create global request configuration
        RequestConfig defaultRequestConfig = RequestConfig.custom().setCookieSpec(CookieSpecs.DEFAULT)
                .setExpectContinueEnabled(true)
                .build();

        // Create an HttpClient with the given custom dependencies and
        // configuration.
        CloseableHttpClient httpclient;
        httpclient = HttpClients.custom().setConnectionManager(connManager)
                .setDefaultCookieStore(cookieStore)
                .setDefaultRequestConfig(defaultRequestConfig).evictExpiredConnections()
                .evictIdleConnections(connEvictIdleConnectionsTimeoutMillSeconds, TimeUnit.MILLISECONDS)
                .setSSLSocketFactory(sslsf).build();
        return httpclient;
    }
}
