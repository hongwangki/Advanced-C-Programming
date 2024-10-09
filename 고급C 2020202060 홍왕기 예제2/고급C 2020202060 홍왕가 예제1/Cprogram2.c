#include <stdio.h>
#define _CRT_SECUTE_NO_WARNININGS
// 배열을 받아 값을 변환하는 함수
void SwapArr(int arr[])
{
    // 값 변환 과정
    int temp;
    temp = arr[0];
    arr[0] = arr[1];
    arr[1] = temp;
}
// 포인터로 주소를 받아 값을 변환하는 함수
void SwapPFun(int *A, int *B)
{
    // 값 변환 과정
    int temp;
    temp = *A;
    *A = *B;
    *B = temp;
}

int main(void)
{
    // 두개의 수를 입력받고 함수를 호출하여 출력
    int arr[2] = {0};
    printf("두개의 정수를 입력하시오:");
    scanf("%d %d", &arr[0], &arr[1]);
    printf("Before Swap: %d %d\n", arr[0], arr[1]);
    SwapArr(arr);
    printf("Swap by index : %d %d\n\n", arr[0], arr[1]);

    printf("두개의 정수를 입력하시오:");
    scanf("%d %d", &arr[0], &arr[1]);
    printf("Before Swap: %d %d\n", arr[0], arr[1]);
    SwapPFun(&arr[0], &arr[1]);
    printf("Swap by Pointer : %d %d", arr[0], arr[1]);
}
