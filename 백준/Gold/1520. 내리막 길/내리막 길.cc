#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int dp[501][501];
int map[501][501];
bool visited[501][501];

int dx[] = {1,-1,0,0};
int dy[] = {0,0,1,-1};
int m,n;
int nx, ny;
int dfs(int a, int b) {
    if (a == m && b == n) return 1; //가장 끝자리를 1로 설정
    if (visited[a][b]) return dp[a][b]; //이미 방문한 곳은 바로 리턴
    visited[a][b] = true; //방문처리

    for (int i = 0 ; i < 4 ; i++) {
        nx = a + dx[i];
        ny = b + dy[i];

        if (nx > 0 && ny > 0 && nx <= m && ny <= n) {
            if (map[nx][ny] < map[a][b] ) {
                //이전 위치보다 새 위치가 더 작은 값을 가진 경우
                //이전 위치는 기존값에 추가로 dfs가 추가됨
                dp[a][b] += dfs(nx,ny);
            }
        }

    }
    return dp[a][b];
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> m >> n;

    for (int i = 1 ; i <= m ; i++) {
        for (int j = 1 ; j <= n ;j++) {
            cin >>map[i][j];
        }
    }
    cout << dfs(1,1);
    return 0;
}