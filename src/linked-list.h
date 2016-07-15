#ifndef COGITO_LL
#define COGITO_LL

#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  char *val;
  struct node *next;
} node_t;

node_t* ll_build(char *val);
void ll_append(node_t *head, char *val);
void ll_print(node_t *node);

#endif
