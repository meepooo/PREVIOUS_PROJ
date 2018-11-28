package com.nia.rpc.core.protocol;

import lombok.Data;
import lombok.Getter;
import lombok.Setter;
/**
 * Author  ÖªÇï
 * Created by Auser on 2017/2/17.
 */
@Data
public class Request {
    private long requestId;
    private Class<?> clazz;
    private String method;
    private Class<?>[] parameterTypes;
    private Object[] params;
    private long requestTime;
}