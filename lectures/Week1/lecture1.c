#include <stdio.h>

x
//this is kind of the same thing as objects, but not methods - this is basically glue-ing the data together
struct coord { //this is a new "type" and the type is struct coord
  int x;
  int y;
  int z;
}; //must have semi-colon at the end of structures

//array of structs
int a[5];
struct hist a[5]; //nested loop with arrays that are 'glued' to each other, then write code to sort the array


//prototypes - can put functions anywhere you want as long as prototypes are up top
void foo(int z);

//passing an array to a fucntion
int xya(int* b) { //this argument is a memory address of an int
  //an array is really a pointer to an integer - this allows you to save memory and avoid having to copy arrays (storing pointers instead of full values)
  b[1] = 2;
  //to index through an array - you have to keep track of the array and the size of the array in c

}

//swap method
void swap(int* pp, int* qq) { //* keeps pointers to original values (mem addresses)
  int temp == *pp;
  *pp = *qq; //follow pointer of pp and qq and reassign
  *qq = temp;
}

int main() {

  struct coord p; //relates to the structure listed above - glues objects together just like classes did in java

  int aa = 5;
  int bb = 8;
  swap(&aa, &bb); //
  printf("%d %d\n", aa, bb);





  int i = 3;

  //this gets memory address of i
  int* q = &i;
  //this gets value at memory address
  int k = *q; //this says "go look at this memory address and go get the value that's there"
  printf("%d\n", k);



  //int[] arr = new int[5];
  //there is no keyword new in c
  int a[5];

  a[0] = 2;
  a[8] = 3;
  a[1] = 7;

  //add 1 because c is smart enough to know the array stores integers, so it moves 4 bytes down in terms of size (1 integer)
  //a[1] is called sugar programming - is really for programmers, cause it does nothing to the computer ultimately - when we type a[8] its really *(a+8)
  printf("%d %d\n", a[0], *(a+1);

  int* b = a ; //this will be stored as an integer  pointer type (aka memory address)
  //printf("%p %p\n", b, a+1);

  //  printf("%d %d\n", a[1], a[1]);
  printf("%p %p\n", a, a+1) //pointer addition
  printf("%d %d\n", a[0], a[6]);

  double x = 5.3;
  int y = 8;
  char c = 'a';
  int q = 'a'; //this returns the int value assigned to this char
  //char c = 98; this returns the character assigned to the ascii value
  //in c and c++ chars are 1 byte long (8 bits) as opposed to java chars are 2 bytes

  //characters and integers are interchangeable in c because of ascii code! a is in fact a 97 in ascii code
  printf{"The value of x is %lf and y is %d and %c \n", x, y, c);

  //if statements are the exact same in c
  //if you do this: if(y = 8) 8 will be shoved into y - this command will not compile in java - booleans are integers in c- anything not 0 is true
  if (y == 7) {
    printf("equals\n");
  } //else {
  //something else
  // }

  foo(y);

  return 0;

}

void foo(int z){
  printf("in foo with value %d\n");
}
