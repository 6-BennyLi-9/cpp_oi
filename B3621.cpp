#include <cstdio>
#include <vector>

int n, k;

class enum_mng {
private:
    std::vector<int> vals;

public:
    enum_mng(int n) : vals(n, 1) {}

    inline void print() {
        for (int i = 0; i < n; ++i) {
            if (i) printf(" ");
            printf("%d", vals[i]);
        }
        printf("\n");
    }

    inline bool nxt() {
        int i = n - 1;

        while (i >= 0 && vals[i] == k) {
            vals[i] = 1;
            --i;
        }

        if (i < 0) return false;

        ++vals[i];
        return true;
    }
};

int main() {
    scanf("%d%d", &n, &k);

    enum_mng mng(n);

    do {
        mng.print();
    } while (mng.nxt());

    return 0;
}