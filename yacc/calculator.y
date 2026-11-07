%{
#include <stdio.h>
#include <stdlib.h>
int yylex();
int yyerror();
%}

%token NUMBER

%left '+' '-'
%left '*' '/'

%%
input:
    expr '\n' { printf("Result = %d", $1); }
    ;

expr:
      NUMBER          { $$ = $1; }
    | expr '+' expr   { $$ = $1 + $3; }
    | expr '-' expr   { $$ = $1 - $3; }
    | expr '*' expr   { $$ = $1 * $3; }
    | expr '/' expr   { $$ = $1 / $3; }
    | '(' expr ')'    { $$ = $2; }
    ;
%%

int yywrap()
{
    return 1;
}

int yyerror()
{
    printf("ERROR\n");
    return 1;
}

int main()
{
    printf("Enter expr: ");
    yyparse();
}