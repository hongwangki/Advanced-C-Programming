#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
int main(void)
{
	int count;	 // 숫자를 입력할 갯수
	int sum = 0; // 입력한 짝 수 합을 계산할 sum
	printf("입력할 개수는 ? ");
	scanf("%d", &count); // 숫자 입력

	int *p;
	p = (int *)malloc(sizeof(int) * count);

	// 메모리 할당 실패 시 처리
	if (p == NULL)
	{
		printf("메모리 할당에 실패했습니다.\n");
		return 1; // 프로그램 종료
	}

	for (int i = 0; i < count; i++)
	{
		printf("%d 번째 숫자 : ", i + 1);
		scanf("%d", &p[i]);
		if (p[i] % 2 == 0)
		{ // 입력 값이 짝수면 sum에 더하기
			sum += p[i];
		}
	}
	printf("입력한 짝수합==> %d\n", sum);

	// 메모리 할당 취소
	free(p);
	return 0;
}