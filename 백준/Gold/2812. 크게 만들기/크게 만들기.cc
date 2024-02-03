#include <iostream>
#include <stack>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    int sz = n - k;
    string s; cin >> s;
    stack<char> st;
    string ans = "";

    for (char ch : s) {
        while (!ans.empty() && k && ans.back() < ch) {ans.pop_back(); --k;}
        ans.push_back(ch);
    }

    while(k) {
        ans.pop_back();
        --k;
    }
    cout << ans;

    return 0;
}