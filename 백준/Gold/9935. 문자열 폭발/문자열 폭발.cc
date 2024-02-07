#include <iostream>
#include <string>
#include <algorithm>
#include <stack>
#define max_l 500000
using namespace std;

int main(void)
{
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    string s, bomb;
    cin >> s >> bomb;
    string ans = "";

    int length = s.length();
    int check = bomb.length() -1;
    int cnt = 0;

    for (int i = 0; i < length; i++) {
        ans += s[i];
        if ( ans[ans.length()-1] == bomb[check] ) {
            if (ans.length() >= bomb.length()) {
                cnt = 1;
                for ( int j = check-1 ; j>= 0 ; j--) {
                    if (ans[ans.length()-1-(check-j)] != bomb[j]) break;
                    cnt++;
                }
                if (cnt == bomb.length()) {
                    for (int i = 0 ; i <= check ; i++) ans.pop_back();
                }
            }
        }
    }
    if (ans.empty()) 
        cout << "FRULA";
    else
    cout << ans;
    return 0;

}