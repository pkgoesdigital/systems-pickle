#include <iostream>
#include "Animal.h"

Animal::Animal() {
  std::cout << "Animal definition constructor\n";
  // strcpy(this->color, "color");
  // strcpy(this->sound, "sound");
}

Animal::Animal(char* c, char* s) {
  std::cout << "Animal constructor2\n";
  strcpy(this->color, c);
  strcpy(this->sound, s);
}

//copy constructor
Animal::Animal(const Animal& a) {
  std::cout << "Animal copy constructor\n";
  strcpy(this->color, a.color);
  strcpy(this->sound, a.sound);
}

Animal::~Animal() {
  std::cout << "Animal destructor\n";
}
