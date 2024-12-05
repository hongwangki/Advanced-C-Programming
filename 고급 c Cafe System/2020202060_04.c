#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h> // INT_MAX 사용

// 메뉴 항목 구조체 정의
typedef struct {
	int id;            // 메뉴 ID
	char name[50];     // 메뉴 이름
	int price;         // 메뉴 가격
	int stock;         // 메뉴 재고
} MenuItem;

// 메뉴 리스트 관리 구조체 정의
typedef struct {
	MenuItem** drink_menu;  // 음료 메뉴 배열
	MenuItem** snack_menu;  // 간식 메뉴 배열
	int drink_count;        // 음료 메뉴 수
	int snack_count;        // 간식 메뉴 수
} MenuList;

typedef struct {
	MenuItem* item; // 주문된 메뉴 항목
} Order;
// 전역 변수 초기화
MenuList menu_list = { NULL, NULL, 0, 0 };
MenuItem** order_list = NULL; // 주문 목록
int order_count = 0;          // 총 주문 수
int asset = 0;                // 현재 자산

// 사용자 또는 관리자 모드 선택 함수
int checkID() {
	int mode;
	char id[10];
	printf("Select Mode (user or admin) : ");
	scanf("%9s", id);

	if (strcmp(id, "user") == 0) {
		mode = 0;
		printf("User Mode\n");
	}
	else if (strcmp(id, "admin") == 0) {
		mode = 1;
		printf("Admin Mode\n");
	}
	else {
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
	FILE* file = fopen("receipt.txt", "w"); // 파일 열기
	if (!file) { // 파일 열기 실패 예외처리
		perror("Failed to open file\n");
		return;
	}
	fprintf(file, "======receipt======\n");

	// 주문 내역 출력
	for (int i = 0; i < order_count; i++) {
		printf("%s  %d\n",
			order_list[i].item->name,
			order_list[i].item->price);

		fprintf(file, "%s  %d\n",
			order_list[i].item->name,
			order_list[i].item->price);
	}

	// 총 가격 출력
	printf("\ntotal_price %d\n", total_price);
	fprintf(file, "\ntotal_price %d\n", total_price);

	printf("===================\n");
	fprintf(file, "=================\n");

	fclose(file); // 파일 닫기
}

// 서비스 모드 함수
void service_mode() {
	int id, num;
	Order* order_list = NULL; // 주문 리스트 초기화
	int order_count = 0;
	int total_price = 0;

	while (1) {
		printf("\nType 1 for drink, 2 for snack, 3 for buy : ");
		scanf("%d", &num);

		if (num == 1) { // 음료 구매
			printf("Type drink id to buy : ");
			scanf("%d", &id);

			// ID 유효성 검사
			if (menu_list.drink_count >= id && id > 0) {
				MenuItem* select_item = menu_list.drink_menu[id - 1];
				if (select_item->stock > 0) { // 재고 확인
					select_item->stock--;
					total_price += select_item->price;
					asset += select_item->price;

					order_list = realloc(order_list, (order_count + 1) * sizeof(Order));
					if (!order_list) { // 메모리 재할당 실패 예외처리
						perror("Memory allocation failed\n");
						break;
					}
					order_list[order_count].item = select_item;
					order_count++;
				}
				else {
					printf("out of stock!\n");
				}
			}
			else {
				printf("Error : Not enough ID for drink!\n");
			}

		}
		else if (num == 2) { // 간식 구매
			printf("Type snack id to buy : ");
			scanf("%d", &id);

			// ID 유효성 검사
			if (menu_list.snack_count >= id && id > 0) {
				MenuItem* select_item = menu_list.snack_menu[id - 1];
				if (select_item->stock > 0) { // 재고 확인
					select_item->stock--;
					total_price += select_item->price;
					asset += select_item->price;

					order_list = realloc(order_list, (order_count + 1) * sizeof(Order));
					if (!order_list) { // 메모리 재할당 실패 예외처리
						perror("Memory allocation failed\n");
						break;
					}
					order_list[order_count].item = select_item;
					order_count++;
				}
				else {
					printf("out of stock!\n");
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
		else { // 잘못된 입력 처리
			printf("Error : Wrong input for type select!\n");
		}
	}
	free(order_list); // 메모리 해제
}




//품절 메뉴 출력 함수
void sold_out_print() {
	printf("\n======Sold out Menu======\n");
	//음료 품절 메뉴 출력
	for (int i = 0; i < menu_list.drink_count; i++) {
		if (menu_list.drink_menu[i]->stock == 0) {
			printf("%d  %s   %d   %d\n",
				menu_list.drink_menu[i]->id,
				menu_list.drink_menu[i]->name,
				menu_list.drink_menu[i]->price,
				menu_list.drink_menu[i]->stock);
		}
	}

	//간식 품절 메뉴 출력
	for (int i = 0; i < menu_list.snack_count; i++) {
		if (menu_list.snack_menu[i]->stock == 0) {
			printf("%d  %s   %d   %d\n",
				menu_list.snack_menu[i]->id,
				menu_list.snack_menu[i]->name,
				menu_list.snack_menu[i]->price,
				menu_list.snack_menu[i]->stock);
		}
	}
	printf("=======================\n");
}

//재고 회사 물품 출력 함수
void print_list(const char* filename) {
	char name[50];
	int price, stock;
	int id = 1;
	//회사 파일 열기
	FILE* file = fopen(filename, "r");
	if (!file) {
		perror("Failed to open file");
		return;
	}

	//회사 리스트 출력
	char buffer[100];
	printf("\n=====%s List======\n", filename);
	while (fgets(buffer, sizeof(buffer), file)) { // 한 줄씩 읽기
		sscanf(buffer, "%[^\t]\t%d\t%d", name, &price, &stock);
		printf("%d : %s  %d  %d\n", id++, name, price, stock);
	}
	printf("=============================\n");
	fclose(file);
}

//최종 주문된 재고 출력 함수
void order_print() {
	if (order_count == 0) {
		printf("주문이 없습니다.\n");
		return;
	}

	printf("\n====== Order List ======\n");
	for (int i = 0; i < order_count; i++) {
		printf("%s   %d   %d\n", order_list[i]->name, order_list[i]->price, order_list[i]->stock);
	}
	printf("Remaining asset: %d\n", asset);
	printf("========================\n");
}

//재고 회사별 최소값 찾는 함수
int find_min(const char* filename, const char* name) {
	FILE* file = fopen(filename, "r");
	if (!file) {
		perror("Faild file open\n");
		return;
	}

	char s_name[50];
	int price, stock;
	int min_price = INT_MAX;
	char buffer[100];

	//가격들을 비교하며 최소값 도출
	while (fgets(buffer, sizeof(buffer), file)) { // 한 줄씩 읽기
		sscanf(buffer, "%[^\t]\t%d\t%d", s_name, &price, &stock);
		if (strcmp(name, s_name) == 0 && stock >= 5) {
			if (price < min_price) {
				min_price = price;
			}
		}
	}
	fclose(file);
	return min_price;
}
void restock() {
	int total_cost = 0; // 총 비용 초기화
	int stock_count = 0; // 재고가 0인 항목의 개수를 세기 위한 변수 초기화

	// 재고가 0인 음료 항목 계산
	for (int i = 0; i < menu_list.drink_count; i++) {
		if (menu_list.drink_menu[i]->stock == 0) {
			stock_count++; // 재고가 0인 항목 개수 증가
		}
	}
	// 재고가 0인 간식 항목 계산
	for (int i = 0; i < menu_list.snack_count; i++) {
		if (menu_list.snack_menu[i]->stock == 0) {
			stock_count++; // 재고가 0인 항목 개수 증가
		}
	}

	// 재고가 0인 항목이 3개 미만이면 주문하지 않음
	if (stock_count < 3) {
		printf("재고가 0인 항목이 3개 이상 있어야 합니다.\n");
		return; // 함수 종료
	}

	// 구매 가능한 동안 반복
	while (1) {
		int purchased = 0; // 구매 성공 여부 확인
		for (int i = 0; i < menu_list.drink_count; i++) {
			if (menu_list.drink_menu[i]->stock == 0) {
				// 각 파일에서 최소 가격 찾기
				int min_price = find_min("coupang.txt", menu_list.drink_menu[i]->name);
				int temp_price = find_min("11st.txt", menu_list.drink_menu[i]->name);
				if (temp_price < min_price) min_price = temp_price;

				temp_price = find_min("gmarket.txt", menu_list.drink_menu[i]->name);
				if (temp_price < min_price) min_price = temp_price;

				if (min_price == INT_MAX) continue; // 유효한 가격이 없으면 건너뜀

				// 5개 구매 시도, 자산 부족 시 가능한 만큼 구매
				int max_quantity = 5;
				int item_cost = min_price * max_quantity;

				if (total_cost + item_cost > asset) {
					max_quantity = (asset - total_cost) / min_price;
					item_cost = min_price * max_quantity;
					if (max_quantity == 0) continue; // 구매할 수 있는 수량이 없으면 건너뜀
				}

				// 구매 확정
				total_cost += item_cost;
				menu_list.drink_menu[i]->stock += max_quantity;

				// 주문 내역 업데이트
				order_list = realloc(order_list, (order_count + 1) * sizeof(MenuItem*));
				if (!order_list) {
					perror("Memory allocation failed\n");
					return;
				}
				order_list[order_count] = malloc(sizeof(MenuItem));
				if (!order_list[order_count]) {
					perror("Memory allocation failed\n");
					return;
				}

				// 주문 항목 복사 및 최소 구매 가격/수량 저장
				*order_list[order_count] = *menu_list.drink_menu[i];
				order_list[order_count]->stock = max_quantity; // 구매한 수량
				order_list[order_count]->price = min_price;    // 최소 구매 가격 저장
				order_count++;

				purchased = 1; // 구매 성공
			}
		}

		// 구매를 더 이상 할 수 없으면 종료
		if (!purchased) break;
	}

	asset -= total_cost; // 남은 자산 계산
	printf("총 비용: %d, 남은 자산: %d\n", total_cost, asset);
}



//admin fun
void admin_mode() {
	//품절 출력
	sold_out_print();

	//재고 회사별 물품 출력
	print_list("coupang.txt");
	print_list("11st.txt");
	print_list("gmarket.txt");

	//재고 충전
	restock();

	//재고 출력
	order_print();


	//업데이트 메뉴 출력
	printf("\n======Update drink Menu======\n");
	for (int i = 0; i < menu_list.drink_count; i++) {
		if (menu_list.drink_menu[i]->stock > 0) {
			printf("%d  %s   %d   %d\n",
				menu_list.drink_menu[i]->id,
				menu_list.drink_menu[i]->name,
				menu_list.drink_menu[i]->price,
				menu_list.drink_menu[i]->stock);
		}
	}
	printf("=============================\n\n");

	printf("\n======Update snack Menu======\n");

	for (int i = 0; i < menu_list.snack_count; i++) {
		if (menu_list.snack_menu[i]->stock > 0) {
			printf("%d  %s   %d   %d\n",
				menu_list.snack_menu[i]->id,
				menu_list.snack_menu[i]->name,
				menu_list.snack_menu[i]->price,
				menu_list.snack_menu[i]->stock);
		}
	}
	printf("=============================\n");

	for (int i = 0; i < order_count; i++) free(order_list[i]);
	free(order_list);
}

int main() {
	//보유금 파일에서 가져오기
	FILE* file = fopen("asset.txt", "r");
	if (file) {
		fscanf(file, "%d", &asset);
		fclose(file);
	}
	printf("init asset : %d\n", asset);

	int mode = checkID();

	//user 모드일때
	if (mode == 0) {
		reset_menu_drink();
		reset_menu_snack();
		service_mode();
		for (int i = 0; i < menu_list.drink_count; i++) free(menu_list.drink_menu[i]);
		free(menu_list.drink_menu);
		for (int i = 0; i < menu_list.snack_count; i++) free(menu_list.snack_menu[i]);
		free(menu_list.snack_menu);
	}
	//admin 모드일때
	else if (mode == 1) {
		reset_menu_drink();
		reset_menu_snack();
		admin_mode();
		for (int i = 0; i < menu_list.drink_count; i++) free(menu_list.drink_menu[i]);
		free(menu_list.drink_menu);
		for (int i = 0; i < menu_list.snack_count; i++) free(menu_list.snack_menu[i]);
		free(menu_list.snack_menu);
	}

	FILE* file1 = fopen("asset.txt", "w");
	if (file1) { // 파일 열기 성공 여부 확인
		fprintf(file1, "%d", asset); // 보유 금액 저장
		fclose(file1); // 파일 닫기
	}
}