#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>

int check_ID() {
    char id[10]; // ID �迭
    int mode;    // ��� ����

    printf("Mode Select (admin or user) : ");
    scanf("%s", id);  // ID �Է�

    if (strcmp(id, "admin") == 0) {
        printf("Admin mode\n");
        mode = 1;  // ������ ���
    }
    else if (strcmp(id, "user") == 0) {
        printf("User mode\n");
        mode = 0;  // ����� ���
    }
    else {
        printf("Error : Wrong Input!\n");
        mode = -1; // ���� ���
    }
    return mode; // ��� ��ȯ
}

int main() {
    int mode = check_ID(); // ��� ����
}
