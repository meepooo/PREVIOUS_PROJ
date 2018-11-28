package com.nia.rpc.core.client;

import lombok.Getter;
import lombok.Setter;
/**
 * Author  ÖªÇï
 * Created by Auser on 2017/2/17.
 */
@Setter
@Getter
public class Response {
    private long requestId;
    private Object response;
    private Throwable throwable;
}