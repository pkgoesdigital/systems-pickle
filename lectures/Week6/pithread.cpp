#include <iostream>
#include <thread> // -std=c++11 -pthread
#include <mutex>

double epi;
std::mutex lock;

void pithread(int start, int stop) {

  // Fix the issue with the sign
  // if we start on an odd term
  int sign = 1;
  if (start%2 == 1) {
    sign = -1;
  }

  for (int i=start; i<stop; i++) {
    double term = 1.0 / ((2 * i) + 1);

    // Lock the shared varriable before using it
    // Would have been better to have a localEPI and then
    //  lock the globalEPI once at the end, but this versions
    //  shows what happens if you don't lock better
    lock.lock();
    epi = epi + (sign * term);
    lock.unlock();

    sign = sign * -1;
  }

}

int main() {

  int nth = 4;
  int n = 10000;
  epi = 0.0;

  std::thread* threads[nth];

  for (int i=0; i<nth; i++) {
    int start = (n/nth)*i;
    int stop = (n/nth)*(i+1);
    threads[i] = new std::thread(pithread, start, stop);
  }

  for (int i=0; i<nth; i++) {
    threads[i]->join();
  }

  epi = epi * 4.0;
  std::cout << epi << "\n";
}
