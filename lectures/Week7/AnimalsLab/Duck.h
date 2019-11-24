#ifndef DUCK_H
#define DUCK_H
#include <iostream>
#include "Animal.h"

class Duck : public Animal {

 public:
  Duck();
  Duck(const char* c);
  Duck(const Duck& d);
  virtual ~Duck();
  const char* getColor();
  void getSound();

};
#endif
