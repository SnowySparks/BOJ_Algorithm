#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int arr[10001];
int btw[10001];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;

    for (int i = 0; i < n; ++i) cin >> arr[i];
    sort(arr, arr+n);
    for (int i = 0; i < n-1; ++i) btw[i] = arr[i+1]-arr[i];
    sort( btw, btw+(n-1));

    int ans = 0;
    for (int i = 0; i < n-k; ++i) {
        ans += btw[i];
    }
    cout << ans;
    return 0;
}