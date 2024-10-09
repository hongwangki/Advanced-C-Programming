#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>

int VIPseat[3] = {301, 302, 303};           // VIP ����
int GENseat[5] = {201, 202, 203, 204, 205}; // �Ϲݽ� ����

int vip_count = 3; // VIP �ܿ� �� ��
int gen_count = 5; // �Ϲݽ� �ܿ� �� ��

// VIP�� ���� �Լ�
bool vip_check(int person)
{
    if (vip_count > 0)
    {
        int required_rooms = (person + 3) / 4; // �ʿ��� VIP �� ��
        if (vip_count >= required_rooms)
        {
            printf("VIP�� ");
            for (int i = 0; i < required_rooms; i++)
            {
                printf("%d ", VIPseat[vip_count - 1]); // �� ��ȣ ���
                vip_count--;                           // �� �ϳ� ���̱�
            }
            printf("ȣ�� ����Ǿ����ϴ�.\n");
            printf("�ܿ� VIP room ����: %d\n\n", vip_count);
            return true;
        }
        else
        {
            printf("VIP���� �����Ͽ� ������ �Ұ����մϴ�.\n\n");
            return false;
        }
    }
    else
    {
        printf("VIP���� ���� ���� ������ �Ұ����մϴ�.\n\n");
        return false;
    }
}

// �Ϲݽ� ���� �Լ�
bool normal_check(int person)
{
    if (gen_count > 0)
    {
        int required_rooms = (person + 3) / 4; // �ʿ��� �Ϲݽ� �� ��
        if (gen_count >= required_rooms)
        {
            printf("�Ϲݷ� ");
            for (int i = 0; i < required_rooms; i++)
            {
                printf("%d ", GENseat[gen_count - 1]); // �� ��ȣ ���
                gen_count--;                           // �� �ϳ� ���̱�
            }
            printf("ȣ�� ����Ǿ����ϴ�.\n");
            printf("�ܿ� �Ϲ� room ����: %d\n\n", gen_count);
            return true;
        }
        else
        {
            printf("�Ϲݷ��� �����Ͽ� ������ �Ұ����մϴ�.\n\n");
            return false;
        }
    }
    else
    {
        printf("�Ϲݷ��� ���� ���� ������ �Ұ����մϴ�.\n\n");
        return false;
    }
}

// ���� ���� �Լ�
void reservation_hotel(int person, int type)
{
    if (type == 0)
    {
        vip_check(person);
    }
    else if (type == 1)
    {
        normal_check(person);
    }
    else
    {
        printf("�߸� �Է��Ͽ����ϴ�\n");
    }
}

int main(void)
{
    int person; // ������� �ο� ����
    int type;   // ���� Ÿ�� ����

    for (int i = 0; i < 5; i++)
    {
        printf("���� ��û�� �ȳ��� ���� ���ּ���:\n");

        printf("����� �� ���̳���? : ");
        scanf("%d", &person);
        printf("���� ������ �����ΰ���?(VIP Room=0, �Ϲ� ��=1) : ");
        scanf("%d", &type);

        reservation_hotel(person, type);
    }

    return 0;
}