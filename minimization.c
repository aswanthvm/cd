
#include <stdio.h>

#define MAX 20

int main()
{
    int n, m, i, j, k;
    int trans[MAX][MAX], final[MAX];
    int group[MAX], newGroup[MAX];
    int changed, groups;

    printf("Enter number of states: ");
    scanf("%d", &n);

    printf("Enter number of symbols: ");
    scanf("%d", &m);

    printf("Enter transition table:\n");

    for (i = 0; i < n; i++)
        for (j = 0; j < m; j++)
            scanf("%d", &trans[i][j]);

    for (i = 0; i < n; i++)
        final[i] = 0;

    printf("Enter number of final states: ");
    scanf("%d", &k);

    printf("Enter final states:\n");

    for (i = 0; i < k; i++)
    {
        scanf("%d", &j);
        final[j] = 1;
    }

    // Initial grouping
    for (i = 0; i < n; i++)
        group[i] = final[i];

    // Refine groups
    do
    {
        changed = 0;
        groups = 0;

        for (i = 0; i < n; i++)
        {
            int found = 0;

            for (j = 0; j < i; j++)
            {
                if (group[i] == group[j])
                {
                    for (k = 0; k < m; k++)
                    {
                        if (group[trans[i][k]] !=
                            group[trans[j][k]])
                            break;
                    }

                    if (k == m)
                    {
                        newGroup[i] = newGroup[j];
                        found = 1;
                        break;
                    }
                }
            }

            if (!found)
                newGroup[i] = groups++;
        }

        for (i = 0; i < n; i++)
        {
            if (group[i] != newGroup[i])
                changed = 1;

            group[i] = newGroup[i];
        }

    } while (changed);

    // Count groups
    groups = 0;

    for (i = 0; i < n; i++)
        if (group[i] >= groups)
            groups = group[i] + 1;

    // Print equivalent states
    printf("\nEquivalent States:\n");

    for (i = 0; i < groups; i++)
    {
        printf("S%d = { ", i);

        for (j = 0; j < n; j++)
            if (group[j] == i)
                printf("q%d ", j);

        printf("}\n");
    }

    // Print minimized transition table
    printf("\nMinimized Transition Table:\n");

    for (i = 0; i < groups; i++)
    {
        printf("S%d: ", i);

        for (j = 0; j < m; j++)
        {
            for (k = 0; k < n; k++)
                if (group[k] == i)
                    break;

            printf("S%d ", group[trans[k][j]]);
        }

        printf("\n");
    }

    // Print final states
    printf("\nFinal States: ");

    for (i = 0; i < groups; i++)
    {
        for (j = 0; j < n; j++)
        {
            if (group[j] == i && final[j])
            {
                printf("S%d ", i);
                break;
            }
        }
    }

    printf("\n");

    return 0;
}
