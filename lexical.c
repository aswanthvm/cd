#include <stdio.h>
#include <string.h>
#include <ctype.h>

int isKeyword(char str[])
{
    char keywords[32][10] = {
        "int", "char", "float", "double", "if", "else",
        "for", "while", "do", "return", "void", "break",
        "continue", "switch", "case", "default", "long",
        "short", "const", "static", "struct", "union",
        "enum", "goto", "sizeof", "auto", "extern",
        "register", "signed", "unsigned", "volatile", "typedef"
    };

    int i;

    for (i = 0; i < 32; i++)
    {
        if (strcmp(str, keywords[i]) == 0)
            return 1;
    }

    return 0;
}

int main()
{
    char ch, buffer[30];
    int i;

    printf("Enter C code :\n");

    while ((ch = getchar()) != EOF)
    {
        if (isspace(ch))
            continue;

        if (isalpha(ch) || ch == '_')
        {
            i = 0;
            buffer[i++] = ch;

            while (isalnum(ch = getchar()) || ch == '_')
                buffer[i++] = ch;

            buffer[i] = '\0';

            if (isKeyword(buffer))
                printf("%-20s Keyword\n", buffer);
            else
                printf("%-20s Identifier\n", buffer);

            ungetc(ch, stdin);
        }

        else if (isdigit(ch))
        {
            i = 0;
            buffer[i++] = ch;

            while (isdigit(ch = getchar()))
                buffer[i++] = ch;

            buffer[i] = '\0';

            printf("%-20s Constant\n", buffer);

            ungetc(ch, stdin);
        }

        else if (strchr("+-*/%=", ch))
            printf("%-20c Operator\n", ch);

        else if (strchr(";,{}()", ch))
            printf("%-20c Special Character\n", ch);
    }

    return 0;
}
