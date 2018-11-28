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
        f.setBackground(Color.GRAY); // 设置Frame的背景颜色，参数是java.awt.Color类的静态常量 
        f.setResizable(true); // 设置Frame是否可以改变大小默认值是true  
        f.setVisible(true); // 设置Frame是否可见，默认值是false
 
    }
}
