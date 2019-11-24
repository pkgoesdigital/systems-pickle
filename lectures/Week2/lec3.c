#include <stdio.h>
#include <string.h> // all string stuff

typedef struct foo {
  int x;
  int y;
} foo;

typedef int coord;

int main() {

  // CStrings
  char str1[6];
  str1[0] = 'h';
  str1[1] = 'e';
  str1[2] = 'l';
  str1[3] = 'l';
  str1[4] = 'o';
  str1[5] = '\0';

  char* str2 = "world";

  printf("My string is %s\n", str2);
  printf("My string is %c\n", str2[3]);

  if (strcmp(str1, str2)== 0) {
    printf("same\n");
  } else {
    printf("not same\n");
  }

  int l = strlen(str1);
  printf("%d\n", l);

  // str1 = str2
  strcpy(str1, str2);
  printf("%s\n", str1);


  /*
  struct foo f;
  f.x = 5;

  foo b;
  b.x = 5;

  coord c;
  */
}


//in class code from prof
#include <stdio.h>
#include <string.h> // all string stuff
typedef struct foo {
  int x;
  int y;
} foo;
typedef int coord;
int main() {
  // CStrings
  char str1[6];
  str1[0] = 'h';
  str1[1] = 'e';
  str1[2] = 'l';
  str1[3] = 'l';
  str1[4] = 'o';
  str1[5] = '\0';
  char* str2 = "world";
  printf("My string is %s\n", str2);
  printf("My string is %c\n", str2[3]);
  if (strcmp(str1, str2)== 0) {
    printf("same\n");
  } else {
    printf("not same\n");
  }
  int l = strlen(str1);
  printf("%d\n", l);
  // str1 = str2
  strcpy(str1, str2);
  printf("%s\n", str1);
  /*
  struct foo f;
  f.x = 5;
  foo b;
  b.x = 5;
  coord c;
  */
}
