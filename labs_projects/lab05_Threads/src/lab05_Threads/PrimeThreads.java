package lab05_Threads;

public class PrimeThreads {

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



	public static void main(String[] args) {

		int numInQuestion = 19991;
		int min = 1000; //used for range function
		int max = 1000000; //used for range function
		int numThreads = 4;
		

		int[] results = new int[numThreads];
		
		Thread[] threads = new Thread[numThreads];

		long startTime = System.nanoTime();
		
		//threading
		for(int i = 0; i < numThreads; i++) {
			int start = (((max - min)/numThreads)*i)+min;
			int stop = ((max - min)/numThreads)*(i+1)+min;
			MyThread mth = new MyThread(i, start, stop, results);
			Thread th = new Thread(mth);
			threads[i] = th;
			th.start();
		}
		for(int j = 0; j < numThreads; j++) {
			try {
				threads[j].join();
			} catch (InterruptedException e) {
				e.printStackTrace();
			}
		}
		
		int result = 0;
		for(int j = 0; j < numThreads; j++) {
			result += results[j];
		}
		System.out.println(result);

		long stopTime = System.nanoTime();
		double duration = (stopTime - startTime)/1000000.0; //duration in ms
		System.out.println(duration + " time for threading isPrime in ms" + "\n");
		//fundamental problem with threads - difficult to debug
		//when running multiple forks with larger amounts of work, 
		//the forks execute at different times and are layered in execution - 
		//returning different values to the same file or "whiteboard" as in-class example


		//Serial Version
		startTime = System.nanoTime();

		//testing isPrime method
		System.out.println(isPrime(numInQuestion));

		stopTime = System.nanoTime();
		duration = (stopTime - startTime)/1000000.0; //duration in ms
		System.out.println(duration + " time for isPrime in ms" + "\n");

		startTime = System.nanoTime();

		//testing numPrimesInRange
		System.out.println(numPrimesInRange(min, max));

		stopTime = System.nanoTime();
		duration = (stopTime - startTime)/1000000.0; //duration in ms
		System.out.println(duration + " time for numPrimesInRange in ms");
	}

}

