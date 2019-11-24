#ifndef CAT_H
#define CAT_H
#include <iostream>
#include "Animal.h"

class Cat : public Animal {
 private:
  char name[20];

 public:
  Cat();
  Cat(const char* n, const char* c);
  Cat(const Cat& c);
  virtual ~Cat();
  const char* getColor();
  const char* getName();
  void getSound();

};
#endif
