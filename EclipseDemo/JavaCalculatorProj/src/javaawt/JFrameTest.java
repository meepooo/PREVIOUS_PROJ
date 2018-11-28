package javaawt;

import java.awt.BorderLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class JFrameTest extends JFrame implements ActionListener{
	public static void main(String[] args) {
		JFrameTest jFrameTest = new JFrameTest();
	}
	
	public JFrameTest () {
		JPanel jPanel = new JPanel();
		JButton jButton = new JButton("JFrame test");
		JLabel jLabel = new JLabel();
		
		jPanel.setBorder(BorderFactory.createEmptyBorder(200, 600, 200, 60));
		jPanel.setLayout(new BorderLayout());
		jPanel.add(jLabel, BorderLayout.CENTER);
		jPanel.add(jLabel, BorderLayout.SOUTH);
		getContentPane().add(jPanel);
		addWindowListener(new WindowAdapter() {
			public void windowClosing(WindowEvent e) {
				System.exit(0);
			}
		});
		pack();
		setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		// TODO 自动生成的方法存根
		
	}
}
