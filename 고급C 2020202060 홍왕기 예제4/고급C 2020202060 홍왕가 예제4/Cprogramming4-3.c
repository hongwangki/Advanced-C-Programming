#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // getline 사용을 위해 필요

int main(void)
{
	char *c[3];
	char tmp[100]; // 임시로 입력받을 배열
	for (int i = 0; i < 3; i++)
	{
		printf("%d 번 째 문자열 ", i + 1);
		fgets(tmp, sizeof(tmp), stdin); // 문자열 입력 받기

		// 개행 문자 제거
		tmp[strcspn(tmp, "\n")] = '\0';

		int size = strlen(tmp); // 입력된 문자열 사이즈 계산

		c[i] = (char *)malloc(sizeof(char) * (size + 1)); // 입력된 길이 + \0

		strcpy(c[i], tmp); // c[i]에 tmp복사
	}

	printf("\n\n-- 입력과 반대로 출력(포인터): 글자 순서도 거꾸로 --\n");

	// 반복하여 출력
	for (int i = 2; i >= 0; i--)
	{
		printf("%d : ", i + 1);
		// 글자 마지막부터 첫번째까지 출력
		for (int j = strlen(c[i]); j > 0; j--)
		{
			printf("%c", c[i][j - 1]);
		}
		printf("\n");
	}
	// 메모리 해제
	for (int i = 0; i < 3; i++)
	{
		free(c[i]);
	}
	return 0;
}
