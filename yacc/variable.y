%{
#include <stdio.h>
int yylex();
int yyerror();
%}

%token LETTER DIGIT

%%
variable : LETTER rest
         ;

rest : LETTER rest
     | DIGIT rest
     |
     ;
%%

int yyerror()
{
    printf("Invalid variable\n");
    return 0;
}

int main()
{
    printf("Enter a variable: ");

    if (yyparse() == 0)
        printf("Valid variable\n");

    return 0;
}