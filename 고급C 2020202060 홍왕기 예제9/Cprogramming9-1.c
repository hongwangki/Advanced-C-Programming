#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

//Human ����ü ����
struct Human {
    char name[10];
    //���� ���� ����
    union {
        char phone[30];
        char id[30];
    } NumOrCall;
};

int main() {
    struct Human human;

    printf("�̸� --> ");
    scanf("%9s", human.name);  // �ִ� 9���ڱ����� �Է¹޵��� ����
    if (strlen(human.name) >= 10) {
        printf("�̸� �Է� ����: �ִ� 9���ڱ��� �Է��ϼ���.\n");
        return 1;
    }

    printf("��ȭ��ȣ/�ֹι�ȣ --> ");
    scanf("%29s", human.NumOrCall.phone);  // �ִ� 29���ڱ����� �Է¹޵��� ����
    if (strlen(human.NumOrCall.phone) >= 30) {
        printf("��ȭ��ȣ/�ֹι�ȣ �Է� ����: �ִ� 29���ڱ��� �Է��ϼ���.\n");
        return 1;
    }

    printf("\n--- ����ü/����ü ȥ�� ��� ---\n");
    printf("�̸� ==> %s\n", human.name);
    printf("��ȭ��ȣ/�ֹι�ȣ ==> %s\n", human.NumOrCall.phone);

    return 0;
}