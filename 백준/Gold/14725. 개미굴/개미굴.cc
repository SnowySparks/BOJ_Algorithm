#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
#include <map>
using namespace std;

// 트라이 기본 구조
struct Trie {
    bool isend; 
    map<string, Trie*> node; //자식 노드로 향하는 것. 메모리 효율성을 위해서 map사용. 오름차순 만들기 위해 maps
    Trie() {}
    void insert(const vector<string> sts, int idx = 0) { //삽입
        if (idx == (int)sts.size()) return; //종료
        if (this->node.find(sts[idx]) == node.end()) {
            Trie *tr = new Trie;
            node[sts[idx]] = tr;
        }
        node[sts[idx]]->insert(sts, idx + 1); //다음 자식에 대한 삽입 호출
    }

    //호출
    void dfs(int depth) { //depth 크기 -> --호출 횟수
        for (auto &nd : node) {
            for (int i = 0; i < depth; ++i) cout <<"--";
            cout << nd.first << '\n'; //
            nd.second->dfs(depth + 1);
            delete nd.second; //사용되어진 Trie 메모리 할당 해제
        }
    }
};

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, cnt; cin >> n;
    Trie* root = new Trie;
    for (int i = 0; i < n; ++i) {
        cin >> cnt;
        vector<string> tmp(cnt);
        for (int j = 0 ; j < cnt; ++j) {
            cin >> tmp[j];
        }
        root->insert(tmp);
    }
    root->dfs(0);
    delete root;
    return 0;
}