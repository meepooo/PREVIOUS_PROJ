package javaawt;

import java.awt.Frame;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class FrameTest extends Frame{
 /**
  * 
  */
 private static final long serialVersionUID = -5650765517644858632L;

 public void init(){
  this.setSize(320,240);
  this.setTitle("Frame");
  
  //加监听使得关闭按钮有效
  this.addWindowListener(new WindowAdapter(){
@Override
   public void windowClosing(WindowEvent e){
    System.exit(0);
   }
  });
  
  this.setVisible(true);
 }
 
 public static void main(String[] args){
  FrameTest frame = new FrameTest();
  frame.init();
 }
}