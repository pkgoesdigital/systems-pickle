#include <iostream>
#include "Cat.h"

  Cat::Cat() {
    std::cout << "Cat const:\n";
    strcpy(this->name, "");
  }

  Cat::Cat(const char* n,const char* c) : Animal(){
    std::cout << "Cat constructor2:\n";
    strcpy(this->name, n);
    strcpy(this->color, c);
  }

  //copy constructor
  Cat::Cat(const Cat& c) : Animal(c){
    std::cout << "Cat copy constructor\n";
    strcpy(this->color, c.color);
    strcpy(this->name, c.name);
  }

  Cat::~Cat() {
    std::cout << "Cat destructor\n";
  }

//move all color methods into Animal - inherit color property from Animal
  const char* Cat::getColor() {
    return color;
  }

  const char* Cat::getName() {
    return name;
  }

  void Cat::getSound() {
    std::cout << "meow\n";
  }
