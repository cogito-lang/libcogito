#include "linked_list.h"

// Append a node to the end of the list
void cg_ll_append(node_t *head, char *val) {
  node_t *tail = cg_ll_build(val);
  node_t *ptr = head;

  while(ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = tail;
}

// Build the first node or append a node to the list
node_t* cg_ll_update(node_t *head, char *val) {
  if (head == NULL) {
    return cg_ll_build(val);
  }
  cg_ll_append(head, val);
  return head;
}

// Build a list node
node_t* cg_ll_build(char *val) {
  node_t *node = (node_t*) malloc(sizeof(node_t));
  node->val = val;
  node->next = NULL;
  return node;
}

// Print out the list starting at the given node
void cg_ll_print(node_t *node) {
  node_t *ptr = node;

  while(ptr != NULL) {
    printf("[%s]\n", ptr->val);
    ptr = ptr->next;
  }
  printf("\n");
}

// The number of nodes in the list
int cg_ll_size(node_t *head) {
  int size = 0;
  node_t *ptr = head;

  while(ptr != NULL) {
    size += 1;
    ptr = ptr->next;
  }
  return size;
}

// The sum of the size of all of the values in the list
size_t cg_ll_val_size_sum(node_t *head) {
  size_t size = 0;
  node_t *ptr = head;

  while(ptr != NULL) {
    size += strlen(ptr->val);
    ptr = ptr->next;
  }
  return size;
}

// Free the memory for the entire list
void cg_ll_free(node_t *head) {
  node_t *previous = head;
  node_t *current = head;

  while(current != NULL) {
    previous = current;
    current = current->next;
    free(previous);
  }
}
