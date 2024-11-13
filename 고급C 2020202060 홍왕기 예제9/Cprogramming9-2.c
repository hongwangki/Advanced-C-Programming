#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
    // enum month
    enum month { Fail, January, February, March, April, May, June, July, August, September, October, November, December };
    int Imonth; // Input Month

    // input month
    printf("월 입력 : ");
    scanf("%d", &Imonth);

    if (Imonth < 1 || Imonth > 12) {
        printf("잘못된 입력입니다.\n");
        return 1; // 프로그램 종료
    }

    enum month mt = Imonth;
    printf("%d월은 ", Imonth);

    //해당 월에 대한 출력값을 스위치문으로 작성
    switch (mt) {
    case January:
        printf("January 입니다.\n");
        break;
    case February:
        printf("February 입니다.\n");
        break;
    case March:
        printf("March 입니다.\n");
        break;
    case April:
        printf("April 입니다.\n");
        break;
    case May:
        printf("May 입니다.\n");
        break;
    case June:
        printf("June 입니다.\n");
        break;
    case July:
        printf("July 입니다.\n");
        break;
    case August:
        printf("August 입니다.\n");
        break;
    case September:
        printf("September 입니다.\n");
        break;
    case October:
        printf("October 입니다.\n");
        break;
    case November:
        printf("November 입니다.\n");
        break;
    case December:
        printf("December 입니다.\n");
        break;
    default:
        printf("잘못된 입력입니다.\n");
    }

    return 0;
}
