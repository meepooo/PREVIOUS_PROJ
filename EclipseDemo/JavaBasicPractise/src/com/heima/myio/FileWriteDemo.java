package com.heima.myio;

import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class FileWriteDemo {
	public static void main(String[] args) {
		try {
//			 FileWriter fw = new FileWriter("F:\\file\\1.txt",true);
//			 fw.write("helloworld\n�ҵ�����");
//			 fw.flush();
//			 fw.close();

			FileReader fr = new FileReader("F:\\file\\1.txt");

			// ����read(buf)��ȡ
			char[] cbuf = new char[2];
			String str="";
			while ((fr.read(cbuf)) != -1) {
				str += new String(cbuf);
//				System.out.println(cbuf);
			}
			System.out.println(str);

			// ����read()��ȡ
			// int ch ;
			// while ( (ch = fr.read()) != -1) {
			// char c = (char)ch;
			// System.out.print(c+" ");
			// }
			fr.close();
		} catch (IOException e) {
			// TODO �Զ����ɵ� catch ��
			e.printStackTrace();
		}
		System.out.println();
	}
}
