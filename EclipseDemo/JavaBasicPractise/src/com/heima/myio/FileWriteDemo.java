package com.heima.myio;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileWriteDemo {
	public static void main(String[] args) {
		try {
//			 FileWriter fw = new FileWriter("F:\\file\\1.txt",true);
//			 fw.write("helloworld\n我的世界");
//			 fw.flush();
//			 fw.close();

			FileReader fr = new FileReader("F:\\file\\1.txt");

			// 利用read(buf)读取
			char[] cbuf = new char[2];
			String str="";
			while ((fr.read(cbuf)) != -1) {
				str += new String(cbuf);
//				System.out.println(cbuf);
			}
			System.out.println(str);

			// 利用read()读取
			// int ch ;
			// while ( (ch = fr.read()) != -1) {
			// char c = (char)ch;
			// System.out.print(c+" ");
			// }
			fr.close();
		} catch (IOException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		}
		System.out.println();
	}
}
