%{
#include <stdlib.h>
#include "src/linked-list.h"
#include "src/statement.h"
#include "parser.tab.h"
%}

white     [ \f\r\n\t]+
allow     (?i:allow)
deny      (?i:deny)
macro     {allow}|{deny}
on        (?i:on)
item      [A-Za-z0-9:/\*\.\-\$\{\}_]+

%%

{white}       {}
{macro}       { yylval.str = strdup(yytext); return MACRO; }
{on}          { yylval.str = "ON"; return ON; }
{item}        { yylval.str = strdup(yytext); return ITEM; }

";" return END;
"," return COMMA;
