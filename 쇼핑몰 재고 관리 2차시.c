#include <stdio.h>
#define MAX_PRODUCTS 100

int main() {
	int ID, product_num;
	int i;
	int stock[MAX_PRODUCTS];
	int sales[MAX_PRODUCTS];
	int invantory[MAX_PRODUCTS];
	int total_sales= 0;
	float percent= 0.0;
	int total_invantory= 0;
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
	//현재 재고량 계산과 원래 재고량 구하기
	for (i = 0;i < product_num;i++) {
		invantory[i] = stock[i] - sales[i];
		total_invantory += stock[i];
	}
	//재고 수량 출력
	printf("재고 수량:");
	for (i = 0;i < product_num;i++) {
		printf("%d ", invantory[i]);
	}
	//총판매량 구하기 
	for (i = 0;i < product_num;i++) {
		total_sales += sales[i];
	}
	percent = ((float)total_sales / total_invantory) * 100;
	printf("\n총 판매량:%d(판매율 %.2f%%)\n", total_sales,percent);

	int worst_sales=99999999999999999, worst_id=0;
	int best_sales=0, best_id=0;

	for (i = 0; i < product_num;i++) {
		//가장 많이 팔린 상품 구하기
		if (best_sales < sales[i]) {
			best_sales = sales[i];
			best_id = i + 1;
		}
		//가장 적게 팔린 상품 구하기
		if (worst_sales > sales[i]) {
			worst_sales = sales[i];
			worst_id = i + 1;
		}
	}
	printf("가장 많이 판매된 상품: ID %d, 판매량 %d\n", best_id, best_sales);
	printf("가장 적게 판매된 상품: ID %d, 판매량 %d\n", worst_id, worst_sales);
	
	for (i = 0;i < product_num;i++) {
		if (invantory[i] < 3) {
			printf("상품 ID %d: 재고부족(%d)\n", i + 1, invantory[i]);
		}
	}

	return 0;
}