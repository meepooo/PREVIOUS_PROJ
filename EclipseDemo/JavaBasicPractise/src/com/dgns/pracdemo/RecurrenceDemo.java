package com.dgns.pracdemo;
/*
 * �ŵ����⣺��һ�����ӣ��ӳ������3������ÿ���¶���һ�����ӣ�
 * 		С���ӳ����������º�ÿ��������һ�����ӣ��������Ӷ�������
 *  	�ʵڶ�ʮ���µ����Ӷ���Ϊ���٣�
 *  
 *  
 *  1
 *  1
 *  2
 *  3
 *  5
 *  8
 *  13
 *  
 *  ���ɣ����˵�һ���º͵ڶ������⣬����ÿ���¶���ǰ������֮��
 *  쳲���������
 *  
 */

public class RecurrenceDemo {
	public static void main(String[] args) {
		System.out.println(function(20));
	}
	
	public static int function(int num){
		
		if (num==1 || num==2)
			return num;
		else
			return function(num-1) + function(num-2);

	}
}
