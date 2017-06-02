%{
#include <stdio.h>
#include <stdlib.h>

#include "buffer.h"
#include "errors.h"
#include "list.h"
#include "statement.h"

int yylex();
void yyerror(JsonNode *json_arr, const char *str);

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);

static void cleanup_statement_allocs(cg_statement_t *stmt);
%}

%union {
  char *str;
  cg_list_t *list;
  cg_statement_t *stmt;
}

%parse-param { JsonNode *json_arr }

%token COMMA END MACRO ON NOT ITEM

%type <str> COMMA END MACRO ON NOT ITEM
%type <list> list list_content
%type <stmt> statement

%destructor { free($$); } MACRO ITEM
%destructor { 
  cg_node_t *ptr;
  cg_ll_foreach($$, ptr) {
    free(ptr->value);
  }
  cg_list_free($$);
} list
%destructor { 
  cleanup_statement_allocs($$);
  cg_stmt_free($$); 
} statement

%%
input:
  /* empty */
  | input statement { 
    json_append_element(json_arr, cg_stmt_to_json($2)); 
    cleanup_statement_allocs($2);
    cg_stmt_free($2);
}
;

statement:
  MACRO list ON list END    { $$ = cg_stmt_build($1, $2, $4); }
;

list:
  list_content              { $$ = $1; }
  | NOT list_content        { cg_list_negate($2); $$ = $2; }
;

list_content:
  ITEM                      { $$ = cg_list_build($1); }
  | list_content COMMA ITEM { cg_list_append($1, $3); $$ = $1; }
;
%%

void yyerror(JsonNode *json_arr, const char *str) {
  printf("%s\n", str);
}

static void cleanup_json_arr(JsonNode *json_arr) {
  JsonNode *json_obj = json_arr->children.head;
  while (json_obj != NULL) {
    json_delete(json_obj);
    json_obj = json_obj->next;
  }
  json_delete(json_arr);
}

static void cleanup_statement_allocs(cg_statement_t *stmt) {
  cg_node_t *ptr;

  cg_ll_foreach(stmt->actions, ptr) {
    free(ptr->value);
  }

  cg_ll_foreach(stmt->resources, ptr) {
    free(ptr->value);
  }
}

int cg_to_json(cg_buf_t *buffer, char *input) {
  JsonNode *json_arr = json_mkarray();
  YY_BUFFER_STATE yy_buffer = yy_scan_string(input);
  yyparse(json_arr);
  yy_delete_buffer(yy_buffer);

  char *output = json_stringify(json_arr, "  ");
  cleanup_json_arr(json_arr);
  int response_code = cg_buf_append(buffer, output);
  free(output);

  return response_code ? CG_ERR_INVALID_IAM : 0;
}

int cg_to_iam(cg_buf_t *buffer, char *input) {
  JsonNode *policies = json_decode(input);

  if (policies == NULL) {
    return CG_ERR_INVALID_JSON;
  } else if (policies->tag != JSON_ARRAY) {
    return CG_ERR_JSON_NOT_ARRAY;
  }

  JsonNode *policy;
  int response_code;

  json_foreach(policy, policies) {
    if ((response_code = cg_append_json_policy(buffer, policy)) != 0) {
      return response_code;
    }
    if (policy->next != NULL) {
      cg_buf_append(buffer, "\n\n");
    }
  }

  cleanup_json_arr(policies);
  return 0;
}
