%{
#include <stdio.h>
#include <stdlib.h>
#include "src/linked-list.h"
#include "src/statement.h"

int yylex();
void yyerror(const char *str);
%}

%union {
  char *str;
  node_t *node;
  statement_t *stmt;
}

%token COMMA END MACRO ON ITEM

%type <str> COMMA END MACRO ON ITEM
%type <node> list
%type <stmt> statement

%%
input:
  /* empty */
  | input statement         { stmt_to_json($2); }
;

statement:
  MACRO list ON list END    { $$ = stmt_build($1, $2, $4); }
;

list:
  ITEM                      { $$ = ll_build($1); }
  | list COMMA ITEM         { ll_append($1, $3); $$ = $1; }
;
%%

void yyerror(const char *str) {
  printf("%s\n", str);
}

int main() {
  return yyparse();
}
