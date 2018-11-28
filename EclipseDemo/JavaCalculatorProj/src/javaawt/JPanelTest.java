package javaawt;
import javax.swing.*; 
import java.awt.*; 
import java.awt.event.*; 

public class JPanelTest extends JFrame{
	
	JPanel contPanel = new JPanel(); 
	JPanel pane1 = new JPanel(); 
	JPanel pane2 = new JPanel(); 
	JButton next = new JButton("下一个"); 
	JButton pre = new JButton("上一个"); 
	
	public void Test() 
	{ 
	setBounds(0,0,200,300); 
	setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); 

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

	setContentPane(contPanel); 
	setVisible(true); 
	} 
	public static void main(String [] args) 
	{ 
	new JPanelTest(); 
	} 
	
	
}
