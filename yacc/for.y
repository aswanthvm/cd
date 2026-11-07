%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

%token FOR ID NUM RELOP INC DEC

%%
stmt : FOR '(' init ';' cond ';' incr ')' body
       {
           printf("Valid for loop syntax\n");
       }
     ;

init : ID '=' expr
     | /* empty */
     ;

cond : expr RELOP expr
     | /* empty */
     ;

incr : ID INC
     | ID DEC
     | INC ID
     | DEC ID
     | ID '=' expr
     | /* empty */
     ;

expr : ID
     | NUM
     | expr '+' expr
     | expr '-' expr
     ;

body : '{' stmts '}'
     | ID '=' expr ';'
     | ';'
     ;

stmts : stmts ID '=' expr ';'
      | /* empty */
      ;
%%

void yyerror(const char *s)
{
    printf("Invalid for loop syntax\n");
}

int main()
{
    printf("Enter a for loop statement:\n");
    yyparse();
    return 0;
}