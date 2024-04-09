#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;
#define H 1
#define T 0
int n;
int coin[20][20];

int ans = 1024;

void check() {
    int total = 0;
    for (int col = 0; col < n; ++col) {
        int cnt = 0;
        for (int row = 0; row < n; ++row) {
            if (coin[row][col] == T) ++cnt;
        }
        if (n-cnt < cnt) total += n-cnt;
        else total += cnt;
    }
    ans = min(ans, total);
    return;
}

void dfs(int now_loc) {
    if (now_loc == n) {
        check();
        return;
    }

    for (int i = 0; i < n; ++i) {
        coin[now_loc][i] ^= 1;
    }
    dfs(now_loc+1);

    for (int i = 0; i < n; ++i) {
        coin[now_loc][i] ^= 1;
    }
    dfs(now_loc+1);

    return;   
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    string s;
    for (int i = 0;i < n; ++i) {
        cin >> s;
        for (int k = 0; k < n; ++k) {
            if (s[k] == 'H') coin[i][k] = H;
            else coin[i][k] = T;
        }
    }

    dfs(0);
    cout << ans;

    return 0;
}