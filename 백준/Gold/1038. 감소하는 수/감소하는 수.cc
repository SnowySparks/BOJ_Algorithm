#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

vector<long long> lst;

void dfs(long long x) {
    lst.push_back(x);
    long long start_num = (x%10)-1;
    for (;start_num >= 0; start_num--) {
        dfs(x*10 + start_num);
    }
    return;
}


int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    if (n >= 1023) {
        cout << -1;
        return 0;
    }
    for (long long i = 0; i < 10; ++i) dfs(i);
    sort(lst.begin(), lst.end());
    cout << lst[n];

    return 0;
}

// 가장큰 감소수 : 9876543210, 
// 10C1 + 10C2 + ... 10C10 == 2^10 -1 이 총 경우의 수.