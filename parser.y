%{
#include <stdio.h>
#include <stdlib.h>
#include "src/linked-list.h"

int yylex();
int yyerror(char *s);
%}

%union {
  char *str;
  node_t *node;
}

%token COMMA END MACRO ON ITEM

%type <str> COMMA END MACRO ON
%type <node> ITEM list

%%
input:
  /* empty */
  | input statement         { printf("hi\n"); }
;

statement:
  MACRO list ON list END    {}
;

list:
  ITEM                      { $$ = ll_build(yylval.str); }
  | list COMMA ITEM         { $1->next = ll_build(yylval.str); $$ = $1; }
;
%%

int yyerror(char *s) {
  printf("%s\n", s);
}

int main() {
  return yyparse();
}
