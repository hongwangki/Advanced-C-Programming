#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

void ySymmetry(char arr[4][4], char resultArr[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resultArr[i][j] = arr[i][3 - j]; // y축 대칭으로 복사
        }
    }
}

void xSymmetry(char arr[4][4], char resultArr[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resultArr[i][j] = arr[3 - i][j]; // x축 대칭으로 복사
        }
    }
}

// 원형 대칭을 수행하고 대칭된 배열을 반환하는 함수
void circularSymmetry(char arr[4][4], char resultArr[4][4])
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            resultArr[i][j] = arr[3 - i][3 - j]; // 원형 대칭으로 복사
        }
    }
}

int main(void)
{
    char arr[4][4];
    char resultArr[4][4];

    // 배열을 'O'로 초기화
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            arr[i][j] = 'O';
        }
    }

    int x, y;
    printf(" -2~2 사이 x좌표와 y좌표를 입력하시오 (0 미포함): ");
    scanf("%d %d", &x, &y);

    // 입력 좌표 유효성 검사
    if (!((x < 3 && x > -3) && (y < 3 && y > -3)) || (x == 0 || y == 0))
    {
        printf("좌표를 잘못 입력하였습니다.");
        return 0;
    }

    // 배열 인덱스 조정
    int indexX, indexY;

    switch (x)
    {
    case 2:
        indexY = 3;
        break;
    case 1:
        indexY = 2;
        break;
    case -1:
        indexY = 1;
        break;
    default:
        indexY = 0;
        break;
    }

    switch (y)
    {
    case 2:
        indexX = 0;
        break;
    case 1:
        indexX = 1;
        break;
    case -1:
        indexX = 2;
        break;
    default:
        indexX = 3;
        break;
    }

    // 입력한 좌표에 'X' 표시
    arr[indexX][indexY] = 'X';

    // 배열 출력
    printf("원본 배열:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%c", arr[i][j]);
        }
        printf("\n");
    }

    // x축 대칭 함수 호출
    xSymmetry(arr, resultArr);

    // 대칭 배열 출력
    printf("x 축 대칭 배열:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%c", resultArr[i][j]);
        }
        printf("\n");
    }

    // y축 대칭 함수 호출
    ySymmetry(arr, resultArr);

    // Y축 대칭 배열 출력
    printf("Y 축 대칭 배열:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%c", resultArr[i][j]);
        }
        printf("\n");
    }

    // 원형 대칭 함수 호출
    circularSymmetry(arr, resultArr);
    printf("원형 대칭 배열:\n");
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            printf("%c", resultArr[i][j]);
        }
        printf("\n");
    }

    return 0;
}