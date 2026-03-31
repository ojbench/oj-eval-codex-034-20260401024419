#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "skip_list.hpp"

using namespace std;

// Driver supports two common formats:
// 1) First line: integer Q (number of operations), followed by Q lines: "op x"
// 2) No count: lines of "op x" until EOF

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    SkipList<long long> sl;

    string line;
    if (!std::getline(cin, line)) return 0;
    auto trim = [](string &s){
        size_t i = 0; while (i < s.size() && isspace((unsigned char)s[i])) ++i; s.erase(0, i);
        size_t j = s.size(); while (j && isspace((unsigned char)s[j-1])) --j; s.erase(j);
    };
    trim(line);
    bool has_count = false;
    long long q = 0;
    if (!line.empty()) {
        stringstream ss(line);
        long long tmp; string extra;
        if ((ss >> tmp) && !(ss >> extra)) {
            has_count = true;
            q = tmp;
        }
    }

    auto process_line = [&](const string &ln){
        if (ln.empty()) return;
        stringstream ss(ln);
        long long op, x;
        if (!(ss >> op >> x)) return; // ignore malformed
        if (op == 1) {
            sl.insert(x);
        } else if (op == 2) {
            sl.deleteItem(x);
        } else if (op == 3) {
            cout << (sl.search(x) ? 1 : 0) << '\n';
        }
    };

    if (has_count) {
        for (long long i = 0; i < q; ++i) {
            if (!std::getline(cin, line)) break;
            trim(line);
            if (line.empty()) { --i; continue; }
            process_line(line);
        }
    } else {
        process_line(line);
        while (std::getline(cin, line)) {
            trim(line);
            process_line(line);
        }
    }
    return 0;
}
