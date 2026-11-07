#include <cstdio>
#include <cstdint>
#include <vector>
#include <algorithm>

const int64_t mod = 998244353;
const int32_t maxn = 1e5 + 5;

class graphic {
std::vector<int32_t> _head, _nxt, _edge;
int32_t _index = 0;
public:
	explicit graphic(int32_t node_size,int32_t edge_size) : _head(node_size), _nxt(edge_size), _edge(edge_size) {
		std::fill(_head.begin(), _head.end(), -1);
	}

	void insert_vector(int32_t x, int32_t y)
	{
		_nxt[_index] = _head[x];
		_edge[_index] = y;
		_head[x] = _index;
		++_index;
	}
	void insert_edge(int32_t x, int32_t y)
	{
		insert_vector(x, y);
		insert_vector(std::move(y), std::move(x));
	}

	class node_outer {
		int32_t _target_node;
		const graphic& _graph;
	public:
		class iterator: std::iterator<
			std::input_iterator_tag,
			int32_t,
			int32_t,
			const int32_t*,
			int32_t
		>{
			int32_t _current;
			const node_outer& _parent;
		public:
			iterator(const node_outer& parent, int32_t current): _parent(parent), _current(current)
			{};
			explicit iterator(const node_outer& parent): iterator(parent, parent._graph._head[parent._target_node])
			{};

			/// @brief iter to next
			/// @return changed
			iterator& operator++()
			{
				_current = _parent._graph._nxt[_current];
				return *this;
			}
			iterator operator++(int)
			{
				auto res = *this;
				++(*this);
				return res;
			}
			bool operator==(iterator other) const 
			{
				return _current == other._current;
			}
			bool operator!=(iterator other) const 
			{ 
				return !(*this == other);
			}
			reference operator*() const 
			{
				return _parent._graph._edge[_current];
			}
		};

		explicit node_outer(const graphic& graph, int32_t target_node) : _graph(graph), _target_node(target_node)
		{}

		iterator begin() 
		{
			return iterator(*this);
		}
    	iterator end() 
		{
			return iterator(*this, -1);
		}
	};

	node_outer fork_from(int32_t target_node) {
		return node_outer(*this, target_node);
	}
};

int32_t n, m, u, v;
int32_t depth[maxn];
int64_t ans = 1;
graphic graph(0, 0);

void dfs(int32_t current, int32_t lst = 0) {
	depth[current] = depth[lst] + 1;
	for(auto nxt : graph.fork_from(current)) {
		if (nxt == lst) continue;

		if(!depth[nxt]) {
			dfs(nxt, current);
		}

		if(depth[nxt] < depth[current]) {
			ans = (ans * (depth[current] - depth[nxt] + 1)) % mod;
		}
	}
}

int main() 
{
	scanf("%d%d", &n, &m);
	graph = std::move(graphic(n + 5, (m << 1) + 10));

	for(int32_t i = 0; i < m; ++ i) {
		scanf("%d%d", &u, &v);
		graph.insert_edge(u, v);
	}

	// for(int32_t i = 1; i <= n; ++ i) {
	// 	for(auto item: graph.fork_from(i)) {
	// 		printf("%d ", item);
	// 	}
	// 	printf("\n");
	// }

	dfs(1);

	printf("%lld", ans);

	return 0;
}