#ifndef COGITO_LINKED_LIST
#define COGITO_LINKED_LIST

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * A struct representing a node in the list. Contains a pointer to a string
 * representing the AWS identifier and a pointer to the next node.
 */
typedef struct cg_node {
  char *val;
  struct cg_node *next;
} cg_node_t;

/**
 * A struct representing the list. Contains a pointer to the head node of the
 * list and an integer flag representing whether or not this list is negated.
 */
typedef struct {
  struct cg_node *head;
  int negated;
} cg_list_t;

/**
 * A macro for looping through the nodes in the list.
 */
#define cg_ll_foreach(list, ptr) \
  for ((ptr) = list->head; (ptr) != NULL; (ptr) = (ptr)->next)

/**
 * Append a node to the end of the list.
 */
void cg_ll_append(cg_list_t *list, char *val);

/**
 * Build the first node or append a node to the list.
 */
cg_list_t* cg_ll_update(cg_list_t *list, char *val);

/**
 * Build the first list node and return the list.
 */
cg_list_t* cg_ll_build(char *val);

/**
 * The sum of the size of all of the values in the list.
 */
size_t cg_ll_val_size_sum(cg_list_t *list);

/**
 * Free the memory for the entire list.
 */
void cg_ll_free(cg_list_t *list);

#endif
