%{
#include <stdio.h>
#include <stdlib.h>
#include "src/linked-list.h"

int yylex();
void yyerror(const char *s);
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
  MACRO list ON list END    {}
;

list:
  ITEM                      { $$ = ll_build($1); }
  | list COMMA ITEM         { $1->next = ll_build($3); $$ = $1; }
;
%%

void yyerror(const char *s) {
  printf("%s\n", s);
}

int main() {
  return yyparse();
}
