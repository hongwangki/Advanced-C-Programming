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

// ���� �뿩 ���� �Լ�
void manage_booklist(char* input, char** BookName, int* BookCount, int numBooks) {
    int bookID = -1;
    //id�� �Է��ϴ� ���
    if (sscanf(input, "%d", &bookID) == 1) {
        if (bookID == -1) {
            printf("���α׷��� �����մϴ�.\n");
            exit(0);
        }

        if (bookID >= 0 && bookID < numBooks) {
            if (BookCount[bookID] > 0) {
                printf("���� '%s' �뿩 �����մϴ�. �뿩 �Ͽ����ϴ�.\n", BookName[bookID]);
                BookCount[bookID]--;
            }
            else {
                printf("���� '%s'�� ��� �뿩 ���Դϴ�.\n", BookName[bookID]);
            }
        }
        else {
            printf("��ȿ���� ���� ���� ID�Դϴ�.\n");
        }
    }
    //å �̸����� �Է��ϴ� ���
    else {
        int found = 0;
        for (int i = 0; i < numBooks; i++) {
            if (strcmp(BookName[i], input) == 0) {
                found = 1;
                if (BookCount[i] > 0) {
                    printf("���� '%s' �뿩 �����մϴ�. �뿩 �Ͽ����ϴ�.\n", BookName[i]);
                    BookCount[i]--;
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


int admin_check() {
    FILE* authFile = fopen("admin_auth.txt", "r");
    if (authFile == NULL) {
        perror("������ ���� ������ �� �� �����ϴ�.");
        return 0;
    }

    char storedID[30], storedPW[30];
    char line[100];

    // ���Ͽ��� ID�� PW �б�
    while (fgets(line, sizeof(line), authFile)) {
        if (strncmp(line, "ID", 2) == 0) {
            sscanf(line, "ID %s", storedID);  // ID ����
        }
        else if (strncmp(line, "PW", 2) == 0) {
            sscanf(line, "PW %s", storedPW); // PW ����
        }
    }
    fclose(authFile);
    //printf("���Ͽ��� ���� ID: '%s', PW: '%s'\n", storedID, storedPW);
    char inputID[30], inputPW[30];
    printf("������ ID�� �Է��ϼ���: ");
    scanf("%s", inputID);
    printf("������ PW�� �Է��ϼ���: ");
    scanf("%s", inputPW);
    
    // ���� Ȯ��
    if (strcmp(storedID, inputID) == 0 && strcmp(storedPW, inputPW) == 0) {
        printf("������ ���� ����.\n");
        return 1;
    }
    else {
        printf("������ ���� ����.\n");
        return 0;
    }
}


// ���� ��� ��Ȳ ��� �Լ�
void print_booklist(char** BookName, int* BookCount, int numBooks) {
    printf("���� ���� ���� ��� ��Ȳ:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("ID: %d, å �̸�: %s, �Ǽ�: %d\n", i, BookName[i], BookCount[i]);
    }
}

// ���α׷� ������
int main(int argc, char* argv[]) {
    char* BookName[MAX_BOOKS];
    int BookCount[MAX_BOOKS];
    int numBooks;

    initial_booklist(BookName, BookCount, &numBooks);

    //admin ���ڰ� ���Դٸ� ��ȯ
    if (argc > 1 && strcmp(argv[1], "admin") == 0) {
        if (admin_check()) {
            print_booklist(BookName, BookCount, numBooks);

            char choice[10];
            printf("���� ���� ��ȯ�Ͻðڽ��ϱ�? (yes/no): ");
            scanf("%s", choice);
            while (getchar() != '\n');  // �Է� ���ۿ� ���� ���� ���� ����

            if (strcmp(choice, "no") == 0) {
                printf("���α׷��� �����մϴ�.\n");
                for (int i = 0; i < numBooks; i++) {
                    free(BookName[i]);
                }
                return 0;
            }
        }
        else {
            printf("������ ���� ���з� ���α׷��� �����մϴ�.\n");
            return 1;
        }
    }
    char tempname[30];
    //���� ���� �ⷫ
    printf("���� ���� ���� ���:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("ID: %d, å �̸�: %s, �Ǽ�: %d\n", i, BookName[i], BookCount[i]);
    }

    //���� �ý��� �ݺ���
    while (1) {
        printf("���� ID �Ǵ� ���� �̸��� �Է��Ͻÿ� (-1�� �Է��ϸ� ����): ");
        fgets(tempname, sizeof(tempname), stdin);
        tempname[strcspn(tempname, "\n")] = 0;

        if (strcmp(tempname, "-1") == 0) {
            printf("���α׷��� �����մϴ�.\n");
            break;
        }

        manage_booklist(tempname, BookName, BookCount, numBooks);
    }

    for (int i = 0; i < numBooks; i++) {
        free(BookName[i]);
    }

    return 0;
}
