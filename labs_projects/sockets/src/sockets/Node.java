package sockets;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.Scanner;

public class Node {

	public static void main(String[] args) throws IOException{

		int numNodes = 4;
		int port = 7000;


		Socket[] socketsArray = new Socket[numNodes];

		try { 
			// establish the connection with server port 8098 
			Socket s = new Socket("localhost", port); 

			ObjectInputStream ois = new ObjectInputStream(s.getInputStream());
			ObjectOutputStream oos = new ObjectOutputStream(s.getOutputStream());

			//readobject is start, 2nd readobject is stop - from MyThread
			oos.writeObject(numPrimesInRange((int)ois.readObject(), (int)ois.readObject()));
			
		} catch (UnknownHostException | ClassNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}


	//finds how many primes in a given range
	public static int numPrimesInRange(int start, int stop) {
		int numPrimes = 0;
		if(start > stop) {
			System.out.println("start cannot be greater than stop - redefine range");
			return start;
		}
		int i = start;
		while(i <= stop) {
			if(isPrime(i) == true) {
				++numPrimes;
				++i;
			}
			else {
				isPrime(i);
				++i;
			}
		}
		//System.out.println("there are " + numPrimes + " primes between " + start + " and " +  stop);
		return numPrimes;
	}


	public static boolean isPrime(int num) {
		int i = 2;
		boolean flag = true;

		while((i < num) && flag) {
			//condition for non-prime
			if(num % i == 0) {
				flag = false;
			}
			++i;
		}
		if(flag) {
			//System.out.println(num + " is a prime number");
			return true;
		}
		//stop early if not prime (return)
		//System.out.println(num + " is not a prime number");
		return false;
	}
}
