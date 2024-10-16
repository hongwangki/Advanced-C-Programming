#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char tmp[100]; // input buf
    printf("���ڿ��� �Է��Ͻÿ�: ");

    fgets(tmp, sizeof(tmp), stdin); // input
    tmp[strcspn(tmp, "\n")] = '\0'; 

    int size = strlen(tmp);

    char* input = (char*)malloc(sizeof(char) * (size + 1)); // input size arr make
    strcpy(input, tmp); // copyt input->tmp

    // �빮�ڿ� �ҹ��ڸ� ������ ������ �迭 ���� �Ҵ�
    char** p = (char**)malloc(sizeof(char*) * 2);
    p[0] = (char*)malloc(sizeof(char) * (size + 1)); // �빮�� ��ȯ ���
    p[1] = (char*)malloc(sizeof(char) * (size + 1)); // �ҹ��� ��ȯ ���

    // ��ҹ��� ��ȯ
    for (int i = 0; i < size; i++) {
        // �빮�� ��ȯ
        if (input[i] >= 'a' && input[i] <= 'z') {
            p[0][i] = input[i] - 32; // �ҹ��ڸ� �빮�ڷ� ��ȯ
        }
        else {
            p[0][i] = input[i]; 
        }

        // �ҹ��� ��ȯ
        if (input[i] >= 'A' && input[i] <= 'Z') {
            p[1][i] = input[i] + 32; // �빮�ڸ� �ҹ��ڷ� ��ȯ
        }
        else {
            p[1][i] = input[i]; 
        }
    }
    p[0][size] = '\0'; 
    p[1][size] = '\0'; 

    // ��� ���
    printf("�빮�ڷ� ��ȯ: %s\n", p[0]);
    printf("�ҹ��ڷ� ��ȯ: %s\n", p[1]);

    // ���� �޸� ����
    free(p[0]);
    free(p[1]);
    free(p);
    free(input);

    return 0;
}