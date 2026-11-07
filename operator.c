#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#define MAX 100

int values[MAX], vtop = -1;
char operators[MAX];
int otop = -1;

int precedence(char op)
{
    if (op == '+' || op == '-')
        return 1;

    if (op == '*' || op == '/')
        return 2;

    return 0;
}

void pushValue(int value)
{
    values[++vtop] = value;
}

void pushOperator(char op)
{
    operators[++otop] = op;
}

int applyOperation()
{
    int b = values[vtop--];
    int a = values[vtop--];
    char op = operators[otop--];

    switch (op)
    {
        case '+':
            pushValue(a + b);
            break;

        case '-':
            pushValue(a - b);
            break;

        case '*':
            pushValue(a * b);
            break;

        case '/':
            if (b == 0)
            {
                printf("Error: Division by zero\n");
                exit(1);
            }

            pushValue(a / b);
            break;
    }

    return 1;
}

int main()
{
    char exp[MAX];
    int i = 0;

    printf("Enter an expression: ");
    fgets(exp, MAX, stdin);

    while (exp[i] != '\0' && exp[i] != '\n')
    {
        if (isspace((unsigned char)exp[i]))
        {
            i++;
        }

        else if (isdigit((unsigned char)exp[i]))
        {
            int num = 0;

            while (isdigit((unsigned char)exp[i]))
            {
                num = num * 10 + (exp[i] - '0');
                i++;
            }

            pushValue(num);
        }

        else if (exp[i] == '(')
        {
            pushOperator(exp[i]);
            i++;
        }

        else if (exp[i] == ')')
        {
            while (otop >= 0 && operators[otop] != '(')
                applyOperation();

            if (otop < 0)
            {
                printf("Invalid expression\n");
                return 1;
            }

            otop--;
            i++;
        }

        else if (strchr("+-*/", exp[i]))
        {
            while (otop >= 0 &&
                   operators[otop] != '(' &&
                   precedence(operators[otop]) >= precedence(exp[i]))
            {
                applyOperation();
            }

            pushOperator(exp[i]);
            i++;
        }

        else
        {
            printf("Invalid character\n");
            return 1;
        }
    }

    while (otop >= 0)
    {
        if (operators[otop] == '(')
        {
            printf("Invalid expression\n");
            return 1;
        }

        applyOperation();
    }

    if (vtop != 0)
    {
        printf("Invalid expression\n");
        return 1;
    }

    printf("Result = %d\n", values[vtop]);

    return 0;
}