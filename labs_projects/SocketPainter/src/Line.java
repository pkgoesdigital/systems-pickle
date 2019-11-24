import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;

public class Line extends PaintingPrimitive{
	
	private Point start; //for location on canvas
	private Point end; //for location on canvas

	//keeping color info with primitive
	public Line(Point start, Point end, Color c) {
		super(c);
		this.start = start;
		this.end = end;
	}
	
	@Override
	protected void drawGeometry(Graphics g) {
		g.drawLine(start.x, start.y, end.x, end.y);
	}

}
