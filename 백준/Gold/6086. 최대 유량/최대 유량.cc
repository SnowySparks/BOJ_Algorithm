#include <iostream>
#include <queue>
#include <vector>
#include <cstring>
#define N_MAX 52
const int inf = 1e9 + 7;
#define f(a, b, c) for(int a= b; a<c;++a)
using namespace std;
// i -> j 으로의 의미
int capacity[N_MAX][N_MAX]; // 용량
int flow[N_MAX][N_MAX]; // 유량
int parent[N_MAX]; // 현재 위치갸 i 일때 그 부모의 위치 (source쪽)
vector<int> adj[N_MAX]; //인접 리스트

int n;

int char_int(char ch) {
    if ('A' <= ch && ch <= 'Z') return ch - 'A';
    return ch-'a' + 26;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    char fr, to; int tmp;
    int f, t;
    f(i, 0, n) {
        cin >> fr >> to >> tmp;
        f = char_int(fr); t = char_int(to);
        capacity[f][t] += tmp;
        capacity[t][f] += tmp;
        adj[f].push_back(t);
        adj[t].push_back(f);
    }
    int source = char_int('A'), sink = char_int('Z'); //시작과 끝
    int total_flow = 0; // 정답

    while (true)
    {   
        // 시물레이션 전 초기화
        queue<int> q;
        memset(parent, -1, sizeof(parent));
        parent[source] = source;
        q.push(source);

        // 증가 경로 찾기
        while (!q.empty() && parent[sink] == -1)
        {   
            int cur = q.front(); q.pop();
            for (int next : adj[cur]) {
                int residual_capacity = capacity[cur][next] - flow[cur][next]; //잔여 용량
                // 잔여 용량이 있고 다음 노드에 대한 부모 탐색이 안된 상태인 경우
                if (residual_capacity > 0 && parent[next] == -1) {
                    parent[next] = cur;
                    q.push(next);
                    // 만약 다음 노드가 sink이면 끝내기
                    if (next == sink) break;
                }
            }
        }
        // 더이상 남는 잔여 용량이 안되어서 sink가 source로 갈 길 이 없으면 종료
        if (parent[sink] == -1) break;

        // 현 탐색한 경로 상 흐를 수 있는 용량의 최저치. (즉 잔여 용량 최저치 찾기)
        // 역으로 탐색
        int mininum_flow = inf;
        for (int i = sink; i != source; i=parent[i]) {
            // 증가 경로로 가면서 p[i] -> i로 가는 잔여 용량의 최저값을 찾음
            mininum_flow = min(mininum_flow, capacity[parent[i]][i] - flow[parent[i]][i]);
        }

        // 찾은경우, 해당 경로에유량 보내기

        for (int i = sink; i != source; i=parent[i]) {
            flow[parent[i]][i] += mininum_flow;
            // 역방향 유량 가산.
            flow[i][parent[i]] -= mininum_flow;
        }
        total_flow += mininum_flow;
    }
    cout << total_flow;
    return 0;
}