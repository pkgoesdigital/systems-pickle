#include <string.h>
#include <stdio.h>

//two's complement representation

void displayInt(int i);
//int makeInt(char* i);
int makeInt(char* s);


typedef union intU {
  unsigned int bits;
  int theInt;
} intU;


//letting comp do conversion to the two's complement
//assign it to the Int part of the union
//use loop to display each of the bits (using the bits as part of the union)
void displayInt(int i) {

  union intU data;

  printf("displayInt data.bits: %i\n", data.bits);

  data.theInt = i;
  printf("displayInt data.theInt: %i\n", data.theInt);

  for(int index = 31; index >= 0; --index) {
      data.bits = i >> index;
      data.bits = data.bits & 1;
      printf("%i", data.bits);
      if(index % 8 == 0) {
	printf(" ");
      }
    }
  //C int is 32 bits
  printf("\n");
}

int makeInt(char* s) {
  //convert to 32 bits
  //make c do the conversion
  //start from 1 in loop
  intU binString;
  binString.bits = 0;

  //masking bits & filling with values
  for(int i = 1; i < strlen(s); ++i) {
    //fill binString
    binString.bits = (binString.bits << 1) + (s[i] - '0');
  }
  if(s[0] == '-') {
    //two's complement - negate and add 1
    binString.bits = (~binString.bits) + 1;
  }
  printf("theInt: %i\n", binString.theInt);
  return binString.theInt;
}


int main() {

  displayInt(5); //working!!
  displayInt(-9); //working!!

  //testing makeInt method
  int result1 = makeInt("+101");
  //should return 5

  int result2 =  makeInt("-1001");
  //should return -9

  int result3 = makeInt("+10001010101");




}
