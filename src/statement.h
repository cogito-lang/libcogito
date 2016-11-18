#ifndef COGITO_STMT
#define COGITO_STMT

#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "json.h"
#include "linked_list.h"
#include "response.h"

typedef struct statement {
  char *macro;
  cg_node_t *actions;
  cg_node_t *resources;
} statement_t;

void stmt_free(statement_t *stmt);
statement_t* stmt_build(char *macro, cg_node_t *actions, cg_node_t *resources);
JsonNode* stmt_to_json(statement_t *stmt);
char* json_to_iam(JsonNode *json);

#endif
