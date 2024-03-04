#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <unordered_map>
using namespace std;

char numlst[10000][11];

// 트라이 기본 구조
struct Trie {
    bool isend= false;
    Trie *child[10];

    Trie() {
        memset(child, 0, sizeof(child));
    }
    ~Trie() {
        for (int i = 0; i < 10; ++i) {
            if (child[i]) delete child[i];
        }
    }

    void insert(char *ch) {
        if (*ch == '\0') {
            isend = true;
            return;
        } 
        else {
            int idx = *ch - '0';
            if (child[idx] == 0) child[idx] = new Trie();
            child[idx]->insert(ch + 1);
        }
    }

    bool find(char *ch) {
        if ( *ch == '\0') return true;
        if (isend) return false;
        int idx = *ch - '0';
        if (child[idx] == 0) return true;
        return child[idx]->find(ch + 1);
    }
};

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    while (T--)
    {
        int n; cin >> n;
        Trie *root = new Trie();
        for (int i = 0; i <n; ++i) {
            cin >> numlst[i];
            root->insert(numlst[i]);
        }
        bool can = true;
        for (int i = 0; i < n ; ++i) {
            if (root->find(numlst[i]) == false) {
                can = false;
                break;
            }
        }
        cout << (can ? "YES" : "NO") << '\n';
    }
    return 0;
}