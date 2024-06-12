#include <iostream>
#include <cstring>
#include <algorithm>
#include <set>
using namespace std;


bool found = false;
string s, ed;
set<string> v;
void dfs(string e) {
    // cout << e << '\n';
    if (found) return;
    if (s.size() == e.size()) {
        if (s == e) {
            found =true;
        }
        return;
    }
    char fr = e.front(), en = e.back();
    if (fr == 'X' && en == 'Y') return; //불가능
    else if (fr == 'X' && en == 'X') { //
        e.pop_back();
        if (v.find(e) == v.end()) {
            v.insert(e);
            dfs(e);
        }
    }
    else if (fr == 'Y' && en == 'Y') {
        reverse(e.begin(), e.end());
        e.pop_back();
        if (v.find(e) == v.end()) {
            v.insert(e);
            dfs(e);
        }
    }
    else {
        string tmp = e;
        //x제거
        tmp.pop_back();
        if (v.find(tmp) == v.end()) {
            v.insert(tmp);
            dfs(tmp);
        }
        tmp = e;
        reverse(tmp.begin(), tmp.end());
        tmp.pop_back();
        if (v.find(tmp) == v.end()) {
            v.insert(tmp);
            dfs(tmp);
        }

    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    for (int tc = 1; tc <= t; ++tc) {
        cin >> s >> ed;
        v.clear();
        found =false;
        dfs(ed);
        cout << '#' << tc << ' ' << (found ? "Yes" : "No") << '\n';
    }
    return 0;
}