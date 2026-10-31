#include <cstdint>
#include <memory>
#include <unordered_map>

struct raw_link_node {
	int32_t val = 0;
	std::shared_ptr<raw_link_node> nxt;
	std::weak_ptr<raw_link_node> pre;
};

using linknode = std::shared_ptr<raw_link_node>;
using weaknode = std::weak_ptr<raw_link_node>;

class link_mng {
private:
	linknode head_;
	std::unordered_map<int32_t, weaknode> library;

public:
	explicit link_mng(int32_t n) {
		head_ = nullptr;
		library = std::unordered_map<int32_t, weaknode>();
		for (int32_t i = n; i >= 1; --i) {
			auto node = std::make_shared<raw_link_node>();
			node->val = i;
			node->nxt = head_;
			if (head_) head_->pre = node;
			head_ = node;

			library[i] = node;
		}
	}

	inline void print() {
		if(!head_) {
			printf("Empty!");
			return;
		}

		linknode current = head_;

		while(current) {
			printf("%d ", current->val);
			current = current->nxt;
		}
	}

	inline void delete_val(int32_t x) {
		auto target = library[x].lock();

		if (auto pre = target->pre.lock()) {
			pre->nxt = target->nxt;
		} 
		if (auto nxt = target->nxt) {
			nxt->pre = target->pre;
		}

		if (head_ == target) {
			head_ = target->nxt;
		}
	}

	inline void replace_left(int32_t dir, int32_t tar) {
		auto target = library[dir].lock();
		auto node = std::make_shared<raw_link_node>();
		node->val = tar;
		node->nxt = target;
		delete_val(tar);

		if (auto pre = target->pre.lock()) {
			pre->nxt = node;
			node->pre = pre;
		} else {
			head_ = node;
		}
		target->pre = node;

		library[tar] = node;
	}

	inline void replace_right(int32_t dir, int32_t tar) {
		auto target = library[dir].lock();
		auto node = std::make_shared<raw_link_node>();
		node->val = tar;
		node->pre = target;
		delete_val(tar);

		if (auto nxt = target->nxt) {
			nxt->pre = node;
			node->nxt = nxt;
		}
		target->nxt = node;

		library[tar] = node;
	}
};

int32_t n, m, code, x, y;

int main() {
	scanf("%d%d", &n, &m);
	link_mng mng(n);
	while(m--) {
		scanf("%d", &code);
		switch(code) {
			case 1:
				scanf("%d%d", &x, &y);
				mng.replace_left(y, x);
				break;
			case 2:
				scanf("%d%d", &x, &y);
				mng.replace_right(y, x);
				break;
			case 3:
				scanf("%d", &x);
				mng.delete_val(x);
				break;
			default:
				return -1;
		}
	}
	mng.print();
	return 0;
}