#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int crane[50];
bool used[10000];
int box[10000];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    for (int i = 0 ; i < n; ++i) cin >> crane[i];
    int m; cin >> m;
    for (int i = 0; i < m; ++i) cin >> box[i];
    sort(crane, crane + n);
    sort(box, box + m);
    if (box[m-1] > crane[n-1]) {
        cout << -1; return 0;
    }
    int cnt = 0;
    int t = 0;
    while (cnt < m)
    {   ++t;
        int idx = n-1;
        for (int i = m-1; i >= 0; i--) {
            if (cnt == m) break;
            if (idx == -1) break;
            if (crane[idx] >= box[i] && !used[i]) {
                used[i] = true;
                ++cnt;
                idx--;
                continue;
            }
        }
        if (cnt == m) break;
    }

    cout << t;
    
    return 0;
}