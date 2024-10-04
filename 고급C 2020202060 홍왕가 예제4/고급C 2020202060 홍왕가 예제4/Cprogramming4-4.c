#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	char *c[3];
	char tmp1[100]; // 임시 배열 공간 tmp
	char tmp2[100];

	// 첫 번째 문자열 입력
	printf("첫 번째 문자열을 입력하시오: ");
	fgets(tmp1, sizeof(tmp1), stdin);
	// 개행 문자 제거
	tmp1[strcspn(tmp1, "\n")] = '\0';

	// 두 번째 문자열 입력
	printf("두 번째 문자열을 입력하시오: ");
	fgets(tmp2, sizeof(tmp2), stdin);
	// 개행 문자 제거
	tmp2[strcspn(tmp2, "\n")] = '\0';

	// 첫번째 문자열 길이만큼 동적할당 후 복사
	int size0 = strlen(tmp1);
	c[0] = (char *)malloc(sizeof(char) * (size0 + 1));
	strcpy(c[0], tmp1);

	// 두번째 문자열 길이만큼 동적할당 후 복사
	int size1 = strlen(tmp2);
	c[1] = (char *)malloc(sizeof(char) * (size1 + 1));
	strcpy(c[1], tmp2);

	// 첫번째 두번째 합에 길이만큼 동적할당 후 복사

	c[2] = (char *)malloc(sizeof(char) * (size1 + size0 + 1));

	// 두 문자열을 붙히고 c[2]에 저장
	strcpy(c[2], tmp1); // c[2]에 tmp1 복사
	strcat(c[2], tmp2); // c[2]에 tmp2 추가

	// 출력
	for (int i = 0; i < 3; i++)
	{
		printf(" %d번째 문자열 : ", i + 1);
		printf("%s\n", c[i]);
	}

	// 메모리 헤제
	for (int i = 0; i < 3; i++)
	{
		free(c[i]);
	}
}