#include <stdio.h>
#define MAX_PRODUCTS 100

int main() {
	int ID,product_num;
	int i;
	int stock[MAX_PRODUCTS];
	int sales[MAX_PRODUCTS];
	int invantory[MAX_PRODUCTS];
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
	printf("\n��ǰ�� id�� �Է����ּ���:");
	scanf("%d", &ID);

	for (i = 0;i < product_num;i++) {
		invantory[i] = stock[i] - sales[i];
	}

	printf("\n�Է��Ͻ� id %d�� ��� ������ \'%d\'�� �Դϴ�\n", ID, invantory[ID - 1]);
	printf("��� ��ǰ�� ��� ������\n");
	for (i = 0;i < product_num;i++) {
		printf("%d ", invantory[i]);
	}


	return 0;
}