#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Human {
	char name[20];
	int age;
};

int main() {
	int count;

	printf("�Է��� �л� �� ");
	scanf("%d", &count);

	//p malloc count arr make
	struct Human* p;
	p = (struct Human*)malloc(sizeof(struct Human) * count);

	//input name and age
	for (int i = 0; i < count; i++) {
		printf("�̸��� ���� �Է� : ");
		scanf("%s %d", p[i].name, &p[i].age);
	}

	printf("-- �л� ��� --\n");


	//print all Human
	for (int i = 0; i < count; i++) {
		printf("�̸�:%s, ����:%d\n",p[i].name,p[i].age);

	}
	
	free(p);


}