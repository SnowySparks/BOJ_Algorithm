#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#define f(a, b, c) for (int a= b;a<c;++a)
using namespace std;
int arr[20][20];
bool v[101];
int mv[4][2] = {{1, 1}, {1, -1}, {-1, -1}, {-1, 1}};
int n;
int ans;
int sr, sc;

//현재 "위치까지" 접근한 상태고, 현재 위치에 가기 위해 온 방향이 dir일 때 dfs 함수
void dfs(int r, int c, int len, int dir) {
    if (dir == 4) return;
    if (r < 0 || c < 0 || r >= n || c >= n) return; //범위 밖 종료
    if (r== sr &&  c == sc) ans = max(ans, len); // 원점 도달시 종료
    if (v[arr[r][c]]) return; //이미 만난 값이면 종료

    if (dir >= 2 && (len+1)*2 <= ans) return;
    //지금 여기 방문처리
    v[arr[r][c]] = true;

    int nr = r + mv[dir][0], nc = c + mv[dir][1]; //현재 방향 그대로 유지시
    dfs(nr, nc, len+1, dir);

    //방향 꺽을 경우
    nr = r + mv[dir+1][0];
    nc = c + mv[dir+1][1];
    dfs(nr, nc, len+1, dir +1);

    //원복 
    v[arr[r][c]] = false;
    return;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    f(tc, 1, T + 1) {
        cin >> n;
        ans = 0;
        f(i, 0, n) f(j, 0, n) cin >> arr[i][j];
        f(i, 0, n-2) f(j, 1, n-1) {
            sr = i; sc = j;
            v[arr[i][j]] = true;
            dfs(i + 1, j + 1, 1, 0);
            memset(v, 0, sizeof(v));
        }
        cout << '#' << tc <<' ' << (ans == 0 ? -1 : ans) << '\n';
    }
    return 0;
}