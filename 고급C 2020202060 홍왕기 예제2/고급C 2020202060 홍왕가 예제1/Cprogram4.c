#include <stdio.h>

int main(void)
{
    int arr[29] = {0};

    // �迭�� 2���� 30���� �ʱ�ȭ
    for (int i = 0; i < 29; i++)
    {
        arr[i] = i + 2;
    }

    // �Ҽ� ã�� �˰���
    for (int i = 2; i < 30; i++)
    {
        for (int j = 0; j < 29; j++)
        {
            if (i != j + 2 && arr[j] % i == 0)
            {
                arr[j] = 0;
            }
        }
    }

    // �迭 ���
    for (int i = 0; i < 29; i++)
    {
        if (arr[i] != 0)
        {
            printf("%d ", arr[i]);
        }
    }
}