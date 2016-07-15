%{
#include <stdio.h>
#include <stdlib.h>
#include "src/linked-list.h"

int yylex();
void yyerror(const char *str);
%}

%union {
  char *str;
  node_t *node;
}

%token COMMA END MACRO ON ITEM

%type <str> COMMA END MACRO ON ITEM
%type <node> list

%%
input:
  /* empty */
  | input statement         { printf("hi\n"); }
;

statement:
  MACRO list ON list END    { ll_print($2); ll_print($4); }
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
