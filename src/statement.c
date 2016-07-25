#include "statement.h"

// Capitalize the macro string
static void format_macro(char *macro) {
  int idx;
  int macro_len = strlen(macro);

  for (idx = 0; idx < macro_len; idx++) {
    macro[idx] = (idx == 0) ? toupper(macro[idx]) : tolower(macro[idx]);
  }
}

// Add the statement macro to the JSON object
static void add_statement_macro(char *macro, JsonNode *json) {
  format_macro(macro);
  json_append_member(json, "Effect", json_mkstring(macro));
}

// Add elements to a JSON array
static void add_elements_to_array(node_t *head, JsonNode *array) {
  node_t *ptr = head;
  while (ptr != NULL) {
    json_append_element(array, json_mkstring(ptr->val));
    ptr = ptr->next;
  }
}

// Add a list of statement elements to the JSON object
static void add_statement_elements(node_t *head, JsonNode *json, char *json_key) {
  JsonNode *elements = json_mkarray();
  add_elements_to_array(head, elements);
  json_append_member(json, json_key, elements);
}


// Build a statement object from the given macro, actions, and resources
statement_t* stmt_build(char *macro, node_t *actions, node_t *resources) {
  statement_t *stmt = (statement_t*) malloc(sizeof(statement_t));
  stmt->macro = macro;
  stmt->actions = actions;
  stmt->resources = resources;
  return stmt;
}

// Converts a given statement object to a JsonNode object
JsonNode* stmt_to_json(statement_t *stmt) {
  JsonNode *json = json_mkobject();
  add_statement_macro(stmt->macro, json);
  add_statement_elements(stmt->actions, json, "Action");
  add_statement_elements(stmt->resources, json, "Resource");
  return json;
}
