#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char input[100];
int pos = 0, tempCount = 0, error = 0;

// Skip spaces in input
void skipSpaces()
{
    while (isspace(input[pos]))
        pos++;
}

// Copy a string
char *copy(char s[])
{
    char *p = malloc(strlen(s) + 1);
    strcpy(p, s);
    return p;
}

// Generate temporary variable
char *newTemp()
{
    char t[10];
    sprintf(t, "t%d", ++tempCount);
    return copy(t);
}

// Function declarations
char *expression();
char *term();
char *factor();

// Handle variables, numbers and brackets
char *factor()
{
    char token[20];
    int i = 0;

    skipSpaces();

    if (input[pos] == '(')
    {
        pos++;
        char *result = expression();

        skipSpaces();

        if (input[pos] == ')')
            pos++;
        else
            error = 1;

        return result;
    }

    if (isalnum(input[pos]) || input[pos] == '_')
    {
        while (isalnum(input[pos]) || input[pos] == '_')
            token[i++] = input[pos++];

        token[i] = '\0';
        return copy(token);
    }

    error = 1;
    return copy("");
}

// Handle multiplication and division
char *term()
{
    char *left = factor();

    while (!error)
    {
        skipSpaces();
        char op = input[pos];

        if (op != '*' && op != '/')
            break;

        pos++;

        char *right = factor();
        char *t = newTemp();

        printf("%s = %s %c %s\n", t, left, op, right);

        left = t;
    }

    return left;
}

// Handle addition and subtraction
char *expression()
{
    char *left = term();

    while (!error)
    {
        skipSpaces();
        char op = input[pos];

        if (op != '+' && op != '-')
            break;

        pos++;

        char *right = term();
        char *t = newTemp();

        printf("%s = %s %c %s\n", t, left, op, right);

        left = t;
    }

    return left;
}

// Main function
int main()
{
    char result[20];
    int i = 0;

    printf("Enter an expression (e.g. a=b+c*d):\n");
    fgets(input, sizeof(input), stdin);

    skipSpaces();

    // Read the result variable
    while (isalnum(input[pos]) || input[pos] == '_')
        result[i++] = input[pos++];

    result[i] = '\0';

    skipSpaces();

    if (i == 0 || input[pos] != '=')
    {
        printf("Invalid expression\n");
        return 0;
    }

    pos++;

    // Generate three address code
    char *value = expression();

    skipSpaces();

    if (error || input[pos] != '\0')
        printf("Invalid expression\n");
    else
        printf("%s = %s\n", result, value);

    return 0;
}