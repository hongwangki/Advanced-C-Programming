#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* Fw;
    char** food;     // 메뉴 이름을 저장할 포인터 배열
    int* price;      // 가격을 저장할 동적 배열
    char temp[50];
    int num;
    int orderCount = 0; // 주문한 메뉴 수
    int totalCost = 0;  // 총 결제 금액
    int orderCapacity = 10; // 주문 번호 저장을 위한 임시 배열 크기
    int* orders = (int*)malloc(orderCapacity * sizeof(int)); // 주문 번호를 동적으로 저장할 배열

    if (orders == NULL) {
        perror("mem malloc fail");
        return 1;
    }

    // file open
    Fw = fopen("menu.txt", "r");
    if (Fw == NULL) {
        perror("files dont open");
        free(orders); // free orders
        return 1;
    }

    // malloc
    food = (char**)malloc(9 * sizeof(char*));
    price = (int*)malloc(9 * sizeof(int));

    if (food == NULL || price == NULL) {
        perror("mem malloc fail");
        fclose(Fw);
        free(orders); //free orders
        return 1;
    }

    // menu read
    printf("[MENU                           PRICE]\n");
    for (int i = 0; i < 9; i++) {
        food[i] = (char*)malloc(30 * sizeof(char)); // menu malloc 
        if (fgets(temp, sizeof(temp), Fw) != NULL) {
            sscanf(temp, "%29[^:] : %d", food[i], &price[i]);
        }
        printf("[%d] %-27s %d\n", i + 1, food[i], price[i]);
    }

    fclose(Fw); // close fw

    while (1) {
        printf("메뉴를 고르세요, 주문완료는 0을 누르세요 : ");
        scanf("%d", &num);
        if (num == 0) {
            break;
        }

        if (num < 1 || num > 9) {
            printf("주문번호가 잘못되었습니다 다시 입력하세요 : \n");
            continue; // input 
        }

        if (orderCount >= orderCapacity) {
            orderCapacity *= 2; // arr size up
            orders = (int*)realloc(orders, orderCapacity * sizeof(int));
            if (orders == NULL) {
                perror("mem malloc fail");
                break;
            }
        }

        orders[orderCount++] = num; // save order
        totalCost += price[num - 1]; // total price update
        printf("%s, 주문 받았습니다\n",food[num - 1]);
    }

    // receipt 
    FILE* receipt = fopen("receipt.txt", "w");
    if (receipt == NULL) {
        perror("영수증 파일을 열 수 없습니다");
        free(orders); // free drders
        for (int i = 0; i < 9; i++) {
            free(food[i]); // free food
        }
        free(food);
        free(price);
        return 1;
    }

    for (int i = 0; i < orderCount; i++) {
        int itemIndex = orders[i] - 1; // index change
        fprintf(receipt, "%s : %d\n", food[itemIndex], price[itemIndex]);
    }
    fprintf(receipt, "\n결제 금액 : % d\n", totalCost);
    fclose(receipt); // receipt close

    // free orders
    free(orders);
    for (int i = 0; i < 9; i++) {
        free(food[i]); // food free
    }
    free(food);
    free(price);

    return 0;
}
