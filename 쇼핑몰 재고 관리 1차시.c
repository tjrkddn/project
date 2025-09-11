#include <stdio.h>
#define MAX_PRODUCTS 100

int main() {
	int ID,product_num;
	int i;
	int stock[MAX_PRODUCTS];
	int sales[MAX_PRODUCTS];
	int invantory[MAX_PRODUCTS];
	printf("상품 개수(종류)입력:");
	scanf("%d", &product_num);

	if (product_num < 1 || product_num>100) {
		printf("상품 개수(종류)는 1에서 100 사이로입력해야합니다.");
	}

	printf("상품 별 입고수량 입력:");
	for (i = 0;i < product_num;i++) {
		scanf("%d", &stock[i]);
	}
	printf("상품 별 판매 수량 입력:");
	for (i = 0;i < product_num;i++) {
		scanf("%d", &sales[i]);
		if (sales[i] < 0) {
			printf("판매 수량은 음수로 입력할 수 없습니다");
			return 1;
		}
	}
	printf("\n상품의 id를 입력해주세요:");
	scanf("%d", &ID);

	for (i = 0;i < product_num;i++) {
		invantory[i] = stock[i] - sales[i];
	}

	printf("\n입력하신 id %d의 재고 수량은 \'%d\'개 입니다\n", ID, invantory[ID - 1]);
	printf("모든 상품의 재고 수량은\n");
	for (i = 0;i < product_num;i++) {
		printf("%d ", invantory[i]);
	}


	return 0;
}