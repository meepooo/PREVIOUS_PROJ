package com.advance;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStreamReader;

public class FileInputStreamDemo {
	public static void main(String[] args) throws IOException {
		File file = new File("F:\\github\\sylucky.github.io\\index.html");
		try {
			FileInputStream fis = new FileInputStream(file);
			// 按字节读
			if (1 == 0) {
				int data;
				while ((data = fis.read()) != -1)
					System.out.print((char) data);
			}

			//读多个字符
			if (1 == 0) {
				byte[] bytes = new byte[10];
				String str = new String();
				while (fis.read(bytes) != -1) {
					str += new String(bytes);
				}
				System.out.print(str);
			}
			
			//字符转码
			InputStreamReader isr = new InputStreamReader(fis, "UTF-8"); // 或GBK,GB2312,GB18030
			BufferedReader read = new BufferedReader(isr);
			String str = null;
			while((str=read.readLine())!=null)
				System.out.println(read.readLine());
		} catch (FileNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}
}
