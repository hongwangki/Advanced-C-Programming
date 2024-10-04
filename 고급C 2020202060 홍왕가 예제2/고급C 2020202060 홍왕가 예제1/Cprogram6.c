#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

char arr[100]; // ���ڿ� �迭
char name[20]; // ���� ����� ������ �迭 (��������/��������)

void input_char();
void func_sort(char arr[], char name[]);
void func_print(char arr[]);

void input_char()
{
    printf("���ڿ� �ִ� 100���� �Է��Ͻÿ�: ");
    // ������ ������ ���ڿ��� �ޱ� ���� %99[^\n] ������ ���
    scanf("%99[^\n]", arr);
    getchar(); // ���ۿ� ���� ���� ���� ����

    printf("���� ����� �Է��Ͻÿ� (��������/��������): ");
    scanf("%19s", name); // ���� ��� �Է�
}

void func_sort(char arr[], char name[])
{
    int length = strlen(arr); // ���ڿ� ���� ���
    char temp;

    if (strncmp(name, "��������", 4) == 0)
    {
        // �������� ���� �ڵ�
        for (int i = 0; i < length - 1; i++)
        {
            for (int j = i + 1; j < length; j++)
            {
                if (arr[i] < arr[j])
                { // �������� ����
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
    else if (strncmp(name, "��������", 4) == 0)
    {
        // �������� ���� �ڵ�
        for (int i = 0; i < length - 1; i++)
        {
            for (int j = i + 1; j < length; j++)
            {
                if (arr[i] > arr[j])
                { // �������� ����
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
    else
    {
        printf("�߸��� ���� ����Դϴ�.\n");
    }
}

void func_print(char arr[])
{
    printf("���ĵ� ���ڿ�: %s\n", arr);
}

int main(void)
{
    input_char();         // ����� �Է� �ޱ�
    func_sort(arr, name); // �Է¹��� ���ڿ��� ���� ������� ���� ����
    func_print(arr);      // ���ĵ� ��� ���
    return 0;
}