#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int main() {
    FILE* f1;
    char inputs[3][100];  // 3 str input -> max size=100

    f1 = fopen("output1.txt", "w");
    fprintf(f1, "--입력과 반대로 출력(포인터) : 글자 순서도 거꾸로 --\n");

    // input str save arr
    for (int i = 0; i < 3; i++) {
        printf("%d 번째 문자열 : ", i + 1);
        gets_s(inputs[i], sizeof(inputs[i]));
    }

    // arr print
    for (int i = 2; i >= 0; i--) {
        fprintf(f1, "%d : ", i + 1);
        for (int j = strlen(inputs[i]) - 1; j >= 0; j--) {
            fprintf(f1, "%c", inputs[i][j]);
        }
        fprintf(f1, "\n");
    }

    fclose(f1);
    return 0;
}