#include <iostream>
#include "Duck.h"

  Duck::Duck() {
    std::cout << "Duck const:\n";
  }

  Duck::Duck(const char* c) : Animal(){
    std::cout << "Duck constructor2:\n";
    strcpy(this->color, c);
  }

  //copy constructor
  Duck::Duck(const Duck& d) : Animal(d){
    std::cout << "Duck copy constructor\n";
    strcpy(this->color, d.color);
    strcpy(this->sound, d.sound);
  }

  Duck::~Duck() {
    std::cout << "Duck destructor\n";
  }

  const char* Duck::getColor() {
    return color;
  }

  void Duck::getSound() {
    std::cout << "quack\n";
  }
