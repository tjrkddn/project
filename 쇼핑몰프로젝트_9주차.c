#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#define MAX_PRODUCTS 100
#define NUM_PRODUCTS 5

void all_stock(int stock[], int inventory[]) {
	int type, ID;
	int quantity;
	printf("입고수량 입력:전체 상품 입고수량 입력 1, 개별 상품 입력 2를 선택.\n>");
	scanf("%d", &type);

	if (type == 1) {
		printf("상품 1부터 5까지의 입고수량을 순서대로 입력하세요 (예: 10 12 9 4 9)\n>");
		for (int i = 0; i < NUM_PRODUCTS; i++) {
			scanf("%d", &quantity);
			stock[i] += quantity;
			inventory[i] += quantity;
		}
	}
	else if (type == 2) {
		printf("상품ID:");
		scanf("%d", &ID);
		if (ID < 1 || ID > NUM_PRODUCTS) {
			printf("상품ID를 1에서 5 사이로 입력해주세요.\n");
			return;
		}
		printf("입고수량:");
		scanf("%d", &quantity);
		stock[ID - 1] += quantity;
		inventory[ID - 1] += quantity;
	}
}

void sell_stock(int sales[], int inventory[]) {
	int type, ID;
	int quantity;
	printf("판매수량 입력:전체 상품 판매수량 입력 1, 개별 상품 입력 2를 선택.\n>");
	scanf("%d", &type);

	if (type == 1) {
		printf("상품 1부터 5까지의 판매수량을 순서대로 입력하세요 (예: 10 12 9 4 9)\n>");
		for (int i = 0; i < NUM_PRODUCTS; i++) {
			scanf("%d", &quantity);
			if (inventory[i] < quantity) {
				printf("상품 ID %d: 재고 부족! (현재 재고: %d, 판매 요청: %d)\n", i + 1, inventory[i], quantity);
			}
			else {
				sales[i] += quantity;
				inventory[i] -= quantity;
			}
		}
	}
	else if (type == 2) {
		printf("상품ID:");
		scanf("%d", &ID);
		if (ID < 1 || ID > NUM_PRODUCTS) {
			printf("상품ID를 1에서 5 사이로 입력해주세요.\n");
			return;
		}
		printf("판매수량:");
		scanf("%d", &quantity);
		if (inventory[ID - 1] < quantity) {
			printf("상품 ID %d: 재고 부족! (현재 재고: %d, 판매 요청: %d)\n", ID, inventory[ID - 1], quantity);
		}
		else {
			sales[ID - 1] += quantity;
			inventory[ID - 1] -= quantity;
		}
	}
}

void information(int inventory[], int sales[], int stock[], char product_names[][50]) {
	int total_sales = 0;
	int total_stock = 0;
	int max_sales = -1, min_sales = -1;
	int max_sales_id = -1, min_sales_id = -1;

	printf("재고수량 : ");
	for (int i = 0; i < NUM_PRODUCTS; i++) {
		printf("%d ", inventory[i]);
		total_sales += sales[i];
		total_stock += stock[i];

		if (max_sales == -1 || sales[i] > max_sales) {
			max_sales = sales[i];
			max_sales_id = i + 1;
		}
		if (min_sales == -1 || sales[i] < min_sales) {
			min_sales = sales[i];
			min_sales_id = i + 1;
		}
	}
	printf("\n");

	float sales_rate = (total_stock > 0) ? ((float)total_sales / total_stock) * 100 : 0.0;
	printf("총 판매량 : %d (판매율 %.2f%%)\n", total_sales, sales_rate);

	if (max_sales_id != -1) {
		printf("가장 많이 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n", max_sales_id, product_names[max_sales_id - 1], max_sales);
	}
	if (min_sales_id != -1) {
		printf("가장 적게 판매된 상품 : ID %d, 상품명 : %s, 판매량 %d\n", min_sales_id, product_names[min_sales_id - 1], min_sales);
	}

	for (int i = 0; i < NUM_PRODUCTS; i++) {
		if (inventory[i] <= 2) { // 재고 부족 기준을 2개 이하로 가정
			printf("상품 ID %d : 상품명 : %s 재고부족(%d)\n", i + 1, product_names[i], inventory[i]);
		}
	}
}

void input_product_names(char product_names[][50]) {
	for (int i = 0; i < NUM_PRODUCTS; i++) {
		printf("ID %d 상품명 : ", i + 1);
		scanf("%s", product_names[i]);
	}
}

int main() {
	int stock[NUM_PRODUCTS] = { 0 };       // 총 입고량
	int sales[NUM_PRODUCTS] = { 0 };       // 총 판매량
	int inventory[NUM_PRODUCTS] = { 0 };   // 현재 재고량
	char product_names[NUM_PRODUCTS][50];

	for (int i = 0; i < NUM_PRODUCTS; i++) {
		sprintf(product_names[i], "상품%d", i + 1); // 기본 상품명 설정
	}

	int choice;
	printf("[쇼핑몰 관리 프로그램]\n");
	while (1) {
		printf("\n원하는 메뉴를 선택하세요.(1.입고, 2.판매, 3.상품현황, 4.상품명 입력, 5.종료)\n>");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			all_stock(stock, inventory); // 입고 함수 호출
			break;
		case 2:
			sell_stock(sales, inventory); // 판매 함수 호출
			break;
		case 3:
			information(inventory, sales, stock, product_names); // 현황 함수 호출
			break;
		case 4:
			input_product_names(product_names);
			break;
		case 5:
			printf("프로그램을 종료합니다.\n");
			return 0; // return 0;을 만나면 main 함수가 종료되어 프로그램이 끝남
		default:
			printf("다시 입력해주세요.\n");
			break;
		}
	}

	return 0;
}
