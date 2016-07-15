%{
#include <stdlib.h>
%}

white     [ \t\n]+
item      [A-Za-z0-9:/\*\.\-\$\{\}_]+
allow     (?i:allow)
deny      (?i:deny)
macro     {allow}|{deny}

%%

{white}       {}
{item}        { printf("item: %s\n", yytext); }
{macro}       { printf("macro: %s\n", yytext); }

"ON" return ON;
";" return END;
"," return COMMA;
