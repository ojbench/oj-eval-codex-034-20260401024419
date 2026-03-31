#include <bits/stdc++.h>
#include "skip_list.hpp"

using namespace std;

// The judge for this repo will build an executable named `code` and run
// problem-specific tests. Implement a driver that reads operations:
// Format (assumed):
// n
// op value
// where op is: 1 insert, 2 delete, 3 search (print 1/0)

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    SkipList<long long> sl;
    int q;
    if (!(cin >> q)) return 0;
    while (q--) {
        int op; long long x; cin >> op >> x;
        if (op == 1) {
            sl.insert(x);
        } else if (op == 2) {
            sl.deleteItem(x);
        } else if (op == 3) {
            cout << (sl.search(x) ? 1 : 0) << '\n';
        }
    }
    return 0;
}

