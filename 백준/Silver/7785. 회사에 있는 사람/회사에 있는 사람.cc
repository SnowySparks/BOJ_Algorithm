#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>
using namespace std;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    string p, cmd;
    unordered_set<string> st;
    while (n--)
    {
        cin >> p >> cmd;
        if (cmd == "enter") {
            st.insert(p);
        }
        else {
            st.erase(p);
        }
    }

    vector<string> ans;
    for (const string &a : st) {
        ans.push_back(a);
    }

    sort(ans.begin(), ans.end());
    reverse(ans.begin(), ans.end());
    for (const string &a : ans) cout << a << '\n';
    
    return 0;
}