#include <iostream>
#include <cstring>
#include <vector>
#include <deque>
#include <queue>
using namespace std;
#define f(a,b,c) for(int a=b; a<c;++a)
int N, W, H; //구슬 갯수, 너비(열개수), 높이(행개수)
int ans; //정답 -> 가능한 최소, 초깃세팅 : W * H

struct info {
    int r, c, d;
};

//남은 블럭 갯수 카운팅
int left_block(const vector<vector<int> > &dt) {
    int res = 0;
    f(i,0,H) {
        f(j, 0, W) {
            if (dt[i][j]) ++res;
        }
    }
    return res;
}

//입력받은 블록 정보에 대해서 모든 블럭을 아래로 이동
void move_blocks(vector<vector<int> > &dt) {
    deque<int> dq;
    f(col, 0, W) {
        f(row, 0, H) {
            if (dt[row][col]) dq.push_back(dt[row][col]);
            dt[row][col] = 0;
        }
        int idx = H-1;
        while (!dq.empty()) {
            dt[idx][col] = dq.back();
            dq.pop_back();
            --idx;
        }
    }
}

//해당 선택된 열에 공 떨굴때의 시물레이션
void delete_block(int idx, vector<vector<int> > &dt) {
    int sr, sc = idx;
    //가장 위 블록을 찾기
    f(row, 0, H) {
        if (dt[row][idx]) {
            sr = row;
            break;
        }
    }
    //bfs 탐색
    queue<info> q;
    q.push({sr, sc, dt[sr][sc]});
    while (!q.empty()) {
        int r = q.front().r, c = q.front().c, d = q.front().d - 1; q.pop();
        dt[r][c] = 0;
        if (d == 0) continue;
        for (int row = max(r-d, 0); row <= min(r+d,H-1); ++row) {
            if (dt[row][c]) {
                q.push({row, c, dt[row][c]});
                dt[row][c] = 0;
            }
            else continue;
        }
        for (int col = max(c-d, 0); col <= min(c+d,W-1); ++col) {
            if (dt[r][col]) {
                q.push({r, col, dt[r][col]});
                dt[r][col] = 0;
            }
            else continue;
        }
    }
    move_blocks(dt);
}

void dfs(vector<vector<int> > dt,int cnt) { //dfs
    if (cnt == N) {
        ans = min(ans, left_block(dt));
        return;
    }
    
    //만약 모든 블럭이 비어 있는 경우는 조기 종료
    int left_col = 0;
    for (int col = 0; col < W; ++col) {
        if (dt[H-1][col]) ++left_col;
    }
    if (left_col == 0) {
        ans = 0;
        return;
    }
    //백업용
    vector<vector<int> > cp(H, vector<int>(W, 0));
    copy(dt.begin(), dt.end(), cp.begin());

    for (int col = 0; col < W; ++col) {
        if (!dt[H-1][col]) continue; //해당 열에 더이상 블럭이 없으면 안떠구는게 무조건 이득
        delete_block(col, dt); //해당 열에 공떨구기
        dfs(dt, cnt+1);
        copy(cp.begin(), cp.end(), dt.begin()); //롤 백
    }
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> N >> W >> H;
        vector<vector<int> > vec(H, vector<int>(W)); //블록 정보들
        for (int i = 0 ; i < H; ++i) {
            for (int j = 0 ; j < W; ++j) {
                cin >> vec[i][j];
            }
        }
        ans = left_block(vec);
        dfs(vec, 0);
        // f(i, 0, H) {
        //     f(j, 0, W) cout << vec[i][j] <<' ';
        //     cout << '\n';
        // }
        cout << '#' << tc << ' ' << ans << '\n';
    }
    return 0;
}