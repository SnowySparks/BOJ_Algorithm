#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

vector<int> gh[3001];
int v[3001], d[3001], n;
int dfs(int now, int pre) {
    // v값 : 0 --> 탐색 x, 1 --> 거쳤으나 사이클 못찾은 상태 , 2 --> 사이클임 해당 노드는 , -1 : 해당 노드 사이클아님, -2 : 이미 찾았고, 사이클에 포함되지 않는 now - pre관계(노선)
    if (v[now] == 1 ) return now; // 현재 위치가 방문한 노드(아직 사이클 못찾았었음) --> 사이클 --> 해당 노드 도출 (어차피 역 번호가 1 이상이기에 가능한 조치)
    v[now] = 1; // 1 : 탐색은 했으나 아직 사이클을 못 찾은 상태
    for (int e : gh[now]) {
        if (e == pre) continue; //역방향으로 인한 사이클 방지
        int r = dfs(e,now); // 다음 노드 탐색 , 1 상태는 이미 걸러짐
        //이제 사이클 이거나 , 역 끝이거나 부터 역으로 고려
        if (r == -2) return -2; 
        if (r >= 1) { //사이클 이거나 사이클 발견한 상태
            v[now] = 2; //해당 노드는 사이클 안
            if (now == r) return -2; // 사이클 시작 위치 동일한 상황 --> 존재x노선
            else return r;
        }
    }
    return -1;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0 ; i < n ; i ++) {
        int a, b; cin >> a >> b;
        gh[a].push_back(b);
        gh[b].push_back(a);
    }
    dfs(1,0);
    queue<int> q;
    for (int i =1 ; i <= n ; i++) {
        if (v[i] == 2) {
            d[i] = 0; q.push(i);
        }
        else d[i] = -1;
    }

    while (!q.empty()) {
        int loc = q.front(); q.pop();
        for (int e : gh[loc]) {
            if (d[e] == -1) {
                d[e] = d[loc] +1;
                q.push(e);
            }
        }
    }
    for (int i =1 ; i <= n ; i++) cout << d[i] <<' ';
    return 0;

}