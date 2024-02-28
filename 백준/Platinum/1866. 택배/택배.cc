#include <iostream>
#include <algorithm>
using namespace std;

int arr[3001];
int dp[3001];
int sum[3001];

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
	int n; cin >> n;

	for(int i=1; i<=n; i++) cin >> arr[i];
	sort(arr+1, arr+n+1);
	for(int i=1; i<=n; i++) sum[i] = sum[i-1] + arr[i];

	int t, h; cin >> t >> h;

	for(int i=1; i<=n; i++){
		dp[i] = dp[i-1] + arr[i] * t;
		for(int j=i; j>=1; j--){
			int mid = (i+j) >> 1;

			int left = (arr[mid] * (mid-j+1) - (sum[mid] - sum[j-1])) * t;
			int right = ((sum[i] - sum[mid-1]) - (arr[mid] * (i-mid+1))) * t;

			int cost = left + right + h;
			dp[i] = min(dp[i], dp[j-1] + cost);
		}
	}

	cout << dp[n];
}