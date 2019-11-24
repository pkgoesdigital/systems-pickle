package sockets;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;

public class MyThread extends Node implements Runnable{

	//variable definitions
	private int start;
	private int stop;
	private int threadID;
	private int[] results;
	private ObjectInputStream ois;
	private ObjectOutputStream oos;

	//constructor call
	public MyThread(int threadID, int start, int stop, int[] results, ObjectInputStream ois, ObjectOutputStream oos) {
		this.start = start;
		this.stop = stop;
		this.threadID = threadID;
		this.results = results;
		this.ois = ois;
		this.oos = oos;
	}


	@Override
	public void run() { //this method is basically the "main" method of the thread
		//thread
		System.out.println(start + "-->" + stop);
		try {
			oos.writeObject(start);
			oos.writeObject(stop);
			results[threadID] = (int) ois.readObject();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		
	}

}
