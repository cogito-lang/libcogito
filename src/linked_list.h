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

void cg_ll_append(node_t *head, char *val);
node_t* cg_ll_update(node_t *head, char *val);
node_t* cg_ll_build(char *val);
void cg_ll_print(node_t *node);
int cg_ll_size(node_t *head);
size_t cg_ll_val_size_sum(node_t *head);
void cg_ll_free(node_t *head);

#endif
