#ifndef DOG_H
#define DOG_H
#include <iostream>
#include "Animal.h"

class Dog : public Animal {

 private:
  char name[20];

 public:
  Dog();
  Dog(const char* n,const char* c);
  Dog(const Dog& d);
  virtual ~Dog();
  const char* getColor();
  const char* getName();
  void getSound();

};
#endif
