// Lab 06 — count primes with OpenMP two ways: blocking (contiguous chunks
// per thread) vs striping (round-robin, schedule(static,1)).
//
// HONEST STATUS: this was submitted as an unfinished draft and had never
// compiled — striping() left an OpenMP block unclosed, which nested every
// later function inside it, and returned from inside that block. Those
// structural errors are fixed (see striping()) so the lab builds and runs,
// but the *algorithm* is left as written, and it is still wrong in ways
// worth studying rather than papering over:
//
//   1. Both functions call omp_get_num_threads() OUTSIDE a parallel region,
//      where it always returns 1 — so elementsPerThread is the whole range.
//   2. blocking() computes numPrimesInRange(start, stop) — the entire range —
//      inside every loop iteration, then assigns (not accumulates) it. Each
//      thread redoes all the work and clobbers the shared counter.
//   3. primeCountBlocking / primeCountStriping are written by all threads
//      with no reduction clause; striping's `+= 1` is a data race. The fix
//      the lab was reaching for is `reduction(+:count)`.
//   4. striping() counts primes of the loop index i (0..stop-start), not of
//      start+i, so it answers a different question than blocking().
//   5. startTime is assigned by every thread inside the parallel region.
//
// Fix them one at a time and watch the numbers change — that is the lab.
#include <thread>
#include <iostream>
#include <omp.h>
#include <mutex>
#include <stdio.h>
#include <cstring>

//declarations
int isPrime(int num);
int numPrimesInRange(int start, int stop);
void func(int threadID, int start, int stop, int* results);
int blocking(int start, int stop);
int striping(int start, int stop);


int main() {
  omp_set_num_threads(5);
  int numThreads = 5;

  blocking(10, 100);
  blocking(1000,1000000);

  striping(10, 100);
  striping(1000, 1000000);

}

int blocking(int start, int stop) {

  //checking how many threads are running
  double numThreads = omp_get_num_threads();
  int i = 0;

  int elementsPerThread = (stop-start)/numThreads;

  //timing stuff
  printf("BLOCKING\n");
  int primeCountBlocking = 0;
  double startTime;
  double endTime;

#pragma omp parallel
  {
    startTime = omp_get_wtime();
#pragma omp parallel for schedule(static, elementsPerThread)
    //for loop to parallelize
  for(i = 0; i < stop-start; i++) {
    printf("Thread ID: %d i = %d\n", omp_get_thread_num(), i);
    primeCountBlocking = numPrimesInRange(start, stop);
  } //end of parallel block
  endTime = omp_get_wtime();
  }

    printf("There are %d prime numbers in given range using blocking.\n", primeCountBlocking);
    printf("Time for blocking: %f\n", endTime - startTime); //%d on a double is UB — it was printing garbage

    return primeCountBlocking;
  }



  int striping(int start, int stop) {

    //check how many threads are going
    double numThreads = omp_get_num_threads();
    int i = 0;

    //timing stuff
    printf("STRIPING\n");
    int primeCountStriping = 0;
    double startTime;
    double endTime;

  // Structural fix (2026): as written, this function never compiled. The
  // `#pragma omp parallel {` below was never closed, so every function after
  // it ended up nested inside striping(); and it returned from inside an
  // OpenMP structured block, which the standard forbids ("invalid exit from
  // OpenMP structured block"). The printing and the return now happen after
  // the parallel region, mirroring blocking() above. The algorithm is
  // unchanged — see the header comment for what is still wrong with it.
  #pragma omp parallel
    {
      startTime = omp_get_wtime();
  #pragma omp for schedule(static, 1)
      for(i = 0; i < stop-start; i++) {
        if(isPrime(i)) {
          primeCountStriping += 1;
        }
      }
      endTime = omp_get_wtime();
    }

    printf("There are %d prime numbers in given range using striping.\n", primeCountStriping);
    printf("Time for striping: %f\n", endTime - startTime);

    return primeCountStriping;
  }


      void func(int threadID, int start, int stop, int* results) {
        printf("I'm ThreadID %i, with Range [%i, %i]\n", threadID, start, stop);
        results[threadID] = numPrimesInRange(start, stop);
        //printf("I'm ThreadID %i, with Range [%i, %i]\n", threadID, start, stop);
      }


      //calculate numPrimes based on range passed in
      int numPrimesInRange(int start, int stop) {
        int numPrimes = 0;
        if(start > stop) {
          printf("%i cannot be greater than stop - redefine range", start);
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
        return numPrimes;
      }


      //determines whether param is a prime number
      int isPrime(int num) {
        int i = 2;
        int flag = 1;

  while((i < num) && flag) {
    //condition for non-prime
    if(num % i == 0) {
      flag = 0;
    }
    ++i;
  }
  if(flag) {
    return 1;
  }
  //stop early if not prime (return)
  return 0;
}
