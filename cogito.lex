%{
#include <stdlib.h>
%}

white     [ \t\n]+
allow     (?i:allow)
deny      (?i:deny)
macro     {allow}|{deny}
item      [A-Za-z0-9:/\*\.\-\$\{\}_]+

%%

{white}       {}
{macro}       { printf("macro: %s\n", yytext); }
{item}        { printf("item: %s\n", yytext); }

"ON" return ON;
";" return END;
"," return COMMA;
