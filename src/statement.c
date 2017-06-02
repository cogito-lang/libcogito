#include "statement.h"

// Capitalize the macro string
static void format_macro(char *macro) {
  char *ptr = macro;
  if (*ptr != '\0') {
    *ptr = toupper(*ptr);
  }

  while (*(++ptr) != '\0') {
    *ptr = tolower(*ptr);
  }
}

// Add elements to a JSON array
static void add_elements_to_array(cg_list_t *list, JsonNode *array) {
  cg_node_t *ptr = list->head;
  while (ptr != NULL) {
    json_append_element(array, json_mkstring(ptr->value));
    ptr = ptr->next;
  }
}

// Add a list of statement elements to the JSON object
static void add_statement_elements(cg_list_t *list, JsonNode *json, char *json_key) {
  JsonNode *elements = json_mkarray();
  add_elements_to_array(list, elements);
  json_append_member(json, json_key, elements);
}

// Add the statement macro to the IAM string buffer
static void add_macro_to_iam(cg_buf_t *buffer, char *macro) {
  int idx;
  int len = strlen(macro);

  for (idx = 0; idx < len; idx++) {
    macro[idx] = toupper(macro[idx]);
  }

  cg_buf_append(buffer, macro);
}

// Add a list of statement elements to the IAM string buffer
static void add_elements_to_iam(cg_buf_t *buffer, cg_list_t *elements) {
  cg_node_t *ptr = elements->head;
  while (ptr != NULL) {
    cg_buf_append(buffer, "  ");
    cg_buf_append(buffer, ptr->value);

    if (ptr->next != NULL) {
      cg_buf_append(buffer, ",\n");
    }
    ptr = ptr->next;
  }
}

// Convert a stmt_t to an IAM string
static char* stmt_to_iam(cg_statement_t *stmt) {
  cg_buf_t *buffer = cg_buf_build();

  add_macro_to_iam(buffer, stmt->macro);
  cg_buf_append(buffer, stmt->actions->negated ? " NOT\n" : "\n");
  add_elements_to_iam(buffer, stmt->actions);

  cg_buf_append(buffer, "\nON");
  cg_buf_append(buffer, stmt->resources->negated ? " NOT\n" : "\n");
  add_elements_to_iam(buffer, stmt->resources);
  cg_buf_append(buffer, ";");

  char *iam = buffer->content;
  free(buffer);
  cg_stmt_free(stmt);

  return iam;
}

// Convert a JSON string or array to a cg_list_t
static cg_list_t* json_to_node(JsonNode* json) {
  cg_list_t *list;

  switch (json->tag) {
    case JSON_STRING:
      list = cg_ll_build(json->string_);
      break;
    case JSON_ARRAY:
      list = (cg_list_t *) NULL;
      JsonNode *element;
      json_foreach(element, json) {
        list = cg_ll_update(list, element->string_);
      }
      break;
    default:
      return (cg_list_t *) NULL;
  }
  return list;
}

cg_statement_t* cg_stmt_build(char *macro, cg_list_t *actions, cg_list_t *resources) {
  cg_statement_t *stmt = (cg_statement_t*) malloc(sizeof(cg_statement_t));
  stmt->macro = macro;
  stmt->actions = actions;
  stmt->resources = resources;
  return stmt;
}

void cg_stmt_free(cg_statement_t *stmt) {
  cg_ll_free(stmt->actions);
  cg_ll_free(stmt->resources);
  free(stmt);
}

JsonNode* cg_stmt_to_json(cg_statement_t *stmt) {
  JsonNode *json = json_mkobject();

  format_macro(stmt->macro);
  json_append_member(json, "Effect", json_mkstring(stmt->macro));

  add_statement_elements(stmt->actions, json,
    stmt->actions->negated ? "NotAction" : "Action");

  add_statement_elements(stmt->resources, json,
    stmt->resources->negated ? "NotResource" : "Resource");

  return json;
}

int cg_append_json_policy(cg_buf_t *buffer, JsonNode *json) {
  JsonNode *macro = json_find_member(json, "Effect");
  JsonNode *node;
  cg_list_t *actions, *resources;

  if ((node = json_find_member(json, "Action")) != NULL) {
    if ((actions = json_to_node(node)) == NULL) {
      return CG_ERR_INVALID_ACTION;
    }
  } else if ((node = json_find_member(json, "NotAction")) != NULL) {
    if ((actions = json_to_node(node)) == NULL) {
      return CG_ERR_INVALID_ACTION;
    }
    cg_ll_negate(actions);
  } else {
    return CG_ERR_INVALID_ACTION;
  }

  if ((node = json_find_member(json, "Resource")) != NULL) {
    if ((resources = json_to_node(node)) == NULL) {
      return CG_ERR_INVALID_ACTION;
    }
  } else if ((node = json_find_member(json, "NotResource")) != NULL) {
    if ((resources = json_to_node(node)) == NULL) {
      return CG_ERR_INVALID_ACTION;
    }
    cg_ll_negate(resources);
  } else {
    return CG_ERR_INVALID_ACTION;
  }

  char *iam = stmt_to_iam(cg_stmt_build(macro->string_, actions, resources));
  int response_code = cg_buf_append(buffer, iam);
  free(iam);

  return response_code;
}
