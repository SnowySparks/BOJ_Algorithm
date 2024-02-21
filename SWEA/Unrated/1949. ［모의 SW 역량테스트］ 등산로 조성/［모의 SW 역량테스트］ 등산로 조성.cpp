#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;
#define f(a,b,c) for (int a=b;a<c;a++)

int dr[] = {1, -1, 0, 0};
int dc[] = {0, 0, 1, -1};

int arr[8][8];
bool v[8][8];
int n, k;

int dfs(int r, int c, bool used) {
    int cnt = 1;
    int res = 0;
    v[r][c] = true;
    f(i, 0, 4) {
        int nr = r + dr[i], nc = c + dc[i];
        if (nr < 0 || nc < 0 || nr >=n || nc >=n) continue;
        if (v[nr][nc]) continue;
        if (arr[nr][nc] < arr[r][c]) {
            res = max(res, dfs(nr, nc, used));
        }
        else {
            if (used) continue;
            else if (arr[nr][nc] - k <= arr[r][c] - 1)  {
                int tmp = arr[nr][nc];
                arr[nr][nc] = arr[r][c] - 1;
                res = max(res, dfs(nr, nc, true));
                arr[nr][nc] = tmp;
            }
        }
    }
    v[r][c] = false;
    return cnt+res;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        //input
        int max_height = 0;
        vector<pair<int ,int> > loc;
        cin >> n >> k;
        f(r, 0, n) {
            f(c, 0, n) {
                cin >> arr[r][c];
                max_height = max(max_height, arr[r][c]);
            }
        }
        //find max_height
        f(r, 0, n) {
            f(c, 0, n) {
                if (arr[r][c] == max_height) loc.push_back({r, c});
            }
        }
        int ans = 0;
        for (auto &[r, c] : loc) {
            ans = max(ans, dfs(r, c, false));
        }
        cout << '#' << tc << ' ' << ans <<'\n';
    }
    return 0;
}