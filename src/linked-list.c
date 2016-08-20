#include "linked-list.h"

// Append a node to the end of the list
void ll_append(node_t *head, char *val) {
  node_t *tail = ll_build(val);
  node_t *ptr = head;

  while(ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = tail;
}

node_t* ll_update(node_t *head, char *val) {
  if (head == NULL) {
    return ll_build(val);
  }
  ll_append(head, val);
  return head;
}

// Build a list node
node_t* ll_build(char *val) {
  node_t *node = (node_t*) malloc(sizeof(node_t));
  node->val = val;
  node->next = NULL;
  return node;
}

// Print out the list starting at the given node
void ll_print(node_t *node) {
  node_t *ptr = node;

  while(ptr != NULL) {
    printf("[%s]\n", ptr->val);
    ptr = ptr->next;
  }
  printf("\n");
}

// The number of nodes in the list
int ll_size(node_t *head) {
  int size = 0;
  node_t *ptr = head;

  while(ptr != NULL) {
    size += 1;
    ptr = ptr->next;
  }
  return size;
}

// The sum of the size of all of the values in the list
size_t ll_val_size_sum(node_t *head) {
  size_t size = 0;
  node_t *ptr = head;

  while(ptr != NULL) {
    size += strlen(ptr->val);
    ptr = ptr->next;
  }
  return size;
}
