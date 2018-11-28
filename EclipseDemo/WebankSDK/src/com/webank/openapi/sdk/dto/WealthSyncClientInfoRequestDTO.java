package com.webank.openapi.sdk.dto;/**
 * Created by jonyang on 2016/1/19.
 */

import com.fasterxml.jackson.annotation.JsonProperty;

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
public class WealthSyncClientInfoRequestDTO extends BaseRequestDTO {
    private String name;
    @JsonProperty("id_type")
    private String idType;
    @JsonProperty("id_no")
    private String idNo;
    @JsonProperty("phone_no")
    private String phoneNo;
    @JsonProperty("other_card_no")
    private String otherCardNo;

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getIdType() {
        return idType;
    }

    public void setIdType(String idType) {
        this.idType = idType;
    }

    public String getIdNo() {
        return idNo;
    }

    public void setIdNo(String idNo) {
        this.idNo = idNo;
    }

    public String getPhoneNo() {
        return phoneNo;
    }

    public void setPhoneNo(String phoneNo) {
        this.phoneNo = phoneNo;
    }

    public String getOtherCardNo() {
        return otherCardNo;
    }

    public void setOtherCardNo(String otherCardNo) {
        this.otherCardNo = otherCardNo;
    }
}
