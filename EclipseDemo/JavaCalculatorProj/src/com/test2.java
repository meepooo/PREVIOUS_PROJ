package com;

import java.awt.*;  
import javax.swing.*;  
  
/*Swing ������JFrame ����ʵ�������ǵĴ��ڡ�JFrame ����AWT Frame ���һ�����ࡣ����������һЩSwing �����е����ԡ��� Frame ��ʹ��ʮ�����ơ�Ψһ���������ڣ��㲻�ܽ�������뵽JFrame�С�����Ի��߽�������뵽JFrame ��content pane(�������) �У������ṩһ���µ�content pane(�������)��
����붥�������Ĳ�ͬ�㣺��岻�ܶ������ڣ����뱻��ӵ����������ڲ���������Ƕ�ף���     
JFrame ��һ�� Content Pane����������ʾ��������������������� Content Pane �С�JFrame �ṩ������������ getContentPane �� setContentPane �������ڻ�ȡ�������� Content Pane �ġ�

��JFrame�����������ַ�ʽ��
1)�� getContentPane ()�������JFrame��������壬�ٶ�����������frame. getContentPane ().add(childComponent)
2)����һ��Jpanel��JDesktopPane֮����м��������������ӵ������У���setContentPane()�����Ѹ�������ΪJFrame��������壺
JPanel contentPane = new JPanel();
����//�����������ӵ�Jpanel��;
frame.setContentPane(contentPane);
//��contentPane�������ó�Ϊframe���������
*/
public class test2 {  
      
    public static void main(String[] args) {  
          
        JFrame frame = new JFrame("Frame With Panel");  
        Container contentPane = frame.getContentPane();  
//        contentPane.setBackground(Color.CYAN); // ��JFrameʵ����������Ϊ����ɫ  
        JPanel panel = new JPanel(); // ����һ��JPanel��ʵ��  
//        panel.setBackground(Color.yellow); // ��JPanel��ʵ����������Ϊ��ɫ  
        JButton button = new JButton("Press me");  
        JButton button1 = new JButton("Press me1");  
        panel.add(button); // ��JButtonʵ����ӵ�JPanel��  
        panel.add(button1);
        
        contentPane.add(panel, BorderLayout.SOUTH); // ��JPanelʵ����ӵ�JFrame���ϲ�  
        frame.setSize(300, 200);  
        frame.setVisible(true);  
    }  
}  