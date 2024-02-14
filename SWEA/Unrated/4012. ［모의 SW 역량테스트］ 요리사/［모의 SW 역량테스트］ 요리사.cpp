#include <iostream>
#include <cstring>
#include <vector>
using namespace std;
#define f(a, b, c) for(int a = b; a < c; ++a)
const int inf = 1e9+100;
int arr[16][16];
int n;
bool isv[16];
int ans;


vector<int> select(bool st) {
    vector<int> r;
    f(i, 0, n) {
        if (isv[i] == st) r.push_back(i);
    }
    return r;
}

int cook(const vector<int> &r) {
    int res = 0;
    for (int a : r) {
        for (int b : r) {
            res += arr[a][b];
        }
    }
    return res;
}

void back_track(int idx, int cnt) {
    if (cnt == n/2) {
        vector<int> s1 = select(false), s2 = select(true);
        ans = min(ans, abs(cook(s1) - cook(s2)));
        return;
    }

    f(i, idx, n) {
        isv[i] = true;
        back_track(i+1, cnt+1);
        isv[i] = false;
    }
    return;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // freopen("input.txt","r",stdin);
    memset(isv, 0, sizeof(isv));

    int T; cin >> T;
    f(tc, 1, T+1) {
        cin >> n;
        f(i, 0, n) f(j, 0, n) cin >> arr[i][j];
        ans = inf;
        back_track(0, 0);
        cout << '#' << tc <<' ' <<ans << '\n';
    }
    return 0;
}