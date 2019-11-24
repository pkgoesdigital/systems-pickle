#include <string.h>
#include <stdio.h>


void displayFloat(float f);
float makeFloat(char* f);


typedef union floatU {
  unsigned int bits;
  float theFloat;
} floatU;


//DisplayFloat should take in a C float and display the 32 bits that represent that float to the screen
void displayFloat(float f) {

  union floatU data;
  
  data.theFloat = f;

  //copy of union "f"
  union floatU temp;
  temp.theFloat = 0;
 
  printf("displayFloat data.theFloat %f\n", data.theFloat);

  //floats are 32 bits - index 0 is sign, next 8 are exponent, last are fraction
  for(int index = 31; index >= 0; index--) {
    temp.bits = data.bits >> index;
    temp.bits = temp.bits & 1;
    if(index == 30 || index == 22) {
      printf(" ");
    }
    printf("%u", temp.bits);
  }
  //float is 32 bits
  printf("\n");
}

float makeFloat(char* f) {
  
  floatU binString;
  binString.bits = 0;

  //setting sign bit
  if(f[0] == '-') {
    binString.bits = binString.bits + 1;
    binString.bits = binString.bits << 31;
  }
  
  //exponent bits
  unsigned int i = 0;
  while(f[i] != '.') {
    i++;
  }
  i = i - 2; //exponent
  i = 127 + i;//with bias
  
  binString.bits = binString.bits | (i << 23);
  //displayFloat(binString.theFloat);

  //fraction bits
  int index = 2; //skip sign and first digit left of decimal after normalization
  int tracker = 22; //32 - 1sign bit - 8exponentbits then 0 based-index
  for(index = 2; index <= strlen(f); index++) { //looping number of chars in parameter
    if(f[index] == '.') {
      //skip decimal
      ++index;
    }
  unsigned int one = 1;
    if(f[index] == '1') {
      //shifting bits based on tracker value - adding 1 to binString at index of tracker - each iteration
      binString.bits = binString.bits | (one << tracker);
      --tracker;
    }
    if(f[index] == '0') { 
      --tracker;
    }
  }
  
  displayFloat(binString.theFloat);
  return binString.theFloat;

}


int main() {
  
  displayFloat(-5.8125);
  displayFloat(5.8125);

  makeFloat("-101.1101");
  

}
