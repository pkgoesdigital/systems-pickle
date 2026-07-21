#ifndef ANIMAL_H
#define ANIMAL_H
#include <iostream>
#include <cstring> // strcpy — macOS libc++ drags this in via <iostream>,
                   // Linux libstdc++ does not, so the 2019 code built on a
                   // Mac and failed everywhere else

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
