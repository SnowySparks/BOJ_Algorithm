#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

int use[10] = {6, 2, 5, 5, 4, 5, 6, 3, 7, 6};
long long dp[101];
long long arr[8] = {0, 0, 1, 7, 4, 3, 0, 8};

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    dp[1] = 99999;
    dp[2] = 1;
    dp[3] = 7;
    dp[4] = 4;
    dp[5] = 2;
    dp[6] = 6;
    dp[7] = 8;

    for (int i = 8; i <= 100; ++i)
        dp[i] = 1e18;

    int T, n;
    cin >> T;
    for (int i = 8; i <= 100; ++i)
    {
        for (int k = 2; k <= 7; ++k)
        {
            long long t = (k == 6) ? 0 : dp[k];
            dp[i] = min(dp[i], dp[i - k] * 10 + t);
        }
    }
    while (T--)
    {
        cin >> n;
        int tmp = n;
        string ans_big = "";

        if (n & 1)
        {
            ans_big.push_back('7');
            n -= 3;
        }
        while (n)
        {
            ans_big.push_back('1');
            n -= 2;
        }

        cout << dp[tmp] << ' ' << ans_big << '\n';
    }

    return 0;
}