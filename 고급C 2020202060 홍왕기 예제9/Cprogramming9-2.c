#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
    // enum month
    enum month { Fail, January, February, March, April, May, June, July, August, September, October, November, December };
    int Imonth; // Input Month

    // input month
    printf("�� �Է� : ");
    scanf("%d", &Imonth);

    if (Imonth < 1 || Imonth > 12) {
        printf("�߸��� �Է��Դϴ�.\n");
        return 1; // ���α׷� ����
    }

    enum month mt = Imonth;
    printf("%d���� ", Imonth);

    //�ش� ���� ���� ��°��� ����ġ������ �ۼ�
    switch (mt) {
    case January:
        printf("January �Դϴ�.\n");
        break;
    case February:
        printf("February �Դϴ�.\n");
        break;
    case March:
        printf("March �Դϴ�.\n");
        break;
    case April:
        printf("April �Դϴ�.\n");
        break;
    case May:
        printf("May �Դϴ�.\n");
        break;
    case June:
        printf("June �Դϴ�.\n");
        break;
    case July:
        printf("July �Դϴ�.\n");
        break;
    case August:
        printf("August �Դϴ�.\n");
        break;
    case September:
        printf("September �Դϴ�.\n");
        break;
    case October:
        printf("October �Դϴ�.\n");
        break;
    case November:
        printf("November �Դϴ�.\n");
        break;
    case December:
        printf("December �Դϴ�.\n");
        break;
    default:
        printf("�߸��� �Է��Դϴ�.\n");
    }

    return 0;
}
