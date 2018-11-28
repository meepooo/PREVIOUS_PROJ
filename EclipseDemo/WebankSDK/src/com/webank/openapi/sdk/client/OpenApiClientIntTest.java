package com.webank.openapi.sdk.client;/**
 * Created by jonyang on 2016/1/11.
 */

import com.webank.openapi.sdk.dto.WealthSyncClientInfoRequestDTO;
import com.webank.openapi.sdk.util.SignUtils;
import org.testng.Assert;
import org.testng.annotations.BeforeClass;
import org.testng.annotations.Test;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.net.URISyntaxException;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.util.ArrayList;
import java.util.List;

/**
 * Copyright (C) @2016 Webank Group Holding Limited
 * <p>
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * <p>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p>
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/**
 * 客户端测试类
 */
public class OpenApiClientIntTest {
    // jks generate command
    //keytool -importkeystore -storepass changeit -srckeystore T*.p12 -srcstoretype PKCS12 -destkeystore webank_keystore.jks -deststoretype JKS
    // !!!!!!!!! keystore password must match p12 password !!!!!!!!!
    //keytool -import -storepass changeit -alias webank-trust -file server*.crt -keystore webank_truststore.jks
    //keytool -list -keystore webank_keystore.jks
    //keytool -list -keystore webank_truststore.jks

    private OpenApiClient client;


    private void populateByteBuffer(File f, ByteBuffer bb) {
        FileInputStream fin = null;
        try {
            fin = new FileInputStream(f);
            FileChannel channel = fin.getChannel();
            while ((channel.read(bb)) > 0) {

            }
        } catch (Exception e) {
            Assert.fail(e.getMessage());
        } finally {
            if (fin != null) {
                try {
                    fin.close();
                } catch (IOException e) {

                }
            }
        }
    }

    @BeforeClass
    public void beforeClass() {
        String appId = "T0000003";
        String secret = "YJSDaX4j6s9k8UnGCNkHVXzIqPE8MqIkuDGGgdm6bwtXSaw5uEbUUWeMeH9eHzm4";
        String webankOpenApiUrlPrefix = "https://sit-svrapi.webank.com/l/api";

        File f;
        try {
            f = getResourceAsFile("/webank_keystore.jks");
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        long size = f.length();
        FileInputStream fin = null;
        ByteBuffer kbb = ByteBuffer.allocate((int) size);
        populateByteBuffer(f, kbb);

        try {
            f = getResourceAsFile("/webank_truststore.jks");
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        size = f.length();
        fin = null;
        ByteBuffer tbb = ByteBuffer.allocate((int) size);
        populateByteBuffer(f, tbb);

        byte[] keyStoreBytes = kbb.array();
        String keyStorePass = "changeit";
        byte[] trustStoreBytes = tbb.array();
        PasswordCallback scb = new PasswordCallback() {
            private String sourceSecret;

            @Override
            public String getPassword() {
                return this.sourceSecret;//可以在这里解密secret为明文
            }

            @Override
            public void setPassword(String secret) {
                this.sourceSecret = secret;//可以密文secret
            }
        };
        scb.setPassword(secret);

        PasswordCallback kcb = new PasswordCallback() {
            private String sourceSecret;

            @Override
            public String getPassword() {
                return this.sourceSecret;//可以在这里解密secret为明文
            }

            @Override
            public void setPassword(String secret) {
                this.sourceSecret = secret;//可以密文secret
            }
        };
        kcb.setPassword("App1234.");
        client = new OpenApiClient(appId, scb, webankOpenApiUrlPrefix, keyStoreBytes, kcb, trustStoreBytes);
    }

    @Test
    public void testGetAccessToken() {

        String accessToken = null;
        try {
            accessToken = client.getAccessToken();
            Assert.assertNotNull(accessToken);
            Assert.assertTrue(accessToken.trim().length() > 0);
        } catch (Exception e) {
            e.printStackTrace();
            Assert.fail(e.getMessage());
        }


    }

    @Test
    public void testGetTicket() {
        String accessToken = null;
        try {
            accessToken = client.getAccessToken();
            String loginTicket = client.getLoginTicket(accessToken, "hellouser");
            Assert.assertNotNull(loginTicket);
            Assert.assertTrue(loginTicket.trim().length() > 0);
            String signTicket = client.getSignTicket(accessToken);
            Assert.assertNotNull(signTicket);
            Assert.assertTrue(signTicket.trim().length() > 0);

        } catch (IOException e) {
            e.printStackTrace();
            Assert.fail(e.getMessage());
        }
    }

    @Test
    public void testGetSign() {
        try {
            String accessToken = client.getAccessToken();
            String signTicket = client.getSignTicket(accessToken);
            Assert.assertNotNull(signTicket);
            Assert.assertTrue(signTicket.trim().length() > 0);

            List<String> data = new ArrayList<String>();
            data.add("test");
            data.add("123456");
            String sign = SignUtils.sign(data, signTicket);
            Assert.assertNotNull(sign);
            Assert.assertTrue(sign.trim().length() > 0);
        } catch (IOException e) {
            e.printStackTrace();
            Assert.fail(e.getMessage());
        }
    }

    @Test
    public void testGetSignByGoogle() {
        try {
            String accessToken = client.getAccessToken();
            String signTicket = client.getSignTicket(accessToken);
            Assert.assertNotNull(signTicket);
            Assert.assertTrue(signTicket.trim().length() > 0);

            List<String> data = new ArrayList<String>();
            data.add("test");
            data.add("123456");
            String sign = SignUtils.signByGoogle(data, signTicket);
            Assert.assertNotNull(sign);
            Assert.assertTrue(sign.trim().length() > 0);
        } catch (IOException e) {
            e.printStackTrace();
            Assert.fail(e.getMessage());
        }
    }

    @Test
    public void testSyncClient() {
        try {
            String accessToken = client.getAccessToken();
            String signTicket = client.getSignTicket(accessToken);
            WealthSyncClientInfoRequestDTO dto = new WealthSyncClientInfoRequestDTO();
            dto.setName("彭劲松");
            dto.setIdNo("513721199110233619");
            dto.setIdType("01");
            dto.setOtherCardNo("4270380012345678");
            dto.setPhoneNo("13541210001");
            boolean b = client.syncWealthClient(dto, signTicket);
            Assert.assertTrue(b);


        } catch (IOException e) {
            e.printStackTrace();
            Assert.fail(e.getMessage());
        }
    }

    private File getResourceAsFile(String name) throws URISyntaxException {
        return new File(this.getClass().getResource(name).toURI());
    }
}
