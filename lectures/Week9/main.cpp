#include <iostream>
#include "Rational.h"

void foo(Rational r) {

}

int main() {

  Rational* r1 = new Rational(5, 3);
  //  r1->display();

  Rational r2; //default constructor
  //  r2.display();

  Rational* r4 = new Rational(5, 8);

  //  foo(*r1);

  //Rational* r3 = new Rational(r2);


  //  Rational* r3 = r1->mult(&r2);

  //  Rational* r3 = r1->mult(r4);

  Rational* r3 = r1 * r2;  // r1.operator*(r4);

  //Rational* r3 = r1.mult(r2);
  //  Rational* r3 = r2 * r2;  // r1.operator*(r4);

  Rational r5 = r2;//  r5.operator=(r2)

  r3->display();

  std::cout << r2;
  //  std::cout.operator<<(r2);   (1)
  //  operator<<(std::cout, r2);   (2)

  delete r1;
  //delete r2;  // NO
}
