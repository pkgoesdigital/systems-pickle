package lab05_Threads;

public class MyThread implements Runnable {

	//variable definitions
	private int start;
	private int stop;
	private int threadID;
	private int[] results;

	//constructor call
	public MyThread(int threadID, int start, int stop, int[] results) {
		this.start = start;
		this.stop = stop;
		this.threadID = threadID;
		this.results = results;
	}


	@Override
	public void run() { //this method is basically the "main" method of the thread
		//thread
		System.out.println(start + "-->" + stop);
		results[threadID] = PrimeThreads.numPrimesInRange(start, stop);

		
		//System.out.println("hi");
	}

}
