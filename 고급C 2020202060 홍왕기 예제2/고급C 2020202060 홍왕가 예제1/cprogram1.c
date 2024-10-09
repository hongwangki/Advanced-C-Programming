#include <stdio.h>
#define _CRT_SECUTE_NO_WARNININGS
// 매개변수로 A B를 전달 받아 교환하는 함수
void SwapFun(int A, int B)
{
    int temp; // 교환하는 값을 저장해 놓는 변수
    // 변환 과정
    temp = A;
    A = B;
    B = temp;
    // 변환값 출력
    printf("After value swap(in function), A : %d, B : %d\n", A, B);
}
// 매개변수로 포인터를 전달받아 A B를 교환하는 함수
void SwapPFun(int *A, int *B)
{
    // 값 변환 과정
    int temp;
    temp = *A;
    *A = *B;
    *B = temp;
    // 변환값 출력 MAIN A B도 값이 바뀜
    printf("After value swap(in function), A : %d, B : %d\n", *A, *B);
}
int main(void)
{
    int A, B, temp;
    printf("A 와 B를 입력하시오:");
    // A와 B를 입력받음
    scanf("%d %d", &A, &B);

    // 변환값을 출력하는 문
    printf("Before swap, A: %d, B: %d\n\n", A, B);
    SwapFun(A, B);
    printf("After value swap(int main), A : %d, B : %d\n\n", A, B);
    SwapPFun(&A, &B);
    printf("Reference value swap(int main), A : %d, B : %d", A, B);
}
