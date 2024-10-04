#include <stdio.h>
#include <stdlib.h> // rand() �Լ� ���� ���̺귯��
#include <time.h>

// ������������ �����ϴ� �Լ�
void sort_Ascending(int arr[])
{
    // insertion sort �˰���
    int key;
    for (int i = 1; i < 100; i++)
    {
        key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

// ������������ �����ϴ� �Լ�
void sort_Descending(int arr[])
{
    // insertion sort �˰���
    int key;
    for (int i = 1; i < 100; i++)
    {
        key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] < key)
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main(void)
{
    srand(time(NULL)); // ���� �ʱ�ȭ
    int arr[100] = {0};
    int used[100] = {0}; // �ߺ� ���� Ȯ���� ���� �迭
    int temp = 0;

    while (temp < 100)
    {
        int num = rand() % 100; // 0~100 ���� ���� ����
        if (used[num] == 0)
        {                    // �ߺ����� ���� ���ڶ��
            arr[temp] = num; // �迭�� ����
            used[num] = 1;   // �ش� ���ڸ� ����ߴٰ� ǥ��
            temp++;
        }
    }

    // �������� ����
    sort_Ascending(arr);
    printf("���� ���� ����:\n");
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", arr[i]);
    }

    printf("\n\n���� ���� ����: \n");

    // �������� ����
    sort_Descending(arr);
    for (int i = 0; i < 100; i++)
    {
        printf("%d ", arr[i]);
    }

    return 0;
}
