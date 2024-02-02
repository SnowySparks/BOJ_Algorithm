#include <iostream>
#include <vector>
#include <cstring>
using namespace std;
int N, M;
int dp[201][201];
int arr[201];
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> M;
    for (int i = 1 ; i <= N ; i++) {
        for (int j = 1 ; j <= M ; j++) {cin >> dp[i][j];} }
    for (int i = 1 ; i <= N ; i++) {
        for (int j = 1 ; j <= M ; j++) {
           dp[i][j]+=dp[i-1][j];}}
    int answer = -2E8, s;
    for (int i = 1 ; i <= N ; i++) { // row from i to j
        for (int j = i; j <= N; j++) {
            memset(arr,0,sizeof(arr));
            for (int k = 1 ; k <= M ; k++) {
                s = dp[j][k] - dp[i-1][k];
                arr[k] = max(s,arr[k-1]+s);
                answer = max(answer,arr[k]);
            }
        }
    }
    cout << answer;
    return 0;
}