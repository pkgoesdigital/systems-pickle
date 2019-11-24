#include <stdio.h> //printf and scanf
#include <stdlib.h> //malloc

int* fill(int* b, int* c) { //int* is memory address for b (pointer to the int)
  //  int b[10]; //creates array on runtime stack
  int* b =  (int*)malloc(10 * sizeof(int)); //cast to int* to make sure the types match (not always necessary but good practice)
  //malloc stands for memory location MALLOC WORKS ONLY IN BYTES - allocates that number of bytes on the heap(in this case, 40)
  int n = 5;
  for(int i = 0; i < n; ++i) {
    b[i]=i;
  }
  *c = n; //reach back through the pointer, and put a 5 in that slot (val of n)
  return b; //which is type int*

}

int search(int* a, int size, int target) { //search function, need to pass size of the array, and just need to check value of target (don't need pointer)
int i = 0;
int foundIt = 0;
//we will search until we hit the end, or till we findIt
while(i<size && !foundIt) {
  if(a[i] == target) {
    foundIt = 1; //setting foundIt to true
  } else {
    i++;
  }
}
if(!foundIt) {
  return -1;
}else {
  return i; //return index of where we found the item
}

//not ideal, as we don't know how many times we will loop, because we don't know where the value we are searching for is
//  for(int i = 0; i < size, ++i) {
//    if(a[i] == target) {
//      return i;
//    }
//  }
//  return -1;

}

int main() {

  //  int a[10]; //this is waste of memory, is replaced in following code
  int* a; //this created an array with memory pointer
  int count;
  //  a[2] = 3; //this is the same as the line below but c changes the pointer
  //  *(a+2) = 3; //this is now a pointer to the second location - take value at slot and make it a 3 - start doing arrays in this way

  a = fill(a, &count); //we're going to fill this array with the fill function above

  for(int i = 0; i < count; ++i) {
    printf("%d ", a[i]);
  }

  int val = search(a, count, 4); //pass things around with this, anytime we're doing things with multiple components (values and pointers)
  printf("%d\n", a[i]);

}
//c and c++ do NOT have a garbage collector - it is OUR responsibility to get rid of things in the heap and keep track of what's in memory
//when things go away in the stack, the memory pointer references are wiped, so we no longer have access to the things we've stored in the heap (objects we've stored)
//will completely clog your memory - MEMORY LEAKS - not an issue for small programs (when program ends it goes away) but for progams that run a long time, memory can be clogged



//in-class code

#include <stdio.h>   // printf/scanf
#include <stdlib.h>  // malloc
int search(int* a, int size, int target) {
  int foundIt = 0;
  int i=0;
  while (i<size && !foundIt) {
    if (a[i] == target) {
      foundIt = 1;
    } else {
      i++;
    }
  }
  if (!foundIt) {
    return -1;
  } else {
    return i;
  }
}
int* fill(int* c) {
  //int b[10];  // creates array on runtime stack
  int* b = (int*)malloc(10 * sizeof(int));
  int n = 5;
  for(int i=0; i<n; i++) {
    b[i] = i*2;
  }
  *  c = n;
  return b;
}
int main() {
  int* a;
  int count;
  a = fill(&count);
  printf("%d\n", a[2]);
  for(int i=0; i<count; i++) {
    printf("%d ", a[i]);
  }
  int index = search(a, count, 3);
  printf("%d\n", index);
  //  a[2] = 3;
  //  *(a+2) = 3;
}
