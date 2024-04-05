#include <iostream>
#include <algorithm>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    string s, t; cin >> s >> t;

    // 원리 : 어차피 둘다 결국 "뒤에 추가" 하는 거임
    // 따라서 t -> s로 역방향으로 가는 방법으로 두면
    // a 이면 그냥 빼기
    // b이면 빼고 뒤집기

    while (s.size() != t.size())
    {
        if (t.back() == 'A') t.pop_back();
        else {
            t.pop_back();
            reverse(t.begin(), t.end());
        }
    }

    if (s == t) cout << 1;
    else cout << 0;

    return 0;
}