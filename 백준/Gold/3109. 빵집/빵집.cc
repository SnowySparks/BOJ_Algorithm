#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int R, C;
int dr[] {-1, 0, 1};
string inp[10000];
bool fd = false;

// 그리디 + dfs
// 가능하면 가장 위쪽 혹은 가장 아래쪽에 둬야함
// 위쪽부터 탐색할 꺼니 가장 위쪽 (가능한 가장 위 행에)
// 가능한 위쪽 부분

bool dfs(int r, int c) {
    if (c == C-1) {
        if (inp[r][c] == '.' && fd==false) {
            inp[r][c] = 'x';
            inp[r][c] = true;
            fd=true;
            return true;
        }
        else return false;
    }
    inp[r][c]='x';
    for (int i = 0; i < 3; ++i) {
        int nr = r + dr[i];
        if (nr >= 0 && nr < R && inp[nr][c+1] =='.') {
            if (dfs(nr,c+1)) {return true;}
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> R >> C;
    for (int i = 0; i < R; ++i) cin >> inp[i];
    int res =0;
    for (int i = 0; i < R; ++i) {
        fd = false;
        if (dfs(i,0)) ++res;
    }
    cout << res;
    return 0;
}