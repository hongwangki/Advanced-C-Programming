#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 메뉴 아이템 구조체
typedef struct {
    int id;        // 메뉴 ID
    char name[50]; // 메뉴 이름
    int price;     // 가격
    int stock;     // 재고
} MenuItem;

// 메뉴 리스트 구조체
typedef struct {
    MenuItem** drink_menu; // 음료 메뉴
    MenuItem** snack_menu; // 스낵 메뉴
    int drink_count;       // 음료 메뉴 수
    int snack_count;       // 스낵 메뉴 수
} MenuList;

// 주문 구조체
typedef struct {
    MenuItem* item; // 주문된 메뉴 아이템
} Order;

// 전역 변수로 메뉴 리스트 관리
MenuList menu_list = { NULL, NULL, 0, 0 };

// 모드 선택 및 ID 확인 함수
int checkID() {
    int mode;
    char id[10]; // ID 입력 버퍼
    printf("Select Mode (user or admin) : ");
    scanf("%9s", id); // ID 입력 (최대 9글자)

    if (strcmp(id, "user") == 0) { // "user" 입력 시
        mode = 0;
        printf("User Mode\n");
    }
    else if (strcmp(id, "admin") == 0) { // "admin" 입력 시
        mode = 1;
        printf("Admin Mode\n");
    }
    else { // 잘못된 입력 처리
        mode = -1;
        printf("Error : Wrong Input!\n");
    }
    return mode;
}

// 음료 메뉴 초기화 함수
void reset_menu_drink() {
    FILE* file = fopen("drink2.txt", "r"); // 음료 파일 열기
    if (!file) { // 파일 열기 실패 시 오류 처리
        perror("Error: Unable to open drink2.txt");
        return;
    }

    // 이전 메뉴 데이터 초기화
    menu_list.drink_count = 0;
    menu_list.drink_menu = NULL;

    char buffer[100]; // 파일 입력 버퍼

    while (fgets(buffer, sizeof(buffer), file)) { // 파일 읽기
        MenuItem* item = malloc(sizeof(MenuItem)); // 새로운 메뉴 아이템 메모리 할당
        if (!item) { // 메모리 할당 실패 처리
            perror("Error: Memory allocation failed");
            fclose(file);
            return;
        }

        // 메뉴 정보 파싱
        if (sscanf(buffer, "%[^\t]\t%d\t%d", item->name, &item->price, &item->stock) != 3) {
            printf("Error: Invalid format in drink2.txt\n");
            free(item);
            continue;
        }
        item->id = menu_list.drink_count + 1; // 메뉴 ID 설정

        // 메뉴 리스트에 추가
        menu_list.drink_menu = realloc(menu_list.drink_menu, (menu_list.drink_count + 1) * sizeof(MenuItem*));
        if (!menu_list.drink_menu) { // realloc 실패 처리
            perror("Error: Memory allocation failed");
            free(item);
            fclose(file);
            return;
        }
        menu_list.drink_menu[menu_list.drink_count] = item;
        menu_list.drink_count++;
    }
    fclose(file); // 파일 닫기

    // 음료 메뉴 출력
    printf("\n======drink menu=====\n");
    for (int i = 0; i < menu_list.drink_count; i++) {
        if (menu_list.drink_menu[i]->stock > 0) { // 재고가 있는 메뉴만 출력
            printf("%d  %s   %d   %d\n",
                menu_list.drink_menu[i]->id,
                menu_list.drink_menu[i]->name,
                menu_list.drink_menu[i]->price,
                menu_list.drink_menu[i]->stock);
        }
    }
    printf("=====================\n");
}

// 스낵 메뉴 초기화 함수
void reset_menu_snack() {
    FILE* file = fopen("snack2.txt", "r"); // 스낵 파일 열기
    if (!file) { // 파일 열기 실패 시 오류 처리
        perror("Error: Unable to open snack2.txt");
        return;
    }

    // 이전 메뉴 데이터 초기화
    menu_list.snack_count = 0;
    menu_list.snack_menu = NULL;

    char buffer[100]; // 파일 입력 버퍼

    while (fgets(buffer, sizeof(buffer), file)) { // 파일 읽기
        MenuItem* item = malloc(sizeof(MenuItem)); // 새로운 메뉴 아이템 메모리 할당
        if (!item) { // 메모리 할당 실패 처리
            perror("Error: Memory allocation failed");
            fclose(file);
            return;
        }

        // 메뉴 정보 파싱
        if (sscanf(buffer, "%[^\t]\t%d\t%d", item->name, &item->price, &item->stock) != 3) {
            printf("Error: Invalid format in snack2.txt\n");
            free(item);
            continue;
        }
        item->id = menu_list.snack_count + 1; // 메뉴 ID 설정

        // 메뉴 리스트에 추가
        menu_list.snack_menu = realloc(menu_list.snack_menu, (menu_list.snack_count + 1) * sizeof(MenuItem*));
        if (!menu_list.snack_menu) { // realloc 실패 처리
            perror("Error: Memory allocation failed");
            free(item);
            fclose(file);
            return;
        }
        menu_list.snack_menu[menu_list.snack_count] = item;
        menu_list.snack_count++;
    }
    fclose(file); // 파일 닫기

    // 스낵 메뉴 출력
    printf("\n======snack menu=====\n");
    for (int i = 0; i < menu_list.snack_count; i++) {
        if (menu_list.snack_menu[i]->stock > 0) { // 재고가 있는 메뉴만 출력
            printf("%d  %s   %d   %d\n",
                menu_list.snack_menu[i]->id,
                menu_list.snack_menu[i]->name,
                menu_list.snack_menu[i]->price,
                menu_list.snack_menu[i]->stock);
        }
    }
    printf("=====================\n");
}

// 영수증 출력 함수
void print_receipt(Order* order_list, int order_count, int total_price) {
    printf("\n======receipt======\n");
    FILE* file = fopen("receipt.txt", "w"); // 영수증 파일 생성
    if (!file) { // 파일 열기 실패 처리
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

// 서비스 모드 실행 함수
void service_mode() {
    int id, num;
    Order* order_list = NULL; // 주문 리스트
    int order_count = 0;      // 주문 수
    int total_price = 0;      // 총 결제 금액

    while (1) {
        printf("\nType 1 for drink, 2 for snack, 3 for buy : ");
        scanf("%d", &num);

        if (num == 1) { // 음료 주문
            printf("Type drink id to buy : ");
            scanf("%d", &id);

            if (id > 0 && id <= menu_list.drink_count) {
                MenuItem* select_item = menu_list.drink_menu[id - 1];
                if (select_item->stock > 0) {
                    select_item->stock--;
                    total_price += select_item->price;

                    order_list = realloc(order_list, (order_count + 1) * sizeof(Order));
                    if (!order_list) { // realloc 실패 처리
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
        else if (num == 2) { // 스낵 주문
            printf("Type snack id to buy : ");
            scanf("%d", &id);

            if (id > 0 && id <= menu_list.snack_count) {
                MenuItem* select_item = menu_list.snack_menu[id - 1];
                if (select_item->stock > 0) {
                    select_item->stock--;
                    total_price += select_item->price;

                    order_list = realloc(order_list, (order_count + 1) * sizeof(Order));
                    if (!order_list) { // realloc 실패 처리
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
        else if (num == 3) { // 구매 완료
            print_receipt(order_list, order_count, total_price);
            break;
        }
        else {
            printf("Error : Wrong input for type select!\n");
        }
    }
    free(order_list); // 주문 리스트 메모리 해제
}

// 메인 함수
int main() {
    int mode = checkID(); // 사용자 모드 확인

    if (mode == 0) { // 사용자 모드 실행
        reset_menu_drink(); // 음료 메뉴 초기화
        reset_menu_snack(); // 스낵 메뉴 초기화
        service_mode(); // 서비스 모드 실행

        // 메모리 해제
        for (int i = 0; i < menu_list.drink_count; i++) free(menu_list.drink_menu[i]);
        free(menu_list.drink_menu);
        for (int i = 0; i < menu_list.snack_count; i++) free(menu_list.snack_menu[i]);
        free(menu_list.snack_menu);
    }

    return 0;
}
