#include <iostream>

class Shape {

protected:
  int x;
  int y;

public:
  Shape() {
    std::cout << "Shape const\n";
    this->x = 0;
    this->y = 0;
  }

  Shape(int x, int y) {
    std::cout << "Shape const2\n";
    this->x = x;
    this->y = y;
  }

  // Copy constr
  Shape(const Shape& s) {
    std::cout << "Shape cpy const\n";
    this->x = s.x;
    this->y = s.y;
  }

  virtual ~Shape() {
    std::cout << "Shape dstr\n";
  }

  void trans(int dx, int dy) {
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

class Rect : public Shape {
private:
  int width;
  int height;

public:
  Rect() : Shape() {   // The : Shape() is implied
    std::cout << "Rect const\n";
    this->width = 1;
    this->height = 1;
  }

  Rect(int w, int h) : Shape() {
    std::cout << "Rect const2\n";
    this->width = w;
    this->height = h;
  }

  Rect(int w, int h, int x, int y) : Shape(x, y) {
    std::cout << "Rect const4\n";
    this->width = w;
    this->height = h;
  }

  // If you don't call :Shape it will call the default base one
  Rect(const Rect& r) : Shape(r) {
    std::cout << "Rect cpy const\n";
    this->width = r.width;
    this->height = r.height;
  }

  virtual ~Rect() {
    std::cout << "Rect dstr\n";
  }

  // Should probably not have this
  //  void trans(int dx, int dy) {
  //    std::cout << "Rect trans\n";
  //    Shape::trans(dx, dy);
  //  }

//is already virtual here because of the shape implementation of area
  double area() {
    return width * height;
  }

  void print() {
    std::cout << "Rect with with of " << width << " and height of " << height << " at " << x << "," << y << "\n";
  }
};


class Circle : public Shape {
private:
  int radius;

public:
  Circle() {
    std::cout << "Circle const\n";
    radius = 1;
  }

  Circle(int r) {
    std::cout << "Circle const1\n";
    radius = r;
  }

  Circle(int r, int x, int y) : Shape(x, y) {
    std::cout << "Circle const3\n";
    radius = r;
  }

  virtual ~Circle() {
    std::cout << "Circle dstr\n";
  }

  double area() {
    return 3.14 * radius * radius;
  }

  void print() {
    std::cout << "Circle with radius of " << radius << " at " << x << "," << y << "\n";
  }
};


int main() {

  Rect* r1 = new Rect(3, 2);
  Circle* c1 = new Circle(5, 3, 2);

  r1->print();
  c1->print();

  r1->trans(5, 3);
  r1->print();

  delete r1;
  delete c1;

  Shape* s1 = new Circle(5, 3, 4);
  s1->print();

  //  Shape* s2 = new Shape();
  //  s2->print();

  Rect* r2 = new Rect(*r1);
  r2->print();

  r2->trans(1, 2);


}
