%{
#include <stdio.h>
#include <stdlib.h>
#include "src/linked-list.h"
#include "src/statement.h"

int yylex();
void yyerror(char *output, const char *str);

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

%parse-param { char *output }

%token COMMA END MACRO ON ITEM

%type <str> COMMA END MACRO ON ITEM
%type <node> list
%type <stmt> statement

%%
input:
  /* empty */
  | input statement         { strcpy(output, stmt_to_json($2)); }
;

statement:
  MACRO list ON list END    { $$ = stmt_build($1, $2, $4); }
;

list:
  ITEM                      { $$ = ll_build($1); }
  | list COMMA ITEM         { ll_append($1, $3); $$ = $1; }
;
%%

void yyerror(char *output, const char *str) {
  printf("%s\n", str);
}

void cg_parse(char *input, char *output) {
  YY_BUFFER_STATE buffer = yy_scan_string(input);
  yyparse(output);
  yy_delete_buffer(buffer);
}
