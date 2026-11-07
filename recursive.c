#include <stdio.h>

char input[100];
int i = 0;

int E();
int E1();
int T();
int T1();
int F();

int E()
{
    return T() && E1();
}

int E1()
{
    if (input[i] == '+')
    {
        i++;
        return T() && E1();
    }
    return 1;
}

int T()
{
    return F() && T1();
}

int T1()
{
    if (input[i] == '*')
    {
        i++;
        return F() && T1();
    }
    return 1;
}

int F()
{
    if (input[i] == 'i')
    {
        i++;
        return 1;
    }

    if (input[i] == '(')
    {
        i++;

        if (E() && input[i] == ')')
        {
            i++;
            return 1;
        }
    }

    return 0;
}

int main()
{
    printf("Grammar:\n");
    printf("E  -> T E'\n");
    printf("E' -> + T E' | e\n");
    printf("T  -> F T'\n");
    printf("T' -> * F T' | e\n");
    printf("F  -> (E) | i\n");

    printf("\nEnter expression: ");
    scanf("%s", input);

    if (E() && input[i] == '\0')
        printf("\nInput Accepted\n");
    else
        printf("\nInput Rejected\n");

    return 0;
}