#include <iostream>
#include "Circle.h"
// Fixed from the 2019 lecture transcription: this file re-defined the whole
// class (already defined in Circle.h) instead of implementing its methods,
// so it never compiled on its own.

Circle::Circle() {
  std::cout << "Circle const\n";
  radius = 1;
}

Circle::Circle(int r) {
  std::cout << "Circle const1\n";
  radius = r;
}

Circle::Circle(int r, int x, int y) : Shape(x, y) {
  std::cout << "Circle const3\n";
  radius = r;
}

Circle::~Circle() {
  std::cout << "Circle dstr\n";
}

double Circle::area() {
  return 3.14 * radius * radius;
}

void Circle::print() {
  std::cout << "Circle with radius of " << radius << " at " << x << "," << y << "\n";
}
