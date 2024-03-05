#include <iostream>
#include <cstring>
#include <algorithm>
#define INF 100000000
#define f(a,b,c) for(int a=b;a<c;++a)
using namespace std;

int st1[100000];
int st2[100000];

void setting(const string &inp, int *target) {
    int a = inp.size();
    for (int i = 0 ; i < a; ++i) {
        if (inp[i] == '0') target[i] = 0;
        else target[i] = 1;
    }
}

bool issame(int n) {
    for (int i = 0; i < n;++i) if (st1[i] != st2[i]) return false;
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    string a, b;
    cin >> a >> b;
    setting(a, st1);
    setting(b, st2);

    // 문제 핵심 : , i (i >= 1) 부터 스위치 누르면 무조건 i-1전구는 i버튼에 의해서만 결정되어짐
    //따라서 0번 버튼을 눌렀을 경우, 안눌렀을 경우 나누어 보기
    // i-1 전구가 안맞으면 i버튼을 눌러서 조정하는 방식으로 처리하기

    //0번 버튼 눌렀을 경우
    st1[0] ^= 1;
    st1[1] ^= 1;
    int cnt = 1, ans = INF;
    for (int i = 1; i < n; ++i) {
        if (st1[i-1] == st2[i-1]) continue;
        else {
            ++cnt;
            for (int k = i-1; k < (min(n, i+2)); ++k) {
                st1[k]^=1;
            }
        }
    }
    if (issame(n)) ans = min(ans, cnt);
    setting(a, st1);

    //안누른경우
    cnt = 0;
    for (int i = 1; i < n; ++i) {
        if (st1[i-1] == st2[i-1]) continue;
        else {
            ++cnt;
            for (int k = i-1; k < (min(n, i+2)); ++k) {
                st1[k]^=1;
            }
        }
    }
    if (issame(n)) ans = min(ans, cnt);
    cout << (ans == INF ? -1 : ans);
    return 0;
}