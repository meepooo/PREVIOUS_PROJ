package test;

import java.io.UnsupportedEncodingException;  
import javax.crypto.Mac;  
import javax.crypto.spec.SecretKeySpec;  
import org.apache.wicket.util.crypt.Base64UrlSafe;  
  
public class testsign {  
     public static void main(String[] args) {  
        String key = "f85b8b30f73eb2bf5d8063a9224b5e90";  
      String toHash =  "GET"+"\n"+"Thu, 09 Aug 2012 13:33:46 +0000"+"\n"+"/ApiChannel/Report.m";  
      //String toHashUtf8 = URLEncoder.encode(toHash, "UTF-8");  
        String res = hmac_sha1(toHash, key);  
        //System.out.print(res+"\n");  
          
        String signature;  
        try {  
            signature = new String(Base64UrlSafe.encodeBase64(res.getBytes()),"UTF-8");  
            signature = appendEqualSign(signature);  
            System.out.print(signature);  
        } catch (UnsupportedEncodingException e) {  
            e.printStackTrace();  
        }  
    }  
      
    public static String hmac_sha1(String value, String key) {  
        try {  
            // Get an hmac_sha1 key from the raw key bytes  
            byte[] keyBytes = key.getBytes();             
            SecretKeySpec signingKey = new SecretKeySpec(keyBytes, "HmacSHA1");  
  
            // Get an hmac_sha1 Mac instance and initialize with the signing key  
            Mac mac = Mac.getInstance("HmacSHA1");  
            mac.init(signingKey);  
  
            // Compute the hmac on input data bytes  
            byte[] rawHmac = mac.doFinal(value.getBytes());  
  
            // Convert raw bytes to Hex  
            String hexBytes = byte2hex(rawHmac);  
            return hexBytes;  
        } catch (Exception e) {  
            throw new RuntimeException(e);  
        }  
    }  
  
    private static String byte2hex(final byte[] b){  
        String hs="";  
        String stmp="";  
        for (int n=0; n<b.length; n++){  
            stmp=(java.lang.Integer.toHexString(b[n] & 0xFF));  
            if (stmp.length()==1) hs=hs+"0"+stmp;  
                else hs=hs+stmp;  
        }  
        return hs;  
    }     
      
    private static String appendEqualSign(String s){  
        int len = s.length();  
        int appendNum = 8 - (int)(len/8);  
        for (int n=0; n<appendNum; n++){  
            s += "%3D";  
        }  
        return s;  
    }  
}  