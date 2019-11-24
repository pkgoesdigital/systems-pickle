import java.awt.Color;
import java.awt.Graphics;

public abstract class PaintingPrimitive {
	
	private Color color;
	
	public PaintingPrimitive(Color c) {
		this.color = c;
	}

	//example of template design pattern
	//called template because contains template of steps involved in drawing - setting color and drawing geometry
	public final void draw(Graphics g) {
		g.setColor(this.color);
		drawGeometry(g);
	}

	//to be defined in subclasses
	protected abstract void drawGeometry(Graphics g);

}
