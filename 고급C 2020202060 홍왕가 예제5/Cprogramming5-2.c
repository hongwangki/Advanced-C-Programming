#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int my_strcmp(char str1[], char str2[])
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        // str1�� str2���� ū ���
        if (tolower(str1[i]) > tolower(str2[i]))
        {
            return 1;
        }
        // str2�� str1���� ū ���
        else if (tolower(str1[i]) < tolower(str2[i]))
        {
            return -1;
        }
        // ���� ��쿡�� ���� ���ڷ� �Ѿ
        i++;
    }

    // �� ���ڿ��� ������ �� ���̰� �ٸ� ��� ó��
    if (str1[i] == '\0' && str2[i] == '\0')
    {
        return 0; // �� ���ڿ��� ����
    }
    else if (str1[i] == '\0')
    {
        return -1; // str1�� �� ª��
    }
    else
    {
        return 1; // str2�� �� ª��
    }
}

int main(void)
{
    char tmp[100]; // input buf
    x` printf("input 1 :(Enter ����) : ");

    // input 1
    fgets(tmp, sizeof(tmp), stdin); // input
    int InputSize1 = strlen(tmp);
    char *input1 = (char *)malloc(sizeof(char) * (InputSize1 + 1)); // input size arr make
    strcpy(input1, tmp);                                            // copyt input->tmp

    printf("input 2 :(Enter ����) : ");

    // input 2
    fgets(tmp, sizeof(tmp), stdin); // input
    int InputSize2 = strlen(tmp);
    char *input2 = (char *)malloc(sizeof(char) * (InputSize2 + 1)); // input size arr make
    strcpy(input2, tmp);                                            // copyt input->tmp

    // �빮�ڿ� �ҹ��ڸ� ������ ������ �迭 ���� �Ҵ�
    char **p = (char **)malloc(sizeof(char *) * 2);
    p[0] = (char *)malloc(sizeof(char) * (InputSize1 + 1)); // input1 point arr
    p[1] = (char *)malloc(sizeof(char) * (InputSize2 + 1)); // input2 point arr
    strcpy(p[0], input1);
    strcpy(p[1], input2);
    p[0][InputSize1] = '\0';
    p[1][InputSize2] = '\0';

    if (InputSize1 != InputSize2)
    {
        printf("False"); // if not same size -> false
        // mem free
        free(p[0]);
        free(p[1]);
        free(p);
        free(input1);
        free(input2);
        return 0;
    }
    // if same size input 1 , input 2
    int strcmp_result = my_strcmp(p[0], p[1]);
    if (strcmp_result == 0)
    {
        printf("True");
    }
    else
    {
        printf("False");
    }

    // mem free
    free(p[0]);
    free(p[1]);
    free(p);
    free(input1);
    free(input2);

    return 0;
}