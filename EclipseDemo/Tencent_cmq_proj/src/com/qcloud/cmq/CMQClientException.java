package com.qcloud.cmq;

/**
 * TODO CMQClientException handle all exception caused by client side.
 *
 * @author York.
 *         Created 2016�?9�?30�?.
 */
public class CMQClientException extends RuntimeException {

    /**
     * TODO .
     *
     * @param message
     */
    public CMQClientException(String message) {
        super(message);
    }
}
