#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define INF 0x7f7f7f7f

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, tlength, st, en;
    cin >> n >> tlength;

    vector<pair<int, int> > pts;
    for (int i = 0; i <n; ++i) {
        cin >> st >> en;
        if (st > en) {
            pts.push_back({en, st});
        }
    }
    sort(pts.begin(), pts.end());

    st = -INF; en = -INF;
    long long ans = tlength;

    for (auto &[s, e] : pts) {
        if (en < s) {
            ans += 2*(en - st);
            en = e; st =  s;
        }
        else {
            en = max(en, e);
        }
    }
    ans += 2*(en - st);
    cout << ans;
    return 0;
}

// 정 방향은 어차피 쭊 가면 되니 그냥 0~M 한번
// 역 방향은 역으로 갔다가 다시 돌아가야 하니 2배 만큼 거리
// 역방향 거리 겹치는 거 고려해서 총 합의 2배를 답에 추가로 더하면 끝