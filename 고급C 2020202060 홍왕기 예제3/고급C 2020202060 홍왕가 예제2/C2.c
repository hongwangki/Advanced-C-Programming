#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int arr[4][8] = {0}; // 4�� 8���� �迭�� 0���� �ʱ�ȭ
    printf("ù��° ���� �Է��Ͻÿ�: ");

    // ù��° �� �Է�
    for (int i = 0; i < 8; i++)
    {
        scanf("%d", &arr[0][i]);
        if (arr[0][i] <= 0)
        {
            printf("0 �Ǵ� ������ �Է��ϸ� �ȵ˴ϴ�.\n");
            return 0;
        }
    }

    // ù��° ���� ������ ���� �ι�° �࿡ �ֱ�
    for (int j = 0; j < 8; j += 2)
    {
        // arr[1][j] = arr[0][j] + arr[0][j + 1];  // ¦�� �ε����� �հ� ����
        *(*(arr + 1) + j) = *(*(arr) + j) + *(*(arr) + j + 1);
    }

    // �ι�° ���� ������ ���� ����° �࿡ �ֱ�
    for (int z = 1; z < 3; z++)
    { // �ι�°�� ����° �࿡ ���� �ݺ�
        for (int i = 0; i < 8; i++)
        {
            if (*(*(arr + z) + i) != 0)
            { // 0�� �ƴ� ��쿡��
                for (int j = i + 1; j < 8; j++)
                {
                    if (*(*(arr + z) + j) != 0)
                    { // ���� 0�� �ƴ� ��Ҹ� ã��
                        // arr[z + 1][i] = arr[z][i] + arr[z][j];  // �ջ��Ͽ� ����
                        *(*(arr + z + 1) + i) = *(*(arr + z) + i) + *(*(arr + z) + j);
                        i = j; // �ε����� ������Ʈ�Ͽ� �ߺ� ��� ����
                        break; // ���� ã���� ���� ����
                    }
                }
            }
        }
    }

    // ��� ���
    for (int z = 0; z < 4; z++)
    {
        for (int k = 0; k < 8; k++)
        {
            printf("%d ", *(*(arr + z) + k));
        }
        printf("\n");
    }

    return 0;
}