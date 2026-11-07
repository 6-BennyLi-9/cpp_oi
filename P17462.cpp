#include <cstdio>
#include <queue>
#include <cstdint>

#define __pass_if(exp) if(exp) continue

struct edge_t {
	int32_t ending, deadline, time_cost;
};

const int32_t maxn = 505;
int32_t n, m, q, u, v, w, t;
std::vector<edge_t> edges[maxn];
/// @brief 最晚出发时间
int32_t deadlines[maxn][maxn];

class dijkstra_sample_t {
public:
	int32_t current_time, ending;

	friend bool operator<(const dijkstra_sample_t& one, const dijkstra_sample_t &another)
	{
		return one.current_time < another.current_time;
	}
	friend bool operator>(const dijkstra_sample_t& one, const dijkstra_sample_t &another)
	{
		return one.current_time > another.current_time;
	}
};

void dijkstra(int32_t ending){
	std::queue<dijkstra_sample_t> queue;
	std::vector<int32_t> distance(n + 1, INT32_MIN);
	distance[ending] = INT32_MAX;
	queue.push(dijkstra_sample_t{INT32_MAX, ending});

	while(!queue.empty()) {
		auto current = queue.front();
		queue.pop();

		__pass_if(current.current_time < distance[current.ending]);

		for (const auto& item: edges[current.ending]) {
			int new_dis = std::min(item.deadline, distance[current.ending] - item.time_cost);

			if (new_dis > distance[item.ending]) {
				distance[item.ending] = new_dis;
				queue.push(dijkstra_sample_t{new_dis, item.ending});
			}
		}
	}

	for (int i = 1; i <= n; ++ i) {
		deadlines[ending][i] = distance[i];
	}
}

int main() 
{
	scanf("%d%d%d", &n, &m, &q);
	
	for(int32_t i = 0; i < m; ++ i) {
		scanf("%d%d%d%d", &u, &v, &w, &t);
		edges[v].push_back(edge_t{u, w, t});
	}
	for(int32_t i = 1; i <= n; ++ i) {
		dijkstra(i);
	}

	// for(int32_t i = 1; i <= n; ++ i) {
	// 	for(int32_t j = 1; j <= n; ++ j) {
	// 		printf("%d ", deadlines[i][j]);
	// 	}
	// 	puts("");
	// }

	for(int32_t i = 0; i < q; ++ i) {
		scanf("%d%d%d", &u, &v, &w);

		if(u == v || deadlines[v][u] >= w) {
			puts("Yes");
		} else {
			puts("No");
		}
	}

	return 0;
}
