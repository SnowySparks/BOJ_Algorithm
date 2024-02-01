#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void) {
    int a;
    cin >> a;
    vector<int> arr(a+1);//stairs
    for (int i=1;i<=a;i++) { 
        cin >> arr[i];
    }
    arr[0]=0;
    vector<int> dp(a+1);
    dp[1]=arr[1];
    dp[2]=arr[1]+arr[2];
    dp[3]=max(arr[1],arr[2])+arr[3];

    for (int i=4;i<=a;i++) {
        dp[i]=max(dp[i-3]+arr[i-1],dp[i-2])+arr[i];
    }
    cout<<dp[a]<<endl;
    return 0;
}