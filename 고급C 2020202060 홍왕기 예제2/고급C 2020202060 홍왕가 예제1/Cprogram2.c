#include <stdio.h>
#define _CRT_SECUTE_NO_WARNININGS
// �迭�� �޾� ���� ��ȯ�ϴ� �Լ�
void SwapArr(int arr[])
{
    // �� ��ȯ ����
    int temp;
    temp = arr[0];
    arr[0] = arr[1];
    arr[1] = temp;
}
// �����ͷ� �ּҸ� �޾� ���� ��ȯ�ϴ� �Լ�
void SwapPFun(int *A, int *B)
{
    // �� ��ȯ ����
    int temp;
    temp = *A;
    *A = *B;
    *B = temp;
}

int main(void)
{
    // �ΰ��� ���� �Է¹ް� �Լ��� ȣ���Ͽ� ���
    int arr[2] = {0};
    printf("�ΰ��� ������ �Է��Ͻÿ�:");
    scanf("%d %d", &arr[0], &arr[1]);
    printf("Before Swap: %d %d\n", arr[0], arr[1]);
    SwapArr(arr);
    printf("Swap by index : %d %d\n\n", arr[0], arr[1]);

    printf("�ΰ��� ������ �Է��Ͻÿ�:");
    scanf("%d %d", &arr[0], &arr[1]);
    printf("Before Swap: %d %d\n", arr[0], arr[1]);
    SwapPFun(&arr[0], &arr[1]);
    printf("Swap by Pointer : %d %d", arr[0], arr[1]);
}
