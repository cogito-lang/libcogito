#include "linked_list.h"

static cg_node_t* cg_ll_build_node(char *value) {
  cg_node_t *node = (cg_node_t *) malloc(sizeof(cg_node_t));
  node->value = value;
  node->next = NULL;
  return node;
}

void cg_ll_append(cg_list_t *list, char *value) {
  cg_node_t *tail = cg_ll_build_node(value);
  cg_node_t *ptr = list->head;

  while(ptr->next != NULL) {
    ptr = ptr->next;
  }
  ptr->next = tail;
}

cg_list_t* cg_ll_update(cg_list_t *list, char *value) {
  if (list == NULL) {
    return cg_ll_build(value);
  }
  cg_ll_append(list, value);
  return list;
}

cg_list_t* cg_ll_build(char *value) {
  cg_list_t *list = (cg_list_t *) malloc(sizeof(cg_list_t));
  list->negated = 0;
  list->head = cg_ll_build_node(value);
  return list;
}

size_t cg_ll_value_size_sum(cg_list_t *list) {
  size_t size = 0;
  cg_node_t *ptr;

  cg_ll_foreach(list, ptr) {
    size += strlen(ptr->value);
  }
  return size;
}

void cg_ll_negate(cg_list_t *list) {
  list->negated = 1 - list->negated;
}

void cg_ll_free(cg_list_t *list) {
  cg_node_t *previous = list->head;
  cg_node_t *current = list->head;

  while(current != NULL) {
    previous = current;
    current = current->next;
    free(previous);
  }

  free(list);
}
