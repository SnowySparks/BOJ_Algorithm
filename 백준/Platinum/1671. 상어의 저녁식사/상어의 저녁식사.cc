#include <iostream>
#include <vector>
#include <cstring>
#include <algorithm>
using namespace std;

int n;
vector<int> adj[51];
int assign[51];
bool v[51];

int shark[51][3];


bool dfs(int x) {
    // cout << x <<'\n';
    for (int &nxt : adj[x]) {
        if (v[nxt]) continue;
        v[nxt] = true;
        if (!assign[nxt] || dfs(assign[nxt])) {
            assign[nxt] = x;
            return true;
        }
    }
    return false;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j < 3; ++j) cin >> shark[i][j];
    }

    int ans = 0;
    for(int i = 1; i < n; ++i) {
        for (int j = i+1; j <= n; ++j) {
            
            int l = 0, r = 0;
            for (int k = 0; k < 3; ++k) {
                if (shark[i][k] <= shark[j][k]) r++;
                if (shark[i][k] >= shark[j][k]) l++;
            }

            if (l == r && 3 == l) {
                adj[i].push_back(j);
                continue;
            }

            if (l == 3) {
                adj[i].push_back(j);
            }
            if (r == 3) {
                adj[j].push_back(i);
            }

        }
    }
    for (int i = 1; i <= n; ++i) {
        for (int k = 0; k < 2; ++k) {
            memset(v, 0, sizeof(v));
            if (dfs(i)) ans++;
        }
    }

    cout << n - ans;


    return 0;
}