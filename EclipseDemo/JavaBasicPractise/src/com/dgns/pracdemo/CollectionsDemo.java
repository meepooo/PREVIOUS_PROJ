package com.dgns.pracdemo;

import java.util.ArrayList;
import java.util.Collections;


/*
*	ģ�⶷��������
	
	����
	ϴ��
	����

*/
public class CollectionsDemo {
	public static void main(String[] args) {
		//����
		String[] arr = {"����","����","��Ƭ","÷��"};
		String[] arr2 = {"A","2","3","4","5","6","7","8","9","10","J","Q","K"};
		
		ArrayList<String> box = new ArrayList<String>();
		//���ÿ����
		for (int i = 0; i < arr.length; i++) {
			//��ȡÿһ����ɫ
			for (int j = 0; j < arr2.length; j++) {
				//��ȡÿһ����
				box.add(arr[i] + arr2[j]);
			}
			
		}
		box.add("����");
		box.add("С��");
		//System.out.println(box.size());
		
		//ϴ��
		Collections.shuffle(box);
		//System.out.println(box);
		
		//����
		ArrayList<String>��־�� = new ArrayList<String>();
		ArrayList<String>������ = new ArrayList<String>();
		ArrayList<String>��� = new ArrayList<String>();
		
		//�����ŵ��Ƹ�����
		for (int i = 0; i < box.size() - 3; i++) {
			/*
			*  i = 0;i % 3 = 0;
			*  i = 1;i % 3 = 1;
			*  i = 2;i % 3 = 2;
			*  i = 3;i % 3 = 0;
			*  i = 4;i % 4 = 1;
			*  i = 5;i % 5 = 2;
			*/
			
			if(i % 3 == 0) {
				��־��.add(box.get(i));
			}
			else if(i % 3 == 1) {
				������.add(box.get(i));
			}
			else if(i % 3 == 2) {
				���.add(box.get(i));
			}
		}
		
		System.out.println("��־�᣺" + ��־��);
		System.out.println("�����磺" + ������);
		System.out.println("��俣�" + ���);
	
	
		System.out.println("���ƣ�");
	/*	System.out.println(box.get(box.size() - 1));
		System.out.println(box.get(box.size() - 2));
		System.out.println(box.get(box.size() - 3));*/
		
		for (int i = box.size() - 3; i < box.size(); i++) {
			System.out.println(box.get(i));
		}
	}
	
}

