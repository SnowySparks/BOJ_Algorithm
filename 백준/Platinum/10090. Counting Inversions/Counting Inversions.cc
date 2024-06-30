#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
using namespace std;
const int max_n = 1000000;
int n;
int arr[max_n];
int temp[max_n];
long long ans = 0;


// 오른쪽 부분이 스왑 되서 들어가면 왼쪽 나머지 부분과 전부 inversino(선 겹침) 되기 때문
void merge(int left, int right) {
    if (left == right) return;
    int mid = (left + right) >> 1;
    merge(left, mid);
    merge(mid+1, right);

    int l = left, r = mid+1, k =left;
    while(l <= mid && r <= right) {
        if (arr[l] <= arr[r]) {
            temp[k++] = arr[l++];
        }
        else {
            temp[k++] = arr[r++];
            ans += (long long) (mid - l + 1);
        }
    }
    while(l <= mid) {
        temp[k++] = arr[l++];
    }
    while(r <= right) {
        temp[k++] = arr[r++];
    }
    for (int i = left; i<= right; ++i) {
        arr[i] = temp[i];
    }
}

// 세그먼트(혹은 펜윅) 으로도 되고, 머지 소트 트리를 이용
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    for (int i = 0; i < n; ++i) cin >> arr[i];
    merge(0, n-1);
    cout << ans;
    return 0;
}