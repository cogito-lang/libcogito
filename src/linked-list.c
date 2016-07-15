#include "linked-list.h"

node_t* ll_build(char *val) {
  node_t *node = (node_t*) malloc(sizeof(node_t));
  node->val = val;
  node->next = NULL;
  return node;
}

void ll_append(node_t *head, char *val) {
  node_t *tail = ll_build(val);
  node_t *ptr = head;

  while(ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = tail;
}

void ll_print(node_t *node) {
  node_t *ptr = node;

  while(ptr != NULL) {
    printf("[%s]\n", ptr->val);
    ptr = ptr->next;
  }
  printf("\n");
}
