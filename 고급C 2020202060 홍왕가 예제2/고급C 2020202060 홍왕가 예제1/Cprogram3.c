#define _CRT_SECURE_NO_WARNINNG
#include <stdio.h>

double PI = 3.14; // �������� ����

int main(void)
{
    int radius;
    printf("�� ��/�� ��  �� �� ��  �� ��  �� �� �� ��  �� �� �� �� ��  : ");
    scanf("%d", &radius); // ������ �� �Է�
    printf("�� �� ��  �� �� ��  : %d ��  �� ��\n", radius);
    printf("�� ��  �� �� ��  %lf\n", PI * radius * radius); // ���� ���
    printf("�� ��  �� �� ��  %lf\n", 2 * PI * radius);      // �ѷ� ���
}
