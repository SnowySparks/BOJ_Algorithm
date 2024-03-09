#include <iostream>
#include <vector>
using namespace std;

bool select_char[26];
string word[50];
int ans = 0;
int n, k;

void back_track(int loc, int cnt) {
    if (cnt == k) {
        int res = 0;
        for (int i = 0; i < n; ++i) {
            bool yes = true;
            for (int t = 4; t < (int)word[i].size()-4; ++t) {
                if ( !select_char[word[i][t]-'a'] ) {
                    yes = false;
                    break;
                }
            }
            if (yes) ++res;
        }
        ans = max(ans, res);
        return;
    }

    if (26 - loc + cnt < k) return;

    for (int idx = loc; idx < 26; ++idx) {
        if (!select_char[idx]) {
            select_char[idx] = true;
            back_track(idx + 1, cnt + 1);
            select_char[idx] = false;
        }
    }
    return;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k;
    for (int i = 0; i < n ; ++i) {
        cin >> word[i];
    }
    if (k < 5) {
        cout << 0;
        return 0;
    }
    k-=5;

    select_char['a' - 'a'] = true;
    select_char['t' - 'a'] = true;
    select_char['c' - 'a'] = true;
    select_char['i' - 'a'] = true;
    select_char['n' - 'a'] = true;
    back_track(0, 0);
    cout << ans;

    return 0;
}