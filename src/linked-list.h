#ifndef COGITO_LL
#define COGITO_LL

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
  char *val;
  struct node *next;
} node_t;

node_t* ll_build(char *val);
void ll_append(node_t *head, char *val);
void ll_print(node_t *node);
size_t ll_val_size_sum(node_t *head);
int ll_size(node_t *head);

#endif
