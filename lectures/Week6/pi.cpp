#include <iostream>

int main() {
  
  int n = 10000;

  double epi = 0.0;

  for (int i=0; i<n; i++) {

    double term = 1.0 / ((2 * i) + 1);

    int sign = 1;
    if (i%2 == 1) {
      sign = -1;
    }

    epi = epi + (sign * term);
  }

  epi = epi * 4.0;

  std::cout << epi << "\n";
}
