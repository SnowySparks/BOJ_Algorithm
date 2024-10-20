#include <cstring>
#include <algorithm>
#include <iostream>
#include <vector>
#include <queue>
#define f(a, b, c) for(int a=b; a<c;++a)
using namespace std;
const int MAX_LV = 16;  // 최대 레벨 깊이
const int MAX_N = 30001; // 최대 노드 수
const int MAX_Q = 5001; // 최대 방문 수
int N, Q; // 도시(노드) 수, 쿼리 수
int query[MAX_Q]; // 방문도시 순서
vector<int> tree[MAX_N]; // 트리
int level[MAX_N]; // 트리 레벨 깊이, -1 : 미방문
int parent[MAX_N][MAX_LV]; // 부모. 2^lv 번째 위의 

void set_level(void); // 레벨 설정
int lca(int a, int b); // 

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // input
    cin >> N;
    int a, b;
    f(i, 0, N-1) {
        cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }
    cin >> Q;
    query[0] = 1;
    f(i, 1, Q+1) cin >> query[i];
    long long answer = 0;
    // 전처리
    memset(level, -1, sizeof(level));
    set_level();


    f(i, 1, Q+1) {
        a = query[i-1]; b = query[i];

        int lca_node = lca(a,b);
        int dist = (level[a] + level[b] - 2*level[lca_node]);
        answer += 1LL * dist;
    }
    cout << answer;
    return 0;
}

// 
void set_level() {
    level[1] = 0;
    queue<int> q; q.push(1);

    while (!q.empty())
    {
        int node = q.front(); q.pop();

        for (int child : tree[node]) {
            if (level[child] != -1) continue; //이미 처리된 노드 스킵
            level[child] = level[node] + 1; // 깊이 레벨 각인
            parent[child][0] = node;
            f(i, 1, MAX_LV) {
                parent[child][i] = parent[ parent[child][i-1] ][i-1]; //부모 희소 배열 
            }
            q.push(child);
        }
    }
}

int lca(int a, int b) {
    if (level[a] < level[b]) swap(a, b); // a를 항상 레벨 깊은쪽으로
    if (a == 1 || b == 1) return 1; //루트 노드 
    int diff = level[a] - level[b]; // 레벨 차

    // 레벨 차 만큼 조절
    for (int i = 0; diff > 0 ; ++i) {
        if (diff & 1) {
            a = parent[a][i];
        }
        diff >>= 1;
    }
    if (a == b) return a; // a, b 둘중 하나가 조상노드

    for (int i = MAX_LV -1; i >= 0; --i) {
        if (parent[a][i] != parent[b][i]) {
            a = parent[a][i];
            b = parent[b][i];
        }
    }
    return parent[a][0];
}
