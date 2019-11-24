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
