#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
using ll = long long;
#define f(a,b,c) for(int a=b;a<c;++a)
const ll max_val = 1e18;
ll dp[5002][5002];
int Knuth_pt[5002][5002];
ll sum[5002];
int n;

//크누스 최적해
//적용법 
//적용될 수 있는 dp식
// dp[i][j] : i ~ j까지의 비용의 최소값. 단 dp[i][j] = ((i < k < j) min( dp[i][k] + dp[k][j])) + sum[i][j]꼴
// sum[i][j] : i ~ j 까지의 단순 비용 총합

//전제조건 1 - 사각부등식
// sum[a][b] + sum[c][d] <= sum[a][d] + sum[b][c], a <= b <= c <= d

// 전제조건 2 - 단조성
// sum[b][c] <= sum[a][c], a <= b <= c <= d

//해당 조건에 맞을 경우 dp[i][j] = ((i < k < j) min( dp[i][k] + dp[k][j])) + sum[i][j] 에서
//가장 최소값을 찾을때의 k값은 반드시 다음과 같음
// a[i][j] -> dp[i][j] 에서의 최소값을 찾을때의 포인터 k를 저장하는 행렬일때
// a[i][j-1] <= a[i][j] == k <= a[i+1][j]를 만족한다


//해당 문제에서 dp[i][j] 를 i+1 ~ j까지의 총합으로 가정하기
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    f(tc, 1, T+1) {
        memset(dp, 0, sizeof(dp));
        memset(Knuth_pt, 0, sizeof(Knuth_pt));
        cin >> n;
        f(i, 1, n+1) {cin >> sum[i]; sum[i] += sum[i-1];}
        sum[n+1] = sum[n];
        f(i, 1, n+1) Knuth_pt[i-1][i] = i;

        f(len, 2, n+1) { //길이 범위
            for(int i = 0; i <= n-len; ++i) { //dp[i][j] 에서 i+1부터연산이라 가정했으니
                int j = i+len;
                
                dp[i][j] = max_val;

                int m1 = Knuth_pt[i][j-1], m2 = Knuth_pt[i+1][j];
                for (int k = m1; k <= m2; ++k) {
                    if (dp[i][j] > (dp[i][k]+dp[k][j] + sum[j] - sum[i])) {
                        dp[i][j] = (dp[i][k]+dp[k][j] + sum[j] - sum[i]);
                        Knuth_pt[i][j] = k;
                    }
                }
            }
        }
        cout << dp[0][n] <<'\n';
    }
    return 0;
}