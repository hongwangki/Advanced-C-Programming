#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int values[] = { 1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1 };
int num;
int count = 0;

char* intToRoman(int num, int count1) {
    char* symbols[] = { "M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I" };

    char* result = (char*)malloc(16 * sizeof(char)); //  15�ڸ� �θ� ���� + null 

    result[0] = '\0'; // ���ڿ� �ʱ�ȭ
    count1 = 0; // ����� �θ� ������ ���� �ʱ�ȭ

    for (int i = 0; i < 13; i++) {
        while (num >= values[i]) {
            num -= values[i];
            strcat(result, symbols[i]); // �θ� ���ڸ� �߰�
            if (strlen(symbols[i]) == 2) {
                count1 += 2;
            }
            else {
                count1++; // ����� �θ� ���� ���� ����
            }
        }
    }
    count = count1;
    return result;
}

int main() {
    printf("Enter a number less than 1000: ");
    scanf("%d", &num);

    if (num < 1 || num > 1000) {
        printf("Only 1~1000 number.\n");
        return 1;
    }
    char* romanNumber = intToRoman(num, count);

    // �� �κ��� �հ� ���
    printf("%d = ", num);
    int temp = num;
    for (int i = 0; i < 13; i++) {
        while (temp >= values[i]) {
            printf("%d", values[i]);
            temp -= values[i];
            if (temp > 0) printf(" + ");
        }
    }

    printf(" = %s, %d\n", romanNumber, count);

    free(romanNumber); // ���� �޸� ����
    return 0;
}
