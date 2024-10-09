#include <stdio.h>
#include <stdlib.h> // rand() 함수 포함 라이브러리
#include <time.h>

// 오름차순으로 정렬하는 함수
void sort_Ascending(int arr[])
{
    // insertion sort 알고리즘
    int key;
    for (int i = 1; i < 100; i++)
    {
        key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// 내림차순으로 정렬하는 함수
void sort_Descending(int arr[])
{
    // insertion sort 알고리즘
    int key;
    for (int i = 1; i < 100; i++)
    {
        key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main(void)
{
    srand(time(NULL)); // 난수 초기화
    int arr[100] = {0};
    int used[100] = {0}; // 중복 여부 확인을 위한 배열
    int temp = 0;

    while (temp < 100)
    {
        int num = rand() % 100; // 0~100 사이 난수 생성
        if (used[num] == 0)
        {                    // 중복되지 않은 숫자라면
            arr[temp] = num; // 배열에 저장
            used[num] = 1;   // 해당 숫자를 사용했다고 표시
            temp++;
        }
    }

    // 오름차순 정렬
    sort_Ascending(arr);
    printf("오름 차순 정렬:\n");
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n\n내림 차순 정렬: \n");

    // 내림차순 정렬
    sort_Descending(arr);
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
