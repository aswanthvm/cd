%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyerror(const char *s);
int yylex(void);
%}

%union {
    char *str;
}

%token <str> NON_TERMINAL TERMINAL ASSIGN PIPE SEMI
%type <str> symbol

%%
grammar:
    rules
    ;

rules:
    rule
    | rules rule
    ;

rule:
    NON_TERMINAL ASSIGN productions SEMI
    {
        printf("\nValid BNF grammar converted successfully.\n");
    }
    ;

productions:
    production
    | productions PIPE production
    ;

production:
    /* empty */
    | production symbol
    ;

symbol:
    NON_TERMINAL { printf("%s ", $1); }
    | TERMINAL   { printf("%s ", $1); }
    ;
%%

void yyerror(const char *s)
{
    fprintf(stderr, "Syntax Error: Invalid BNF format (%s)\n", s);
}

int main()
{
    printf("Enter BNF production rule (e.g., <E> ::= <E> + <T> | <T> ;):\n");
    yyparse();
    return 0;
}