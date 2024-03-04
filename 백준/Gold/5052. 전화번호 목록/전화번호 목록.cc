#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;

// 트라이 기본 구조
struct Trie {
    bool isend = false;
    Trie* num[10];

    Trie() {
        memset(num, 0, sizeof(num));
    }
    ~Trie() {
        for (int i = 0; i < 10; ++i) {
            if (num[i]) delete num[i];
        }
    }

    void insert(const string &n, int idx = 0) {
        if (idx == (int)n.size()) {
            isend = true;
            return;
        }
        int nidx = n[idx] - '0';
        Trie *tr = new Trie;
        num[nidx] = tr;
        tr->insert(n, idx + 1);
    }

    bool find(const string &other, int idx=0) {
        if (idx == (int)other.size()) return true;
        if (isend) return false;
        int nidx = other[idx]-'0';
        if (num[nidx] == 0) return true;
        return num[nidx]->find(other, idx + 1);
    }

};

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--)
    {
        int n; cin >> n;
        Trie* root = new Trie;
        vector<string> s(n);
        for (int i = 0; i < n; ++i) cin >> s[i];
        sort(s.begin(),s.end());
        bool can = true;
        for (const string &val : s) {
            if (root->find(val)) root->insert(val);
            else {
                can = false;
                break;
            }
        }
        cout << (can ? "YES" : "NO") <<'\n';
    }
    return 0;
}