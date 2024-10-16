#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char tmp[100]; // input buf
    printf("문자열을 입력하시오: ");

    fgets(tmp, sizeof(tmp), stdin); // input
    tmp[strcspn(tmp, "\n")] = '\0'; 

    int size = strlen(tmp);

    char* input = (char*)malloc(sizeof(char) * (size + 1)); // input size arr make
    strcpy(input, tmp); // copyt input->tmp

    // 대문자와 소문자를 저장할 포인터 배열 동적 할당
    char** p = (char**)malloc(sizeof(char*) * 2);
    p[0] = (char*)malloc(sizeof(char) * (size + 1)); // 대문자 변환 결과
    p[1] = (char*)malloc(sizeof(char) * (size + 1)); // 소문자 변환 결과

    // 대소문자 변환
    for (int i = 0; i < size; i++) {
        // 대문자 변환
        if (input[i] >= 'a' && input[i] <= 'z') {
            p[0][i] = input[i] - 32; // 소문자를 대문자로 변환
        }
        else {
            p[0][i] = input[i]; 
        }

        // 소문자 변환
        if (input[i] >= 'A' && input[i] <= 'Z') {
            p[1][i] = input[i] + 32; // 대문자를 소문자로 변환
        }
        else {
            p[1][i] = input[i]; 
        }
    }
    p[0][size] = '\0'; 
    p[1][size] = '\0'; 

    // 결과 출력
    printf("대문자로 변환: %s\n", p[0]);
    printf("소문자로 변환: %s\n", p[1]);

    // 동적 메모리 해제
    free(p[0]);
    free(p[1]);
    free(p);
    free(input);

    return 0;
}