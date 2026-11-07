
#include <stdio.h>
#include <string.h>

char transitions[20][3];
char closure[20][20];
int n, t;

void add_state(char str[], char state)
{
    if (strchr(str, state) == NULL)
    {
        int len = strlen(str);
        str[len] = state;
        str[len + 1] = '\0';
    }
}

void findClosure(int state)
{
    for (int i = 0; i < t; i++)
    {
        if (transitions[i][0] == state + '0' &&
            transitions[i][1] == 'e')
        {
            char next = transitions[i][2];

            if (strchr(closure[state], next) == NULL)
            {
                add_state(closure[state], next);
                findClosure(next - '0');
            }
        }
    }
}

int main()
{
    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of transitions: ");
    scanf("%d", &t);

    printf("Enter transitions (Start Input End):\n");

    for (int i = 0; i < t; i++)
        scanf("%s", transitions[i]);

    for (int i = 0; i < n; i++)
    {
        sprintf(closure[i], "%d", i);
        findClosure(i);
    }

    printf("\nEpsilon Closures:\n");

    for (int i = 0; i < n; i++)
    {
        printf("E-closure(q%d) = { ", i);

        for (int j = 0; j < strlen(closure[i]); j++)
            printf("q%c ", closure[i][j]);

        printf("}\n");
    }

    return 0;
}
