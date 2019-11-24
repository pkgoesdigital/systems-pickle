#ifndef RATIONAL_H
#define RATIONAL_H

#include <iostream>

class Rational {
private:
  int num;
  int dem;

public:
 
  Rational();
  Rational(int n);
  Rational(int n, int d);
  Rational(const Rational& r);

  ~Rational();

  Rational* operator*(const Rational& r) const;
  Rational& operator=(const Rational& r);
  

  void display();


  friend std::ostream& operator<<(std::ostream& os, const Rational& r);
};

#endif
