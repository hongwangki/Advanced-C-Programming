#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BOOKS 30
#define MAX_TITLE_LENGTH 100
#define MAX_STORAGE_BOOKS 100

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

// â���� ������ �ҷ����� �Լ�
void load_storage_books(char** storageBookNames, int* storageBookCount, int* storageNumBooks) {
    FILE* fr = fopen("storage.txt", "r");
    if (fr == NULL) {
        perror("â�� ������ �� �� �����ϴ�.");
        return;
    }

    *storageNumBooks = 0;
    char line[200];
     // ù ��° ��(���)�� ����
    fgets(line, sizeof(line), fr);
    while (fgets(line, sizeof(line), fr) != NULL && *storageNumBooks < MAX_STORAGE_BOOKS) {
        char title[MAX_TITLE_LENGTH];
        int count;

        line[strcspn(line, "\n")] = 0;  // �� ���� ���� ���� ����

        char* last_space = strrchr(line, ' ');  // ������ ������ ã��
        if (last_space != NULL) {
            *last_space = '\0';  // ������ ������ �������� ����� �Ǽ��� ������ ���� ������ '\0'���� ����
            count = atoi(last_space + 1);  // ���� ���� ���ڸ� �о� �Ǽ��� ��ȯ
            strcpy(title, line);  // ���� ����
            storageBookNames[*storageNumBooks] = (char*)malloc((strlen(title) + 1) * sizeof(char));
            strcpy(storageBookNames[*storageNumBooks], title);
            storageBookCount[*storageNumBooks] = count;
            (*storageNumBooks)++;
        }
        else {
            printf("���: '%s'�� ��ȿ���� ���� �����Դϴ�.\n", line); // �߸��� �� ���� ���
        }
    }

    fclose(fr);
}

// â�� ���� ��Ȳ ��� �Լ�
void print_storage_books(char** storageBookNames, int* storageBookCount, int storageNumBooks) {
    printf("\nâ�� ���� ��Ȳ:\n");
    if (storageNumBooks == 0) {
        printf("â�� ������ �����ϴ�.\n");
    }
    else {
        for (int i = 0; i < storageNumBooks; i++) {
            printf("å �̸�: %s, �Ǽ�: %d\n", storageBookNames[i], storageBookCount[i]);
        }
    }
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

// â�� ��� ���� ������Ʈ �Լ�
void update_storage_books(char** storageBookNames, int* storageBookCount, int storageNumBooks) {
    FILE* fw = fopen("storage.txt", "w");
    if (fw == NULL) {
        perror("â�� ������ �� �� �����ϴ�.");
        return;
    }

    // ��� �߰�
    fprintf(fw, "å �̸� �Ǽ�\n");
    for (int i = 0; i < storageNumBooks; i++) {
        fprintf(fw, "%s %d\n", storageBookNames[i], storageBookCount[i]);
    }

    // ���� �ݱ�
    fclose(fw);
}

void extend_book_inventory(char** BookName, int* BookCount, int numBooks, char** storageBookNames, int* storageBookCount, int storageNumBooks) {
    // ���� ��� Ȯ�� ����
    for (int i = 0; i < numBooks; i++) {
        if (BookCount[i] == 0) {
            for (int j = 0; j < storageNumBooks; j++) {
                if (strcmp(BookName[i], storageBookNames[j]) == 0 && storageBookCount[j] >= 3) {
                    BookCount[i] = 3;  // ��� 3������ Ȯ��
                    storageBookCount[j] -= 3;  // â���� �ش� ���� 3�� ����
                    printf("���� '%s'�� ��� 3������ Ȯ��Ǿ����ϴ�.\n", BookName[i]);
                    break;
                }
                else if (strcmp(BookName[i], storageBookNames[j]) == 0 && storageBookCount[j] > 0) {
                    BookCount[i] = storageBookCount[j];  // �����ִ� �Ǽ���ŭ �߰�
                    storageBookCount[j] = 0;  // â���� �ش� ���� ��� ����
                    printf("���� '%s'�� ��� %d������ Ȯ��Ǿ����ϴ�.\n", BookName[i], BookCount[i]);
                    break;
                }
            }
        }
    }

    // â�� ��� ���� ������Ʈ
    update_storage_books(storageBookNames, storageBookCount, storageNumBooks);

    // Ȯ��� â�� ���� ��Ȳ ���
    print_storage_books(storageBookNames, storageBookCount, storageNumBooks);
}




// ���α׷� ������
int main(int argc, char* argv[]) {
    char* BookName[MAX_BOOKS];
    int BookCount[MAX_BOOKS];
    int numBooks;

    initial_booklist(BookName, BookCount, &numBooks);

    char* storageBookNames[MAX_STORAGE_BOOKS];
    int storageBookCount[MAX_STORAGE_BOOKS];
    int storageNumBooks;

    load_storage_books(storageBookNames, storageBookCount, &storageNumBooks);

    // admin ���ڰ� ���Դٸ� ��ȯ
    if (argc > 1 && strcmp(argv[1], "admin") == 0) {
        if (admin_check()) {
            print_booklist(BookName, BookCount, numBooks);

            // ���� ��� Ȯ��
            extend_book_inventory(BookName, BookCount, numBooks, storageBookNames, storageBookCount, storageNumBooks);

            printf("\nȮ��� ���� ��� ��Ȳ:\n");
            print_booklist(BookName, BookCount, numBooks);

            // â�� ���� ��Ȳ ���
            print_storage_books(storageBookNames, storageBookCount, storageNumBooks);

            char choice[10];
            printf("���� ���� ��ȯ�Ͻðڽ��ϱ�? (yes/no): ");
            scanf("%s", choice);
            while (getchar() != '\n');  // �Է� ���ۿ� ���� ���� ���� ����

            if (strcmp(choice, "no") == 0) {
                printf("���α׷��� �����մϴ�.\n");
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
            printf("������ ���� ���з� ���α׷��� �����մϴ�.\n");
            return 1;
        }
    }

    // ���� ���� ��� ���
    printf("���� ���� ���� ���:\n");
    for (int i = 0; i < numBooks; i++) {
        printf("ID: %d, å �̸�: %s, �Ǽ�: %d\n", i, BookName[i], BookCount[i]);
    }

    // ���� �ý��� �ݺ���
    char tempname[30];
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
    for (int i = 0; i < storageNumBooks; i++) {
        free(storageBookNames[i]);
    }

    return 0;
}
