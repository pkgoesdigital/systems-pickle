import java.awt.Color;
import java.awt.Graphics;
import java.util.ArrayList;

import javax.swing.JPanel;

public class PaintingPanel extends JPanel{

	ArrayList<PaintingPrimitive> list = new ArrayList<>();
	//JPanel drawCanvas = new JPanel();
	
	public PaintingPanel() {
		this.setBackground(Color.WHITE);
		
	}	
	
	public void addPrimitive(PaintingPrimitive obj) {
		this.list.add(obj);
	}
	
	@Override
	public void paintComponent(Graphics g) {
		System.out.println("paint component");
		super.paintComponent(g);
		//iterator
		for(PaintingPrimitive obj : list) {
			obj.draw(g);
		}	
	}
	

	

}
