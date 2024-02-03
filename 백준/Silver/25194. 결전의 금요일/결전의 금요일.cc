#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<int> inp;
bool dp[7];

void doit (int idx, int val, int n) {
    if (idx == n) return;
    dp[val%7]=true;
    doit(idx+1,val+inp[idx],n);
    doit(idx+1,val,n);
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n,cnt=0; cin >> n;
    for (int i = 0 ; i < n; ++i) {
        int tmp; cin >> tmp; tmp%=7;
        if (tmp) {++cnt; inp.push_back(tmp);}
    }

    if (cnt >= 7) { //비둘기집 원리 - 나머지가 존재하는 일 수가 7개이상 -> 무조건 금요일 어떻게든 만듬
        cout << "YES"; return 0;
    }  
    inp.push_back(0);
    doit(0,0,(int)inp.size());
    if (dp[4]) cout <<"YES";
    else cout <<"NO";
    return 0;
}