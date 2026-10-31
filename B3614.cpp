#include <cstdio>
#include <cstring>
#include <cstdint>
#include <stack>
#define __streq(_Str1, _Str2) !strcmp(_Str1, _Str2)

int32_t t,n;
int64_t x;
char command[25];
std::stack<uint64_t> st;

int main() {
	scanf("%d", &t);
	while(t--) {
		scanf("%d", &n);
		while(n--){
			scanf("%s", command);

			if (__streq(command, "push")) {
				scanf("%llu", &x);
				st.push(x);
			} else if (__streq(command, "pop")) {
				if (st.empty()) {
					printf("Empty\n");
				} else {
					st.pop();
				}
			} else if (__streq(command, "query")) {
				if (st.empty()) {
					printf("Anguei!\n");
				} else {
					printf("%llu\n", st.top());
				}
			} else if (__streq(command, "size")) {
				printf("%d\n", st.size());
			} else {
				return -1;
			}
		}
		st = std::move(std::stack<uint64_t>());
	}

	return 0;
}