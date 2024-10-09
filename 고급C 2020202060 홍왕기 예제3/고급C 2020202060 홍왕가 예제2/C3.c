#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void ySymmetry(char arr[4][4], char resultArr[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resultArr[i][j] = arr[i][3 - j]; // y�� ��Ī���� ����
        }
    }
}

void xSymmetry(char arr[4][4], char resultArr[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resultArr[i][j] = arr[3 - i][j]; // x�� ��Ī���� ����
        }
    }
}

// ���� ��Ī�� �����ϰ� ��Ī�� �迭�� ��ȯ�ϴ� �Լ�
void circularSymmetry(char arr[4][4], char resultArr[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resultArr[i][j] = arr[3 - i][3 - j]; // ���� ��Ī���� ����
        }
    }
}

int main(void)
{
    char arr[4][4];
    char resultArr[4][4];

    // �迭�� 'O'�� �ʱ�ȭ
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            arr[i][j] = 'O';
        }
    }

    int x, y;
    printf(" -2~2 ���� x��ǥ�� y��ǥ�� �Է��Ͻÿ� (0 ������): ");
    scanf("%d %d", &x, &y);

    // �Է� ��ǥ ��ȿ�� �˻�
    if (!((x < 3 && x > -3) && (y < 3 && y > -3)) || (x == 0 || y == 0))
    {
        printf("��ǥ�� �߸� �Է��Ͽ����ϴ�.");
        return 0;
    }

    // �迭 �ε��� ����
    int indexX, indexY;

    switch (x)
    {
    case 2:
        indexY = 3;
        break;
    case 1:
        indexY = 2;
        break;
    case -1:
        indexY = 1;
        break;
    default:
        indexY = 0;
        break;
    }

    switch (y)
    {
    case 2:
        indexX = 0;
        break;
    case 1:
        indexX = 1;
        break;
    case -1:
        indexX = 2;
        break;
    default:
        indexX = 3;
        break;
    }

    // �Է��� ��ǥ�� 'X' ǥ��
    arr[indexX][indexY] = 'X';

    // �迭 ���
    printf("���� �迭:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }

    // x�� ��Ī �Լ� ȣ��
    xSymmetry(arr, resultArr);

    // ��Ī �迭 ���
    printf("x �� ��Ī �迭:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%c", resultArr[i][j]);
        }
        printf("\n");
    }

    // y�� ��Ī �Լ� ȣ��
    ySymmetry(arr, resultArr);

    // Y�� ��Ī �迭 ���
    printf("Y �� ��Ī �迭:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%c", resultArr[i][j]);
        }
        printf("\n");
    }

    // ���� ��Ī �Լ� ȣ��
    circularSymmetry(arr, resultArr);
    printf("���� ��Ī �迭:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%c", resultArr[i][j]);
        }
        printf("\n");
    }

    return 0;
}