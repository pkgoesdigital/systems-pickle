#include <stdio.h> //printf and scanf
#include <string.h> //reading in and working with strings
#include <stdlib.h>
#include <math.h>
#include <ctype.h> //using isdigit

//create two functions that perform binary to decimal conversion and back

int binToDec(char* bin) { //passing in char array named bin (pointer to char array technically)  
  int decimalToReturn;
  int digitCounter = 0;
  // printf("digitCounter: %d\n", digitCounter);

  while(bin[digitCounter] != '\0') {
    //getting length of binary number
    //  printf("digitCounter: %d\n", digitCounter);
    digitCounter++;
  }
  // printf("Number of digits in Binary Number: %d\n", digitCounter);
  int point = 0;
  
  for(int i = digitCounter-1; i  >= 0; i--) {
    if(bin[point] == '1') {
      decimalToReturn += pow(2, i);
      //printf("decimalToReturn: %i\n", decimalToReturn);
    } 
    ++point;
    //printf("point: %d\n", point);
  }
  printf("decimalToReturn: %i\n", decimalToReturn); 
  return decimalToReturn;

}

char* decToBin(int dec) { //decimal conversion is 25 [11001]

  int numDigits = 0;
  int exp = 0;
  while(dec >= pow(2,exp)) {
    ++numDigits;
    ++exp;
  }
  --exp;
  
  char* binArray = (char*)malloc((numDigits+1) * (sizeof(char)));

  for(int index = 0; index < numDigits; ++index) {
    if((pow(2,exp)) <= dec) {
      printf("power of 2 is less than decimal -- decimal is: %i\n", dec);
      printf("print of index: %d\n", index);
      dec = dec - (pow(2,exp));
      printf("dec value: %d\n", dec);
      binArray[index] = '1';
      printf("array: [%s]\n", binArray);
      --exp;
    }
    else if((pow(2,exp)) > dec) {
      printf("power of 2 is greater than decimal -- decimal is: %i\n", dec);
      printf("print of index: %d\n", index);
      binArray[index] = '0';
      printf("array: [%s]\n", binArray);
      --exp; //go backwards in exponents to continue to subtract values
    }
    
  }

  //account for null character at end of newly created char array
  binArray[numDigits] = '\0';

  //should be [11001] when passing in 25
  printf("array after filling: [%s]\n", binArray);
  return binArray;
}

//make copy of above methods and upgrade to do any base conversion to decimal and back
int baseToDec(int base, char* value) {
  
  int decimalToReturn = 0;
  int digitCounter = 0;

  while(value[digitCounter] != '\0') {
    digitCounter++;
  }

  printf("digitCount: %d\n", digitCounter);

  int temp = 0;
  int exp = 0;
  for(int i = digitCounter-1; i  >= 0; i--) {
    if(isdigit(value[i])) {
      temp = value[i] - '0'; //
    }
    else {
      temp = (value[i] - '0') - 7; //convert from hex
    }
    temp = temp * pow(base,exp);
    decimalToReturn += temp;
    ++exp;
  }
  printf("decimalToReturn: %i\n", decimalToReturn);
  return decimalToReturn;
}



char* decToBase(int base, int dec) {
  int numDigits = 0;
  int exp = 0;

  while(dec >= pow(base,exp)) {
    ++numDigits;
    ++exp;
  }
  --exp;

  char* decArray = (char*)malloc((numDigits+1) * (sizeof(char)));
  int index = 0;

  for(int index = 0; index < numDigits; ++index) {
    if((pow(base,exp)) <= dec) {
      int multiplier = 0;
      while((pow(base,exp) * multiplier) <= dec) {
	++multiplier;
      }
      --multiplier; //exponent is one less than this value hence decrement
      printf("decimal value: %d\n", dec);
      dec = dec - (pow(base,exp) * multiplier);
      printf("decimal value: %d\n", dec);
      if(multiplier >= 10) {
	decArray[index] = multiplier + '0' + 7; //conversion to hex
      } else {
      decArray[index] = multiplier + '0';
      }
      printf("array: [%s]\n", decArray);
      --exp;

    } else if((pow(base,exp)) > dec) {
      printf("%d to the %d > decimal, decimal is: %d\n", base, exp, dec);
      printf("index in decToBase elif: %d\n", index);
      decArray[index] = '0';
      printf("array: [%s]\n", decArray);
      --exp; //go backwards in exponents to continue to subtract values                                                                     
    }

  }
  //account for null character at end of newly created char array                                                                           
  decArray[numDigits] = '\0';

  //should be [11001] when passing in 25                                                                                                    
  printf("array after filling: [%s]\n", decArray);
  return decArray;
}


int main() {
  
  //calls for initial methods - converting from binary to dec & viceversa
  int decimal = binToDec("11001");
  char* binary = decToBin(128);
  
  //calls for generic methods
  int d = baseToDec(2, "11001");
  int b = baseToDec(8, "157");
  int c = baseToDec(16, "F8");

  //generic decimal To Base
  char* f = decToBase(8, 100);
  char* z = decToBase(16, 160);
  
  
  
}
