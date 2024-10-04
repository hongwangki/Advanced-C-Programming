#define _CRT_SECURE_NO_WARNINGS
#include <stdbool.h>
#include <stdio.h>

int VIPseat[3] = {301, 302, 303};           // VIP 여석
int GENseat[5] = {201, 202, 203, 204, 205}; // 일반실 여석

int vip_count = 3; // VIP 잔여 방 수
int gen_count = 5; // 일반실 잔여 방 수

// VIP룸 예약 함수
bool vip_check(int person)
{
    if (vip_count > 0)
    {
        int required_rooms = (person + 3) / 4; // 필요한 VIP 방 수
        if (vip_count >= required_rooms)
        {
            printf("VIP룸 ");
            for (int i = 0; i < required_rooms; i++)
            {
                printf("%d ", VIPseat[vip_count - 1]); // 방 번호 출력
                vip_count--;                           // 방 하나 줄이기
            }
            printf("호가 예약되었습니다.\n");
            printf("잔여 VIP room 갯수: %d\n\n", vip_count);
            return true;
        }
        else
        {
            printf("VIP룸이 부족하여 예약이 불가능합니다.\n\n");
            return false;
        }
    }
    else
    {
        printf("VIP룸이 방이 없어 예약이 불가능합니다.\n\n");
        return false;
    }
}

// 일반실 예약 함수
bool normal_check(int person)
{
    if (gen_count > 0)
    {
        int required_rooms = (person + 3) / 4; // 필요한 일반실 방 수
        if (gen_count >= required_rooms)
        {
            printf("일반룸 ");
            for (int i = 0; i < required_rooms; i++)
            {
                printf("%d ", GENseat[gen_count - 1]); // 방 번호 출력
                gen_count--;                           // 방 하나 줄이기
            }
            printf("호가 예약되었습니다.\n");
            printf("잔여 일반 room 갯수: %d\n\n", gen_count);
            return true;
        }
        else
        {
            printf("일반룸이 부족하여 예약이 불가능합니다.\n\n");
            return false;
        }
    }
    else
    {
        printf("일반룸이 방이 없어 예약이 불가능합니다.\n\n");
        return false;
    }
}

// 객실 예약 함수
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
        printf("잘못 입력하였습니다\n");
    }
}

int main(void)
{
    int person; // 예약받을 인원 변수
    int type;   // 객실 타입 변수

    for (int i = 0; i < 5; i++)
    {
        printf("예약 요청을 안내에 따라 해주세요:\n");

        printf("사람은 몇 명이나요? : ");
        scanf("%d", &person);
        printf("객실 유형은 무엇인가요?(VIP Room=0, 일반 룸=1) : ");
        scanf("%d", &type);

        reservation_hotel(person, type);
    }

    return 0;
}