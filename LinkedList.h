#include "hcompress.h"  // for struct tnode
// Structures and typedefs
struct node {
  struct tnode *data;
  struct node *next; /* pointer to next element in list */
};
typedef struct node LLIST;


// Prototypes
LLIST *list_add(LLIST **p, struct tnode *pp);
void list_remove(LLIST **p);
LLIST **list_search(LLIST **n, int);
void list_print(LLIST *n);
LLIST* list_add_in_order(LLIST **p, struct tnode *tn);
LLIST* LLCreate();
