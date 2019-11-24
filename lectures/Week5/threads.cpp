#include <stdio.h>
#include <thread>
#include <iostream>
#include <stdlib.h>

//delcarations
int isPrime(int num);
int numPrimesInRange(int start, int stop);
void func(int threadID, int start, int stop, int* results);


int main() {

  int numThreads = 4;
  int* results = (int*)malloc(numThreads*sizeof(int));
  int min = 1000;
  int max = 1000000;

  std::thread* threads[numThreads];

  for(int i = 0; i < numThreads; i++){
    int start = (((max - min)/numThreads)*i)+min;
    int stop = ((max - min)/numThreads)*(i+1)+min;
    threads[i] = new std::thread(func, i, start, stop, results);
    }

  for(int i = 0; i < numThreads; i++) {
    threads[i]->join();
  }  


  int finalResult = 0;
  for(int j = 0; j < numThreads; j++) {
    finalResult += results[j];
    std::cout << (results[j]) << "\n";
  }
  
  printf("final result %i\n", finalResult);

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



