import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class ConnectionThread implements Runnable {

	
	private ServerSocket ss;
	private ArrayList<Socket> painters;
	private ArrayList<HubInputThread> inputThreads;
	private ArrayList<ObjectOutputStream> ooss;
	private ArrayList<ObjectInputStream> oiss;
	private PaintingPanel masterPanel;
	private int connectionID;
	
	
	public ConnectionThread(ServerSocket ss, ArrayList<Socket> painters, ArrayList<HubInputThread> inputThreads, ArrayList<ObjectOutputStream> ooss, ArrayList<ObjectInputStream> oiss, PaintingPanel masterPanel) {
		this.ss = ss;
		this.painters = painters;
		this.inputThreads = inputThreads;
		this.ooss = ooss;
		this.oiss = oiss;
		this.masterPanel = masterPanel;
		connectionID = 0;
	}
	@Override
	public void run() {
		
		while(true) {
			try {
				Socket painter = ss.accept();
				painters.add(painter);
				ObjectInputStream ois = new ObjectInputStream(painter.getInputStream());
				ObjectOutputStream oos = new ObjectOutputStream(painter.getOutputStream());
				ooss.add(oos);
				oos.writeObject(masterPanel);
				HubInputThread hit = new HubInputThread(ois, connectionID);
				Thread th = new Thread(hit);
				th.start();
				connectionID++;
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
		
		
		
	}

}
