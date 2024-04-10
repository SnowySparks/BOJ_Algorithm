#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;
using ll = long long;

struct io {
    char ch;
    ll w = 0;
    bool first_use = false;
};

string inp[50];
io alpha[10];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    // 세팅
    for (int i = 0; i < 10; ++i) {
        alpha[i].ch = (char) ('A' + i);
    }
    // 입력
    int n; cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> inp[i];

        // 첫 숫자 (가장 큰 weight 부분) 등록
        alpha[ inp[i][0] - 'A' ].first_use = true;

        // 뒤집기
        reverse(inp[i].begin(), inp[i].end());

        // 가중치 계산
        ll d = 1;
        for (char ch : inp[i]) {
            alpha[ch - 'A'].w += d;
            d *= 10;
        }
    }

    // 첫 숫자가 안나온 알파벳 중 가장 작은 걸 가중치 가장 작게 부여 

    // 탐색
    ll not_first_use_min_w = 1e18;
    char not_first_low = 'a';
    for (int i = 0; i < 10; ++i) {
        if (alpha[i].first_use) continue;
        if (alpha[i].w < not_first_use_min_w) {
            not_first_use_min_w = alpha[i].w;
            not_first_low = alpha[i].ch;
        }
    }

    alpha[not_first_low - 'A'].w = 0;

    sort(alpha, alpha + 10, [](const io &a, const io &b) {
        return a.w > b.w;
    });

    ll ans = 0;
    for (int i = 0; i < 10; ++i) {
       ans += (9-i) * alpha[i].w;
    }
    cout << ans;

    return 0;
}