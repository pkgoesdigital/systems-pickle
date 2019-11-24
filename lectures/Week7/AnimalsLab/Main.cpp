#include <iostream>
#include "Animal.h"
#include "Cat.h"
#include "Dog.h"
#include "Duck.h"

int main(int argc, char const *argv[]) {

  Dog* a1 = new Dog("Fido", "brown");
  std::cout << a1->getName() << "\n";
  std::cout << a1->getColor() << "\n";
  a1->getSound();

  //You should also test having your animals cast as the generic top-level class.  For example:
  Animal* a2 = new Cat("Whiskers", "calico");
  a2->getSound();
  std::cout << a2->getColor() << "\n";

  Animal* a3 = new Duck("brown");
  a3->getSound();
  std::cout << a3->getColor() << "\n";

  //
  // Dog* a4 = new Dog(*a1);
  // std::cout << a4->getName() << "\n";
  // std::cout << a4->getColor() << "\n";


  //Make sure to test your copy constructor and destructor as well
  delete a1;
  delete a2;
  delete a3;


}
