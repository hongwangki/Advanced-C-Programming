#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// �޴� ������ ����ü
typedef struct {
    int id;        // �޴� ID
    char name[50]; // �޴� �̸�
    int price;     // ����
    int stock;     // ���
} MenuItem;

// �޴� ����Ʈ ����ü
typedef struct {
    MenuItem** drink_menu; // ���� �޴�
    MenuItem** snack_menu; // ���� �޴�
    int drink_count;       // ���� �޴� ��
    int snack_count;       // ���� �޴� ��
} MenuList;

// �ֹ� ����ü
typedef struct {
    MenuItem* item; // �ֹ��� �޴� ������
} Order;

// ���� ������ �޴� ����Ʈ ����
MenuList menu_list = { NULL, NULL, 0, 0 };

// ��� ���� �� ID Ȯ�� �Լ�
int checkID() {
    int mode;
    char id[10]; // ID �Է� ����
    printf("Select Mode (user or admin) : ");
    scanf("%9s", id); // ID �Է� (�ִ� 9����)

    if (strcmp(id, "user") == 0) { // "user" �Է� ��
        mode = 0;
        printf("User Mode\n");
    }
    else if (strcmp(id, "admin") == 0) { // "admin" �Է� ��
        mode = 1;
        printf("Admin Mode\n");
    }
    else { // �߸��� �Է� ó��
        mode = -1;
        printf("Error : Wrong Input!\n");
    }
    return mode;
}

// ���� �޴� �ʱ�ȭ �Լ�
void reset_menu_drink() {
    FILE* file = fopen("drink2.txt", "r"); // ���� ���� ����
    if (!file) { // ���� ���� ���� �� ���� ó��
        perror("Error: Unable to open drink2.txt");
        return;
    }

    // ���� �޴� ������ �ʱ�ȭ
    menu_list.drink_count = 0;
    menu_list.drink_menu = NULL;

    char buffer[100]; // ���� �Է� ����

    while (fgets(buffer, sizeof(buffer), file)) { // ���� �б�
        MenuItem* item = malloc(sizeof(MenuItem)); // ���ο� �޴� ������ �޸� �Ҵ�
        if (!item) { // �޸� �Ҵ� ���� ó��
            perror("Error: Memory allocation failed");
            fclose(file);
            return;
        }

        // �޴� ���� �Ľ�
        if (sscanf(buffer, "%[^\t]\t%d\t%d", item->name, &item->price, &item->stock) != 3) {
            printf("Error: Invalid format in drink2.txt\n");
            free(item);
            continue;
        }
        item->id = menu_list.drink_count + 1; // �޴� ID ����

        // �޴� ����Ʈ�� �߰�
        menu_list.drink_menu = realloc(menu_list.drink_menu, (menu_list.drink_count + 1) * sizeof(MenuItem*));
        if (!menu_list.drink_menu) { // realloc ���� ó��
            perror("Error: Memory allocation failed");
            free(item);
            fclose(file);
            return;
        }
        menu_list.drink_menu[menu_list.drink_count] = item;
        menu_list.drink_count++;
    }
    fclose(file); // ���� �ݱ�

    // ���� �޴� ���
    printf("\n======drink menu=====\n");
    for (int i = 0; i < menu_list.drink_count; i++) {
        if (menu_list.drink_menu[i]->stock > 0) { // ��� �ִ� �޴��� ���
            printf("%d  %s   %d   %d\n",
                menu_list.drink_menu[i]->id,
                menu_list.drink_menu[i]->name,
                menu_list.drink_menu[i]->price,
                menu_list.drink_menu[i]->stock);
        }
    }
    printf("=====================\n");
}

// ���� �޴� �ʱ�ȭ �Լ�
void reset_menu_snack() {
    FILE* file = fopen("snack2.txt", "r"); // ���� ���� ����
    if (!file) { // ���� ���� ���� �� ���� ó��
        perror("Error: Unable to open snack2.txt");
        return;
    }

    // ���� �޴� ������ �ʱ�ȭ
    menu_list.snack_count = 0;
    menu_list.snack_menu = NULL;

    char buffer[100]; // ���� �Է� ����

    while (fgets(buffer, sizeof(buffer), file)) { // ���� �б�
        MenuItem* item = malloc(sizeof(MenuItem)); // ���ο� �޴� ������ �޸� �Ҵ�
        if (!item) { // �޸� �Ҵ� ���� ó��
            perror("Error: Memory allocation failed");
            fclose(file);
            return;
        }

        // �޴� ���� �Ľ�
        if (sscanf(buffer, "%[^\t]\t%d\t%d", item->name, &item->price, &item->stock) != 3) {
            printf("Error: Invalid format in snack2.txt\n");
            free(item);
            continue;
        }
        item->id = menu_list.snack_count + 1; // �޴� ID ����

        // �޴� ����Ʈ�� �߰�
        menu_list.snack_menu = realloc(menu_list.snack_menu, (menu_list.snack_count + 1) * sizeof(MenuItem*));
        if (!menu_list.snack_menu) { // realloc ���� ó��
            perror("Error: Memory allocation failed");
            free(item);
            fclose(file);
            return;
        }
        menu_list.snack_menu[menu_list.snack_count] = item;
        menu_list.snack_count++;
    }
    fclose(file); // ���� �ݱ�

    // ���� �޴� ���
    printf("\n======snack menu=====\n");
    for (int i = 0; i < menu_list.snack_count; i++) {
        if (menu_list.snack_menu[i]->stock > 0) { // ��� �ִ� �޴��� ���
            printf("%d  %s   %d   %d\n",
                menu_list.snack_menu[i]->id,
                menu_list.snack_menu[i]->name,
                menu_list.snack_menu[i]->price,
                menu_list.snack_menu[i]->stock);
        }
    }
    printf("=====================\n");
}

// ������ ��� �Լ�
void print_receipt(Order* order_list, int order_count, int total_price) {
    printf("\n======receipt======\n");
    FILE* file = fopen("receipt.txt", "w"); // ������ ���� ����
    if (!file) { // ���� ���� ���� ó��
        perror("Error: Unable to create receipt.txt");
        return;
    }

    fprintf(file, "======receipt======\n");
    for (int i = 0; i < order_count; i++) {
        printf("%s  %d\n",
            order_list[i].item->name,
            order_list[i].item->price);
        fprintf(file, "%s  %d\n",
            order_list[i].item->name,
            order_list[i].item->price);
    }

    printf("\ntotal_price %d\n", total_price);
    fprintf(file, "\ntotal_price %d\n", total_price);
    printf("===================\n");
    fprintf(file, "=================\n");
    fclose(file);
}

// ���� ��� ���� �Լ�
void service_mode() {
    int id, num;
    Order* order_list = NULL; // �ֹ� ����Ʈ
    int order_count = 0;      // �ֹ� ��
    int total_price = 0;      // �� ���� �ݾ�

    while (1) {
        printf("\nType 1 for drink, 2 for snack, 3 for buy : ");
        scanf("%d", &num);

        if (num == 1) { // ���� �ֹ�
            printf("Type drink id to buy : ");
            scanf("%d", &id);

            if (id > 0 && id <= menu_list.drink_count) {
                MenuItem* select_item = menu_list.drink_menu[id - 1];
                if (select_item->stock > 0) {
                    select_item->stock--;
                    total_price += select_item->price;

                    order_list = realloc(order_list, (order_count + 1) * sizeof(Order));
                    if (!order_list) { // realloc ���� ó��
                        perror("Error: Memory allocation failed");
                        return;
                    }
                    order_list[order_count].item = select_item;
                    order_count++;
                }
                else {
                    printf("Out of stock!\n");
                }
            }
            else {
                printf("Error : Not enough ID for drink!\n");
            }
        }
        else if (num == 2) { // ���� �ֹ�
            printf("Type snack id to buy : ");
            scanf("%d", &id);

            if (id > 0 && id <= menu_list.snack_count) {
                MenuItem* select_item = menu_list.snack_menu[id - 1];
                if (select_item->stock > 0) {
                    select_item->stock--;
                    total_price += select_item->price;

                    order_list = realloc(order_list, (order_count + 1) * sizeof(Order));
                    if (!order_list) { // realloc ���� ó��
                        perror("Error: Memory allocation failed");
                        return;
                    }
                    order_list[order_count].item = select_item;
                    order_count++;
                }
                else {
                    printf("Out of stock!\n");
                }
            }
            else {
                printf("Error : Not enough ID for snack!\n");
            }
        }
        else if (num == 3) { // ���� �Ϸ�
            print_receipt(order_list, order_count, total_price);
            break;
        }
        else {
            printf("Error : Wrong input for type select!\n");
        }
    }
    free(order_list); // �ֹ� ����Ʈ �޸� ����
}

// ���� �Լ�
int main() {
    int mode = checkID(); // ����� ��� Ȯ��

    if (mode == 0) { // ����� ��� ����
        reset_menu_drink(); // ���� �޴� �ʱ�ȭ
        reset_menu_snack(); // ���� �޴� �ʱ�ȭ
        service_mode(); // ���� ��� ����

        // �޸� ����
        for (int i = 0; i < menu_list.drink_count; i++) free(menu_list.drink_menu[i]);
        free(menu_list.drink_menu);
        for (int i = 0; i < menu_list.snack_count; i++) free(menu_list.snack_menu[i]);
        free(menu_list.snack_menu);
    }

    return 0;
}
