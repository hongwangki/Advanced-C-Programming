#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    FILE* Fw;
    char** food;     // �޴� �̸��� ������ ������ �迭
    int* price;      // ������ ������ ���� �迭
    char temp[50];
    int num;
    int orderCount = 0; // �ֹ��� �޴� ��
    int totalCost = 0;  // �� ���� �ݾ�
    int orderCapacity = 10; // �ֹ� ��ȣ ������ ���� �ӽ� �迭 ũ��
    int* orders = (int*)malloc(orderCapacity * sizeof(int)); // �ֹ� ��ȣ�� �������� ������ �迭

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
        printf("�޴��� ������, �ֹ��Ϸ�� 0�� �������� : ");
        scanf("%d", &num);
        if (num == 0) {
            break;
        }

        if (num < 1 || num > 9) {
            printf("�ֹ���ȣ�� �߸��Ǿ����ϴ� �ٽ� �Է��ϼ��� : \n");
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
        printf("%s, �ֹ� �޾ҽ��ϴ�\n",food[num - 1]);
    }

    // receipt 
    FILE* receipt = fopen("receipt.txt", "w");
    if (receipt == NULL) {
        perror("������ ������ �� �� �����ϴ�");
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
    fprintf(receipt, "\n���� �ݾ� : % d\n", totalCost);
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
