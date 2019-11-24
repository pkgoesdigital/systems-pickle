#include <iostream>
#include "Dog.h"

  Dog::Dog() {
    std::cout << "Dog const:\n";
    strcpy(name, "");
  }

  Dog::Dog(const char* n, const char* c){
    std::cout << "Dog constructor2:\n";
    strcpy(name, n);
    strcpy(color, c);
   }

   //copy constructor
   Dog::Dog(const Dog& d) : Animal(d){
     std::cout << "Dog copy constructor\n";
     strcpy(this->color, d.color);
     strcpy(this->name, d.name);
   }

  Dog::~Dog() {
    std::cout << "Dog destructor\n";
}

  const char* Dog::getColor() {
    return color;
  }

  const char* Dog::getName() {
    return name;
  }

  void Dog::getSound() {
    std::cout << "woof\n";
  }
