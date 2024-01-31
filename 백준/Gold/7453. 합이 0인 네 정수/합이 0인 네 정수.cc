#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

unordered_map<long long, long long> save_left;
int main(void) {
    long long answer = 0;
    long long temp;
    long long a,b,c,d;
    int n; cin >> n;
    long long dt[4001][4];
    vector<long long> left_save;
    for (int i = 0; i < n; i++) {
        cin >> dt[i][0] >> dt[i][1] >> dt[i][2] >> dt[i][3];
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            left_save.push_back(dt[i][0] + dt[j][1]);
        }
    }
    sort(left_save.begin(),left_save.end());
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            temp = -(dt[i][2] + dt[j][3]);
            auto it1 = lower_bound(left_save.begin(),left_save.end(),temp);
            auto it2 = upper_bound(left_save.begin(),left_save.end(),temp);
            answer+=(it2 - it1);
        }
    }
    cout << answer;
}