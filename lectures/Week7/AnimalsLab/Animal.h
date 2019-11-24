#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>

class Animal {

 protected:
    char color[20];
    char* sound;

 public:
    Animal();
    Animal(char* color, char* sound);
    Animal(const Animal& a);
    virtual ~Animal();
    virtual const char* getColor() = 0;
    virtual void getSound() = 0;

};
#endif
