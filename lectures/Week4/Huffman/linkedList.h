#include <stdio.h>
#include <stdlib.h> // malloc


typedef struct node {
  int value;
  struct node* next;
} LinkedList;

// Huffman tree node. In 2019 this typedef replaced the node struct above
// and was *also* named LinkedList — which broke linkedList.c, whose code
// still used .value/.next. Both now coexist under their own names; the
// tree node belonged to the hcompress assignment (see
// hcompress-fragment.c.txt and HuffmanSubmission.docx).
typedef struct tnode {

  int frequency;

  int c;

  struct tnode* left;

  struct tnode* right;

  struct tnode* parent;
} TreeNode;


LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, int newValue);
void llFree(LinkedList* ll);
