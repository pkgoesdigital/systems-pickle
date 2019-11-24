
public class Test {

  public static void main(String[] args) {

    int[] results = new int[4];
    Thread[] threads = new Thread[4];
    for(int j=0; j<4; j++) {
      int start = j*25;
      int stop = (j+1) * 25;
      MyThread mth = new MyThread(j, start, stop, results);
        Thread th = new Thread(mth);
        threads[j] = th;
        th.start();  // fork
      }
      for(int j=0; j<4; j++) {
        try {
          threads[j].join();
        } catch (InterruptedException e) {
          e.printStackTrace();
        }
      }
      int result = 0;
      for(int j=0; j<4; j++) {
        result += results[j];
      }
      System.out.println(result);
    }
  }

  //fundamental problem with threads - difficult to debug
  //when running multiple forks with larger amounts of work, the forks execute at different times and are layered in execution - returning different values to the same file or "whiteboard" as in-class example
}

}
