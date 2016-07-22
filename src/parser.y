%{
#include <stdio.h>
#include <stdlib.h>
#include "linked-list.h"
#include "statement.h"

int yylex();
void yyerror(JsonNode *json_arr, const char *str);

typedef struct yy_buffer_state * YY_BUFFER_STATE;
extern int yyparse();
extern YY_BUFFER_STATE yy_scan_string(char *str);
extern void yy_delete_buffer(YY_BUFFER_STATE buffer);
%}

%union {
  char *str;
  node_t *node;
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
  ITEM                      { $$ = ll_build($1); }
  | list COMMA ITEM         { ll_append($1, $3); $$ = $1; }
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

char* cg_parse(char *input) {
  JsonNode *json_arr = json_mkarray();
  YY_BUFFER_STATE buffer = yy_scan_string(input);
  yyparse(json_arr);
  yy_delete_buffer(buffer);
  char *output = json_stringify(json_arr, "  ");
  cleanup_json_arr(json_arr);
  return output;
}
