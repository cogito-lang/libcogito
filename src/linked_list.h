#ifndef COGITO_LL
#define COGITO_LL

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct cg_node {
  char *val;
  struct cg_node *next;
} cg_node_t;

#define cg_ll_foreach(head, ptr) \
  for ((ptr) = head; (ptr) != NULL; (ptr) = (ptr)->next)

void cg_ll_append(cg_node_t *head, char *val);
cg_node_t* cg_ll_update(cg_node_t *head, char *val);
cg_node_t* cg_ll_build(char *val);
void cg_ll_print(cg_node_t *node);
int cg_ll_size(cg_node_t *head);
size_t cg_ll_val_size_sum(cg_node_t *head);
void cg_ll_free(cg_node_t *head);

#endif
