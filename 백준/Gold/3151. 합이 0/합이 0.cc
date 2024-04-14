#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;
using ll = long long;

int arr[10000];
int cnt[25000];

int c(int x) {
    return cnt[x + 10000];
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    ll ans = 0;
    int n;
    cin >> n;
    for(int i = 0; i < n; ++i) {
        cin >> arr[i];
        cnt[arr[i] + 10000]++;
    }

    sort(arr, arr+n);

    for (int i = 0; i < n-2; ++i) {
        int l = i+1, r = n - 1;
        while (l < r)
        {
            int w = arr[i] + arr[l] + arr[r];
            if (w == 0) {
                // l, r 위치 값이 같은 경우 그 구간 내에서 조합이 이루어지는 것을 감안한 연슨
                if (arr[l] == arr[r]) ans += (1LL)*(r - l);
                // 아닌 경우, 오른쪽 기준 카운트
                else ans += (1LL)*c(arr[r]);
            }
            if (w <= 0) l++;
            else r--;
        }
    }
    cout << ans;

    return 0;
}

//세 수의 합이 0 인 모든 경우의 수 찾기
