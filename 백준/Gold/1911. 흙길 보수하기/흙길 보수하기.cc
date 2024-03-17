#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int N, L, start, end;
    cin >> N >> L;
    vector<pair<int,int>> v;

    for (int i = 0; i < N; ++i) {
        cin >> start >> end;
        v.push_back({start, end});
    }

    sort(v.begin(), v.end());

    int cnt =0;
    int upcnt =0;
    for (int i = 0 ; i < v.size(); i++) {
        if(v[i].first > upcnt)
            upcnt = v[i].first;

        while(upcnt < v[i].second) {
            upcnt += L;
            cnt++;
        }
    }
    cout << cnt;
}