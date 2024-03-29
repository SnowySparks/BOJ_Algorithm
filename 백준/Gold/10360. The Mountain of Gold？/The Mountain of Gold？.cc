#include <iostream>
#include <cstring>
#include <vector>
#include <queue>
#include <algorithm>
#define INF (int)1e9
using namespace std;
int n, m;
vector<pair<int, int> > adj[1001];
vector<int> rev[1001];
int dist[1001];
bool check[1001];
bool v[1001];

int main() {
	ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int T; cin >> T;
	for (int tc = 1; tc <= T; tc++) {
		cin >> n >> m;
        
        // 초기화
        memset(check, 0, sizeof(check));
        memset(v, 0, sizeof(v));
        for(int i = 0; i < n; ++i) {
            adj[i].clear();
            rev[i].clear();
            dist[i] = INF;
        }

        // 간선 및 역방향 간선 입력
		while (m--) {
			int a, b, c; cin >> a >> b >> c;
			adj[a].push_back({ b, c });
			rev[b].push_back(a);
		}

        // 벨만 - 포드, 추가적으로 음의 사이클이 생기는 노드 체크
        dist[0] = 0;
		for (int cnt = 0; cnt < n; cnt++) {
			bool update = false;
			for (int i = 0; i < n; i++) for (const auto& [j, cost] : adj[i]) {
				if (dist[j] > dist[i] + cost) {
					dist[j] = dist[i] + cost, update = true;
					if (cnt == n-1) check[j] = 1;
				}
			}
			if (!update) break;
		}

        // 역방향 간선을 기준으로 0번부터 다른 음의 사이클로 갈 수 있는가 판단
		v[0] = true;
		queue<int> q; 
        q.push(0);

		while (!q.empty()) {
			int cur = q.front(); q.pop();
			for (const int& nxt : rev[cur])
				if (!v[nxt]) {
                    q.push(nxt);
                    v[nxt] = 1;
                }
		}

		bool flag = false;
		for (int i = 0; i < n; i++) if (v[i] && check[i]) flag = true;
		cout << "Case #" << tc << ": " << (flag ? "possible" : "not possible") << '\n';
	}
}