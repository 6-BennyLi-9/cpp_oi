#include <cstdio>
#include <algorithm>
#include <cstdint>
#include <vector>
#include <numeric>

const int32_t maxn = 5e3 + 10;
class edge{
public:
	int u,w,v;
private:
	friend bool operator <(edge a,edge b){
		return a.v<b.v;
	} 
}graph[maxn];

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
}dataset(maxn);

int32_t n, m, cnt, tot, h, cache;

void kruskal(){
	for (int32_t j = 1; j <= h && tot <= m; ++j) {
		if(!dataset.is_united(graph[j].u, graph[j].w)) {
			++tot;
			cnt+=graph[j].v;
			dataset.unite(graph[j].u, graph[j].w);
		}
	}
}

void add(int32_t a,int32_t b,int32_t w){
	++h;
	graph[h].u=a;
	graph[h].w=b;
	graph[h].v=w;
}

int main(){
	scanf("%d%d",&n,&m);
	for(int32_t i=1;i<=m;i++)for(int32_t j=1;j<=m;j++){
		scanf("%d",&cache);
		if(i<j&&cache)
			add(i,j,cache);
	}
	
	for(int32_t i=1;i<=m;i++)add(0,i,n);
	std::sort(graph+1,graph+h+1);
	
	kruskal();
	printf("%d",cnt);
	return 0;
}
