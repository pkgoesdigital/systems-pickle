package sockets;

import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Head {

	public static void main(String[] args) throws IOException {

		int numNodes = 4;
		int[] results = new int[numNodes];
		Thread[] threads = new Thread[numNodes];
		
		int min = 1000; //used for range function
		int max = 1000000; //used for range function
		int port = 7000;
		
		//server is listening on port 8098
		ServerSocket ss = new ServerSocket(port);

		while(true) {

			Socket[] socketsArray = new Socket[numNodes];
			
			ObjectOutputStream[] oos = new ObjectOutputStream[numNodes];
			ObjectInputStream[] ois = new ObjectInputStream[numNodes];
			
			for(int j = 0; j < numNodes; j++) {
				//setting up sockets to acccept threads
				socketsArray[j] = ss.accept(); //blocking
				System.out.println("A new client is connected: " + j);
				oos[j] = new ObjectOutputStream(socketsArray[j].getOutputStream());
				ois[j] = new ObjectInputStream(socketsArray[j].getInputStream());
			}


			//threading
			for(int i = 0; i < numNodes; i++) {
				int start = (((max - min)/numNodes)*i)+min;
				int stop = ((max - min)/numNodes)*(i+1)+min;
				MyThread mth = new MyThread(i, start, stop, results, ois[i], oos[i]);
				System.out.println("Thread num: " + i);
				Thread th = new Thread(mth);
				threads[i] = th;
				th.start();
			}

			for(int j = 0; j < numNodes; j++) {
				try {
					threads[j].join();
				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}

			int result = 0;
			for(int j = 0; j < numNodes; j++) {
				result += results[j];
			}

			System.out.println("result: " + result);
		
		}
	}
}
