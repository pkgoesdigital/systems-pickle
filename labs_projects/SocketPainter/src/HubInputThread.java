import java.io.IOException;
import java.io.ObjectInputStream;
import java.util.ArrayList;

public class HubInputThread implements Runnable{

	//needs the painting panel, object input stream, and all the output threads(?)...
	//new output threads will be continually added so it would need to be an array/arraylist that communicates between here and the hub?
	//variable definitions
	
	//private PaintingPanel masterPanel;
	private ObjectInputStream ois;
	//private ArrayList<hubOutputThread> outputThreads;
	private int connectionID;
	
	//constructor call
	public HubInputThread(ObjectInputStream ois, int connectionID) {
	//	this.masterPanel = masterPanel;
		this.ois = ois;
		this.connectionID = connectionID;
	}
	
	@Override
	public void run() {
		try {
			Object input = ois.readObject();
			if (input instanceof String) {
				//Do stuff to master chat panel i guess	
			} else {
				Hub.updateMaster((PaintingPrimitive)input);
				//want to pass connectionID as an argument but updateMaster uses 
				//an arraylist of oos's and I'm not sure how they would align with 
				//the connectionID I'm using here. (specifically when a painter/oos gets removed
				//from the arraylist
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

