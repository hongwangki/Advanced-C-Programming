#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int main(void)
{
	char *c[3];
	char tmp1[100]; // �ӽ� �迭 ���� tmp
	char tmp2[100];

	// ù ��° ���ڿ� �Է�
	printf("ù ��° ���ڿ��� �Է��Ͻÿ�: ");
	fgets(tmp1, sizeof(tmp1), stdin);
	// ���� ���� ����
	tmp1[strcspn(tmp1, "\n")] = '\0';

	// �� ��° ���ڿ� �Է�
	printf("�� ��° ���ڿ��� �Է��Ͻÿ�: ");
	fgets(tmp2, sizeof(tmp2), stdin);
	// ���� ���� ����
	tmp2[strcspn(tmp2, "\n")] = '\0';

	// ù��° ���ڿ� ���̸�ŭ �����Ҵ� �� ����
	int size0 = strlen(tmp1);
	c[0] = (char *)malloc(sizeof(char) * (size0 + 1));
	strcpy(c[0], tmp1);

	// �ι�° ���ڿ� ���̸�ŭ �����Ҵ� �� ����
	int size1 = strlen(tmp2);
	c[1] = (char *)malloc(sizeof(char) * (size1 + 1));
	strcpy(c[1], tmp2);

	// ù��° �ι�° �տ� ���̸�ŭ �����Ҵ� �� ����

	c[2] = (char *)malloc(sizeof(char) * (size1 + size0 + 1));

	// �� ���ڿ��� ������ c[2]�� ����
	strcpy(c[2], tmp1); // c[2]�� tmp1 ����
	strcat(c[2], tmp2); // c[2]�� tmp2 �߰�

	// ���
	for (int i = 0; i < 3; i++)
	{
		printf(" %d��° ���ڿ� : ", i + 1);
		printf("%s\n", c[i]);
	}

	// �޸� ����
	for (int i = 0; i < 3; i++)
	{
		free(c[i]);
	}
}