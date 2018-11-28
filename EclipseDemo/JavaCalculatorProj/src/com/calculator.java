package com;

/*公共类：calculator
功能：计算器界面
版本：1.0      Bill        2015 11 28     
      实现了计算器界面布置，准备加入事件

        2.0      Bill        2015 12 2
        计划加入监听事件，实现按键功能

        2.1      Bill        2015 12 5
        打算关闭再打开时能显示上次的结果,结果失败，逻辑上出现问题
*/


import java.awt.*;         //绘制组件
import java.awt.event.*;   //监听事件组件

import javax.swing.*;      //gui组件

import java.io.*;          //用于存储和恢复文件的包

public class calculator                                     //implements ActionListener
 implements ActionListener
{   
    JFrame frame;
    JButton btn[]=new JButton[12];                                       //12个用来放数字
    JButton add,minus,plus,divide,clean,back,sqrt,equal;    //分别是+，-，*，/，全清，删除，开方，等于
    double x,y;                                             //计算的数字
    int z;                                                  //用来存储符号
    int z2;
    JTextField field;
    StringBuffer str;

    public static void main(String[] args)
    {
        calculator cal=new calculator();
    }
    public calculator()
    {   
        frame=new JFrame("我的第一个计算器");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);            //关闭gui时关程序
        frame.getContentPane();                                          //获得面板内容


        JPanel shangBufen=new JPanel();                                 //上半部分的面板
        JPanel xiaBufen=new JPanel();                                   //下半部分的面板

        //创建一个空字符串缓冲区
        str=new StringBuffer();

       //下面编辑上半部分的面板
        field=new JTextField(30);                    //20字宽的文本框用于显示(可能要改一下显示字体大小)
        field.setText("0");
        field.setHorizontalAlignment(JTextField.RIGHT);        //文本对齐右边
        field.setEditable(false);
        shangBufen.add(field);
        shangBufen.setLayout(new GridLayout(2,1));            //两行一列

        //0~9数字的实例化

        String s;
        for(int i=0;i<10;i++)
        {
            s=""+i;
            btn[i]=new JButton(s);
            btn[i].addActionListener(this);
        }
         btn[10]=new JButton("-/+");
         btn[10].addActionListener(this);
         btn[11]=new JButton(".");
         btn[11].addActionListener(this);

         add=new JButton("+");minus=new JButton("-");
         add.addActionListener(this);minus.addActionListener(this);
         plus=new JButton("*");divide=new JButton("/");
         plus.addActionListener(this);divide.addActionListener(this);
         clean=new JButton("C");back=new JButton("Back");
         clean.addActionListener(this);back.addActionListener(this);
         sqrt=new JButton("Sqrt");equal=new JButton("=");
         sqrt.addActionListener(this);equal.addActionListener(this);



        xiaBufen.add(btn[7]); xiaBufen.add(btn[8]); xiaBufen.add(btn[9]); xiaBufen.add(add); xiaBufen.add(minus);  
        xiaBufen.add(btn[4]); xiaBufen.add(btn[5]); xiaBufen.add(btn[6]); xiaBufen.add(plus); xiaBufen.add(divide);  
        xiaBufen.add(btn[1]); xiaBufen.add(btn[2]);xiaBufen.add(btn[3]); xiaBufen.add(clean); xiaBufen.add(back);  
        xiaBufen.add(btn[0]); xiaBufen.add(btn[10]); xiaBufen.add(btn[11]);xiaBufen.add(sqrt);xiaBufen.add(equal);  
        xiaBufen.setLayout(new GridLayout(4,5,5,5));                          //四行五列，间隔5像素

        frame.add(shangBufen);
        frame.add(xiaBufen);
        frame.setLayout(new FlowLayout());            //顺序排列

        frame.setSize(400,300);
        frame.setResizable(false);           //禁止修改窗口大小
        frame.setVisible(true);         
    }

        public void actionPerformed(ActionEvent event)                   //监听事件的实现
        {
          try
          {
              if(event.getSource()==clean)                              //清除显示的按键
              {
                field.setText("0");                                     //清零显示
                field.setHorizontalAlignment(JTextField.RIGHT);         //文本对齐右边
                str.setLength(0);                                       //字符串缓冲区清零              
                z=0;z2=0;
              }
              else if(event.getSource()==back)                          //清除一个字符的按键
              {
                  if(!field.getText().trim().equals("0"))    //如果显示的不是0,trim()是提取消除空格之后的字符串
                  {  
                       if(str.length()!=1)                
                       {
                       field.setText(str.delete(str.length()-1,str.length()).toString());//清除最后一个字符,可能抛出字符串越界异常
                       field.setHorizontalAlignment(JTextField.RIGHT);
                       }
                       else
                       {
                          field.setText("0");
                          field.setHorizontalAlignment(JTextField.RIGHT);
                          str.setLength(0);
                       }
                 }
              }
              else if(event.getSource()==btn[10])                                        //取反的按键
              {
                  x=Double.parseDouble(field.getText().trim());
                  x=-x;
                  field.setText(""+x);
                  field.setHorizontalAlignment(JTextField.RIGHT);
              }
              else if(event.getSource()==btn[11])                                        //小数点的按钮
              {
                  //首先判断字符串中是否包含小数点了
                  if(field.getText().trim().indexOf(".")==-1)          //没有找到就返回-1
                  {   
                      field.setText(str.append(event.getActionCommand()).toString());            //getActionCommmand()是返回发生事件的对象
                      field.setHorizontalAlignment(JTextField.RIGHT);
                  }
              }else if(event.getSource()==sqrt)                                          //求平方根的按键
              {
                  x=Double.parseDouble(field.getText().trim());
                  if(x>=0)
                  {   
                      x=Math.sqrt(x);
                      field.setText(""+x);
                      field.setHorizontalAlignment(JTextField.RIGHT);
                  }
                  y=0d;
                  str.setLength(0);
                  str.append(""+x);
              }else if(event.getSource()==add)                                          //"+"的按键
              {


                  if(z!=0)
                  {
                      y=Double.parseDouble(field.getText().trim());
                      str.setLength(0);
                      switch(z)
                      {case 1:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 2:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 3:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 4:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 0:break;
                      }  
                  }else
                  {field.setText(""+0);}
                  y=0d;
                  z=1;z2=1;
              }else if(event.getSource()==minus)                                       //“-”的按键
              {


                  if(z!=0)
                  {
                      y=Double.parseDouble(field.getText().trim());
                      str.setLength(0);
                      switch(z)
                      {case 1:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 2:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 3:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 4:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 0:break;
                      }  
                  }else
                  {field.setText(""+0);}
                  y=0d;
                  z=2;z2=1;
              }else if(event.getSource()==plus)                                        //“*”的按键
              {


                  if(z!=0)
                  {
                      y=Double.parseDouble(field.getText().trim());
                      str.setLength(0);
                      switch(z)
                      {case 1:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 2:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 3:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 4:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 0:break;
                      }  
                  }else
                  {field.setText(""+0);}
                  y=0d;
                  z=3;z2=1;
              }else if(event.getSource()==divide)                                      //“/”的按键
              {

                  if(z!=0)
                  {
                      y=Double.parseDouble(field.getText().trim());
                      str.setLength(0);
                      switch(z)
                      {case 1:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 2:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 3:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 4:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                       case 0:break;
                      }  
                  }else
                  {field.setText(""+0);}
                  y=0d;
                  z=4;z2=1;
              }else if(event.getSource()==equal)  
              {
                  y=Double.parseDouble(field.getText().trim());
                  str.setLength(0);
                  switch(z)
                  {case 1:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                   case 2:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                   case 3:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                   case 4:field.setText(str.append(""+(x+y)).toString());field.setHorizontalAlignment(JTextField.RIGHT);break;
                   case 0:break;
                  }
                  z=0;z2=0;

              }else if(event.getSource()==btn[0])
              {
                  if(!field.getText().trim().equals("0"))
                  {
                      field.setText(str.append(event.getActionCommand()).toString());            //getActionCommmand()是返回发生事件的对象
                      field.setHorizontalAlignment(JTextField.RIGHT);
                  }
              }else                                                                          //输入的是其他数字
              {   if(z!=0)
                 {
                  if(z2==1)
                  {
                      str.setLength(0);
                      field.setText(str.append(event.getActionCommand()).toString());            //getActionCommmand()是返回发生事件的对象
                      field.setHorizontalAlignment(JTextField.RIGHT);
                      x=Double.parseDouble(field.getText().trim());
                      z2=0;
                  }else
                  {
                      field.setText(str.append(event.getActionCommand()).toString());            //getActionCommmand()是返回发生事件的对象
                      field.setHorizontalAlignment(JTextField.RIGHT);  
                      x=Double.parseDouble(field.getText().trim());               
                  } 
                 }else
                 {
                     field.setText(str.append(event.getActionCommand()).toString());            //getActionCommmand()是返回发生事件的对象
                     field.setHorizontalAlignment(JTextField.RIGHT); 
                     x=Double.parseDouble(field.getText().trim());
                 }
              }
          }catch(NumberFormatException e1)           //异常处理
          {e1.printStackTrace();}
           catch(StringIndexOutOfBoundsException e2)       //字符串索引超出范围
          {e2.printStackTrace();}
        }

}
