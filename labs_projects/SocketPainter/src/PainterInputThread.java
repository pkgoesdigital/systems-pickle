import java.io.IOException;
import java.io.ObjectInputStream;

public class PainterInputThread implements Runnable{

	private ObjectInputStream ois;
	private PaintingPanel pp;
	
	public PainterInputThread(ObjectInputStream ois, PaintingPanel pp) {
		this.ois = ois;
		this.pp = pp;
		
	}
	
	@Override
	public void run() {
		
		while(true) {
			try {
				Object input = ois.readObject();
				if(input instanceof String) {
					//update chat panel
				} else {
					pp.addPrimitive((PaintingPrimitive)input);
					//pp.paintComponent(pp.getGraphics());
					pp.repaint();
				}
			} catch (ClassNotFoundException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			
		}
		
	}

}
