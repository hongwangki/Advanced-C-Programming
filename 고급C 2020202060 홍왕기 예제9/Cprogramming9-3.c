#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 30
#define MAX_TITLE_LENGTH 100

// �ʱ� ���� ����Ʈ�� �ҷ����� �Լ�
void initial_booklist(char** BookName, int* BookCount, int* numBooks) {
    FILE* fr = fopen("books.txt", "r");
    if (fr == NULL) {
        perror("������ �� �� �����ϴ�.");
        return;
    }

    *numBooks = 0;
    char line[200];

    // ù ��° ��(���)�� ����
    fgets(line, sizeof(line), fr);

    // ������ �� �پ� �о� ���� �̸��� ���� ���� �Ľ�
    while (fgets(line, sizeof(line), fr) != NULL && *numBooks < MAX_BOOKS) {
        char title[MAX_TITLE_LENGTH];
        int count;

        // ���� ���� ���� (������ �ٿ��� ����)
        line[strcspn(line, "\n")] = 0;

        // �� �ٿ��� ����� �Ǽ� �Ľ�
        if (sscanf(line, "%[^\t]%*[\t]%d", title, &count) == 2) {
            BookName[*numBooks] = (char*)malloc((strlen(title) + 1) * sizeof(char));
            strcpy(BookName[*numBooks], title);
            BookCount[*numBooks] = count;
            (*numBooks)++;
        }
    }

    fclose(fr);
}

// ���� �뿩 ���� �Լ�
void manage_booklist(char* input, char** BookName, int* BookCount, int numBooks) {
    int bookID = -1;

    // �Է°��� �������� Ȯ���Ͽ� ID�� ã�� �� �ִ��� Ȯ��
    if (sscanf(input, "%d", &bookID) == 1) {
        // ID�� ���� ã��
        if (bookID == -1) {
            printf("���α׷��� �����մϴ�.\n");
            exit(0);  // ����
        }

        if (bookID >= 0 && bookID < numBooks) {
            if (BookCount[bookID] > 0) {
                printf("���� '%s' �뿩 �����մϴ�. �뿩 �Ͽ����ϴ�.\n", BookName[bookID]);
                BookCount[bookID]--;  // �뿩 �� ���� ����
            }
            else {
                printf("���� '%s'�� ��� �뿩 ���Դϴ�.\n", BookName[bookID]);
            }
        }
        else {
            printf("��ȿ���� ���� ���� ID�Դϴ�.\n");
        }
    }
    else {
        // ���� �̸����� ã��
        int found = 0;
        for (int i = 0; i < numBooks; i++) {
            if (strcmp(BookName[i], input) == 0) {
                found = 1;
                if (BookCount[i] > 0) {
                    printf("���� '%s' �뿩 �����մϴ�. �뿩 �Ͽ����ϴ�. \n", BookName[i]);
                    BookCount[i]--;  // �뿩 �� ���� ����
                }
                else {
                    printf("���� '%s'�� ��� �뿩 ���Դϴ�.\n", BookName[i]);
                }
                break;
            }
        }

        if (!found) {
            printf("���� '%s'�� ã�� �� �����ϴ�.\n", input);
        }
    }
}

int main() {
    char* BookName[MAX_BOOKS];
    int BookCount[MAX_BOOKS];
    int numBooks;
    char tempname[30];

    initial_booklist(BookName, BookCount, &numBooks);

    // ���� ��� ���
    printf("���� ���� ���� ���:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("ID: %d, å �̸�: %s, �Ǽ�: %d\n", i, BookName[i], BookCount[i]);
    }

    // ����� �Է� �ݺ�
    while (1) {
        printf("���� ID �Ǵ� ���� �̸��� �Է��Ͻÿ� (-1�� �Է��ϸ� ����): ");
        fgets(tempname, sizeof(tempname), stdin);
        tempname[strcspn(tempname, "\n")] = 0;  // ���� ���� ����

        if (strcmp(tempname, "-1") == 0) {
            printf("���α׷��� �����մϴ�.\n");
            break;  // ����
        }

        manage_booklist(tempname, BookName, BookCount, numBooks);
    }

    // �Ҵ��� �޸� ����
    for (int i = 0; i < numBooks; i++) {
        free(BookName[i]);
    }

    return 0;
}
