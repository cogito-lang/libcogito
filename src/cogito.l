%{
#include <stdlib.h>
#include "linked-list.h"
#include "statement.h"
#include "parser.h"
%}

white     [ \f\r\n\t]+
allow     (?i:allow)
deny      (?i:deny)
macro     {allow}|{deny}
on        (?i:on)
item      [A-Za-z0-9:/\*\.\-\$\{\}_]+

%option noinput
%option nounput

%%

{white}       {}
{macro}       { yylval.str = strdup(yytext); return MACRO; }
{on}          { yylval.str = "ON"; return ON; }
{item}        { yylval.str = strdup(yytext); return ITEM; }

";" return END;
"," return COMMA;
