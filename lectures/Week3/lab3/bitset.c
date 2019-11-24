#include <stdio.h> //printf and scanf
#include <stdlib.h> //malloc
#include <string.h> //reading in and working with strings


typedef unsigned short bitSet;


//method signature declarations
bitSet makeBitSet(); //create a new bitset
void displayBitSet(bitSet bs); //Displays the 16 bits of the bitset to the screen
void setBit(bitSet* bs, int index); //Sets bit 'index' of the bitset to 1
void clearBit(bitSet* bs, int index); //Sets bit 'index' of the bitset to 0
int bitValue(bitSet bs, int index); //Returns the value of the bit at 'index'

//***NOTE***
//MUST USE BITWISE OPERATIONS RATHER THAN ADDINT AND POWERS TO DO THESE FUNCTIONS
//WITH THE EXCEPTION OF THE DISPLAY FUNCTION, THERE SHOULD BE NO LOOPS


bitSet makeBitSet() {
  return 0;
}

//>> right shift, << left shift
void displayBitSet(bitSet bs) {
  bitSet temp = 0;
  for(int i = 15; i >= 0; --i) {
    temp = bs >> i;
    temp = temp & 1; //anding to single out bit
    printf("%i",temp);
  }
  printf("\n");
}

void setBit(bitSet* bs, int index) {
  bitSet temp = 1;
  temp = temp << (index-1);
  temp = temp | *bs;
  *bs = temp;
}

void clearBit(bitSet* bs, int index) {
  bitSet temp = 1;
  temp = temp << (index-1);
  temp = ~temp; 
  temp = temp & *bs;
  *bs = temp;
}


int bitValue(bitSet bs, int index) {
  bitSet temp = bs;
  temp = temp >> (index-1);
  temp = temp & 1;
  return temp;
}



//should have main and several functions that operate on bitsets
int main() {
  
  bitSet b = makeBitSet();
  displayBitSet(b);
  b = 5;
  displayBitSet(b);
  
  setBit(&b, 5);
  displayBitSet(b);
  
  clearBit(&b, 5);
  displayBitSet(b);

  int value = bitValue(b, 3);
  printf("value:%i", value);
}

