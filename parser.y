%{
#include <stdio.h>
#include <stdlib.h>
#define YYSTYPE char*
%}

%token COMMA END ITEM MACRO ON

%%
input:
  /* empty */
  | input line
;

line:
  END
  | statement END           { printf("%s\n", $1); }
;

statement:
  MACRO list ON list END    {}
;

list:
  ITEM                      {}
  | ITEM COMMA list         {}
;
%%

int yyerror(char *s) {
  printf("%s\n", s);
}

int main() {
  return yyparse();
}
