#include <stdio.h>

int main(void)
{
	int n;
	unsigned char month;
	scanf("%d", &n);
	scanf("%hhu", &month);
	unsigned int num;
	unsigned int sum[4];
	for (int i = 0; i < 4; i++)
		sum[i] = 0;
	for (int i = 0; i < n; i++) {
		scanf("%x", &num);
		unsigned char this_month = num >> (8 * 3) & 0x000000ff;
		unsigned char category = num >> (8 * 1) & 0x000000ff;
		unsigned int amount = num & 0x000000ff;
		if (this_month == month)
			sum[category - 1] += amount;
	}
	for (int i = 0; i < 4; i++)
		printf("%d : %u\n", i + 1, sum[i]);
	return 0;
}
