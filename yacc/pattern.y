%{
#include <stdio.h>

int yylex(void);
void yyerror(const char *s);
%}

%token A B INVALID

%%
input : sequence B '\n'
        {
            printf("Pattern matched\n");
        }
      ;

sequence : A sequence
         | /* empty */
         ;
%%

void yyerror(const char *s)
{
    printf("Pattern not matched\n");
}

int main()
{
    printf("Enter a string (pattern a*b):\n");
    yyparse();

    return 0;
}