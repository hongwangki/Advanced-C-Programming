#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 30
#define MAX_TITLE_LENGTH 100

// 초기 도서 리스트를 불러오는 함수
void initial_booklist(char** BookName, int* BookCount, int* numBooks) {
    FILE* fr = fopen("books.txt", "r");
    if (fr == NULL) {
        perror("파일을 열 수 없습니다.");
        return;
    }

    *numBooks = 0;
    char line[200];

    // 첫 번째 줄(헤더)은 무시
    fgets(line, sizeof(line), fr);

    // 파일을 한 줄씩 읽어 도서 이름과 보유 수량 파싱
    while (fgets(line, sizeof(line), fr) != NULL && *numBooks < MAX_BOOKS) {
        char title[MAX_TITLE_LENGTH];
        int count;

        // 개행 문자 제거 (마지막 줄에도 적용)
        line[strcspn(line, "\n")] = 0;

        // 각 줄에서 제목과 권수 파싱
        if (sscanf(line, "%[^\t]%*[\t]%d", title, &count) == 2) {
            BookName[*numBooks] = (char*)malloc((strlen(title) + 1) * sizeof(char));
            strcpy(BookName[*numBooks], title);
            BookCount[*numBooks] = count;
            (*numBooks)++;
        }
    }

    fclose(fr);
}

// 도서 대여 관리 함수
void manage_booklist(char* input, char** BookName, int* BookCount, int numBooks) {
    int bookID = -1;

    // 입력값이 숫자인지 확인하여 ID로 찾을 수 있는지 확인
    if (sscanf(input, "%d", &bookID) == 1) {
        // ID로 도서 찾기
        if (bookID == -1) {
            printf("프로그램을 종료합니다.\n");
            exit(0);  // 종료
        }

        if (bookID >= 0 && bookID < numBooks) {
            if (BookCount[bookID] > 0) {
                printf("도서 '%s' 대여 가능합니다. 대여 하였습니다.\n", BookName[bookID]);
                BookCount[bookID]--;  // 대여 시 수량 감소
            }
            else {
                printf("도서 '%s'는 모두 대여 중입니다.\n", BookName[bookID]);
            }
        }
        else {
            printf("유효하지 않은 도서 ID입니다.\n");
        }
    }
    else {
        // 도서 이름으로 찾기
        int found = 0;
        for (int i = 0; i < numBooks; i++) {
            if (strcmp(BookName[i], input) == 0) {
                found = 1;
                if (BookCount[i] > 0) {
                    printf("도서 '%s' 대여 가능합니다. 대여 하였습니다. \n", BookName[i]);
                    BookCount[i]--;  // 대여 시 수량 감소
                }
                else {
                    printf("도서 '%s'는 모두 대여 중입니다.\n", BookName[i]);
                }
                break;
            }
        }

        if (!found) {
            printf("도서 '%s'를 찾을 수 없습니다.\n", input);
        }
    }
}

int main() {
    char* BookName[MAX_BOOKS];
    int BookCount[MAX_BOOKS];
    int numBooks;
    char tempname[30];

    initial_booklist(BookName, BookCount, &numBooks);

    // 도서 목록 출력
    printf("현재 보유 도서 목록:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("ID: %d, 책 이름: %s, 권수: %d\n", i, BookName[i], BookCount[i]);
    }

    // 사용자 입력 반복
    while (1) {
        printf("도서 ID 또는 도서 이름을 입력하시오 (-1을 입력하면 종료): ");
        fgets(tempname, sizeof(tempname), stdin);
        tempname[strcspn(tempname, "\n")] = 0;  // 개행 문자 제거

        if (strcmp(tempname, "-1") == 0) {
            printf("프로그램을 종료합니다.\n");
            break;  // 종료
        }

        manage_booklist(tempname, BookName, BookCount, numBooks);
    }

    // 할당한 메모리 해제
    for (int i = 0; i < numBooks; i++) {
        free(BookName[i]);
    }

    return 0;
}
