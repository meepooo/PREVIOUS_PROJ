package com.heima.classa;

import java.util.Scanner;

public class PasswdDemo {
	public static void main(String[] args) {
		//�趨����
		String passwd = "wangqs";
		
		//ѭ���������룬���ж������Ƿ���ȷ
		for (int i = 0; i < 3; i++) {
			
			//��������
			Scanner sc = new Scanner(System.in);
			
			//�ж������Ƿ���ȷ
			if (passwd.equals(sc.nextLine())) {
				System.out.println("������ȷ");
				break;
			}

			//��ӡ������Ϣ
			System.out.println("������󣬻�ʣ " + (3 - i - 1) + " �λ��ᣡ");
			
			if (i == 2) {
				System.out.println("����ȫ����������˳���");
			}
		}

		//�������
		System.out.println("�������!");
	}
}
