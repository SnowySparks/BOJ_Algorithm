#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define maxn 1000
#define dmaxn 1000000
using ll = long long;
ll arr[maxn];
ll darr[dmaxn];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    for (int i = 0 ; i < n; ++i) cin >> arr[i];
    int cnt = 0;
    for (int i = 0; i < n ; ++i) {
        for (int j = 0; j < n; ++j) {
            darr[cnt++] = arr[i]+arr[j];
        }
    }
    sort(arr,arr+n);
    sort(darr,darr+cnt);
    ll ans = -1;
    
    for (int i = n-1; i >= 0; --i) { // arr[i] 가 a + b + c의 결과라고 가정
        for (int j = i ; j >= 0 ; --j) {
            ll ab = arr[i]-arr[j]; // a + b +c = d <-> a + b = d - c, d=arr[i], c = arr[j]
            int l = 0, r = cnt -1;
            // 이분탐색
            while (l <= r)
            {   
                //찾음
                int mid = (l+r)>>1;
                if (darr[mid] == ab) {
                    cout << arr[i];
                    return 0;
                }
                else if (darr[mid] < ab) l = mid + 1;
                else r = mid-1;
            }
        }
    }   
    return 0;
}