#include <iostream>
#include "shape.h"

  shape::Shape() {
    std::cout << "Shape def const\n";
    this->x = 0;
    this->y = 0;
  }

  shape::Shape(int x, int y) {
    std::cout << "Shape const2\n";
    this->x = x;
    this->y = y;
  }

  // Copy constr
  shape::Shape(const Shape& s) {
    std::cout << "Shape cpy const\n";
    this->x = s.x;
    this->y = s.y;
  }

  virtual shape::~Shape() {
    std::cout << "Shape dstr\n";
  }

//shape:: in front of method says it belongs to the shape class
  void shape::trans(int dx, int dy) {
    std::cout << "Shape trans\n";
    this->x += dx;
    this->y += dy;
  }

  // pure virtual function
  virtual double area() = 0; //pure virtual function == abstract

  virtual void print() {
    std::cout << "generic shape\n";
  }

};
