#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <functional>
#include <vector>
#include <numeric>

const int32_t maxn = 2e5 + 5; 
int32_t n, m;

class data
{
public:
	int32_t a, b, c;
private:
	friend bool operator<(const data &one, const data &anoter) {
		return one.c < anoter.c;
	}
	friend bool operator>(const data &one, const data &anoter) {
		return one.c > anoter.c;
	}
	friend bool operator==(const data &one, const data &anoter) {
		return one.c == anoter.c;
	}
};
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
};

data input[maxn];

int main() 
{
	scanf("%d%d", &n, &m);
	for (int32_t i = 0; i < m; ++i)
	{
		scanf("%d%d%d", &input[i].a, &input[i].b, &input[i].c);
	}

	std::sort(input, input + m, std::greater<data>());

	dsu mng(n * 2 + 15);

	for (int32_t i = 0; i < m; ++i) {
		mng.unite(input[i].a, input[i].b + n);
		mng.unite(input[i].a + n, input[i].b);

		if(mng.is_united(input[i].a, input[i].a + n) 
		|| mng.is_united(input[i].b, input[i].b + n)) {
			printf("%d", input[i].c);
			return 0;
		}
	}

	printf("0");
	return 0;
}
