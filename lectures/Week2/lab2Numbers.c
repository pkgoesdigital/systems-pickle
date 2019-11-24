//Paula Klimas

#include <stdio.h> //printf and scanf
#include <stdlib.h> //malloc

typedef struct freq {
  int freq;
  int num;

} Histogram ;

//method signature declarations
void displayScores(int numCount, int* numArray);
int* readScores(int* numCount);
void displayHistogram(Histogram* histogram,  int sizeOfHist);
void sortHistogram(Histogram* histogram, int sizeOfHist);
int calcHistogram(Histogram** histogramPointer, int* numArray, int numCount);

int main() {

  int numCount; //represents size of first array
  int* numArray; //creates an array with memory pointer     
  numArray = readScores(&numCount); //fill array with readScores function                           

  int num; //size of Histogram array
  Histogram* arrayPoint;
 
  num = calcHistogram(&arrayPoint, numArray, numCount);

  displayScores(numCount, numArray);

  printf("num: %d arrayPoint: %d\n", num, arrayPoint[0].num);
 
  displayHistogram(arrayPoint, num);

  sortHistogram(arrayPoint, num);

  displayHistogram(arrayPoint, num);

}

int* readScores (int* numCount) {
  
  int* pointer;
  int k = 0, i = 0;

  //adding in malloc
  pointer = (int*)malloc(100 * sizeof(int));
 
  if(pointer == NULL) {
    printf("Memory not allocated.\n");
    exit(0);
  } else {
    printf("Memory successfully allocated\n");
    //fill array till EOF
    while(scanf("%d", &k) != EOF) {
      pointer[i] = k;
      ++i;
      // printf("ReadScores: input %d, filled at index %d\n", k, i);
  } 
  *numCount = i; //changing the value of numCount to i   
  }
  return pointer; //is of type int*
}

void displayScores(int numCount, int* numArray){
  //incrementing through the size of the histogram Array 
  for(int i = 0; i < numCount; i++) {
    printf("score %d: numArray[i]: %d\n", i, numArray[i]);
}
}

//old version took in pre-created array and its count & scores information
//change so count info is passed back through return value rather than parameter
//array should be create on the heap from within the function & passed back through return value
int calcHistogram (Histogram** histogramPointer, int* numArray, int numCount){
  int loneScores = 0;

  //adding in malloc
  //this is referencing a Histogram* pointer which is pointint to the pointer in main
  Histogram* histogram  = (Histogram*)malloc(numCount * sizeof(Histogram));

    //creating array on heap from within function
    for(int i = 0; i < numCount; i++) {
      int foundIt = 0;
      int loopCount = 0;

      while(loopCount < loneScores && !foundIt) {
	if(histogram[loopCount].num == numArray[i]) {
	  histogram[loopCount].freq++;
	  foundIt = 1;
	} else {
	  ++loopCount;
	  // printf("incremented loopCount\n");
      }
    }
      if(loopCount == loneScores){
	histogram[loopCount].num = numArray[i];
	histogram[loopCount].freq = 1;
	++loneScores;
	// printf("calcHistogram incremented loneScores\n");
      }
    }
    printf("calcHistogram loneScores val: %d\n", loneScores);
    *histogramPointer = histogram;  

 return loneScores;
}


void displayHistogram(Histogram* histogram,  int sizeOfHist) {  

  //printing out the histogram frequencies
  for(int i = 0; i < sizeOfHist; i++) { //incrementing through the size of the Histogram array
    printf("value %d: freq %d\n", histogram[i].num, histogram[i].freq); //printing the value in the array with histogram[i].num and the frequency with histogram[i].freq
}
}

//should modify the histogram array it is given to be in order by frequency
void sortHistogram(Histogram* histogram, int sizeOfHist) {
  int count = 0;
  for(int i = 0; i < sizeOfHist; i++) {
    //sort
    int max = i;
    for(int j = i; j < sizeOfHist; j++) {
      if(histogram[j].freq > histogram[max].freq) {
	max = j;
      }
    }
      if(max != i) {
	//you've found max freq
	Histogram temp = histogram[i];
	histogram[i] = histogram[max];
	histogram[max] = temp;
      }
  }
}
