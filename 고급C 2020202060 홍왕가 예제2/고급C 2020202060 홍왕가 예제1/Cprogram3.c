#define _CRT_SECURE_NO_WARNINNG
#include <stdio.h>

double PI = 3.14; // 전역변수 설정

int main(void)
{
    int radius;
    printf("넓 이/둘 레  를 구 할  원 의  반 지 름 을  입 력 하 시 오  : ");
    scanf("%d", &radius); // 반지름 값 입력
    printf("입 력 한  반 지 름  : %d 에  대 한\n", radius);
    printf("원 의  넓 이 는  %lf\n", PI * radius * radius); // 넓이 출력
    printf("원 의  둘 레 는  %lf\n", 2 * PI * radius);      // 둘레 출력
}
