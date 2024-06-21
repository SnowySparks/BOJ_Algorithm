#include <iostream>
#define f(a, b, c) for(int a=b;a<c;++a)
using namespace std;
const int maxn = 1e6+1;
int n;
int arr[maxn], arrow_height[maxn+1];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    f(i, 0, n) cin >> arr[i];
    int ans = 0;
    f(i, 0, n) {
        if (arrow_height[arr[i]]) {
            arrow_height[arr[i]]--;
            arrow_height[arr[i]-1]++;
        }

        else {
            ans++;
            arrow_height[arr[i]-1]++;
        }
    }
    cout << ans;
    return 0;
}