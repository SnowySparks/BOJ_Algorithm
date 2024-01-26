#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
#define f(a,b,c) for(int a=b;a<c;a++)
int cat[5000];

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    int left = 0, right = n-1;
    f(i,0,n) cin >> cat[i];
    sort(cat, cat+n);
    int ans = 0;
    while (left < right) {
        if (cat[left] + cat[right] <= k) {
            ans++;
            left++;
            right--;
        }
        else right--;
    }
    cout << ans;
    return 0;
}