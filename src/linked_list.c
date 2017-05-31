#include "linked_list.h"

// Append a node to the end of the list
void cg_ll_append(cg_node_t *head, char *val) {
  cg_node_t *tail = cg_ll_build(val);
  cg_node_t *ptr = head;

  while(ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = tail;
}

// Build the first node or append a node to the list
cg_node_t* cg_ll_update(cg_node_t *head, char *val) {
  if (head == NULL) {
    return cg_ll_build(val);
  }
  cg_ll_append(head, val);
  return head;
}

// Build a list node
cg_node_t* cg_ll_build(char *val) {
  cg_node_t *node = (cg_node_t*) malloc(sizeof(cg_node_t));
  node->val = val;
  node->next = NULL;
  return node;
}

// Print out the list starting at the given node
void cg_ll_print(cg_node_t *node) {
  cg_node_t *ptr;

  cg_ll_foreach(node, ptr) {
    printf("[%s]\n", ptr->val);
  }
  printf("\n");
}

// The sum of the size of all of the values in the list
size_t cg_ll_val_size_sum(cg_node_t *head) {
  size_t size = 0;
  cg_node_t *ptr;

  cg_ll_foreach(head, ptr) {
    size += strlen(ptr->val);
  }
  return size;
}

// Free the memory for the entire list
void cg_ll_free(cg_node_t *head) {
  cg_node_t *previous = head;
  cg_node_t *current = head;

  while(current != NULL) {
    previous = current;
    current = current->next;
    free(previous);
  }
}
