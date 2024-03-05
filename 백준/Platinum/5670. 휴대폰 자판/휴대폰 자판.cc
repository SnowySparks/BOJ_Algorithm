#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <map>
using namespace std;

char lst[100000][81];
int temp = 0;
struct Trie {
    bool isend = false;
    bool isroot = false;
    map<char, Trie*> child;
    Trie(bool isroot = false) : isroot(isroot) {}
    ~Trie() {
        for (auto it : child) {
            delete it.second;
        }
    }

    void insert(char *ch) {
        if (*ch == '\0') isend = true;
        else {
            if (child.find(*ch) == child.end()) child[*ch] = new Trie();
            child[*ch]->insert(ch + 1);
        }
    }

    int find(char *ch) {
        if (*ch == '\0') return 0;
        if (isroot) return 1 + child[*ch]->find(ch +1); //첫 입력은 무조건 입력해야해서 
        int res = (((int)child.size() >= 2 || isend ) ? 1 : 0); //다음 부턴 자식이 2개이상 혹은 중간에 종료조건 있을 경우 카운팅
        return res + child[*ch]->find(ch+1); //다음 자식 입력에 대한 접근
    }
};

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int n;
    while (cin >> n)
    {   Trie *root = new Trie(true); //Root Trie Tree node
        for (int i = 0 ; i < n; ++i) {
            cin >> lst[i];
            root->insert(lst[i]);
        }
        // bool issame = ((int)root->child.size() == 1 ? true : false);
        int cnt = 0;
        for (int i = 0; i < n; ++i) {
            cnt += root->find(lst[i]);
        }
        printf("%.2f\n", (double)cnt/n);
    }
    
    return 0;
}