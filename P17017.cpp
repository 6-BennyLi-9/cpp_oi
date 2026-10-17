#include <cstdio>

const int mod = 1e9 + 7;
const int maxm = 1e5 + 5;
int n, m, u;
long long ans = 1;

long long power(long long a, long long b){
	long long res = 1;
	for(; b; b >>= 1, a = a * a % mod) {
		if(b & 1){
			res = res * a % mod;
		}
	}
	return res;
}

int main() {
	scanf("%d%d", &m, &n);
	
	if(n < m || !n || !m) {
		printf("0");
		return 0;
	}
	
	if(n == m) {
		printf("1");
		return 0;
	}
	
	for (int i = m + 1;i <= n + m; ++i){
		ans = ans * i % mod;
	}
	for (int i = 1;i <= n; ++i){
		ans = ans * power(i, mod - 2) % mod;
	}
	
//	printf("%d\n", fn / fm / fd);
//	printf("%d, %d, %d\n", fn , fm , fd);
//	printf("%d, %d, %d\n", fn , power(fm, mod - 2) , power(fd, mod - 2));
	printf("%d", ans);
	return 0;
}
