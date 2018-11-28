package com.nia.rpc.core.client;
import com.nia.rpc.core.protocol.Response;
import io.netty.channel.ChannelHandler;
import io.netty.channel.ChannelHandlerContext;
import io.netty.channel.SimpleChannelInboundHandler;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import java.util.concurrent.BlockingQueue;
import static com.nia.rpc.core.utils.ResponseMapHelper.responseMap;
/**
 * Author  ֪��
 * Created by Auser on 2017/2/18.
 */
@ChannelHandler.Sharable/*��ΪҪ�ڲ�ͬchannel�й���ʹ��responseMap��blockingQueue������Ҫ�Ӵ�ע��*/
public class RpcClientHandler extends SimpleChannelInboundHandler<Response> {
    private static final Logger LOGGER = LoggerFactory.getLogger(RpcClientHandler.class);
    //��Ϊ�˴����Ҫ���ã����ó��������ŵ�һ������������
   // public static ConcurrentMap<Long, BlockingQueue<Response>> responseMap = new ConcurrentHashMap<Long, BlockingQueue<Response>>();
    @Override
    protected void channelRead0(ChannelHandlerContext ctx, Response msg) throws Exception {
        //�˴���ҵ���߼������õ���Ӧid����������Ϣ������ӦblockingQueue��
        BlockingQueue<Response> blockingQueue = responseMap.get(msg.getRequestId());
        if (blockingQueue != null) {
            blockingQueue.put(msg);
        }
    }
    @Override
    public void exceptionCaught(ChannelHandlerContext ctx, Throwable cause) throws Exception {
        LOGGER.error("Exception caught on {}, ", ctx.channel(), cause);
        ctx.channel().close();
    }
}