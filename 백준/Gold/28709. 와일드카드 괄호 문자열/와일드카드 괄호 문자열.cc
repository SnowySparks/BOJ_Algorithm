#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

bool ispossible(const string &s) {
    int N = s.size(); //size
    int open_cnt = 0, close_cnt = 0;
    bool hasAsterisk = false;

    for (char ch : s) {
        if (ch == '(') open_cnt++;
        else if (ch == ')') close_cnt++;
        else if (ch == '*') hasAsterisk = true;
    }

    // 만약 * 이 있을 경우 
    // 왼쪽에서 텀색해서 ( 가 ) 보다 많거나 같은경우 그리고
    // 오른쪽부터 탐색해서 ) 가 ( 보다 많거나 같은 경우 이 2개가 만족해야 함

    if (hasAsterisk) {
        int cnt = 0;
        for (int i = 0; s[i] != '*'; ++i) {
            if (s[i]  == '(' || s[i] == '?') cnt++;
            else if (s[i] ==')') {
                cnt--;
                if (cnt < 0) return false;
            }
        }

        cnt = 0;
        for (int i = s.size()-1; s[i] !='*'; --i) {
            if (s[i] == ')' || s[i] == '?') cnt++;
            else {
                cnt --;
                if (cnt < 0) return false;
            }
        }
        return true;
    }

    // *없는 경우...
    if (open_cnt > N/2 || close_cnt > N/2) return false;
    if (N&1) return false;


    // 일단 최대한 ( 로 두다가 open_cnt == N/2 도달 후 부턴 전부 ) 로 취급
    int cnt = 0;
    for (char ch : s) {
        if (ch == '(') ++cnt;
        else if (ch == ')') {
            --cnt;
            if (cnt < 0) return false;
        }
        else {
            if (open_cnt < N/2) {
                ++cnt;
                open_cnt++;
            }
            else {
                cnt--;
                close_cnt++;
                if (cnt < 0) return false;
            }
        }
    }
    return true;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int T; cin >> T;
    string s;
    // 대 전제 그리디 조건
    // 항상 ( ) 의 최종 개수는 결국 같아야 하고
    // 모든 문자열 위치 기준 ( 개수는 ) 보다 많거나 같아야함
    while (T--)
    {
        cin >> s;
        if (ispossible(s)) cout <<"YES\n";
        else cout <<"NO\n";

    }
    

    return 0;
}