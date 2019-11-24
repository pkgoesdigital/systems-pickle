import java.awt.Color;
import java.awt.Graphics;
import java.awt.Point;

public class Circle extends PaintingPrimitive{

	private Point center;
	private Point radiusPoint;
	
	public Circle(Point r, Point center, Color c) {
		super(c);
		this.radiusPoint = r;
		this.center = center;
	}

	@Override
	protected void drawGeometry(Graphics g) {
		int radius = (int) Math.abs(center.distance(radiusPoint));
		g.drawOval(center.x - radius, center.y - radius, radius*2, radius*2);	
	}
}
