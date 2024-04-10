#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

int n, m;

// 어느 한 점에서 바라 볼 때 관련된 컨닝 관계 상대적 위치
int mv[6][2] = {{-1, -1}, {0, -1}, {1, -1}, {-1, 1}, {0, 1}, {1, 1}};

int ton(int r, int c) {
    return r*m + c;
}

vector<int> gh[7000];
bool v[7000];
bool mp[80][80]; //map, 0 : . // 1 : x
int assign[7000];

void reset() {
    memset(v, 0, sizeof(v));
    memset(assign, -1, sizeof(assign));

    for (int i = 0; i < n*m+1; ++i) gh[i].clear();
    
}

bool dfs(int x) {
    for (int nxt : gh[x]) {
        if (v[nxt]) continue;
        v[nxt] = true;
        if (assign[nxt] == -1 || dfs(assign[nxt])) {
            assign[nxt] = x;
            return true;
        }
    }
    return false;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    char ch;
    while (T--)
    {   
        int totalx = 0; // x counting

        cin >> n >> m;

        reset();

        // input
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cin >> ch;
                mp[i][j] = (ch == 'x');
                if (ch == 'x') totalx++;
            }
        }

        // graph 구성
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {

                // 해당 좌표 기준, 컨닝 관계 가능한 모든 부분 탐색 및 가능성 있는 부분 전부 연결
                if (mp[r][c]) continue;

                for (auto &[dr, dc] : mv) {
                    int nr = r + dr, nc = c + dc;
                    if (nr < 0 || nr >= n || nc < 0 || nc >= m || mp[nr][nc]) continue;

                    gh[ton(r,c)].push_back(ton(nr,nc));
                }
            }
        }

        int max_matching = 0;
        // 이분 매칭 시행. 0, 2, 4..번째 열만 시행 (1, 3, 5 번째 해도 되긴 될듯?)
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; c+=2) { 
                if (mp[r][c]) continue; // x 부분은 스킵
                memset(v, 0, sizeof(v));
                if (dfs(ton(r,c))) max_matching++;
            }
        }
        // 쾨닉의 정리 : 전체 노드수 = 최대 독립 집합 노드수 + 최대 매칭 수
        cout << n*m - totalx - max_matching << '\n';
    }
    

    return 0;
}