package test;

public class testMain {
	public static void main(String[] args) {
		
		/*
		String url="https://cvm.api.qcloud.com/v2/index.php";
		String para1= "Action=DescribeInstances";
		String para2= "&InstanceIds.0=ins-09dx96dg";
		String para3= "&Nonce=11886";
		String para4= "&Region=ap-guangzhou";
		String para5= "&SecretId=AKIDYEYtGY2gS5Wm9fncqs4JetwBKH2b7BC1";
		String para6= "&SignatureMethod=HmacSHA256";
		String para7= "&Timestamp=1465185768";
//		String para20= "&Signature=ccQqsqLgKGCR8oe5ZdBFMBZjRvmh1bLGXZ2uWgXAJRk=";
		
		Hash hash = new Hash("vfDLUVL4jHk3hNtDMQI2b2HPVRBi4RyK","GET"+url+"?"+para1+para2+para3+para4+para5+para6+para7+para8+para9+para10+para11+para12+para13+para14+para15);
		String sign = hash.getHash();
*/
		
		
		
		String url="https://cvm.api.qcloud.com/v2/index.php";
		String para1= "";
		String para2= "Action=DescribeRegions";
		String para3= "";
		String para4= "&InstanceIds.0=queue-rplmn2sy";
		String para5= "";
		String para6= "&Nonce=11886";
		String para7= "";
		String para8= "&Region=ap-guangzhou";
		String para9= "";
		String para10= "&SecretId=AKIDYEYtGY2gS5Wm9fncqs4JetwBKH2b7BC1";
		String para11= "";
		String para12= "&SignatureMethod=HmacSHA256";
		String para13= "";
		String para14= "&Timestamp=1465185768";
		String para15= "";

		
		Hash hash = new Hash("vfDLUVL4jHk3hNtDMQI2b2HPVRBi4RyK","GET"+url+"?"+para1+para2+para3+para4+para5+para6+para7+para8+para9+para10+para11+para12+para13+para14+para15);
		String sign = hash.getHash();
		System.out.println("sign");
		System.out.println(sign);
		String newsign=UrlUtil.getURLEncoderString(sign);
		System.out.println("newsign");
		System.out.println(newsign);
		
		String para20= "&Signature="+newsign;
		System.out.println("url");
		System.out.println(url+"?"+para1+para2+para3+para4+para5+para6+para7+para8+para9+para10+para11+para12+para13+para14+para15+para20);
		
	    //发送 GET 请求
//	    String s=HttpRequest.sendGet("https://cvm.api.qcloud.com/v2/index.php", "Action=DescribeInstances&SecretId=AKIDYEYtGY2gS5Wm9fncqs4JetwBKH2b7BC1&Region=ap-guangzhou&Timestamp=1465055529&Nonce=59485&Sgnature=mysignature&SignatureMethod=HmacSHA256&instanceIds.0=ins-0hm4gvho&instanceIds.1=ins-8oby8q00&offset=0&limit=20&status=2&zoneId=10003");
	    String s=HttpRequest.sendGet(url,para1+para2+para3+para4+para5+para6+para7+para8+para9+para10+para11+para12+para13+para14+para15+para20);
	    System.out.println(s);
	    
	    
	    //发送 POST 请求
//	    String sr=HttpRequest.sendPost("https://cmq-queue-region.api.qcloud.com", "key=123&v=456");
//	    System.out.println(sr);
	}
}