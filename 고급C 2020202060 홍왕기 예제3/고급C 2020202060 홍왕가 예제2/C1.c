#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // malloc 사용을 위한 헤더파일

int my_strcmp(char str1[], char str2[])
{
    int i = 0;
    while (str1[i] != '\0' && str2[i] != '\0')
    {
        // str1이 str2보다 큰 경우
        if (str1[i] > str2[i])
        {
            return 1;
        }
        // str2가 str1보다 큰 경우
        else if (str1[i] < str2[i])
        {
            return -1;
        }
        // 같을 경우에는 다음 문자로 넘어감
        i++;
    }

    // 두 문자열이 끝났을 때 길이가 다른 경우 처리
    if (str1[i] == '\0' && str2[i] == '\0')
    {
        return 0; // 두 문자열이 같음
    }
    else if (str1[i] == '\0')
    {
        return -1; // str1이 더 짧음
    }
    else
    {
        return 1; // str2가 더 짧음
    }
}

char *my_strcat(char str1[], char str2[], char resultArr[])
{
    int j = 0;
    for (int i = 0; str1[i] != '\0'; i++)
    {
        resultArr[j++] = str1[i];
    }
    for (int i = 0; str2[i] != '\0'; i++)
    {
        resultArr[j++] = str2[i];
    }
    resultArr[j] = '\0'; // 마지막에 null 문자 추가
    return resultArr;
}

char *my_strcpy(char str[])
{
    int len = 0;

    // 복사할 길이 재기
    while (str[len] != '\0')
    {
        len++;
    }

    // 동적 메모리 할당
    char *newArr = (char *)malloc((len + 1) * sizeof(char));
    if (newArr == NULL)
    { // 메모리 할당 실패 확인
        return NULL;
    }

    // 문자열 복사
    for (int i = 0; i < len; i++)
    {
        newArr[i] = str[i];
    }
    newArr[len] = '\0'; // 널 종료 추가

    return newArr; // 복사한 문자열 반환
}

int my_strlen(char str[])
{
    int len = 0;
    while (str[len] != '\0')
    { // 문자열의 끝에 도달할 때까지 길이를 센다.
        len++;
    }
    return len; // 길이를 반환
}

int main(void)
{
    char str1[10], str2[10], resultArr[12]; // 여유 공간 생성

    printf("5글자 이내의 영어단어 두개를 입력하시오: ");
    scanf("%9s %9s", str1, str2);

    // 5글자 이상 체크
    int len1 = my_strlen(str1);
    int len2 = my_strlen(str2);

    if (len1 > 5 || len2 > 5)
    {
        printf("5자 이내를 입력하여야 합니다.\n");
        return 1; // 5글자 이상일 경우 종료
    }

    // my_strcmp 테스트
    int strcmp = my_strcmp(str1, str2);
    printf("strcmp 반환값은 : %d\n", strcmp);

    char *CatStr = my_strcat(str1, str2, resultArr);
    printf("strcat 반환값은 : %s\n", CatStr);

    char *CpyStr1 = my_strcpy(str1); // str1을 복사
    if (CpyStr1 != NULL)
    {
        printf("strcpy 첫번째 문자열 반환값은 : %s\n", CpyStr1);
        free(CpyStr1); // 동적 할당된 메모리 해제
    }
    else
    {
        printf("메모리 할당 오류!\n");
    }

    char *CpyStr2 = my_strcpy(str2); // str1을 복사
    if (CpyStr2 != NULL)
    {
        printf("strcpy 두번째 문자열 반환값은 : %s\n", CpyStr2);
        free(CpyStr2); // 동적 할당된 메모리 해제
    }
    else
    {
        printf("메모리 할당 오류!\n");
    }

    return 0;
}
