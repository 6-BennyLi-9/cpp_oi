#include <vector>
#include <queue>
#include <cstdint>
#include <cstdio>
#include <algorithm>

#define get_id(x) static_cast<int32_t>(lower_bound(vals.begin(), vals.end(), x) - vals.begin())

const int32_t INF = 1e9;
int32_t T, n, ans;

int32_t core(int32_t x) {
	int32_t res = 1;
	for (int p = 2; p * p <= x; ++p) {
		int cnt = 0;
		while (x % p == 0) {
			x /= p;
			cnt ^= 1;
		}
		if (cnt) res *= p;
	}
	if (x > 1) res *= x;
	return res;
}

int32_t bfs(int32_t target, int32_t start, int32_t id_one, std::vector<int32_t> &dist, const std::vector<std::vector<std::pair<int32_t, int32_t>>> &library) {
	fill(dist.begin(), dist.end(), -1);

	std::queue<int32_t> q;
	dist[start] = 0;
	q.push(start);

	while (!q.empty())
	{
		int32_t select = q.front();
		q.pop();

		for (auto item : library[select])
		{
			if (item.first == target)
				continue;

			if (item.second == id_one)
			{
				return dist[select] + 1;
			}

			if (dist[item.second] == -1)
			{
				dist[item.second] = dist[select] + 1;
				q.push(item.second);
			}
		}
	}

	return INF;
}

int32_t main() {
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &n);

		std::vector<int32_t> a(n), b(n);
		std::vector<int32_t> ca(n), cb(n);
		std::vector<int32_t> vals;
		vals.push_back(1);

		for (int32_t i = 0; i < n; ++i) {
			scanf("%d%d", &a[i], &b[i]);
			ca[i] = core(a[i]);
			cb[i] = core(b[i]);
			vals.push_back(ca[i]);
			vals.push_back(cb[i]);
		}

		sort(vals.begin(), vals.end());
		vals.erase(unique(vals.begin(), vals.end()), vals.end());

		int32_t sizelen = vals.size();
		int32_t id_one = get_id(1);

		std::vector<std::vector<std::pair<int32_t, int32_t>>> library(sizelen);
		std::vector<int32_t> u(n), v(n);

		for (int32_t i = 0; i < n; ++i) {
			u[i] = get_id(ca[i]);
			v[i] = get_id(cb[i]);
			library[u[i]].push_back({i, v[i]});
		}

		std::vector<int32_t> dist(sizelen);

		ans = INF;

		for (int32_t i = 0; i < n; ++i) {
			if (u[i] != id_one) continue;

			int32_t len = bfs(i, v[i], id_one, dist, library);
			if (len < INF) {
				ans = std::min(ans, 1 + len);
			}
		}

		if (ans == INF) printf("-1\n");
		else printf("%d\n", ans);
	}

	return 0;
}