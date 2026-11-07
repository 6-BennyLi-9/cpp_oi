#include <cstdio>
#include <cstdint>

int32_t n;

int main() {
	scanf("%d", &n);

	if (n <= 4) {
		printf("-1");
		return 0;
	}

	for (int32_t i = 1; i <= n; i += 2) printf("%d ", i);
	for (int32_t i = 2; i <= n; i += 2) printf("%d ", i);
	printf("\n");

	if (n & 1) {
		for (int i = 3; i <= n; i += 2) printf("%d ", i);
		printf("1 ");
		for (int i = 4; i <= n - 1; i += 2) printf("%d ", i);
		printf("2");
	} else {
		for (int i = 3; i <= n - 1; i += 2) printf("%d ", i);
		printf("1 ");
		for (int i = 4; i <= n; i += 2) printf("%d ", i);
		printf("2");
	}

	return 0;
}