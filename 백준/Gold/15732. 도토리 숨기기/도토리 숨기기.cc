#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int n, k; long long d; //상자갯수, 규칙갯수, 도토리 갯수
struct info {
    int a, b, c; //a 상자부터 b 상자까지 c개간격으로 
};

int add_more_ddotry(int endbox, const info &r) {
    if (r.a > endbox) return 0;
    return (min(r.b, endbox) - r.a)/r.c +1;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n >> k >> d;
    vector<info> rule(k);

    //이분탐색 하는 것 : 상자의 위치 값 그 자체!
    for (int i = 0 ; i < k ; ++i) {
        cin >> rule[i].a >>rule[i].b >>rule[i].c;
    }
    int ans = 0;
    int l = 1, r = n;

    while (l <= r) {
        int mid = (l+r)>>1;
        long long cnt = 0;
        for (int i = 0; i < k; ++i) {
            cnt += add_more_ddotry(mid, rule[i]);
        }
        if (cnt >= d){
            ans = mid;
            r = mid-1;
        }
        else l = mid+1;
    }
    cout << ans;
    return 0;
}