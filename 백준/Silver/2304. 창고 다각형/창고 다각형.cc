#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;
int arr[1001];

//스택 구조는 사용 안하지만 충분히 스택 구조를 사용할 수 있음
// 가장 높은 블럭 기준 왼쪽, 오른쪽 갈수록 기울기가 낮아지는 방향으로 가야함
// 중간에 더 높은 블럭이 나오는 경우를 탐색하기 위해서 스택...을 이용하는 방법인듯
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    int l, h;

    int max_right = -1;
    for (int i = 0; i < n; ++i) {
        cin >> l >> h;
        max_right = max(max_right, l);
        arr[l] = h;
    }
    int max_loc = max_element(arr, arr+max_right + 1) - arr;
    int ans = 0;
    int max_h = 0;
    for (int i = max_right; i > max_loc ; --i) {
        max_h = max(max_h, arr[i]);
        ans += max_h;
    }
    max_h = 0;
    for (int i = 1; i < max_loc ; ++i) {
        max_h = max(max_h, arr[i]);
        ans += max_h;
    }
    ans += arr[max_loc];
    cout << ans;
    return 0;
}