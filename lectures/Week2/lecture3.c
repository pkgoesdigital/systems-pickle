//class 4 notes

#include <stdio.h>
#include <stdlib.h> //malloc/free — was missing; modern compilers reject implicit declarations

typedef int coord;

int main() {
  int* a = (int*) malloc(10 * sizeof(int)); //int a[10]

  free(a); //frees heap memory *don't double free!!! major crash
  a = NULL; //null frees the memory - is nice to do in order to get segmentation fault errors so you can troubleshoot easier

  // a[2] = 5; //this is legal, but it changes the memory so things will be accessed differently
  //  ^ uncomment to watch it crash. Because a was just set to NULL, this
  //    writes to address 0x8 and the program dies with SIGSEGV — which is
  //    exactly the "nice to do ... so you can troubleshoot easier" payoff
  //    the line above describes. Left commented so the file runs clean.


}

// Second transcription from the same class — a C-strings walkthrough.
// Guarded out so this file compiles as one translation unit (two main()s
// can't coexist); it is also an unfinished draft: the buffer is declared
// `str` but used as `str1` throughout. The finished version of this exact
// program is lec3.c in this folder.
#if 0
#include <stdio.h>
#include <string.h> //includes all string things

typedef int coord;

int main() {
  //CS Strings

  char str[6];
  str1[0] = 'h';
  str1[1] = 'e';
  str1[2] = 'l';
  str1[3] = 'l';
  str1[4] = 'o';
  str1[5] = '\0';

  char* str2 = "world"; //this line is looking at the string, saying it has 5 characters, we need an array with 6 characters, and


  printf("My string is %s\n", str1); //this prints the entire str1
  printf("My string is %s\n", str2); //this prints the entire str2
  printf("My string is %c\n", str2[3]); //this prints l

if(strcmp(str1, str2)== 0) {
//if(str1 == str2) { //we're literally comparing pointers here
  printf("same\n");
} else {
  printf("not same\n");
}

int l = strlen(str1); //this length does not include the termination character
printf("%d\n", 1);

strcpy(str1, str2); //which is source and which is copy? think about it as the second value is getting assigned into first one
//cannot read or copy a string into a smaller buffer
printf("%s\n", str1);

//working with structs
  // struct foo f;
  // f.x = 5;
  //
  // foo b;
  // b.x = 5;
  //
  // coord c;
  //
}
#endif

//lab02 - we need to use malloc to make the arrays in the methods, and change the arrays into dealing with words and not numbers
