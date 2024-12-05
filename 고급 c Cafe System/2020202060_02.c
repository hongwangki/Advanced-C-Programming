#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// ����� ���� �޴��� ������ ���� ����
char** drink_menu = NULL; // ���� �޴� �迭
char** snack_menu = NULL; // ���� �޴� �迭
int drink_count = 0;      // ���� �޴� ��
int snack_count = 0;      // ���� �޴� ��

// ID üũ �� ��� ���� �Լ�
int check_ID() {
    char id[10]; // ID �Է��� ���� �迭
    int mode;    // ��带 ������ ����

    printf("Mode Select (admin or user) : ");
    scanf("%s", id);  // ID �Է�

    if (strcmp(id, "admin") == 0) { // "admin" �Է� ��
        printf("Admin mode\n");
        mode = 1;  // ������ ���
    }
    else if (strcmp(id, "user") == 0) { // "user" �Է� ��
        printf("User mode\n");
        mode = 0;  // ����� ���
    }
    else { // �߸��� �Է� ó��
        printf("Error : Wrong Input!\n");
        mode = -1; // ���� ���
    }
    return mode; // ��� ��ȯ
}

// ���� �޴� ���� �ʱ�ȭ �� �޴� �ε� �Լ�
void reset_menu_drink() {
    FILE* file = fopen("drink1.txt", "r"); // ���� �޴� ���� ����
    if (!file) { // ���� ���� ���� ó��
        perror("file dont open\n");
        return;
    }

    // ���� �޴� �޸� ����
    drink_count = 0;
    free(drink_menu);
    drink_menu = NULL;

    char buffer[100]; // ������ �� ���� ���� ����

    while (fgets(buffer, sizeof(buffer), file)) { // ������ �� �پ� �б�
        char* token = strtok(buffer, "\n"); // �ٹٲ� ���� ����
        if (token) {
            // ���ο� �޴� �߰�
            drink_menu = realloc(drink_menu, (drink_count + 1) * sizeof(char*));
            if (!drink_menu) { // realloc ���� ó��
                perror("Memory allocation failed");
                fclose(file);
                return;
            }
            drink_menu[drink_count] = malloc(strlen(token) + 1);
            if (!drink_menu[drink_count]) { // malloc ���� ó��
                perror("Memory allocation failed");
                fclose(file);
                return;
            }
            strcpy(drink_menu[drink_count], token);
            drink_count++;
        }
    }
    fclose(file); // ���� �ݱ�

    // ���� �޴� ���
    printf("\n======drink menu=====\n");
    for (int i = 0; i < drink_count; i++) {
        printf("%d  %s\n", i + 1, drink_menu[i]);
    }
    printf("=====================\n");
}

// ���� �޴� ���� �ʱ�ȭ �� �޴� �ε� �Լ�
void reset_menu_snack() {
    FILE* file = fopen("snack1.txt", "r"); // ���� �޴� ���� ����
    if (!file) { // ���� ���� ���� ó��
        perror("file dont open\n");
        return;
    }

    // ���� �޴� �޸� ����
    snack_count = 0;
    free(snack_menu);
    snack_menu = NULL;

    char buffer[100]; // ������ �� ���� ���� ����

    while (fgets(buffer, sizeof(buffer), file)) { // ������ �� �پ� �б�
        char* token = strtok(buffer, "\n"); // �ٹٲ� ���� ����
        if (token) {
            // ���ο� �޴� �߰�
            snack_menu = realloc(snack_menu, (snack_count + 1) * sizeof(char*));
            if (!snack_menu) { // realloc ���� ó��
                perror("Memory allocation failed");
                fclose(file);
                return;
            }
            snack_menu[snack_count] = malloc(strlen(token) + 1);
            if (!snack_menu[snack_count]) { // malloc ���� ó��
                perror("Memory allocation failed");
                fclose(file);
                return;
            }
            strcpy(snack_menu[snack_count], token);
            snack_count++;
        }
    }
    fclose(file); // ���� �ݱ�

    // ���� �޴� ���
    printf("\n======snack menu=====\n");
    for (int i = 0; i < snack_count; i++) {
        printf("%d  %s\n", i + 1, snack_menu[i]);
    }
    printf("=====================\n");
}

// ����� ���� ��� �Լ�
void service_mode() {
    int id, num; // �Է� ����
    char** order_list = NULL; // �ֹ� ����Ʈ
    int order_count = 0; // �ֹ� ��

    while (1) {
        printf("\nType 1 for drink, 2 for snack, 3 for buy : ");
        scanf("%d", &num); // �޴� ���� �Է�

        if (num == 1) { // ���� ����
            printf("Type drink id to buy : ");
            scanf("%d", &id);

            if (id > 0 && id <= drink_count) { // ��ȿ�� ID���� Ȯ��
                order_list = realloc(order_list, (order_count + 1) * sizeof(char*));
                if (!order_list) { // realloc ���� ó��
                    perror("Memory allocation failed");
                    return;
                }
                order_list[order_count] = malloc(strlen(drink_menu[id - 1]) + 1);
                if (!order_list[order_count]) { // malloc ���� ó��
                    perror("Memory allocation failed");
                    return;
                }
                strcpy(order_list[order_count], drink_menu[id - 1]);
                order_count++;
            }
            else {
                printf("Error : Not enough ID for drink!\n");
            }

        }
        else if (num == 2) { // ���� ����
            printf("Type snack id to buy : ");
            scanf("%d", &id);

            if (id > 0 && id <= snack_count) { // ��ȿ�� ID���� Ȯ��
                order_list = realloc(order_list, (order_count + 1) * sizeof(char*));
                if (!order_list) { // realloc ���� ó��
                    perror("Memory allocation failed");
                    return;
                }
                order_list[order_count] = malloc(strlen(snack_menu[id - 1]) + 1);
                if (!order_list[order_count]) { // malloc ���� ó��
                    perror("Memory allocation failed");
                    return;
                }
                strcpy(order_list[order_count], snack_menu[id - 1]);
                order_count++;
            }
            else {
                printf("Error : Not enough ID for snack!\n");
            }

        }
        else if (num == 3) { // ������ ��� �� ����
            printf("\n======receipt======\n");
            for (int i = 0; i < order_count; i++) {
                printf("%s\n", order_list[i]);
            }
            printf("===================\n");
            break;
        }
        else { // �߸��� �Է� ó��
            printf("Error : Wrong input for type select!\n");
        }
    }

    // �ֹ� ����Ʈ �޸� ����
    for (int i = 0; i < order_count; i++) free(order_list[i]);
    free(order_list);
}

// ���� �Լ�
int main() {
    int mode = check_ID(); // ��� Ȯ��

    if (mode == 0) { // ����� ���
        reset_menu_drink(); // ���� �޴� �ε�
        reset_menu_snack(); // ���� �޴� �ε�
        service_mode(); // ���� ��� ����
        // �޴� �޸� ����
        for (int i = 0; i < drink_count; i++) free(drink_menu[i]);
        free(drink_menu);
        for (int i = 0; i < snack_count; i++) free(snack_menu[i]);
        free(snack_menu);
    }
}
