#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // malloc ����� ���� �������

int my_strcmp(char str1[], char str2[])
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        // str1�� str2���� ū ���
        if (str1[i] > str2[i])
        {
            return 1;
        }
        // str2�� str1���� ū ���
        else if (str1[i] < str2[i])
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

char *my_strcat(char str1[], char str2[], char resultArr[])
{
    int j = 0;
    for (int i = 0; str1[i] != '\0'; i++)
    {
        resultArr[j++] = str1[i];
    }
    for (int i = 0; str2[i] != '\0'; i++)
    {
        resultArr[j++] = str2[i];
    }
    resultArr[j] = '\0'; // �������� null ���� �߰�
    return resultArr;
}

char *my_strcpy(char str[])
{
    int len = 0;

    // ������ ���� ���
    while (str[len] != '\0')
    {
        len++;
    }

    // ���� �޸� �Ҵ�
    char *newArr = (char *)malloc((len + 1) * sizeof(char));
    if (newArr == NULL)
    { // �޸� �Ҵ� ���� Ȯ��
        return NULL;
    }

    // ���ڿ� ����
    for (int i = 0; i < len; i++)
    {
        newArr[i] = str[i];
    }
    newArr[len] = '\0'; // �� ���� �߰�

    return newArr; // ������ ���ڿ� ��ȯ
}

int my_strlen(char str[])
{
    int len = 0;
    while (str[len] != '\0')
    { // ���ڿ��� ���� ������ ������ ���̸� ����.
        len++;
    }
    return len; // ���̸� ��ȯ
}

int main(void)
{
    char str1[10], str2[10], resultArr[12]; // ���� ���� ����

    printf("5���� �̳��� ����ܾ� �ΰ��� �Է��Ͻÿ�: ");
    scanf("%9s %9s", str1, str2);

    // 5���� �̻� üũ
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);

    if (len1 > 5 || len2 > 5)
    {
        printf("5�� �̳��� �Է��Ͽ��� �մϴ�.\n");
        return 1; // 5���� �̻��� ��� ����
    }

    // my_strcmp �׽�Ʈ
    int strcmp = my_strcmp(str1, str2);
    printf("strcmp ��ȯ���� : %d\n", strcmp);

    char *CatStr = my_strcat(str1, str2, resultArr);
    printf("strcat ��ȯ���� : %s\n", CatStr);

    char *CpyStr1 = my_strcpy(str1); // str1�� ����
    if (CpyStr1 != NULL)
    {
        printf("strcpy ù��° ���ڿ� ��ȯ���� : %s\n", CpyStr1);
        free(CpyStr1); // ���� �Ҵ�� �޸� ����
    }
    else
    {
        printf("�޸� �Ҵ� ����!\n");
    }

    char *CpyStr2 = my_strcpy(str2); // str1�� ����
    if (CpyStr2 != NULL)
    {
        printf("strcpy �ι�° ���ڿ� ��ȯ���� : %s\n", CpyStr2);
        free(CpyStr2); // ���� �Ҵ�� �޸� ����
    }
    else
    {
        printf("�޸� �Ҵ� ����!\n");
    }

    return 0;
}
