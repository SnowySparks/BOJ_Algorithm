#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;
int n;
int func[200001][22];

int query(int lv, int x) {
    for (int i = 0 ; lv ; ++i) {
        if (lv&1) x = func[x][i];
        lv >>= 1;
    }
    return x;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int q;
    cin >> n;

    for (int i = 1; i <= n; ++i) cin >> func[i][0];
    for (int lv = 1; lv <= 21; ++lv) {
        for (int i = 1;  i <= n ; ++i) {
            func[i][lv] = func[ func[i][lv-1] ][lv-1];
        }
    }
    cin >> q;
    while (q--) {
        int a, b; cin >> a >> b;
        cout << query(a, b) << '\n';
    }
    return 0;
}