#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

int check_ID() {
    char id[10]; // ID 배열
    int mode;    // 모드 변수

    printf("Mode Select (admin or user) : ");
    scanf("%s", id);  // ID 입력

    if (strcmp(id, "admin") == 0) {
        printf("Admin mode\n");
        mode = 1;  // 관리자 모드
    }
    else if (strcmp(id, "user") == 0) {
        printf("User mode\n");
        mode = 0;  // 사용자 모드
    }
    else {
        printf("Error : Wrong Input!\n");
        mode = -1; // 오류 모드
    }
    return mode; // 모드 반환
}

int main() {
    int mode = check_ID(); // 모드 설정
}
