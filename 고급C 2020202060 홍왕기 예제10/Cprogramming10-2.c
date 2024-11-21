#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����ü ����
typedef struct {
    int id;
    char name[30];
    float price;
} MenuItem;

// �Լ� ����
void load_menu_from_file(const char* filename, MenuItem** menu, int* count);
void print_menu(MenuItem* menu, int count, const char* type);
void process_order(MenuItem* menu, int count, int* orders, int* orderCount, float* total);
void print_receipt(MenuItem* drinks, int* drinkOrders, int drinkOrderCount, MenuItem* desserts, int* dessertOrders, int dessertOrderCount, float total);

int main() {
    MenuItem* drinks = NULL;
    MenuItem* desserts = NULL;
    int drinkCount = 0, dessertCount = 0;
    int drinkOrders[50] = { 0 }, dessertOrders[50] = { 0 };
    int drinkOrderCount = 0, dessertOrderCount = 0;
    float total = 0.0;
    int choice;

    // ���Ͽ��� �޴� �ҷ�����
    load_menu_from_file("drink.txt", &drinks, &drinkCount);
    load_menu_from_file("dessert.txt", &desserts, &dessertCount);

    // �ֹ� �ݺ�
    while (1) {
        // ���� �޴� ���
        printf("\n1. ���� �ֹ��ϱ�\n2. ����Ʈ �ֹ��ϱ�\n0. ����\n�ֹ��� �����ϼ���: ");
        scanf("%d", &choice);

        if (choice == 0) break; // ����
        else if (choice == 1) { // ���� �ֹ�
            print_menu(drinks, drinkCount, "����");
            process_order(drinks, drinkCount, drinkOrders, &drinkOrderCount, &total,"����");
        }
        else if (choice == 2) { // ����Ʈ �ֹ�
            print_menu(desserts, dessertCount, "����Ʈ");
            process_order(desserts, dessertCount, dessertOrders, &dessertOrderCount, &total,"����Ʈ");
        }
        else {
            printf("�߸��� �����Դϴ�. �ٽ� �õ��ϼ���.\n");
        }
    }

    // ������ ���
    print_receipt(drinks, drinkOrders, drinkOrderCount, desserts, dessertOrders, dessertOrderCount, total);

    // ���� �޸� ����
    free(drinks);
    free(desserts);

    return 0;
}

void load_menu_from_file(const char* filename, MenuItem** menu, int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("������ �� �� �����ϴ�");
        exit(1);
    }

    // �޴� �׸� �� ���
    *count = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        (*count)++;
    }
    rewind(file);

    // ���� �޸� �Ҵ�
    *menu = (MenuItem*)malloc((*count) * sizeof(MenuItem));

    // ���Ͽ��� �޴� ������ �б�
    int id = 1;
    for (int i = 0; i < *count; i++) {
        char name[30];
        float price;
        fscanf(file, "%s %f", name, &price);

        (*menu)[i].id = id++;
        strcpy((*menu)[i].name, name);
        (*menu)[i].price = price;
    }

    fclose(file);
}

//�޴� ����Ʈ �Լ�
void print_menu(MenuItem* menu, int count, const char* type) {
    printf("\n%s �޴�\n", type);
    for (int i = 0; i < count; i++) {
        printf("[%d] %-15s %.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
}

//�ֹ� �ޱ�
void process_order(MenuItem* menu, int count, int* orders, int* orderCount, float* total, const char* type) {
    int id;
        printf("\n�ֹ��� %s ID�� �Է��ϼ��� : ", type);
        scanf("%d", &id);
        if (id < 1 || id > count) {
            printf("�߸��� ID�Դϴ�. �ٽ� �Է��ϼ���.\n");
        }
        orders[(*orderCount)++] = id;
        *total += menu[id - 1].price;
        printf("%s �ֹ� �Ϸ�! ���� �Ѿ�: %.2f\n", menu[id - 1].name, *total);
}

//������ ����Ʈ �Լ�
void print_receipt(MenuItem* drinks, int* drinkOrders, int drinkOrderCount, MenuItem* desserts, int* dessertOrders, int dessertOrderCount, float total) {
    FILE* receipt = fopen("receipt.txt", "w");
    if (receipt == NULL) {
        perror("������ ������ ������ �� �����ϴ�.");
        return;
    }

    fprintf(receipt, "===========================\n");
    fprintf(receipt, "          Receipt          \n");
    fprintf(receipt, "===========================\n");

    printf("\n������:\n");
    printf("===========================\n");
    printf("          Receipt          \n");
    printf("===========================\n");

    // ���� ���
    for (int i = 0; i < drinkOrderCount; i++) {
        int id = drinkOrders[i];
        fprintf(receipt, "%s x %d = %.2f\n", drinks[id - 1].name, 1, drinks[id - 1].price);
        printf("%s x %d = %.2f\n", drinks[id - 1].name, 1, drinks[id - 1].price);
    }

    // ����Ʈ ���
    for (int i = 0; i < dessertOrderCount; i++) {
        int id = dessertOrders[i];
        fprintf(receipt, "%s x %d = %.2f\n", desserts[id - 1].name, 1, desserts[id - 1].price);
        printf("%s x %d = %.2f\n", desserts[id - 1].name, 1, desserts[id - 1].price);
    }

    fprintf(receipt, "===========================\n");
    fprintf(receipt, "Total :: %.2f\n", total);
    fclose(receipt);

    printf("===========================\n");
    printf("Total :: %.2f\n", total);
    printf("�������� receipt.txt�� ����Ǿ����ϴ�.\n");
}
