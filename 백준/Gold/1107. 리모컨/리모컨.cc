#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int loc; cin >> loc;
    int n; cin >> n;
    int ans = abs(loc - 100); //100에서 부터 시작하는 + - 입력
    vector<char> prohibit(n);
    for (int i = 0 ; i < n; ++i) cin >> prohibit[i];
    if (loc == 100) {
        cout << 0;
        return 0;
    }
    for (int i = 0; i <= 1000000; ++i) { //완탐
        string tmp = to_string(i); //문자열로
        if (ans <= (int)tmp.size()) continue; //금지된 숫자 하나라도 있음 해당 채널 입력 불가
        bool yes = true;
        for (char ch : prohibit) {
            if (tmp.find(ch) != string::npos) {
                yes = false;
                break;
            }
        }
        if (yes) { //가능한 채녈이면, 채녈 번호입력횟수 , 원하는 목표까지 탐색
            ans = min(ans, (int)tmp.size() + abs(i-loc));
        }
    }
    cout << ans;
}