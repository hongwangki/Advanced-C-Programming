#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// 음료와 스낵 메뉴를 저장할 전역 변수
char** drink_menu = NULL; // 음료 메뉴 배열
char** snack_menu = NULL; // 스낵 메뉴 배열
int drink_count = 0;      // 음료 메뉴 수
int snack_count = 0;      // 스낵 메뉴 수

// ID 체크 및 모드 설정 함수
int check_ID() {
    char id[10]; // ID 입력을 위한 배열
    int mode;    // 모드를 저장할 변수

    printf("Mode Select (admin or user) : ");
    scanf("%s", id);  // ID 입력

    if (strcmp(id, "admin") == 0) { // "admin" 입력 시
        printf("Admin mode\n");
        mode = 1;  // 관리자 모드
    }
    else if (strcmp(id, "user") == 0) { // "user" 입력 시
        printf("User mode\n");
        mode = 0;  // 사용자 모드
    }
    else { // 잘못된 입력 처리
        printf("Error : Wrong Input!\n");
        mode = -1; // 오류 모드
    }
    return mode; // 모드 반환
}

// 음료 메뉴 파일 초기화 및 메뉴 로드 함수
void reset_menu_drink() {
    FILE* file = fopen("drink1.txt", "r"); // 음료 메뉴 파일 열기
    if (!file) { // 파일 열기 실패 처리
        perror("file dont open\n");
        return;
    }

    // 이전 메뉴 메모리 해제
    drink_count = 0;
    free(drink_menu);
    drink_menu = NULL;

    char buffer[100]; // 파일의 한 줄을 읽을 버퍼

    while (fgets(buffer, sizeof(buffer), file)) { // 파일을 한 줄씩 읽기
        char* token = strtok(buffer, "\n"); // 줄바꿈 문자 제거
        if (token) {
            // 새로운 메뉴 추가
            drink_menu = realloc(drink_menu, (drink_count + 1) * sizeof(char*));
            if (!drink_menu) { // realloc 실패 처리
                perror("Memory allocation failed");
                fclose(file);
                return;
            }
            drink_menu[drink_count] = malloc(strlen(token) + 1);
            if (!drink_menu[drink_count]) { // malloc 실패 처리
                perror("Memory allocation failed");
                fclose(file);
                return;
            }
            strcpy(drink_menu[drink_count], token);
            drink_count++;
        }
    }
    fclose(file); // 파일 닫기

    // 음료 메뉴 출력
    printf("\n======drink menu=====\n");
    for (int i = 0; i < drink_count; i++) {
        printf("%d  %s\n", i + 1, drink_menu[i]);
    }
    printf("=====================\n");
}

// 스낵 메뉴 파일 초기화 및 메뉴 로드 함수
void reset_menu_snack() {
    FILE* file = fopen("snack1.txt", "r"); // 스낵 메뉴 파일 열기
    if (!file) { // 파일 열기 실패 처리
        perror("file dont open\n");
        return;
    }

    // 이전 메뉴 메모리 해제
    snack_count = 0;
    free(snack_menu);
    snack_menu = NULL;

    char buffer[100]; // 파일의 한 줄을 읽을 버퍼

    while (fgets(buffer, sizeof(buffer), file)) { // 파일을 한 줄씩 읽기
        char* token = strtok(buffer, "\n"); // 줄바꿈 문자 제거
        if (token) {
            // 새로운 메뉴 추가
            snack_menu = realloc(snack_menu, (snack_count + 1) * sizeof(char*));
            if (!snack_menu) { // realloc 실패 처리
                perror("Memory allocation failed");
                fclose(file);
                return;
            }
            snack_menu[snack_count] = malloc(strlen(token) + 1);
            if (!snack_menu[snack_count]) { // malloc 실패 처리
                perror("Memory allocation failed");
                fclose(file);
                return;
            }
            strcpy(snack_menu[snack_count], token);
            snack_count++;
        }
    }
    fclose(file); // 파일 닫기

    // 스낵 메뉴 출력
    printf("\n======snack menu=====\n");
    for (int i = 0; i < snack_count; i++) {
        printf("%d  %s\n", i + 1, snack_menu[i]);
    }
    printf("=====================\n");
}

// 사용자 서비스 모드 함수
void service_mode() {
    int id, num; // 입력 변수
    char** order_list = NULL; // 주문 리스트
    int order_count = 0; // 주문 수

    while (1) {
        printf("\nType 1 for drink, 2 for snack, 3 for buy : ");
        scanf("%d", &num); // 메뉴 선택 입력

        if (num == 1) { // 음료 선택
            printf("Type drink id to buy : ");
            scanf("%d", &id);

            if (id > 0 && id <= drink_count) { // 유효한 ID인지 확인
                order_list = realloc(order_list, (order_count + 1) * sizeof(char*));
                if (!order_list) { // realloc 실패 처리
                    perror("Memory allocation failed");
                    return;
                }
                order_list[order_count] = malloc(strlen(drink_menu[id - 1]) + 1);
                if (!order_list[order_count]) { // malloc 실패 처리
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
        else if (num == 2) { // 스낵 선택
            printf("Type snack id to buy : ");
            scanf("%d", &id);

            if (id > 0 && id <= snack_count) { // 유효한 ID인지 확인
                order_list = realloc(order_list, (order_count + 1) * sizeof(char*));
                if (!order_list) { // realloc 실패 처리
                    perror("Memory allocation failed");
                    return;
                }
                order_list[order_count] = malloc(strlen(snack_menu[id - 1]) + 1);
                if (!order_list[order_count]) { // malloc 실패 처리
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
        else if (num == 3) { // 영수증 출력 및 종료
            printf("\n======receipt======\n");
            for (int i = 0; i < order_count; i++) {
                printf("%s\n", order_list[i]);
            }
            printf("===================\n");
            break;
        }
        else { // 잘못된 입력 처리
            printf("Error : Wrong input for type select!\n");
        }
    }

    // 주문 리스트 메모리 해제
    for (int i = 0; i < order_count; i++) free(order_list[i]);
    free(order_list);
}

// 메인 함수
int main() {
    int mode = check_ID(); // 모드 확인

    if (mode == 0) { // 사용자 모드
        reset_menu_drink(); // 음료 메뉴 로드
        reset_menu_snack(); // 스낵 메뉴 로드
        service_mode(); // 서비스 모드 실행
        // 메뉴 메모리 해제
        for (int i = 0; i < drink_count; i++) free(drink_menu[i]);
        free(drink_menu);
        for (int i = 0; i < snack_count; i++) free(snack_menu[i]);
        free(snack_menu);
    }
}
