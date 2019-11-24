//Paula Klimas

#include <stdio.h>
struct freq {
  int freq;
  int num;
};

//method signature declarations
void displayScores(int numCount, int* numArray);
void readScores(int* numCount, int* numArray);
void displayHistogram(struct freq* histogram,  int sizeOfHist);
void sortHistogram(struct freq* histogram, int sizeOfHist);
void calcHistogram(struct freq* histogram, int numCount, int* numArray, int* sizeOfHist);



int main() {

  int numCount;
  int numArray[100]; //creates an array with memory pointer                                                  
  readScores(&numCount, numArray); //fill array with readScores function                           

  int num;
  struct freq histogram[numCount];

  calcHistogram(histogram, numCount, numArray, &num);

  displayScores(numCount, numArray);
 
  displayHistogram(histogram, num);

  sortHistogram(histogram, num);

  displayHistogram(histogram, num);

}



void readScores (int* numCount, int* numArray) {
  int i = 0; //# read in
  int k = 0;
  //fill until we hit the end of the file

  while(scanf("%d", &k) != EOF) {
    numArray[i] = k;
    ++i;
  }
  *numCount = i; //changing the value of numCount to i
}




void displayScores(int numCount, int* numArray){

  for(int i = 0; i < numCount; i++) {
    printf("score %d: %d\n", i, numArray[i]);
}
}




void calcHistogram (struct freq* histogram, int numCount, int* numArray, int* sizeOfHist){
  
  int loneScores = 0;

  for(int i = 0; i < numCount; i++) {
  int foundIt = 0;
  int loopCount = 0;

   while(loopCount < loneScores && !foundIt) {
      if(histogram[loopCount].num == numArray[i]) {
	histogram[loopCount].freq++;
	foundIt = 1;
      } else {
	++loopCount;
      }
    }
    if(loopCount == loneScores){
      histogram[loopCount].num = numArray[i];
      histogram[loopCount].freq = 1; 
	++loneScores;
    }
  }
  //passes back to where pointer is in main
  *sizeOfHist = loneScores;
}



void displayHistogram(struct freq* histogram,  int sizeOfHist) {  

  for(int i = 0; i < sizeOfHist; i++) {
    printf("value %d: freq %d\n", histogram[i].num, histogram[i].freq);
}
}




//should modify the histogram array it is given to be in order by frequency
void sortHistogram(struct freq* histogram, int sizeOfHist) {
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
	struct freq temp = histogram[i];
	histogram[i] = histogram[max];
	histogram[max] = temp;
      }

  }
}
