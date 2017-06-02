#ifndef COGITO_STATEMENT
#define COGITO_STATEMENT

#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "errors.h"
#include "json.h"
#include "linked_list.h"

/**
 * A struct representing a cogito statement. Contains a string which is either
 * ALLOW or DENY. Also contains a pointer to both a list of actions and a list
 * of resources.
 */
typedef struct {
  char *macro;
  cg_list_t *actions;
  cg_list_t *resources;
} statement_t;

void stmt_free(statement_t *stmt);
statement_t* stmt_build(char *macro, cg_list_t *actions, cg_list_t *resources);
JsonNode* stmt_to_json(statement_t *stmt);
int cg_append_json_policy(cg_buf_t *buffer, JsonNode *json);

#endif
