package com.webank.openapi.sdk.util;/**
 * Created by jonyang on 2016/1/11.
 */

import com.fasterxml.jackson.annotation.JsonInclude;
import com.fasterxml.jackson.databind.DeserializationFeature;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.SerializationFeature;

import java.io.IOException;

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
public class JsonMapper {

    private static ObjectMapper mapper;

    public JsonMapper() {
        mapper = new ObjectMapper();
        // 设置输出时包含属性的风格
        mapper.setSerializationInclusion(JsonInclude.Include.NON_NULL);

        // 设置输入时忽略在JSON字符串中存在但Java对象实际没有的属性
        mapper.disable(DeserializationFeature.FAIL_ON_UNKNOWN_PROPERTIES);
        //
        mapper.disable(SerializationFeature.FAIL_ON_EMPTY_BEANS);

    }


    /**
     * Object可以是POJO，也可以是Collection或数组。 如果对象为Null, 返回"null". 如果集合为空集合, 返回"[]".
     *
     * @param object 对象
     * @return json串
     */
    public String toJson(Object object) throws IOException {

        try {
            return mapper.writeValueAsString(object);
        } catch (IOException e) {
            throw e;
        }
    }

    /**
     * 反序列化POJO或简单Collection如List&lt;String&gt;. 如果JSON字符串为Null或"null"字符串,
     * 返回Null. 如果JSON字符串为"[]", 返回空集合. 如需反序列化复杂Collection如List&lt;MyBean&gt;,
     * 请使用fromJson(String, JavaType)
     *
     * @param jsonString json串
     * @param clazz      对象类型
     * @param <T>        返回对象类型
     * @return 对象
     */
    public <T> T fromJson(String jsonString, Class<T> clazz) throws IOException {
        if (jsonString == null || jsonString.trim().length() == 0) {
            return null;
        }

        try {
            return mapper.readValue(jsonString, clazz);
        } catch (IOException e) {
            throw e;
        }
    }

}
