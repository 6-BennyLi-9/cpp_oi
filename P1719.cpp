#include <cstdio>
#include <cstdint>
#include <algorithm>

const int32_t maxn = 205;
int32_t n;
int32_t raw[maxn][maxn], seq[maxn][maxn], ans = -1;

int main() {
	scanf("%d", &n);

	for (int32_t i = 1; i <= n; ++ i) {
		for (int32_t j = 1; j <= n; ++ j) {
			scanf("%d", &raw[i][j]);
			seq[i][j] = seq[i][j - 1] + seq[i - 1][j] - seq[i - 1][j - 1] + raw[i][j];
		}
	}
	
	for (int32_t a_i = 1; a_i <= n; ++ a_i) {
		for (int32_t a_j = 1; a_j <= n; ++ a_j) {
			for (int32_t b_i = a_i + 1; b_i <= n; ++ b_i) {
				for (int32_t b_j = a_j + 1; b_j <= n; ++ b_j) {
					ans = std::max(ans,
						seq[b_i][b_j] - seq[a_i - 1][b_j] - seq[b_i][a_j - 1] + seq[a_i - 1][a_j - 1]
					);
				}
			}
		}
	}

	printf("%d", ans);
	return 0;
}