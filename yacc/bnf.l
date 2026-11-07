%{
#include "y.tab.h"
#include <string.h>
%}

%%
"::="                       { return ASSIGN; }
"|"                         { return PIPE; }
";"                         { return SEMI; }

"<"[a-zA-Z_][a-zA-Z0-9_]*">" {
                                yylval.str = strdup(yytext);
                                return NON_TERMINAL;
                            }

[a-zA-Z0-9_]+                {
                                yylval.str = strdup(yytext);
                                return TERMINAL;
                            }

\'[^\']\'                   {
                                yylval.str = strdup(yytext);
                                return TERMINAL;
                            }

[ \t\n]                     ;
.                           { return yytext[0]; }
%%

int yywrap()
{
    return 1;
}