#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 음료 정보 노드 구조체 정의
struct Drink {
    char name[50];
    float price;
    struct Drink* next;
};

// 새 음료 노드를 생성하는 함수
struct Drink* createDrink(char* name, float price) {
    struct Drink* newDrink = (struct Drink*)malloc(sizeof(struct Drink));
    strcpy(newDrink->name, name);
    newDrink->price = price;
    newDrink->next = NULL;
    return newDrink;
}

// 리스트를 출력하는 함수
void printList(struct Drink* head) {
    struct Drink* current = head;
    while (current != NULL) {
        printf("%s %.2f\n", current->name, current->price);
        current = current->next;
    }
    printf("\n");
}

// 리스트를 이름순으로 정렬하는 함수
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
                // 노드 데이터 교환
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

// 리스트를 가격순으로 정렬하는 함수
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
                // 노드 데이터 교환
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

// 메인 함수
int main() {
    struct Drink* head = NULL;
    struct Drink* tail = NULL;
    FILE* file = fopen("drink.txt", "r");

    if (file == NULL) {
        printf("파일을 열 수 없습니다.\n");
        return 1;
    }

    char name[50];
    float price;

    // 파일에서 데이터 읽기
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

    // 이름순 정렬
    struct Drink* nameSorted = sortByName(head);
    printf("이름순 정렬 결과:\n");
    printList(nameSorted);

    // 가격순 정렬
    struct Drink* priceSorted = sortByPrice(head);
    printf("가격순 정렬 결과:\n");
    printList(priceSorted);

    return 0;
}
