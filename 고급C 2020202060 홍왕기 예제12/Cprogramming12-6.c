#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ���� ���� ��� ����ü ����
struct Drink {
    char name[50];
    float price;
    struct Drink* next;
};

// �� ���� ��带 �����ϴ� �Լ�
struct Drink* createDrink(char* name, float price) {
    struct Drink* newDrink = (struct Drink*)malloc(sizeof(struct Drink));
    strcpy(newDrink->name, name);
    newDrink->price = price;
    newDrink->next = NULL;
    return newDrink;
}

// ����Ʈ�� ����ϴ� �Լ�
void printList(struct Drink* head) {
    struct Drink* current = head;
    while (current != NULL) {
        printf("%s %.2f\n", current->name, current->price);
        current = current->next;
    }
    printf("\n");
}

// ����Ʈ�� �̸������� �����ϴ� �Լ�
struct Drink* sortByName(struct Drink* head) {
    if (head == NULL || head->next == NULL) return head;

    struct Drink* current;
    struct Drink* lastSorted = NULL;
    int swapped;

    do {
        swapped = 0;
        current = head;

        while (current->next != lastSorted) {
            if (strcmp(current->name, current->next->name) > 0) {
                // ��� ������ ��ȯ
                char tempName[50];
                float tempPrice;

                strcpy(tempName, current->name);
                tempPrice = current->price;

                strcpy(current->name, current->next->name);
                current->price = current->next->price;

                strcpy(current->next->name, tempName);
                current->next->price = tempPrice;

                swapped = 1;
            }
            current = current->next;
        }
        lastSorted = current;
    } while (swapped);

    return head;
}

// ����Ʈ�� ���ݼ����� �����ϴ� �Լ�
struct Drink* sortByPrice(struct Drink* head) {
    if (head == NULL || head->next == NULL) return head;

    struct Drink* current;
    struct Drink* lastSorted = NULL;
    int swapped;

    do {
        swapped = 0;
        current = head;

        while (current->next != lastSorted) {
            if (current->price > current->next->price) {
                // ��� ������ ��ȯ
                char tempName[50];
                float tempPrice;

                strcpy(tempName, current->name);
                tempPrice = current->price;

                strcpy(current->name, current->next->name);
                current->price = current->next->price;

                strcpy(current->next->name, tempName);
                current->next->price = tempPrice;

                swapped = 1;
            }
            current = current->next;
        }
        lastSorted = current;
    } while (swapped);

    return head;
}

// ���� �Լ�
int main() {
    struct Drink* head = NULL;
    struct Drink* tail = NULL;
    FILE* file = fopen("drink.txt", "r");

    if (file == NULL) {
        printf("������ �� �� �����ϴ�.\n");
        return 1;
    }

    char name[50];
    float price;

    // ���Ͽ��� ������ �б�
    while (fscanf(file, "%s %f", name, &price) != EOF) {
        struct Drink* newDrink = createDrink(name, price);
        if (head == NULL) {
            head = newDrink;
            tail = newDrink;
        }
        else {
            tail->next = newDrink;
            tail = newDrink;
        }
    }
    fclose(file);

    // �̸��� ����
    struct Drink* nameSorted = sortByName(head);
    printf("�̸��� ���� ���:\n");
    printList(nameSorted);

    // ���ݼ� ����
    struct Drink* priceSorted = sortByPrice(head);
    printf("���ݼ� ���� ���:\n");
    printList(priceSorted);

    return 0;
}
