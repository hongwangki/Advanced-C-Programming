#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE *Fw;
	int dan;
	char filename[20];

	printf("����ϰ� ���� ���� �Է� : ");
	scanf("%d", &dan);
	sprintf(filename, "%d_dan.txt", dan); //copy filename
	Fw=fopen(filename, "w");

	// output printf -> file
	for (int i = 1; i <= 9; i++) {
		fprintf(Fw, "%d X %d = %d\n", dan, i, dan * i);
	}
	printf("%d_dan.txt�� ����� ����\n",dan);

	//close file
	fclose(Fw);
}