#include "statement.h"

// Capitalize the macro string
static void format_macro(char *macro) {
    char *ptr = macro;
    if (*ptr != '\0') *ptr = toupper(*ptr);
            
    while (*(++ptr) != '\0') {
        *ptr = tolower(*ptr);
    }
}

// Add elements to a JSON array
static void add_elements_to_array(cg_node_t *head, JsonNode *array) {
  cg_node_t *ptr = head;
  while (ptr != NULL) {
    json_append_element(array, json_mkstring(ptr->val));
    ptr = ptr->next;
  }
}

// Add a list of statement elements to the JSON object
static void add_statement_elements(cg_node_t *head, JsonNode *json, char *json_key) {
  JsonNode *elements = json_mkarray();
  add_elements_to_array(head, elements);
  json_append_member(json, json_key, elements);
}


// Build a statement object from the given macro, actions, and resources
statement_t* stmt_build(char *macro, cg_node_t *actions, cg_node_t *resources) {
  statement_t *stmt = (statement_t*) malloc(sizeof(statement_t));
  stmt->macro = macro;
  stmt->actions = actions;
  stmt->resources = resources;
  return stmt;
}

// Converts a given statement object to a JsonNode object
JsonNode* stmt_to_json(statement_t *stmt) {
  JsonNode *json = json_mkobject();

  format_macro(stmt->macro);
  json_append_member(json, "Effect", json_mkstring(stmt->macro));

  add_statement_elements(stmt->actions, json, "Action");
  add_statement_elements(stmt->resources, json, "Resource");
  return json;
}

// Add the statement macro to the IAM string buffer
static void add_macro_to_iam(cg_buf_t *buffer, char *macro) {
  int idx;
  int len = strlen(macro);

  for (idx = 0; idx < len; idx++) {
    macro[idx] = toupper(macro[idx]);
  }

  cg_buf_append(buffer, macro);
  cg_buf_append(buffer, "\n");
}

// Add a list of statement elements to the IAM string buffer
static void add_elements_to_iam(cg_buf_t *buffer, cg_node_t *elements) {
  cg_node_t *ptr = elements;
  while (ptr != NULL) {
    cg_buf_append(buffer, "  ");
    cg_buf_append(buffer, ptr->val);

    if (ptr->next != NULL) {
      cg_buf_append(buffer, ",\n");
    }
    ptr = ptr->next;
  }
}

// Free a statement_t object
void stmt_free(statement_t *stmt) {
  cg_ll_free(stmt->actions);
  cg_ll_free(stmt->resources);
  free(stmt);
}

// Convert a stmt_t to an IAM string
char* stmt_to_iam(statement_t *stmt) {
  cg_buf_t *buffer = cg_buf_build();

  add_macro_to_iam(buffer, stmt->macro);
  add_elements_to_iam(buffer, stmt->actions);

  cg_buf_append(buffer, "\nON\n");
  add_elements_to_iam(buffer, stmt->resources);
  cg_buf_append(buffer, ";");

  char *iam = buffer->content;
  free(buffer);
  stmt_free(stmt);

  return iam;
}

// Convert a JSON string or array to a cg_node_t
cg_node_t* json_to_node(JsonNode* json) {
  cg_node_t *node;
  switch (json->tag) {
    case JSON_STRING:
      node = cg_ll_build(json->string_);
      break;
    case JSON_ARRAY:
      node = (cg_node_t *)NULL;
      JsonNode *element;
      json_foreach(element, json) {
        node = cg_ll_update(node, element->string_);
      }
      break;
    default:
      return (cg_node_t *)NULL;
  }
  return node;
}

// Append a JSON policy to a buffer
int cg_append_json_policy(cg_buf_t *buffer, JsonNode *json) {
  JsonNode *macro = json_find_member(json, "Effect");
  cg_node_t *actions, *resources;

  if ((actions = json_to_node(json_find_member(json, "Action"))) == NULL) {
    return CG_ERR_INVALID_ACTION;
  }
  if ((resources = json_to_node(json_find_member(json, "Resource"))) == NULL) {
    return CG_ERR_INVALID_RESOURCE;
  }

  char *iam = stmt_to_iam(stmt_build(macro->string_, actions, resources));
  int response_code = cg_buf_append(buffer, iam);
  free(iam);

  return response_code;
}
