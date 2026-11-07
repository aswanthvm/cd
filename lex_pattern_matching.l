%{
#include <stdio.h>
%}

%%
a*b\n       { printf("Valid string\n"); }
.*\n        { printf("Invalid string\n"); }
%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a string: ");
    yylex();
    return 0;
}