#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

int dp[100001];

int main(void) {
    ios::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);
    dp[0] = 1;
    int n,k,temp; cin >> n >> k;
    vector<int> coins;
    while (n--) {
        cin >> temp;
        coins.push_back(temp);
    }

    for (auto e : coins) {
        for (int j = e ; j<=k;j++) {
            dp[j]=dp[j] + dp[j-e];
        }
    }
    cout << dp[k];

    return 0;
}