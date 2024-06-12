#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int main(void) {
    int t; cin >> t;
    string s, e;
    for (int tc = 1; tc <= t; ++tc) {
        cin >> s >> e;

        while (s.size() < e.size())
        {
            if (e.back() == 'X') e.pop_back();
            else {
                e.pop_back();
                reverse(e.begin(), e.end());
            }
        }

        cout << '#' << tc << ' ' << (s == e ? "Yes" : "No") << '\n';
    }
    return 0;
}