#ifndef COGITO_STMT
#define COGITO_STMT

#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"

typedef struct statement {
  char *macro;
  node_t *actions;
  node_t *resources;
} statement_t;

#endif
