#include <cstdint>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

const int32_t maxn = 1e6 + 5;
int32_t t, n, i, j, e, len;
int32_t library[maxn];
bool result;

class dsu{
	std::vector<size_t> index;
public:
	explicit dsu(size_t capacity) :
	index(capacity) 
	{ 
		std::iota(index.begin(), index.end(), 0); 
	}

	size_t find(size_t x) 
	{
		return index[x] == x? x: index[x] = find(index[x]);
	}

	size_t unite(size_t one, size_t another) 
	{
		index[find(one)] = index[find(another)];
	}

	bool is_united(size_t one, size_t another)
	{
		return find(one) == find(another);
	}

	void renewal()
	{
		std::iota(index.begin(), index.end(), 0); 
	}
} eq(maxn);

struct command{
	int32_t one, another, type;
} commands[maxn];

#define __index_of(s) std::lower_bound(library, library + len, s) - library 

int main() {
	std::cin >> t;
	for (int32_t counter = 0; counter < t; ++ counter)
	{
		result = true;
		std::cin >> n;

		len = 0;
		dsu eq(n + 5), ne(n + 5);
		for (int32_t c = 0; c < n; ++ c) {
			std::cin >> i >> j >> e;
			commands[c] = {i, j, e};
			library[++len] = i;
			library[++len] = j;
		}

		std::sort(commands, commands + n, [](const command &one, const command &another){return one.type > another.type;});
		n = std::unique(commands, commands + n, [](const command &one, const command &another){return one.type == another.type && ((one.one == another.one && one.another == another.another) || (one.another == another.another && one.one == another.one));}) - commands;
		std::sort(library, library + len);
		len = std::unique(library, library + len) - library;
		eq.renewal();

		for (int32_t c = 0; c < n; ++ c) {
			if (commands[c].type) { // x_i == x_j
				eq.unite(__index_of(commands[c].one), __index_of(commands[c].another));
			} else if (eq.is_united(__index_of(commands[c].one), __index_of(commands[c].another))) {
				result = false;
				break;
			}
		}

		std::cout << (result? "YES\n":"NO\n");
	}
	
	return 0;
}