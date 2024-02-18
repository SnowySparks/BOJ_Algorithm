#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <algorithm>
using namespace std;
#define INF 10000000
#define MAX_VAL 1000
#define f(a,b,c) for (int a=b;a<c;++a)
vector<int> adj[MAX_VAL+1];
int dp[1000][1000];
int n;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    int T; cin >> T;
    int tmp;
    for (int tc = 1; tc <=T;++tc) {
        cin >> n;
        f(r, 0, n) {
            f(c, 0, n) {
                cin >> dp[r][c];
                if (r == c) continue;
                else if (dp[r][c] == 0) dp[r][c] = INF;
            }
        }
        
        //플루이드 워셜
        f(mid, 0, n) {
            f(start, 0, n) {
                f(end, 0, n) {
                    if (mid == start || start == end || mid == end) continue;
                    int mid_pas = dp[start][mid] + dp[mid][end];
                    if (mid_pas < dp[start][end]) {
                        dp[start][end] = mid_pas;
                        dp[end][start] = mid_pas;
                    }
                }
            }
        }

        int ans = INF;
        f(r, 0, n) {
            int cnt = 0;
            f(c, 0, n) cnt+=dp[r][c];
            ans = min(ans, cnt);
        }
        cout << '#' <<tc <<' ' << ans << '\n';
    }
    return 0;
}