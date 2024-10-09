#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void)
{
    int arr[4][8] = {0}; // 4행 8열의 배열을 0으로 초기화
    printf("첫번째 행을 입력하시오: ");

    // 첫번째 행 입력
    for (int i = 0; i < 8; i++)
    {
        scanf("%d", &arr[0][i]);
        if (arr[0][i] <= 0)
        {
            printf("0 또는 음수는 입력하면 안됩니다.\n");
            return 0;
        }
    }

    // 첫번째 행의 인접한 값을 두번째 행에 넣기
    for (int j = 0; j < 8; j += 2)
    {
        // arr[1][j] = arr[0][j] + arr[0][j + 1];  // 짝수 인덱스에 합계 저장
        *(*(arr + 1) + j) = *(*(arr) + j) + *(*(arr) + j + 1);
    }

    // 두번째 행의 인접한 값을 세번째 행에 넣기
    for (int z = 1; z < 3; z++)
    { // 두번째와 세번째 행에 대해 반복
        for (int i = 0; i < 8; i++)
        {
            if (*(*(arr + z) + i) != 0)
            { // 0이 아닌 경우에만
                for (int j = i + 1; j < 8; j++)
                {
                    if (*(*(arr + z) + j) != 0)
                    { // 다음 0이 아닌 요소를 찾음
                        // arr[z + 1][i] = arr[z][i] + arr[z][j];  // 합산하여 저장
                        *(*(arr + z + 1) + i) = *(*(arr + z) + i) + *(*(arr + z) + j);
                        i = j; // 인덱스를 업데이트하여 중복 사용 방지
                        break; // 값을 찾으면 루프 종료
                    }
                }
            }
        }
    }

    // 결과 출력
    for (int z = 0; z < 4; z++)
    {
        for (int k = 0; k < 8; k++)
        {
            printf("%d ", *(*(arr + z) + k));
        }
        printf("\n");
    }

    return 0;
}