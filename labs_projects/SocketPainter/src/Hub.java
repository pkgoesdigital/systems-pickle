import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.ArrayList;

public class Hub {

	ArrayList<Socket> painters;
	PaintingPanel masterPanel;
	ArrayList<ObjectOutputStream> ooss;

	public Hub() throws IOException {
		
		int port = 7000;
		int maxSize = 20;
		ServerSocket ss = new ServerSocket(port);
		painters = new ArrayList<>();
		ArrayList<ObjectInputStream> oiss = new ArrayList<>();
		ooss = new ArrayList<>();
		ArrayList<HubOutputThread> outputThreads = new ArrayList<>();
		masterPanel = new PaintingPanel();

		while(true) {

			Socket painter = ss.accept();
			painters.add(painter);
			ObjectInputStream ois = new ObjectInputStream(painter.getInputStream());
			ObjectOutputStream oos = new ObjectOutputStream(painter.getOutputStream());
			outputThreads.add(new HubOutputThread());
			ooss.add(oos);


		}
	}


	public static void main(String[] args) throws IOException {

		Hub h = new Hub();
		
		
	}


	//if threads can have identifiers, pass that in to avoid double printing?
	public synchronized void updateMaster(PaintingPrimitive inputObject) throws IOException {
		masterPanel.addPrimitive(inputObject);
		for(ObjectOutputStream oos : ooss) {
			oos.writeObject(inputObject);
		}
	}

}
