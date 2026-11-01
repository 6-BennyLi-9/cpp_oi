#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <cstring>
#include <memory>

void dfs(const int8_t current, int8_t depth, char list[]) {
	if (current == depth) {
		printf("%s\n", list);
	} else {
		dfs(current, depth + 1, (list[depth] = 'N', list));
		dfs(current, depth + 1, (list[depth] = 'Y', list));
	}
}

int8_t n;

int main() {
	scanf("%d", &n);
	auto cache = std::move(static_cast<char*>(malloc((n + 5) * sizeof(char))));
	for(int8_t i = 0; i < n + 5; ++i) {
		cache[i] = 0;
	}
	dfs(n, 0, std::move(cache));
	return 0;
}