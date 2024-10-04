#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

char arr[100]; // 문자열 배열
char name[20]; // 정렬 방식을 저장할 배열 (오름차순/내림차순)

void input_char();
void func_sort(char arr[], char name[]);
void func_print(char arr[]);

void input_char()
{
    printf("문자열 최대 100개를 입력하시오: ");
    // 공백을 포함한 문자열을 받기 위해 %99[^\n] 형식을 사용
    scanf("%99[^\n]", arr);
    getchar(); // 버퍼에 남은 개행 문자 제거

    printf("정렬 방식을 입력하시오 (오름차순/내림차순): ");
    scanf("%19s", name); // 정렬 방식 입력
}

void func_sort(char arr[], char name[])
{
    int length = strlen(arr); // 문자열 길이 계산
    char temp;

    if (strncmp(name, "내림차순", 4) == 0)
    {
        // 내림차순 정렬 코드
        for (int i = 0; i < length - 1; i++)
        {
            for (int j = i + 1; j < length; j++)
            {
                if (arr[i] < arr[j])
                { // 내림차순 조건
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
    else if (strncmp(name, "오름차순", 4) == 0)
    {
        // 오름차순 정렬 코드
        for (int i = 0; i < length - 1; i++)
        {
            for (int j = i + 1; j < length; j++)
            {
                if (arr[i] > arr[j])
                { // 오름차순 조건
                    temp = arr[i];
                    arr[i] = arr[j];
                    arr[j] = temp;
                }
            }
        }
    }
    else
    {
        printf("잘못된 정렬 방식입니다.\n");
    }
}

void func_print(char arr[])
{
    printf("정렬된 문자열: %s\n", arr);
}

int main(void)
{
    input_char();         // 사용자 입력 받기
    func_sort(arr, name); // 입력받은 문자열과 정렬 방식으로 정렬 수행
    func_print(arr);      // 정렬된 결과 출력
    return 0;
}