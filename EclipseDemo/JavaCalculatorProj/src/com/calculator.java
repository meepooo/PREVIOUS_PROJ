package com;

/*�����ࣺcalculator
���ܣ�����������
�汾��1.0      Bill        2015 11 28     
      ʵ���˼��������沼�ã�׼�������¼�

        2.0      Bill        2015 12 2
        �ƻ���������¼���ʵ�ְ�������

        2.1      Bill        2015 12 5
        ����ر��ٴ�ʱ����ʾ�ϴεĽ��,���ʧ�ܣ��߼��ϳ�������
*/


import java.awt.*;         //�������
import java.awt.event.*;   //�����¼����

import javax.swing.*;      //gui���

import java.io.*;          //���ڴ洢�ͻָ��ļ��İ�

public class calculator                                     //implements ActionListener
 implements ActionListener
{   
    JFrame frame;
    JButton btn[]=new JButton[12];                                       //12������������
    JButton add,minus,plus,divide,clean,back,sqrt,equal;    //�ֱ���+��-��*��/��ȫ�壬ɾ��������������
    double x,y;                                             //���������
    int z;                                                  //�����洢����
    int z2;
    JTextField field;
    StringBuffer str;

    public static void main(String[] args)
    {
        calculator cal=new calculator();
    }
    public calculator()
    {   
        frame=new JFrame("�ҵĵ�һ��������");
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);            //�ر�guiʱ�س���
        frame.getContentPane();                                          //����������


        JPanel shangBufen=new JPanel();                                 //�ϰ벿�ֵ����
        JPanel xiaBufen=new JPanel();                                   //�°벿�ֵ����

        //����һ�����ַ���������
        str=new StringBuffer();

       //����༭�ϰ벿�ֵ����
        field=new JTextField(30);                    //20�ֿ���ı���������ʾ(����Ҫ��һ����ʾ�����С)
        field.setText("0");
        field.setHorizontalAlignment(JTextField.RIGHT);        //�ı������ұ�
        field.setEditable(false);
        shangBufen.add(field);
        shangBufen.setLayout(new GridLayout(2,1));            //����һ��

        //0~9���ֵ�ʵ����

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
        xiaBufen.setLayout(new GridLayout(4,5,5,5));                          //�������У����5����

        frame.add(shangBufen);
        frame.add(xiaBufen);
        frame.setLayout(new FlowLayout());            //˳������

        frame.setSize(400,300);
        frame.setResizable(false);           //��ֹ�޸Ĵ��ڴ�С
        frame.setVisible(true);         
    }

        public void actionPerformed(ActionEvent event)                   //�����¼���ʵ��
        {
          try
          {
              if(event.getSource()==clean)                              //�����ʾ�İ���
              {
                field.setText("0");                                     //������ʾ
                field.setHorizontalAlignment(JTextField.RIGHT);         //�ı������ұ�
                str.setLength(0);                                       //�ַ�������������              
                z=0;z2=0;
              }
              else if(event.getSource()==back)                          //���һ���ַ��İ���
              {
                  if(!field.getText().trim().equals("0"))    //�����ʾ�Ĳ���0,trim()����ȡ�����ո�֮����ַ���
                  {  
                       if(str.length()!=1)                
                       {
                       field.setText(str.delete(str.length()-1,str.length()).toString());//������һ���ַ�,�����׳��ַ���Խ���쳣
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
              else if(event.getSource()==btn[10])                                        //ȡ���İ���
              {
                  x=Double.parseDouble(field.getText().trim());
                  x=-x;
                  field.setText(""+x);
                  field.setHorizontalAlignment(JTextField.RIGHT);
              }
              else if(event.getSource()==btn[11])                                        //С����İ�ť
              {
                  //�����ж��ַ������Ƿ����С������
                  if(field.getText().trim().indexOf(".")==-1)          //û���ҵ��ͷ���-1
                  {   
                      field.setText(str.append(event.getActionCommand()).toString());            //getActionCommmand()�Ƿ��ط����¼��Ķ���
                      field.setHorizontalAlignment(JTextField.RIGHT);
                  }
              }else if(event.getSource()==sqrt)                                          //��ƽ�����İ���
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
              }else if(event.getSource()==add)                                          //"+"�İ���
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
              }else if(event.getSource()==minus)                                       //��-���İ���
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
              }else if(event.getSource()==plus)                                        //��*���İ���
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
              }else if(event.getSource()==divide)                                      //��/���İ���
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
                      field.setText(str.append(event.getActionCommand()).toString());            //getActionCommmand()�Ƿ��ط����¼��Ķ���
                      field.setHorizontalAlignment(JTextField.RIGHT);
                  }
              }else                                                                          //���������������
              {   if(z!=0)
                 {
                  if(z2==1)
                  {
                      str.setLength(0);
                      field.setText(str.append(event.getActionCommand()).toString());            //getActionCommmand()�Ƿ��ط����¼��Ķ���
                      field.setHorizontalAlignment(JTextField.RIGHT);
                      x=Double.parseDouble(field.getText().trim());
                      z2=0;
                  }else
                  {
                      field.setText(str.append(event.getActionCommand()).toString());            //getActionCommmand()�Ƿ��ط����¼��Ķ���
                      field.setHorizontalAlignment(JTextField.RIGHT);  
                      x=Double.parseDouble(field.getText().trim());               
                  } 
                 }else
                 {
                     field.setText(str.append(event.getActionCommand()).toString());            //getActionCommmand()�Ƿ��ط����¼��Ķ���
                     field.setHorizontalAlignment(JTextField.RIGHT); 
                     x=Double.parseDouble(field.getText().trim());
                 }
              }
          }catch(NumberFormatException e1)           //�쳣����
          {e1.printStackTrace();}
           catch(StringIndexOutOfBoundsException e2)       //�ַ�������������Χ
          {e2.printStackTrace();}
        }

}
