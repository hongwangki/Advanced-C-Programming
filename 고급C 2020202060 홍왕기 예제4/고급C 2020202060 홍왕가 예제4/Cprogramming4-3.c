#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h> // getline ����� ���� �ʿ�

int main(void)
{
	char *c[3];
	char tmp[100]; // �ӽ÷� �Է¹��� �迭
	for (int i = 0; i < 3; i++)
	{
		printf("%d �� ° ���ڿ� ", i + 1);
		fgets(tmp, sizeof(tmp), stdin); // ���ڿ� �Է� �ޱ�

		// ���� ���� ����
		tmp[strcspn(tmp, "\n")] = '\0';

		int size = strlen(tmp); // �Էµ� ���ڿ� ������ ���

		c[i] = (char *)malloc(sizeof(char) * (size + 1)); // �Էµ� ���� + \0

		strcpy(c[i], tmp); // c[i]�� tmp����
	}

	printf("\n\n-- �Է°� �ݴ�� ���(������): ���� ������ �Ųٷ� --\n");

	// �ݺ��Ͽ� ���
	for (int i = 2; i >= 0; i--)
	{
		printf("%d : ", i + 1);
		// ���� ���������� ù��°���� ���
		for (int j = strlen(c[i]); j > 0; j--)
		{
			printf("%c", c[i][j - 1]);
		}
		printf("\n");
	}
	// �޸� ����
	for (int i = 0; i < 3; i++)
	{
		free(c[i]);
	}
	return 0;
}
