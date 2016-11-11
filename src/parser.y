%{
#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "response.h"
#include "statement.h"
#include "smart_string.h"

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

response_t* cg_to_json(char *input_iam) {
  JsonNode *json_arr = json_mkarray();
  YY_BUFFER_STATE buffer = yy_scan_string(input_iam);
  yyparse(json_arr);
  yy_delete_buffer(buffer);
  char *output = json_stringify(json_arr, "  ");
  cleanup_json_arr(json_arr);
  return cg_response_build(0, output);
}

response_t* cg_to_iam(char *input_json) {
  JsonNode *policies = json_decode(input_json);
  // Handle error cases
  if (policies == NULL) {
    return cg_response_build(1, "Invalid JSON");
  } else if (policies->tag != JSON_ARRAY) {
    return cg_response_build(1, "JSON object must be an array");
  }

  JsonNode *policy;
  response_t *converted;
  SmartString *smartstring = smart_string_new();

  json_foreach(policy, policies) {
    converted = json_to_iam(policy);
    if (converted->status != 0) {
      return cg_response_build(1, converted->message);
    }

    smart_string_append(smartstring, converted->message);
    if (policy->next != NULL) {
      smart_string_append(smartstring, "\n\n");
    }
  }

  char *result = smartstring->buffer;
  // Free the smartstring struct, but not its buffer which is stored in `result`
  free(smartstring);
  return cg_response_build(0, result);
}
