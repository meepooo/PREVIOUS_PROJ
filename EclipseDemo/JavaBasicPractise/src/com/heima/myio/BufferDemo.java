package com.heima.myio;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class BufferDemo {
	public static void main(String[] args) throws IOException {
		BufferedWriter bw = new BufferedWriter(new FileWriter("2.txt", true));
		bw.write("hello wwqqss");
		bw.newLine();
		bw.flush();
		bw.close();

		BufferedReader br = new BufferedReader(new FileReader("2.txt"));
		char[] cbuf = new char[1024];
		br.read(cbuf);
		System.out.println(cbuf);
		br.close();
	}
}
