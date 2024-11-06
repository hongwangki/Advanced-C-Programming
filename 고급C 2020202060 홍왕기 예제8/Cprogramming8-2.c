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

	printf("입력할 학생 수 ");
	scanf("%d", &count);

	//p malloc count arr make
	struct Human* p;
	p = (struct Human*)malloc(sizeof(struct Human) * count);

	//input name and age
	for (int i = 0; i < count; i++) {
		printf("이름과 나이 입력 : ");
		scanf("%s %d", p[i].name, &p[i].age);
	}

	printf("-- 학생 명단 --\n");


	//print all Human
	for (int i = 0; i < count; i++) {
		printf("이름:%s, 나이:%d\n",p[i].name,p[i].age);

	}
	
	free(p);


}