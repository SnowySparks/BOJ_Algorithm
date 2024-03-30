#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

pair<int ,int> arr[100001];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    long long total_people = 0;
    for (int i = 0; i < n; ++i) {
        cin >> arr[i].first >> arr[i].second;
        total_people += arr[i].second;
    }
    sort(arr, arr+n);
    long long prefix_people = 0;
    int ans = 0;
    for (; ans < n; ++ans) {
        prefix_people += arr[ans].second;
        if (prefix_people >= (total_people/2 + (total_people&1 ? 1 : 0 ))) break;
    }
    cout << arr[ans].first;
    return 0;
}