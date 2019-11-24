#ifndef CIRCLE_H
#define CIRCLE_H
#include <iostream>
#include "Shape.h"

class Circle : public Shape {
private:
  int radius;

public:
  Circle();
  Circle(int r);
  Circle(int r, int x, int y);
  virtual ~Circle();
  double area();
  void print();

};
#endif
