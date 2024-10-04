#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // malloc, free �Լ��� ���ǵ� ���

int main(void)
{
	int *p = NULL;
	int sum = 0;
	int i = 0;
	int num;
	while (1)
	{
		printf("���� �Է��Ͻÿ� : (0�̸� ����) ");
		scanf("%d", &num);

		if (num == 0)
		{
			break;
		}

		// i=0 �̸� ó�� �Ҵ��̹Ƿ� malloc�� �����Ҵ�
		if (i == 0)
		{
			p = (int *)malloc(sizeof(int) * 1);
		}
		// �ƴϸ� realloc�� �߰� ���� ����
		else
		{
			p = (int *)realloc(p, sizeof(int) * (i + 1));
		}

		if (p == NULL)
		{
			// �޸� �Ҵ� ���� �� ���� ó��
			printf("�޸� �Ҵ� ����\n");
			return 1;
		}

		p[i] = num; // �Էµ� ���ڸ� �迭�� ����

		// p[i]�� 2�� ¦���̸� sum�� ����
		if (p[i] % 2 == 0)
		{
			sum += p[i];
		}
		i++;
	}
	printf("�Է��� ¦����==> %d\n", sum);
	if (p != NULL)
	{
		free(p); // ���� �޸� ����
	}
	return 0;
}