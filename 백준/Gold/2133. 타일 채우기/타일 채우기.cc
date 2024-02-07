#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

long long dp[31];

int main(void) {
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    int n; cin >> n;

    dp[0] = 1;
    dp[2] = 3;

    for (int i = 4 ; i <= n ; i+=2) {
        dp[i] = dp[i-2] *3;
        for (int j = 0 ; j <i-2 ; j+=2) {
            dp[i] += (dp[j] * 2);
        }
    }

    cout << dp[n];

}