#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE *Fw;
	int dan;
	char filename[20];

	printf("출력하고 싶은 단을 입력 : ");
	scanf("%d", &dan);
	sprintf(filename, "%d_dan.txt", dan); //copy filename
	Fw=fopen(filename, "w");

	// output printf -> file
	for (int i = 1; i <= 9; i++) {
		fprintf(Fw, "%d X %d = %d\n", dan, i, dan * i);
	}
	printf("%d_dan.txt에 결과를 저장\n",dan);

	//close file
	fclose(Fw);
}