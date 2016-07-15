#include "statement.h"

statement_t* stmt_build(char *macro, node_t *actions, node_t *resources) {
  statement_t *stmt = (statement_t*) malloc(sizeof(statement_t));
  stmt->macro = macro;
  stmt->actions = actions;
  stmt->resources = resources;
  return stmt;
}

static void ll_to_str(node_t *head, char *converted, int size) {
  int location = 1;
  converted[0] = '[';

  node_t *ptr = head;
  while(ptr != NULL) {
    converted[location++] = '"';

    strncpy(converted + location, ptr->val, strlen(ptr->val));
    location += strlen(ptr->val);

    if (ptr->next == NULL) {
      converted[location] = '"';
    } else {
      strncpy(converted + location, "\", ", 3);
      location += 3;
    }

    ptr = ptr->next;
  }

  converted[size - 2] = ']';
  converted[size - 1] = '\0';
}

static int converted_size(node_t *head) {
  return 4 * ll_size(head) + ll_val_size_sum(head) + 1;
}

static void format_macro(char *macro) {
  int idx;
  int macro_len = strlen(macro);

  for (idx = 0; idx < macro_len; idx++) {
    macro[idx] = (idx == 0) ? toupper(macro[idx]) : tolower(macro[idx]);
  }
}

void stmt_to_json(statement_t *stmt) {
  int actions_size = converted_size(stmt->actions);
  int resources_size = converted_size(stmt->resources);

  char actions[actions_size];
  char resources[resources_size];

  ll_to_str(stmt->actions, actions, actions_size);
  ll_to_str(stmt->resources, resources, resources_size);
  format_macro(stmt->macro);

  printf("{\n  \"Effect\": \"%s\",\n  \"Action\": %s,\n  \"Resource\": %s\n}\n", stmt->macro, actions, resources);
}
