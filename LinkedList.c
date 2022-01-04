/* Slighted modified LinkedList C implementation from Wikipedia */

#include <stdio.h>    /* for printf */
#include <stdlib.h>   /* for malloc */
#include "LinkedList.h"

// Functions

// Add to the head of the given linkedlist
LLIST* list_add(LLIST **p, struct tnode* tn) {
  // Sanity check to make sure this is really a pointer to a linkedlist
  if (p == NULL)
    return NULL;
  
  LLIST *n = malloc(sizeof(LLIST));
  // Make sure we were able to allocate the next node
  if (n == NULL)
    return NULL;
  
  // Do the linking by adding it to the head of p
  n->next = *p; /* the previous element (*p) now becomes the "next" element */
  *p = n;       /* add new empty element to the front (head) of the list */
  n->data = tn;
  
  return *p;
}

LLIST* list_add_in_order(LLIST **p, struct tnode *tn) {
	if (p == NULL)
		return NULL;

	LLIST *s = malloc(sizeof(LLIST));
	if (s == NULL)
		return NULL;
	LLIST** n = p;
	if((*n) == NULL || (*n)->data->weight >= (*tn).weight) {
		list_add(p,tn);
	} else {

		while((*n)->next != NULL) {
			//printf("here\n");
			if(((*n)->next)->data->weight >= (*tn).weight){
				break;
			}
			n = &((*n)->next);
		} 
		s->data = tn;
		s->next = (*n)->next;
		(*n)->next = s;
	}
	return *p;
}
LLIST* LLCreate() {
	return NULL;
}
// Remove the head of the given linkedlist
void list_remove(LLIST **p) {
  if (p != NULL && *p != NULL) {
    LLIST *n = *p;
    *p = (*p)->next;
    free(n);
  }
}

// Find the node in the list and return it
LLIST **list_search(LLIST **n, int d) {
  if (n == NULL)
    return NULL;
  
  while (*n != NULL) {
    if ((*n)->data->c == d) {
      return n;
    }
    n = &((*n)->next);
  }
  return NULL;
}

// Display the list
void list_print(LLIST *n) {
  printf("[");
  while (n != NULL) {
    printf(" %d %c (%p -> %p) --", n->data->weight, n->data->c,  n, n->next);
    n = n->next;
  }
  printf("]\n");
}
/*
int main() {
	LLIST* A = LLCreate();
	struct tnode p;
	p.weight = 12;
	p.c = 0;
	struct tnode s;
	s.weight = 17;
	s.c = 0;
	struct tnode w;
	w.weight = 15;
	w.c = 0;
	list_add_in_order(&A, &p);
	list_add_in_order(&A, &s);
	//list_print(A);
	list_add_in_order(&A, &p);
	//printf("break\n");
	//list_print(A);
	list_add_in_order(&A, &s);
	//printf("break\n");
	list_add_in_order(&A, &w);
	//list_add(&A, 3);
	printf("f\n");
	//list_add(&A, 4);
	//list_print(A);

}
*/
