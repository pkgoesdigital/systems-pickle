#include <iostream>
#include "Shape.h"
// Fixed from the 2019 lecture transcription: the include is Shape.h (case
// matters on Linux), the class is Shape not shape, `virtual` only appears
// inside the class definition (it was written on out-of-class definitions),
// and the pure-virtual area() lives in the header only.

Shape::Shape() {
  std::cout << "Shape def const\n";
  this->x = 0;
  this->y = 0;
}

Shape::Shape(int x, int y) {
  std::cout << "Shape const2\n";
  this->x = x;
  this->y = y;
}

// Copy constr
Shape::Shape(const Shape& s) {
  std::cout << "Shape cpy const\n";
  this->x = s.x;
  this->y = s.y;
}

Shape::~Shape() {
  std::cout << "Shape dstr\n";
}

//Shape:: in front of method says it belongs to the Shape class
void Shape::trans(int dx, int dy) {
  std::cout << "Shape trans\n";
  this->x += dx;
  this->y += dy;
}

// area() is pure virtual (== abstract) — declared in Shape.h, no body here

void Shape::print() {
  std::cout << "generic shape\n";
}
