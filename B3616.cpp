#include <cstdio>
#include <cstdint>
#include <queue>
#define __query_loop(T) scanf("%d", &T); while(T--)

int32_t n, command, x;
std::queue<int32_t> st;

int main() {
	__query_loop(n){
		scanf("%d", &command);

		switch (command) {
			case 1:
				scanf("%d", &x);
				st.push(x);
				break;
			case 2:
				if (st.empty()) {
					printf("ERR_CANNOT_POP\n");
				} else {
					st.pop();
				}
				break;
			case 3:
				if (st.empty()) {
					printf("ERR_CANNOT_QUERY\n");
				} else {
					printf("%d\n", st.front());
				}
				break;
			case 4:
				printf("%d\n", st.size());
				break;
			default:
				return -1;
		}
	}

	return 0;
}