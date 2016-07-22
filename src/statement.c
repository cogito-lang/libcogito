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
static void add_statement_macro(char *macro, json_object *json) {
  format_macro(macro);
  json_object_object_add(json, "Effect", json_object_new_string(macro));
}

// Add elements to a JSON array
static void add_elements_to_array(node_t *head, json_object *array) {
  node_t *ptr = head;
  while (ptr != NULL) {
    json_object_array_add(array, json_object_new_string(ptr->val));
    ptr = ptr->next;
  }
}

// Add a list of statement elements to the JSON object
static void add_statement_elements(node_t *head, json_object *json, char *json_key) {
  json_object *elements = json_object_new_array();
  add_elements_to_array(head, elements);
  json_object_object_add(json, json_key, elements);
}

static void cleanup_json(json_object* json) {
  json_object_object_del(json, "Effect");
  json_object_object_del(json, "Action");
  json_object_object_del(json, "Resource");
}

// Build a statement object from the given macro, actions, and resources
statement_t* stmt_build(char *macro, node_t *actions, node_t *resources) {
  statement_t *stmt = (statement_t*) malloc(sizeof(statement_t));
  stmt->macro = macro;
  stmt->actions = actions;
  stmt->resources = resources;
  return stmt;
}

// Converts a given statement object to a JSON string
char* stmt_to_json(statement_t *stmt) {
  json_object *json = json_object_new_object();
  add_statement_macro(stmt->macro, json);
  add_statement_elements(stmt->actions, json, "Action");
  add_statement_elements(stmt->resources, json, "Resource");

  char *json_string = json_object_to_json_string_ext(json, JSON_C_TO_STRING_SPACED | JSON_C_TO_STRING_PRETTY);
  cleanup_json(json);
  return json_string;
}
