#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int CardCount = 0;
; // ī�� ���� ��������
int userCardCount = 0;
int dealerCardCount = 0;

int *User = NULL;	// ����� ī�� ��������
int *Dealer = NULL; // ���� ī�� ��������
int *Card = NULL;

int Usersum = 0;
int DealerSum = 0;

int *Shuffle()
{
	int *Card = (int *)malloc(sizeof(int) * (20)); // ī�� 20��� \0���ڿ� ���� �迭 ����
	int count[14] = {
		0,
	}; // 0��� x
	srand(time(NULL));
	int i = 0;
	// ī�� ������ ����
	while (i < 20)
	{
		int x = (rand() % 13) + 1; // 1~13���� ���� ���� 11=j 12=q 13=k
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
			printf("%d ", User[i]); // 1~10������ ���ڷ� ���
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
			printf("%d ", Dealer[i]); // 1~10������ ���ڷ� ���
		}
	}
	printf("\n");
}

void Hit(int **User, int **Dealer, int *Card, int index)
{
	// index�� 1�̸� ���� ī�� ���� ����
	if (index == 1)
	{
		*User = (int *)realloc(*User, sizeof(int) * (userCardCount + 1));
		(*User)[userCardCount] = Card[CardCount];
		userCardCount++;
	}
	// �ƴϸ� �������� ����
	else
	{
		*Dealer = (int *)realloc(*Dealer, sizeof(int) * (dealerCardCount + 1));
		(*Dealer)[dealerCardCount] = Card[CardCount];
		dealerCardCount++;
	}
	// ī�� ���� ����
	CardCount++;
}

void End(int **Dealer)
{
	DealerSum = 0;
	for (int i = 0; i < dealerCardCount; i++)
	{
		if ((*Dealer)[i] == 11 || (*Dealer)[i] == 12 || (*Dealer)[i] == 13)
		{
			DealerSum += 10; // J, Q, K�� ������ 10���� ó��
		}
		else
		{
			DealerSum += (*Dealer)[i]; // �Ϲ� ī���� ���� �߰�
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
	{ // ���� ���� �� ��� Ȯ��
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
	{ // Hit �� ���� Ȯ��
		if (Usersum > 21)
		{
			printf("Busted! Over 21! Dealer Wins\n");
		}
	}
}
int CalculateSum(int *cards, int cardCount)
{
	int sum = 0;
	int aceCount = 0; // Ace�� �ִ��� üũ

	for (int i = 0; i < cardCount; i++)
	{
		if (cards[i] >= 11 && cards[i] <= 13)
		{
			sum += 10; // J, Q, K�� 10���� ���
		}
		else if (cards[i] == 1)
		{
			aceCount++; // Ace�� ���߿� ó��
			sum += 11;	// �ϴ� 11�� ó��
		}
		else
		{
			sum += cards[i];
		}
	}

	// Ace�� 1�� �ٲ�� �ϴ� ��Ȳ üũ (���� 21�� ������ Ace�� 1�� ó��)
	while (sum > 21 && aceCount > 0)
	{
		sum -= 10; // Ace�� 1�� ó��
		aceCount--;
	}

	return sum;
}

// ������ ���� �� �޸� ������
void ResetGame(int **User, int **Dealer)
{
	int *tempUser = (int *)realloc(*User, 2 * sizeof(int));
	if (tempUser == NULL)
	{
		printf("Memory reallocation failed for User reset\n");
		exit(1); // �޸� ���Ҵ� ���� �� ���α׷� ����
	}
	*User = tempUser;

	int *tempDealer = (int *)realloc(*Dealer, 2 * sizeof(int));
	if (tempDealer == NULL)
	{
		printf("Memory reallocation failed for Dealer reset\n");
		exit(1); // �޸� ���Ҵ� ���� �� ���α׷� ����
	}
	*Dealer = tempDealer;

	// ī�� ���� �ʱ�ȭ
	userCardCount = 2;
	dealerCardCount = 2;
}

int main(void)
{
	char start[100]; // Start ���ο� ���� char �迭 ����

	// �⺻ �� �� �� �Ҵ�
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

			Card = Shuffle();					// Shuffle �Լ� ȣ���Ͽ� ī�� �迭 �޾ƿ�
			Initialization(User, Dealer, Card); // ī�� �� �徿 ����
			Status(User, Dealer);				// ���� ī�� ��Ȳ ���

			while (1)
			{
				char check[10]; // Hit ���θ� �˱� ���� �迭
				printf("More Card? ");
				scanf("%s", check);

				// �Էµ� ���ڿ� ���� Ȯ��
				if (strlen(check) > 9)
				{ // 10���� �̻��� ���
					printf("Error: Input exceeded 10 characters!\n");
					return 1;
				}

				if (strcmp(check, "Hit") == 0)
				{
					Hit(&User, &Dealer, Card, 1);
					Usersum = CalculateSum(User, userCardCount); // Hit �� �հ� ���
					Status(User, Dealer);						 // Hit �� ī�� ��Ȳ ���

					if (Usersum > 21)
					{
						break; // �÷��̾ 21�� ������ ���� ����
					}
				}
				else if (strcmp(check, "Stay") == 0)
				{
					while (DealerSum < 17)
					{													   // ������ 17 �̸��� �� ī�带 �� ����
						End(&Dealer);									   // ���� ī�� ó��
						DealerSum = CalculateSum(Dealer, dealerCardCount); // ���� �հ� ���
						Status(User, Dealer);							   // ������ Stay�� ��� ���� ���
					}
					break; // Stay�� �Է��ϸ� ���� ���� �� ����� �Ѿ
				}
				else
				{
					printf("Error: Wrong Input, Try Again.\n");
				}
			}

			// ���� ���� �� ��� ��� �� �޸� ����
			Result(&User, &Dealer, 1); // ��� ���
			free(Card);
			// ���� ����
			ResetGame(&User, &Dealer); // �迭 ũ�⸦ 2�� �ٿ� �ʱ�ȭ
		}
		else if (strcmp(start, "End") == 0)
		{
			break; // ���� ����
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