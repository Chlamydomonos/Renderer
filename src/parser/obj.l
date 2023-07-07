%option noyywrap

%{
#include "parser.h"

#include <stdio.h>
#include <stdlib.h>
%}

%%

v { return VERTEX; }
f { return FACE; }
vt { return TEXTURE; }
vn { return NORMAL; }

v[a-mo-su-z].*$ { /* ignore */ }
[a-eg-uw-z].*$ { /* ignore */ }

[0-9]+ { yylval.id = atoi(yytext); return ID; }
"-"?[0-9]+"."[0-9]+(e("+"|"-")?[0-9]+)? { yylval.value = atof(yytext); return NUMBER; }

"/" { return SLASH; }

\n { /* ignore */ }
. { /* ignore */ }

%%