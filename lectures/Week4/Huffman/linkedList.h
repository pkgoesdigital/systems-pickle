#include <stdio.h>
#include <stdlib.h> // malloc  


/* typedef struct node {
  int value;
  struct node* next;
  } LinkedList; */

typedef struct tnode {

  int frequency;

  int c;

  struct tnode* left;

  struct tnode* right;

  struct tnode* parent;
} LinkedList;


LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, int newValue);
void llFree(LinkedList* ll);


