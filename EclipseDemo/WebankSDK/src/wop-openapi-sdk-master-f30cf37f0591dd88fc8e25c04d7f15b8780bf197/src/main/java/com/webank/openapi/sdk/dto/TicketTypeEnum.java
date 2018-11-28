package com.webank.openapi.sdk.dto;

/**
 * 票据类型
 *
 *
 */
public enum TicketTypeEnum {
    /**
     * 签名票据
     */
    SIGN("SIGN"),
    /**
     * 加密票据
     */
    ENCRYPT("ENCRYPT"),

    /**
     * 一次性票据
     * <p>
     * 一次性票据和一个KEY绑定使用，这个KEY一般是用户ID
     * </p>
     */
    NONCE("NONCE");

    private String value;

    TicketTypeEnum(String v) {
        value = v;
    }

    public String getValue() {
        return value;
    }

}
