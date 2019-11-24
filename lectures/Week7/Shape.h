#ifndef SHAPE_H
#define SHAPE_H
#include <iostream>

class Shape {

protected:
  int x;
  int y;

public:
  Shape();
  Shape(int x, int y);
  Shape(const Shape& s);
  virtual ~Shape();
  void trans(int dx, int dy);
  virtual double area() = 0;
  virtual void print();

};
#endif
