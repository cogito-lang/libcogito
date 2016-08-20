#ifndef COGITO_STMT
#define COGITO_STMT

#include <stdio.h>
#include <stdlib.h>
#include "json.h"
#include "linked-list.h"
#include "smart_string.h"

typedef struct statement {
  char *macro;
  node_t *actions;
  node_t *resources;
} statement_t;

statement_t* stmt_build(char *macro, node_t *actions, node_t *resources);
JsonNode* stmt_to_json(statement_t *stmt);
char* json_to_iam(JsonNode *json);

#endif
