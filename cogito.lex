%{
#include <stdlib.h>
#include "parser.tab.h"
#define YYSTYPE char*
%}

white     [ \r\n\t]+
allow     (?i:allow)
deny      (?i:deny)
macro     {allow}|{deny}
on        (?i:on)
item      [A-Za-z0-9:/\*\.\-\$\{\}_]+

%%

{white}       {}
{macro}       { printf("macro: %s\n", yytext); return MACRO; }
{on}          { printf("on: %s\n", yytext); return ON; }
{item}        { printf("item: %s\n", yytext); return ITEM; }

";" return END;
"," return COMMA;
