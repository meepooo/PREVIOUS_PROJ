package com.qcloud.cmq;

import java.util.List;
import java.util.ArrayList;
import java.util.TreeMap;
import java.lang.Integer;

import com.qcloud.cmq.*;
import com.qcloud.cmq.Json.*;

/**
 * Queue class.
 *
 * @author York.
 *         Created 2016�?9�?26�?.
 */
public class Queue{
	protected String queueName;
	protected CMQClient client;
	
	
	Queue(String queueName, CMQClient client){
		this.queueName = queueName;
		this.client = client;
	}
	
	/**
	 * 设置队列属�??
	 *
	 * @param meta        队列属�?�参�?
	 * @throws CMQClientException
	 * @throws CMQServerException
	 */
	public void setQueueAttributes(QueueMeta meta) throws Exception {
		TreeMap<String, String> param = new TreeMap<String, String>();

		param.put("queueName",this.queueName);
		
		if(meta.maxMsgHeapNum > 0)
			param.put("maxMsgHeapNum",Integer.toString(meta.maxMsgHeapNum));
		if(meta.pollingWaitSeconds > 0)
			param.put("pollingWaitSeconds",Integer.toString(meta.pollingWaitSeconds));
		if(meta.visibilityTimeout > 0)
			param.put("visibilityTimeout",Integer.toString(meta.visibilityTimeout));
		if(meta.maxMsgSize > 0)
			param.put("maxMsgSize",Integer.toString(meta.maxMsgSize));
		if(meta.msgRetentionSeconds > 0)
			param.put("msgRetentionSeconds",Integer.toString(meta.msgRetentionSeconds));
		
		String result = this.client.call("SetQueueAttributes", param);
		JSONObject jsonObj = new JSONObject(result);
		int code = jsonObj.getInt("code");
		if(code != 0)
			throw new CMQServerException(code,jsonObj.getString("message"),jsonObj.getString("requestId"));
	}
	
	/**
	 * 获取队列属�??
	 *
	 * @return        返回的队列属性参�?
	 * @throws CMQClientException
	 * @throws CMQServerException
	 */
	public QueueMeta getQueueAttributes() throws Exception {
		TreeMap<String, String> param = new TreeMap<String, String>();

		param.put("queueName",this.queueName);
		String result = this.client.call("GetQueueAttributes", param);
		JSONObject jsonObj = new JSONObject(result);
		int code = jsonObj.getInt("code");
		if(code != 0)
			throw new CMQServerException(code,jsonObj.getString("message"),jsonObj.getString("requestId"));

		QueueMeta meta = new QueueMeta();
		meta.maxMsgHeapNum = jsonObj.getInt("maxMsgHeapNum");
		meta.pollingWaitSeconds = jsonObj.getInt("pollingWaitSeconds");
		meta.visibilityTimeout = jsonObj.getInt("visibilityTimeout");
		meta.maxMsgSize = jsonObj.getInt("maxMsgSize");
		meta.msgRetentionSeconds = jsonObj.getInt("msgRetentionSeconds");
		meta.createTime = jsonObj.getInt("createTime");
		meta.lastModifyTime = jsonObj.getInt("lastModifyTime");
		meta.activeMsgNum = jsonObj.getInt("activeMsgNum");
		meta.inactiveMsgNum = jsonObj.getInt("inactiveMsgNum");
		meta.rewindmsgNum = jsonObj.getInt("rewindMsgNum");
		meta.minMsgTime = jsonObj.getInt("minMsgTime");
		meta.delayMsgNum = jsonObj.getInt("delayMsgNum");
		
		
		return meta;
	}
	
	/**
	 * 发�?�消�?
	 *
	 * @param msgBody     消息内容
	 * @return            服务器返回的消息唯一标识
	 * @throws CMQClientException
	 * @throws CMQServerException
	 */
    public String sendMessage(String msgBody) throws Exception {
        return sendMessage(msgBody, 0);
    }
	public String sendMessage(String msgBody ,int delayTime) throws Exception {
		TreeMap<String, String> param = new TreeMap<String, String>();

		param.put("queueName",this.queueName);
		param.put("msgBody",msgBody);
        param.put("delaySeconds",Integer.toString(delayTime));
		
		String result = this.client.call("SendMessage", param);
		JSONObject jsonObj = new JSONObject(result);
		int code = jsonObj.getInt("code");
		if(code != 0)
			throw new CMQServerException(code,jsonObj.getString("message"),jsonObj.getString("requestId"));
		
		return jsonObj.getString("msgId");
	}
	
	/**
	 * 批量发�?�消�?
	 *
	 * @param vtMsgBody   消息列表
	 * @return            服务器返回的消息唯一标识列表
	 * @throws CMQClientException
	 * @throws CMQServerException
	 */
    public List<String> batchSendMessage(List<String> vtMsgBody) throws Exception {
        return batchSendMessage(vtMsgBody, 0);
    }
	public List<String> batchSendMessage(List<String> vtMsgBody,int delayTime) throws Exception {

		if(vtMsgBody.isEmpty()  || vtMsgBody.size() > 16)
			throw new CMQClientException("Error: message size is empty or more than 16");
		
		TreeMap<String, String> param = new TreeMap<String, String>();

		param.put("queueName",this.queueName);
		for(int i=0;i<vtMsgBody.size();i++)
		{
			String k = "msgBody." + Integer.toString(i+1);
			param.put(k,vtMsgBody.get(i));
		}
		param.put("delaySeconds", Integer.toString(delayTime));

		String result = this.client.call("BatchSendMessage", param);
		JSONObject jsonObj = new JSONObject(result);
		int code = jsonObj.getInt("code");
		if(code != 0)
			throw new CMQServerException(code,jsonObj.getString("message"),jsonObj.getString("requestId"));
		
		ArrayList<String> vtMsgId = new ArrayList<String>();
		JSONArray jsonArray = jsonObj.getJSONArray("msgList");
		for(int i=0;i<jsonArray.length();i++)
		{	
			JSONObject obj = (JSONObject)jsonArray.get(i);
			vtMsgId.add(obj.getString("msgId"));
		}
		
		return vtMsgId;
	}
	
	/**
	 * 获取消息
	 *
	 * @param pollingWaitSeconds     请求�?长的Polling等待时间
	 * @return 						 服务器返回消�?
	 * @throws CMQClientException
	 * @throws CMQServerException
	 */
	public Message receiveMessage(int pollingWaitSeconds) throws Exception {
		TreeMap<String, String> param = new TreeMap<String, String>();

	    param.put("queueName",this.queueName);
        if(pollingWaitSeconds > 0)
        {
		param.put("UserpollingWaitSeconds",Integer.toString(pollingWaitSeconds *1000));
		param.put("pollingWaitSeconds", Integer.toString(pollingWaitSeconds) );
        }
        else
        {
		param.put("UserpollingWaitSeconds",Integer.toString(30000));
        }
		
		String result = this.client.call("ReceiveMessage", param);
		JSONObject jsonObj = new JSONObject(result);
		int code = jsonObj.getInt("code");
		if(code != 0)
			throw new CMQServerException(code,jsonObj.getString("message"),jsonObj.getString("requestId"));
		
		Message msg = new Message();
		msg.msgId = jsonObj.getString("msgId");
		msg.receiptHandle = jsonObj.getString("receiptHandle");
		msg.msgBody = jsonObj.getString("msgBody");
		msg.enqueueTime = jsonObj.getLong("enqueueTime");
		msg.nextVisibleTime = jsonObj.getLong("nextVisibleTime");
		msg.firstDequeueTime = jsonObj.getLong("firstDequeueTime");
		msg.dequeueCount = jsonObj.getInt("dequeueCount");
		
		return msg;
	}
	
	/**
	 * 批量获取消息
	 *
	 * @param numOfMsg               准备获取消息�?
	 * @param pollingWaitSeconds     请求�?长的Polling等待时间
	 * @return                       服务器返回消息列�?
	 * @throws CMQClientException
	 * @throws CMQServerException
	 */
	public List<Message> batchReceiveMessage(int numOfMsg, int pollingWaitSeconds) throws Exception {
		TreeMap<String, String> param = new TreeMap<String, String>();

		param.put("queueName",this.queueName);
		param.put("numOfMsg",Integer.toString(numOfMsg));
		if(pollingWaitSeconds > 0)
        {
		param.put("UserpollingWaitSeconds",Integer.toString(pollingWaitSeconds*1000));
		param.put("pollingWaitSeconds", Integer.toString(pollingWaitSeconds) );
        }
        else
        {
		param.put("UserpollingWaitSeconds",Integer.toString(30000));
        }
		String result = this.client.call("BatchReceiveMessage", param);
		JSONObject jsonObj = new JSONObject(result);
		int code = jsonObj.getInt("code");
		if(code != 0)
			throw new CMQServerException(code,jsonObj.getString("message"),jsonObj.getString("requestId"));
		
		ArrayList<Message> vtMessage = new ArrayList<Message>();
		
		JSONArray jsonArray = jsonObj.getJSONArray("msgInfoList");
		for(int i=0;i<jsonArray.length();i++)
		{	
			JSONObject obj = (JSONObject)jsonArray.get(i);
			Message msg = new Message();
			msg.msgId = obj.getString("msgId");
			msg.receiptHandle = obj.getString("receiptHandle");
			msg.msgBody = obj.getString("msgBody");
			msg.enqueueTime = obj.getLong("enqueueTime");
			msg.nextVisibleTime = obj.getLong("nextVisibleTime");
			msg.firstDequeueTime = obj.getLong("firstDequeueTime");
			msg.dequeueCount = obj.getInt("dequeueCount");
			
			vtMessage.add(msg);
		}
		
		return vtMessage;
	}
	
	/**
	 * 删除消息
	 *
	 * @param receiptHandle     消息句柄,获取消息时由服务器返�?
	 * @throws CMQClientException
	 * @throws CMQServerException
	 */
	public void deleteMessage(String receiptHandle) throws Exception {
		TreeMap<String, String> param = new TreeMap<String, String>();

		param.put("queueName",this.queueName);
		param.put("receiptHandle",receiptHandle);
		
		String result = this.client.call("DeleteMessage", param);
		JSONObject jsonObj = new JSONObject(result);
		int code = jsonObj.getInt("code");
		if(code != 0)
			throw new CMQServerException(code,jsonObj.getString("message"),jsonObj.getString("requestId"));
	}
	
	/**
	 * 批量删除消息
	 *
	 * @param receiptHandle     消息句柄列表，获取消息时由服务器返回
	 * @throws CMQClientException
	 * @throws CMQServerException
	 */
	public void batchDeleteMessage(List<String> vtReceiptHandle) throws Exception {
		if(vtReceiptHandle.isEmpty())
			return;
		
		TreeMap<String, String> param = new TreeMap<String, String>();

		param.put("queueName",this.queueName);
		for(int i=0;i<vtReceiptHandle.size();i++)
		{
			String k = "receiptHandle." + Integer.toString(i+1);
			param.put(k,vtReceiptHandle.get(i));
		}
		
		String result = this.client.call("BatchDeleteMessage", param);
		JSONObject jsonObj = new JSONObject(result);
		int code = jsonObj.getInt("code");
		if(code != 0)
			throw new CMQServerException(code,jsonObj.getString("message"),jsonObj.getString("requestId"));
	}
}
