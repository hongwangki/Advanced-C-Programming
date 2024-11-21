#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 30
#define MAX_TITLE_LENGTH 100
#define MAX_STORAGE_BOOKS 100

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

    while (fgets(line, sizeof(line), fr) != NULL && *numBooks < MAX_BOOKS) {
        char title[MAX_TITLE_LENGTH];
        int count;

        line[strcspn(line, "\n")] = 0;

        if (sscanf(line, "%[^\t]%*[\t]%d", title, &count) == 2) {
            BookName[*numBooks] = (char*)malloc((strlen(title) + 1) * sizeof(char));
            strcpy(BookName[*numBooks], title);
            BookCount[*numBooks] = count;
            (*numBooks)++;
        }
    }

    fclose(fr);
}

// 창고에서 도서를 불러오는 함수
void load_storage_books(char** storageBookNames, int* storageBookCount, int* storageNumBooks) {
    FILE* fr = fopen("storage.txt", "r");
    if (fr == NULL) {
        perror("창고 파일을 열 수 없습니다.");
        return;
    }

    *storageNumBooks = 0;
    char line[200];
     // 첫 번째 줄(헤더)은 무시
    fgets(line, sizeof(line), fr);
    while (fgets(line, sizeof(line), fr) != NULL && *storageNumBooks < MAX_STORAGE_BOOKS) {
        char title[MAX_TITLE_LENGTH];
        int count;

        line[strcspn(line, "\n")] = 0;  // 줄 끝의 개행 문자 제거

        char* last_space = strrchr(line, ' ');  // 마지막 공백을 찾음
        if (last_space != NULL) {
            *last_space = '\0';  // 마지막 공백을 기준으로 제목과 권수를 나누기 위해 공백을 '\0'으로 변경
            count = atoi(last_space + 1);  // 공백 뒤의 숫자를 읽어 권수로 변환
            strcpy(title, line);  // 제목 저장
            storageBookNames[*storageNumBooks] = (char*)malloc((strlen(title) + 1) * sizeof(char));
            strcpy(storageBookNames[*storageNumBooks], title);
            storageBookCount[*storageNumBooks] = count;
            (*storageNumBooks)++;
        }
        else {
            printf("경고: '%s'는 유효하지 않은 형식입니다.\n", line); // 잘못된 줄 형식 출력
        }
    }

    fclose(fr);
}

// 창고 도서 현황 출력 함수
void print_storage_books(char** storageBookNames, int* storageBookCount, int storageNumBooks) {
    printf("\n창고 도서 현황:\n");
    if (storageNumBooks == 0) {
        printf("창고에 도서가 없습니다.\n");
    }
    else {
        for (int i = 0; i < storageNumBooks; i++) {
            printf("책 이름: %s, 권수: %d\n", storageBookNames[i], storageBookCount[i]);
        }
    }
}

// 도서 대여 관리 함수
void manage_booklist(char* input, char** BookName, int* BookCount, int numBooks) {
    int bookID = -1;
    //id로 입력하는 경우
    if (sscanf(input, "%d", &bookID) == 1) {
        if (bookID == -1) {
            printf("프로그램을 종료합니다.\n");
            exit(0);
        }

        if (bookID >= 0 && bookID < numBooks) {
            if (BookCount[bookID] > 0) {
                printf("도서 '%s' 대여 가능합니다. 대여 하였습니다.\n", BookName[bookID]);
                BookCount[bookID]--;
            }
            else {
                printf("도서 '%s'는 모두 대여 중입니다.\n", BookName[bookID]);
            }
        }
        else {
            printf("유효하지 않은 도서 ID입니다.\n");
        }
    }
    //책 이름으로 입력하는 경우
    else {
        int found = 0;
        for (int i = 0; i < numBooks; i++) {
            if (strcmp(BookName[i], input) == 0) {
                found = 1;
                if (BookCount[i] > 0) {
                    printf("도서 '%s' 대여 가능합니다. 대여 하였습니다.\n", BookName[i]);
                    BookCount[i]--;
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

int admin_check() {
    FILE* authFile = fopen("admin_auth.txt", "r");
    if (authFile == NULL) {
        perror("관리자 인증 파일을 열 수 없습니다.");
        return 0;
    }

    char storedID[30], storedPW[30];
    char line[100];

    // 파일에서 ID와 PW 읽기
    while (fgets(line, sizeof(line), authFile)) {
        if (strncmp(line, "ID", 2) == 0) {
            sscanf(line, "ID %s", storedID);  // ID 추출
        }
        else if (strncmp(line, "PW", 2) == 0) {
            sscanf(line, "PW %s", storedPW); // PW 추출
        }
    }
    fclose(authFile);
    char inputID[30], inputPW[30];
    printf("관리자 ID를 입력하세요: ");
    scanf("%s", inputID);
    printf("관리자 PW를 입력하세요: ");
    scanf("%s", inputPW);
    
    // 인증 확인
    if (strcmp(storedID, inputID) == 0 && strcmp(storedPW, inputPW) == 0) {
        printf("관리자 인증 성공.\n");
        return 1;
    }
    else {
        printf("관리자 인증 실패.\n");
        return 0;
    }
}

// 도서 재고 현황 출력 함수
void print_booklist(char** BookName, int* BookCount, int numBooks) {
    printf("현재 보유 도서 재고 현황:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("ID: %d, 책 이름: %s, 권수: %d\n", i, BookName[i], BookCount[i]);
    }
}

// 창고 재고 파일 업데이트 함수
void update_storage_books(char** storageBookNames, int* storageBookCount, int storageNumBooks) {
    FILE* fw = fopen("storage.txt", "w");
    if (fw == NULL) {
        perror("창고 파일을 열 수 없습니다.");
        return;
    }

    // 헤더 추가
    fprintf(fw, "책 이름 권수\n");
    for (int i = 0; i < storageNumBooks; i++) {
        fprintf(fw, "%s %d\n", storageBookNames[i], storageBookCount[i]);
    }

    // 파일 닫기
    fclose(fw);
}

void extend_book_inventory(char** BookName, int* BookCount, int numBooks, char** storageBookNames, int* storageBookCount, int storageNumBooks) {
    // 도서 재고 확장 로직
    for (int i = 0; i < numBooks; i++) {
        if (BookCount[i] == 0) {
            for (int j = 0; j < storageNumBooks; j++) {
                if (strcmp(BookName[i], storageBookNames[j]) == 0 && storageBookCount[j] >= 3) {
                    BookCount[i] = 3;  // 재고를 3권으로 확장
                    storageBookCount[j] -= 3;  // 창고에서 해당 도서 3권 감소
                    printf("도서 '%s'의 재고가 3권으로 확장되었습니다.\n", BookName[i]);
                    break;
                }
                else if (strcmp(BookName[i], storageBookNames[j]) == 0 && storageBookCount[j] > 0) {
                    BookCount[i] = storageBookCount[j];  // 남아있는 권수만큼 추가
                    storageBookCount[j] = 0;  // 창고에서 해당 도서 모두 감소
                    printf("도서 '%s'의 재고가 %d권으로 확장되었습니다.\n", BookName[i], BookCount[i]);
                    break;
                }
            }
        }
    }

    // 창고 재고 파일 업데이트
    update_storage_books(storageBookNames, storageBookCount, storageNumBooks);

    // 확장된 창고 도서 현황 출력
    print_storage_books(storageBookNames, storageBookCount, storageNumBooks);
}




// 프로그램 진입점
int main(int argc, char* argv[]) {
    char* BookName[MAX_BOOKS];
    int BookCount[MAX_BOOKS];
    int numBooks;

    initial_booklist(BookName, BookCount, &numBooks);

    char* storageBookNames[MAX_STORAGE_BOOKS];
    int storageBookCount[MAX_STORAGE_BOOKS];
    int storageNumBooks;

    load_storage_books(storageBookNames, storageBookCount, &storageNumBooks);

    // admin 인자가 들어왔다면 전환
    if (argc > 1 && strcmp(argv[1], "admin") == 0) {
        if (admin_check()) {
            print_booklist(BookName, BookCount, numBooks);

            // 도서 재고 확장
            extend_book_inventory(BookName, BookCount, numBooks, storageBookNames, storageBookCount, storageNumBooks);

            printf("\n확장된 도서 재고 현황:\n");
            print_booklist(BookName, BookCount, numBooks);

            // 창고 도서 현황 출력
            print_storage_books(storageBookNames, storageBookCount, storageNumBooks);

            char choice[10];
            printf("서비스 모드로 전환하시겠습니까? (yes/no): ");
            scanf("%s", choice);
            while (getchar() != '\n');  // 입력 버퍼에 남은 개행 문자 제거

            if (strcmp(choice, "no") == 0) {
                printf("프로그램을 종료합니다.\n");
                for (int i = 0; i < numBooks; i++) {
                    free(BookName[i]);
                }
                for (int i = 0; i < storageNumBooks; i++) {
                    free(storageBookNames[i]);
                }
                return 0;
            }
        }
        else {
            printf("관리자 인증 실패로 프로그램을 종료합니다.\n");
            return 1;
        }
    }

    // 보유 도서 목록 출력
    printf("현재 보유 도서 목록:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("ID: %d, 책 이름: %s, 권수: %d\n", i, BookName[i], BookCount[i]);
    }

    // 대출 시스템 반복문
    char tempname[30];
    while (1) {
        printf("도서 ID 또는 도서 이름을 입력하시오 (-1을 입력하면 종료): ");
        fgets(tempname, sizeof(tempname), stdin);
        tempname[strcspn(tempname, "\n")] = 0;

        if (strcmp(tempname, "-1") == 0) {
            printf("프로그램을 종료합니다.\n");
            break;
        }

        manage_booklist(tempname, BookName, BookCount, numBooks);
    }

    for (int i = 0; i < numBooks; i++) {
        free(BookName[i]);
    }
    for (int i = 0; i < storageNumBooks; i++) {
        free(storageBookNames[i]);
    }

    return 0;
}
