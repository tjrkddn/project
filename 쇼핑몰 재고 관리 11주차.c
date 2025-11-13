#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> // malloc, free, exit 함수를 위해 추가
#define MAX_PRODUCTS 100

void all_stock(int stock[], int inventory[], int num_products) {
	int type, ID;
	int quantity;
	printf("입고수량 입력:전체 상품 입고수량 입력 1, 개별 상품 입력 2를 선택.\n>");
	scanf("%d", &type);

	if (type == 1) {
		printf("상품 1부터 %d까지의 입고수량을 순서대로 입력하세요 (예: 10 12 9 4 9)\n>", num_products);
		for (int i = 0; i < num_products; i++) {
			scanf("%d", &quantity);
			stock[i] += quantity;
			inventory[i] += quantity;
		}
	}
	else if (type == 2) {
		printf("상품ID:");
		scanf("%d", &ID);
		if (ID < 1 || ID > num_products) {
			printf("상품ID를 1에서 %d 사이로 입력해주세요.\n", num_products);
			return;
		}
		printf("입고수량:");
		scanf("%d", &quantity);
		stock[ID - 1] += quantity;
		inventory[ID - 1] += quantity;
	}
}

void sell_stock(int sales[], int inventory[], int num_products) {
	int type, ID;
	int quantity;
	printf("판매수량 입력:전체 상품 판매수량 입력 1, 개별 상품 입력 2를 선택.\n>");
	scanf("%d", &type);

	if (type == 1) {
		printf("상품 1부터 %d까지의 판매수량을 순서대로 입력하세요 (예: 10 12 9 4 9)\n>", num_products);
		for (int i = 0; i < num_products; i++) {
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
		if (ID < 1 || ID > num_products) {
			printf("상품ID를 1에서 %d 사이로 입력해주세요.\n", num_products);
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

void information(int inventory[], int sales[], int stock[], char** product_names, int num_products) {
	int total_sales = 0;
	int total_stock = 0;
	int max_sales = -1, min_sales = -1;
	int max_sales_id = -1, min_sales_id = -1;

	printf("재고수량 : ");
	for (int i = 0; i < num_products; i++) {
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

	for (int i = 0; i < num_products; i++) {
		if (inventory[i] <= 2) { // 재고 부족 기준을 2개 이하로 가정
			printf("상품 ID %d : 상품명 : %s 재고부족(%d)\n", i + 1, product_names[i], inventory[i]);
		}
	}
}

void input_product_names(char** product_names, int num_products) {
	for (int i = 0; i < num_products; i++) {
		printf("ID %d 상품명 : ", i + 1);
		scanf("%s", product_names[i]);
	}
}

void save_data(int stock[], int sales[], int inventory[], char** product_names, int num_products) {
	FILE* fp = fopen("products.txt", "w");
	if (fp == NULL) {
		printf("파일 저장에 실패했습니다.\n");
		return;
	}

	fprintf(fp, "%d\n", num_products); // 상품 개수 저장

	for (int i = 0; i < num_products; i++) { fprintf(fp, "%d ", stock[i]); }
	fprintf(fp, "\n");
	for (int i = 0; i < num_products; i++) { fprintf(fp, "%d ", sales[i]); }
	fprintf(fp, "\n");
	for (int i = 0; i < num_products; i++) { fprintf(fp, "%d ", inventory[i]); }
	fprintf(fp, "\n");
	for (int i = 0; i < num_products; i++) { fprintf(fp, "%s\n", product_names[i]); }

	fclose(fp);
	printf("상품 정보가 'products.txt' 파일에 저장되었습니다.\n");
}

// 데이터를 불러올 때, 파일에 저장된 상품 수에 맞춰 메모리를 재할당해야 하므로 포인터의 주소를 받습니다.
void load_data(int** stock, int** sales, int** inventory, char*** product_names, int* num_products_ptr) {
	FILE* fp = fopen("products.txt", "r");
	if (fp == NULL) {
		printf("저장된 상품 정보 파일을 찾을 수 없습니다.\n");
		return;
	}

	// 기존에 할당된 메모리가 있다면 해제
	if (*stock) free(*stock);
	if (*sales) free(*sales);
	if (*inventory) free(*inventory);
	if (*product_names) {
		for (int i = 0; i < *num_products_ptr; i++) {
			free((*product_names)[i]);
		}
		free(*product_names);
	}

	fscanf(fp, "%d", num_products_ptr); // 파일에서 상품 개수 읽기
	int num_products = *num_products_ptr;

	// 새 상품 개수에 맞게 메모리 동적 할당
	*stock = (int*)malloc(sizeof(int) * num_products);
	*sales = (int*)malloc(sizeof(int) * num_products);
	*inventory = (int*)malloc(sizeof(int) * num_products);
	*product_names = (char**)malloc(sizeof(char*) * num_products);
	for (int i = 0; i < num_products; i++) {
		(*product_names)[i] = (char*)malloc(sizeof(char) * 50);
	}

	// 파일에서 데이터 읽기
	for (int i = 0; i < num_products; i++) { fscanf(fp, "%d", &(*stock)[i]); }
	for (int i = 0; i < num_products; i++) { fscanf(fp, "%d", &(*sales)[i]); }
	for (int i = 0; i < num_products; i++) { fscanf(fp, "%d", &(*inventory)[i]); }
	for (int i = 0; i < num_products; i++) {
		// 파일에서 상품명을 읽을 때 공백을 포함할 수 있으므로, 앞의 개행문자를 건너뜁니다.
		fscanf(fp, " %49[^\n]", (*product_names)[i]);
	}

	fclose(fp);
	printf("'products.txt' 파일에서 상품 정보를 가져왔습니다.\n");
}

int main() {
	int* stock = NULL;       // 총 입고량
	int* sales = NULL;       // 총 판매량
	int* inventory = NULL;   // 현재 재고량
	char** product_names = NULL;
	int num_products = 0;

	printf("[쇼핑몰 관리 프로그램]\n");
	printf("관리할 상품의 개수를 입력하세요: ");
	scanf("%d", &num_products);

	if (num_products <= 0) {
		printf("상품 개수는 1 이상이어야 합니다. 프로그램을 종료합니다.\n");
		return 1;
	}

	// 각 배열에 대해 동적 메모리 할당
	stock = (int*)malloc(sizeof(int) * num_products);
	sales = (int*)malloc(sizeof(int) * num_products);
	inventory = (int*)malloc(sizeof(int) * num_products);
	product_names = (char**)malloc(sizeof(char*) * num_products);

	if (!stock || !sales || !inventory || !product_names) {
		printf("메모리 할당에 실패했습니다. 프로그램을 종료합니다.\n");
		exit(1);
	}

	for (int i = 0; i < num_products; i++) {
		product_names[i] = (char*)malloc(sizeof(char) * 50);
		if (!product_names[i]) {
			printf("메모리 할당에 실패했습니다. 프로그램을 종료합니다.\n");
			exit(1);
		}
		// 메모리 초기화
		stock[i] = 0;
		sales[i] = 0;
		inventory[i] = 0;
		sprintf(product_names[i], "상품%d", i + 1); // 기본 상품명 설정
	}

	int choice;
	while (1) {
		printf("\n원하는 메뉴를 선택하세요.(1.입고, 2.판매, 3.상품현황, 4.상품명 입력, 5.상품정보저장, 6.상품정보가져오기, 7.종료)\n>");
		scanf("%d", &choice);
		switch (choice) {
		case 1:
			all_stock(stock, inventory, num_products); // 입고 함수 호출
			break;
		case 2:
			sell_stock(sales, inventory, num_products); // 판매 함수 호출
			break;
		case 3:
			information(inventory, sales, stock, product_names, num_products); // 현황 함수 호출
			break;
		case 4:
			input_product_names(product_names, num_products);
			break;
		case 5:
			save_data(stock, sales, inventory, product_names, num_products);
			break;
		case 6:
			load_data(&stock, &sales, &inventory, &product_names, &num_products);
			break;
		case 7:
			printf("프로그램을 종료합니다.\n");
			// 할당된 메모리 해제
			for (int i = 0; i < num_products; i++) {
				free(product_names[i]);
			}
			free(product_names);
			free(inventory);
			free(sales);
			free(stock);
			return 0;
		default:
			printf("다시 입력해주세요.\n");
			break;
		}
	}

	return 0;
}
