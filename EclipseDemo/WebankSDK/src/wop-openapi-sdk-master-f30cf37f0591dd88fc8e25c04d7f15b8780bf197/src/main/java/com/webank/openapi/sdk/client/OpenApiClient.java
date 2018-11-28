package com.webank.openapi.sdk.client;


import com.webank.openapi.sdk.dto.*;
import com.webank.openapi.sdk.exception.OpenApiException;
import com.webank.openapi.sdk.util.HttpClientUtils;
import com.webank.openapi.sdk.util.JsonMapper;
import com.webank.openapi.sdk.util.SignUtils;
import org.apache.commons.codec.Charsets;
import org.apache.commons.lang3.RandomStringUtils;
import org.apache.http.HttpEntity;
import org.apache.http.HttpHeaders;
import org.apache.http.HttpStatus;
import org.apache.http.NameValuePair;
import org.apache.http.client.methods.CloseableHttpResponse;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.utils.URLEncodedUtils;
import org.apache.http.entity.StringEntity;
import org.apache.http.impl.client.CloseableHttpClient;
import org.apache.http.message.BasicNameValuePair;
import org.apache.http.util.EntityUtils;

import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.charset.Charset;
import java.security.KeyStore;
import java.util.ArrayList;
import java.util.List;

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
public class OpenApiClient {
    private final static JsonMapper jsonMapper = new JsonMapper();
    private String appId;
    private String secret;
    private String webankOpenApiUrlPrefix;
    private CloseableHttpClient httpClient;

    public OpenApiClient(String appId, PasswordCallback passwordCallback, String webankOpenApiUrlPrefix, byte[] keyStoreBytes, PasswordCallback keyStorePass, byte[] trustStoreBytes) {
        this(appId, passwordCallback, webankOpenApiUrlPrefix, keyStoreBytes, keyStorePass, trustStoreBytes, 200, 5, 1000, 3000);
    }

    public OpenApiClient(String appId, PasswordCallback passwordCallback, String webankOpenApiUrlPrefix, byte[] keyStoreBytes, PasswordCallback keyStorePass, byte[] trustStoreBytes,
                         int connMaxTotal,
                         int connDefaultMaxPerRoute,
                         int validateInactivityMillSeconds,
                         int connEvictIdleConnectionsTimeoutMillSeconds) {
        this.appId = appId;
        this.secret = passwordCallback.getPassword();
        this.webankOpenApiUrlPrefix = webankOpenApiUrlPrefix;
        InputStream keyStoreInput = null;
        InputStream trustStoreInput = null;
        try {
            KeyStore keyStore = KeyStore.getInstance(KeyStore.getDefaultType());
            keyStoreInput = new ByteArrayInputStream(keyStoreBytes);//new FileInputStream(new File("D:\\project\\wop-openapi-sdk\\src\\intTest\\resources\\webank_keystore.jks"));
            keyStore.load(keyStoreInput, keyStorePass.getPassword().toCharArray());

            KeyStore trustStore = KeyStore.getInstance(KeyStore.getDefaultType());
            trustStoreInput = new ByteArrayInputStream(trustStoreBytes);//new FileInputStream(new File("D:\\project\\wop-openapi-sdk\\src\\intTest\\resources\\webank_truststore.jks"));
            trustStore.load(trustStoreInput, null);

            httpClient = HttpClientUtils.createHttpClientWithCert(keyStore, keyStorePass.getPassword(), trustStore, connMaxTotal, connDefaultMaxPerRoute, validateInactivityMillSeconds, connEvictIdleConnectionsTimeoutMillSeconds);
        } catch (Exception e) {
            throw new OpenApiException("create http client fail", e);
        } finally {
            if (keyStoreInput != null) {
                try {
                    keyStoreInput.close();
                } catch (IOException e) {
                    throw new OpenApiException("key store close fail", e);
                }
            }

            if (trustStoreInput != null) {
                try {
                    trustStoreInput.close();
                } catch (IOException e) {
                    throw new OpenApiException("trust store close fail", e);
                }
            }
        }

    }


    public static String sign(List<String> values, String signTicket) {
        return SignUtils.sign(values, signTicket);
    }


    public String getAccessToken() {
        String serviceUrl = "oauth2/access_token?";

        List<NameValuePair> nvps = new ArrayList<NameValuePair>();
        nvps.add(new BasicNameValuePair("app_id", this.appId));
        nvps.add(new BasicNameValuePair("secret", this.secret));
        nvps.add(new BasicNameValuePair("grant_type", "client_credential"));
        nvps.add(new BasicNameValuePair("version", "1.0.0"));
        String parametersFormat = URLEncodedUtils.format(nvps, Charsets.UTF_8);
        String requestUrl = webankOpenApiUrlPrefix + (webankOpenApiUrlPrefix.endsWith("/") ? "" : "/") + serviceUrl + parametersFormat;

        HttpGet httpGet = new HttpGet(requestUrl);

        CloseableHttpResponse response = null;
        try {
            httpGet.setHeader(HttpHeaders.CONTENT_TYPE, "application/json;charset=utf-8");
            response = httpClient.execute(httpGet);
            int statusCode = response.getStatusLine().getStatusCode();
            if (statusCode != HttpStatus.SC_OK) {
                throw new OpenApiException(new Exception("http response error:" + statusCode));
            }

            HttpEntity entity = response.getEntity();
            String entityString = EntityUtils.toString(entity);
            TokenResponseDTO tokenResponse = jsonMapper.fromJson(entityString, TokenResponseDTO.class);

            if (tokenResponse.getCode().equals("0")) {
                return tokenResponse.getAccessToken();
            } else {
                throw new OpenApiException("access fail", new Exception(tokenResponse.getMsg()));
            }
        } catch (IOException e) {
            throw new OpenApiException("get accessToken fail", e);
        } finally {
            if (response != null) {
                try {
                    response.close();
                } catch (IOException e) {
                    throw new OpenApiException("response close fail", e);
                }
            }
        }
    }

    public String getLoginTicket(String accessToken, String userId) throws IOException {
        List<TicketDTO> tickets = getTickets(TicketTypeEnum.NONCE.getValue(), accessToken, userId);
        TicketDTO nonce = tickets.get(0);
        return nonce.getValue();
    }

    public String getSignTicket(String accessToken) throws IOException {
        TicketDTO sign = getTickets(TicketTypeEnum.SIGN.getValue(), accessToken, "").get(0);
        return sign.getValue();
    }

    private List<TicketDTO> getTickets(String ticketEnums, String accessToken, String userId) {
        String serviceUrl = "oauth2/api_ticket?";

        List<NameValuePair> nvps = new ArrayList<NameValuePair>();
        nvps.add(new BasicNameValuePair("app_id", this.appId));
        nvps.add(new BasicNameValuePair("access_token", accessToken));
        nvps.add(new BasicNameValuePair("type", ticketEnums));
        nvps.add(new BasicNameValuePair("version", "1.0.0"));
        nvps.add(new BasicNameValuePair("user_id", userId));


        String parametersFormat = URLEncodedUtils.format(nvps, Charsets.UTF_8);
        String requestUrl = webankOpenApiUrlPrefix + (webankOpenApiUrlPrefix.endsWith("/") ? "" : "/") + serviceUrl + parametersFormat;

        HttpGet httpGet = new HttpGet(requestUrl);
        CloseableHttpResponse response = null;
        try {
            httpGet.setHeader(HttpHeaders.CONTENT_TYPE, "application/json;charset=utf-8");
            response = httpClient.execute(httpGet);
            int statusCode = response.getStatusLine().getStatusCode();
            if (statusCode != HttpStatus.SC_OK) {
                throw new OpenApiException(new Exception("http response error:" + statusCode));
            }

            HttpEntity entity = response.getEntity();
            String entityString = EntityUtils.toString(entity);
            TicketResponseDTO ticketResponseDTO = jsonMapper.fromJson(entityString, TicketResponseDTO.class);
            if (ticketResponseDTO.getCode().equals("0")) {
                return ticketResponseDTO.getTickets();
            } else {
                throw new OpenApiException("access fail", new Exception(ticketResponseDTO.getMsg()));
            }
        } catch (IOException e) {
            throw new OpenApiException("get getTickets fail", e);
        } finally {
            if (response != null) {
                try {
                    response.close();
                } catch (IOException e) {
                    throw new OpenApiException("response close fail", e);
                }
            }
        }
    }


    public boolean syncWealthClient(WealthSyncClientInfoRequestDTO dto, String signTicket) {
        String serviceUrl = "wealth/server/syncClient?";
        String nonce = RandomStringUtils.randomAlphabetic(32);

        String json = "";
        try {
            json = jsonMapper.toJson(dto);
        } catch (IOException e) {
            throw new OpenApiException("json mapper error", e);
        }


        List<String> data = new ArrayList<String>();
        data.add(this.appId);
        data.add(nonce);
        data.add("1.0.0");
        data.add(json);
        String sign = SignUtils.sign(data, signTicket);

        List<NameValuePair> nvps = new ArrayList<NameValuePair>();
        nvps.add(new BasicNameValuePair("app_id", this.appId));
        nvps.add(new BasicNameValuePair("nonce", nonce));
        nvps.add(new BasicNameValuePair("version", "1.0.0"));
        nvps.add(new BasicNameValuePair("sign", sign));

        String parametersFormat = URLEncodedUtils.format(nvps, Charsets.UTF_8);
        String requestUrl = webankOpenApiUrlPrefix + (webankOpenApiUrlPrefix.endsWith("/") ? "" : "/") + serviceUrl + parametersFormat;
        System.out.println(requestUrl);

        HttpPost httpPost = new HttpPost(requestUrl);
        CloseableHttpResponse response = null;
        try {
            httpPost.setHeader(HttpHeaders.CONTENT_TYPE, "application/json;charset=utf-8");
            StringEntity jsonEntity = new StringEntity(json, Charset.forName("utf-8"));
            httpPost.setEntity(jsonEntity);
            response = httpClient.execute(httpPost);
            int statusCode = response.getStatusLine().getStatusCode();
            if (statusCode != HttpStatus.SC_OK) {
                throw new OpenApiException(new Exception("http response error:" + statusCode));
            }

            HttpEntity entity = response.getEntity();
            String entityString = EntityUtils.toString(entity);
            BaseResponseDTO baseResponseDTO = jsonMapper.fromJson(entityString, BaseResponseDTO.class);
            if (baseResponseDTO.getCode().equals("0")) {
                return true;
            } else {
                return false;
            }
        } catch (IOException e) {
            throw new OpenApiException("get getTickets fail", e);
        } finally {
            if (response != null) {
                try {
                    response.close();
                } catch (IOException e) {
                    throw new OpenApiException("response close fail", e);
                }
            }
        }


    }


}
