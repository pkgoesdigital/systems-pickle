#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  int value;
  struct node* next;
} LinkedList;


LinkedList* llCreate() {
  return NULL; //null is actually defined to be memory address 0
}


void llAdd(LinkedList* l, int item) {
  
  //LinkedList newNode; //this creates on runtime stack - need to malloc
  LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
  newNode->value = item;
  newNode->next = NULL;

  if(*l == NULL) { //empty list case
   *l = newNode;

  } else {//all other cases
    //walk through list
    LinkedList* p = *l; //temp pointer (makes 2 things pointing at first node, so when p is pointing to next index in list we still have a pointer to original first location in list)
    while ( (*p).next != NULL ) { //*p dereferences - "changes" to node type instead
      p = p->next; //this means find the pointer, and follow it down to the data its pointing to - can only be used with structures
  }

  p->next = newNode;
  }
}

void llDisplay(LinkedList *1){

}



int main() {
  //linkedList create function
  LinkedList* l = llCreate(); //makes new LL and hands it back after call //l will really be a pointer to head of linkedList

  //addNodemethod
  llAdd(l, 2); //parameter is second, l is reference to linkedList


  



}
