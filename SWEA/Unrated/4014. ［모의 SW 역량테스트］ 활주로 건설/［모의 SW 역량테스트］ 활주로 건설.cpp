#include <iostream>
#include <cstring>
using namespace std;
#define f(a, b, c) for (int a = b; a<c; ++a)
int n, x;
int arr[20][20];

int dr[] = {0, 1};
int dc[] = {1, 0};

bool ispossible(int sr, int sc, int dir) {
    int now_num=arr[sr][sc];
    int before_num = arr[sr][sc];
    int cnt = 1;
    bool need_install = false;

    for(int r = sr +dr[dir], c = sc + dc[dir], idx = 1; r < n && c <n; r+=dr[dir], c+=dc[dir], ++idx) {
        before_num = now_num;
        now_num = arr[r][c];
        if (now_num == before_num) {
            ++cnt;
            if (need_install && cnt==x) {
                need_install = false;
                cnt =0;
            }
        }
        else if (now_num - before_num == 1) {
            if (cnt >= x) {
                cnt = 1;
            }
            else {
                return false;
            }
        }

        else if (now_num - before_num == -1) {
            if (need_install && cnt < x) return false;
            need_install = true;
            cnt = 1;
        }
        else if (abs(now_num-before_num) >= 2) {
            return false;}
        if (idx == n-1 && need_install ) {

            if (cnt < x) {
  
                return false;
            }
        }
    }
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    for (int tc = 1; tc <= T; ++tc) {
        cin >> n >> x;
        f(r, 0, n) {
            f(c, 0, n) {
                cin >> arr[r][c];
            }
        }
        int ans = 0;
        f(r, 0, n) {
            ans += (ispossible(0,r,1) ? 1 : 0);
            ans += (ispossible(r,0,0) ? 1 : 0);
        }
        cout <<'#' <<tc <<' ' <<ans <<'\n';
    }
    return 0;
}