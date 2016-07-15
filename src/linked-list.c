#include "linked-list.h"

node_t* ll_build(char *val) {
  node_t *node = (node_t*) malloc(sizeof(node_t));
  node->val = val;
  node->next = NULL;
  return node;
}

void ll_print(node_t *node) {
  node_t *ptr = node;

  while(ptr != NULL) {
    printf("[%s]\n", ptr->val);
    ptr = ptr->next;
  }
  printf("\n");
}
