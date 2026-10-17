#include <cstdio>
#include <stdint.h>

const int32_t maxn = 205;
int32_t n, a, b, cnt_a, cnt_b;
int32_t c_a[maxn], c_b[maxn];

int8_t result[5][5] = {
	{0, -1, 1, 1, -1},
	{1, 0, -1, 1, -1},
	{-1, 1, 0, -1, 1},
	{-1, -1, 1, 0, 1},
	{1, 1, -1, -1, 0}
};

int main()
{
	scanf("%d%d%d", &n, &a, &b);

	for (int32_t i = 0; i < a; ++i)
	{
		scanf("%d", &c_a[i]);
	}
	for (int32_t i = 0; i < b; ++i)
	{
		scanf("%d", &c_b[i]);
	}

	for (int32_t i = 0; i < n; ++i)
	{
		switch (result[c_a[i % a]][c_b[i % b]]) {
			case 0:
			continue;
			case 1:
			++ cnt_a;
			break;
			case -1:
			++ cnt_b;
			break;
			default:
			return -1;
		}
	}

	printf("%d %d", cnt_a, cnt_b);

	return 0;
}