#include <iostream>
#include "Rect.h"
// Fixed from the 2019 lecture transcription: this file re-defined the whole
// class (already defined in Rect.h) instead of implementing its methods,
// so it never compiled on its own.

Rect::Rect() : Shape() {   // The : Shape() is implied
  std::cout << "Rect const\n";
  this->width = 1;
  this->height = 1;
}

Rect::Rect(int w, int h) : Shape() {
  std::cout << "Rect const2\n";
  this->width = w;
  this->height = h;
}

Rect::Rect(int w, int h, int x, int y) : Shape(x, y) {
  std::cout << "Rect const4\n";
  this->width = w;
  this->height = h;
}

// If you don't call :Shape it will call the default base one
Rect::Rect(const Rect& r) : Shape(r) {
  std::cout << "Rect cpy const\n";
  this->width = r.width;
  this->height = r.height;
}

Rect::~Rect() {
  std::cout << "Rect dstr\n";
}

// Should probably not have this
//  void Rect::trans(int dx, int dy) {
//    std::cout << "Rect trans\n";
//    Shape::trans(dx, dy);
//  }

//is already virtual here because of the Shape declaration of area
double Rect::area() {
  return width * height;
}

void Rect::print() {
  std::cout << "Rect with width of " << width << " and height of " << height << " at " << x << "," << y << "\n";
}
