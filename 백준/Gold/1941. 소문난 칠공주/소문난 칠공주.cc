#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstring>
#include <queue>
using namespace std;
#define N 5
#define f(a, b, c) for(int a = b; a < c; a++)
#define pii pair<int, int>

const int dx[] = {0, 0, 1, -1};
const int dy[] = {1, -1, 0, 0};
char mp[5][5];
bool v[5][5];
bool lst_block[5][5];
int lst[7][2]; // 목록

int pts_to_int(int r, int c) {
    return r * N + c;
}

pii int_to_pts(int n) {
    return {n / N, n % N};
}

bool is_valid(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < N;
}

vector<int> possible_list;

// 25개중 7개 선택 가능한 모든 경우의 수 구하기
void back_track(int val, int cnt, int last_loc) {
    if (cnt == 7) {
        // cout << val;
        possible_list.push_back(val);
    }
    else {
        for(int i = last_loc ; i < 25; ++i) {
            val = val | ( 1 << i);
            back_track(val, cnt+1, i+1);
            val = val & (~(1 << i));
        }
    }
}


// 가능한 목록들 중 조건에 부합하는 경우인가 아닌가?
bool is_possible(int val) {
    int cnt = 0;
    memset(v, 0, sizeof(v));
    memset(lst_block, 0, sizeof(lst_block));
    f(i, 0, 25) {
        if (val & (1 << i)) {
            auto [r, c] = int_to_pts(i);
            lst[cnt][0] = r; lst[cnt][1] = c;
            ++cnt;
            lst_block[r][c] = true;
        }
    }
    cnt = 0; // 첫 블럭 기준 접하는 갯수
    queue<pair<int ,int>> q;
    q.push({lst[0][0], lst[0][1]});
    v[lst[0][0]][lst[0][1]] = true;
    int scnt = 0; // S개수
    while (!q.empty())
    {
        int r = q.front().first, c = q.front().second; q.pop();
        ++cnt;
        if (mp[r][c] == 'S') ++scnt;
        f(i, 0, 4) {
            int nr = r + dx[i], nc = c + dy[i];
            if (!is_valid(nr, nc) || v[nr][nc]) continue; // 영역밖 및 이미 방문 -> 컷
            if (!lst_block[nr][nc]) continue;; // -> 7개 블록에 해당하는가?
            v[nr][nc] = true;
            q.push({nr, nc});
        }
    }
    if (cnt == 7 && scnt >= 4) return true;
    return false;
    
}



int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    f(i, 0, 5) f(j, 0, 5) cin >> mp[i][j];
    back_track(0, 0, 0);
    int ans = 0;
    for (int val : possible_list) {
        ans += (is_possible(val) ? 1 : 0);
    }
    cout << ans;
    return 0;
}