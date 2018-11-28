/**
 * @author 琪
 * @version 1.00
 */

package hello;

import java.util.Arrays;
import java.util.Date;
import java.util.Scanner;
import java.io.*;

public class HelloWorld {
	public static void main(String[] args) {
		test printHello = new test();
		printHello.arrayTest();
//		System.out.println(new Date());
//		File file;
//		printHello.sayHello();
//		int x=5 ;
		
//		System.out.println("mainprint:"+printHello.times(x));
//		HelloWorld helloWorld = new HelloWorld();
//		helloWorld.hello();
	}
	void hello() {
		int a=100;
		System.out.println("xxx");
		Scanner in = new Scanner(System.in);
		String s = in.nextLine();  //读取一行
//        int i = in.nextInt();  //读取一个整型
//        double d = in.nextDouble();  //读取一个双精度型
        System.out.println("s="+s);
        String s2 = new String();

        in.close();
        s2 = "hello";
        if (s.compareTo(s2)==0) {
        	System.out.println("相等");
        }
        else
        	;
        	
		File file = new File("E:\\恒生开增值税发票.txt");
		Arrays.asList(a);
		try {
//			BufferedReader b1=new BufferedReader(new InputStreamReader(System.in));
			BufferedReader fileln
			   = new BufferedReader(new FileReader(file));
			String tmp = fileln.readLine();
			while (tmp != null) {
				System.out.println(tmp);
				tmp = fileln.readLine();
			}
			fileln.close();
		}catch (IOException e) {
			e.printStackTrace();
		}

		System.out.println("HelloWorld:"+a);
	}
}
