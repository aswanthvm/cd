
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char production[20][20];
char first[26][30];
char follow[26][30];

int n;

int add(char set[], char c)
{
    if (strchr(set, c))
        return 0;

    int len = strlen(set);
    set[len] = c;
    set[len + 1] = '\0';

    return 1;
}

void findFirst(char symbol, char result[])
{
    int i, j;

    if (!isupper(symbol))
    {
        add(result, symbol);
        return;
    }

    for (i = 0; i < n; i++)
    {
        if (production[i][0] == symbol)
        {
            for (j = 2; production[i][j] != '\0'; j++)
            {
                char x = production[i][j];

                if (!isupper(x))
                {
                    add(result, x);
                    break;
                }

                char temp[30] = "";

                findFirst(x, temp);

                int epsilon = 0;

                for (int k = 0; temp[k] != '\0'; k++)
                {
                    if (temp[k] == '#')
                        epsilon = 1;
                    else
                        add(result, temp[k]);
                }

                if (!epsilon)
                    break;

                if (production[i][j + 1] == '\0')
                    add(result, '#');
            }
        }
    }
}

void findFollow()
{
    int i, j, k, change;

    add(follow[production[0][0] - 'A'], '$');

    do
    {
        change = 0;

        for (i = 0; i < n; i++)
        {
            char A = production[i][0];

            for (j = 2; production[i][j] != '\0'; j++)
            {
                char B = production[i][j];

                if (!isupper(B))
                    continue;

                int nullable = 1;

                for (k = j + 1; production[i][k] != '\0'; k++)
                {
                    char x = production[i][k];

                    if (!isupper(x))
                    {
                        change |= add(follow[B - 'A'], x);
                        nullable = 0;
                        break;
                    }

                    char temp[30] = "";

                    findFirst(x, temp);

                    for (int m = 0; temp[m] != '\0'; m++)
                    {
                        if (temp[m] != '#')
                            change |= add(follow[B - 'A'], temp[m]);
                    }

                    if (!strchr(temp, '#'))
                    {
                        nullable = 0;
                        break;
                    }
                }

                if (nullable)
                {
                    for (k = 0; follow[A - 'A'][k] != '\0'; k++)
                        change |= add(follow[B - 'A'],
                                      follow[A - 'A'][k]);
                }
            }
        }

    } while (change);
}

int main()
{
    int i;
    char seen[26] = {0};

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (example E=TR):\n");

    for (i = 0; i < n; i++)
        scanf("%s", production[i]);

    for (i = 0; i < n; i++)
        findFirst(production[i][0],
                  first[production[i][0] - 'A']);

    findFollow();

    printf("\nFIRST:\n");

    for (i = 0; i < n; i++)
    {
        char c = production[i][0];

        if (!seen[c - 'A'])
        {
            printf("FIRST(%c) = { %s }\n",
                   c, first[c - 'A']);

            seen[c - 'A'] = 1;
        }
    }

    for (i = 0; i < 26; i++)
        seen[i] = 0;

    printf("\nFOLLOW:\n");

    for (i = 0; i < n; i++)
    {
        char c = production[i][0];

        if (!seen[c - 'A'])
        {
            printf("FOLLOW(%c) = { %s }\n",
                   c, follow[c - 'A']);

            seen[c - 'A'] = 1;
        }
    }

    return 0;
}
