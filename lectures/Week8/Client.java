package edu.du.cs.dsteven.sockets;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;

public class Client {

	public static void main(String[] args) {
		
		try {
			System.out.println("About to call");
			Socket s = new Socket("localhost", 7000);
			System.out.println("Connected");
			
			// DataOutputStream
			ObjectOutputStream oos = new ObjectOutputStream(s.getOutputStream());
			ObjectInputStream ois = new ObjectInputStream(s.getInputStream());
			
			
			oos.writeObject(5);
			
			
			int x = (int)ois.readObject();
			
			System.out.println(x);
			
			s.close();
			
		} catch (IOException | ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		

	}

}
