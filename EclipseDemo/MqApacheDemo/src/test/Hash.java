package test;
import javax.crypto.Mac;
import javax.crypto.spec.SecretKeySpec;
import org.apache.commons.codec.binary.Base64;

public class Hash {
	public String hashresult ;
	
	public String getHash() {
		return hashresult ;
	}
  public Hash(String secret, String message) {
    try {
     //String secret = "secret";
     //String message = "Message";

    //	secret = "vfDLUVL4jHk3hNtDMQI2b2HPVRBi4RyK";
     //   message = "GEThttps://cvm.api.qcloud.com/v2/index.php?Action=DescribeInstances&InstanceIds.0=ins-09dx96dg&Nonce=11886&Region=ap-guangzhou&SecretId=AKIDYEYtGY2gS5Wm9fncqs4JetwBKH2b7BC1&SignatureMethod=HmacSHA256&Timestamp=1465185768";
    System.out.println(secret);
    System.out.println(message);
     Mac sha256_HMAC = Mac.getInstance("HmacSHA256");
     SecretKeySpec secret_key = new SecretKeySpec(secret.getBytes(), "HmacSHA256");
     sha256_HMAC.init(secret_key);

     hashresult = Base64.encodeBase64String(sha256_HMAC.doFinal(message.getBytes()));
     System.out.println(hashresult);
    }
    catch (Exception e){
     System.out.println("Error");
    }
   }
}