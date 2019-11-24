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
