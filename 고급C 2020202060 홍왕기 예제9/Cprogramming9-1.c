#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//Human 구조체 선언
struct Human {
    char name[10];
    //공용 변수 선언
    union {
        char phone[30];
        char id[30];
    } NumOrCall;
};

int main() {
    struct Human human;

    printf("이름 --> ");
    scanf("%9s", human.name);  // 최대 9글자까지만 입력받도록 제한
    if (strlen(human.name) >= 10) {
        printf("이름 입력 실패: 최대 9글자까지 입력하세요.\n");
        return 1;
    }

    printf("전화번호/주민번호 --> ");
    scanf("%29s", human.NumOrCall.phone);  // 최대 29글자까지만 입력받도록 제한
    if (strlen(human.NumOrCall.phone) >= 30) {
        printf("전화번호/주민번호 입력 실패: 최대 29글자까지 입력하세요.\n");
        return 1;
    }

    printf("\n--- 구조체/공용체 혼합 사용 ---\n");
    printf("이름 ==> %s\n", human.name);
    printf("전화번호/주민번호 ==> %s\n", human.NumOrCall.phone);

    return 0;
}