#include <stdio.h>

/*
int main(void) {
//used to fork additional threads to carry out the work enclosed in the block following the #pragma construct
//block is executed by all threads in parallel
//original thread will be denoted as master thread with thread-id 0
#pragma omp parallel 
{
  printf("Hello, world.\n"); 
}

 return 0;

 //prints out 8 different print statements of Hello world (related to the number of cores)
 //threads are all writing to the std output and is a race to share it - the way the threads are displayed is completely arbitrary - garbled output is possible
}*/


//Private and Shared Variables
 //private - each thread owns a copy of the variable - private to each thread - each thread has a local copy and uses it as temporary variable - not initialized and value is not maintainted for use outside the parallel region - by default loop iteration counters in the OpenMP loop constructs are private
 //shared - must be used with care because they cause race conditions - visible and accessible by all threads simultaneously - by default all variables in the work sharing region are shared except the loop iteration counter
 /*
int main (int argc, char *argv[]) {

  int th_id, nthreads;
 //th_id is declared above - is specified as private; each thread has copy
#pragma omp parallel private(th_id)
{
  th_id = omp_get_thread_num();
  printf("Hello World from thread %d\n", th_id);
}

}*/

//Synchronization
  //Critical, Atomic, Ordered, Barrier, Nowait
  /*
 critical: the enclosed code block will be executed by only one thread at a time, and not simultaneously executed by multiple threads. It is often used to protect shared data from race conditions.

   atomic: the memory update (write, or read-modify-write) in the next instruction will be performed atomically. It does not make the entire statement atomic; only the memory update is atomic. A compiler might use special hardware instructions for better performance than when using critical.

   ordered: the structured block is executed in the order in which iterations would be executed in a sequential loop

   barrier: each thread waits until all of the other threads of a team have reached this point. A work-sharing construct has an implicit barrier synchronization at the end.

   nowait: specifies that threads completing assigned work can proceed without waiting for all threads in the team to finish. In the absence of this clause, threads encounter a barrier synchronization at the end of the work sharing construct. 
  */

  //Barrier example
  /* int main (int argc, char *argv[]) {
   int th_id, nthreads;

#pragma omp parallel private(th_id)
   {
     th_id = omp_get_thread_num();
     printf("Hello World from thread %d\n", th_id);

#pragma omp barrier
     if(th_id == 0) {
       nthreads = omp_get_num_threads();
       printf("There are %d threads\n", nthreads);
     }
   }
   }*/


//Parallelizing loops
int main(int argc, char **argv)
{
  int a[100000];
  int i = 0;
    #pragma omp parallel for
  for (i = 0; i < 100000; i++) {
    a[i] = 2 * i;
    printf("assigning i = %d\n");
  }

  return 0;
}
