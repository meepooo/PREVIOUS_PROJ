package javaawt;

import java.awt.Color;
import java.awt.Dialog;
import java.awt.Event;
import java.awt.Frame;
import java.awt.event.*;
 


public class AwtTest {  
    public static void main(String[] args) {  
    	AwtTest a = new AwtTest();
    	a.createFram();
    	
    }
    private void createFram() {
        Frame f = new Frame("this is my first frame");
        f.setBounds(200, 100, 800, 500); 
        f.setBackground(Color.GRAY); // ����Frame�ı�����ɫ��������java.awt.Color��ľ�̬���� 
        f.setResizable(true); // ����Frame�Ƿ���Ըı��СĬ��ֵ��true  
        f.setVisible(true); // ����Frame�Ƿ�ɼ���Ĭ��ֵ��false
 
    }
}
