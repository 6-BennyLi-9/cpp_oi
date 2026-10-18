#include <string>
#include <iostream>
#include <cstdint>
#include <algorithm>

const uint64_t mod = 212370440130137957ll;
const uint64_t base = 99;
const uint64_t addition = 114514;
const size_t maxn = 1e5 + 5;

int32_t n, cnt = 1;
std::string input;
uint64_t a[maxn];

uint64_t hashcode(const std::string &str) 
{
    size_t len = str.length();
    uint64_t res = 0;

    for (size_t i = 0; i < len; ++ i) {
        res = (res * base + (uint64_t)(str[i])) % mod + addition;
    }

    return res;
}

int main() {
    std::cin >> n;
    for (int32_t i = 0; i < n; ++ i) {
        std::cin >> input;
        a[i] = hashcode(input);
    } 
    std::sort(a, a + n);

    for (int32_t i = 1; i < n; ++ i) {
        if (a[i] != a[i - 1]) {
            ++ cnt;
        }
    }

    std::cout << cnt ;
    return 0;
}