#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int CardCount = 0;
; // 카드 수량 전역변수
int userCardCount = 0;
int dealerCardCount = 0;

int *User = NULL;	// 사용자 카드 전역변수
int *Dealer = NULL; // 딜러 카드 전역변수
int *Card = NULL;

int Usersum = 0;
int DealerSum = 0;

int *Shuffle()
{
	int *Card = (int *)malloc(sizeof(int) * (20)); // 카드 20장과 \0문자에 대한 배열 생성
	int count[14] = {
		0,
	}; // 0사용 x
	srand(time(NULL));
	int i = 0;
	// 카드 무작위 생성
	while (i < 20)
	{
		int x = (rand() % 13) + 1; // 1~13까지 난수 생성 11=j 12=q 13=k
		if (count[x] < 4)
		{
			count[x] += 1;
			Card[i] = x;
			i++;
		}
	}
	return Card;
}

void Initialization(int *User, int *Dealer, int *Card)
{
	int j = 0;
	for (int i = 0; i < 2; i++)
	{
		User[i] = Card[i + j];
		Dealer[i] = Card[i + 1 + j];
		j++;
	}

	CardCount += 4;
	userCardCount += 2;
	dealerCardCount += 2;
}

void Status(int *User, int *Dealer)
{
	printf("User: ");
	for (int i = 0; i < userCardCount; i++)
	{
		if (User[i] == 11)
		{
			printf("J ");
		}
		else if (User[i] == 12)
		{
			printf("Q ");
		}
		else if (User[i] == 13)
		{
			printf("K ");
		}
		else
		{
			printf("%d ", User[i]); // 1~10까지는 숫자로 출력
		}
	}

	printf("\nDealer: ");
	for (int i = 0; i < dealerCardCount; i++)
	{
		if (Dealer[i] == 11)
		{
			printf("J ");
		}
		else if (Dealer[i] == 12)
		{
			printf("Q ");
		}
		else if (Dealer[i] == 13)
		{
			printf("K ");
		}
		else
		{
			printf("%d ", Dealer[i]); // 1~10까지는 숫자로 출력
		}
	}
	printf("\n");
}

void Hit(int **User, int **Dealer, int *Card, int index)
{
	// index가 1이면 유저 카드 한장 증가
	if (index == 1)
	{
		*User = (int *)realloc(*User, sizeof(int) * (userCardCount + 1));
		(*User)[userCardCount] = Card[CardCount];
		userCardCount++;
	}
	// 아니면 딜러에게 증가
	else
	{
		*Dealer = (int *)realloc(*Dealer, sizeof(int) * (dealerCardCount + 1));
		(*Dealer)[dealerCardCount] = Card[CardCount];
		dealerCardCount++;
	}
	// 카드 갯수 증가
	CardCount++;
}

void End(int **Dealer)
{
	DealerSum = 0;
	for (int i = 0; i < dealerCardCount; i++)
	{
		if ((*Dealer)[i] == 11 || (*Dealer)[i] == 12 || (*Dealer)[i] == 13)
		{
			DealerSum += 10; // J, Q, K의 점수를 10으로 처리
		}
		else
		{
			DealerSum += (*Dealer)[i]; // 일반 카드의 점수 추가
		}
	}
	if (DealerSum < 17)
	{
		Hit(&User, Dealer, Card, 2);
	}
}

void Result(int **User, int **Dealer, int mode)
{
	Usersum = CalculateSum(*User, userCardCount);
	DealerSum = CalculateSum(*Dealer, dealerCardCount);

	if (mode == 1)
	{ // 게임 종료 시 결과 확인
		if (Usersum >= 21)
		{
			printf("Busted! Over 21! Dealer Wins\n");
		}
		else if (DealerSum >= 21)
		{
			printf("Dealer Busted! User Wins\n");
		}
		else if (Usersum > DealerSum)
		{
			printf("User Wins!\n");
		}
		else if (Usersum < DealerSum)
		{
			printf("Dealer Wins!\n");
		}
		else
		{
			printf("Draw!\n");
		}
	}
	else if (mode == 2)
	{ // Hit 후 상태 확인
		if (Usersum > 21)
		{
			printf("Busted! Over 21! Dealer Wins\n");
		}
	}
}
int CalculateSum(int *cards, int cardCount)
{
	int sum = 0;
	int aceCount = 0; // Ace가 있는지 체크

	for (int i = 0; i < cardCount; i++)
	{
		if (cards[i] >= 11 && cards[i] <= 13)
		{
			sum += 10; // J, Q, K는 10으로 계산
		}
		else if (cards[i] == 1)
		{
			aceCount++; // Ace는 나중에 처리
			sum += 11;	// 일단 11로 처리
		}
		else
		{
			sum += cards[i];
		}
	}

	// Ace를 1로 바꿔야 하는 상황 체크 (합이 21을 넘으면 Ace를 1로 처리)
	while (sum > 21 && aceCount > 0)
	{
		sum -= 10; // Ace를 1로 처리
		aceCount--;
	}

	return sum;
}

// 게임이 끝난 후 메모리 재조정
void ResetGame(int **User, int **Dealer)
{
	int *tempUser = (int *)realloc(*User, 2 * sizeof(int));
	if (tempUser == NULL)
	{
		printf("Memory reallocation failed for User reset\n");
		exit(1); // 메모리 재할당 실패 시 프로그램 종료
	}
	*User = tempUser;

	int *tempDealer = (int *)realloc(*Dealer, 2 * sizeof(int));
	if (tempDealer == NULL)
	{
		printf("Memory reallocation failed for Dealer reset\n");
		exit(1); // 메모리 재할당 실패 시 프로그램 종료
	}
	*Dealer = tempDealer;

	// 카드 개수 초기화
	userCardCount = 2;
	dealerCardCount = 2;
}

int main(void)
{
	char start[100]; // Start 여부에 대한 char 배열 선언

	// 기본 패 두 장 할당
	User = (int *)malloc(2 * sizeof(int));
	Dealer = (int *)malloc(2 * sizeof(int));

	while (1)
	{
		printf("Game Start? ");
		scanf("%s", start);

		if (strcmp(start, "Start") == 0)
		{
			CardCount = 0;
			userCardCount = 0;
			dealerCardCount = 0;
			Usersum = 0;
			DealerSum = 0;

			Card = Shuffle();					// Shuffle 함수 호출하여 카드 배열 받아옴
			Initialization(User, Dealer, Card); // 카드 두 장씩 제공
			Status(User, Dealer);				// 현재 카드 상황 출력

			while (1)
			{
				char check[10]; // Hit 여부를 알기 위한 배열
				printf("More Card? ");
				scanf("%s", check);

				// 입력된 문자열 길이 확인
				if (strlen(check) > 9)
				{ // 10글자 이상일 경우
					printf("Error: Input exceeded 10 characters!\n");
					return 1;
				}

				if (strcmp(check, "Hit") == 0)
				{
					Hit(&User, &Dealer, Card, 1);
					Usersum = CalculateSum(User, userCardCount); // Hit 후 합계 계산
					Status(User, Dealer);						 // Hit 후 카드 상황 출력

					if (Usersum > 21)
					{
						break; // 플레이어가 21을 넘으면 게임 종료
					}
				}
				else if (strcmp(check, "Stay") == 0)
				{
					while (DealerSum < 17)
					{													   // 딜러가 17 미만일 때 카드를 더 받음
						End(&Dealer);									   // 딜러 카드 처리
						DealerSum = CalculateSum(Dealer, dealerCardCount); // 딜러 합계 계산
						Status(User, Dealer);							   // 딜러가 Stay인 경우 상태 출력
					}
					break; // Stay를 입력하면 게임 종료 후 결과로 넘어감
				}
				else
				{
					printf("Error: Wrong Input, Try Again.\n");
				}
			}

			// 게임 종료 후 결과 출력 및 메모리 해제
			Result(&User, &Dealer, 1); // 결과 출력
			free(Card);
			// 게임 리셋
			ResetGame(&User, &Dealer); // 배열 크기를 2로 줄여 초기화
		}
		else if (strcmp(start, "End") == 0)
		{
			break; // 게임 종료
		}
		else
		{
			printf("Error: Wrong Input, Try Again.\n");
		}
	}
	free(User);
	free(Dealer);
	return 0;
}