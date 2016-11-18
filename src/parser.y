%{
#include <stdio.h>
#include <stdlib.h>
#include "buffer.h"
#include "linked_list.h"
#include "statement.h"

const int CG_ERR_INVALID_IAM = 1;
const int CG_ERR_INVALID_JSON = 2;
const int CG_ERR_JSON_NOT_ARRAY = 3;

int yylex();
void yyerror(JsonNode *json_arr, const char *str);

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
%}

%union {
  char *str;
  cg_node_t *node;
  statement_t *stmt;
}

%parse-param { JsonNode *json_arr }

%token COMMA END MACRO ON ITEM

%type <str> COMMA END MACRO ON ITEM
%type <node> list
%type <stmt> statement

%%
input:
  /* empty */
  | input statement { json_append_element(json_arr, stmt_to_json($2)); }
;

statement:
  MACRO list ON list END    { $$ = stmt_build($1, $2, $4); }
;

list:
  ITEM                      { $$ = cg_ll_build($1); }
  | list COMMA ITEM         { cg_ll_append($1, $3); $$ = $1; }
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
    if (!(response_code = cg_append_json_policy(buffer, policy))) {
      return response_code;
    }
    if (policy->next != NULL) {
      cg_buf_append(buffer, "\n\n");
    }
  }

  cleanup_json_arr(policies);
  return 0;
}
