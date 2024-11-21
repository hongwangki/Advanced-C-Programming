#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 구조체 정의
typedef struct {
    int id;
    char name[30];
    float price;
} MenuItem;

// 함수 선언
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

    // 파일에서 메뉴 불러오기
    load_menu_from_file("drink.txt", &drinks, &drinkCount);
    load_menu_from_file("dessert.txt", &desserts, &dessertCount);

    // 주문 반복
    while (1) {
        // 메인 메뉴 출력
        printf("\n1. 음료 주문하기\n2. 디저트 주문하기\n0. 종료\n주문을 선택하세요: ");
        scanf("%d", &choice);

        if (choice == 0) break; // 종료
        else if (choice == 1) { // 음료 주문
            print_menu(drinks, drinkCount, "음료");
            process_order(drinks, drinkCount, drinkOrders, &drinkOrderCount, &total,"음료");
        }
        else if (choice == 2) { // 디저트 주문
            print_menu(desserts, dessertCount, "디저트");
            process_order(desserts, dessertCount, dessertOrders, &dessertOrderCount, &total,"디저트");
        }
        else {
            printf("잘못된 선택입니다. 다시 시도하세요.\n");
        }
    }

    // 영수증 출력
    print_receipt(drinks, drinkOrders, drinkOrderCount, desserts, dessertOrders, dessertOrderCount, total);

    // 동적 메모리 해제
    free(drinks);
    free(desserts);

    return 0;
}

void load_menu_from_file(const char* filename, MenuItem** menu, int* count) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        perror("파일을 열 수 없습니다");
        exit(1);
    }

    // 메뉴 항목 수 계산
    *count = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file)) {
        (*count)++;
    }
    rewind(file);

    // 동적 메모리 할당
    *menu = (MenuItem*)malloc((*count) * sizeof(MenuItem));

    // 파일에서 메뉴 데이터 읽기
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

//메뉴 프린트 함수
void print_menu(MenuItem* menu, int count, const char* type) {
    printf("\n%s 메뉴\n", type);
    for (int i = 0; i < count; i++) {
        printf("[%d] %-15s %.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
}

//주문 받기
void process_order(MenuItem* menu, int count, int* orders, int* orderCount, float* total, const char* type) {
    int id;
        printf("\n주문할 %s ID를 입력하세요 : ", type);
        scanf("%d", &id);
        if (id < 1 || id > count) {
            printf("잘못된 ID입니다. 다시 입력하세요.\n");
        }
        orders[(*orderCount)++] = id;
        *total += menu[id - 1].price;
        printf("%s 주문 완료! 현재 총액: %.2f\n", menu[id - 1].name, *total);
}

//레시피 프린트 함수
void print_receipt(MenuItem* drinks, int* drinkOrders, int drinkOrderCount, MenuItem* desserts, int* dessertOrders, int dessertOrderCount, float total) {
    FILE* receipt = fopen("receipt.txt", "w");
    if (receipt == NULL) {
        perror("영수증 파일을 생성할 수 없습니다.");
        return;
    }

    fprintf(receipt, "===========================\n");
    fprintf(receipt, "          Receipt          \n");
    fprintf(receipt, "===========================\n");

    printf("\n영수증:\n");
    printf("===========================\n");
    printf("          Receipt          \n");
    printf("===========================\n");

    // 음료 출력
    for (int i = 0; i < drinkOrderCount; i++) {
        int id = drinkOrders[i];
        fprintf(receipt, "%s x %d = %.2f\n", drinks[id - 1].name, 1, drinks[id - 1].price);
        printf("%s x %d = %.2f\n", drinks[id - 1].name, 1, drinks[id - 1].price);
    }

    // 디저트 출력
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
    printf("영수증이 receipt.txt에 저장되었습니다.\n");
}
