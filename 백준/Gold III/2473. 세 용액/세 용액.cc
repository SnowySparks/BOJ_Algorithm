#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
long long arr[5000];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    for (int i = 0 ; i < n ; ++i) cin >> arr[i];
    sort(arr,arr+n);

    int l = 0, r = n-1;
    long long abs_min = 1e10;
    long long ans[3];
    //원래는 n^3 이나 어느 기준점을 두고 해당 기준점 이후 영역의 배열 부분을 two pointer로 탐색
    for (int i = 0; i < n -2 ; ++i) {//arr[i] 기준으로 두고 l, r 탐색
        int l = i+1, r = n-1;
        while (l < r) {
            long long a1 = arr[l];
            long long a2 = arr[r];

            if (abs_min > abs(a1 + a2 + arr[i])) {
                abs_min = abs(a1 + a2 + arr[i]);
                ans[0] = arr[i];
                ans[1] = arr[l];
                ans[2] = arr[r];
            }

            if (abs_min == 0) break;

            if (a1 + a2 + arr[i] > 0)  --r;
            else l++;
        }
        if (abs_min == 0) break;
    }
    cout << ans[0] << ' ' << ans[1] << ' ' << ans[2];
    return 0;
}