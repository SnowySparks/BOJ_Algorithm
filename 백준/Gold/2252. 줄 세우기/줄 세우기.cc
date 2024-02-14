#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

vector<int> graph[32001];
vector<int> inDegree(32001); //들어오는 degree들 합

int main(void) {
    ios_base::sync_with_stdio(false) ; cin.tie(NULL); cout.tie(NULL);
    int N , M; cin >> N >> M;
    vector<int> answer;
    int a,b;
    queue<int> q; //초기에 inDegree가 0인 것을 넣고 거기서 시작함.
    while (M--) {
        cin >> a >> b;
        graph[a].push_back(b);
        inDegree[b]++;
    }

    for (int i = 1 ; i <= N ; i++) {
        if (inDegree[i] == 0) q.push(i);
    }
    //원리
    // 큐의 가장 앞에 담긴 노드와 연결된 모든 노드들은 끊어버린다 ()
    // 그리고 진입차수가 0인 모든 노드를 큐에 넣는다
    // 그리고 q를 pop한다. pop한 순서가 곧 순서 그 자체가 된다
    // 총 N번 시행되고, N번 시행 되기 전 끝날 경우, 사이클이 발생했다는 뜻

    for (int i = 1 ; i <= N ; i++) {
        if (q.empty()) return 1; //사이클 발생
        
        int cur = q.front();
        q.pop();
        answer.push_back(cur);

        for (auto e  : graph[cur]) {
            if (--inDegree[e] == 0) q.push(e);
        }
    }

    for (auto e : answer) {
        cout << e << ' ';
    }
    return 0;

}
