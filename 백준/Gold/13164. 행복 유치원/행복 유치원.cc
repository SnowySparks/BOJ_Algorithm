#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#define f(a, b, c) for(int a=b;a<c;++a)
using namespace std;
vector<int> v; //서로 인접한 키차이 저장 (n-1개)
int arr[300001]; //키.

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n, k; cin >> n >> k;
    f(i, 0, n) cin >> arr[i];
    f(i, 1, n) v.push_back(arr[i] - arr[i-1]);
    sort(v.begin(), v.end());

    int ans = 0;
    f(i, 0, n-k) { //n-k개 키 차이만 더하기
        ans += v[i];
    }
    cout << ans;
}

