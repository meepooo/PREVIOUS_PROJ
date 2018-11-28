package com.heima.myio;

import java.io.FileReader;
import java.io.IOException;

public class FileWriteDemo2 {
	public static void main(String[] args) {
//		System.out.println("helloworld");
		try {
			// FileWriter Usage
			// FileWriter fw = new FileWriter("F:\\file\\1.txt", true);
			// fw.write("Hello wqs\r\n");
			// String str="Hello 世界!aaabbbccc\r\n";
			// fw.write(str, 0, str.length());
			// char[] cbuf = str.toCharArray();
			// fw.write(cbuf, 0, cbuf.length);
			// fw.flush();
			// fw.close();

			// FileReader Usage
			FileReader fr = new FileReader("F:\\file\\HelloWorld.java");
			char[] cbuf = new char[10];
			// int len=1024;
			String str = "";
			while (fr.read(cbuf) != -1) {
				str += new String(cbuf);
				// System.out.print(cbuf);
			}
			System.out.println(str);
			// fr.read(cbuf);
			// String str=new String(cbuf);
			// System.out.println(str);
			fr.close();

		} catch (IOException e) {
			// TODO 自动生成的 catch 块
			e.printStackTrace();
		}
	}
}
