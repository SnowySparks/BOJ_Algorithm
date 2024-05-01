#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
int n;
pair<int, int> arr[50]; // input에서 ( input_value, i )
int p[50]; // arr sort후 p[arr.sec] = i

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cin >> n;
    int tmp;
    for(int i = 0; i < n; ++i) {
        cin >> tmp;
        arr[i] = {tmp, i};
    }
    sort(arr,arr+n);
    for (int i = 0; i < n; ++i) p[arr[i].second] = i;
    for (int i = 0; i < n; ++i) cout << p[i] <<' ';
    return 0;
}