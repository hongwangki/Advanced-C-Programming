#include <stdio.h>
#define _CRT_SECUTE_NO_WARNININGS
// �Ű������� A B�� ���� �޾� ��ȯ�ϴ� �Լ�
void SwapFun(int A, int B)
{
    int temp; // ��ȯ�ϴ� ���� ������ ���� ����
    // ��ȯ ����
    temp = A;
    A = B;
    B = temp;
    // ��ȯ�� ���
    printf("After value swap(in function), A : %d, B : %d\n", A, B);
}
// �Ű������� �����͸� ���޹޾� A B�� ��ȯ�ϴ� �Լ�
void SwapPFun(int *A, int *B)
{
    // �� ��ȯ ����
    int temp;
    temp = *A;
    *A = *B;
    *B = temp;
    // ��ȯ�� ��� MAIN A B�� ���� �ٲ�
    printf("After value swap(in function), A : %d, B : %d\n", *A, *B);
}
int main(void)
{
    int A, B, temp;
    printf("A �� B�� �Է��Ͻÿ�:");
    // A�� B�� �Է¹���
    scanf("%d %d", &A, &B);

    // ��ȯ���� ����ϴ� ��
    printf("Before swap, A: %d, B: %d\n\n", A, B);
    SwapFun(A, B);
    printf("After value swap(int main), A : %d, B : %d\n\n", A, B);
    SwapPFun(&A, &B);
    printf("Reference value swap(int main), A : %d, B : %d", A, B);
}
