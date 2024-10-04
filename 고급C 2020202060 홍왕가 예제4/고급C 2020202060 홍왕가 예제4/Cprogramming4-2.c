#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // malloc, free 함수가 정의된 헤더

int main(void)
{
	int *p = NULL;
	int sum = 0;
	int i = 0;
	int num;
	while (1)
	{
		printf("수를 입력하시오 : (0이면 종료) ");
		scanf("%d", &num);

		if (num == 0)
		{
			break;
		}

		// i=0 이면 처음 할당이므로 malloc로 동적할당
		if (i == 0)
		{
			p = (int *)malloc(sizeof(int) * 1);
		}
		// 아니면 realloc로 추가 공간 생성
		else
		{
			p = (int *)realloc(p, sizeof(int) * (i + 1));
		}

		if (p == NULL)
		{
			// 메모리 할당 실패 시 오류 처리
			printf("메모리 할당 실패\n");
			return 1;
		}

		p[i] = num; // 입력된 숫자를 배열에 저장

		// p[i]가 2에 짝수이면 sum에 더함
		if (p[i] % 2 == 0)
		{
			sum += p[i];
		}
		i++;
	}
	printf("입력한 짝수합==> %d\n", sum);
	if (p != NULL)
	{
		free(p); // 동적 메모리 해제
	}
	return 0;
}