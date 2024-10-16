#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    int num;       // input count
    char tmp[100]; // tmp buff
    int maxsize = 0;

    printf("Number of input?: ");
    scanf("%d", &num);
    getchar();

    // point arr make
    char **p = (char **)malloc(sizeof(char *) * num);

    for (int i = 0; i < num; i++)
    {
        printf("%d input (Enter) : ", i + 1);
        fgets(tmp, sizeof(tmp), stdin);
        int size = strlen(tmp);

        if (tmp[size - 1] == '\n')
        {
            tmp[size - 1] = '\0';
            size--;
        }

        if (maxsize < size)
        {
            maxsize = size;
        }

        p[i] = (char *)malloc(sizeof(char) * (size + 1));
        strcpy(p[i], tmp);
    }

    for (int j = 0; j < maxsize; j++)
    {
        for (int i = 0; i < num; i++)
        {
            // J is vaild?
            if (j < strlen(p[i]))
            {
                printf("%c", p[i][j]);
            }
        }
    }

    printf("\n");

    for (int i = 0; i < num; i++)
    {
        free(p[i]);
    }
    free(p);
}
