#include <iostream>
#include <map>
#include <algorithm>
#include <vector>
#include <cstring>
using namespace std;
#define f(a,b,c) for(int a=b; a<c;a++)
pair<int, int> dt[300];
int dp[601][601];
int tlst[601];
map<int, int> tp;
vector<int> t;
int main(void) {
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int T; cin >> T;
    int n;
    while(T--) {
        cin >> n;
        f(i,0,n) { 
            cin >> dt[i].first >> dt[i].second;
            tlst[2*i] = dt[i].first;
            tlst[2*i+1] = dt[i].second;
        }   
        sort(tlst, tlst+(2*n));
        f(i,0,2*n) if (tp.find(tlst[i])==tp.end()) tp[tlst[i]] = tp.size();
        f(i,0,n) {
            int nland = tp[ dt[i].first], nout = tp[ dt[i].second];
            dp[ nland][ nout]++;
        }

        for (int end = 1 ; end < tp.size(); end++) {
            for (int start = end-1; start >=0; start--) {
                int max_v = 0;
                for (int k = end-1 ; k >start; k--) {
                    max_v = max(max_v,dp[start][k] + dp[k][end]);
                }
                dp[start][end] += max_v;
            }
        }
        cout << dp[0][tp.size()-1] <<'\n';

        tp.clear();
        memset(dp,0,sizeof(dp));
    }
    return 0;
}