/*Online Java Paper Test*/

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

class OnlineTest extends JFrame implements ActionListener
{
	JLabel l;
	JRadioButton jb[]=new JRadioButton[5];
	JButton b1,b2;
	ButtonGroup bg;
	int count=0,current=0,x=1,y=1,now=0;
	int m[]=new int[10];	
	OnlineTest(String s)
	{
		super(s);
		l=new JLabel();
		add(l);
		bg=new ButtonGroup();
		for(int i=0;i<5;i++)
		{
			jb[i]=new JRadioButton();	
			add(jb[i]);
			bg.add(jb[i]);
		}
		b1=new JButton("Next");
		b2=new JButton("Bookmark");
		b1.addActionListener(this);
		b2.addActionListener(this);
		add(b1);add(b2);
		set();
		l.setBounds(50,40,1000,30);
		jb[0].setBounds(50,80,500,20);
		jb[1].setBounds(50,110,500,20);
		jb[2].setBounds(50,140,500,20);
		jb[3].setBounds(50,170,500,20);
		b1.setBounds(100,240,100,30);
		b2.setBounds(270,240,100,30);
		setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		setLayout(null);
		setLocation(250,100);
		setVisible(true);
		setSize(800,450);
	}
	public void actionPerformed(ActionEvent e)
	{
		if(e.getSource()==b1)
		{
			if(check())
				count=count+1;
			current++;
			set();	
			if(current==9)
			{
				b1.setEnabled(false);
				b2.setText("Result");
			}
		}
		if(e.getActionCommand().equals("Bookmark"))
		{
			JButton bk=new JButton("Bookmark"+x);
			bk.setBounds(480,20+30*x,100,30);
			add(bk);
			bk.addActionListener(this);
			m[x]=current;
			x++;
			current++;
			set();	
			if(current==9)
				b2.setText("Result");
			setVisible(false);
			setVisible(true);
		}
		for(int i=0,y=1;i<x;i++,y++)
		{
		if(e.getActionCommand().equals("Bookmark"+y))
		{
			if(check())
				count=count+1;
			now=current;
			current=m[y];
			set();
			((JButton)e.getSource()).setEnabled(false);
			current=now;
		}
		}
	
		if(e.getActionCommand().equals("Result"))
		{
			if(check())
				count=count+1;
			current++;
			//System.out.println("correct ans="+count);
			JOptionPane.showMessageDialog(this,"correct ans="+count);
			System.exit(0);
		}
	}
	void set()
	{
		jb[4].setSelected(true);
		if(current==0)
		{
			l.setText("Que1: Who was the first Chief Minister of Odisha?");
			jb[0].setText("Biju Patnaik");jb[1].setText("Sadashiva Tripathy");jb[2].setText("Harekrushna Mahatab");jb[3].setText("Nandini Satpathy");	
		}
		if(current==1)
		{
			l.setText("Que2: In Ancient times,Odisha was know by the name of");
			jb[0].setText("Konkan");jb[1].setText("Kalinga");jb[2].setText("Kurukshetra");jb[3].setText("None of the above");
		}
		if(current==2)
		{
			l.setText("Que3: The jagannath Puri Temple was built in the year");
			jb[0].setText("1001");jb[1].setText("1109");jb[2].setText("1150");jb[3].setText("1161");
		}
		if(current==3)
		{
			l.setText("Que4: Total number of Districts in Odisha");
			jb[0].setText("25");jb[1].setText("27");jb[2].setText("30");jb[3].setText("32");
		}
		if(current==4)
		{
			l.setText("Que5: IF 23+15=28, 46+52=66, 87+31=90 THEN 86+72=?");
			jb[0].setText("126");jb[1].setText("120");jb[2].setText("88");jb[3].setText("130");
		}
		if(current==5)
		{
			l.setText("Que6: Which month has 28 days?");
			jb[0].setText("February");jb[1].setText("June");jb[2].setText("Every month");jb[3].setText("None");
		}
		if(current==6)
		{
			l.setText("Que7: Where was the electricity supply first introduced in India ? ");
			jb[0].setText("Mumbai");jb[1].setText("Dehradun");jb[2].setText("Darjeeling");jb[3].setText("Chennai");
		}
		if(current==7)
		{
			l.setText("Que8: Google has allowed which social media app onto the Google Play Store, after it was removed in 2021?");
			jb[0].setText("Sharechat");jb[1].setText("Parler");jb[2].setText("Tiktok");jb[3].setText("Truth");		
		}
		if(current==8)
		{
			l.setText("Que9: Which social media company has released its first annual human rights report?");
			jb[0].setText("Twitter");jb[1].setText("Meta");jb[2].setText("Snapchat");jb[3].setText("Linkedin");
		}
		if(current==9)
		{
			l.setText("Que10: What is YouTube's Slogan?");
			jb[0].setText("Anytime Video");jb[1].setText("Think Different");jb[2].setText("Broadcast Yourself");jb[3].setText("Just Video It");
		}
		l.setBounds(50,40,1000,30);
		for(int i=0,j=0;i<=90;i+=30,j++)
			jb[j].setBounds(50,80+i,200,20);
	}
	boolean check()
	{
		if(current==0)
			return(jb[2].isSelected());
		if(current==1)
			return(jb[1].isSelected());
		if(current==2)
			return(jb[3].isSelected());
		if(current==3)
			return(jb[2].isSelected());
		if(current==4)
			return(jb[3].isSelected());
		if(current==5)
			return(jb[2].isSelected());
		if(current==6)
			return(jb[2].isSelected());
		if(current==7)
			return(jb[1].isSelected());
		if(current==8)
			return(jb[1].isSelected());
		if(current==9)
			return(jb[2].isSelected());
		return false;
	}
	public static void main(String s[])
	{
		new OnlineTest("Online Exam");
	}


}
