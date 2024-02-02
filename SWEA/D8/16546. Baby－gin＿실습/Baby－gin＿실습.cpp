#include <iostream>
#include <cstring>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    int cnt[10]; string s;
    for (int tc = 1; tc <= 10 ; ++tc) {
        memset(cnt,0,sizeof(cnt));
        cin >> s;
        for (char c : s) ++cnt[c - '0'];

        for (int i = 0 ; i < 10 ; ++i) cnt[i]%=3;

        for (int i = 1 ; i < 9 ; ++i) {
            int min_val = min(cnt[i-1],min(cnt[i],cnt[i+1]));
            cnt[i-1]-=min_val;
            cnt[i]-=min_val;
            cnt[i+1]-=min_val;
        }
        cout << '#' << tc <<' ';
        bool fd = false;
        for (int i = 0 ; i < 10 ; ++i) {
            if (cnt[i]) {
                cout << "false\n";
                fd =true;
                break;
            }
        }
        if (!fd) {
        cout <<"true\n";}
    }
    return 0;
}