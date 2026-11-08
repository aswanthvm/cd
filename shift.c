#include <stdio.h>
#include <string.h>

char stack[100];
int top = -1;

void reduce()
{
    if (top >= 0 && stack[top] == 'i')
    {
        stack[top] = 'E';
        return;
    }

    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '+' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        return;
    }

    if (top >= 2 &&
        stack[top - 2] == 'E' &&
        stack[top - 1] == '*' &&
        stack[top] == 'E')
    {
        top -= 2;
        stack[top] = 'E';
        return;
    }

    if (top >= 2 &&
        stack[top - 2] == '(' &&
        stack[top - 1] == 'E' &&
        stack[top] == ')')
    {
        top -= 2;
        stack[top] = 'E';
    }
}

int main()
{
    char input[100];
    int i;

    printf("Enter expression using i: ");
    scanf("%s", input);

    for (i = 0; input[i] != '\0'; i++)
    {
        stack[++top] = input[i];

        printf("Shift: %c\n", input[i]);

        reduce();

        printf("Stack: ");

        for (int j = 0; j <= top; j++)
            printf("%c", stack[j]);

        printf("\n");
    }

    while (top > 0)
        reduce();

    if (top == 0 && stack[0] == 'E')
        printf("Accepted\n");
    else
        printf("Rejected\n");

    return 0;
}
