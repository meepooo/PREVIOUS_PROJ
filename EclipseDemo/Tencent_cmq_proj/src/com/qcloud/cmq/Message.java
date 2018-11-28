package com.qcloud.cmq;

import java.util.Vector;

/**
 *  Message class .
 *
 * @author York.
 *         Created 2016�?9�?26�?.
 */
public class Message {
	
	/** 服务器返回的消息ID */
	public String msgId;
	/** 每次消费唯一的消息句柄，用于删除等操�? */
	public String receiptHandle;
	/** 消息�? */
	public String msgBody;
	/** 消息发�?�到队列的时间，�? 1970�?1�?1�? 00:00:00 000 �?始的毫秒�? */
    public long enqueueTime;
	/** 消息下次可见的时间，�? 1970�?1�?1�? 00:00:00 000 �?始的毫秒�? */
	public long nextVisibleTime;
	/** 消息第一次出队列的时间，�? 1970�?1�?1�? 00:00:00 000 �?始的毫秒�? */
	public long firstDequeueTime;
	/** 出队列次�? */
	public	int dequeueCount;
	public  Vector<String> msgTag;
}
