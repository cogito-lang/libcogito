#include "statement.h"

// Capitalize the macro string
static void format_macro(char *macro) {
  int idx;
  int macro_len = strlen(macro);

  for (idx = 0; idx < macro_len; idx++) {
    macro[idx] = (idx == 0) ? toupper(macro[idx]) : tolower(macro[idx]);
  }
}

static void capitalize_str(char *str) {
  int idx;
  int len = strlen(str);

  for (idx = 0; idx < len; idx++) {
    str[idx] = toupper(str[idx]);
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

// Add the statement macro to the IAM string buffer
static void add_macro_to_iam(SmartString *smartstring, char *macro) {
  capitalize_str(macro);
  smart_string_append_sprintf(smartstring, "%s\n", macro);
}

// Add a list of statement elements to the IAM string buffer
static void add_elements_to_iam(SmartString *smartstring, node_t *elements) {
  node_t *ptr = elements;
  while (ptr != NULL) {
    smart_string_append_sprintf(smartstring, "  %s", ptr->val);
    if (ptr->next != NULL) {
      smart_string_append(smartstring, ",\n");
    }
    ptr = ptr->next;
  }
}

// Convert a stmt_t to an IAM string
char* stmt_to_iam(statement_t *stmt) {
  SmartString *smartstring = smart_string_new();
  add_macro_to_iam(smartstring, stmt->macro);
  add_elements_to_iam(smartstring, stmt->actions);
  smart_string_append(smartstring, "\nON\n");
  add_elements_to_iam(smartstring, stmt->resources);
  smart_string_append(smartstring, ";");
  char *iam = smartstring->buffer;
  // Free the smartstring struct, but not its buffer which is stored in `iam`
  free(smartstring);
  return iam;
}

// Convert a JSON string or array to a node_t
node_t* json_to_node(JsonNode* json) {
  node_t *node;
  switch (json->tag) {
    case JSON_STRING:
      node = ll_build(json->string_);
      break;
    case JSON_ARRAY:
      node = (node_t *)NULL;
      JsonNode *element;
      json_foreach(element, json) {
        node = ll_update(node, element->string_);
      }
      break;
    default:
      fprintf(stderr, "Unknown JSON type\n");
      exit(EXIT_FAILURE);
  }
  return node;
}

// Convert a JSON string to an IAM string
char* json_to_iam(JsonNode *json) {
  JsonNode *macro = json_find_member(json, "Effect");
  JsonNode *actions = json_find_member(json, "Action");
  JsonNode *resources = json_find_member(json, "Resource");
  statement_t *stmt = stmt_build(macro->string_, json_to_node(actions), json_to_node(resources));
  return stmt_to_iam(stmt);
}
