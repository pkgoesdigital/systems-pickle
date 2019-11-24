import javax.swing.JFrame;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Point;
import java.awt.event.*;
import javax.swing.*;

public class Painter extends JFrame implements ActionListener, MouseListener{

	public static final int size = 800;
	public Color color = Color.RED;
	public String shape = "line";
	private Point start;
	private PaintingPanel pp;

	public Painter() {
		super("Painter");
		
		JPanel holder = new JPanel();
		setSize(size, size);
		setDefaultCloseOperation(EXIT_ON_CLOSE);

		holder.setLayout(new BorderLayout());

		JPanel colorSelector = new JPanel();
		colorSelector.setLayout(new GridLayout(3,1));

		//add red paint button
		JButton red = new JButton("red");
		red.setBackground(Color.RED);
		red.setOpaque(true);
		red.setBorderPainted(false);
		red.addActionListener(this);
		red.setActionCommand("red");
		colorSelector.add(red); //adds in next open cell in the grid
		
		
		//add green paint button
		JButton green = new JButton("green");
		green.setBackground(Color.GREEN);
		green.setOpaque(true);
		green.setBorderPainted(false);
		green.addActionListener(this);
		green.setActionCommand("green");
		colorSelector.add(green); //adds in next open cell in the grid
		
		//add blue paint button
		JButton blue = new JButton("blue");
		blue.setBackground(Color.BLUE);
		blue.setOpaque(true);
		blue.setBorderPainted(false);
		blue.addActionListener(this);
		blue.setActionCommand("blue");
		colorSelector.add(blue); //adds in next open cell in the grid
		

		JPanel shapeSelector = new JPanel();
		shapeSelector.setLayout(new GridLayout(1,2));
		
		//Line button
		JButton line = new JButton("line");
		line.setBorderPainted(true);
		line.addActionListener(this);
		line.setActionCommand("line");
		shapeSelector.add(line); //adds in next open cell in grid
		
		//Circle button
		JButton circle = new JButton("circle");
		circle.setBorderPainted(true);
		circle.addActionListener(this);
		circle.setActionCommand("circle");
		shapeSelector.add(circle); //adds in next open cell

		//JPanel centerPanel = new JPanel();
		pp = new PaintingPanel();
		pp.addMouseListener(this);
		//centerPanel.add(pp);
		pp.setOpaque(true);
		pp.setLayout(new GridLayout(1,1));
		
		//NEED to add send message button which will take the text in the 
		//textfield, append the name of the user and put in the text area,
		//then needs to clear the text field
		JTextArea chat = new JTextArea(5, 20);
		JTextField userInput = new JTextField();
		JPanel chatPanel = new JPanel();
		chatPanel.setLayout(new GridLayout(2,1));
		chatPanel.add(userInput);
		chatPanel.add(chat);
		chat.setOpaque(true);
		chatPanel.setOpaque(true);
		
		//add panels to overall panel holder
		holder.add(shapeSelector, BorderLayout.NORTH);	
		holder.add(pp, BorderLayout.CENTER);
		holder.add(chatPanel, BorderLayout.SOUTH);
		holder.add(colorSelector, BorderLayout.WEST);
		
		
		//connect holder to JFrame
		setContentPane(holder);
		//make visible to layout all components on screen
		setVisible(true);
	}

	@Override
	public void actionPerformed(ActionEvent e) {
		String actionCommand = e.getActionCommand();
		System.out.println("Action Command:" + actionCommand);
		if(actionCommand.equals("red")) {
			color = Color.RED;
		} else if (actionCommand.equals("green")) {
			color = Color.GREEN;
		} else if (actionCommand.equals("blue")) {
			color = Color.BLUE;
		} else if (actionCommand.equals("line")) {
			shape = actionCommand;
		} else if (actionCommand.equals("circle")) {
			shape = actionCommand;
		}
	}

	@Override
	public void mouseClicked(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mousePressed(MouseEvent e) {
		System.out.println("mouse pressed");
		start = e.getPoint();
	}

	@Override
	public void mouseReleased(MouseEvent e) {
		System.out.println("mouse released");
		if(shape.equals("line")) {
			pp.addPrimitive(new Line(start, e.getPoint(), color));
		} else if (shape.equals("circle")) {
			pp.addPrimitive(new Circle(e.getPoint(), start, color));
		}
		
		//pp.paintComponent(pp.getGraphics());
		pp.repaint();
	}

	@Override
	public void mouseEntered(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}

	@Override
	public void mouseExited(MouseEvent e) {
		// TODO Auto-generated method stub
		
	}


}
