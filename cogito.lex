%{
#include <stdlib.h>
#include "parser.tab.h"
#define YYSTYPE char*
%}

white     [ \t\n]+
allow     (?i:allow)
deny      (?i:deny)
macro     {allow}|{deny}
item      [A-Za-z0-9:/\*\.\-\$\{\}_]+

%%

{white}       {}
{macro}       { printf("macro: %s\n", yytext); return MACRO; }
{item}        { printf("item: %s\n", yytext); return ITEM; }

"ON" return ON;
";" return END;
"," return COMMA;
