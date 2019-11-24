#include <iostream>
#include <omp.h>  //mac: -Xpreprocessor -fopenmp -lomp
                  //linux: -fopenmp

//use this for next weeks lab - striping, parallel programming, timing
//might have to break up #pragma line
//specific about output and how it looks
int main() {

  omp_set_num_threads(4);

  int n = 10000;

  double epi = 0.0;
//operations for +:epi must be communitative (add, multiply)
#pragma omp parallel for schedule(static, 2500) reduction(+:epi) //what does this do? the var epi (which is basically a global var) that the threads can all "share" - behind the scenes, create 4 of these variables as a copy, and give one to each thread
//reduction goes and automatically takes all of the "copied" epi's, adds them together, and returns the value - super powerful - reduction passes numbers, kind of like a relay race, and then the composite adds themselves to the other composites...etc. basically creates a process tree

  for (int i=0; i<n; i++) {

    double term = 1.0 / ((2 * i) + 1);

    int sign = 1;
    if (i%2 == 1) {
      sign = -1;
    }
//#pragma omp critical //this could work, but not ideal
    epi = epi + (sign * term);
  }

  epi = epi * 4.0;

  std::cout << epi << "\n";
}
