%{
#include <stdlib.h>
#include "list.h"
#include "statement.h"
#include "parser.h"
%}

white     [ \f\r\n\t]+
allow     (?i:allow)
deny      (?i:deny)
macro     {allow}|{deny}
on        (?i:on)
not       (?i:not)
item      [A-Za-z0-9:/\*\.\-\$\{\}_]+

%option noinput
%option nounput
%option noyywrap

%%

{white}       {}
{macro}       { yylval.str = strdup(yytext); return MACRO; }
{on}          { yylval.str = "ON"; return ON; }
{not}         { yylval.str = "NOT"; return NOT; }
{item}        { yylval.str = strdup(yytext); return ITEM; }

";" return END;
"," return COMMA;
