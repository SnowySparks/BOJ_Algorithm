#include <iostream>
#define f(a,b,c) for(int a=b; a<=c;++a)
using namespace std;
int dp[301][301][11], n;
int arr[11];

int cnt (int x1, int y1, int x2, int y2, int num) {
    return dp[x2][y2][num] - dp[x2][y1-1][num] - dp[x1-1][y2][num] + dp[x1-1][y1-1][num];
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int tmp;
    cin >> n;

    f(r,1,n) {
        f(c,1,n) {
            cin >> tmp;
            dp[r][c][tmp] = 1;
        }
    }

    //행 방향으로 누적 (->)
    f(r,1,n) {
        f(c,1,n) {
            f(num,1,10) {
                dp[r][c][num] += dp[r][c-1][num];
            }
        }
    }
    f(c,1,n) {
        f(r,1,n) {
            f(num,1,10) {
                dp[r][c][num] += dp[r-1][c][num];
            }
        }
    }

    int q,x1,x2,y1,y2,c; cin >> q;
    while (q--) {
        c = 0;
        cin >> x1 >> y1 >> x2 >> y2;
        f(i,1,10) arr[i] = cnt(x1,y1,x2,y2,i);
        f(i,1,10) if (arr[i]>=1) c++;
        cout << c << '\n';
    }

    
}