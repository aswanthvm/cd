
#include <stdio.h>

#define MAX 10

int n, m;
int trans[MAX][MAX][MAX];
int eps[MAX][MAX];
int closure[MAX][MAX];
int nfa[MAX][MAX][MAX];

void findClosure()
{
    int i, j, k;

    for (i = 0; i < n; i++)
    {
        closure[i][i] = 1;

        for (j = 0; j < n; j++)
            if (eps[i][j])
                closure[i][j] = 1;
    }

    for (k = 0; k < n; k++)
        for (i = 0; i < n; i++)
            for (j = 0; j < n; j++)
                if (closure[i][k] && closure[k][j])
                    closure[i][j] = 1;
}

int main()
{
    int i, j, k, a, b;
    int start, f;
    int final[MAX], newFinal[MAX] = {0};

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of input symbols: ");
    scanf("%d", &m);

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            printf("Number of transitions from state %d on symbol %d: ", i, j);
            scanf("%d", &k);

            for (a = 0; a < k; a++)
            {
                printf("Enter destination state: ");
                scanf("%d", &b);
                trans[i][j][b] = 1;
            }
        }

        printf("Number of epsilon transitions from state %d: ", i);
        scanf("%d", &k);

        for (a = 0; a < k; a++)
        {
            printf("Enter destination state: ");
            scanf("%d", &b);
            eps[i][b] = 1;
        }
    }

    printf("Enter initial state: ");
    scanf("%d", &start);

    printf("Enter number of final states: ");
    scanf("%d", &f);

    for (i = 0; i < f; i++)
    {
        printf("Enter final state: ");
        scanf("%d", &final[i]);
    }

    findClosure();

    for (i = 0; i < n; i++)
    {
        for (j = 0; j < m; j++)
        {
            for (k = 0; k < n; k++)
            {
                if (closure[i][k])
                {
                    for (a = 0; a < n; a++)
                    {
                        if (trans[k][j][a])
                        {
                            for (b = 0; b < n; b++)
                            {
                                if (closure[a][b])
                                    nfa[i][j][b] = 1;
                            }
                        }
                    }
                }
            }
        }
    }

    for (i = 0; i < n; i++)
        for (j = 0; j < f; j++)
            if (closure[i][final[j]])
                newFinal[i] = 1;

    printf("\nEquivalent NFA Transition Table:\n");

    for (i = 0; i < n; i++)
    {
        printf("State %d:\n", i);

        for (j = 0; j < m; j++)
        {
            printf("Symbol %d -> {", j);

            for (k = 0; k < n; k++)
                if (nfa[i][j][k])
                    printf(" %d", k);

            printf(" }\n");
        }
    }

    printf("\nInitial state: {");

    for (i = 0; i < n; i++)
        if (closure[start][i])
            printf(" %d", i);

    printf(" }\n");

    printf("Final states: ");

    for (i = 0; i < n; i++)
        if (newFinal[i])
            printf("%d ", i);

    printf("\n");

    return 0;
}
