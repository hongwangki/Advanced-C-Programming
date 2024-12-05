#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<limits.h> // INT_MAX ���

// �޴� �׸� ����ü ����
typedef struct {
	int id;            // �޴� ID
	char name[50];     // �޴� �̸�
	int price;         // �޴� ����
	int stock;         // �޴� ���
} MenuItem;

// �޴� ����Ʈ ���� ����ü ����
typedef struct {
	MenuItem** drink_menu;  // ���� �޴� �迭
	MenuItem** snack_menu;  // ���� �޴� �迭
	int drink_count;        // ���� �޴� ��
	int snack_count;        // ���� �޴� ��
} MenuList;

typedef struct {
	MenuItem* item; // �ֹ��� �޴� �׸�
} Order;
// ���� ���� �ʱ�ȭ
MenuList menu_list = { NULL, NULL, 0, 0 };
MenuItem** order_list = NULL; // �ֹ� ���
int order_count = 0;          // �� �ֹ� ��
int asset = 0;                // ���� �ڻ�

// ����� �Ǵ� ������ ��� ���� �Լ�
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
	FILE* file = fopen("receipt.txt", "w"); // ���� ����
	if (!file) { // ���� ���� ���� ����ó��
		perror("Failed to open file\n");
		return;
	}
	fprintf(file, "======receipt======\n");

	// �ֹ� ���� ���
	for (int i = 0; i < order_count; i++) {
		printf("%s  %d\n",
			order_list[i].item->name,
			order_list[i].item->price);

		fprintf(file, "%s  %d\n",
			order_list[i].item->name,
			order_list[i].item->price);
	}

	// �� ���� ���
	printf("\ntotal_price %d\n", total_price);
	fprintf(file, "\ntotal_price %d\n", total_price);

	printf("===================\n");
	fprintf(file, "=================\n");

	fclose(file); // ���� �ݱ�
}

// ���� ��� �Լ�
void service_mode() {
	int id, num;
	Order* order_list = NULL; // �ֹ� ����Ʈ �ʱ�ȭ
	int order_count = 0;
	int total_price = 0;

	while (1) {
		printf("\nType 1 for drink, 2 for snack, 3 for buy : ");
		scanf("%d", &num);

		if (num == 1) { // ���� ����
			printf("Type drink id to buy : ");
			scanf("%d", &id);

			// ID ��ȿ�� �˻�
			if (menu_list.drink_count >= id && id > 0) {
				MenuItem* select_item = menu_list.drink_menu[id - 1];
				if (select_item->stock > 0) { // ��� Ȯ��
					select_item->stock--;
					total_price += select_item->price;
					asset += select_item->price;

					order_list = realloc(order_list, (order_count + 1) * sizeof(Order));
					if (!order_list) { // �޸� ���Ҵ� ���� ����ó��
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
		else if (num == 2) { // ���� ����
			printf("Type snack id to buy : ");
			scanf("%d", &id);

			// ID ��ȿ�� �˻�
			if (menu_list.snack_count >= id && id > 0) {
				MenuItem* select_item = menu_list.snack_menu[id - 1];
				if (select_item->stock > 0) { // ��� Ȯ��
					select_item->stock--;
					total_price += select_item->price;
					asset += select_item->price;

					order_list = realloc(order_list, (order_count + 1) * sizeof(Order));
					if (!order_list) { // �޸� ���Ҵ� ���� ����ó��
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
		else if (num == 3) { // ���� �Ϸ�
			print_receipt(order_list, order_count, total_price);
			break;
		}
		else { // �߸��� �Է� ó��
			printf("Error : Wrong input for type select!\n");
		}
	}
	free(order_list); // �޸� ����
}




//ǰ�� �޴� ��� �Լ�
void sold_out_print() {
	printf("\n======Sold out Menu======\n");
	//���� ǰ�� �޴� ���
	for (int i = 0; i < menu_list.drink_count; i++) {
		if (menu_list.drink_menu[i]->stock == 0) {
			printf("%d  %s   %d   %d\n",
				menu_list.drink_menu[i]->id,
				menu_list.drink_menu[i]->name,
				menu_list.drink_menu[i]->price,
				menu_list.drink_menu[i]->stock);
		}
	}

	//���� ǰ�� �޴� ���
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

//��� ȸ�� ��ǰ ��� �Լ�
void print_list(const char* filename) {
	char name[50];
	int price, stock;
	int id = 1;
	//ȸ�� ���� ����
	FILE* file = fopen(filename, "r");
	if (!file) {
		perror("Failed to open file");
		return;
	}

	//ȸ�� ����Ʈ ���
	char buffer[100];
	printf("\n=====%s List======\n", filename);
	while (fgets(buffer, sizeof(buffer), file)) { // �� �پ� �б�
		sscanf(buffer, "%[^\t]\t%d\t%d", name, &price, &stock);
		printf("%d : %s  %d  %d\n", id++, name, price, stock);
	}
	printf("=============================\n");
	fclose(file);
}

//���� �ֹ��� ��� ��� �Լ�
void order_print() {
	if (order_count == 0) {
		printf("�ֹ��� �����ϴ�.\n");
		return;
	}

	printf("\n====== Order List ======\n");
	for (int i = 0; i < order_count; i++) {
		printf("%s   %d   %d\n", order_list[i]->name, order_list[i]->price, order_list[i]->stock);
	}
	printf("Remaining asset: %d\n", asset);
	printf("========================\n");
}

//��� ȸ�纰 �ּҰ� ã�� �Լ�
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

	//���ݵ��� ���ϸ� �ּҰ� ����
	while (fgets(buffer, sizeof(buffer), file)) { // �� �پ� �б�
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
	int total_cost = 0; // �� ��� �ʱ�ȭ
	int stock_count = 0; // ��� 0�� �׸��� ������ ���� ���� ���� �ʱ�ȭ

	// ��� 0�� ���� �׸� ���
	for (int i = 0; i < menu_list.drink_count; i++) {
		if (menu_list.drink_menu[i]->stock == 0) {
			stock_count++; // ��� 0�� �׸� ���� ����
		}
	}
	// ��� 0�� ���� �׸� ���
	for (int i = 0; i < menu_list.snack_count; i++) {
		if (menu_list.snack_menu[i]->stock == 0) {
			stock_count++; // ��� 0�� �׸� ���� ����
		}
	}

	// ��� 0�� �׸��� 3�� �̸��̸� �ֹ����� ����
	if (stock_count < 3) {
		printf("��� 0�� �׸��� 3�� �̻� �־�� �մϴ�.\n");
		return; // �Լ� ����
	}

	// ���� ������ ���� �ݺ�
	while (1) {
		int purchased = 0; // ���� ���� ���� Ȯ��
		for (int i = 0; i < menu_list.drink_count; i++) {
			if (menu_list.drink_menu[i]->stock == 0) {
				// �� ���Ͽ��� �ּ� ���� ã��
				int min_price = find_min("coupang.txt", menu_list.drink_menu[i]->name);
				int temp_price = find_min("11st.txt", menu_list.drink_menu[i]->name);
				if (temp_price < min_price) min_price = temp_price;

				temp_price = find_min("gmarket.txt", menu_list.drink_menu[i]->name);
				if (temp_price < min_price) min_price = temp_price;

				if (min_price == INT_MAX) continue; // ��ȿ�� ������ ������ �ǳʶ�

				// 5�� ���� �õ�, �ڻ� ���� �� ������ ��ŭ ����
				int max_quantity = 5;
				int item_cost = min_price * max_quantity;

				if (total_cost + item_cost > asset) {
					max_quantity = (asset - total_cost) / min_price;
					item_cost = min_price * max_quantity;
					if (max_quantity == 0) continue; // ������ �� �ִ� ������ ������ �ǳʶ�
				}

				// ���� Ȯ��
				total_cost += item_cost;
				menu_list.drink_menu[i]->stock += max_quantity;

				// �ֹ� ���� ������Ʈ
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

				// �ֹ� �׸� ���� �� �ּ� ���� ����/���� ����
				*order_list[order_count] = *menu_list.drink_menu[i];
				order_list[order_count]->stock = max_quantity; // ������ ����
				order_list[order_count]->price = min_price;    // �ּ� ���� ���� ����
				order_count++;

				purchased = 1; // ���� ����
			}
		}

		// ���Ÿ� �� �̻� �� �� ������ ����
		if (!purchased) break;
	}

	asset -= total_cost; // ���� �ڻ� ���
	printf("�� ���: %d, ���� �ڻ�: %d\n", total_cost, asset);
}



//admin fun
void admin_mode() {
	//ǰ�� ���
	sold_out_print();

	//��� ȸ�纰 ��ǰ ���
	print_list("coupang.txt");
	print_list("11st.txt");
	print_list("gmarket.txt");

	//��� ����
	restock();

	//��� ���
	order_print();


	//������Ʈ �޴� ���
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
	//������ ���Ͽ��� ��������
	FILE* file = fopen("asset.txt", "r");
	if (file) {
		fscanf(file, "%d", &asset);
		fclose(file);
	}
	printf("init asset : %d\n", asset);

	int mode = checkID();

	//user ����϶�
	if (mode == 0) {
		reset_menu_drink();
		reset_menu_snack();
		service_mode();
		for (int i = 0; i < menu_list.drink_count; i++) free(menu_list.drink_menu[i]);
		free(menu_list.drink_menu);
		for (int i = 0; i < menu_list.snack_count; i++) free(menu_list.snack_menu[i]);
		free(menu_list.snack_menu);
	}
	//admin ����϶�
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
	if (file1) { // ���� ���� ���� ���� Ȯ��
		fprintf(file1, "%d", asset); // ���� �ݾ� ����
		fclose(file1); // ���� �ݱ�
	}
}