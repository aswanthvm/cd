
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char p[10][10];
int n;

void first(char c, char s[])
{
    int i, j, k;

    if (!isupper(c))
    {
        if (!strchr(s, c))
            strncat(s, &c, 1);

        return;
    }

    for (i = 0; i < n; i++)
    {
        if (p[i][0] == c)
        {
            if (p[i][3] == '#')
            {
                if (!strchr(s, '#'))
                    strcat(s, "#");
            }
            else
            {
                for (j = 3; p[i][j]; j++)
                {
                    char t[20] = "";

                    first(p[i][j], t);

                    for (k = 0; t[k]; k++)
                    {
                        if (t[k] != '#' && !strchr(s, t[k]))
                            strncat(s, &t[k], 1);
                    }

                    if (!strchr(t, '#'))
                        break;
                }

                if (!p[i][j] && !strchr(s, '#'))
                    strcat(s, "#");
            }
        }
    }
}

void follow(char c, char s[])
{
    int i, j, k;

    if (c == p[0][0] && !strchr(s, '$'))
        strcat(s, "$");

    for (i = 0; i < n; i++)
    {
        for (j = 3; p[i][j]; j++)
        {
            if (p[i][j] == c)
            {
                if (p[i][j + 1])
                {
                    char t[20] = "";

                    first(p[i][j + 1], t);

                    for (k = 0; t[k]; k++)
                    {
                        if (t[k] != '#' && !strchr(s, t[k]))
                            strncat(s, &t[k], 1);
                    }

                    if (strchr(t, '#') && p[i][0] != c)
                    {
                        char u[20] = "";

                        follow(p[i][0], u);

                        for (k = 0; u[k]; k++)
                        {
                            if (!strchr(s, u[k]))
                                strncat(s, &u[k], 1);
                        }
                    }
                }
                else if (p[i][0] != c)
                {
                    char u[20] = "";

                    follow(p[i][0], u);

                    for (k = 0; u[k]; k++)
                    {
                        if (!strchr(s, u[k]))
                            strncat(s, &u[k], 1);
                    }
                }
            }
        }
    }
}

int main()
{
    int i;
    char nt[10] = "";

    printf("Enter number of productions: ");
    scanf("%d", &n);

    printf("Enter productions (use # for epsilon):\n");

    for (i = 0; i < n; i++)
        scanf("%s", p[i]);

    for (i = 0; i < n; i++)
    {
        if (!strchr(nt, p[i][0]))
            strncat(nt, &p[i][0], 1);
    }

    printf("\nFIRST sets:\n");

    for (i = 0; nt[i]; i++)
    {
        char s[20] = "";

        first(nt[i], s);

        printf("FIRST(%c) = {%s}\n", nt[i], s);
    }

    printf("\nFOLLOW sets:\n");

    for (i = 0; nt[i]; i++)
    {
        char s[20] = "";

        follow(nt[i], s);

        printf("FOLLOW(%c) = {%s}\n", nt[i], s);
    }

    return 0;
}
