#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
using namespace std;

double arr[16][16];
double dp[16][1<<16];
pair<int, int> cord[16];
int n;
const double inf = 1e9;

double dist(const pair<int,int> &a, const pair<int,int> &b) {
    return sqrt(pow(a.first - b.first,2) + pow(a.second - b.second,2));
}

double dfs(int nowcity, int state) {
    if (state == ((1<<n) -1)) return arr[nowcity][0]; //마지막 도착시, nowcity -> 0 가는 길 찾기
    double &ret = dp[nowcity][state]; 
    if (ret != (double)-1.0) return ret; //dp
    ret = inf;
    for (int i = 0 ; i < n; ++i) {
        if (state & (1<<i)) continue; //이미 거친 도시 안가기
        ret = min(ret, dfs(i,state|(1<<i)) + arr[nowcity][i]); //다음 상태 재귀 호출
    }
    return ret;
}

int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(0); cout.tie(0);
    cout<<fixed;
    cout.precision(9);
    cin >> n;
    for (int i = 0; i < n; ++i) {
        cin >> cord[i].first >> cord[i].second;
    }
    fill(&dp[0][0], &dp[15][1<<16], -1.0);
    for (int i = 0 ; i < n-1; ++i) {
        for (int j = i+1; j < n; ++j) {
            arr[i][j] = dist(cord[i],cord[j]);
            arr[j][i] = arr[i][j];
        }
    }

    cout << dfs(0, 0);
    return 0;
}