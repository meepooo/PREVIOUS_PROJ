/**
 * Copyright (C) @2016 Webank Group Holding Limited
 * <p/>
 * Licensed under the Apache License, Version 2.0 (the "License"); you may not use this file except
 * in compliance with the License. You may obtain a copy of the License at
 * <p/>
 * http://www.apache.org/licenses/LICENSE-2.0
 * <p/>
 * Unless required by applicable law or agreed to in writing, software distributed under the License
 * is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
 * or implied. See the License for the specific language governing permissions and limitations under
 * the License.
 */
package com.webank.openapi.sdk.util;

import java.security.MessageDigest;
import java.util.Collections;
import java.util.List;

import com.google.common.hash.Hashing;

import org.apache.commons.codec.Charsets;


/**
 * Created by jonyang on 2016/1/11.
 */
public class SignUtils {

    private final static char[] hexArray = "0123456789ABCDEF".toCharArray();

    private static String bytesToHex(byte[] bytes) {
        char[] hexChars = new char[bytes.length * 2];
        for (int j = 0; j < bytes.length; j++) {
            int v = bytes[j] & 0xFF;
            hexChars[j * 2] = hexArray[v >>> 4];
            hexChars[j * 2 + 1] = hexArray[v & 0x0F];
        }
        return new String(hexChars);
    }

    public static String sign(List<String> values, String signTicket) {
        if (values == null) {
            throw new NullPointerException("values is null");
        }

        values.removeAll(Collections.singleton(null));// remove null
        values.add(signTicket);
        java.util.Collections.sort(values);

        StringBuilder sb = new StringBuilder();
        for (String s : values) {
            sb.append(s);
        }
        try {
            MessageDigest md = MessageDigest.getInstance("sha1");
            md.update(sb.toString().getBytes("UTF-8"));
            String nativeSign = bytesToHex(md.digest());
            return nativeSign;
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }

    public static String signByGoogle(List<String> values, String signTicket) {
        if (values == null) {
            throw new NullPointerException("values is null");
        }

        values.removeAll(Collections.singleton(null));// remove null
        values.add(signTicket);
        java.util.Collections.sort(values);

        StringBuilder sb = new StringBuilder();
        for (String s : values) {
            sb.append(s);
        }
        return Hashing.sha1().hashString(sb, Charsets.UTF_8).toString().toUpperCase();
    }
}
