#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int dp[500][500];
int main(void) {
    int a;
    cin >> a;

    vector<vector<int> > v(a);

    for (int i = 0; i < a; i++) {
        for (int j = 0; j <= i; j++) {
            int p;
            cin>>p;
            v[i].push_back(p);
        }
    }

    dp[0][0]=v[0][0];

    for (int i = 1; i < a; i++) {
        for (int j = 0; j < v[i].size(); j++) {
            if (j==0) {
                dp[i][0]=dp[i-1][0]+v[i][0];
            }
            else if (j==i) {
                dp[i][j]=dp[i-1][j-1]+v[i][j];
            }
            else {
                dp[i][j]=max(dp[i-1][j-1],dp[i-1][j])+v[i][j];
            }
        }
    }
    

    cout<<*max_element(dp[a-1],dp[a-1]+a)<<endl;
    return 0;
}