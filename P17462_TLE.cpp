#include <cstdio>
#include <cstdint>
#include <vector>
#include <queue>
#include <algorithm>

#define __pass_if(exp) if(exp) continue

struct trajectory_t{
	int32_t terminate_node, terminate_time, time_cost;
};

class graph_t {
std::vector<int32_t> _head, _nxt;
std::vector<trajectory_t> _edge;
int32_t _index = 0;
public:
	explicit graph_t(int32_t node_size,int32_t edge_size) : _head(node_size), _nxt(edge_size), _edge(edge_size) {
		std::fill(_head.begin(), _head.end(), -1);
	}

	void insert_vector(int32_t x, const trajectory_t& trajectory)
	{
		_nxt[_index] = _head[x];
		_edge[_index] = trajectory;
		_head[x] = _index;
		++_index;
	}

	class node_outer_t {
		int32_t _target_node;
		const graph_t& _graph;
	public:
		/// @brief I HATE CPP. IT'S TOOOOOOOOOOOOOOOOOOOOO UGLY!!!!!
		class iterator_t: std::iterator<
			std::input_iterator_tag,
			int32_t,
			int32_t,
			const int32_t*,
			trajectory_t
		>{
			int32_t _current;
			const node_outer_t& _parent;
		public:
			iterator_t(const node_outer_t& parent, int32_t current): _parent(parent), _current(current)
			{};
			explicit iterator_t(const node_outer_t& parent): iterator_t(parent, parent._graph._head[parent._target_node])
			{};

			/// @brief iter to next
			/// @return changed
			iterator_t& operator++()
			{
				_current = _parent._graph._nxt[_current];
				return *this;
			}
			iterator_t operator++(int)
			{
				auto res = *this;
				++(*this);
				return res;
			}
			bool operator==(iterator_t other) const 
			{
				return _current == other._current;
			}
			bool operator!=(iterator_t other) const 
			{ 
				return !(*this == other);
			}
			reference operator*() const 
			{
				return _parent._graph._edge[_current];
			}
		};

		explicit node_outer_t(const graph_t& graph, int32_t target_node) : _graph(graph), _target_node(target_node)
		{}

		iterator_t begin() 
		{
			return iterator_t(*this);
		}
		iterator_t end() 
		{
			return iterator_t(*this, -1);
		}
	};

	/// @brief fork a iter from the node. It will go through all the branches that the node leads out.
	/// @param target_node the orinal node
	/// @return the iter. Don't make other usage.
	node_outer_t fork_from(int32_t target_node) {
		return node_outer_t(*this, target_node);
	}
};

const int32_t maxn = 1005;
int32_t n, m, q, u, v, w, t;
int32_t minimum[maxn];
// bool vis[maxn];
graph_t graph(0, 0);

class dijkstra_sample_t {
public:
	int32_t current_time, ending;

	friend bool operator<(const dijkstra_sample_t& one, const dijkstra_sample_t &another)
	{
		return minimum[one.ending] < minimum[another.ending];
	}
	friend bool operator>(const dijkstra_sample_t& one, const dijkstra_sample_t &another)
	{
		return minimum[one.ending] > minimum[another.ending];
	}
};

bool dijkstra() {
	std::fill(minimum, minimum + maxn, INT32_MAX);
	// memset(vis, 0, sizeof(vis));
	minimum[u] = 0;

	std::priority_queue<dijkstra_sample_t> queue;
	dijkstra_sample_t current;
	queue.push(std::move(dijkstra_sample_t{w, u}));

	while(!queue.empty()) {
		current = queue.top();
		queue.pop();

		if(current.ending == v) return true;

		// printf("at %d, now %d\n", current.ending, current.current_time);

		// __pass_if(vis[current.ending]);
		// vis[current.ending] = true;

		for(auto nxt: graph.fork_from(current.ending)) {
			// printf("checking: train to %d end at %d, now %d\n", nxt.terminate_node, nxt.terminate_time, current.current_time);
			// __pass_if(vis[nxt.terminate_node]);
			__pass_if(nxt.terminate_time < current.current_time);

			if (nxt.time_cost + minimum[current.ending] < minimum[nxt.terminate_node]) {
				queue.push(std::move(dijkstra_sample_t{nxt.time_cost + current.current_time, nxt.terminate_node}));
			}
		}
	}

	return false;
}

int main() 
{
	scanf("%d%d%d", &n, &m, &q);
	graph = std::move(graph_t(n + 5, (m << 1) + 10));

	for(int32_t i = 0; i < m; ++ i) {
		scanf("%d%d%d%d", &u, &v, &w, &t);
		graph.insert_vector(u, std::move(trajectory_t{v, w, t}));
	}

	for(int32_t i = 0; i < q; ++ i) {
		scanf("%d%d%d", &u, &v, &w);
		printf("%s\n", dijkstra()? "Yes": "No");
	}

	return 0;
}