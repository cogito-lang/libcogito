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
} cg_statement_t;

/**
 * Build a statement object from the given macro, actions, and resources.
 * @param macro The text saying whether this is an ALLOW or DENY command
 * @param actions The list of actions from AWS
 * @param resource The list of resources from AWS
 * @return The newly allocated and initialized statement
 */
cg_statement_t* cg_stmt_build(char *macro, cg_list_t *actions, cg_list_t *resources);

/**
 * Free an allocated statement
 * @param stmt The statement to free
 */
void cg_stmt_free(cg_statement_t *stmt);

/**
 * Converts a given statement object to a JsonNode object.
 * @param stmt The statement struct to convert to JSON
 * @return A JSON node representing the statement
 */
JsonNode* cg_stmt_to_json(cg_statement_t *stmt);

/**
 * Append a JSON policy to a buffer.
 * @param buffer The buffer on which to append the converted IAM syntax
 * @param json The JSON node that should be converted and added to the buffer
 * @return An integer describing success (0 for success, error code for failure)
 */
int cg_append_json_policy(cg_buf_t *buffer, JsonNode *json);

#endif
