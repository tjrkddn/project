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
	printf("��ǰ ����(����)�Է�:");
	scanf("%d", &product_num);

	if (product_num < 1 || product_num>100) {
		printf("��ǰ ����(����)�� 1���� 100 ���̷��Է��ؾ��մϴ�.");
	}

	printf("��ǰ �� �԰���� �Է�:");
	for (i = 0;i < product_num;i++) {
		scanf("%d", &stock[i]);
	}
	printf("��ǰ �� �Ǹ� ���� �Է�:");
	for (i = 0;i < product_num;i++) {
		scanf("%d", &sales[i]);
		if (sales[i] < 0) {
			printf("�Ǹ� ������ ������ �Է��� �� �����ϴ�");
			return 1;
		}
	}
	//���� ��� ���� ���� ��� ���ϱ�
	for (i = 0;i < product_num;i++) {
		invantory[i] = stock[i] - sales[i];
		total_invantory += stock[i];
	}
	//��� ���� ���
	printf("��� ����:");
	for (i = 0;i < product_num;i++) {
		printf("%d ", invantory[i]);
	}
	//���Ǹŷ� ���ϱ� 
	for (i = 0;i < product_num;i++) {
		total_sales += sales[i];
	}
	percent = ((float)total_sales / total_invantory) * 100;
	printf("\n�� �Ǹŷ�:%d(�Ǹ��� %.2f%%)\n", total_sales,percent);

	int worst_sales=99999999999999999, worst_id=0;
	int best_sales=0, best_id=0;

	for (i = 0; i < product_num;i++) {
		//���� ���� �ȸ� ��ǰ ���ϱ�
		if (best_sales < sales[i]) {
			best_sales = sales[i];
			best_id = i + 1;
		}
		//���� ���� �ȸ� ��ǰ ���ϱ�
		if (worst_sales > sales[i]) {
			worst_sales = sales[i];
			worst_id = i + 1;
		}
	}
	printf("���� ���� �Ǹŵ� ��ǰ: ID %d, �Ǹŷ� %d\n", best_id, best_sales);
	printf("���� ���� �Ǹŵ� ��ǰ: ID %d, �Ǹŷ� %d\n", worst_id, worst_sales);
	
	for (i = 0;i < product_num;i++) {
		if (invantory[i] < 3) {
			printf("��ǰ ID %d: ������(%d)\n", i + 1, invantory[i]);
		}
	}

	return 0;
}