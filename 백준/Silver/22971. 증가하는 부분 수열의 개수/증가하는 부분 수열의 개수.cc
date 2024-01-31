#include <iostream>
#include <vector>
using namespace std;
#define f(a,b,c) for(int a=b;a<c;a++)
const int mol = 998244353;
int arr[5001];
int dp[5001];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    f(i,1,n+1) cin >> arr[i];
    dp[0] = 1;
    f(i,1,n+1) {
        f (k,0,i) if (arr[k] < arr[i]) dp[i]=(dp[i] + dp[k])%mol; 
    }
    f(i,1,n+1) cout << dp[i] << ' ';
    return 0;
}