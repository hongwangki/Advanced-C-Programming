#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <malloc.h>
int main(void)
{
	int count;	 // ���ڸ� �Է��� ����
	int sum = 0; // �Է��� ¦ �� ���� ����� sum
	printf("�Է��� ������ ? ");
	scanf("%d", &count); // ���� �Է�

	int *p;
	p = (int *)malloc(sizeof(int) * count);

	// �޸� �Ҵ� ���� �� ó��
	if (p == NULL)
	{
		printf("�޸� �Ҵ翡 �����߽��ϴ�.\n");
		return 1; // ���α׷� ����
	}

	for (int i = 0; i < count; i++)
	{
		printf("%d ��° ���� : ", i + 1);
		scanf("%d", &p[i]);
		if (p[i] % 2 == 0)
		{ // �Է� ���� ¦���� sum�� ���ϱ�
			sum += p[i];
		}
	}
	printf("�Է��� ¦����==> %d\n", sum);

	// �޸� �Ҵ� ���
	free(p);
	return 0;
}