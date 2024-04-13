#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>
#include <queue>
#include <cstring>
using namespace std;
using pii = pair<int, int>;
#define f(a,b,c) for(int a=b; a<c; ++a)
#define EMPTY -2
#define WALL -1
#define RAINBOW 0
int mv[4][2] = {{-1, 0}, {1, 0}, {0, 1}, {0, -1}};
const int inf = 1e9;
int n, m;

int arr[20][20]; //map
int tmp[20][20];
bool v[20][20];
vector<pii> rainbow_loc; // rainbow 색 위치 판별
deque<int> dq;

void only_rainbow_reset() { //rainbow 위치만 방문 해제 처리
    for (auto &[r, c] : rainbow_loc) {
        v[r][c] =false;
    }
}

void rotate() {
    memcpy(tmp, arr, sizeof(arr));
    f(i, 0, n) {
        f(j, 0, n) {
            arr[n-1-j][i] = tmp[i][j];
        }
    }
}

void gravity() {
    f(c, 0, n) {
        f(r, 0, n) {
            if ( arr[r][c] == WALL) {
                int loc = r-1;
                while (!dq.empty())
                {
                   arr[loc][c] = dq.back();
                   dq.pop_back();
                   loc--;
                }
                continue;
            }

            if (arr[r][c] != WALL && arr[r][c] != EMPTY) {
                dq.push_back(arr[r][c]);
                arr[r][c] = EMPTY;
            }

            if (r == n-1) {
                int loc = n-1;

                while (!dq.empty())
                {
                   arr[loc][c] = dq.back();
                   dq.pop_back();
                   loc--;
                }
            }
        }
    }
}


pair<int, int> bfs(int sr, int sc, int color, bool change = false) {
    v[sr][sc] = true;
    if (change) arr[sr][sc] = EMPTY;
    queue<pii> q;
    q.push({sr, sc});
    int cnt = 1;
    int rainbow = 0;
    while (!q.empty())
    {
        int r= q.front().first, c = q.front().second; q.pop();
        for (auto &[dr, dc] : mv) {
            int nr = r +dr, nc = c + dc;
            if (nr < 0 || nc < 0 || nr >= n || nc >= n || v[nr][nc]) continue;
            if (arr[nr][nc] == color || arr[nr][nc] == 0) {
                v[nr][nc] = true;
                if (arr[nr][nc] == 0) rainbow++;
                q.push({nr, nc});
                if (change) arr[nr][nc] = EMPTY;
                cnt++;
            }
        }

    }
    return {cnt, rainbow};
}

int score() {
    int max_score = -1;
    int max_rainbow = -1;
    int cr, cc; //center
    
    f(i, 0, n) f(j, 0, n) {
        if (!v[i][j] && arr[i][j] > 0) {
            only_rainbow_reset();
            pii res = bfs(i, j, arr[i][j]);
            if (res.first <= 1) continue;
            
            if (max_score < res.first || max_score == res.first && max_rainbow < res.second ) {
                cr = i; cc = j; max_score = res.first; max_rainbow = res.second;
            }
            else if (max_score == res.first && max_rainbow == res.second) {
                if (cr < i || cr == i && cc < j) {
                    cr = i; cc = j;
                }
            }
        }
    }
    memset(v, 0, sizeof(v));
    if (max_score <= 0) return -inf;
    bfs(cr, cc, arr[cr][cc], true);

    return max_score*max_score;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt", "r", stdin);
    // freopen("output.txt","w",stdout);
    cin >> n >> m;
    f(i, 0, n) f(j, 0, n) cin >> arr[i][j];
   
    
    int ans = 0;

    while (true)
    {   
        // f(i, 0, n) {
        //     f(j, 0, n) cout << arr[i][j] << '\t';
        //     cout <<'\n';
        // }

        memset(v, 0, sizeof(v));
        rainbow_loc.clear();
        f(i, 0, n) f(j, 0, n) {
            if (arr[i][j] == RAINBOW) rainbow_loc.push_back({i, j});
        }


        int res = score();
        if (res <= 0 ) break;
        // cout << "res : " << res << '\n';
        ans += res;

        gravity();
        rotate();
        gravity();

        // cout << "---\n";

    }
    
    cout << ans;


    return 0;
}