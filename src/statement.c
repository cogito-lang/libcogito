#include "statement.h"

statement_t* stmt_build(char *macro, node_t *actions, node_t *resources) {
  statement_t *stmt = (statement_t*) malloc(sizeof(statement_t));
  stmt->macro = macro;
  stmt->actions = actions;
  stmt->resources = resources;
  return stmt;
}

void stmt_to_json(statement_t *stmt) {
  printf("{\n  \"Effect\": \"%s\",\n  \"Action\": %s,\n  \"Resource\":  %s\n}\n", stmt->macro, "alpha", "beta");
}
