#include <stdio.h>

int main(void)
{
    int arr[29] = {0};

    // 배열에 2부터 30까지 초기화
    for (int i = 0; i < 29; i++)
    {
        arr[i] = i + 2;
    }

    // 소수 찾기 알고리즘
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

    // 배열 출력
    for (int i = 0; i < 29; i++)
    {
        if (arr[i] != 0)
        {
            printf("%d ", arr[i]);
        }
    }
}