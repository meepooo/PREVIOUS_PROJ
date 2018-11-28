package com;

import java.awt.*;  
import javax.swing.*;  
  
/*Swing 程序用JFrame 对象实现了它们的窗口。JFrame 类是AWT Frame 类的一个子类。它还加入了一些Swing 所独有的特性。与 Frame 的使用十分相似。唯一的区别在于，你不能将组件加入到JFrame中。你可以或者将组件加入到JFrame 的content pane(内容面板) 中，或者提供一个新的content pane(内容面板)。
面板与顶层容器的不同点：面板不能独立存在，必须被添加到其他容器内部（面板可以嵌套）。     
JFrame 有一个 Content Pane，窗口能显示的所有组件都是添加在这个 Content Pane 中。JFrame 提供了两个方法： getContentPane 和 setContentPane 就是用于获取和设置其 Content Pane 的。

对JFrame添加组件有两种方式：
1)用 getContentPane ()方法获得JFrame的内容面板，再对其加入组件：frame. getContentPane ().add(childComponent)
2)建立一个Jpanel或JDesktopPane之类的中间容器，把组件添加到容器中，用setContentPane()方法把该容器置为JFrame的内容面板：
JPanel contentPane = new JPanel();
……//把其它组件添加到Jpanel中;
frame.setContentPane(contentPane);
//把contentPane对象设置成为frame的内容面板
*/
public class test2 {  
      
    public static void main(String[] args) {  
          
        JFrame frame = new JFrame("Frame With Panel");  
        Container contentPane = frame.getContentPane();  
//        contentPane.setBackground(Color.CYAN); // 将JFrame实例背景设置为蓝绿色  
        JPanel panel = new JPanel(); // 创建一个JPanel的实例  
//        panel.setBackground(Color.yellow); // 将JPanel的实例背景设置为黄色  
        JButton button = new JButton("Press me");  
        JButton button1 = new JButton("Press me1");  
        panel.add(button); // 将JButton实例添加到JPanel中  
        panel.add(button1);
        
        contentPane.add(panel, BorderLayout.SOUTH); // 将JPanel实例添加到JFrame的南侧  
        frame.setSize(300, 200);  
        frame.setVisible(true);  
    }  
}  