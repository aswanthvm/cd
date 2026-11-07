%{
#include <stdio.h>

int words = 0;
int spaces = 0;
int tabs = 0;
int characters = 0;
%}

%%
[ \t]+ {
    for (int i = 0; yytext[i] != '\0'; i++) {
        if (yytext[i] == ' ')
            spaces++;
        else if (yytext[i] == '\t')
            tabs++;

        characters++;
    }
}

[^\n\t ]+ {
    words++;
    characters += yyleng;
}

\n  { characters++; }
.   { characters++; }
%%

int main()
{
    printf("Enter a string:\n");
    yylex();

    printf("\n--- Results ---\n");
    printf("Words: %d\n", words);
    printf("Spaces: %d\n", spaces);
    printf("Tabs: %d\n", tabs);
    printf("Characters: %d\n", characters);

    return 0;
}

int yywrap()
{
    return 1;
}