#include <iostream>
// #include "shape.cpp" //not ideal to directly include files
// #include "circle.cpp"
// #include "rectangle.cpp"
#include "Shape.h"   // header names are case-sensitive on Linux — the 2019
#include "Circle.h"  // includes (shape.h/circle.h/rectangle.h) only worked
#include "Rect.h"    // on macOS's case-insensitive filesystem
//compile the .h files as .h at compile like we did in huffman

int main() {

  Rect* r1 = new Rect(3, 2);
  Circle* c1 = new Circle(5, 3, 2);

  r1->print();
  c1->print();

  r1->trans(5, 3);
  r1->print();

  // Copy r1 BEFORE deleting it — the 2019 version did `new Rect(*r1)` after
  // `delete r1`, reading freed memory (use-after-free).
  Rect* r2 = new Rect(*r1);
  r2->print();

  delete r1;
  delete c1;

  Shape* s1 = new Circle(5, 3, 4);
  s1->print();

  //  Shape* s2 = new Shape();
  //  s2->print();

  r2->trans(1, 2);
  r2->print();

  delete s1;
  delete r2;
}
