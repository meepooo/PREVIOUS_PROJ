package com;

import java.awt.*;
import javax.swing.*;

public class test1 extends JFrame {
	// ���尴ť���
	JButton jb1 = null;

	public static void main(String[] args) {
		test1 swing = new test1();
	}

	// ���캯��
	public test1() {
		// JFrame��һ����������
		jb1 = new JButton("���ǰ�ť");
		// ���ô���ı���
		this.setTitle("MyFirstSwing");
		// ���ô�С,������
		this.setSize(200, 200);
		// ���JButton�齨
		this.add(jb1);
		// ���ô���λ��
		this.setLocation(400, 200);
		// ���õ��رմ���ʱ,��֤jvmҲ�˳�
		this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		// ���ô���ɼ���
		this.setVisible(true);
	}
}