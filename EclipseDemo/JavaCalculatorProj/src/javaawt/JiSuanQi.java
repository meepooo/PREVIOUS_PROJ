package javaawt;

import java.awt.BorderLayout;
import java.awt.Container;

import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

public class JiSuanQi extends JFrame{
	static JPanel num1 = new JPanel(); 
	static JPanel num2 = new JPanel(); 
	static JPanel num3 = new JPanel(); 
	static JPanel num4 = new JPanel(); 
	static JPanel num5 = new JPanel(); 
	static JPanel num6 = new JPanel(); 
	static JPanel num7 = new JPanel(); 
	static JPanel num8 = new JPanel(); 
	static JPanel num9 = new JPanel(); 
	static JPanel num0 = new JPanel(); 
	static JPanel numeq = new JPanel(); 
	
	static JButton jb1;
	static JButton jb2;
	static JButton jb3;
	static JButton jb4;
	static JButton jb5;
	static JButton jb6;
	static JButton jb7;
	static JButton jb8;
	static JButton jb9;
	static JButton jb0;
	
	public static void main(String argv[]) {
		System.out.println("Hello world!");
		JiSuanQi jisuanqi = new JiSuanQi();
		int a = jisuanqi.add(4, 5);
		System.out.println(a);
		
		jiemian();
	}
	
	private int add(int a, int b) {
		return a+b ;
	}
	
	public static void jiemian() {
		JButton jb1 = new JButton("1");
		JButton jb2 = new JButton("2");
		JButton jb3 = new JButton("3");
		JButton jb4 = new JButton("4");
		JButton jb5 = new JButton("5");
		JButton jb6 = new JButton("6");
		JButton jb7 = new JButton("7");
		JButton jb8 = new JButton("8");
		JButton jb9 = new JButton("9");
		
		JiSuanQi js = new JiSuanQi();
		Container container = js.getContentPane();
		
		// 设置窗体的标题
		js.setTitle("MyFirstSwing");
		// 设置大小,按像素
		js.setSize(200, 200);
		// 添加JButton组建
//		js.add(jb1,BorderLayout.SOUTH);
		// 设置窗体位置
		js.setLocation(400, 200);
		// 设置当关闭窗口时,保证jvm也退出
		js.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		num1.add(jb1,BorderLayout.SOUTH);
		num1.add(jb2,BorderLayout.SOUTH);
		num1.add(jb3,BorderLayout.SOUTH);
		num1.add(jb4,BorderLayout.SOUTH);
		num1.add(jb5,BorderLayout.SOUTH);
		num1.add(jb6,BorderLayout.SOUTH);
		num1.add(jb7,BorderLayout.SOUTH);
		num1.add(jb8,BorderLayout.SOUTH);
		num1.add(jb9,BorderLayout.SOUTH);
		// 设置窗体可见性
		container.add(num1, BorderLayout.EAST);;
		num1.setSize(200, 300);
		num1.setLocation(200, 100);
		js.setVisible(true);
		
/*		JFrame jFrame = new JFrame();
		jFrame.setVisible(true);
		jFrame.setBounds(200, 200, 300, 300);
		
		jFrame.addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		
		JPanel jPanel = new JPanel();
		JButton jButton = new JButton("JFrame test");
		JLabel jLabel = new JLabel();
		
		jPanel.setBounds(200, 200, 200, 200);
		jPanel.setLayout(new BorderLayout());
		contPanel.add(pane1); 
		jPanel.add(jButton);
		jPanel.add(jLabel);
		
		contPanel.setBounds(0,0,200,300); 
//		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 

		contPanel.add(pane1); 

		pane1.add(next); 
		pane2.add(pre); 
		next.addActionListener(new ActionListener(){ 
		public void actionPerformed(ActionEvent e) 
		{ 
		contPanel.remove(pane1); 
		contPanel.add(pane2); 
		contPanel.revalidate(); 
		contPanel.repaint(); 
		} 
		}); 
		
		pre.addActionListener(new ActionListener(){ 
			public void actionPerformed(ActionEvent e) 
			{ 
			contPanel.remove(pane2); 
			contPanel.add(pane1); 
			contPanel.revalidate(); 
			contPanel.repaint(); 
			} 
			}); 
		
//		contPanel.setContentPane(contPanel); 
		contPanel.setVisible(true); 
		
		jPanel.setVisible(true);
//		setVisible(true);
*/	}
	
}

