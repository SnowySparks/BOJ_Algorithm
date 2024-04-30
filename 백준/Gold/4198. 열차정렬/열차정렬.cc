#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;
#define f(a, b, c) for (int a = b; a < c; ++a)
int n;
const int maxn = 2e3;

int arr[maxn], dp1[maxn], dp2[maxn]; //input, 증가(lis), 감소 (lds)
int ans = 0;

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    vector<int> tmp;
    cin >> n;
    if (!n) {
        cout << 0; return 0;
    }
    f(i, 0, n) cin >> arr[i];

    for (int i = n-1; i >= 0; --i) { //기준점
        dp1[i] = 1; dp2[i] = 1; //자기자신
        for (int j = i+1; j < n; ++j) {
            if (arr[i] < arr[j]) dp1[i] = max(dp1[i], dp1[j] + 1); // 해댱 인덱스 기준 자기 포함 lis 최대 길이
            if (arr[i] > arr[j]) dp2[i] = max(dp2[i], dp2[j] + 1); // 해당 인덱스 기준 자기 포함 lds 최대 길이
        }
    }

    int ans = 0;
    f(i, 0, n) ans = max(ans, dp1[i] +dp2[i] -1);
    cout << ans;

    return 0;
}